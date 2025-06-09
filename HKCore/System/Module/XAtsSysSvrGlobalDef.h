// XAtsSysSvrGlobalDef.h
//

#pragma once

#include "../../Module/API/GlobalConfigApi.h"
#include "../../Module/OSInterface/OSInterface.h"

#define XMODULE_ID_DvmTest            _T("DvmTest")
#define XMODULE_ID_DvmMap             _T("DvmMap")
// #define XMODULE_ID_AutoTest           _T("AutoTest")
#define XMODULE_ID_AutoTest           _T("SmartTest")
#define XMODULE_ID_VTerminalTest      _T("VTerminalTest")
#define XMODULE_ID_GuideBookDev       _T("GuideBookDev")
#define XMODULE_ID_ReportTemplateDev  _T("ReportTemplateDev")
#define XMODULE_ID_PpMmsEngine        _T("PpMmsEngine")
#define XMODULE_ID_PpDev              _T("PpDev")
#define XMODULE_ID_PpEngine           _T("PpEngine")
#define XMODULE_ID_StationTestMain    _T("StationTestMain")
#define XMODULE_ID_Iec61850Config    _T("Iec61850Config")
#define XMODULE_ID_SclFileRead    _T("SclFileRead")
#define XMODULE_ID_SclFileTest    _T("SclFileTest")
#define XMODULE_ID_ReportMerge    _T("ReportMerge")
#define XMODULE_ID_OAMngrClient    _T("OAMngrClient")

#define XMODULE_OPTR_DVM_BEGINTEST      _T("dvm-begin-test")
#define XMODULE_OPTR_DVM_FINISHTEST     _T("dvm-finish-test")
#define XMODULE_OPTR_DVM_FINISHCMP     _T("dvm-finish-cmp")
#define XMODULE_OPTR_DVM_FILEOPEN     _T("dvm-file-open")
#define XMODULE_OPTR_GBDEV_OPEN         _T("gbdev-open")
#define XMODULE_OPTR_GBDEV_CLOSE        _T("dbdev-close")
#define XMODULE_OPTR_RPTDEV_OPEN        _T("rptdev-open")
#define XMODULE_OPTR_RPTDEV_CLOSE       _T("rptdev-close")
#define XMODULE_OPTR_AUTOTEST_BEGINTEST _T("autotest-begin-test")
#define XMODULE_OPTR_AUTOTEST_FINISH    _T("autotest-finish-test")
#define XMODULE_OPTR_IEC61850CONFIG     _T("ieccfg-finish")
#define XMODULE_OPTR_SCLFILE_FINISHTEST     _T("sclfile-finish-test")//zhouhj 20180630 增加对SCL文件检测的处理部分

//2020-02-03 lijq
//SmartTest<<==>>GuideBookDev
//自动测试过程中，修改参数，更新到测试模板编辑中；测试模板编辑更新到自动测试中
#define XMODULE_OPTR_GET_ITEM_PARA      _T("get-item-para")
#define XMODULE_OPTR_SET_ITEM_PARA      _T("update-item-para")
//SmartTest==>>GuideBookDev，自动测试过程中，修改参数，更新到测试模板编辑中
#define XMODULE_OPTR_ATS_TEST_ITEM      _T("test-item")
#define XMODULE_OPTR_ATS_VIEW_ITEM_REPORT      _T("view-item-report")


#define XPARA_ID_GBXMLFILE  _T("gbxml-file")
#define XPARA_ID_XTESTDB_TASKS  _T("xtest-db-task")
#define XPARA_ID_DEVICE_ATTR  _T("device-attr")
#define XPARA_ID_GBRPTFILE  _T("gbrpt-file")
#define XPARA_ID_DVMFILE    _T("dvm-file")
#define XPARA_ID_DVMFILE_DST    _T("dvm-file-dst")
#define XPARA_ID_DVMFILES    _T("dvm-files")
#define XPARA_ID_PPXMLFILE   _T("ppxml-file")
#define XPARA_ID_TscdFile    _T("tscd-file")
#define XPARA_ID_IecfgFile   _T("iecfg-file")
#define XPARA_ID_DvmMapFile  _T("dvmmap-file")
#define XPARA_ID_EngineProgID  _T("engine-progid")
#define XPARA_ID_FILE_PATH _T("File_Path")
#define XPARA_ID_XMLRPTFILE   _T("xml-file")
#define XPARA_ID_DOCRPTFILE  _T("doc-file")
#define XPARA_ID_PDFRPTFILE  _T("pdf-file")
#define XPARA_ID_DOCRPTFILEEX  _T("doc-file-ex")

#define XPARA_ID_Optr   _T("optr")
#define XPARA_ID_OptrVal_New   _T("new")
#define XPARA_ID_OptrVal_Open   _T("open")

//2020-02-03 lijq
//测试项目的XML文本数据
#define XPARA_ID_Item_PATH   _T("item-path")
#define XPARA_ID_Item_xml   _T("item-xml")

//2021-8-4  lijunqing
#define XPARA_ID_EngineProgID_2  _T("EngineProgID")

//shaolei 2023-11-2 
#define XPARA_ID_EngineMode   _T("EngineMode")
#define XPARA_ID_DeviceSN     _T("DeviceSN")

#define XMODULE_STATE_TESTING      _T("testing")
#define XMODULE_STATE_FINISH       _T("test-finish")
#define XMODULE_STATE_ERROR        _T("test-err")

#define XMODULE_PARAID_FILE       _T("file")

#define XMODULE_VM_EXE            _T("vm-exe")
#define XMODULE_VM_SHAKEHAND      _T("vm-shake-hand")

inline CString atssys_GetTestState(const CString &strState, COLORREF &crBack)
{
	CString strText;
	crBack = RGB(255, 255, 255);

	if (strState == XMODULE_STATE_TESTING)
	{
		strText = _T("测试中");
		crBack = RGB(0, 255, 0);
	}
	else if (strState == XMODULE_STATE_FINISH)
	{
		strText = _T("测试完成");
		crBack = RGB(230, 230, 230);
	}
	else if (strState == XMODULE_STATE_ERROR)
	{
		strText = _T("不合格");
		crBack = RGB(255, 0, 0);
	}
	else
	{
		strText = _T("未测试");
	}

	return strText;
}

inline CString atssys_GetTestState(const CString &strState)
{
	CString strText;

	if (strState == XMODULE_STATE_TESTING)
	{
		strText = _T("测试中");
	}
	else if (strState == XMODULE_STATE_FINISH)
	{
		strText = _T("测试完成");
	}
	else if (strState == XMODULE_STATE_ERROR)
	{
		strText = _T("不合格");
	}
	else
	{
		strText = _T("未测试");
	}

	return strText;
}


inline CString atssys_GetProtocolPath()
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol");
	strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetProtocolTemplatePath()
{
	CString strPath = atssys_GetProtocolPath();
	strPath += g_pszKeyTemplate;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetProtocolDvmPath()
{
	CString strPath = atssys_GetProtocolPath();
	strPath += g_pszKeyLibrary;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetReportPath()
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report");
	strPath +=_P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetReportLibraryPath()
{
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report");
	strPath += _P_FOLDER_PATH_SEPARATOR_;
	strPath += g_pszKeyLibrary;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetReportTemplatePath()
{
	CString strPath = atssys_GetReportPath();
	strPath += g_pszKeyTemplate;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetReportWorkspacePath()
{
	CString strPath = atssys_GetReportPath();
	strPath += g_pszKeyWorkspace;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}

inline CString atssys_GetReportConfigPath()
{
	CString strPath = atssys_GetReportPath();
	strPath += g_pszKeyConfig;
    strPath += _P_FOLDER_PATH_SEPARATOR_;

	return strPath;
}
