#pragma once
#include "EpProtocolCreator.h"

class CEpProtocolFactory : public CExBaseList
{
public:
	static CEpProtocolFactory* g_pEpFactory;
	static CEpProtocolFactory* Create();
	static void Release();
	static CProtocolBase* CreateProtocolByID(const CString &strID);
	static CProtocolBase* CreateProtocolByIndex(long nIndex);
	static CProtocolBase* CreateProtocolByID(DWORD dwProtocolID);

private:
	CEpProtocolFactory(void);
	virtual ~CEpProtocolFactory(void);
	static long g_nProtocolFactoryRef;

protected:
	void RegisterProtocol(const CString &strName, const CString &strID, DWORD dwProtocolID, EPPCREATE* pFunCreate);

	void RegisterProtocols();
};
