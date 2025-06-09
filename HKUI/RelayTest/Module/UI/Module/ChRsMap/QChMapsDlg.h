#ifndef QChMapsDlg_H
#define QChMapsDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "QChMapsWidget.h"
#include "BinBoutMapsGrid.h"


class QChMapsDlg : public QDialog
{
	Q_OBJECT

public:
	QChMapsDlg(QWidget *parent = 0);
	~QChMapsDlg();

	void initUI();
	void ReleaseUI();
	void DisableCtrls_SysCfg();   //将系统参数部分的控件，设置为disable状态

	BOOL m_bSysParasHasChanged;

protected:
	void InitDatas();

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QHBoxLayout *m_pBottom_HBoxLayout;

	//20240905 huangliang 
	QTabWidget *m_pTabWidget;
	QChMapsWidget *m_pChMapsWidget;
	CBinBoutMapsGrid *m_pBinMapsGrid;
	CBinBoutMapsGrid *m_pBoutMapsGrid;

	QPushButton *m_pDefautMaps_PButton;//生成缺省通道映射
	QPushButton *m_pImportChMaps_PButton;//导入通道映射文件
	QPushButton *m_pExportChMaps_PButton;//导出通道映射文件

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	QCheckBox *m_pLockMaps_CheckBox;//锁定映射

	CSttChMaps m_oSttChMaps;	
	STT_SystemParas m_oSysParas;

	CExBaseList m_olistBin;	//20240921 huangliang 界面编辑链表
	CExBaseList m_olistBout;
	void SetGridShowDatas();		//20240905 huangliang  设置3个表格数据

public:
signals:
	void sig_UpdateChRsMaps(BOOL bSysParasHasChanged);

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

	void slot_DefautMapsClicked();
	void slot_ImportChMapsClicked();
	void slot_ExportChMapsClicked();
    void slot_LockMapsChecked(int);//wangtao1 20240508
};

#endif // QChMapsDlg_H
