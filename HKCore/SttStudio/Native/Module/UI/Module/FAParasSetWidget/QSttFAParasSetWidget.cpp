#include "QSttFAParasSetWidget.h"
#include "ui_QSttFAParasSetWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../../../Module/SttGlobalDef.h"
#include <QComboBox>
#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

QSttFAParasSetWidget::QSttFAParasSetWidget(QWidget *parent) : 
ui(new Ui::QSttFAParasSetWidget)
{
	ui->setupUi(this);
	m_bRemoteMonitor = TRUE;

	InitUI();
	SetFAParasFont();
	InitConnections();
}


QSttFAParasSetWidget::~QSttFAParasSetWidget()
{
	//DeleteIntervalListDatas();
}

void QSttFAParasSetWidget::InitUI()
{
 	ui->m_editRatedVol->setDisabled(true);
 	ui->m_editRatedCur->setDisabled(true);

 	if (g_nBinCount > MAX_BINARYIN_COUNT)
 	{
 		g_nBinCount = MAX_BINARYIN_COUNT;
 	}

	QString strBinName;
	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBinName = g_sLangTxt_Manual_InA;
		}
		else if (i == 1)
		{
			strBinName = g_sLangTxt_Manual_InB;
		}
		else if (i == 2)
		{
			strBinName= g_sLangTxt_Manual_InC;
		}
		else if (i == 3)
		{
			strBinName = g_sLangTxt_Manual_InD;
		}
		else
		{
			break;
		}

		ui->m_cmbTermCloseOutput->addItem(strBinName);
		ui->m_cmbTermOpenOutput->addItem(strBinName);
		m_pOutputItem << strBinName;

	}

	if (g_nBinCount > MAX_BINARYIN_COUNT)
	{
		g_nBinCount = MAX_BINARYIN_COUNT;
	}

	QString strBin0Name;
	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBin0Name = g_sLangTxt_Manual_Out1;
		}
		else if (i == 1)
		{
			strBin0Name = g_sLangTxt_Manual_Out2;
		}
		else if (i == 2)
		{
			strBin0Name = g_sLangTxt_Manual_Out3;
		}
		else if (i == 3)
		{
			strBin0Name = g_sLangTxt_Manual_Out4;
		}
		else if (i == 4)
		{
			strBin0Name = g_sLangTxt_Manual_Out5;
		}
		else if (i == 5)
		{
			strBin0Name = g_sLangTxt_Manual_Out6;
		}
		else if (i == 6)
		{
			strBin0Name = g_sLangTxt_Manual_Out7;
		}
		else if (i == 7)
		{
			strBin0Name = g_sLangTxt_Manual_Out8;
		}
		else
		{
			break;
		}
		ui->m_cmbTermCloseSignal->addItem(strBin0Name);
		ui->m_cmbTermQuantileSignal->addItem(strBin0Name);
		m_pSignalItem << strBin0Name;
	}
}

void QSttFAParasSetWidget::InitData(CDataGroup *pParas)
{
	m_pParas = pParas;
	//InitIntervalListDatas();

	float fValue;
	m_pParas->SetDataValue(_T("NormVol"), g_oSystemParas.m_fVNom);
	ui->m_editRatedVol->setText(QString::number(g_oSystemParas.m_fVNom, 'f', 3) + "V"); 
	
	m_pParas->SetDataValue(_T("NormCur"), g_oSystemParas.m_fINom);
	ui->m_editRatedCur->setText(QString::number(g_oSystemParas.m_fINom, 'f', 3) + "A");

	stt_GetDataValueByID(m_pParas, _T("TimeAbsError"), fValue);
	ui->m_editErrorTime->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("XTime"), fValue);
	ui->m_editxTime->setText(QString::number(fValue, 'f', 3) + "s");
	
	stt_GetDataValueByID(m_pParas, _T("YTime"), fValue);
	ui->m_edityTime->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("ZTime"), fValue);
	ui->m_editzTime->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("XLTime"), fValue);
	ui->m_editxlTime->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("X2Time"), fValue);
	ui->m_editX2Time->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("STime"), fValue);
	ui->m_editsTime->setText(QString::number(fValue, 'f', 3) + "s");

	stt_GetDataValueByID(m_pParas, _T("ResidualVoltage"), fValue);
	ui->m_editVol->setText(QString::number(fValue, 'f', 3) + "V");

	stt_GetDataValueByID(m_pParas, _T("FaultCurrent"), fValue);
	ui->m_editCur->setText(QString::number(fValue, 'f', 3) + "A");

	stt_GetDataValueByID(m_pParas, _T("FaultCurrentDuration"), fValue);
	ui->m_editCurHoldTime->setText(QString::number(fValue, 'f', 3) + "s");



	disconnect(ui->m_cmbTermCloseOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseOutputIndexChanged(int)));
	disconnect(ui->m_cmbTermOpenOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermOpenOutputIndexChanged(int)));
	disconnect(ui->m_cmbTermCloseSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseSignalIndexChanged(int)));
	disconnect(ui->m_cmbTermQuantileSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermQuantileSignalIndexChanged(int)));

	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(m_pParas, strID, strValue);

		if (m_bRemoteMonitor)
		{
			if (strValue == _T("Din_1") || strValue == _T("1"))
			{
				m_pParas->SetDataValue(strID, _T("Din_1"));  
			}
			else if (strValue == _T("Din_2") || strValue == _T("0"))
			{
				m_pParas->SetDataValue(strID, _T("Din_2"));
			}
			else if (strValue == _T("Din_5") || strValue == _T("2"))
			{
				m_pParas->SetDataValue(strID, _T("Din_5"));
			}
			else
			{
				m_pParas->SetDataValue(strID, _T(""));  
			}
		}
		else
		{
			if (strValue == _T("Din_1") || strValue == _T("1"))
			{
				m_pParas->SetDataValue(strID, _T("1"));  
			}
			else if (strValue == _T("Din_2") || strValue == _T("0"))
			{
				m_pParas->SetDataValue(strID, _T("0"));
			}
			else if (strValue == _T("Din_5") || strValue == _T("2"))
			{
				m_pParas->SetDataValue(strID, _T("2"));
			}
			else
			{
				m_pParas->SetDataValue(strID, _T("3"));  
			}
		}

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			ui->m_cmbTermCloseSignal->setCurrentIndex(i);
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			ui->m_cmbTermQuantileSignal->setCurrentIndex(i);
		}
	}

	for (int i = 0; i < 4 ;i++)
	{
		strID.Format(_T("Bin%c"), 'A' + i);
		stt_GetDataValueByID(m_pParas, strID, strValue);

		if (strValue == _T("0"))
		{
			ui->m_cmbTermCloseOutput->setCurrentIndex(i);
		}
		else if (strValue == _T("1"))
		{
			ui->m_cmbTermOpenOutput->setCurrentIndex(i);
		}
	}


// 	CString strDatasetpath;
// 	stt_GetDataValueByID(m_pParas, _T("datasetpath"), strDatasetpath);
// 	int pos1 = strDatasetpath.Find(_T('$'));
// 	if (pos1 != -1) 
// 	{
// 		strDatasetpath = strDatasetpath.Left(pos1);
// 		TCHAR lastChar= strDatasetpath.GetAt(strDatasetpath.GetLength() - 1);
// 		CString strLastChar;
// 		strLastChar.Format(_T("%c"), lastChar);
// 		long nIndex = CString_To_long(strLastChar);
// 		ui->m_cmbInterSelect->ShowBaseList(&m_IntervalList);
// 		ui->m_cmbInterSelect->setCurrentIndex(nIndex-1);
// 	}
// 
// 	if (m_bRemoteMonitor)
// 	{
// 		ui->m_cmbInterSelect->show();
// 		ui->m_labInterSelect->show();
// 	}
// 	else
// 	{
// 		ui->m_cmbInterSelect->hide();
// 		ui->m_labInterSelect->hide();
// 	}


	slot_TermCloseOutputIndexChanged(0); 
	slot_TermOpenOutputIndexChanged(0); 
	slot_TermCloseSignalIndexChanged(0);
	slot_TermQuantileSignalIndexChanged(0);


	connect(ui->m_cmbTermCloseOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseOutputIndexChanged(int)));
	connect(ui->m_cmbTermOpenOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermOpenOutputIndexChanged(int)));
	connect(ui->m_cmbTermCloseSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseSignalIndexChanged(int)));
	connect(ui->m_cmbTermQuantileSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermQuantileSignalIndexChanged(int)));
}

 void QSttFAParasSetWidget::InitIntervalListDatas()
 {
 	//DeleteIntervalListDatas();
 
 	CDvmDevice* pDvmDevice = NULL;
 #ifdef _PSX_QT_WINDOWS_
 	pDvmDevice = g_theGbSmartGenWzd->m_pDvmDevice ;
 #else
 	pDvmDevice = g_pTheSttTestApp->m_pDvmDevice;
 #endif
 
 	if (pDvmDevice == NULL)
 	{
 		m_bRemoteMonitor = FALSE;
 		return;
 	}
 
 	m_bRemoteMonitor = TRUE;
 
//  	CDvmDataset *pDvmDatasetRef = NULL,*pCurrDataset = NULL;
//  	CDvmData*pCurrDvmData = NULL;
//  	CExBaseList *pCurObj = NULL;
//  
//  	POS pos = pDvmDevice->GetHeadPosition();
//  	while(pos)
//  	{
//  		pCurObj = (CExBaseList*)pDvmDevice->GetNext(pos);	
//  
//  		if (pCurObj->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
//  		{
//  			continue;
//  		}
//  
//  		if (pCurObj->m_strID == _T("report") || pCurObj->m_strID == _T("CommMessage"))
//  		{
//  			continue;
//  		}
//  
//  		pDvmDatasetRef = new CDvmDataset;
//  		m_IntervalList.AddNewChild(pDvmDatasetRef);
//  		pDvmDatasetRef->m_strName = pCurObj->m_strName;
//  		pDvmDatasetRef->m_strID = pCurObj->m_strID;
//  
//  		POS pos_dataset = pCurObj->GetHeadPosition();
//  		while(pos_dataset)
//  		{
//  			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);
//  
//  			if (pCurrDataset->m_strID == _T("dsDin"))
//  			{
//  				pDvmDatasetRef->m_strDataType.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
//  
//  				POS pos_data = pCurrDataset->GetHeadPosition();
//  				while(pos_data)
//  				{
//  					pCurrDvmData = (CDvmData *)pCurrDataset->GetNext(pos_data);
//  					if (pCurrDvmData == NULL)
//  					{
//  						continue;
//  					}
//  					if (pCurrDvmData->m_strID == _T("Din_1") || pCurrDvmData->m_strID == _T("Din_2") || pCurrDvmData->m_strID == _T("Din_5"))
//  					{
//  						pDvmDatasetRef->AddNewChild(pCurrDvmData);
//  					}
//  				}
//  			}
//  		}
//  	}
 }

void QSttFAParasSetWidget::SetFAParasFont()
{
	ui->m_editRatedVol->setFont(*g_pSttGlobalFont);
	ui->m_editRatedCur->setFont(*g_pSttGlobalFont);
	ui->m_editErrorTime->setFont(*g_pSttGlobalFont);
	ui->m_editxTime->setFont(*g_pSttGlobalFont);
	ui->m_edityTime->setFont(*g_pSttGlobalFont);
	ui->m_editzTime->setFont(*g_pSttGlobalFont);
	ui->m_editxlTime->setFont(*g_pSttGlobalFont);
	ui->m_editsTime->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermCloseOutput->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermOpenOutput->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermCloseSignal->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermQuantileSignal->setFont(*g_pSttGlobalFont);
	ui->m_labRatedVol->setFont(*g_pSttGlobalFont);
	ui->m_labRatedCur->setFont(*g_pSttGlobalFont);
	ui->m_labErrorTime->setFont(*g_pSttGlobalFont);
	ui->m_labTermCloseOutput->setFont(*g_pSttGlobalFont);
	ui->m_labTermOpenOutput->setFont(*g_pSttGlobalFont);
	ui->m_labTermCloseSignal->setFont(*g_pSttGlobalFont);
	ui->m_labTermQuantileSignal->setFont(*g_pSttGlobalFont);
	ui->m_labxTime->setFont(*g_pSttGlobalFont);
	ui->m_labyTime->setFont(*g_pSttGlobalFont);
	ui->m_labzTime->setFont(*g_pSttGlobalFont);
	ui->m_labxlTime->setFont(*g_pSttGlobalFont);
	ui->m_labsTime->setFont(*g_pSttGlobalFont);
	ui->m_labX2Time->setFont(*g_pSttGlobalFont);
	ui->m_editX2Time->setFont(*g_pSttGlobalFont);
// 	ui->m_labInterSelect->setFont(*g_pSttGlobalFont);
// 	ui->m_cmbInterSelect->setFont(*g_pSttGlobalFont);

	ui->label->setFont(*g_pSttGlobalFont);
	ui->label_2->setFont(*g_pSttGlobalFont);
	ui->label_3->setFont(*g_pSttGlobalFont);
	ui->m_editVol->setFont(*g_pSttGlobalFont);
	ui->m_editCur->setFont(*g_pSttGlobalFont);
	ui->m_editCurHoldTime->setFont(*g_pSttGlobalFont);
}

void QSttFAParasSetWidget::InitConnections()
{
	connect(ui->m_editErrorTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editErrorTime()));
	connect(ui->m_editxTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editxTime()));
	connect(ui->m_edityTime, SIGNAL(editingFinished()), this, SLOT(slot_m_edityTime()));
	connect(ui->m_editzTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editzTime()));
	connect(ui->m_editxlTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editxlTime()));
	connect(ui->m_editsTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editsTime()));
	connect(ui->m_editX2Time, SIGNAL(editingFinished()), this, SLOT(slot_m_editx2Time()));
	connect(ui->m_editVol, SIGNAL(editingFinished()), this, SLOT(slot_m_editVol()));
	connect(ui->m_editCur, SIGNAL(editingFinished()), this, SLOT(slot_m_editFaultCur()));
	connect(ui->m_editCurHoldTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editFaultHoldTime()));


	//开入
	connect(ui->m_cmbTermCloseOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseOutputIndexChanged(int)));
	connect(ui->m_cmbTermOpenOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermOpenOutputIndexChanged(int)));

	//开出
	connect(ui->m_cmbTermCloseSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseSignalIndexChanged(int)));
	connect(ui->m_cmbTermQuantileSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermQuantileSignalIndexChanged(int)));
	//connect(ui->m_cmbInterSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
}

void QSttFAParasSetWidget::slot_TermCloseOutputIndexChanged(int index) 
{
	if (index < 0)
	{
		return;
	}	
	CString strText = ui->m_cmbTermCloseOutput->currentText();
	UpdateOpenCloseCombox(ui->m_cmbTermOpenOutput,m_pOutputItem,strText);
}

void QSttFAParasSetWidget::slot_TermOpenOutputIndexChanged(int index) 
{
	if (index < 0)
	{
		return;
	}	
	CString strText = ui->m_cmbTermOpenOutput->currentText();
	UpdateOpenCloseCombox(ui->m_cmbTermCloseOutput,m_pOutputItem,strText);
}

void QSttFAParasSetWidget::slot_TermCloseSignalIndexChanged(int index)
{
	if (index < 0)
	{
		return;
	}
 
	CString strText = ui->m_cmbTermCloseSignal->currentText();
	UpdateOpenCloseCombox(ui->m_cmbTermQuantileSignal,m_pSignalItem,strText);
}

void QSttFAParasSetWidget::slot_TermQuantileSignalIndexChanged(int index)
{
	if (index < 0)
	{
		return;
	}

	CString strText = ui->m_cmbTermQuantileSignal->currentText();
	UpdateOpenCloseCombox(ui->m_cmbTermCloseSignal,m_pSignalItem,strText);
}

void QSttFAParasSetWidget::SaveBoutDataValue(CString strText, const CString& strDinValue)
{
	int nValue = strText.Right(1).toInt();  
	CString strID;

	for (int i = 0; i < 8; ++i)
	{			
		strID.Format(_T("Bout%d"), i + 1);  
		if (nValue == (i + 1))
		{
			m_pParas->SetDataValue(strID, strDinValue);  
		}
	}
}

void QSttFAParasSetWidget::SaveBinDataValue( CString strText, const CString& strValue)
{
	CString strID;
	for (int i = 0; i < 4; ++i)
	{
		strID.Format(_T("Bin%c"), 'A' + i);

		if (strID.Right(1) == strText.Right(1))
		{
			m_pParas->SetDataValue(strID, strValue);
		}
	}
}

void QSttFAParasSetWidget::DeleteIntervalListDatas()
{
// 	CExBaseList *pChildList = NULL;
// 	POS pos = m_IntervalList.GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pChildList = (CExBaseList *)m_IntervalList.GetNext(pos);
// 		pChildList->RemoveAll();
// 	}
// 
// 	m_IntervalList.DeleteAll();
}

void QSttFAParasSetWidget::SaveData()
{
	CString strID,strValue;
	for (int i = 0; i < 8; ++i)
	{			
		strID.Format(_T("Bout%d"), i + 1);  
		stt_GetDataValueByID(m_pParas, strID, strValue);
		if (strValue == _T("Din_5") || strValue == _T("2"))//未储能不处理
		{
			continue;
		}

		if (m_bRemoteMonitor)
		{
			m_pParas->SetDataValue(strID, _T(""));
		}
		else
		{
			m_pParas->SetDataValue(strID, _T("3"));
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		strID.Format(_T("Bin%c"), 'A' + i);
		m_pParas->SetDataValue(strID, _T("2"));  
	}

	CString strCloseSignal,strQuantileSignal;
	if (m_bRemoteMonitor)
	{
		strCloseSignal = _T("Din_1");
		strQuantileSignal = _T("Din_2");
	}
	else
	{
		strCloseSignal = _T("1");
		strQuantileSignal = _T("0");
	}

	SaveBoutDataValue(ui->m_cmbTermCloseSignal->currentText(),strCloseSignal);
	SaveBoutDataValue(ui->m_cmbTermQuantileSignal->currentText(),strQuantileSignal);
	SaveBinDataValue(ui->m_cmbTermCloseOutput->currentText(),_T("0"));
	SaveBinDataValue(ui->m_cmbTermOpenOutput->currentText(),_T("1"));

// 	CDvmDataset *pCurrDataset = (CDvmDataset*)(ui->m_cmbInterSelect->GetCurrSelObject());
// 	if (pCurrDataset)
// 	{
// 		m_pParas->SetDataValue(_T("datasetpath"),pCurrDataset->m_strDataType);
// 	}
	
	strValue = ui->m_editxTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("XTime"),strValue);
	
	strValue = ui->m_edityTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("YTime"),strValue);
	
	strValue = ui->m_editzTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("ZTime"),strValue);
	
	strValue = ui->m_editxlTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("XLTime"),strValue);

	strValue = ui->m_editX2Time->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("X2Time"),strValue);

	strValue = ui->m_editsTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("STime"),strValue);

	strValue = ui->m_editErrorTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("TimeAbsError"),strValue);


	strValue = ui->m_editVol->text();
	strValue.Replace(_T("V"), _T(""));
	m_pParas->SetDataValue(_T("ResidualVoltage"),strValue);
	strValue = ui->m_editCur->text();
	strValue.Replace(_T("A"), _T(""));
	m_pParas->SetDataValue(_T("FaultCurrent"),strValue);
	strValue = ui->m_editCurHoldTime->text();
	strValue.Replace(_T("s"), _T(""));
	m_pParas->SetDataValue(_T("FaultCurrentDuration"),strValue);

	m_pParas->SetDataValue(_T("NormVol"),g_oSystemParas.m_fVNom);
	m_pParas->SetDataValue(_T("NormCur"),g_oSystemParas.m_fINom);
}



void QSttFAParasSetWidget::UpdateOpenCloseCombox( QComboBox* pCombox, const QStringList& pItems, const QString& strText )
{
	QString currentText = pCombox->currentText();
	pCombox->blockSignals(true); 
	pCombox->clear();

	for (int i = 0; i < pItems.size(); ++i)
	{
		if (pItems[i] != strText)
		{
			pCombox->addItem(pItems[i]);

			int nIndex = pCombox->findText(currentText);
			if (nIndex != -1)
			{
				pCombox->setCurrentIndex(nIndex);
			}
		}
	}
	pCombox->blockSignals(false); 
}


// 槽函数 - m_editErrorTime
void QSttFAParasSetWidget::slot_m_editErrorTime()
{
	CString strValue = ui->m_editErrorTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();
	fv = setLimit(0,5,fv);
	ui->m_editErrorTime->setText(QString::number(fv, 'f', 3) + "s");
}

// 槽函数 - m_fxTime
void QSttFAParasSetWidget::slot_m_editxTime()
{
	CString strValue = ui->m_editxTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();
	fv = setLimit(1,10,fv);
	ui->m_editxTime->setText(QString::number(fv, 'f', 3) + "s");
}

// 槽函数 - m_fyTime
void QSttFAParasSetWidget::slot_m_edityTime()
{
	CString strValue = ui->m_edityTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();

	fv = setLimit(1,10,fv);
	ui->m_edityTime->setText(QString::number(fv, 'f', 3) + "s");
}

// 槽函数 - m_editzTime
void QSttFAParasSetWidget::slot_m_editzTime()
{
	CString strValue = ui->m_editzTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();

	fv = setLimit(1,5,fv);
	ui->m_editzTime->setText(QString::number(fv, 'f', 3) + "s");
}

// 槽函数 - m_editxlTime
void QSttFAParasSetWidget::slot_m_editxlTime()
{
	CString strValue = ui->m_editxlTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();
	fv = setLimit(20,100,fv);
	ui->m_editxlTime->setText(QString::number(fv, 'f', 3) + "s");
}

// 槽函数 - m_editsTime
void QSttFAParasSetWidget::slot_m_editsTime()
{
	CString strValue = ui->m_editsTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();

	fv = setLimit(0,0.5,fv);
	ui->m_editsTime->setText(QString::number(fv, 'f', 3) + "s");
}

void QSttFAParasSetWidget::slot_m_editx2Time()
{	
	CString strValue = ui->m_editX2Time->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();

	fv = setLimit(20,100,fv);
	ui->m_editX2Time->setText(QString::number(fv, 'f', 3) + "s");
}

void QSttFAParasSetWidget::slot_m_editVol()
{
	CString strValue = ui->m_editVol->text();
	strValue.Replace(_T("V"), _T(""));
	float fv = strValue.toFloat();

	float fVmax = g_oSystemParas.m_fVNom;
	float fVmin = fVmax *  0.3;

	fv = setLimit(fVmin,fVmax,fv);
	ui->m_editVol->setText(QString::number(fv, 'f', 3) + "V");
}

void QSttFAParasSetWidget::slot_m_editFaultCur()
{
	CString strValue = ui->m_editCur->text();
	strValue.Replace(_T("A"), _T(""));
	float fv = strValue.toFloat();

	float fImax = g_oSystemParas.m_fINom * 2;

	fv = setLimit(0,fImax,fv);
	ui->m_editCur->setText(QString::number(fv, 'f', 3) + "A");
}

void QSttFAParasSetWidget::slot_m_editFaultHoldTime()
{
	CString strValue = ui->m_editCurHoldTime->text();
	strValue.Replace(_T("s"), _T(""));
	float fv = strValue.toFloat();

	fv = setLimit(0,5,fv);
	ui->m_editCurHoldTime->setText(QString::number(fv, 'f', 3) + "s");
}

// void QSttFAParasSetWidget::slot_InterSelectIndexChanged( int nIndex )
// {
// 	if (nIndex < 0)
// 	{
// 		return;
// 	}
// // 	CDvmDataset *pCurrDataset = (CDvmDataset*)(ui->m_cmbInterSelect->GetCurrSelObject());
// // 	if (pCurrDataset)
// // 	{
// // 		m_pParas->SetDataValue(_T("datasetpath"),pCurrDataset->m_strDataType);
// // 	}
// 
// 	//CExBaseList *pChildList = (CExBaseList *)m_IntervalList.GetAt(nIndex);
// 
// }

