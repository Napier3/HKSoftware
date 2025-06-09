#include "SttIecSMVFT3InMapSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"



QSttIecSMVFT3InMapSetDialog::QSttIecSMVFT3InMapSetDialog(CString strMapString,QWidget *parent)
{

	m_strMapString = strMapString;
	InitUI();

}

QSttIecSMVFT3InMapSetDialog::~QSttIecSMVFT3InMapSetDialog()
{


}


void QSttIecSMVFT3InMapSetDialog::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);	//去掉对话框问号

	resize(500,500);

	setWindowTitle(g_sLangTxt_IEC_FT3MapParameterSet);

	CString strText;

	strText= _T("Bit[0]");
	m_pBit0_label = new QLabel(strText);
	m_pBit0_label->setAlignment(Qt::AlignCenter);
	m_pBit0_comboBox = new QComboBox();
	SetComboxItem(m_pBit0_comboBox);

	strText = _T("Bit[1]");
	m_pBit1_label = new QLabel(strText);
	m_pBit1_label->setAlignment(Qt::AlignCenter);
	m_pBit1_comboBox = new QComboBox();
	SetComboxItem(m_pBit1_comboBox);

	strText = _T("Bit[2]");
	m_pBit2_label = new QLabel(strText);
	m_pBit2_label->setAlignment(Qt::AlignCenter);
	m_pBit2_comboBox = new QComboBox();
	SetComboxItem(m_pBit2_comboBox);

	strText = _T("Bit[3]");
	m_pBit3_label = new QLabel(strText);
	m_pBit3_label->setAlignment(Qt::AlignCenter);
	m_pBit3_comboBox = new QComboBox();
	SetComboxItem(m_pBit3_comboBox);

	strText = _T("Bit[4]");
	m_pBit4_label = new QLabel(strText);
	m_pBit4_label->setAlignment(Qt::AlignCenter);
	m_pBit4_comboBox = new QComboBox();
	SetComboxItem(m_pBit4_comboBox);

	strText = _T("Bit[5]");
	m_pBit5_label = new QLabel(strText);
	m_pBit5_label->setAlignment(Qt::AlignCenter);
	m_pBit5_comboBox = new QComboBox();
	SetComboxItem(m_pBit5_comboBox);

	strText = _T("Bit[6]");
	m_pBit6_label = new QLabel(strText);
	m_pBit6_label->setAlignment(Qt::AlignCenter);
	m_pBit6_comboBox = new QComboBox();
	SetComboxItem(m_pBit6_comboBox);

	strText = _T("Bit[7]");
	m_pBit7_label = new QLabel(strText);
	m_pBit7_label->setAlignment(Qt::AlignCenter);
	m_pBit7_comboBox = new QComboBox();
	SetComboxItem(m_pBit7_comboBox);

	strText = _T("Bit[8]");
	m_pBit8_label = new QLabel(strText);
	m_pBit8_label->setAlignment(Qt::AlignCenter);
	m_pBit8_comboBox = new QComboBox();
	SetComboxItem(m_pBit8_comboBox);

	strText = _T("Bit[9]");
	m_pBit9_label = new QLabel(strText);
	m_pBit9_label->setAlignment(Qt::AlignCenter);
	m_pBit9_comboBox = new QComboBox();
	SetComboxItem(m_pBit9_comboBox);

	strText = _T("Bit[10]");
	m_pBit10_label = new QLabel(strText);
	m_pBit10_label->setAlignment(Qt::AlignCenter);
	m_pBit10_comboBox = new QComboBox();
	SetComboxItem(m_pBit10_comboBox);

	strText = _T("Bit[11]");
	m_pBit11_label = new QLabel(strText);
	m_pBit11_label->setAlignment(Qt::AlignCenter);
	m_pBit11_comboBox = new QComboBox();
	SetComboxItem(m_pBit11_comboBox);

	strText = _T("Bit[12]");
	m_pBit12_label = new QLabel(strText);
	m_pBit12_label->setAlignment(Qt::AlignCenter);
	m_pBit12_comboBox = new QComboBox();
	SetComboxItem(m_pBit12_comboBox);

	strText = _T("Bit[13]");
	m_pBit13_label = new QLabel(strText);
	m_pBit13_label->setAlignment(Qt::AlignCenter);
	m_pBit13_comboBox = new QComboBox();
	SetComboxItem(m_pBit13_comboBox);

	strText = _T("Bit[14]");
	m_pBit14_label = new QLabel(strText);
	m_pBit14_label->setAlignment(Qt::AlignCenter);
	m_pBit14_comboBox = new QComboBox();
	SetComboxItem(m_pBit14_comboBox);

	strText = _T("Bit[15]");
	m_pBit15_label = new QLabel(strText);
	m_pBit15_label->setAlignment(Qt::AlignCenter);
	m_pBit15_comboBox = new QComboBox();
	SetComboxItem(m_pBit15_comboBox);

	m_pBinGridLayout = new QGridLayout();

	m_pBinGridLayout->addWidget(m_pBit0_label,0,0);
	m_pBinGridLayout->addWidget(m_pBit0_comboBox,0,1);
	m_pBinGridLayout->addWidget(m_pBit8_label,0,2);
	m_pBinGridLayout->addWidget(m_pBit8_comboBox,0,3);


	m_pBinGridLayout->addWidget(m_pBit1_label,1,0);
	m_pBinGridLayout->addWidget(m_pBit1_comboBox,1,1);
	m_pBinGridLayout->addWidget(m_pBit9_label,1,2);
	m_pBinGridLayout->addWidget(m_pBit9_comboBox,1,3);


	m_pBinGridLayout->addWidget(m_pBit2_label,2,0);
	m_pBinGridLayout->addWidget(m_pBit2_comboBox,2,1);
	m_pBinGridLayout->addWidget(m_pBit10_label,2,2);
	m_pBinGridLayout->addWidget(m_pBit10_comboBox,2,3);


	m_pBinGridLayout->addWidget(m_pBit3_label,3,0);
	m_pBinGridLayout->addWidget(m_pBit3_comboBox,3,1);
	m_pBinGridLayout->addWidget(m_pBit11_label,3,2);
	m_pBinGridLayout->addWidget(m_pBit11_comboBox,3,3);


	m_pBinGridLayout->addWidget(m_pBit4_label,4,0);
	m_pBinGridLayout->addWidget(m_pBit4_comboBox,4,1);
	m_pBinGridLayout->addWidget(m_pBit12_label,4,2);
	m_pBinGridLayout->addWidget(m_pBit12_comboBox,4,3);


	m_pBinGridLayout->addWidget(m_pBit5_label,5,0);
	m_pBinGridLayout->addWidget(m_pBit5_comboBox,5,1);
	m_pBinGridLayout->addWidget(m_pBit13_label,5,2);
	m_pBinGridLayout->addWidget(m_pBit13_comboBox,5,3);


	m_pBinGridLayout->addWidget(m_pBit6_label,6,0);
	m_pBinGridLayout->addWidget(m_pBit6_comboBox,6,1);
	m_pBinGridLayout->addWidget(m_pBit14_label,6,2);
	m_pBinGridLayout->addWidget(m_pBit14_comboBox,6,3);

	m_pBinGridLayout->addWidget(m_pBit7_label,7,0);
	m_pBinGridLayout->addWidget(m_pBit7_comboBox,7,1);
	m_pBinGridLayout->addWidget(m_pBit15_label,7,2);
	m_pBinGridLayout->addWidget(m_pBit15_comboBox,7,3);


	// 	m_pBinGridLayout->setAlignment(Qt::AlignCenter);
	m_pBinGridLayout->setContentsMargins(0,10,0,10);
	m_pBinGridLayout->setSpacing(30);

	m_pOK_PushButton = new QPushButton(g_sLangTxt_OK);
	m_pCancel_PushButton = new QPushButton(g_sLangTxt_Cancel);

	horizontalLayout_Btn = new QHBoxLayout();
	horizontalLayout_Btn->addStretch();
	horizontalLayout_Btn->addWidget(m_pOK_PushButton);
	horizontalLayout_Btn->addStretch();
	horizontalLayout_Btn->addWidget(m_pCancel_PushButton);
	horizontalLayout_Btn->addStretch();


	m_pMainVLayout = new QVBoxLayout();

	m_pMainVLayout->addLayout(m_pBinGridLayout);
	m_pMainVLayout->addLayout(horizontalLayout_Btn);
	setLayout(m_pMainVLayout);


//把所有的combox添加进combox数组，方面后面使用
	m_BitComBox[0]=m_pBit0_comboBox;
	m_BitComBox[1]=m_pBit1_comboBox;
	m_BitComBox[2]=m_pBit2_comboBox;
	m_BitComBox[3]=m_pBit3_comboBox;
	m_BitComBox[4]=m_pBit4_comboBox;
	m_BitComBox[5]=m_pBit5_comboBox;
	m_BitComBox[6]=m_pBit6_comboBox;
	m_BitComBox[7]=m_pBit7_comboBox;
	m_BitComBox[8]=m_pBit8_comboBox;
	m_BitComBox[9]=m_pBit9_comboBox;
	m_BitComBox[10]=m_pBit10_comboBox;
	m_BitComBox[11]=m_pBit11_comboBox;
	m_BitComBox[12]=m_pBit12_comboBox;
	m_BitComBox[13]=m_pBit13_comboBox;
	m_BitComBox[14]=m_pBit14_comboBox;
	m_BitComBox[15]=m_pBit15_comboBox;



	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);	//去掉对话框问号



	connect(m_pCancel_PushButton,SIGNAL(clicked()),this,SLOT(slot_CancelClicked()));
	connect(m_pOK_PushButton,SIGNAL(clicked()),this,SLOT(slot_OKClicked()));
	SetIecSMVFT3InMapFont();
	ShowData();
}

void QSttIecSMVFT3InMapSetDialog::SetComboxItem(QComboBox *m_Combox)
{
	CString ComboxItem;
	xlang_GetLangStrByFile(ComboxItem,_T("sNone"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InA"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InB"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InC"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InD"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InE"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InF"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InG"));
	m_Combox->addItem(ComboxItem);
	xlang_GetLangStrByFile(ComboxItem,_T("Manual_InH"));
	m_Combox->addItem(ComboxItem);

}

void QSttIecSMVFT3InMapSetDialog::SetIecSMVFT3InMapFont()
{
	m_pBit0_label->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
// 	m_pLeftWidget->setFont(*g_pSttGlobalFont);
	m_pBit0_label->setFont(*g_pSttGlobalFont);
	m_pBit0_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit1_label->setFont(*g_pSttGlobalFont);
	m_pBit1_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit2_label->setFont(*g_pSttGlobalFont);
	m_pBit2_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit3_label->setFont(*g_pSttGlobalFont);
	m_pBit3_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit4_label->setFont(*g_pSttGlobalFont);
	m_pBit4_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit5_label->setFont(*g_pSttGlobalFont);
	m_pBit5_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit6_label->setFont(*g_pSttGlobalFont);
	m_pBit6_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit7_label->setFont(*g_pSttGlobalFont);
	m_pBit7_comboBox->setFont(*g_pSttGlobalFont);
// 	m_pRightWidget->setFont(*g_pSttGlobalFont);
	m_pBit8_label->setFont(*g_pSttGlobalFont);
	m_pBit8_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit9_label->setFont(*g_pSttGlobalFont);
	m_pBit9_comboBox->setFont(*g_pSttGlobalFont);
	 m_pBit10_label->setFont(*g_pSttGlobalFont);
	m_pBit10_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit11_label->setFont(*g_pSttGlobalFont);
	 m_pBit11_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit12_label->setFont(*g_pSttGlobalFont);
	m_pBit12_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit13_label->setFont(*g_pSttGlobalFont);
	m_pBit13_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit14_label->setFont(*g_pSttGlobalFont);
	m_pBit14_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit15_label->setFont(*g_pSttGlobalFont);
	m_pBit15_comboBox->setFont(*g_pSttGlobalFont);
}
void QSttIecSMVFT3InMapSetDialog::SaveData()
{
	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_MapSelectBitData[nIndex]=m_BitComBox[nIndex]->currentText();
	}

	CString strSelectID;
	for(int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		if(m_MapSelectBitData[nIndex]==/* CString("无") */g_sLangTxt_None)
		{
			m_MapBitDataID[nIndex] = "none";
			m_MapBitSelIndex[nIndex] = 0;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入A") */g_sLangTxt_Manual_InA)
		{
			m_MapBitDataID[nIndex] = "bin1";
			m_MapBitSelIndex[nIndex] = 1;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入B") */g_sLangTxt_Manual_InB)
		{
			m_MapBitDataID[nIndex] = "bin2";
			m_MapBitSelIndex[nIndex] = 2;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入C") */g_sLangTxt_Manual_InC)
		{
			m_MapBitDataID[nIndex] = "bin3";
			m_MapBitSelIndex[nIndex] = 3;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入D") */g_sLangTxt_Manual_InD)
		{
			m_MapBitDataID[nIndex] = "bin4";
			m_MapBitSelIndex[nIndex] = 4;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入E") */g_sLangTxt_Manual_InE)
		{
			m_MapBitDataID[nIndex] = "bin5";
			m_MapBitSelIndex[nIndex] = 5;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入F") */g_sLangTxt_Manual_InF)
		{
			m_MapBitDataID[nIndex] = "bin6";
			m_MapBitSelIndex[nIndex] = 6;
		}
		else if(m_MapSelectBitData[nIndex]==/* CString("开入G") */g_sLangTxt_Manual_InG)
		{
			m_MapBitDataID[nIndex] = "bin7";
			m_MapBitSelIndex[nIndex] = 7;
		}
		else
		{
			m_MapBitDataID[nIndex] = "bin8";
			m_MapBitSelIndex[nIndex] = 8;
		}

	}
	
	m_strMapString = _T("");
	
	for(int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		strSelectID =m_MapBitDataID[nIndex];
		if(strSelectID!="none")
		{
			m_strMapString.AppendFormat(_T("bit%d=%s;"),nIndex,strSelectID.GetString());
		}
	}
	
	if(m_strMapString.IsEmpty())
	{
		m_strMapString = "none";
	}
	
		//m_pCfg6044CommonCh->m_strDevChID = m_strMapString;
}

void QSttIecSMVFT3InMapSetDialog::SetComboxData(QString m_str)
{
	int o_len = m_str.size();
	QString ComboxSel,ComboxID;
	int ComboxNum = 20;		//大于15，防止开始就给combox操作
	int ComboxSelNum = 20;	//大于，防止开始就对combox操作
	for(int i=0;i<o_len;++i)
	{
		if(m_str[i]>='0'&&m_str[i]<='9')
		{
			ComboxSel+=m_str[i];
		}
		if(m_str[i]=='=')
		{
			ComboxID=ComboxSel;
			ComboxSel="";
			ComboxNum=ComboxID.toInt();
		}
	}
	ComboxSelNum=ComboxSel.toInt();

	m_BitComBox[ComboxNum]->setCurrentIndex(ComboxSelNum);
	
}

void QSttIecSMVFT3InMapSetDialog::ShowData()
{	
	QStringList  strMapString_Split=m_strMapString.split(';');
	strMapString_Split.removeLast();
	int o_len1 = strMapString_Split.size();
	for(int i=0;i<o_len1;++i)
	{
		QString o_strMapSplit = strMapString_Split[i];
		SetComboxData(o_strMapSplit);	
	}
	
}

void QSttIecSMVFT3InMapSetDialog::slot_CancelClicked()
{

	close();
}

void QSttIecSMVFT3InMapSetDialog::slot_OKClicked()
{
	SaveData();
	close();


}