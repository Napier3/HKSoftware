#ifndef QSTTSCLFILEPARSEDIALOG_H
#define QSTTSCLFILEPARSEDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QGridLayout>
#include <QSplitter>
#include <QLabel>
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../Controls/SttLineEdit.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttSclCtrlsWidget.h"
//#include "./SCDView/SttSclIedViewWidget.h"
#include <QToolButton>

//2023/9/19 wjs 
#include "Grid/QSclSelectCtrlsGrid.h"
#include "Grid/SclCtrlChsGridBase.h"

#include "../Module/CommonCtrl_QT/QSttProgDlg.h"
#include "SCDView/SttSclIedSketchMapWidget.h"

//#define  USE_STT_SCLIED_VIEW


class QSttSclFileParseDialog : public QDialog
{
	Q_OBJECT

public:
	QSttSclFileParseDialog(CSclStation  *pSclStation,QFont oFont , QWidget *parent = NULL);
	virtual ~QSttSclFileParseDialog();

	void InitUI();//初始化创建整个界面
	void InitIecCfgDatasMngr(CIecCfgDatasMngr *pIecCfgDatasMngr)
	{
		m_pIecCfgDatasMngr = pIecCfgDatasMngr;
	}

    void UpdateIedSearchEditFocus();//更新对应焦点

	QVBoxLayout *m_pSclFileIED_MainLayout;//整个对话框的布局
	QSplitter *m_pSclFileIED_Splitter;//整个对话框的切分视图
	QTreeWidget *m_pSclFileIED_TreeWidget; //
	QTabWidget *m_pSclFileIedCtrls_TabWidget;
	QWidget *m_pSplitterLeftWidget;
	QVBoxLayout *m_pSplitterLeft_VBoxLayout;
	QHBoxLayout *m_pIedSearch_HBoxLayout;
	QHBoxLayout *m_pSclFileBottom_HBoxLayout;
	QLabel *m_pFind_Label;
	QSttLineEdit *m_pIedSearch_LineEdit;
	QPushButton *m_pSCLSelect_PushButton;
	QPushButton *m_pOneKeyCfg_PushButton;
	QPushButton *m_pImportIecCfg_PushButton;
	QPushButton *m_pCancel_PushButton;

	QSttSclCtrlsWidget *m_pGooseOutWidget;
	QSttSclCtrlsWidget *m_pGooseInWidget;
	QSttSclCtrlsWidget *m_pSmvOutWidget;
	QSttSclCtrlsWidget *m_pSmvInWidget;

// #ifdef USE_STT_SCLIED_VIEW
// 	QSttSclIedViewWidget *m_pIedViewWidget;  //lichao添加图形界面
// #endif
	QSttSclIedSkectMapWidget *m_pSttSclSkectMapWidget;//chenling 示意图
	//2023/9/19 wjs 添加控件
	QVBoxLayout *m_pSplitterRight_VBoxLayout;
	QWidget *m_pSplitterRightWidget;

	QSplitter *m_pLeftDownSplitter;//左对话框的切分视图
	QVBoxLayout *m_pLeftDown_VBoxLayout;
	QWidget* m_pLeftDownWidget;

	QSclSelectCtrlsGrid *m_pSclSelectCtrlsGrid;
	QSttProgDlg *m_pSttSclParseProgDlg;

	HANDLE m_pSttSclViewDatasParseThread;
//#ifdef USE_STT_SCLIED_VIEW
#ifdef _PSX_QT_LINUX_
	static void* SttSclViewDatasParseThread(LPVOID pParam);
#else
	static UINT SttSclViewDatasParseThread(LPVOID pParam);	
#endif
//#endif


protected:
	CSclStation  *m_pSclStation;
	CIecCfgDatasMngr *m_pIecCfgDatasMngr;
	CSclIed *m_pCurrSelSclIed;
	CSclCtrls m_oSelectedSclCtrlsRef;
	CString m_strSearchText;
	QFont m_oIecFont;

protected:
	bool eventFilter(QObject *obj, QEvent *event);

	void ReleaseUI();//释放整个界面
	void CreateSclFileIEDTree();
	
	void InitData();
	void InitIedInforDatas();  //lichao初始化图形界面数据
	void ShowSclIedDetail(CSclIed *pSclIed);
	void AddGridCtrls(CSclCtrls *pSclCtrls);
	void UpdateIedTreeBySearchText(const CString &strSearchText);

	//窗口关闭
	virtual void closeEvent ( QCloseEvent * event );
	void SetSclFileParseFont();

signals:
	void sig_IecCfgDataMngrUpdate();//向外部发送IEC更新消息
	//void sig_SelectCtrlsGridGetData(QExBaseListGridBase *);

protected slots:
	void slot_OneKeyCfgBtnClicked();
	void slot_SCLSelectBtnClicked();
	void slot_ImportIecCfgBtnClicked();
	void slot_CancelBtnClicked();

	void slot_TreeItemClicked(QTreeWidgetItem * item, int column );
	void slot_IedSearchtextclicked();
	void slot_IedSearchtextChanged(/*const QString &text*/);
	//void slot_UpdateCurrentChsGrid();

public slots:
	void slot_UpdateSelectCtrlsGrid();
	void slot_UpdateSketchMapWidgetSize(int pos, int index);
};

extern QFont *g_pSttGlobalFont;

#endif // QSTTSCLFILEPARSEDIALOG_H
