#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"
#include "QSttMacroParaEditViewAntiShakeTime.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "Grid/QSttAntiShakeTimeTestItemsGroupGrid.h"
#include "Grid/QSttAntiShakeTimeDinEventGroupGrid.h"
#include "../Module/CommonCtrl_QT/QLongLineEdit.h"

QSttMacroParaEditViewAntiShakeTime::QSttMacroParaEditViewAntiShakeTime(QWidget *parent)
{
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

	m_pTopLayout = NULL;     	  
	m_pTotalLayout = NULL;      

	m_pBtnAddTestItem = NULL;   
	m_pBtnDeleteTestItem = NULL;

	m_pTopTabWidget = NULL;
	m_pMiddleTabWidget = NULL;
	m_pBottomTabWidget = NULL;
	m_pTopWidget = NULL;
	m_pMiddleWidget = NULL;
	m_pBottomWidget = NULL;

	InitUI();
	InitConnections();
	OpenXmlFile();
	Initcontrol();

	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
}

QSttMacroParaEditViewAntiShakeTime::~QSttMacroParaEditViewAntiShakeTime()
{
	DeleteIntervalListDatas();
	m_oTestObjectList.RemoveAll();
}

void QSttMacroParaEditViewAntiShakeTime::InitUI()
{     
	m_pTotalLayout = new QVBoxLayout(this);
	m_pTopTabWidget = new QTabWidget(this);
	m_pMiddleTabWidget = new QTabWidget(this);
	m_pBottomTabWidget = new QTabWidget(this);

	// 创建部件
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
	m_pEditAntiShakeTime = new QLongLineEdit();

	strText = _T("毫秒");
	m_pLabelTimeMsec = new QLabel(this);
	m_pLabelTimeMsec->setText(strText);

	strText = _T("SOE分辨率:   ");
	m_pLabelSOEResolution = new QLabel(this);
	m_pLabelSOEResolution->setText(strText);
	m_pEditSOEResolution = new QLongLineEdit();

	strText = _T("毫秒");
	m_pLabelSOEMsec = new QLabel(this);
	m_pLabelSOEMsec->setText(strText);

	strText = _T("添加测试项");
	m_pBtnAddTestItem = new QPushButton(this);
	m_pBtnAddTestItem->setText(strText);

	strText = _T("删除测试项");
	m_pBtnDeleteTestItem = new QPushButton(this);
	m_pBtnDeleteTestItem->setText(strText);

	m_pTopWidget = new QWidget(this);
	m_pTopLayout = new QGridLayout(m_pTopWidget);
	QLabel *spacerLabel = new QLabel();
	spacerLabel->setFixedWidth(20); // 设置宽度为 10（根据需要调整间距大小）

	QLabel *spacerLabel1 = new QLabel();
	spacerLabel1->setFixedWidth(20); // 设置宽度为 10（根据需要调整间距大小）

	m_pTopLayout->addWidget(m_pLabelInterval, 0, 1);
	m_pTopLayout->addWidget(m_pCmbIntervalSelect, 0, 2);
	m_pTopLayout->addWidget(spacerLabel1, 0, 3); // 在这里插入间距
	m_pTopLayout->addWidget(m_pLabelTestObject, 0, 4);
	m_pTopLayout->addWidget(m_pCmbTestObject, 0, 5);

	m_pTopLayout->addWidget(spacerLabel, 0, 7); // 在这里插入间距
	m_pTopLayout->addWidget(m_pLabelAntiShakeTime, 0, 8);
	m_pTopLayout->addWidget(m_pEditAntiShakeTime, 0, 9);
	m_pTopLayout->addWidget(m_pLabelTimeMsec, 0, 10);

	m_pTopLayout->addWidget(m_pLabelSOEResolution, 0, 11);
	m_pTopLayout->addWidget(spacerLabel, 0, 12); // 在这里插入间距
	m_pTopLayout->addWidget(m_pEditSOEResolution, 0, 13);
	m_pTopLayout->addWidget(m_pLabelSOEMsec, 0, 14);

	m_pTopLayout->addWidget(m_pLabelBoutSet, 1, 1);
	m_pTopLayout->addWidget(m_pCmbBoutSet, 1, 2);
	m_pTopLayout->addWidget(spacerLabel1, 1, 3); // 在这里插入间距
	m_pTopLayout->addWidget(m_pLabelInitState, 1, 4);
	m_pTopLayout->addWidget(m_pCmbInitState, 1, 5);

	m_pTopLayout->addWidget(spacerLabel, 1, 7); // 在这里插入间距
	m_pTopLayout->addWidget(m_pBtnAddTestItem, 1, 9);
	m_pTopLayout->addWidget(m_pBtnDeleteTestItem, 1, 13);

	// 创建中间布局
	m_pMiddleWidget = new QWidget(m_pTopTabWidget);
	m_pMiddleLayout = new QVBoxLayout();
	m_pMiddleLayout->setContentsMargins(0, 0, 0, 0); // 去除内边距
	m_pTestRecordsGroupGrid = new QSttAntiShakeTimeTestItemsGroupGrid(this,m_pMiddleWidget);
	m_pTestRecordsGroupGrid->InitGrid();
	m_pMiddleLayout->addWidget(m_pTestRecordsGroupGrid);

	//创建下边布局
	m_pBottomWidget = new QWidget(m_pMiddleTabWidget);
	m_pBottomLayout = new QVBoxLayout();
	m_pBottomLayout->setContentsMargins(0, 0, 0, 0);
	m_pDinEventGroupGrid = new QSttAntiShakeTimeDinEventGroupGrid(m_pBottomWidget);
	m_pDinEventGroupGrid->InitUI();
	m_pDinEventGroupGrid->setFont(*g_pSttGlobalFont);
	m_pBottomLayout->addWidget(m_pDinEventGroupGrid);
	m_pBottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 将顶部和中间布局添加到Tab Widget中
	m_pTopTabWidget->setLayout(m_pTopLayout);
	m_pMiddleTabWidget->setLayout(m_pMiddleLayout);
	m_pBottomTabWidget->setLayout(m_pBottomLayout);

	// 将Tab Widget添加到总体布局管理器中
	m_pTotalLayout->addWidget(m_pTopTabWidget);
	m_pTotalLayout->addWidget(m_pMiddleTabWidget);
	m_pTotalLayout->addWidget(m_pBottomTabWidget);

	m_pEditAntiShakeTime->InitCoverage(0,1000);
	m_pEditSOEResolution->InitCoverage(0,1000);
	setLayout(m_pTotalLayout);

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
	// 设置QComboBox的固定宽度
	m_pCmbIntervalSelect->setFixedWidth(95);
	m_pCmbIntervalSelect->setFixedHeight(30); // 设置高度，保持与其他控件一致
	m_pCmbBoutSet->setFixedWidth(95);
	m_pCmbBoutSet->setFixedHeight(30); // 设置高度，保持与其他控件一致
	m_pCmbTestObject->setFixedWidth(95);
	m_pCmbInitState->setFixedWidth(95);

	// 设置QLineEdit的固定宽度
	m_pEditAntiShakeTime->setFixedWidth(95);
	m_pEditSOEResolution->setFixedWidth(95);
	
	// 设置QPushButton的固定宽度
	m_pBtnAddTestItem->setFixedWidth(100);
	m_pBtnDeleteTestItem->setFixedWidth(100);

	// 使用样式表设置QComboBox、QLineEdit和QPushButton的高度与固定宽度相同
	CString strStyle = "QComboBox, QLineEdit, QPushButton { height: 30px; }"; // 设置高度为30像素，您可以根据需要调整大小
	m_pCmbIntervalSelect->setStyleSheet(strStyle);
	m_pCmbTestObject->setStyleSheet(strStyle);
	m_pCmbBoutSet->setStyleSheet(strStyle);
	m_pCmbInitState->setStyleSheet(strStyle);

	m_pEditAntiShakeTime->setStyleSheet(strStyle);
	m_pEditSOEResolution->setStyleSheet(strStyle);

	m_pBtnAddTestItem->setStyleSheet(strStyle);
	m_pBtnDeleteTestItem->setStyleSheet(strStyle);

	CString strInitState[2] = { _T("断开"), _T("闭合")};
	
	m_pCmbInitState->addItem(strInitState[0]);
	m_pCmbInitState->addItem(strInitState[1]);
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
		m_oIntervalList.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();
		long nIndex = 0;

		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID.Find(STT_ANTISHAKE_TIME_Dataset_ID) >= 0)
			{
				pDvmDatasetRef->Append(*pCurrDataset);

				if (nIndex == 0)//将对应的ID设置为第一个遥测数据集的路径,方便后续从装置读取数据
				{
					pDvmDatasetRef->m_strID.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
				}
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
	CDvmData *pDvmDataRef = NULL;
	
	while (posDataset)
	{
		pCurrData = (CDvmData *)pDataset->GetNext(posDataset);

		// 		if (pCurrData->m_strDataType == "BOOL" || pCurrData->m_strDataType == "INT")
		// 		{
		m_oTestObjectList.AddTail(pCurrData);
		//		}
	}

	m_pCmbTestObject->ShowBaseList(&m_oTestObjectList);
}

void QSttMacroParaEditViewAntiShakeTime::InitBoutSetListDatas()
{
	m_oBoutSetList.DeleteAll();
	CString strName;

	for (int nIndex = 1; nIndex <= g_nBoutCount; nIndex++)
	{
		CDvmData *pDvmData = new CDvmData;
		strName.Format(_T("开出%d"), nIndex);
		pDvmData->m_strName = strName;
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
		nEstimateTimesTop = 0;			//预计变位次数
	} 
	else
	{
		nEstimateTimesTop = 0;
	}

	if (nPulseWidthBottom > nAntiShakeTime) 
	{
		nEstimateTimesBottom = 2;			    //实际变位次数
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
        if(pDataGroup != NULL && pDvmData->m_strValue.IsEmpty())
		{
			int nPulseWidth = (nTestItemNumber % 2 == 0) ? nPulseWidthBottom : nPulseWidthTop;
			int nEstimateTimes = (nTestItemNumber % 2 == 0) ? nEstimateTimesBottom : nEstimateTimesTop;

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_SELECT);
			long nValue = CString_To_long(pDvmData->m_strValue);
			if(pDvmData->m_strValue.IsEmpty() || nValue == nZero)
	{
				pDvmData->m_strValue = "0";
	}
			else if (nValue == nSelectValue)
	{
				pDvmData->m_strValue = "1";
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_INTERVAL_SELECT);
			if (pDvmData != NULL) 
		{
				pDvmData->m_strValue = CString::number(nInterval);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_TEST_OBJECT);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nTestObject);
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_BOUT_SET);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nBoutSet); 
				m_pCmbBoutSet->setItemData(nBoutSet, QVariant(0), Qt::UserRole - 1);
				for (int i = 0; i < g_nBoutCount; ++i) 
				{
					if (!m_pCmbBoutSet->itemData(i, Qt::UserRole - 1).isValid()) 
					{
						m_pCmbBoutSet->setCurrentIndex(i);
						break;
					}
				}
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_INIT_STATE);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = CString::number(nInitState);
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

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_ACTUAL_TIMES);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = "-";
			}

			pDvmData = (CDvmData*)pDataGroup->FindByID(STT_ANTISHAKE_TIME_TEST_RESUL);
			if (pDvmData != NULL) 
			{
				pDvmData->m_strValue = "-";
			}
			nItemsToAdd--;
		}
		nTestItemNumber++;
	}

	UpDateItemNumValue(nTestItemNumber - 1);
	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
	SaveXmlParas();
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
		pData->m_strName = "测试项数量";
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
	SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_DeleteTestItem()
{	
	int nSelectValue = 1;				  //CheckBox勾选值
	int nDeletedTestItems = 0;
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
				int nIndex = strData.toInt();
				if (nIndex != -1)
				{
					m_pCmbBoutSet->setItemData(nIndex, QVariant(), Qt::UserRole - 1);
				}
				m_oTestRecordsDataGroup.Remove(pDataGroup);
				nDeletedTestItems++; // 每删除一个测试项，计数器加一
			}
		}
	}

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
			pData1->m_strName = "选择";
			pData1->m_strID = STT_ANTISHAKE_TIME_SELECT;
			pData1->m_strValue = "";
			pDataGroup->AddNewChild(pData1);

			CDvmData* pData2 = new CDvmData;
			pData2->m_strName = "间隔选择";
			pData2->m_strID = STT_ANTISHAKE_TIME_INTERVAL_SELECT;
			pData2->m_strValue = "";
			pDataGroup->AddNewChild(pData2);

			CDvmData* pData3 = new CDvmData;
			pData3->m_strName = "测试对象";
			pData3->m_strID = STT_ANTISHAKE_TIME_TEST_OBJECT;
			pData3->m_strValue = "";
			pDataGroup->AddNewChild(pData3);

			CDvmData* pData4 = new CDvmData;
			pData4->m_strName = "开出设置";
			pData4->m_strID = STT_ANTISHAKE_TIME_BOUT_SET;
			pData4->m_strValue = "";
			pDataGroup->AddNewChild(pData4);

			CDvmData* pData5 = new CDvmData;
			pData5->m_strName = "初始状态";
			pData5->m_strID = STT_ANTISHAKE_TIME_INIT_STATE;
			pData5->m_strValue = "";
			pDataGroup->AddNewChild(pData5);

			CDvmData* pData6 = new CDvmData;
			pData6->m_strName = "脉冲宽度(ms)";
			pData6->m_strID = STT_ANTISHAKE_TIME_PULSE_WIDTH;
			pData6->m_strValue = "";
			pDataGroup->AddNewChild(pData6);

			CDvmData* pData7  =new CDvmData;
			pData7->m_strName = "预计变位次数";
			pData7->m_strID = STT_ANTISHAKE_TIME_ESTIMATE_TIMES;
			pData7->m_strValue = "";
			pDataGroup->AddNewChild(pData7);

			CDvmData* pData8 = new CDvmData;
			pData8->m_strName = "实际变位次数";
			pData8->m_strID = STT_ANTISHAKE_TIME_ACTUAL_TIMES;
			pData8->m_strValue = "";
			pDataGroup->AddNewChild(pData8);

			CDvmData* pData9 = new CDvmData;
			pData9->m_strName = "测试结果";
			pData9->m_strID = STT_ANTISHAKE_TIME_TEST_RESUL;
			pData9->m_strValue = "";
			pDataGroup->AddNewChild(pData9);

			m_oTestRecordsDataGroup.AddNewChild(pDataGroup);
	}
	}
	CDvmData* pDvmData1 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ITEM_NUM);
	CString strIntervalValue = pDvmData1->m_strValue;
	int nIndex = strIntervalValue.toInt();
	UpDateItemNumValue(nIndex - nDeletedTestItems);
	UpDataTestItemName();
	m_pTestRecordsGroupGrid->ShowDatas(&m_oTestRecordsDataGroup);
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
		pData->m_strName = "间隔选择";
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
		pData->m_strName = "测试对象";
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
		pData->m_strName = "开出设置";
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
		pData->m_strName = "初始状态";
		pData->m_strID = STT_ANTISHAKE_TIME_INIT_STATE1;
		pData->m_strValue = strText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_EditAntiShakeTime()
{
	CString strNewText = m_pEditAntiShakeTime->text();
	CDvmData* pDvmData = static_cast<CDvmData*>(m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME));
	if (pDvmData != NULL) 
	{
	pDvmData->m_strValue = strNewText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = "防抖时间";
		pData->m_strID = STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME;
		pData->m_strValue = strNewText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}

	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::slot_EditSOEResolution()
{
	CString strNewText = m_pEditSOEResolution->text();
	CDvmData* pDvmData = static_cast<CDvmData*>(m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_SOE_RESOLUTION));
	if (pDvmData != NULL) 
	{
	pDvmData->m_strValue = strNewText;
	}
	else
	{
		CDvmData* pData = new CDvmData;
		pData->m_strName = "SOE分辨率";
		pData->m_strID = STT_ANTISHAKE_TIME_SOE_RESOLUTION;
		pData->m_strValue = strNewText;
		m_oTestRecordsDataGroup.AddNewChild(pData);
	}
	//SaveXmlParas();
}

void QSttMacroParaEditViewAntiShakeTime::Initcontrol()
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
		pData1->m_strName = "间隔选择";
		pData1->m_strID = STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT;
		pData1->m_strValue = "0";
		m_oTestRecordsDataGroup.AddNewChild(pData1);
	}

	CDvmData* pDvmData2 = (CDvmData*)m_oTestRecordsDataGroup.FindByID(STT_ANTISHAKE_TIME_INIT_TEST_OBJECT);
	if (pDvmData2 != NULL) 
	{
	CString strTestObjectValue = pDvmData2->m_strValue;
		int nIndex1 = strTestObjectValue.toInt();
		m_pCmbTestObject->setCurrentIndex(nIndex1);
	}
	else
	{
		CDvmData* pData2 = new CDvmData;
		pData2->m_strName = "测试对象";
		pData2->m_strID = STT_ANTISHAKE_TIME_INIT_TEST_OBJECT;
		pData2->m_strValue = "0";
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
		pData3->m_strName = "开出设置";
		pData3->m_strID = STT_ANTISHAKE_TIME_INIT_BOUT_SET;
		pData3->m_strValue = "0";
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
		pData4->m_strName = "初始状态";
		pData4->m_strID = STT_ANTISHAKE_TIME_INIT_STATE1;
		pData4->m_strValue = "0";
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
		pData5->m_strName = "防抖时间";
		pData5->m_strID = STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME;
		pData5->m_strValue = "20";
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
		pData6->m_strName = "SOE分辨率";
		pData6->m_strID = STT_ANTISHAKE_TIME_SOE_RESOLUTION;
		pData6->m_strValue = "2";
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
}

void QSttMacroParaEditViewAntiShakeTime::SaveXmlParas()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/AntiShakeTime_Paras.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oTestRecordsDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
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

			if (pDvmData->m_strValue == "1")
			{
				bEnableButton = true;
				break;  
			}
		}
	}
	m_pBtnDeleteTestItem->setEnabled(bEnableButton);
}
