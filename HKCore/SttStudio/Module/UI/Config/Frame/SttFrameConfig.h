//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	long m_nWidth;//�ֱ��� sf 20220105
	long m_nHeight;

	long m_nLogDebugInfor;
	CString m_strMacroFileID;//���Թ����ļ�ID��RelayTest��MuTest��
	long m_nSelMacroShow;//�Ƿ���ʾ ѡ���� 0: ����ʾ  1�� ��ʾ

	//2023-2-26  lijunqing
	long m_nFrameBtnGap;   //��ܹ�������ť��ֱ������߿�֮��ļ��
//���غ���
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

//˽�г�Ա����
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

//˽�г�Ա�������ʷ���
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
	long GetTabHeight();//��ȡTab�ĸ߶�
	long GetComBoxItemHeight();//��ȡCombox�ؼ�����Item�߶�
	long GetTableVertScrollWidth();//��ȡTable��ֱ���������
	long GetTableHorizontalScrollHeight();//��ȡTableˮƽ�������߶�
	long GetTreeVertScrollWidth(); //��ȡTree��ֱ���������
	long GetTreeHorizontalScrollHeight(); //��ȡTreeˮƽ���������
	long GetComBoxVertScrollWidth();//��ȡcombox�����򻬶�����


/*	long GetVertScrollWidth();//��ȡ��ֱ������Ŀ��
	long GetLevelScrollHeight();//��ȡˮƽ������Ŀ��
	long GetComBoxVertScrollWidth();//��ȡcombox�����򻬶�����
	long GetQTreeWidgetVertScrollWidth();//��ȡQtree��ֱ��������
	long GetQTreeWidgetLevelScrollWidth();//��ȡQtreeˮƽ������
	long GetGooseVertScrollWidth();//��ȡGoose������ֱ������
	long GetGooseLevelScrollWidth();//��ȡGoose����ˮƽ������
	long GetCustomSetVertScrollWidth();//��ȡ�˵����Զ������ý�����ֱ������
	long GetCustomSetLevelScrollWidth();//��ȡ�˵����Զ������ý���ˮƽ������
	long GetLeadingInVertScrollWidth(); //��ȡ�˵�������ͨ��ӳ�������ֱ������
	long GetLeadingLevelScrollWidth();//��ȡ�˵�������ͨ��ӳ�����ˮƽ������
*/
	CSttFrame_Button* FindStartStopBtn();//zhouhj 20220416 ���ҿ�ʼֹͣ���԰�ť
	CSttFrame_Button* FindBtnByID(const CString &strBtnID);


//���Ա������ʷ���
public:
	BOOL Open(const CString &strFrameCfgFile);
	BOOL OpenFile(const CString &strFile);
};

