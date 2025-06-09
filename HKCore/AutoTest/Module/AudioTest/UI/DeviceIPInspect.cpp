 // D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\DeviceIPInspect.cpp : 实现文件
//

#include "stdafx.h"
#include "DeviceIPInspect.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"

#include "../../../../Module/Socket/XPing.h"
// CDeviceIPInspect 对话框

IMPLEMENT_DYNAMIC(CDeviceIPInspect, CDialog)

CDeviceIPInspect::CDeviceIPInspect(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CDeviceIPInspect::IDD, pParent)
{

}

CDeviceIPInspect::~CDeviceIPInspect()
{
}

void CDeviceIPInspect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeviceIPInspect, CDialog)
END_MESSAGE_MAP()
// CDeviceIPInspect 消息处理程序

BOOL CDeviceIPInspect::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_static.SubclassDlgItem(IDC_STATIC_DEVICEIP, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	return TRUE;
}

bool CDeviceIPInspect::DealAnswer(CString strResult)
{
	if(m_strIP.IsEmpty())
	{
		GetDlgItem(IDC_IPADDRESS1)->GetWindowText(m_strIP);
	}

	if(m_strIP.IsEmpty())
	{
		return false;
	}
	return xping(m_strIP);
}

void CDeviceIPInspect::FindSelectAnswer(CString strResult)
{
	//FindResult(strResult)
	m_strIP = strResult;
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(m_strIP);
}

CString CDeviceIPInspect::GetCurrentResult()
{
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(m_strIP);
	if(m_strIP == "0.0.0.0")
	{
		return "";
	}
	return m_strIP;
}


/*
bool IsValidIP(char *ip)
{
	std::string sip=ip;
	int pos=(int)sip.find_first_of(“.“);//查找第1个符号“.”的位置
	if(pos==0)//如果没有找到，则返回false
		return false;
	std::string s1=sip.substr(0,pos);//s1是IP地址中的第1个数字
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s1.length()>3)
		return false;
	for(int i=0;i<(int)s1.length();i++)//判断是否每个字符都是数字
	{
		intc=s1.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	inta=atoi(s1.c_str());//判断是否在1~255之间
	if(a<1|| a>255)
		return false;
	pos=(int)sip.find_first_of(“.”);
	std::strings2=sip.substr(0,pos); //s2是IP地址中的第2个数字
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s2.length()>3)
		return false;
	for(int i=0;i<(int)s2.length();i++)//判断是否每个字符都是数字
	{
		int c=s2.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s2.c_str());
	if(a>255)//判断是否在0~255之间
		return false;
	pos=(int)sip.find_first_of(“.”);
	std::string s3=sip.substr(0,pos); //s3是IP地址中的第3个数字
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s3.length()>3)
		return false;
	for(int i=0;i<(int)s3.length();i++)//判断是否每个字符都是数字
	{
		int c=s3.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s3.c_str());
	if(a>255)//判断是否在0~255之间
		return false;
	pos=(int)sip.find_first_of(“.”);
	std::strings4=sip.substr(0,pos); //s4是IP地址中的第4个数字
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s4.length()>3)
		return false;
	for(int i=0;i<(int)s4.length();i++)//判断是否每个字符都是数字
	{
		int c=s4.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s4.c_str());
	if(a>254)//判断是否在0~254之间
		return false;
	//通过上面所有检测后，确定该字符串为合法IP地址
	return true;
}
*/