#pragma once

#include "GbWzdAiScript.h"
#include "GbWzdAiParasBase.h"

/*
第一步：跟随Tool对象，执行每个case的计算，获取当前满足条件的case
第二步：Tool遍历所有的switch，传入整个模型，对每个case进行赋值操作
第三步：每个case，遍历所有的dvm-match object，进行计算
*/
//////////////////////////////////////////////////////////////////////////
class CGbAiCase : public CGbAiOptrBase
{
public:
	CGbAiCase(void);
	virtual ~CGbAiCase(void);

	static CGbAiCase* _New(CExBaseObject *pParent)
	{
		CGbAiCase *pNew = new CGbAiCase();
		pNew->SetParent(pParent);
		return pNew;
	}

	CGbWzdAiParasBase *m_pParas;
	CGbAiParaScript *m_pScript;
	CString m_strValue;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiCase;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiCaseKey ;	}

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
	virtual void InitMacroPara(CDataGroup *pMacroParas);

	//针对需要第二轮进行数据处理的，例如switch/case
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};


//////////////////////////////////////////////////////////////////////////
class CGbAiSwitch : public CGbAiOptrBase
{
public:
	CGbAiSwitch();
	virtual ~CGbAiSwitch();

	CGbAiCase *m_pActiveCase;  //活动的case
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiSwitch;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiSwitchKey ;	}

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
	virtual void InitMacroPara(CDataGroup *pMacroParas);
	virtual void ClearScptState();

	//针对需要第二轮进行数据处理的，例如switch/case
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};

