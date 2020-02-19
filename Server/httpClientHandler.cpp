#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_msg.h>

#include "httpClientHandler.hpp"
//#include "TagDecider.h"
#include "adapter.h"
#include "TLV.h"
#include "TimeoutSerial.h"

#include <iostream>

Serio::HttpClientHandler::HttpClientHandler()
{
    
}

Serio::HttpClientHandler::HttpClientHandler(Adapter &m_adap)
{
    adap = m_adap;
}


/* Serio::HttpClientHandler::HttpClientHandler(std::vector<uint8_t> package)
{
    setHandlerTag(package[1]);
} */

std::vector<std::string> Serio::HttpClientHandler::mySplit(const std::string &myStr,  const char &ch)
{
    std::vector<std::string> myVec;
    size_t pos = myStr.find(ch);
    size_t initialPos = 0;
    myVec.clear();
    while(pos != std::string::npos)
    {
        myVec.push_back(myStr.substr(initialPos, pos - initialPos));
        initialPos = pos+1;
        pos = myStr.find(ch, initialPos);
    }
    myVec.push_back(myStr.substr(initialPos, std::min(pos,myStr.size()) - initialPos+1));

    return myVec;
}

int Serio::HttpClientHandler::handleTLV(TLV tlv){
    
    switch(tlv.getTag()){
        case 0x30: /* Login Post */
            try{
                std::string username = "";
                std::string password = "";
                
                std::string str;
                for(auto val : tlv.getValue())
                {
                    str += val;
                }
                std::vector<std::string> myData = mySplit(str, '"');
                for(auto val: myData)
                {
                    std::cout<<"Sp->"<<val<<std::endl;
                }
                username = myData[3];
                password = myData[7];
                std::cout<<"username->"<<username<<std::endl;
                std::cout<<"password->"<<password<<std::endl;
                // TODO: extract username & passwrod from data and send to handleLoginPost
                handleLoginPost(username, password);

                return 0;
            }catch(std::exception &e){
                return 1;
            }
            break;
    }

    return 0;
}

/* void Serio::HttpClientHandler::handleLoginPost(std::string username, std::string password){
    printf("--%s--\n", __FUNCTION__);

    Adapter adapter;
    adapter.read_P_R_U();
    
    std::cout<<"ad.end1-->"<<adap.endpointDecider(adap.getTag()) <<std::endl;
    web::http::client::http_client client(U(adapter.getUrl()));
    web::http::uri_builder uri(U(adap.endpointDecider(adap.getTag())));
    std::cout << "uri to query: " << uri.to_string() << std::endl;
    printf("check1\n");
    pplx::task<web::http::http_response> resp = client.request(web::http::methods::POST, uri.to_string());
    //std::cout<<"resp->"<<resp<<std::endl;
    printf("check2\n");

    resp.then([=](pplx::task<web::http::http_response> task) mutable {
        printf("check3.\n");
        web::http::http_response response = task.get();
        printf("check4\n");
        std::cout<<"received response status code: "<< response.status_code()<<std::endl;
        printf("check5\n");
        std::string str = response.extract_utf8string().get();
        printf("check6\n");
        std::cout<<"port->"<<adapter.getPort()<<" ---- rate->"<< std::stoi(adapter.getRate()) <<std::endl;
        TimeoutSerial serial(adapter.getPort(),std::stoi(adapter.getRate()));
        printf("check7\n");
        serial.setTimeout(boost::posix_time::seconds(0));
        serial.writeString(str+'\x03');
        std::cout<<"str->" << str<<std::endl;
        printf("check8\n");
    });   

printf("check9\n");
   // printf("HIIIII\n");
}
 */

void Serio::HttpClientHandler::handleLoginPost(std::string username, std::string password){
    printf("--%s--\n", __FUNCTION__);
    
    Adapter adapter;
    adapter.read_P_R_U();
    
    std::cout<<"ad.end1-->"<<adap.endpointDecider(adap.getTag()) <<std::endl;
    
    web::http::client::http_client client(U(adapter.getUrl()));
    web::http::uri_builder uri(U(adap.endpointDecider(adap.getTag())));
    std::cout << "uri to query: " << uri.to_string() << std::endl;
    printf("check1\n");
    //pplx::task<web::http::http_response> resp = client.request(web::http::methods::GET, uri.to_string());
    printf("check2\n");

    int flag  = 0;
     client.request(web::http::methods::GET, uri.to_string()).then([=] (web::http::http_response response) mutable { 
        //pplx::task<web::http::http_response> resp = client.request(web::http::methods::GET, uri.to_string());
        flag = 1;
        printf("check3.\n");
        //web::http::http_response response = task.get();
        printf("check4\n");
        std::cout<<"received response status code: "<< response.status_code()<<std::endl;
        printf("check5\n");
        std::string str = response.extract_utf8string().get();
        printf("check6\n");
        std::cout<<"port->"<<adapter.getPort()<<" ---- "<< std::stoi(adapter.getRate()) <<std::endl;
        TimeoutSerial serial(adapter.getPort(),std::stoi(adapter.getRate()));
        printf("check7\n");
        serial.setTimeout(boost::posix_time::seconds(0));
        serial.writeString(str+'\x03');
        std::cout<<"str->" << str<<std::endl;
        printf("check8\n"); 
    }).then([=] (pplx::task<void> previous_task) mutable { 
        if (previous_task._GetImpl()->_HasUserException()) { 
        auto holder = previous_task._GetImpl()->_GetExceptionHolder(); // Probably should put in try 

        try { 
        // Need to make sure you try/catch here, as _RethrowUserException can throw 
        holder->_RethrowUserException(); 
        } catch (std::exception& e) { 
        // Do what you need to do here 
        } 
        } 
    });


printf("check9\n");
if(flag == 0)
{
    printf("ERROR: Istediginiz bilgiye ulasamadiniz\n");
}

}