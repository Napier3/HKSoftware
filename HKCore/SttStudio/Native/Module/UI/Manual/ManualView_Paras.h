#ifndef MANUALVIEWPARAS_H
#define MANUALVIEWPARAS_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/tmt_manu_test.h"

#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include "../Module/ScrollCtrl/ScrollComboBox.h"

class QManualView_Paras : public QObject
{
	Q_OBJECT

public:
    QManualView_Paras();
    virtual ~QManualView_Paras();

    //QLineEdit* m_pEditDelayed;
    QLineEdit* m_pEditStep;
    QLineEdit* m_pEditInitVal;
	QLineEdit* m_pEditFinishVal;
    QLineEdit* m_pEditTime;

	QLineEdit *m_pEditUdc;

    QScrollComboBox* m_pCbbChannel;
    QScrollComboBox* m_pCbbSelect;//通道类型选择(幅值/相位/频率)
    QScrollComboBox* m_pCbbChangeType;

	QIcon m_imgLock;
	QIcon m_imgUnlock;

    QCheckBox* m_pCbOut1;
    QCheckBox* m_pCbOut2;
    QCheckBox* m_pCbOut3;
    QCheckBox* m_pCbOut4;
    /*QCheckBox* m_pCbOut5;
    QCheckBox* m_pCbOut6;
    QCheckBox* m_pCbOut7;
    QCheckBox* m_pCbOut8;
	QCheckBox* m_pCbOut9;
	QCheckBox* m_pCbOut10;
	QCheckBox* m_pCbInA;
	QCheckBox* m_pCbInB;
	QCheckBox* m_pCbInC;
	QCheckBox* m_pCbInD;
	QCheckBox* m_pCbInE;
	QCheckBox* m_pCbInF;
	QCheckBox* m_pCbInG;
	QCheckBox* m_pCbInH;
	QCheckBox* m_pCbInI;
	QCheckBox* m_pCbInJ;*/
    QCheckBox* m_pCbOld;
    QCheckBox* m_pCbAuto;
    QCheckBox* m_pCbDC;
	/*QCheckBox* m_pCheckBoxDC;
	QCheckBox* m_pCheckBoxOld;*/
	QPushButton* m_pInBinaryOutSet;


// 	QRadioButton* m_pBtnAnd;
// 	QRadioButton* m_pBtnOr;

	QPushButton* m_pBtnAdd;
	QPushButton* m_pBtnMinus;
	QPushButton* m_pBtnLock;

//	QCheckBox *m_pCheckBoxHarm;// zhouhj 2023.7.31 删除重复
	QScrollComboBox *m_pComboBoxHarm;

	QLabel* m_pLabStep; 
	QLabel* m_pLabInitVal;
	QLabel* m_pLabFinishVal;
	/*
	QLineEdit* m_pEditAction;
	QLineEdit* m_pEditActionTime;
	QLineEdit* m_pEditReturn;
	QLineEdit* m_pEditReturnTime;
	QLabel* m_pLabAction;
	QLabel* m_pLabReturn;
	*/

public:
	CSttTestResourceBase* m_pTestResource;
	tmt_ManualParas* m_pManualParas;
	CEventResult* m_pEvent;

	int m_nVChNums,m_nIChNums;

private:
	bool m_bControlLock; //锁
	QString m_sUnit;
	CDataType m_oGradientChs;

	long m_nChanneType; //电压还是电流 0-电压 1-电流
	long m_nUnitType; //0-幅值 1-相位 2-频率

	float slot_lne_Changed(QLineEdit* pLineEdit);
	void ValidBinSelect();//验证开入选择是否有效,如果全都不选,默认勾选开入A

	void ChannelTableItemValue_AllFreq(float fstep,int AddOrMinus,bool bDC);//修改全部通道频率(前两组电压电流)

public:
	void Init();
	void InitHarmCombox();
	/*
	void UpdateResult(float fActValue, float fActTime,
					  float fReturnValue, float fReturnTime);
	void UpdateResult(const CString& strActValue, const CString& strActTime,
		const CString& strReturnValue, const CString& strReturnTime);
	*/

	void SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* pManualParas,CEventResult* pEvent);
	void UpdateData();
	void InitGradientData();
	void SetUnitType (int index);
	long GetChsCount() { return m_oGradientChs.GetCount(); }

	void InitGradientVarList();
	void InitGradientVar(para_type vartype);

	void StartInit();
	void StopInit();

public:
	void slot_btn_LockClicked();
	void slot_btn_AddClicked();
	void slot_btn_MinusClicked();
	void slot_lne_startChanged();
	void slot_lne_endChanged();
	void slot_lne_stepChanged();
	//void slot_lne_delayedChanged();
	void slot_lne_steptimeChanged();
	void slot_lne_UdcChanged();
	void slot_cb_OldClicked();
	void slot_cb_AutoClicked();
	void slot_cb_DCClicked();
	void slot_cbb_SelectChanged(int index);
	void slot_cbb_ChannelChanged(int index);
	void slot_cbb_ChangeTypeChanged(int index);

	void slot_ck_Out1StateChanged();
	void slot_ck_Out2StateChanged();
	void slot_ck_Out3StateChanged();
	void slot_ck_Out4StateChanged();
	/*void slot_ck_Out5StateChanged();
	void slot_ck_Out6StateChanged();
	void slot_ck_Out7StateChanged();
	void slot_ck_Out8StateChanged();
	void slot_ck_Out9StateChanged();
	void slot_ck_Out10StateChanged();

	void slot_ck_InAStateChanged();
	void slot_ck_InBStateChanged();
	void slot_ck_InCStateChanged();
	void slot_ck_InDStateChanged();
	void slot_ck_InEStateChanged();
	void slot_ck_InFStateChanged();
	void slot_ck_InGStateChanged();
	void slot_ck_InHStateChanged();
	void slot_ck_InIStateChanged();
	void slot_ck_InJStateChanged();*/

	/*void slot_rb_RdAndStateChanged();
	void slot_rb_RdOrStateChanged();*/

	void slot_UpdateUdcEditEnabled();

signals:
	//向界面类发信号调用表格类的函数
	void sig_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);

};

#endif // MANUALVIEWPARAS_H
