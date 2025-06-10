#ifndef QSYSPARASDLG_H
#define QSYSPARASDLG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../ChRsMap/QChMapsWidget.h"
#include "QWeakSetWidget.h"
#include "QSysParasWidget.h"
#include "../ModuleSetDlg/QModuleSetWidget.h"
#include "../../../Module/SttTest/Common/tmt_system_config.h"

class QSysParasDlg : public QDialog
{
	Q_OBJECT

public:
	QSysParasDlg(QWidget *parent = 0);
	~QSysParasDlg();

	void initUI();
	void ReleaseUI();
	void DisEnableDigitalUI();
	void DisEnableWeekUI();

	BOOL m_bOutputTypeHasChanged;
	UINT m_nSysConfig_Mode;

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

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_TabChanged(QWidget *);
};

#endif // PLOTWIDGET_H
