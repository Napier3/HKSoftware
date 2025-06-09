#ifndef	QSCLCHECKSETTINGWIDGET
#define QSCLCHECKSETTINGWIDGET
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QTabWidget>
#include "QSchemaCheckSettingGrid.h"
#include "QMannualCheckSettingGrid.h"
#include "ui_QSCLCheckSettingWidget.h"
#include "..\SclCheckDataMngr\SclCheckObjectsSet.h"

class QSCLCheckSettingWidget:public QDialog
{
	Q_OBJECT

public:
		
	QSCLCheckSettingWidget(QWidget* pparent = NULL);
	virtual ~QSCLCheckSettingWidget();
	
	Ui::QCheckSetting ui;
	void InitUI();
	void GetConfigs();
	void SetConfigs();
	void UpdateGrids();
	
	QSchemaCheckSettingGrid *m_pSchemaSettingGrid;
	QMannualCheckSettingGrid *m_pDL860CheckSettingGrid;
	QMannualCheckSettingGrid *m_pProModCheckSettingGrid;
	QMannualCheckSettingGrid *m_pVirtualLoopCheckSettingGrid;

	CSclCheckObjectsSet m_oSclCheckObjects;
	CSchemaChecks *m_pSchemaSettings;
	CDLT860ModelChecks *m_pDL860CheckSettings;
	CProjAppModelChecks *m_pProModCheckSettings;
	CVirLoopChecks *m_pVirtualLoopCheckSettings;


	CString m_strCheckSettingConfigPath;

public slots:
	void slot_m_OK_Btn_Clicked();
	void slot_m_Cancel_Btn_Clicked();
	void slot_SelectAll();
	void slot_UnSelectAll();
	void slot_Reverse();

signals:
	void sig_UpdateConfigs();
};


#endif
