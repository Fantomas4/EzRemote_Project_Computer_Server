//
// Created by Sierra Kilo on 26-Feb-19.
//

#ifndef EZREMOTE_PROJECT_JSON_H
#define EZREMOTE_PROJECT_JSON_H


#include <string>
#include "nlohmann/json.hpp"

class JSON {
    nlohmann::json generate_json_msg(std::string status, std::map<std::string, std::string> data);
};


#endif //EZREMOTE_PROJECT_JSON_H
