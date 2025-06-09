#ifndef COMMONPARASDIALOG_H
#define COMMONPARASDIALOG_H

#include <QDialog> 
#include <QToolButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "..\..\Module\SttTest\Common\Impedance\tmt_impedance_test.h"
#include "..\..\Module\SttCmd\SttCmdDefineGlobal.h"
#include "..\..\Module\TestWinFrame\SysParasSetDlg\QValueComboBox.h"
#include "..\..\Module\TestWinFrame\SysParasSetDlg\QFloatLineEdit.h"
#include "..\..\Module\SttTest\Common\Impedance\tmt_cb_operate_test.h"
#include "..\..\Module\SttTest\Common\Impedance\tmt_distance_search_test.h"
#include "..\..\Module\SttTest\Common\Impedance\tmt_reclose_acc_test.h"
#include "..\..\Module\SttTest\Common\ActionTime\tmt_vol_inverse_time_test.h"
#include "..\..\Module\SttTest\Common\DC\tmt_dc_overcurrent_test.h"


class CommonParasDialog : public QDialog
{
	Q_OBJECT

public:
	CommonParasDialog(tmt_ImpedanceParas *pImpedanceParas,const CString &strMacroID,QWidget *parent);
	CommonParasDialog(tmt_VolInverseTimeParasEx *pVolInverseTimeParas, const CString &strMacroID,QWidget *parent);


	~CommonParasDialog();

	static void JudgeModifyPara(float a,float b);
	static void JudgeModifyPara(int a,int b);
	static void JudgeModifyPara(long a,long b);

	virtual void init(const CString &strMacroID); 
	
	void initUI_Base();//过流 距离 零序
	void initBtn();
	virtual void initData();
	virtual void initConnect();

	void initUI_CB();				//整组 mym 2021-8-3;
	void initData_CB();			//整组 mym 2021-8-3;
	void initPara_CB();			//整组 mym 2021-8-3;
	void initConnect_CB();
	void SetPara_CB();


	void initUI_Re();					//重合闸 mym 2021-8-11;
	void initData_Re();				// 重合闸 mym 2021-8-11;
	void initPara_Re();				//重合闸 mym 2021-8-11;
	void initConnect_Re();
	void SetPara_Re();


	void initUI_Voltage();
	void initPara_Voltage();
	void initData_Voltage();
	void initConnect_Voltage();
	void SetPara_Voltage();

	void initUI_DS();//搜索阻抗边界
	void initData_DS();
	void initConnect_DS();

	void initUI_DC();//过流保护(直流)
	void initData_DC();
	void initConnect_DC();

	//A的内容拷贝到B 过流 距离 零序 sf 20210804
	static void CopyPartForImpedance(tmt_ImpedanceParas &Para_A,tmt_ImpedanceParas &Para_B);
	static void CopyPartForDS(tmt_DistanceSearchParas &Para_A,tmt_DistanceSearchParas &Para_B);
	static void CopyPartForDCOverCurrent(tmt_DCOverCurrentParas &Para_A,tmt_DCOverCurrentParas &Para_B);

	void closeEvent(QCloseEvent *event);
	int m_nIsOK;//判断点击的是OK还是取消

public:
	tmt_ImpedanceParas *m_pImpedanceParas;
	tmt_ImpedanceParas m_ImpedanceParas;
public: //搜索阻抗边界
	tmt_DistanceSearchParas *m_pDSParas;
	tmt_DistanceSearchParas m_DSParas;
signals:
	void sig_ClickOk();  //信号预留使用,供外部调用
private slots:
	void slot_ClickOk();
	void slot_ClickCancel();

	void slot_FaultTimeChange();

	void slot_FaultTrigModeChange(int);
	void slot_CBSimulationChange(int);
	void slot_VzDefineChange(int);
	void slot_FaultIncModeChange(int);
	void slot_CalModeChange(int);
	void slot_K0CalModeChange(int);
	void slot_TestProcessChange_CB(int nIndex);
	void slot_CalcuModeChange_CB(int nIndex);
	void slot_CBSimulationChange_CB(int nIndex);
	void slot_PsuVzDefineChange_CB(int nIndex);
	void slot_FaultTrigModeChange_CB(int nIndex);	
	void slot_FaultAngleChange_CB(int nIndex);
	void slot_CTPointChange_Voltage(int nIndex);
	void slot_FaultTypeChange_Voltage(int nIndex);

	void slot_EditValueChanged_CB();    // mym 2021-9-15 add
	void slot_Cmb_Changed_CB(int nIndex);                     // mym 2021-9-15  add

	void slot_ClickOk_CB();
	void slot_ClickCancel_CB();

	void slot_ClickOk_Re();//重合闸
	void slot_ClickCancel_Re();//重合闸
	
	void slot_EditValueChanged_Re(/*QString strValue*/);    // mym 2021-9-15 add
	void slot_Cmb_Changed_Re(int nIndex);					  // mym 2021-9-15 add

	void slot_EditValueChanged_Voltage(QString strValue);    // mym 2021-9-15 add

	void slot_ClickOk_Voltage();
	void slot_ClickCancel_Voltage();

	void slot_ClickOk_DS();
	void slot_EditValueChanged_DS();
	
	void slot_ClickOk_DC();
	void slot_PreFaultVolChange_DC();//gongyiping 20231211 故障前电压(V)
	void slot_PreFaultCurChange_DC();//gongyiping 20231211 故障前电流(A)
	void slot_PreFaultTimeChange_DC();//gongyiping 20231211 故障前时间(s)
	void slot_PostFaultTimeChange_DC();//gongyiping 20231211 保护动作后持续时间(s)
	void slot_FaultTimeChange_DC();

	void slot_CBSimulationChange_Re(int nIndex);//重合闸里使用
	void slot_FaultTrigModeChange_Re(int nIndex);

public:
	QVBoxLayout *m_MainLayout;
	QGridLayout *m_TopLayout;
	QHBoxLayout *m_BottomLayout;


	QFloatLineEdit *m_editPreFaultTime;                 //故障前时间
	QLineEdit *m_editFaultTime;                //故障时间裕度  //20211026 sf 测试要求输入0.001的时候,要能挨个输入,验证器实现不了,所以使用信号槽
	QFloatLineEdit *m_editPostFaultTime;            //保护动作后持续时间
	QValueComboBox *m_CmbFaultTrigMode;        //故障触发方式

	QLabel *label_PreFaultTime;
	QLabel *label_FaultTime;
	QLabel *label_PostFaultTime;
	QLabel *label_FaultTrigMode;

	
	QValueComboBox *m_CmbPTPoint;             //PT安装位置
	QValueComboBox *m_CmbCTPoint;             //CT正极性
	QLabel *label_PTPoint;
	QLabel *label_CTPoint;

	QFloatLineEdit *m_editIfh;                     //负荷电流
	QFloatLineEdit *m_editPowerAngle;              //负荷功角
	QLabel *label_Ifh;
	QLabel *label_PowerAngle;

	QValueComboBox *m_CmbCBSimulation;        //是否模拟断路器延时
	QFloatLineEdit *m_editCBTripTime;               //分闸延时
	QFloatLineEdit *m_editCBCloseTime;             //合闸延时

	QLabel *label_CBSimulation;
	QLabel *label_CBTripTime;
	QLabel *label_CBCloseTime;

	QValueComboBox *m_CmbVzDefine;             //UZ输出定义
	QValueComboBox *m_CmbVzPhDefine;        //Uz参考相定义
	QFloatLineEdit *m_editVzPh;              //Uz相角
	QLabel *label_VzDefine;
	QLabel *label_VzPhDefine;
	QLabel *label_VzPh;

	//搜索阻抗边界
	QValueComboBox *m_CmbK0CalMode;             //零序补偿系数计算方式
	QFloatLineEdit *m_editK0Amp;              //零序补偿系数RE/RL
	QFloatLineEdit *m_editK0Angle;              //零序补偿系数XE/XL
	QLabel *label_K0CalMode;
	QLabel *label_K0Amp;
	QLabel *label_K0Angle;

	QValueComboBox *m_CmbSearchMode;             //搜索方式
	QValueComboBox *m_CmbCalMode;        //计算方式
	QLabel *label_SearchMode;
	QLabel *label_CalMode;

	QValueComboBox *m_CmbIPlusDC;             //是否叠加非周期分量
	QValueComboBox *m_CmbFaultIncMode;              //合闸角方式
	QFloatLineEdit *m_editFaultAngle;              //合闸角
	QLabel *label_IPlusDC;
	QLabel *label_FaultIncMode;
	QLabel *label_FaultAngle;

	QFloatLineEdit *m_editSetting0;				//系统阻抗
	QLabel *label_Setting0;

	QFloatLineEdit *m_editSetting1;				//系统阻抗角
	QLabel *label_Setting1;

	QPushButton *m_BtnOk;
	QPushButton *m_BtnCancel;
     int   m_nInitFlag;

	 QGroupBox *m_pPreFaultOutput_GroupBox;  //故障前输出Group
	 QGridLayout *m_pPreFaultOutput_GridLayout;
	 QLabel *label_PreFaultVol;			//故障前电压
	 QLabel *label_PreFaultCur;         //故障前电流
	 QFloatLineEdit *m_editPreFaultVol;  
	 QFloatLineEdit *m_editPreFaultCur;   

	 tmt_DCOverCurrentParas *m_pDCOverCurrentParas;
	 tmt_DCOverCurrentParas m_oDCOverCurrentParas;

	// 整组的东西 mym add 
public:
	QLabel *label_CB[25];
	QFloatLineEdit *m_pEditCB[13];                    //无压测试值
	QValueComboBox *m_pCmbCB[13];             //辅助电压Ux 输出方式

	tmt_CBOperateParas *m_pCBOperateParas;
	tmt_CBOperateParas m_oCBOperateParas;

	// 重合闸的东西 mym add 2021-8-11  
	public:
		QLabel *label_Re[25];
		QFloatLineEdit *m_pEditRe[13];                    //无压测试值
		QValueComboBox *m_pCmbRe[13];             //辅助电压Ux 输出方式

		tmt_RecloseAccParasEx *m_pRecloseAccParas;
		tmt_RecloseAccParasEx m_oRecloseAccParas;

public:

	QLabel *label_Volt[10];
	QFloatLineEdit *m_pEditVolt[10];                    //无压测试值
	QValueComboBox *m_pCmbVolt[10];             //辅助电压Ux 输出方式

	tmt_VolInverseTimeParasEx * m_pVolInverseTimeParas;
	tmt_VolInverseTimeParasEx   m_oVolInverseTimeParas;


	CString m_strMacroID;


};

void stt_copy_commparas_cb(tmt_CBOperateParas &Para_A,tmt_CBOperateParas &Para_B);
void stt_copy_commparas_re(tmt_RecloseAccParasEx &Para_A,tmt_RecloseAccParasEx &Para_B);
void stt_copy_commparas_volt(tmt_VolInverseTimeParasEx &Para_A,tmt_VolInverseTimeParasEx &Para_B);

#endif // COMMONPARASDIALOG_H
