#ifndef FT3OUTPARAWIDGET_H
#define FT3OUTPARAWIDGET_H

#include "FT3OutWidget.h"
#include <QWidget>
#include <QTabWidget>
#include "../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
class QFT3OutParaWidget : public QWidget
{
	Q_OBJECT

public:
	QFT3OutParaWidget(CIecCfgDatasSMV *pIecCfgDatasSMV,bool bInitEditable = TRUE);
	~QFT3OutParaWidget();

	void initUI();
	void InitFT3Table(CIecCfgDatasSMV *pIecCfgDatasSMV);
	void initOneFT3BlockTable(FT3OutWidget *p,CIecCfg6044CommonData *pCfg6044CommonData);

	void SetRunState(int nRunState);
	void SetRunState();
	void SetGooseDisabled(bool bFlag);
	void SetGooseDisabled();
	BOOL m_bFt3Flag;
	bool m_bFt3Disabled;
	int m_nRunState;

private:
	QTabWidget* m_tab_FT3Pub;
	QList<FT3OutWidget *> m_pFT3WidgetList;
	bool m_bInitEditable;
	
signals:
	void sig_FT3DataChanged();

protected slots:
	void slot_FT3DataChanged();
};

extern QFont *g_pSttGlobalFont; 

#endif