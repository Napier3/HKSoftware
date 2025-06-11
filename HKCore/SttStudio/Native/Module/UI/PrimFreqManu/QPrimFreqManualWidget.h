#ifndef QPrimFreqManualWidget_H
#define QPrimFreqManualWidget_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/PrimFreq/tmt_prim_freq_manu_test.h"

#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttTabWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include "../Controls/SttLineEdit.h"


class QPrimFreqManualWidget : public QWidget
{
	Q_OBJECT

public:
	 explicit QPrimFreqManualWidget(QWidget *parent = NULL);
	 virtual ~QPrimFreqManualWidget();

    QSttLineEdit* m_pEditStep;
    QSttLineEdit* m_pEditInitVal;
	QSttLineEdit* m_pEditFinishVal;
    QSttLineEdit* m_pEditTime;
	QLabel* m_plabChannel;
	QLabel* m_plabTime;
	QLabel* m_plabChangeType;

    QScrollComboBox* m_pCbbChannel;
    QScrollComboBox* m_pCbbSelect;//通道类型选择(幅值/相位/频率)
    QScrollComboBox* m_pCbbChangeType;//始终/始终始

	QIcon m_imgLock;
	QIcon m_imgUnlock;

    QCheckBox* m_pCbOut1;
    QCheckBox* m_pCbOut2;
    QCheckBox* m_pCbOut3;
    QCheckBox* m_pCbOut4;
	QGroupBox* m_pGrpCbOut;

    QCheckBox* m_pCbAuto;

	QPushButton* m_pInBinaryOutSet;
	QPushButton* m_pBtnAdd;
	QPushButton* m_pBtnMinus;
	QPushButton* m_pBtnLock;

	QLabel* m_pLabStep; 
	QLabel* m_pLabInitVal;
	QLabel* m_pLabFinishVal;
	QGridLayout *m_pGridLayout;

	QSttTabWidget *m_pTabWidget;

	QHBoxLayout *m_pBtnLayout1;
	QHBoxLayout *m_pBtnLayout2;
	QVBoxLayout *m_pVMainLayout;
	QVBoxLayout *m_pVBtnLayout;
	QHBoxLayout *m_pHDownLayout;
	QHBoxLayout *m_pPulseLayout ;

	//一次调频部分

	// 转速脉冲信号
	QGroupBox* m_pGrpPulseSignal;
	QLabel* m_pLblPulseType;
	QScrollComboBox* m_pCbbPulseType;
	QLabel* m_pLblPulseWidth;
	QSttLineEdit* m_pEditPulseWidth;
	QLabel* m_pLblPeakValue;
	QScrollComboBox* m_pCbbPeakValue;
	QLabel* m_pLblPulseFreq;
	QSttLineEdit* m_pEditPulseFreq;

	// 直流信号源
	QHBoxLayout *m_pDcLayout ;
	QGroupBox* m_pGrpDcSignal;
	QLabel* m_pLblDc1;
	QScrollComboBox* m_pCbbDcChangeType;//直流电流通道转换方式
	QSttLineEdit* m_pEditDcChangeValue;
	QSttLineEdit* m_pEditDc1;
	QLabel* m_pLblDc2;
	QSttLineEdit* m_pEditDc2;
	QPushButton* m_pBtnMapping;

public:
	CSttTestResourceBase* m_pTestResource;
	tmt_PrimFreqManualParas* m_pManualParas;
	CEventResult* m_pEvent;

	int m_nVChNums,m_nIChNums;

private:
	bool m_bControlLock; //锁
	QString m_sUnit;
	CDataType m_oGradientChs;

	long m_nChanneType; //电压还是电流 0-电压 1-电流
	long m_nUnitType; //0-幅值 1-相位 2-频率

	float slot_lne_Changed(QSttLineEdit* pLineEdit);
	void ValidBinSelect();//验证开入选择是否有效,如果全都不选,默认勾选开入A

	void ChannelTableItemValue_AllFreq(float fstep,int AddOrMinus,bool bDC);//修改全部通道频率(前两组电压电流)

public:
	void Init();
	void InitUI();

	long GetChsCount() { return m_oGradientChs.GetCount(); }


	long GetChanneType();
	long GetCbbSelect();


signals:
	//向界面类发信号调用表格类的函数
	void sig_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);

};

#endif // MANUALVIEWPARAS_H
