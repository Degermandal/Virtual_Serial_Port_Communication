#include "adapter.h"

char Adapter::tagDecider(std::string method, std::string endpoint)
{
    if(method=="GET")
    {
        if(endpoint=="/api/info")
            return '\x01';
    }
}

std::string Adapter::serialize(web::http::http_request msg, std::string method)
{
    std::string message;
    Adapter adapter;
    message=message + '\x02';
    message=message + adapter.tagDecider(method,msg.request_uri().path());
    message=message + (char) msg.extract_utf8string().get().length();
    message = message + msg.extract_utf8string().get();
    message = message + '\x03';
    return message;
}

std::string Adapter::getVal(std::string msg)
{
    std::string val;
    for(int i=3;i<msg.length();i++)
           val=val+msg[i];
    return val;

}

char Adapter::getTag(std::string msg)
{
    return msg[1];
}

char Adapter::getLength(std::string msg)
{
    return msg[2];
}

std::string Adapter::methodDecider(char tag)
{
    if(tag < '\x11')
        return "GET";
    else if (tag < '\x27')
         return "POST";
    else {
        return "PATCH";
    }
}

std::string Adapter::endpointDecider(char tag)
{
    if(tag=='\x01')
        return "/api/info";
}
