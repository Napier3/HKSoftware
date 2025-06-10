#include "SttItemStateObject.h"

CSttItemStateObject::CSttItemStateObject()
{
	m_pItem = NULL;
	m_pParas = NULL;
	m_nDeviceIndex = 0;
	m_nReportIndex = 0;
	m_nItemIndex = 0;
	m_nState = 0;
}

CSttItemStateObject::~CSttItemStateObject()
{
	FreeItemState();
}

void CSttItemStateObject::SetItemState(CExBaseObject *pItem, long nDeviceIndex, long nReportIndex,
				  long nItemIndex, const CString& strItemID, long nState, CSttParas *pParas)
{
	m_pItem = pItem;
	m_nDeviceIndex = nDeviceIndex;
	m_nReportIndex = nReportIndex;
	m_nItemIndex = nItemIndex;
	m_strItemID = strItemID;
	m_nState = nState;
	m_pParas = (CSttParas*)pParas->CloneEx(TRUE, TRUE);
}

void CSttItemStateObject::FreeItemState()
{
	if(m_pItem)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	if(m_pParas)
	{
		delete m_pParas;
		m_pParas = NULL;
	}
}