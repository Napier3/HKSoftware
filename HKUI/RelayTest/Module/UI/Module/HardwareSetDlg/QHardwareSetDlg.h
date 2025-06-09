#ifndef QHardwareSetDlg_H
#define QHardwareSetDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "../../../SttTest/Common/tmt_system_config.h"
#include "../../Controls/SttCheckBox.h"
#include "../../Controls/SttLineEdit.h"
#include "../ScrollCtrl/ScrollComboBox.h"
#include "../CommonCtrl_QT/QLongLineEdit.h"
#include "../../Config/Frame/SttFrameConfig.h"

#define HARDWARESET_4G "4G"

class QHardwareSetDlg : public QDialog
{
	Q_OBJECT

public:
	QHardwareSetDlg(QWidget *parent = 0);
	~QHardwareSetDlg();

	void initUI(STT_SystemParas *pSysParas);
	void ReleaseUI();

protected:
	void InitDatas();
	void Update4GEnable();//dingxy 20240415 4G勾选框是否可选

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局

	QGroupBox *m_p4GBlueTooth_GroupBox;
	QHBoxLayout *m_p4GBlueTooth_HBoxLayout;
	QSttCheckBox *m_p4G_CheckBox;
	QSttCheckBox *m_pBlueTooth_CheckBox;
	QSttCheckBox *m_pWirelessNet_CheckBox;
	QSttCheckBox *m_pLocalNet_CheckBox;

	QGroupBox *m_pOtherSet_GroupBox;
	QVBoxLayout *m_pOtherSet_VLayout;
	//QHBoxLayout *m_pBackLightTime_HBoxLayout;
	QLabel *m_pScreenBright_Label;
	QLongLineEdit *m_pScreenBright_LineEdit;//dingxy 20240415 增加屏幕亮度
	QLabel *m_pReMarksScreen_Label;
	QLabel *m_pBackLightTime_Label;
	QLongLineEdit *m_pBackLightTime_LineEdit;
	QLabel *m_pReMarks_Label;

	QHBoxLayout *m_pTimeZoneSet_HBoxLayout;
	QLabel *m_pTimeZoneSet_Label;
	QScrollComboBox *m_pTimeZoneSet_ComboBox;
	QGridLayout *m_pOtherSet_GridLayout;
	
	QLabel *m_pFanMode_Label;
	QButtonGroup *m_pFanModeBtnGroup;
	QRadioButton *m_pNormal_RadioButton;
	QRadioButton *m_pMute_RadioButton;
	QHBoxLayout *m_pFanMode_HBoxLayout;
	

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;
	QHBoxLayout *m_pOkCancel_HBoxLayout;

	STT_SystemParas *m_pSysParas;
	CSttFrameConfig * m_pSttFrameConfig;


public:
signals:
	//void sig_UpdateModulesGear(BOOL bMergeCurrHasChanged);//通知外部模块更新测试仪模块档位信息

public slots:
	void slot_On4GBlueToothSetCheckChanged();
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_radio_NormalLogicChanged(bool ret);
	void slot_radio_MuteLogicChanged(bool ret);
};

#endif // QHardwareSetDlg_H
