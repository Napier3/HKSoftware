#ifndef FT3PARAWIDGET_H
#define FT3PARAWIDGET_H

#include "FT3Widget.h"
#include <QWidget>
#include <QTabWidget>
#include "../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
class QFT3ParaWidget : public QWidget
{
	Q_OBJECT

public:
	QFT3ParaWidget(CIecCfgDatasSMV *pIecCfgDatasSMV);
	~QFT3ParaWidget();

	void initUI();
	void InitFT3Table(CIecCfgDatasSMV *pIecCfgDatasSMV);
	void initOneFT3BlockTable(FT3Widget *p,CIecCfg6044CommonData *pCfg6044CommonData);

	void SetRunState(int nRunState);
	void SetGooseDisabled(bool bFlag);

private:
	QTabWidget* m_tab_FT3Pub;
	QList<FT3Widget *> m_pFT3WidgetList;
	
signals:
	void sig_FT3DataChanged();

protected slots:
	void slot_FT3DataChanged();
};
#endif