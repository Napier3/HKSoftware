//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocText.h  CDocText

#pragma once

#include "DocCmpGlobal.h"



class CDocText : public CExBaseObject
{
public:
	CDocText();
	virtual ~CDocText();


	CString  m_strCmp_Id;
	CString  m_strTxt;
	long  m_nStart;
	long  m_nEnd;
	long  m_nError;
//重载函数
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	void Init();
	void SetCmpError();
	BOOL Cmp(CDocText *pRef);
};

