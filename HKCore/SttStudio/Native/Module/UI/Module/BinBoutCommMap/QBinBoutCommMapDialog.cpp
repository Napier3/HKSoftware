#include "QBinBoutCommMapDialog.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../SttTestCtrl/SttTestAppBase.h"
#include "../../DataMngr/DvmDevice.h"
#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

QBinBoutCommMapDialog::QBinBoutCommMapDialog(QWidget* parent ): QDialog(parent)
{
	setWindowTitle(_T("通用参数"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 600);
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenBinBoutMapXml();
	
	InitUI();
}

QBinBoutCommMapDialog::~QBinBoutCommMapDialog()
{
	m_pBinBoutMapDataCopy->DeleteAll();
	DeleteIntervalListDatas();
}

void QBinBoutCommMapDialog::InitUI()
{
	QTabWidget *pTabWidget = new QTabWidget(this);

	CString strText;
	QGroupBox *pBinGroupBox = new QGroupBox;
	strText = _T("开入量");
	pBinGroupBox->setFont(*g_pSttGlobalFont);
	pBinGroupBox->setTitle(strText);

	QGridLayout* pBinGridLayout = new QGridLayout(pBinGroupBox);
	strText = _T("开入A");
	QLabel *pLabelA = new QLabel;
	pLabelA->setText(strText);
	strText = _T("开入B");
	QLabel *pLabelB = new QLabel;
	pLabelB->setText(strText);
	strText = _T("开入C");
	QLabel *pLabelC = new QLabel;
	pLabelC->setText(strText);
	strText = _T("开入D");
	QLabel *pLabelD = new QLabel;
	pLabelD->setText(strText);

	QStringList oList;
	oList << _T("合闸") <<  _T("分闸") << _T("空");
	QScrollComboBox *pComboBoxA = new QScrollComboBox(this);
	pComboBoxA->addItems(oList);
	pComboBoxA->setFont(*g_pSttGlobalFont);
	QScrollComboBox *pComboBoxB = new QScrollComboBox(this);
	pComboBoxB->addItems(oList);
	pComboBoxB->setFont(*g_pSttGlobalFont);
	QScrollComboBox *pComboBoxC = new QScrollComboBox(this);
	pComboBoxC->addItems(oList);
	pComboBoxC->setFont(*g_pSttGlobalFont);
	QScrollComboBox *pComboBoxD = new QScrollComboBox(this);
	pComboBoxD->addItems(oList);
	pComboBoxD->setFont(*g_pSttGlobalFont);
	pBinGridLayout->addWidget(pLabelA,0,0,1,1);
	pBinGridLayout->addWidget(pComboBoxA,0,1,1,1);
	pBinGridLayout->addWidget(pLabelB,1,0,1,1);
	pBinGridLayout->addWidget(pComboBoxB,1,1,1,1);
	pBinGridLayout->addWidget(pLabelC,2,0,1,1);
	pBinGridLayout->addWidget(pComboBoxC,2,1,1,1);
	pBinGridLayout->addWidget(pLabelD,3,0,1,1);
	pBinGridLayout->addWidget(pComboBoxD,3,1,1,1);

	pComboBoxA->setObjectName(QString::fromUtf8("BinA"));
	GetComboBoxValue(pComboBoxA,_T("BinA"));
	pComboBoxB->setObjectName(QString::fromUtf8("BinB"));
	GetComboBoxValue(pComboBoxB,_T("BinB"));	
	pComboBoxC->setObjectName(QString::fromUtf8("BinC"));
	GetComboBoxValue(pComboBoxC,_T("BinC"));
	pComboBoxD->setObjectName(QString::fromUtf8("BinD"));
	GetComboBoxValue(pComboBoxD,_T("BinD"));

	connect(pComboBoxA, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BinComboBoxChanged(int)));
	connect(pComboBoxB, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BinComboBoxChanged(int)));
	connect(pComboBoxC, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BinComboBoxChanged(int)));
	connect(pComboBoxD, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_BinComboBoxChanged(int)));
	m_pBinComboBoxList.append(pComboBoxA);
	m_pBinComboBoxList.append(pComboBoxB);
	m_pBinComboBoxList.append(pComboBoxC);
	m_pBinComboBoxList.append(pComboBoxD);
	slot_BinComboBoxChanged(0);


	QGroupBox *pBoutGroupBox = new QGroupBox;
	strText = _T("开出量");
	pBoutGroupBox->setFont(*g_pSttGlobalFont);
	pBoutGroupBox->setTitle(strText);

	QStringList oListName,oListID;
	for (int i = 0; i < m_pBoutStringList.size(); ++i) 
	{
		oListName.append(m_pBoutStringList[i].first);
		oListID.append(m_pBoutStringList[i].second);
	}
	CString strID;
	QGridLayout* pBoutGridLayout = new QGridLayout(pBoutGroupBox);
	for (int i = 0; i < 8 ;i++)
	{
		strText.Format(_T("开出%d"), i+1);
		strID.Format(_T("Bout%d"), i+1);
		QLabel *pLabel = new QLabel;
		pLabel->setText(strText);
		QScrollComboBox *pComboBox = new QScrollComboBox(this);
		pComboBox->setFont(*g_pSttGlobalFont);
		pComboBox->addItems(oListName);
		pComboBox->setObjectName(strID);
		m_pBoutComboBoxList.append(pComboBox);
		GetComboBoxValue(pComboBox,strID,oListID);
		pBoutGridLayout->addWidget(pLabel,i,0,1,1);
		pBoutGridLayout->addWidget(pComboBox,i,1,1,1);
		connect(pComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(Slot_BoutComboBoxChanged(int)));
	}

	Slot_BoutComboBoxChanged(0);

	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);


	QVBoxLayout *pBinLayout = new QVBoxLayout;
	pBinLayout->addWidget(pBinGroupBox);
	pBinLayout->setContentsMargins(10, 10, 10, 10);
	QWidget *pBinWidget = new QWidget;
	pBinWidget->setLayout(pBinLayout);

	QVBoxLayout *pBoutLayout = new QVBoxLayout;
	pBoutLayout->addWidget(pBoutGroupBox);
	pBoutLayout->setContentsMargins(10, 10, 10, 10);
	QWidget *pBoutWidget = new QWidget;
	pBoutWidget->setLayout(pBoutLayout);

	QGridLayout *pGridLayout = new QGridLayout;
	QWidget *pWidget = new QWidget;
	pWidget->setLayout(pGridLayout);
	strText = _T("间隔选择");
	QLabel *pInterSelect = new QLabel(this);
	pInterSelect->setText(strText);
	m_pInterSelect_ComboBox = new CExBaseListComboBox(this);
	pInterSelect->setFont(*g_pSttGlobalFont);
	m_pInterSelect_ComboBox->setFont(*g_pSttGlobalFont);  
	strText = _T("装置相数");
	QLabel *pPhase = new QLabel(this);
	pPhase->setText(strText);
	m_pPhaseComboBox = new QScrollComboBox;
	m_pPhaseComboBox->addItems(QStringList()<<_T("2相电压")<<_T("3相电压"));
	long nIndex = 0;
	CDvmData* pCurData = (CDvmData*)m_pBinBoutMapDataGroup.FindByID(_T("Phase_Number"));
	if (pCurData)
	{
		if (pCurData->m_strValue == _T("2"))
		{
			nIndex = 0;
		}
		else if(pCurData->m_strValue == _T("3"))
		{
			nIndex = 1;
		}
	}
	m_pPhaseComboBox->setCurrentIndex(nIndex);
	pPhase->setFont(*g_pSttGlobalFont);
	m_pPhaseComboBox->setFont(*g_pSttGlobalFont);  
	pGridLayout->addWidget(pInterSelect,0,0,1,1);
	pGridLayout->addWidget(m_pInterSelect_ComboBox,0,1,1,1);
	pGridLayout->addWidget(pPhase,1,0,1,1);
	pGridLayout->addWidget(m_pPhaseComboBox,1,1,1,1);

	CString strDatasetpath;
	stt_GetDataValueByID(&m_pBinBoutMapDataGroup, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos);
		TCHAR lastChar= strDatasetpath.GetAt(strDatasetpath.GetLength() - 1);
		CString strLastChar;
		strLastChar.Format(_T("%c"), lastChar);
		long nIndex = CString_To_long(strLastChar);
		m_pInterSelect_ComboBox->ShowBaseList(&m_IntervalList);
		m_pInterSelect_ComboBox->setCurrentIndex(nIndex-1);
	}

// 	CDvmDataset *pInterDataset = (CDvmDataset*)m_pInterSelect_ComboBox->GetCurrSelObject();
// 	if (pInterDataset)
// 	{
// 		m_pBinBoutMapDataGroup.SetDataValue(_T("datasetpath"),pInterDataset->m_strDataType);
// 	}


	pTabWidget->addTab(pBinWidget, _T("开入配置"));
	pTabWidget->addTab(pBoutWidget, _T("开出配置"));
	pTabWidget->addTab(pWidget, _T("装置参数"));
	pTabWidget->setFont(*g_pSttGlobalFont);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(pTabWidget);
	pMainLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainLayout);	


	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	connect(m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
	connect(m_pPhaseComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PhaseIndexChanged(int)));
}


void QBinBoutCommMapDialog::slot_btnOK_Clicked()
{
	QMap<QString, QString>::iterator i;
	for (i = m_BinaryValue.begin(); i != m_BinaryValue.end(); ++i)
	{
		m_pBinBoutMapDataGroup.SetDataValue(i.key(), i.value());
	}

	m_BinaryValue.clear();
	close();

	if (!m_pBinBoutMapDataCopy->IsEqual(&m_pBinBoutMapDataGroup))
	{
		emit sig_BinBoutCommMapDataUpdate(&m_pBinBoutMapDataGroup);
		UpdateData(&m_pBinBoutMapDataGroup);
		SaveBinBoutMapXml();
	}
}

void QBinBoutCommMapDialog::slot_btnCancel_Clicked()
{
	close();
}

void QBinBoutCommMapDialog::GetComboBoxValue(QScrollComboBox* pComboBox,const CString strID,const QStringList& pList)
{
	CDvmData* pCurData = (CDvmData*)m_pBinBoutMapDataGroup.FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	int nIndex = -1;
	if (!pList.isEmpty())
	{
		nIndex = pList.indexOf(pCurData->m_strValue);
	}
	else
	{
		nIndex = CString_To_long(pCurData->m_strValue);
	}

	if (nIndex != -1)
	{
		pComboBox->setCurrentIndex(nIndex);
	}
}

void QBinBoutCommMapDialog::UpdateComboBox(QStringList pList,QList<QScrollComboBox*> pComboBoxList,bool bBout)
{
	QList<QString> pSelectedValues;
	pSelectedValues.clear();
	foreach (QScrollComboBox* pComboBox, pComboBoxList)
	{
		QString currentText = pComboBox->currentText();
		if (currentText != _T("空"))
		{
			pSelectedValues.append(currentText);
		}
	}

	foreach (QScrollComboBox* pComboBox, pComboBoxList)
	{
		QString currentText = pComboBox->currentText();
		pComboBox->blockSignals(true); 
		pComboBox->clear();
		foreach (const QString& value,  pList)
		{
			if (!pSelectedValues.contains(value) || value == currentText)
			{
				pComboBox->addItem(value);
			}
		}
		pComboBox->addItem(_T("空"));
		int nIndex = pComboBox->findText(currentText);
		if (nIndex != -1)
		{
			pComboBox->setCurrentIndex(nIndex);
		}
		else
		{
			pComboBox->setCurrentIndex(pComboBox->findText(_T("空")));
		}

		CString strValue;
		if (bBout)
		{
			for (int i = 0; i < m_pBoutStringList.size(); ++i) 
			{
				if (m_pBoutStringList[i].first == currentText) 
				{
					strValue = m_pBoutStringList[i].second;
					m_BinaryValue[pComboBox->objectName()] = strValue;
				}
			}
		}
		else
		{
			if (currentText == _T("合闸"))
			{
				strValue = _T("0");
			}
			else if (currentText == _T("分闸"))
			{
				strValue = _T("1");
			}
			else
			{
				strValue = _T("2");
			}
			m_BinaryValue[pComboBox->objectName()] = strValue;
		}
		
		pComboBox->blockSignals(false); 
	}
}


void QBinBoutCommMapDialog::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pBinBoutMapDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(&m_pBinBoutMapDataGroup, strID, strValue);

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			m_pBinBoutMapDataGroup.SetDataValue(strID, _T("Din_1"));  
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			m_pBinBoutMapDataGroup.SetDataValue(strID, _T("Din_2"));
		}
		else if (strValue == _T("Din_5") || strValue == _T("2"))
		{
			m_pBinBoutMapDataGroup.SetDataValue(strID, _T("Din_5"));
		}
		else
		{
			m_pBinBoutMapDataGroup.SetDataValue(strID, _T(""));  
		}
	}

	m_pBinBoutMapDataCopy = (CDataGroup*)(&m_pBinBoutMapDataGroup)->Clone();

	InitIntervalListDatas();
}

void QBinBoutCommMapDialog::SaveBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	m_pBinBoutMapDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QBinBoutCommMapDialog::InitIntervalListDatas( )
{
	CString strDatasetpath;
	stt_GetDataValueByID(&m_pBinBoutMapDataGroup, _T("datasetpath"), strDatasetpath);

	DeleteIntervalListDatas();
	m_pBoutStringList.clear();

	CDvmDevice* pDvmDevice = NULL;
#ifdef _PSX_QT_WINDOWS_
	pDvmDevice = g_theGbSmartGenWzd->m_pDvmDevice ;
#else
	pDvmDevice = g_pTheSttTestApp->m_pDvmDevice;
#endif

	if (pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDvmDatasetRef = NULL,*pCurrDataset = NULL;
	CDvmData*pCurrDvmData = NULL;
	CExBaseList *pCurObj = NULL;

	POS pos = pDvmDevice->GetHeadPosition();
	while(pos)
	{
		pCurObj = (CExBaseList*)pDvmDevice->GetNext(pos);	

		if (pCurObj->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		if (pCurObj->m_strID == _T("report") || pCurObj->m_strID == _T("CommMessage"))
		{
			continue;
		}

		pDvmDatasetRef = new CDvmDataset;
		m_IntervalList.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();
		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID == _T("dsDin"))
			{
				pDvmDatasetRef->m_strDataType.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());

				POS pos_data = pCurrDataset->GetHeadPosition();
				while(pos_data)
				{
					pCurrDvmData = (CDvmData *)pCurrDataset->GetNext(pos_data);
					if (pCurrDvmData == NULL)
					{
						continue;
					}
					if (pCurrDvmData->m_strID == _T("Din_1") || pCurrDvmData->m_strID == _T("Din_2") || pCurrDvmData->m_strID == _T("Din_5"))
					{
						if (strDatasetpath == pDvmDatasetRef->m_strDataType)
						{
						QPair<QString, QString> pair(pCurrDvmData->m_strName, pCurrDvmData->m_strID);
						m_pBoutStringList.append(pair);
						}
						pDvmDatasetRef->AddNewChild(pCurrDvmData);
					}
				}
			}
		}
	}

	m_pBoutStringList.append(qMakePair(QString(_T("空")), QString("")));
}


void QBinBoutCommMapDialog::UpdateData( CDataGroup *pParas )
{
	if(!g_pTheSttTestApp->m_pTestMacroUI)
	{
		return;
	}
	if (!g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		return;
	}

	CSttMacroParaEditViewOriginal *pMacroEditView = (CSttMacroParaEditViewOriginal*)g_theTestCntrFrame->GetMacroEditView();
	if (pMacroEditView)
	{
		pMacroEditView->UpdateRemoteBoutData(pParas);
	}
}

void QBinBoutCommMapDialog::DeleteIntervalListDatas()
{
	CExBaseList *pChildList = NULL;
	POS pos = m_IntervalList.GetHeadPosition();

	while(pos)
	{
		pChildList = (CExBaseList *)m_IntervalList.GetNext(pos);
		pChildList->RemoveAll();
	}

	m_IntervalList.DeleteAll();
}

void QBinBoutCommMapDialog::UpdateBoutData(CExBaseList *pChildList)
{
	m_pBoutStringList.clear();
	POS pos = pChildList->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	while(pos)
	{
		pObj = (CExBaseObject *)pChildList->GetNext(pos);
		if (pObj == NULL)
		{
			continue;
		}
		if (pObj->m_strID == _T("Din_1") || pObj->m_strID == _T("Din_2") || pObj->m_strID == _T("Din_5"))
		{
			QPair<QString, QString> pair(pObj->m_strName, pObj->m_strID);
			m_pBoutStringList.append(pair);
		}
	}
	m_pBoutStringList.append(qMakePair(QString(_T("空")), QString("")));

	QStringList oListName,oListID;
	for (int j = 0; j < m_pBoutStringList.size(); ++j) 
	{
		oListName.append(m_pBoutStringList[j].first);
		oListID.append(m_pBoutStringList[j].second);
	}

	int listSize = m_pBoutStringList.size();
	for (int i = 0;i <m_pBoutComboBoxList.size();++i)
	{
		if (i >= listSize)
		{
			break;
		}
		
		QScrollComboBox* pComboBox = m_pBoutComboBoxList.at(i);
		disconnect(pComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(Slot_BoutComboBoxChanged(int)));
		pComboBox->clear();
		pComboBox->addItems(oListName);
		GetComboBoxValue(pComboBox,pComboBox->objectName(),oListID);
		connect(pComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(Slot_BoutComboBoxChanged(int)));
	}

	Slot_BoutComboBoxChanged(0);
}

void QBinBoutCommMapDialog::Slot_BoutComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}

	QStringList oList;

	for (int i = 0; i < m_pBoutStringList.size(); ++i) 
	{
		QString firstString = m_pBoutStringList[i].first;
		if (firstString != "空")
		{
			oList.append(firstString);
		}
	}

	UpdateComboBox(oList,m_pBoutComboBoxList,true);
}


void QBinBoutCommMapDialog::slot_InterSelectIndexChanged( int nIndex )
{
	if (nIndex < 0)
	{
		return;
	}

	CDvmDataset *pCurrDataset = (CDvmDataset*)m_pInterSelect_ComboBox->GetCurrSelObject();
	if (pCurrDataset)
	{
		m_pBinBoutMapDataGroup.SetDataValue(_T("datasetpath"),pCurrDataset->m_strDataType);
	}

	CExBaseList *pChildList = (CExBaseList *)m_IntervalList.GetAt(nIndex);
	UpdateBoutData(pChildList);
}

void QBinBoutCommMapDialog::slot_PhaseIndexChanged( int nIndex )
{
	if (nIndex < 0)
	{
		return;
	}
	long nPhaseNumber = 0;
	if (nIndex == 0)
	{
		nPhaseNumber = 2;
	}
	else
	{
		nPhaseNumber = 3;
	}

	m_pBinBoutMapDataGroup.SetDataValue(_T("Phase_Number"),nPhaseNumber);
}

void QBinBoutCommMapDialog::slot_BinComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}

	QStringList oList;
	oList << _T("合闸") <<  _T("分闸");
	UpdateComboBox(oList,m_pBinComboBoxList,false);
}
