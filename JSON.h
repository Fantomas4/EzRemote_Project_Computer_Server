//
// Created by Sierra Kilo on 26-Feb-19.
//

#ifndef EZREMOTE_PROJECT_JSON_H
#define EZREMOTE_PROJECT_JSON_H


#include <string>
#include "nlohmann/json.hpp"

class JSON {

public:
    static nlohmann::json prepareJsonReply(std::string status, std::map<std::string, std::string> data);
//    static nlohmann::json convert_string_to_json(std::string received_msg);

    static std::string convertJsonToString(nlohmann::json jsonObj);
};


#endif //EZREMOTE_PROJECT_JSON_H
