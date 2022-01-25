#include "MqttClient.h"

#include "topics.h"

using namespace std;

MqttClient::MqttClient(const string &address, const string &clientID)
        : client(address, clientID)
        , conOptions(mqtt::connect_options_builder().clean_session(false).finalize())
{

}

MqttClient::~MqttClient() {
    if (client.is_connected()) {
        cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
        client.unsubscribe(Topics::global_topics.at("motor"))->wait();
        client.unsubscribe(Topics::global_topics.at("control"))->wait();
        client.unsubscribe(Topics::global_topics.at("experiment"))->wait();
        client.stop_consuming();
        client.disconnect()->wait();
        cout << "OK" << endl;
    } else {
        cout << "\nClient is already disconnected" << endl;
    }
}

void MqttClient::connectToServer() {
    cout << "Connecting to the MQTT server..." << flush;

    // Start consumer before connecting to make sure to not miss messages
    startConsuming();

    // Connect to the server
    auto tok = client.connect(conOptions);
    tok->wait_for(TIMEOUT);

    // Getting the connect response will block waiting for the
    // connection to complete.
    mqtt::connect_response rsp = tok->get_connect_response();

    subscribeToTopics(rsp);

    cout << "OK" << endl;
}

void MqttClient::subscribeToTopics(const mqtt::connect_response &rsp) {
    // If there is session present, then we need to subscribe
    if (rsp.is_session_present()) {
        client.subscribe(Topics::global_topics.at("motor"), QoS)->wait();
        client.subscribe(Topics::global_topics.at("control"), QoS)->wait();
        client.subscribe(Topics::global_topics.at("experiment"), QoS)->wait();
    }
}

void MqttClient::startConsuming() {
    client.start_consuming();
}

void MqttClient::stopConsuming() {
    client.stop_consuming();
}

void MqttClient::publish(const string &topic, const string &string_message, bool retained) {
    const char *message = string_message.c_str();
    client.publish(topic, message, strlen(message), QoS, retained);
}

std::tuple<bool, std::string, std::string> MqttClient::tryConsumeMessage() {
    string topic, message;
    bool received = false;

    // If message was read
    mqtt::const_message_ptr msg;
    if (client.try_consume_message(&msg)) {
        topic = msg->get_topic();
        message = msg->to_string();
        received = true;
    }

    return make_tuple(received, topic, message);
}

std::tuple<bool, std::string, std::string>
MqttClient::tryConsumeMessage(int timeout) {
    string topic, message;
    bool received = false;

    // If message was read
    mqtt::const_message_ptr msg;
    if (client.try_consume_message(&msg)) {
        topic = msg->get_topic();
        message = msg->to_string();
        received = true;
    }

    if (timeout > 0) {
        this_thread::sleep_for(chrono::milliseconds(timeout));
    }

    return make_tuple(received, topic, message);
}
