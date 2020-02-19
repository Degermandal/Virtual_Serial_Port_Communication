
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>


#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_msg.h>
#include <fstream>

#include "httpClientHandler.hpp"
#include "MethodDecider.h"
#include "CheckData.h"
//#include "TagDecider.h"
#include "adapter.h"
#include "iniconfig.hpp"
#include "TimeoutSerial.h"
#include "package.h"
#include "TLV.h"

//using namespace Serio;

#define GETLINE_LEN 256
#define BYTE_STX 0x02
#define BYTE_ETX 0X03

uint16_t convertTwo8To16(uint8_t dataFirst, uint8_t dataSecond)
{
    uint16_t dataBoth = 0x0000;
    dataBoth = dataFirst;
    dataBoth = dataBoth << 8;
    dataBoth |= dataSecond;
    return dataBoth;
}

void printTLV(TLV tlv)
{
    printf("\nTLV'den once:\n");
    int vS = tlv.getValue().size();
    printf("\n");

    if(vS < 30)
    {
        printf(" "); printf("TAG"); printf(" "); printf("|");
        printf(" "); printf("LEN"); printf(" "); printf("|");
        for(int i = 0; i< (vS*5-5)/2; i++)
            printf(" ");
        printf("VALUE");
        for(int i = 0; i< (vS*5-5)/2; i++)
            printf(" ");
        printf("\n");

        printf(" %02x", tlv.getTag()); printf("  |");
        printf(" %04x", tlv.getLen()); printf("  |");
        for(int i = 0; i<vS; i++)
            printf(" %02x ",tlv.getValue()[i]);
        printf("\n");
    }
    else
    {
        printf(" "); printf("TAG"); printf(" "); printf("|");
        printf(" "); printf("LEN"); printf(" "); printf("|");
        printf("\n");

        printf(" %02x", tlv.getTag()); printf("  |");
        printf(" %04x", tlv.getLen()); printf("  |");
        printf("\n\n");  printf("|");
        for(int i = 0; i< (20*4 -8)/2; i++)
            printf(" ");
        printf("VALUE");
        for(int i = 0; i< (20*4-8)/2; i++)
            printf(" ");         
        printf("|");
        printf("\n");

        int temp = 20;        
        for(int i = 0; i<vS; i++)
        {
            if(i == temp)
            {
                printf("\n");
                temp += 20;
            }               
            printf(" %02x ",tlv.getValue()[i]);
        }           
        printf("\n"); 
    }
    printf("\n");
}

void printRaw(std::vector<uint8_t> all)
{
    printf("\nTLV'den sonra:\n");
    int vS = all.size() - 4;
    uint16_t len = convertTwo8To16(all[2], all[3]);
    printf("\n");

    if(vS < 30)
    {
        printf(" "); printf("STX"); printf(" "); printf("|");
        printf(" "); printf("TAG"); printf(" "); printf("|");
        printf(" "); printf("LEN"); printf(" "); printf("|");
        for(int i = 0; i< (vS*4-5)/2; i++)
            printf(" ");
        printf("VALUE");
        for(int i = 0; i< (vS*4-5)/2; i++)
            printf(" ");
        printf(" |");
        printf(" "); printf("ETX"); printf(" "); printf("|");
        printf("\n");

        printf(" %02x", all[0]);/*stx */ printf("  |");
        printf(" %02x", all[1]);/*tag */ printf("  |");
        printf(" %04x", len);/*len*/ printf("  |");
        if(vS == 0)
            printf("      ");
        else
        {
            for(int i = 4; i<vS+3; i++)
                printf(" %02x ",all[i]);
        }
        
        printf("|"); printf(" %02x", all[all.size()-1]); printf("  |");
        printf("\n");
    }
    else
    {
        printf(" "); printf("STX"); printf(" "); printf("|");
        printf(" "); printf("TAG"); printf(" "); printf("|");
        printf(" "); printf("LEN"); printf(" "); printf("|"); 
        
        printf("\n");

        printf(" %02x", all[0]);/*stx */ printf("  |");
        printf(" %02x", all[1]);/*tag */ printf("  |");
        printf(" %04x",len);/*len */ printf("  |");
        printf("\n\n"); printf("|");
        for(int i = 0; i< (20*4-5)/2; i++)
            printf(" ");
        printf("VALUE");
        for(int i = 0; i< (20*4-5)/2; i++)
            printf(" ");
        printf("|");
        printf("\n");

        int temp = 20;
        for(int i = 4; i<vS+3; i++)
        {
            if(i == temp+4)
            {
                printf("\n");
                temp += 20;
            }
            printf(" %02x ",all[i]);
        }
        
        printf("\n\n"); printf("|");
        printf(" "); printf("ETX"); printf(" "); printf("|");
        printf("\n");
        printf("|"); printf(" %02x", all[all.size()-1]); printf("  |");   
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    std::string received = "";
    //TagDecider td;
    Adapter adapter;
    try {
        /* std::string port = "/dev/pts/18";//new char[15];
        std::string rate = "115200";//new char[15];
        std::string url = "http://172.20.2.22:6502";//new char[30];

        IniConfig config;
        auto rv = config.load();
        if(rv != 0){
            std::cerr << "loading config failed with rv:" << rv << ", using defaults" << std::endl;
        }else{
            rv = config.get("port", port);
            rv = config.get("rate", rate);
            rv = config.get("url", url);
        } */
        
        adapter.read_P_R_U();
        std::cout<<"port:"<<adapter.getPort()<<" baud_rate:"<<adapter.getRate() <<" url:"<< adapter.getUrl() <<std::endl;

       // web::http::client::http_client client(U(adapter.getUrl()));
        TimeoutSerial serial(adapter.getPort(),std::stoi(adapter.getRate() ));
        serial.setTimeout(boost::posix_time::seconds(0));

        while(true){
            received=serial.readStringUntil("\x03");

            std::vector<uint8_t> dataVec;
            for(int i = 4; i<received.size(); i++)
            {
                dataVec.push_back(received[i]);
            }

            package packageToSend;
            packageToSend.stx = BYTE_STX;
            
            uint16_t mylen = convertTwo8To16((uint8_t)received[2], (uint8_t)received[3]);
            TLV tlv(received[1], mylen, dataVec);
            //packageToSend.data = TLV(received[1], mylen, dataVec);
            packageToSend.data = tlv;
            printTLV(packageToSend.data);
            packageToSend.etx = BYTE_ETX;

            //std::cout<<"serial msg begin["<<(received)<<"]end"<<std::endl;

            /* | STX | TAG | L1 | L2 | DATA | ETX |  halini return eder */
            std::vector<uint8_t> allValues =  packageToSend.getBytes();

            printRaw(allValues); //??? allValues yaziyordu

            CheckData cd;
            cd.Check(allValues);

            printf(".....................................................\n");

            Adapter ad(received);
            ad.setData(allValues);
            uint8_t T_tag = ad.decideTheTag("POST", "/api/login");
            printf("Tag->%02x\n",T_tag);
            std::cout<< "Data->" << ad.getVal()<<std::endl;
            printf("Size->%d (%02x)\n",ad.getVal().length(), ad.getVal().length());
 
           //allValues.clear();
            printf("\n####################################################\n");

            //Adapter ad(received); //???

            // TODO: send tlv to http client handler
            Serio::HttpClientHandler handler(ad);
            //Serio::HttpClientHandler h(allValues);
            int rv = handler.handleTLV(tlv);

            printf("\n####################################################\n");
            allValues.clear();
            
        }
    } catch(boost::system::system_error& e){
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}

