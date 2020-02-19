#include "myserver.h"
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include <vector>
#include "timeoutserial.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include "adapter.h"
#include <fstream>

using namespace web;
using namespace utility;
using namespace http;
using namespace http::experimental::listener;

MyServer::MyServer(utility::string_t url) : m_listener(url)
{
    m_listener.support(web::http::methods::GET,std::bind(&MyServer::handle_get,this,std::placeholders::_1));
    m_listener.support(web::http::methods::POST,std::bind(&MyServer::handle_post,this,std::placeholders::_1));
    //m_listener.support(web::http::methods::PATCH,std::bind(&MyServer::handle_patch,this,std::placeholders::_1));

}

void MyServer::handle_get(http_request message)
{
    try{
    Adapter adapter;
    char *s = new char [15];
    char *port = new char [15];
    char *rate = new char [15];
    ucout<<message.to_string()<<std::endl;
    std::fstream config;
    config.open("config.txt");
    for(int i = 0 ; i < 2 ; i++)
    {
        config.getline(s,15,'=');
        if(i==0)
                config.getline(port,15,'\n');
        else if(i==1)
                config.getline(rate,15,'\n');
    }
    //std::string msg=message.extract_utf8string().get();
    std::string msg=adapter.serialize(message,"GET");
    std::cout<<"uri is :"<<message.request_uri().path()<<std::endl;
    std::cout<<"endpoint is "<<adapter.endpointDecider(adapter.getTag(msg))<<std::endl;
    std::cout<<"method is "<<adapter.methodDecider(adapter.getTag(msg))<<std::endl;
    std::cout<<"message is "<<msg<<std::endl;
    //std::cout<<"received string is :" <<msg<<std::endl;
    //char tag = adapter.getTag(msg);
    //char len = adapter.getLength(msg);
    //std::string val = adapter.getVal(msg);
    //std::cout<<"tag is "<< tag <<"length is "<<len << "val is" << val<<std::endl;
    TimeoutSerial serialDev(port,std::atoi(rate));
    //std::cout<<"serial is:"<<serialDev.isOpen()<<std::endl;
    serialDev.setTimeout(boost::posix_time::seconds(5));
    //std::cout<<"after write"<<std::endl;
    serialDev.writeString(msg+'\n');
    std::string resp=serialDev.readStringUntil();
    //std::cout<<"reading :"<<resp<<std::endl;
    //std::cout<<adapter.sttoj(msg)<<std::endl;
    message.reply(status_codes::OK,resp,"text/plain charset=utf-8");
    //message.reply(status_codes::OK,"transmission complete","text/plain charset=utf-8");

    }
    catch (boost::system::system_error& e)
    {
        std::cout<<"error:"<<e.what()<<std::endl;
    }
}

/*void MyServer::handle_put(http_request message)
{
    try{
    Adapter adapter;
    char *s = new char [15];
    char *port = new char [15];
    char *rate = new char [15];
    ucout<<message.to_string()<<std::endl;
    std::fstream config;
    config.open("config.txt");
    for(int i = 0 ; i < 2 ; i++)
    {
        config.getline(s,15,'=');
        if(i==0)
                config.getline(port,15,'\n');
        else if(i==1)
                config.getline(rate,15,'\n');
    }
    //std::string msg=message.extract_utf8string().get();
    std::string msg=adapter.serialize(message,"PUT");
    std::cout<<msg<<"end of msg"<<std::endl;
    std::cout<<adapter.endpointDecider(adapter.getTag(msg))<<"debug2"<<std::endl;
    //std::cout<<"received string is :" <<msg<<std::endl;
    //char tag = adapter.getTag(msg);
    //char len = adapter.getLength(msg);
    //std::string val = adapter.getVal(msg);
    //std::cout<<"tag is "<< tag <<"length is "<<len << "val is" << val<<std::endl;
    //TimeoutSerial serialDev(port,std::atoi(rate));
    //std::cout<<"serial is:"<<serialDev.isOpen()<<std::endl;
    //serialDev.setTimeout(boost::posix_time::seconds(5));
    //std::cout<<"after write"<<std::endl;
    //serialDev.writeString(msg+'\n');
    //std::string resp=serialDev.readStringUntil();
    //std::cout<<"reading :"<<resp<<std::endl;
    //std::cout<<adapter.sttoj(msg)<<std::endl;
    //message.reply(status_codes::OK,resp,"text/plain charset=utf-8");
    message.reply(status_codes::OK,"transmission complete","text/plain charset=utf-8");

    }
    catch (boost::system::system_error& e)
    {
        std::cout<<"error:"<<e.what()<<std::endl;
    }
}*/

void MyServer::handle_post(http_request message)
{
    ucout<<"message.to_string()"<<std::endl;
    message.reply(status_codes::OK);
    return ;
}

void MyServer::handle_patch(http_request message)
{
    ucout<<"message.to_string()"<<std::endl;
    message.reply(status_codes::OK);
    return ;
}
