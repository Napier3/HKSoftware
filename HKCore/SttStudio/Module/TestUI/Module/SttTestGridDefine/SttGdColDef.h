//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef.h  CSttGdColDef

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdColDef_Para.h"
#include "SttGdColDef_Script.h"

class CSttGdColDef : public CExBaseList
{
public:
	CSttGdColDef();
	virtual ~CSttGdColDef();


	CString  m_strDataType;
	CString  m_strUnit;
	CString  m_strDecimal;
	CString  m_strMax;
	CString  m_strMin;
	long  m_nEditable;
	long  m_nWidth;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDefKey();     }
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
};

