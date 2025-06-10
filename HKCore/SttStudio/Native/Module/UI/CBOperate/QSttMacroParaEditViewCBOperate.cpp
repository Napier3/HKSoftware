#include "QSttMacroParaEditViewCBOperate.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"

QSttMacroParaEditViewCBOperate::QSttMacroParaEditViewCBOperate(QWidget *parent)
{
	m_pLabFaultType = NULL;               
	m_pLabCurShortCircuit = NULL;		   
	m_pLabZ = NULL;			          
	m_pLabVolShortCircuit = NULL;		   
	m_pLabImpedanceAngle = NULL;		   
	m_pLabFaultDirection = NULL;          
	m_pLabCurLoad = NULL;				   
	m_pLabFaultQuality = NULL;			   
	m_pLabPowerAngleLoad = NULL;		  
	m_pLabLarFaultTime = NULL;			   
	m_pLabFaultTrigTime = NULL;		  
	m_pLabImpedanceWay = NULL;            
	m_pLabConversionTime = NULL;		
	m_pLabHour = NULL;					   
	m_pLabMinute = NULL;		          
	m_pLabSecond = NULL;		          

	m_pChkAmpAngle = NULL;          
	m_pChkRX = NULL;				   
	m_pChkConversionFault = NULL;   

	m_pCmbFaultType = NULL;			  
	m_pCmbFaultDirection = NULL;       
	m_pCmbFaultQuality = NULL;       

	m_pEditCurShortCircuit = NULL;	 
	m_pEditZ = NULL;			     
	m_pEditVolShortCircuit = NULL;    
	m_pEditImpedanceAngle = NULL;     
	m_pEditCurLoad = NULL;			  
	m_pEditPowerAngleLoad = NULL;	  
	m_pEditLarFaultTime = NULL;		  
	m_pEditConversionTime = NULL;	  
	m_pEditHour = NULL;               
	m_pEditMinute = NULL;		     
	m_pEditSecond = NULL;		    

	m_pLabRFaultType = NULL;               //故障类型
	m_pLabRCurShortCircuit = NULL;		   //短路电流
	m_pLabRZ = NULL;			           //|Z|
	m_pLabRVolShortCircuit = NULL;		   //短路电压
	m_pLabRImpedanceAngle = NULL;		   //阻抗角
	m_pLabRFaultDirection = NULL;          //故障方向

	m_pCmbRFaultType = NULL;			   //故障类型
	m_pCmbRFaultDirection = NULL;       //故障方向
	m_pEditRCurShortCircuit = NULL;	  //短路电流
	m_pEditRZ = NULL;			      //|Z|
	m_pEditRVolShortCircuit = NULL;    //短路电压
	m_pEditRImpedanceAngle = NULL;     //阻抗角

	m_pBtnResultAssess = NULL;     
	m_pBtnCommonParas = NULL;      

	m_pLeftWidget = NULL;
	m_pRightWidget = NULL;
	m_pBottomWidget = NULL;
	m_pVlayout = NULL;
	m_pLeftGridLayout = NULL;
	m_pRightGridLayout = NULL;
	m_pBottomGridLayout = NULL;
	m_ButtonGroup = NULL;

	m_pResultAssessWidget = NULL;
	m_pCommonParas = NULL;

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();

	m_oCBOperateParas = &m_oCBOperateTest.m_oCBOperateParas;
	
	OpenTestTestMngrFile(m_strDefaultParaFile);


	memset(m_uiVOL, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));

	InitUI();
	InitFont();
	InitConnections();
	Initdates();
	SetDatas(NULL);


}

QSttMacroParaEditViewCBOperate::~QSttMacroParaEditViewCBOperate()
{

}

void QSttMacroParaEditViewCBOperate::InitUI()
{
	m_pVlayout = new QGridLayout(this);

	m_pLabFaultType = new QLabel(this);    
	m_pLabFaultType->setText(/*_T("故障类型")*/g_sLangTxt_State_FaultType);
	m_ItemsList << /*"A相接地" */g_sLangTxt_Native_GndA<</* "B相接地"*/g_sLangTxt_Native_GndB << g_sLangTxt_Native_GndC/*"C相接地" */<< /*"AB短路" */g_sLangTxt_Native_ShortAB<< g_sLangTxt_Native_ShortBC/*"BC短路"*/ <</* "CA短路"*/g_sLangTxt_Native_ShortCA <</* "AB相接地短路"*/ g_sLangTxt_Native_GndShortAB
		<< /*"BC相接地短路"*/g_sLangTxt_Native_GndShortBC << /*"CA相接地短路"*/g_sLangTxt_Native_GndShortCA <</* "ABC短路"*/g_sLangTxt_Native_ShortABC << /*"单相阻抗"*/g_sLangTxt_State_SinglephaseImpedance;
	m_pCmbFaultType = new QComboBox(this);	
	m_pCmbFaultType->setMaxVisibleItems(m_ItemsList.count());
	m_pCmbFaultType->addItems(m_ItemsList);
	m_pLabZ = new QLabel(this);
	m_pLabZ->setText(_T("|Z|(Ω)"));
	m_pEditZ = new QLineEdit(this);		

	m_pLabImpedanceAngle = new QLabel(this);
	m_pLabImpedanceAngle->setText(/*_T("阻抗角(°)")*/g_sLangTxt_Gradient_ImpAngle);
	m_pEditImpedanceAngle = new QLineEdit(this);   

	m_pLabCurLoad = new QLabel(this);	
	m_pLabCurLoad->setText(/*_T("负荷电流(A)")*/g_sLangTxt_LoadI);
	m_pEditCurLoad = new QLineEdit(this);

	m_pLabPowerAngleLoad = new QLabel(this);
	m_pLabPowerAngleLoad->setText(/*_T("负荷功角(°)")*/g_sLangTxt_State_LoadAngle);
	m_pEditPowerAngleLoad = new QLineEdit(this);	

	m_pLabCurShortCircuit = new QLabel(this);
	m_pLabCurShortCircuit->setText(/*_T("短路电流")*/g_sLangTxt_Native_ShortCircuit);
	m_pEditCurShortCircuit = new QLineEdit(this);	

	m_pLabVolShortCircuit = new QLabel(this);	
	m_pLabVolShortCircuit->setText(/*_T("短路电压")*/g_sLangTxt_Native_ShortCircuitV);
	m_pEditVolShortCircuit = new QLineEdit(this);    

	m_pLabFaultDirection = new QLabel(this);  
	m_pLabFaultDirection->setText(/*_T("故障方向")*/g_sLangTxt_Gradient_FailDirect);
	m_pCmbFaultDirection = new QComboBox(this); 
	m_pCmbFaultDirection->addItem(/*"反向"*/g_sLangTxt_CBOperate_Reverse);
	m_pCmbFaultDirection->addItem(/*"正向"*/g_sLangTxt_CBOperate_Positive);

	m_pLabFaultQuality = new QLabel(this);		
	m_pLabFaultQuality->setText(/*_T("故障性质")*/g_sLangTxt_Native_NatureMalf);
	m_pCmbFaultQuality = new QComboBox(this);
	m_pCmbFaultQuality->addItem(/*"瞬时"*/g_sLangTxt_CBOperate_Instan);
	m_pCmbFaultQuality->addItem(/*"永久"*/g_sLangTxt_CBOperate_Perpetual);

	m_pLabLarFaultTime = new QLabel(this);	
	m_pLabLarFaultTime->setText(/*_T("最大故障时间(S)")*/g_sLangTxt_CBOperate_MaxFaultTime);
	m_pEditLarFaultTime = new QLineEdit(this);		 

	m_pLabFaultTrigTime = new QLabel(this);	
	m_pLabFaultTrigTime->setText(/*_T("故障触发时刻")*/g_sLangTxt_CBOperate_FaultMoment);
	m_pLabHour = new QLabel(this);				
	m_pLabHour->setText(/*_T("时")*/g_sLangTxt_CBOperate_Hour);
	m_pEditHour = new QLineEdit(this); 
	m_pLabMinute = new QLabel(this);		          
	m_pLabMinute->setText(/*_T("分")*/g_sLangTxt_CBOperate_Minute);
	m_pEditMinute = new QLineEdit(this);	
	m_pLabSecond = new QLabel(this);		        
	m_pLabSecond->setText(/*_T("秒")*/g_sLangTxt_CBOperate_Second);
	m_pEditSecond = new QLineEdit(this);    


	m_pCmbRFaultType = new QComboBox(this);
	m_pCmbRFaultDirection = new QComboBox(this); 
	m_pEditRCurShortCircuit = new QLineEdit(this);
	m_pEditRZ = new QLineEdit(this);
	m_pEditRVolShortCircuit = new QLineEdit(this);
	m_pEditRImpedanceAngle = new QLineEdit(this);
	m_pLabImpedanceWay = new QLabel(this);  
	m_pLabImpedanceWay->setText(/*_T("阻抗表示方式：")*/g_sLangTxt_CBOperate_ImpRepre);
	m_pChkAmpAngle = new QRadioButton(this);   
	m_pChkAmpAngle->setText(/*_T("幅值相位")*/g_sLangTxt_CBOperate_AmpPhase);
	m_pChkRX = new QRadioButton(this);				
	m_pChkRX->setText(_T("R-X"));
	m_ButtonGroup = new QButtonGroup(this);
	m_ButtonGroup->addButton(m_pChkAmpAngle);
	m_ButtonGroup->addButton(m_pChkRX);
	m_pChkAmpAngle->setChecked(true);

	m_pLabConversionTime = new QLabel(this);
	m_pLabConversionTime->setText(/*_T("转换时间(S)")*/g_sLangTxt_CBOperate_ConversionTime);
	m_pEditConversionTime = new QLineEdit(this);	  

	m_pLabRFaultType = new QLabel(this);             
	m_pLabRFaultType->setText(/*_T("故障类型")*/g_sLangTxt_State_FaultType);
	m_pCmbRFaultType->addItems(m_ItemsList);
	m_pCmbRFaultType->setMaxVisibleItems(m_ItemsList.count());
	m_pLabRCurShortCircuit = new QLabel(this);		   
	m_pLabRCurShortCircuit->setText(/*_T("短路电流(A)")*/g_sLangTxt_State_ShortI);

	m_pLabRZ = new QLabel(this);			           
	m_pLabRZ->setText(_T("|Z|(Ω)"));

	m_pLabRVolShortCircuit = new QLabel(this);	   
	m_pLabRVolShortCircuit->setText(/*_T("短路电压(V)")*/g_sLangTxt_State_ShortU);

	m_pLabRImpedanceAngle = new QLabel(this);		  
	m_pLabRImpedanceAngle->setText(/*_T("阻抗角(°)")*/g_sLangTxt_Gradient_ImpAngle);

	m_pLabRFaultDirection = new QLabel(this);          
	m_pLabRFaultDirection->setText(/*_T("故障方向")*/g_sLangTxt_Gradient_FailDirect);
	m_pCmbRFaultDirection->addItem(/*"反向"*/g_sLangTxt_CBOperate_Reverse);
	m_pCmbRFaultDirection->addItem(/*"正向"*/g_sLangTxt_CBOperate_Positive);

	m_pBtnResultAssess = new QPushButton(this);     
	m_pBtnResultAssess->setText(/*_T("结果评估")*/g_sLangTxt_StateEstimate_ResultEstimate);

	m_pBtnCommonParas = new QPushButton(this);
	m_pBtnCommonParas->setText(/*_T("通用参数")*/g_sLangTxt_GeneralParameter);

	m_pLeftWidget = new QWidget(this);
	m_pLeftGridLayout = new QGridLayout(m_pLeftWidget);

	m_pLeftGridLayout->addWidget(m_pLabFaultType, 0, 0);
	m_pLeftGridLayout->addWidget(m_pCmbFaultType, 0, 1);
	m_pLeftGridLayout->addWidget(m_pLabZ, 1, 0);
	m_pLeftGridLayout->addWidget(m_pEditZ, 1, 1);
	m_pLeftGridLayout->addWidget(m_pLabImpedanceAngle, 2, 0);
	m_pLeftGridLayout->addWidget(m_pEditImpedanceAngle, 2, 1);
	m_pLeftGridLayout->addWidget(m_pLabCurLoad, 3, 0);
	m_pLeftGridLayout->addWidget(m_pEditCurLoad, 3, 1);
	m_pLeftGridLayout->addWidget(m_pLabPowerAngleLoad, 4, 0);
	m_pLeftGridLayout->addWidget(m_pEditPowerAngleLoad, 4, 1);
	m_pLeftGridLayout->addWidget(m_pLabCurShortCircuit, 0, 3);
	m_pLeftGridLayout->addWidget(m_pEditCurShortCircuit, 0, 5);
	m_pLeftGridLayout->addWidget(m_pLabVolShortCircuit, 1, 3);
	m_pLeftGridLayout->addWidget(m_pEditVolShortCircuit, 1, 5);
	m_pLeftGridLayout->addWidget(m_pLabFaultDirection, 2, 3);
	m_pLeftGridLayout->addWidget(m_pCmbFaultDirection, 2, 5);
	m_pLeftGridLayout->addWidget(m_pLabFaultQuality, 3, 3);
	m_pLeftGridLayout->addWidget(m_pCmbFaultQuality, 3, 5);
	m_pLeftGridLayout->addWidget(m_pLabLarFaultTime, 4, 3);
	m_pLeftGridLayout->addWidget(m_pEditLarFaultTime, 4, 5);
	m_pLeftGridLayout->addWidget(m_pLabFaultTrigTime, 5, 0);
	m_pLeftGridLayout->addWidget(m_pEditHour, 5, 1);
	m_pLeftGridLayout->addWidget(m_pLabHour, 5, 2);
	m_pLeftGridLayout->addWidget(m_pEditMinute, 5, 3);
	m_pLeftGridLayout->addWidget(m_pLabMinute, 5, 4);
	m_pLeftGridLayout->addWidget(m_pEditSecond, 5, 5);
	m_pLeftGridLayout->addWidget(m_pLabSecond, 5, 6);
	m_pLeftGridLayout->addWidget(m_pLabImpedanceWay, 6, 1);
	m_pLeftGridLayout->addWidget(m_pChkAmpAngle, 6, 3);
	m_pLeftGridLayout->addWidget(m_pChkRX, 6, 5);

	m_pLeftGridLayout->setSpacing(10);
	m_pLeftGridLayout->setContentsMargins(10, 10, 10, 10);

	m_pRightWidget = new QWidget(this);
	m_pRightGridLayout = new QGridLayout(m_pRightWidget);

	m_pRightGridLayout->addWidget(m_pLabRFaultType, 0, 0);
	m_pRightGridLayout->addWidget(m_pCmbRFaultType, 0, 1);
	m_pRightGridLayout->addWidget(m_pLabConversionTime, 1, 0);
	m_pRightGridLayout->addWidget(m_pEditConversionTime, 1, 1);
	m_pRightGridLayout->addWidget(m_pLabRZ, 2, 0);
	m_pRightGridLayout->addWidget(m_pEditRZ, 2, 1);
	m_pRightGridLayout->addWidget(m_pLabRImpedanceAngle, 3, 0);
	m_pRightGridLayout->addWidget(m_pEditRImpedanceAngle, 3, 1);
	m_pRightGridLayout->addWidget(m_pLabRCurShortCircuit, 4, 0);
	m_pRightGridLayout->addWidget(m_pEditRCurShortCircuit, 4, 1);
	m_pRightGridLayout->addWidget(m_pLabRVolShortCircuit, 5, 0);
	m_pRightGridLayout->addWidget(m_pEditRVolShortCircuit, 5, 1);
	m_pRightGridLayout->addWidget(m_pLabRFaultDirection, 6, 0);
	m_pRightGridLayout->addWidget(m_pCmbRFaultDirection, 6, 1);

	m_pRightGridLayout->setSpacing(10);
	m_pRightGridLayout->setContentsMargins(10, 10, 10, 10);

	m_pGroupBox = new QGroupBox("", this);
	m_pGroupBox->setLayout(m_pRightGridLayout);
	m_pGroupBoxLayout = new QVBoxLayout;
	m_pGroupBoxLayout->addWidget(m_pGroupBox);

	m_pChkConversionFault = new QSttCheckBox(/*"转换性故障"*/g_sLangTxt_CBOperate_ConversionFail, this);
	m_pGroupBoxLayout->setAlignment(m_pChkConversionFault, Qt::AlignTop | Qt::AlignLeft);
	m_pGroupBoxLayout->addWidget(m_pChkConversionFault);


	m_pBottomWidget = new QWidget(this);
	m_pBottomGridLayout = new QGridLayout(m_pBottomWidget);
	m_pBottomGridLayout->addWidget(m_pBtnResultAssess, 0, 0);
	m_pBottomGridLayout->addWidget(m_pBtnCommonParas, 0, 1);
	m_pRightGridLayout->setSpacing(10);
	m_pRightGridLayout->setContentsMargins(10, 10, 10, 10);

	m_pLeftWidget->setLayout(m_pLeftGridLayout);
	m_pRightWidget->setLayout(m_pGroupBoxLayout);

	m_pBottomWidget->setLayout(m_pBottomGridLayout);
	m_pBottomWidget->setFixedHeight(50);
	m_pVlayout->addWidget(m_pLeftWidget, 0, 0);
	m_pVlayout->addWidget(m_pRightWidget, 0, 1);
	m_pVlayout->addWidget(m_pBottomWidget, 1, 1);

	m_pEditVolShortCircuit->setEnabled(false);
	m_pEditHour->setEnabled(false);
	m_pEditMinute->setEnabled(false);
	m_pEditSecond->setEnabled(false);
	m_pCmbRFaultType->setEnabled(false);
	m_pCmbRFaultDirection->setEnabled(false);
	m_pEditRZ->setEnabled(false);
	m_pEditRImpedanceAngle->setEnabled(false);
	m_pEditConversionTime->setEnabled(false);

	m_pEditCurShortCircuit->setEnabled(true);
	m_pEditVolShortCircuit->setEnabled(false);
	m_pEditRCurShortCircuit->setEnabled(false);
	m_pEditRVolShortCircuit->setEnabled(false);

	setLayout(m_pVlayout);
}

void QSttMacroParaEditViewCBOperate::InitFont()
{
	m_pLabFaultType->setFont(*g_pSttGlobalFont);               
	m_pLabCurShortCircuit->setFont(*g_pSttGlobalFont);	   
	m_pLabZ->setFont(*g_pSttGlobalFont);			          
	m_pLabVolShortCircuit->setFont(*g_pSttGlobalFont);		   
	m_pLabImpedanceAngle->setFont(*g_pSttGlobalFont);		   
	m_pLabFaultDirection->setFont(*g_pSttGlobalFont);          
	m_pLabCurLoad->setFont(*g_pSttGlobalFont);				   
	m_pLabFaultQuality->setFont(*g_pSttGlobalFont);			   
	m_pLabPowerAngleLoad->setFont(*g_pSttGlobalFont);		  
	m_pLabLarFaultTime->setFont(*g_pSttGlobalFont);			   
	m_pLabFaultTrigTime->setFont(*g_pSttGlobalFont);		  
	m_pLabImpedanceWay->setFont(*g_pSttGlobalFont);          
	m_pLabConversionTime->setFont(*g_pSttGlobalFont);		
	m_pLabHour->setFont(*g_pSttGlobalFont);					   
	m_pLabMinute->setFont(*g_pSttGlobalFont);		          
	m_pLabSecond->setFont(*g_pSttGlobalFont);		          

	m_pChkAmpAngle->setFont(*g_pSttGlobalFont);          
	m_pChkRX->setFont(*g_pSttGlobalFont);				   
	m_pChkConversionFault->setFont(*g_pSttGlobalFont);  
	m_pCmbFaultType->setFont(*g_pSttGlobalFont);			  
	m_pCmbFaultDirection->setFont(*g_pSttGlobalFont);       
	m_pCmbFaultQuality->setFont(*g_pSttGlobalFont);       

	m_pEditCurShortCircuit->setFont(*g_pSttGlobalFont);	 
	m_pEditZ->setFont(*g_pSttGlobalFont);			     
	m_pEditVolShortCircuit->setFont(*g_pSttGlobalFont);  
	m_pEditImpedanceAngle->setFont(*g_pSttGlobalFont);     
	m_pEditCurLoad->setFont(*g_pSttGlobalFont);			  
	m_pEditPowerAngleLoad->setFont(*g_pSttGlobalFont);	  
	m_pEditLarFaultTime->setFont(*g_pSttGlobalFont);		  
	m_pEditConversionTime->setFont(*g_pSttGlobalFont);	  
	m_pEditHour->setFont(*g_pSttGlobalFont);              
	m_pEditMinute->setFont(*g_pSttGlobalFont);		     
	m_pEditSecond->setFont(*g_pSttGlobalFont);	      

	m_pLabRFaultType->setFont(*g_pSttGlobalFont);	 
	m_pLabRCurShortCircuit->setFont(*g_pSttGlobalFont);	 
	m_pLabRZ->setFont(*g_pSttGlobalFont);	 
	m_pLabRVolShortCircuit->setFont(*g_pSttGlobalFont);	 
	m_pLabRImpedanceAngle->setFont(*g_pSttGlobalFont);	 
	m_pLabRFaultDirection->setFont(*g_pSttGlobalFont);	 
	m_pCmbRFaultType->setFont(*g_pSttGlobalFont);	 
	m_pCmbRFaultDirection->setFont(*g_pSttGlobalFont);	 
	m_pEditRCurShortCircuit->setFont(*g_pSttGlobalFont);	 
	m_pEditRZ->setFont(*g_pSttGlobalFont);	 
	m_pEditRVolShortCircuit->setFont(*g_pSttGlobalFont);	 
	m_pEditRImpedanceAngle->setFont(*g_pSttGlobalFont);	 

	m_pBtnResultAssess->setFont(*g_pSttGlobalFont);    
	m_pBtnCommonParas->setFont(*g_pSttGlobalFont); 
}

void QSttMacroParaEditViewCBOperate::InitConnections()
{
	connect(m_pBtnResultAssess, SIGNAL(clicked()), this, SLOT(slot_ResultAssess()));
	connect(m_pBtnCommonParas, SIGNAL(clicked()), this, SLOT(slot_CommonParas()));
	connect(m_pChkConversionFault, SIGNAL(clicked()), this, SLOT(slot_ConversionFault()));
	connect(m_pChkAmpAngle,SIGNAL(toggled(bool)),this,SLOT(slot_ImpedanceChanged(bool)));

	connect(m_pCmbFaultType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultType(int)));
	connect(m_pEditZ, SIGNAL(editingFinished()), this, SLOT(slot_EditZ()));
	connect(m_pEditImpedanceAngle, SIGNAL(editingFinished()), this, SLOT(slot_EditImpedanceAngle()));
	connect(m_pEditCurLoad, SIGNAL(editingFinished()), this, SLOT(slot_EditCurLoad()));
	connect(m_pEditPowerAngleLoad, SIGNAL(editingFinished()), this, SLOT(slot_EditPowerAngleLoad()));
	connect(m_pEditCurShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditCurShortCircuit()));
	connect(m_pEditVolShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditVolShortCircuit()));
	connect(m_pCmbFaultDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultDirection(int)));
	connect(m_pCmbFaultQuality, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultQuality(int)));
	connect(m_pEditLarFaultTime, SIGNAL(editingFinished()), this, SLOT(slot_EditLarFaultTime()));
	connect(m_pEditHour, SIGNAL(editingFinished()), this, SLOT(slot_EditHour()));
	connect(m_pEditMinute, SIGNAL(editingFinished()), this, SLOT(slot_EditMinute()));
	connect(m_pEditSecond, SIGNAL(editingFinished()), this, SLOT(slot_EditSecond()));
	connect(m_pChkConversionFault, SIGNAL(clicked()), this, SLOT(slot_ChkConversionFault()));
	connect(m_pCmbRFaultType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbRFaultType(int)));
	connect(m_pEditConversionTime, SIGNAL(editingFinished()), this, SLOT(slot_EditConversionTime()));
	connect(m_pEditRZ, SIGNAL(editingFinished()), this, SLOT(slot_EditRZ()));
	connect(m_pEditRImpedanceAngle, SIGNAL(editingFinished()), this, SLOT(slot_EditRImpedanceAngle()));
	connect(m_pEditRCurShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditRCurShortCircuit()));
	connect(m_pEditRVolShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditRVolShortCircuit()));
	connect(m_pCmbRFaultDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbRFaultDirection(int)));
}

void QSttMacroParaEditViewCBOperate::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
														   long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_CBOperateTest *pTmtCBOperateTest = (tmt_CBOperateTest *)pParas;

	stt_xml_serialize(&pTmtCBOperateTest->m_oCBOperateParas,pMacroParas);

}


void QSttMacroParaEditViewCBOperate::slot_ResultAssess()
{
	CBOperateResultAssessGrid dlg(m_oCBOperateParas,this);
	dlg.setWindowTitle(/*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
	
#else
	dlg.exec();
#endif
	
}

void QSttMacroParaEditViewCBOperate::slot_CommonParas()
{
	CBOperateCommonParasDlg dlg(m_oCBOperateParas,this);
	dlg.setWindowTitle(/*"通用参数"*/g_sLangTxt_Gradient_CommonParas);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

	int nMode = dlg.m_pCmbFaultTrigMode->currentIndex();
	if (nMode == 3)
	{
		m_pEditHour->setEnabled(true);
		m_pEditMinute->setEnabled(true);
		m_pEditSecond->setEnabled(true);
	}
	else
	{
		m_pEditHour->setEnabled(false);
		m_pEditMinute->setEnabled(false);
		m_pEditSecond->setEnabled(false);
	}

	int nCalMode = dlg.m_pCmbCalMode->currentIndex();
	if (nCalMode == 0)
	{
		m_pEditCurShortCircuit->setEnabled(true);
		m_pEditVolShortCircuit->setEnabled(false);
		m_pEditRCurShortCircuit->setEnabled(true);
		m_pEditRVolShortCircuit->setEnabled(false);
	}
	if (nCalMode == 1)
	{
		m_pEditCurShortCircuit->setEnabled(false);
		m_pEditVolShortCircuit->setEnabled(true);
		m_pEditRCurShortCircuit->setEnabled(false);
		m_pEditRVolShortCircuit->setEnabled(true);
	}
	if (nCalMode == 2)
	{
		m_pEditCurShortCircuit->setEnabled(false);
		m_pEditVolShortCircuit->setEnabled(false);
		m_pEditRCurShortCircuit->setEnabled(false);
		m_pEditRVolShortCircuit->setEnabled(false);
	}
	if(!m_pChkConversionFault->isChecked())
	{
		m_pEditRCurShortCircuit->setEnabled(false);
		m_pEditRVolShortCircuit->setEnabled(false);
	}
}

void QSttMacroParaEditViewCBOperate::slot_ConversionFault()
{
	bool isChecked = m_pChkConversionFault->isChecked();

	m_pCmbRFaultType->setEnabled(isChecked);
	m_pCmbRFaultDirection->setEnabled(isChecked);
	m_pEditRCurShortCircuit->setEnabled(isChecked);
	m_pEditRZ->setEnabled(isChecked);
	m_pEditRVolShortCircuit->setEnabled(isChecked);
	m_pEditRImpedanceAngle->setEnabled(isChecked);
	m_pEditConversionTime->setEnabled(isChecked);

	if (isChecked)
	{
		if (m_oCBOperateParas->m_nCalMode == 0)
		{
			m_pEditCurShortCircuit->setEnabled(true);
			m_pEditVolShortCircuit->setEnabled(false);
			m_pEditRCurShortCircuit->setEnabled(true);
			m_pEditRVolShortCircuit->setEnabled(false);
		}
		if (m_oCBOperateParas->m_nCalMode == 1)
		{
			m_pEditCurShortCircuit->setEnabled(false);
			m_pEditVolShortCircuit->setEnabled(true);
			m_pEditRCurShortCircuit->setEnabled(false);
			m_pEditRVolShortCircuit->setEnabled(true);
		}
		if (m_oCBOperateParas->m_nCalMode == 2)
		{
			m_pEditCurShortCircuit->setEnabled(false);
			m_pEditVolShortCircuit->setEnabled(false);
			m_pEditRCurShortCircuit->setEnabled(false);
			m_pEditRVolShortCircuit->setEnabled(false);
		}
	}
}

void QSttMacroParaEditViewCBOperate::Initdates()
{
	m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
	
	m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
	m_pEditCurShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCCurrent[0], 'f', 3));
	m_pEditVolShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCVoltage[0], 'f', 3));
	m_pCmbFaultDirection->setCurrentIndex(m_oCBOperateParas->m_nFaultDir[0]); 
	m_pCmbFaultQuality->setCurrentIndex(m_oCBOperateParas->m_nFaultProperty); 
	m_pEditLarFaultTime->setText(QString::number(m_oCBOperateParas->m_fMaxFaultTime, 'f', 3));
	m_pEditCurLoad->setText(QString::number(m_oCBOperateParas->m_fIfh, 'f', 3));
	m_pEditPowerAngleLoad->setText(QString::number(m_oCBOperateParas->m_fPowerAngle, 'f', 3));

	m_pChkConversionFault->setChecked(m_oCBOperateParas->m_bTransFault);
	m_pCmbRFaultType->setCurrentIndex(m_oCBOperateParas->m_nFaultType[1]);
	m_pEditConversionTime->setText(QString::number(m_oCBOperateParas->m_fTransTime, 'f', 3));
	m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
	m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
	m_pEditRCurShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCCurrent[1], 'f', 3));
	m_pEditRVolShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCVoltage[0], 'f', 3));
	m_pCmbRFaultDirection->setCurrentIndex(m_oCBOperateParas->m_nFaultDir[1]);
	m_pEditHour->setText(QString::number(m_oCBOTime.nHour));
	m_pEditMinute->setText(QString::number(m_oCBOTime.nMinutes));
	m_pEditSecond->setText(QString::number(m_oCBOTime.nSeconds));
}

void QSttMacroParaEditViewCBOperate::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewCBOperate::SetDatas(CDataGroup *pParas)
{
	g_theTestCntrFrame->InitVectorWidget(m_uiVOL,m_uiCUR);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->InitPowerWidget(m_uiVOL,m_uiCUR);

}

void QSttMacroParaEditViewCBOperate::slot_AmpAngle()
{
	bool state = m_pChkAmpAngle->isCheckable();
	if (state)
	{
		m_pLabZ->setText("|Z|(Ω)");
		m_pLabImpedanceAngle->setText("阻抗角(°)");		
		m_pLabRZ->setText("|Z|(Ω)");
		m_pLabRImpedanceAngle->setText("阻抗角(°)");
		m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
		m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
	}
}

void QSttMacroParaEditViewCBOperate::slot_RX()
{
	bool state = m_pChkRX->isCheckable();
	if (state)
	{
	
		m_pLabZ->setText("R(Ω)");
		m_pLabImpedanceAngle->setText("X(Ω)");
		m_pLabRZ->setText("R(Ω)");
		m_pLabRImpedanceAngle->setText("X(Ω)");
		
		m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
		m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
	}
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultType(int nIndex)
{
	m_oCBOperateParas->m_nFaultType[0] = nIndex;
	
}

void QSttMacroParaEditViewCBOperate::slot_EditZ()
{
	float fv = m_pEditZ->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pEditZ->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpedance[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditImpedanceAngle()
{
	float fv = m_pEditImpedanceAngle->text().toFloat();
	fv = setLimit(-360.000,360.000,fv);
	m_pEditImpedanceAngle->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpAngle[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditCurLoad()
{
	float fv = m_pEditCurLoad->text().toFloat();
	fv = setLimit(0,20.000,fv);
	m_pEditCurLoad->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fIfh = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditPowerAngleLoad()
{
	float fv = m_pEditPowerAngleLoad->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
	m_pEditPowerAngleLoad->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fPowerAngle = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditCurShortCircuit()
{
	float fv = m_pEditCurShortCircuit->text().toFloat();
	fv = setLimit(0,20.0,fv);
	m_pEditCurShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCCurrent[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditVolShortCircuit()
{
	float fv = m_pEditVolShortCircuit->text().toFloat();
	fv = setLimit(0,130.000,fv);
	m_pEditVolShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCVoltage[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultDirection(int nIndex)
{
	m_oCBOperateParas->m_nFaultDir[0] = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultQuality(int nIndex)
{
	m_oCBOperateParas->m_nFaultProperty = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_EditLarFaultTime()
{
	float fv = m_pEditLarFaultTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pEditLarFaultTime->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fMaxFaultTime = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditHour()
{
	int fv = m_pEditHour->text().toInt();
	fv = setLimit(0,999,fv);
	m_pEditHour->setText(QString::number(fv));
	m_oCBOTime.nHour = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditMinute()
{
	int fv = m_pEditMinute->text().toInt();
	fv = setLimit(0,999,fv);
	m_pEditMinute->setText(QString::number(fv));
	m_oCBOTime.nMinutes = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditSecond()
{
	int fv = m_pEditSecond->text().toInt();
	fv = setLimit(0,999,fv);
	m_pEditSecond->setText(QString::number(fv));
	m_oCBOTime.nSeconds =fv;
}

void QSttMacroParaEditViewCBOperate::slot_ChkConversionFault()
{
	m_oCBOperateParas->m_bTransFault = m_pChkConversionFault->isChecked();
}

void QSttMacroParaEditViewCBOperate::slot_CmbRFaultType(int nIndex)
{
	m_oCBOperateParas->m_nFaultType[1] = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_EditConversionTime()
{
	float fv = m_pEditConversionTime->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	m_pEditConversionTime->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fTransTime = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditRZ()
{
	float fv = m_pEditRZ->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pEditRZ->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpedance[1] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditRImpedanceAngle()
{
	float fv = m_pEditRImpedanceAngle->text().toFloat();
	fv = setLimit(-360.000,360.000,fv);
	m_pEditRImpedanceAngle->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpAngle[1] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditRCurShortCircuit()
{
	float fv = m_pEditRCurShortCircuit->text().toFloat();
	fv = setLimit(0,20.000,fv);
	m_pEditRCurShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCCurrent[1] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditRVolShortCircuit()
{
	float fv = m_pEditRVolShortCircuit->text().toFloat();
	fv = setLimit(0,130.000,fv);
	m_pEditRVolShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCVoltage[1] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_CmbRFaultDirection(int nIndex)
{
	m_oCBOperateParas->m_nFaultDir[1] = nIndex;
}


void QSttMacroParaEditViewCBOperate::OnViewTestStart()
{
	startInit();
}

void QSttMacroParaEditViewCBOperate::OnViewTestStop()
{
	stopInit();
}

void QSttMacroParaEditViewCBOperate::startInit()
{
	m_pCmbFaultType->setEnabled(false);
	m_pEditZ->setEnabled(false);
	m_pEditImpedanceAngle->setEnabled(false);
	m_pEditCurLoad->setEnabled(false);
	m_pEditPowerAngleLoad->setEnabled(false);
	m_pEditCurShortCircuit->setEnabled(false);
	m_pEditVolShortCircuit->setEnabled(false);
	m_pCmbFaultDirection->setEnabled(false);
	m_pCmbFaultQuality->setEnabled(false);
	m_pEditLarFaultTime->setEnabled(false);
	m_pEditConversionTime->setEnabled(false);
	m_pEditHour->setEnabled(false);
	m_pEditMinute->setEnabled(false);
	m_pEditSecond->setEnabled(false);
	m_pBtnResultAssess->setEnabled(false);
	m_pBtnCommonParas->setEnabled(false);
	m_pCmbRFaultType->setEnabled(false);
	m_pCmbRFaultDirection->setEnabled(false);
	m_pEditRCurShortCircuit->setEnabled(false);
	m_pEditRZ->setEnabled(false);
	m_pEditRVolShortCircuit->setEnabled(false);
	m_pEditRImpedanceAngle->setEnabled(false);
	m_pChkConversionFault->setEnabled(false);
	m_pChkRX->setEnabled(false);
	m_pChkAmpAngle->setEnabled(false);
}

void QSttMacroParaEditViewCBOperate::stopInit()
{
	
	m_pCmbFaultType->setEnabled(true);
	m_pEditZ->setEnabled(true);
	m_pEditImpedanceAngle->setEnabled(true);
	m_pEditCurLoad->setEnabled(true);
	m_pEditPowerAngleLoad->setEnabled(true);
	m_pEditCurShortCircuit->setEnabled(true);
	m_pEditVolShortCircuit->setEnabled(false);
	m_pCmbFaultDirection->setEnabled(true);
	m_pCmbFaultQuality->setEnabled(true);
	m_pEditLarFaultTime->setEnabled(true);
	m_pEditHour->setEnabled(false);
	m_pEditMinute->setEnabled(false);
	m_pEditSecond->setEnabled(false);
	m_pBtnResultAssess->setEnabled(true);
	m_pBtnCommonParas->setEnabled(true);
	m_pChkConversionFault->setEnabled(true);
	m_pChkRX->setEnabled(true);
	m_pChkAmpAngle->setEnabled(true);

	bool isChecked = m_pChkConversionFault->isChecked();
	m_pCmbRFaultType->setEnabled(isChecked);
	m_pCmbRFaultDirection->setEnabled(isChecked);
	m_pEditRCurShortCircuit->setEnabled(isChecked);
	m_pEditRZ->setEnabled(isChecked);
	m_pEditRVolShortCircuit->setEnabled(false);
	m_pEditRImpedanceAngle->setEnabled(isChecked);
	m_pEditConversionTime->setEnabled(isChecked);
}

void QSttMacroParaEditViewCBOperate::slot_ImpedanceChanged( bool bIsrBtnAmpAngleChecked)
{

	QString strEdit1 ;
	QString strEdit2 ;

	if (bIsrBtnAmpAngleChecked)
	{
		strEdit1 = GetImpedanceByXY("Amp",m_pEditZ->text(),m_pEditImpedanceAngle->text());
		strEdit2 = GetImpedanceByXY("Angle",m_pEditZ->text(),m_pEditImpedanceAngle->text());
		m_pEditZ->setText(strEdit1);
		m_pEditImpedanceAngle->setText(strEdit2);

		strEdit1 = GetImpedanceByXY("Amp",m_pEditRZ->text(),m_pEditRImpedanceAngle->text());
		strEdit2 = GetImpedanceByXY("Angle",m_pEditRZ->text(),m_pEditRImpedanceAngle->text());
		m_pEditRZ->setText(strEdit1);
		m_pEditRImpedanceAngle->setText(strEdit2);

	}	
	else
	{
		strEdit1 = GetXYByImpedance("X",m_pEditZ->text(),m_pEditImpedanceAngle->text());
		strEdit2 = GetXYByImpedance("Y",m_pEditZ->text(),m_pEditImpedanceAngle->text());
		m_pEditZ->setText(strEdit1);
		m_pEditImpedanceAngle->setText(strEdit2);

		strEdit1 = GetXYByImpedance("X",m_pEditRZ->text(),m_pEditRImpedanceAngle->text());
		strEdit2 = GetXYByImpedance("Y",m_pEditRZ->text(),m_pEditRImpedanceAngle->text());
		m_pEditRZ->setText(strEdit1);
		m_pEditRImpedanceAngle->setText(strEdit2);

	}
			
}
CString QSttMacroParaEditViewCBOperate::GetXYByImpedance(QString strXY,QString strAmp,QString strAngle)
{
	double  dCoordsValue ;

	if(strXY.compare("X") == 0)
	{
		dCoordsValue = strAmp.toDouble() * cos(strAngle.toDouble() * _PI / 180);
	}
	else
	{
		dCoordsValue = strAmp.toDouble() * sin(strAngle.toDouble() * _PI / 180);
	}
	return QString::number(dCoordsValue, 'f', 3);
}

CString QSttMacroParaEditViewCBOperate::GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle)
{
	double  dImpedanceValue ;
    
	if(strAmpAngle.compare("Amp") == 0)
	{
		dImpedanceValue = sqrt(strAmp.toDouble() * strAmp.toDouble()+strAngle.toDouble() * strAngle.toDouble());
		return QString::number(dImpedanceValue, 'f', 3);
	}
	else
	{
		dImpedanceValue = atan2(strAngle.toDouble(),strAmp.toDouble()) * 180 / _PI;
		return QString::number(dImpedanceValue, 'f', 3);
	}


	
}
