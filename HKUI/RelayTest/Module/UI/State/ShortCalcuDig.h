#ifndef SHORTCALCUDIG_H
#define SHORTCALCUDIG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QMouseEvent>

#include "ui_ShortCalcuDig.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../Module/SttTestBase/SttComplexp.h"
#include "../Module/CommonMethod/FaultCalculat.h"
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../../Module/SttTest/Common/tmt_result_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

namespace Ui {
	class ShortCalcuDig;
}

class ShortCalcuDig : public QDialog
{
	Q_OBJECT

public:
	Ui::ShortCalcuDig *ui;

	ShortCalcuDig(CSttTestResourceBase *pSttTestResource
		, tmt_channel *uiVOL,tmt_channel *uiCUR
		, ShortCalcuPara para,QWidget *parent = 0);
	~ShortCalcuDig();
	
signals:
	void sig_ShortCalcuOk(ShortCalcuPara &);

private slots:
	void slot_CmbErrorTypeIndexChanged(int);
	void slot_RadioZPhiAndRX_StateChanged();
	void slot_lneZ_TextChanged();
 	void slot_lneZ_TextKeyBoard();
	void slot_lnePhi_TextChanged();
	void slot_lnePhi_TextKeyBoard();
	void slot_lneR_TextChanged();
	void slot_lneR_TextKeyBoard();
	void slot_lneX_TextChanged();
	void slot_lneX_TextKeyBoard();
	void slot_CmbCalModeIndexChanged(int);
	void slot_lneDLDL_TextChanged();   //短路电流
	void slot_lneDLDL_TextKeyBoard(); 
	void slot_lneDLDY_TextChanged();   //短路电压
	void slot_lneDLDY_TextKeyBoard();
	void slot_lneZSZL_TextChanged();   //ZS/ZL
	void slot_lneZSZL_TextKeyBoard();
	void slot_CmbCalTypeIndexChanged(int);
	void slot_lneFZ_TextChanged();
	void slot_lneFZ_TextKeyBoard();
	void slot_lneXJ_TextChanged();
	void slot_lneXJ_TextKeyBoard();
	void slot_lne_LoadI_TextChanged();  //负荷电流
	void slot_lne_LoadI_TextKeyBoard();
	void slot_lne_LoadAngle_TextChanged();  //负荷功角
	void slot_lne_LoadAngle_TextKeyBoard();

	void slot_ConfirmClicked();
	void slot_CancelClicked();

public:
	QPushButton *m_pbn_Cancel;
	QPushButton *m_pbn_Ok;
	QLabel *m_pZLabel;
	QLabel *m_pFaultTypeLabel;
	QLabel *m_pChGroupLabel;
	QLabel *m_pNulllabel;
	QLabel *m_pRXLabel;
	QLabel *m_pCacuModeLabel;
	QLabel *m_pLoadILabel;
	QLabel *m_pDLILabel;
	QLabel *m_pLoadAngleLabel;
	QLabel *m_pDLVLabel;
	QLabel *m_pZSZLLabel;
	QLabel *m_pCacuTypeLabel;
	QLabel *m_pAmpLabel;
	QLabel *m_pAngleLabel;
	QScrollComboBox *m_pCmb_ChGroup;
	QScrollComboBox *m_pCmb_FaultType;
	QScrollComboBox *m_pCmb_CacuMode;
	QScrollComboBox *m_pCmb_CacuType;
	QRadioButton *m_pRad_ZPhi;
	QRadioButton *m_pRad_RX;
	QSttLineEdit *m_pPhiEdit;
	QSttLineEdit *m_pZEdit;
	QSttLineEdit *m_pXEdit;
	QSttLineEdit *m_pREdit;
	QSttLineEdit *m_pLoadIEdit ;
	QSttLineEdit *m_pShortIEdit;
	QSttLineEdit *m_pLoadAngleEdit;
	QSttLineEdit *m_pZSZLEdit;
	QSttLineEdit *m_pShortUEdit;
	QSttLineEdit *m_pAmpEdit;
	QSttLineEdit *m_pAngleEdit;
	
public:
	//tmt_StatePara* m_pStatePara;
	tmt_channel *m_uiVOL;
	tmt_channel *m_uiCUR;

	CSttTestResourceBase *m_pShortCalcuSttTestResource;

private:
	ShortCalcuPara  m_para;
	void initPara();

	void initUI();
	void initConnections();
	void initBaseData();
	void initData();

	void OnRXValue();
	
	void MakeDataToGroup();
	void SetShortFont();

        QMap<int,QList<tmt_Channel> > m_UChanelDataMap;
        QMap<int,QList<tmt_Channel> > m_IChanelDataMap;

	QMap<int,int> m_UModuleOfDataKeyMap;
	QMap<int,int> m_IModuleOfDataKeyMap;

	QStringList m_errorTypeList;
	QStringList m_CalTypeList;
	QStringList m_CalModList;
	QStringList m_Z_P_R_XList;

	int m_nRadio;
	int m_nFaultType;
	int m_nCalMode;
	int m_nCalType;
	bool m_bZPhi;
	bool m_bRX;

	float m_fR;
	float m_fX;
	float m_fZ;
	float m_fPhi;

	float m_fDLI;
	float m_fDLV;
	float m_fKr;
	float m_fKx;
	float m_fZSZL;
	float m_fVmax;
	float m_fImax;

	Complex m_fVa;
	Complex m_fVb;
	Complex m_fVc;
	Complex m_fIa;
	Complex m_fIb;
	Complex m_fIc;

	bool m_bFaultDir;
	bool m_bCTPoint;
	float m_fIfh;			//负荷电流
	float m_fPowerAngle;	//负荷功角
	float m_fVnom;
	float m_fK0l;
	float m_fK0lPh;

	bool m_bPrimaryPara;
	double m_fVFactor;
	double m_fIFactor;
};

#endif // SHORTCALCUDIG_H
