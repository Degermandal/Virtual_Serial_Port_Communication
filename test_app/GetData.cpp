#include "GetData.h"
#include <sstream>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#define USERNAME_S 10*2
#define PASSWORD_S 5*2

#define ACCESSKEY_S 36*2
#define SALEID_S 16*2
#define ITEMARRAY_S 32
#define PAYMENTARRAY_S 3
#define DISCOUNTARRAY_S 2

#define SETVAT_SECTION_S 10*2
//#define NAME_S 24
//#define PRICE_S 4
//#define TWOB_S 2
//#define ONE_S 1


std::vector<uint8_t> GetData::string2byte(std::string input, std::vector<uint8_t> &outData){
    for(int idx = 0 ; idx < input.length() ; idx++){
        outData.push_back((uint8_t) input.at(idx));
    }

    /* for(auto val : outData)
    {
        std::cout<<"out->" << val <<std::endl;
    } */
    return outData;
}

std::string GetData::getInput(){

     std::string input = "";
    std::cout << "Enter data:\n";
    std::cin.ignore();
    getline(std::cin, input);
    return input; 

   /*  std::string input = "";
    std::string input2 = "";
    std::string input3 = "";
    std::string input4 = "";
    std::cout << "Enter data:";
    std::cin.ignore();
    getline(std::cin, input);
    getline(std::cin, input2);
    input += input2;
    getline(std::cin, input3);
    input += input3;
    getline(std::cin, input4);
    input += input4;
    return input; */
}


GetData::GetData()
{

}

void GetData::mySplit(const std::string &myStr, std::vector<std::string> &myVec, const char &ch)
{
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
}

std::vector<uint8_t> GetData::loginGetData(std::string filename)
{
    std::ifstream input;
	input.open(filename.c_str());
    std::string str = "";

    //filedan okuduklarimi doldurdugum vector
    std::vector<std::string> read;
    //okudugum stringleri uint8_t haline cevirmek icin olusturdugum vector
    std::vector<uint8_t> myData;

    while(!input.eof())//dosyadan okuma ve vectore push etme
    {
        std::getline(input,str);
        std::cout<<"ReadFile->"<<str<<std::endl;
        read.push_back(str);
    }

    if(read.size() != 1 || read[0].size()%2 != 0 || read[0].size() != (USERNAME_S+PASSWORD_S) )
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();
        return myData;
    }
/*............................................... */
    for(int i = 0; i<read[0].length(); i+=2)
    {
        std::string t = read[0].substr(i,2).c_str();
        uint8_t temp = (uint8_t)strtol(t.c_str(), 0, 16);
        myData.push_back((uint8_t)temp);
    }
/*............................................... */
	input.close();
	return myData;
}

std::vector< uint8_t > GetData::startSaleGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector<uint8_t > GetData::instantSaleGetData(std::string filename)
{
    std::ifstream input;
	input.open(filename.c_str());
    std::string str = "";

    //filedan okuduklarimi doldurdugum vector
    std::vector<std::string> read;
    //okudugum stringleri uint8_t haline cevirmek icin olusturdugum vector
    std::vector<uint8_t> myData;

    while(!input.eof())
    {
        std::getline(input,str);
        std::cout<<"ReadFile->"<<str<<std::endl;
        read.push_back(str);
    }
    if(read.size() != 4 )
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();        
        return myData;
    }
    if(read[0].size()%2 != 0 || read[0].size() != (ACCESSKEY_S+SALEID_S) )
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();        
        return myData;
    }
    
    if(read[1].size()%2 != 0 || read[1].size()%ITEMARRAY_S != 0)//32 itemarray size
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();        
        return myData;
    }
    if(read[2].size()%2 != 0 || read[2].length()% PAYMENTARRAY_S != 0)//3 payment array size
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();        
        return myData;
    }
    if(read[3].size()% DISCOUNTARRAY_S != 0 )//2 discount array size
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();        
        return myData;
    }
/*............................................... */   
    for(int i = 0; i<read[0].size(); i+=2)
    {
        std::string str = read[0].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t) value);
    }
   
/*............................................... */

/*    ITEM ARRAY    */
    //int count = read[1].size() / ITEMARRAY_S * 2; //TWO CHAR SEKLINDE OKUNDUGU ICIN
    for(int i = 0; i<read[1].length(); i+=2)
    {
        std::string str = read[1].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t) value);
    }

/*............................................... */
/*    PAYMENT ARRAY    */  
    //count = read[2].size() / PAYMENTARRAY_S * 2; //TWO CHAR SEKLINDE OKUNDUGU ICIN
    for(int i = 0; i<read[2].length(); i+=2)
    {
        std::string str = read[2].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t) value);
    }
/*............................................... */
/*    DISCOUNT ARRAY    */
    //count = read[3].size() / DISCOUNTARRAY_S * 2;//TWO CHAR SEKLINDE OKUNDUGU ICIN
    for(int i = 0; i<read[3].length(); i+=2)
    {
        std::string str = read[3].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t) value);
    }
	input.close(); 

	return myData;
}

std::vector< uint8_t> GetData::xReportGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::zReportGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::setVatGetData(std::string filename)
{
    std::ifstream input;
	input.open(filename.c_str());
    std::string str = "";

    //filedan okuduklarimi doldurdugum vector
    std::vector<std::string> read;
    //okudugum stringleri uint8_t haline cevirmek icin olusturdugum vector
    std::vector<uint8_t> myData;

    while(!input.eof())
    {
        std::getline(input,str);
        std::cout<<"ReadFile->"<<str<<std::endl;
        read.push_back(str);
    }
    if(read.size() != 1 || read[0].size()%2 != 0 || read[0].size() != SETVAT_SECTION_S )//10 setVat alinacak verinin byte uzunlugu
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();
        return myData;
    }
/*............................................... */

    for(int i = 0; i<read[0].length(); i+= 2)
    {
        std::string str = read[0].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t)value);
    }    

	input.close();

	return myData;
}

std::vector< uint8_t > GetData::getVatListGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::setSectionGetData(std::string filename)
{
    std::ifstream input;
	input.open(filename.c_str());
    std::string str = "";

    //filedan okuduklarimi doldurdugum vector
    std::vector<std::string> read;
    //okudugum stringleri uint8_t haline cevirmek icin olusturdugum vector
    std::vector<uint8_t> myData;

    while(!input.eof())
    {
        std::getline(input,str);
        std::cout<<"ReadFile->"<<str<<std::endl;
        read.push_back(str);
    }
    if(read.size() != 1 || read[0].size()%2 != 0 || read[0].size() != SETVAT_SECTION_S)//10 setVat alinacak verinin byte uzunlugu
    {
        std::cout<<"Error: Veriler dogru bir sekilde girilmemistir\n";
        myData.clear();
        return myData;
    }
/*............................................... */

    for(int i = 0; i<read[0].length(); i+= 2)
    {
        std::string str = read[0].substr(i,2).c_str();
        uint8_t value = (uint8_t) strtol(str.c_str(), 0, 16);
        myData.push_back((uint8_t)value);
    }    

	input.close();

	return myData;
}

std::vector< uint8_t > GetData::getSectionListGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::getHeadersGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::getUserListGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}

std::vector< uint8_t > GetData::selfTestGetData()
{
    std::vector<uint8_t > myData;
    return myData;
}
