#include "SttMacroParaEditViewPriorityDeliverWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewPriorityDeliverWidget::QSttMacroParaEditViewPriorityDeliverWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pDeliverTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewPriorityDeliverWidget::~QSttMacroParaEditViewPriorityDeliverWidget()
{

}

void QSttMacroParaEditViewPriorityDeliverWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("遥信优先上送测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

// 	CDvmData* pCurData = (CDvmData*)m_pDeliverDataGroup.FindByID(_T("Remote_PriorityDelivery_Check"));
// 	if (pCurData)
// 	{
// 		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
// 		m_pGroupBox->setChecked(nIsSelected);
// 	}

	m_pDeliverTable = new QSttMacroParaEditViewPriorityDeliverTable(this);
	//m_pDeliverTable->m_pDeliverDataGroup = &m_pDeliverDataGroup;

	m_pDeliverTable->setFont(*g_pSttGlobalFont);
	m_pDeliverTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pDeliverTable);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
	OpenBinBoutMapXml();
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
}

BOOL QSttMacroParaEditViewPriorityDeliverWidget::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup* pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if ((pDataGroup->GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,pDataGroup);
	}

	if (pDataGroup->GetCount()>0)
	{
		pDataGroup->CopyChildren(&m_pDeliverDataGroup);
	}
	return TRUE;
}


void QSttMacroParaEditViewPriorityDeliverWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{	
	CString strDatasetpath,strDatasetpathdsAin;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pDeliverDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);

	strDatasetpathdsAin = strDatasetpath;
	int pos = strDatasetpathdsAin.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpathdsAin = strDatasetpathdsAin.Left(pos+1);
		strDatasetpathdsAin = strDatasetpathdsAin + _T("dsAin");
		m_pDeliverDataGroup.SetDataValue(_T("datasetpathdsAin"),strDatasetpathdsAin);
	}	
	
	m_pDeliverTable->InitData(pParas,&m_pDeliverDataGroup);
}


void QSttMacroParaEditViewPriorityDeliverWidget::SaveParasXml()
{
	m_pDeliverDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pDeliverDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDeliverDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pDeliverDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_PriorityDelivery_Paras.xml");
	m_pDeliverDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewPriorityDeliverWidget::OnViewTestStart()
{	
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewPriorityDeliverWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewPriorityDeliverWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pDeliverDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewPriorityDeliverWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pDeliverDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pDeliverDataGroup.FindByID(_T("Remote_PriorityDelivery_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	m_pDeliverTable->UpdateTable(&m_pDeliverDataGroup);

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewPriorityDeliverWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(&oDataGroup, strID, strValue);

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_1"));  
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_2"));
		}
		else if (strValue == _T("Din_5") || strValue == _T("2"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_5"));
		}
		else
		{
			oDataGroup.SetDataValue(strID, _T(""));  
		}
	}

	UpdateRemoteBoutData(&oDataGroup);
}

void QSttMacroParaEditViewPriorityDeliverWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pDeliverDataGroup.SetDataValue(_T("Remote_PriorityDelivery_Check"),(long)checked);	
}
