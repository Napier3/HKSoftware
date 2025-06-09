
#pragma once
#include "../../Module/BaseClass/ExBaseList.h"

class CDataNode : public CExBaseList
{
public:
	CDataNode();
	virtual ~CDataNode();

	UINT    m_type;
	UINT    m_datType;
	UINT    m_upReason;

public:
	BOOL Empty();
	CDataNode* Child(const CString &strID);
	CDataNode* AppendChild(const CString &strID, UINT nType);
};


