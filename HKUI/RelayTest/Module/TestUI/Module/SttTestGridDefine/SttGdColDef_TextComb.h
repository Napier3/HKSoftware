//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_TextComb.h  CSttGdColDef_TextComb

#pragma once

#include "SttTestGridDefineGlobal.h"



class CSttGdColDef_TextComb : public CExBaseObject
{
public:
	CSttGdColDef_TextComb();
	virtual ~CSttGdColDef_TextComb();


	CString  m_strPrevText;
	CString  m_strAfterText;
	long  m_nWithUnit;
	CString  m_strDecimal;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDef_TextCombKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

