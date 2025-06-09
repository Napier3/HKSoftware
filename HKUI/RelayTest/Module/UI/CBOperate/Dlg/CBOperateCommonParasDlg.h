#ifndef QCBOPERATEADDMULTCOMMONPARAS_H
#define QCBOPERATEADDMULTCOMMONPARAS_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../../SttTest/Common/Impedance/tmt_cb_operate_test.h"
#include "../../Controls/SettingCtrls/QSettingLineEdit.h"
class CBOperateCommonParasDlg : public QDialog
{
	Q_OBJECT

public:
	CBOperateCommonParasDlg(tmt_CBOperateParas *pCBOperateParas ,QWidget *parent = 0);
	virtual ~CBOperateCommonParasDlg();            

public:
	QLabel *m_pLabPreFaultTime;        //故障前时间(s)
	QLabel *m_pLabTimeAfterTrigger;    //保护动作后持续时间(s)
	QLabel *m_pLabFaultTrigMode;       //故障触发方式
	QLabel *m_pLabPTPos;			   //TV安装位置
	QLabel *m_pLabCTPos;               //TA正极性
	QLabel *m_pLabTestProcess;		   //试验过程
	QLabel *m_pLabRecloseMode;         //重合方式
	QLabel *m_pLabAfterOpenTime;	   //开关跳开后持续时间(s)
	QLabel *m_pLabRecloseTime;         //重合持续时间(s)
	QLabel *m_pLabAfterAccTime;        //后加速开关跳开后持续时间(s)
	QLabel *m_pLabK0Mode;			   //零序补偿系数表达方式
	QLabel *m_pLabKlKr;				   //零序补偿系数RMRL
	QLabel *m_pLabAngKx;               //零序补偿系数XMXL
	QLabel *m_pLabCalMode;             //计算方式
	QLabel *m_pLabZs;                  //系统阻抗(Ω)
	QLabel *m_pLabZsPh;                //系统阻抗角(°)
	QLabel *m_pLabSimulateBreakerDelay;//断路器模拟
	QLabel *m_pLabBrkBreakTime;        //分闸时间（s）
	QLabel *m_pLabBrkCloseTime;        //合闸时间（s）
	QLabel *m_pLabFaultIncMode;        //合闸角选择
	QLabel *m_pLabFaultAngle;          //合闸角（°）
	QLabel *m_pLabBIPlusDC;            //叠加非周期分量
	QLabel *m_pLabVzDefine;            //抽取电压输出定义
	QLabel *m_pLabPsuVzRefPhase;       //抽取电压参考相定义
	QLabel *m_pLabVzPh;                //抽取电压相角
	QLabel *m_pLabBinSelect;           //开入量选择
	QLabel *m_pLabBinA;                //开入A
	QLabel *m_pLabBinB;                //开入B
	QLabel *m_pLabBinC;                //开入C
	QLabel *m_pLabBinD;                //开入D
	QLabel *m_pLabBinE;                //开入E
	QLabel *m_pLabBinF;                //开入F
	QLabel *m_pLabBinG;                //开入G
	QLabel *m_pLabBinH;                //开入H
	QLabel *m_pLabBoutA;               //开出A
	QLabel *m_pLabBoutB;               //开出B
	QLabel *m_pLabBoutC;               //开出C
	QLabel *m_pLabBoutD;               //开出D
	QLabel *m_pLabBoutE;               //开出E
	QLabel *m_pLabBoutF;               //开出F
	QLabel *m_pLabBoutG;               //开出G
	QLabel *m_pLabBoutH;               //开出H
	QLabel *m_pLabOutputSwitchMode;    //开出翻转启动方式
	QLabel *m_pLabOutputKeepTime;      //开出保持时间
	QLabel *m_pLabOutputDelayTime;     //开出翻转时刻

	QLineEdit *m_pEditPreFaultTime;    //故障前时间(s)
	QLineEdit *m_pEditTimeAfterTrigger;//保护动作后持续时间(s)
	QLineEdit *m_pEditAfterOpenTime;   //开关跳开后持续时间(s)
	QLineEdit *m_pEditRecloseTime;     //重合持续时间(s)
	QLineEdit *m_pEditAfterAccTime;    //后加速开关跳开后持续时间(s)
    QSettingLineEdit *m_pEditKlKr;			   //零序补偿系数RMRL
    QSettingLineEdit *m_pEditAngKx;           //零序补偿系数XMXL
	QLineEdit *m_pEditZs;              //系统阻抗(Ω)
	QLineEdit *m_pEditZsPh;            //系统阻抗角(°)
	QLineEdit *m_pEditBrkBreakTime;    //分闸时间（s）
	QLineEdit *m_pEditBrkCloseTime;    //合闸时间（s）
	QLineEdit *m_pEditFaultAngle;      //合闸角（°）
	QLineEdit *m_pEditVzPh;            //抽取电压相角
	QLineEdit *m_pEditOutputKeepTime;  //开出保持时间
	QLineEdit *m_pEditOutputDelayTime; //开出翻转时刻

	QComboBox *m_pCmbFaultTrigMode;       //故障触发方式
	QComboBox *m_pCmbPTPos;			   //TV安装位置
	QComboBox *m_pCmbCTPos;               //TA正极性
	QComboBox *m_pCmbTestProcess;		   //试验过程
	QComboBox *m_pCmbRecloseMode;         //重合方式
	QComboBox *m_pCmbK0Mode;			   //零序补偿系数表达方式
	QComboBox *m_pCmbCalMode;             //计算方式
	QComboBox *m_pCmbSimulateBreakerDelay;//断路器模拟
	QComboBox *m_pCmbFaultIncMode;        //合闸角选择
	QComboBox *m_pCmbBIPlusDC;            //叠加非周期分量
	QComboBox *m_pCmbVzDefine;            //抽取电压输出定义
	QComboBox *m_pCmbPsuVzRefPhase;       //抽取电压参考相定义
	QComboBox *m_pCmbBinSelect;           //开入量选择
	QComboBox *m_pCmbBinA;                //开入A
	QComboBox *m_pCmbBinB;                //开入B
	QComboBox *m_pCmbBinC;                //开入C
	QComboBox *m_pCmbBinD;                //开入D
	QComboBox *m_pCmbBinE;                //开入E
	QComboBox *m_pCmbBinF;                //开入F
	QComboBox *m_pCmbBinG;                //开入G
	QComboBox *m_pCmbBinH;                //开入H
	QComboBox *m_pCmbBoutA;               //开出A
	QComboBox *m_pCmbBoutB;               //开出B
	QComboBox *m_pCmbBoutC;               //开出C
	QComboBox *m_pCmbBoutD;               //开出D
	QComboBox *m_pCmbBoutE;               //开出E
	QComboBox *m_pCmbBoutF;               //开出F
	QComboBox *m_pCmbBoutG;               //开出G
	QComboBox *m_pCmbBoutH;               //开出H
	QComboBox *m_pCmbOutputSwitchMode;    //开出翻转启动方式

	QTabWidget *m_pCommonParas;
	QWidget *m_pGeneralParas;
	QWidget *m_pBinBout;

	QPushButton *m_pBtnOKCommonParas;
	QPushButton *m_pBtnCancelCommonParas;
	QPushButton *m_pBtnOKBinBout;
	QPushButton *m_pCancelBinBout;

	QGridLayout *m_pBinBoutLayout;
	QGridLayout *m_pGeneralParasLayout;
	QVBoxLayout *m_pMainLayout;
	QVBoxLayout *m_pLayout;
	QHBoxLayout *m_pBtnResultAssessLayout;
	QHBoxLayout *m_pBtnCommonParasLayout;

	QSpacerItem *m_pSpacerleft;
	QSpacerItem *m_pSpacerright;

	QSpacerItem *m_pSpacerLeft;
	QSpacerItem *m_pSpacerRight;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;

public:
	void InitUI();
	void InitFont();
	void Initdates();
	void InitConnections();

public slots:
	void slot_BinSelect(int nIndex);
	void slot_OutputSwitchMode(int nIndex);
	void slot_FaultTrigMode(int nIndex);
	void slot_TestProcess(int nIndex);
	void slot_CalMode(int nIndex);
	void slot_SimulateBreakerDelay(int nIndex);
	void slot_FaultIncMode(int nIndex);
	void slot_VzDefine(int nIndex);

	void slot_BtnOKCommonParas();
	void slot_BtnCancelCommonParas();
	void slot_BtnOKBinBout();
	void slot_CancelBinBout();

	void slot_EditPreFaultTime();
	void slot_EditTimeAfterTrigger();
	void slot_EditAfterOpenTime();
	void slot_EditRecloseTime();
	void slot_EditAfterAccTime();
	void slot_EditKlKr();
	void slot_EditAngKx();
	void slot_EditZs();
	void slot_EditZsPh();
	void slot_EditBrkBreakTime();
	void slot_EditBrkCloseTime();
	void slot_EditFaultAngle();
	void slot_EditVzPh();
	void slot_EditOutputKeepTime();
	void slot_EditOutputDelayTime();
	void slot_EditK0Mode(int nValue);
};

#endif