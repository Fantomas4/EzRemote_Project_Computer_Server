//
// Created by Sierra Kilo on 26-Feb-19.
//

#ifndef EZREMOTE_PROJECT_JSON_H
#define EZREMOTE_PROJECT_JSON_H


#include <string>
#include "nlohmann/json.hpp"

class JSON {

public:
    static nlohmann::json prepare_json_reply(std::string status, std::map<std::string, std::string> data);
//    static nlohmann::json convert_string_to_json(std::string received_msg);
};


#endif //EZREMOTE_PROJECT_JSON_H
