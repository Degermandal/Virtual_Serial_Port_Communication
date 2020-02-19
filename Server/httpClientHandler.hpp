#ifndef __HTTPCLIENTHANDLER_H__
#define __HTTPCLIENTHANDLER_H__

#include <iostream>
#include <string>
#include <vector>

#include "TagDecider.h"
#include "adapter.h"
#include "TLV.h"

namespace Serio{
    class HttpClientHandler{
        public:
            HttpClientHandler();
            HttpClientHandler(Adapter &m_adap);
            int handleTLV(TLV tlv);
            void setHandlerTag(uint8_t m_tag){ tag = m_tag; }
            uint8_t getHandlerTag() { printf("ii\n"); return tag; }

        private:
            uint8_t tag;
            Adapter adap;
            std::vector<std::string> mySplit(const std::string &myStr,  const char &ch);
            void handleLoginPost(std::string username, std::string password);
            void handleInstantSalePost(/* ect.. */);
    };
}

#endif