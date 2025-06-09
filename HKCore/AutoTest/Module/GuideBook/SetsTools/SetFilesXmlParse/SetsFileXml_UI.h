
#pragma once

#include "SetFileXmlParseGlobal.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"



class CSetsFileXml_UI : public CExBaseObject
{
public:
	CSetsFileXml_UI();
	virtual ~CSetsFileXml_UI();


	CString  m_strClass;
	CString  m_strmd5;

	//2024-11-15 yuanting
	CString  m_strLd;
	long  m_nGrp;
	pugi::xml_node *m_pNode;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_UI;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey();     }
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
	void SetGrp(long nGrp);
	void SetClass(const CString &strClass);
	void SetMd5(const CString &strMd5);
	void SetLd(const CString &strLd);

//属性变量访问方法
public:
};

