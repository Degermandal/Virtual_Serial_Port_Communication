#include <iostream>
#include <string>
#include <fstream>

#include "MethodDecider.h"
#include "GetData.h"


void handleSelection(const int selection, std::string filename){
    MethodDecider md;
    GetData gd;
    std::vector< uint8_t > m_data;

    //added
    std::string input = "";
    std::vector<uint8_t> byteArr;
    auto rv = 0;
    switch(selection){
        case 1: /* Login */
            input = gd.getInput();        
            gd.string2byte(input, m_data);
           // m_data = gd.loginGetData(filename);
            printf("\n");
            md.decideMethod(m_data, '\x30');
            break;  
        case 2: /* Start Sale */
            input = gd.getInput();         
            gd.string2byte(input, m_data);
            //m_data = gd.startSaleGetData();
            printf("\n");
            md.decideMethod(m_data, '\x42');
            break;    
        case 3: /* Instant Sale */
            input = gd.getInput();         
            gd.string2byte(input, m_data);
            //m_data = gd.instantSaleGetData(filename);
            printf("\n");
            md.decideMethod(m_data, '\x40');
            break;
        case 4: /* Cancel All */
//          md.decideMethod();
            break;
        case 5: /* X Report */
            input = gd.getInput();         
            gd.string2byte(input, m_data);
            //m_data = gd.xReportGetData();
            printf("\n");
            md.decideMethod(m_data, '\x50');
            break;
        case 6: /* Z Report */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.zReportGetData();
            printf("\n");
            md.decideMethod(m_data, '\x51');
            break;
        case 7: /* Fiscal Report */
//            md.decideMethod();
            break;
        case 8: /* Query Receipt */
//            md.decideMethod();
            break;
        case 9: /* Ej Details */
//            md.decideMethod();
            break;
        case 10: /* Set Vat */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.setVatGetData(filename);
            printf("\n");
            md.decideMethod(m_data, '\x60');
            break;
        case 11: /* Get Vat List */
            input = gd.getInput();         
            gd.string2byte(input, m_data);
            //m_data = gd.getVatListGetData();
            printf("\n");
            md.decideMethod(m_data, '\x61');
            break;
        case 12: /* Set Section */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.setSectionGetData(filename);
            printf("\n");
            md.decideMethod(m_data, '\x62');
            break;
        case 13: /* Get Section List */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.getSectionListGetData();
            printf("\n");
            md.decideMethod(m_data, '\x63');
            break;
        case 14: /* Set Headers */
//            md.decideMethod();
            break;
        case 15: /* Get Headers */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.getHeadersGetData();
            printf("\n");
            md.decideMethod(m_data, '\x65');
            break;
        case 16: /* Set Discount */
//            md.decideMethod();
            break;
        case 17: /* Set Receipt Limit */
//            md.decideMethod();
            break;
        case 18: /* Set User */
//            md.decideMethod();
            break;
        case 19: /* Get User List */
            input = gd.getInput();          
            gd.string2byte(input, m_data);
            //m_data = gd.getUserListGetData();
            printf("\n");
            md.decideMethod(m_data, '\x69');
            break;
        case 20: /* Service Login */
//            md.decideMethod();
            break;
        case 21: /* Install Fm */
//            md.decideMethod();
            break;
        case 22: /* Fiscalize */
//            md.decideMethod();
            break;
        case 23: /* Install Ej */
//            md.decideMethod();
            break;
        case 24: /* Set Date Time */
 //           md.decideMethod();
            break;
        case 25: /* Network Settings */
 //           md.decideMethod();
            break;
        case 26: /* Self Test */
            input = gd.getInput();    
            gd.string2byte(input, m_data);
            //m_data = gd.selfTestGetData();
            printf("\n");
            md.decideMethod(m_data, '\x26');
            break;
        case 27: /* Logs */
//            md.decideMethod();
            break;
        case 28: /* Reset Admin Pass */
//            md.decideMethod();
            break; 

        case 0: /* Exit */
            exit(0);
            break;
        default:
            std::cerr << "Invalid selection : In handleSelection" << std::endl;
    }
}

int displayMenu(){
    std::cout << std::endl;
    std::cout << "### Select option ###" << std::endl;
    std::cout << "1- Login" << std::endl;
    std::cout << "2- Start Sale" << std::endl;
    std::cout << "3- Instant Sale" << std::endl;
    std::cout << "4- Cancel All" << std::endl;
    std::cout << "5- X Report" << std::endl;
    std::cout << "6- Z Report" << std::endl;
    std::cout << "7- Fiscal Report" << std::endl;
    std::cout << "8- Query Receipt" << std::endl;
    std::cout << "9- Ej Details" << std::endl;
    std::cout << "10- Set Vat" << std::endl;
    std::cout << "11- Get Vat List" << std::endl;
    std::cout << "12- Set Section" << std::endl;
    std::cout << "13- Get Section List" << std::endl;
    std::cout << "14- Set Headers" << std::endl;
    std::cout << "15- Get Headers" << std::endl;
    std::cout << "16- Set Discount" << std::endl;
    std::cout << "17- Set Receipt Limit" << std::endl;
    std::cout << "18- Set User" << std::endl;
    std::cout << "19- Get User List" << std::endl;
    std::cout << "20- Service Login" << std::endl;
    std::cout << "21- Install Fm" << std::endl;
    std::cout << "22- Fiscalize" << std::endl;
    std::cout << "23- Install Ej" << std::endl;
    std::cout << "24- Set Date Time" << std::endl;
    std::cout << "25- Network Settings" << std::endl;
    std::cout << "26- Self Test" << std::endl;
    std::cout << "27- Logs" << std::endl;
    std::cout << "28- Reset Admin Pass" << std::endl;
    
    int selection = -1;
    std::cin >> selection;
    std::cout << std::endl;
    return selection;
}

int main(){
    int selection;
    std::string filename = "Data.txt";
    while(true)
    {
        selection = displayMenu();
        handleSelection(selection, filename);
    }
    
    return 0;
}
