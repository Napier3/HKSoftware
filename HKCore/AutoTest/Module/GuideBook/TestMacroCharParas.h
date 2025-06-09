#pragma once
#include "GuideBookDefine.h"

//对于差动、阻抗边界搜索功能，需要在GenerateItems的REPLY报文、模板中保存特性曲线信息
//故增加此类
class CTestMacroCharParas :public CExBaseObject
{
public:
	CTestMacroCharParas(void);
	virtual ~CTestMacroCharParas(void);

//属性：
public:
	CString m_strParaText;

//公共接口：
public:
// 	void SetParaText(const CString &strParaText)	{	m_strParaText = strParaText;	}
// 	CString GetParaText()		{	return m_strParaText;	}

//重写父类方法：
	virtual UINT GetClassID()		{			return GBCLASSID_TESTMACROCHARPARAS;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strTestMacroCharParasKey;			}
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL UpdateOwn(CBaseObject* pDest);
};
