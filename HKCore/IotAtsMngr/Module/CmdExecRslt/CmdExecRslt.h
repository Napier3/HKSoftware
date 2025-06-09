//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CmdExecRslt.h  CCmdExecRslt

#pragma once

#include "CmdExecGlobal.h"


#include "ExecResult.h"

class CCmdExecRslt : public CExBaseList
{
public:
	CCmdExecRslt();
	virtual ~CCmdExecRslt();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CCMDEXECRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CCmdExecXmlRWKeys::CCmdExecRsltKey();     }
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
	CDvmDataset *m_pDvmDataset;
	CExecResult *m_pExecResult;

//私有成员变量访问方法
public:
	CDvmDataset* GetDvmDataset()	{	return m_pDvmDataset;	}
	CExecResult* GetExecResult()	{	return m_pExecResult;	}

//属性变量访问方法
public:
	void GenerateCmdExecRslt(long nRslt,CDvmDataset *pDataset);
};

