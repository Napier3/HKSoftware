#pragma once
#ifndef QIECDETCETWIDGET_H
#define QIECDETCETWIDGET_H

#include <QWidget>
#include "ui_QIecDetcetWidget.h"
#include "SttIecCbGrid.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDeviceMngr.h"
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"

class QIecDetcetWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QIecDetcetWidget(QWidget *pparent = NULL);
	~QIecDetcetWidget();

	BOOL m_bDetect;
	CSttIecCbGrid *m_pGridIecCb;
	CCapDeviceMngr m_oCapDeviceAll;  //检测、探测到的全部装置
	CCapDeviceMngr m_oRecordDevice; //录波的装置

	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);


//	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj 查找SCD,根据SCD文件中对应的AppID更新当前控制块内容

private:
	Ui::QIecDetcetWidget ui;


signals:
//	void sig_AddNewDevice(CCapDeviceBase *pCapDevice);

public slots:
	void slot_On_m_BtnStartDetect_clicked();
	void slot_On_m_BtnStopDetect_clicked();
	void slot_On_m_BtnClearDetect_clicked();
//	void on_AddNewDevice(CCapDeviceBase *pCapDevice);
	
};

#endif // QIECDETCETWIDGET_H
