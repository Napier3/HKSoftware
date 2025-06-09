#ifndef STTIECSYSCFGWIDGET_H
#define STTIECSYSCFGWIDGET_H

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
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "SttIecSysCfgChildWidget.h"


#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

class QSttIecSysCfgWidget : public QWidget, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecSysCfgWidget(QFont oIecFont,QWidget *parent);
	~QSttIecSysCfgWidget();

	virtual void InitData(CIecCfgSysParas* pIecCfgSysParas);
	virtual void SaveData();

	QTabWidget *m_pIecCfgTabWidget;
	QSttIecSysCfgChildWidget *m_pSmvOutPrimRateWidget;
	QSttIecSysCfgChildWidget *m_pSmvInPrimRateWidget;
	QSttIecSysCfgChildWidget *m_pFibersWidget;
	QSttIecSysCfgChildWidget *m_pFibersInWidget;

	QVBoxLayout *m_pMainVLayout;

	QHBoxLayout *m_pPkgSendType_HBoxLayout;
	QFormLayout *m_pPkgSendType_FormLayout;
	QFormLayout *m_pParasSetSel_FormLayout;
	QFormLayout *m_pPkgSendSel_FormLayout;
	QComboBox *m_pPkgSendTypeComboBox;
	QComboBox *m_pParasSetSelCombox;
	QComboBox *m_pPkgSendSelCombox;
	QLabel *m_pPacketSendingMode_Label;
	QLabel *m_pParasSet_Label;
	QLabel *m_pPacketSending_Label;


private:
	void InitUI();
	CIecCfgSysParas* m_pIecCfgSysParas;
	QFont m_oIecFont;
	void SetIecSysCfgFont();//20221022 sy 增加字体设置
	void UpdateRates_EditState();//更新变比的编辑状态

public slots:
	void slot_ParasSetSelChanged(int);
	void slot_PkgSendSelChanged(int);
};

extern CFont *g_pSttGlobalFont; 

#endif // STTIECSYSCFGWIDGET_H
