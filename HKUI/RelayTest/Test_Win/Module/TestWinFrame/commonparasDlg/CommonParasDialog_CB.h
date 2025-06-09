#ifndef COMMONPARASDIALOG_CB_H
#define COMMONPARASDIALOG_CB_H

#include <QDialog> 

#include "CommonParasDialog.h"
#include "..\..\Module\SttTest\Common\Impedance\tmt_cb_operate_test.h"
#include "..\..\Module\SttTest\Common\Impedance\tmt_reclose_acc_test.h"
class CommonParasDialog_CB : public CommonParasDialog
{
	Q_OBJECT

public:
	CommonParasDialog_CB(tmt_CBOperateParas *pImpedanceParas,  const CString &strMacroID,  QWidget *parent);
	~CommonParasDialog_CB();

public:
	QValueComboBox *m_CmbCalcuMode;             //计算方式
	QFloatLineEdit *m_editSystemImp;                  //系统阻抗
	QFloatLineEdit *m_editSystemImpAng;           //系统阻抗角

	QLabel *label_28;
	QLabel *label_29;
	QLabel *label_30;

	//int		m_nTestProcCtrlMode;	// 试验过程控制方式 0-跳合控制 1-时间控制
	//float m_nRecloseMode;// 重合方式：0-综重（单重+三重） 1-三重 2-不重合

	//pXmlSierialize->xml_serialize("开关跳开后持续时间","AfterRecloseTime","s","number",pParas->m_fTAfterReclose);

	QValueComboBox *m_CmbTestCtrlMode;             //试验过程控制方式
	QValueComboBox *m_CmbRecoseMode;             //重合方式
	QFloatLineEdit *m_editRecloseTime;                  //系统阻抗
	
	QLabel *label_31;
	QLabel *label_32;
	QLabel *label_33;
	tmt_CBOperateParas * m_pCBOperateParas;

	int		 m_nTestProcCtrlMode;	// 试验过程控制方式 0-跳合控制 1-时间控制
	int     m_nRecloseMode;           // 重合方式：0-综重（单重+三重） 1-三重 2-不重合
	float  m_fTAfterTrig;			        // 后加速开关跳开后持续时间

public:
 	virtual  void init();
 	virtual	void initUI();
 	virtual	void SetPara();
 	virtual	void initPara();
 	virtual	void initData();
	void init_CB();

};

#endif // COMMONPARASDIALOG_CB_H
