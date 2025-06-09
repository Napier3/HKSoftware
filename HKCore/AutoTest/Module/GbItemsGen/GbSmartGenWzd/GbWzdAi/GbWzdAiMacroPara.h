#pragma once

#include "GbWzdAiScript.h"
class CGbAiSwitch;
#include "../../../../../SttStudio/Module/SttCmd/GuideBook/SttGuideBook.h"

//////////////////////////////////////////////////////////////////////////
//
class CGbWzdAiValueSet : public CGbAiOptrInterface
{
public:
	CGbWzdAiValueSet(void);
	virtual ~CGbWzdAiValueSet(void);

	CString m_strType;  
	CString m_strValue;  

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiValSet;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiValSetKey ;	}

	virtual CBaseObject* Clone();

public:
	void SetParaValue(CDvmData *pPara, CDvmData *pDvmData, CSttGuideBook *pSttGuideBook);
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};


//////////////////////////////////////////////////////////////////////////
class CGbWzdAiMacroPara : public CGbAiOptrBase
{
public:
	CGbWzdAiMacroPara(void);
	virtual ~CGbWzdAiMacroPara(void);

	CString m_strExpr;    //表达式
	
	CDvmData *m_pMacroParaRef;    //关联的参数对象
	CDvmData *m_pDvmDataRef;     //关联的数据模型对象，通过智能识别和匹配得到

	CGbAiParaScript *m_pScript;
	CGbWzdAiValueSet *m_pValSet;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiMacroPara;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiMacroParatKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
	virtual void InitMacroPara(CDataGroup *pMacroParas);

	void InitGbAiDataKey(CXKeyDB *pKeyDB);
	void SetParaValue(CDvmData *pPara, CDvmData *pDvmData, CSttGuideBook *pSttGuideBook);
};
