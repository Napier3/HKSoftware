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
	CCapDeviceMngr m_oCapDeviceAll;  //��⡢̽�⵽��ȫ��װ��
	CCapDeviceMngr m_oRecordDevice; //¼����װ��

	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);


//	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj ����SCD,����SCD�ļ��ж�Ӧ��AppID���µ�ǰ���ƿ�����

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
