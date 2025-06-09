//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeWithApp.h  CEdgeWithApp

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeFile.h"
#include "EdgeCfgCpu.h"
#include "EdgeCfgMem.h"
#include "EdgeCmdErrorMngr.h"

class CEdgeWithApp : public CEdgeCmdErrorMngr
{
public:
	CEdgeWithApp();
	virtual ~CEdgeWithApp();


	CString  m_strVersion;
	CString  m_strEnable;
//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEWITHAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeWithAppKey();     }
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
	CEdgeFile *m_pEdgeFile;
	CEdgeCfgMem *m_pEdgeCfgMem;
	CEdgeCfgCpu *m_pEdgeCfgCpu;

//私有成员变量访问方法
public:
	CEdgeFile* GetEdgeFile()	{	return m_pEdgeFile;	}
	void SetEdgeFile(CEdgeFile* pEdgeFile)	{	m_pEdgeFile = pEdgeFile;AddTail(pEdgeFile);	}
	CEdgeCfgMem* GetEdgeCfgMem()	{	return m_pEdgeCfgMem;	}
	void SetEdgeCfgMem(CEdgeCfgMem* pEdgeCfgMem)	{	m_pEdgeCfgMem = pEdgeCfgMem;AddTail(pEdgeCfgMem);	}
	CEdgeCfgCpu* GetEdgeCfgCpu()	{	return m_pEdgeCfgCpu;	}
	void SetEdgeCfgCpu(CEdgeCfgCpu* pEdgeCfgCpu)	{	m_pEdgeCfgCpu = pEdgeCfgCpu;AddTail(pEdgeCfgCpu);	}

//属性变量访问方法
public:
};

