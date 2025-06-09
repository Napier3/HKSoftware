//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlowsEvx.h  CAtsSvrTestFlowsEvx

#pragma once

#include "AtsSvrTestFlowEvx.h"
#include "../AtsSvrTestFlows.h"

class CAtsSvrTestFlowsEvx : public CAtsSvrTestFlows
{
public:
	CAtsSvrTestFlowsEvx();
	virtual ~CAtsSvrTestFlowsEvx();

//重载函数
public:
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

public:
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)	{	return 0;	}

};

