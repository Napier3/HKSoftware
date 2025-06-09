#include "StdAfx.h"
#include "TcpDeal.h"

CTcpDeal::CTcpDeal(void)
{

}

CTcpDeal::~CTcpDeal(void)
{

}

CString CTcpDeal::GetValueFromByteArray(CByteArray &m_Array,int m_StartPos,int m_Length)
{
	CString strResult = _T("");
	for (int i =0;i<m_Length;i++)
	{
		CString temp;
		BYTE t_Byte = m_Array.GetAt(m_StartPos+i);
		temp.Format(_T("%.2X"),t_Byte);
		strResult+=temp;
	}
	return strResult;
}
