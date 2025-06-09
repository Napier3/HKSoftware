//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrameConfig.h  CSttFrameConfig

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"


#include "SttFrame_Font.h"
#include "SttFrame_Menus.h"
#include "SttFrame_XBar.h"
#include "SttFrame_GbTree.h"
#include "SttFrame_MacroParaView.h"
#include "SttFrame_ReportView.h"
#include "SttFrame_RightPanes.h"
#include "SttFrame_GlobalDatas.h"

class CSttFrameConfig : public CExBaseList
{
private:
	CSttFrameConfig();
	virtual ~CSttFrameConfig();

public:
	static CSttFrameConfig* g_pSttFrameConfig;
	static long g_nSttFrameConfig;

	static CSttFrameConfig* Create(const CString &strFrameCfgFile);
	static void Release();

	CString	 m_strFile;  

	long m_nWidth;//分辨率 sf 20220105
	long m_nHeight;

	long m_nLogDebugInfor;
	CString m_strMacroFileID;//测试功能文件ID：RelayTest、MuTest等
	long m_nSelMacroShow;//是否显示 选择功能 0: 不显示  1： 显示

	//2023-2-26  lijunqing
	long m_nFrameBtnGap;   //框架工具栏按钮垂直方向与边框之间的间隔
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAMECONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrameConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CSttFrame_Font *m_pFont;
	CSttFrame_Menus *m_pMenus;
	CSttFrame_ToolBar *m_pToolBar;
	CSttFrame_GbTree *m_pGbTree;
	CSttFrame_MacroParaView *m_pMacroParaView;
	CSttFrame_ReportView *m_pReprotView;
	CSttFrame_RightPanes *m_pRightPanes;
	CSttFrame_StatusBar *m_pStatusBar;
	CSttFrame_ResultBar *m_pResultBar;
	CSttFrame_GlobalDatas *m_pGlobalDatas;

//私有成员变量访问方法
public:
	CSttFrame_Font* GetFont()	{	return m_pFont;	}
	void SetFont(CSttFrame_Font* pFont)	{	m_pFont = pFont;	}
	CSttFrame_Menus* GetMenus()	{	return m_pMenus;	}
	void SetMenus(CSttFrame_Menus* pMenus)	{	m_pMenus = pMenus;	}
	CSttFrame_ToolBar* GetToolBar()	{	return m_pToolBar;	}
	void SetToolBar(CSttFrame_ToolBar* pToolBar)	{	m_pToolBar = pToolBar;	}
	CSttFrame_GbTree* GetGbTree()	{	return m_pGbTree;	}
	void SetGbTree(CSttFrame_GbTree* pGbTree)	{	m_pGbTree = pGbTree;	}
	CSttFrame_MacroParaView* GetMacroParaView()	{	return m_pMacroParaView;	}
	void SetMacroParaView(CSttFrame_MacroParaView* pMacroParaView)	{	m_pMacroParaView = pMacroParaView;	}
	CSttFrame_ReportView* GetReprotView()	{	return m_pReprotView;	}
	void SetReprotView(CSttFrame_ReportView* pReprotView)	{	m_pReprotView = pReprotView;	}
	CSttFrame_RightPanes* GetRightPanes()	{	return m_pRightPanes;	}
	void SetRightPanes(CSttFrame_RightPanes* pRightPanes)	{	m_pRightPanes = pRightPanes;	}
	CSttFrame_StatusBar* GetStatusBar()	{	return m_pStatusBar;	}
	void SetStatusBar(CSttFrame_StatusBar* pStatusBar)	{	m_pStatusBar = pStatusBar;	}
	CSttFrame_ResultBar* GetResultBar()	{	return m_pResultBar;	}
	void SetResultBar(CSttFrame_ResultBar* pResultBar)	{	m_pResultBar = pResultBar;	}

	CSttFrame_GlobalDatas* GetGlobalDatas();
    void SetGlobalDatas(CSttFrame_GlobalDatas* pGlobalDatas){	m_pGlobalDatas = pGlobalDatas;	}
	long GetTabHeight();//获取Tab的高度
	long GetComBoxItemHeight();//获取Combox控件单个Item高度
	long GetTableVertScrollWidth();//获取Table垂直滚动条宽度
	long GetTableHorizontalScrollHeight();//获取Table水平滚动条高度
	long GetTreeVertScrollWidth(); //获取Tree垂直滚动条宽度
	long GetTreeHorizontalScrollHeight(); //获取Tree水平滚动条宽度
	long GetComBoxVertScrollWidth();//获取combox下拉框滑动块宽度


/*	long GetVertScrollWidth();//获取竖直滑动块的宽度
	long GetLevelScrollHeight();//获取水平滑动块的宽度
	long GetComBoxVertScrollWidth();//获取combox下拉框滑动块宽度
	long GetQTreeWidgetVertScrollWidth();//获取Qtree竖直滑动块宽度
	long GetQTreeWidgetLevelScrollWidth();//获取Qtree水平滑块宽度
	long GetGooseVertScrollWidth();//获取Goose界面竖直滑块宽度
	long GetGooseLevelScrollWidth();//获取Goose界面水平滑块宽度
	long GetCustomSetVertScrollWidth();//获取菜单栏自定义设置界面竖直滑块宽度
	long GetCustomSetLevelScrollWidth();//获取菜单栏自定义设置界面水平滑块宽度
	long GetLeadingInVertScrollWidth(); //获取菜单栏导入通道映射界面竖直滑块宽度
	long GetLeadingLevelScrollWidth();//获取菜单栏导入通道映射界面水平滑块宽度
*/
	CSttFrame_Button* FindStartStopBtn();//zhouhj 20220416 查找开始停止测试按钮
	CSttFrame_Button* FindBtnByID(const CString &strBtnID);


//属性变量访问方法
public:
	BOOL Open(const CString &strFrameCfgFile);
	BOOL OpenFile(const CString &strFile);
};

