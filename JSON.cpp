//
// Created by Sierra Kilo on 26-Feb-19.
//

#include "JSON.h"

nlohmann::json JSON::prepare_json_reply(std::string status, std::map<std::string, std::string> data) {
    // msg_type is "request" or "response
    // msg_content describes the data content of the message
    // for example, identification_info

    nlohmann::json json_msg;

    json_msg = {
            {"status", status},
            {"data", data}
    };

    return json_msg;
}

nlohmann::json JSON::convert_string_to_json(std::string received_msg) {
    nlohmann::json json_msg = nlohmann::json::parse(received_msg);
};