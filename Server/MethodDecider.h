#ifndef METHODDECIDER_H
#define METHODDECIDER_H

#include <iostream>
#include <vector>

class MethodDecider{
    public:
        MethodDecider(uint8_t);
        MethodDecider();
        void decideMethod(std::vector<uint8_t> m_data);
        std::vector<uint8_t> returnResponse(std::vector<uint8_t> val);

    private:
        void Login(std::vector<uint8_t> m_data, int msg_s);
        void StartSale();
        void InstantSale();
        void CancelAll();
        void XReport();
        void ZReport();
        void FiscalReport();
        void QueryReceipt();
        void EjDetails();
        void SetVat();
        void GetVatList();
        void SetSection();
        void GetSectionList();
        void SetHeaders();
        void GetHeaders();
        void SetDiscount();
        void SetReceiptLimit();
        void SetUser();
        void GetUserList();
        void ServiceLogin();
        void InstallFm();
        void Fiscalize();
        void InstallEj();
        void SetDateTime();
        void NetworkSettings();
        void SelfTest();
        void Logs();
        void ResetAdminPass();

    private:
    //uint8_t tag;
};

#endif //METHODDECIDER_H