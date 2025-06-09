 // D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\DeviceIPInspect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeviceIPInspect.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"

#include "../../../../Module/Socket/XPing.h"
// CDeviceIPInspect �Ի���

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
// CDeviceIPInspect ��Ϣ�������

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
	int pos=(int)sip.find_first_of(��.��);//���ҵ�1�����š�.����λ��
	if(pos==0)//���û���ҵ����򷵻�false
		return false;
	std::string s1=sip.substr(0,pos);//s1��IP��ַ�еĵ�1������
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s1.length()>3)
		return false;
	for(int i=0;i<(int)s1.length();i++)//�ж��Ƿ�ÿ���ַ���������
	{
		intc=s1.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	inta=atoi(s1.c_str());//�ж��Ƿ���1~255֮��
	if(a<1|| a>255)
		return false;
	pos=(int)sip.find_first_of(��.��);
	std::strings2=sip.substr(0,pos); //s2��IP��ַ�еĵ�2������
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s2.length()>3)
		return false;
	for(int i=0;i<(int)s2.length();i++)//�ж��Ƿ�ÿ���ַ���������
	{
		int c=s2.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s2.c_str());
	if(a>255)//�ж��Ƿ���0~255֮��
		return false;
	pos=(int)sip.find_first_of(��.��);
	std::string s3=sip.substr(0,pos); //s3��IP��ַ�еĵ�3������
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s3.length()>3)
		return false;
	for(int i=0;i<(int)s3.length();i++)//�ж��Ƿ�ÿ���ַ���������
	{
		int c=s3.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s3.c_str());
	if(a>255)//�ж��Ƿ���0~255֮��
		return false;
	pos=(int)sip.find_first_of(��.��);
	std::strings4=sip.substr(0,pos); //s4��IP��ַ�еĵ�4������
	sip=sip.substr(pos+1,sip.length()-pos);
	if(s4.length()>3)
		return false;
	for(int i=0;i<(int)s4.length();i++)//�ж��Ƿ�ÿ���ַ���������
	{
		int c=s4.c_str()[i];
		if(!isdigit(c))
			return false;
	}
	a=atoi(s4.c_str());
	if(a>254)//�ж��Ƿ���0~254֮��
		return false;
	//ͨ���������м���ȷ�����ַ���Ϊ�Ϸ�IP��ַ
	return true;
}
*/