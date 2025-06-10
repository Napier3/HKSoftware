#pragma once

#include "ProtocolEngineInterface.h"

class CPpsttEngineCreator : public CProtocolEngineCreatorInterface
{
public:
	CPpsttEngineCreator();
	virtual ~CPpsttEngineCreator();

public:
	virtual CProtocolEngineInterface* GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID);
	virtual void ReleasePpEngine(const CString &strProgID);
	virtual void ReleasePpEngine();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);
	virtual BOOL HasPpEngine();
	virtual void InitPpEngineShowSpyWnd();
    virtual long ConfigEngine();

private:
	CProtocolEngineInterface* NewProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID);
};

