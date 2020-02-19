#include "MethodDecider.h"
#include "TLV.h"
#include "TimeoutSerial.h"
#include "iniconfig.hpp"
#define BYTE_STX 0x02
#define BYTE_ETX 0X03

MethodDecider::MethodDecider(uint8_t m_tag)
{
    tag = m_tag;
	port = "";
	rate = "";
}

MethodDecider::MethodDecider() 
{   
	tag = '\x00';
	port = "";
	rate = "";
}

void MethodDecider::getRatePort()
{
	IniConfig config;
	int rv = config.load();
	if(rv != 0){
		std::cerr<<"Error: In getRatePort\n";
	}

	std::string port, rate;
	config.get("port", port);
	config.get("rate", rate);

	setPort(port);
	setRate(rate);
}

void MethodDecider::sendInfo(std::vector<uint8_t> value){
    getRatePort();
	std::cout << std::endl;
    std::cout<<"Port->"<<getPort()<<"  Rate->"<<getRate() <<std::endl;
    TimeoutSerial serial(getPort(),std::stoi(getRate()));
    //serial.setTimeout(boost::posix_time::seconds(0));
    TLV toSend;
    toSend.setTag(getTag());
	uint16_t myLen = (uint16_t)value.size();
    toSend.setLen(myLen);
    toSend.setData(value);

	printf("Tag->%02x\n", getTag());
	std::cout<<"Len->"<<(int)value.size();
	printf(" ( %02x )\n",value.size());
	printf("Value:\n");

	if(value.size() <20)
	{
		std::cout<<std::endl;
		for(auto val: value)
		{
			printf("%02x ", val);
		}
	}
	else
	{
		int flag = 0;
		int flag2 = 20;
		
		std::cout<<std::endl;
		for(auto val: value)
		{
			if(flag == flag2)
			{
				printf("\n");
				flag2+=20;
			}
			flag++;
			printf("%02x ", val);
		}
	}
	
	std::cout<<std::endl;
    auto toSendSerialized  = toSend.serialize();

    std::vector<uint8_t> data;
    data.push_back(BYTE_STX);
    for(auto &item  : toSendSerialized){
        data.push_back(item);
    }
    data.push_back(BYTE_ETX);
    serial.write((const char*)(data.data()) , data.size());
}

void MethodDecider::decideMethod(std::vector<uint8_t > m_value, uint8_t m_tag)
{
	setTag(m_tag);
	switch(m_tag)
	{
		case 0x30: //Login
			Login(m_value);			
			break;
		case 0x42: //Start Sale
			StartSale(m_value);			
			break;
		case 0x40: //Instant Sale
			InstantSale(m_value);
			break;
		case 0x41: //Cancel All
			CancelAll();
			break;
		case 0x50: //X report
			XReport(m_value);
			break;
 		case 0x51: //Z Report
			ZReport(m_value);
			break;
 		case 0x52: //Fiscal Report
			FiscalReport();
			break;
		case 0x53: //Query Receipt
			QueryReceipt();
			break;
		case 0x54: //Ej Details
			EjDetails();
			break;
        case 0x60: //Set Vat
			SetVat(m_value);
			break;
		case 0x61: //Get Vat List
			GetVatList(m_value);
			break;
		case 0x62: //Set Section
			SetSection(m_value);
			break;
		case 0x63: //Get Section List
			GetSectionList(m_value);
			break;
		case 0x64: //Set Headers
			SetHeaders();
			break;
		case 0x65: //Get Headers
			GetHeaders(m_value);
			break;
		case 0x66: //Set Discount
			SetDiscount();
			break;
		case 0x67: //Set Receipt Limit
			SetReceiptLimit();
			break;
		case 0x68: //Set User
			SetUser();
			break;
        case 0x69: //Get User List
			GetUserList(m_value);
			break;
		case 0x20: //Service Login
			ServiceLogin();
			break;
		case 0x21: //Install Fm
			InstallFm();
			break;
		case 0x22: //Fiscalize
			Fiscalize();
			break;
		case 0x23: //Install Ej
			InstallEj();
			break;
		case 0x24: //Set Date Time
			SetDateTime();
			break;
		case 0x25: //Network Settings
			NetworkSettings();
			break;
		case 0x26: //Self Test
			SelfTest(m_value);
			break;
		case 0x27: //Logs
			Logs();
			break;
		case 0x28: //Reset Admin Pass
			ResetAdminPass();
			break; 

        default:
            std::cerr<<"Error: in decideMethod()\n";
            break;
	}
}

void MethodDecider::Login(std::vector<uint8_t > m_value)
{
	printf("--%s--\n", __FUNCTION__);
	
	sendInfo(m_value);
    
}

void MethodDecider::StartSale(std::vector<uint8_t > m_value)
{
	printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}

void MethodDecider::InstantSale(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::CancelAll()
{
    printf("--%s--\n", __FUNCTION__);
}
void MethodDecider::XReport(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::ZReport(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::FiscalReport()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::QueryReceipt()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::EjDetails()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::SetVat(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::GetVatList(std::vector<uint8_t > m_value)
{
	printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}

void MethodDecider::SetSection(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::GetSectionList(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::SetHeaders()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::GetHeaders(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::SetDiscount()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::SetReceiptLimit()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::SetUser()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::GetUserList(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::ServiceLogin()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::InstallFm()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::Fiscalize()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::InstallEj()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::SetDateTime()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::NetworkSettings()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::SelfTest(std::vector<uint8_t > m_value)
{
    printf("--%s--\n", __FUNCTION__);
	sendInfo(m_value);
}
void MethodDecider::Logs()
{
    printf("%s\n", __FUNCTION__);
}
void MethodDecider::ResetAdminPass()
{
    printf("%s\n", __FUNCTION__);
}
