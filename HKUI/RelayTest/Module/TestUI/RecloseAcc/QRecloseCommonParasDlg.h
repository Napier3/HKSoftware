#ifndef QRECLOSECOMMONPARASDLG_H
#define QRECLOSECOMMONPARASDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"


class QRecloseCommonParasDlg : public QDialog
{
	Q_OBJECT

public:
	QRecloseCommonParasDlg(CDataGroup *m_oRecloseAccDataGroup,QWidget *parent = 0);
	virtual ~QRecloseCommonParasDlg();            

public:

	QLabel *m_pLabFaultTrigMode;       //故障触发方式
	QLabel *m_pLabPTPos;			   //TV安装位置
	QLabel *m_pLabCTPos;               //TA正极性
	QLabel *m_pLabCurLoad;				   //负荷电流
	QLabel *m_pLabPowerAngleLoad;		   //负荷角度
	QLabel *m_pLabSimulateBreakerDelay;//断路器模拟
	QLabel *m_pLabBrkBreakTime;        //分闸时间（s）
	QLabel *m_pLabBrkCloseTime;        //合闸时间（s）

	QLabel *m_pLabBinSelect;           //开入量选择
	QLabel *m_pLabBinA;                //开入A
	QLabel *m_pLabBinB;                //开入B
	QLabel *m_pLabBinC;                //开入C
	QLabel *m_pLabBinD;                //开入D
	QLabel *m_pLabBinE;                //开入E
	QLabel *m_pLabBinF;                //开入F
	QLabel *m_pLabBinG;                //开入G
	QLabel *m_pLabBinH;                //开入H

	QLabel *m_pLabBout1;               //开出A
	QLabel *m_pLabBout2;               //开出B
	QLabel *m_pLabBout3;               //开出C
	QLabel *m_pLabBout4;               //开出D
	QLabel *m_pLabBout5;               //开出E
	QLabel *m_pLabBout6;               //开出F
	QLabel *m_pLabBout7;               //开出G
	QLabel *m_pLabBout8;               //开出H
	QLabel *m_pLabOutputSwitchMode;    //开出翻转启动方式
	QLabel *m_pLabOutputKeepTime;      //开出保持时间
	QLabel *m_pLabOutputDelayTime;     //开出翻转时刻

	QComboBox *m_pCmbFaultTrigMode;       //故障触发方式
	QComboBox *m_pCmbPTPos;			   //TV安装位置
	QComboBox *m_pCmbCTPos;               //TA正极性
	QLineEdit *m_pEditCurLoad;			  //负荷电流
	QLineEdit *m_pEditPowerAngleLoad;	  //负荷角度
	QComboBox *m_pCmbSimulateBreakerDelay;//断路器模拟
	QLineEdit *m_pEditBrkBreakTime;    //分闸时间（s）
	QLineEdit *m_pEditBrkCloseTime;    //合闸时间（s）

	QLineEdit *m_pEditOutputKeepTime;  //开出保持时间
	QLineEdit *m_pEditOutputDelayTime; //开出翻转时刻


	QComboBox *m_pCmbBinSelect;           //开入量选择
	QComboBox *m_pCmbBinA;                //开入A
	QComboBox *m_pCmbBinB;                //开入B
	QComboBox *m_pCmbBinC;                //开入C
	QComboBox *m_pCmbBinD;                //开入D
	QComboBox *m_pCmbBinE;                //开入E
	QComboBox *m_pCmbBinF;                //开入F
	QComboBox *m_pCmbBinG;                //开入G
	QComboBox *m_pCmbBinH;                //开入H
	QComboBox *m_pCmbBout1;               //开出1
	QComboBox *m_pCmbBout2;               //开出2
	QComboBox *m_pCmbBout3;               //开出3
	QComboBox *m_pCmbBout4;               //开出4
	QComboBox *m_pCmbBout5;               //开出5
	QComboBox *m_pCmbBout6;               //开出6
	QComboBox *m_pCmbBout7;               //开出7
	QComboBox *m_pCmbBout8;               //开出8
	QComboBox *m_pCmbOutputSwitchMode;    //开出翻转启动方式

	QTabWidget *m_pCommonParasTabWidget;
	QWidget *m_pGeneralParasWidget;
	QWidget *m_pBinWidget;
	QWidget *m_pBoutWidget;

	QPushButton *m_pBtnOKCommonParas;
	QPushButton *m_pBtnCancelCommonParas;
	QPushButton *m_pBtnOKBin;
	QPushButton *m_pBtnCancelBin;
	QPushButton *m_pBtnOKBout;
	QPushButton *m_pBtnCancelBout;

	QGridLayout *m_pBinLayout;
	QGridLayout *m_pBoutLayout;
	QGridLayout *m_pGeneralParasLayout;
	QVBoxLayout *m_pMainBinLayout;
	QVBoxLayout *m_pMainBoutLayout;
	QVBoxLayout *m_pMainCommonParasLayout;
	QHBoxLayout *m_pBinbtnLayout;
	QHBoxLayout *m_pCommonParasLayout;
	QHBoxLayout *m_pBoutbtnLayout;

	QSpacerItem *m_pSpacerLeft;
	QSpacerItem *m_pSpacerRight;
	CDataGroup *m_pRecloseCommonParasDataGroup;

public:
	void InitUI();
	void InitFont();
	void Initdates();
	void InitConnections();

public slots:
	void slot_BinSelect(int nIndex);
	void slot_OutputSwitchMode(int nIndex);
	void slot_SimulateBreakerDelay(int nIndex);

	void slot_OKCommonParas();
	void slot_CancelCommonParas();

	void slot_CurLoad();
	void slot_PowerAngleLoad();
	void slot_BrkBreakTime();
	void slot_BrkCloseTime();
	void slot_OutputKeepTime();
	void slot_OutputDelayTime();

};

#endif
