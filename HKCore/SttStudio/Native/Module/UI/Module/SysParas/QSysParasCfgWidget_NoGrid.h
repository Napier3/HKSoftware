#ifndef QSYSPARASCFG_NOGRID_WIDGET_H
#define QSYSPARASCFG_NOGRID_WIDGET_H

#include <QLabel>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include "../CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

#define STT_SYSPARAS_TRANS_RADIO_NUM                               6

class QSysParasCfgWidget_NoGrid : public QWidget
{
	Q_OBJECT
public:
	QSysParasCfgWidget_NoGrid(CIecCfgSysParas* pIecCfgSysParas, QWidget *parent = 0);
	~QSysParasCfgWidget_NoGrid();

	void InitUI();
	void InitConnection();
	void InitData();
	void UpdateRates_EditState();//更新变比的编辑状态
	void SaveDatas();

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
	CIecCfgSysParas* m_pCfgSysParas;
	CIecCfgPrimRates* m_pPrimRates;

	QVBoxLayout* m_pTransRadio_VBoxLayout;
	QVBoxLayout* m_pMainVLayout;
	QHBoxLayout* m_pPkgSendType_HBoxLayout;
	QComboBox* m_pParasSetSelCombox;
	QLabel* m_pParasSet_Label;
public slots:
	void slot_ParasSetSelChanged(int nIndex);
};

#endif