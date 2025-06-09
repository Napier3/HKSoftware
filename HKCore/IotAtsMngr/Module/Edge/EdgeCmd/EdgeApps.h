//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeApps.h  CEdgeApps

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeProcess.h"

class CEdgeApps : public CExBaseList
{
public:
	CEdgeApps();
	virtual ~CEdgeApps();


	CString  m_strApp;
	CString  m_strVersion;
	CString  m_strAppHash;
	long  m_nSrvNumber;
	long  m_nLifeTime;
//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEAPPS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeAppsKey();     }
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
	CEdgeProcess *m_pEdgeProcess;

//私有成员变量访问方法
public:
	CEdgeProcess* GetEdgeProcess()	{	return m_pEdgeProcess;	}
	void SetEdgeProcess(CEdgeProcess* pEdgeProcess)	{	m_pEdgeProcess = pEdgeProcess;AddTail(pEdgeProcess);	}

//属性变量访问方法
public:
};

