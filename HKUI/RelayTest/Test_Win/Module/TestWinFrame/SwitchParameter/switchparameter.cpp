#include "switchparameter.h"

#include "..\Module\SttXTestMngrBaseApp.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
extern CSttXTestMngrBaseApp* g_theSttXTestMngrBaseApp;

SwitchParameter::SwitchParameter(tmt_ImpedanceParas *pImpedanceParas,  QWidget *parent)
	: QDialog(parent)
{
	
	this->setWindowTitle(/*QString::fromLocal8Bit("开入、开出量设置")*/g_sLangTxt_Native_IOSet);
	
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint|Qt::WindowCloseButtonHint);

	layoutIn = NULL;
	layoutOut  = NULL;

	pOKBtn  = NULL;
	pCancelBtn = NULL;
	pokLayout = NULL;
	mainLayout = NULL;
	m_pImpedanceParas = pImpedanceParas;
	m_pImpedanceParasEx = m_pImpedanceParas;//2024-02-26 wuxinyi 修改m_pImpedanceParasEx传值中断问题
	listLabel.clear();
	listComboBox.clear();
	m_nIsOK = 0;
	m_nInitFlag = 0;

	initUI();
	InitParameter();
	UpdateDataForDlg();
	m_nInitFlag = 2;
}

SwitchParameter::~SwitchParameter()
{
	if (layoutIn != NULL)
		delete layoutIn;	
	if (layoutOut != NULL)
		delete layoutOut;	
	if (pOKBtn != NULL)
		delete pOKBtn ;
	if (pCancelBtn != NULL)
		delete pCancelBtn;
	if (pokLayout != NULL)
		delete  pokLayout;
	//if (mainLayout != NULL)
	//	delete mainLayout;
}

void SwitchParameter::initUI()
{
	listComboBox.clear();

	resize(300,  300);
	QString strName[30];
	strName[0] = /*QString::fromLocal8Bit("开入选择")*/g_sLangTxt_Native_InputSelect;
	strName[1] = /*QString::fromLocal8Bit("开入A")*/g_sLangTxt_Manual_InA;
	strName[2] = /*QString::fromLocal8Bit("开入B")*/g_sLangTxt_Manual_InB;
	strName[3] = /*QString::fromLocal8Bit("开入C")*/g_sLangTxt_Manual_InC;
	strName[4] = /*QString::fromLocal8Bit("开入D")*/g_sLangTxt_Manual_InD;
	strName[5] = /*QString::fromLocal8Bit("开入E")*/g_sLangTxt_Manual_InE;
	strName[6] = /*QString::fromLocal8Bit("开入F")*/g_sLangTxt_Manual_InF;
	strName[7] = /*QString::fromLocal8Bit("开入G")*/g_sLangTxt_Manual_InG;
	strName[8] = /*QString::fromLocal8Bit("开入H")*/g_sLangTxt_Manual_InH;
	strName[9] = /*QString::fromLocal8Bit("开出1")*/g_sLangTxt_Manual_Out1;
	strName[10] = /*QString::fromLocal8Bit("开出2")*/g_sLangTxt_Manual_Out2;
	strName[11] = /*QString::fromLocal8Bit("开出3")*/g_sLangTxt_Manual_Out3;
	strName[12] = /*QString::fromLocal8Bit("开出4")*/g_sLangTxt_Manual_Out4;
	strName[13] = /*QString::fromLocal8Bit("开出5")*/g_sLangTxt_Manual_Out5;
	strName[14] = /*QString::fromLocal8Bit("开出6")*/g_sLangTxt_Manual_Out6;
	strName[15] = /*QString::fromLocal8Bit("开出7")*/g_sLangTxt_Manual_Out7;
	strName[16] = /*QString::fromLocal8Bit("开出8")*/g_sLangTxt_Manual_Out8;
	strName[17] = /*QString::fromLocal8Bit("开出翻转启动方式")*/g_sLangTxt_Native_OutputFlipStart;
	strName[18] = /*QString::fromLocal8Bit("开出保持时间(s)")*/g_sLangTxt_Native_OutputHoldTime;
	strName[19] = /*QString::fromLocal8Bit("开出翻转时刻(s)")*/g_sLangTxt_Native_OutputFlipMoment;

	QString strItemInput[3];
	strItemInput[0] = /*QString::fromLocal8Bit("单跳")*/g_sLangTxt_Native_SingleJump;
	strItemInput[1] = /*QString::fromLocal8Bit("三跳")*/g_sLangTxt_Native_TripleJump;
	strItemInput[2] = /*QString::fromLocal8Bit("重合")*/g_sLangTxt_Native_Reincidence;

	QString strItemOutput[2];
	strItemOutput[0] = /*QString::fromLocal8Bit("断开")*/g_sLangTxt_SOE_Break;
	strItemOutput[1] = /*QString::fromLocal8Bit("闭合")*/g_sLangTxt_SOE_Shutting;

	QString strFZFS[2];
	strFZFS[0] = /*QString::fromLocal8Bit("时间启动")*/g_sLangTxt_Native_TimeStart;
	strFZFS[1] = /*QString::fromLocal8Bit("开入量启动")*/g_sLangTxt_Native_InputStart;

	QString strInputSel[2];
	strInputSel[0] = /*QString::fromLocal8Bit("开入A-B-C-D")*/g_sLangTxt_Native_InputABCD;
	strInputSel[1] = /*QString::fromLocal8Bit("开入E-F-G-H")*/g_sLangTxt_Native_InputEFGH;

	QString strOutputSel[2];
	strOutputSel[0] = /*QString::fromLocal8Bit("开出A-B-C-D")*/g_sLangTxt_Native_OutputABCD;
	strOutputSel[1] = /*QString::fromLocal8Bit("开出E-F-G-H")*/g_sLangTxt_Native_OutputEFGH;

	QString strOK[2];
	strOK[0] = /*QString::fromLocal8Bit("确定")*/g_sLangTxt_OK;
	strOK[1] = /*QString::fromLocal8Bit("取消")*/g_sLangTxt_Cancel;


	m_pVBoxLayout = new QVBoxLayout(this);//整个的布局；

	groupBoxIn = new QGroupBox(this);
	groupBoxIn->setTitle(/*tr("开入操作")*/g_sLangTxt_Native_InputOper);

	QFont font1;
	font1.setPointSize(10);
	groupBoxIn->setFont(font1);

	int nSpacing = 5;
	m_pVBoxLayout->addWidget(groupBoxIn);

	layoutIn   =  new QGridLayout(groupBoxIn);
	for (int nIndex = 0;  nIndex <  9 ; nIndex++)
	{
		QLabel *label1  = new QLabel(strName[nIndex], groupBoxIn);
		listLabel.push_back(label1);

		QComboBox *combox1  =  new QComboBox(groupBoxIn);
		if (nIndex == 0)
		{	
			for(int nItem = 0; nItem <  2; nItem++)
				combox1->addItem(strInputSel[nItem]);
		}
		else if (nIndex >= 1 && nIndex <= 8)
		{
			for(int nItem = 0; nItem <  3; nItem++)
				combox1->addItem(strItemInput[nItem]);
		}

		combox1->setCurrentIndex(0);
		combox1->setFixedWidth(200); 
		layoutIn->addWidget(combox1, nIndex, 1);

		connect(combox1, SIGNAL(currentIndexChanged(int)),   this ,  SLOT(slot_cmb_CurrentChanged( int)));
		listComboBox.push_back(combox1);

		layoutIn->addWidget(label1, nIndex,  0);	
		layoutIn->setSpacing(nSpacing);//设置行间距
	}

	groupBoxOut = new QGroupBox(this);
	groupBoxOut->setTitle(/*tr("开出操作")*/g_sLangTxt_Native_OutputOper);
	QFont fontOut;
	fontOut.setPointSize(10);
	groupBoxOut->setFont(fontOut);

	m_pVBoxLayout->addWidget(groupBoxOut);

	layoutOut   =  new QGridLayout(groupBoxOut);
	for (int nIndex = 9;  nIndex <  20 ; nIndex++)
	{
		QLabel *label1  = new QLabel(strName[nIndex],  groupBoxOut);
		listLabel.push_back(label1);
		if (nIndex >= 9 && nIndex <= 16)
		{
			QComboBox *combox1  =  new QComboBox(groupBoxOut);

			for(int nItem = 0; nItem <  2; nItem++)
				combox1->addItem(strItemOutput[nItem]);

			combox1->setCurrentIndex(0);
			combox1->setFixedWidth(200); //内容宽
			layoutOut->addWidget(combox1, nIndex, 1);

			connect(combox1, SIGNAL(currentIndexChanged(int)),   this ,  SLOT(slot_cmb_CurrentChanged( int)));
			listComboBox.push_back(combox1);
		}
		else if (nIndex == 17)
		{	
			QComboBox *combox1  =  new QComboBox(groupBoxOut);

			for(int nItem = 0; nItem <  2; nItem++)
				combox1->addItem(strFZFS[nItem]);

			combox1->setCurrentIndex(0);
			combox1->setFixedWidth(200); //内容宽
			layoutOut->addWidget(combox1, nIndex, 1);

			connect(combox1, SIGNAL(currentIndexChanged(int)),   this ,  SLOT(slot_cmb_CurrentChanged( int)));
			listComboBox.push_back(combox1);
		}
		else if (nIndex == 18)
		{
			fanZhuanTime  = new QFloatLineEdit(groupBoxOut);
			outPutKeepTime = fanZhuanTime;
			connect(fanZhuanTime,  SIGNAL(editingFinished ()),   this ,  SLOT(slot_fanZhuanTimeChanged()));
			layoutOut->addWidget(fanZhuanTime,  nIndex, 1);
			//fanZhuanTime->InitCoverage(0.01,  100000);
			fanZhuanTime->InitCoverage(0,  100000);//dingxiaoya 20231215 解决不能输入小数
		}
		else if (nIndex == 19)
		{
			fanZhuanStoreTime  =  new QFloatLineEdit(groupBoxOut);
			outPutDelayTime = fanZhuanStoreTime;
			connect(fanZhuanStoreTime,  SIGNAL(editingFinished ()),   this ,  SLOT(slot_fanZhuanStoreTimeChanged()));
			layoutOut->addWidget(fanZhuanStoreTime,  nIndex, 1);
			fanZhuanStoreTime->InitCoverage(0,  100000);
		}

		layoutOut->setSpacing(nSpacing);//设置行间距
		layoutOut->addWidget(label1, nIndex,  0);
	}



	/*
	for (int nIndex = 0;  nIndex <  23 ; nIndex++)
	{
		QLabel *label1  = new QLabel(strName[nIndex], this);
		listLabel.push_back(label1);

		if (nIndex  != 0  &&  nIndex  != 10 &&  nIndex  != 11 &&  nIndex  != 21 &&  nIndex  != 22)
		{
			QComboBox *combox1  =  new QComboBox(this);

			if (nIndex == 1)
			{	
				for(int nItem = 0; nItem <  2; nItem++)
					combox1->addItem(strInputSel[nItem]);
			}
			else if (nIndex == 20)
			{	
				for(int nItem = 0; nItem <  2; nItem++)
					combox1->addItem(strFZFS[nItem]);
			}
			else 	if (nIndex >= 2 && nIndex <= 9)
			{
				for(int nItem = 0; nItem <  3; nItem++)
					combox1->addItem(strItemInput[nItem]);
			}
			else 	if (nIndex >= 12 && nIndex <= 19)
			{
				for(int nItem = 0; nItem <  2; nItem++)
					combox1->addItem(strItemOutput[nItem]);
			}

			combox1->setCurrentIndex(0);
			combox1->setFixedWidth(200); //内容宽
			layout->addWidget(combox1, nIndex, 1);

			connect(combox1, SIGNAL(currentIndexChanged(int)),   this ,  SLOT(slot_cmb_CurrentChanged( int)));
			listComboBox.push_back(combox1);
		}
		else if (nIndex==21)
		{
			fanZhuanTime  = new QLineEdit(this);
			connect(fanZhuanTime, SIGNAL(editingFinished ()),   this ,  SLOT(slot_fanZhuanTimeChanged()));

			layout->addWidget(fanZhuanTime,  nIndex, 1);
		}	
		else if (nIndex==22)
		{
			fanZhuanStoreTime  =  new QLineEdit(this);	
			connect(fanZhuanStoreTime, SIGNAL(editingFinished ()),   this ,  SLOT(slot_fanZhuanStoreTimeChanged()));

			layout->addWidget(fanZhuanStoreTime,  nIndex, 1);
		}

		layout->addWidget(label1, nIndex,  0);
		}
		*/


	pOKBtn = new QPushButton(strOK[0] ,this);
	pCancelBtn = new QPushButton(strOK[1] ,this);
	pOKBtn->setFixedWidth(100);
	pCancelBtn->setFixedWidth(100);

 	pokLayout = new QHBoxLayout();
 	pokLayout->addWidget(pOKBtn);
 	pokLayout->addWidget(pCancelBtn);
 	pokLayout->setStretchFactor(pOKBtn, 4);  //label3占水平布局的1/4
 	pokLayout->setStretchFactor(pCancelBtn, 4);  //label4占水平布局的3/4

	m_pVBoxLayout->addLayout(pokLayout);

	groupBoxIn->raise();
	groupBoxOut->raise();
	m_pVBoxLayout->addStretch();

/*
	mainLayout  = new QGridLayout();
	mainLayout->addLayout((QLayout*)m_pVBoxLayout,  0,  0);
	mainLayout->addLayout((QLayout*)pokLayout,  1,  0);

	//mainLayout->addLayout((QLayout*)pokLayout,  1,  0);

	setLayout(mainLayout);
*/
	QObject::connect(pOKBtn,  SIGNAL(clicked ()),  this, SLOT(slot_btnOKClicked()),  Qt::UniqueConnection);
	QObject::connect(pCancelBtn,  SIGNAL(clicked ()),  this, SLOT(slot_btnCancelClicked()),  Qt::UniqueConnection);
}


void  SwitchParameter::slot_btnClicked()
{
}

void  SwitchParameter::slot_btnOKClicked()
{
	if (SetParameter())
		close();
	else 
		return;

	m_nIsOK = 1;
}

void  SwitchParameter::slot_btnCancelClicked()
{
	close();
	m_nIsOK = 2;
}


void SwitchParameter::closeEvent(QCloseEvent *event)
{
	int adf = 0;
	m_nIsOK = 2;
// QMessageBox::StandardButton button;
//     button = QMessageBox::question(this, tr("退出程序"),
//         QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
//         QMessageBox::Yes | QMessageBox::No);
// 
//     if (button == QMessageBox::No) {
//         event->ignore();  //忽略退出信号，程序继续运行
//     }
//     else if (button == QMessageBox::Yes) {
	//         event->accept();  //接受退出信号，程序退出
	//     }
}

void SwitchParameter::setData()
{
	//long m_nDInputState[MAX_BINARYIN_COUNT];//开入量状态  0:单跳;1：三跳;2：重合
	//long m_nStateBOut[MAX_BINARYIN_COUNT];//用二进制标识各个开出状态
	//long m_nBinSelect;//开入量选择第几组   0-ABCD 1-EFGH 0
}


void SwitchParameter::slot_cmb_CurrentChanged(int nIndex)
{
	QComboBox *combox =  qobject_cast<QComboBox *>(sender());

	int nItem  =  0;
	for (nItem   =  0;  nItem  <  listComboBox.size();   nItem++)
	{
		if (listComboBox[nItem] == combox)
		{
			break;
		}
	}

	if (nItem ==  0)
		m_ImpedanceParas.m_nBinSelect  = nIndex;

	else if (nItem  >= 1&& nItem <=  8)
		m_ImpedanceParas.m_nDInputState[nItem  -  1]   =  nIndex;

	else 	if (nItem >= 9 && nItem <= 16)
		m_ImpedanceParas.m_nStateBOut[nItem   -   9]   =   nIndex;
	else if (nItem == 17)
	{
		m_ImpedanceParas.m_nOutputSwitchMode  =  nIndex;
		
		if (m_ImpedanceParas.m_nOutputSwitchMode==0)
		{
			fanZhuanTime->setDisabled(false);
			fanZhuanStoreTime->setDisabled(false);
		}
		else if (m_ImpedanceParas.m_nOutputSwitchMode==1)
		{
			fanZhuanTime->setDisabled(false);
			fanZhuanStoreTime->setDisabled(true);
		}
	}

	//chenling 20230525
 	if (nItem==0)
 	{
		UpdateBinEnable();
 	}

	m_pImpedanceParasEx = &m_ImpedanceParas;

	SetModifyPara();
}

void SwitchParameter::UpdateBinEnable()
{
	if (m_ImpedanceParas.m_nBinSelect==0)
	{
		for (int i = 1;  i < 5;  i++)
		{
			listComboBox[i]->setDisabled(false);
		}
		for (int i = 5;  i < 9;  i++)
		{
			listComboBox[i]->setDisabled(true);
		}

	}
	else if (m_ImpedanceParas.m_nBinSelect==1)
	{
		for (int i = 1;  i < 5;  i++)
		{
			listComboBox[i]->setDisabled(true);
		}
		for (int i = 5;  i < 9;  i++)
		{
			listComboBox[i]->setDisabled(false);
		}
	}	
}

void SwitchParameter::slot_fanZhuanTimeChanged()
{
	QString str = fanZhuanTime->text();
	// 	if (str.right(1).contains("."))
	// 	{
	// 		str.append("000");
	// 	}
	float fsec = str.toFloat();
	m_ImpedanceParas.m_fBoutHoldTime = fsec;
// 	fsec = setLimit(1,  999.999,  fsec);
	QString strHoldTime = QString::number(m_ImpedanceParas.m_fBoutHoldTime , 'f',  3);//dingxiaoya 20231215 保留3位小数
	fanZhuanTime->setText(strHoldTime);

	SetModifyPara();
}

void SwitchParameter::slot_fanZhuanStoreTimeChanged()
{
	QString str = fanZhuanStoreTime->text();
	//if (str.right(1).contains("."))
	//{
	//	str.append("000");
	//}
	float fsec = str.toFloat();
	m_ImpedanceParas. m_fBoutTimeTrig =  fsec;
	//fsec = setLimit(0,  999.999,  fsec);
	//int adf = 0;
	QString strTimeTrig = QString::number(m_ImpedanceParas.m_fBoutTimeTrig , 'f',  3);
	fanZhuanStoreTime->setText(strTimeTrig);
	SetModifyPara();
}

int SwitchParameter::CheckParameter()
{
	slot_fanZhuanTimeChanged();
	slot_fanZhuanStoreTimeChanged();
	GetInput_OutputState();

	bool bHasTrip = false, bHasReclose = false;
	long nBeginIndex = 0,nEndIndex = 4;

	if (m_ImpedanceParas.m_nBinSelect)
	{
		nBeginIndex = 4;
		nEndIndex = 8;
	}

	for (int nIndex = nBeginIndex;  nIndex < nEndIndex;  nIndex++)
	{
		if (m_ImpedanceParas.m_nDInputState[nIndex]  !=  2)
		{
			bHasTrip = true;
		}
		else
		{
			bHasReclose = true;
		}

	}

	if ((!bHasTrip)||(!bHasReclose))
	{
		return 0;
	}

	return 1;

// 	if (nFlag==4)
// 	{
// 		m_ImpedanceParas.m_nDInputState[3] = 2;
// 		listComboBox[4]->setCurrentIndex(2);
// 		bRet = false;
// 	}
// 
// 	bool bRetEx = true;
// 	nFlag = 0;
// 	for (int i = 5;  i < 9;  i++)
// 	{
// 		if (m_ImpedanceParas.m_nDInputState[i]  !=  2)
// 			listComboBox[i]->setDisabled(true);
// 			nFlag++;
// 	}
// 
// 	if (nFlag==4)
// 	{
// 		m_ImpedanceParas.m_nDInputState[7] = 2;
// 		listComboBox[8]->setCurrentIndex(2);
// 		bRetEx = false;
// 	}
// 
// 	if (!bRet && !bRetEx)
// 		return 	3;// 4和8都有问题，
// 	if (!bRet && bRetEx)
// 		return 	2;//8哟问题
// 	if (bRet && !bRetEx)
// 		return 	1;//4有问题
// 	if (bRet && bRetEx)
// 		return 	0;//都么有问题
// 
// 	return 1;
}

bool SwitchParameter::SetParameter()
{
	int nRet = CheckParameter();
	//2023-12-06 suyang 注销
// 	if (nRet == 0)
// 	{
// 		CString strText;
// 		strText = /*_T("缺少跳闸或重合闸开入选择.")*/g_sLangTxt_Native_InSel;
// 		QMessageBox::information(NULL, /*QObject::tr("提示")*/g_sLangTxt_Message.GetString(), strText);
// //		emit sig_CheckPara(nRet);
// 		return false;
// 	}

	m_pImpedanceParas->m_nBinSelect  = m_ImpedanceParas.m_nBinSelect;

	for (int i = 0;  i < 8;  i++)
	{
		m_pImpedanceParas->m_nDInputState[i]   =  m_ImpedanceParas.m_nDInputState[i] ;
		m_pImpedanceParas->m_nStateBOut[i]      =  m_ImpedanceParas.m_nStateBOut[i] ;
	}

	m_pImpedanceParas->m_nOutputSwitchMode   =  m_ImpedanceParas.m_nOutputSwitchMode ;
	m_pImpedanceParas->m_fBoutHoldTime   =  m_ImpedanceParas.m_fBoutHoldTime ;
	m_pImpedanceParas->m_fBoutTimeTrig   =  m_ImpedanceParas.m_fBoutTimeTrig ;
	return true;
}

void SwitchParameter::InitParameter()
{
	m_ImpedanceParas.m_nBinSelect	 = m_pImpedanceParas->m_nBinSelect ;
	for (int i = 0;  i < 8;  i++)
	{
		m_ImpedanceParas.m_nDInputState[i]  = m_pImpedanceParas->m_nDInputState[i];
		m_ImpedanceParas.m_nStateBOut[i]  = m_pImpedanceParas->m_nStateBOut[i];
	}

	m_ImpedanceParas.m_nOutputSwitchMode  =  m_pImpedanceParas->m_nOutputSwitchMode;
	m_ImpedanceParas.m_fBoutHoldTime  = m_pImpedanceParas->m_fBoutHoldTime;
	m_ImpedanceParas.m_fBoutTimeTrig  =  m_pImpedanceParas->m_fBoutTimeTrig;
}

void SwitchParameter::UpdateDataForDlg()
{
	int nItem  =  0;
	for (nItem   =  0;  nItem  <  listComboBox.size();   nItem++)
	{
		if (nItem ==  0)
		{
			if (m_ImpedanceParas.m_nBinSelect >= 0)
				listComboBox[nItem]->setCurrentIndex(m_ImpedanceParas.m_nBinSelect );
		}
		else if (nItem  >= 1&& nItem <=  8)
		{
			listComboBox[nItem]->setCurrentIndex(m_ImpedanceParas.m_nDInputState[nItem  -  1]);
		}
		else 	if (nItem >= 9 && nItem <= 16)
		{
			listComboBox[nItem]->setCurrentIndex(m_ImpedanceParas.m_nStateBOut[nItem  -  9]);
		}
		else if (nItem == 17)
		{
			if (m_ImpedanceParas.m_nOutputSwitchMode >= 0)
				listComboBox[nItem]->setCurrentIndex(m_ImpedanceParas.m_nOutputSwitchMode );
			else 
				listComboBox[nItem]->setCurrentIndex(-1);

			//
			if (m_ImpedanceParas.m_nOutputSwitchMode==0)
			{
				fanZhuanTime->setDisabled(false);
				fanZhuanStoreTime->setDisabled(false);
			}
			else if (m_ImpedanceParas.m_nOutputSwitchMode==1)
			{
				fanZhuanTime->setDisabled(false);
				fanZhuanStoreTime->setDisabled(true);
			}
		}
	}

	QString strHoldTime  =   QString::number(m_ImpedanceParas.m_fBoutHoldTime , 'f',  3);
	QString strTimeTrig   =   QString::number(m_ImpedanceParas.m_fBoutTimeTrig , 'f',  3);
	fanZhuanTime->setText(strHoldTime);
	fanZhuanStoreTime->setText(strTimeTrig);
	UpdateBinEnable();
}

//点击OK的时候获取所有combox里索引;
void SwitchParameter::GetInput_OutputState()
{
	int nItem = 0;
	for (nItem  =  0;  nItem  <  listComboBox.size();   nItem++)
	{
		if (nItem ==  0)
			m_ImpedanceParas.m_nBinSelect  = listComboBox[nItem]->currentIndex();
		else if (nItem  >= 1&& nItem <=  8)
			m_ImpedanceParas.m_nDInputState[nItem -  1] = listComboBox[nItem]->currentIndex();
		else 	if (nItem >= 9 && nItem <= 16)
			m_ImpedanceParas.m_nStateBOut[nItem -  9]  =  listComboBox[nItem]->currentIndex();
		else if (nItem == 17)
			m_ImpedanceParas.m_nOutputSwitchMode  =  listComboBox[nItem]->currentIndex();
	}
	int adf = 0;
}

void SwitchParameter::SetModifyPara()
{
	if (m_nInitFlag==2)
		g_theSttXTestMngrBaseApp->SetModifyPara();
}
void SwitchParameter::SetHideGroupBoxIn()
{
	groupBoxIn->setFixedHeight(0);
	pOKBtn->setVisible(false);
	pCancelBtn->setVisible(false);
}