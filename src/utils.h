#ifndef TEST_CONTROLHARDWARE_UTILS_H
#define TEST_CONTROLHARDWARE_UTILS_H

#include <mqtt_control/mqtt_control.h>

#include "MqttClient.h"
#include "topics.h"

void reconnectPort(serial &serial0, modbus_ls_dust_motor &motor, modbus_ls_dust_control &control,
                   modbus_ls_dust_experimental &experimental) {
    serial0.closeport();
    serial0.openport();

    motor.reset();
    control.reset();
    experimental.reset();
}

vector<string> splitIntoWords(const string &str) {
    vector<string> result;

    auto str_begin = begin(str);
    const auto str_end = end(str);

    while (true) {
        auto it = find(str_begin, str_end, ' ');
        string word = string{str_begin, it};
        if (!word.empty()) {
            result.emplace_back(word);
        }
        if (it == str_end) {
            break;
        } else {
            str_begin = it + 1;
        }
    }

    return result;
}

#endif //TEST_CONTROLHARDWARE_UTILS_H
