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

	void InitUI();//��ʼ��������������
	void SetIecConfigFont();//2022-10-25 ������������

	QGridLayout *m_pSttIecConfigMainLayout;//�����Ի���Ĳ���
	QSplitter *m_pSttIecConfigSplitter;//�����Ի�����з���ͼ
	QTreeWidget *m_IecConfigNavigationTree; //��ർ����
	int m_nIecConfigNavigationTreeIndex;//����������
	QTabWidget *m_pIecConfigRightTabWidget;
	QStackedWidget *m_pIecConfigRightStackedWidget;//��ջ����,����ʵ�ֶ������л���ʾ

	QToolBar *m_pSttIecConfigToolBar;
	QToolButton *m_pOpenCfgToolBtn;
	QToolButton *m_pSaveAsCfgToolBtn;
	QToolButton *m_pImportSCLToolBtn;
	QToolButton *m_pSaveToolBtn;
	QToolButton *m_pCancelToolBtn;

	CSclStation   *m_pSclStation;

#ifdef IecCfgSysParas_USE_Grid
	QSttIecSysCfgWidget *m_pSysParasWidget;//ϵͳ��������
#else
	QSttSysParasWidget *m_pSysParasWidget;//ϵͳ��������
#endif
	QSttIecSMV92Widget *m_pIecSMV92OutWidget;
	QSttIecSMVFT3OutWidget *m_pIecSMVFT3OutWidget;
	QSttIecSMV92InWidget *m_pIecSMV92InWidget;
	QSttIecSMVFT3InWidget *m_pIecSMVFT3InWidget;
	QSttIecGinWidget *m_pIecGinWidget;
	QSttIecGoutWidget *m_pIecGoutWidget;

protected:
	QHash<QTreeWidgetItem *, int > m_oTreeStackedWidgetHash; //�������νڵ����Ҳ���ͼ����֮��Ĺ���
	QList<CIecConfigInterface *> m_oRightStackedWidgetList;
	CIecCfgDatasMngr *m_pIecCfgDatasMngr_Inter;//�ڲ�������ʾʹ�õ�IEC���ö���
	QFont m_oIecFont;
	QIcon  m_oIconTree;
	bool m_bTotalFiberNum_LC,m_bTotalFiberNum_STSend; //20240520 suyang ���Ӷ�LC��ں�ST����жϣ��Կ��ƿ�����ѡ��һ�����ж�

private:
	CIecCfgDatasMngr *m_pIecCfgDatasMngr_Extern;//�ⲿ�����IEC���ö���
//	QSclFileRead  m_oSclFileRead;


protected:
	bool eventFilter(QObject *obj, QEvent *event);

	void ReleaseUI();//�ͷ���������
	void CreateToolBar();//����������,�ú�����InitUI�е���
	void CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend);
	
	void InitData();
	//���ڹر�
	virtual void closeEvent ( QCloseEvent * event );

signals:
	void sig_IecCfgDataMngrUpdate();//���ⲿ����IEC������Ϣ
	void sig_IecCfg_New();  //���ⲿ���ʹ�������IEC61850Config��������Ŀ����Ϣ

protected slots:
	void slot_OpenCfgBtnClicked();
	void slot_SaveAsCfgBtnClicked();
	void slot_ImportSCLBtnClicked();
	void slot_IecCfgDataMngrUpdate();
	//�����ļ�
	void slot_SaveBtnClicked();////
	//ȡ�����˳�����
	void slot_CancelBtnClicked();

	void slot_TreeItemClicked(QTreeWidgetItem * item, int column );
	void slot_TreeItemChanged(QTreeWidgetItem * item, int column );

public:
	CString OpenixmlFileDlg(BOOL bIsOpen = TRUE);

};

#endif // QSTTIECCONFIGDIALOG_H
