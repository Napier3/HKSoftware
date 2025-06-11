//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrameConfig.cpp  CSttFrameConfig


#include "stdafx.h"
#include "SttFrameConfig.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../SttTestCntrCmdDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long g_nComBoxItemHeight = 50;  //2023-1-4  lijunqing
long g_nTableVertScrollWidth = 30;  //Table垂直滚动条宽度
long g_nTableHorizontalScrollHeight = 30; //Table水平滑动块宽度
long g_nTreeVertScrollWidth = 30; //Tree垂直滚动条宽度
long g_nTreeHorizontalScrollHeight = 30; //Tree水平滚动条高度
long g_nComBoxVertScrollWidth = 30; //Combox控件下拉框竖直滑动条宽度

/*long g_nVertScrollWidth= 50 ;  //竖直滑动块宽度定为50//
long g_nLevelScrollHeight = 50;	//水平滑动块宽度定为50
long g_nTreeVertScrollWidth = 50; //QTreeWideget 竖直滑动块宽度为50
long g_nTreeLevelWidth = 50; //QTreeWideget 水平滑动块宽度为50
long g_nComBoxVertScrollWidth = 50; //Combox控件下拉框竖直滑动条宽度
long g_nGooseVertWidth = 50;	//Goose界面竖直滑块宽度
long g_nGooseLevelWidth = 50;	//Goose界面水平滑块宽度
long g_nCustomVertWidth = 50; //菜单栏自定义设置界面竖直滑块宽度
long g_nCustomLevelWidth = 50; //菜单栏自定义设置界面水平滑块宽度
long g_nLeadInVertWidth = 50;	//菜单栏导入通道映射界面竖直滑块宽度
long g_nLeadLevelWidth =50;	//菜单栏导入通道映射界面水平滑块宽度
*/
CSttFrameConfig* CSttFrameConfig::g_pSttFrameConfig = NULL;
long CSttFrameConfig::g_nSttFrameConfig = 0;

long SttFrame_Vert_Gap = 0;  //框架按钮垂直方向上的间隔，系统为工具栏、状态栏绘制边框
long SttFrame_Line_Pix = 1;    //绘制边框的像素点

CSttFrameConfig* CSttFrameConfig::Create(const CString &strFrameCfgFile)
{
	g_nSttFrameConfig++;

	if (g_nSttFrameConfig == 1)
	{
		CSttTestCtrlFrameCfgMngrXmlRWKeys::Create();
		g_pSttFrameConfig = new CSttFrameConfig();
		g_pSttFrameConfig->Open(strFrameCfgFile);

#ifndef NOT_USE_XLANGUAGE
		xlang_TranslateByResourceFileEx(g_pSttFrameConfig, strFrameCfgFile);
#endif
	}

	return g_pSttFrameConfig;
}

void CSttFrameConfig::Release()
{
	g_nSttFrameConfig--;

	if (g_nSttFrameConfig == 0)
	{
		CSttTestCtrlFrameCfgMngrXmlRWKeys::Release();
		delete g_pSttFrameConfig;
		g_pSttFrameConfig = NULL;
	}
}

CSttFrameConfig::CSttFrameConfig()
{
	m_nLogDebugInfor = 0;
	m_nSelMacroShow = 1;

	//初始化属性
	m_nHeight = 0;
	m_nWidth = 0;
	//初始化成员变量
	m_pFont = NULL;
	m_pMenus = NULL;
	m_pToolBar = NULL;
	m_pGbTree = NULL;
	m_pMacroParaView = NULL;
	m_pReprotView = NULL;
	m_pRightPanes = NULL;
	m_pStatusBar = NULL;
	m_pResultBar = NULL;
	m_pGlobalDatas = NULL;
}

CSttFrameConfig::~CSttFrameConfig()
{
}

long CSttFrameConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_nHeight);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strLogDebugInforKey, oNode, m_nLogDebugInfor);
	xml_GetAttibuteValue(pXmlKeys->m_strFrameBtnGapKey, oNode, SttFrame_Vert_Gap);
	xml_GetAttibuteValue(pXmlKeys->m_strSelMacroShow, oNode, m_nSelMacroShow);


	return 0;
}

long CSttFrameConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_nHeight);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strFrameBtnGapKey, oElement, SttFrame_Vert_Gap);

	return 0;
}

long CSttFrameConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nHeight);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nHeight);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nHeight);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
	}
	return 0;
}

void CSttFrameConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
		{
			m_pFont = (CSttFrame_Font*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATAS)
		{
			m_pGlobalDatas = (CSttFrame_GlobalDatas*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_MENUS)
		{
			m_pMenus = (CSttFrame_Menus*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_TOOLBAR)
		{
			m_pToolBar = (CSttFrame_ToolBar*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_GBTREE)
		{
			m_pGbTree = (CSttFrame_GbTree*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_MACROPARAVIEW)
		{
			m_pMacroParaView = (CSttFrame_MacroParaView*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_REPORTVIEW)
		{
			m_pReprotView = (CSttFrame_ReportView*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_RIGHTPANES)
		{
			m_pRightPanes = (CSttFrame_RightPanes*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_STATUSBAR)
		{
			m_pStatusBar = (CSttFrame_StatusBar*)p;
		}
		else if (nClassID == MNGRCLASSID_CSTTFRAME_RESULTBAR)
		{
			m_pResultBar = (CSttFrame_ResultBar*)p;
		}	
	}

	if (m_pFont == NULL)
	{
		m_pFont = (CSttFrame_Font*)AddNewChild(new CSttFrame_Font());
	}
	if (m_pGlobalDatas == NULL)
	{
		m_pGlobalDatas = (CSttFrame_GlobalDatas*)AddNewChild(new CSttFrame_GlobalDatas());
	}
	if (m_pMenus == NULL)
	{
		m_pMenus = (CSttFrame_Menus*)AddNewChild(new CSttFrame_Menus());
	}

	if (m_pToolBar == NULL)
	{
		m_pToolBar = (CSttFrame_ToolBar*)AddNewChild(new CSttFrame_ToolBar());
	}

	if (m_pGbTree == NULL)
	{
		m_pGbTree = (CSttFrame_GbTree*)AddNewChild(new CSttFrame_GbTree());
	}

	if (m_pMacroParaView == NULL)
	{
		m_pMacroParaView = (CSttFrame_MacroParaView*)AddNewChild(new CSttFrame_MacroParaView());
	}

	if (m_pReprotView == NULL)
	{
		m_pReprotView = (CSttFrame_ReportView*)AddNewChild(new CSttFrame_ReportView());
	}

	if (m_pRightPanes == NULL)
	{
		m_pRightPanes = (CSttFrame_RightPanes*)AddNewChild(new CSttFrame_RightPanes());
	}

	if (m_pStatusBar == NULL)
	{
		m_pStatusBar = (CSttFrame_StatusBar*)AddNewChild(new CSttFrame_StatusBar());
	}

// 	if (m_pResultBar == NULL)
// 	{
// 		m_pResultBar = (CSttFrame_ResultBar*)AddNewChild(new CSttFrame_ResultBar());
// 	}

	//2023-1-4  lijunqing
	g_nComBoxItemHeight = GetComBoxItemHeight();
	g_nTableVertScrollWidth = GetTableVertScrollWidth();
	g_nTableHorizontalScrollHeight =GetTableHorizontalScrollHeight();
	g_nTreeVertScrollWidth = GetTreeVertScrollWidth();
	g_nTreeHorizontalScrollHeight = GetTreeHorizontalScrollHeight();
	g_nComBoxVertScrollWidth=GetComBoxVertScrollWidth();

	/*g_nVertScrollWidth = GetVertScrollWidth();
	g_nLevelScrollHeight = GetLevelScrollHeight();
	g_nComBoxVertScrollWidth=GetComBoxVertScrollWidth();
	g_nTreeVertScrollWidth=GetQTreeWidgetVertScrollWidth();
	g_nTreeLevelWidth=GetQTreeWidgetLevelScrollWidth();
	g_nGooseVertWidth=GetGooseVertScrollWidth();
	g_nGooseLevelWidth=GetGooseLevelScrollWidth();
	g_nCustomVertWidth=GetCustomSetVertScrollWidth();
	g_nCustomLevelWidth=GetCustomSetLevelScrollWidth();
	g_nLeadInVertWidth=GetLeadingInVertScrollWidth();
	g_nLeadLevelWidth=GetLeadingLevelScrollWidth();*/
}

BOOL CSttFrameConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrameConfig *p = (CSttFrameConfig*)pObj;

	if(m_nHeight != p->m_nHeight)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttFrameConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrameConfig *p = (CSttFrameConfig*)pDest;

	p->m_nHeight = m_nHeight;
	p->m_nWidth = m_nWidth;

	return TRUE;
}

CBaseObject* CSttFrameConfig::Clone()
{
	CSttFrameConfig *p = new CSttFrameConfig();
	Copy(p);
	return p;
}

CBaseObject* CSttFrameConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrameConfig *p = new CSttFrameConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrameConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		return TRUE;
	}
	if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATAS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_MENUS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_TOOLBAR)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_GBTREE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_MACROPARAVIEW)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_REPORTVIEW)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_RIGHTPANES)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_STATUSBAR)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTFRAME_RESULTBAR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrameConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_FontKey)
	{
		pNew = new CSttFrame_Font();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_GlobalDatasKey)
	{
		pNew = new CSttFrame_GlobalDatas();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_MenusKey)
	{
		pNew = new CSttFrame_Menus();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_ToolBarKey)
	{
		pNew = new CSttFrame_ToolBar();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_GbTreeKey)
	{
		pNew = new CSttFrame_GbTree();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_MacroParaViewKey)
	{
		pNew = new CSttFrame_MacroParaView();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_ReportViewKey)
	{
		pNew = new CSttFrame_ReportView();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_RightPanesKey)
	{
		pNew = new CSttFrame_RightPanes();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_StatusBarKey)
	{
		pNew = new CSttFrame_StatusBar();
	}
	else if (strClassID == pXmlKeys->m_strCSttFrame_ResultBarKey)
	{
		pNew = new CSttFrame_ResultBar();
	}

	return pNew;
}

CExBaseObject* CSttFrameConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_FONT)
	{
		pNew = new CSttFrame_Font();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATAS)
	{
		pNew = new CSttFrame_GlobalDatas();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_MENUS)
	{
		pNew = new CSttFrame_Menus();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_TOOLBAR)
	{
		pNew = new CSttFrame_ToolBar();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_GBTREE)
	{
		pNew = new CSttFrame_GbTree();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_MACROPARAVIEW)
	{
		pNew = new CSttFrame_MacroParaView();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_REPORTVIEW)
	{
		pNew = new CSttFrame_ReportView();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_RIGHTPANES)
	{
		pNew = new CSttFrame_RightPanes();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_STATUSBAR)
	{
		pNew = new CSttFrame_StatusBar();
	}
	else if (nClassID == MNGRCLASSID_CSTTFRAME_RESULTBAR)
	{
		pNew = new CSttFrame_ResultBar();
	}

	return pNew;
}

BOOL CSttFrameConfig::Open(const CString &strFrameCfgFile)
{
	ASSERT (CSttTestCtrlFrameCfgMngrXmlRWKeys::g_pXmlKeys != NULL);
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += strFrameCfgFile;
	m_strMacroFileID = _T("");
	long nIndex = strFrameCfgFile.ReverseFind('\\');

	if (nIndex < 0)
	{
		nIndex = strFrameCfgFile.ReverseFind('/');
	}

	if (nIndex>0)
	{
		if (!IsFileExist(m_strFile))
		{
			m_strFile = (CString)_P_GetConfigPath();
			m_strFile += strFrameCfgFile.Mid(nIndex+1);
		}
		else
		{
			m_strMacroFileID = strFrameCfgFile.Left(nIndex);
		}
	}

	return OpenFile(m_strFile);
}

CSttFrame_GlobalDatas* CSttFrameConfig::GetGlobalDatas()
{	
	if (m_pGlobalDatas == NULL)
	{
        m_pGlobalDatas = (CSttFrame_GlobalDatas*)FindByClassID(MNGRCLASSID_CSTTFRAME_GLOBALDATAS);

		if (m_pGlobalDatas == NULL)
		{
			m_pGlobalDatas = new CSttFrame_GlobalDatas();
			AddNewChild(m_pGlobalDatas);
		}
	}

	return m_pGlobalDatas;	
}

long CSttFrameConfig::GetTabHeight()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetTabHeight();
}

long CSttFrameConfig::GetComBoxItemHeight()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetComBoxItemHeight();
}

long CSttFrameConfig::GetTableVertScrollWidth()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetTableVertScrollWidth();
}

long CSttFrameConfig::GetTableHorizontalScrollHeight()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetTableHorizontalScrollHeight();
}

long CSttFrameConfig::GetTreeVertScrollWidth()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetTreeVertScrollWidth();
}

long CSttFrameConfig::GetTreeHorizontalScrollHeight()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetTreeHorizontalScrollHeight();
}

long CSttFrameConfig::GetComBoxVertScrollWidth()
{
	CSttFrame_GlobalDatas *pGlobalDatas = GetGlobalDatas();
	return pGlobalDatas->GetComBoxVertScrollWidth();

}


BOOL CSttFrameConfig::OpenFile(const CString &strFile)
{
	return OpenXmlFile(strFile, CSttTestCtrlFrameCfgMngrXmlRWKeys::g_pXmlKeys);
}

CSttFrame_Button* CSttFrameConfig::FindStartStopBtn()
{
	CSttFrame_Button *pStartTestBtn = NULL;

	if (m_pToolBar != NULL)
	{
		pStartTestBtn = m_pToolBar->FindBtnByID(STT_CNTR_CMD_StartTest);

		if (pStartTestBtn == NULL)
		{
			pStartTestBtn = m_pToolBar->FindBtnByID(STT_CNTR_CMD_StopTest);
		}
	}

	if ((pStartTestBtn == NULL)&&(m_pStatusBar != NULL))
	{
		pStartTestBtn = m_pStatusBar->FindBtnByID(STT_CNTR_CMD_StartTest);

		if (pStartTestBtn == NULL)
		{
			pStartTestBtn = m_pStatusBar->FindBtnByID(STT_CNTR_CMD_StopTest);
		}
	}

	return pStartTestBtn;
}

CSttFrame_Button* CSttFrameConfig::FindBtnByID(const CString &strBtnID)
{
	CSttFrame_Button *pFindBtn = NULL;

	if (m_pToolBar != NULL)
	{
		pFindBtn = m_pToolBar->FindBtnByID(strBtnID);
	}

	if ((pFindBtn == NULL)&&(m_pStatusBar != NULL))
	{
		pFindBtn = m_pStatusBar->FindBtnByID(strBtnID);
	}

	return pFindBtn;
}
