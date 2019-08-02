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

    static nlohmann::json prepareJsonRequest(std::string request, std::map<std::string, std::string> data);

    static std::string convertJsonToString(nlohmann::json jsonObj);
};


#endif //EZREMOTE_PROJECT_JSON_H
