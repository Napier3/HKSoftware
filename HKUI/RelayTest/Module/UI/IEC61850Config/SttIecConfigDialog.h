#ifndef QSTTIECCONFIGDIALOG_H
#define QSTTIECCONFIGDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QGridLayout>
#include <QSplitter>

#include "SttIecConfigGlobalDef.h"
#include "SttIecSysParasWidget.h"
#include "SttIecSysCfgWidget.h"
#include "SttIecSMV92Widget.h"
#include "SttIecSMV92InWidget.h"
#include "SttIecSMVFT3OutWidget.h"
#include "SttIecSMVFT3InWidget.h"
#include "SttIecGinWidget.h"
#include "SttIecGoutWidget.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../../61850/Module/SCL_Qt/QSclFileRead.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../Controls/SttToolButtonBase.h"
#include <QToolButton>

#define IecCfgSysParas_USE_Grid
#define STT_IECCONFIG_TREE_LEVEL_TOP                                             0
#define STT_IECCONFIG_TREE_LEVEL_SECOND                                          1

class QSttIecConfigDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecConfigDialog(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent = NULL);
	~QSttIecConfigDialog();

	void InitUI();//初始化创建整个界面
	void SetIecConfigFont();//2022-10-25 增加字体设置

	QGridLayout *m_pSttIecConfigMainLayout;//整个对话框的布局
	QSplitter *m_pSttIecConfigSplitter;//整个对话框的切分视图
	QTreeWidget *m_IecConfigNavigationTree; //左侧导航树
	int m_nIecConfigNavigationTreeIndex;//导航树索引
	QTabWidget *m_pIecConfigRightTabWidget;
	QStackedWidget *m_pIecConfigRightStackedWidget;//堆栈窗体,用于实现多界面的切换显示

	QToolBar *m_pSttIecConfigToolBar;
	QToolButton *m_pOpenCfgToolBtn;
	QToolButton *m_pSaveAsCfgToolBtn;
	QToolButton *m_pImportSCLToolBtn;
	QToolButton *m_pSaveToolBtn;
	QToolButton *m_pCancelToolBtn;

	CSclStation   *m_pSclStation;

#ifdef IecCfgSysParas_USE_Grid
	QSttIecSysCfgWidget *m_pSysParasWidget;//系统参数界面
#else
	QSttSysParasWidget *m_pSysParasWidget;//系统参数界面
#endif
	QSttIecSMV92Widget *m_pIecSMV92OutWidget;
	QSttIecSMVFT3OutWidget *m_pIecSMVFT3OutWidget;
	QSttIecSMV92InWidget *m_pIecSMV92InWidget;
	QSttIecSMVFT3InWidget *m_pIecSMVFT3InWidget;
	QSttIecGinWidget *m_pIecGinWidget;
	QSttIecGoutWidget *m_pIecGoutWidget;

protected:
	QHash<QTreeWidgetItem *, int > m_oTreeStackedWidgetHash; //导航树形节点与右侧视图窗体之间的关联
	QList<CIecConfigInterface *> m_oRightStackedWidgetList;
	CIecCfgDatasMngr *m_pIecCfgDatasMngr_Inter;//内部界面显示使用的IEC配置对象
	QFont m_oIecFont;
	QIcon  m_oIconTree;
	bool m_bTotalFiberNum_LC,m_bTotalFiberNum_STSend; //20240520 suyang 增加对LC光口和ST光口判断，对控制块至少选择一个做判断

private:
	CIecCfgDatasMngr *m_pIecCfgDatasMngr_Extern;//外部传入的IEC配置对象
//	QSclFileRead  m_oSclFileRead;


protected:
	bool eventFilter(QObject *obj, QEvent *event);

	void ReleaseUI();//释放整个界面
	void CreateToolBar();//创建工具栏,该函数在InitUI中调用
	void CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend);
	
	void InitData();
	//窗口关闭
	virtual void closeEvent ( QCloseEvent * event );

signals:
	void sig_IecCfgDataMngrUpdate();//向外部发送IEC更新消息
	void sig_IecCfg_New();  //向外部发送创建单个IEC61850Config电气量项目的消息

protected slots:
	void slot_OpenCfgBtnClicked();
	void slot_SaveAsCfgBtnClicked();
	void slot_ImportSCLBtnClicked();
	void slot_IecCfgDataMngrUpdate();
	//保存文件
	void slot_SaveBtnClicked();////
	//取消（退出程序）
	void slot_CancelBtnClicked();

	void slot_TreeItemClicked(QTreeWidgetItem * item, int column );
	void slot_TreeItemChanged(QTreeWidgetItem * item, int column );

public:
	CString OpenixmlFileDlg(BOOL bIsOpen = TRUE);

};



#endif // QSTTIECCONFIGDIALOG_H
