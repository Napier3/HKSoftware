#pragma once

#ifndef NGDSMARTTESTMAINWIDGET_H
#define NGDSMARTTESTMAINWIDGET_H

#include <QWidget>
#include "ui_NGDSmartTestMain.h"
#include "NGDSmartTestWinFrameBase.h"
#include "QIecDetcetWidget.h"
#include "QGooseInCfgWidget.h"
#include "QChooseDeviceWidget.h"
#include "QChooseSCDWidget.h"
#include "QGooseOutCfgWidget.h"

class NGDSmartTestMainWidget : public QWidget, public NGDSmartTestWinFrameBase
{
	Q_OBJECT

public:
	NGDSmartTestMainWidget(QWidget *parent = NULL);
	~NGDSmartTestMainWidget();


	QChooseSCDWidget m_oChooseSCDWidget;
	QIecDetcetWidget m_oIecDetectWidget;
	QGooseInCfgWidget m_oGooseInCfgWidget;
	QGooseOutCfgWidget m_oGooseOutCfgWidget;
	QChooseDeviceWidget m_oChooseDeviceWidget;

	virtual long OnRtData(CSttParas *pParas);//传控制块的接口


	virtual void InitUI();
	virtual void UpdateView();//根据当前Page来刷新页面
	virtual CString GetSmartTestModFile();


private:
	Ui::NGDSmartTestMainWidget ui;

signals:
	void sig_UpdateCbsGrid();
public slots:
	void slot_On_m_Btn_PreStep_clicked();
	void slot_On_m_Btn_NextStep_clicked();
	void slot_TimerForHeartBeat();

	
};

#endif // NGDSMARTTESTMAINWIDGET_H
