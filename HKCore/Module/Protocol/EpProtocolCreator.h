#pragma once

#include "..\ProtocolBase\ProtocolBase.h"

typedef CProtocolBase* (EPPCREATE)();

class CEpProtocolCreator : public CExBaseObject
{
public:
	CEpProtocolCreator(const CString &strName,const CString &strID, DWORD dwProtocolID, EPPCREATE* pFunCreate);
	virtual ~CEpProtocolCreator(void);

	CProtocolBase* Create()
	{
		CProtocolBase *pEpProtocol = m_pFunCreate();
		return pEpProtocol;
	}

	BOOL IsProtocol(DWORD dwProtocolID)
	{
			return (m_dwProtocolID == dwProtocolID);
	}

public:

private:
	EPPCREATE* m_pFunCreate;
	DWORD m_dwProtocolID;

private:
	CEpProtocolCreator(void ) {	}
};
