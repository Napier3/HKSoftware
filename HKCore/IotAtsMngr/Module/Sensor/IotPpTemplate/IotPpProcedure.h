//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProcedure.h  CIotPpProcedure

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpInterface.h"
#include "IotPpNode.h"

class CIotPpProcedure : public CExBaseList
{
public:
	CIotPpProcedure();
	virtual ~CIotPpProcedure();


//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPPROCEDURE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpProcedureKey();     }
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
	CIotPpInterface *m_pIotPpInterface;
	CIotPpNode *m_pIotPpNode;

//私有成员变量访问方法
public:
	CIotPpInterface* GetIotPpInterface()	{	return m_pIotPpInterface;	}
	CIotPpNode* GetIotPpNode()	{	return m_pIotPpNode;	}

//属性变量访问方法
public:
	CIotPpNode* GetRootNode();
	void UpdateNodeTimers(CDvmDataset *pAttrDataset);
};

