#ifndef FT3WIDGET_H
#define FT3WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FT3Grid.h"
#include "../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgChsBase.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"

class FT3Widget : public QWidget
{
	Q_OBJECT

public:
	FT3Widget(QWidget *parent = 0);
	~FT3Widget();

	void InitUI();
	void InitData(CIecCfg6044CommonData *pIecCfg6044CommonData);
	void SetRunState(int nRunState);
	FT3Grid *m_pFT3Grid;

private:	
	QVBoxLayout *m_pMainLayout;

private slots:
	void slot_dataChanged();

signals:
	void sig_FT3DataChanged();
};
#endif