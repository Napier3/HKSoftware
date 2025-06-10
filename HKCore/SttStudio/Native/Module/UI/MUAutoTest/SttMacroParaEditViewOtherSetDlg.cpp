#include "SttMacroParaEditViewOtherSetDlg.h"


QSttMacroParaEditViewOtherSetDlg::QSttMacroParaEditViewOtherSetDlg(QWidget* parent) :QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint|= Qt::WindowMaximizeButtonHint |Qt::WindowCloseButtonHint );

	m_pMainLayout = NULL;
	m_pLGroupBoxLayout = NULL;
	m_pRGroupBoxLayout = NULL;
	m_pButtonLayout = NULL;
	m_pParasetlayout = NULL;
	m_pRAllLayout = NULL;
	m_pPPssetlayout = NULL;
	m_pGroupBox_L = NULL;
	m_pGroupBox_R = NULL;
	m_pReceivLabel = NULL;
	m_pTestLabel = NULL;
	m_pBOutputLabel = NULL;
	m_pRCombox = NULL;
	m_pTCombox = NULL;
	m_pBCombox = NULL;
	m_pNoPPSRButton = NULL;
	m_pRiseRButton = NULL;
	m_pFallRButton = NULL; 
	m_pButton_OK = NULL;
	m_pButton_Cancel = NULL;
	m_pOPSetDataGroup = NULL;
	
}

QSttMacroParaEditViewOtherSetDlg::~QSttMacroParaEditViewOtherSetDlg()
{
	
}

void QSttMacroParaEditViewOtherSetDlg::InitUI()
{  
	m_pMainLayout = new QHBoxLayout();
	m_pLGroupBoxLayout = new QVBoxLayout();
	m_pRGroupBoxLayout = new QVBoxLayout();
	m_pButtonLayout = new QHBoxLayout();
	m_pParasetlayout = new QGridLayout();
	m_pPPssetlayout = new QGridLayout();
	m_pRAllLayout = new QVBoxLayout();
    m_pGroupBox_L = new QGroupBox();
	m_pGroupBox_R = new QGroupBox();
    m_pReceivLabel= new QLabel();
	m_pTestLabel = new QLabel();
	m_pBOutputLabel = new QLabel();
	m_pRCombox = new QComboBox();
	m_pTCombox = new QComboBox();
	m_pBCombox = new QComboBox();
	m_pNoPPSRButton = new QRadioButton();
	m_pRiseRButton = new QRadioButton();
	m_pFallRButton = new QRadioButton(); 
	m_pButton_OK = new QPushButton();
	m_pButton_Cancel = new QPushButton();
	    
	this->resize(450,200);
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath += _T("file.png");
#else
    strPngPath = ":/ctrls/images/file.png";
#endif
	this->setWindowIcon(QIcon(strPngPath));
	
	CString strTitle = _T("其他设置");
	this->setWindowTitle(strTitle);
	CString strGroupbox;
    strGroupbox = _T("参数设置");
    m_pGroupBox_L->setTitle(strGroupbox);
	strGroupbox = _T("PPS设置");
    m_pGroupBox_R->setTitle(strGroupbox);
	CString strLabel;
	strLabel = _T("接收报文类型");
    m_pReceivLabel->setText(strLabel);
	strLabel = _T("测试方法");
    m_pTestLabel->setText(strLabel);
	strLabel = _T("B码输出逻辑");
    m_pBOutputLabel->setText(strLabel);	

	m_pRCombox->addItem(_T("IEC-61850-9-2"));
	m_pRCombox->addItem(_T("IEC-60044-8(FT3)"));
	m_pTCombox->addItem(_T("同步法"));
	m_pTCombox->addItem(_T("插值法"));
	m_pBCombox->addItem(_T("正逻辑"));
	m_pBCombox->addItem(_T("负逻辑"));
	
	CString strRButton;
    strRButton = _T("无PPS");
    m_pNoPPSRButton->setText(strRButton);
	strRButton = _T("上升沿有效");
	m_pRiseRButton->setText(strRButton);
	strRButton = _T("下降沿有效");
	m_pFallRButton->setText(strRButton);
	CString strButton;
    strButton = _T("确认");
    m_pButton_OK->setText(strButton);
	strButton = _T("取消");
	m_pButton_Cancel->setText(strButton);

	m_pPPssetlayout->addWidget(m_pRiseRButton,0,0,1,1);
	m_pPPssetlayout->addWidget(m_pFallRButton,1,0,1,1);
	m_pPPssetlayout->addWidget(m_pNoPPSRButton,2,0,1,1);
	m_pGroupBox_L->setLayout(m_pPPssetlayout);
	m_pParasetlayout->addWidget(m_pReceivLabel,0,0,1,1);
	m_pParasetlayout->addWidget(m_pTestLabel,1,0,1,1);
	m_pParasetlayout->addWidget(m_pBOutputLabel,2,0,1,1);
	m_pParasetlayout->addWidget(m_pRCombox,0,1,1,1);
	m_pParasetlayout->addWidget(m_pTCombox,1,1,1,1);
	m_pParasetlayout->addWidget(m_pBCombox,2,1,1,1);
    m_pGroupBox_R->setLayout(m_pParasetlayout);
	m_pLGroupBoxLayout->addWidget(m_pGroupBox_L);
	m_pRGroupBoxLayout->addWidget(m_pGroupBox_R);
	m_pButtonLayout->addWidget(m_pButton_OK);
	m_pButtonLayout->addStretch(2);
	m_pButtonLayout->addWidget(m_pButton_Cancel);
    m_pRAllLayout->addLayout(m_pRGroupBoxLayout);
    m_pRAllLayout->addLayout(m_pButtonLayout);
	m_pMainLayout->addLayout(m_pLGroupBoxLayout,1);
    m_pMainLayout->addLayout(m_pRAllLayout,1);
	this->setLayout(m_pMainLayout);

}


void  QSttMacroParaEditViewOtherSetDlg::GetDatas(CDataGroup *m_pParas)
{
   m_pOPSetDataGroup = m_pParas;
}
void QSttMacroParaEditViewOtherSetDlg::InitData()
{
	if( m_pOPSetDataGroup->GetCount() < 0)
	{
	   return;
	}  
     
	long nValue;
    m_pOPSetDataGroup->GetDataValue(_T(STT_MUAUTOTEST_COMBOX_MEASTEAP),nValue);
	m_pRCombox->setCurrentIndex(nValue);
	m_pOPSetDataGroup->GetDataValue(_T(STT_MUAUTOTEST_COMBOX_TESTMETHOD),nValue);
	m_pTCombox->setCurrentIndex(nValue);
	m_pOPSetDataGroup->GetDataValue(_T(STT_MUAUTOTEST_COMBOX_BCODE),nValue);
 	m_pBCombox->setCurrentIndex(nValue);
	m_pOPSetDataGroup->GetDataValue(_T(STT_MUAUTOTEST_RATIOBUTTON_PPSSELECT),nValue);
	
 	if(nValue == 0)
 	{
 		m_pRiseRButton->setChecked(1);	
 	}
 	else if(nValue == 1)
 	{
 		m_pFallRButton->setChecked(1);		
 	}
 	else 
 	{
 		m_pNoPPSRButton->setChecked(1);		
 	}

}
void QSttMacroParaEditViewOtherSetDlg::InitConnection()
{
	connect(m_pButton_Cancel,SIGNAL(clicked()),this,SLOT(slot_Cancel()));
	connect(m_pButton_OK,SIGNAL(clicked()),this,SLOT(slot_Confirm()));
}
// void QSttMacroParaEditViewOtherSetDlg::UpdateMUOtherParaSetUI()
// {
//   	  InitUI();
// 	  InitConnection();
// 	  InitData();
// }

void QSttMacroParaEditViewOtherSetDlg::slot_Confirm()
{
 	if(m_pOPSetDataGroup->GetCount() < 0) 
 	{
 		return ;
 	}
 
    RatioSelected();
    ComboxSelected();

	long nTValue,nBValue;
	m_pOPSetDataGroup->GetDataValue(STT_MUAUTOTEST_COMBOX_MEASTEAP,nTValue);
	m_pOPSetDataGroup->GetDataValue(STT_MUAUTOTEST_COMBOX_BCODE,nBValue);
	g_oSystemParas.m_nIecFormatMeas = nTValue;
	g_oSystemParas.m_nBCodeMode = nBValue;

    close();
}

void QSttMacroParaEditViewOtherSetDlg::slot_Cancel()
{
	close();
}
void QSttMacroParaEditViewOtherSetDlg::RatioSelected()
{
	if( m_pNoPPSRButton->isChecked())
	{
		 m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_RATIOBUTTON_PPSSELECT),"2");
	}
	else if(m_pRiseRButton->isChecked())
    {
		 m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_RATIOBUTTON_PPSSELECT),"0");
	}
	else if(m_pFallRButton->isChecked())
	{
		 m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_RATIOBUTTON_PPSSELECT),"1");
	}
	
}

void  QSttMacroParaEditViewOtherSetDlg::ComboxSelected()
{
	CString strValue; 
	int nCurrentIndex;

	nCurrentIndex = m_pRCombox->currentIndex();
	strValue.Format(_T("%d"),nCurrentIndex);
	m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_COMBOX_MEASTEAP),strValue);

	nCurrentIndex = m_pTCombox->currentIndex();
	strValue.Format(_T("%d"),nCurrentIndex);
	m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_COMBOX_TESTMETHOD),strValue);

	nCurrentIndex = m_pBCombox->currentIndex();
	strValue.Format(_T("%d"),nCurrentIndex);
	m_pOPSetDataGroup->SetDataValue(_T(STT_MUAUTOTEST_COMBOX_BCODE),strValue);
}