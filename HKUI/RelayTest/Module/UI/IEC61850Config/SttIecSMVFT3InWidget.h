/************************************************************************/
/* SMVFT3订阅页面                                                 */
/************************************************************************/
#ifndef STTIECSMVFT3INWIDGET_H
#define STTIECSMVFT3INWIDGET_H

#include "SttIecConfigWidgetBase.h"
#include "SttIecConfigGlobalDef.h"
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "Grid/IecCfgSmvDataFT3Grid.h"
#include "Grid/IecCfgSmvDataFT3InGrid.h"
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvInDatas.h"

#define STT_IEC_SMVFT3_BAUD_MAX_NUM                    4
#define STT_IEC_SMVFT3_RATE_MAX_NUM                    7

class QSttIecSMVFT3InWidget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecSMVFT3InWidget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecSMVFT3InWidget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();
	virtual CIecCfgDataBase* AddNewIecCfgData();
	virtual void EnableAllButtons();
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONINDATA;   }
protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
	void SetIecSMVFT3InFont();

	QComboBox *m_pSmpRateComboBox;
	QComboBox *m_pBAUDComboBox;
	CExBaseListComboBox *m_pPkgTypeSelCombox;//报文类型选择下拉框
	QHBoxLayout *m_pSMVFT3InFirstHLayout;
	QPushButton *m_pSMVFT3InOtherSetButton;//码值设置
	QLabel *m_pLabel;
	QLabel *m_Baud_Label;
	QLabel *m_pPkgTypeSel_Label;//报文选择
	int m_pSmpRate[STT_IEC_SMVFT3_RATE_MAX_NUM];
	//柔直FT3 显示CRC 
	QLabel *m_pCRC_Label;
	QComboBox* m_pCRC_ComboBox;

	CIecCfgDatasSmvIn* m_pIecCfgDatasSMVInCopy; //20241023 wuxinyi 增加处理报文类型选择数据(参考330)
	void UpdateDates(CIecCfgDatasSmvIn* pIecCfgDatasSmvIn);

protected slots:
	void slot_SMVFT3InOtherSetClicked();
	void slot_CurrentPkgTypeSelChanged(int nIndex);

};

extern CFont *g_pSttGlobalFont;  

#endif // GSEPubDIALOG_H
