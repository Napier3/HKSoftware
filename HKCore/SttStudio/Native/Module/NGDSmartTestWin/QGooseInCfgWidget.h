#pragma once
#ifndef QGOOSECFGWIDGET_H
#define QGOOSECFGWIDGET_H

#include <QWidget>
#include "ui_QGooseInCfgWidget.h"
#include "SttIecCbGrid.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDeviceMngr.h"
#include "IecCfgChsGrid.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "IecCfgGooseDataGrid.h"

class QGooseInCfgWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QGooseInCfgWidget(QWidget *pparent = NULL);
	~QGooseInCfgWidget();

	CSttIecCbGrid *m_pGridIecCb;
	CCapDeviceMngr m_oRecordDevice; //录波的装置
	CSclStation *m_pSclStation;

	CIecCfgGooseDataGrid* m_pIecCfgGooseInDataGrid;//Goose订阅控制块表格
	CIecCfgChsGrid *m_pIecCfgGInChsGrid;//Goose开入配置表格

	void SetSCLStation(CSclStation *pSclStation);
	void initData(CIecCfgGinDatas* IecCfgGinDatas);//初始化界面数据
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
public slots:
		void slot_UpdateCB_ChDatas(CExBaseList *pCurrSelData);
private:
	Ui::QGooseInCfgWidget ui;

	
};

#endif // QGOOSECFGWIDGET_H
