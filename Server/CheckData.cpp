#include "CheckData.h"

CheckData::CheckData()
{

}


void CheckData::Check(std::vector<uint8_t> m_data)
{
    std::vector<uint8_t> value;
    for(int i = 4; i<m_data.size()-1; i++)
    {
        value.push_back(m_data[i]);
    }
	switch(m_data[1])
	{
		case 0x30: //Login
			Login(value);
			break;
		case 0x42: //Start Sale
			StartSale(value);
			break;
		case 0x40: //Instant Sale
			InstantSale(value);
			break;
		case 0x41: //Cancel All
			CancelAll();
			break;
		case 0x50: //X report
			XReport(value);
			break;
		case 0x51: //Z Report
			ZReport(value);
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
			SetVat(value);
			break;
		case 0x61: //Get Vat List
			GetVatList(value);
			break;
		case 0x62: //Set Section
			SetSection(value);
			break;
		case 0x63: //Get Section List
			GetSectionList(value);
			break;
		case 0x64: //Set Headers
			SetHeaders();
			break;
		case 0x65: //Get Headers
			GetHeaders(value);
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
			GetUserList(value);
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
			SelfTest(value);
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

void CheckData::Login(std::vector<uint8_t> m_data)
{
	printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() != 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::StartSale(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::InstantSale(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() != 0)
		std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";       
    else
       std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::CancelAll()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::XReport(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::ZReport(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::FiscalReport()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::QueryReceipt()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::EjDetails()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::SetVat(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);
    if(m_data.size() != 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::GetVatList(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::SetSection(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() != 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::GetSectionList(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::SetHeaders()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::GetHeaders(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::SetDiscount()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::SetReceiptLimit()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::SetUser()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::GetUserList(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::ServiceLogin()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::InstallFm()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::Fiscalize()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::InstallEj()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::SetDateTime()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::NetworkSettings()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::SelfTest(std::vector<uint8_t> m_data)
{
    printf("---%s---\n\n", __FUNCTION__);

    if(m_data.size() == 0)
        std::cout<<"Girilen veri dogru bir sekilde girilmistir.\n";
    else
        std::cout<<"ERROR: Girilen veri dogru bir sekilde girilmemistir.\n";
}
void CheckData::Logs()
{
    printf("---%s---\n", __FUNCTION__);
}
void CheckData::ResetAdminPass()
{
    printf("---%s---\n", __FUNCTION__);
}
