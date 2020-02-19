#ifndef TAGDECIDER_H
#define TAGDECIDER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class TagDecider{
    public:
        TagDecider();
        
        uint8_t decideTheTag(std::string method, std::string endPoint);
        void read_P_R_U();

        std::string setData(std::vector< uint8_t > TLVData);
        std::string getData();

        void setUrl(std::string m_url) { url = m_url; }
        std::string getUrl(){ return url; }

        void setPort(std::string m_port) { port = m_port; }
        std::string getPort(){ return port; }

        void setRate(std::string m_rate) { rate = m_rate; }
        std::string getRate(){ return rate; }

    private:
        std::string port;
        std::string rate;
        std::string url;
        std::string data;
};

#endif