#include "QRecloseCommonParasDlg.h"

#include "../../Module/SttGlobalDef.h"
#include "../../UI/SttTestCntrFrameBase.h"

QRecloseCommonParasDlg::QRecloseCommonParasDlg(CDataGroup *m_oRecloseAccDataGroup,QWidget *parent) : QDialog(parent)
{
	m_pRecloseCommonParasDataGroup = m_oRecloseAccDataGroup;
	InitUI();
	InitFont();
	InitConnections();
}

QRecloseCommonParasDlg::~QRecloseCommonParasDlg()
{

}

void QRecloseCommonParasDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_pCommonParasTabWidget = new QTabWidget(this);
	m_pGeneralParasWidget = new QWidget(this);
	m_pBinWidget = new QWidget(this);
	m_pBoutWidget = new QWidget(this);

	m_pCommonParasTabWidget->addTab(m_pGeneralParasWidget, _T("通用参数"));

	m_pLabFaultTrigMode = new QLabel(_T("故障触发方式"),this);                //故障触发方式
	m_pLabPTPos = new QLabel(_T("TV安装位置"),this);			              //TV安装位置
	m_pLabCTPos = new QLabel(_T("TA正极性"),this);                            //TA正极性
	m_pLabCurLoad = new QLabel(_T("负荷电流"),this);						  //负荷电流
	m_pLabPowerAngleLoad = new QLabel(_T("负荷角度"),this);					  //负荷角度
	m_pLabSimulateBreakerDelay = new QLabel(_T("断路器模拟"),this);			  //断路器模拟
	m_pLabBrkBreakTime = new QLabel(_T("分闸时间(ms)"),this);			      //分闸时间(ms)
	m_pLabBrkCloseTime = new QLabel(_T("合闸时间(ms)"),this);				  //合闸时间(ms)

	m_pCmbFaultTrigMode = new QComboBox(this);    //故障触发方式
	m_pCmbFaultTrigMode->addItem("时间触发");
	m_pCmbFaultTrigMode->addItem("手动触发");
	m_pCmbFaultTrigMode->addItem("开入量触发");

	m_pCmbPTPos = new QComboBox(this);			  //TV安装位置
	m_pCmbPTPos->addItem("母线侧");
	m_pCmbPTPos->addItem("线路侧");

	m_pCmbCTPos = new QComboBox(this);	          //TA正极性
	m_pCmbCTPos->addItem("指向母线");
	m_pCmbCTPos->addItem("指向线路");

	m_pCmbSimulateBreakerDelay = new QComboBox(this);//断路器模拟
	m_pCmbSimulateBreakerDelay->addItem("不模拟");
	m_pCmbSimulateBreakerDelay->addItem("模拟");
	m_pEditBrkBreakTime = new QLineEdit(this);    //分闸时间(ms)
	m_pEditBrkCloseTime = new QLineEdit(this);    //合闸时间(ms)
	m_pEditCurLoad = new QLineEdit(this); 		
	m_pEditPowerAngleLoad = new QLineEdit(this);  

	m_pGeneralParasLayout = new QGridLayout();
	m_pGeneralParasLayout->setVerticalSpacing(25);   // 设置垂直间距为10像素
	m_pGeneralParasLayout->setHorizontalSpacing(15); // 设置水平间距为15像素
	m_pGeneralParasLayout->addWidget(m_pLabFaultTrigMode, 0, 0);
	m_pGeneralParasLayout->addWidget(m_pLabPTPos, 1, 0);
	m_pGeneralParasLayout->addWidget(m_pLabCTPos, 2, 0);
	m_pGeneralParasLayout->addWidget(m_pLabCurLoad,3, 0);
	m_pGeneralParasLayout->addWidget(m_pLabPowerAngleLoad, 4, 0);
	m_pGeneralParasLayout->addWidget(m_pLabSimulateBreakerDelay, 5, 0);
	m_pGeneralParasLayout->addWidget(m_pLabBrkBreakTime, 6, 0);
	m_pGeneralParasLayout->addWidget(m_pLabBrkCloseTime, 7, 0);

	m_pGeneralParasLayout->addWidget(m_pCmbFaultTrigMode, 0, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbPTPos, 1, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbCTPos, 2, 1);
	m_pGeneralParasLayout->addWidget(m_pEditCurLoad, 3, 1);
	m_pGeneralParasLayout->addWidget(m_pEditPowerAngleLoad, 4, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbSimulateBreakerDelay, 5, 1);
	m_pGeneralParasLayout->addWidget(m_pEditBrkBreakTime, 6, 1);
	m_pGeneralParasLayout->addWidget(m_pEditBrkCloseTime, 7, 1);


	m_pCmbFaultTrigMode->setFixedWidth(150);
	m_pCmbFaultTrigMode->setFixedWidth(150);       //故障触发方式
	m_pCmbPTPos->setFixedWidth(150);			   //TV安装位置
	m_pCmbCTPos->setFixedWidth(150);               //TA正极性
	m_pEditCurLoad->setFixedWidth(150);			  //负荷电流
	m_pEditPowerAngleLoad->setFixedWidth(150);	  //负荷角度
	m_pCmbSimulateBreakerDelay->setFixedWidth(150);//断路器模拟
	m_pEditBrkBreakTime->setFixedWidth(150);    //分闸时间（s）
	m_pEditBrkCloseTime->setFixedWidth(150);    //合闸时间（s）

	m_pBtnOKCommonParas = new QPushButton(_T("确定"));
	m_pBtnCancelCommonParas = new QPushButton(_T("取消"));
	m_pBtnOKCommonParas->setFixedWidth(100);
	m_pBtnCancelCommonParas->setFixedWidth(100);
	m_pCommonParasLayout = new QHBoxLayout;
	m_pSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_pSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_pCommonParasLayout->addItem(m_pSpacerLeft);
	m_pCommonParasLayout->addWidget(m_pBtnOKCommonParas);
	m_pCommonParasLayout->addWidget(m_pBtnCancelCommonParas);
	m_pCommonParasLayout->addItem(m_pSpacerRight);

	m_pMainCommonParasLayout = new QVBoxLayout;
	m_pMainCommonParasLayout->addLayout(m_pGeneralParasLayout);
	m_pMainCommonParasLayout->addLayout(m_pCommonParasLayout);
	m_pGeneralParasWidget->setLayout(m_pMainCommonParasLayout);

	m_pCommonParasTabWidget->addTab(m_pBinWidget, _T("开入量"));
	m_pBinLayout = new QGridLayout();
	QStringList BinList;
	BinList  << "单跳" << "三跳" << "重合";
	QStringList BoutList;
	BoutList  << "断开" << "闭合";
	m_pLabBinSelect= new QLabel(_T("开入选择"),this);            //开入量选择
	m_pLabBinA= new QLabel(_T("开入A"),this);                      //开入A
	m_pLabBinB= new QLabel(_T("开入B"),this);                      //开入B
	m_pLabBinC= new QLabel(_T("开入C"),this);                      //开入C
	m_pLabBinD= new QLabel(_T("开入D"),this);                      //开入D
	m_pLabBinE= new QLabel(_T("开入E"),this);                      //开入E
	m_pLabBinF= new QLabel(_T("开入F"),this);                      //开入F
	m_pLabBinG= new QLabel(_T("开入G"),this);                      //开入G
	m_pLabBinH= new QLabel(_T("开入H"),this);                      //开入H

	m_pCmbBinSelect = new QComboBox(this);           //开入量选择
	m_pCmbBinSelect->addItem("开入A-B-C-D");
	m_pCmbBinSelect->addItem("开入E-F-G-H");
	m_pCmbBinA = new QComboBox(this);                //开入A
	m_pCmbBinB = new QComboBox(this);                //开入B
	m_pCmbBinC = new QComboBox(this);                //开入C
	m_pCmbBinD = new QComboBox(this);                //开入D
	m_pCmbBinE = new QComboBox(this);                //开入E
	m_pCmbBinF = new QComboBox(this);                //开入F
	m_pCmbBinG = new QComboBox(this);                //开入G
	m_pCmbBinH = new QComboBox(this);                //开入H
	m_pCmbBinA->addItems(BinList);
	m_pCmbBinB->addItems(BinList);
	m_pCmbBinC->addItems(BinList);
	m_pCmbBinD->addItems(BinList);
	m_pCmbBinE->addItems(BinList);
	m_pCmbBinF->addItems(BinList);
	m_pCmbBinG->addItems(BinList);
	m_pCmbBinH->addItems(BinList);

	m_pCmbBinSelect->setFixedWidth(150);
	m_pBinLayout->addWidget(m_pLabBinSelect, 0, 0);
	m_pBinLayout->addWidget(m_pLabBinA, 1, 0);
	m_pBinLayout->addWidget(m_pLabBinB, 2, 0);
	m_pBinLayout->addWidget(m_pLabBinC, 3, 0);
	m_pBinLayout->addWidget(m_pLabBinD, 4, 0);
	m_pBinLayout->addWidget(m_pLabBinE, 5, 0);
	m_pBinLayout->addWidget(m_pLabBinF, 6, 0);
	m_pBinLayout->addWidget(m_pLabBinG, 7, 0);
	m_pBinLayout->addWidget(m_pLabBinH, 8, 0);

	m_pBinLayout->addWidget(m_pCmbBinSelect, 0, 1);
	m_pBinLayout->addWidget(m_pCmbBinA, 1, 1);
	m_pBinLayout->addWidget(m_pCmbBinB, 2, 1);
	m_pBinLayout->addWidget(m_pCmbBinC, 3, 1);
	m_pBinLayout->addWidget(m_pCmbBinD, 4, 1);
	m_pBinLayout->addWidget(m_pCmbBinE, 5, 1);
	m_pBinLayout->addWidget(m_pCmbBinF, 6, 1);
	m_pBinLayout->addWidget(m_pCmbBinG, 7, 1);
	m_pBinLayout->addWidget(m_pCmbBinH, 8, 1);

	m_pBtnOKBin = new QPushButton(_T("确定"));
	m_pBtnCancelBin = new QPushButton(_T("取消"));
	m_pBtnOKBin->setFixedWidth(100);
	m_pBtnCancelBin->setFixedWidth(100);
	m_pBinbtnLayout = new QHBoxLayout;
	m_pSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_pSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_pBinbtnLayout->addItem(m_pSpacerLeft);
	m_pBinbtnLayout->addWidget(m_pBtnOKBin);
	m_pBinbtnLayout->addWidget(m_pBtnCancelBin);
	m_pBinbtnLayout->addItem(m_pSpacerRight);

	m_pMainBinLayout = new QVBoxLayout;
	m_pMainBinLayout->addLayout(m_pBinLayout);
	m_pMainBinLayout->addLayout(m_pBinbtnLayout);

	m_pBinWidget->setLayout(m_pMainBinLayout);

	m_pCommonParasTabWidget->addTab(m_pBoutWidget, _T("开出量"));
	m_pBoutLayout = new QGridLayout();
	m_pLabBout1 = new QLabel(_T("开出1"),this);               //开出1
	m_pLabBout2 = new QLabel(_T("开出2"),this);               //开出2
	m_pLabBout3 = new QLabel(_T("开出3"),this);               //开出3
	m_pLabBout4 = new QLabel(_T("开出4"),this);               //开出4
	m_pLabBout5 = new QLabel(_T("开出5"),this);               //开出5
	m_pLabBout6 = new QLabel(_T("开出6"),this);               //开出6
	m_pLabBout7 = new QLabel(_T("开出7"),this);               //开出7
	m_pLabBout8 = new QLabel(_T("开出8"),this);               //开出8
	m_pLabOutputSwitchMode= new QLabel(_T("开出翻转启动方式"),this);//开出翻转启动方式
	m_pLabOutputKeepTime= new QLabel(_T("开出保持时间"),this);      //开出保持时间
	m_pLabOutputDelayTime= new QLabel(_T("开出翻转时刻"),this);     //开出翻转时刻

	m_pCmbBout1 = new QComboBox(this);               //开出A
	m_pCmbBout2 = new QComboBox(this);               //开出B
	m_pCmbBout3 = new QComboBox(this);               //开出C
	m_pCmbBout4 = new QComboBox(this);               //开出D
	m_pCmbBout5 = new QComboBox(this);               //开出E
	m_pCmbBout6 = new QComboBox(this);               //开出F
	m_pCmbBout7 = new QComboBox(this);               //开出G
	m_pCmbBout8 = new QComboBox(this);               //开出H
	m_pCmbBout1->addItems(BoutList);
	m_pCmbBout2->addItems(BoutList);
	m_pCmbBout3->addItems(BoutList);
	m_pCmbBout4->addItems(BoutList);
	m_pCmbBout5->addItems(BoutList);
	m_pCmbBout6->addItems(BoutList);
	m_pCmbBout7->addItems(BoutList);
	m_pCmbBout8->addItems(BoutList);

	m_pCmbOutputSwitchMode = new QComboBox(this);    //开出翻转启动方式
	m_pCmbOutputSwitchMode->addItem("时间启动");
	m_pCmbOutputSwitchMode->addItem("开入量启动");
	m_pEditOutputKeepTime = new QLineEdit(this);     //开出保持时间
	m_pEditOutputDelayTime = new QLineEdit(this);    //开出翻转时刻

	m_pBoutLayout->addWidget(m_pLabBout1, 0, 0);
	m_pBoutLayout->addWidget(m_pLabBout2, 1, 0);
	m_pBoutLayout->addWidget(m_pLabBout3, 2, 0);
	m_pBoutLayout->addWidget(m_pLabBout4, 3, 0);
	m_pBoutLayout->addWidget(m_pLabBout5, 4, 0);
	m_pBoutLayout->addWidget(m_pLabBout6, 5, 0);
	m_pBoutLayout->addWidget(m_pLabBout7, 6, 0);
	m_pBoutLayout->addWidget(m_pLabBout8, 7, 0);
	m_pBoutLayout->addWidget(m_pLabOutputSwitchMode, 8, 0);
	m_pBoutLayout->addWidget(m_pLabOutputKeepTime, 9, 0);
	m_pBoutLayout->addWidget(m_pLabOutputDelayTime, 10, 0);

	m_pBoutLayout->addWidget(m_pCmbBout1, 0, 1);
	m_pBoutLayout->addWidget(m_pCmbBout2, 1, 1);
	m_pBoutLayout->addWidget(m_pCmbBout3, 2, 1);
	m_pBoutLayout->addWidget(m_pCmbBout4, 3, 1);
	m_pBoutLayout->addWidget(m_pCmbBout5, 4, 1);
	m_pBoutLayout->addWidget(m_pCmbBout6, 5, 1);
	m_pBoutLayout->addWidget(m_pCmbBout7, 6, 1);
	m_pBoutLayout->addWidget(m_pCmbBout8, 7, 1);
	m_pBoutLayout->addWidget(m_pCmbOutputSwitchMode, 8, 1);
	m_pBoutLayout->addWidget(m_pEditOutputKeepTime, 9, 1);
	m_pBoutLayout->addWidget(m_pEditOutputDelayTime, 10, 1);

	m_pBtnOKBout = new QPushButton(_T("确定"));
	m_pBtnCancelBout = new QPushButton(_T("取消"));
	m_pBtnOKBout->setFixedWidth(100);
	m_pBtnCancelBout->setFixedWidth(100);
	m_pBoutbtnLayout = new QHBoxLayout;
	m_pSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_pSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_pBoutbtnLayout->addItem(m_pSpacerLeft);
	m_pBoutbtnLayout->addWidget(m_pBtnOKBout);
	m_pBoutbtnLayout->addWidget(m_pBtnCancelBout);
	m_pBoutbtnLayout->addItem(m_pSpacerRight);

	m_pMainBoutLayout = new QVBoxLayout;
	m_pMainBoutLayout->addLayout(m_pBoutLayout);
	m_pMainBoutLayout->addLayout(m_pBoutbtnLayout);
	m_pBoutWidget->setLayout(m_pMainBoutLayout);

	m_pCommonParasTabWidget->setFixedSize(350, 500); // 设置固定大小

	m_pCmbBinA->setEnabled(true);                
	m_pCmbBinB->setEnabled(true);                
	m_pCmbBinC->setEnabled(true);               
	m_pCmbBinD->setEnabled(true);               
	m_pCmbBinE->setEnabled(false);               
	m_pCmbBinF->setEnabled(false);                
	m_pCmbBinG->setEnabled(false);               
	m_pCmbBinH->setEnabled(false);  
	m_pEditBrkBreakTime->setEnabled(false);
	m_pEditBrkCloseTime->setEnabled(false);

	Initdates();
}

void QRecloseCommonParasDlg::InitFont()
{
	m_pCommonParasTabWidget->setFont(*g_pSttGlobalFont); 
	m_pGeneralParasWidget->setFont(*g_pSttGlobalFont); 
	m_pBinWidget->setFont(*g_pSttGlobalFont); 
	m_pBoutWidget->setFont(*g_pSttGlobalFont); 
	m_pLabFaultTrigMode->setFont(*g_pSttGlobalFont);       //故障触发方式
	m_pLabPTPos->setFont(*g_pSttGlobalFont);			   //TV安装位置
	m_pLabCTPos->setFont(*g_pSttGlobalFont);               //TA正极性
	m_pLabCurLoad->setFont(*g_pSttGlobalFont);  				   //负荷电流
	m_pLabPowerAngleLoad->setFont(*g_pSttGlobalFont);  		   //负荷角度
	m_pLabSimulateBreakerDelay->setFont(*g_pSttGlobalFont);//断路器模拟
	m_pLabBrkBreakTime->setFont(*g_pSttGlobalFont);        //分闸时间（s）
	m_pLabBrkCloseTime->setFont(*g_pSttGlobalFont);        //合闸时间（s）


	m_pLabBinSelect->setFont(*g_pSttGlobalFont);           //开入量选择
	m_pLabBinA->setFont(*g_pSttGlobalFont);                //开入A
	m_pLabBinB->setFont(*g_pSttGlobalFont);                //开入B
	m_pLabBinC->setFont(*g_pSttGlobalFont);                //开入C
	m_pLabBinD->setFont(*g_pSttGlobalFont);                //开入D
	m_pLabBinE->setFont(*g_pSttGlobalFont);                //开入E
	m_pLabBinF->setFont(*g_pSttGlobalFont);                //开入F
	m_pLabBinG->setFont(*g_pSttGlobalFont);                //开入G
	m_pLabBinH->setFont(*g_pSttGlobalFont);                //开入H

	m_pLabBout1->setFont(*g_pSttGlobalFont);               //开出1
	m_pLabBout2->setFont(*g_pSttGlobalFont);               //开出2
	m_pLabBout3->setFont(*g_pSttGlobalFont);               //开出3
	m_pLabBout4->setFont(*g_pSttGlobalFont);               //开出4
	m_pLabBout5->setFont(*g_pSttGlobalFont);               //开出5
	m_pLabBout6->setFont(*g_pSttGlobalFont);               //开出6
	m_pLabBout7->setFont(*g_pSttGlobalFont);               //开出7
	m_pLabBout8->setFont(*g_pSttGlobalFont);               //开出8
	m_pLabOutputSwitchMode->setFont(*g_pSttGlobalFont);    //开出翻转启动方式
	m_pLabOutputKeepTime->setFont(*g_pSttGlobalFont);      //开出保持时间
	m_pLabOutputDelayTime->setFont(*g_pSttGlobalFont);     //开出翻转时刻


	m_pEditBrkBreakTime->setFont(*g_pSttGlobalFont);    //分闸时间（s）
	m_pEditBrkCloseTime->setFont(*g_pSttGlobalFont);    //合闸时间（s）
	m_pEditPowerAngleLoad->setFont(*g_pSttGlobalFont);
	m_pEditCurLoad->setFont(*g_pSttGlobalFont);
	m_pEditOutputKeepTime->setFont(*g_pSttGlobalFont);  //开出保持时间
	m_pEditOutputDelayTime->setFont(*g_pSttGlobalFont); //开出翻转时刻
	m_pCmbFaultTrigMode->setFont(*g_pSttGlobalFont);       //故障触发方式
	m_pCmbPTPos->setFont(*g_pSttGlobalFont);			   //TV安装位置
	m_pCmbCTPos->setFont(*g_pSttGlobalFont);               //TA正极性
	m_pCmbSimulateBreakerDelay->setFont(*g_pSttGlobalFont);//断路器模拟

	m_pCmbBinSelect->setFont(*g_pSttGlobalFont);           //开入量选择
	m_pCmbBinA->setFont(*g_pSttGlobalFont);                //开入A
	m_pCmbBinB->setFont(*g_pSttGlobalFont);                //开入B
	m_pCmbBinC->setFont(*g_pSttGlobalFont);                //开入C
	m_pCmbBinD->setFont(*g_pSttGlobalFont);                //开入D
	m_pCmbBinE->setFont(*g_pSttGlobalFont);                //开入E
	m_pCmbBinF->setFont(*g_pSttGlobalFont);                //开入F
	m_pCmbBinG->setFont(*g_pSttGlobalFont);                //开入G
	m_pCmbBinH->setFont(*g_pSttGlobalFont);                //开入H
	m_pCmbBout1->setFont(*g_pSttGlobalFont);               //开出1
	m_pCmbBout2->setFont(*g_pSttGlobalFont);               //开出2
	m_pCmbBout3->setFont(*g_pSttGlobalFont);               //开出3
	m_pCmbBout4->setFont(*g_pSttGlobalFont);               //开出4
	m_pCmbBout5->setFont(*g_pSttGlobalFont);               //开出5
	m_pCmbBout6->setFont(*g_pSttGlobalFont);               //开出6
	m_pCmbBout7->setFont(*g_pSttGlobalFont);               //开出7
	m_pCmbBout8->setFont(*g_pSttGlobalFont);               //开出8
	m_pCmbOutputSwitchMode->setFont(*g_pSttGlobalFont);    //开出翻转启动方式

	m_pBtnOKCommonParas->setFont(*g_pSttGlobalFont);
	m_pBtnCancelCommonParas->setFont(*g_pSttGlobalFont);
	m_pBtnOKBin->setFont(*g_pSttGlobalFont);
	m_pBtnCancelBin->setFont(*g_pSttGlobalFont);
	m_pBtnOKBout->setFont(*g_pSttGlobalFont);
	m_pBtnCancelBout->setFont(*g_pSttGlobalFont);
}

void QRecloseCommonParasDlg::Initdates()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("FaultTrigMode");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbFaultTrigMode->setCurrentIndex(nValue);

	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("PTPos");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbPTPos->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("CTPos");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbCTPos->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("ILoad");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pEditCurLoad->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("ILoadPh");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pEditPowerAngleLoad->setText(QString::number(fValue, 'f', 1));
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("SimulateBreakerDelay");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbSimulateBreakerDelay->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BrkBreakTime");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pEditBrkBreakTime->setText(QString::number(nValue));
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BrkCloseTime");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pEditBrkCloseTime->setText(QString::number(nValue));
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BinSelect");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinSelect->setCurrentIndex(nValue);
		if (nValue == 0)
		{
			m_pCmbBinA->setEnabled(true);
			m_pCmbBinB->setEnabled(true);
			m_pCmbBinC->setEnabled(true);
			m_pCmbBinD->setEnabled(true);
			m_pCmbBinE->setEnabled(false);
			m_pCmbBinF->setEnabled(false);
			m_pCmbBinG->setEnabled(false);
			m_pCmbBinH->setEnabled(false);
		}
		if (nValue == 1)
		{
			m_pCmbBinA->setEnabled(false);
			m_pCmbBinB->setEnabled(false);
			m_pCmbBinC->setEnabled(false);
			m_pCmbBinD->setEnabled(false);
			m_pCmbBinE->setEnabled(true);
			m_pCmbBinF->setEnabled(true);
			m_pCmbBinG->setEnabled(true);
			m_pCmbBinH->setEnabled(true);
		}
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("A");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinA->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("B");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinB->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("C");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinC->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("R");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinD->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("E");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinE->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("F");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinF->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("G");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinG->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("H");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBinH->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B01");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout1->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B02");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout2->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B03");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout3->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B04");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout4->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B05");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout5->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B06");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout6->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B07");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout7->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B08");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbBout8->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_OutputSwitchMode");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbOutputSwitchMode->setCurrentIndex(nValue);
		if (nValue == 0)
		{
			m_pEditOutputDelayTime->setEnabled(true);
		}
		if (nValue == 1)
		{
			m_pEditOutputDelayTime->setEnabled(false);
		}
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_OutputKeepTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pEditOutputKeepTime->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_OutputDelayTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pEditOutputDelayTime->setText(QString::number(fValue, 'f', 3));
	}

	long nSimulate = m_pCmbSimulateBreakerDelay->currentIndex();
	if (nSimulate == 0)
	{
		m_pEditBrkBreakTime->setEnabled(false);
		m_pEditBrkCloseTime->setEnabled(false);
	}
	if (nSimulate == 1)
	{
		m_pEditBrkBreakTime->setEnabled(true);
		m_pEditBrkCloseTime->setEnabled(true);
	}

	long nOutput = m_pCmbOutputSwitchMode->currentIndex();
	if (nOutput == 0)
	{
		m_pLabOutputDelayTime->setEnabled(true);
	}
	if (nOutput == 1)
	{
		m_pLabOutputDelayTime->setEnabled(false);
	}
}


void QRecloseCommonParasDlg::InitConnections()
{
	connect(m_pCmbBinSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_BinSelect(int)));
	connect(m_pCmbOutputSwitchMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_OutputSwitchMode(int)));
	connect(m_pCmbSimulateBreakerDelay,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_SimulateBreakerDelay(int)));

	connect(m_pEditCurLoad,SIGNAL(editingFinished()),this,SLOT(slot_CurLoad()));
	connect(m_pEditPowerAngleLoad,SIGNAL(editingFinished()),this,SLOT(slot_PowerAngleLoad()));
	connect(m_pEditBrkBreakTime,SIGNAL(editingFinished()),this,SLOT(slot_BrkBreakTime()));
	connect(m_pEditBrkCloseTime,SIGNAL(editingFinished()),this,SLOT(slot_BrkCloseTime()));
	connect(m_pEditOutputKeepTime,SIGNAL(editingFinished()),this,SLOT(slot_OutputKeepTime()));
	connect(m_pEditOutputDelayTime,SIGNAL(editingFinished()),this,SLOT(slot_OutputDelayTime()));

	connect(m_pBtnOKCommonParas,SIGNAL(clicked()),this,SLOT(slot_OKCommonParas()));
	connect(m_pBtnCancelCommonParas,SIGNAL(clicked()),this,SLOT(slot_CancelCommonParas()));
	connect(m_pBtnOKBin,SIGNAL(clicked()),this,SLOT(slot_OKCommonParas()));
	connect(m_pBtnCancelBin,SIGNAL(clicked()),this,SLOT(slot_CancelCommonParas()));
	connect(m_pBtnOKBout,SIGNAL(clicked()),this,SLOT(slot_OKCommonParas()));
	connect(m_pBtnCancelBout,SIGNAL(clicked()),this,SLOT(slot_CancelCommonParas()));
}

void QRecloseCommonParasDlg::slot_BinSelect(int nIndex)
{
	if (nIndex == 0)
	{
		m_pCmbBinA->setEnabled(true);                
		m_pCmbBinB->setEnabled(true);                
		m_pCmbBinC->setEnabled(true);               
		m_pCmbBinD->setEnabled(true);               
		m_pCmbBinE->setEnabled(false);               
		m_pCmbBinF->setEnabled(false);                
		m_pCmbBinG->setEnabled(false);               
		m_pCmbBinH->setEnabled(false);               
	}
	if (nIndex == 1)
	{
		m_pCmbBinA->setEnabled(false);                
		m_pCmbBinB->setEnabled(false);                
		m_pCmbBinC->setEnabled(false);               
		m_pCmbBinD->setEnabled(false);               
		m_pCmbBinE->setEnabled(true);               
		m_pCmbBinF->setEnabled(true);                
		m_pCmbBinG->setEnabled(true);               
		m_pCmbBinH->setEnabled(true); 
	}
}

void QRecloseCommonParasDlg::slot_OutputSwitchMode(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditOutputDelayTime->setEnabled(true);
	}
	if (nIndex == 1)
	{
		m_pEditOutputDelayTime->setEnabled(false);
	}
}

void QRecloseCommonParasDlg::slot_SimulateBreakerDelay(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditBrkBreakTime->setEnabled(false);
		m_pEditBrkCloseTime->setEnabled(false);
	}
	if (nIndex == 1)
	{
		m_pEditBrkBreakTime->setEnabled(true);
		m_pEditBrkCloseTime->setEnabled(true);
	}
}

void QRecloseCommonParasDlg::slot_OKCommonParas()
{
	CDvmData *pData;
	long nFaultTrigMode = m_pCmbFaultTrigMode->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("FaultTrigMode");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFaultTrigMode);
		m_pCmbFaultTrigMode->setCurrentIndex(nFaultTrigMode);
	}

	long nPTPos = m_pCmbPTPos->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("PTPos");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nPTPos);
		m_pCmbPTPos->setCurrentIndex(nPTPos);
	}

	long nCTPos = m_pCmbCTPos->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("CTPos");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nCTPos);
		m_pCmbCTPos->setCurrentIndex(nCTPos);
	}

	float fCurLoad = m_pEditCurLoad->text().toFloat();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("ILoad");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fCurLoad, 'f', 3);
		m_pEditCurLoad->setText(QString::number(fCurLoad, 'f', 3));
	}

	float fPowerAngleLoad = m_pEditPowerAngleLoad->text().toFloat();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("ILoadPh");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fPowerAngleLoad, 'f', 3);
		m_pEditPowerAngleLoad->setText(QString::number(fPowerAngleLoad, 'f', 1));
	}

	long nSimulateBreakerDelay = m_pCmbSimulateBreakerDelay->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("SimulateBreakerDelay");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSimulateBreakerDelay);
		m_pCmbSimulateBreakerDelay->setCurrentIndex(nSimulateBreakerDelay);
	}

	int nBrkBreakTime = m_pEditBrkBreakTime->text().toInt();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BrkBreakTime");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBrkBreakTime);
		m_pEditBrkBreakTime->setText(QString::number(nBrkBreakTime));
	}

	int nBrkCloseTime = m_pEditBrkCloseTime->text().toInt();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BrkCloseTime");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBrkCloseTime);
		m_pEditBrkCloseTime->setText(QString::number(nBrkCloseTime));
	}

	long nBinSelect = m_pCmbBinSelect->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("BinSelect");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinSelect);
		m_pCmbBinSelect->setCurrentIndex(nBinSelect);
	}

	long nBinA = m_pCmbBinA->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("A");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinA);
		m_pCmbBinA->setCurrentIndex(nBinA);
	}

	long nBinB = m_pCmbBinB->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("B");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinB);
		m_pCmbBinB->setCurrentIndex(nBinB);
	}

	long nBinC = m_pCmbBinC->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("C");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinC);
		m_pCmbBinC->setCurrentIndex(nBinC);
	}

	long nBinD = m_pCmbBinD->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("R");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinD);
		m_pCmbBinD->setCurrentIndex(nBinD);
	}

	long nBinE = m_pCmbBinE->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("E");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinE);
		m_pCmbBinE->setCurrentIndex(nBinE);
	}

	long nBinF = m_pCmbBinF->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("F");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinF);
		m_pCmbBinF->setCurrentIndex(nBinF);
	}

	long nBinG = m_pCmbBinG->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("G");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinG);
		m_pCmbBinG->setCurrentIndex(nBinG);
	}

	long nBinH = m_pCmbBinH->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("H");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBinH);
		m_pCmbBinH->setCurrentIndex(nBinH);
	}
	long nBout1 = m_pCmbBout1->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B01");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout1);
		m_pCmbBout1->setCurrentIndex(nBout1);
	}

	long nBout2 = m_pCmbBout2->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B02");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout2);
		m_pCmbBout2->setCurrentIndex(nBout2);
	}

	long nBout3 = m_pCmbBout3->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B03");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout3);
		m_pCmbBout3->setCurrentIndex(nBout3);
	}

	long nBout4 = m_pCmbBout4->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B04");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout4);
		m_pCmbBout4->setCurrentIndex(nBout4);
	}

	long nBout5 = m_pCmbBout5->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B05");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout5);
		m_pCmbBout5->setCurrentIndex(nBout5);
	}

	long nBout6 = m_pCmbBout6->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B06");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout6);
		m_pCmbBout6->setCurrentIndex(nBout6);
	}

	long nBout7 = m_pCmbBout7->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B07");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout7);
		m_pCmbBout7->setCurrentIndex(nBout7);
	}

	long nBout8 = m_pCmbBout8->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_B08");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nBout8);
		m_pCmbBout8->setCurrentIndex(nBout8);
	}

	long nOutputSwitchMode = m_pCmbOutputSwitchMode->currentIndex();
	pData = (CDvmData *)m_pRecloseCommonParasDataGroup->FindByID("_OutputSwitchMode");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nOutputSwitchMode);
		m_pCmbOutputSwitchMode->setCurrentIndex(nOutputSwitchMode);
	}
	long nFaultTime = m_pCmbFaultTrigMode->currentIndex();
	accept();
}

void QRecloseCommonParasDlg::slot_CancelCommonParas()
{
	reject();
}

void QRecloseCommonParasDlg::slot_CurLoad()
{
	float fv =m_pEditCurLoad->text().toFloat();
	fv = setLimit(0,20.000,fv);
	m_pEditCurLoad->setText(QString::number(fv, 'f', 3));
}

void QRecloseCommonParasDlg::slot_PowerAngleLoad()
{
	float fv = m_pEditPowerAngleLoad->text().toFloat();
	fv = setLimit(0,360.0,fv);
	m_pEditPowerAngleLoad->setText(QString::number(fv, 'f', 1));
}

void QRecloseCommonParasDlg::slot_BrkBreakTime()
{
	int fv = m_pEditBrkBreakTime->text().toFloat();
	fv = setLimit(0,999999,fv);
	m_pEditBrkBreakTime->setText(QString::number(fv));
}

void QRecloseCommonParasDlg::slot_BrkCloseTime()
{
	int fv = m_pEditBrkCloseTime->text().toFloat();
	fv = setLimit(0,999999,fv);
	m_pEditBrkCloseTime->setText(QString::number(fv));
}

void QRecloseCommonParasDlg::slot_OutputKeepTime()
{
	float fv = m_pEditOutputKeepTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditOutputKeepTime->setText(QString::number(fv, 'f', 3));
}

void QRecloseCommonParasDlg::slot_OutputDelayTime()
{
	float fv = m_pEditOutputDelayTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditOutputDelayTime->setText(QString::number(fv, 'f', 3));
}