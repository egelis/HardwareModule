#ifndef TEST_CONTROLHARDWARE_MQTTCLIENT_H
#define TEST_CONTROLHARDWARE_MQTTCLIENT_H

#include <string>
#include <chrono>
#include <tuple>

#include <mqtt_control/mqtt_control.h>

class MqttClient {
public:
    MqttClient(const std::string &address, const std::string &clientID);

    void connectToServer();

    void startConsuming();

    void stopConsuming();

    void publish(const std::string &topic, const std::string &string_message, bool retained = false);

    std::tuple<bool, std::string, std::string> tryConsumeMessage();

    std::tuple<bool, std::string, std::string>
    tryConsumeMessage(int timeout);

    ~MqttClient();

private:
    const uint8_t QoS{1};
    const std::chrono::seconds TIMEOUT{std::chrono::seconds(10)};

    mqtt::async_client client;
    mqtt::connect_options conOptions;

private:
    void subscribeToTopics(const mqtt::connect_response &rsp);
};


#endif //TEST_CONTROLHARDWARE_MQTTCLIENT_H
