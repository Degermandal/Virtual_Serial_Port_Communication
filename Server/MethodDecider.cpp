#include "MethodDecider.h"
#include "TLV.h"

MethodDecider::MethodDecider(uint8_t tg)
{
    //tag = tg;
}

MethodDecider::MethodDecider()
{
   
}

std::vector<uint8_t> MethodDecider::returnResponse(std::vector<uint8_t> val)
{
	printf("%s\n", __FUNCTION__);
	std::vector<uint8_t> message = {0x31, 0x44, 0x03, /*msgLen */ 0x48, 0x49, 0x21, 0x44, 0x41, 0x54, 0x41};
	//uint8_t state = 0x31;
	//uint8_t code = 0x44;
	return message;
}

void MethodDecider::decideMethod(std::vector<uint8_t> m_data)
{
	uint8_t tag = m_data[1];
	std::vector<uint8_t> value;
	for(int i = 3; i<m_data[2]+3; i++)
	{
		value.push_back(m_data[i]);
	}
	std::vector<uint8_t> response = returnResponse(value);
	int messLen = response[2];
	response.erase(response.begin()+2);

	switch(tag)
	{
		case 0x30: //Login
			Login(response, messLen);
			break;
		case 0x42: //Start Sale
			StartSale();
			break;
		case 0x40: //Instant Sale
			InstantSale();
			break;
		case 0x41: //Cancel All
			CancelAll();
			break;
		case 0x50: //X report
			XReport();
			break;
		case 0x51: //Z Report
			ZReport();
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
			SetVat();
			break;
		case 0x61: //Get Vat List
			GetVatList();
			break;
		case 0x62: //Set Section
			SetSection();
			break;
		case 0x63: //Get Section List
			GetSectionList();
			break;
		case 0x64: //Set Headers
			SetHeaders();
			break;
		case 0x65: //Get Headers
			GetHeaders();
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
			GetUserList();
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
			SelfTest();
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

void MethodDecider::Login(std::vector<uint8_t> m_data, int msg_s)
{
	printf("---%s---\n", __FUNCTION__);

/* 	uint8_t state = m_data[0];
	uint8_t code = m_data[1];
	uint8_t msgByteArr[msg_s];
	int data_s = m_data.size() -2 - msg_s;
	uint8_t dataByteArr[data_s];
	int j = 0;
	for(int i =2; i<msg_s+2; i++)
	{
		msgByteArr[j++] = m_data[i];
	}
	j = 0;
	for(int i=msg_s+2; i<m_data.size(); i++ )
	{
		dataByteArr[j] = m_data[i];
	}

	std::cout<<"state->"<<state<<std::endl;
	std::cout<<"code->"<<code<<std::endl;
	std::cout<<"msgByte->"<<std::endl;
	for(auto val:msgByteArr)
	{
		std::cout<<" "<<val;
	}

	std::cout<<std::endl;
	std::cout<<"DataByteArr->"<<std::endl;
	for(auto val:dataByteArr)
	{
		std::cout<<" "<<val;
	}
	std::cout<<std::endl;
 */


}
void MethodDecider::StartSale()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::InstantSale()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::CancelAll()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::XReport()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::ZReport()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::FiscalReport()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::QueryReceipt()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::EjDetails()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetVat()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::GetVatList()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetSection()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::GetSectionList()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetHeaders()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::GetHeaders()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetDiscount()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetReceiptLimit()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetUser()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::GetUserList()
{
    printf("---%s---n", __FUNCTION__);
}
void MethodDecider::ServiceLogin()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::InstallFm()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::Fiscalize()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::InstallEj()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SetDateTime()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::NetworkSettings()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::SelfTest()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::Logs()
{
    printf("---%s---\n", __FUNCTION__);
}
void MethodDecider::ResetAdminPass()
{
    printf("---%s---\n", __FUNCTION__);
}
