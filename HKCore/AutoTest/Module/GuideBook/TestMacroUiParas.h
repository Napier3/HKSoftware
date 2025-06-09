#pragma once
#include "GuideBookDefine.h"

class CTestMacroUiParas :public CExBaseObject
{
public:
	CTestMacroUiParas(void);
	~CTestMacroUiParas(void);

//属性：
public:
	CString m_strParaText;

//公共接口：
public:
// 	void SetParaText(const CString &strParaText)	{	m_strParaText = strParaText;	}
// 	CString GetParaText()		{	return m_strParaText;	}

//重写父类方法：
	virtual UINT GetClassID()		{			return GBCLASSID_TESTMACROUIPARAS;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strTestMacroUiParasKey;			}
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL UpdateOwn(CBaseObject* pDest);
};
