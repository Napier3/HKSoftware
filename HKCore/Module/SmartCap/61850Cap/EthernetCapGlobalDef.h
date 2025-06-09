#pragma once

#include "CapGlobalDef.h"

//#pragma pack(1)

#ifndef _PSX_IDE_QT_
#define HAVE_REMOTE
#include "../../../Module/WinPcap/Include/pcap.h"
#pragma comment(lib, "wpcap.lib")
#endif

typedef struct ether_header
{
	u_char  ether_dhost[6];      /* destination eth addr */
	u_char  ether_shost[6];      /* source ether addr    */
	u_short ether_type;          /* packet type ID field */
}ETHER_HEADER ,*PETHER_HEADER;


#define   EtherType_Priority 0x0081
#define   EtherType_Smv      0xBA88
#define   EtherType_Goose    0xB888

#define CAPCFGMASK_USESRCMAC  0X00000001
#define CAPCFGMASK_SRCMAC     0X00000002
#define CAPCFGMASK_USEDESTMAC 0X00000004
#define CAPCFGMASK_DESTMAC    0X00000008
#define CAPCFGMASK_CAPSMV     0X00000010
#define CAPCFGMASK_CAPGOOSE   0X00000020
#define CAPCFGMASK_CARDINDEX  0X00000040
#define CAPCFGMASK_ALL        0XFFFFFFFF

typedef struct ether_cap_config
{
	SHORT nUseSrcMac;
	SHORT nUseDestMac;
	BYTE  byteSrcMac[6];
	BYTE  byteDestMac[6];
	SHORT nCapSmv;
	SHORT nCapGoose;
	long  nNetCardIndex;
}ETHER_CAP_CONFIG, *PETHER_CAP_CONFIG;

#ifndef _PSX_IDE_QT_
class CStNetCardInfor
{
public:
	CStNetCardInfor(LPCSTR pName, LPCSTR pInfor, LPCSTR pIP)
	{
		m_strID = pName;
		m_strInfor = pInfor;
		m_strIP = pIP;
	}
public:
	CStringA m_strID;
	CStringA m_strInfor;
	CStringA m_strIP;
};

class CStNetCardInforList : public CTLinkList<CStNetCardInfor> 
{
private:
	CStNetCardInforList()	{}
	virtual ~CStNetCardInforList(){};

	CStNetCardInfor* AddNew(LPCSTR pName, LPCSTR pInfor, LPCSTR pIP)
	{	
		CStNetCardInfor *pNew = new CStNetCardInfor(pName, pInfor, pIP);
		AddTail(pNew);
		return pNew;
	}

	void InitNetCardInfor();
	static long g_nSTGRef;
	void InitIp(pcap_if_t *d, CStringA &strIP);


public:
	static CStNetCardInforList* g_pNetCardList;
	static CStNetCardInforList* Create();
	static void Release();
	static void InsertToComboBox(CComboBox *pComboBox);
};
#endif
