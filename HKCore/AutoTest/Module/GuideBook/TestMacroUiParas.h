#pragma once
#include "GuideBookDefine.h"

class CTestMacroUiParas :public CExBaseObject
{
public:
	CTestMacroUiParas(void);
	~CTestMacroUiParas(void);

//���ԣ�
public:
	CString m_strParaText;

//�����ӿڣ�
public:
// 	void SetParaText(const CString &strParaText)	{	m_strParaText = strParaText;	}
// 	CString GetParaText()		{	return m_strParaText;	}

//��д���෽����
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
