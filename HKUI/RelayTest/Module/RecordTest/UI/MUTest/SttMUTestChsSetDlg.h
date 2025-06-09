#ifndef STTMUTESTCHSSETDLG_H
#define STTMUTESTCHSSETDLG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include "../../../UI/Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../../../Module/SmartCap/X61850CapBase.h"
#include "../../../UI/IEC61850Config/Grid/IecCfgPrimRateGrid.h"
#include "../../../UI/IEC61850Config/Grid/IecCfgSmv92InChsGrid.h"
#include "../../../UI/IEC61850Config/Grid/IecCfgSmvFT3InChsGrid.h"

class QSttMUTestChsSetDlg : public QDialog
{
	Q_OBJECT

public:
	QSttMUTestChsSetDlg(QWidget *parent,BOOL bIsFT3MUTest = FALSE);
	virtual ~QSttMUTestChsSetDlg();

	virtual void SaveData();
	void InitData(CIecCfgDataBase *pIecCfgData,CCapAnalysisConfig *pCapAnalysisConfig,CIecCfgPrimRatesIn *pIecCfgPrimRatesIn);

	long m_nParasModifyType;//参数修改类型
	void SetIsFT3MUTest(BOOL bIsFT3MUTest);

private:
	BOOL m_bIsFT3MUTest;
	void InitUI();
	BOOL IsAppChIDEqual(const CString &strAppChID1,const CString &strAppChID2);
	CIecCfgPrimRatesIn *m_pIecCfgPrimRatesIn_External;
	CIecCfgPrimRatesIn *m_pIecCfgPrimRatesIn_Internal;
	CExBaseList m_oVolPrimRateList;
	CExBaseList m_oCurPrimRateList;

	CIecCfgChsBase *m_pCfgChs_External;
	CIecCfgChsBase *m_pCfgChs_Internal;
	CCapAnalysisConfig *m_pSttCapAnalysisConfig;

	CIecCfgChsGridBase *m_pIecCfgSmvInChsGrid;
	CIecCfgPrimRateGrid *m_pLeft_PrimRateGrid;
	CIecCfgPrimRateGrid *m_pRight_PrimRateGrid;
	QHBoxLayout *m_pPT_CT_RatesHLayout;
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pRadioHLayout;
	QGroupBox *m_pRateGroupBox;

	QLabel *m_pChNumLabel;
	QLineEdit *m_pChNumLineEdit;
	QRadioButton *m_pPrimaryValueRadioBtn;
	QRadioButton *m_pSecondValueRadioBtn;

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	QHBoxLayout *m_pBtnClickedHLayout;
	QSpacerItem * m_pSparcer_BtnClick;
	QPushButton *m_pClickedAll_PushButton;
	QPushButton *m_pDisclickedAll_PushButton;
	QPushButton *m_pInvert_PushButton;

	void SetMUTestChsSetDlgEnabled();//2023-12-22 suyang 开始测试后使能状态改变

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

	void slot_BtnClickedAllClicked();
	void slot_BtnDisClickedAllClicked();
	void slot_BtnInvertClicked();

};

extern CFont *g_pSttGlobalFont;
#endif // STTMUTESTCHSSETDLG_H
