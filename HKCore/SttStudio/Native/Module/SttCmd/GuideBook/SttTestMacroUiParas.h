#pragma once
#include "../SttCmdDefineGlobal.h"

class CSttTestMacroUiParas :public CExBaseObject
{
public:
	CSttTestMacroUiParas(void);
	~CSttTestMacroUiParas(void);

//���ԣ�
public:
	CString m_strParaText;

//�����ӿڣ�
public:

//��д���෽����
	virtual UINT GetClassID()		{			return STTGBXMLCLASSID_CSTTTESTMACROUIPARAS;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTestMacroUiParasKey;			}
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL UpdateOwn(CBaseObject* pDest);
};
