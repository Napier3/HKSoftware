#include "SwitchConfigDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "..\..\..\..\..\Module\Log\LogPrint.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

CSwitchConfigDlg::CSwitchConfigDlg(tmt_BinaryConfig *pBinaryCfg,int nBinInNum,int nBinOutNum,QWidget *pParent):QDialog(pParent)
{
	m_pBinInGroup = NULL;
	m_pBinOutGroup = NULL;
	m_pRadioLogicAnd = NULL;
	m_pRadioLogicOr = NULL;

	m_pBinaryConfig = pBinaryCfg;

	m_nBinInNum = min(nBinInNum,MAX_BINARYIN_COUNT);
	m_nBinOutNum = min(nBinOutNum,MAX_BINARYOUT_COUNT);

	initUI(); 
}

CSwitchConfigDlg::~CSwitchConfigDlg()
{

}

void CSwitchConfigDlg::initUI()
{
	CString strName;

	QHBoxLayout *pHLay1 = new QHBoxLayout;
	QVBoxLayout *pVLay = NULL;
	QCheckBox *pCheckBox = NULL;

	if (m_nBinInNum > 0)
	{
		m_pBinInGroup = new QGroupBox(/*tr("开入量设置")*/g_sLangTxt_Native_InputSet);
		pVLay = new QVBoxLayout();

		char arrBinIn[MAX_BINARYIN_COUNT] ="ABCDEFGHIJKLMNOPQ";
		for (int i=0; i<m_nBinInNum; i++)
		{
			CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
			CString str2;
			str2.Format(_T("%c"),arrBinIn[i]);

			strName = str1 + str2;
			pCheckBox = new QCheckBox(strName);
			if(m_pBinaryConfig)
			{
				pCheckBox->setChecked(m_pBinaryConfig->m_binIn[i].nSelect==1);
			}
			pVLay->addWidget(pCheckBox);
			m_BinInCheckList.append(pCheckBox);
		}

		m_pRadioLogicAnd = new QRadioButton(/*tr("逻辑与")*/g_sLangTxt_Native_LogicAnd);
		if(m_pBinaryConfig)
		{
			m_pRadioLogicAnd->setChecked(m_pBinaryConfig->m_nBinLogic==1);
		}
		pVLay->addWidget(m_pRadioLogicAnd);

		m_pRadioLogicOr = new QRadioButton(/*tr("逻辑或")*/g_sLangTxt_Native_LogicOr);
		m_pRadioLogicOr->setChecked(m_pBinaryConfig->m_nBinLogic==0);
		pVLay->addWidget(m_pRadioLogicOr);

		connect(m_pRadioLogicAnd, SIGNAL(clicked()), this, SLOT(slot_RadioLogicAndClicked()));
		connect(m_pRadioLogicOr, SIGNAL(clicked()), this, SLOT(slot_RadioLogicOrClicked()));

		pVLay->addStretch();
		m_pBinInGroup->setLayout(pVLay);
		pHLay1->addWidget(m_pBinInGroup);
	}
	
	if (m_nBinOutNum > 0)
	{
		m_pBinOutGroup = new QGroupBox(/*tr("开出量设置")*/g_sLangTxt_Gradient_BoutSet);
		pVLay = new QVBoxLayout;

		for (int i=0; i<m_nBinOutNum; i++)
		{
			CString str1 =/* _T("开出")*/g_sLangTxt_Native_BoutX;
			CString str2;
			str2.Format(_T("%d"),i+1);

			strName = str1 + str2;
			pCheckBox = new QCheckBox(strName);
			if(m_pBinaryConfig)
			{
				pCheckBox->setChecked(m_pBinaryConfig->m_binOut[i].nState==1);
			}
			pVLay->addWidget(pCheckBox);
			m_BinOutCheckList.append(pCheckBox);
		}
		
		pVLay->addStretch();
		m_pBinOutGroup->setLayout(pVLay);
		pHLay1->addWidget(m_pBinOutGroup);
	}

	m_pbtnOK = new QPushButton(/*tr("确定")*/g_sLangTxt_OK);
	m_pbtnCancel = new QPushButton(/*tr("取消")*/g_sLangTxt_Cancel);
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addStretch();
	pHLay2->addWidget(m_pbtnOK);
	pHLay2->addWidget(m_pbtnCancel);
	pHLay2->addStretch();

	QVBoxLayout *pMainLay = new QVBoxLayout;
	pMainLay->addLayout(pHLay1);
	pMainLay->addLayout(pHLay2);
	setLayout(pMainLay); //设置为窗体的主布局

	setWindowTitle(/*tr("开关量设置")*/g_sLangTxt_Native_Switch);

	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void CSwitchConfigDlg::slot_OKClicked()
{
	for (int i=0; i<m_BinInCheckList.size(); i++)
	{
		if (m_BinInCheckList.at(i)->isChecked())
		{
			m_pBinaryConfig->m_binIn[i].nSelect = 1;
		}
		else
		{
			m_pBinaryConfig->m_binIn[i].nSelect = 0;
		}
	}

	for (int i=0; i<m_BinOutCheckList.size(); i++)
	{
		if (m_BinOutCheckList.at(i)->isChecked())
		{
			m_pBinaryConfig->m_binOut[i].nState = 1;
		}
		else
		{
			m_pBinaryConfig->m_binOut[i].nState = 0;
		}
	}

	emit sig_SwitchCfgOK(m_pBinaryConfig);

	close();
}

void CSwitchConfigDlg::slot_CancelClicked()
{
	close();
}

void CSwitchConfigDlg::slot_RadioLogicAndClicked()
{
	m_pRadioLogicAnd->setChecked(true);
	m_pRadioLogicOr->setChecked(false);
	m_pBinaryConfig->m_nBinLogic = 1;
}

void CSwitchConfigDlg::slot_RadioLogicOrClicked()
{
	m_pRadioLogicAnd->setChecked(false);
	m_pRadioLogicOr->setChecked(true);
	m_pBinaryConfig->m_nBinLogic = 0;
}

void CSwitchConfigDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{

	}
}