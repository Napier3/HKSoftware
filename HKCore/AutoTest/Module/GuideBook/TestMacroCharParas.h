#pragma once
#include "GuideBookDefine.h"

//���ڲ���迹�߽��������ܣ���Ҫ��GenerateItems��REPLY���ġ�ģ���б�������������Ϣ
//�����Ӵ���
class CTestMacroCharParas :public CExBaseObject
{
public:
	CTestMacroCharParas(void);
	virtual ~CTestMacroCharParas(void);

//���ԣ�
public:
	CString m_strParaText;

//�����ӿڣ�
public:
// 	void SetParaText(const CString &strParaText)	{	m_strParaText = strParaText;	}
// 	CString GetParaText()		{	return m_strParaText;	}

//��д���෽����
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
