#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"
#include "QSttMacroParaEditViewAntiShakeTime.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "Grid/QSttAntiShakeTimeTestItemsGroupGrid.h"
#include "Grid/QSttAntiShakeTimeDinEventGroupGrid.h"
#include "../Module/CommonCtrl_QT/QLongLineEdit.h"
//#ifdef _PSX_QT_WINDOWS_
//#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
//extern CGbSmartGenWzd *g_theGbSmartGenWzd;
//#endif

QSttMacroParaEditViewAntiShakeTime* g_pAntiShakeTime = NULL;
QSttMacroParaEditViewAntiShakeTime::QSttMacroParaEditViewAntiShakeTime(QWidget *parent)
{

	g_pTheSttTestApp->IinitGbWzdAiTool();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime setWindowFlags", true);
	g_pAntiShakeTime = this;
	m_pTestRecordsGroupGrid = NULL;
	m_pDinEventGroupGrid = NULL;

	m_pLabelInterval = NULL;         
	m_pLabelTestObject = NULL;      
	m_pLabelAntiShakeTime = NULL;    
	m_pLabelTimeMsec = NULL;        
	m_pLabelSOEResolution = NULL;	  
	m_pLabelSOEMsec = NULL;		  
	m_pLabelBoutSet = NULL;		  
	m_pLabelInitState = NULL;	

	m_pCmbIntervalSelect = NULL; 
	m_pCmbTestObject = NULL;	 
	m_pCmbBoutSet = NULL;		  
	m_pCmbInitState = NULL;	

	m_pEditAntiShakeTime = NULL;  
	m_pEditSOEResolution = NULL; 

	m_pBtnAddTestItem = NULL;   
	m_pBtnDeleteTestItem = NULL;

	OpenXmlFile();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime OpenXmlFile", true);
	InitUI();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime InitUI", true);
	InitConnections();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime InitConnections", true);
	InitData();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime InitData", true);
	DelCmbBoutSetData();
	debug_time_long_log("QSttMacroParaEditViewAntiShakeTime DelCmbBoutSetData", true);
}

QSttMacroParaEditViewAntiShakeTime::~QSttMacroParaEditViewAntiShakeTime()
{
	DeleteIntervalListDatas();
	m_oTestObjectList.RemoveAll();
	m_oBoutSetList.RemoveAll();
}

void QSttMacroParaEditViewAntiShakeTime::InitUI()
{     
	CString strText;
	strText = _T("间隔选择:");
	m_pLabelInterval = new QLabel(this);
	m_pLabelInterval->setText(strText);
	m_pCmbIntervalSelect = new CExBaseListComboBox(this);
	strText = _T("测试对象:");
	m_pLabelTestObject = new QLabel(this);
	m_pLabelTestObject->setText(strText);
	m_pCmbTestObject = new CExBaseListComboBox(this);
	strText = _T("开出设置:");
	m_pLabelBoutSet = new QLabel(this);
	m_pLabelBoutSet->setText(strText);
	m_pCmbBoutSet = new CExBaseListComboBox(this);
	strText = _T("初始状态:");
	m_pLabelInitState = new QLabel(this);
	m_pLabelInitState->setText(strText);
	m_pCmbInitState = new QComboBox();
	strText = _T("防抖时间:");
	m_pLabelAntiShakeTime = new QLabel(this);
	m_pLabelAntiShakeTime->setText(strText);
	m_pEditAntiShakeTime = new QSttLineEdit();
	strText = _T("毫秒");
	m_pLabelTimeMsec = new QLabel(this);
	m_pLabelTimeMsec->setText(strText);
	strText = _T("SOE分辨率:");
	m_pLabelSOEResolution = new QLabel(this);
	m_pLabelSOEResolution->setText(strText);
	m_pEditSOEResolution = new QSttLineEdit();
	strText = _T("毫秒");
	m_pLabelSOEMsec = new QLabel(this);
	m_pLabelSOEMsec->setText(strText);
	strText = _T("添加测试项");
	m_pBtnAddTestItem = new QPushButton(this);
	m_pBtnAddTestItem->setText(strText);
	strText = _T("删除测试项");
	m_pBtnDeleteTestItem = new QPushButton(this);
	m_pBtnDeleteTestItem->setText(strText);
	strText = _T("清空事件记录");
	QPushButton *pBtnClearSoeRecord = new QPushButton(this);
	pBtnClearSoeRecord->setText(strText);
	pBtnClearSoeRecord->setFont(*g_pSttGlobalFont);
	connect(pBtnClearSoeRecord, SIGNAL(clicked()), this, SLOT(slot_btn_ClearClearEventRecordsClicked()));	


	QGridLayout *pTopGridLayout = new QGridLayout();
	pTopGridLayout->addWidget(m_pLabelInterval, 0, 0,1,1);
	pTopGridLayout->addWidget(m_pCmbIntervalSelect, 0, 1,1,1);
	pTopGridLayout->addWidget(m_pLabelTestObject, 0, 2,1,1);
	pTopGridLayout->addWidget(m_pCmbTestObject, 0, 3,1,1);
	pTopGridLayout->addWidget(m_pLabelAntiShakeTime, 0, 4,1,1);
	pTopGridLayout->addWidget(m_pEditAntiShakeTime, 0, 5,1,1);
	pTopGridLayout->addWidget(m_pLabelTimeMsec, 0, 6,1,1);
	pTopGridLayout->addWidget(m_pLabelSOEResolution, 0, 7,1,1);
	pTopGridLayout->addWidget(m_pEditSOEResolution, 0, 8,1,1);
	pTopGridLayout->addWidget(m_pLabelSOEMsec, 0, 9,1,1);
	pTopGridLayout->addWidget(m_pLabelBoutSet, 1, 0,1,1);
	pTopGridLayout->addWidget(m_pCmbBoutSet, 1, 1,1,1);
	pTopGridLayout->addWidget(m_pLabelInitState, 1, 2,1,1);
	pTopGridLayout->addWidget(m_pCmbInitState, 1, 3,1,1);
// 	pTopGridLayout->addWidget(m_pBtnAddTestItem, 1, 6 ,1 ,2);
// 	pTopGridLayout->addWidget(m_pBtnDeleteTestItem, 1, 9,1 ,2);
	QHBoxLayout *pBtnHBoxLayout = new QHBoxLayout();
	pBtnHBoxLayout->addWidget(m_pBtnAddTestItem);
	pBtnHBoxLayout->addWidget(m_pBtnDeleteTestItem);
	pBtnHBoxLayout->addWidget(pBtnClearSoeRecord);
	QWidget *pBtnContainer = new QWidget();
	pBtnContainer->setLayout(pBtnHBoxLayout);
	pTopGridLayout->addWidget(pBtnContainer, 1, 5, 1, 4);

	m_pTestRecordsGroupGrid = new QSttAntiShakeTimeTestItemsGroupGrid();
	m_pTestRecordsGroupGrid->setFont(*g_pSttGlobalFont);
	m_pTestRecordsGroupGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pTestRecordsGroupGrid->InitGrid();

	
	m_pDinEventGroupGrid = new QSttAntiShakeTimeDinEventGroupGrid();
	m_pDinEventGroupGrid->InitUI();
	m_pDinEventGroupGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pDinEventGroupGrid->setFont(*g_pSttGlobalFont);


	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addLayout(pTopGridLayout);
	pMainLayout->addWidget(m_pTestRecordsGroupGrid);
	pMainLayout->addWidget(m_pDinEventGroupGrid);
	setLayout(pMainLayout);	

	InitFont();
	InitComboBox();
	InitIntervalListDatas();
	InitTestObjectListDatas();
	InitBoutSetListDatas();
	UpDateButtonState();
} 

void QSttMacroParaEditViewAntiShakeTime::InitFont()
{   
	m_pLabelInterval->setFont(*g_pSttGlobalFont);
	m_pCmbIntervalSelect->setFont(*g_pSttGlobalFont);

	m_pLabelTestObject->setFont(*g_pSttGlobalFont);
	m_pCmbTestObject->setFont(*g_pSttGlobalFont);

	m_pLabelBoutSet->setFont(*g_pSttGlobalFont);
	m_pCmbBoutSet->setFont(*g_pSttGlobalFont);

	m_pLabelInitState->setFont(*g_pSttGlobalFont);
	m_pCmbInitState->setFont(*g_pSttGlobalFont);

	m_pLabelAntiShakeTime->setFont(*g_pSttGlobalFont);
	m_pEditAntiShakeTime->setFont(*g_pSttGlobalFont);
	m_pLabelTimeMsec->setFont(*g_pSttGlobalFont);

	m_pLabelSOEResolution->setFont(*g_pSttGlobalFont);
	m_pEditSOEResolution->setFont(*g_pSttGlobalFont);
	m_pLabelSOEMsec->setFont(*g_pSttGlobalFont);

	m_pBtnAddTestItem->setFont(*g_pSttGlobalFont);
	m_pBtnDeleteTestItem->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewAntiShakeTime::InitConnections()
{
	connect(m_pBtnAddTestItem,SIGNAL(clicked()),this,SLOT(slot_AddTestItem()));
	connect(m_pBtnDeleteTestItem,SIGNAL(clicked()),this,SLOT(slot_DeleteTestItem()));
	connect(m_pCmbIntervalSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbIntervalSelect(int)));
	connect(m_pCmbTestObject,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbTestObject(int)));
	connect(m_pCmbBoutSet,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbBoutSet(int)));
	connect(m_pCmbInitState,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbInitState(int)));
	connect(m_pEditAntiShakeTime,SIGNAL(editingFinished()),this,SLOT(slot_EditAntiShakeTime()));
	connect(m_pEditSOEResolution,SIGNAL(editingFinished()),this,SLOT(slot_EditSOEResolution()));
}

void QSttMacroParaEditViewAntiShakeTime::InitComboBox()
{
	m_pCmbIntervalSelect->setMinimumWidth(100);
	m_pCmbTestObject->setMinimumWidth(120);
 	m_pEditAntiShakeTime->setFocusPolicy(Qt::ClickFocus);
 	m_pEditSOEResolution->setFocusPolicy(Qt::ClickFocus);

	
	m_pCmbInitState->addItem(_T("断开"));
	m_pCmbInitState->addItem(_T("闭合"));
}


void QSttMacroParaEditViewAntiShakeTime::DeleteIntervalListDatas()
{
	CExBaseList *pChildList = NULL;
	POS pos = m_oIntervalList.GetHeadPosition();

	while(pos)
	{
		pChildList = (CExBaseList *)m_oIntervalList.GetNext(pos);
		pChildList->RemoveAll();
	}

	m_oIntervalList.DeleteAll();
}

void QSttMacroParaEditViewAntiShakeTime::InitIntervalListDatas()
{
	DeleteIntervalListDatas();

// 	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
// 	{
// 		g_theTestCntrFrame->CreateEngineClientWidget();
// 	}

	//CDvmDevice* pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;
	CDvmDevice* pDvmDevice = g_pTheSttTestApp->m_pDvmDevice;

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

		if (pCurObj->m_strID == _T("report")|| pCurObj->m_strID == _T("CommMessage"))
		{
			continue;
		}

		pDvmDatasetRef = new CDvmDataset;
		m_oIntervalList.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();
		long nIndex = 0;

		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID/*.Find(STT_ANTISHAKE_TIME_Dataset_ID) >= 0*/ == _T("dsDin"))
			{
				pDvmDatasetRef->Append(*pCurrDataset);

// 				if (nIndex == 0)//将对应的ID设置为第一个遥测数据集的路径,方便后续从装置读取数据
// 				{
// 					pDvmDatasetRef->m_strID.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
// 				}
				pDvmDatasetRef->m_strDataType.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());

				nIndex++;
			}
		}
	}
	m_pCmbIntervalSelect->ShowBaseList(&m_oIntervalList);
}

void QSttMacroParaEditViewAntiShakeTime::InitTestObjectListDatas()
{
	m_oTestObjectList.RemoveAll();
	CExBaseList *pDataset = (CExBaseList*)m_pCmbIntervalSelect->GetCurrSelObject();

	if (pDataset == NULL)
	{
		return;
	}

	POS posDataset = pDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	
	while (posDataset)
	{
		pCurrData = (CDvmData *)pDataset->GetNext(posDataset);

		if (pCurrData->m_strID == _T("Din_1") || pCurrData->m_strID == _T("Din_2") || pCurrData->m_strID == _T("Din_5"))
		{
		m_oTestObjectList.AddTail(pCurrData);
		}
	}

	m_pCmbTestObject->ShowBaseList(&m_oTestObjectList);
}

void QSttMacroParaEditViewAntiShakeTime::InitBoutSetListDatas()
{
	m_oBoutSetList.DeleteAll();
	CString strName,strID;

	for (int nIndex = 1; nIndex <= g_nBoutCount; nIndex++)
	{
		CDvmData *pDvmData = new CDvmData;
		strName.Format(_T("开出%d"), nIndex);
		strID.Format(_T("Bout%d"), nIndex);
		pDvmData->m_strName = strName;
		pDvmData->m_strID = strID;
		m_oBoutSetList.AddTail(pDvmData);
	}
	m_pCmbBoutSet->ShowBaseList(&m_oBoutSetList);
}

void QSttMacroParaEditViewAntiShakeTime::OpenXmlFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/AntiShakeTime_Paras.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oTestRecordsDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}


void QSttMacroParaEditViewAntiShakeTime::slot_AddTestItem()
{ 
	long nSelectValue = 1;
	int nExistingTestItems;			    //现有测试项
	int nEstimateTimesTop;              //预计变位次数
	int nEstimateTimesBottom;		    //实际变位次数

	int nInterval = m_pCmbIntervalSelect->currentIndex();     // 间隔选择
	int nTestObject = m_pCmbTestObject->currentIndex();       // 测试对象
	int nBoutSet = m_pCmbBoutSet->currentIndex();             // 开出设置
	int nInitState = m_pCmbInitState->currentIndex();         // 初始状态

	int nAntiShakeTime = m_pEditAntiShakeTime->text().toInt(); // 防抖时间
	int nSOEResolution = m_pEditSOEResolution->text().toInt(); // SOE分辨率

	// 计算防抖时间减去 SOE，确保结果大于等于0
	int nPulseWidthTop = (nAntiShakeTime >= nSOEResolution) ? (nAntiShakeTime - nSOEResolution) : 0;

	// 计算防抖时间加上 SOE，确保结果大于等于0
	int nPulseWidthBottom = nAntiShakeTime + nSOEResolution;
	nPulseWidthBottom = (nPulseWidthBottom >= 0) ? nPulseWidthBottom : 0;

	if (nPulseWidthTop < nAntiShakeTime) 
	{
		if (m_pCmbInitState->currentIndex() == 0)
		{
			nEstimateTimesTop = 0;
		}
		else
		{
			nEstimateTimesTop = 2;			//预计变位次数
		}
	} 
	else
	{
		nEstimateTimesTop = 0;
	}

	if (nPulseWidthBottom > nAntiShakeTime) 
	{
		if (m_pCmbInitState->currentIndex() == 0)
		{
			nEstimateTimesBottom = 2;
		}
		else
		{
			nEstimateTimesBottom = 4;			    //实际变位次数
		}
	} 
	else
	{
		nEstimateTimesBottom = 0;
	}
	
	CDataGroup* pDataGroup = NULL;
	CDvmData* pDvmData = NULL;
	int nMaxTestItems = 10; // 一共有十个测试项
	int nItemsToAdd = 2; // 每次添加两个测试项

	int nStartIndex = 7; // 第7个子节点后是测试项

	int nTestItemNumber = 1;

	long nZero = 0;
	while (nItemsToAdd > 0 && nTestItemNumber <= nMaxTestItems)
	{
		CString strTestItemName;
		strTestItemName.Format(_T("TestItem%d"), nTestItemNumber);

		pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.FindByID(strTestItemName);
		pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);
		if(pDataGroup != NULL && pDvmData->m_strValue == NULL)
		{
			int nPulseWidth = (nTestItemNumber % 2 == 0) ? nPulseWidthBottom : nPulseWidthTop;
			int nEstimateTimes = (nTestItemNumber % 2 == 0) ? nEstimateTimesBottom : nEstimateTimesTop;

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);
			long nValue = CString_To_long(pDvmData->m_strValue);
			if(pDvmData->m_strValue.IsEmpty() || nValue == nZero)
			{
				pDvmData->m_strValue = _T("0");
			}
			else if (nValue == nSelectValue)
			{
				pDvmData->m_strValue = _T("1");
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_INTERVAL_SELECT);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nInterval);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_TEST_OBJECT);
			if (pDvmData != NULL) 
			{
				CDvmData *pCurrData = (CDvmData *)m_oTestObjectList.GetAt(nTestObject);
				pDvmData->m_strValue = /*CString::number(nTestObject)*/pCurrData->m_strID;
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_BOUT_SET);
			if (pDvmData != NULL) 
			{
				CString strText = m_pCmbBoutSet->currentText();
				strText = strText.right(1);
				//strText.Format(_T("Bout%d"),strText.toInt());
				pDvmData->m_strValue = /*CString::number(nBoutSet)*/strText; 
// 				m_pCmbBoutSet->setItemData(nBoutSet, QVariant(0), Qt::UserRole - 1);
// 				for (int i = 0; i < g_nBoutCount; ++i) 
// 				{
// 					if (!m_pCmbBoutSet->itemData(i, Qt::UserRole - 1).isValid()) 
// 					{
// 						m_pCmbBoutSet->setCurrentIndex(i);
// 						break;
// 					}
// 				}
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_INIT_STATE);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nInitState);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(_T("count"));
			if (pDvmData != NULL) 
			{
				if (m_pCmbInitState->currentIndex() == 0)
				{
					pDvmData->m_strValue = _T("2");
				}
				else
				{
					pDvmData->m_strValue = _T("3");
				}
			}
			pDvmData = (CDvmData*)pDataGroup->FindByID(_T("datasetpath"));
			if (pDvmData != NULL) 
			{
				CDvmDataset *pInterDataset = (CDvmDataset*)m_pCmbIntervalSelect->GetCurrSelObject();
				pDvmData->m_strValue = pInterDataset->m_strDataType;
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_PULSE_WIDTH);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nPulseWidth);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_ESTIMATE_TIMES);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nEstimateTimes);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(_T("AntiShakeTime"));
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = m_pEditAntiShakeTime->text();
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_ACTUAL_TIMES);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = _T("-");
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_TEST_RESUL);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = _T("-");
			}
			nItemsToAdd--;
		}
		nTestItemNumber++;
	}

	UpDateItemNumValue(nTestItemNumber - 1);
	m_pTestRecordsGroupGrid->m_ObjectIdList.clear();
	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
	DelCmbBoutSetData();
	//SaveXmlParas();
} 

void QSttMacroParaEditViewAntiShakeTime::UpDateItemNumValue(int nNewValue)
{
	CDvmData* pItemNumData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ITEM_NUM);
	if (pItemNumData != NULL) 
	{
		pItemNumData->m_strValue = CString::number(nNewValue);
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("测试项数量");
		pData->m_strID = STT_ANTISHAKE_TIME_ITEM_NUM;
		pData->m_strValue = CString::number(nNewValue);
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	if (STT_ANTISHAKE_TIME_TESTITEM_NUMBER - nNewValue < 2)
	{
		m_pBtnAddTestItem->setEnabled(false);
	}
	else
	{
		m_pBtnAddTestItem->setEnabled(true);
	}
	if (nNewValue == 0)
	{
		m_pBtnDeleteTestItem->setEnabled(false);
	}
	else
	{
		m_pBtnDeleteTestItem->setEnabled(true);
	}
}

void QSttMacroParaEditViewAntiShakeTime::UpDataTestItemName()
{
	CDataGroup *pDataGroup;
	POS pos = m_oTestRecordsDataGroup.GetHeadPosition();
	int nIndex = 1;
 	while(pos)
 	{
		pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.GetNext(pos);
		UINT classID = pDataGroup->GetClassID();
		if (classID != DVMCLASSID_CDVMDATA)
		{
			CString strName, strID;
			strName.Format(_T("测试项%d"), nIndex);
			strID.Format(_T("TestItem%d"), nIndex);
			pDataGroup->m_strName = strName;
			pDataGroup->m_strID = strID;
			nIndex++;
		}
 	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_DeleteTestItem()
{	
	int nSelectValue = 1;				  //CheckBox勾选值
	int nDeletedTestItems = 0;
	QList<QString> oSetList;
	for (int i = 0; i < STT_ANTISHAKE_TIME_TESTITEM_NUMBER; i++)
	{
		CString strToFind;
		strToFind.Format(_T("TestItem%d"), i+1);
		CDataGroup* pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.FindByID(strToFind);
		
		if (pDataGroup != NULL) 
		{
			
			CDvmData* pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);
			CString strData;
			strData.Format(_T("%d"),nSelectValue);
			QString strSel= pDvmData->m_strValue.GetString();
			if (strSel == strData)
			{
				CDvmData* pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_BOUT_SET);
				CString strData = pDvmData->m_strValue;
// 				int nIndex = strData.toInt();
// 				if (nIndex != -1)
//  				{
// 					CDvmData *pBoutDvmData = new CDvmData;
// 					pBoutDvmData->m_strName.Format(_T("开出%d"),nIndex+1);
// 					pBoutDvmData->m_strID.Format(_T("Bout%d"),nIndex+1);
// 					m_oBoutSetList.AddTail(pBoutDvmData);
// 
//  					//m_pCmbBoutSet->setItemData(nIndex, QVariant(), Qt::UserRole - 1);
//  				}

				strData.Format(_T("Bout%d"),strData.toInt());
				oSetList.append(strData);

				m_oTestRecordsDataGroup.Remove(pDataGroup);
				nDeletedTestItems++; // 每删除一个测试项，计数器加一

			}
		}
	}

	AddCmbBoutSetData(oSetList);

	for (int i = 0;i < STT_ANTISHAKE_TIME_TESTITEM_NUMBER; i++)
	{
		CString strToFind;
		strToFind.Format(_T("TestItem%d"), i+1);
		CDataGroup* pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.FindByID(strToFind);

		if (pDataGroup == NULL)
		{
			CDataGroup* pDataGroup = new CDataGroup();
			pDataGroup->m_strName.Format(_T("测试项%d"), i);
			pDataGroup->m_strID = strToFind;

			CDvmData* pData1 = new CDvmData;
			pData1->m_strName = _T("选择");
			pData1->m_strID = STT_ANTISHAKE_TIME_SELECT;
			pData1->m_strValue = "";
			pDataGroup->AddNewChild(pData1);

			CDvmData* pData2 = new CDvmData;
			pData2->m_strName = _T("间隔选择");
			pData2->m_strID = STT_ANTISHAKE_TIME_INTERVAL_SELECT;
			pData2->m_strValue = "";
			pDataGroup->AddNewChild(pData2);

			CDvmData* pData3 = new CDvmData;
			pData3->m_strName = _T("测试对象");
			pData3->m_strID = STT_ANTISHAKE_TIME_TEST_OBJECT;
			pData3->m_strValue = "";
			pDataGroup->AddNewChild(pData3);

			CDvmData* pData4 = new CDvmData;
			pData4->m_strName = _T("开出设置");
			pData4->m_strID = STT_ANTISHAKE_TIME_BOUT_SET;
			pData4->m_strValue = "";
			pDataGroup->AddNewChild(pData4);

			CDvmData* pData5 = new CDvmData;
			pData5->m_strName = _T("初始状态");
			pData5->m_strID = STT_ANTISHAKE_TIME_INIT_STATE;
			pData5->m_strValue = "";
			pDataGroup->AddNewChild(pData5);

			CDvmData* pData6 = new CDvmData;
			pData6->m_strName = _T("脉冲宽度(ms)");
			pData6->m_strID = STT_ANTISHAKE_TIME_PULSE_WIDTH;
			pData6->m_strValue = "";
			pDataGroup->AddNewChild(pData6);

			CDvmData* pData7  =new CDvmData;
			pData7->m_strName = _T("预计变位次数");
			pData7->m_strID = STT_ANTISHAKE_TIME_ESTIMATE_TIMES;
			pData7->m_strValue = "";
			pDataGroup->AddNewChild(pData7);

			CDvmData* pData8 = new CDvmData;
			pData8->m_strName = _T("实际变位次数");
			pData8->m_strID = STT_ANTISHAKE_TIME_ACTUAL_TIMES;
			pData8->m_strValue = "";
			pDataGroup->AddNewChild(pData8);

			CDvmData* pData9 = new CDvmData;
			pData9->m_strName = _T("测试结果");
			pData9->m_strID = STT_ANTISHAKE_TIME_TEST_RESUL;
			pData9->m_strValue = "";
			pDataGroup->AddNewChild(pData9);

			CDvmData* pData10 = new CDvmData;
			pData10->m_strName = _T("间隔路径");
			pData10->m_strID = _T("datasetpath");
			pData10->m_strValue = "";
			pDataGroup->AddNewChild(pData10);

			CDvmData* pData11 = new CDvmData;
			pData11->m_strName = _T("变位");
			pData11->m_strID = _T("count");
			pData11->m_strValue = "";
			pDataGroup->AddNewChild(pData11);

			CDvmData* pData12 = new CDvmData;
			pData12->m_strName = _T("防抖时间");
			pData12->m_strID = _T("AntiShakeTime");
			pData12->m_strValue = "";
			pDataGroup->AddNewChild(pData12);

			m_oTestRecordsDataGroup.AddNewChild(pDataGroup);
		}
	}
	CDvmData* pDvmData1 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ITEM_NUM);
	CString strIntervalValue = pDvmData1->m_strValue;
	int nIndex = strIntervalValue.toInt();
	UpDateItemNumValue(nIndex - nDeletedTestItems);
	UpDataTestItemName();
	m_pTestRecordsGroupGrid->m_ObjectIdList.clear();
	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
	m_pTestRecordsGroupGrid->m_oBoutSetList.clear();
}

void QSttMacroParaEditViewAntiShakeTime::slot_CmbIntervalSelect(int nIndex)
{
	CString strText;
	strText.Format("%d",nIndex);
	CDvmData* pDvmData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT);
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("间隔选择");
		pData->m_strID = STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT;
		pData->m_strValue = strText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_CmbTestObject(int nIndex)
{
	CString strText;
	strText.Format("%d",nIndex);
	CDvmData* pDvmData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_TEST_OBJECT);
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("测试对象");
		pData->m_strID = STT_ANTISHAKE_TIME_INIT_TEST_OBJECT;
		pData->m_strValue = strText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_CmbBoutSet(int nIndex)
{
	CString strText;
	strText.Format("%d",nIndex);
	CDvmData* pDvmData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_BOUT_SET);
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("开出设置");
		pData->m_strID = STT_ANTISHAKE_TIME_INIT_BOUT_SET;
		pData->m_strValue = strText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_CmbInitState(int nIndex)
{
	CString strText;
	strText.Format("%d",nIndex);
	CDvmData* pDvmData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_STATE1);
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("初始状态");
		pData->m_strID = STT_ANTISHAKE_TIME_INIT_STATE1;
		pData->m_strValue = strText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_EditAntiShakeTime()
{
	float fValue = m_pEditAntiShakeTime->text().toFloat();
	fValue = setLimit(0,1000,fValue);

	CString strNewText /*= m_pEditAntiShakeTime->text()*/;
	strNewText.Format(_T("%f"),fValue);

	CDvmData* pDvmData = static_cast<CDvmData*>(m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME));
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strNewText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("防抖时间");
		pData->m_strID = STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME;
		pData->m_strValue = strNewText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	m_pEditAntiShakeTime->setText(QString::number(fValue,'f', 0));

	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_EditSOEResolution()
{
	float fValue = m_pEditSOEResolution->text().toFloat();
	fValue = setLimit(0,1000,fValue);

	CString strNewText /*= m_pEditSOEResolution->text()*/;
	strNewText.Format(_T("%f"),fValue);

	CDvmData* pDvmData = static_cast<CDvmData*>(m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_SOE_RESOLUTION));
	if (pDvmData != NULL) 
	{
		pDvmData->m_strValue = strNewText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = _T("SOE分辨率");
		pData->m_strID = STT_ANTISHAKE_TIME_SOE_RESOLUTION;
		pData->m_strValue = strNewText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	m_pEditSOEResolution->setText(QString::number(fValue,'f', 0));

	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_btn_ClearClearEventRecordsClicked()
{
	if (m_pDinEventGroupGrid == NULL)
	{
		return;
	}
	m_pDinEventGroupGrid->clearContents();
	m_pDinEventGroupGrid->setRowCount(0);
}

void QSttMacroParaEditViewAntiShakeTime::InitData()
{
	CDvmData* pDvmData1 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT);
	if (pDvmData1 != NULL) 
	{
		CString strIntervalValue = pDvmData1->m_strValue;
		int nIndex = strIntervalValue.toInt();
		m_pCmbIntervalSelect->setCurrentIndex(nIndex);
	}
	else
	{
		CDvmData* pData1 = new CDvmData;
		pData1->m_strName = _T("间隔选择");
		pData1->m_strID = STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT;
		pData1->m_strValue = _T("0");
		m_oTestRecordsDataGroup.AddNewChild(pData1);
	}

	CDvmData* pDvmData2 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_TEST_OBJECT);
	if (pDvmData2 != NULL) 
	{
		CString strTestObjectValue = pDvmData2->m_strValue;
		int nIndex1 = strTestObjectValue.toInt();
		if (nIndex1 < 0)
		{
			nIndex1 = 0;
		}
		m_pCmbTestObject->setCurrentIndex(nIndex1);
	}
	else
	{
		CDvmData* pData2 = new CDvmData;
		pData2->m_strName = _T("测试对象");
		pData2->m_strID = STT_ANTISHAKE_TIME_INIT_TEST_OBJECT;
		pData2->m_strValue = _T("0");
		m_oTestRecordsDataGroup.AddNewChild(pData2);
	}

	CDvmData* pDvmData3 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_BOUT_SET);
	if (pDvmData3 != NULL) 
	{
		CString strBoutSetValue = pDvmData3->m_strValue;
		int nIndex2 = strBoutSetValue.toInt();
		m_pCmbBoutSet->setCurrentIndex(nIndex2);
	}
	else
	{
		CDvmData* pData3 = new CDvmData;
		pData3->m_strName = _T("开出设置");
		pData3->m_strID = STT_ANTISHAKE_TIME_INIT_BOUT_SET;
		pData3->m_strValue = _T("0");
		m_oTestRecordsDataGroup.AddNewChild(pData3);
	}

	CDvmData* pDvmData4 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_STATE1);
	if (pDvmData4 != NULL) 
	{
		CString strInitStateValue = pDvmData4->m_strValue;
		int nIndex3 = strInitStateValue.toInt();
		m_pCmbInitState->setCurrentIndex(nIndex3);
	}
	else
	{
		CDvmData* pData4 = new CDvmData;
		pData4->m_strName = _T("初始状态");
		pData4->m_strID = STT_ANTISHAKE_TIME_INIT_STATE1;
		pData4->m_strValue = _T("0");
		m_oTestRecordsDataGroup.AddNewChild(pData4);
	}

	CDvmData* pDvmData5 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME);
	if (pDvmData5 != NULL) 
	{
		CString strAntiShakeTimeValue = pDvmData5->m_strValue;
		m_pEditAntiShakeTime->setText(strAntiShakeTimeValue);
	}
	else
	{
		CDvmData* pData5 = new CDvmData;
		pData5->m_strName = _T("防抖时间");
		pData5->m_strID = STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME;
		pData5->m_strValue = _T("20");
		m_oTestRecordsDataGroup.AddNewChild(pData5);
	}
	
	CDvmData* pDvmData6 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_SOE_RESOLUTION);
	if (pDvmData6 != NULL) 
	{
		CString strSOEResolutionValue = pDvmData6->m_strValue;
		m_pEditSOEResolution->setText(strSOEResolutionValue);
	}
	else
	{
		CDvmData* pData6 = new CDvmData;
		pData6->m_strName = _T("SOE分辨率");
		pData6->m_strID = STT_ANTISHAKE_TIME_SOE_RESOLUTION;
		pData6->m_strValue = _T("2");
		m_oTestRecordsDataGroup.AddNewChild(pData6);
	}

	int nTestItemCount = 0;
	for (int i = 0; i < STT_ANTISHAKE_TIME_TESTITEM_NUMBER; i++)
	{
		CString strToFind;
		strToFind.Format(_T("TestItem%d"), i + 1);
		CDataGroup* pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.FindByID(strToFind);
		CDvmData* pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_INTERVAL_SELECT);

		if (!pDvmData->m_strValue.IsEmpty())
		{
			nTestItemCount++;
		}
	}

	if (nTestItemCount >= 9 && nTestItemCount <= STT_ANTISHAKE_TIME_TESTITEM_NUMBER)
	{
		m_pBtnAddTestItem->setEnabled(false);
	}
	else
	{
		m_pBtnAddTestItem->setEnabled(true);
	}

	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
}

void QSttMacroParaEditViewAntiShakeTime::SaveXmlParas()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/AntiShakeTime_Paras.xml");
	//CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oTestRecordsDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	//CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QSttMacroParaEditViewAntiShakeTime::UpDateButtonState()
{
	bool bEnableButton = false;  // 默认将按钮设置为不可用

	for (int i = 0; i < STT_ANTISHAKE_TIME_TESTITEM_NUMBER; i++)
	{
		CString strToFind;
		strToFind.Format(_T("TestItem%d"), i+1);
		CDataGroup* pDataGroup = (CDataGroup*)m_oTestRecordsDataGroup.FindByID(strToFind);

		if (pDataGroup != NULL)
		{
			CDvmData* pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);

			if (pDvmData->m_strValue == _T("1"))
			{
				bEnableButton = true;
				break;  
			}
		}
	}
	m_pBtnDeleteTestItem->setEnabled(bEnableButton);
}


void QSttMacroParaEditViewAntiShakeTime::OpenXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;


	CDvmData *pPpDvmData = (CDvmData*)oDataGroup.FindByID(_T("ppxml-file"));
	if (pPpDvmData)
	{
		g_pTheSttTestApp->m_oCommConfig.Set_PpXmlFile(pPpDvmData->m_strValue);
	}
	CDvmData *pDvmData = (CDvmData*)oDataGroup.FindByID(_T("dvm-file"));
	if (pDvmData)
	{
		g_pTheSttTestApp->m_oCommConfig.Set_DvmFile(pDvmData->m_strValue);
	}
}

void QSttMacroParaEditViewAntiShakeTime::UpdateDeviceModelRef()
{
	g_pTheSttTestApp->m_pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;
	InitIntervalListDatas();
	OpenXml();
}


void QSttMacroParaEditViewAntiShakeTime::GetSelectObject()
{
	if (m_pTestRecordsGroupGrid == NULL)
	{
		return;
	}
	m_SelectTestObjetcList.clear();


	for (int nRow = 0;nRow < m_pTestRecordsGroupGrid->rowCount();nRow++)
	{
		QGV_ITEM *pItem = m_pTestRecordsGroupGrid->GetCell(nRow,1); 

		if (pItem == NULL)
		{
			continue;
		}

		if (pItem->checkState() != Qt::Unchecked)
		{	
			CString strID = m_pTestRecordsGroupGrid->m_ObjectIdList.at(nRow);
			m_SelectTestObjetcList.append(strID);
		}
	}
}

BOOL QSttMacroParaEditViewAntiShakeTime::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}
	CString strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if(strItemID.Find(_T("ReadCount")) == -1)
	{
		return FALSE;
	}
	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
	CString strTestCount,strID,strChannelName;
	CDataGroup *pTestMacroUI_Paras = &m_oTestRecordsDataGroup;

	CDvmValue *pDvmValue = NULL;
	int nTestIndex = (strItemID == _T("AntiShakeTimeTest$ReadCount")) ? 1 : strItemID.right(1).toInt()+1;
	int nCount = m_pTestRecordsGroupGrid->GetGridRow(nTestIndex);	
	if (nCount == -1)
	{
		return FALSE;
	}
	strID.Format(_T("TestItem%d"),nCount+1);
	CDataGroup *pDataGroup = (CDataGroup *)pTestMacroUI_Paras->FindByID(strID);
	if(pDataGroup == NULL)
	{
		return FALSE;
	}

	CDvmData *pChannelData = (CDvmData *)pDataGroup->FindByID(_T("TestObject"));
	if (pChannelData->m_strValue == _T("Din_1"))
	{
		strChannelName = _T("合位");
	}
	else if (pChannelData->m_strValue == _T("Din_2"))
	{
		strChannelName = _T("分位");
	}
	else if (pChannelData->m_strValue == _T("Din_5"))
	{
		strChannelName = _T("未储能");
	}
	pDvmValue = new CDvmValue;
	pDvmValue->m_strID = _T("TestObject");
	pDvmValue->m_strName = _T("YX通道");
	pDvmValue->m_strValue = strChannelName;
	pDvmValues->AddNewChild(pDvmValue);
	
	CDvmData *pShakeTimeData = (CDvmData *)pDataGroup->FindByID(_T("AntiShakeTime"));
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("防抖时间");
	pDvmValue->m_strID = _T("AntiShakeTime");
	pDvmValue->m_strValue = pShakeTimeData->m_strValue;
	pDvmValues->AddNewChild(pDvmValue);

	CDvmData *pPulseData = (CDvmData *)pDataGroup->FindByID(_T("PulseWidth"));
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("脉冲宽度");
	pDvmValue->m_strID = _T("PulseWidth");
	pDvmValue->m_strValue = pPulseData->m_strValue;
	pDvmValues->AddNewChild(pDvmValue);

	CDvmData *pEstimateTimesData = (CDvmData *)pDataGroup->FindByID(_T("EstimateTimes"));
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("预计变位次数");
	pDvmValue->m_strID = _T("EstimateTimes");
	pDvmValue->m_strValue = pEstimateTimesData->m_strValue;
	pDvmValues->AddNewChild(pDvmValue);
	
	if ((pRptDvmDataset != NULL)&&(pRptDvmDataset->GetCount()>0))
	{
		CString strValue;
		CDvmData *pActualTimesData = (CDvmData *)pRptDvmDataset->FindByID(pChannelData->m_strValue);
		if (pActualTimesData != NULL)
		{
			CDvmValue* pActualTimesValue = pActualTimesData->FindValueByID(_T("$st_all"));//dingxy 20241113 实际变位次数
			if (pActualTimesValue != NULL)
			{
				strValue = pActualTimesValue->m_strValue;
			}
			else
			{
			strValue = pActualTimesData->m_strValue;
		}
		}
		else
		{
			strValue = _T("0");
		}
		
		pDvmValue = new CDvmValue;
		pDvmValue->m_strName = _T("实际变位次数");
		pDvmValue->m_strID = _T("ActualTimes");
		pDvmValue->m_strValue = strValue;
		pDvmValues->AddNewChild(pDvmValue);
	}
	return TRUE;
}

void QSttMacroParaEditViewAntiShakeTime::DelCmbBoutSetData()
{
	if(m_pTestRecordsGroupGrid == NULL)
	{
		return ;
	}
	for (int i = 0; i < m_pTestRecordsGroupGrid->m_oBoutSetList.size(); ++i)
	{
		CString strID = m_pTestRecordsGroupGrid->m_oBoutSetList[i];
		int nBoutIndex = m_oBoutSetList.FindIndexByID(strID);
		if (nBoutIndex >= 0 && nBoutIndex < m_oBoutSetList.GetCount())
		{
			m_oBoutSetList.RemoveAt(nBoutIndex);
			m_pCmbBoutSet->ShowBaseList(&m_oBoutSetList);
		}
	}	
	m_pTestRecordsGroupGrid->m_oBoutSetList.clear();
}

void QSttMacroParaEditViewAntiShakeTime::AddCmbBoutSetData(QList<QString> oList)
{
	QMap<QString, int> idCount;
	for (int i = 0; i < oList.size(); ++i)
	{
		QString strID = oList[i];
		if (idCount.contains(strID)) 
		{
			idCount[strID]++;
		} 
		else 
		{
			idCount[strID] = 1;
		}
	}

	QMap<QString, int>::const_iterator it = idCount.constBegin();
	while (it != idCount.constEnd()) 
	{
		CString strID,strName;
		strID = it.key();
		strName.Format(_T("开出%d"),strID.right(1).toInt());
		int nCount = FindBoutChans(strName);
		if ((it.value() == 2) || (it.value() < 2 && nCount != 2))
		{	
			int nIndex = m_oBoutSetList.FindIndexByID(strID);
			if (nIndex < 0)
			{
				CDvmData *pBoutDvmData = new CDvmData;
				pBoutDvmData->m_strID = strID;	
				pBoutDvmData->m_strName = strName;
				m_oBoutSetList.AddTail(pBoutDvmData);
			}
		}
		++it;
	}
	m_oBoutSetList.SortByID();
	m_pCmbBoutSet->ShowBaseList(&m_oBoutSetList);
}

int QSttMacroParaEditViewAntiShakeTime::FindBoutChans(CString strName)
{
	int nCount = 0;
	if(m_pTestRecordsGroupGrid == NULL)
	{
		return 0;
	}
	int nRowCount = m_pTestRecordsGroupGrid->rowCount();

	if (nRowCount <= 0)
	{
		return 0;
	}

	for (int nRow = 0; nRow < nRowCount; ++nRow)
	{
		QGV_ITEM* pGV_ITEM = m_pTestRecordsGroupGrid->GetCell(nRow, 4);
		if (pGV_ITEM != NULL)
		{
			CString strText = pGV_ITEM->text();
			if (strText == strName)
			{
				nCount++;
			}
		}
	}	
	return nCount;
}


void QSttMacroParaEditViewAntiShakeTime::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	m_oTestRecordsDataGroup.Copy(pParas);//dingxy 20241114 getdata
	SaveXmlParas();
}


void QSttMacroParaEditViewAntiShakeTime::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
}


void QSttMacroParaEditViewAntiShakeTime::ShowReport( CDvmValues *pValues )
{
	//g_theTestCntrFrame->UpdateRptHtml();
}

void QSttMacroParaEditViewAntiShakeTime::AddShowSoeReports( CDvmDataset *pSoeRptDataset )
{
	if (m_pDinEventGroupGrid == NULL)
	{
		return;
	}

	m_pDinEventGroupGrid->AddShowReports(pSoeRptDataset);
}

void QSttMacroParaEditViewAntiShakeTime::UpdateDinCount( CDvmValues *pValues,CDvmDataset *pSoeRptDataset,CString strItemID)
{
	if (m_pTestRecordsGroupGrid == NULL)
	{
		return;
	}

	m_pTestRecordsGroupGrid->UpdateDatas(pValues,pSoeRptDataset,strItemID);
}

void QSttMacroParaEditViewAntiShakeTime::OnViewTestStart()
{
	//SaveXmlParas();
	m_pCmbIntervalSelect->setDisabled(true);
	m_pCmbTestObject->setDisabled(true);
	m_pCmbBoutSet->setDisabled(true);
	m_pCmbInitState->setDisabled(true);
	m_pEditAntiShakeTime->setDisabled(true);
	m_pEditSOEResolution->setDisabled(true);
	m_pBtnAddTestItem->setDisabled(true);
	m_pBtnDeleteTestItem->setDisabled(true);
	m_pTestRecordsGroupGrid->setDisabled(true);
	//m_pDinEventGroupGrid->setDisabled(true);
	GetSelectObject();
}

void QSttMacroParaEditViewAntiShakeTime::OnViewTestStop()
{
	m_pCmbIntervalSelect->setDisabled(false);
	m_pCmbTestObject->setDisabled(false);
	m_pCmbBoutSet->setDisabled(false);
	m_pCmbInitState->setDisabled(false);
	m_pEditAntiShakeTime->setDisabled(false);
	m_pEditSOEResolution->setDisabled(false);
	m_pTestRecordsGroupGrid->setDisabled(false);
	//m_pDinEventGroupGrid->setDisabled(false);


	int nRecordCount = 0;
	CDvmData* pItemNumData = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ITEM_NUM);
	if (pItemNumData != NULL) 
	{
		nRecordCount = pItemNumData->m_strValue.toInt();
	}

	if (nRecordCount > STT_ANTISHAKE_TIME_TESTITEM_NUMBER)
	{
		m_pBtnAddTestItem->setDisabled(true);
	}
	else
	{
		m_pBtnAddTestItem->setDisabled(false);
	}

	UpDateButtonState();
}

