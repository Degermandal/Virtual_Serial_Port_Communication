#ifndef CHECKDATA_H
#define CHECKDATA_H

#include <iostream>
#include <vector>

class CheckData{
    public:
        CheckData();
        void Check(std::vector<uint8_t>);

    private:
        void Login(std::vector<uint8_t>);
        void StartSale(std::vector<uint8_t>);
        void InstantSale(std::vector<uint8_t>);
        void CancelAll();
        void XReport(std::vector<uint8_t>);
        void ZReport(std::vector<uint8_t>);
        void FiscalReport();
        void QueryReceipt();
        void EjDetails();
        void SetVat(std::vector<uint8_t>);
        void GetVatList(std::vector<uint8_t>);
        void SetSection(std::vector<uint8_t>);
        void GetSectionList(std::vector<uint8_t>);
        void SetHeaders();
        void GetHeaders(std::vector<uint8_t>);
        void SetDiscount();
        void SetReceiptLimit();
        void SetUser();
        void GetUserList(std::vector<uint8_t>);
        void ServiceLogin();
        void InstallFm();
        void Fiscalize();
        void InstallEj();
        void SetDateTime();
        void NetworkSettings();
        void SelfTest(std::vector<uint8_t>);
        void Logs();
        void ResetAdminPass();

    private:
    //uint8_t tag;
};

#endif 