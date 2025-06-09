#include "RemoteMeasRatWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "SttMacroParaEditViewRemoteMeas.h"
#include "../SttTestCntrFrameBase.h"

QRemoteMeasRatWidget::QRemoteMeasRatWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pSelect_ComboBox = NULL;
	m_pVolt1_LineEdit = NULL;
	m_pVolt2_LineEdit = NULL;
	m_pCurr1_LineEdit = NULL;
	m_pCurr2_LineEdit = NULL;
	m_pZeroVolt1_LineEdit = NULL;
	m_pZeroVolt2_LineEdit = NULL;
	m_pZeroCurr1_LineEdit = NULL;
	m_pZeroCurr2_LineEdit = NULL;

	m_fPrimVolValue = 10;
	m_fSecondVolValue = 0.1;
	m_fPrimCurValue = 600;
	m_fSecondCurValue = 5;
	m_fPrimVZeroValue = 10;
	m_fSecondVZeroValue = 0.1;//chenling2024.04.29 默认设置0.1
	m_fPrimCZeroValue = 100;
	m_fSecondCZeroValue = 1;

	initUI();
	SetFont();
}

QRemoteMeasRatWidget::~QRemoteMeasRatWidget()
{
	DeleteAinInterDatas();
}

void QRemoteMeasRatWidget::DeleteAinInterDatas()
{
	CExBaseList *pChildList = NULL;
	POS pos = m_oAinInterDatasRef.GetHeadPosition();

	while(pos)
	{
		pChildList = (CExBaseList *)m_oAinInterDatasRef.GetNext(pos);
		pChildList->RemoveAll();
	}

	m_oAinInterDatasRef.DeleteAll();
}

void QRemoteMeasRatWidget::SetFont()
{
	m_pSelect->setFont(*g_pSttGlobalFont);
	m_pSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pVoltRatio_Label->setFont(*g_pSttGlobalFont);
	m_pVolt1_LineEdit->setFont(*g_pSttGlobalFont);
	m_pLabel1->setFont(*g_pSttGlobalFont);
	m_pVolt2_LineEdit->setFont(*g_pSttGlobalFont);
	m_pCurrRatio_Label->setFont(*g_pSttGlobalFont);
	m_pCurr1_LineEdit->setFont(*g_pSttGlobalFont);
	m_pLabel2->setFont(*g_pSttGlobalFont);
	m_pCurr2_LineEdit->setFont(*g_pSttGlobalFont);
	m_pZeroVoltRatio_Label->setFont(*g_pSttGlobalFont);
	m_pZeroVolt1_LineEdit->setFont(*g_pSttGlobalFont);
	m_pLabel3->setFont(*g_pSttGlobalFont);
	m_pZeroVolt2_LineEdit->setFont(*g_pSttGlobalFont);
	m_pZeroCurrRatio_Label->setFont(*g_pSttGlobalFont);
	m_pZeroCurr1_LineEdit->setFont(*g_pSttGlobalFont);
	m_pLabel4->setFont(*g_pSttGlobalFont);
	m_pZeroCurr2_LineEdit->setFont(*g_pSttGlobalFont);

#ifndef _PSX_QT_WINDOWS_
	QFont font;
	font.setPixelSize(15);
	font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	m_pSelect->setFont(font);
	m_pSelect_ComboBox->setFont(font);
	m_pVoltRatio_Label->setFont(font);
	m_pVolt1_LineEdit->setFont(font);
	m_pLabel1->setFont(font);
	m_pVolt2_LineEdit->setFont(font);
	m_pCurrRatio_Label->setFont(font);
	m_pCurr1_LineEdit->setFont(font);
	m_pLabel2->setFont(font);
	m_pCurr2_LineEdit->setFont(font);
	m_pZeroVoltRatio_Label->setFont(font);
	m_pZeroVolt1_LineEdit->setFont(font);
	m_pLabel3->setFont(font);
	m_pZeroVolt2_LineEdit->setFont(font);
	m_pZeroCurrRatio_Label->setFont(font);
	m_pZeroCurr1_LineEdit->setFont(font);
	m_pLabel4->setFont(font);
	m_pZeroCurr2_LineEdit->setFont(font);
#endif

}

void QRemoteMeasRatWidget::initUI()
{
	CString strText;
	strText = _T("间隔选择");
	m_pSelect=new QLabel(this);
	m_pSelect->setText(strText);
	m_pSelect_ComboBox = new CExBaseListComboBox(this);
	strText = _T("相电压比");
	m_pVoltRatio_Label=new QLabel(this);
	m_pVoltRatio_Label->setText(strText);
	m_pVolt1_LineEdit = new QSttLineEdit(this);
	m_pLabel1 = new QLabel("/");
	m_pVolt2_LineEdit = new QSttLineEdit(this);
	strText = _T("相电流比");
	m_pCurrRatio_Label=new QLabel(this);
	m_pCurrRatio_Label->setText(strText);
	m_pCurr1_LineEdit = new QSttLineEdit(this);
	m_pLabel2 = new QLabel("/");
	m_pCurr2_LineEdit = new QSttLineEdit(this);
	strText = _T("零序电压比");
	m_pZeroVoltRatio_Label=new QLabel(this);
	m_pZeroVoltRatio_Label->setText(strText);
	m_pZeroVolt1_LineEdit = new QSttLineEdit(this);
	m_pLabel3 = new QLabel("/");
	m_pZeroVolt2_LineEdit = new QSttLineEdit(this);
	strText = _T("零序电流比");
	m_pZeroCurrRatio_Label=new QLabel(this);
	m_pZeroCurrRatio_Label->setText(strText);
	m_pZeroCurr1_LineEdit = new QSttLineEdit(this);
	m_pLabel4 = new QLabel("/");
	m_pZeroCurr2_LineEdit = new QSttLineEdit(this);

	QBoxLayout* pLayout = NULL;
	pLayout = new QHBoxLayout;
	pLayout->addWidget(m_pSelect);
	pLayout->addWidget(m_pSelect_ComboBox);
	pLayout->addWidget(m_pVoltRatio_Label);
	pLayout->addWidget(m_pVolt1_LineEdit);
	pLayout->addWidget(m_pLabel1);
	pLayout->addWidget(m_pVolt2_LineEdit);
	pLayout->addWidget(m_pCurrRatio_Label);
	pLayout->addWidget(m_pCurr1_LineEdit);
	pLayout->addWidget(m_pLabel2);
	pLayout->addWidget(m_pCurr2_LineEdit);
	pLayout->addWidget(m_pZeroVoltRatio_Label);
	pLayout->addWidget(m_pZeroVolt1_LineEdit);
	pLayout->addWidget(m_pLabel3);
	pLayout->addWidget(m_pZeroVolt2_LineEdit);
	pLayout->addWidget(m_pZeroCurrRatio_Label);
	pLayout->addWidget(m_pZeroCurr1_LineEdit);
	pLayout->addWidget(m_pLabel4);
	pLayout->addWidget(m_pZeroCurr2_LineEdit);
	pLayout->setSpacing(0);

	m_pVLayout = new QVBoxLayout();
	m_pUIParaWidget = new RemoteMeasParaSet();
	m_pVLayout->addLayout(pLayout);
	m_pVLayout->addWidget(m_pUIParaWidget);
	m_pVLayout->setContentsMargins(3, 0, 3, 0); 
	m_pVLayout->setSpacing(0);

	setLayout(m_pVLayout);	
}

void QRemoteMeasRatWidget::setData(tmt_ManualParas* pManualParas)
{
	m_pManualParas = pManualParas;
	initBaseData();
}

void QRemoteMeasRatWidget::initBaseData()
{
	if(m_pManualParas == NULL)
	{
		return;
	}

	initInterSelectData();
	//保留两位小数
	m_pVolt1_LineEdit->setText(QString::number(m_fPrimVolValue,'f',2)+"kV");
	m_pVolt2_LineEdit->setText(QString::number(m_fSecondVolValue,'f',2)+"kV");
	m_pCurr1_LineEdit->setText(QString::number(m_fPrimCurValue,'f',2)+"A");
	m_pCurr2_LineEdit->setText(QString::number(m_fSecondCurValue,'f',2)+"A");
	m_pZeroVolt1_LineEdit->setText(QString::number(m_fPrimVZeroValue,'f',2)+"kV");
	m_pZeroVolt2_LineEdit->setText(QString::number(m_fSecondVZeroValue,'f',2)+"kV");
	m_pZeroCurr1_LineEdit->setText(QString::number(m_fPrimCZeroValue,'f',2)+"A");
	m_pZeroCurr2_LineEdit->setText(QString::number(m_fSecondCZeroValue,'f',2)+"A");
}

void QRemoteMeasRatWidget::initInterSelectData()
{
	DeleteAinInterDatas();

	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		g_theTestCntrFrame->CreateEngineClientWidget();
	}


	CDvmDevice* pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;

	if (pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDvmDatasetRef = NULL,*pCurrDataset = NULL;

	POS pos = pDvmDevice->GetHeadPosition();
	CExBaseList *pCurObj = NULL;

	while(pos)
	{
		pCurObj = (CExBaseList*)pDvmDevice->GetNext(pos);	

		if (pCurObj->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		if (pCurObj->m_strID == _T("report"))
		{
			continue;
		}

		pDvmDatasetRef = new CDvmDataset;
		m_oAinInterDatasRef.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();
		long nIndex = 0;

		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID.Find(STT_RemoteMeas_Dataset_ID) >= 0)
			{
				pDvmDatasetRef->Append(*pCurrDataset);

				if (nIndex == 0)//将对应的ID设置为第一个遥测数据集的路径,方便后续从装置读取遥测数据
				{
					pDvmDatasetRef->m_strID.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
				}
				nIndex++;
			}
		}
	}

	m_pSelect_ComboBox->ShowBaseList(&m_oAinInterDatasRef);
}

void QRemoteMeasRatWidget::startInit()
{
	setEnabled(false);
	m_pSelect_ComboBox->setDisabled(true);
	m_pVolt1_LineEdit->setDisabled(true);
	m_pVolt2_LineEdit->setDisabled(true);
	m_pCurr1_LineEdit->setDisabled(true);
	m_pCurr2_LineEdit->setDisabled(true);
	m_pZeroVolt1_LineEdit->setDisabled(true);
	m_pZeroVolt2_LineEdit->setDisabled(true);
	m_pZeroCurr1_LineEdit->setDisabled(true);
	m_pZeroCurr2_LineEdit->setDisabled(true);
}

void QRemoteMeasRatWidget::stopInit(BOOL bHasPasteState)
{
	setEnabled(true);

 	m_pSelect_ComboBox->setDisabled(false);
 	m_pVolt1_LineEdit->setDisabled(false);
	m_pVolt2_LineEdit->setDisabled(false);
	m_pCurr1_LineEdit->setDisabled(false);
	m_pCurr2_LineEdit->setDisabled(false);
	m_pZeroVolt1_LineEdit->setDisabled(false);
	m_pZeroVolt2_LineEdit->setDisabled(false);
	m_pZeroCurr1_LineEdit->setDisabled(false);
	m_pZeroCurr2_LineEdit->setDisabled(false);
}

// void QRemoteMeasRatWidget::UpdateStateCombox()
// {
// 	initBaseData();
// }

void QRemoteMeasRatWidget::slot_lne_Volt1Changed()
{
	CString strText = m_pVolt1_LineEdit->text(); //chenling 20240307 变比修改不成功

	int nIndex = strText.Find(_T("kV"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pVolt1_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fPrimVolValue != fv)
	{
		m_fPrimVolValue = fv;
	}

	m_pVolt1_LineEdit->setText(QString::number(fv,'f',2)+"kV");
}

void QRemoteMeasRatWidget::slot_lne_Volt2Changed()
{
	CString strText = m_pVolt2_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("kV"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pVolt2_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fSecondVolValue != fv)
	{
		m_fSecondVolValue = fv;
	}

	m_pVolt2_LineEdit->setText(QString::number(fv,'f',2)+"kV");
}

void QRemoteMeasRatWidget::slot_lne_Curr1Changed()
{
	CString strText = m_pCurr1_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("A"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pCurr1_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fPrimCurValue != fv)
	{
		m_fPrimCurValue = fv;
	}

	m_pCurr1_LineEdit->setText(QString::number(fv,'f',2)+"A");
}

void QRemoteMeasRatWidget::slot_lne_Curr2Changed()
{
	CString strText = m_pCurr2_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("A"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pCurr2_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fSecondCurValue != fv)
	{
		m_fSecondCurValue = fv;
	}

	m_pCurr2_LineEdit->setText(QString::number(fv,'f',2)+"A");
}

void QRemoteMeasRatWidget::slot_lne_ZeroVolt1Changed()
{
	CString strText = m_pZeroVolt1_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("kV"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pZeroVolt1_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fPrimVZeroValue != fv)
	{
		m_fPrimVZeroValue = fv;
	}

	m_pZeroVolt1_LineEdit->setText(QString::number(fv,'f',2)+"kV");
}

void QRemoteMeasRatWidget::slot_lne_ZeroVolt2Changed()
{
	CString strText = m_pZeroVolt2_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("kV"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pZeroVolt2_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fSecondVZeroValue != fv)
	{
		m_fSecondVZeroValue = fv;
	}

	m_pZeroVolt2_LineEdit->setText(QString::number(fv,'f',2)+"kV");
}

void QRemoteMeasRatWidget::slot_lne_ZeroCurr1Changed()
{
	CString strText = m_pZeroCurr1_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("A"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pZeroCurr1_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fPrimCZeroValue != fv)
	{
		m_fPrimCZeroValue = fv;
	}

	m_pZeroCurr1_LineEdit->setText(QString::number(fv,'f',2)+"A");
}

void QRemoteMeasRatWidget::slot_lne_ZeroCurr2Changed()
{
	CString strText = m_pZeroCurr2_LineEdit->text(); //chenling 20240307 变比修改不成功
	int nIndex = strText.Find(_T("A"));
	if (nIndex >= 0)
	{
		strText = strText.Left(nIndex);
	}

	float fv = strText.toFloat();
	//float fv = m_pZeroCurr2_LineEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);

	if (m_fSecondCZeroValue != fv)
	{
		m_fSecondCZeroValue = fv;
	}

	m_pZeroCurr2_LineEdit->setText(QString::number(fv,'f',2)+"A");
}