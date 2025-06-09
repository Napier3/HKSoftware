//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeAppCfgs.h  CEdgeAppCfgs

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeCfgMem.h"
#include "EdgeCfgCpu.h"

class CEdgeAppCfgs : public CExBaseList
{
public:
	CEdgeAppCfgs();
	virtual ~CEdgeAppCfgs();


	CString  m_strApp;
//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEAPPCFGS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeAppCfgsKey();     }
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
	CEdgeCfgCpu *m_pEdgeCfgCpu;
	CEdgeCfgMem *m_pEdgeCfgMem;

//私有成员变量访问方法
public:
	CEdgeCfgCpu* GetEdgeCfgCpu()	{	return m_pEdgeCfgCpu;	}
	void SetEdgeCpuLmt(CEdgeCfgCpu* pEdgeCfgCpu)	{	m_pEdgeCfgCpu = pEdgeCfgCpu;AddTail(pEdgeCfgCpu);	}
	CEdgeCfgMem* GetEdgeCfgMem()	{	return m_pEdgeCfgMem;	}
	void SetEdgeMemLmt(CEdgeCfgMem* pEdgeCfgMem)	{	m_pEdgeCfgMem = pEdgeCfgMem;AddTail(pEdgeCfgMem);	}

//属性变量访问方法
public:
};

