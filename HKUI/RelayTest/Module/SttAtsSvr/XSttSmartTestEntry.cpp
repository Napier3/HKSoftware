#include "stdafx.h"
#include "XSttSmartTestEntry.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXSmartTestEntry* CXSmartTestEntry::g_pXSttSmartTestEntry = NULL;
long CXSmartTestEntry::g_nXSttSmartTestEntryRef = 0;
extern CSttGuideBookGenServer g_oSttGuideBookGenServer; 


CXSmartTestEntry::CXSmartTestEntry()
{
	CString strSysPath;
	strSysPath = _P_GetInstallPath();
	strSysPath += _T("STT/");
	g_oSttGuideBookGenServer.InitGbGenSysPath(strSysPath);  //2022-3-29  lijunqing SmartTest
	CSttMacroTestUI_TestMacroUIDB::Create(strSysPath);
	CGbItemsGenRuleDefMngrXmlRWKeys::Create();

	//shaolei 注释此处
	//注释原因：不能在此处创建TestControl，需要19815服务起来之后，再创建TestControl
	//与19814联机后，需要绑定转发对象
	//InitTestControl(true);
}

CXSmartTestEntry::~CXSmartTestEntry()
{
	CGbItemsGenRuleDefMngrXmlRWKeys::Release();
	CSttMacroTestUI_TestMacroUIDB::Release();
}

CXSmartTestEntry* CXSmartTestEntry::Create()
{
	g_nXSttSmartTestEntryRef++;

	if (g_nXSttSmartTestEntryRef == 1)
	{
		g_pXSttSmartTestEntry = new CXSmartTestEntry();
		g_theSttSmartTest = g_pXSttSmartTestEntry;
	}

	return g_pXSttSmartTestEntry;
}

void CXSmartTestEntry::Release()
{
	g_nXSttSmartTestEntryRef--;

	if (g_nXSttSmartTestEntryRef == 0)
	{
		delete g_pXSttSmartTestEntry;
		g_pXSttSmartTestEntry = NULL;
		g_theSttSmartTest = NULL;
	}
}

//CString CXSmartTestEntry::ValidFileName(const CString &strPath, const CString &strFileName, const CString &strProfix)
//{
//	CString strLocalPath;
//
//	if (strPath.Right(1) == _T("\\"))
//	{
//		strLocalPath = strPath + strFileName;
//	}
//	else
//	{
//		strLocalPath = strPath + _T("\\") + strFileName;
//	}
//
//	strLocalPath = ChangeFilePostfix(strLocalPath, strProfix);
//	return strLocalPath;
//}
