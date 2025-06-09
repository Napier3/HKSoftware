#ifndef CSTTITEMSTATEOBJECT_H
#define CSTTITEMSTATEOBJECT_H

#include "../../../../Module/BaseClass/ExBaseObject.h"
#include "../SttParas.h"

class CSttItemStateObject : public CExBaseObject
{
public:
	CExBaseObject* m_pItem;
	long m_nDeviceIndex;
	long m_nReportIndex;
	long m_nItemIndex;
	CString m_strItemID;
	long m_nState;
	CSttParas* m_pParas;

public:
	CSttItemStateObject();
	virtual ~CSttItemStateObject();

	void SetItemState(CExBaseObject *pItem, long nDeviceIndex, long nReportIndex,
		long nItemIndex, const CString& strItemID, long nState, CSttParas *pParas);
	void FreeItemState();
};

#endif//!CSTTITEMSTATEOBJECT_H