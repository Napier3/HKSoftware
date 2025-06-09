#include "stdafx.h"
#include "GbWzdCmdGbAttr.h"
#include "GuideBookWizard.h"
#include "..\XLanguageResourceAts.h"
#define GBWZDDVM_STATE_EDIT_DEVICE           0
#define GBWZDDVM_STATE_EDIT_DEVICEMODEL      1
#define GBWZDDVM_STATE_EDIT_CHARACTERISTIC   2

CGbWzdCmdGbAttr::CGbWzdCmdGbAttr()
{
	m_nGbWzdCmdGbAttrIndex = -1;
	m_strName = /*_T("设置测试模板的属性")*/g_sLangTxt_SetTestTemAttr;
	m_strID = _T("GbAttr");
}


CGbWzdCmdGbAttr::~CGbWzdCmdGbAttr()
{
	
}


long CGbWzdCmdGbAttr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdGbAttr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
// 	CGbWzdCmd::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strNameKey,oNode,m_strGbName);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIDKey,oNode,m_strGbID);

	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pGbXmlKeys->m_strMacroFileKey,oNode,m_strTestMacroFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strTestTypeFileKey,oNode,m_strTestTypeFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDeviceIDKey,oNode,m_strDevID);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDevByKey,oNode,m_strDevBy);
	xml_GetAttibuteValue(pGbXmlKeys->m_strVersionKey,oNode,m_strVersion);
	xml_GetAttibuteValue(pGbXmlKeys->m_strCommCmdConfigFileKey,oNode,m_strCommCmdConfigFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strScriptMngrFileKey,oNode,m_strScriptMngrFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDvmFileKey,oNode,m_strDvmFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strStandNameFileKey,oNode,m_strStandNameFile);
	xml_GetAttibuteValue(pGbXmlKeys->m_strDeviceModelFileKey,oNode,m_strDeviceModelFile);

	return 0;
}

long CGbWzdCmdGbAttr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CGbWzdCmd::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strGbName);
	xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strGbID);

	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pGbXmlKeys->m_strTestTypeFileKey,oElement,m_strTestTypeFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strMacroFileKey,oElement,m_strTestMacroFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strDeviceIDKey,oElement, m_strDevID);
	xml_SetAttributeValue(pGbXmlKeys->m_strDevByKey,oElement,m_strDevBy);
	xml_SetAttributeValue(pGbXmlKeys->m_strVersionKey,oElement,m_strVersion);
	xml_SetAttributeValue(pGbXmlKeys->m_strCommCmdConfigFileKey,oElement,m_strCommCmdConfigFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strScriptMngrFileKey,oElement,m_strScriptMngrFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(pGbXmlKeys->m_strDvmFileKey,oElement,m_strDvmFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strStandNameFileKey,oElement,m_strStandNameFile);
	xml_SetAttributeValue(pGbXmlKeys->m_strDeviceModelFileKey,oElement,m_strDeviceModelFile);

	return 0;
}

BSTR CGbWzdCmdGbAttr::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdGbAttrKey();
}


BOOL CGbWzdCmdGbAttr::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdGbAttr::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdGbAttr::Clone()
{
	CGbWzdCmdGbAttr *pNew = new CGbWzdCmdGbAttr();
	Copy(pNew);
	return pNew;
}


BOOL CGbWzdCmdGbAttr::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);

	CGuideBook *pGuideBook = GetGuideBook();
	CTreeCtrl *pGbTree = GetGuideBookEditTreeCtrl();
	CFrameWnd* pFrameWnd = GetMaiFrame();
	CDevice *pDevice = NULL;
	CGbWzdAutoConfig *pWzdAutoCfg = CGuideBookWizard::GetGbWzdAutoConfig();

	if (dwExecMode == WZDEXEC_AUTO)
	{
		InitGuideBook(pGuideBook);
	}


	if (pWzdAutoCfg != NULL)
	{
		pGuideBook->m_strName = pWzdAutoCfg->m_strName;

		if (pWzdAutoCfg->m_strID.GetLength() > 0)
		{
			pGuideBook->m_strID = pWzdAutoCfg->m_strID;
		}
		else
		{
			pGuideBook->m_strID = pWzdAutoCfg->m_strName;
		}
	}

	pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pGuideBook, (LPARAM)pGuideBook);
	ShowGbWzdMsg(/*_T("设置测试模板的属性：主要设置测试功能文件、规约种类选择")*/g_sLangTxt_SetTestTemAttr2);

	if (CGuideBookWizard::IsQuickWizard())
	{
		CFrameWnd *pFrameWnd = GetMaiFrame();
		pFrameWnd->PostMessage(WM_EXEC_GBWZD_EXEC_NEXT, 0, 0);
	}

	return TRUE;
}


void CGbWzdCmdGbAttr::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdGbAttr::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;

	return TRUE;
}

void CGbWzdCmdGbAttr::InitByGuideBook(CGuideBook *pGuideBook)
{
	m_strGbName = pGuideBook->m_strName;
	m_strGbID = pGuideBook->m_strID;
	m_strDevBy = pGuideBook->m_strDevBy;
	m_strVersion = pGuideBook->m_strVersion;
	m_strPpTemplateFile = pGuideBook->m_strPpTemplateFile; 
	m_strCommCmdConfigFile = pGuideBook->m_strCommCmdConfigFile;
	m_strScriptMngrFile = pGuideBook->m_strScriptMngrFile;
	m_strTestMacroFile = pGuideBook->m_strTestMacroFileID;
	m_strTestTypeFile = pGuideBook->m_strTestTypeFile;
	m_strPpEngineProgID = pGuideBook->m_strPpEngineProgID;
	m_strDvmFile = pGuideBook->m_strDvmFile;

	m_strDeviceModelFile = pGuideBook->m_strDeviceModelFile;
	m_strDevID = pGuideBook->m_strDevID;
	m_strStandNameFile = pGuideBook->m_strStandNameFile;
}

void CGbWzdCmdGbAttr::InitGuideBook(CGuideBook *pGuideBook)
{
	pGuideBook->m_strName = m_strGbName;
	pGuideBook->m_strID = m_strGbID;
	pGuideBook->m_strDevBy = m_strDevBy;
	pGuideBook->m_strVersion = m_strVersion;
	pGuideBook->m_strPpTemplateFile = m_strPpTemplateFile; 
	pGuideBook->m_strCommCmdConfigFile = m_strCommCmdConfigFile;
	pGuideBook->m_strScriptMngrFile = m_strScriptMngrFile;
	pGuideBook->m_strTestMacroFileID = m_strTestMacroFile;
	pGuideBook->m_strTestTypeFile = m_strTestTypeFile;
	pGuideBook->m_strPpEngineProgID = m_strPpEngineProgID;
	pGuideBook->m_strDvmFile = m_strDvmFile;

	pGuideBook->m_strDeviceModelFile = m_strDeviceModelFile;
	pGuideBook->m_strDevID = m_strDevID;
	pGuideBook->m_strStandNameFile = m_strStandNameFile;
}

