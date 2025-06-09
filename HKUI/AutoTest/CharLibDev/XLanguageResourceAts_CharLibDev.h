#pragma once

#include "..\..\Module\XLanguage\XLanguageMngr.h"
#include "..\Module\XLanguageResourceAts.h"

class CXLanguageResourceAts_CharLibDev : public CXLanguageResourceAtsBase
{
// 构造
public:
	CXLanguageResourceAts_CharLibDev();
	virtual ~CXLanguageResourceAts_CharLibDev();
	
private:
	CXLanguage m_oXLangRsAts_CharLibDev;
	static const CString  g_strXLangRsAts_CharLibDevFile;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

public:
	
};

extern CString g_sLangID_File1; 
extern CString g_sLangTxt_File1;
extern CString g_sLangID_Print1; 
extern CString g_sLangTxt_Print1;
extern CString g_sLangID_FileClose1; 
extern CString g_sLangTxt_FileClose1;
extern CString g_sLangID_Exit1; 
extern CString g_sLangTxt_Exit1;
extern CString g_sLangID_Exit1Tip; 
extern CString g_sLangTxt_Exit1Tip;
extern CString g_sLangID_View1; 
extern CString g_sLangTxt_View1;
extern CString g_sLangID_OutputBar1; 
extern CString g_sLangTxt_OutputBar1;
extern CString g_sLangID_OutputBar1Tip; 
extern CString g_sLangTxt_OutputBar1Tip;
extern CString g_sLangID_About1; 
extern CString g_sLangTxt_About1;
extern CString g_sLangID_About1Tip; 
extern CString g_sLangTxt_About1Tip;
extern CString g_sLangID_NewFileCreat; 
extern CString g_sLangTxt_NewFileCreat;
extern CString g_sLangID_NewFileCreatTip; 
extern CString g_sLangTxt_NewFileCreatTip;
extern CString g_sLangID_Open0; 
extern CString g_sLangTxt_Open0;
extern CString g_sLangID_Open0Tip; 
extern CString g_sLangTxt_Open0Tip;
extern CString g_sLangID_SaveS; 
extern CString g_sLangTxt_SaveS;
extern CString g_sLangID_SaveSTip; 
extern CString g_sLangTxt_SaveSTip;
extern CString g_sLangID_SaveAsA; 
extern CString g_sLangTxt_SaveAsA;
extern CString g_sLangID_SaveAsATip; 
extern CString g_sLangTxt_SaveAsATip;
extern CString g_sLangID_RePrintDoc; //预览并打印文档
extern CString g_sLangTxt_RePrintDoc;
extern CString g_sLangID_PrintQuick; //快速打印
extern CString g_sLangTxt_PrintQuick;
extern CString g_sLangID_PrintPre; //打印预览
extern CString g_sLangTxt_PrintPre;
extern CString g_sLangID_PrintSet; //打印设置
extern CString g_sLangTxt_PrintSet;
extern CString g_sLangID_CurrentUseDoc; //最近使用的文档
extern CString g_sLangTxt_CurrentUseDoc;
extern CString g_sLangID_CharCurveOprt; //特性曲线操作
extern CString g_sLangTxt_CharCurveOprt;
extern CString g_sLangID_CurveOprt; //曲线操作
extern CString g_sLangTxt_CurveOprt;
extern CString g_sLangID_NewCurve; //新建曲线
extern CString g_sLangTxt_NewCurve;
extern CString g_sLangID_SaveCurve; //保存曲线
extern CString g_sLangTxt_SaveCurve;
extern CString g_sLangID_SaveAsCurve; //曲线另存为
extern CString g_sLangTxt_SaveAsCurve;
extern CString g_sLangID_DeleteCurve; //删除曲线
extern CString g_sLangTxt_DeleteCurve;
extern CString g_sLangID_ImportCurve; //导出曲线
extern CString g_sLangTxt_ImportCurve;
extern CString g_sLangID_ExportCurve; //导出曲线
extern CString g_sLangTxt_ExportCurve;
extern CString g_sLangID_ModifyCurve; //修改曲线
extern CString g_sLangTxt_ModifyCurve;
extern CString g_sLangID_CurveBar; //曲线栏
extern CString g_sLangTxt_CurveBar;
extern CString g_sLangID_CurveBarTip; //显示或隐藏特性曲线\n特性曲线栏
extern CString g_sLangTxt_CurveBarTip;
extern CString g_sLangID_NewCurveTip; //新建特性曲线\n新建
extern CString g_sLangTxt_NewCurveTip;
extern CString g_sLangID_SaveCurveTip; //保存特性曲线\n保存
extern CString g_sLangTxt_SaveCurveTip;
extern CString g_sLangID_SaveAsCurveTip; //特性曲线另存为\n另存为
extern CString g_sLangTxt_SaveAsCurveTip;
extern CString g_sLangID_DeleteCurveTip; //删除特性曲线\n删除
extern CString g_sLangTxt_DeleteCurveTip;
extern CString g_sLangID_ImportCurveTip; //导入特性曲线\n导入
extern CString g_sLangTxt_ImportCurveTip;
extern CString g_sLangID_ExportCurveTip; //导出特性曲线\n导出
extern CString g_sLangTxt_ExportCurveTip;
extern CString g_sLangID_ModifyCurveTip; //修改特性曲线\n修改
extern CString g_sLangTxt_ModifyCurveTip;
extern CString g_sLangID_Style; //样式
extern CString g_sLangTxt_Style;
extern CString g_sLangID_StyleTip1; //修改视觉样式
extern CString g_sLangTxt_StyleTip1;
extern CString g_sLangID_StyleTip2; //选择一个office 2007主题
extern CString g_sLangTxt_StyleTip2;
extern CString g_sLangID_CharCurveSave; //特性曲线库已经被修改，是否保存修改？
extern CString g_sLangTxt_CharCurveSave;
extern CString g_sLangID_Message1; //提示
extern CString g_sLangTxt_Message1;
extern CString g_sLangID_ModifyCharCurve; //修改特性曲线
extern CString g_sLangTxt_ModifyCharCurve;
extern CString g_sLangID_OutPut; //输出
extern CString g_sLangTxt_OutPut;
extern CString g_sLangID_CopyOutPut; //复制输出
extern CString g_sLangTxt_CopyOutPut;
extern CString g_sLangID_ClearOutPut; //清除输出
extern CString g_sLangTxt_ClearOutPut;
extern CString g_sLangID_FatherSame; //父文件夹“%s”存在相同名称的“%s”子文件夹！
extern CString g_sLangTxt_FatherSame;
extern CString g_sLangID_NewCharCurve; //新建特性曲线
extern CString g_sLangTxt_NewCharCurve;
extern CString g_sLangID_UnAddPic; //无法加载位图: %x\n
extern CString g_sLangTxt_UnAddPic;
extern CString g_sLangID_NotReali; //还没有实现
extern CString g_sLangTxt_NotReali;
extern CString g_sLangID_AddMemberFctn; //添加成员函数...
extern CString g_sLangTxt_AddMemberFctn;
extern CString g_sLangID_SureDelElement; //你确实要删除元素“%s”吗？
extern CString g_sLangTxt_SureDelElement;
extern CString g_sLangID_SureDelVarious; //是否删除变量“%s”？
extern CString g_sLangTxt_SureDelVarious;
extern CString g_sLangID_ExistNameCurve; //存在名称为“%s”的曲线
extern CString g_sLangTxt_ExistNameCurve;
extern CString g_sLangID_NewVarious; //新建变量
extern CString g_sLangTxt_NewVarious;
extern CString g_sLangID_DeleteVarious; //删除变量
extern CString g_sLangTxt_DeleteVarious;
extern CString g_sLangID_InportElement; //插入元素
extern CString g_sLangTxt_InportElement;
extern CString g_sLangID_DeleteElement; //删除元素
extern CString g_sLangTxt_DeleteElement;
extern CString g_sLangID_EdgeElementType; 
extern CString g_sLangTxt_EdgeElementType;
extern CString g_sLangID_ErrorBandLength; 
extern CString g_sLangTxt_ErrorBandLength;
extern CString g_sLangID_EdgTestPoints; 
extern CString g_sLangTxt_EdgTestPoints;
extern CString g_sLangID_CharCurveEdge; 
extern CString g_sLangTxt_CharCurveEdge;
extern CString g_sLangID_FolderName; //文件夹名称
extern CString g_sLangTxt_FolderName;
extern CString g_sLangID_CurveMageFolder; //曲线管理文件夹
extern CString g_sLangTxt_CurveMageFolder;

extern CString g_sLangID_CharCurve; //特性曲线
extern CString g_sLangTxt_CharCurve;
extern CString g_sLangID_DecSystem; //笛卡尔坐标系
extern CString g_sLangTxt_DecSystem;
extern CString g_sLangID_PolarSystem; //极坐标系
extern CString g_sLangTxt_PolarSystem;
extern CString g_sLangID_LogSystem; //对数坐标系
extern CString g_sLangTxt_LogSystem;
extern CString g_sLangID_Vertical; //垂线
extern CString g_sLangTxt_Vertical;
extern CString g_sLangID_VerticalLine; //垂直竖线
extern CString g_sLangTxt_VerticalLine;
extern CString g_sLangID_HorizontalLine; //水平横线
extern CString g_sLangTxt_HorizontalLine;
extern CString g_sLangID_SearchLineMode; //搜索线模式
extern CString g_sLangTxt_SearchLineMode;
extern CString g_sLangID_ElementDevelop; //元素开发中.....
extern CString g_sLangTxt_ElementDevelop;
extern CString g_sLangID_ClassView; //类视图
extern CString g_sLangTxt_ClassView;
extern CString g_sLangID_ToolTip_143;//新建文件夹\n新建文件夹
extern CString g_sLangTxt_ToolTip_143;
extern CString g_sLangID_ToolTip_32779;//编辑文件夹\n编辑文件夹
extern CString g_sLangTxt_ToolTip_32779;
extern CString g_sLangID_ToolTip_32780;//删除文件夹\n删除文件夹
extern CString g_sLangTxt_ToolTip_32780;