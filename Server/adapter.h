#ifndef ADAPTER_H
#define ADAPTER_H

#include <cpprest/http_listener.h>
#include <iostream>
#include <string>
#include <vector>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/base_uri.h>
#include <cpprest/json.h>
#include <pplx/pplxcancellation_token.h>
#include <pplx/pplx.h>



class Adapter
{
public:
    Adapter();
    Adapter(std::string);

    //char tagDecider(std::string method,std::string endpoint);
    std::string endpointDecider(char);
    std::string methodDecider(char);

    char decideTheTag(std::string method, std::string endPoint);
    void read_P_R_U();

    std::string serialize(web::http::http_request,std::string);
    inline std::string getVal(){ return value; }
    void setVal(std::string received);
    std::string setData(std::vector< uint8_t > TLVData);
    inline char getTag() { return  tag; }
    inline void setTag(std::string received){ tag = received[1]; }
    void setLength(std::string received);
    inline std::string getLength() { return length; }

    inline void setUrl(std::string m_url) { url = m_url; }
    inline std::string getUrl(){ return url; }

    inline void setPort(std::string m_port) { port = m_port; }
    inline std::string getPort(){ return port; }

    inline void setRate(std::string m_rate) { rate = m_rate; }
    inline std::string getRate(){ return rate; }
    

private:
    std::string port;
    std::string rate;
    std::string url;

    char tag;
    std::string length;
    std::string value;
    //added
    //void methodChooser(char);
};

#endif // ADAPTER_H
