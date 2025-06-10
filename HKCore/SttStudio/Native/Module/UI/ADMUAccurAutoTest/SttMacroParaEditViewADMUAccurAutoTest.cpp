#include "SttMacroParaEditViewADMUAccurAutoTest.h"
#include "ADMUAccurAutoTestParasSetDialog.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../Module/SmartCap/XSmartCapMngr.h"

QSttMacroParaEditViewAdmuAccurAutoTest *g_pAdmuAccurAutoTest = NULL;

QSttMacroParaEditViewAdmuAccurAutoTest::QSttMacroParaEditViewAdmuAccurAutoTest( QWidget *parent)
:CSttMacroParaEditViewOriginal(parent)
{
	g_pAdmuAccurAutoTest = this;
	m_pFirstHarmTimesLineEdit = NULL;
	m_pLastHarmTimesLineEdit = NULL;
	m_pParasSetBtn = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(&m_pADMUAutoTestDataGroup);
}

QSttMacroParaEditViewAdmuAccurAutoTest::~QSttMacroParaEditViewAdmuAccurAutoTest()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear(); 

	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		delete m_pAllLineEditList.at(i); 
	}
	m_pAllLineEditList.clear(); 

	for (int i = 0; i < m_pAllGroupBoxList.size(); ++i) 
	{
		delete m_pAllGroupBoxList.at(i); 
	}
	m_pAllGroupBoxList.clear();
}

void QSttMacroParaEditViewAdmuAccurAutoTest::InitUI()
{
	CString strText ,strID;
	QGroupBox *pBinaryGroupBox = new QGroupBox;
	strText = _T("����������");
	pBinaryGroupBox->setTitle(strText);
	pBinaryGroupBox->setObjectName(_T("Binary_Check"));
	m_pAllGroupBoxList.append(pBinaryGroupBox);
	QGridLayout *pBinaryLayout = new QGridLayout(pBinaryGroupBox);
	for (int nIndex=1;nIndex<=5;nIndex++)
	{
		strText.Format(_T("����%d"),nIndex);
		strID.Format(_T("B0%d_Check"),nIndex);
		QCheckBox *pBinaryCheck = new QCheckBox();
		pBinaryCheck->setText(strText);
		pBinaryLayout->addWidget(pBinaryCheck,0,nIndex-1);
		pBinaryCheck->setObjectName(strID);
		//GetCheckBoxValue(pBinaryCheck,strID);
		m_pAllCheckBoxList.append(pBinaryCheck);
		connect(pBinaryCheck, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}

	QLabel *pBoutCountLabel = new QLabel;
	strText = _T("������λ����");
	pBoutCountLabel->setText(strText);
	QLineEdit *pBoutCountLineEdit = new QLineEdit;
	pBoutCountLineEdit->setObjectName(QString::fromUtf8("Bout_Count"));
	pBoutCountLineEdit->setMaximumWidth(100);
	m_pAllLineEditList.append(pBoutCountLineEdit);
	//GetLineEditValue(pBoutCountLineEdit,_T("Bout_Count"));
	connect(pBoutCountLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	QHBoxLayout *pBoutCountBoxLayout = new QHBoxLayout;
	pBoutCountBoxLayout->addWidget(pBoutCountLabel);
	pBoutCountBoxLayout->addWidget(pBoutCountLineEdit);
	//pBoutCountBoxLayout->addSpacerItem(new QSpacerItem(20,5,QSizePolicy::Expanding));
	pBoutCountBoxLayout->addStretch();
	QWidget *pBoutCountWidget = new QWidget;
	pBoutCountWidget->setLayout(pBoutCountBoxLayout);
	pBinaryLayout->addWidget(pBoutCountWidget, 0, 6,1,2);

	QGroupBox *pAccuracyGroupBox = new QGroupBox;
	strText = _T("׼ȷ������");
	pAccuracyGroupBox->setTitle(strText);
	pAccuracyGroupBox->setObjectName(_T("Accary_Check"));
	m_pAllGroupBoxList.append(pAccuracyGroupBox);
	QGridLayout  *pAccuracyLayout = new QGridLayout (pAccuracyGroupBox);    
	QLabel *pCurLabel = new QLabel(this);
	strText = _T("����");
	pCurLabel->setText(strText);
	QLabel *pVolLabel = new QLabel(this);
	strText = _T("��ѹ");
	pVolLabel->setText(strText);
	QLabel *pCustomLabel = new QLabel(this);
	strText = _T("�Զ���");
	pCustomLabel->setText(strText);
	QLabel *pPhaseDiffLabel = new QLabel(this);
	strText = _T("��λ��");
	pPhaseDiffLabel->setText(strText);
	pAccuracyLayout->addWidget(pVolLabel,0,0);
	pAccuracyLayout->addWidget(pCurLabel,1,0);
	pAccuracyLayout->addWidget(pCustomLabel,2,0);
	pAccuracyLayout->addWidget(pPhaseDiffLabel,3,0);

	QStringList oCurList,oVolList;
	oVolList << _T("2%") << _T("5%")<< _T("20%")<< _T("100%")<< _T("120%")<< _T("190%")<< _T("300%");
	oCurList << _T("1%") << _T("5%")<< _T("20%")<< _T("100%")<< _T("120%")<< _T("1000%")<< _T("3000%");

	for (int i = 0; i < oVolList.size(); ++i)
	{
		QCheckBox* pVolCheckBox = new QCheckBox;
		strText = oVolList.at(i);
		pVolCheckBox->setText(strText);
		pAccuracyLayout->addWidget(pVolCheckBox,0,i+1,1,1);
		strText = ProcessString(strText);
		strID = _T("Un_") + strText + _T("_Check");
		pVolCheckBox->setObjectName(strID);
		//GetCheckBoxValue(pVolCheckBox,strID);
		m_pAllCheckBoxList.append(pVolCheckBox);
		connect(pVolCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}

	for (int i = 0; i < oCurList.size(); ++i)
	{
		QCheckBox* pCurCheckBox = new QCheckBox;
		strText = oCurList.at(i);
		pCurCheckBox->setText(strText);
		pAccuracyLayout->addWidget(pCurCheckBox,1,i+1,1,1);
		strText = ProcessString(strText);
		strID = _T("In_") + strText + _T("_Check");
		pCurCheckBox->setObjectName(strID);
		//GetCheckBoxValue(pCurCheckBox,strID);
		m_pAllCheckBoxList.append(pCurCheckBox);
		connect(pCurCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}

	QLineEdit *pUnLineEdit1 = new QLineEdit;
	pUnLineEdit1->setObjectName(QString::fromUtf8("Un_Custom1"));
	//GetLineEditValue(pUnLineEdit1,_T("Un_Custom1"));
	connect(pUnLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	QCheckBox* pUnCheckBox1 = new QCheckBox;
	pUnCheckBox1->setObjectName(QString::fromUtf8("Un_Custom1_Check"));
	//GetCheckBoxValue(pUnCheckBox1,_T("Un_Custom1_Check"));
	connect(pUnCheckBox1, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pUnCheckBox1);
	m_pAllLineEditList.append(pUnLineEdit1);

	QLabel *pUnLabel1 = new QLabel;
	QLineEdit *pUnLineEdit2 = new QLineEdit;
	pUnLineEdit2->setObjectName(QString::fromUtf8("Un_Custom2"));
	//GetLineEditValue(pUnLineEdit2,_T("Un_Custom2"));
	connect(pUnLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	QCheckBox* pUnCheckBox2 = new QCheckBox;
	pUnCheckBox2->setObjectName(QString::fromUtf8("Un_Custom2_Check"));
	//GetCheckBoxValue(pUnCheckBox2,_T("Un_Custom2_Check"));
	connect(pUnCheckBox2, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pUnCheckBox2);
	m_pAllLineEditList.append(pUnLineEdit2);

	QLabel *pUnLabel2 = new QLabel;
	QLineEdit *pInLineEdit1 = new QLineEdit;
	pInLineEdit1->setObjectName(QString::fromUtf8("In_Custom1"));
	//GetLineEditValue(pInLineEdit1,_T("In_Custom1"));
	connect(pInLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	QCheckBox* pInCheckBox1 = new QCheckBox;
	pInCheckBox1->setObjectName(QString::fromUtf8("In_Custom1_Check"));
	//GetCheckBoxValue(pInCheckBox1,_T("In_Custom1_Check"));
	connect(pInCheckBox1, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pInCheckBox1);
	m_pAllLineEditList.append(pInLineEdit1);

	QLabel *pInLabel1 = new QLabel;
	QLineEdit *pInLineEdit2 = new QLineEdit;
	pInLineEdit2->setObjectName(QString::fromUtf8("In_Custom2"));
	//GetLineEditValue(pInLineEdit2,_T("In_Custom2"));
	connect(pInLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	QCheckBox* pInCheckBox2 = new QCheckBox;
	pInCheckBox2->setObjectName(QString::fromUtf8("In_Custom2_Check"));
	//GetCheckBoxValue(pInCheckBox2,_T("In_Custom2_Check"));
	connect(pInCheckBox2, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pInCheckBox2);
	m_pAllLineEditList.append(pInLineEdit2);

	QLabel *pInLabel2 = new QLabel;
	strText = _T("%Un");
	pUnLabel1->setText(strText);
	pUnLabel2->setText(strText);
	strText = _T("%In");
	pInLabel1->setText(strText);
	pInLabel2->setText(strText);
	pUnLineEdit1->setMaximumWidth(100);
	pUnLineEdit2->setMaximumWidth(100);
	pInLineEdit1->setMaximumWidth(100);
	pInLineEdit2->setMaximumWidth(100);
	QHBoxLayout *pCustomHBoxLayout = new QHBoxLayout;
	pCustomHBoxLayout->addWidget(pUnCheckBox1);
	pCustomHBoxLayout->addWidget(pUnLineEdit1);
	pCustomHBoxLayout->addWidget(pUnLabel1);
	pCustomHBoxLayout->addWidget(pUnCheckBox2);
	pCustomHBoxLayout->addWidget(pUnLineEdit2);
	pCustomHBoxLayout->addWidget(pUnLabel2);
	pCustomHBoxLayout->addWidget(pInCheckBox1);
	pCustomHBoxLayout->addWidget(pInLineEdit1);
	pCustomHBoxLayout->addWidget(pInLabel1);
	pCustomHBoxLayout->addWidget(pInCheckBox2);
	pCustomHBoxLayout->addWidget(pInLineEdit2);
	pCustomHBoxLayout->addWidget(pInLabel2);
	pCustomHBoxLayout->addStretch();

	QWidget *pCustomWidget = new QWidget;
	pCustomWidget->setLayout(pCustomHBoxLayout);
	pAccuracyLayout->addWidget(pCustomWidget, 2, 1, 1, 7);
	QLabel *pAngelLabel = new QLabel;
	strText = _T("�н�");
	pAngelLabel->setText(strText);
	QLineEdit *pAngelLineEdit = new QLineEdit;
	pAngelLineEdit->setMaximumWidth(100);
	QLabel *pAngelLabel1 = new QLabel;
	strText = _T("��");
	pAngelLabel1->setText(strText);
	QHBoxLayout *pPhaseDiffHBoxLayout = new QHBoxLayout(this);
	pPhaseDiffHBoxLayout->addWidget(pAngelLabel);
	pPhaseDiffHBoxLayout->addWidget(pAngelLineEdit);
	pPhaseDiffHBoxLayout->addWidget(pAngelLabel1);
	pPhaseDiffHBoxLayout->addSpacing(10);
	pAngelLineEdit->setObjectName(QString::fromUtf8("Ang"));
	//GetLineEditValue(pAngelLineEdit,_T("Ang"));
	connect(pAngelLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	m_pAllLineEditList.append(pAngelLineEdit);

	QStringList oPhseCurList;
	oPhseCurList << _T("1%In") << _T("5%In")<< _T("20%In")<< _T("100%In")<< _T("120%In");
	for (int i = 0; i < oPhseCurList.size(); ++i)
	{
		QCheckBox* pInCheckBox = new QCheckBox;
		strText = oPhseCurList.at(i);
		pInCheckBox->setText(strText);
		pPhaseDiffHBoxLayout->addWidget(pInCheckBox);
		strText = ProcessString(strText);
		strID = _T("Ang_") + strText + _T("In_Check");
		pInCheckBox->setObjectName(strID);
		//GetCheckBoxValue(pInCheckBox,strID);
		m_pAllCheckBoxList.append(pInCheckBox);
		connect(pInCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}
	QWidget *pPhaseDiffWidget = new QWidget;
	pPhaseDiffWidget->setLayout(pPhaseDiffHBoxLayout);
	pAccuracyLayout->addWidget(pPhaseDiffWidget, 3, 1, 1, 7);
 	pAccuracyLayout->setVerticalSpacing(5); 

	QGroupBox *pFreqGroupBox = new QGroupBox;
	strText = _T("Ƶ��Ӱ����׼ȷ������");
	pFreqGroupBox->setTitle(strText);
	pFreqGroupBox->setObjectName(_T("FreqAccuary_Check"));
	m_pAllGroupBoxList.append(pFreqGroupBox);
	QHBoxLayout  *pFreqLayout = new QHBoxLayout (pFreqGroupBox);
	QCheckBox* pCheckBox45Hz = new QCheckBox;
	strText = _T("45Hz");
	pCheckBox45Hz->setText(strText);
	QCheckBox* pCheckBox55Hz = new QCheckBox;
	strText = _T("55Hz");
	pCheckBox45Hz->setObjectName(QString::fromUtf8("F_45_Check"));
	//GetCheckBoxValue(pCheckBox45Hz,_T("F_45_Check"));
	connect(pCheckBox45Hz, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pCheckBox55Hz->setText(strText);
	pCheckBox55Hz->setObjectName(QString::fromUtf8("F_55_Check"));
	//GetCheckBoxValue(pCheckBox55Hz,_T("F_55_Check"));
	connect(pCheckBox55Hz, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pCheckBox45Hz);
	m_pAllCheckBoxList.append(pCheckBox55Hz);
	QLabel *pFreqCustomLabel = new QLabel;
	strText = _T("�Զ���");
	pFreqCustomLabel->setText(strText);
	QCheckBox* pCheckBoxHz1 = new QCheckBox;
	QLineEdit *pLineEditHz1 = new QLineEdit;
	QLabel *pLabelHz1 = new QLabel;
	strText = _T("Hz");
	pLabelHz1->setText(strText);
	QCheckBox* pCheckBoxHz2 = new QCheckBox;
	QLineEdit *pLineEditHz2 = new QLineEdit;
	QLabel *pLabelHz2 = new QLabel;
	strText = _T("Hz");
	pLabelHz2->setText(strText);
	pCheckBoxHz1->setObjectName(QString::fromUtf8("F_Custom1_Check"));
	//GetCheckBoxValue(pCheckBoxHz1,_T("F_Custom1_Check"));
	connect(pCheckBoxHz1, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pLineEditHz1->setObjectName(QString::fromUtf8("F_Custom1"));
	//GetLineEditValue(pLineEditHz1,_T("F_Custom1"));
	connect(pLineEditHz1, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pCheckBoxHz2->setObjectName(QString::fromUtf8("F_Custom2_Check"));
	//GetCheckBoxValue(pCheckBoxHz2,_T("F_Custom2_Check"));
	connect(pCheckBoxHz2, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pLineEditHz2->setObjectName(QString::fromUtf8("F_Custom2"));
	//GetLineEditValue(pLineEditHz2,_T("F_Custom2"));
	connect(pLineEditHz2, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	m_pAllCheckBoxList.append(pCheckBoxHz1);
	m_pAllCheckBoxList.append(pCheckBoxHz2);
	m_pAllLineEditList.append(pLineEditHz1);
	m_pAllLineEditList.append(pLineEditHz2);
	pLineEditHz1->setMaximumWidth(100);
	pLineEditHz2->setMaximumWidth(100);
	pFreqLayout->addWidget(pCheckBox45Hz);
	pFreqLayout->addWidget(pCheckBox55Hz);
	pFreqLayout->addWidget(pFreqCustomLabel);
	pFreqLayout->addWidget(pCheckBoxHz1);
	pFreqLayout->addWidget(pLineEditHz1);
	pFreqLayout->addWidget(pLabelHz1);
	pFreqLayout->addWidget(pCheckBoxHz2);
	pFreqLayout->addWidget(pLineEditHz2);
	pFreqLayout->addWidget(pLabelHz2);
	pFreqLayout->addStretch();
	QGroupBox *pHarmGroupBox = new QGroupBox;
	strText = _T("г��Ӱ����׼ȷ������");
	pHarmGroupBox->setTitle(strText);
	pHarmGroupBox->setObjectName(_T("HarmAccuary_Check"));
	m_pAllGroupBoxList.append(pHarmGroupBox);
	QHBoxLayout  *pHarmLayout = new QHBoxLayout (pHarmGroupBox);
	QCheckBox* pHarmCheckBox = new QCheckBox;
	strText = _T("����ʩ��г��");
	pHarmCheckBox->setText(strText);
	pHarmCheckBox->setObjectName(QString::fromUtf8("Harm_Check"));
	//GetCheckBoxValue(pHarmCheckBox,_T("Harm_Check"));
	connect(pHarmCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pFirstHarmTimesLineEdit = new QLineEdit;
	QLabel *pLabelHarm1 = new QLabel;
	strText = _T("��");
	pLabelHarm1->setText(strText);
	m_pLastHarmTimesLineEdit = new QLineEdit;
	QLabel *pLabelHarm2 = new QLabel;
	strText = _T("��");
	pLabelHarm2->setText(strText);
	QLabel *pLabelHarm3 = new QLabel;
	strText = _T("��ѹг������");
	pLabelHarm3->setText(strText);
	QLineEdit *pLineEditHarm3 = new QLineEdit;
	QLabel *pLabelHarm4 = new QLabel;
	strText = _T("%");
	pLabelHarm4->setText(strText);
	QLabel *pLabelHarm5 = new QLabel;
	strText = _T("����г������");
	pLabelHarm5->setText(strText);
	QLineEdit *pLineEditHarm4 = new QLineEdit;
	QLabel *pLabelHarm6 = new QLabel;
	strText = _T("%");
	pLabelHarm6->setText(strText);
	m_pFirstHarmTimesLineEdit->setObjectName(QString::fromUtf8("First_Harm_Times"));
	m_pLastHarmTimesLineEdit->setObjectName(QString::fromUtf8("Last_Harm_Times"));
	//GetLineEditValue(m_pFirstHarmTimesLineEdit,_T("First_Harm_Times"));
	connect(m_pFirstHarmTimesLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_FirstHarmTimeseditFinished()));
	//GetLineEditValue(m_pLastHarmTimesLineEdit,_T("Last_Harm_Times"));
	connect(m_pLastHarmTimesLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LastHarmTimeseditFinished()));
	pLineEditHarm3->setObjectName(QString::fromUtf8("U_Harm_Content"));
	//GetLineEditValue(pLineEditHarm3,_T("U_Harm_Content"));
	connect(pLineEditHarm3, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pLineEditHarm4->setObjectName(QString::fromUtf8("I_Harm_Content"));
	//GetLineEditValue(pLineEditHarm4,_T("I_Harm_Content"));
	connect(pLineEditHarm4, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	m_pAllCheckBoxList.append(pHarmCheckBox);
	m_pAllLineEditList.append(m_pFirstHarmTimesLineEdit);
	m_pAllLineEditList.append(m_pLastHarmTimesLineEdit);
	m_pAllLineEditList.append(pLineEditHarm3);
	m_pAllLineEditList.append(pLineEditHarm4);
	m_pFirstHarmTimesLineEdit->setMaximumWidth(100);
	m_pLastHarmTimesLineEdit->setMaximumWidth(100);
	pLineEditHarm3->setMaximumWidth(100);
	pLineEditHarm4->setMaximumWidth(100);
	pHarmLayout->addWidget(pHarmCheckBox);
	pHarmLayout->addWidget(m_pFirstHarmTimesLineEdit);
	pHarmLayout->addWidget(pLabelHarm1);
	pHarmLayout->addWidget(m_pLastHarmTimesLineEdit);
	pHarmLayout->addWidget(pLabelHarm2);
	pHarmLayout->addWidget(pLabelHarm3);
	pHarmLayout->addWidget(pLineEditHarm3);
	pHarmLayout->addWidget(pLabelHarm4);
	pHarmLayout->addWidget(pLabelHarm5);
	pHarmLayout->addWidget(pLineEditHarm4);
	pHarmLayout->addWidget(pLabelHarm6);

	QGroupBox *pAnalogGroupBox = new QGroupBox;
	strText = _T("ģ�������������������");
	pAnalogGroupBox->setTitle(strText);
	pAnalogGroupBox->setObjectName(_T("TimeOver_Check"));
	m_pAllGroupBoxList.append(pAnalogGroupBox);
	QGridLayout  *pAnalogLayout = new QGridLayout (pAnalogGroupBox);
	m_pParasSetBtn = new QPushButton(this);
	strText = _T("��������");
	m_pParasSetBtn->setText(strText);
	m_pParasSetBtn->setMaximumWidth(80);
	QLabel *pContinueLabel = new QLabel(this);
	strText = _T("������������");
	pContinueLabel->setText(strText);
	QLabel *pShortLabel = new QLabel(this);
	strText = _T("��ʱ��������");
	pShortLabel->setText(strText);
	QCheckBox* pContinVol = new QCheckBox;
	strText = _T("��ѹ");
	pContinVol->setText(strText);
	QCheckBox* pContinCur = new QCheckBox;
	strText = _T("����");
	pContinCur->setText(strText);
	QCheckBox* pContinVolCur = new QCheckBox;
	strText = _T("��ѹ�͵���");
	pContinVolCur->setText(strText);
	QCheckBox* pShortVol = new QCheckBox;
	strText = _T("��ѹ");
	pShortVol->setText(strText);
	QCheckBox* pShortCur = new QCheckBox;
	strText = _T("����");
	pShortCur->setText(strText);
	pContinVol->setObjectName(QString::fromUtf8("LongTimeOver_U_Check"));
	//GetCheckBoxValue(pContinVol,_T("LongTimeOver_U_Check"));
	connect(pContinVol, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pContinCur->setObjectName(QString::fromUtf8("LongTimeOver_I_Check"));
	//GetCheckBoxValue(pContinCur,_T("LongTimeOver_I_Check"));
	connect(pContinCur, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pContinVolCur->setObjectName(QString::fromUtf8("LongTimeOver_UI_Check"));
	//GetCheckBoxValue(pContinVolCur,_T("LongTimeOver_UI_Check"));
	connect(pContinVolCur, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pShortVol->setObjectName(QString::fromUtf8("ShortTimeOver_U_Check"));
	//GetCheckBoxValue(pShortVol,_T("ShortTimeOver_U_Check"));
	connect(pShortVol, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pShortCur->setObjectName(QString::fromUtf8("ShortTimeOver_I_Check"));
	//GetCheckBoxValue(pShortCur,_T("ShortTimeOver_I_Check"));
	connect(pShortCur, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	m_pAllCheckBoxList.append(pContinVol);
	m_pAllCheckBoxList.append(pContinCur);
	m_pAllCheckBoxList.append(pContinVolCur);
	m_pAllCheckBoxList.append(pShortVol);
	m_pAllCheckBoxList.append(pShortCur);
	pAnalogLayout->addWidget(m_pParasSetBtn,0,0,2,1);
	pAnalogLayout->addWidget(pContinueLabel,0,1,1,1);
	pAnalogLayout->addWidget(pContinVol,0,2,1,1);
	pAnalogLayout->addWidget(pContinCur,0,3,1,1);
	pAnalogLayout->addWidget(pContinVolCur,0,4,1,1);
	pAnalogLayout->addWidget(pShortLabel,1,1,1,1);
	pAnalogLayout->addWidget(pShortVol,1,2,1,1);
	pAnalogLayout->addWidget(pShortCur,1,3,1,1);

	QGroupBox *pBatteryGroupBox = new QGroupBox;
	strText = _T("����ͨ���ȶ�������");
	pBatteryGroupBox->setTitle(strText);
	pBatteryGroupBox->setObjectName(_T("Battery_Check"));
	m_pAllGroupBoxList.append(pBatteryGroupBox);
	QHBoxLayout  *pBatteryLayout = new QHBoxLayout (pBatteryGroupBox);
	QCheckBox* pBatteryBox = new QCheckBox;
	strText = _T("����ͨ��ʱ��");
	pBatteryBox->setText(strText);
	QLineEdit *pBatteryLineEdit = new QLineEdit;
	QLabel *pHourLabel = new QLabel;
	strText = _T("Сʱ");
	pHourLabel->setText(strText);
	pBatteryLineEdit->setMaximumWidth(100);
	pBatteryLayout->addWidget(pBatteryBox);
	pBatteryLayout->addWidget(pBatteryLineEdit);
	pBatteryLayout->addWidget(pHourLabel);
	pBatteryLayout->addStretch();
	pBatteryBox->setObjectName(QString::fromUtf8("CPS_Check"));
	//GetCheckBoxValue(pBatteryBox,_T("CPS_Check"));
	connect(pBatteryBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	pBatteryLineEdit->setObjectName(QString::fromUtf8("CPS_Time"));
	//GetLineEditValue(pBatteryLineEdit,_T("CPS_Time"));
	connect(pBatteryLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	m_pAllCheckBoxList.append(pBatteryBox);
	m_pAllLineEditList.append(pBatteryLineEdit);
	
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(pBinaryGroupBox);
	pMainLayout->addWidget(pAccuracyGroupBox);
	pMainLayout->addWidget(pFreqGroupBox);
	pMainLayout->addWidget(pHarmGroupBox);
	pMainLayout->addWidget(pAnalogGroupBox);
	pMainLayout->addWidget(pBatteryGroupBox);
	//pMainLayout->setContentsMargins(0, 0, 0, 0);
	
	//setLayout(pMainLayout);
	setFocusPolicy(Qt::StrongFocus);
	connect(m_pParasSetBtn, SIGNAL(clicked()), this, SLOT(slot_ParasSetPushButton_Clicked()));	

	for (int i = 0; i < m_pAllGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pAllGroupBoxList.at(i);
		connect(pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	}


#ifndef  _PSX_QT_LINUX_
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	HDC hd = GetDC(NULL);
	double dDotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
	double dUIShowCoef = dDotPix1 / 96;

	bool shouldUseScrollArea = false;
	if (rect.width() >= 1920) 
	{
// 		double dCoef = 1;
// 		if (abs(dUIShowCoef - 1.5) < 0.000001) //����150%
// 		{
// 			dCoef = 0.7;
// 		} 
// 		else if (abs(dUIShowCoef - 1.25) < 0.000001 ) //����125%
// 		{
// 			dCoef = 0.8;
// 		}

//		for (int i = 0; i < pMainLayout->count(); ++i)
//		{
//			QWidget* widget = pMainLayout->itemAt(i)->widget();
//			if (widget)
		{
// 				QFont font = widget->font();
// 				font.setPointSize(font.pointSize() * dCoef); // �������С��С
// 				widget->setFont(font);

// 				QSize size = widget->size();
//  				size.setWidth(size.width() * dCoef); // ��С���
//  				size.setHeight(size.height() * dCoef); // ��С�߶�
//  				widget->resize(size);
		}
 	//	}

		if (abs(dUIShowCoef - 1.0) > 0.000001)// ���Ŵ���100%
		{
			 shouldUseScrollArea = true;
		}
	}
	if (shouldUseScrollArea)
			{
		QWidget* pMainWidget = new QWidget();
		pMainWidget->setLayout(pMainLayout);
		QScrollArea* pScrollArea = new QScrollArea();
		pScrollArea->setWidget(pMainWidget);
		pScrollArea->setWidgetResizable(true);
		QVBoxLayout* pScrollLayout = new QVBoxLayout();
		pScrollLayout->addWidget(pScrollArea);
		pScrollLayout->setContentsMargins(0, 0, 0, 0);
		setLayout(pScrollLayout);
			}
	else
	{
		setLayout(pMainLayout);
		}
#endif
}


void QSttMacroParaEditViewAdmuAccurAutoTest::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_pADMUAutoTestDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewAdmuAccurAutoTest::SetDatas(CDataGroup *pParas)
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(pParas,pCheckBox,pCheckBox->objectName());
		}
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(pParas,pLineEdit,pLineEdit->objectName());
		}
	}

	for (int i = 0; i < m_pAllGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pAllGroupBoxList.at(i);
		if (pGroupBox)
		{
			GetGroupBoxCheckable(pParas,pGroupBox,pGroupBox->objectName());
		}
	}
}


BOOL QSttMacroParaEditViewAdmuAccurAutoTest::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup* pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if (pDataGroup->GetCount() <= 0)
	{
		return FALSE;
	}

	pDataGroup->CopyChildren(&m_pADMUAutoTestDataGroup);
	return TRUE;
}

void QSttMacroParaEditViewAdmuAccurAutoTest::OnViewTestStart()
{
	SaveADMUAutoTestParasXml();

	m_pParasSetBtn->setEnabled(false);
// 	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
// 	{
// 		QCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
// 		pCheckBox->setEnabled(false);
// 	}
	for (int i = 0; i < m_pAllGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pAllGroupBoxList.at(i);
		pGroupBox->setEnabled(false);
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		//pLineEdit->setEnabled(false);

		if (pLineEdit->objectName() == _T("Bout_Count"))
		{
			CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();
			if (pXSttCap_61850 == NULL)
			{
				return;
			}
			if (pXSttCap_61850->m_pDataset_StateValueChangedRlt == NULL)
			{
				return;
			}

			CDvmDataset *pDvmDataset = pXSttCap_61850->m_pDataset_StateValueChangedRlt;
			CDvmData *pDvmData = (CDvmData*)pDvmDataset->FindByID(_T("BoutValueChangedCount"));
			if (pDvmData)
			{
				pDvmData->m_strValue.Format(_T("%f"),pLineEdit->text().toFloat());
			}
		}
	}
}

void QSttMacroParaEditViewAdmuAccurAutoTest::OnViewTestStop()
{
	m_pParasSetBtn->setEnabled(true);
// 	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
// 	{
// 		QCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
// 		pCheckBox->setEnabled(true);
// 	}
// 	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
// 	{
// 		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
// 		pLineEdit->setEnabled(true);
// 	}

	for (int i = 0; i < m_pAllGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pAllGroupBoxList.at(i);
		pGroupBox->setEnabled(true);
	}

}

void QSttMacroParaEditViewAdmuAccurAutoTest::slot_ParasSetPushButton_Clicked()
{
	QAdmuAccurAutoTestParasSetDialog pParasSetDialog(this);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&pParasSetDialog);
	pParasSetDialog.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	pParasSetDialog.exec();
#endif
}


void QSttMacroParaEditViewAdmuAccurAutoTest::GetCheckBoxValue( CDataGroup *pParas,QCheckBox * pCheckBox,CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pADMUAutoTestDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pCheckBox->setChecked(true);
	}
	else
	{
		pCheckBox->setChecked(false);
	}
}

void QSttMacroParaEditViewAdmuAccurAutoTest::GetLineEditValue(CDataGroup *pParas, QLineEdit * pLineEdit,CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pADMUAutoTestDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',0));
}

void QSttMacroParaEditViewAdmuAccurAutoTest::GetGroupBoxCheckable( CDataGroup *pParas,QGroupBox * pGroupBox,CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(true);
	}
	else
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(false);
	}
}

void QSttMacroParaEditViewAdmuAccurAutoTest::slot_CheckBoxStateChanged(int)
{
	CString strID;
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender()); 
	if (pCheckBox)
	{	
		strID = pCheckBox->objectName();
		if (pCheckBox->isChecked()) 
		{
			m_pADMUAutoTestDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pADMUAutoTestDataGroup.SetDataValue(strID,(long)0);
		}
	}
}


void QSttMacroParaEditViewAdmuAccurAutoTest::slot_GroupBoxtoggled( bool )
{
	CString strID;
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender()); 
	if (pGroupBox)
	{	
		strID = pGroupBox->objectName();
		if (pGroupBox->isChecked()) 
		{
			m_pADMUAutoTestDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pADMUAutoTestDataGroup.SetDataValue(strID,(long)0);
		}
	}
}

void QSttMacroParaEditViewAdmuAccurAutoTest::slot_LineEditFinished()
{
	CString strID;
	float fValue ,fMinValue,fMaxValue;

	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		if (strID.Find(_T("Un_Custom")) >= 0)
		{			
			fMinValue = 1;
			fMaxValue = 300;
		}
		else if (strID.Find(_T("In_Custom")) >= 0)
		{
			fMinValue = 1;
			fMaxValue = 3000;
		}
		else if (strID == _T("Ang"))
		{
			fMinValue = 0;
			fMaxValue = 360;
		}
		else if (strID.Find(_T("F_Custom")) >= 0 )
		{
			fMinValue = 45;
			fMaxValue = 55;
		}
		else if (strID.Find(_T("Harm_Content")) >= 0)
		{
			fMinValue = 0;
			fMaxValue = 100;
		}
		else if (strID == _T("CPS_Time"))
		{
			fMinValue = 1;
			fMaxValue = 100;
		}
		else if (strID == _T("Bout_Count"))
		{
			fMinValue = 1;
			fMaxValue = 20;
		}
		
		fValue = pLineEdit->text().toFloat();
		if (fValue > fMaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ%fС�����ֵ%f"), fValue,fMaxValue);
		}
		if (fValue < fMinValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ%f������Сֵ%f"), fValue,fMinValue);
		}

		fValue = setLimit(fMinValue,fMaxValue,fValue);

		if (strID == _T("Bout_Count"))
		{
			if (static_cast<int>(fValue) % 2 != 0)
			{
				fValue = fValue -1.0f ;
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ֻ֧�ֱ�λż����."));
			}
			pLineEdit->setText(QString::number(fValue,'f',0));
			m_pADMUAutoTestDataGroup.SetDataValue(strID,fValue);
			return;
		}
		pLineEdit->setText(QString::number(fValue,'f',0));
		m_pADMUAutoTestDataGroup.SetDataValue(strID,fValue);
	}
}

void QSttMacroParaEditViewAdmuAccurAutoTest::SaveADMUAutoTestParasXml()
{
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Fnom"),g_oSystemParas.m_fFNom);
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/ADMUAccurAuto_Paras.xml");
	m_pADMUAutoTestDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewAdmuAccurAutoTest::slot_FirstHarmTimeseditFinished()
{
	int nFirstHarmTimes  = m_pFirstHarmTimesLineEdit->text().toInt();
	int nLastHarmTimes = m_pLastHarmTimesLineEdit->text().toInt();

	if(nFirstHarmTimes >= nLastHarmTimes)
	{
		nFirstHarmTimes = nLastHarmTimes -1;
		if (nFirstHarmTimes < 2)
		{
			nFirstHarmTimes = 2;
		}
	}
	else if (nFirstHarmTimes < 2)
	{
		nFirstHarmTimes = 2;
	}

 	m_pFirstHarmTimesLineEdit->setText(QString::number(nFirstHarmTimes));
 	m_pADMUAutoTestDataGroup.SetDataValue(_T("First_Harm_Times"),(long)nFirstHarmTimes);
}

void QSttMacroParaEditViewAdmuAccurAutoTest::slot_LastHarmTimeseditFinished()
{
	int nFirstHarmTimes  = m_pFirstHarmTimesLineEdit->text().toInt();
	int nLastHarmTimes = m_pLastHarmTimesLineEdit->text().toInt();

	if(nLastHarmTimes <= nFirstHarmTimes)
	{
		nLastHarmTimes = nFirstHarmTimes + 1;
		if (nLastHarmTimes > 25) 
		{
			nLastHarmTimes = 25;
		}
	}
	else if (nLastHarmTimes > 25)
	{
		nLastHarmTimes = 25;
	}

 	m_pLastHarmTimesLineEdit->setText(QString::number(nLastHarmTimes));
	m_pADMUAutoTestDataGroup.SetDataValue(_T("Last_Harm_Times"),(long)nLastHarmTimes);
}

CString QSttMacroParaEditViewAdmuAccurAutoTest::ProcessString( CString &str )
{
	CString strProcessed = str;
	int index = strProcessed.indexOf('%');
	if (index != -1)
	{
		strProcessed = strProcessed.left(index); 
	}
	if (strProcessed.length() < 3)
	{
		int numZeros = 3 - strProcessed.length();
		strProcessed = QString(numZeros, '0') + strProcessed; // ��ǰ�油��0
	}
	return strProcessed;
}

BOOL QSttMacroParaEditViewAdmuAccurAutoTest::SetValues_dsRcdStep6U6I( CDvmDataset *pDsRcdStep6U6I )
{
	if (pDsRcdStep6U6I == NULL)
	{
		return FALSE;
	}

	CDvmData *pUnData = (CDvmData*)pDsRcdStep6U6I->FindByID(_T("VNom"));
	CDvmData *pInData = (CDvmData*)pDsRcdStep6U6I->FindByID(_T("INom"));
	CDvmData *pU0Data = (CDvmData*)pDsRcdStep6U6I->FindByID(_T("U0"));
	CDvmData *pI0Data = (CDvmData*)pDsRcdStep6U6I->FindByID(_T("I0"));
	
	if((pUnData == NULL)||(pInData == NULL)||(pU0Data == NULL)||(pI0Data == NULL))
		return FALSE;

	pUnData->m_strValue.Format(_T("%f"),g_oSystemParas.m_fVNom);
	pInData->m_strValue.Format(_T("%f"),g_oSystemParas.m_fINom);
	pU0Data->m_strValue.Format(_T("%f"),g_oSystemParas.m_fU0_Std);
	pI0Data->m_strValue.Format(_T("%f"),g_oSystemParas.m_fI0_Std);

	return TRUE;
}










