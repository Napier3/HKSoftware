//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.cpp  CXLanguageResourceBase


#include "stdafx.h"
#include "XLanguageResource.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "XLanguageMngr.h"
#endif

//#include "../Api/GlobalConfigApi.h"
#include "../API/GlobalConfigApi.h"
#include "../DataMngr/DataMngrGlobal.h"
#include "../API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strXLangRsBaseFile = _T("RsBase");


CXLanguageResourceBase::CXLanguageResourceBase()
{
	m_pXLangRsExe = NULL;
}


CXLanguageResourceBase::~CXLanguageResourceBase()
{
	m_oXLangRsBase.RemoveAll();
}

void CXLanguageResourceBase::InitLangFileForDebug(const CString &strModule)
{
	m_strXLangFile = _P_GetLanguagePath();
	m_strXLangFile.AppendFormat(_T("%s.xml"), strModule.GetString());
}

CXLangItem* CXLanguageResourceBase::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);
	m_oXLangRsBase.AddTail(p);

	return p;
}

CXLangItem* CXLanguageResourceBase::rs_AddString2(const CString &strID, const CString &strString)
{
	CXLangItem *p = CXLanguage::AddString(strID, strString);

	ASSERT (m_pXLangRsExe != NULL);
	m_pXLangRsExe->AddTail(p);

	return p;
}

void CXLanguageResourceBase::InitLangRsByFile()
{
	InitLangRsByFileEx(&m_oXLangRsBase, g_strXLangRsBaseFile);
	// 	CXLanguage oXLanguage;
	// 	
	// 	if (!oXLanguage.LoadLanguagegResourceFileEx(g_strXLangRsBaseFile))
	// 	{
	// 		return;
	// 	}
	// 
	// 	if (oXLanguage.InitResourceByLangFile(this, TRUE))
	// 	{
	// 		if (xlang_IsInDebugState())
	// 		{
	// 			m_oXLangRsBase.SaveLanguagegResourceFile();
	// 		}
	// 	}
}

void CXLanguageResourceBase::InitLangRsByFileEx(CXLanguage *pXLangRef, const CString &strFile)
{
#ifdef _PSX_QT_LINUX_
#ifndef NOT_USE_XLANGUAGE
	if (xlang_IsCurrXLanguageChinese())
	{//2023-2-28  lijunqing 中文环境，不做处理
		return;
	}
#endif
#endif

#ifdef NOT_USE_XLANGUAGE
#else
	if (xlang_IsInDebugState())
	{
		CString strTemp = strFile;
		strTemp += _T(".xml");
		pXLangRef->SaveLanguagegResourceFile_Chinese(strTemp, xlang_IsUseXLangCommonPath());
	}

	CXLanguage oXLanguage;
	BOOL bNeedSaveFile_sttr = FALSE;

#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
	CString strFile_bstt,strFilePath_bstt;
	strFile_bstt = ChangeFilePostfix(strFile, _T("bstt"));
	strFilePath_bstt = CXLanguageMngr::xlang_GetLanguagePath();
	strFilePath_bstt += "/";
	strFilePath_bstt +=  strFile_bstt;
	BOOL bRet = FALSE;

	if (IsFileExist(strFilePath_bstt))//dingxy 20240918 采用二进制文件方式打开保存多语言文件
	{
		bRet = dvm_OpenBinaryFile(&oXLanguage, strFilePath_bstt, true);
	}
	else
	{
		bRet = oXLanguage.LoadLanguagegResourceFileEx(strFile);
		bNeedSaveFile_sttr = TRUE;
	}

	if (!bRet)
#else
	if (!oXLanguage.LoadLanguagegResourceFileEx(strFile))
#endif
	{
		if (xlang_IsInDebugState())
		{
			pXLangRef->SaveLanguagegResourceFileEx(strFile);
			bNeedSaveFile_sttr = TRUE;
		}
	}
	else if (oXLanguage.InitResourceByLangFile(pXLangRef, TRUE))
	{
#ifdef _DEBUG
		if (xlang_IsInDebugState())
		{
			pXLangRef->SaveLanguagegResourceFileEx(strFile);
			bNeedSaveFile_sttr = TRUE;
		}
#endif
	}

#ifdef USE_ExBaseFile_AutoTrans_BinaryBsttFile
	dvm_SaveBinaryFile(pXLangRef, strFilePath_bstt, true);
#endif

#endif
}

void CXLanguageResourceBase::SaveXLangRsFile()
{
	ASSERT (m_pXLangRsExe != NULL);

	if (m_pXLangRsExe == NULL)
	{
		return;
	}

	m_pXLangRsExe->SaveLanguagegResourceFileEx(m_pXLangRsExe->m_strID);
}

void CXLanguageResourceBase::RegisterLanguageResource()
{
	rs_AddString(g_sLangID_Chinese, &g_sLangID_Chinese);
	rs_AddString(g_sLangID_English, &g_sLangID_English);

	rs_AddString(g_sLangID_File, &g_sLangTxt_File);
	rs_AddString(g_sLangID_FileNew, &g_sLangTxt_FileNew);
	rs_AddString(g_sLangID_FileNewTip, &g_sLangTxt_FileNewTip);
	rs_AddString(g_sLangID_FileOpen, &g_sLangTxt_FileOpen);
	rs_AddString(g_sLangID_Save, &g_sLangTxt_Save);
	rs_AddString(g_sLangID_SaveTip, &g_sLangTxt_SaveTip);
	rs_AddString(g_sLangID_SaveAs, &g_sLangTxt_SaveAs);
	rs_AddString(g_sLangID_SaveAsTip, &g_sLangTxt_SaveAsTip);
	rs_AddString(g_sLangID_Print, &g_sLangTxt_Print);
	rs_AddString(g_sLangID_FileClose, &g_sLangTxt_FileClose);
	rs_AddString(g_sLangID_Clipboard, &g_sLangTxt_Clipboard);
	rs_AddString(g_sLangID_Copy, &g_sLangTxt_Copy);
	rs_AddString(g_sLangID_View, &g_sLangTxt_View);
	rs_AddString(g_sLangID_SelAll, &g_sLangTxt_SelAll);
	rs_AddString(g_sLangID_PasteData, &g_sLangTxt_PasteData);
	rs_AddString(g_sLangID_Paste, &g_sLangTxt_Paste);
	rs_AddString(g_sLangID_PasteTip, &g_sLangTxt_PasteTip);
	rs_AddString(g_sLangID_Cut, &g_sLangTxt_Cut);
	rs_AddString(g_sLangID_Delete, &g_sLangTxt_Delete);
	rs_AddString(g_sLangID_OK, &g_sLangTxt_OK);
	rs_AddString(g_sLangID_Cancel, &g_sLangTxt_Cancel);
	rs_AddString(g_sLangID_Help, &g_sLangTxt_Help);
	rs_AddString(g_sLangID_HelpAbout, &g_sLangTxt_HelpAbout);
	rs_AddString(g_sLangID_AppExit, &g_sLangTxt_AppExit);
	rs_AddString(g_sLangID_AppExitTip, &g_sLangTxt_AppExitTip);
	//
	rs_AddString(g_sLangID_Name, &g_sLangTxt_Name);
	rs_AddString(g_sLangID_Index, &g_sLangTxt_Index);
	rs_AddString(g_sLangID_Type, &g_sLangTxt_Type);
	rs_AddString(g_sLangID_Open, &g_sLangTxt_Open);
	rs_AddString(g_sLangID_Location, &g_sLangTxt_Location);
	rs_AddString(g_sLangID_Path, &g_sLangTxt_Path);
	rs_AddString(g_sLangID_Size, &g_sLangTxt_Size);
	rs_AddString(g_sLangID_ModifiedTime, &g_sLangTxt_ModifiedTime);
	rs_AddString(g_sLangID_Back,&g_sLangTxt_Back);

	rs_AddString(g_sLangID_Folder, &g_sLangTxt_Folder);
	rs_AddString(g_sLangID_SureDeleItem, &g_sLangTxt_SureDeleItem);
	rs_AddString(g_sLangID_SureDelete, &g_sLangTxt_SureDelete);
	rs_AddString(g_sLangID_SureAgain, &g_sLangTxt_SureAgain);
	rs_AddString(g_sLangID_DeleteFail, &g_sLangTxt_DeleteFail);
	rs_AddString(g_sLangID_FileDeleteFail, &g_sLangTxt_FileDeleteFail);
	rs_AddString(g_sLangID_DeleteFailFold, &g_sLangTxt_DeleteFailFold);
	rs_AddString(g_sLangID_FolderDeleteFail, &g_sLangTxt_FolderDeleteFail);
	rs_AddString(g_sLangID_FoldAlrOpen, &g_sLangTxt_FoldAlrOpen);
	rs_AddString(g_sLangID_ModifiedFail, &g_sLangTxt_ModifiedFail);
	rs_AddString(g_sLangID_FileOpened, &g_sLangTxt_FileOpened);

	rs_AddString(g_sLangID_History, &g_sLangTxt_History);
	rs_AddString(g_sLangID_SerNumber, &g_sLangTxt_SerNumber);
	rs_AddString(g_sLangID_MinTime, &g_sLangTxt_MinTime);
	rs_AddString(g_sLangID_MaxTime, &g_sLangTxt_MaxTime);

	rs_AddString(g_sLangID_Filter, &g_sLangTxt_Filter);
	rs_AddString(g_sLangID_CinKeyDb, &g_sLangTxt_CinKeyDb);
	rs_AddString(g_sLangID_BaseKeyNew, &g_sLangTxt_BaseKeyNew);
	rs_AddString(g_sLangID_MultiKeyNew, &g_sLangTxt_MultiKeyNew);
	rs_AddString(g_sLangID_DeleteKey, &g_sLangTxt_DeleteKey);
	rs_AddString(g_sLangID_SelectSameKey, &g_sLangTxt_SelectSameKey);
	rs_AddString(g_sLangID_AnalyzeKey, &g_sLangTxt_AnalyzeKey);
	rs_AddString(g_sLangID_AnalyzeKeyUnsu, &g_sLangTxt_AnalyzeKeyUnsu);
	rs_AddString(g_sLangID_AnalyzeKeySu, &g_sLangTxt_AnalyzeKeySu);
	rs_AddString(g_sLangID_DeleteKeyObj, &g_sLangTxt_DeleteKeyObj);

	rs_AddString(g_sLangID_Data, &g_sLangTxt_Data);
	rs_AddString(g_sLangID_OperIns, &g_sLangTxt_OperIns);
	rs_AddString(g_sLangID_PromptMessage, &g_sLangTxt_PromptMessage);
	rs_AddString(g_sLangID_PleaseChoose, &g_sLangTxt_PleaseChoose);
	rs_AddString(g_sLangID_FileAlrExi, &g_sLangTxt_FileAlrExi);
	rs_AddString(g_sLangID_StandardFileName, &g_sLangTxt_StandardFileName);
	rs_AddString(g_sLangID_ManagSave, &g_sLangTxt_ManagSave);
	rs_AddString(g_sLangID_ManagOpen, &g_sLangTxt_ManagOpen);
	rs_AddString(g_sLangID_FileExYN, &g_sLangTxt_FileExYN);
	rs_AddString(g_sLangID_FileDupliName, &g_sLangTxt_FileDupliName);
	rs_AddString(g_sLangID_AlrOpenFail, &g_sLangTxt_AlrOpenFail);
	rs_AddString(g_sLangID_FileCoverFail, &g_sLangTxt_FileCoverFail);

	rs_AddString(g_sLangID_AddDirectory, &g_sLangTxt_AddDirectory);
	rs_AddString(g_sLangID_ImportDirectory, &g_sLangTxt_ImportDirectory);
	rs_AddString(g_sLangID_ExportDirectory, &g_sLangTxt_ExportDirectory);
	rs_AddString(g_sLangID_CopyFile, &g_sLangTxt_CopyFile);
	rs_AddString(g_sLangID_PasteFile, &g_sLangTxt_PasteFile);
	rs_AddString(g_sLangID_DeleteFile, &g_sLangTxt_DeleteFile);
	rs_AddString(g_sLangID_FileRename, &g_sLangTxt_FileRename);
	rs_AddString(g_sLangID_ImportFile, &g_sLangTxt_ImportFile);
	rs_AddString(g_sLangID_ExportFile, &g_sLangTxt_ExportFile);
	rs_AddString(g_sLangID_DeleteDirectory, &g_sLangTxt_DeleteDirectory);
	rs_AddString(g_sLangID_DirectoryRename, &g_sLangTxt_DirectoryRename);
	rs_AddString(g_sLangID_FileCover, &g_sLangTxt_FileCover);
	rs_AddString(g_sLangID_ExiSaNameFileCov, &g_sLangTxt_ExiSaNameFileCov);
	rs_AddString(g_sLangID_Message, &g_sLangTxt_Message);
	rs_AddString(g_sLangID_SureDeleFile, &g_sLangTxt_SureDeleFile);
	rs_AddString(g_sLangID_ExiSaNameFile, &g_sLangTxt_ExiSaNameFile);
	rs_AddString(g_sLangID_ExiSmNmFile2, &g_sLangTxt_ExiSmNmFile2);
	rs_AddString(g_sLangID_ChoImpFile, &g_sLangTxt_ChoImpFile);
	rs_AddString(g_sLangID_ExpFileFin, &g_sLangTxt_ExpFileFin);
	rs_AddString(g_sLangID_TargFolderExist, &g_sLangTxt_TargFolderExist);
	rs_AddString(g_sLangID_ChoFoldExDir, &g_sLangTxt_ChoFoldExDir);
	rs_AddString(g_sLangID_SureDeleFold, &g_sLangTxt_SureDeleFold);
	rs_AddString(g_sLangID_DeleFold, &g_sLangTxt_DeleFold);
	rs_AddString(g_sLangID_FoldCoverFold, &g_sLangTxt_FoldCoverFold);
	rs_AddString(g_sLangID_ConfigFileManag, &g_sLangTxt_ConfigFileManag);

	rs_AddString(g_sLangID_AtsPubFileManag, &g_sLangTxt_AtsPubFileManag);
	rs_AddString(g_sLangID_AddPubFile, &g_sLangTxt_AddPubFile);
	rs_AddString(g_sLangID_ModifyPubFile, &g_sLangTxt_ModifyPubFile);
	rs_AddString(g_sLangID_DeletePubFile, &g_sLangTxt_DeletePubFile);

	//故障、通用、结果参数
	rs_AddString(g_sLangID_FaultParameter, &g_sLangTxt_FaultParameter);
	rs_AddString(g_sLangID_GeneralParameter, &g_sLangTxt_GeneralParameter);
	rs_AddString(g_sLangID_ResultParameter, &g_sLangTxt_ResultParameter);

	rs_AddString(g_sLangID_ArbitrElement, &g_sLangTxt_ArbitrElement);
	rs_AddString(g_sLangID_SpecifiedElement, &g_sLangTxt_SpecifiedElement);
	rs_AddString(g_sLangID_SequDefinElemIn, &g_sLangTxt_SequDefinElemIn);
	rs_AddString(g_sLangID_SequDefinElemOut, &g_sLangTxt_SequDefinElemOut);
	rs_AddString(g_sLangID_ReferElements, &g_sLangTxt_ReferElements);
	rs_AddString(g_sLangID_Values, &g_sLangTxt_Values);
	rs_AddString(g_sLangID_Time, &g_sLangTxt_Time);
	rs_AddString(g_sLangID_Integer, &g_sLangTxt_Integer);
	rs_AddString(g_sLangID_FloatNumber, &g_sLangTxt_FloatNumber);
	rs_AddString(g_sLangID_CharacterString, &g_sLangTxt_CharacterString);
	rs_AddString(g_sLangID_Equal, &g_sLangTxt_Equal);
	rs_AddString(g_sLangID_LessThan, &g_sLangTxt_LessThan);
	rs_AddString(g_sLangID_LessOrEqual, &g_sLangTxt_LessOrEqual);
	rs_AddString(g_sLangID_MoreThan, &g_sLangTxt_MoreThan);
	rs_AddString(g_sLangID_MoreOrEqual, &g_sLangTxt_MoreOrEqual);
	rs_AddString(g_sLangID_NotEqual, &g_sLangTxt_NotEqual);
	rs_AddString(g_sLangID_CharStringIncl, &g_sLangTxt_CharStringIncl);
	rs_AddString(g_sLangID_CharStringNIncl, &g_sLangTxt_CharStringNIncl);
	rs_AddString(g_sLangID_NumberRange, &g_sLangTxt_NumberRange);
	rs_AddString(g_sLangID_BoundNumRange, &g_sLangTxt_BoundNumRange);
	rs_AddString(g_sLangID_DataVarAss, &g_sLangTxt_DataVarAss);
	rs_AddString(g_sLangID_PropertyID, &g_sLangTxt_PropertyID);
	rs_AddString(g_sLangID_DataType, &g_sLangTxt_DataType);
	rs_AddString(g_sLangID_FunctionalSymbol, &g_sLangTxt_FunctionalSymbol);
	rs_AddString(g_sLangID_Data2, &g_sLangTxt_Data2);
	rs_AddString(g_sLangID_ResultVariable, &g_sLangTxt_ResultVariable);
	rs_AddString(g_sLangID_GnrtFileNm, &g_sLangTxt_GnrtFileNm);
	rs_AddString(g_sLangID_OrgnFileNm, &g_sLangTxt_OrgnFileNm);
	rs_AddString(g_sLangID_TgetFileNm, &g_sLangTxt_TgetFileNm);

	rs_AddString(g_sLangID_TraProtocol, &g_sLangTxt_TraProtocol);
	rs_AddString(g_sLangID_61850Protocol, &g_sLangTxt_61850Protocol);
	rs_AddString(g_sLangID_None, &g_sLangTxt_None);
	rs_AddString(g_sLangID_OverWrite, &g_sLangTxt_OverWrite);
	rs_AddString(g_sLangID_FilePasteOprt, &g_sLangTxt_FilePasteOprt);
	rs_AddString(g_sLangID_ExiFileOvwt, &g_sLangTxt_ExiFileOvwt);
	rs_AddString(g_sLangID_SelFolder, &g_sLangTxt_SelFolder);
	rs_AddString(g_sLangID_FileName, &g_sLangTxt_FileName);
	rs_AddString(g_sLangID_NewFolder, &g_sLangTxt_NewFolder);
	rs_AddString(g_sLangID_FolderNmMdf, &g_sLangTxt_FolderNmMdf);
	//
	rs_AddString(g_sLangID_NotAuthorized, &g_sLangTxt_NotAuthorized);
	// 	rs_AddString(g_sLangID_AuthorizedUserUnit, &g_sLangTxt_AuthorizedUserUnit);
	rs_AddString(g_sLangID_NotAuthorized2, &g_sLangTxt_NotAuthorized2);
	rs_AddString(g_sLangID_Close, &g_sLangTxt_Close);
	rs_AddString(g_sLangID_CloseTip, &g_sLangTxt_CloseTip);
	rs_AddString(g_sLangID_DataSets, &g_sLangTxt_DataSets);
	rs_AddString(g_sLangID_EquipDataModel, &g_sLangTxt_EquipDataModel);
	rs_AddString(g_sLangID_DevAtrbDefin, &g_sLangTxt_DevAtrbDefin);
	rs_AddString(g_sLangID_LogicdevCPU, &g_sLangTxt_LogicdevCPU);

	rs_AddString(g_sLangID_LogicDevice, &g_sLangTxt_LogicDevice);
	rs_AddString(g_sLangID_LogicDeviceMap, &g_sLangTxt_LogicDeviceMap);
	rs_AddString(g_sLangID_DataSetsMap, &g_sLangTxt_DataSetsMap);

	rs_AddString(g_sLangID_ParaTypeGroup, &g_sLangTxt_ParaTypeGroup);
	rs_AddString(g_sLangID_NoParaTypeGroup, &g_sLangTxt_NoParaTypeGroup);
	rs_AddString(g_sLangID_DevDataFile, &g_sLangTxt_DevDataFile);
	rs_AddString(g_sLangID_RightsReserved, &g_sLangTxt_RightsReserved);
	rs_AddString(g_sLangID_LicensedTo, &g_sLangTxt_LicensedTo);
	rs_AddString(g_sLangID_DataTypeUnExist, &g_sLangTxt_DataTypeUnExist);
	rs_AddString(g_sLangID_Sizes, &g_sLangTxt_Sizes);
	rs_AddString(g_sLangID_SourceDataObject, &g_sLangTxt_SourceDataObject);
	rs_AddString(g_sLangID_MatchDataObject, &g_sLangTxt_MatchDataObject);
	rs_AddString(g_sLangID_SelMatchDataObject, &g_sLangTxt_SelMatchDataObject);

	rs_AddString(g_sLangID_USBKey, &g_sLangTxt_USBKey);
	rs_AddString(g_sLangID_USBKeyUpdate, &g_sLangTxt_USBKeyUpdate);
	rs_AddString(g_sLangID_NoUSBkey, &g_sLangTxt_NoUSBkey);
	rs_AddString(g_sLangID_SystemError, &g_sLangTxt_SystemError);
	rs_AddString(g_sLangID_SystemError2, &g_sLangTxt_SystemError2);
	rs_AddString(g_sLangID_SystemError3, &g_sLangTxt_SystemError3);
	rs_AddString(g_sLangID_SystemError4, &g_sLangTxt_SystemError4);
	// 	rs_AddString(g_sLangID_RightReservedS, &g_sLangTxt_RightReservedS);
	rs_AddString(g_sLangID_SystemDevelop, &g_sLangTxt_SystemDevelop);
	rs_AddString(g_sLangID_UserName, &g_sLangTxt_UserName);
	rs_AddString(g_sLangID_ClientUnit, &g_sLangTxt_ClientUnit);
	rs_AddString(g_sLangID_ServerLicense, &g_sLangTxt_ServerLicense);
	rs_AddString(g_sLangID_ServerLicense2, &g_sLangTxt_ServerLicense2);
	rs_AddString(g_sLangID_LicenseCommun, &g_sLangTxt_LicenseCommun);
	rs_AddString(g_sLangID_TestInstSel, &g_sLangTxt_TestInstSel);
	rs_AddString(g_sLangID_AddScriptFail, &g_sLangTxt_AddScriptFail);
	rs_AddString(g_sLangID_TestFctnUnExist, &g_sLangTxt_TestFctnUnExist);
	rs_AddString(g_sLangID_IEC61850SetFile, &g_sLangTxt_IEC61850SetFile);
	rs_AddString(g_sLangID_ComtradeFile, &g_sLangTxt_ComtradeFile);
	rs_AddString(g_sLangID_TestFctnFile, &g_sLangTxt_TestFctnFile);
	rs_AddString(g_sLangID_CommunStraFile, &g_sLangTxt_CommunStraFile);
	rs_AddString(g_sLangID_Number2, &g_sLangTxt_Number2);
	rs_AddString(g_sLangID_ALreadyExist, &g_sLangTxt_ALreadyExist);
	rs_AddString(g_sLangID_MdtInsert, &g_sLangTxt_MdtInsert);
	rs_AddString(g_sLangID_UpMove, &g_sLangTxt_UpMove);
	rs_AddString(g_sLangID_DownMove, &g_sLangTxt_DownMove);
	rs_AddString(g_sLangID_Unit, &g_sLangTxt_Unit);
	rs_AddString(g_sLangID_MinValue, &g_sLangTxt_MinValue);
	rs_AddString(g_sLangID_MaxValue, &g_sLangTxt_MaxValue);
	rs_AddString(g_sLangID_Step, &g_sLangTxt_Step);
	rs_AddString(g_sLangID_Nonstandard, &g_sLangTxt_Nonstandard);
	//rs_AddString(g_sLangID_StatePower, &g_sLangTxt_StatePower);
	rs_AddString(g_sLangID_Aphase, &g_sLangTxt_Aphase);
	rs_AddString(g_sLangID_Bphase, &g_sLangTxt_Bphase);
	rs_AddString(g_sLangID_Cphase, &g_sLangTxt_Cphase);
	rs_AddString(g_sLangID_ABphase, &g_sLangTxt_ABphase);
	rs_AddString(g_sLangID_BCphase, &g_sLangTxt_BCphase);
	rs_AddString(g_sLangID_CAphase, &g_sLangTxt_CAphase);
	rs_AddString(g_sLangID_Application, &g_sLangTxt_Application);
	rs_AddString(g_sLangID_FixedValueRegion, &g_sLangTxt_FixedValueRegion);
	rs_AddString(g_sLangID_Modify, &g_sLangTxt_Modify);
	rs_AddString(g_sLangID_ItemPrtcFile, &g_sLangTxt_ItemPrtcFile);
	rs_AddString(g_sLangID_SelDevDaModFile, &g_sLangTxt_SelDevDaModFile);
	rs_AddString(g_sLangID_TemDataFileChange, &g_sLangTxt_TemDataFileChange);
	rs_AddString(g_sLangID_ConServerFail, &g_sLangTxt_ConServerFail);
	rs_AddString(g_sLangID_ConServerSucc, &g_sLangTxt_ConServerSucc);
	rs_AddString(g_sLangID_UserUnExist, &g_sLangTxt_UserUnExist);
	rs_AddString(g_sLangID_PasswordIncorrect, &g_sLangTxt_PasswordIncorrect);
	rs_AddString(g_sLangID_LoginError, &g_sLangTxt_LoginError);
	rs_AddString(g_sLangID_StopTest, &g_sLangTxt_StopTest);
	rs_AddString(g_sLangID_StartTest, &g_sLangTxt_StartTest);
	rs_AddString(g_sLangID_ExportReport, &g_sLangTxt_ExportReport);
	rs_AddString(g_sLangID_ExportReportBatch, &g_sLangTxt_ExportReportBatch);
	rs_AddString(g_sLangID_StatusBar, &g_sLangTxt_StatusBar);
	rs_AddString(g_sLangID_TestStop2, &g_sLangTxt_TestStop2);
	rs_AddString(g_sLangID_DataOpreation, &g_sLangTxt_DataOpreation);

	rs_AddString(g_sLangID_OpenTip, &g_sLangTxt_OpenTip);
	rs_AddString(g_sLangID_ModelTestTip, &g_sLangTxt_ModelTestTip);
	rs_AddString(g_sLangID_DevModelTestTip, &g_sLangTxt_DevModelTestTip);
	rs_AddString(g_sLangID_StopTestTip, &g_sLangTxt_StopTestTip);
	rs_AddString(g_sLangID_ExportReportTip, &g_sLangTxt_ExportReportTip);
	rs_AddString(g_sLangID_SaveFileTip, &g_sLangTxt_SaveFileTip);
	rs_AddString(g_sLangID_OutputBarTip, &g_sLangTxt_OutputBarTip);
	rs_AddString(g_sLangID_StatusBarTip, &g_sLangTxt_StatusBarTip);
	rs_AddString(g_sLangID_CompareDataTip, &g_sLangTxt_CompareDataTip);
	rs_AddString(g_sLangID_AboutTip, &g_sLangTxt_AboutTip);
	rs_AddString(g_sLangID_TestMain, &g_sLangTxt_TestMain);
	rs_AddString(g_sLangID_ModelTest, &g_sLangTxt_ModelTest);
	rs_AddString(g_sLangID_ProtocolTest, &g_sLangTxt_ProtocolTest);
	rs_AddString(g_sLangID_ModelFileTest, &g_sLangTxt_ModelFileTest);
	rs_AddString(g_sLangID_DevModelTest, &g_sLangTxt_DevModelTest);
	rs_AddString(g_sLangID_ResultOpera, &g_sLangTxt_ResultOpera);
	rs_AddString(g_sLangID_SaveFile, &g_sLangTxt_SaveFile);
	rs_AddString(g_sLangID_OutputBar, &g_sLangTxt_OutputBar);
	rs_AddString(g_sLangID_CompareData, &g_sLangTxt_CompareData);
	rs_AddString(g_sLangID_Browse, &g_sLangTxt_Browse);
	rs_AddString(g_sLangID_Home, &g_sLangTxt_Home);
	rs_AddString(g_sLangID_CreatDataMap, &g_sLangTxt_CreatDataMap);
	rs_AddString(g_sLangID_DeleteDataMap, &g_sLangTxt_DeleteDataMap);
	rs_AddString(g_sLangID_CreatDataMap2, &g_sLangTxt_CreatDataMap2);
	rs_AddString(g_sLangID_DeleteDataMap2, &g_sLangTxt_DeleteDataMap2);
	rs_AddString(g_sLangID_SelStdDataFile, &g_sLangTxt_SelStdDataFile);
	rs_AddString(g_sLangID_DataSetNoOnly, &g_sLangTxt_DataSetNoOnly);
	rs_AddString(g_sLangID_User, &g_sLangTxt_User);
	rs_AddString(g_sLangID_Module, &g_sLangTxt_Module);
	rs_AddString(g_sLangID_RemotePort, &g_sLangTxt_RemotePort);
	rs_AddString(g_sLangID_LocalPort, &g_sLangTxt_LocalPort);
	rs_AddString(g_sLangID_State, &g_sLangTxt_State);
	rs_AddString(g_sLangID_ServerWorkPath, &g_sLangTxt_ServerWorkPath);

	rs_AddString(g_sLangID_New, &g_sLangTxt_New);
	rs_AddString(g_sLangID_TemNew, &g_sLangTxt_TemNew);
	rs_AddString(g_sLangID_NewTip, &g_sLangTxt_NewTip);
	rs_AddString(g_sLangID_OpenTips, &g_sLangTxt_OpenTips);
	rs_AddString(g_sLangID_SaveTips, &g_sLangTxt_SaveTips);
	rs_AddString(g_sLangID_SaveAsTips, &g_sLangTxt_SaveAsTips);
	rs_AddString(g_sLangID_RecentFile, &g_sLangTxt_RecentFile);

	rs_AddString(g_sLangID_TemplateDef, &g_sLangTxt_TemplateDef);
	rs_AddString(g_sLangID_TemplateProperty, &g_sLangTxt_TemplateProperty);
	rs_AddString(g_sLangID_CommDef, &g_sLangTxt_CommDef);
	rs_AddString(g_sLangID_InitDef, &g_sLangTxt_InitDef);
	rs_AddString(g_sLangID_NoDataNotInsert, &g_sLangTxt_NoDataNotInsert);
	rs_AddString(g_sLangID_Exist, &g_sLangTxt_Exist);
	rs_AddString(g_sLangID_Attention, &g_sLangTxt_Attention);
	rs_AddString(g_sLangID_KeySameId, &g_sLangTxt_KeySameId);

	rs_AddString(g_sLangID_InitiaErrors, &g_sLangTxt_InitiaErrors);
	rs_AddString(g_sLangID_OtherStart, &g_sLangTxt_OtherStart);
	rs_AddString(g_sLangID_OtherClose, &g_sLangTxt_OtherClose);
	rs_AddString(g_sLangID_ConnectRefuse, &g_sLangTxt_ConnectRefuse);
	rs_AddString(g_sLangID_AttemptOperate, &g_sLangTxt_AttemptOperate);
	rs_AddString(g_sLangID_SpecificUse, &g_sLangTxt_SpecificUse);
	rs_AddString(g_sLangID_ConnectionClosed, &g_sLangTxt_ConnectionClosed);
	rs_AddString(g_sLangID_GenericError, &g_sLangTxt_GenericError);
	rs_AddString(g_sLangID_Add, &g_sLangTxt_Add);
	rs_AddString(g_sLangID_NoDataChangeMsg, &g_sLangTxt_NoDataChangeMsg);
	rs_AddString(g_sLangID_FileNameInclude, &g_sLangTxt_FileNameInclude);

	rs_AddString(g_sLangID_Add3, &g_sLangTxt_Add3);
	rs_AddString(g_sLangID_Select, &g_sLangTxt_Select);
	rs_AddString(g_sLangID_Value, &g_sLangTxt_Value);
	rs_AddString(g_sLangID_DefaultValue, &g_sLangTxt_DefaultValue);

	rs_AddString(g_sLangID_PrtcTempFile, &g_sLangTxt_PrtcTempFile);
	rs_AddString(g_sLangID_ModelFile, &g_sLangTxt_ModelFile);
	rs_AddString(g_sLangID_PrtcProjectFile, &g_sLangTxt_PrtcProjectFile);
	rs_AddString(g_sLangID_PrtcTempFileMagn, &g_sLangTxt_PrtcTempFileMagn);
	rs_AddString(g_sLangID_Version, &g_sLangTxt_Version);

	rs_AddString(g_sLangID_TimeLimit, &g_sLangTxt_TimeLimit);
	rs_AddString(g_sLangID_ComparaObject, &g_sLangTxt_ComparaObject);
	rs_AddString(g_sLangID_StandardValue, &g_sLangTxt_StandardValue);
	rs_AddString(g_sLangID_TureValue, &g_sLangTxt_TureValue);
	rs_AddString(g_sLangID_Property, &g_sLangTxt_Property);
	rs_AddString(g_sLangID_UnStallWord, &g_sLangTxt_UnStallWord);
	rs_AddString(g_sLangID_Title, &g_sLangTxt_Title);
	rs_AddString(g_sLangID_ReName, &g_sLangTxt_ReName);
	rs_AddString(g_sLangID_UserUnits, &g_sLangTxt_UserUnits);
	rs_AddString(g_sLangID_User2, &g_sLangTxt_User2);
	rs_AddString(g_sLangID_Develop, &g_sLangTxt_Develop);
	rs_AddString(g_sLangID_Variable, &g_sLangTxt_Variable);
	rs_AddString(g_sLangID_DeleteFloder, &g_sLangTxt_DeleteFloder);
	rs_AddString(g_sLangID_SureDelFoldItem, &g_sLangTxt_SureDelFoldItem);
	rs_AddString(g_sLangID_Size2, &g_sLangTxt_Size2);
	rs_AddString(g_sLangID_ModiftyFileNameFail, &g_sLangTxt_ModiftyFileNameFail);

	//文件管理
	rs_AddString(g_sLangID_SCDFiles, &g_sLangTxt_SCDFiles);
	rs_AddString(g_sLangID_RecordFiles, &g_sLangTxt_RecordFiles);
	rs_AddString(g_sLangID_TemplateFiles, &g_sLangTxt_TemplateFiles);
	rs_AddString(g_sLangID_WorkspaceFiles, &g_sLangTxt_WorkspaceFiles);
	rs_AddString(g_sLangID_IEC61850SetFiles, &g_sLangTxt_IEC61850SetFiles);
	rs_AddString(g_sLangID_PcapFiles, &g_sLangTxt_PcapFiles);
	rs_AddString(g_sLangID_PrintScreen, &g_sLangTxt_PrintScreen);
	rs_AddString(g_sLangID_Others, &g_sLangTxt_Others);
	rs_AddString(g_sLangID_SavePcapFiles, &g_sLangTxt_SavePcapFiles);
	rs_AddString(g_sLangID_SavePrintScreen, &g_sLangTxt_SavePrintScreen);
	rs_AddString(g_sLangID_OtherTypeFiles, &g_sLangTxt_OtherTypeFiles);

	rs_AddString(g_sLangID_Output, &g_sLangTxt_Output);
	rs_AddString(g_sLangID_ConfirmDel, &g_sLangTxt_ConfirmDel);
	rs_AddString(g_sLangID_NoSave, &g_sLangTxt_NoSave);

	rs_AddString(g_sLangID_Increase, &g_sLangTxt_Increase);
	rs_AddString(g_sLangID_Decrease, &g_sLangTxt_Decrease);
	rs_AddString(g_sLangID_Export, &g_sLangTxt_Export);
	rs_AddString(g_sLangID_Import, &g_sLangTxt_Import);
	rs_AddString(g_sLangID_ClcltFmla, &g_sLangTxt_ClcltFmla);
	rs_AddString(g_sLangID_GuideWizardFile, &g_sLangTxt_GuideWizardFile);

	rs_AddString(g_sLangID_IecConfigFile, &g_sLangTxt_IecConfigFile);
	rs_AddString(g_sLangID_DvIecConfigFile, &g_sLangTxt_DvIecConfigFile);
	rs_AddString(g_sLangID_DvIecConfigFileMngr, &g_sLangTxt_DvIecConfigFileMngr);

	rs_AddString(g_sLangID_NoTitle, &g_sLangTxt_NoTitle);
	rs_AddString(g_sLangID_FileNotExist, &g_sLangTxt_FileNotExist);

	rs_AddString(g_sLangID_Login, &g_sLangTxt_Login);
	rs_AddString(g_sLangID_YunDownFileFaild, &g_sLangTxt_YunDownFileFaild);
	rs_AddString(g_sLangID_UpLoad, &g_sLangTxt_UpLoad);
	rs_AddString(g_sLangID_DownLoad, &g_sLangTxt_DownLoad);

	rs_AddString(g_sLangID_TestItemParEdit, &g_sLangTxt_TestItemParEdit);
	rs_AddString(g_sLangID_ParaName, &g_sLangTxt_ParaName);
	rs_AddString(g_sLangID_ParaValue, &g_sLangTxt_ParaValue);
	rs_AddString(g_sLangID_GlobalData, &g_sLangTxt_GlobalData);
	rs_AddString(g_sLangID_TestAppDef, &g_sLangTxt_TestAppDef);
	rs_AddString(g_sLangID_RepeatResultInfo, &g_sLangTxt_RepeatResultInfo);
	rs_AddString(g_sLangID_Clear, &g_sLangTxt_Clear);
	rs_AddString(g_sLangID_SyntaxCheck, &g_sLangTxt_SyntaxCheck);
	rs_AddString(g_sLangID_SyntaxCheckTips, &g_sLangTxt_SyntaxCheckTips);

	rs_AddString(g_sLangID_OutputWnd, &g_sLangTxt_OutputWnd);
	rs_AddString(g_sLangID_DataSet, &g_sLangTxt_DataSet);

	rs_AddString(g_sLangID_Quit, &g_sLangTxt_Quit);
	rs_AddString(g_sLangID_QuitTip, &g_sLangTxt_QuitTip);

    //shaolei 2024-1-4
    rs_AddString(g_sLangID_Voltage, &g_sLangTxt_Voltage);
    rs_AddString(g_sLangID_Current, &g_sLangTxt_Current);
    rs_AddString(g_sLangID_ActivePower, &g_sLangTxt_ActivePower);
    rs_AddString(g_sLangID_ReactivePower, &g_sLangTxt_ReactivePower);
    rs_AddString(g_sLangID_Frequency, &g_sLangTxt_Frequency);
    rs_AddString(g_sLangID_PowerFactor, &g_sLangTxt_PowerFactor);

	rs_AddString(g_sLangID_Native_StartOutput, &g_sLangTxt_Native_StartOutput);
	//实际在CXLanguageResourceAtsBase中定义故删除  zhouhj 2024.5.25
 //   rs_AddString(g_sLangID_TestComplete, &g_sLangTxt_TestComplete);
    rs_AddString(g_sLangID_Native_TestAnomalies, &g_sLangTxt_Native_TestAnomalies);
    rs_AddString(g_sLangID_Native_RelieveTestAnomalies, &g_sLangTxt_Native_RelieveTestAnomalies);
    rs_AddString(g_sLangID_Native_StateSwitch, &g_sLangTxt_Native_StateSwitch);
    rs_AddString(g_sLangID_Native_SupDCSwitch, &g_sLangTxt_Native_SupDCSwitch);
    rs_AddString(g_sLangID_Native_BinDisPlace, &g_sLangTxt_Native_BinDisPlace);
    rs_AddString(g_sLangID_Native_BoutDisPlace, &g_sLangTxt_Native_BoutDisPlace);
    rs_AddString(g_sLangID_Native_ParaUpdata, &g_sLangTxt_Native_ParaUpdata);

	rs_AddString(g_sLangID_Native_Port, &g_sLangTxt_Native_Port);

	rs_AddString(g_sLangID_TestInstrumentConfig, &g_sLangTxt_TestInstrumentConfig);
	rs_AddString(g_sLangID_ScanLANTestInstrument, &g_sLangTxt_ScanLANTestInstrument);
	rs_AddString(g_sLangID_DirectConfigRemoteInstrument, &g_sLangTxt_DirectConfigRemoteInstrument);
	rs_AddString(g_sLangID_ScanRemoteTestInstrument, &g_sLangTxt_ScanRemoteTestInstrument);
	rs_AddString(g_sLangID_Setup, &g_sLangTxt_Setup);
	rs_AddString(g_sLangID_Upgrade, &g_sLangTxt_Upgrade);
	rs_AddString(g_sLangID_EnablePUDA, &g_sLangTxt_EnablePUDA);
	rs_AddString(g_sLangID_EnableTestSvr, &g_sLangTxt_EnableTestSvr);
	rs_AddString(g_sLangID_TestInstrumentModel, &g_sLangTxt_TestInstrumentModel);
	rs_AddString(g_sLangID_TestInstrumentID, &g_sLangTxt_TestInstrumentID);
	rs_AddString(g_sLangID_CloudIP, &g_sLangTxt_CloudIP);
	rs_AddString(g_sLangID_CloudPort, &g_sLangTxt_CloudPort);
	rs_AddString(g_sLangID_TestInstrumentSerialNumber, &g_sLangTxt_TestInstrumentSerialNumber);
	rs_AddString(g_sLangID_Password, &g_sLangTxt_Password);
	rs_AddString(g_sLangID_Unit2, &g_sLangTxt_Unit2);
	rs_AddString(g_sLangID_Bind, &g_sLangTxt_Bind);
	rs_AddString(g_sLangID_Query, &g_sLangTxt_Query);
	rs_AddString(g_sLangID_TestInstrumentConnectionError, &g_sLangTxt_TestInstrumentConnectionError);
	rs_AddString(g_sLangID_CloudServerConnectionError, &g_sLangTxt_CloudServerConnectionError);
	rs_AddString(g_sLangID_IPIsEmpty, &g_sLangTxt_IPIsEmpty);
	rs_AddString(g_sLangID_ConnectionTestInstrumentFailed, &g_sLangTxt_ConnectionTestInstrumentFailed);
	rs_AddString(g_sLangID_MulticastInitSuccess, &g_sLangTxt_MulticastInitSuccess);
	rs_AddString(g_sLangID_MulticastInitFailed, &g_sLangTxt_MulticastInitFailed);
	rs_AddString(g_sLangID_MulticastInitBindSuccess, &g_sLangTxt_MulticastInitBindSuccess);
	rs_AddString(g_sLangID_Disconnection, &g_sLangTxt_Disconnection);
	rs_AddString(g_sLangID_CloudConnectionFailed, &g_sLangTxt_CloudConnectionFailed);
	rs_AddString(g_sLangID_TestInstrumentUserInfoError, &g_sLangTxt_TestInstrumentUserInfoError);
	rs_AddString(g_sLangID_Connect, &g_sLangTxt_Connect);
	rs_AddString(g_sLangID_StopScanning, &g_sLangTxt_StopScanning);
	rs_AddString(g_sLangID_Scanning, &g_sLangTxt_Scanning);
	rs_AddString(g_sLangID_NanjingEnergyCloud, &g_sLangTxt_NanjingEnergyCloud);
	rs_AddString(g_sLangID_TestInstrumentConfigFileNotFound, &g_sLangTxt_TestInstrumentConfigFileNotFound);
	rs_AddString(g_sLangID_OAClientInitFail, &g_sLangTxt_OAClientInitFail);

	rs_AddString(g_sLangID_ResultBar, &g_sLangTxt_ResultBar);
	rs_AddString(g_sLangID_StatusLight, &g_sLangTxt_StatusLight);
	rs_AddString(g_sLangID_WinwordProcessWarning, &g_sLangTxt_WinwordProcessWarning);
	rs_AddString(g_sLangID_CloseProcessWarning, &g_sLangTxt_CloseProcessWarning);


}

long g_nCXLanguageResourceBase_InitLangTxt = 0;

void CXLanguageResourceBase::InitLangTxt()
{
	if (g_nCXLanguageResourceBase_InitLangTxt > 0)
	{
		//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("++++++++InitLangTxt+++512"));
		return;
	}

	//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("++++++++InitLangTxt+++516"));
	g_nCXLanguageResourceBase_InitLangTxt = 1;

	g_sLangID_Chinese       = _T("Chinese");
	g_sLangID_English       = _T("English");

	g_sLangID_File          = _T("sFile");
	g_sLangTxt_File         = _T("文件");
	g_sLangID_FileNew       = _T("sFileNew");
	g_sLangTxt_FileNew      = _T("新建文件");
	g_sLangID_FileNewTip    = _T("sFileNewTip");
	g_sLangTxt_FileNewTip   = _T("新建文件\n新建");
	g_sLangID_FileOpen      = _T("sFileOpen");
	g_sLangTxt_FileOpen     = _T("打开文件");
	g_sLangID_Save          = _T("sSave");
	g_sLangTxt_Save         = _T("保存");
	g_sLangID_SaveTip          = _T("sSaveTip");
	g_sLangTxt_SaveTip         = _T("保存模型文件\n保存");
	g_sLangID_SaveAs        = _T("sSaveAs");
	g_sLangTxt_SaveAs       = _T("另存为");
	g_sLangID_SaveAsTip        = _T("sSaveAsTip");
	g_sLangTxt_SaveAsTip       = _T("模型文件另存为\n另存为");
	g_sLangID_Print         = _T("sPrint");
	g_sLangTxt_Print        = _T("打印");
	g_sLangID_FileClose     = _T("sFileClose");
	g_sLangTxt_FileClose    = _T("关闭文件");
	g_sLangID_Copy          = _T("sCopy");
	g_sLangTxt_Copy         = _T("拷贝");
	g_sLangID_View          = _T("sView");
	g_sLangTxt_View         = _T("视图");
	g_sLangID_SelAll        = _T("sSelAll");
	g_sLangTxt_SelAll       = _T("全选");
	g_sLangID_Clipboard     = _T("sClipboard");
	g_sLangTxt_Clipboard    = _T("剪切板");
	g_sLangID_PasteData         = _T("sPasteData");
	g_sLangTxt_PasteData        = _T("粘贴数据");
	g_sLangID_Paste         = _T("sPaste");
	g_sLangTxt_Paste        = _T("粘贴");
	g_sLangID_PasteTip      = _T("sPasteTip");
	g_sLangTxt_PasteTip     = _T("插入剪贴板内容\n粘贴");
	g_sLangID_Cut           = _T("sCut");
	g_sLangTxt_Cut          = _T("剪切");
	g_sLangID_Delete        = _T("sDelete");
	g_sLangTxt_Delete       = _T("删除");
	g_sLangID_OK            = _T("sOK");
	g_sLangTxt_OK           = _T("确定");
	g_sLangID_Cancel        = _T("sCancel");
	g_sLangTxt_Cancel       = _T("取消");
	g_sLangID_AppExit       = _T("sAppExit");
	g_sLangTxt_AppExit      = _T("退出");
	g_sLangID_AppExitTip    = _T("sAppExitTip");
	g_sLangTxt_AppExitTip   = _T("退出应用程序；提示保存文档\n退出");
	g_sLangID_Help          = _T("sHelp");
	g_sLangTxt_Help         = _T("帮助");
	g_sLangID_HelpAbout     = _T("sHelpAbout");
	g_sLangTxt_HelpAbout    = _T("关于");
	g_sLangID_Back        = _T("sBack");
	g_sLangTxt_Back       = _T("返回");
	//
	g_sLangID_Name       = _T("sName");
	g_sLangTxt_Name      = _T("名称");
	g_sLangID_Index      = _T("sIndex");
	g_sLangTxt_Index     = _T("编号");
	g_sLangID_Type       = _T("sType");
	g_sLangTxt_Type      = _T("类型");
	g_sLangID_History    = _T("sHistory");
	g_sLangTxt_History   = _T("历史");
	g_sLangID_Open       = _T("sOpen");
	g_sLangTxt_Open      = _T("打开");
	g_sLangID_Location   = _T("sLocation");
	g_sLangTxt_Location  = _T("定位");
	g_sLangID_Path       = _T("sPath");
	g_sLangTxt_Path      = _T("路径");
	g_sLangID_Size       = _T("sSize");
	g_sLangTxt_Size      = _T("大小(KB)");
	g_sLangID_ModifiedTime       = _T("sModifiedTime");
	g_sLangTxt_ModifiedTime      = _T("修改时间");

	g_sLangID_Folder               = _T("sFolder");
	g_sLangTxt_Folder              = _T("文件夹");
	g_sLangID_SureDeleItem         = _T("sSureDeleItem");
	g_sLangTxt_SureDeleItem        = _T("确定要删除这 %d 个项目吗?");
	g_sLangID_SureDelete           = _T("sSureDelete");
	g_sLangTxt_SureDelete          = _T("删除确认");
	g_sLangID_SureAgain            = _T("sSureAgain");
	g_sLangTxt_SureAgain           = _T("删除后将无法恢复，请再次确认");
	g_sLangID_DeleteFail           = _T("sDeleteFail");
	g_sLangTxt_DeleteFail          = _T("文件正在被使用，删除失败");
	g_sLangID_FileDeleteFail       = _T("sFileDeleteFail");
	g_sLangTxt_FileDeleteFail      = _T("删除文件失败");
	g_sLangID_DeleteFailFold       = _T("sDeleteFailFold");
	g_sLangTxt_DeleteFailFold      = _T("文件夹中包含正在被使用的文件，删除失败");
	g_sLangID_FolderDeleteFail     = _T("sFolderDeleteFail");
	g_sLangTxt_FolderDeleteFail    = _T("删除文件夹失败");
	g_sLangID_FoldAlrOpen          = _T("sFoldAlrOpen");
	g_sLangTxt_FoldAlrOpen         = _T("该文件夹中已被打开的文件");
	g_sLangID_ModifiedFail         = _T("sModifiedFail");
	g_sLangTxt_ModifiedFail        = _T("修改文件夹名称失败");
	g_sLangID_FileOpened           = _T("sFileOpened");
	g_sLangTxt_FileOpened          = _T("该文件已被打开");


	g_sLangID_SerNumber       = _T("sSerNumber");
	g_sLangTxt_SerNumber      = _T("序号");
	g_sLangID_MinTime         = _T("sMinTime");
	g_sLangTxt_MinTime        = _T("最小次数");
	g_sLangID_MaxTime         = _T("sMaxTime");
	g_sLangTxt_MaxTime        = _T("最大次数");

	g_sLangID_Filter          = _T("sFilter");
	g_sLangTxt_Filter         = _T("过滤");
	g_sLangID_CinKeyDb        = _T("sCinKeyDb");
	g_sLangTxt_CinKeyDb       = _T("合并文件");
	g_sLangID_BaseKeyNew      = _T("sBaseKeyNew");
	g_sLangTxt_BaseKeyNew     = _T("新建关键字");
	g_sLangID_MultiKeyNew     = _T("sMultiKeyNew");
	g_sLangTxt_MultiKeyNew    = _T("新建复合关键字");
	g_sLangID_DeleteKey       = _T("sDeleteKey");
	g_sLangTxt_DeleteKey      = _T("删除关键字");
	g_sLangID_SelectSameKey   = _T("sSelectSameKey");
	g_sLangTxt_SelectSameKey  = _T("查找无效关键字");
	g_sLangID_AnalyzeKey      = _T("sAnalyzeKey");
	g_sLangTxt_AnalyzeKey     = _T("关键字分析");
	g_sLangID_AnalyzeKeyUnsu  = _T("sAnalyzeKeyUnsu");
	g_sLangTxt_AnalyzeKeyUnsu = _T("没有匹配成功关键字");
	g_sLangID_AnalyzeKeySu    = _T("sAnalyzeKeySu");
	g_sLangTxt_AnalyzeKeySu   = _T("匹配成功的关键字");
	g_sLangID_DeleteKeyObj    = _T("sDeleteKeyObj");
	g_sLangTxt_DeleteKeyObj   = _T("请选择要删除的对象！");

	g_sLangID_Data               = _T("sData");
	g_sLangTxt_Data              = _T("数据");
	g_sLangID_OperIns            = _T("sOperIns");
	g_sLangTxt_OperIns           = _T("作业指导书");
	g_sLangID_PromptMessage      = _T("sPromptMessage");
	g_sLangTxt_PromptMessage     = _T("提示信息");
	g_sLangID_PleaseChoose       = _T("sPleaseChoose");
	g_sLangTxt_PleaseChoose      = _T("请在 %s 下选择%s");
	g_sLangID_FileAlrExi         = _T("sFileAlrExi");
	g_sLangTxt_FileAlrExi        = _T("文件 %s 已经存在");
	g_sLangID_StandardFileName   = _T("sStandardFileName");
	g_sLangTxt_StandardFileName  = _T("标准文件名");
	g_sLangID_ManagSave          = _T("sManagSave");
	g_sLangTxt_ManagSave         = _T("%s 管理---保存");
	g_sLangID_ManagOpen          = _T("sManagOpen");
	g_sLangTxt_ManagOpen         = _T("%s 管理---打开");
	g_sLangID_FileExYN           = _T("sFileExYN");
	g_sLangTxt_FileExYN          = _T("%s 文件已经存在，是否覆盖?");
	g_sLangID_FileDupliName      = _T("sFileDupliName");
	g_sLangTxt_FileDupliName     = _T("文件重名");
	g_sLangID_AlrOpenFail        = _T("sAlrOpenFail");
	g_sLangTxt_AlrOpenFail       = _T("%s 已经被打开，文件覆盖失败");
	g_sLangID_FileCoverFail      = _T("sFileCoverFail");
	g_sLangTxt_FileCoverFail     = _T("文件覆盖失败");

	g_sLangID_AddDirectory               = _T("sAddDirectory");
	g_sLangTxt_AddDirectory              = _T("添加目录");
	g_sLangID_ImportDirectory            = _T("sImportDirectory");
	g_sLangTxt_ImportDirectory           = _T("导入目录");
	g_sLangID_ExportDirectory            = _T("sExportDirectory");
	g_sLangTxt_ExportDirectory           = _T("导出目录");
	g_sLangID_CopyFile                   = _T("sCopyFile");
	g_sLangTxt_CopyFile                  = _T("拷贝文件");
	g_sLangID_PasteFile                  = _T("sPasteFile");
	g_sLangTxt_PasteFile                 = _T("粘贴文件");
	g_sLangID_DeleteFile                 = _T("sDeleteFile");
	g_sLangTxt_DeleteFile                = _T("删除文件");
	g_sLangID_FileRename                 = _T("sFileRename");
	g_sLangTxt_FileRename                = _T("修改文件名称");
	g_sLangID_ImportFile                 = _T("sImportFile");
	g_sLangTxt_ImportFile                = _T("导入文件");
	g_sLangID_ExportFile                 = _T("sExportFile");
	g_sLangTxt_ExportFile                = _T("导出文件");
	g_sLangID_DeleteDirectory            = _T("sDeleteDirectory");
	g_sLangTxt_DeleteDirectory           = _T("删除目录");
	g_sLangID_DirectoryRename            = _T("sDirectoryRename");
	g_sLangTxt_DirectoryRename           = _T("修改目录名称");
	g_sLangID_FileCover                  = _T("sFileCover");
	g_sLangTxt_FileCover                 = _T("覆盖文件");
	g_sLangID_ExiSaNameFileCov           = _T("sExiSaNameFileCov");
	g_sLangTxt_ExiSaNameFileCov          = _T("存在同名称的文件【%s】,覆盖吗？");
	g_sLangID_ExiFileOvwt                = _T("sExiFileOvwt");
	g_sLangTxt_ExiFileOvwt               = _T("文件【%s】已经存在,覆盖吗？");
	g_sLangID_Message                    = _T("sMessage");
	g_sLangTxt_Message                   = _T("提示");
	g_sLangID_SureDeleFile               = _T("sSureDeleFile");
	g_sLangTxt_SureDeleFile              = _T("你确实要删除文件【%s】吗");
	g_sLangID_ExiSaNameFile              = _T("sExiSaNameFile");
	g_sLangTxt_ExiSaNameFile             = _T("存在同名称的文件夹【%s】");
	g_sLangID_ExiSmNmFile3               = _T("sExiSmNmFile3");
	g_sLangTxt_ExiSmNmFile3              = _T("存在同名称的文件【%s】");
	g_sLangID_ExiSmNmFile2               = _T("sExiSmNmFile2");
	g_sLangTxt_ExiSmNmFile2              = _T("文件夹【%s】存在同名称的文件【%s】");
	g_sLangID_ChoImpFile                 = _T("sChoImpFile");
	g_sLangTxt_ChoImpFile                = _T("选择导入的配置文件夹");
	g_sLangID_ExpFileFin                 = _T("sExpFileFin");
	g_sLangTxt_ExpFileFin                = _T("导出目标文件夹【%s】完成");
	g_sLangID_TargFolderExist            = _T("sTargFolderExist");
	g_sLangTxt_TargFolderExist           = _T("目标文件夹【%s】已经存在");
	g_sLangID_ChoFoldExDir               = _T("sChoFoldExDir");
	g_sLangTxt_ChoFoldExDir              = _T("选择配置文件夹导出目标目录");
	g_sLangID_SureDeleFold               = _T("sSureDeleFold");
	g_sLangTxt_SureDeleFold              = _T("确实要删除文件夹【%s】吗？");
	g_sLangID_DeleFold                   = _T("sDeleFold");
	g_sLangTxt_DeleFold                  = _T("删除文件夹将删除此文件夹及其下的全部文件及文件夹。\r\n确实要删除文件夹【%s】吗？");
	g_sLangID_FoldCoverFold              = _T("sFoldCoverFold");
	g_sLangTxt_FoldCoverFold             = _T("文件夹【%s】包含子文件夹或者文件\r\n请先删除子文件夹或者文件，然后再删除目录");
	g_sLangID_ConfigFileManag            = _T("sConfigFileManag");
	g_sLangTxt_ConfigFileManag           = _T("IEC61850配置文件管理");

	g_sLangID_AtsPubFileManag            = _T("sAtsPubFileManag");
	g_sLangTxt_AtsPubFileManag           = _T("自动测试文件发布管理");
	g_sLangID_AddPubFile				= _T("sAddPubFile");
	g_sLangTxt_AddPubFile				= _T("添加发布");
	g_sLangID_ModifyPubFile				= _T("sModifyPubFile");
	g_sLangTxt_ModifyPubFile			= _T("修改发布");
	g_sLangID_DeletePubFile				= _T("sDeletePubFile");
	g_sLangTxt_DeletePubFile			= _T("删除发布");

	//故障、通用、结果参数
	g_sLangID_FaultParameter            = _T("sFaultParameter");
	g_sLangTxt_FaultParameter           = _T("故障参数");
	g_sLangID_GeneralParameter          = _T("sGeneralParameter");
	g_sLangTxt_GeneralParameter         = _T("通用参数");
	g_sLangID_ResultParameter           = _T("sResultParameter");
	g_sLangTxt_ResultParameter          = _T("结果参数");
	g_sLangID_AppBaseParameter           = _T("sAppBaseParameter");
	g_sLangTxt_AppBaseParameter          = _T("底层参数");

	g_sLangID_ArbitrElement             = _T("sArbitrElement");
	g_sLangTxt_ArbitrElement            = _T("任意元素");
	g_sLangID_SpecifiedElement          = _T("sSpecifiedElement");
	g_sLangTxt_SpecifiedElement         = _T("指定的元素");
	g_sLangID_SequDefinElemIn           = _T("sSequDefinElemIn");
	g_sLangTxt_SequDefinElemIn          = _T("序列定义中的元素");
	g_sLangID_SequDefinElemOut          = _T("sSequDefinElemOut");
	g_sLangTxt_SequDefinElemOut         = _T("序列定义之外的元素");
	g_sLangID_ReferElements             = _T("sReferElements");
	g_sLangTxt_ReferElements            = _T("引用元素");
	g_sLangID_Values                     = _T("sValues");
	g_sLangTxt_Values                    = _T("值");
	g_sLangID_Time                      = _T("sTime");
	g_sLangTxt_Time                     = _T("时间");
	g_sLangID_Integer                   = _T("sInteger");
	g_sLangTxt_Integer                  = _T("整数");
	g_sLangID_FloatNumber               = _T("sFloatNumber");
	g_sLangTxt_FloatNumber              = _T("浮点数");
	g_sLangID_CharacterString           = _T("sCharacterString");
	g_sLangTxt_CharacterString          = _T("字符串");
	g_sLangID_Equal                     = _T("sEqual");
	g_sLangTxt_Equal                    = _T("等于");
	g_sLangID_LessThan                  = _T("sLessThan");
	g_sLangTxt_LessThan                 = _T("小于");
	g_sLangID_LessOrEqual               = _T("sLessOrEqual");
	g_sLangTxt_LessOrEqual              = _T("小于等于");
	g_sLangID_MoreThan                  = _T("sMoreThan");
	g_sLangTxt_MoreThan                 = _T("大于");
	g_sLangID_MoreOrEqual               = _T("sMoreOrEqual");
	g_sLangTxt_MoreOrEqual              = _T("大于等于");
	g_sLangID_NotEqual                  = _T("sNotEqual");
	g_sLangTxt_NotEqual                 = _T("不等于");
	g_sLangID_CharStringIncl            = _T("sCharStringIncl");
	g_sLangTxt_CharStringIncl           = _T("字符串包含");
	g_sLangID_CharStringNIncl           = _T("sCharStringNIncl");
	g_sLangTxt_CharStringNIncl          = _T("字符串不包含");
	g_sLangID_NumberRange               = _T("sNumberRange");
	g_sLangTxt_NumberRange              = _T("数值范围");
	g_sLangID_BoundNumRange             = _T("sBoundNumRange");
	g_sLangTxt_BoundNumRange            = _T("数值范围带边界");
	g_sLangID_DataVarAss                = _T("sDataVarAss");
	g_sLangTxt_DataVarAss               = _T("数据变量赋值");
	g_sLangID_PropertyID                = _T("sPropertyID");
	g_sLangTxt_PropertyID               = _T("属性ID");
	g_sLangID_DataType                  = _T("sDataType");
	g_sLangTxt_DataType                 = _T("数据类型");
	g_sLangID_FunctionalSymbol          = _T("sFunctionalSymbol");
	g_sLangTxt_FunctionalSymbol         = _T("操作符号");
	g_sLangID_Data2                     = _T("sData2 ");
	g_sLangTxt_Data2                    = _T("数据2");
	g_sLangID_ResultVariable            = _T("sResultVariable");
	g_sLangTxt_ResultVariable           = _T("结果变量");
	g_sLangID_GnrtFileNm                = _T("sGnrtFileNm");
	g_sLangTxt_GnrtFileNm               = _T("组合生成文件名称");
	g_sLangID_OrgnFileNm                = _T("sOrgnFileNm");
	g_sLangTxt_OrgnFileNm               = _T("原文件名称");
	g_sLangID_TgetFileNm                = _T("sTgetFileNm");
	g_sLangTxt_TgetFileNm               = _T("目标文件名称");

	g_sLangID_TraProtocol               = _T("sTraProtocol");
	g_sLangTxt_TraProtocol              = _T("传统规约");
	g_sLangID_61850Protocol             = _T("s61850Protocol");
	g_sLangTxt_61850Protocol            = _T("61850规约");
	g_sLangID_None                      = _T("sNone");
	g_sLangTxt_None                     = _T("无");

	g_sLangID_OverWrite                 = _T("sOverWrite");
	g_sLangTxt_OverWrite                = _T("覆盖");
	g_sLangID_FilePasteOprt             = _T("sFilePasteOprt");
	g_sLangTxt_FilePasteOprt            = _T("文件粘贴：操作处理");
	g_sLangID_SelFolder                 = _T("sSelFolder");
	g_sLangTxt_SelFolder                = _T("选择文件夹");
	g_sLangID_FileName                  = _T("sFileName");
	g_sLangTxt_FileName                 = _T("文件名");
	g_sLangID_NewFolder                 = _T("sNewFolder");
	g_sLangTxt_NewFolder                = _T("新建文件夹");
	g_sLangID_FolderNmMdf               = _T("sFolderNmMdf");
	g_sLangTxt_FolderNmMdf              = _T("文件夹名称修改");
	//
	g_sLangID_NotAuthorized               = _T("sNotAuthorized");
	g_sLangTxt_NotAuthorized              = _T("你使用的系统没有授权");
	//  g_sLangID_AuthorizedUserUnit               = _T("sAuthorizedUserUnit");
	//  g_sLangTxt_AuthorizedUserUnit              = _T("版权所有：%s      授权用户单位：%s     授权用户名：%s");
	g_sLangID_NotAuthorized2               = _T("sNotAuthorized2");
	g_sLangTxt_NotAuthorized2              = _T("没有授权");
	g_sLangID_Close                = _T("sClose");
	g_sLangTxt_Close               = _T("关闭");
	g_sLangID_CloseTip                = _T("sCloseTip");
	g_sLangTxt_CloseTip               = _T("关闭活动文档\n关闭");
	g_sLangID_DataSets                = _T("sDataSets");
	g_sLangTxt_DataSets               = _T("数据集");
	g_sLangID_EquipDataModel                = _T("sEquipDataModel");
	g_sLangTxt_EquipDataModel               = _T("设备数据模型");
	g_sLangID_DevAtrbDefin                = _T("sDevAtrbDefin");
	g_sLangTxt_DevAtrbDefin               = _T("设备属性定义");
	g_sLangID_LogicdevCPU                = _T("sLogicdevCPU");
	g_sLangTxt_LogicdevCPU               = _T("逻辑设备(CPU)");

	g_sLangID_LogicDevice = _T("sLogicDevice"); //逻辑设备
	g_sLangTxt_LogicDevice = _T("逻辑设备");
	g_sLangID_LogicDeviceMap = _T("sLogicDeviceMap"); //逻辑设备MAP
	g_sLangTxt_LogicDeviceMap = _T("逻辑设备映射");
	g_sLangID_DataSetsMap = _T("sDataSetsMap"); //数据集
	g_sLangTxt_DataSetsMap = _T("数据集映射");

	g_sLangID_ParaTypeGroup                = _T("sParaTypeGroup");
	g_sLangTxt_ParaTypeGroup               = _T("参数类型【%s】组必须有一组");
	g_sLangID_NoParaTypeGroup                = _T("sNoParaTypeGroup");
	g_sLangTxt_NoParaTypeGroup               = _T("不存在参数类型为【%s】的组");
	g_sLangID_DevDataFile                = _T("sDevDataFile");
	g_sLangTxt_DevDataFile                = _T("设备数据模型文件(*.xml)|*.xml||");
	g_sLangID_RightsReserved                = _T("sRightsReserved");
	g_sLangTxt_RightsReserved               = _T("版权所有：");
	g_sLangID_LicensedTo                = _T("sLicensedTo");
	g_sLangTxt_LicensedTo               = _T("授权给：");
	g_sLangID_DataTypeUnExist                = _T("sDataTypeUnExist");
	g_sLangTxt_DataTypeUnExist               = _T("Row=%d  Col=%d  数据类型对象不存在");
	g_sLangID_Sizes                = _T("sSizes");
	g_sLangTxt_Sizes               = _T("号");
	g_sLangID_SourceDataObject                = _T("sSourceDataObject");
	g_sLangTxt_SourceDataObject               = _T("源数据对象");
	g_sLangID_MatchDataObject                = _T("sMatchDataObject");
	g_sLangTxt_MatchDataObject                = _T("匹配数据对象");
	g_sLangID_SelMatchDataObject                = _T("sSelMatchDataObject");
	g_sLangTxt_SelMatchDataObject               = _T("选择匹配的数据对象");

	g_sLangID_USBKey                = _T("sUSBKey");
	g_sLangTxt_USBKey               = _T("请插入授权加密狗！");
	g_sLangID_USBKeyUpdate                = _T("sUSBKeyUpdate");
	g_sLangTxt_USBKeyUpdate               = _T("授权加密狗驱动程序版本过低，请更新驱动程序！");
	g_sLangID_NoUSBkey                = _T("sNoUSBkey");
	g_sLangTxt_NoUSBkey                = _T("没有安装授权加密狗驱动程序，请安装驱动程序！");
	g_sLangID_SystemError                = _T("sSystemError");
	g_sLangTxt_SystemError               = _T("系统错误！");
	g_sLangID_SystemError2                = _T("sSystemError2");
	g_sLangTxt_SystemError2              = _T("系统错误：HASP_INV_HND：Invalid login handle passed to function");
	g_sLangID_SystemError3                = _T("sSystemError3");
	g_sLangTxt_SystemError3               = _T("系统错误：HASP_INV_FILEID：Specified File ID not recognized by API");
	g_sLangID_SystemError4                = _T("sSystemError4");
	g_sLangTxt_SystemError4               = _T("系统错误：HASP_MEM_RANGE：Request exceeds memory range of a Sentinel file");
	//  g_sLangID_RightReservedS                = _T("sRightReservedS");
	//  g_sLangTxt_RightReservedS               = _T("版权所有：%s");
	g_sLangID_SystemDevelop                = _T("sSystemDevelop");
	g_sLangTxt_SystemDevelop              = _T("系统开发");
	g_sLangID_UserName                = _T("sUserName");
	g_sLangTxt_UserName               = _T("使用用户");
	g_sLangID_ClientUnit                = _T("sClientUnit");
	g_sLangTxt_ClientUnit               = _T("客户单位");
	g_sLangID_ServerLicense                = _T("sServerLicense");
	g_sLangTxt_ServerLicense               = _T("服务器授权");
	g_sLangID_ServerLicense2                = _T("sServerLicense2");
	g_sLangTxt_ServerLicense2               = _T("从服务器获取授权信息，请稍候....");
	g_sLangID_LicenseCommun                = _T("sLicenseCommun");
	g_sLangTxt_LicenseCommun               = _T("与授权服务器通信超时，请确保网络连接和服务器配置正确！");
	g_sLangID_TestInstSel              = _T("sTestInstSel");
	g_sLangTxt_TestInstSel             = _T("测试仪选择");
	g_sLangID_AddScriptFail              = _T("sAddScriptFail");
	g_sLangTxt_AddScriptFail             = _T("加载功能脚本文件[%s]失败");
	g_sLangID_TestFctnUnExist              = _T("sTestFctnUnExist");
	g_sLangTxt_TestFctnUnExist             = _T("测试功能\"%s\"不存在");
	g_sLangID_IEC61850SetFile              = _T("sIEC61850SetFile");
	g_sLangTxt_IEC61850SetFile             = _T("IEC61850配置文件");
	g_sLangID_ComtradeFile              = _T("sComtradeFile");
	g_sLangTxt_ComtradeFile             = _T("COMTRADE录波文件");
	g_sLangID_TestFctnFile              = _T("sTestFctnFile");
	g_sLangTxt_TestFctnFile             = _T("测试功能标准文件");
	g_sLangID_CommunStraFile              = _T("sCommunStraFile");
	g_sLangTxt_CommunStraFile             = _T("通讯标准文件");
	g_sLangID_Number2              = _T("sNumber2");
	g_sLangTxt_Number2             = _T("编号/条目号");
	g_sLangID_ALreadyExist              = _T("sALreadyExist");
	g_sLangTxt_ALreadyExist             = _T("【%s】在【%s】已经存在");
	g_sLangID_MdtInsert            = _T("sMdtInsert");
	g_sLangTxt_MdtInsert           = _T("插入");
	g_sLangID_UpMove            = _T("sUpMove");
	g_sLangTxt_UpMove           = _T("上移");
	g_sLangID_DownMove            = _T("sDownMove");
	g_sLangTxt_DownMove           = _T("下移");
	g_sLangID_Unit                 = _T("sUnit");
	g_sLangTxt_Unit             = _T("单位");
	g_sLangID_MinValue                 = _T("sMinValue");
	g_sLangTxt_MinValue             = _T("最小值");
	g_sLangID_MaxValue                 = _T("sMaxValue");
	g_sLangTxt_MaxValue             = _T("最大值");
	g_sLangID_Step                 = _T("sStep");
	g_sLangTxt_Step            = _T("步长");
	g_sLangID_Nonstandard                 = _T("sNonstandard");
	g_sLangTxt_Nonstandard              = _T("非标");
	g_sLangID_StatePower                 = _T("sStatePower");
	g_sLangTxt_StatePower              = _T("国电南京自动化股份有限公司");
	g_sLangID_Bphase                 = _T("sBphase");
	g_sLangTxt_Bphase              = _T("B相");
	g_sLangID_Aphase                 = _T("sAphase");
	g_sLangTxt_Aphase              = _T("A相");
	g_sLangID_Cphase                = _T("sCphase");
	g_sLangTxt_Cphase              = _T("C相");
	g_sLangID_ABphase                 = _T("sABphase");
	g_sLangTxt_ABphase              = _T("AB相");
	g_sLangID_BCphase                 = _T("sBCphase");
	g_sLangTxt_BCphase              = _T("BC相");
	g_sLangID_CAphase                 = _T("sCAphase");
	g_sLangTxt_CAphase              = _T("CA相");
	g_sLangID_Application                 = _T("sApplication");
	g_sLangTxt_Application              = _T("应用程序向导生成的本地应用程序");
	g_sLangID_FixedValueRegion                 = _T("sFixedValueRegion");
	g_sLangTxt_FixedValueRegion              = _T("定值区");
	g_sLangID_Modify               = _T("sModify");
	g_sLangTxt_Modify                  = _T("修改");
	g_sLangID_ItemPrtcFile               = _T("sItemPrtcFile");
	g_sLangTxt_ItemPrtcFile                  = _T("设备点表文件(*.xml)|*.xml||");
	g_sLangID_SelDevDaModFile     = _T("sSelDevDaModFile");
	g_sLangTxt_SelDevDaModFile    = _T("选择设备数据模型文件");
	g_sLangID_TemDataFileChange     = _T("sTemDataFileChange");
	g_sLangTxt_TemDataFileChange    = _T("模板设备数据模型替换映射配置文件");
	g_sLangID_ConServerFail     = _T("sConServerFail");
	g_sLangTxt_ConServerFail    = _T("连接服务器【%s】【%d】失败");
	g_sLangID_ConServerSucc     = _T("sConServerSucc");
	g_sLangTxt_ConServerSucc    = _T("连接服务器【%s】【%d】成功");
	g_sLangID_UserUnExist     = _T("sUserUnExist");
	g_sLangTxt_UserUnExist    = _T("用户名不存在");
	g_sLangID_PasswordIncorrect     = _T("sPasswordIncorrect");
	g_sLangTxt_PasswordIncorrect   = _T("密码不正确");
	g_sLangID_LoginError     = _T("sLoginError");
	g_sLangTxt_LoginError    = _T("登录错误");
	g_sLangID_StopTest                 = _T("sStopTest");
	g_sLangTxt_StopTest                = _T("停止测试");
	g_sLangID_StartTest                 = _T("sStartTest");
	g_sLangTxt_StartTest                = _T("开始测试");
	g_sLangID_ExportReport         = _T("sExportReport");
	g_sLangTxt_ExportReport        = _T("导出报告");
	g_sLangID_ExportReportBatch         = _T("sExportReportBatch");
	g_sLangTxt_ExportReportBatch        = _T("批量导出报告");
	g_sLangID_StatusBar                = _T("sStatusBar");
	g_sLangTxt_StatusBar               = _T("状态栏");
	g_sLangID_TestStop2                            = _T("sTestStop2");
	g_sLangTxt_TestStop2                           = _T("连接设备失败，测试终止");
	g_sLangID_DataOpreation                           = _T("sDataOpreation");
	g_sLangTxt_DataOpreation                           = _T("数据操作");

	g_sLangID_OpenTip             = _T("sOpenTip");
	g_sLangTxt_OpenTip            = _T("打开");
	g_sLangID_ModelTestTip             = _T("sModelTestTip");
	g_sLangTxt_ModelTestTip            = _T("开始测试两个数设备数据模型\n开始测试");
	g_sLangID_DevModelTestTip             = _T("sDevModelTestTip");
	g_sLangTxt_DevModelTestTip            = _T("从装置枚举数据模型，然后进行测试\n装置模型测试");
	g_sLangID_StopTestTip             = _T("sStopTestTip");
	g_sLangTxt_StopTestTip            = _T("停止测试\n停止测试");
	g_sLangID_ExportReportTip             = _T("sExportReportTip");
	g_sLangTxt_ExportReportTip            = _T("导出报告\n导出报告");
	g_sLangID_SaveFileTip             = _T("sSaveFileTip");
	g_sLangTxt_SaveFileTip            = _T("保存设备数据模型映射关系文件\n保存文件");
	g_sLangID_OutputBarTip             = _T("sOutputBarTip");
	g_sLangTxt_OutputBarTip            = _T("显示或隐藏输出栏\n切换输出栏");
	g_sLangID_StatusBarTip             = _T("sStatusBarTip");
	g_sLangTxt_StatusBarTip            = _T("显示或隐藏状态栏\n切换状态栏");
	g_sLangID_CompareDataTip             = _T("sCompareDataTip");
	g_sLangTxt_CompareDataTip            = _T("比较ID\n比较ID");
	g_sLangID_AboutTip             = _T("sAboutTip");
	g_sLangTxt_AboutTip            = _T("显示程序信息、版本号和版权\n关于");
	g_sLangID_TestMain             = _T("sTestMain");
	g_sLangTxt_TestMain            = _T("测试主页(&H)");
	g_sLangID_ModelTest             = _T("sModelTest");
	g_sLangTxt_ModelTest            = _T("模型测试");
	g_sLangID_ProtocolTest             = _T("sProtocolTest");
	g_sLangTxt_ProtocolTest            = _T("规约测试");
	g_sLangID_ModelFileTest             = _T("sModelFileTest");
	g_sLangTxt_ModelFileTest            = _T("模型文件测试");
	g_sLangID_DevModelTest             = _T("sDevModelTest");
	g_sLangTxt_DevModelTest            = _T("装置模型测试");
	g_sLangID_ResultOpera             = _T("sResultOpera");
	g_sLangTxt_ResultOpera           = _T("结果操作");
	g_sLangID_SaveFile             = _T("sSaveFile");
	g_sLangTxt_SaveFile            = _T("保存映射文件");
	g_sLangID_OutputBar             = _T("sOutputBar");
	g_sLangTxt_OutputBar            = _T("输出栏");
	g_sLangID_CompareData             = _T("sCompareData");
	g_sLangTxt_CompareData            = _T("比较数据ID");
	g_sLangID_CmpDataNameFull = _T("sCmpDataNameFull");//数据名称全字符串比较
	g_sLangTxt_CmpDataNameFull = _T("名称全字符串比较");
	g_sLangID_Browse             = _T("sBrowse");
	g_sLangTxt_Browse            = _T("浏览");
	g_sLangID_Home             = _T("sHome");
	g_sLangTxt_Home            = _T("主页(H)");
	g_sLangID_CreatDataMap             = _T("sCreatDataMap");
	g_sLangTxt_CreatDataMap            = _T("创建数据映射");
	g_sLangID_DeleteDataMap             = _T("sDeleteDataMap");
	g_sLangTxt_DeleteDataMap            = _T("删除数据映射");
	g_sLangID_CreatDataMap2             = _T("sCreatDataMap2");
	g_sLangTxt_CreatDataMap2            = _T("创建数据集映射");
	g_sLangID_DeleteDataMap2             = _T("sDeleteDataMap2");
	g_sLangTxt_DeleteDataMap2            = _T("删除数据集映射");
	g_sLangID_SelStdDataFile             = _T("sSelStdDataFile");
	g_sLangTxt_SelStdDataFile            = _T("请选择标准设备数据模型文件");
	g_sLangID_DataSetNoOnly             = _T("sDataSetNoOnly");
	g_sLangTxt_DataSetNoOnly            = _T("数据集【%s】不唯一");
	g_sLangID_User = _T("sUser");
	g_sLangTxt_User = _T("用户");
	g_sLangID_Module = _T("sModule");
	g_sLangTxt_Module = _T("模块");
	g_sLangID_RemotePort = _T("sRemotePort");
	g_sLangTxt_RemotePort = _T("远程端口");
	g_sLangID_LocalPort = _T("sLocalPort");
	g_sLangTxt_LocalPort = _T("本地端口");
	g_sLangID_State = _T("sState");
	g_sLangTxt_State = _T("状态");
	g_sLangID_ServerWorkPath = _T("sServerPath");
	g_sLangTxt_ServerWorkPath = _T("服务器工作路径");

	g_sLangID_New                                 = _T("sNew");
	g_sLangTxt_New                                = _T("新建(N)");
	g_sLangID_TemNew                                 = _T("sTemNew");
	g_sLangTxt_TemNew                                = _T("新建模板");
	g_sLangID_NewTip                                 = _T("sNewTip");
	g_sLangTxt_NewTip                                = _T("创建新规约模板\n新建");
	g_sLangID_OpenTips                                 = _T("sOpenTips");
	g_sLangTxt_OpenTips                                = _T("打开现有规约模板\n打开");
	g_sLangID_SaveTips                                 = _T("sSaveTips");
	g_sLangTxt_SaveTips                                = _T("保存规约模板\n保存");
	g_sLangID_SaveAsTips                                 = _T("sSaveAsTips");
	g_sLangTxt_SaveAsTips                                = _T("用新名称保存规约模板\n另存为");
	g_sLangID_RecentFile                                 = _T("sRecentFile");
	g_sLangTxt_RecentFile                                = _T("最近使用的文档");

	g_sLangID_TemplateDef                                 = _T("sTemplateDef");
	g_sLangTxt_TemplateDef                                = _T("模板定义");
	g_sLangID_TemplateProperty                                 = _T("sTemplateProperty");
	g_sLangTxt_TemplateProperty                                = _T("模板属性");
	g_sLangID_CommDef                                 = _T("sCommDef");
	g_sLangTxt_CommDef                                = _T("通讯定义");
	g_sLangID_InitDef                                 = _T("sInitDef");
	g_sLangTxt_InitDef                                = _T("初始化定义");
	g_sLangID_Exist                                 = _T("sExist");
	g_sLangTxt_Exist                                = _T("【%s】已经存在");
	g_sLangID_NoDataNotInsert                                 = _T("sNoDataNotInsert");
	g_sLangTxt_NoDataNotInsert                                = _T("无数据，不能插入！");
	g_sLangID_KeySameId                                 = _T("sKeySameId");
	g_sLangTxt_KeySameId                                = _T("存在相同名称的关键字【%s】");
	g_sLangID_Attention                                 = _T("sAttention");
	g_sLangTxt_Attention                                = _T("注意");

	g_sLangID_InitiaErrors                                 = _T("sInitiaErrors");
	g_sLangTxt_InitiaErrors                                = _T("初始化错误");
	g_sLangID_OtherStart                                 = _T("sOtherStart");
	g_sLangTxt_OtherStart                                = _T("对方没有启动");
	g_sLangID_OtherClose                                 = _T("sOtherClose");
	g_sLangTxt_OtherClose                                = _T("对方已经关闭");
	g_sLangID_ConnectRefuse                                 = _T("sConnectRefuse");
	g_sLangTxt_ConnectRefuse                                = _T("连接的尝试被拒绝");
	g_sLangID_AttemptOperate                                 = _T("sAttemptOperate");
	g_sLangTxt_AttemptOperate                                = _T("在一个非套接字上尝试了一个操作");
	g_sLangID_SpecificUse                                 = _T("sSpecificUse");
	g_sLangTxt_SpecificUse                                = _T("特定的地址已在使用中");
	g_sLangID_ConnectionClosed                                 = _T("sConnectionClosed");
	g_sLangTxt_ConnectionClosed                                = _T("与主机的连接被关闭");
	g_sLangID_GenericError                                 = _T("sGenericError");
	g_sLangTxt_GenericError                                = _T("一般错误");
	g_sLangID_Add             = _T("sAdd");
	g_sLangTxt_Add             = _T("添加");
	g_sLangID_NoDataChangeMsg             = _T("sNoDataChangeMsg");
	g_sLangTxt_NoDataChangeMsg             = _T("没有注册节点[%d]数据改变消息");
	g_sLangID_FileNameInclude             = _T("sFileNameInclude");
	g_sLangTxt_FileNameInclude             = _T("文件名【%s】包含【%s】等非法字符");

	g_sLangID_Add3             = _T("sAdd3");
	g_sLangTxt_Add3             = _T("增加");
	g_sLangID_Select                = _T("sSelect");
	g_sLangTxt_Select                = _T("选择");
	g_sLangID_Value                    = _T("sValue");
	g_sLangTxt_Value                   = _T("数值");
	g_sLangID_DefaultValue                    = _T("sDefaultValue");
	g_sLangTxt_DefaultValue                   = _T("默认值");
	g_sLangID_PrtcTempFile             = _T("sPrtcTempFile");
	g_sLangTxt_PrtcTempFile            = _T("规约模板文件");
	g_sLangID_PrtcTempFileMagn             = _T("sPrtcTempFileMagn");
	g_sLangTxt_PrtcTempFileMagn            = _T("规约模板文件管理");
	g_sLangID_PrtcProjectFile             = _T("sPrtcProjectFile");
	g_sLangTxt_PrtcProjectFile            = _T("规约工程文件");
	g_sLangID_ModelFile           = _T("sModelFile");
	g_sLangTxt_ModelFile          = _T("模型文件");

	g_sLangID_Version             = _T("sVersion");
	g_sLangTxt_Version            = _T("版本");
	g_sLangID_TimeLimit             = _T("sTimeLimit");
	g_sLangTxt_TimeLimit            = _T("时限");
	g_sLangID_ComparaObject             = _T("sComparaObject");
	g_sLangTxt_ComparaObject           = _T("比较项");
	g_sLangID_StandardValue             = _T("sStandardValue");
	g_sLangTxt_StandardValue           = _T("标准值");
	g_sLangID_TureValue             = _T("sTureValue");
	g_sLangTxt_TureValue           = _T("实际值");
	g_sLangID_Property             = _T("sProperty");
	g_sLangTxt_Property           = _T("属性");
	g_sLangID_UnStallWord             = _T("sUnStallWord");
	g_sLangTxt_UnStallWord           = _T("没有安装Word");
	g_sLangID_Title             = _T("sTitle");
	g_sLangTxt_Title           = _T("标题 %d");
	g_sLangID_ReName             = _T("sReName");
	g_sLangTxt_ReName           = _T("重命名");
	g_sLangID_UserUnits             = _T("sUserUnits");
	g_sLangTxt_UserUnits           = _T("用户单位：");
	g_sLangID_User2             = _T("sUser2");
	g_sLangTxt_User2           = _T("用户：");
	g_sLangID_Develop             = _T("sDevelop");
	g_sLangTxt_Develop           = _T("开发：");

	g_sLangID_Variable             = _T("sVariable");
	g_sLangTxt_Variable            = _T("变量");
	g_sLangID_DeleteFloder             = _T("sDeleteFloder");
	g_sLangTxt_DeleteFloder            = _T("删除文件夹");
	g_sLangID_SureDelFoldItem             = _T("sSureDelFoldItem");
	g_sLangTxt_SureDelFoldItem            = _T("确定要删除文件夹 %s 及其子项目吗?");
	g_sLangID_Size2             = _T("sSize2");
	g_sLangTxt_Size2            = _T("大小");
	g_sLangID_ModiftyFileNameFail             = _T("sModiftyFileNameFail");
	g_sLangTxt_ModiftyFileNameFail            = _T("修改文件名称失败");


	g_sLangID_SCDFiles            = _T("sSCDFiles");
	g_sLangTxt_SCDFiles            = _T("SCD文件");
	g_sLangID_RecordFiles            = _T("sRecordFiles");
	g_sLangTxt_RecordFiles            = _T("录波文件");
	g_sLangID_TemplateFiles            = _T("sTemplateFiles");
	g_sLangTxt_TemplateFiles            = _T("模板文件");
	g_sLangID_WorkspaceFiles            = _T("sReportFiles");
	g_sLangTxt_WorkspaceFiles            = _T("报告文件");
	g_sLangID_IEC61850SetFiles            = _T("sIEC61850SetFiles");
	g_sLangTxt_IEC61850SetFiles            = _T("IEC61850配置文件");
	g_sLangID_PcapFiles            = _T("sPcapFiles");
	g_sLangTxt_PcapFiles            = _T("Pcap文件");
	g_sLangID_PrintScreen            = _T("sPrintScreen");
	g_sLangTxt_PrintScreen            = _T("截屏文件夹");
	g_sLangID_Others            = _T("sOthers");
	g_sLangTxt_Others            = _T("其他");
	g_sLangID_SavePcapFiles            = _T("sSavePcapFiles");
	g_sLangTxt_SavePcapFiles           = _T("保存Pcap文件");
	g_sLangID_SavePrintScreen            = _T("sSavePrintScreen");
	g_sLangTxt_SavePrintScreen            = _T("保存截屏图片");
	g_sLangID_OtherTypeFiles            = _T("sOtherTypeFiles");
	g_sLangTxt_OtherTypeFiles            = _T("其他类型文件");



	g_sLangID_Output             = _T("sOutput");
	g_sLangTxt_Output            = _T("输出");
	g_sLangID_ConfirmDel             = _T("sConfirmDel");
	g_sLangTxt_ConfirmDel            = _T("确定要删除【%s】吗？");
	g_sLangID_NoSave             = _T("sNoSave");
	g_sLangTxt_NoSave             = _T("文件【%s】没有保存，保存吗？");
	g_sLangID_Increase                = _T("sIncrease"); 
	g_sLangTxt_Increase               = _T("递增");      
	g_sLangID_Decrease                = _T("sDecrease"); 
	g_sLangTxt_Decrease              = _T("递减");  

	g_sLangID_Export                   = _T("sExport");
	g_sLangTxt_Export                  = _T("导出");
	g_sLangID_Import                   = _T("sImport");
	g_sLangTxt_Import                  = _T("导入");
	g_sLangID_ClcltFmla             = _T("sClcltFmla");
	g_sLangTxt_ClcltFmla             = _T("计算公式");
	g_sLangID_GuideWizardFile       = _T("sGuideWizardFile");
	g_sLangTxt_GuideWizardFile      = _T("作业指导书向导文件");

	g_sLangID_IecConfigFile            = _T("sIecConfigFile");
	g_sLangTxt_IecConfigFile           = _T("IEC61850配置文件");
	g_sLangID_DvIecConfigFile            = _T("sDvIecConfigFile");
	g_sLangTxt_DvIecConfigFile           = _T("智能设备测试仪IEC61850配置文件");
	g_sLangID_DvIecConfigFileMngr            = _T("sDvIecConfigFileMngr");
	g_sLangTxt_DvIecConfigFileMngr           = _T("智能设备测试仪IEC61850配置文件管理");

	g_sLangID_NoTitle           = _T("sNoTitle ");
	g_sLangTxt_NoTitle           = _T("无标题");
	g_sLangID_FileNotExist      = _T("sFileNotExist");
	g_sLangTxt_FileNotExist     = _T("文件【%s】不存在");

	g_sLangID_YunDownFileFaild = _T("sYunDownFileFaild");//从云端下载文件失败
	g_sLangTxt_YunDownFileFaild = _T("从云端下载文件失败");

	g_sLangID_Login                    = _T("sLogin");
	g_sLangTxt_Login                   = _T("登录");
	g_sLangID_UpLoad                   = _T("sUpLoad");
	g_sLangTxt_UpLoad                  = _T("上传");
	g_sLangID_DownLoad                 = _T("sDownLoad");
	g_sLangTxt_DownLoad                = _T("下载");

	g_sLangID_TestItemParEdit       = _T("sTestItemParEdi");
	g_sLangTxt_TestItemParEdit      = _T("测试项目参数编辑");
	g_sLangID_ParaName                = _T("sParaName");
	g_sLangTxt_ParaName                = _T("参数名称");
	g_sLangID_ParaValue                = _T("sParaValue");
	g_sLangTxt_ParaValue              = _T("参数值");

	g_sLangID_GlobalData                    = _T("sGlobalData");
	g_sLangTxt_GlobalData                   = _T("全局数据");
	g_sLangID_TestAppDef                    = _T("sTestAppDef");
	g_sLangTxt_TestAppDef                   = _T("测试仪定义");
	g_sLangID_RepeatResultInfo                    = _T("sRepeatResultInfo");
	g_sLangTxt_RepeatResultInfo                   = _T("计算结果:");

	g_sLangID_Clear                    = _T("sClear");
	g_sLangTxt_Clear                   = _T("清除");
	g_sLangID_SyntaxCheck                    = _T("sSyntaxCheck");
	g_sLangTxt_SyntaxCheck                   = _T("语法检查");
	g_sLangID_SyntaxCheckTips                    = _T("sSyntaxCheckTips");
	g_sLangTxt_SyntaxCheckTips                   = _T("语法检查\n语法检查");

	g_sLangID_OutputWnd                = _T("sOutputWnd");
	g_sLangTxt_OutputWnd               = _T("输出窗口");

	g_sLangID_DataSet                 = _T("sDataSet");
	g_sLangTxt_DataSet            = _T("数据集");

	g_sLangID_Quit                     = _T("sQuit");
	g_sLangTxt_Quit                    = _T("退出");
	g_sLangID_QuitTip                  = _T("sQuitTip");
	g_sLangTxt_QuitTip                 = _T("退出应用程序；提示保存文档\n退出");

    //shaolei 2024-1-4
    g_sLangID_Voltage             = _T("sVoltage");
    g_sLangTxt_Voltage            = _T("电压（V）");
    g_sLangID_Current             = _T("sCurrent");
    g_sLangTxt_Current             = _T("电流");
    g_sLangID_ActivePower             = _T("sActivePower");
    g_sLangTxt_ActivePower             = _T("有功功率");
    g_sLangID_ReactivePower             = _T("sReactivePower");
    g_sLangTxt_ReactivePower             = _T("无功功率");
    g_sLangID_Frequency             = _T("sFrequency");
    g_sLangTxt_Frequency             = _T("频率(Hz)");
    g_sLangID_PowerFactor             = _T("sPowerFactor");
    g_sLangTxt_PowerFactor             = _T("功率因数");

	g_sLangID_Native_StartOutput = _T("Native_StartOutput");
	g_sLangTxt_Native_StartOutput = _T("开始输出");
	////实际在CXLanguageResourceAtsBase中定义故删除  zhouhj 2024.5.25
//     g_sLangID_TestComplete               = _T("sTestComplete");
//     g_sLangTxt_TestComplete              = _T("测试完成");
    g_sLangID_Native_TestAnomalies       = _T("Native_TestAnomalies");
    g_sLangTxt_Native_TestAnomalies      = _T("测试异常");
    g_sLangID_Native_RelieveTestAnomalies= _T("Native_RelieveTestAnomalies");
    g_sLangTxt_Native_RelieveTestAnomalies= _T("解除测试异常");
    g_sLangID_Native_StateSwitch         = _T("Native_StateSwitch");
    g_sLangTxt_Native_StateSwitch        = _T("状态切换");
    g_sLangID_Native_SupDCSwitch         = _T("Native_SupDCSwitch");
    g_sLangTxt_Native_SupDCSwitch        = _T("辅助直流切换");
    g_sLangID_Native_BinDisPlace         = _T("Native_BinDisPlace");
    g_sLangTxt_Native_BinDisPlace        = _T("开入变位");
    g_sLangID_Native_BoutDisPlace        = _T("Native_BoutDisPlace");
    g_sLangTxt_Native_BoutDisPlace       = _T("开出变位");
    g_sLangID_Native_ParaUpdata          = _T("Native_ParaUpdata");
    g_sLangTxt_Native_ParaUpdata         = _T("参数更新");

	g_sLangID_Native_Port				 = _T("Native_Port");
	g_sLangTxt_Native_Port				 = _T("口");

	g_sLangID_TestInstrumentConfig = _T("TestInstrumentConfig");
	g_sLangTxt_TestInstrumentConfig = _T("测试仪配置");

	g_sLangID_ScanLANTestInstrument = _T("ScanLANTestInstrument");
	g_sLangTxt_ScanLANTestInstrument = _T("扫描局域网测试仪");

	g_sLangID_DirectConfigRemoteInstrument = _T("DirectConfigRemoteInstrument");
	g_sLangTxt_DirectConfigRemoteInstrument = _T("直接配置远程测试仪");

	g_sLangID_ScanRemoteTestInstrument = _T("ScanRemoteTestInstrument");
	g_sLangTxt_ScanRemoteTestInstrument = _T("扫描远程测试仪");
	g_sLangID_Setup = _T("Setup");
	g_sLangTxt_Setup = _T("设置");
	g_sLangID_Upgrade = _T("Upgrade");
	g_sLangTxt_Upgrade = _T("启升级");
	g_sLangID_EnablePUDA = _T("EnablePUDA");
	g_sLangTxt_EnablePUDA = _T("启PUDA");
	g_sLangID_EnableTestSvr = _T("EnableTestSvr");
	g_sLangTxt_EnableTestSvr = _T("启TestSvr");
	g_sLangID_TestInstrumentModel = _T("TestInstrumentModel");
	g_sLangTxt_TestInstrumentModel = _T("测试仪型号");
	g_sLangID_TestInstrumentID = _T("TestInstrumentID");
	g_sLangTxt_TestInstrumentID = _T("测试仪编号");
	g_sLangID_CloudIP = _T("CloudIP");
	g_sLangTxt_CloudIP = _T("云端IP：");
	g_sLangID_CloudPort = _T("CloudPort");
	g_sLangTxt_CloudPort = _T("云端Port：");
	g_sLangID_TestInstrumentSerialNumber = _T("TestInstrumentSerialNumber");
	g_sLangTxt_TestInstrumentSerialNumber = _T("测试仪序列号：");
	g_sLangID_Password = _T("Password");
	g_sLangTxt_Password = _T("密码：");
	g_sLangID_Unit2 = _T("Unit");
	g_sLangTxt_Unit2 = _T("单位：");
	g_sLangID_Bind = _T("Bind");
	g_sLangTxt_Bind = _T("绑定");
	g_sLangID_Query = _T("Query");
	g_sLangTxt_Query = _T("查询");
	g_sLangID_TestInstrumentConnectionError = _T("TestInstrumentConnectionError");
	g_sLangTxt_TestInstrumentConnectionError = _T("测试仪：%s 网络连接不通！");
	g_sLangID_CloudServerConnectionError = _T("CloudServerConnectionError");
	g_sLangTxt_CloudServerConnectionError = _T("云服务器：%s 网络连接不通！");
	g_sLangID_IPIsEmpty = _T("IPIsEmpty");
	g_sLangTxt_IPIsEmpty = _T("IP为空");
	g_sLangID_ConnectionTestInstrumentFailed = _T("ConnectionTestInstrumentFailed");
	g_sLangTxt_ConnectionTestInstrumentFailed = _T("连接测试仪失败");
	g_sLangID_MulticastInitSuccess = _T("MulticastInitSuccess");
	g_sLangTxt_MulticastInitSuccess = _T("组播初始化[%s][%d]成功");
	g_sLangID_MulticastInitFailed = _T("MulticastInitFailed");
	g_sLangTxt_MulticastInitFailed = _T("组播初始化[%s][%d]失败");
	g_sLangID_MulticastInitBindSuccess = _T("MulticastInitBindSuccess");
	g_sLangTxt_MulticastInitBindSuccess = _T("组播初始化[%s][%d]成功，绑定本地IP[%s]");
	g_sLangID_Disconnection = _T("Disconnection");
	g_sLangTxt_Disconnection = _T("断链");
	g_sLangID_CloudConnectionFailed = _T("CloudConnectionFailed");
	g_sLangTxt_CloudConnectionFailed = _T("连接云端失败");
	g_sLangID_TestInstrumentUserInfoError = _T("TestInstrumentUserInfoError");
	g_sLangTxt_TestInstrumentUserInfoError = _T("测试仪信息、用户信息输出错误");
	g_sLangID_Connect = _T("Connect");
	g_sLangTxt_Connect = _T("连接");
	g_sLangID_StopScanning = _T("StopScanning");
	g_sLangTxt_StopScanning = _T("停止扫描");
	g_sLangID_Scanning = _T("Scanning");
	g_sLangTxt_Scanning = _T("扫描");
	g_sLangID_NanjingEnergyCloud = _T("NanjingEnergyCloud");
	g_sLangTxt_NanjingEnergyCloud = _T("南京能云电力");
	g_sLangID_TestInstrumentConfigFileNotFound = _T("TestInstrumentConfigFileNotFound");
	g_sLangTxt_TestInstrumentConfigFileNotFound = _T("测试仪配置文件：%s 找不到！");
	g_sLangID_OAClientInitFail = _T("OAClientInitFail");
	g_sLangTxt_OAClientInitFail = _T("OA客户端COM接口初始化失败。");

	//2024-10-22 wuxinyi
	g_sLangID_ResultBar = _T("sResultBar");
	g_sLangTxt_ResultBar = _T("结果栏");
	g_sLangID_StatusLight = _T("sStatusLight");
	g_sLangTxt_StatusLight = _T("状态灯显示");
	g_sLangID_WinwordProcessWarning = _T("WinwordProcessWarning");
	g_sLangTxt_WinwordProcessWarning = _T("检测到WINWORD.EXE进程正在运行，请先关闭进程后，再导出报告。\r\n点击“Yes”，关闭进程，继续导出。点击“No”，取消导出");
	g_sLangID_CloseProcessWarning = _T("CloseProcessWarning");
	g_sLangTxt_CloseProcessWarning = _T("请关闭进程……");

}


CString g_sLangID_Chinese       ;// _T("Chinese");
CString g_sLangID_English       ;// _T("English");

CString g_sLangID_File          ;// _T("sFile");
CString g_sLangTxt_File         ;// _T("文件");
CString g_sLangID_FileNew       ;// _T("sFileNew");
CString g_sLangTxt_FileNew      ;// _T("新建文件");
CString g_sLangID_FileNewTip    ;// _T("sFileNewTip");
CString g_sLangTxt_FileNewTip   ;// _T("新建文件\n新建");
CString g_sLangID_FileOpen      ;// _T("sFileOpen");
CString g_sLangTxt_FileOpen     ;// _T("打开文件");
CString g_sLangID_Save          ;// _T("sSave");
CString g_sLangTxt_Save         ;// _T("保存");
CString g_sLangID_SaveTip          ;// _T("sSaveTip");
CString g_sLangTxt_SaveTip         ;// _T("保存模型文件\n保存");
CString g_sLangID_SaveAs        ;// _T("sSaveAs");
CString g_sLangTxt_SaveAs       ;// _T("另存为");
CString g_sLangID_SaveAsTip        ;// _T("sSaveAsTip");
CString g_sLangTxt_SaveAsTip       ;// _T("模型文件另存为\n另存为");
CString g_sLangID_Print         ;// _T("sPrint");
CString g_sLangTxt_Print        ;// _T("打印");
CString g_sLangID_FileClose     ;// _T("sFileClose");
CString g_sLangTxt_FileClose    ;// _T("关闭文件");
CString g_sLangID_Copy          ;// _T("sCopy");
CString g_sLangTxt_Copy         ;// _T("拷贝");
CString g_sLangID_View          ;// _T("sView");
CString g_sLangTxt_View         ;// _T("视图");
CString g_sLangID_SelAll        ;// _T("sSelAll");
CString g_sLangTxt_SelAll       ;// _T("全选");
CString g_sLangID_Clipboard     ;// _T("sClipboard");
CString g_sLangTxt_Clipboard    ;// _T("剪切板");
CString g_sLangID_PasteData         ;// _T("sPasteData");
CString g_sLangTxt_PasteData        ;// _T("粘贴数据");
CString g_sLangID_Paste         ;// _T("sPaste");
CString g_sLangTxt_Paste        ;// _T("粘贴");
CString g_sLangID_PasteTip      ;// _T("sPasteTip");
CString g_sLangTxt_PasteTip     ;// _T("插入剪贴板内容\n粘贴");
CString g_sLangID_Cut           ;// _T("sCut");
CString g_sLangTxt_Cut          ;// _T("剪切");
CString g_sLangID_Delete        ;// _T("sDelete");
CString g_sLangTxt_Delete       ;// _T("删除");
CString g_sLangID_OK            ;// _T("sOK");
CString g_sLangTxt_OK           ;// _T("确定");
CString g_sLangID_Cancel        ;// _T("sCancel");
CString g_sLangTxt_Cancel       ;// _T("取消");
CString g_sLangID_AppExit       ;// _T("sAppExit");
CString g_sLangTxt_AppExit      ;// _T("退出");
CString g_sLangID_AppExitTip    ;// _T("sAppExitTip");
CString g_sLangTxt_AppExitTip   ;// _T("退出应用程序；提示保存文档\n退出");
CString g_sLangID_Help          ;// _T("sHelp");
CString g_sLangTxt_Help         ;// _T("帮助");
CString g_sLangID_HelpAbout     ;// _T("sHelpAbout");
CString g_sLangTxt_HelpAbout    ;// _T("关于");
CString g_sLangID_Back        ;// _T("sBack");
CString g_sLangTxt_Back       ;// _T("返回");
//
CString g_sLangID_Name       ;// _T("sName");
CString g_sLangTxt_Name      ;// _T("名称");
CString g_sLangID_Index      ;// _T("sIndex");
CString g_sLangTxt_Index     ;// _T("编号");
CString g_sLangID_Type       ;// _T("sType");
CString g_sLangTxt_Type      ;// _T("类型");
CString g_sLangID_History    ;// _T("sHistory");
CString g_sLangTxt_History   ;// _T("历史");
CString g_sLangID_Open       ;// _T("sOpen");
CString g_sLangTxt_Open      ;// _T("打开");
CString g_sLangID_Location   ;// _T("sLocation");
CString g_sLangTxt_Location  ;// _T("定位");
CString g_sLangID_Path       ;// _T("sPath");
CString g_sLangTxt_Path      ;// _T("路径");
CString g_sLangID_Size       ;// _T("sSize");
CString g_sLangTxt_Size      ;// _T("大小(KB)");
CString g_sLangID_ModifiedTime       ;// _T("sModifiedTime");
CString g_sLangTxt_ModifiedTime      ;// _T("修改时间");

CString g_sLangID_Folder               ;// _T("sFolder");
CString g_sLangTxt_Folder              ;// _T("文件夹");
CString g_sLangID_SureDeleItem         ;// _T("sSureDeleItem");
CString g_sLangTxt_SureDeleItem        ;// _T("确定要删除这 %d 个项目吗?");
CString g_sLangID_SureDelete           ;// _T("sSureDelete");
CString g_sLangTxt_SureDelete          ;// _T("删除确认");
CString g_sLangID_SureAgain            ;// _T("sSureAgain");
CString g_sLangTxt_SureAgain           ;// _T("删除后将无法恢复，请再次确认");
CString g_sLangID_DeleteFail           ;// _T("sDeleteFail");
CString g_sLangTxt_DeleteFail          ;// _T("文件正在被使用，删除失败");
CString g_sLangID_FileDeleteFail       ;// _T("sFileDeleteFail");
CString g_sLangTxt_FileDeleteFail      ;// _T("删除文件失败");
CString g_sLangID_DeleteFailFold       ;// _T("sDeleteFailFold");
CString g_sLangTxt_DeleteFailFold      ;// _T("文件夹中包含正在被使用的文件，删除失败");
CString g_sLangID_FolderDeleteFail     ;// _T("sFolderDeleteFail");
CString g_sLangTxt_FolderDeleteFail    ;// _T("删除文件夹失败");
CString g_sLangID_FoldAlrOpen          ;// _T("sFoldAlrOpen");
CString g_sLangTxt_FoldAlrOpen         ;// _T("该文件夹中已被打开的文件");
CString g_sLangID_ModifiedFail         ;// _T("sModifiedFail");
CString g_sLangTxt_ModifiedFail        ;// _T("修改文件夹名称失败");
CString g_sLangID_FileOpened           ;// _T("sFileOpened");
CString g_sLangTxt_FileOpened          ;// _T("该文件已被打开");


CString g_sLangID_SerNumber       ;// _T("sSerNumber");
CString g_sLangTxt_SerNumber      ;// _T("序号");
CString g_sLangID_MinTime         ;// _T("sMinTime");
CString g_sLangTxt_MinTime        ;// _T("最小次数");
CString g_sLangID_MaxTime         ;// _T("sMaxTime");
CString g_sLangTxt_MaxTime        ;// _T("最大次数");

CString g_sLangID_Filter          ;// _T("sFilter");
CString g_sLangTxt_Filter         ;// _T("过滤");
CString g_sLangID_CinKeyDb        ;// _T("sCinKeyDb");
CString g_sLangTxt_CinKeyDb       ;// _T("合并文件");
CString g_sLangID_BaseKeyNew      ;// _T("sBaseKeyNew");
CString g_sLangTxt_BaseKeyNew     ;// _T("新建关键字");
CString g_sLangID_MultiKeyNew     ;// _T("sMultiKeyNew");
CString g_sLangTxt_MultiKeyNew    ;// _T("新建复合关键字");
CString g_sLangID_DeleteKey       ;// _T("sDeleteKey");
CString g_sLangTxt_DeleteKey      ;// _T("删除关键字");
CString g_sLangID_SelectSameKey   ;// _T("sSelectSameKey");
CString g_sLangTxt_SelectSameKey  ;// _T("查找无效关键字");
CString g_sLangID_AnalyzeKey      ;// _T("sAnalyzeKey");
CString g_sLangTxt_AnalyzeKey     ;// _T("关键字分析");
CString g_sLangID_AnalyzeKeyUnsu  ;// _T("sAnalyzeKeyUnsu");
CString g_sLangTxt_AnalyzeKeyUnsu ;// _T("没有匹配成功关键字");
CString g_sLangID_AnalyzeKeySu    ;// _T("sAnalyzeKeySu");
CString g_sLangTxt_AnalyzeKeySu   ;// _T("匹配成功的关键字");
CString g_sLangID_DeleteKeyObj    ;// _T("sDeleteKeyObj");
CString g_sLangTxt_DeleteKeyObj   ;// _T("请选择要删除的对象！");

CString g_sLangID_Data               ;// _T("sData");
CString g_sLangTxt_Data              ;// _T("数据");
CString g_sLangID_OperIns            ;// _T("sOperIns");
CString g_sLangTxt_OperIns           ;// _T("作业指导书");
CString g_sLangID_PromptMessage      ;// _T("sPromptMessage");
CString g_sLangTxt_PromptMessage     ;// _T("提示信息");
CString g_sLangID_PleaseChoose       ;// _T("sPleaseChoose");
CString g_sLangTxt_PleaseChoose      ;// _T("请在 %s 下选择%s");
CString g_sLangID_FileAlrExi         ;// _T("sFileAlrExi");
CString g_sLangTxt_FileAlrExi        ;// _T("文件 %s 已经存在");
CString g_sLangID_StandardFileName   ;// _T("sStandardFileName");
CString g_sLangTxt_StandardFileName  ;// _T("标准文件名");
CString g_sLangID_ManagSave          ;// _T("sManagSave");
CString g_sLangTxt_ManagSave         ;// _T("%s 管理---保存");
CString g_sLangID_ManagOpen          ;// _T("sManagOpen");
CString g_sLangTxt_ManagOpen         ;// _T("%s 管理---打开");
CString g_sLangID_FileExYN           ;// _T("sFileExYN");
CString g_sLangTxt_FileExYN          ;// _T("%s 文件已经存在，是否覆盖?");
CString g_sLangID_FileDupliName      ;// _T("sFileDupliName");
CString g_sLangTxt_FileDupliName     ;// _T("文件重名");
CString g_sLangID_AlrOpenFail        ;// _T("sAlrOpenFail");
CString g_sLangTxt_AlrOpenFail       ;// _T("%s 已经被打开，文件覆盖失败");
CString g_sLangID_FileCoverFail      ;// _T("sFileCoverFail");
CString g_sLangTxt_FileCoverFail     ;// _T("文件覆盖失败");

CString g_sLangID_AddDirectory               ;// _T("sAddDirectory");
CString g_sLangTxt_AddDirectory              ;// _T("添加目录");
CString g_sLangID_ImportDirectory            ;// _T("sImportDirectory");
CString g_sLangTxt_ImportDirectory           ;// _T("导入目录");
CString g_sLangID_ExportDirectory            ;// _T("sExportDirectory");
CString g_sLangTxt_ExportDirectory           ;// _T("导出目录");
CString g_sLangID_CopyFile                   ;// _T("sCopyFile");
CString g_sLangTxt_CopyFile                  ;// _T("拷贝文件");
CString g_sLangID_PasteFile                  ;// _T("sPasteFile");
CString g_sLangTxt_PasteFile                 ;// _T("粘贴文件");
CString g_sLangID_DeleteFile                 ;// _T("sDeleteFile");
CString g_sLangTxt_DeleteFile                ;// _T("删除文件");
CString g_sLangID_FileRename                 ;// _T("sFileRename");
CString g_sLangTxt_FileRename                ;// _T("修改文件名称");
CString g_sLangID_ImportFile                 ;// _T("sImportFile");
CString g_sLangTxt_ImportFile                ;// _T("导入文件");
CString g_sLangID_ExportFile                 ;// _T("sExportFile");
CString g_sLangTxt_ExportFile                ;// _T("导出文件");
CString g_sLangID_DeleteDirectory            ;// _T("sDeleteDirectory");
CString g_sLangTxt_DeleteDirectory           ;// _T("删除目录");
CString g_sLangID_DirectoryRename            ;// _T("sDirectoryRename");
CString g_sLangTxt_DirectoryRename           ;// _T("修改目录名称");
CString g_sLangID_FileCover                  ;// _T("sFileCover");
CString g_sLangTxt_FileCover                 ;// _T("覆盖文件");
CString g_sLangID_ExiSaNameFileCov           ;// _T("sExiSaNameFileCov");
CString g_sLangTxt_ExiSaNameFileCov          ;// _T("存在同名称的文件【%s】,覆盖吗？");
CString g_sLangID_ExiFileOvwt                ;// _T("sExiFileOvwt");
CString g_sLangTxt_ExiFileOvwt               ;// _T("文件【%s】已经存在,覆盖吗？");
CString g_sLangID_Message                    ;// _T("sMessage");
CString g_sLangTxt_Message                   = _T("提示");                   ;// _T("提示");
CString g_sLangID_SureDeleFile               ;// _T("sSureDeleFile");
CString g_sLangTxt_SureDeleFile              ;// _T("你确实要删除文件【%s】吗");
CString g_sLangID_ExiSaNameFile              ;// _T("sExiSaNameFile");
CString g_sLangTxt_ExiSaNameFile             ;// _T("存在同名称的文件夹【%s】");
CString g_sLangID_ExiSmNmFile3               ;// _T("sExiSmNmFile3");
CString g_sLangTxt_ExiSmNmFile3              ;// _T("存在同名称的文件【%s】");
CString g_sLangID_ExiSmNmFile2               ;// _T("sExiSmNmFile2");
CString g_sLangTxt_ExiSmNmFile2              ;// _T("文件夹【%s】存在同名称的文件【%s】");
CString g_sLangID_ChoImpFile                 ;// _T("sChoImpFile");
CString g_sLangTxt_ChoImpFile                ;// _T("选择导入的配置文件夹");
CString g_sLangID_ExpFileFin                 ;// _T("sExpFileFin");
CString g_sLangTxt_ExpFileFin                ;// _T("导出目标文件夹【%s】完成");
CString g_sLangID_TargFolderExist            ;// _T("sTargFolderExist");
CString g_sLangTxt_TargFolderExist           ;// _T("目标文件夹【%s】已经存在");
CString g_sLangID_ChoFoldExDir               ;// _T("sChoFoldExDir");
CString g_sLangTxt_ChoFoldExDir              ;// _T("选择配置文件夹导出目标目录");
CString g_sLangID_SureDeleFold               ;// _T("sSureDeleFold");
CString g_sLangTxt_SureDeleFold              ;// _T("确实要删除文件夹【%s】吗？");
CString g_sLangID_DeleFold                   ;// _T("sDeleFold");
CString g_sLangTxt_DeleFold                  ;// _T("删除文件夹将删除此文件夹及其下的全部文件及文件夹。\r\n确实要删除文件夹【%s】吗？");
CString g_sLangID_FoldCoverFold              ;// _T("sFoldCoverFold");
CString g_sLangTxt_FoldCoverFold             ;// _T("文件夹【%s】包含子文件夹或者文件\r\n请先删除子文件夹或者文件，然后再删除目录");
CString g_sLangID_ConfigFileManag            ;// _T("sConfigFileManag");
CString g_sLangTxt_ConfigFileManag           ;// _T("IEC61850配置文件管理");

CString g_sLangID_AtsPubFileManag            ;// _T("sAtsPubFileManag");
CString g_sLangTxt_AtsPubFileManag           ;// _T("自动测试文件发布管理");
CString g_sLangID_AddPubFile				;// _T("sAddPubFile");
CString g_sLangTxt_AddPubFile				;// _T("添加发布");
CString g_sLangID_ModifyPubFile				;// _T("sModifyPubFile");
CString g_sLangTxt_ModifyPubFile			;// _T("修改发布");
CString g_sLangID_DeletePubFile				;// _T("sDeletePubFile");
CString g_sLangTxt_DeletePubFile			;// _T("删除发布");

//故障、通用、结果参数
CString g_sLangID_FaultParameter            ;// _T("sFaultParameter");
CString g_sLangTxt_FaultParameter           ;// _T("故障参数");
CString g_sLangID_GeneralParameter          ;// _T("sGeneralParameter");
CString g_sLangTxt_GeneralParameter         ;// _T("通用参数");
CString g_sLangID_ResultParameter           ;// _T("sResultParameter");
CString g_sLangTxt_ResultParameter          ;// _T("结果参数");
CString g_sLangID_AppBaseParameter           ;// _T("sAppBaseParameter");
CString g_sLangTxt_AppBaseParameter          ;// _T("底层参数");

CString g_sLangID_ArbitrElement             ;// _T("sArbitrElement");
CString g_sLangTxt_ArbitrElement            ;// _T("任意元素");
CString g_sLangID_SpecifiedElement          ;// _T("sSpecifiedElement");
CString g_sLangTxt_SpecifiedElement         ;// _T("指定的元素");
CString g_sLangID_SequDefinElemIn           ;// _T("sSequDefinElemIn");
CString g_sLangTxt_SequDefinElemIn          ;// _T("序列定义中的元素");
CString g_sLangID_SequDefinElemOut          ;// _T("sSequDefinElemOut");
CString g_sLangTxt_SequDefinElemOut         ;// _T("序列定义之外的元素");
CString g_sLangID_ReferElements             ;// _T("sReferElements");
CString g_sLangTxt_ReferElements            ;// _T("引用元素");
CString g_sLangID_Values                     ;// _T("sValues");
CString g_sLangTxt_Values                    ;// _T("值");
CString g_sLangID_Time                      ;// _T("sTime");
CString g_sLangTxt_Time                     ;// _T("时间");
CString g_sLangID_Integer                   ;// _T("sInteger");
CString g_sLangTxt_Integer                  ;// _T("整数");
CString g_sLangID_FloatNumber               ;// _T("sFloatNumber");
CString g_sLangTxt_FloatNumber              ;// _T("浮点数");
CString g_sLangID_CharacterString           ;// _T("sCharacterString");
CString g_sLangTxt_CharacterString          ;// _T("字符串");
CString g_sLangID_Equal                     ;// _T("sEqual");
CString g_sLangTxt_Equal                    ;// _T("等于");
CString g_sLangID_LessThan                  ;// _T("sLessThan");
CString g_sLangTxt_LessThan                 ;// _T("小于");
CString g_sLangID_LessOrEqual               ;// _T("sLessOrEqual");
CString g_sLangTxt_LessOrEqual              ;// _T("小于等于");
CString g_sLangID_MoreThan                  ;// _T("sMoreThan");
CString g_sLangTxt_MoreThan                 ;// _T("大于");
CString g_sLangID_MoreOrEqual               ;// _T("sMoreOrEqual");
CString g_sLangTxt_MoreOrEqual              ;// _T("大于等于");
CString g_sLangID_NotEqual                  ;// _T("sNotEqual");
CString g_sLangTxt_NotEqual                 ;// _T("不等于");
CString g_sLangID_CharStringIncl            ;// _T("sCharStringIncl");
CString g_sLangTxt_CharStringIncl           ;// _T("字符串包含");
CString g_sLangID_CharStringNIncl           ;// _T("sCharStringNIncl");
CString g_sLangTxt_CharStringNIncl          ;// _T("字符串不包含");
CString g_sLangID_NumberRange               ;// _T("sNumberRange");
CString g_sLangTxt_NumberRange              ;// _T("数值范围");
CString g_sLangID_BoundNumRange             ;// _T("sBoundNumRange");
CString g_sLangTxt_BoundNumRange            ;// _T("数值范围带边界");
CString g_sLangID_DataVarAss                ;// _T("sDataVarAss");
CString g_sLangTxt_DataVarAss               ;// _T("数据变量赋值");
CString g_sLangID_PropertyID                ;// _T("sPropertyID");
CString g_sLangTxt_PropertyID               ;// _T("属性ID");
CString g_sLangID_DataType                  ;// _T("sDataType");
CString g_sLangTxt_DataType                 ;// _T("数据类型");
CString g_sLangID_FunctionalSymbol          ;// _T("sFunctionalSymbol");
CString g_sLangTxt_FunctionalSymbol         ;// _T("操作符号");
CString g_sLangID_Data2                     ;// _T("sData2 ");
CString g_sLangTxt_Data2                    ;// _T("数据2");
CString g_sLangID_ResultVariable            ;// _T("sResultVariable");
CString g_sLangTxt_ResultVariable           ;// _T("结果变量");
CString g_sLangID_GnrtFileNm                ;// _T("sGnrtFileNm");
CString g_sLangTxt_GnrtFileNm               ;// _T("组合生成文件名称");
CString g_sLangID_OrgnFileNm                ;// _T("sOrgnFileNm");
CString g_sLangTxt_OrgnFileNm               ;// _T("原文件名称");
CString g_sLangID_TgetFileNm                ;// _T("sTgetFileNm");
CString g_sLangTxt_TgetFileNm               ;// _T("目标文件名称");

CString g_sLangID_TraProtocol               ;// _T("sTraProtocol");
CString g_sLangTxt_TraProtocol              ;// _T("传统规约");
CString g_sLangID_61850Protocol             ;// _T("s61850Protocol");
CString g_sLangTxt_61850Protocol            ;// _T("61850规约");
CString g_sLangID_None                      ;// _T("sNone");
CString g_sLangTxt_None                     ;// _T("无");

CString g_sLangID_OverWrite                 ;// _T("sOverWrite");
CString g_sLangTxt_OverWrite                ;// _T("覆盖");
CString g_sLangID_FilePasteOprt             ;// _T("sFilePasteOprt");
CString g_sLangTxt_FilePasteOprt            ;// _T("文件粘贴：操作处理");
CString g_sLangID_SelFolder                 ;// _T("sSelFolder");
CString g_sLangTxt_SelFolder                ;// _T("选择文件夹");
CString g_sLangID_FileName                  ;// _T("sFileName");
CString g_sLangTxt_FileName                 ;// _T("文件名");
CString g_sLangID_NewFolder                 ;// _T("sNewFolder");
CString g_sLangTxt_NewFolder                ;// _T("新建文件夹");
CString g_sLangID_FolderNmMdf               ;// _T("sFolderNmMdf");
CString g_sLangTxt_FolderNmMdf              ;// _T("文件夹名称修改");
//
CString g_sLangID_NotAuthorized               ;// _T("sNotAuthorized");
CString g_sLangTxt_NotAuthorized              ;// _T("你使用的系统没有授权");
// CString g_sLangID_AuthorizedUserUnit               ;// _T("sAuthorizedUserUnit");
// CString g_sLangTxt_AuthorizedUserUnit              ;// _T("版权所有：%s      授权用户单位：%s     授权用户名：%s");
CString g_sLangID_NotAuthorized2               ;// _T("sNotAuthorized2");
CString g_sLangTxt_NotAuthorized2              ;// _T("没有授权");
CString g_sLangID_Close                ;// _T("sClose");
CString g_sLangTxt_Close               ;// _T("关闭");
CString g_sLangID_CloseTip                ;// _T("sCloseTip");
CString g_sLangTxt_CloseTip               ;// _T("关闭活动文档\n关闭");
CString g_sLangID_DataSets                ;// _T("sDataSets");
CString g_sLangTxt_DataSets               ;// _T("数据集");
CString g_sLangID_EquipDataModel                ;// _T("sEquipDataModel");
CString g_sLangTxt_EquipDataModel               ;// _T("设备数据模型");
CString g_sLangID_DevAtrbDefin                ;// _T("sDevAtrbDefin");
CString g_sLangTxt_DevAtrbDefin               ;// _T("设备属性定义");
CString g_sLangID_LogicdevCPU                ;// _T("sLogicdevCPU");
CString g_sLangTxt_LogicdevCPU               ;// _T("逻辑设备(CPU)");

CString g_sLangID_LogicDevice ;// _T("sLogicDevice"); //逻辑设备
CString g_sLangTxt_LogicDevice ;// _T("逻辑设备");
CString g_sLangID_LogicDeviceMap ;// _T("sLogicDeviceMap"); //逻辑设备MAP
CString g_sLangTxt_LogicDeviceMap ;// _T("逻辑设备映射");
CString g_sLangID_DataSetsMap ;// _T("sDataSetsMap"); //数据集
CString g_sLangTxt_DataSetsMap ;// _T("数据集映射");

CString g_sLangID_ParaTypeGroup                ;// _T("sParaTypeGroup");
CString g_sLangTxt_ParaTypeGroup               ;// _T("参数类型【%s】组必须有一组");
CString g_sLangID_NoParaTypeGroup                ;// _T("sNoParaTypeGroup");
CString g_sLangTxt_NoParaTypeGroup               ;// _T("不存在参数类型为【%s】的组");
CString g_sLangID_DevDataFile                ;// _T("sDevDataFile");
CString g_sLangTxt_DevDataFile                ;// _T("设备数据模型文件(*.xml)|*.xml||");
CString g_sLangID_RightsReserved                ;// _T("sRightsReserved");
CString g_sLangTxt_RightsReserved               ;// _T("版权所有：");
CString g_sLangID_LicensedTo                ;// _T("sLicensedTo");
CString g_sLangTxt_LicensedTo               ;// _T("授权给：");
CString g_sLangID_DataTypeUnExist                ;// _T("sDataTypeUnExist");
CString g_sLangTxt_DataTypeUnExist               ;// _T("Row;//%d  Col;//%d  数据类型对象不存在");
CString g_sLangID_Sizes                ;// _T("sSizes");
CString g_sLangTxt_Sizes               ;// _T("号");
CString g_sLangID_SourceDataObject                ;// _T("sSourceDataObject");
CString g_sLangTxt_SourceDataObject               ;// _T("源数据对象");
CString g_sLangID_MatchDataObject                ;// _T("sMatchDataObject");
CString g_sLangTxt_MatchDataObject                ;// _T("匹配数据对象");
CString g_sLangID_SelMatchDataObject                ;// _T("sSelMatchDataObject");
CString g_sLangTxt_SelMatchDataObject               ;// _T("选择匹配的数据对象");

CString g_sLangID_USBKey                ;// _T("sUSBKey");
CString g_sLangTxt_USBKey               ;// _T("请插入授权加密狗！");
CString g_sLangID_USBKeyUpdate                ;// _T("sUSBKeyUpdate");
CString g_sLangTxt_USBKeyUpdate               ;// _T("授权加密狗驱动程序版本过低，请更新驱动程序！");
CString g_sLangID_NoUSBkey                ;// _T("sNoUSBkey");
CString g_sLangTxt_NoUSBkey                ;// _T("没有安装授权加密狗驱动程序，请安装驱动程序！");
CString g_sLangID_SystemError                ;// _T("sSystemError");
CString g_sLangTxt_SystemError               ;// _T("系统错误！");
CString g_sLangID_SystemError2                ;// _T("sSystemError2");
CString g_sLangTxt_SystemError2              ;// _T("系统错误：HASP_INV_HND：Invalid login handle passed to function");
CString g_sLangID_SystemError3                ;// _T("sSystemError3");
CString g_sLangTxt_SystemError3               ;// _T("系统错误：HASP_INV_FILEID：Specified File ID not recognized by API");
CString g_sLangID_SystemError4                ;// _T("sSystemError4");
CString g_sLangTxt_SystemError4               ;// _T("系统错误：HASP_MEM_RANGE：Request exceeds memory range of a Sentinel file");
// CString g_sLangID_RightReservedS                ;// _T("sRightReservedS");
// CString g_sLangTxt_RightReservedS               ;// _T("版权所有：%s");
CString g_sLangID_SystemDevelop                ;// _T("sSystemDevelop");
CString g_sLangTxt_SystemDevelop              ;// _T("系统开发");
CString g_sLangID_UserName                ;// _T("sUserName");
CString g_sLangTxt_UserName               ;// _T("使用用户");
CString g_sLangID_ClientUnit                ;// _T("sClientUnit");
CString g_sLangTxt_ClientUnit               ;// _T("客户单位");
CString g_sLangID_ServerLicense                ;// _T("sServerLicense");
CString g_sLangTxt_ServerLicense               ;// _T("服务器授权");
CString g_sLangID_ServerLicense2                ;// _T("sServerLicense2");
CString g_sLangTxt_ServerLicense2               ;// _T("从服务器获取授权信息，请稍候....");
CString g_sLangID_LicenseCommun                ;// _T("sLicenseCommun");
CString g_sLangTxt_LicenseCommun               ;// _T("与授权服务器通信超时，请确保网络连接和服务器配置正确！");
CString g_sLangID_TestInstSel              ;// _T("sTestInstSel");
CString g_sLangTxt_TestInstSel             ;// _T("测试仪选择");
CString g_sLangID_AddScriptFail              ;// _T("sAddScriptFail");
CString g_sLangTxt_AddScriptFail             ;// _T("加载功能脚本文件[%s]失败");
CString g_sLangID_TestFctnUnExist              ;// _T("sTestFctnUnExist");
CString g_sLangTxt_TestFctnUnExist             ;// _T("测试功能\"%s\"不存在");
CString g_sLangID_IEC61850SetFile              ;// _T("sIEC61850SetFile");
CString g_sLangTxt_IEC61850SetFile             ;// _T("IEC61850配置文件");
CString g_sLangID_ComtradeFile              ;// _T("sComtradeFile");
CString g_sLangTxt_ComtradeFile             ;// _T("COMTRADE录波文件");
CString g_sLangID_TestFctnFile              ;// _T("sTestFctnFile");
CString g_sLangTxt_TestFctnFile             ;// _T("测试功能标准文件");
CString g_sLangID_CommunStraFile              ;// _T("sCommunStraFile");
CString g_sLangTxt_CommunStraFile             ;// _T("通讯标准文件");
CString g_sLangID_Number2              ;// _T("sNumber2");
CString g_sLangTxt_Number2             ;// _T("编号/条目号");
CString g_sLangID_ALreadyExist              ;// _T("sALreadyExist");
CString g_sLangTxt_ALreadyExist             ;// _T("【%s】在【%s】已经存在");
CString g_sLangID_MdtInsert            ;// _T("sMdtInsert");
CString g_sLangTxt_MdtInsert           ;// _T("插入");
CString g_sLangID_UpMove            ;// _T("sUpMove");
CString g_sLangTxt_UpMove           ;// _T("上移");
CString g_sLangID_DownMove            ;// _T("sDownMove");
CString g_sLangTxt_DownMove           ;// _T("下移");
CString g_sLangID_Unit                 ;// _T("sUnit");
CString g_sLangTxt_Unit             ;// _T("单位");
CString g_sLangID_MinValue                 ;// _T("sMinValue");
CString g_sLangTxt_MinValue             ;// _T("最小值");
CString g_sLangID_MaxValue                 ;// _T("sMaxValue");
CString g_sLangTxt_MaxValue             ;// _T("最大值");
CString g_sLangID_Step                 ;// _T("sStep");
CString g_sLangTxt_Step            ;// _T("步长");
CString g_sLangID_Nonstandard                 ;// _T("sNonstandard");
CString g_sLangTxt_Nonstandard              ;// _T("非标");
CString g_sLangID_StatePower                 ;// _T("sStatePower");
CString g_sLangTxt_StatePower              ;// _T("国电南京自动化股份有限公司");
CString g_sLangID_Bphase                 ;// _T("sBphase");
CString g_sLangTxt_Bphase              ;// _T("B相");
CString g_sLangID_Aphase                 ;// _T("sAphase");
CString g_sLangTxt_Aphase              ;// _T("A相");
CString g_sLangID_Cphase                ;// _T("sCphase");
CString g_sLangTxt_Cphase              ;// _T("C相");
CString g_sLangID_ABphase                 ;// _T("sABphase");
CString g_sLangTxt_ABphase              ;// _T("AB相");
CString g_sLangID_BCphase                 ;// _T("sBCphase");
CString g_sLangTxt_BCphase              ;// _T("BC相");
CString g_sLangID_CAphase                 ;// _T("sCAphase");
CString g_sLangTxt_CAphase              ;// _T("CA相");
CString g_sLangID_Application                 ;// _T("sApplication");
CString g_sLangTxt_Application              ;// _T("应用程序向导生成的本地应用程序");
CString g_sLangID_FixedValueRegion                 ;// _T("sFixedValueRegion");
CString g_sLangTxt_FixedValueRegion              ;// _T("定值区");
CString g_sLangID_Modify               ;// _T("sModify");
CString g_sLangTxt_Modify                  ;// _T("修改");
CString g_sLangID_ItemPrtcFile               ;// _T("sItemPrtcFile");
CString g_sLangTxt_ItemPrtcFile                  ;// _T("设备点表文件(*.xml)|*.xml||");
CString g_sLangID_SelDevDaModFile     ;// _T("sSelDevDaModFile");
CString g_sLangTxt_SelDevDaModFile    ;// _T("选择设备数据模型文件");
CString g_sLangID_TemDataFileChange     ;// _T("sTemDataFileChange");
CString g_sLangTxt_TemDataFileChange    ;// _T("模板设备数据模型替换映射配置文件");
CString g_sLangID_ConServerFail     ;// _T("sConServerFail");
CString g_sLangTxt_ConServerFail    ;// _T("连接服务器【%s】【%d】失败");
CString g_sLangID_ConServerSucc     ;//= _T("sConServerSucc");
CString g_sLangTxt_ConServerSucc    ;//= _T("连接服务器【%s】【%d】成功");
CString g_sLangID_UserUnExist     ;// _T("sUserUnExist");
CString g_sLangTxt_UserUnExist    ;// _T("用户名不存在");
CString g_sLangID_PasswordIncorrect     ;// _T("sPasswordIncorrect");
CString g_sLangTxt_PasswordIncorrect   ;// _T("密码不正确");
CString g_sLangID_LoginError     ;// _T("sLoginError");
CString g_sLangTxt_LoginError    ;// _T("登录错误");
CString g_sLangID_StopTest                 ;// _T("sStopTest");
CString g_sLangTxt_StopTest                ;// _T("停止测试");
CString g_sLangID_StartTest                 ;// _T("sStartTest");
CString g_sLangTxt_StartTest                ;// _T("开始测试");
CString g_sLangID_ExportReport         ;// _T("sExportReport");
CString g_sLangTxt_ExportReport        ;// _T("导出报告");
CString g_sLangID_ExportReportBatch         ;// _T("sExportReportBatch");
CString g_sLangTxt_ExportReportBatch        ;// _T("批量导出报告");
CString g_sLangID_StatusBar                ;// _T("sStatusBar");
CString g_sLangTxt_StatusBar               ;// _T("状态栏");
CString g_sLangID_TestStop2                            ;// _T("sTestStop2");
CString g_sLangTxt_TestStop2                           ;// _T("连接设备失败，测试终止");
CString g_sLangID_DataOpreation                           ;// _T("sDataOpreation");
CString g_sLangTxt_DataOpreation                           ;// _T("数据操作");

CString g_sLangID_OpenTip             ;// _T("sOpenTip");
CString g_sLangTxt_OpenTip            ;// _T("打开");
CString g_sLangID_ModelTestTip             ;// _T("sModelTestTip");
CString g_sLangTxt_ModelTestTip            ;// _T("开始测试两个数设备数据模型\n开始测试");
CString g_sLangID_DevModelTestTip             ;// _T("sDevModelTestTip");
CString g_sLangTxt_DevModelTestTip            ;// _T("从装置枚举数据模型，然后进行测试\n装置模型测试");
CString g_sLangID_StopTestTip             ;// _T("sStopTestTip");
CString g_sLangTxt_StopTestTip            ;// _T("停止测试\n停止测试");
CString g_sLangID_ExportReportTip             ;// _T("sExportReportTip");
CString g_sLangTxt_ExportReportTip            ;// _T("导出报告\n导出报告");
CString g_sLangID_SaveFileTip             ;// _T("sSaveFileTip");
CString g_sLangTxt_SaveFileTip            ;// _T("保存设备数据模型映射关系文件\n保存文件");
CString g_sLangID_OutputBarTip             ;// _T("sOutputBarTip");
CString g_sLangTxt_OutputBarTip            ;// _T("显示或隐藏输出栏\n切换输出栏");
CString g_sLangID_StatusBarTip             ;// _T("sStatusBarTip");
CString g_sLangTxt_StatusBarTip            ;// _T("显示或隐藏状态栏\n切换状态栏");
CString g_sLangID_CompareDataTip             ;// _T("sCompareDataTip");
CString g_sLangTxt_CompareDataTip            ;// _T("比较ID\n比较ID");
CString g_sLangID_AboutTip             ;// _T("sAboutTip");
CString g_sLangTxt_AboutTip            ;// _T("显示程序信息、版本号和版权\n关于");
CString g_sLangID_TestMain             ;// _T("sTestMain");
CString g_sLangTxt_TestMain            ;// _T("测试主页(&H)");
CString g_sLangID_ModelTest             ;// _T("sModelTest");
CString g_sLangTxt_ModelTest            ;// _T("模型测试");
CString g_sLangID_ProtocolTest             ;// _T("sProtocolTest");
CString g_sLangTxt_ProtocolTest            ;// _T("规约测试");
CString g_sLangID_ModelFileTest             ;// _T("sModelFileTest");
CString g_sLangTxt_ModelFileTest            ;// _T("模型文件测试");
CString g_sLangID_DevModelTest             ;// _T("sDevModelTest");
CString g_sLangTxt_DevModelTest            ;// _T("装置模型测试");
CString g_sLangID_ResultOpera             ;// _T("sResultOpera");
CString g_sLangTxt_ResultOpera           ;// _T("结果操作");
CString g_sLangID_SaveFile             ;// _T("sSaveFile");
CString g_sLangTxt_SaveFile            ;// _T("保存映射文件");
CString g_sLangID_OutputBar             ;// _T("sOutputBar");
CString g_sLangTxt_OutputBar            ;// _T("输出栏");
CString g_sLangID_CompareData             ;// _T("sCompareData");
CString g_sLangTxt_CompareData            ;// _T("比较数据ID");
CString g_sLangID_CmpDataNameFull ;// _T("sCmpDataNameFull");//数据名称全字符串比较
CString g_sLangTxt_CmpDataNameFull ;// _T("名称全字符串比较");
CString g_sLangID_Browse             ;// _T("sBrowse");
CString g_sLangTxt_Browse            ;// _T("浏览");
CString g_sLangID_Home             ;// _T("sHome");
CString g_sLangTxt_Home            ;// _T("主页(H)");
CString g_sLangID_CreatDataMap             ;// _T("sCreatDataMap");
CString g_sLangTxt_CreatDataMap            ;// _T("创建数据映射");
CString g_sLangID_DeleteDataMap             ;// _T("sDeleteDataMap");
CString g_sLangTxt_DeleteDataMap            ;// _T("删除数据映射");
CString g_sLangID_CreatDataMap2             ;// _T("sCreatDataMap2");
CString g_sLangTxt_CreatDataMap2            ;// _T("创建数据集映射");
CString g_sLangID_DeleteDataMap2             ;// _T("sDeleteDataMap2");
CString g_sLangTxt_DeleteDataMap2            ;// _T("删除数据集映射");
CString g_sLangID_SelStdDataFile             ;// _T("sSelStdDataFile");
CString g_sLangTxt_SelStdDataFile            ;// _T("请选择标准设备数据模型文件");
CString g_sLangID_DataSetNoOnly             ;// _T("sDataSetNoOnly");
CString g_sLangTxt_DataSetNoOnly            ;// _T("数据集【%s】不唯一");
CString g_sLangID_User ;// _T("sUser");
CString g_sLangTxt_User ;// _T("用户");
CString g_sLangID_Module ;// _T("sModule");
CString g_sLangTxt_Module ;// _T("模块");
CString g_sLangID_RemotePort ;// _T("sRemotePort");
CString g_sLangTxt_RemotePort ;// _T("远程端口");
CString g_sLangID_LocalPort ;// _T("sLocalPort");
CString g_sLangTxt_LocalPort ;// _T("本地端口");
CString g_sLangID_State ;// _T("sState");
CString g_sLangTxt_State ;// _T("状态");
CString g_sLangID_ServerWorkPath ;// _T("sServerPath");
CString g_sLangTxt_ServerWorkPath ;// _T("服务器工作路径");

CString g_sLangID_New                                 ;// _T("sNew");
CString g_sLangTxt_New                                ;// _T("新建(N)");
CString g_sLangID_TemNew                                 ;// _T("sTemNew");
CString g_sLangTxt_TemNew                                ;// _T("新建模板");
CString g_sLangID_NewTip                                 ;// _T("sNewTip");
CString g_sLangTxt_NewTip                                ;// _T("创建新规约模板\n新建");
CString g_sLangID_OpenTips                                 ;// _T("sOpenTips");
CString g_sLangTxt_OpenTips                                ;// _T("打开现有规约模板\n打开");
CString g_sLangID_SaveTips                                 ;// _T("sSaveTips");
CString g_sLangTxt_SaveTips                                ;// _T("保存规约模板\n保存");
CString g_sLangID_SaveAsTips                                 ;// _T("sSaveAsTips");
CString g_sLangTxt_SaveAsTips                                ;// _T("用新名称保存规约模板\n另存为");
CString g_sLangID_RecentFile                                 ;// _T("sRecentFile");
CString g_sLangTxt_RecentFile                                ;// _T("最近使用的文档");

CString g_sLangID_TemplateDef                                 ;// _T("sTemplateDef");
CString g_sLangTxt_TemplateDef                                ;// _T("模板定义");
CString g_sLangID_TemplateProperty                                 ;// _T("sTemplateProperty");
CString g_sLangTxt_TemplateProperty                                ;// _T("模板属性");
CString g_sLangID_CommDef                                 ;// _T("sCommDef");
CString g_sLangTxt_CommDef                                ;// _T("通讯定义");
CString g_sLangID_InitDef                                 ;// _T("sInitDef");
CString g_sLangTxt_InitDef                                ;// _T("初始化定义");
CString g_sLangID_Exist                                 ;// _T("sExist");
CString g_sLangTxt_Exist                                ;// _T("【%s】已经存在");
CString g_sLangID_NoDataNotInsert                                 ;// _T("sNoDataNotInsert");
CString g_sLangTxt_NoDataNotInsert                                ;// _T("无数据，不能插入！");
CString g_sLangID_KeySameId                                 ;// _T("sKeySameId");
CString g_sLangTxt_KeySameId                                ;// _T("存在相同名称的关键字【%s】");
CString g_sLangID_Attention                                 ;// _T("sAttention");
CString g_sLangTxt_Attention                                ;// _T("注意");

CString g_sLangID_InitiaErrors                                 ;// _T("sInitiaErrors");
CString g_sLangTxt_InitiaErrors                                ;// _T("初始化错误");
CString g_sLangID_OtherStart                                 ;// _T("sOtherStart");
CString g_sLangTxt_OtherStart                                ;// _T("对方没有启动");
CString g_sLangID_OtherClose                                 ;// _T("sOtherClose");
CString g_sLangTxt_OtherClose                                ;// _T("对方已经关闭");
CString g_sLangID_ConnectRefuse                                 ;// _T("sConnectRefuse");
CString g_sLangTxt_ConnectRefuse                                ;// _T("连接的尝试被拒绝");
CString g_sLangID_AttemptOperate                                 ;// _T("sAttemptOperate");
CString g_sLangTxt_AttemptOperate                                ;// _T("在一个非套接字上尝试了一个操作");
CString g_sLangID_SpecificUse                                 ;// _T("sSpecificUse");
CString g_sLangTxt_SpecificUse                                ;// _T("特定的地址已在使用中");
CString g_sLangID_ConnectionClosed                                 ;// _T("sConnectionClosed");
CString g_sLangTxt_ConnectionClosed                                ;// _T("与主机的连接被关闭");
CString g_sLangID_GenericError                                 ;// _T("sGenericError");
CString g_sLangTxt_GenericError                                ;// _T("一般错误");
CString g_sLangID_Add             ;// _T("sAdd");
CString g_sLangTxt_Add             ;// _T("添加");
CString g_sLangID_NoDataChangeMsg             ;// _T("sNoDataChangeMsg");
CString g_sLangTxt_NoDataChangeMsg             ;// _T("没有注册节点[%d]数据改变消息");
CString g_sLangID_FileNameInclude             ;// _T("sFileNameInclude");
CString g_sLangTxt_FileNameInclude             ;// _T("文件名【%s】包含【%s】等非法字符");

CString g_sLangID_Add3             ;// _T("sAdd3");
CString g_sLangTxt_Add3             ;// _T("增加");
CString g_sLangID_Select                ;// _T("sSelect");
CString g_sLangTxt_Select                ;// _T("选择");
CString g_sLangID_Value                    ;// _T("sValue");
CString g_sLangTxt_Value                   ;// _T("数值");
CString g_sLangID_DefaultValue                    ;// _T("sDefaultValue");
CString g_sLangTxt_DefaultValue                   ;// _T("默认值");
CString g_sLangID_PrtcTempFile             ;// _T("sPrtcTempFile");
CString g_sLangTxt_PrtcTempFile            ;// _T("规约模板文件");
CString g_sLangID_PrtcTempFileMagn             ;// _T("sPrtcTempFileMagn");
CString g_sLangTxt_PrtcTempFileMagn            ;// _T("规约模板文件管理");
CString g_sLangID_PrtcProjectFile             ;// _T("sPrtcProjectFile");
CString g_sLangTxt_PrtcProjectFile            ;// _T("规约工程文件");
CString g_sLangID_ModelFile           ;// _T("sModelFile");
CString g_sLangTxt_ModelFile          ;// _T("模型文件");

CString g_sLangID_Version             ;// _T("sVersion");
CString g_sLangTxt_Version            ;// _T("版本");
CString g_sLangID_TimeLimit             ;// _T("sTimeLimit");
CString g_sLangTxt_TimeLimit            ;// _T("时限");
CString g_sLangID_ComparaObject             ;// _T("sComparaObject");
CString g_sLangTxt_ComparaObject           ;// _T("比较项");
CString g_sLangID_StandardValue             ;// _T("sStandardValue");
CString g_sLangTxt_StandardValue           ;// _T("标准值");
CString g_sLangID_TureValue             ;// _T("sTureValue");
CString g_sLangTxt_TureValue           ;// _T("实际值");
CString g_sLangID_Property             ;// _T("sProperty");
CString g_sLangTxt_Property           ;// _T("属性");
CString g_sLangID_UnStallWord             ;// _T("sUnStallWord");
CString g_sLangTxt_UnStallWord           ;// _T("没有安装Word");
CString g_sLangID_Title             ;// _T("sTitle");
CString g_sLangTxt_Title           ;// _T("标题 %d");
CString g_sLangID_ReName             ;// _T("sReName");
CString g_sLangTxt_ReName           ;// _T("重命名");
CString g_sLangID_UserUnits             ;// _T("sUserUnits");
CString g_sLangTxt_UserUnits           ;// _T("用户单位：");
CString g_sLangID_User2             ;// _T("sUser2");
CString g_sLangTxt_User2           ;// _T("用户：");
CString g_sLangID_Develop             ;// _T("sDevelop");
CString g_sLangTxt_Develop           ;// _T("开发：");

CString g_sLangID_Variable             ;// _T("sVariable");
CString g_sLangTxt_Variable            ;// _T("变量");
CString g_sLangID_DeleteFloder             ;// _T("sDeleteFloder");
CString g_sLangTxt_DeleteFloder            ;// _T("删除文件夹");
CString g_sLangID_SureDelFoldItem             ;// _T("sSureDelFoldItem");
CString g_sLangTxt_SureDelFoldItem            ;// _T("确定要删除文件夹 %s 及其子项目吗?");
CString g_sLangID_Size2             ;// _T("sSize2");
CString g_sLangTxt_Size2            ;// _T("大小");
CString g_sLangID_ModiftyFileNameFail             ;// _T("sModiftyFileNameFail");
CString g_sLangTxt_ModiftyFileNameFail            ;// _T("修改文件名称失败");


CString g_sLangID_SCDFiles           ;//= _T("sSCDFiles");
CString g_sLangTxt_SCDFiles           ;//= _T("SCD文件");
CString g_sLangID_RecordFiles           ;// = _T("sRecordFiles");
CString g_sLangTxt_RecordFiles            ;// = _T("录波文件");
CString g_sLangID_TemplateFiles           ;// = _T("sTemplateFiles");
CString g_sLangTxt_TemplateFiles          ;//  = _T("模板文件");
CString g_sLangID_WorkspaceFiles            ;// = _T("sWorkspaceFiles");
CString g_sLangTxt_WorkspaceFiles           ;// = _T("报告文件");
CString g_sLangID_IEC61850SetFiles          ;//  = _T("sIEC61850SetFiles");
CString g_sLangTxt_IEC61850SetFiles          ;//  = _T("IEC61850配置文件");
CString g_sLangID_PcapFiles           ;// = _T("sPcapFiles");
CString g_sLangTxt_PcapFiles          ;//  = _T("Pcap文件");
CString g_sLangID_PrintScreen         ;//   = _T("sPrintScreen");
CString g_sLangTxt_PrintScreen        ;//    = _T("截屏文件夹");
CString g_sLangID_Others          ;//  = _T("sOthers");
CString g_sLangTxt_Others          ;//  = _T("其他");
CString g_sLangID_SavePcapFiles          ;//  = _T("sSavePcapFiles");
CString g_sLangTxt_SavePcapFiles         ;//  = _T("保存Pcap文件");
CString g_sLangID_SavePrintScreen       ;//    = _T("sSavePrintScreen");
CString g_sLangTxt_SavePrintScreen        ;//    = _T("保存截屏图片");
CString g_sLangID_OtherTypeFiles          ;//  = _T("sOtherTypeFiles");
CString g_sLangTxt_OtherTypeFiles        ;//    = _T("其他类型文件");


CString g_sLangID_Output             ;// _T("sOutput");
CString g_sLangTxt_Output            ;// _T("输出");
CString g_sLangID_ConfirmDel             ;// _T("sConfirmDel");
CString g_sLangTxt_ConfirmDel            ;// _T("确定要删除【%s】吗？");
CString g_sLangID_NoSave             ;// _T("sNoSave");
CString g_sLangTxt_NoSave             ;// _T("文件【%s】没有保存，保存吗？");
CString g_sLangID_Increase                ;// _T("sIncrease"); 
CString g_sLangTxt_Increase               ;// _T("递增");      
CString g_sLangID_Decrease                ;// _T("sDecrease"); 
CString g_sLangTxt_Decrease              ;// _T("递减");  

CString g_sLangID_Export                   ;// _T("sExport");
CString g_sLangTxt_Export                  ;// _T("导出");
CString g_sLangID_Import                   ;// _T("sImport");
CString g_sLangTxt_Import                  ;// _T("导入");
CString g_sLangID_ClcltFmla             ;// _T("sClcltFmla");
CString g_sLangTxt_ClcltFmla             ;// _T("计算公式");
CString g_sLangID_GuideWizardFile       ;// _T("sGuideWizardFile");
CString g_sLangTxt_GuideWizardFile      ;// _T("作业指导书向导文件");

CString g_sLangID_IecConfigFile            ;// _T("sIecConfigFile");
CString g_sLangTxt_IecConfigFile           ;// _T("IEC61850配置文件");
CString g_sLangID_DvIecConfigFile            ;// _T("sDvIecConfigFile");
CString g_sLangTxt_DvIecConfigFile           ;// _T("智能设备测试仪IEC61850配置文件");
CString g_sLangID_DvIecConfigFileMngr            ;// _T("sDvIecConfigFileMngr");
CString g_sLangTxt_DvIecConfigFileMngr           ;// _T("智能设备测试仪IEC61850配置文件管理");

CString g_sLangID_NoTitle           ;// _T("sNoTitle ");
CString g_sLangTxt_NoTitle           ;// _T("无标题");
CString g_sLangID_FileNotExist      ;// _T("sFileNotExist");
CString g_sLangTxt_FileNotExist     ;// _T("文件【%s】不存在");

CString g_sLangID_YunDownFileFaild ;// _T("sYunDownFileFaild");//从云端下载文件失败
CString g_sLangTxt_YunDownFileFaild ;// _T("从云端下载文件失败");

CString g_sLangID_Login                    ;// _T("sLogin");
CString g_sLangTxt_Login                   ;// _T("登录");
CString g_sLangID_UpLoad                   ;// _T("sUpLoad");
CString g_sLangTxt_UpLoad                  ;// _T("上传");
CString g_sLangID_DownLoad                 ;// _T("sDownLoad");
CString g_sLangTxt_DownLoad                ;// _T("下载");

CString g_sLangID_TestItemParEdit       ;// _T("sTestItemParEdi");
CString g_sLangTxt_TestItemParEdit      ;// _T("测试项目参数编辑");
CString g_sLangID_ParaName                ;// _T("sParaName");
CString g_sLangTxt_ParaName                ;// _T("参数名称");
CString g_sLangID_ParaValue                ;// _T("sParaValue");
CString g_sLangTxt_ParaValue              ;// _T("参数值");

CString g_sLangID_GlobalData                    ;// _T("sGlobalData");
CString g_sLangTxt_GlobalData                   ;// _T("全局数据");
CString g_sLangID_TestAppDef                    ;// _T("sTestAppDef");
CString g_sLangTxt_TestAppDef                   ;// _T("测试仪定义");
CString g_sLangID_RepeatResultInfo                    ;// _T("sRepeatResultInfo");
CString g_sLangTxt_RepeatResultInfo                   ;// _T("计算结果:");

CString g_sLangID_Clear                    ;// _T("sClear");
CString g_sLangTxt_Clear                   ;// _T("清除");
CString g_sLangID_SyntaxCheck                    ;// _T("sSyntaxCheck");
CString g_sLangTxt_SyntaxCheck                   ;// _T("语法检查");
CString g_sLangID_SyntaxCheckTips                    ;// _T("sSyntaxCheckTips");
CString g_sLangTxt_SyntaxCheckTips                   ;// _T("语法检查\n语法检查");

CString g_sLangID_OutputWnd                ;//= _T("sOutputWnd");
CString g_sLangTxt_OutputWnd               ;//= _T("输出窗口");

//2023-03-12  lijunqing 从MMS和ATS移动到此处
CString g_sLangID_DataSet                 ;//= _T("sDataSet");
CString g_sLangTxt_DataSet            ;//= _T("数据集");

//2023-3-15 lijunqing from 61850cfg and autotest
CString g_sLangID_Quit                     ;  //= _T("sQuit");
CString g_sLangTxt_Quit                    ;  //= _T("退出");
CString g_sLangID_QuitTip                  ;  //= _T("sQuitTip");
CString g_sLangTxt_QuitTip                 ;  //= _T("退出应用程序；提示保存文档\n退出");

//2024-1-4 shaolei
CString g_sLangID_Voltage             ;    //= _T("sVoltage");
CString g_sLangTxt_Voltage            ;    //= _T("电压");
CString g_sLangID_Current             ;    //= _T("sCurrent");
CString g_sLangTxt_Current             ;    //= _T("电流");
CString g_sLangID_ActivePower             ;    //= _T("sActivePower");
CString g_sLangTxt_ActivePower             ;    //= _T("有功功率");
CString g_sLangID_ReactivePower             ;    //= _T("sReactivePower");
CString g_sLangTxt_ReactivePower             ;    //= _T("无功功率");
CString g_sLangID_Frequency             ;    //= _T("sFrequency");
CString g_sLangTxt_Frequency             ;    //= _T("频率(Hz)");
CString g_sLangID_PowerFactor             ;    //= _T("sPowerFactor");
CString g_sLangTxt_PowerFactor             ;    //= _T("功率因数");

CString g_sLangID_Native_StartOutput;		// = _T("Native_StartOutput")
CString g_sLangTxt_Native_StartOutput;		// = _T("开始输出")
CString g_sLangID_Native_TestAnomalies;     //= _T("Native_TestAnomalies");
CString g_sLangTxt_Native_TestAnomalies;    //= _T("测试异常");
CString g_sLangID_Native_RelieveTestAnomalies; //= _T("Native_RelieveTestAnomalies")
CString g_sLangTxt_Native_RelieveTestAnomalies; //= _T("解除测试异常")
CString g_sLangID_Native_StateSwitch;        //= _T("Native_StateSwitch");
CString g_sLangTxt_Native_StateSwitch;       //= _T("状态切换");
CString g_sLangID_Native_SupDCSwitch;        //= _T("Native_SupDCSwitch");
CString g_sLangTxt_Native_SupDCSwitch;       //= _T("辅助直流切换");
CString g_sLangID_Native_BinDisPlace;        // = _T("Native_BinDisPlace");
CString g_sLangTxt_Native_BinDisPlace;       //= _T("开入变位");
CString g_sLangID_Native_BoutDisPlace;       //= _T("Native_BinDisPlace");
CString g_sLangTxt_Native_BoutDisPlace;      //= _T("开出变位");
CString g_sLangID_Native_ParaUpdata;         //= _T("Native_ParaUpdata");
CString g_sLangTxt_Native_ParaUpdata;        //= _T("参数更新");

//2024-9-10 wuxinyi 
CString g_sLangID_Native_Port;		// = _T("Native_Port")
CString g_sLangTxt_Native_Port;        //= _T("口");

CString g_sLangID_TestInstrumentConfig;
CString g_sLangTxt_TestInstrumentConfig;
CString g_sLangID_ScanLANTestInstrument;
CString g_sLangTxt_ScanLANTestInstrument;
CString g_sLangID_DirectConfigRemoteInstrument;
CString g_sLangTxt_DirectConfigRemoteInstrument;
CString g_sLangID_ScanRemoteTestInstrument;
CString g_sLangTxt_ScanRemoteTestInstrument;
CString g_sLangID_Setup;
CString g_sLangTxt_Setup;
CString g_sLangID_Upgrade;
CString g_sLangTxt_Upgrade;
CString g_sLangID_EnablePUDA;
CString g_sLangTxt_EnablePUDA;
CString g_sLangID_EnableTestSvr;
CString g_sLangTxt_EnableTestSvr;
CString g_sLangID_TestInstrumentModel;
CString g_sLangTxt_TestInstrumentModel;
CString g_sLangID_TestInstrumentID;
CString g_sLangTxt_TestInstrumentID;
CString g_sLangID_CloudIP;
CString g_sLangTxt_CloudIP;
CString g_sLangID_CloudPort;
CString g_sLangTxt_CloudPort;
CString g_sLangID_TestInstrumentSerialNumber;
CString g_sLangTxt_TestInstrumentSerialNumber;
CString g_sLangID_Password;
CString g_sLangTxt_Password;
CString g_sLangID_Unit2;
CString g_sLangTxt_Unit2;
CString g_sLangID_Bind;
CString g_sLangTxt_Bind;
CString g_sLangID_Query;
CString g_sLangTxt_Query;
CString g_sLangID_TestInstrumentConnectionError;
CString g_sLangTxt_TestInstrumentConnectionError;
CString g_sLangID_CloudServerConnectionError;
CString g_sLangTxt_CloudServerConnectionError;
CString g_sLangID_IPIsEmpty;
CString g_sLangTxt_IPIsEmpty;
CString g_sLangID_ConnectionTestInstrumentFailed;
CString g_sLangTxt_ConnectionTestInstrumentFailed;
CString g_sLangID_MulticastInitSuccess;
CString g_sLangTxt_MulticastInitSuccess;
CString g_sLangID_MulticastInitFailed;
CString g_sLangTxt_MulticastInitFailed;
CString g_sLangID_MulticastInitBindSuccess;
CString g_sLangTxt_MulticastInitBindSuccess;
CString g_sLangID_Disconnection;
CString g_sLangTxt_Disconnection;
CString g_sLangID_CloudConnectionFailed;
CString g_sLangTxt_CloudConnectionFailed;
CString g_sLangID_TestInstrumentUserInfoError;
CString g_sLangTxt_TestInstrumentUserInfoError;
CString g_sLangID_Connect;
CString g_sLangTxt_Connect;
CString g_sLangID_StopScanning;
CString g_sLangTxt_StopScanning;
CString g_sLangID_Scanning;
CString g_sLangTxt_Scanning;
CString g_sLangID_NanjingEnergyCloud;
CString g_sLangTxt_NanjingEnergyCloud;
CString g_sLangID_TestInstrumentConfigFileNotFound;
CString g_sLangTxt_TestInstrumentConfigFileNotFound;
CString g_sLangID_OAClientInitFail;
CString g_sLangTxt_OAClientInitFail;
//2024-10-22 wuxinyi 
CString g_sLangID_ResultBar;//结果栏
CString g_sLangTxt_ResultBar;
CString g_sLangID_StatusLight;
CString g_sLangTxt_StatusLight;
CString g_sLangID_WinwordProcessWarning;
CString g_sLangTxt_WinwordProcessWarning;
CString g_sLangID_CloseProcessWarning;
CString g_sLangTxt_CloseProcessWarning;
