#ifndef QSYSPARASCFGWIDGET_H
#define QSYSPARASCFGWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QHBoxLayout>

#include "../../IEC61850Config/SttIecSysCfgChildWidget.h"
#include "../../../XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

class QSysParasCfgWidget : public QWidget
{
	Q_OBJECT
public:
	QSysParasCfgWidget(CIecCfgSysParas* pIecCfgSysParas, QWidget *parent = 0);
	~QSysParasCfgWidget();

	void InitUI();
	void InitConnection();
	void InitData();
	void UpdateRates_EditState();//更新变比的编辑状态
	void SaveDatas();

	CIecCfgSysParas* m_pCfgSysParas;

	QSttIecSysCfgChildWidget *m_pSmvOutPrimRateWidget;   //发送变比设置
	QComboBox *m_pParasSetSelCombox;
	QLabel *m_pParasSet_Label;
	QHBoxLayout *m_pPkgSendType_HBoxLayout;
	QVBoxLayout *m_pMainVLayout;
	QTabWidget *m_pIecCfgTabWidget;
public slots:
	void slot_ParasSetSelChanged(int nIndex);
};

#endif
