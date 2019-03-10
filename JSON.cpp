//
// Created by Sierra Kilo on 26-Feb-19.
//

#include "JSON.h"

nlohmann::json JSON::prepareJsonReply(std::string status, std::map<std::string, std::string> data) {

    nlohmann::json json_msg;

    json_msg = {
            {"status", status},
            {"data", data}
    };

    return json_msg;
}

std::string JSON::convertJsonToString(nlohmann::json jsonObj) {
    return jsonObj.dump(4);
}