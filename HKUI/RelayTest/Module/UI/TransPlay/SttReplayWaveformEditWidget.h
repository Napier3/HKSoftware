#ifndef _QWAVEFORMEDITWIDGET_H_
#define _QWAVEFORMEDITWIDGET_H_


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpacerItem>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "ui_SttReplayWaveformEditWidget.h"

#define REPLAYTEST_INSERT_TYPE_RAW		0			//原波形编辑
#define REPLAYTEST_INSERT_TYPE_NORMAL		1		//插入常态波形

class SttReplayWaveformEditWidget : public QWidget
{
	Q_OBJECT

public:
	SttReplayWaveformEditWidget(QWidget *pParent = 0);
	~SttReplayWaveformEditWidget(void);

public:
	void initUI();
    void initLauguage();
	void InitWaveEditWidget();
	void initSignalSlots();
	void uninitSignalSlots();
	void InitWidget();//根据参数修改控件使能

	void SetEnableState(bool bEnable);//20230839-wxy-勾选框状态
	int GetWaveEditType();
	int GetInsertNormalType();

private:
	Ui::SttReplayWaveformEditWidget ui;
	int m_nWaveEditType;//0-原波形编辑 1-插入常态波形
	int m_nInsertNormal_Type;//插入常态波形  0-起始位置 1-结束位置

public:
	BOOL CheckMaxDataTime(double dTime);

signals:
	void sig_UpdateWaveSelectBack(bool );	

public slots:

	void slot_InsertRbuttonClicked();
	void slot_InsertNormalRbuttonClicked();

	//点号
	void slot_Insert_ZeroChanged();
	void slot_Insert_DestinationChanged();
	//时间
	void slot_Insert_BeginTimeChanged();
	void slot_Insert_EndTimeChanged();

	void slot_Insert_TypeChanged(int nIndex);

	void slot_Insert_CycleIndexChanged();

	void slot_Delete_ZeroChanged();
	void slot_Delete_DestinationChanged();

	void slot_InsertNormal_ValChanged();
	void slot_InsertNormal_CurChanged();
	void slot_InsertNormal_OutTimeChanged();
	void slot_InsertNormal_TypeChanged(int nIndex);

	void slot_Insert_OK();
	void slot_Delete_OK();
	void slot_Wave_ReCovery();

public:
	void SetInsertWaveLayoutControlEnable(BOOL bState);
	void SetInsertNormalLayoutControlEnable(BOOL bState);
	void SetDeleteWaveLayoutControlEnable(BOOL bState);
	BOOL VaildWaveOverlap();//验证插入删除波形是否重合
	void UpdateInsertTypeWidgetChange(int nType);


};

#endif