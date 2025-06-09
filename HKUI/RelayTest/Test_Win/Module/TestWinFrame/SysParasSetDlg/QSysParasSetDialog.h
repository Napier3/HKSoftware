#ifndef _QSysParasSetDialog_H
#define _QSysParasSetDialog_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "QChMapsWidget.h"
#include "QWeakSetWidget.h"
#include "QSysParasWidget.h"
#include "QModuleSetWidget.h"
#include "../../../../Module/SttTest/Common/tmt_system_config.h"

class QSysParasSetDialog : public QDialog
{
	Q_OBJECT

public:
	QSysParasSetDialog(QWidget *parent = 0);
	~QSysParasSetDialog();

	void initUI();
	void ReleaseUI();
	void DisEnableDigitalUI();
	void DisEnableWeekUI();

	BOOL m_bOutputTypeHasChanged;

protected:
	void InitDatas();

	QVBoxLayout *m_pVLayout;
	QTabWidget *m_tabWidget;

//	QChMapsWidget *m_pChMapsWiget;
	QWeakSetWidget *m_pWeakSetWiget;
	QSysParasWidget *m_pSysParasWiget;
//	QModuleSetWidget *m_pModuleSetWiget;

	QHBoxLayout *m_pHBoxLayout;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CSttChMaps m_oSttChMaps;
	STT_SystemParas m_oSysParas;

signals:
//	void sig_SysParasHasChanged(BOOL bChMapsHasChanged);//发送系统参数改变信号

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_TabChanged(QWidget *);
};

#endif // PLOTWIDGET_H
