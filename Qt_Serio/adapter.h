#ifndef ADAPTER_H
#define ADAPTER_H
#include "cpprest/http_listener.h"
#include <iostream>
#include <string>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/base_uri.h>
#include <cpprest/json.h>
#include <pplx/pplxcancellation_token.h>
#include <pplx/pplx.h>



class Adapter
{
public:
    std::string serialize(web::http::http_request,std::string);
    std::string getVal(std::string);
    char getTag(std::string);
    char getLength(std::string);
    char tagDecider(std::string method,std::string endpoint);
    std::string endpointDecider(char);
    std::string methodDecider(char);
};

#endif // ADAPTER_H
