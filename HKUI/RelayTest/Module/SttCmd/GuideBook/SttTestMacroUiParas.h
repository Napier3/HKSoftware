#pragma once
#include "../SttCmdDefineGlobal.h"

class CSttTestMacroUiParas :public CExBaseObject
{
public:
	CSttTestMacroUiParas(void);
	~CSttTestMacroUiParas(void);

//属性：
public:
	CString m_strParaText;

//公共接口：
public:

//重写父类方法：
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
