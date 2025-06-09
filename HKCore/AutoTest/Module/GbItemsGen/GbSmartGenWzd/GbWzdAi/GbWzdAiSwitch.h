#pragma once

#include "GbWzdAiScript.h"
#include "GbWzdAiParasBase.h"

/*
��һ��������Tool����ִ��ÿ��case�ļ��㣬��ȡ��ǰ����������case
�ڶ�����Tool�������е�switch����������ģ�ͣ���ÿ��case���и�ֵ����
��������ÿ��case���������е�dvm-match object�����м���
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

	//�����Ҫ�ڶ��ֽ������ݴ���ģ�����switch/case
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};


//////////////////////////////////////////////////////////////////////////
class CGbAiSwitch : public CGbAiOptrBase
{
public:
	CGbAiSwitch();
	virtual ~CGbAiSwitch();

	CGbAiCase *m_pActiveCase;  //���case
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

	//�����Ҫ�ڶ��ֽ������ݴ���ģ�����switch/case
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};

