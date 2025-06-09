#ifndef QSTTMACROPARAEDITVIEWCBOPERATE_H
#define QSTTMACROPARAEDITVIEWCBOPERATE_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttCheckBox.h"
#include "Grid/CBOperateResultAssessGrid.h"
#include "Dlg/CBOperateCommonParasDlg.h"
#include "../../SttTest/Common/Impedance/tmt_cb_operate_test.h"
#include <QRadioButton>
#include <QGroupBox>
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "ui_QSttMacroParaEditViewCBOperate.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"

namespace Ui {
class QSttMacroParaEditViewCBOperate;
};

class QSttMacroParaEditViewCBOperate : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewCBOperate(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewCBOperate();

public:
	virtual char* GetMacroID(){return STT_ORG_MACRO_CBOperateTest; }
    Ui::QSttMacroParaEditViewCBOperate *ui;
	void InitUI();						 //初始化界面
	void InitFont();                     //初始化字体
	void InitConnections();     
	void Initdates();
	virtual void SetDatas(CDataGroup *pDataset);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void startInit();
	virtual void stopInit();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oCBOperateTest;}
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);


	CString GetXYByImpedance(QString strXY,QString strAmp,QString strAngle);//根据幅值相位求xy坐标
	CString GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle);//根据xy坐标求幅值相位
public:
	CBOperateResultAssessGrid *m_pResultAssessWidget;
	CBOperateCommonParasDlg *m_pCommonParas;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;
	tmt_Time m_oCBOTime;
	QStringList m_ItemsList;

	QGooseParaWidget* m_pGooseParaWidget;

public slots:
	void slot_ResultAssess();
	void slot_CommonParas();
	void slot_ConversionFault();
	void slot_ImpedanceChanged(bool);

	void slot_CmbFaultType(int nIndex);
	void slot_EditZ();
	void slot_EditImpedanceAngle();
	void slot_EditCurLoad();
	void slot_EditPowerAngleLoad();
	void slot_EditCurShortCircuit();
	void slot_EditVolShortCircuit();
	void slot_CmbFaultDirection(int nIndex);
	void slot_CmbFaultQuality(int nIndex);
	void slot_EditLarFaultTime();
	void slot_EditHour();
	void slot_EditMinute();
	void slot_EditSecond();
	//void slot_ChkConversionFault();
	void slot_CmbRFaultType(int nIndex);
	void slot_EditConversionTime();
	void slot_EditRZ();
	void slot_EditRImpedanceAngle();
	void slot_EditRCurShortCircuit();
	void slot_EditRVolShortCircuit();
	void slot_CmbRFaultDirection(int nIndex);

public:
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
};


#endif
