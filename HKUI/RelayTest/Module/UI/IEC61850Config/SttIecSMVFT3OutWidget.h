/************************************************************************/
/* SMVFT3发布页面                                                 */
/************************************************************************/
#ifndef STTIECSMVFT3OUTWIDGET_H
#define STTIECSMVFT3OUTWIDGET_H

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
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

//2023/10/12 wjs 
#include "SttIecSMVFT3DCOtherSetDialog.h"

#define STT_IEC_SMVFT3_BAUD_MAX_NUM                    4
#define STT_IEC_SMVFT3_RATE_MAX_NUM                    7

class QSttIecSMVFT3OutWidget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecSMVFT3OutWidget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecSMVFT3OutWidget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();
	virtual CIecCfgDataBase* AddNewIecCfgData();
	virtual void EnableAllButtons();
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONDATA;   }
protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
	void SetIecSMVFT3OutFont();

	QComboBox *m_pSmpRateComboBox;
	QComboBox *m_pBAUDComboBox;
	CExBaseListComboBox *m_pPkgTypeSelCombox;//报文类型选择下拉框
	QPushButton *m_pSMVFT3OutOtherSetButton;
	QHBoxLayout *m_pSMVFT3OutFirstHLayout;
	QLabel *m_pLabel;
	QLabel *m_Baud_Label;
	QLabel *m_pPkgTypeSel_Label;//报文选择
	int m_pSmpRate[STT_IEC_SMVFT3_RATE_MAX_NUM];

	//柔直FT3 显示CRC 
	QLabel *m_pCRC_Label;
	QComboBox* m_pCRC_ComboBox;

	CIecCfgDatasSMV* m_pIecCfgDatasSMVCopy; 
	void UpdateDates(CIecCfgDatasSMV* pIecCfgDatasSmvIn);
signals:

protected slots:
		void slot_SMVFT3OutOtherSetClicked();
		void slot_CurrentPkgTypeSelChanged(int nIndex);

};

extern CFont *g_pSttGlobalFont;  

#endif // GSEPubDIALOG_H
