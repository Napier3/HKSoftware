#ifndef STTMACROPARAEDITVIEWOTHERSETDLG_H
#define STTMACROPARAEDITVIEWOTHERSETDLG_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QCheckBox>
#include <QString>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../Module/CommonCtrl_QT/QLongLineEdit.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../SttTestCntrFrameBase.h"

#define	 STT_MUAUTOTEST_COMBOX_MEASTEAP 				 _T("Combox1_select")    //接收报文类型
#define	 STT_MUAUTOTEST_COMBOX_TESTMETHOD				 _T("Combox2_select")    //测试方法
#define	 STT_MUAUTOTEST_COMBOX_BCODE 				 _T("Combox3_select")        //B码输出逻辑
#define	 STT_MUAUTOTEST_RATIOBUTTON_PPSSELECT 				 _T("PPS_SetType")  //PPS设置


class QSttMacroParaEditViewOtherSetDlg : public QDialog
{
	Q_OBJECT

public:

	QSttMacroParaEditViewOtherSetDlg(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewOtherSetDlg();

    QHBoxLayout* m_pMainLayout;
	QVBoxLayout* m_pLGroupBoxLayout;
	QVBoxLayout* m_pRGroupBoxLayout;
	QHBoxLayout* m_pButtonLayout;
	QVBoxLayout* m_pRAllLayout;
	QGridLayout* m_pParasetlayout;
	QGridLayout* m_pPPssetlayout;
	QGroupBox* m_pGroupBox_L;
	QGroupBox* m_pGroupBox_R;
    QLabel* m_pReceivLabel;
	QLabel* m_pTestLabel;
	QLabel* m_pBOutputLabel;
	QComboBox* m_pRCombox;
	QComboBox* m_pTCombox;
	QComboBox* m_pBCombox;
	QRadioButton* m_pNoPPSRButton;
	QRadioButton* m_pRiseRButton; 
	QRadioButton* m_pFallRButton; 
	QPushButton* m_pButton_OK;
	QPushButton* m_pButton_Cancel;

	CDataGroup*  m_pOPSetDataGroup;


public:
	void InitUI();
	void InitData();
	//void UpdateMUOtherParaSetUI();
	void InitConnection();
	void GetDatas(CDataGroup *m_pParas);
	void ComboxSelected();
	void RatioSelected();

public slots:
    void slot_Confirm();
	void slot_Cancel();
	
};

#endif