#ifndef QCBOPERATEADDMULTDLG_H
#define QCBOPERATEADDMULTDLG_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttCheckBox.h"
#include "Grid/CBOperateResultAssessGrid.h"
#include "Dlg/CBOperateCommonParasDlg.h"
#include "../../SttTest/Common/Impedance/tmt_cb_operate_test.h"

class QSttMacroParaEditViewCBOperate : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewCBOperate(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewCBOperate();

public:
	virtual char* GetMacroID(){return STT_ORG_MACRO_CBOperateTest; }

	void InitUI();						 //初始化界面
	void InitFont();                     //初始化字体
	void InitConnections();     
	void Initdates();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void startInit();
	virtual void stopInit();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oCBOperateTest;}

	CString GetXYByImpedance(QString strXY,QString strAmp,QString strAngle);//根据幅值相位求xy坐标
	CString GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle);//根据xy坐标求幅值相位
public:
	QLabel *m_pLabFaultType;               //故障类型
	QLabel *m_pLabCurShortCircuit;		   //短路电流
	QLabel *m_pLabZ;			           //|Z|
	QLabel *m_pLabVolShortCircuit;		   //短路电压
	QLabel *m_pLabImpedanceAngle;		   //阻抗角
	QLabel *m_pLabFaultDirection;          //故障方向
	QLabel *m_pLabCurLoad;				   //负荷电流
	QLabel *m_pLabFaultQuality;			   //故障性质
	QLabel *m_pLabPowerAngleLoad;		   //负荷功角
	QLabel *m_pLabLarFaultTime;			   //最大故障时间
	QLabel *m_pLabFaultTrigTime;		   //故障触发时刻
	QLabel *m_pLabImpedanceWay;            //阻抗表示方式
	QLabel *m_pLabConversionTime;		   //转换时间
	QLabel *m_pLabHour;					   //时
	QLabel *m_pLabMinute;		           //分
	QLabel *m_pLabSecond;		           //秒

	QRadioButton *m_pChkAmpAngle;          //幅值相位
	QRadioButton *m_pChkRX;				   //R-X
	QSttCheckBox *m_pChkConversionFault;   //转换性故障
	QButtonGroup* m_ButtonGroup;

	QComboBox *m_pCmbFaultType;			   //故障类型
	QComboBox *m_pCmbFaultDirection;       //故障方向
	QComboBox *m_pCmbFaultQuality;         //故障性质

	QLineEdit *m_pEditCurShortCircuit;	  //短路电流
	QLineEdit *m_pEditZ;			      //|Z|
	QLineEdit *m_pEditVolShortCircuit;    //短路电压
	QLineEdit *m_pEditImpedanceAngle;     //阻抗角
	QLineEdit *m_pEditCurLoad;			  //负荷电流
	QLineEdit *m_pEditPowerAngleLoad;	  //负荷功角
	QLineEdit *m_pEditLarFaultTime;		  //最大故障时间
	QLineEdit *m_pEditConversionTime;	  //转换时间
	QLineEdit *m_pEditHour;               //时
	QLineEdit *m_pEditMinute;		      //分
	QLineEdit *m_pEditSecond;		      //秒

	QPushButton *m_pBtnResultAssess;      //结果评估
	QPushButton *m_pBtnCommonParas;       //通用参数

	QLabel *m_pLabRFaultType;               //故障类型
	QLabel *m_pLabRCurShortCircuit;		   //短路电流
	QLabel *m_pLabRZ;			           //|Z|
	QLabel *m_pLabRVolShortCircuit;		   //短路电压
	QLabel *m_pLabRImpedanceAngle;		   //阻抗角
	QLabel *m_pLabRFaultDirection;          //故障方向

	QComboBox *m_pCmbRFaultType;			   //故障类型
	QComboBox *m_pCmbRFaultDirection;       //故障方向
	QLineEdit *m_pEditRCurShortCircuit;	  //短路电流
	QLineEdit *m_pEditRZ;			      //|Z|
	QLineEdit *m_pEditRVolShortCircuit;    //短路电压
	QLineEdit *m_pEditRImpedanceAngle;     //阻抗角

	QWidget *m_pLeftWidget;
	QWidget *m_pRightWidget;
	QWidget *m_pBottomWidget;

	QGridLayout *m_pVlayout;
	QGridLayout *m_pLeftGridLayout;
	QGridLayout *m_pRightGridLayout;
	QGridLayout *m_pBottomGridLayout;
	QGroupBox *m_pGroupBox;
	QVBoxLayout *m_pGroupBoxLayout;

	CBOperateResultAssessGrid *m_pResultAssessWidget;
	CBOperateCommonParasDlg *m_pCommonParas;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;
	tmt_Time m_oCBOTime;
	QStringList m_ItemsList;

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public slots:
	void slot_ResultAssess();
	void slot_CommonParas();
	void slot_ConversionFault();
	void slot_ImpedanceChanged(bool);
	void slot_AmpAngle();
	void slot_RX();

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
	void slot_ChkConversionFault();
	void slot_CmbRFaultType(int nIndex);
	void slot_EditConversionTime();
	void slot_EditRZ();
	void slot_EditRImpedanceAngle();
	void slot_EditRCurShortCircuit();
	void slot_EditRVolShortCircuit();
	void slot_CmbRFaultDirection(int nIndex);
};


#endif