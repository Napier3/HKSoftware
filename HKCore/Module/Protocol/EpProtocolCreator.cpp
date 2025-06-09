#include "StdAfx.h"
#include "EpProtocolCreator.h"

CEpProtocolCreator::CEpProtocolCreator(const CString &strName, const CString &strID, DWORD dwProtocolID, EPPCREATE* pFunCreate)
{
	m_strName = strName;
	m_strID = strID;
	m_pFunCreate = pFunCreate;
	m_dwProtocolID = dwProtocolID;
}

CEpProtocolCreator::~CEpProtocolCreator(void)
{

}
