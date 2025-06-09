#ifndef STTSYSPARASWIDGET_H
#define STTSYSPARASWIDGET_H
#include "SttIecConfigGlobalDef.h"

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

#define STT_SYSPARAS_TRANS_RADIO_NUM                               6

#define IECCFG_SYSPARAS_VIEW_VOLT_TYPE            0
#define IECCFG_SYSPARAS_VIEW_CURR_TYPE            1

#define IECCFG_SYSPARAS_VIEW_PRIM_TYPE            0
#define IECCFG_SYSPARAS_VIEW_SECOND_TYPE          1

class QSttSysParasWidget : public QWidget, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttSysParasWidget(QWidget *parent);
	~QSttSysParasWidget();

	virtual void InitData(CIecCfgSysParas* pIecCfgSysParas);
	virtual void SaveData();

	//设置变比组能否编辑
	void SetScaleEnable(bool _bEnable);
	void SetPrimRateValue(int nGroupIndex,int nVoltCurType,int nPrimSecondType,float fValue);

private:
	void InitUI();
	void UpdateRates_EditState();//更新变比的编辑状态

	QHBoxLayout *m_pMain_HLayout;
	QGridLayout *m_pScrollAreaWidget_GridLayout;
	QHBoxLayout *m_pPkgSendType_HBoxLayout;
	QFormLayout *m_pPkgSendType_FormLayout;
	QFormLayout *m_pParasSetSel_FormLayout;
	QFormLayout *m_pPkgSendSel_FormLayout;
//	QFormLayout *m_pSencondSyn_FormLayout;
	QVBoxLayout *m_pTransRadio_VBoxLayout;

	QGroupBox *m_pPkgSendType_GroupBox;
	QGroupBox *m_pTransRadios_GroupBox;

	QScrollArea *m_pMain_ScrollArea;
	QWidget *m_pScrollArea_Widget;
	QComboBox *m_pPkgSendTypeComboBox;
	QComboBox *m_pParasSetSelCombox;
	QComboBox *m_pPkgSendSelCombox;
//	QComboBox *m_pSecondSynComboBox;
	QPushButton *m_pOtherSetPushBtn;

	QLineEdit *m_voltageLineEdit;
	QLineEdit *m_currentLineEdit;
	QLineEdit *m_frequencyLineEdit;
	QLineEdit *m_stableTimeLineEdit;
	QComboBox *m_productComboBox;

	struct SysParasTransRadio_Struct
	{
		QGroupBox *pGroupBox;
		QHBoxLayout *pHBoxLayout;
		QFloatLineEdit *pPrimaryCurrLineEdit;
		QFloatLineEdit *pSecondCurrLineEdit;
		QFloatLineEdit *pPrimaryVolLineEdit;
		QFloatLineEdit *pSecondVolLineEdit;
	};

	SysParasTransRadio_Struct m_oTransRadioGroup[STT_SYSPARAS_TRANS_RADIO_NUM];

	CIecCfgSysParas* m_pIecCfgSysParas;
	CIecCfgPrimRates *m_pPrimRates;
	CIecCfgPrimRatesIn *m_pPrimRatesIn;



public slots:

	void slot_PkgSendTypeChanged(int);
	void slot_ParasSetSelChanged(int);
	void slot_PkgSendSelChanged(int);
	void slot_OtherSetPushBtnClicked();
	void slot_lne_Clicked();
};

#endif // STTSYSPARASWIDGET_H
