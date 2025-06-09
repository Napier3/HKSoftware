#include "switchparameter.h"
#include "../ReportView/XLangResource_PowerTestWin.h"


SwitchParameter::SwitchParameter(tmt_ImpedanceParas *pImpedanceParas,  QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(/*QString::fromLocal8Bit("开入、开出量设置")*/g_sLangTxt_Native_IOSet);
	layout = NULL;
	pOKBtn  = NULL;
	pCancelBtn = NULL;
	pokLayout = NULL;
	mainLayout = NULL;
	m_pImpedanceParas = pImpedanceParas;
	listLabel.clear();
	listComboBox.clear();

	initUI();
	InitParameter();
	UpdateDataForDlg();
}

SwitchParameter::~SwitchParameter()
{
	delete layout;
	delete pOKBtn ;
	delete pCancelBtn;
	delete  pokLayout;
	delete mainLayout;
}

void SwitchParameter::initUI()
{
	listComboBox.clear();

	resize(300,  300);
	QString strName[30];
	strName[0] = /*QString::fromLocal8Bit("开入操作:")*/g_sLangTxt_Native_InputOpers;
	strName[1] = /*QString::fromLocal8Bit("开入选择")*/g_sLangTxt_Native_InputSelect;
	strName[2] = /*QString::fromLocal8Bit("开入A")*/g_sLangTxt_Manual_InA;
	strName[3] = /*QString::fromLocal8Bit("开入B")*/g_sLangTxt_Manual_InB;
	strName[4] = /*QString::fromLocal8Bit("开入C")*/g_sLangTxt_Manual_InC;
	strName[5] = /*QString::fromLocal8Bit("开入D")*/g_sLangTxt_Manual_InD;
	strName[6] = /*QString::fromLocal8Bit("开入E")*/g_sLangTxt_Manual_InE;
	strName[7] = /*QString::fromLocal8Bit("开入F")*/g_sLangTxt_Manual_InF;
	strName[8] = /*QString::fromLocal8Bit("开入G")*/g_sLangTxt_Manual_InG;
	strName[9] = /*QString::fromLocal8Bit("开入H")*/g_sLangTxt_Manual_InH;

	strName[10] = QString::fromLocal8Bit("  ");
	strName[11] = /*QString::fromLocal8Bit("开出操作:")*/g_sLangTxt_Native_OutputOpers;	//strName[12] = QString::fromLocal8Bit("开出选择");
	strName[12] = /*QString::fromLocal8Bit("开出A")*/g_sLangTxt_Native_OutputA;
	strName[13] = /*QString::fromLocal8Bit("开出B")*/g_sLangTxt_Native_OutputB;
	strName[14] = /*QString::fromLocal8Bit("开出C")*/g_sLangTxt_Native_OutputC;
	strName[15] = /*QString::fromLocal8Bit("开出D")*/g_sLangTxt_Native_OutputD;
	strName[16] = /*QString::fromLocal8Bit("开出E")*/g_sLangTxt_Native_OutputE;
	strName[17] = /*QString::fromLocal8Bit("开出F")*/g_sLangTxt_Native_OutputF;
	strName[18] = /*QString::fromLocal8Bit("开出G")*/g_sLangTxt_Native_OutputG;
	strName[19] = /*QString::fromLocal8Bit("开出H")*/g_sLangTxt_Native_OutputH;

	strName[20] = /*QString::fromLocal8Bit("开出翻转启动方式")*/g_sLangTxt_Native_OutputFlipStart;
	strName[21] = /*QString::fromLocal8Bit("开出翻转时刻")*/g_sLangTxt_Native_OutputFlipMomentS;
	strName[22] = /*QString::fromLocal8Bit("开出保持时间")*/g_sLangTxt_Native_OutputHoldTimeS;

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

	pOKBtn = new QPushButton(strOK[0] ,this);
	pCancelBtn = new QPushButton(strOK[1] ,this);

	layout   =  new QGridLayout();

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

    pokLayout = new QHBoxLayout();
	pokLayout->addWidget(pOKBtn);
	pokLayout->addWidget(pCancelBtn);
	pokLayout->setStretchFactor(pOKBtn, 4);  //label3占水平布局的1/4
	pokLayout->setStretchFactor(pCancelBtn, 4);  //label4占水平布局的3/4

	mainLayout  = new QGridLayout();

	//mainLayout.setMargin(10);
	//mainLayout.setSpacing(10);
	mainLayout->addLayout((QLayout*)layout,  0,  0);
	mainLayout->addLayout((QLayout*)pokLayout,  1,  0);

	setLayout(mainLayout);

	QObject::connect(pOKBtn,  SIGNAL(clicked ()),  this, SLOT(slot_btnOKClicked()),  Qt::UniqueConnection);
	QObject::connect(pCancelBtn,  SIGNAL(clicked ()),  this, SLOT(slot_btnCancelClicked()),  Qt::UniqueConnection);
}

void  SwitchParameter::slot_btnClicked()
{
}



void  SwitchParameter::slot_btnOKClicked()
{
	SetParameter();
	close();
}

void  SwitchParameter::slot_btnCancelClicked()
{
	close();
}


void SwitchParameter::closeEvent(QCloseEvent *event)
{
	int adf = 0;

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
		m_ImpedanceParas.m_nOutputSwitchMode  =  nIndex;

	int adf = 0;
}

void SwitchParameter::slot_fanZhuanTimeChanged()
{
	QString str = fanZhuanTime->text();
// 	if (str.right(1).contains("."))
	// 	{
	// 		str.append("000");
	// 	}
	float fsec = str.toFloat();
	m_ImpedanceParas.m_fBoutTimeTrig = fsec;
	fsec = setLimit(0,999.999,fsec);
}

void SwitchParameter::slot_fanZhuanStoreTimeChanged()
{
	QString str = fanZhuanStoreTime->text();
// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
	float fsec = str.toFloat();
	m_ImpedanceParas.m_fBoutHoldTime  =  fsec;
	fsec = setLimit(0,  999.999,  fsec);
	int adf = 0;
}

void SwitchParameter::SetParameter()
{
	m_pImpedanceParas->m_nBinSelect  = m_ImpedanceParas.m_nBinSelect;
	for (int i = 0;  i < 8;  i++)
	{
		m_pImpedanceParas->m_nDInputState[i]   =  m_ImpedanceParas.m_nDInputState[i] ;
		m_pImpedanceParas->m_nStateBOut[i]      =  m_ImpedanceParas.m_nStateBOut[i] ;
	}

	m_pImpedanceParas->m_nOutputSwitchMode   =  m_ImpedanceParas.m_nOutputSwitchMode ;
	m_pImpedanceParas->m_fBoutHoldTime   =  m_ImpedanceParas.m_fBoutHoldTime ;
	m_pImpedanceParas->m_fBoutTimeTrig   =  m_ImpedanceParas.m_fBoutTimeTrig ;
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
		}
	}

	QString strHoldTime   =   QString::number(m_ImpedanceParas.m_fBoutHoldTime , 'f',  3);
	QString strTimeTrig     =   QString::number(m_ImpedanceParas.m_fBoutTimeTrig , 'f',  3);
	fanZhuanTime->setText(strHoldTime);
	fanZhuanStoreTime->setText(strTimeTrig);
}