#ifndef FT3OUTWIDGET_H
#define FT3OUTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "IecCfgFT3OutGrid.h"
#include "../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgChsBase.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"

class QFT3OutParaWidget;
class FT3OutWidget : public QWidget
{
	Q_OBJECT

public:
	FT3OutWidget(QFT3OutParaWidget *pParaWidget,QWidget *parent = 0);
	~FT3OutWidget();

	void InitUI();
	void InitData(CIecCfg6044CommonData *pIecCfg6044CommonData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
	IecCfgFT3OutGrid *m_pIecCfgFT3OutGrid;
	QFT3OutParaWidget *m_pParent;

private:	
	QVBoxLayout *m_pMainLayout;

private slots:
	void slot_dataChanged();

signals:
	void sig_FT3DataChanged();
};

extern QFont *g_pSttGlobalFont; 

#endif