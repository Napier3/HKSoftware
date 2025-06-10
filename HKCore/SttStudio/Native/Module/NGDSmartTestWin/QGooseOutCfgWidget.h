#ifndef QGOOSEOUTCFGWIDGET_H
#define QGOOSEOUTCFGWIDGET_H

#include <QWidget>
#include "ui_QGooseOutCfgWidget.h"
#include "SttIecCbGrid.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDeviceMngr.h"
#include "IecCfgChsGrid.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "IecCfgGooseDataGrid.h"

class QGooseOutCfgWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QGooseOutCfgWidget(QWidget *parent = NULL);
	~QGooseOutCfgWidget();

	//CSttIecCbGrid *m_pGridIecCb;
	CCapDeviceMngr m_oRecordDevice; //¼����װ��
	CSclStation *m_pSclStation;
	CIecCfgGooseDataGrid *m_pIecGoutDataGrid;

	CIecCfgChsGrid *m_pIecCfgGOutChsGrid;//Goose�������ñ��

	void SetSCLStation(CSclStation *pSclStation);
	void initData(CIecCfgGoutDatas* IecCfgGoutDatas);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public slots:
	void slot_UpdateCB_ChDatas(CExBaseList *pCurrSelData);

private:
	Ui::QGooseOutCfgWidget ui;
	
};

#endif // QGOOSEOUTCFGWIDGET_H
