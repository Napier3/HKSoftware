//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageMngr.cpp  CXLanguageMngr


#include "stdafx.h"
#include "XLanguageMngr.h"
#include "XLanguageNameParser.h"
#include "../API/FileApi.h"
#include "../API/GlobalConfigApi.h"
#include "../DataMngr/DataMngrGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXLanguageMngr* CXLanguageMngr::g_pXLanguageMngr = NULL;
long CXLanguageMngr::g_nXLanguageMngrRef = 0;
BOOL CXLanguageMngr::g_bXInLanguageEditState = FALSE;

CXLanguageMngr* CXLanguageMngr::Create(CXLanguageResourceBase *pXLanguageResoure, const CString &strFileName)
{
	g_nXLanguageMngrRef++;

	if (g_nXLanguageMngrRef == 1)
	{
		g_pXLanguageMngr = new CXLanguageMngr();
		g_pXLanguageMngr->OpenXLangConfigFile(FALSE);
		g_pXLanguageMngr->m_pXLanguageResoure = pXLanguageResoure;
		pXLanguageResoure->RegisterLanguageResource();

		g_pXLanguageMngr->InitCurrLanguage();
	}

	return g_pXLanguageMngr;
}

CXLanguageMngr* CXLanguageMngr::Create(CXLanguageResourceBase *pXLanguageResoure, BOOL bUseCommonPath)
{
	g_nXLanguageMngrRef++;

	if (g_nXLanguageMngrRef == 1)
	{
		g_pXLanguageMngr = new CXLanguageMngr();
        g_pXLanguageMngr->OpenXLangConfigFile(bUseCommonPath);
		g_pXLanguageMngr->m_pXLanguageResoure = pXLanguageResoure;

//#ifdef _PSX_QT_LINUX_
		pXLanguageResoure->InitLangTxt();
//#endif
        pXLanguageResoure->RegisterLanguageResource();

		g_pXLanguageMngr->InitCurrLanguage();
	}

	return g_pXLanguageMngr;
}

//2022-3-25  lijunqing
void CXLanguageMngr::xlang_AddXLanguageRerouce(CXLanguageResourceBase *pXLanguageResoure, BOOL bUseCommonPath)
{
	pXLanguageResoure->InitLangTxt();
    pXLanguageResoure->RegisterLanguageResource();
    pXLanguageResoure->InitLangRsByFile();
    g_pXLanguageMngr->m_listXLanguageResoure.AddTail(pXLanguageResoure);
}

#ifdef _DEBUG
	
void CXLanguageMngr::CreateXLangSourceFile()
{
	if (m_pXLangSourceFile != NULL)
	{
		return;
	}

	m_pXLangSourceFile = new CFile();
	CString strFile;
	strFile = _P_GetLanguagePath(m_bUseLangCommonPath);

	CString strSoftName;
	strSoftName = _P_GetMoudleFileName();

	strFile.AppendFormat(_T("Source_%s.txt"), strSoftName);
	m_bXLangSourceFile = m_pXLangSourceFile->Open(strFile.GetString(), CFile::modeCreate | CFile::modeWrite);
}

void xlang_WriteText(CFile *pFile, const CString &strText)
{
#ifndef _PSX_IDE_QT_
#ifdef _UNICODE
	pFile->Write(strText, strText.GetLength()*2);
#else
	pFile->Write(strText, strText.GetLength());
#endif
#endif

}

void CXLanguageMngr::WriteXLangSourceFile()
{
#ifdef ENABLE_LANGUAGE
    if (m_listXLangSourceCode.GetCount() == 0)
	{
		return;
	}

	CreateXLangSourceFile();

	if (!m_bXLangSourceFile)
	{
		return;
	}

	POS pos = m_listXLangSourceCode.GetHeadPosition();
	CXLangItem *pItem = NULL;
	CString strCodeLine;
	CString strItemID;

	//写头文件
	while (pos != NULL)
	{
		pItem = (CXLangItem *)m_listXLangSourceCode.GetNext(pos);
		strItemID = pItem->m_strID.Mid(1);
		strCodeLine.Format(_T("static CString g_sLangID_%s;\r\n"), strItemID);
		xlang_WriteText(m_pXLangSourceFile, strCodeLine);
		strCodeLine.Format(_T("static CString g_sLangTxt_%s;\r\n"), strItemID);
		xlang_WriteText(m_pXLangSourceFile, strCodeLine);
	}
	
	strCodeLine = _T("\r\n\r\n\r\n\r\n");
	xlang_WriteText(m_pXLangSourceFile, strCodeLine);
	
	//写CPP文件代码
	pos = m_listXLangSourceCode.GetHeadPosition();
	while (pos != NULL)
	{
		pItem = (CXLangItem *)m_listXLangSourceCode.GetNext(pos);
		strItemID = pItem->m_strID.Mid(1);
		strCodeLine.Format(_T("CString CXLanguageResourceXxx::g_sLangID_%s = _T(\"s%s\");\r\n"), strItemID, strItemID);
		xlang_WriteText(m_pXLangSourceFile, strCodeLine);
		strCodeLine.Format(_T("CString CXLanguageResourceXxx::g_sLangTxt_%s = _T(\"%s\");"), strItemID, pItem->m_strSrcText);
		strCodeLine.Replace(_T("\n"), _T("\\n"));
		strCodeLine += _T("\r\n");
		xlang_WriteText(m_pXLangSourceFile, strCodeLine);
	}

	strCodeLine = _T("\r\n\r\n\r\n\r\n");
	xlang_WriteText(m_pXLangSourceFile, strCodeLine);

	//写CPP文件代码-rs_AddString
	pos = m_listXLangSourceCode.GetHeadPosition();
	while (pos != NULL)
	{
		pItem = (CXLangItem *)m_listXLangSourceCode.GetNext(pos);
		strItemID = pItem->m_strID.Mid(1);
		strCodeLine.Format(_T("rs_AddString(g_sLangID_%s,&g_sLangTxt_%s);\r\n"), strItemID, strItemID);
		xlang_WriteText(m_pXLangSourceFile, strCodeLine);
	}

	m_listXLangSourceCode.RemoveAll();

	if (m_pXLangSourceFile != NULL)
	{
		m_pXLangSourceFile->Close();
		delete m_pXLangSourceFile;
		m_pXLangSourceFile = NULL;
	}
#endif
}

#endif


void CXLanguageMngr::Release()
{
	g_nXLanguageMngrRef--;

	if (g_nXLanguageMngrRef == 0)
	{
		delete g_pXLanguageMngr;
	}
}



CString CXLanguageMngr::xlang_GetLangConfigPath(BOOL bCommon)
{
	CString strFile;
	strFile = _P_GetLanguagePath(bCommon);

	strFile += _T("LanguageConfig.xml");
	
	return strFile;
}

CString CXLanguageMngr::xlang_GetLanguagePath()
{
	CString strFile;
	strFile = _P_GetLanguagePath(g_pXLanguageMngr->m_bUseLangCommonPath);

    strFile.AppendFormat(_T("%s"), xlang_GetCurrLanguageID().GetString());

	return strFile;
}

BOOL CXLanguageMngr::xlang_IsUseXLangCommonPath()
{
	ASSERT (g_pXLanguageMngr != NULL);

	return g_pXLanguageMngr->m_bUseLangCommonPath;
}

BOOL CXLanguageMngr::OpenXLangConfigFile(BOOL bUseCommonPath)
{
	m_bUseLangCommonPath = bUseCommonPath;
	m_strLangConfigFile = xlang_GetLangConfigPath(bUseCommonPath);
#ifdef ENABLE_LANGUAGE
    return OpenXmlFile(m_strLangConfigFile, CXLanguageXmlRWKeys::g_pXmlKeys);
#else
    return true;
#endif
}

BOOL CXLanguageMngr::SaveXLangConfigFile()
{
#ifdef ENABLE_LANGUAGE
    return SaveXmlFile(m_strLangConfigFile, CXLanguageXmlRWKeys::g_pXmlKeys);
#else
    return true;
#endif
}

BOOL CXLanguageMngr::xlang_IsCurrXLanguageChinese()
{
	ASSERT (g_pXLanguageMngr != NULL);
	CString strCurrLang = g_pXLanguageMngr->m_strCurrLanguage;
	strCurrLang.MakeLower();

	if (strCurrLang.GetLength() == 0)
	{
		return TRUE;
	}

	CString strChinese = g_sLangID_Chinese;
	strChinese.MakeLower();

	if (strCurrLang == strChinese)
	{
		return TRUE;
	}

	return FALSE;
}

CXLanguageMngr::CXLanguageMngr()
{
	//初始化属性
	m_pXLanguageResoure = NULL;
	m_pCurrLanguage = NULL;

#ifdef _DEBUG
	m_pXLangSourceFile = NULL;
	m_bXLangSourceFile = FALSE;
#endif

	//初始化成员变量
	m_nDebugState = 0;
}

CXLanguageMngr::~CXLanguageMngr()
{
#ifdef _DEBUG
	WriteXLangSourceFile();
#endif

	delete m_pXLanguageResoure;
	m_pXLanguageResoure = NULL;
}

long CXLanguageMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCurrLanguageKey, oNode, m_strCurrLanguage);
	xml_GetAttibuteValue(pXmlKeys->m_strDebugStateKey, oNode, m_nDebugState);

	return 0;
}

long CXLanguageMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCurrLanguageKey, oElement, m_strCurrLanguage);
	xml_SetAttributeValue(pXmlKeys->m_strDebugStateKey, oElement, m_nDebugState);

	return 0;
}

long CXLanguageMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCurrLanguage);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCurrLanguage);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCurrLanguage);
	}
	return 0;
}

void CXLanguageMngr::InitAfterRead()
{
}

BOOL CXLanguageMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXLanguageMngr *p = (CXLanguageMngr*)pObj;

	return TRUE;
}

BOOL CXLanguageMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXLanguageMngr *p = (CXLanguageMngr*)pDest;

	return TRUE;
}

CBaseObject* CXLanguageMngr::Clone()
{
	CXLanguageMngr *p = new CXLanguageMngr();
	Copy(p);
	return p;
}

BOOL CXLanguageMngr::CanPaste(UINT nClassID)
{
	if (nClassID == LGUGCLASSID_CLANGUAGE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXLanguageMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXLanguageKey)
	{
		pNew = new CXLanguage();
	}

	return pNew;
}

CExBaseObject* CXLanguageMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == LGUGCLASSID_CLANGUAGE)
	{
		pNew = new CXLanguage();
	}

	return pNew;
}

void CXLanguageMngr::InitCurrLanguage(const CString &strFileName)
{
	if (m_strCurrLanguage.GetLength() > 0)
	{
		m_pCurrLanguage = (CXLanguage *)FindByID(m_strCurrLanguage);
	}
	
	if (m_pCurrLanguage == NULL)
	{
		m_pCurrLanguage = (CXLanguage *)GetHead();
	}

	m_pCurrLanguage->LoadLanguagegResourceFile(strFileName);

	if (xlang_IsInDebugState())
	{
		m_pXLanguageResoure->InitLangFileForDebug(strFileName);
		
		if (m_pCurrLanguage->InitResourceByLangFile(m_pXLanguageResoure, TRUE))
		{
			m_pCurrLanguage->SaveLanguagegResourceFile();
		}

		if (m_pXLanguageResoure->InsertNoExist(m_pCurrLanguage))
		{
			m_pXLanguageResoure->SaveLanguagegResourceFile();
		}
	}
	else
	{
		m_pCurrLanguage->InitResourceByLangFile(m_pXLanguageResoure, FALSE);
		m_pCurrLanguage->DeleteAll();
	}

}


	//将通用数据文件处理功能放到基类，2016-10-13
void CXLanguageMngr::InitCurrLanguage()
{
	if (m_strCurrLanguage.GetLength() > 0)
	{
		m_pCurrLanguage = (CXLanguage *)FindByID(m_strCurrLanguage);
	}
	
	if (m_pCurrLanguage == NULL)
	{
		m_pCurrLanguage = (CXLanguage *)GetHead();
	}

	m_pXLanguageResoure->InitLangRsByFile();
}

BOOL CXLanguageMngr::xlang_GetLgugStr(const CString &strID, CString &strLanguageString)
{
    ASSERT (m_pXLanguageResoure != NULL);
    BOOL bFind = m_pXLanguageResoure->xlang_GetLgugStr(strID, strLanguageString);

    if (bFind)
    {
        return bFind;
    }

    POS pos = m_listXLanguageResoure.GetHeadPosition();
    CXLanguageResourceBase *p = NULL;

    while (pos != NULL)
    {
        p = (CXLanguageResourceBase*)m_listXLanguageResoure.GetNext(pos);

        bFind = m_pXLanguageResoure->xlang_GetLgugStr(strID, strLanguageString);

        if (bFind)
        {
            break;
        }
    }

    return bFind;
}

const CString& CXLanguageMngr::xlang_GetLgugStr(const CString &strID)
{
//     //2022-3-25  lijunqing
//     CString strLanguageString;
//     xlang_GetLgugStr(strID, strLanguageString);
// 
//     return strLanguageString;
    ASSERT (m_pXLanguageResoure != NULL);
    return m_pXLanguageResoure->xlang_GetLgugStr(strID);//zhouhj 20220326 上面的写法有问题,与李工确认后,改回此写法
}


void CXLanguageMngr::xlang_AddString(const CString &strID, const CString &strLanguageString)
{
	//m_pCurrLanguage->AddString(strID, strLanguageString);
	CXLangItem *pXLangItem = NULL;
	
	pXLangItem = (CXLangItem*)m_pXLanguageResoure->FindByID(strID);

	if (pXLangItem != NULL)
	{
		return;
	}

	pXLangItem = m_pXLanguageResoure->rs_AddString2(strID, strLanguageString);

#ifdef _DEBUG
	m_listXLangSourceCode.AddTail(pXLangItem);
#endif

}

void CXLanguageMngr::xlang_Save()
{
	//m_pCurrLanguage->SaveLanguagegResourceFile();
	m_pXLanguageResoure->SaveXLangRsFile();
}


void CXLanguageMngr::xlang_SetCurrLanguageID(const CString &strID)
{
	m_strCurrLanguage = strID;
	SaveXLangConfigFile();
}

CString CXLanguageMngr::xlang_FindLandidByLangTxt(const CString &strText)
{
	POS pos = m_pXLanguageResoure->GetHeadPosition();
	CXLangItem *pXLangItem = NULL;

	while (pos != NULL)
	{
		pXLangItem = (CXLangItem *)m_pXLanguageResoure->GetNext(pos);

		if (pXLangItem->m_strSrcText == strText)
		{
			return pXLangItem->m_strID;
		}
	}

	return _T("");
}

CString CXLanguageMngr::xlang_FindLandTransByLangTxt(const CString &strText)
{
	POS pos = m_pXLanguageResoure->GetHeadPosition();
	CXLangItem *pXLangItem = NULL;

	while (pos != NULL)
	{
		pXLangItem = (CXLangItem *)m_pXLanguageResoure->GetNext(pos);

		if (pXLangItem->m_strSrcText == strText)
		{
			return pXLangItem->m_strTranslation;
		}
	}

	return _T("");
}

BOOL CXLanguageMngr::xlang_IsLandidExist(const CString &strXlangID)
{
	return (m_pXLanguageResoure->FindByID(strXlangID) != NULL);
}

const CString& xlang_GetCurrLanguageID()
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
}

void xlang_SetCurrLanguageID(const CString &strID)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_SetCurrLanguageID(strID);
}

CString xlang_GetCurrLanguagePath(const CString &strFileName)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);

	CString strFile;
	strFile = CXLanguageMngr::xlang_GetLanguagePath();
	CString strTemp;
	strTemp = strFileName.Right(4);
	strTemp.MakeLower();

	if (strTemp == _T(".xml"))
	{
        strFile.AppendFormat(_T("/%s"), strFileName.GetString());
	}
	else
	{
        strFile.AppendFormat(_T("/%s.xml"), strFileName.GetString());
	}

	return strFile;
}

BOOL xlang_IsCurrXLanguageChinese()
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_IsCurrXLanguageChinese();
}

BOOL xlang_GetLgugStr(const CString &strID, CString &strLanguageString)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_GetLgugStr(strID, strLanguageString);
}

const CString& xlang_GetLgugStr(const CString &strID)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_GetLgugStr(strID);
}

BOOL xlang_InitByLgugStr(const CString &strID, CWnd *pWnd)
{
	CString strLanguageString;
	
	if (xlang_GetLgugStr(strID, strLanguageString))
	{
		pWnd->SetWindowText(strLanguageString);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void xlang_AddString(const CString &strID, const CString &strLanguageString)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_AddString(strID, strLanguageString);
}

void xlang_Save()
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_Save();
}

BOOL xlang_IsInDebugState()
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->m_nDebugState;
}

BOOL xlang_ParseLanguageStr(CString &strLanguageString)
{
	if (strLanguageString.GetLength() > 0)
	{
		CXLanguageNameParser oParser;
		oParser.ParseLanguageString(strLanguageString);
	}
	else
	{
	}

	return TRUE;
}


void xlang_WriteResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile, CXmlRWKeys *pXmlKeys)
{
	CXLanguage oXLanguage;
	oXLanguage.xlang_Buid(pObjRcFile);

	CString strTemp = ParseFileName(strRcFile);
	oXLanguage.SaveLanguagegResourceFile(strTemp);

	CString strXLangMacroFile;
	strXLangMacroFile = _P_GetConfigPath();
    strXLangMacroFile.AppendFormat(_T("lang_%s"), strRcFile.GetString());
	pObjRcFile->SaveXmlFile(strXLangMacroFile, pXmlKeys);

// 	oXLanguage.xlang_Translate(pObjRcFile);
// 	strXLangMacroFile = _P_GetConfigPath();
// 	strXLangMacroFile.AppendFormat(_T("trans_%s"), strRcFile);
// 	pObjRcFile->SaveXmlFile(strXLangMacroFile, pXmlKeys);
}

void xlang_TranslateByResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);

	if (CXLanguageMngr::g_pXLanguageMngr == NULL)
	{
		return;
	}

	xlang_TranslateByResourceFile(pObjRcFile, strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
}

//2016-12-12  直接在原始数据对象文件中进行翻译转换，省掉进行格式转换带来的麻烦。
void xlang_TranslateByResourceFileEx(CExBaseList *pObjRcFile, const CString &strRcFile)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);

	if (CXLanguageMngr::g_pXLanguageMngr == NULL)
	{
		return;
	}

	if ( xlang_IsCurrXLanguageChinese())
	{
//2022-3-25  lijuniqng
//QT环境下，全局静态语言资源的初始化，在设置QT语言为GBK之前，因此所有中文全局语言资源都是错误的
//因此，在此种情形下，必须得重新初始化语言资源
//同时为了避免覆盖中文资源导致乱码，语言资源不做初始化保存
		if (xlang_IsInDebugState())
		{
			CXLanguage oXLanguage;
			oXLanguage.xlang_BuidEx(pObjRcFile);

#ifndef _PSX_IDE_QT_
			oXLanguage.SaveLanguagegResourceFile_Chinese(strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
#endif
		}

//#ifndef _PSX_IDE_QT_
		return;
//#endif
	}

	CXLanguage oXLanguage;
	oXLanguage.xlang_BuidEx(pObjRcFile);

	if (xlang_IsInDebugState())
	{
		xlang_TranslateByResourceFileEx(pObjRcFile, strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
	}
	else
	{
		xlang_TranslateByResourceFile(pObjRcFile, strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
	}
}
void xlang_TranslateByResourceFileEx_NoWrite(CExBaseList *pObjRcFile, const CString &strRcFile)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);

	if (CXLanguageMngr::g_pXLanguageMngr == NULL)
	{
		return;
	}

	if ( xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	CXLanguage oXLanguage;
	oXLanguage.xlang_BuidEx(pObjRcFile);

	if (xlang_IsInDebugState())
	{
		xlang_TranslateByResourceFileEx(pObjRcFile, strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
	}
	else
	{
		xlang_TranslateByResourceFile(pObjRcFile, strRcFile, CXLanguageMngr::xlang_IsUseXLangCommonPath());
	}
}

void xlang_TranslateByResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile, BOOL bUseCommon)
{
	CXLanguage oXLanguage;
	oXLanguage.m_strID = xlang_GetCurrLanguageID();
	//dingxy 20240918 打开二进制文件优化启动效率
	CString strTemp = ParseFileName(strRcFile);
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
	CString strTempB = ChangeFilePostfix(strTemp, _T("bstt"));
	CString strRcFileB;
	if (bUseCommon)
	{
		strRcFileB = CXLanguageMngr::xlang_GetLanguagePath();
		strRcFileB.AppendFormat(_T("/%s"), strTempB.GetString());
		if (IsFileExist(strRcFileB))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, strRcFileB);
			BOOL bRet = dvm_OpenBinaryFile(&oXLanguage, strRcFileB, true);
			if (bRet)
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
			}
		}
		else
		{
			if (oXLanguage.LoadLanguagegResourceFileEx(strTemp))
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
				dvm_SaveBinaryFile(&oXLanguage, strRcFileB, true);
			}
		}
	}
	else
	{
		strRcFileB = _P_GetLanguagePath();
		if (strTemp.GetLength() == 0)
		{
			strRcFileB.AppendFormat(_T("%s.bstt"), oXLanguage.m_strID.GetString());
		}
		else
			strRcFileB.AppendFormat(_T("%s\\%s"), oXLanguage.m_strID.GetString(), strTempB.GetString());
		if (IsFileExist(strRcFileB))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, strRcFileB);
			BOOL bRet = dvm_OpenBinaryFile(&oXLanguage, strRcFileB, true);
			if (bRet)
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
			}
		}
		else
		{
			if (oXLanguage.LoadLanguagegResourceFile(strTemp))
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
				dvm_SaveBinaryFile(&oXLanguage, strRcFileB, true);
			}
		}
	}
#else
	if (bUseCommon)
	{
		if (oXLanguage.LoadLanguagegResourceFileEx(strTemp))
		{
			oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
		}
	}
	else
	{
		if (oXLanguage.LoadLanguagegResourceFile(strTemp))
		{
			oXLanguage.xlang_TranslateEx(pObjRcFile, NULL);
		}
	}
#endif
}

void xlang_TranslateByResourceFileEx(CExBaseList *pObjRcFile, const CString &strRcFile, BOOL bUseCommon)
{
	CXLanguage oXLanguage;
	oXLanguage.m_strID = xlang_GetCurrLanguageID();

	CString strTemp = ParseFileName(strRcFile);
#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
	//dingxy 20240918 打开二进制文件优化启动效率
	CString strTempB = ChangeFilePostfix(strTemp, _T("bstt"));
	CString strRcFileB;
	CExBaseList listErrors;

	if (bUseCommon)
	{
		strRcFileB = CXLanguageMngr::xlang_GetLanguagePath();
		strRcFileB.AppendFormat(_T("/%s"), strTempB.GetString());
		if (IsFileExist(strRcFileB))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, strRcFileB);
			BOOL bRet = dvm_OpenBinaryFile(&oXLanguage, strRcFileB, true);
			if (bRet)
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
			}
		}
		else
		{
		//2024-09-25 zhouyangyong 多语言调试模式下，语言资源文件不存在的时候自动创建语言文件
		if (oXLanguage.LoadLanguagegResourceFileEx(strTemp) || xlang_IsInDebugState())
		{
			oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
				dvm_SaveBinaryFile(&oXLanguage, strRcFileB, true);
			}
		}
	}
	else
	{
		strRcFileB = _P_GetLanguagePath();
		if (strTemp.GetLength() == 0)
		{
			strRcFileB.AppendFormat(_T("%s.bstt"), oXLanguage.m_strID.GetString());
		}
		else
			strRcFileB.AppendFormat(_T("%s\\%s"), oXLanguage.m_strID.GetString(), strTempB.GetString());
		if (IsFileExist(strRcFileB))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, strRcFileB);
			BOOL bRet = dvm_OpenBinaryFile(&oXLanguage, strRcFileB, true);
			if (bRet)
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
			}
		}
		else
		{
			if (oXLanguage.LoadLanguagegResourceFile(strTemp))
			{
				oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
				dvm_SaveBinaryFile(&oXLanguage, strRcFileB, true);
			}
		}
	}

	if (listErrors.GetCount() > 0)
	{
		oXLanguage.Append(listErrors);
		listErrors.RemoveAll();
		oXLanguage.SaveLanguagegResourceFileEx(strTemp);
		strRcFileB = CXLanguageMngr::xlang_GetLanguagePath();
		strRcFileB.AppendFormat(_T("/%s"), strTempB.GetString());
		dvm_SaveBinaryFile(&oXLanguage, strRcFileB, true);
	}
#else
	CExBaseList listErrors;

	if (bUseCommon)
	{
		if (oXLanguage.LoadLanguagegResourceFileEx(strTemp))
		{
			oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
		}
	}
	else
	{
		if (oXLanguage.LoadLanguagegResourceFile(strTemp))
		{
			oXLanguage.xlang_TranslateEx(pObjRcFile, &listErrors);
		}
	}

	if (listErrors.GetCount() > 0)
	{
		oXLanguage.Append(listErrors);
		listErrors.RemoveAll();
		oXLanguage.SaveLanguagegResourceFileEx(strTemp);
	}
#endif
}

#ifndef _PSX_IDE_QT_
void xlang_SetFrameDocTitle(CFrameWnd *pFrameWnd, const CString &strTitle)
{
	CDocument* pDoc = pFrameWnd->GetActiveDocument();
	ASSERT(pDoc != NULL);

	if (strTitle.GetLength() == 0)
	{
		pDoc->SetTitle(g_sLangTxt_NoTitle/*_T("无标题")*/);
	}
	else
	{
		pDoc->SetTitle(strTitle);
	}
}
#endif

CString xlang_FindLandidByLangTxt(const CString &strText)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_FindLandidByLangTxt(strText);
}

CString xlang_FindLandTransByLangTxt(const CString &strText)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_FindLandTransByLangTxt(strText);
}

BOOL xlang_IsLandidExist(const CString &strXlangID)
{
	ASSERT (CXLanguageMngr::g_pXLanguageMngr != NULL);
	return CXLanguageMngr::g_pXLanguageMngr->xlang_IsLandidExist(strXlangID);
}

#ifndef _PSX_IDE_QT_
void xlang_AppendMenu(CMenu &menu, UINT nID, const CString &strXlangText)
{
	long nPos = strXlangText.Find('\n');

	if (nPos > 0)
	{
		CString strTemp = strXlangText.Left(nPos);
		menu.AppendMenu(MF_STRING, nID,  strTemp);
	}
	else
	{
		menu.AppendMenu(MF_STRING, nID,  strXlangText);
	}
}
#endif

