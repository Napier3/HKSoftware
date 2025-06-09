// NetDeviceComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "NetDeviceComboBox.h"


// CNetDeviceComboBox

IMPLEMENT_DYNAMIC(CNetDeviceComboBox, CComboBox)

CNetDeviceComboBox::CNetDeviceComboBox()
{
	m_byte1 = 192;
	m_byte2 = 168;
	m_byte3 = 1;
	m_byte4 = 1;
}

CNetDeviceComboBox::~CNetDeviceComboBox()
{
}


BEGIN_MESSAGE_MAP(CNetDeviceComboBox, CComboBox)
END_MESSAGE_MAP()



// CNetDeviceComboBox 消息处理程序

void CNetDeviceComboBox::InitNetDevice(BOOL bOnllyShowDesc)
{
	pcap_if_t *d;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];

	//AfxMessageBox(_T("1"));
	// 获取网络设备列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		AfxMessageBox(_T("寻找网络设备失败"));
		return ;
	}

	// 输出网络设备
	ResetContent();
	CString strText;

	if (alldevs == NULL)
	{
		AfxMessageBox(_T("alldevs == NULL"));
		return;
	}

	//AfxMessageBox(_T("2"));

	for(d=alldevs; d; d=d->next)
	{
		//InitIp(d);

		if (bOnllyShowDesc)
		{
			strText= CString(d->description);
		}
		else
		{
			strText.Format(_T("%s(%s)"), CString(d->name), CString(d->description));
		}

		strText.Replace(CString(PCAP_SRC_IF_STRING), _T(""));
		AddString(strText);
		i++;
	}

	//AfxMessageBox(_T("3"));

	pcap_freealldevs(alldevs);

	if(i > 0)
	{
		SetCurSel(0);
	}

	//AfxMessageBox(_T("4"));
}

void CNetDeviceComboBox::InitIp(pcap_if_t *d)
{
	if (m_strIP.GetLength() >= 7)
	{
		return;
	}

	pcap_addr *addr = d->addresses;
	
	while (addr != NULL)
	{
		if (addr->addr == NULL)
		{
			break;
		}

		if (addr->addr->sa_family == AF_INET)
		{
			BYTE *p = (BYTE*)(addr->addr->sa_data);

			while (*p == 0)
			{
				p++;
			}

			m_byte1 = *p++;
			m_byte2 = *p++;
			m_byte3 = *p++;
			m_byte4 = *p++;
			m_strIP.Format(_T("%d.%d.%d.%d"), m_byte1, m_byte2, m_byte3, m_byte4);

			break;
		}

		addr = addr->next;
	}
}


