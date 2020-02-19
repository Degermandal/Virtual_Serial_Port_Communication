#ifndef METHODDECIDER_H
#define METHODDECIDER_H

#include <iostream>
#include <vector>


class MethodDecider{
    public:
        MethodDecider();
        MethodDecider(uint8_t);

        std::string getPort() { return port;    }
        std::string getRate() { return rate;    }
        void setPort(std::string m_port){port = m_port;}
        void setRate(std::string m_rate){rate = m_rate;}
        void getRatePort();

        uint8_t getTag(){ return tag; }
        void setTag(const uint8_t &m_tag){ tag = m_tag; }
    
        void decideMethod(std::vector<uint8_t > m_value, uint8_t m_tag);
        void sendInfo(std::vector<uint8_t> value);
        

    private:
        void Login(std::vector<uint8_t > m_value);
        void StartSale(std::vector<uint8_t > m_value);
        void InstantSale(std::vector<uint8_t > m_value);
        void CancelAll();
        void XReport(std::vector<uint8_t > m_value);
        void ZReport(std::vector<uint8_t > m_value);
        void FiscalReport();
        void QueryReceipt();
        void EjDetails();
        void SetVat(std::vector<uint8_t > m_value);
        void GetVatList(std::vector<uint8_t > m_value);
        void SetSection(std::vector<uint8_t > m_value);
        void GetSectionList(std::vector<uint8_t > m_value);
        void SetHeaders();
        void GetHeaders(std::vector<uint8_t > m_value);
        void SetDiscount();
        void SetReceiptLimit();
        void SetUser();
        void GetUserList(std::vector<uint8_t > m_value);
        void ServiceLogin();
        void InstallFm();
        void Fiscalize();
        void InstallEj();
        void SetDateTime();
        void NetworkSettings();
        void SelfTest(std::vector<uint8_t > m_value);
        void Logs();
        void ResetAdminPass();

    private:
        std::string port;
        std::string rate;
        uint8_t tag;
};

#endif //METHODDECIDER_H