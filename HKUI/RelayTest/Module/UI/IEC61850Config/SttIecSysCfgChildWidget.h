#ifndef STTIECSYSCFGCHILDWIDGET_H
#define STTIECSYSCFGCHILDWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "Grid/IecCfgPrimRateGrid.h"
#include "Grid/IecCfgFiberSetGrid.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

#define STT_IECSYS_WIDGET_TYPE_SmvOutRate                0
#define STT_IECSYS_WIDGET_TYPE_SmvInRate                 1
#define STT_IECSYS_WIDGET_TYPE_FiberSet                  2
#define STT_IECSYS_WIDGET_TYPE_FiberInSet                3


class QSttIecSysCfgChildWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIecSysCfgChildWidget(QFont oIecFont,long nSysParaType,QWidget *parent = NULL);
	~QSttIecSysCfgChildWidget();

	virtual void InitData(CIecCfgSysParas* pIecCfgSysParas);
	virtual void SaveData();
	void SetEnableState(bool bEnable);

protected:
	void InitUI();
	void GetSmvOutRateList(CIecCfgPrimRates* pPrimRates);
	void GetSmvInRateList(CIecCfgPrimRatesIn *pPrimRates);
	void GetFiberSetList(CIecCfgFiberParas *pIecCfgFiberParas);
	void GetFiberInSetList(CIecCfgFiberParasIn *pIecCfgFiberParasIn);


	QHBoxLayout *m_pMain_HBoxLayout;
	QExBaseListGridBase *m_pLeft_SysCfgChildGrid;
	QExBaseListGridBase *m_pRight_SysCfgChildGrid;

private:
	long m_nSysParaType;
	CExBaseList m_oLeftList;
	CExBaseList m_oRightList;
	QFont m_oIecFont;
};

extern CFont *g_pSttGlobalFont;  

#endif // STTIECSYSCFGCHILDWIDGET_H
