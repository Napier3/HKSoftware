#include "QWeakSetWidget.h"

QWeakSetWidget::QWeakSetWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pChMaps = NULL;
	m_pWeakSetGrid = NULL;
}

QWeakSetWidget::~QWeakSetWidget()
{
	ReleaseUI();
}

// QString GetWeakSetGroupName(int nGroupIndex)
// {
// 	QString strGroupName;
// 	strGroupName = QString(QObject::_T("第%1组(U%2,U%3,U%4,I%5,I%6,I%7)")).arg(nGroupIndex+1).arg(nGroupIndex*3+1).arg(nGroupIndex*3+2).arg(nGroupIndex*3+3)
// 		.arg(nGroupIndex*3+1).arg(nGroupIndex*3+2).arg(nGroupIndex*3+3);
// 
// 	return strGroupName;
// }

void QWeakSetWidget::initUI(CSttChMaps *pChMaps)
{
	ReleaseUI();
	m_pChMaps = pChMaps;

	m_pAll_VBoxLayout = new QVBoxLayout(this);//整个布局控件

	m_pWeakSetGrid = new CWeakSetGrid(this);
	m_pWeakSetGrid->InitGrid();
	m_pAll_VBoxLayout->addWidget(m_pWeakSetGrid);

	InitDatas();
	m_pWeakSetGrid->ShowDatas(pChMaps);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	QString strTmp;
// 
// 	for (int nGroupIndex = 0;nGroupIndex<MAX_WEEK_GROUP_NUM;nGroupIndex++)
// 	{
// 		m_pGroup_GroupBox[nGroupIndex] = new QGroupBox(this);//第一行所有控件，放入该Group下
// 		m_pAll_VBoxLayout->addWidget(m_pGroup_GroupBox[nGroupIndex]);
// 		strTmp = GetWeakSetGroupName(nGroupIndex);
// 		m_pGroup_GroupBox[nGroupIndex]->setTitle(strTmp);
// 
// 		m_pGroup_HBoxLayout[nGroupIndex] = new QHBoxLayout(m_pGroup_GroupBox[nGroupIndex]);//在Group内部增加表格布局，表格布局中包含第一行全部控件
// 		m_pPT_Rate_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pPT_Rate_Label[nGroupIndex]->setText(_T("PT变比:"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pPT_Rate_Label[nGroupIndex]);
// 
// 		m_pPT_PrimValue_LineEdit[nGroupIndex] = new QFloatLineEdit(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pPT_PrimValue_LineEdit[nGroupIndex]->InitCoverage(1,130);
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pPT_PrimValue_LineEdit[nGroupIndex]);
// 
// 		m_pPT_Unit1_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pPT_Unit1_Label[nGroupIndex]->setText(_T("V/"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pPT_Unit1_Label[nGroupIndex]);
// 
// 		m_pPT_SecondValue_LineEdit[nGroupIndex] = new QFloatLineEdit(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pPT_SecondValue_LineEdit[nGroupIndex]->InitCoverage(1,10);
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pPT_SecondValue_LineEdit[nGroupIndex]);
// 
// 		m_pPT_Unit2_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pPT_Unit2_Label[nGroupIndex]->setText(_T("V"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pPT_Unit2_Label[nGroupIndex]);
// 
// 		m_pGroup_HBoxLayout[nGroupIndex]->addStretch();
// 
// 		m_pCT_Rate_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pCT_Rate_Label[nGroupIndex]->setText(_T("CT变比:"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pCT_Rate_Label[nGroupIndex]);
// 
// 		m_pCT_PrimValue_LineEdit[nGroupIndex] = new QFloatLineEdit(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pCT_PrimValue_LineEdit[nGroupIndex]->InitCoverage(1,50);
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pCT_PrimValue_LineEdit[nGroupIndex]);
// 
// 		m_pCT_Unit1_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pCT_Unit1_Label[nGroupIndex]->setText(_T("A/"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pCT_Unit1_Label[nGroupIndex]);
// 
// 		m_pCT_SecondValue_LineEdit[nGroupIndex] = new QFloatLineEdit(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pCT_SecondValue_LineEdit[nGroupIndex]->InitCoverage(1,10);
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pCT_SecondValue_LineEdit[nGroupIndex]);
// 
// 		m_pCT_Unit2_Label[nGroupIndex] = new QLabel(m_pGroup_GroupBox[nGroupIndex]);
// 		m_pCT_Unit2_Label[nGroupIndex]->setText(_T("A"));
// 		m_pGroup_HBoxLayout[nGroupIndex]->addWidget(m_pCT_Unit2_Label[nGroupIndex]);
// 	}

//	m_pAll_VBoxLayout->addStretch();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	InitDatas();
}

void QWeakSetWidget::ReleaseUI()
{

}

void QWeakSetWidget::InitDatas()
{
// 	for (int nGroupIndex = 0;nGroupIndex<MAX_WEEK_GROUP_NUM;nGroupIndex++)
// 	{
// 		m_pPT_PrimValue_LineEdit[nGroupIndex]->SetValue(m_pSysParas->m_fVPrimary_Weak[nGroupIndex]);
// 		m_pPT_SecondValue_LineEdit[nGroupIndex]->SetValue(m_pSysParas->m_fVSecondary_Weak[nGroupIndex]);
// 		m_pCT_PrimValue_LineEdit[nGroupIndex]->SetValue(m_pSysParas->m_fIPrimary_Weak[nGroupIndex]);
// 		m_pCT_SecondValue_LineEdit[nGroupIndex]->SetValue(m_pSysParas->m_fISecondary_Weak[nGroupIndex]);
// 	}
}

void QWeakSetWidget::SaveDatas()
{
// 	for (int nGroupIndex = 0;nGroupIndex<MAX_WEEK_GROUP_NUM;nGroupIndex++)
// 	{
// 		m_pSysParas->m_fVPrimary_Weak[nGroupIndex] = m_pPT_PrimValue_LineEdit[nGroupIndex]->GetValue();
// 		m_pSysParas->m_fVSecondary_Weak[nGroupIndex] = m_pPT_SecondValue_LineEdit[nGroupIndex]->GetValue();
// 		m_pSysParas->m_fIPrimary_Weak[nGroupIndex] = m_pCT_PrimValue_LineEdit[nGroupIndex]->GetValue();
// 		m_pSysParas->m_fISecondary_Weak[nGroupIndex] = m_pCT_SecondValue_LineEdit[nGroupIndex]->GetValue();
// 	}
}
