#pragma once

#include "GuideBookDefine.h"
#include "../../../Module/XVM/XvmScriptBuilder.h"

class CScriptText : public CExBaseObject
{
public:
	CScriptText();
	virtual ~CScriptText();

//属性
public:
	CString m_strScriptText;
// 	long m_nScriptID;				//脚本的ID，参见CTestItemBase   lijq-2010-07-25
	long m_nIsRef;
	char m_pszFuncName[SCRIPT_FUNC_NAME_MAXLEN];
	long m_nFuncNameLen;

	//脚本执行过程中跳转的项目ID，因为测试控制与作业指导书两个模块是分开的
	//所以，需要保存跳转的项目的ID，在执行完脚本后执行相关的跳转操作
	//跳转完成，清空m_strGotoItem

//公共接口
public:
	void SetScriptText(const CString &strScriptText)		{			m_strScriptText = strScriptText;			}
	CString GetScriptText()								{			return m_strScriptText;						}

	long InitFuncName(long &nScriptIndex);
//重写父类方法
public:
	virtual UINT GetClassID()		{			return GBCLASSID_SCRIPTTEXT;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeOwn_XVM(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strScriptKey;			}

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual BOOL UpdateOwn(CBaseObject* pDest);

	CExBaseObject* GetParentGbItem();
	CExBaseObject* GetScriptTextMngr();
	CScriptText* GetRefScriptText();

	virtual void ClearItemInDbState();
};

class CScriptTextInit : public CScriptText
{
public:
	CScriptTextInit(){};
	virtual ~CScriptTextInit(){};

public:
	virtual UINT GetClassID()		{			return GBCLASSID_SCRIPTTEXT_INIT;			}
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strScriptInitKey;			}
	virtual CBaseObject* Clone();
};

class CScriptTextName : public CScriptText
{
public:
	CScriptTextName(){};
	virtual ~CScriptTextName(){};

public:
	virtual UINT GetClassID()		{			return GBCLASSID_SCRIPTTEXT_NAME;			}
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strScriptNameKey;			}
	virtual CBaseObject* Clone();
};


class CScriptTextResult : public CScriptText
{
public:
	CScriptTextResult(){};
	virtual ~CScriptTextResult(){};

public:
	virtual UINT GetClassID()		{			return GBCLASSID_SCRIPTTEXT_RESULT;			}
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strScriptResultKey;			}
	virtual CBaseObject* Clone();
};


class CScriptTextMngr : public CExBaseList
{
public:
	CScriptTextMngr();
	virtual ~CScriptTextMngr();

	CString m_strScriptMngrFile;

public:
	virtual UINT GetClassID()		{			return GBCLASSID_SCRIPT_TEXT_MNGR;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strScriptMngrKey;			}

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	CScriptText* AddNewScriptText(const CString &strID);

	virtual BOOL OpenScriptMngrFile(const CString &strFile);
	virtual BOOL SaveScriptMngrFile(const CString &strFile);

public:
	void Import(CScriptTextMngr *pSrc);
};


class CScriptTextMngrGlobalPool : public CExBaseList
{
private:
	CScriptTextMngrGlobalPool();
	virtual ~CScriptTextMngrGlobalPool();

public:
	static CScriptTextMngrGlobalPool *g_pScriptTextMngrGlobalPool;
	static long g_nScriptTextMngrGlobalPool;

	static CScriptTextMngr* CreateScriptTextMngr(const CString &strFile);

	static void Create();
	static void Release();

};


inline BOOL Gb_IsScript(CExBaseObject *p)
{
	UINT nClassID = p->GetClassID();

	return ((GBCLASSID_SCRIPTTEXT == nClassID) 
		|| (GBCLASSID_SCRIPTTEXT_INIT == nClassID) 
		|| (GBCLASSID_SCRIPTTEXT_NAME == nClassID)
		|| (GBCLASSID_SCRIPTTEXT_RESULT == nClassID) );
}

