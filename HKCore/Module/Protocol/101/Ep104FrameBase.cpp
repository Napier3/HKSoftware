#include "StdAfx.h"
#include "Ep104FrameBase.h"

CEp104FrameBase::CEp104FrameBase(void)
{
//	m_byteControl = 0;  //控制域（C）的定义
	m_byteLinkAddr = 0;     //链路地址域

// 	m_byteDIR = 0;
// 	m_bytePRM = 0;
// 	m_byteFCB_ACD = 0;
// 	m_byteFCV_DFC = 0;
// 	m_byteFuncCode = 0;
}

CEp104FrameBase::~CEp104FrameBase(void)
{

}

void CEp104FrameBase::AddControlByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteControl)
{
	m_pControl = new CEpByteBlockControl(byteControl);
	m_pControl->m_strID = strID;
	m_pControl->m_strName = strID;
	m_pControl->m_nIndex = nIndex;
	m_pControl->m_nLength = nLen;
	pDetailList->AddNewChild(m_pControl);
}

