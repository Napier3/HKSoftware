#ifndef _CSttReplayTriggerWidget_H_
#define _CSttReplayTriggerWidget_H_

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

#include "../../ReplayTest/BigComtradeTransPlay.h"


class CSttReplayTriggerWidget : public QWidget
{
	Q_OBJECT

public:
	CSttReplayTriggerWidget(QWidget *pParent = 0);
	~CSttReplayTriggerWidget();

	void ConnectAllBinaryIn(BOOL bCoonect);

private:
	QCheckBox *m_pRadioBtn_NoTrip;
	QCheckBox *m_pRadioBtn_ManualTrip;
	QCheckBox *m_pRadioBtn_GpsTrip;
	QCheckBox *m_pRadioBtn_BinaryInTrip;

	QLabel *m_plbGpsTime;
	QLineEdit *m_pedtGpsTime_Hour;
	QLineEdit *m_pedtGpsTime_Minute;
	QLineEdit *m_pedtGpsTime_Second;
	QLabel* m_plbGpsTime_Hour_comma;
	QLabel* m_plbGpsTime_Minute_comma;


	QLabel *m_plbTripAfterMode;
	QComboBox *m_pcmbTripAfterMode;

	QLabel *m_plbCycleNum;
	QLineEdit *m_pedtCycleNum;

	QGroupBox *m_pGroupBox_PutInSet;
	QGridLayout *m_pGridLayout_PutInSet;
	QCheckBox *m_pCheck_Input1;
	QCheckBox *m_pCheck_Input2;
	QCheckBox *m_pCheck_Input3;
	QCheckBox *m_pCheck_Input4;
	QCheckBox *m_pCheck_Input5;
	QCheckBox *m_pCheck_Input6;
	QCheckBox *m_pCheck_Input7;
	QCheckBox *m_pCheck_Input8;
	QCheckBox *m_pCheck_Input9;
	QCheckBox *m_pCheck_Input10;
	QRadioButton* m_pLogicAnd;
	QRadioButton* m_pLogicOr;

	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pHLayout1;
	QHBoxLayout *m_pHLayout2;
	QHBoxLayout *m_pHLayout3;
	QHBoxLayout *m_pHLayout4;
	QHBoxLayout *m_pHLayout5;

signals:
	//void sig_InPutStateChanged();

public slots:
	void slot_NoTripClicked();
	void slot_ManualTripClicked();
	void slot_GpsTripClicked();
	void slot_BinaryInTripClicked();
	void slot_TripAfterModeChanged(int);
	void slot_GpsTimeChanged();
	void slot_CycleNumChanged();
	void slot_SttLineEditChanged();

	void slot_ck_In1StateChanged(int);
	void slot_ck_In2StateChanged(int);
	void slot_ck_In3StateChanged(int);
	void slot_ck_In4StateChanged(int);
	void slot_ck_In5StateChanged(int);
	void slot_ck_In6StateChanged(int);
	void slot_ck_In7StateChanged(int);
	void slot_ck_In8StateChanged(int);
	void slot_ck_In9StateChanged(int);
	void slot_ck_In10StateChanged(int);
	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);

private:
	void initUI();
	void initSignalSlots();
	void uninitSignalSlots();
	void UpdateWidget(int nMode);
public:
	void UpdateEditData();
	void InitSttReplayTriggerWidget();
	void SetTriggerParaFont();
	void SetBinaryInEnable(bool bFlag);
	void UpdateBinaryInEnable();
};



#endif