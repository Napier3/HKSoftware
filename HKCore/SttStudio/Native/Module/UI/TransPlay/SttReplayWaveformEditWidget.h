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

#define REPLAYTEST_INSERT_TYPE_RAW		0			//ԭ���α༭
#define REPLAYTEST_INSERT_TYPE_NORMAL		1		//���볣̬����

class SttReplayWaveformEditWidget : public QWidget
{
	Q_OBJECT

public:
	SttReplayWaveformEditWidget(QWidget *pParent = 0);
	~SttReplayWaveformEditWidget(void);

public:
	void initUI();
	void InitWaveEditWidget();
	void initSignalSlots();
	void uninitSignalSlots();
	void InitWidget();//���ݲ����޸Ŀؼ�ʹ��

	void SetEnableState(bool bEnable);//20230839-wxy-��ѡ��״̬
	int GetWaveEditType();

private:
	Ui::SttReplayWaveformEditWidget ui;
	int m_nWaveEditType;//0-ԭ���α༭ 1-���볣̬����

public:
	BOOL CheckMaxDataTime(double dTime);

signals:
	void sig_UpdateWaveSelectBack(bool );	

public slots:

	void slot_InsertRbuttonClicked();
	void slot_InsertNormalRbuttonClicked();

	//���
	void slot_Insert_ZeroChanged();
	void slot_Insert_DestinationChanged();
	//ʱ��
	void slot_Insert_BeginTimeChanged();
	void slot_Insert_EndTimeChanged();

	void slot_Insert_TypeChanged(int nIndex);

	void slot_Insert_CycleIndexChanged();

	void slot_Delete_ZeroChanged();
	void slot_Delete_DestinationChanged();

	void slot_InsertNormal_ValChanged();
	void slot_InsertNormal_CurChanged();
	void slot_InsertNormal_OutTimeChanged();

	void slot_Insert_OK();
	void slot_Delete_OK();
	void slot_Wave_ReCovery();

public:
	void SetInsertWaveLayoutControlEnable(BOOL bState);
	void SetInsertNormalLayoutControlEnable(BOOL bState);
	void SetDeleteWaveLayoutControlEnable(BOOL bState);
	BOOL VaildWaveOverlap();//��֤����ɾ�������Ƿ��غ�
	void UpdateInsertTypeWidgetChange(int nType);


};

#endif