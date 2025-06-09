#pragma once
#include "../SttCmdDefineGlobal.h"

class CSttTestMacroCharParas :public CExBaseObject
{
public:
	CSttTestMacroCharParas(void);
	~CSttTestMacroCharParas(void);

//属性：
public:
	CString m_strParaText;

//公共接口：
public:

//重写父类方法：
	virtual UINT GetClassID()		{			return STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTestMacroCharParasKey;			}
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL UpdateOwn(CBaseObject* pDest);
};
