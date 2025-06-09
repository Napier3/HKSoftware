
#include "stdafx.h"
#include "XLanguageResourceAts_CharLibDev.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CXLanguageResourceAts_AutoTest
const CString  CXLanguageResourceAts_CharLibDev::g_strXLangRsAts_CharLibDevFile = _T("CharLibDev");

CXLanguageResourceAts_CharLibDev::CXLanguageResourceAts_CharLibDev()
{
	
}

CXLanguageResourceAts_CharLibDev::~CXLanguageResourceAts_CharLibDev()
{
	m_oXLangRsAts_CharLibDev.RemoveAll();
}

CXLangItem* CXLanguageResourceAts_CharLibDev::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);

	m_oXLangRsAts_CharLibDev.AddTail(p);

	return p;
}


void CXLanguageResourceAts_CharLibDev::InitLangRsByFile()
{
	CXLanguageResourceAtsBase::InitLangRsByFile();

	InitLangRsByFileEx(&m_oXLangRsAts_CharLibDev, g_strXLangRsAts_CharLibDevFile);
}

void CXLanguageResourceAts_CharLibDev::RegisterLanguageResource()
{
	CXLanguageResourceAtsBase::RegisterLanguageResource();

    rs_AddString(g_sLangID_File1, &g_sLangTxt_File1);
	rs_AddString(g_sLangID_Print1, &g_sLangTxt_Print1);
	rs_AddString(g_sLangID_FileClose1, &g_sLangTxt_FileClose1);
	rs_AddString(g_sLangID_Exit1, &g_sLangTxt_Exit1);
	rs_AddString(g_sLangID_Exit1Tip, &g_sLangTxt_Exit1Tip);
	rs_AddString(g_sLangID_View1, &g_sLangTxt_View1);
	rs_AddString(g_sLangID_OutputBar1, &g_sLangTxt_OutputBar1);
	rs_AddString(g_sLangID_OutputBar1Tip, &g_sLangTxt_OutputBar1Tip);
	rs_AddString(g_sLangID_About1, &g_sLangTxt_About1);
	rs_AddString(g_sLangID_About1Tip, &g_sLangTxt_About1Tip);
	rs_AddString(g_sLangID_NewFileCreat, &g_sLangTxt_NewFileCreat);
	rs_AddString(g_sLangID_NewFileCreatTip, &g_sLangTxt_NewFileCreatTip);

	rs_AddString(g_sLangID_Open0, &g_sLangTxt_Open0);
	rs_AddString(g_sLangID_Open0Tip, &g_sLangTxt_Open0Tip);
	rs_AddString(g_sLangID_SaveS, &g_sLangTxt_SaveS);
	rs_AddString(g_sLangID_SaveSTip, &g_sLangTxt_SaveSTip);
	rs_AddString(g_sLangID_SaveAsA, &g_sLangTxt_SaveAsA);
	rs_AddString(g_sLangID_SaveAsATip, &g_sLangTxt_SaveAsATip);
	rs_AddString(g_sLangID_RePrintDoc, &g_sLangTxt_RePrintDoc);
	rs_AddString(g_sLangID_PrintQuick, &g_sLangTxt_PrintQuick);
	rs_AddString(g_sLangID_PrintPre, &g_sLangTxt_PrintPre);
	rs_AddString(g_sLangID_PrintSet, &g_sLangTxt_PrintSet);
	rs_AddString(g_sLangID_CurrentUseDoc, &g_sLangTxt_CurrentUseDoc);

	rs_AddString(g_sLangID_CharCurveOprt, &g_sLangTxt_CharCurveOprt);
	rs_AddString(g_sLangID_CurveOprt, &g_sLangTxt_CurveOprt);
	rs_AddString(g_sLangID_NewCurve, &g_sLangTxt_NewCurve);
	rs_AddString(g_sLangID_SaveCurve, &g_sLangTxt_SaveCurve);
	rs_AddString(g_sLangID_SaveAsCurve, &g_sLangTxt_SaveAsCurve);
	rs_AddString(g_sLangID_DeleteCurve, &g_sLangTxt_DeleteCurve);
	rs_AddString(g_sLangID_ImportCurve, &g_sLangTxt_ImportCurve);
	rs_AddString(g_sLangID_ExportCurve, &g_sLangTxt_ExportCurve);
	rs_AddString(g_sLangID_ModifyCurve, &g_sLangTxt_ModifyCurve);
	rs_AddString(g_sLangID_CurveBar, &g_sLangTxt_CurveBar);
	rs_AddString(g_sLangID_CurveBarTip, &g_sLangTxt_CurveBarTip);
	rs_AddString(g_sLangID_NewCurveTip, &g_sLangTxt_NewCurveTip);
	rs_AddString(g_sLangID_SaveCurveTip, &g_sLangTxt_SaveCurveTip);
	rs_AddString(g_sLangID_SaveAsCurveTip, &g_sLangTxt_SaveAsCurveTip);
	rs_AddString(g_sLangID_DeleteCurveTip, &g_sLangTxt_DeleteCurveTip);
	rs_AddString(g_sLangID_ImportCurveTip, &g_sLangTxt_ImportCurveTip);
	rs_AddString(g_sLangID_ExportCurveTip, &g_sLangTxt_ExportCurveTip);
	rs_AddString(g_sLangID_ModifyCurveTip, &g_sLangTxt_ModifyCurveTip);
	rs_AddString(g_sLangID_Style, &g_sLangTxt_Style);
	rs_AddString(g_sLangID_StyleTip1, &g_sLangTxt_StyleTip1);
	rs_AddString(g_sLangID_StyleTip2, &g_sLangTxt_StyleTip2);
	rs_AddString(g_sLangID_CharCurveSave, &g_sLangTxt_CharCurveSave);
	rs_AddString(g_sLangID_Message1, &g_sLangTxt_Message1);
	rs_AddString(g_sLangID_ModifyCharCurve, &g_sLangTxt_ModifyCharCurve);
	rs_AddString(g_sLangID_OutPut, &g_sLangTxt_OutPut);
	rs_AddString(g_sLangID_CopyOutPut, &g_sLangTxt_CopyOutPut);
	rs_AddString(g_sLangID_ClearOutPut, &g_sLangTxt_ClearOutPut);

	rs_AddString(g_sLangID_FatherSame, &g_sLangTxt_FatherSame);
	rs_AddString(g_sLangID_NewCharCurve, &g_sLangTxt_NewCharCurve);
	rs_AddString(g_sLangID_UnAddPic, &g_sLangTxt_UnAddPic);
	rs_AddString(g_sLangID_NotReali, &g_sLangTxt_NotReali);
	rs_AddString(g_sLangID_AddMemberFctn, &g_sLangTxt_AddMemberFctn);
	rs_AddString(g_sLangID_SureDelElement, &g_sLangTxt_SureDelElement);
	rs_AddString(g_sLangID_SureDelVarious, &g_sLangTxt_SureDelVarious);
	rs_AddString(g_sLangID_ExistNameCurve, &g_sLangTxt_ExistNameCurve);

	rs_AddString(g_sLangID_NewVarious, &g_sLangTxt_NewVarious);
	rs_AddString(g_sLangID_DeleteVarious, &g_sLangTxt_DeleteVarious);
	rs_AddString(g_sLangID_InportElement, &g_sLangTxt_InportElement);
	rs_AddString(g_sLangID_DeleteElement, &g_sLangTxt_DeleteElement);
	rs_AddString(g_sLangID_EdgeElementType, &g_sLangTxt_EdgeElementType);
	rs_AddString(g_sLangID_ErrorBandLength, &g_sLangTxt_ErrorBandLength);
	rs_AddString(g_sLangID_EdgTestPoints, &g_sLangTxt_EdgTestPoints);
	rs_AddString(g_sLangID_CharCurveEdge, &g_sLangTxt_CharCurveEdge);
	rs_AddString(g_sLangID_FolderName, &g_sLangTxt_FolderName);
	rs_AddString(g_sLangID_CurveMageFolder, &g_sLangTxt_CurveMageFolder);

	rs_AddString(g_sLangID_CharCurve, &g_sLangTxt_CharCurve);
	rs_AddString(g_sLangID_DecSystem, &g_sLangTxt_DecSystem);
	rs_AddString(g_sLangID_PolarSystem, &g_sLangTxt_PolarSystem);
	rs_AddString(g_sLangID_LogSystem, &g_sLangTxt_LogSystem);
	rs_AddString(g_sLangID_Vertical, &g_sLangTxt_Vertical);
	rs_AddString(g_sLangID_VerticalLine, &g_sLangTxt_VerticalLine);
	rs_AddString(g_sLangID_HorizontalLine, &g_sLangTxt_HorizontalLine);
	rs_AddString(g_sLangID_SearchLineMode, &g_sLangTxt_SearchLineMode);
	rs_AddString(g_sLangID_ElementDevelop, &g_sLangTxt_ElementDevelop);
	rs_AddString(g_sLangID_ClassView, &g_sLangTxt_ClassView);
	rs_AddString(g_sLangID_ToolTip_143, &g_sLangTxt_ToolTip_143);
	rs_AddString(g_sLangID_ToolTip_32779, &g_sLangTxt_ToolTip_32779);
	rs_AddString(g_sLangID_ToolTip_32780, &g_sLangTxt_ToolTip_32780);
}

static long g_nXLanguageResourceAts_CharLibDe_InitLangTxt = 0;

void CXLanguageResourceAts_CharLibDev::InitLangTxt()
{
	CXLanguageResourceAtsBase::InitLangTxt();

	if (g_nXLanguageResourceAts_CharLibDe_InitLangTxt>0)
	{
		return;
	}

	g_nXLanguageResourceAts_CharLibDe_InitLangTxt = 1;

	g_sLangID_File1                    = _T("sFile1");
	g_sLangTxt_File1                   = _T("文件");
	g_sLangID_Print1                    = _T("sPrint1");
	g_sLangTxt_Print1                   = _T("打印");
	g_sLangID_FileClose1                    = _T("sFileClose1");
	g_sLangTxt_FileClose1                   = _T("关闭文件");
	g_sLangID_Exit1                    = _T("sExit1");
	g_sLangTxt_Exit1                   = _T("退出");
	g_sLangID_Exit1Tip                    = _T("sExit1Tip");
	g_sLangTxt_Exit1Tip                   = _T("退出应用程序；提示保存文档\n退出");
	g_sLangID_View1                    = _T("sView1");
	g_sLangTxt_View1                   = _T("视图");
	g_sLangID_OutputBar1                    = _T("sOutputBar1");
	g_sLangTxt_OutputBar1                   = _T("输出栏");
	g_sLangID_OutputBar1Tip                    = _T("sOutputBar1Tip");
	g_sLangTxt_OutputBar1Tip                   = _T("显示或隐藏输出栏\n输出栏");
	g_sLangID_About1                    = _T("sAbout1");
	g_sLangTxt_About1                   = _T("关于");
	g_sLangID_About1Tip                    = _T("sAbout1Tip");
	g_sLangTxt_About1Tip                   = _T("显示程序信息、版本号和版权\n关于");
	g_sLangID_NewFileCreat                    = _T("sNewFileCreat");
	g_sLangTxt_NewFileCreat                   = _T("新建文件");
	g_sLangID_NewFileCreatTip                    = _T("sNewFileCreatTip");
	g_sLangTxt_NewFileCreatTip                   = _T("创建新文档\n新建");
	g_sLangID_Open0                    = _T("sOpen0");
	g_sLangTxt_Open0                   = _T("打开");
	g_sLangID_Open0Tip                    = _T("sOpen0Tip");
	g_sLangTxt_Open0Tip                   = _T("打开现有文档\n打开");
	g_sLangID_SaveS                    = _T("sSaveS");
	g_sLangTxt_SaveS                   = _T("保存");
	g_sLangID_SaveSTip                    = _T("sSaveSTip");
	g_sLangTxt_SaveSTip                   = _T("保存活动文档\n保存");
	g_sLangID_SaveAsA                    = _T("sSaveAsA");
	g_sLangTxt_SaveAsA                   = _T("另存为");
	g_sLangID_SaveAsATip                    = _T("sSaveAsATip");
	g_sLangTxt_SaveAsATip                   = _T("用新名称保存活动文档\n另存为");
	g_sLangID_RePrintDoc                    = _T("sRePrintDoc");
	g_sLangTxt_RePrintDoc                   = _T("预览并打印文档");
	g_sLangID_PrintQuick                    = _T("sPrintQuick");
	g_sLangTxt_PrintQuick                   = _T("快速打印");
	g_sLangID_PrintPre                    = _T("sPrintPre");
	g_sLangTxt_PrintPre                   = _T("打印预览");
	g_sLangID_PrintSet                    = _T("sPrintSet");
	g_sLangTxt_PrintSet                   = _T("打印设置");
	g_sLangID_CurrentUseDoc                    = _T("sCurrentUseDoc");
	g_sLangTxt_CurrentUseDoc                   = _T("最近使用的文档");
	g_sLangID_CharCurveOprt                    = _T("sCharCurveOprt");
	g_sLangTxt_CharCurveOprt                   = _T("特性曲线操作");
	g_sLangID_CurveOprt                    = _T("sCurveOprt");
	g_sLangTxt_CurveOprt                   = _T("曲线操作");
	g_sLangID_NewCurve                    = _T("sNewCurve");
	g_sLangTxt_NewCurve                   = _T("新建曲线");
	g_sLangID_SaveCurve                    = _T("sSaveCurve");
	g_sLangTxt_SaveCurve                   = _T("保存曲线");
	g_sLangID_SaveAsCurve                    = _T("sSaveAsCurve");
	g_sLangTxt_SaveAsCurve                    = _T("曲线另存为");
	g_sLangID_DeleteCurve                    = _T("sDeleteCurve");
	g_sLangTxt_DeleteCurve                   = _T("删除曲线");
	g_sLangID_ImportCurve                    = _T("sImportCurve");
	g_sLangTxt_ImportCurve                   = _T("导入曲线");
	g_sLangID_ExportCurve                    = _T("sExportCurve");
	g_sLangTxt_ExportCurve                   = _T("导出曲线");
	g_sLangID_ModifyCurve                    = _T("sModifyCurve");
	g_sLangTxt_ModifyCurve                   = _T("修改曲线");
	g_sLangID_CurveBar                    = _T("sCurveBar");
	g_sLangTxt_CurveBar                   = _T("曲线栏");
	g_sLangID_CurveBarTip                    = _T("sCurveBarTip");
	g_sLangTxt_CurveBarTip                   = _T("显示或隐藏特性曲线\n特性曲线栏");
	g_sLangID_NewCurveTip                    = _T("sNewCurveTip");
	g_sLangTxt_NewCurveTip                   = _T("新建特性曲线\n新建");
	g_sLangID_SaveCurveTip                    = _T("sSaveCurveTip");
	g_sLangTxt_SaveCurveTip                   = _T("保存特性曲线\n保存");
	g_sLangID_SaveAsCurveTip                    = _T("sSaveAsCurveTip");
	g_sLangTxt_SaveAsCurveTip                    = _T("特性曲线另存为\n另存为");
	g_sLangID_DeleteCurveTip                    = _T("sDeleteCurveTip");
	g_sLangTxt_DeleteCurveTip                   = _T("删除特性曲线\n删除");
	g_sLangID_ImportCurveTip                    = _T("sImportCurveTip");
	g_sLangTxt_ImportCurveTip                   = _T("导入特性曲线\n导入");
	g_sLangID_ExportCurveTip                    = _T("sExportCurveTip");
	g_sLangTxt_ExportCurveTip                   = _T("导出特性曲线\n导出");
	g_sLangID_ModifyCurveTip                    = _T("sModifyCurveTip");
	g_sLangTxt_ModifyCurveTip                   = _T("修改特性曲线\n修改");
	g_sLangID_Style                    = _T("sStyle");
	g_sLangTxt_Style                   = _T("样式");
	g_sLangID_StyleTip1                    = _T("sStyleTip1");
	g_sLangTxt_StyleTip1                   = _T("修改视觉样式");
	g_sLangID_StyleTip2                    = _T("sStyleTip2");
	g_sLangTxt_StyleTip2                   = _T("选择一个office 2007主题");
	g_sLangID_CharCurveSave                    = _T("sCharCurveSave");
	g_sLangTxt_CharCurveSave                   = _T("特性曲线库已经被修改，是否保存修改？");
	g_sLangID_Message1                    = _T("sMessage1");
	g_sLangTxt_Message1                   = _T("提示");
	g_sLangID_ModifyCharCurve                    = _T("sModifyCharCurve");
	g_sLangTxt_ModifyCharCurve                    = _T("修改特性曲线");
	g_sLangID_OutPut                    = _T("sOutPut");
	g_sLangTxt_OutPut                    = _T("输出");
	g_sLangID_CopyOutPut                    = _T("sCopyOutPut");
	g_sLangTxt_CopyOutPut                    = _T("复制输出");
	g_sLangID_ClearOutPut                    = _T("sClearOutPut");
	g_sLangTxt_ClearOutPut                    = _T("清除输出");
	g_sLangID_FatherSame                    = _T("sFatherSame");
	g_sLangTxt_FatherSame                    = _T("父文件夹“%s”存在相同名称的“%s”子文件夹！");
	g_sLangID_NewCharCurve                    = _T("sNewCharCurve");
	g_sLangTxt_NewCharCurve                    = _T("新建特性曲线");
	g_sLangID_UnAddPic                    = _T("sUnAddPic");
	g_sLangTxt_UnAddPic                    = _T("无法加载位图: %x\n");
	g_sLangID_NotReali                    = _T("sNotReali");
	g_sLangTxt_NotReali                     = _T("还没有实现");
	g_sLangID_AddMemberFctn                    = _T("sAddMemberFctn");
	g_sLangTxt_AddMemberFctn                    = _T("添加成员函数...");
	g_sLangID_SureDelElement                    = _T("sSureDelElement");
	g_sLangTxt_SureDelElement                     = _T("你确实要删除元素“%s”吗？");
	g_sLangID_SureDelVarious                    = _T("sSureDelVarious");
	g_sLangTxt_SureDelVarious                     = _T("是否删除变量“%s”？");
	g_sLangID_ExistNameCurve                    = _T("sExistNameCurve");
	g_sLangTxt_ExistNameCurve                     = _T("存在名称为“%s”的曲线");

	g_sLangID_NewVarious                    = _T("sNewVarious");
	g_sLangTxt_NewVarious                     = _T("新建变量");
	g_sLangID_DeleteVarious                    = _T("sDeleteVarious");
	g_sLangTxt_DeleteVarious                     = _T("删除变量");
	g_sLangID_InportElement                    = _T("sInportElement");
	g_sLangTxt_InportElement                     = _T("插入元素");
	g_sLangID_DeleteElement                    = _T("sDeleteElement");
	g_sLangTxt_DeleteElement                     = _T("删除元素");
	g_sLangID_EdgeElementType                    = _T("sEdgeElementType");
	g_sLangTxt_EdgeElementType                     = _T("边元素类型");
	g_sLangID_ErrorBandLength                    = _T("sErrorBandLength");
	g_sLangTxt_ErrorBandLength                     = _T("误差带长度");
	g_sLangID_EdgTestPoints                    = _T("sEdgTestPoints");
	g_sLangTxt_EdgTestPoints                     = _T("边测试点数");
	g_sLangID_CharCurveEdge                    = _T("sCharCurveEdge");
	g_sLangTxt_CharCurveEdge                     = _T("特性曲线边元素");
	g_sLangID_FolderName                    = _T("sFolderName");
	g_sLangTxt_FolderName                     = _T("文件夹名称");
	g_sLangID_CurveMageFolder                    = _T("sCurveMageFolder");
	g_sLangTxt_CurveMageFolder                     = _T("曲线管理文件夹");

	g_sLangID_CharCurve                    = _T("sCharCurve");
	g_sLangTxt_CharCurve                     = _T("特性曲线");
	g_sLangID_DecSystem                    = _T("sDecSystem");
	g_sLangTxt_DecSystem                     = _T("笛卡尔坐标系");
	g_sLangID_PolarSystem                    = _T("sPolarSystem");
	g_sLangTxt_PolarSystem                     = _T("极坐标系");
	g_sLangID_LogSystem                    = _T("sLogSystem");
	g_sLangTxt_LogSystem                      = _T("对数坐标系");
	g_sLangID_Vertical                    = _T("sVertical");
	g_sLangTxt_Vertical                     = _T("垂线");
	g_sLangID_VerticalLine                    = _T("sVerticalLine");
	g_sLangTxt_VerticalLine                     = _T("垂直竖线");
	g_sLangID_HorizontalLine                    = _T("sHorizontalLine");
	g_sLangTxt_HorizontalLine                     = _T("水平横线");
	g_sLangID_SearchLineMode                    = _T("sSearchLineMode");
	g_sLangTxt_SearchLineMode                     = _T("搜索线模式");
	g_sLangID_ElementDevelop                    = _T("sElementDevelop");
	g_sLangTxt_ElementDevelop                     = _T("元素开发中.....");
	g_sLangID_ClassView                    = _T("sClassView");
	g_sLangTxt_ClassView                     = _T("类视图");
	g_sLangID_ToolTip_143                    = _T("sToolTip_143");
	g_sLangTxt_ToolTip_143                     = _T("新建文件夹\n新建文件夹");
	g_sLangID_ToolTip_32779                    = _T("sToolTip_32779");
	g_sLangTxt_ToolTip_32779                     = _T("编辑文件夹\n编辑文件夹");
	g_sLangID_ToolTip_32780                    = _T("sToolTip_32780");
	g_sLangTxt_ToolTip_32780                     = _T("删除文件夹\n删除文件夹");
}



CString g_sLangID_File1; 
CString g_sLangTxt_File1;
CString g_sLangID_Print1; 
CString g_sLangTxt_Print1;
CString g_sLangID_FileClose1; 
CString g_sLangTxt_FileClose1;
CString g_sLangID_Exit1; 
CString g_sLangTxt_Exit1;
CString g_sLangID_Exit1Tip; 
CString g_sLangTxt_Exit1Tip;
CString g_sLangID_View1; 
CString g_sLangTxt_View1;
CString g_sLangID_OutputBar1; 
CString g_sLangTxt_OutputBar1;
CString g_sLangID_OutputBar1Tip; 
CString g_sLangTxt_OutputBar1Tip;
CString g_sLangID_About1; 
CString g_sLangTxt_About1;
CString g_sLangID_About1Tip; 
CString g_sLangTxt_About1Tip;
CString g_sLangID_NewFileCreat; 
CString g_sLangTxt_NewFileCreat;
CString g_sLangID_NewFileCreatTip; 
CString g_sLangTxt_NewFileCreatTip;
CString g_sLangID_Open0; 
CString g_sLangTxt_Open0;
CString g_sLangID_Open0Tip; 
CString g_sLangTxt_Open0Tip;
CString g_sLangID_SaveS; 
CString g_sLangTxt_SaveS;
CString g_sLangID_SaveSTip; 
CString g_sLangTxt_SaveSTip;
CString g_sLangID_SaveAsA; 
CString g_sLangTxt_SaveAsA;
CString g_sLangID_SaveAsATip; 
CString g_sLangTxt_SaveAsATip;
CString g_sLangID_RePrintDoc; //预览并打印文档
CString g_sLangTxt_RePrintDoc;
CString g_sLangID_PrintQuick; //快速打印
CString g_sLangTxt_PrintQuick;
CString g_sLangID_PrintPre; //打印预览
CString g_sLangTxt_PrintPre;
CString g_sLangID_PrintSet; //打印设置
CString g_sLangTxt_PrintSet;
CString g_sLangID_CurrentUseDoc; //最近使用的文档
CString g_sLangTxt_CurrentUseDoc;
CString g_sLangID_CharCurveOprt; //特性曲线操作
CString g_sLangTxt_CharCurveOprt;
CString g_sLangID_CurveOprt; //曲线操作
CString g_sLangTxt_CurveOprt;
CString g_sLangID_NewCurve; //新建曲线
CString g_sLangTxt_NewCurve;
CString g_sLangID_SaveCurve; //保存曲线
CString g_sLangTxt_SaveCurve;
CString g_sLangID_SaveAsCurve; //曲线另存为
CString g_sLangTxt_SaveAsCurve;
CString g_sLangID_DeleteCurve; //删除曲线
CString g_sLangTxt_DeleteCurve;
CString g_sLangID_ImportCurve; //导出曲线
CString g_sLangTxt_ImportCurve;
CString g_sLangID_ExportCurve; //导出曲线
CString g_sLangTxt_ExportCurve;
CString g_sLangID_ModifyCurve; //修改曲线
CString g_sLangTxt_ModifyCurve;
CString g_sLangID_CurveBar; //曲线栏
CString g_sLangTxt_CurveBar;
CString g_sLangID_CurveBarTip; //显示或隐藏特性曲线\n特性曲线栏
CString g_sLangTxt_CurveBarTip;
CString g_sLangID_NewCurveTip; //新建特性曲线\n新建
CString g_sLangTxt_NewCurveTip;
CString g_sLangID_SaveCurveTip; //保存特性曲线\n保存
CString g_sLangTxt_SaveCurveTip;
CString g_sLangID_SaveAsCurveTip; //特性曲线另存为\n另存为
CString g_sLangTxt_SaveAsCurveTip;
CString g_sLangID_DeleteCurveTip; //删除特性曲线\n删除
CString g_sLangTxt_DeleteCurveTip;
CString g_sLangID_ImportCurveTip; //导入特性曲线\n导入
CString g_sLangTxt_ImportCurveTip;
CString g_sLangID_ExportCurveTip; //导出特性曲线\n导出
CString g_sLangTxt_ExportCurveTip;
CString g_sLangID_ModifyCurveTip; //修改特性曲线\n修改
CString g_sLangTxt_ModifyCurveTip;
CString g_sLangID_Style; //样式
CString g_sLangTxt_Style;
CString g_sLangID_StyleTip1; //修改视觉样式
CString g_sLangTxt_StyleTip1;
CString g_sLangID_StyleTip2; //选择一个office 2007主题
CString g_sLangTxt_StyleTip2;
CString g_sLangID_CharCurveSave; //特性曲线库已经被修改，是否保存修改？
CString g_sLangTxt_CharCurveSave;
CString g_sLangID_Message1; //提示
CString g_sLangTxt_Message1;
CString g_sLangID_ModifyCharCurve; //修改特性曲线
CString g_sLangTxt_ModifyCharCurve;
CString g_sLangID_OutPut; //输出
CString g_sLangTxt_OutPut;
CString g_sLangID_CopyOutPut; //复制输出
CString g_sLangTxt_CopyOutPut;
CString g_sLangID_ClearOutPut; //清除输出
CString g_sLangTxt_ClearOutPut;
CString g_sLangID_FatherSame; //父文件夹“%s”存在相同名称的“%s”子文件夹！
CString g_sLangTxt_FatherSame;
CString g_sLangID_NewCharCurve; //新建特性曲线
CString g_sLangTxt_NewCharCurve;
CString g_sLangID_UnAddPic; //无法加载位图: %x\n
CString g_sLangTxt_UnAddPic;
CString g_sLangID_NotReali; //还没有实现
CString g_sLangTxt_NotReali;
CString g_sLangID_AddMemberFctn; //添加成员函数...
CString g_sLangTxt_AddMemberFctn;
CString g_sLangID_SureDelElement; //你确实要删除元素“%s”吗？
CString g_sLangTxt_SureDelElement;
CString g_sLangID_SureDelVarious; //是否删除变量“%s”？
CString g_sLangTxt_SureDelVarious;
CString g_sLangID_ExistNameCurve; //存在名称为“%s”的曲线
CString g_sLangTxt_ExistNameCurve;
CString g_sLangID_NewVarious; //新建变量
CString g_sLangTxt_NewVarious;
CString g_sLangID_DeleteVarious; //删除变量
CString g_sLangTxt_DeleteVarious;
CString g_sLangID_InportElement; //插入元素
CString g_sLangTxt_InportElement;
CString g_sLangID_DeleteElement; //删除元素
CString g_sLangTxt_DeleteElement;
CString g_sLangID_EdgeElementType; 
CString g_sLangTxt_EdgeElementType;
CString g_sLangID_ErrorBandLength; 
CString g_sLangTxt_ErrorBandLength;
CString g_sLangID_EdgTestPoints; 
CString g_sLangTxt_EdgTestPoints;
CString g_sLangID_CharCurveEdge; 
CString g_sLangTxt_CharCurveEdge;
CString g_sLangID_FolderName; //文件夹名称
CString g_sLangTxt_FolderName;
CString g_sLangID_CurveMageFolder; //曲线管理文件夹
CString g_sLangTxt_CurveMageFolder;

CString g_sLangID_CharCurve; //特性曲线
CString g_sLangTxt_CharCurve;
CString g_sLangID_DecSystem; //笛卡尔坐标系
CString g_sLangTxt_DecSystem;
CString g_sLangID_PolarSystem; //极坐标系
CString g_sLangTxt_PolarSystem;
CString g_sLangID_LogSystem; //对数坐标系
CString g_sLangTxt_LogSystem;
CString g_sLangID_Vertical; //垂线
CString g_sLangTxt_Vertical;
CString g_sLangID_VerticalLine; //垂直竖线
CString g_sLangTxt_VerticalLine;
CString g_sLangID_HorizontalLine; //水平横线
CString g_sLangTxt_HorizontalLine;
CString g_sLangID_SearchLineMode; //搜索线模式
CString g_sLangTxt_SearchLineMode;
CString g_sLangID_ElementDevelop; //元素开发中.....
CString g_sLangTxt_ElementDevelop;
CString g_sLangID_ClassView; //类视图
CString g_sLangTxt_ClassView;
CString g_sLangID_ToolTip_143;//新建文件夹\n新建文件夹
CString g_sLangTxt_ToolTip_143;
CString g_sLangID_ToolTip_32779;//编辑文件夹\n编辑文件夹
CString g_sLangTxt_ToolTip_32779;
CString g_sLangID_ToolTip_32780;//删除文件夹\n删除文件夹
CString g_sLangTxt_ToolTip_32780;