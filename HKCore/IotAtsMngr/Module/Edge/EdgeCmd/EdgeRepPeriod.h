//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeRepPeriod.h  CEdgeRepPeriod

#pragma once

#include "EdgeCmdMngrGlobal.h"
#include "EdgeCmdErrorMngr.h"

class CEdgeRepPeriod : public CEdgeCmdErrorMngr
{
public:
	CEdgeRepPeriod();
	virtual ~CEdgeRepPeriod();


	long  m_nDevPeriod;
	long  m_nConPeriod;
	long  m_nAppPeriod;
	long  m_nHeartPeriod;
//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEREPPERIOD;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeRepPeriodKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	void InitRepPeriod(long nDevPeriod, long nConPeriod, long nAppPeriod, long nHeartPeriod = 0){
		m_nDevPeriod = nDevPeriod;
		m_nConPeriod = nConPeriod;
		m_nAppPeriod = nAppPeriod;
		m_nHeartPeriod = nHeartPeriod;
	}
};

