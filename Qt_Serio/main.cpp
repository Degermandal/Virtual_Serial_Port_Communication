
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include "adapter.h"
#include "timeoutserial.h"
#include "package.h"
#include "TLV.h"
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_msg.h>
#include <fstream>

int main(int argc, char* argv[]){
  std::vector<uint8_t> v;
  int count = 0;
  std::string str("Hello world Init!");
  std::string received;
    try {
        std::fstream config;
        config.open("config.txt");
        char *port = "/dev/ttys003";//new char[15];
        char *rate = "19200";//new char[15];
        char *url = "http://192.168.0.1:6502";//new char[30];
        char *s = new char[15];
        for(int i = 0; i < 3; i++)
        {
        config.getline(s,15,'=');
        if(i==0)
            config.getline(port,15,'\n');
        else if(i==1)
            config.getline(rate,15,'\n');
        else
            config.getline(url,30,'\n');
        }
        std::cout<<port<<rate<<url<<std::endl;
        Adapter adapter;
        std::copy(str.begin(), str.end(), std::back_inserter(v));
        package packageToSend;
        packageToSend.stx = '\x02';
        packageToSend.data = TLV(51,52,v);
        packageToSend.etx = '\x03';
        web::http::client::http_client client(U(url));
        TimeoutSerial serial(port,std::stoi(rate));
        serial.setTimeout(boost::posix_time::seconds(0));
        while(1){

        std::vector<uint8_t> vec = packageToSend.getBytes();
        std::string serializedStr(vec.begin(), vec.end());
        std::cout<<serializedStr<<std::endl;
        received=serial.readStringUntil();
        std::cout<<"begin "<<received<<" end"<<std::endl;
        web::uri_builder uri(U(adapter.endpointDecider(adapter.getTag(received))));
        //std::cout<<"Received : "<<received<<" "<<count++ <<std::endl;
        //std::cout<<"Received val is :"<<adapter.getVal(received)<<std::endl;
        //std::cout<<"Json format of received package is :"<<adapter.sttoj(received)<<std::endl;
        pplx::task<web::http::http_response> resp;
        if(adapter.methodDecider(adapter.getTag(received))=="GET")
            resp = client.request(web::http::methods::GET, uri.to_string());
        else if(adapter.methodDecider(adapter.getTag(received))=="PATCH")
            resp = client.request(web::http::methods::PATCH, uri.to_string());
        else if(adapter.methodDecider(adapter.getTag(received))=="POST")
            resp = client.request(web::http::methods::POST, uri.to_string());
        //pplx::task<web::http::http_response> resp = client.request(web::http::methods::GET, uri.to_string());
        resp.then([=](pplx::task<web::http::http_response> task) mutable {
        web::http::http_response  response = task.get();
        std::cout<<"Received response status code: "<< response.status_code()<<std::endl;
        std::string str = response.extract_utf8string().get();
        TimeoutSerial serial(port,std::stoi(rate));
        serial.setTimeout(boost::posix_time::seconds(0));
        serial.writeString(str+'\n');
        std::cout<<str<<std::endl;
    });
        //serial.writeString(str+'\n');
        //std::cout <<"sending package len:"<<serializedStr.length()<<std::endl;
        //serial.writeString(serializedStr +'\n'); no longer required
        
    }
    } catch(boost::system::system_error& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }
}
