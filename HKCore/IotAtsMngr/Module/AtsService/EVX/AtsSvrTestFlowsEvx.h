//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrTestFlowsEvx.h  CAtsSvrTestFlowsEvx

#pragma once

#include "AtsSvrTestFlowEvx.h"
#include "../AtsSvrTestFlows.h"

class CAtsSvrTestFlowsEvx : public CAtsSvrTestFlows
{
public:
	CAtsSvrTestFlowsEvx();
	virtual ~CAtsSvrTestFlowsEvx();

//���غ���
public:
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

public:
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)	{	return 0;	}

};

