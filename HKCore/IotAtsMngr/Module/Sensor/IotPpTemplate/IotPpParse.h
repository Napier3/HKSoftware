//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpParse.h  CIotPpParse

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpPkgHead.h"
#include "IotPpDataList.h"

class CIotPpParse : public CExBaseList
{
public:
	CIotPpParse();
	virtual ~CIotPpParse();


	CString  m_strDs_Optr;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPPARSE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpParseKey();     }
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
protected:
	CIotPpPkgHead *m_pIotPpPkgHead;
	CIotPpDataList *m_pIotPpDataList;

//私有成员变量访问方法
public:
	CIotPpPkgHead* GetIotPpPkgHead()	{	return m_pIotPpPkgHead;	}
	CIotPpDataList* GetIotPpDataList()	{	return m_pIotPpDataList;	}

//属性变量访问方法
public:
	CString GetDatasetID();
	BOOL IsModelOptr_Write(){return m_strDs_Optr == _T("write");}
};

