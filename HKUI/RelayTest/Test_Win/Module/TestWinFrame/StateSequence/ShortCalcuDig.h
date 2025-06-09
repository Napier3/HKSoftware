#ifndef SHORTCALCUDIG_H
#define SHORTCALCUDIG_H

#include <QDialog>
#include "..\..\Define.h"
#include "..\..\CommonMethod\commonMethod.h"
#include "..\..\CommonMethod\Complexp.h"
#include "..\..\CommonMethod\FaultCalculat.h"
#include "..\..\..\..\Module\SttTest\Common\tmt_state_test.h"
#include "..\..\..\..\Module\SttTest\Common\tmt_result_def.h"
#include "..\..\..\..\Module\SttTestResourceMngr\SttTestResourceMngr.h"

#include "ui_ShortCalcuDig.h"
#include <QKeyEvent>
class ShortCalcuDig : public QDialog
{
	Q_OBJECT

public:
	ShortCalcuDig(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara,ShortCalcuPara para,QWidget *parent = 0);
	~ShortCalcuDig();
	
	void keyPressEvent(QKeyEvent *event);
	
signals:
	void sig_ShortCalcuOk(ShortCalcuPara &);

private slots:
	void slot_CmbErrorTypeIndexChanged(int);
	void slot_RadioZPhiAndRX_StateChanged();
	void slot_lneZ_TextChanged();
	void slot_lnePhi_TextChanged();
	void slot_lneR_TextChanged();
	void slot_lneX_TextChanged();
	void slot_CmbCalModeIndexChanged(int);
	void slot_lneDLDL_TextChanged();   //短路电流
	void slot_lneDLDY_TextChanged();   //短路电压
	void slot_lneZSZL_TextChanged();   //ZS/ZL
	void slot_CmbCalTypeIndexChanged(int);
	void slot_lneFZ_TextChanged();
	void slot_lneXJ_TextChanged();
	void slot_lne_LoadI_TextChanged();  //负荷电流
	void slot_lne_LoadAngle_TextChanged();  //负荷功角

	void slot_ConfirmClicked();
	void slot_CancelClicked();

public:
	tmt_StatePara* m_pStatePara;
	CSttTestResourceBase *m_pSttTestResource;

private:
	Ui::ShortCalcuDig ui;

	ShortCalcuPara  m_para;
	int m_disp;// 0:一次值 1：二次值

	void Init();
        void InitLanguage();
	void InitData();
	void OnRXValue();
	void InitConnection();
	void MakeDataToGroup();

	QMap<int,QList<tmt_Channel>> m_UChanelDataMap;
	QMap<int,QList<tmt_Channel>> m_IChanelDataMap;

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
