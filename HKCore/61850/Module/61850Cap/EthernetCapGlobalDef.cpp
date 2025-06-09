#include "StdAfx.h"
#include "EthernetCapGlobalDef.h"


//////////////////////////////////////////////////////////////////////////

// class CCapIpGroupColor
// {
// public:
// 	CCapIpGroupColor(_ETHER_CAP_IP_GROUP &ip)
// 	{
// 		//memset(&m_ipGroup, 0, sizeof(_ETHER_CAP_IP_GROUP));
// 		m_ipGroup = ip;
// 	}
// 
// 	virtual ~CCapIpGroupColor()	{}
// 
// public:
// 	_ETHER_CAP_IP_GROUP m_ipGroup;
// 	COLORREF m_crIpGroup;
// 
// 	BOOL IsEqual(_ETHER_CAP_IP_GROUP &ip)
// 	{
// 		return (( m_ipGroup.dst.ip.s_addr == ip.dst.ip.s_addr) && (m_ipGroup.src.ip.s_addr == ip.src.ip.s_addr));
// 	}
// };
// 
// class CCapIpGroupColorMngr : public CTLinkList<CCapIpGroupColor> 
// {
// public:
// 	CCapIpGroupColorMngr()
// 	{
// 
// 	}
// 
// 	virtual ~CCapIpGroupColorMngr()	{		DeleteAll();		}
// 
// private:
// 	CCapIpGroupColor* FindCapIpGroupColor(_ETHER_CAP_IP_GROUP &ip)
// 	{
// 		POS pos = GetHeadPosition();
// 		CCapIpGroupColor *p = NULL;
// 		CCapIpGroupColor *pFind = NULL;
// 
// 		while (pos != NULL)
// 		{
// 			p = GetNext(pos);
// 
// 			if (p->IsEqual(ip))
// 			{
// 				pFind = p;
// 				break;
// 			}
// 		}
// 
// 		if (pFind == NULL)
// 		{
// 			static COLORREF crArray[10] = {RGB(0, 0, 255), RGB(0, 128, 64), RGB(0, 255, 255)
// 				, RGB(255, 128, 64), RGB(128, 128, 64), RGB(255, 128, 128)
// 				, RGB(255, 255, 128), RGB(128, 128, 192), RGB(128, 64, 64)
// 				, RGB(0, 64, 0), };
// 			
// 			pFind = new CCapIpGroupColor(ip);
// 			long nCount = GetCount();
// 			nCount %= 10;
// 			pFind->m_crIpGroup = crArray[nCount];
// 			AddTail(pFind);
// 		}
// 
// 		return pFind;
// 	}
// 
// public:
// 	COLORREF GetCapIpGroupColor(_ETHER_CAP_IP_GROUP &ip)
// 	{
// 		CCapIpGroupColor *p = FindCapIpGroupColor(ip);
// 		return p->m_crIpGroup;
// 	}
// 
// };
// 
// CCapIpGroupColorMngr g_oCapIpGroupColorMngr;
// 
// COLORREF GetCapIpGroupColor(_ETHER_CAP_IP_GROUP &ip)
// {
// 	return g_oCapIpGroupColorMngr.GetCapIpGroupColor(ip);
// }

CStNetCardInforList* CStNetCardInforList::g_pNetCardList = NULL;
long CStNetCardInforList::g_nSTGRef = 0;

CStNetCardInforList* CStNetCardInforList::Create()
{
	g_nSTGRef++;

	if (g_nSTGRef == 1)
	{
		g_pNetCardList = new CStNetCardInforList();
		g_pNetCardList->InitNetCardInfor();
	}

	return g_pNetCardList;
}

void CStNetCardInforList::Release()
{
	g_nSTGRef--;

	if (g_nSTGRef == 0)
	{
		delete g_pNetCardList;
		g_pNetCardList = NULL;
	}
}

void CStNetCardInforList::InitNetCardInfor()
{
	pcap_if_t* alldevs = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		TRACE("Error in pcap_findalldevs: %s\n", errbuf);
		return ;
	}

	CStringA strIP;
	for(pcap_if_t* d=alldevs; d;  d=d->next)
	{
		if (d->description)
		{
			TRACE(" %s : (%s)\n", d->name, d->description);
			InitIp(d, strIP);
			AddNew(d->name, d->description, strIP);
		}
		else
		{
			TRACE(" %s : (no info.)\n", d->name);
		}
	}	
}

void CStNetCardInforList::InitIp(pcap_if_t *d, CStringA &strIP)
{
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

			BYTE byte1 = *p++;
			BYTE byte2 = *p++;
			BYTE byte3 = *p++;
			BYTE byte4 = *p++;
			strIP.Format(("%d.%d.%d.%d"), byte1, byte2, byte3, byte4);

			break;
		}

		addr = addr->next;
	}
}

