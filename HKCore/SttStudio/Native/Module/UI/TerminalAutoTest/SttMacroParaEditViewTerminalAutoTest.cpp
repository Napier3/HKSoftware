#include "SttMacroParaEditViewTerminalAutoTest.h"
#include <QSplitter>
#include <QVBoxLayout>
#include "../SttTestCntrFrameBase.h"
#include "../../SttCmd/GuideBook/SttItemStateObject.h"

QSttMacroParaEditViewTerminalAutoTest* g_TerminalAutoTest = NULL;

QSttMacroParaEditViewTerminalAutoTest::QSttMacroParaEditViewTerminalAutoTest(QWidget* parent) :CSttMacroParaEditViewOriginal(parent)
{
	g_TerminalAutoTest = this;
	m_pMuTerminalTreeWidget = NULL;
	m_pMuTerminalTabWidget = NULL;
	
	OpenTestTestMngrFile(_T(""));
	m_strInitBinIn= _T("");
	m_strEndBinIn= _T("");

	InitUI();
	InitConnection();
	updateData();
	SetDatas(&m_pMUAutoTestDataGroup);
}


QSttMacroParaEditViewTerminalAutoTest::~QSttMacroParaEditViewTerminalAutoTest()
{

}



void QSttMacroParaEditViewTerminalAutoTest::updateData()
{
	UpdateGinData();	
	UpdateGoutData();

	m_pMuTerminalTreeWidget->UpdateTreeItem();
}

void QSttMacroParaEditViewTerminalAutoTest::InitUI()
{
	QSplitter *pMainSplitter = new QSplitter(Qt::Horizontal);

	m_pMuTerminalTabWidget = new QTerminalTabWidget(this);
	m_pMuTerminalTreeWidget = new QTerminalTreeWidget(this);

	pMainSplitter->addWidget(m_pMuTerminalTreeWidget);
	pMainSplitter->addWidget(m_pMuTerminalTabWidget);
	pMainSplitter->setStretchFactor(0,3);
	pMainSplitter->setStretchFactor(1,7);

	QVBoxLayout *pLayout = new QVBoxLayout;
	pLayout->addWidget(pMainSplitter);
	setLayout(pLayout);
}

void QSttMacroParaEditViewTerminalAutoTest::GetDatas(CDataGroup *pParas)
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_pMUAutoTestDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewTerminalAutoTest::SetDatas(CDataGroup *pParas)
{
	SetTreeWidgetItemValue(m_pMuTerminalTreeWidget->m_pSOEItem1,_T("SOEGout_Check"),pParas);  
	SetTreeWidgetItemValue(m_pMuTerminalTreeWidget->m_pSOEItem2,_T("SOEGin_Check"),pParas);

	CString strID;
	for (int i = 0 ; i< m_pMuTerminalTabWidget->m_nBoutIndex;i++)//goose转开入
	{
		strID.Format(_T("Gout_Check%d"),i+1);
		SetTreeWidgetItemValue(m_pMuTerminalTreeWidget->m_pGoutTestItems[i],strID,pParas);
	}

	for (int i = 0 ; i< m_pMuTerminalTabWidget->m_nBinIndex ;i++)//开出转goose
	{
		strID.Format(_T("Gin_Check%d"),i+1);
		SetTreeWidgetItemValue(m_pMuTerminalTreeWidget->m_pGinTestItems[i],strID,pParas);
	}

// 	Qt::CheckState SOEItem1state = m_pMuTerminalTreeWidget->m_pSOEItem1->checkState(0);
// 	Qt::CheckState SOEItem2state = m_pMuTerminalTreeWidget->m_pSOEItem2->checkState(0);
// 
// 	if (SOEItem1state == Qt::Unchecked && SOEItem2state == Qt::Unchecked)
// 	{
// 		m_pMuTerminalTreeWidget->m_pSOEItem->setCheckState(0,Qt::Unchecked);
// 	}


	UpdateMapValue(m_pGoutMapChs,_T("bin"),_T("Gout"),_T("SOEGout"));
	UpdateMapValue(m_pGinMapChs,_T("bout"),_T("Gin"),_T("SOEGin"));
	SaveXmlParas();
}

void QSttMacroParaEditViewTerminalAutoTest::InitConnection()
{
	connect(this,SIGNAL(sig_UpdateGoutData(CExBaseObject*)),m_pMuTerminalTabWidget,SLOT(InitGoutData(CExBaseObject *)));
	connect(this,SIGNAL(sig_UpdateGinData(CExBaseObject*)),m_pMuTerminalTabWidget,SLOT(InitGinData(CExBaseObject *)));
	connect(m_pMuTerminalTreeWidget->m_pTreeWidget,SIGNAL(/*itemPressed*/itemClicked(QTreeWidgetItem *,int)),this,SLOT(slot_TreeItemSelectionChanged(QTreeWidgetItem *,int)));
	//connect(m_pMuTerminalTreeWidget->m_pTreeWidget,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(slot_TreeItemClicked(QTreeWidgetItem *,int)));
}


void QSttMacroParaEditViewTerminalAutoTest::SetTreeWidgetItemValue(QExBaseTreeWidgetItem * pItem,CString strID,CDataGroup *pParas)
{	
	BOOL nIsSelected;
	CDvmData* pMUCurData = (CDvmData*)pParas->FindByID(strID);
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

void QSttMacroParaEditViewTerminalAutoTest::UpdateGoutData()
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgGoutDatas *pIecCfgGoutDatas = pIecCfgDatasMngr->GetGoutMngr();
	m_pIecCfgGoutDatas = pIecCfgGoutDatas;

	long nIndex = 0;
	CIecCfgGoutData* pIecCfgGoutData = NULL;
	POS pos = pIecCfgGoutDatas->GetHeadPosition();
	CIecCfgGoutChs *pIecCfgGoutChs = NULL;

	while(pos)
	{
		pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->GetNext(pos);

		if (pIecCfgGoutData->m_nUseFlag == 1)
		{
			pIecCfgGoutChs = (CIecCfgGoutChs*)pIecCfgGoutData->FindByClassID(CFGCLASSID_CIECCFGCHSGOUT);
			m_pGoutMapChs = pIecCfgGoutChs;
		}
		if (nIndex == 0)
		{
			m_pIecCfgGoutChs = (CIecCfgGoutChs*)pIecCfgGoutData->FindByClassID(CFGCLASSID_CIECCFGCHSGOUT);
		}
		nIndex ++;
	}

    CExBaseObject *pGoutChs = (CExBaseObject *)pIecCfgGoutChs;
	emit sig_UpdateGoutData(pGoutChs);
}

void QSttMacroParaEditViewTerminalAutoTest::UpdateGinData()
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgGinData* pIecCfgGinData = NULL;

	m_pIecCfgGinDatas = pIecCfgGinDatas;

	POS pos = pIecCfgGinDatas->GetHeadPosition();
	CIecCfgGinChs *pIecCfgGinChs = NULL;
	long nIndex = 0;
	while(pos)
	{
		pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->GetNext(pos);

		if (pIecCfgGinData->m_nUseFlag == 1)
		{
			pIecCfgGinChs = (CIecCfgGinChs*)pIecCfgGinData->FindByClassID(CFGCLASSID_CIECCFGCHSGIN);
			m_pGinMapChs = pIecCfgGinChs;
		}
		if (nIndex == 0)
		{
			m_pIecCfgGinChs = (CIecCfgGinChs*)pIecCfgGinData->FindByClassID(CFGCLASSID_CIECCFGCHSGIN);
		}
		nIndex ++;
	}

	CExBaseObject *pGinChs = (CExBaseObject *)pIecCfgGinChs;
	emit sig_UpdateGinData(pGinChs);
}

BOOL QSttMacroParaEditViewTerminalAutoTest::OpenTestTestMngrFile(const CString& strParasFile)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup*  pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if (pDataGroup->GetCount() <= 0)
	{
		return FALSE;
	}

	pDataGroup->CopyChildren(&m_pMUAutoTestDataGroup);
	return TRUE;
}

void QSttMacroParaEditViewTerminalAutoTest::slot_TreeItemSelectionChanged(QTreeWidgetItem * pItem, int colunm)
{
	if(m_pMUAutoTestDataGroup.GetCount() < 0 )
	{
		return;
	}
	if (pItem == NULL)
	{
		return;
	}

	QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)pItem;


	if (pExBaseTreeWidgetItem->parent() == NULL || pExBaseTreeWidgetItem->m_pItemData == NULL)
	{
		return;
	}

	CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;
	if (m_pMuTerminalTabWidget)//chenling20240304 SOE测试点小于3个，soe测试就无法勾选，提示栏里面提示
	{
		if (strItemID == _T("SOEGout_Check") && m_pMuTerminalTabWidget->m_nBoutIndex < 3)
		{
			pItem->setCheckState(colunm, Qt::Unchecked);
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的GOOSE转开入测试点%d个小于3个."),m_pMuTerminalTabWidget->m_nBoutIndex);
			return;
		}

		if(strItemID == _T("SOEGin_Check") && m_pMuTerminalTabWidget->m_nBinIndex < 3)
		{
			pItem->setCheckState(colunm, Qt::Unchecked);
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的开出转GOOSE测试点%d个小于3个."),m_pMuTerminalTabWidget->m_nBinIndex);
			return;
		}
	}
	

	if (pItem->checkState(0) == Qt::Checked)
	{
		pItem->setCheckState(colunm, Qt::Unchecked);
		m_pMUAutoTestDataGroup.SetDataValue(strItemID,"0");
	}
	else
	{
		pItem->setCheckState(colunm, Qt::Checked);
		m_pMUAutoTestDataGroup.SetDataValue(strItemID,"1");
	}    
}


void QSttMacroParaEditViewTerminalAutoTest::OnViewTestStart()
{
	ClearData();
	m_pMuTerminalTreeWidget->StartInit();
	m_pMuTerminalTabWidget->StartInit();
	SaveXmlParas();
	
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	g_theTestCntrFrame->EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewTerminalAutoTest::OnViewTestStop()
{
	m_pMuTerminalTreeWidget->StopInit();
	m_pMuTerminalTabWidget->StopInit();
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);
	g_theTestCntrFrame->StopPowerWidget(false);
}

void QSttMacroParaEditViewTerminalAutoTest::SaveXmlParas()
{
//  	m_pMuTerminalTreeWidget->m_pMuSettingTabWidget->SaveGoutMapValue();
//  	m_pMuTerminalTreeWidget->m_pMuSettingTabWidget->SaveGinMapValue();
 	CString strFile;
 	strFile = _P_GetDBPath();
 	strFile += _T("atsgen/TerminalAuto_Paras.xml");
 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
	m_pMUAutoTestDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
}

void QSttMacroParaEditViewTerminalAutoTest::UpdateEventMsg(CEventResult *pCurrEventResult )
{
	if(pCurrEventResult == NULL)
	{
		return;
	}

	if (pCurrEventResult->m_strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		if (m_strInitBinIn.GetLength() >= g_nBinCount)
		{
			m_strInitBinIn = _T("");
		}
		for (int i = 0; i< g_nBinCount; i++)
		{
			m_strInitBinIn.AppendFormat(_T("%d"),pCurrEventResult->m_BinIn[i]);
		}
	}

	CExBaseObject *pCurrTestItem = g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
	CSttItemStateObject* pObj  = (CSttItemStateObject*)pCurrTestItem;
	CString strItemID =  pObj->m_strItemID;
	if ((strItemID.Find(_T("GooseToBin")) >= 0) || (strItemID.Find(_T("BoutToGoose")) >= 0))
	{
	if (pCurrEventResult->m_nCurrStateIndex == 1 )//状态2
	{
		UpdateEventResult(pCurrEventResult);
	}
	}
	else if ((strItemID.Find(_T("SOEGin")) >= 0) ||  (strItemID.Find(_T("SOEGout")) >= 0)) //SOE测试 20240305chenling
	{
		if (pCurrEventResult->m_nCurrStateIndex == 3 )//状态4
		{
			UpdateEventResult(pCurrEventResult);
		}
	}
}

void QSttMacroParaEditViewTerminalAutoTest::UpdateEventResult( CEventResult *pCurrEventResult )
{
	if(pCurrEventResult == NULL)
	{
		return;
	}
	char flag ='A';

	CExBaseObject *pCurrTestItem = g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
	CSttItemStateObject* pObj  = (CSttItemStateObject*)pCurrTestItem;
	CString strItemID =  pObj->m_strItemID;

	if(pCurrEventResult->m_strEventID == SYS_STATE_REPORT_OnSwichInChanged)
	{	
		if (m_strEndBinIn.GetLength() >= g_nBinCount)
		{
			m_strEndBinIn = _T("");
		}
		for (int i=0; i< g_nBinCount; i++)
		{
			m_strEndBinIn.AppendFormat("%d",pCurrEventResult->m_BinIn[i]);
			if (m_strInitBinIn[i] != m_strEndBinIn[i])
			{
				if (m_pMuTerminalTabWidget)
				{
// 					CExBaseObject *pCurrTestItem = g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
// 					CSttItemStateObject* pObj  = (CSttItemStateObject*)pCurrTestItem;
// 					CString strItemID =  pObj->m_strItemID;
					if(strItemID.Find(_T("GooseToBin")) >= 0)
					{					
						long nIndex = CString_To_long(strItemID.right(1));
						CIecCfgDataGooseChBase *pIecCfgCh = (CIecCfgDataGooseChBase *)m_pMuTerminalTabWidget->m_oBoutGooseList[nIndex-1];
						char displayChar = char('A' + (pIecCfgCh->m_strDevChID.right(1).toInt() - 1));
						
						if (displayChar == flag)
						{
							m_pMuTerminalTabWidget->m_MuBoutGooseGrid->GoutToBinResultVlaues(pCurrEventResult->m_fActTime,flag);	
						}
					}
					else if(strItemID.Find(_T("BoutToGoose")) >= 0)
					{
						long nIndex = CString_To_long(strItemID.right(1));
						CIecCfgDataGooseChBase *pIecCfgCh = (CIecCfgDataGooseChBase *)m_pMuTerminalTabWidget->m_oGooseBinList[nIndex-1];
						char displayChar = char('A' + (pIecCfgCh->m_strDevChID.right(1).toInt() - 1));

						if (displayChar == flag)
						{
							m_pMuTerminalTabWidget->m_MuGooseBinGrid->BoutToGinResultVlaues(pCurrEventResult->m_fActTime,flag);
						}
					}
					else if (strItemID.Find(_T("SOEGout")) >= 0)
					{
						m_pMuTerminalTabWidget->m_SOEBoutGooseGrid->GoutToBinResultVlaues(pCurrEventResult->m_fActTime,flag);
					}
					else if (strItemID.Find(_T("SOEGin")) >= 0)
					{
					m_pMuTerminalTabWidget->m_SOEGooseBinGrid->BoutToGinResultVlaues(pCurrEventResult->m_fActTime,flag);
					}
				}	
			}
			flag++;
			// 二次记录开入变量的动作值作为参照量	
			m_strInitBinIn.AppendFormat(_T("%d"),pCurrEventResult->m_BinIn[i]); 
			if (m_strInitBinIn.GetLength() >= g_nBinCount*2)
			{
				m_strInitBinIn = m_strInitBinIn.Right(g_nBinCount);
			}
		}
	}
	else
	{
		long nIndex;
		nIndex = CString_To_long(strItemID.right(1));
		nIndex = nIndex-1;

		if(strItemID.Find(_T("GooseToBin")) >= 0)
		{					
			m_pMuTerminalTabWidget->m_MuBoutGooseGrid->UpdateBoutToGinGrid(nIndex);
			m_GooseOutIndexList.push_back(nIndex);
		}
		else if (strItemID.Find(_T("BoutToGoose")) >= 0)
		{
			m_pMuTerminalTabWidget->m_MuGooseBinGrid->UpdateGoutToBinGrid(nIndex);
			m_GooseInIndexList.push_back(nIndex);
		}
		else if (strItemID.Find(_T("SOEGout")) >= 0)
		{
			for (int i = 0; i < m_GooseOutIndexList.size(); ++i) 
			{
				long nValue = m_GooseOutIndexList.at(i);
				m_pMuTerminalTabWidget->m_SOEBoutGooseGrid->UpdateBoutToGinGrid(nValue);
			}
		}
		else if (strItemID.Find(_T("SOEGin")) >= 0)
		{
			for (int i = 0; i < m_GooseInIndexList.size(); ++i) 
			{
				long nValue = m_GooseInIndexList.at(i);
				m_pMuTerminalTabWidget->m_SOEGooseBinGrid->UpdateGoutToBinGrid(nValue);
			}
		}
	}
}

void QSttMacroParaEditViewTerminalAutoTest::ClearData()
{
	m_GooseOutIndexList.clear();
	m_GooseInIndexList.clear();

	if (m_pMuTerminalTabWidget)
	{
		m_pMuTerminalTabWidget->m_MuGooseBinGrid->ClearBoutToGinResultData();	
		m_pMuTerminalTabWidget->m_MuBoutGooseGrid->ClearGoutToBinResultData();
		m_pMuTerminalTabWidget->m_SOEGooseBinGrid->ClearBoutToGinResultData();
		m_pMuTerminalTabWidget->m_SOEBoutGooseGrid->ClearGoutToBinResultData();	
	}
}

void QSttMacroParaEditViewTerminalAutoTest::ShowReport( CDvmValues *pValues )
{
	g_theTestCntrFrame->UpdateRptHtml();
}


void QSttMacroParaEditViewTerminalAutoTest::UpdateMapValue(CIecCfgChsBase *pIecCfgChsBase,CString str1,CString str2,CString srtSOE)
{
	long nIndex = 0,nIndex1 = 0;
	QString strDevID,strDevValue,strAppID,strAppValue,strCheck;
	QString strSoeDevID,strSoeDevValue,strSoeAppID,strSoeAppValue,strSoeCheck;

	CIecCfgDataGooseChBase *pIecCfgCh = NULL;
	POS pos = pIecCfgChsBase->GetHeadPosition();
	while(pos)
	{
		pIecCfgCh = (CIecCfgDataGooseChBase *)pIecCfgChsBase->GetNext(pos);

		strDevID = QString("%1_Check%2_Map").arg(str2).arg(nIndex1 + 1);
		strDevValue = "0"; 	
		strAppID = QString("%1_Check%2_Value").arg(str2).arg(nIndex1 + 1);
		strAppValue = "0";	

		strSoeDevID = QString("%1_Check%2_Map").arg(srtSOE).arg(nIndex1 + 1);
		strSoeDevValue = "0";
		strSoeAppID = QString("%1_Check%2_Value").arg(srtSOE).arg(nIndex1 + 1);
		strSoeAppValue = "0";

		strCheck = QString("%1_Check%2").arg(str2).arg(nIndex1 + 1);
		m_pMUAutoTestDataGroup.SetDataValue(strCheck,strAppValue);

		strSoeCheck = QString("%1_Check%2").arg(srtSOE).arg(nIndex1 + 1);
		m_pMUAutoTestDataGroup.SetDataValue(strSoeCheck,strSoeAppValue);

		m_pMUAutoTestDataGroup.SetDataValue(strAppID,strAppValue);
		m_pMUAutoTestDataGroup.SetDataValue(strDevID,strDevValue);
		m_pMUAutoTestDataGroup.SetDataValue(strSoeDevID,strSoeDevValue);
		m_pMUAutoTestDataGroup.SetDataValue(strSoeAppID,strSoeAppValue);

		if (pIecCfgCh->m_strDevChID.Find(str1) >= 0)
		{
			strDevID = QString("%1_Check%2_Map").arg(str2).arg(nIndex + 1);
			strDevValue = pIecCfgCh->m_strDevChID.right(1);

			strAppID = QString("%1_Check%2_Value").arg(str2).arg(nIndex + 1);
			strAppValue = pIecCfgCh->m_strDevChID.right(1);

			strSoeDevID = QString("%1_Check%2_Map").arg(srtSOE).arg(nIndex + 1);
			strSoeDevValue = pIecCfgCh->m_strDevChID.right(1);
			strSoeAppID = QString("%1_Check%2_Value").arg(srtSOE).arg(nIndex + 1);
			strSoeAppValue = pIecCfgCh->m_strDevChID.right(1);

			strCheck = QString("%1_Check%2").arg(str2).arg(nIndex + 1);
			m_pMUAutoTestDataGroup.SetDataValue(strCheck,"1");

			nIndex ++;

			m_pMUAutoTestDataGroup.SetDataValue(strAppID,strAppValue);
			m_pMUAutoTestDataGroup.SetDataValue(strDevID,strDevValue);
			m_pMUAutoTestDataGroup.SetDataValue(strSoeDevID,strSoeDevValue);
			m_pMUAutoTestDataGroup.SetDataValue(strSoeAppID,strSoeAppValue);
		}
		nIndex1 ++;
	}
}

