#ifndef GETDATA_H
#define GETDATA_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>



class GetData{
    public:
        std::vector<uint8_t> string2byte(std::string input, std::vector<uint8_t> &outData);
        std::string getInput();

        GetData();
        //std::vector<std::vector<uint8_t> > getData(int selection, std::string filename);

        //std::vector<char> readFile(std::string filename);
        /*1-LOGIN */
        std::vector<uint8_t > loginGetData(std::string filename);
        /*2-START SALE */
        std::vector< uint8_t > startSaleGetData();
        /*3-INSTANT SALE */
        std::vector< uint8_t > instantSaleGetData(std::string filename);
        /*5-X REPORT */
        std::vector< uint8_t > xReportGetData();
        /*6-Z REPORT */
        std::vector< uint8_t > zReportGetData();
        /*10-SET VAT*/
        std::vector< uint8_t > setVatGetData(std::string filename);
        /*11-GET VAT LIST */
        std::vector< uint8_t > getVatListGetData();
        /*12-SET SECTION */
        std::vector< uint8_t > setSectionGetData(std::string filename);
        /*13-GET SECTION LIST */
        std::vector< uint8_t > getSectionListGetData();
        /*15-GET HEADERS */
        std::vector< uint8_t > getHeadersGetData();
        /*19-GET USER LIST */
        std::vector< uint8_t > getUserListGetData();
        /*26-SELF TEST */
        std::vector< uint8_t > selfTestGetData();
    private:
        void mySplit(const std::string &myStr, std::vector<std::string> &myVec, const char &ch);
       
};

#endif