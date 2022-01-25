#include <iostream>
#include <chrono>

#include <mqtt_control/mqtt_control.h>
#include "ModbusLib/serial.hpp"
#include "ModbusLib/modbus_ls_dust.hpp"
#include "topics.h"

#include "MqttClient.h"
#include "utils.h"
#include "states.h"
#include "stopwatch.h"

using namespace std;

const string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};
const string DFLT_CLIENT_ID{"HardwareModule"};

const int MIN_LOOP_DURATION{100};

int main(int argc, char *argv[]) {
    // Initialization of server
    string address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
           clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

    MqttClient client(address, clientID);

    // Declaration and initialization of devices
    serial                      serial0;
    modbus_ls_dust_motor        motor;
    modbus_ls_dust_control      control;
    modbus_ls_dust_experimental experimental;

    serial0     .init("/dev/ttyUSB0", 115200);
//    serial0     .init("/dev/ttyS0", 115200);
    motor       .init(&serial0, 1, "motor");
    control     .init(&serial0, 3, "control");
    experimental.init(&serial0, 5, "exper");

    serial0.openport();
    // End of initializations

    try {
        client.connectToServer();

        // Consume messages
        cout << "Waiting for messages on topic" << Topics::global_topics.at("motor") << ", "
                                                << Topics::global_topics.at("control") << ", "
                                                << Topics::global_topics.at("experiment") << endl;

        StopWatch motorSW, lightSW, knivesSw, controlTempPresSW, experTempPresSW, lifeStatusSW, loopDurationSW;
        while (true) {
            if (lifeStatusSW.countInSeconds() >= 2) {
                client.publish(Topics::hw_status_topics.at("life_status"), "1", true);

                if (!motor.error) {
                    client.publish(Topics::hw_status_topics.at("motor_life_status"), "1", true);
                }
                if (!control.error) {
                    client.publish(Topics::hw_status_topics.at("control_life_status"), "1", true);
                }
                if (!experimental.error) {
                    client.publish(Topics::hw_status_topics.at("exper_life_status"), "1", true);
                }

                lifeStatusSW.reset();
            }

            // If all devices have error, then try to fix them publishing messages about error
            if (motor.error && control.error && experimental.error)
            {
                if (States::isConsuming) {
                    client.stopConsuming();
                    States::isConsuming = false;
                }

                client.publish(Topics::hw_status_topics.at("motor_life_status"), "0", true);
                client.publish(Topics::hw_status_topics.at("control_life_status"), "0", true);
                client.publish(Topics::hw_status_topics.at("exper_life_status"), "0", true);

                reconnectPort(serial0, motor, control, experimental);

                this_thread::sleep_for(chrono::seconds(2));
            }

            // Check devices
            // Here an error can change status in 1 or stay in 0
            const string pos       = to_string(motor.getPosition());
            const string ctrl_temp = to_string(control.getTemperature());
            const string exp_temp  = to_string(experimental.getTemperature());

            // If the errors in all devices is present, then skip next code
            if (motor.error && control.error && experimental.error) {
                continue;
            } else {
                if (!States::isConsuming) {
                    client.startConsuming();
                    States::isConsuming = true;
                }
            }

            if (!motor.error)
            {
                if (motorSW.countInSeconds() >= 1 && States::isMotorStarted) {
                    const string vel = to_string(motor.getVelocity());
                    const string pos = to_string(motor.getPosition());
                    const string end_status = to_string(motor.getPositionEndStatus());

                    client.publish(Topics::motor_topics.at("position"), pos, true);
                    client.publish(Topics::motor_topics.at("velocity"), vel, true);
                    client.publish(Topics::motor_topics.at("end_status"), end_status, true);

                    motorSW.reset();
                }
            }
            else {
                client.publish(Topics::hw_status_topics.at("motor_life_status"), "0", true);
            }

            if (!control.error)
            {
                if (knivesSw.countInSeconds() >= 1 && States::isKnivesStarted) {
                    const string current1 = to_string(control.getKnifeCurrentOne());
                    const string current2 = to_string(control.getKnifeCurrentTwo());

                    client.publish(Topics::control_topics.at("knife_current1"), current1, true);
                    client.publish(Topics::control_topics.at("knife_current2"), current2, true);

                    knivesSw.reset();
                }

                if (controlTempPresSW.countInSeconds() >= 10) {
                    const string ctrl_temp = to_string(control.getTemperatureCPU());
                    const string ctrl_pres = to_string(control.getPressure());

                    client.publish(Topics::control_topics.at("temperature"), ctrl_temp, true);
                    client.publish(Topics::control_topics.at("pressure"), ctrl_pres, true);

                    controlTempPresSW.reset();
                }
            }
            else {
                client.publish(Topics::hw_status_topics.at("control_life_status"), "0", true);
            }

            if (!experimental.error)
            {
                if (lightSW.countInSeconds() >= 1) {
                    if (States::isLight1Started) {
                        const string current = to_string(experimental.getLightCurrentOne());
                        client.publish(Topics::experimental_topics.at("light_current1"), current, true);
                    }

                    if (States::isLight2Started) {
                        const string current = to_string(experimental.getLightCurrentTwo());
                        client.publish(Topics::experimental_topics.at("light_current2"), current, true);
                    }

                    lightSW.reset();
                }

                if (experTempPresSW.countInSeconds() >= 10) {
                    const string exp_temp = to_string(experimental.getTemperatureCPU());
                    const string exp_pres = to_string(experimental.getPressure());

                    client.publish(Topics::experimental_topics.at("temperature"), exp_temp, true);
                    client.publish(Topics::experimental_topics.at("pressure"), exp_pres, true);

                    /*string disc_status = to_string(experimental.getDisclousureStatus());
                    client.publish(Topics::experimental_topics.at("disclosure_status"), disc_status, true);*/

                    experTempPresSW.reset();
                }
            }
            else {
                client.publish(Topics::hw_status_topics.at("exper_life_status"), "0", true);
            }

            auto[received, topic, message] = client.tryConsumeMessage(
                    static_cast<int>(MIN_LOOP_DURATION - loopDurationSW.countInMilliseconds())
            );
            loopDurationSW.reset();

            if (!received) {
                continue;
            }

            // Handle topics

            auto params = splitIntoWords(message);

            // Motor
            if (!motor.error)
            {
                if (topic == Topics::motor_topics.at("start") && params.size() == 2) {
                    cout << "/motor/start" << endl;
                    motor.start(stof(params[0]), stof(params[1]));
                    States::isMotorStarted = true;
                } else if (topic == Topics::motor_topics.at("stop")) {
                    cout << "/motor/stop" << endl;
                    motor.stop();
                    States::isMotorStarted = false;
                } else if (topic == Topics::motor_topics.at("timeout") && message == "?") {
                    cout << "/motor/timeout" << endl;
                    string timeout = to_string(motor.getTimeout());
                    client.publish(Topics::motor_topics.at("timeout"), timeout, true);
                } else if (topic == Topics::motor_topics.at("end_status") && message == "?") {
                    cout << "/motor/end_status" << endl;
                    string end_status = to_string(motor.getPositionEndStatus());
                    client.publish(Topics::motor_topics.at("end_status"), end_status, true);
                } else if (topic == Topics::motor_topics.at("ampl_voltage") && message == "?") {
                    cout << "/motor/amplitude_voltage" << endl;
                    string ampl_voltage = to_string(motor.getAmplitudeVoltage());
                    client.publish(Topics::motor_topics.at("ampl_voltage"), ampl_voltage, true);
                } else if (topic == Topics::motor_topics.at("ampl_current") && message == "?") {
                    cout << "/motor/amplitude_current" << endl;
                    string ampl_current = to_string(motor.getAmplitudeCurrent());
                    client.publish(Topics::motor_topics.at("ampl_current"), ampl_current, true);
                }
            }
            // Control
            if (!control.error)
            {
                // Vibrobank
                if (topic == Topics::control_topics.at("vibrobank") && params.size() == 4) {
                    cout << "/control/vibrobank" << endl;
                    control.VibroBank(stof(params[0]), stof(params[1]),
                                      stoi(params[2]), stoi(params[3]));
                }
                // Openbank
                else if (topic == Topics::control_topics.at("openbank") && params.size() == 3) {
                    cout << "/control/openbank" << endl;
                    control.OpenBank(stof(params[0]), stof(params[1]),
                                     stoi(params[2]));
                } else if (topic == Topics::control_topics.at("overburning_current") && message == "?") {
                    cout << "/control/overburning_current" << endl;
                    string current = to_string(control.getOpenOverburningCurrent());
                    client.publish(Topics::control_topics.at("overburning_current"), current, true);
                }
            }
            // Experimental
            if (!experimental.error)
            {
                //Lights
                if (topic == Topics::experimental_topics.at("light_enable1") && params.size() == 1) {
                    cout << "/experiment/light_enable1" << endl;
                    experimental.LightOne(stof(params[0]));
                    States::isLight1Started = true;
                } else if (topic == Topics::experimental_topics.at("light_enable2") && params.size() == 1) {
                    cout << "/experiment/light_enable2" << endl;
                    experimental.LightTwo(stof(params[0]));
                    States::isLight2Started = true;
                }
                // Disclosure
                else if (topic == Topics::experimental_topics.at("disclosure") && params.size() == 1) {
                    cout << "/experiment/disclosure" << endl;
                    experimental.Disclousure(stof(params[0]));
                } else if (topic == Topics::experimental_topics.at("disclosure_status") && message == "?") {
                    cout << "/experiment/disclosure_status" << endl;
                    string disc_status = to_string(experimental.getDisclousureStatus());
                    client.publish(Topics::experimental_topics.at("disclosure_status"), disc_status, true);
                }
                // Syncro and knives
                else if (topic == Topics::experimental_topics.at("knives_syncrocam_enable") && params.size() == 4) {
                    cout << "/experiment/knives_syncrocam_enable" << endl;
                    experimental.SyncroCameras(stof(params[0]), stof(params[1]),
                                               stof(params[2]), stof(params[3]));
                    States::isKnivesStarted = true;
                }
            }
        }
    }
    catch (const mqtt::exception &exc) {
        cerr << exc.what() << endl;
        return 1;
    }

    return 0;
}
