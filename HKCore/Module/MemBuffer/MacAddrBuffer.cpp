// MacAddrBuffer.cpp: implementation of the CMacAddrBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MacAddrBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/*
CString strMac = _T("12-34-56-78-90-FF");
BYTE bMacAddr[6];

CMacAddrBuffer oMacAddr;
oMacAddr.SetMacAddr(strMac);
oMacAddr.GetMacAddr(bMacAddr);

CMacAddrBuffer oMacAddr2;
oMacAddr2.SetMacAddr(bMacAddr);
CString str = oMacAddr2.GetMacAddr();

*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMacAddrBuffer::CMacAddrBuffer()
{
	
}


CMacAddrBuffer::~CMacAddrBuffer()
{

}

BOOL CMacAddrBuffer::SetMacAddr(const CString &strMacAddr)
{
	InitBuffer(strMacAddr);
	FormatBuffer('-');
	char *pMac = NULL;
	ResetPointer();
	long nCount = 0;
	long nIndex = 5;
	memset(m_byteMacAddr, 0, 6);

	while (IsPoiterInBuffer())
	{
		pMac = GetString();
		m_byteMacAddr[nIndex] = HexToValue((BYTE)pMac[0], (BYTE)pMac[1]);
		pMac = NextString();
		nIndex--;

		if (nIndex<0)
		{
			break;
		}
	}

	return TRUE;
}

BOOL CMacAddrBuffer::SetMacAddr(BYTE b6, BYTE b5, BYTE b4, BYTE b3, BYTE b2, BYTE b1)
{
	m_strMacAddr.Empty();
	AppendMacAddr(b6);
	AppendMacAddr(b5);
	AppendMacAddr(b4);
	AppendMacAddr(b3);
	AppendMacAddr(b2);
	AppendMacAddr(b1, FALSE);

	return TRUE;
}

void CMacAddrBuffer::AppendMacAddr(BYTE bVal, BOOL bAddDot)
{
	char pszMacAddr[3];
	pszMacAddr[2] = 0;

	ValueToHex(bVal, pszMacAddr[0], pszMacAddr[1]);
	m_strMacAddr += pszMacAddr;

	if (bAddDot)
	{
		m_strMacAddr += _T("-");
	}
}


BOOL CMacAddrBuffer::SetMacAddr(BYTE *pMacAddr)
{
	return SetMacAddr(pMacAddr[5], pMacAddr[4], pMacAddr[3], pMacAddr[2], pMacAddr[1], pMacAddr[0]);
}


CString CMacAddrBuffer::GetMacAddr()
{
	return m_strMacAddr;
}

BOOL CMacAddrBuffer::GetMacAddr(BYTE &b6, BYTE &b5, BYTE &b4, BYTE &b3, BYTE &b2, BYTE &b1)
{
	b6 = m_byteMacAddr[5];
	b5 = m_byteMacAddr[4];
	b4 = m_byteMacAddr[3];
	b3 = m_byteMacAddr[2];
	b2 = m_byteMacAddr[1];
	b1 = m_byteMacAddr[0];

	return TRUE;
}

BOOL CMacAddrBuffer::GetMacAddr(BYTE *pMacAddr)
{
	memcpy(pMacAddr, m_byteMacAddr, 6);
	return TRUE;
}

