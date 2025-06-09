#include "SttMacroParaEditViewMuAutoTest.h"
#include "../../RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../../RecordTest/UI/MUTest/SttIecRecordCbInterface.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewMuAutoTest::QSttMacroParaEditViewMuAutoTest(QWidget* parent) :CSttMacroParaEditViewOriginal(parent)
{
	
	m_pMainVLayout = NULL;
	m_pMUAutoParaSet= NULL;
	m_pMuAUtoParaDisplay = NULL;
	m_pTreeLayout = NULL;
	m_pParaLayout = NULL;
	m_pParaKidLayout = NULL;
	m_pParaKidLayout_1 = NULL;
	m_pParaKidLayout_2 = NULL;
	m_pParaKidLayout_3 = NULL;
	m_pParaKidLayout_4 = NULL;
	m_pButtonLayout = NULL;
	m_pSelectall = NULL;
	m_pClear = NULL;
	m_pOtherparameters = NULL;
	m_pRefresh = NULL;
	m_pParameterSet = NULL; 
	m_pPTRatio = NULL;
	m_pCTRatio = NULL;
	m_pNumTests = NULL;
	m_pVolEdit_0 = NULL;
	m_pVolEdit_1 = NULL;
	m_pCurEdit_0 = NULL;
	m_pCurEdit_1 = NULL;
	m_pTestEdit = NULL;
	m_pAotuTestTree = NULL;
    m_pPTSLash = NULL;
    m_pCTSLash = NULL;
	
    OpenTestTestMngrFile(_T(""));
    InitUI();
	InitConnection();
	SetDatas(&m_oMUAutoTestDataGroup);
	SetMUAutoTestWidgetFont();
  
}

QSttMacroParaEditViewMuAutoTest::~QSttMacroParaEditViewMuAutoTest()
{
	if(m_pAotuTestTree != NULL)
	{
	    delete m_pAotuTestTree;
	}
}

void QSttMacroParaEditViewMuAutoTest::InitConnection()
{
	connect(m_pOtherparameters,SIGNAL(clicked()), this, SLOT(slot_Otherparameters()));
	connect(m_pRefresh,SIGNAL(clicked()), this, SLOT(slot_Refresh()));
	connect(m_pSelectall,SIGNAL(clicked()), this, SLOT(slot_AllSelected()));
	connect(m_pClear,SIGNAL(clicked()), this, SLOT(slot_Clear()));
	connect(m_pAotuTestTree->m_pTreeWidget,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(slot_TreeItemSelectionChanged(QTreeWidgetItem *,int)));
	connect(m_pAotuTestTree->m_pTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_handleItemChanged(QTreeWidgetItem*, int)));
	connect(m_pVolEdit_0,SIGNAL(editingFinished()),this,SLOT(slot_PTCTLineEditChanged()));
	connect(m_pVolEdit_1,SIGNAL(editingFinished()),this,SLOT(slot_PTCTLineEditChanged()));
	connect(m_pCurEdit_0,SIGNAL(editingFinished()),this,SLOT(slot_PTCTLineEditChanged()));
	connect(m_pCurEdit_1,SIGNAL(editingFinished()),this,SLOT(slot_PTCTLineEditChanged()));
	connect(m_pTestEdit,SIGNAL(editingFinished()),this,SLOT(slot_PTCTLineEditChanged()));	

#ifdef _PSX_QT_LINUX_
    connect(m_pVolEdit_0,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));	
	connect(m_pVolEdit_1,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pCurEdit_0,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pCurEdit_1,SIGNAL(clicked()),this,SLOT(slot_FloatLineEditChanged()));
	connect(m_pTestEdit,SIGNAL(clicked()),this,SLOT(slot_LongLineEditChanged()()));
#endif
		
}	


void QSttMacroParaEditViewMuAutoTest::GetDatas(CDataGroup *pParas)
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_oMUAutoTestDataGroup.CopyChildren(pParas);
	//UpdateTreeWidgetItem(pParas);
}

void QSttMacroParaEditViewMuAutoTest::InitUI()
{
  
	this->resize(256,600);
	m_pMainVLayout = new QHBoxLayout(); 
	m_pMUAutoParaSet = new QVBoxLayout();
	m_pMuAUtoParaDisplay = new QVBoxLayout();
	m_pTreeLayout = new QHBoxLayout();
	m_pButtonLayout = new QHBoxLayout();	
	m_pParaLayout = new QHBoxLayout();
	m_pParaKidLayout_1 = new QHBoxLayout();
	m_pParaKidLayout_2 = new QHBoxLayout();
	m_pParaKidLayout_3 = new QHBoxLayout();
	m_pParaKidLayout_4 = new QHBoxLayout();
	m_pParaKidLayout = new QVBoxLayout();
	m_pSelectall = new QPushButton();	  
	m_pClear = new QPushButton();		  
	m_pOtherparameters = new QPushButton();
	m_pRefresh = new QPushButton();
	m_pParameterSet = new QGroupBox();
	m_pPTRatio = new QLabel();
	m_pCTRatio = new QLabel();
	m_pNumTests = new QLabel();
	m_pPTSLash = new QLabel();
	m_pCTSLash= new QLabel();
	m_pVolEdit_0 = new QFloatLineEdit();
	m_pVolEdit_1 = new QFloatLineEdit();
	m_pCurEdit_0 = new QFloatLineEdit();
	m_pCurEdit_1 = new QFloatLineEdit();
	m_pTestEdit = new QLongLineEdit();
	m_pAotuTestTree = new QSttMacroParaEditViewMuTreeWidget();

	CString strButton;
	strButton = _T("全选");
	m_pSelectall->setText(strButton);
	m_pSelectall->adjustSize();
	strButton= _T("清除");
	m_pClear->setText(strButton);
	m_pClear->adjustSize();
	strButton = _T("其他参数");
	m_pOtherparameters->setText(strButton);
	m_pOtherparameters->adjustSize();
	strButton = _T("刷新");
	m_pRefresh->setText(strButton);
	m_pRefresh->adjustSize();
	CString strGroupbox = _T("参数设置");
    m_pParameterSet->setTitle(strGroupbox);
	CString strLabel;
	strLabel = _T("PT变比");
    m_pPTRatio->setText(strLabel);
	strLabel = _T("CT变比");
	m_pCTRatio->setText(strLabel);
	strLabel = _T("测试次数");
	m_pNumTests->setText(strLabel);
    strLabel = _T("/");
	m_pPTSLash->setText(strLabel);
	m_pCTSLash->setText(strLabel);
	m_pTestEdit->setFixedWidth(50);
	m_pButtonLayout->addStretch(1);
	m_pButtonLayout->addWidget(m_pSelectall);
	m_pButtonLayout->addStretch(2);
	m_pButtonLayout->addWidget(m_pClear);
	m_pButtonLayout->addStretch(1);
    m_pAotuTestTree->InitTreeUI();
	m_pTreeLayout->addWidget(m_pAotuTestTree);

	m_pParaKidLayout_1->addWidget(m_pPTRatio);
	m_pParaKidLayout_1->addWidget(m_pVolEdit_0);
	m_pParaKidLayout_1->addWidget(m_pPTSLash);
	m_pParaKidLayout_1->addWidget(m_pVolEdit_1);
	m_pParaKidLayout_2->addWidget(m_pCTRatio);
	m_pParaKidLayout_2->addWidget(m_pCurEdit_0);
	m_pParaKidLayout_2->addWidget(m_pCTSLash);
	m_pParaKidLayout_2->addWidget(m_pCurEdit_1);
	m_pParaKidLayout_3->addWidget(m_pNumTests);
	m_pParaKidLayout_3->addWidget(m_pTestEdit);
	m_pParaKidLayout_3->addStretch(1);
	m_pParaKidLayout_4->addWidget(m_pOtherparameters);
    m_pParaKidLayout_4->addStretch(1);
	m_pParaKidLayout_4->addWidget(m_pRefresh);
    m_pParaKidLayout->addLayout(m_pParaKidLayout_1);
	m_pParaKidLayout->addLayout(m_pParaKidLayout_2);
	m_pParaKidLayout->addLayout(m_pParaKidLayout_3);
	m_pParaKidLayout->addLayout(m_pParaKidLayout_4);
    m_pParameterSet->setLayout(m_pParaKidLayout);
    m_pParaLayout->addWidget(m_pParameterSet);
	m_pMUAutoParaSet->addLayout(m_pButtonLayout);
	m_pMUAutoParaSet->addLayout(m_pTreeLayout);
    m_pMUAutoParaSet->addLayout(m_pParaLayout);
    m_pMainVLayout->addLayout(m_pMUAutoParaSet);
	this->setLayout(m_pMainVLayout);
    InitEditCoverage();
	   
}
void QSttMacroParaEditViewMuAutoTest::slot_Otherparameters()
{
	QSttMacroParaEditViewOtherSetDlg dlg(this);
	dlg.InitUI();
	dlg.GetDatas(&m_oMUAutoTestDataGroup);
	dlg.InitData();
	dlg.InitConnection();
	dlg.setFont(*g_pSttGlobalFont);
	dlg.exec();
    
}

void QSttMacroParaEditViewMuAutoTest::SetDatas(CDataGroup *pParas)
{
	 double fValue;
	 CString strValue;
     BOOL nIsGetValue = FALSE;	

	 nIsGetValue = pParas->GetDataValue(STT_MUAUTOTEST_LINEDIT_VOL_LPTRATIO,fValue);
     m_pVolEdit_0->SetValue((float)fValue);
	 nIsGetValue = pParas->GetDataValue(STT_MUAUTOTEST_LINEDIT_VOL_RPTRATIO,fValue);
	 m_pVolEdit_1->SetValue((float)fValue);
     nIsGetValue = pParas->GetDataValue(STT_MUAUTOTEST_LINEDIT_CUR_LCTRATIO,fValue);
	 m_pCurEdit_0->SetValue((float)fValue);
     nIsGetValue = pParas->GetDataValue(STT_MUAUTOTEST_LINEDIT_CUR_RCTRATIO,fValue);
	 m_pCurEdit_1->SetValue((float)fValue);
	 nIsGetValue = pParas->GetDataValue(STT_MUAUTOTEST_LINEDIT_TESTNUMBER,strValue);
	 m_pTestEdit->setText(strValue);

     SetTreeWidgetItemValue(m_pAotuTestTree->m_pAutomatedTestItem,STT_MUAUTOTEST_TREEITEM_AUTOMATEDTEST,pParas);   
     SetTreeWidgetItemValue(m_pAotuTestTree->m_pAccuracyTestItem,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST,pParas);   
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pZeroDrifTestItem,STT_MUAUTOTEST_TREEITEM_ZEROTEST,pParas);     
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pFirWeekWaveTestItem,STT_MUAUTOTEST_TREEITEM_WAVETEST,pParas); 
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pTimAccuracyItem,STT_MUAUTOTEST_TREEITEM_TIME_TIMEACCURACY,pParas);  
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPunAccuracyItem,STT_MUAUTOTEST_TREEITEM_TIME_PUNACCURACY,pParas); 
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pTimeTestItem,STT_MUAUTOTEST_TREEITEM_TIMETEST,pParas);  
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_2,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER002,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_100,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER100,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_5,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER005,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_10,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER010,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_50,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER050,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_80,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER080,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_120,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER120,pParas);
	 SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_150,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER150,pParas);
 
}
void QSttMacroParaEditViewMuAutoTest::SetTreeWidgetItemValue(QExBaseTreeWidgetItem * pItem,CString strID,CDataGroup *pParas)
{	
	BOOL nIsSelected;
	CDvmData* pMUCurData = (CDvmData*)pParas->FindByID(strID);

	if (pMUCurData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("不存在当前测试项节点"));//lcq	
		return;
	}

    pItem->m_pItemData = (CExBaseObject *)pMUCurData->Clone();
	
	nIsSelected = CString_To_long(pMUCurData->m_strValue);

	if(nIsSelected)
	{
		pItem->setCheckState(0,Qt::Checked); 
	}
	else
	{
		pItem->setCheckState(0,Qt::Unchecked); 
	}

}

void QSttMacroParaEditViewMuAutoTest::UpdateTreeWidgetItem(CDataGroup *pParas)
{
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pAutomatedTestItem,STT_MUAUTOTEST_TREEITEM_AUTOMATEDTEST,pParas);   
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pAccuracyTestItem,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST,pParas);    
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pZeroDrifTestItem,STT_MUAUTOTEST_TREEITEM_ZEROTEST,pParas);     
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pFirWeekWaveTestItem,STT_MUAUTOTEST_TREEITEM_WAVETEST,pParas); 
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPunAccuracyItem,STT_MUAUTOTEST_TREEITEM_TIME_PUNACCURACY,pParas); 
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pTimAccuracyItem,STT_MUAUTOTEST_TREEITEM_TIME_TIMEACCURACY,pParas);  
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_2,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER002,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_100,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER100,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_5,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER005,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_10,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER010,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_50,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER050,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_80,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER080,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_120,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER120,pParas);
	SetTreeWidgetItemValue(m_pAotuTestTree->m_pPercentItem_150,STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER150,pParas);
}

void QSttMacroParaEditViewMuAutoTest::slot_AllSelected()
{
 	QTreeWidgetItemIterator ite(m_pAotuTestTree->m_pTreeWidget);
 	while(*ite)
 	{
		if((*ite)->checkState(0) == Qt::Unchecked)
		{
 		(*ite)->setCheckState(0,Qt::Checked); 
			QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)*ite;
			CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;
			m_oMUAutoTestDataGroup.SetDataValue(strItemID,"1");
		}
 		ite++;
 	}

}

void QSttMacroParaEditViewMuAutoTest::slot_Clear()
{
	QTreeWidgetItemIterator ite(m_pAotuTestTree->m_pTreeWidget);
	while(*ite)
	{
		if((*ite)->checkState(0) == Qt::Checked)
		{
			(*ite)->setCheckState(0,Qt::Unchecked); 
			QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)*ite;
			CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;
			m_oMUAutoTestDataGroup.SetDataValue(strItemID,"0");		
		}
		ite++;
	}

}

void QSttMacroParaEditViewMuAutoTest::slot_handleItemChanged(QTreeWidgetItem* item, int column)
{

/*#ifdef _PSX_QT_LINUX_*/
// 	if (m_pAotuTestTree->m_pTreeWidget->IsScrollMoving())
// 	{
// 		return;
// 	}
/*#endif*/

	int nCount = item->childCount();

	if(nCount > 0)
	{
        CheckChildItems(item, item->checkState(column)); 
	}

	else
	{
		return;
	}

}

void QSttMacroParaEditViewMuAutoTest::CheckChildItems(QTreeWidgetItem* item, Qt::CheckState Ischecked)
{
	int nCount = item->childCount();

	for (int i = 0; i < nCount; ++i)
	{
		QTreeWidgetItem* pItemChild = item->child(i);
		pItemChild->setCheckState(0, Ischecked);

		QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)pItemChild;

	if (pExBaseTreeWidgetItem->m_pItemData == NULL)
	{
		return;
	}

	CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;

	if (item->checkState(0) == Qt::Checked)
	{
		m_oMUAutoTestDataGroup.SetDataValue(strItemID,"1");
	}
	else
	{
		m_oMUAutoTestDataGroup.SetDataValue(strItemID,"0");
	} 

		CheckChildItems(pItemChild, Ischecked); 
	}
}
void QSttMacroParaEditViewMuAutoTest::slot_Refresh()
{
	if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
	}
}

void QSttMacroParaEditViewMuAutoTest::slot_TreeItemSelectionChanged(QTreeWidgetItem * pItem, int colunm)
{

/*#ifdef _PSX_QT_LINUX_*/
// 	if (m_pAotuTestTree->m_pTreeWidget->IsScrollMoving() && m_pAotuTestTree->m_nIsRelease == FALSE)
// 	{
// 		return;
// 	}
/*#endif*/

	if(m_oMUAutoTestDataGroup.GetCount() < 0 )
	{
		return;
	}
	if (pItem == NULL)
	{
		return;
	}

	QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)pItem;


	if (/*pExBaseTreeWidgetItem->parent() == NULL ||*/ pExBaseTreeWidgetItem->m_pItemData == NULL)
	{
		return;
	}

    CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;

#ifdef _PSX_QT_WINDOWS_
// 	if (m_pAotuTestTree->GetIgnoreSingleClick())
// 	{
// 		return;
// 	}

	QRect rect = m_pAotuTestTree->m_pTreeWidget->visualItemRect(pItem);
	QStyleOptionButton option;
	int checkBoxWidth = m_pAotuTestTree->m_pTreeWidget->style()->subElementRect(QStyle::SE_CheckBoxIndicator, &option).width();
	QPoint cursorPos = m_pAotuTestTree->m_pTreeWidget->viewport()->mapFromGlobal(QCursor::pos());

	// 如果点击在复选框区域外（即在文字区域），则手动切换复选框状态
	if (cursorPos.x() > rect.left() + checkBoxWidth)
	{
		if (pItem->checkState(0) == Qt::Checked)
		{
			pItem->setCheckState(0, Qt::Unchecked);
			m_oMUAutoTestDataGroup.SetDataValue(strItemID, "0");
		}
		else 
		{
			pItem->setCheckState(0, Qt::Checked);
			m_oMUAutoTestDataGroup.SetDataValue(strItemID, "1");
		}
	}
	else
	{
		if (pItem->checkState(colunm) == Qt::Checked)
		{
			m_oMUAutoTestDataGroup.SetDataValue(strItemID, "1");
		}
		else
		{
			m_oMUAutoTestDataGroup.SetDataValue(strItemID, "0");
		}
	}

#else
	if (pItem->checkState(0) == Qt::Checked)
	{
        pItem->setCheckState(colunm, Qt::Unchecked);
		m_oMUAutoTestDataGroup.SetDataValue(strItemID, "0");
	}
	else
	{
		pItem->setCheckState(colunm, Qt::Checked);
		m_oMUAutoTestDataGroup.SetDataValue(strItemID, "1");
	}
#endif // _PSX_QT_WINDOWS_

}
void QSttMacroParaEditViewMuAutoTest::slot_PTCTLineEditChanged()
{  

	if(m_oMUAutoTestDataGroup.GetCount() < 0) 
	{
		return ;
	}
	//发送信号者的对象
 	QLineEdit *ptBtn = qobject_cast<QLineEdit *>(sender());
 	CString strTemp ;

 		if(ptBtn == m_pVolEdit_0)
 		{
		    strTemp = m_pVolEdit_0->GetValue_String();
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_LINEDIT_VOL_LPTRATIO,strTemp);
 		}
 		else if(ptBtn == m_pVolEdit_1)
 		{
			strTemp = m_pVolEdit_1->GetValue_String();
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_LINEDIT_VOL_RPTRATIO,strTemp);
 		}
 		else if(ptBtn == m_pCurEdit_0)
  		{
			strTemp = m_pCurEdit_0->GetValue_String();
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_LINEDIT_CUR_LCTRATIO,strTemp);
 		}
 		else if(ptBtn == m_pCurEdit_1)
 		{
			strTemp = m_pCurEdit_1->GetValue_String();
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_LINEDIT_CUR_RCTRATIO,strTemp);
 		}
 		else if(ptBtn == m_pTestEdit)
 		{
		    strTemp = m_pTestEdit->text();
		    m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_LINEDIT_TESTNUMBER,strTemp);
 		}
		else
		{
			return ;
		}
}

void QSttMacroParaEditViewMuAutoTest::InitEditCoverage()
{
	m_pVolEdit_0->setAlignment(Qt::AlignHCenter);
	m_pVolEdit_0->InitCoverage_EditFinished(1,10000,3);
	m_pVolEdit_0->InitUnit("kV");
	m_pVolEdit_1->setAlignment(Qt::AlignHCenter);
	m_pVolEdit_1->InitCoverage_EditFinished(1,10000,3);
	m_pVolEdit_1->InitUnit("V");
	m_pCurEdit_0->setAlignment(Qt::AlignHCenter);
	m_pCurEdit_0->InitCoverage_EditFinished(1,10000,3);
	m_pCurEdit_0->InitUnit("A");
	m_pCurEdit_1->setAlignment(Qt::AlignHCenter);
	m_pCurEdit_1->InitCoverage_EditFinished(1,10000,3);
    m_pCurEdit_1->InitUnit("A");
	m_pTestEdit->setAlignment(Qt::AlignHCenter);
	m_pTestEdit->InitCoverage(1,100);
}

void QSttMacroParaEditViewMuAutoTest::slot_FloatLineEditChanged()
{
	QFloatLineEdit *pEditLine = qobject_cast<QFloatLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("1.000");
	}

	QString str = pEditLine->GetValue_String();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
}
void QSttMacroParaEditViewMuAutoTest::slot_LongLineEditChanged()
{
	QLongLineEdit *pEditLine = qobject_cast<QLongLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("1");
	}

	QString str = pEditLine->text();
	GetWidgetBoard_DigitData(4,str,pEditLine,this);
}

void QSttMacroParaEditViewMuAutoTest::OnViewTestLink(BOOL b)
{

}
void QSttMacroParaEditViewMuAutoTest::StartInit()
{
	m_pSelectall->setDisabled(true);
	m_pClear->setDisabled(true);
	m_pOtherparameters->setDisabled(true);
	m_pRefresh->setDisabled(true);
	m_pParameterSet->setDisabled(true);
	m_pPTRatio->setDisabled(true);
	m_pCTRatio->setDisabled(true);
	m_pNumTests->setDisabled(true);
	m_pPTSLash->setDisabled(true);
	m_pCTSLash->setDisabled(true);
	m_pVolEdit_0->setDisabled(true);
	m_pVolEdit_1->setDisabled(true);
	m_pCurEdit_0->setDisabled(true);
	m_pCurEdit_1->setDisabled(true);
	m_pTestEdit->setDisabled(true);

	if(m_pAotuTestTree != NULL)
	{
       m_pAotuTestTree->StartInit();
	}
}
void QSttMacroParaEditViewMuAutoTest::StopInit()
{
	m_pSelectall->setDisabled(false);
	m_pClear->setDisabled(false);
	m_pOtherparameters->setDisabled(false);
	m_pRefresh->setDisabled(false);
	m_pParameterSet->setDisabled(false);
	m_pPTRatio->setDisabled(false);
	m_pCTRatio->setDisabled(false);
	m_pNumTests->setDisabled(false);
	m_pPTSLash->setDisabled(false);
	m_pCTSLash->setDisabled(false);
	m_pVolEdit_0->setDisabled(false);
	m_pVolEdit_1->setDisabled(false);
	m_pCurEdit_0->setDisabled(false);
	m_pCurEdit_1->setDisabled(false);
	m_pTestEdit->setDisabled(false);

	if(m_pAotuTestTree != NULL)
	{
		m_pAotuTestTree->StopInit();
	}
}
void QSttMacroParaEditViewMuAutoTest::OnViewTestStart()
{
    StartInit();
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();
	stt_Frame_EnableManualTriggerButton(false);

}
void QSttMacroParaEditViewMuAutoTest::OnViewTestStop()
{
	StopInit();
    stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget(false);
	stt_Frame_StopPowerWidget(false);
}

CSttTestResourceBase* QSttMacroParaEditViewMuAutoTest::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewMuAutoTest::ShowReport(CDvmValues *pValues)
{

	CDvmValue* pActValueData = (CDvmValue*)pValues->FindByID("ActValue");
	CDvmValue* pActTimeData = (CDvmValue*)pValues->FindByID("TripTime");
	CDvmValue* pActReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pActReturnTimeData = (CDvmValue*)pValues->FindByID("ReturnTime");
	float fActValue = 0, fActTime = 0, fReturnValue = 0, fReturnTime = 0;

	if (pActValueData != NULL)
	{
		fActValue = GlobalSetResultValue(pActValueData,3);
	}

	if (pActTimeData != NULL)
	{
		fActTime = GlobalSetResultValue(pActTimeData,4);
	}

	if (pActReturnData != NULL)
	{
		fReturnValue = GlobalSetResultValue(pActReturnData,3);
	}

	if (pActReturnTimeData != NULL)
	{
		fReturnTime = GlobalSetResultValue(pActReturnTimeData,4);
	}
}


BOOL QSttMacroParaEditViewMuAutoTest::OpenTestTestMngrFile(const CString& strParasFile)
{
    if (stt_Frame_TestMacroUI() == NULL)
	{
		return FALSE;
	}

    CDataGroup*  pDataGroup = stt_Frame_GetTestMacroUI_Paras();

	if (pDataGroup->GetCount() <= 0)
	{
        return FALSE;
	}

	pDataGroup->CopyChildren(&m_oMUAutoTestDataGroup);
	return TRUE;
}
void QSttMacroParaEditViewMuAutoTest::SetMUAutoTestWidgetFont()
{
      m_pSelectall->setFont(*g_pSttGlobalFont);
	  m_pClear->setFont(*g_pSttGlobalFont);
	  m_pOtherparameters->setFont(*g_pSttGlobalFont);
	  m_pRefresh->setFont(*g_pSttGlobalFont);
	  m_pPTRatio->setFont(*g_pSttGlobalFont);
	  m_pCTRatio->setFont(*g_pSttGlobalFont);
	  m_pNumTests->setFont(*g_pSttGlobalFont);
	  m_pPTSLash->setFont(*g_pSttGlobalFont);
	  m_pCTSLash->setFont(*g_pSttGlobalFont);
	  m_pVolEdit_0->setFont(*g_pSttGlobalFont);
	  m_pVolEdit_1->setFont(*g_pSttGlobalFont);
	  m_pCurEdit_0->setFont(*g_pSttGlobalFont);
	  m_pCurEdit_1->setFont(*g_pSttGlobalFont);
	  m_pTestEdit->setFont(*g_pSttGlobalFont);
      m_pAotuTestTree->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewMuAutoTest::UpdateTestResource(BOOL bCreateChMaps)
{
		m_nIecFormatMeas = g_oSystemParas.m_nIecFormatMeas;
		m_nBCodeMode = g_oSystemParas.m_nBCodeMode;
	
        long nTValue,nBValue;
		m_oMUAutoTestDataGroup.GetDataValue(STT_MUAUTOTEST_COMBOX_MEASTEAP,nTValue);
		m_oMUAutoTestDataGroup.GetDataValue(STT_MUAUTOTEST_COMBOX_BCODE,nBValue);

 		if (m_nIecFormatMeas != nTValue || m_nBCodeMode != nBValue  )
 		{
			nTValue = m_nIecFormatMeas;
            nBValue = m_nBCodeMode;
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_COMBOX_MEASTEAP,nTValue);
			m_oMUAutoTestDataGroup.SetDataValue(STT_MUAUTOTEST_COMBOX_BCODE,nBValue);
		}
}
bool QSttMacroParaEditViewMuAutoTest::PrepStartTest()
{
	QTreeWidgetItemIterator ite(m_pAotuTestTree->m_pTreeWidget);
	while(*ite)
	{
		if((*ite)->checkState(0) == Qt::Checked)
		{
			return true;
		}
		ite++;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("未勾选测试项节点"));//lcq	 
	return false;
}

