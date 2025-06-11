#include "SttMacroParaEditViewResolutionWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewResolutionWidget::QSttMacroParaEditViewResolutionWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pResolutionTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewResolutionWidget::~QSttMacroParaEditViewResolutionWidget()
{

}

void QSttMacroParaEditViewResolutionWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("遥信分辨率测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

//  	CDvmData* pCurData = (CDvmData*)m_pResolutionDataGroup.FindByID(_T("SoeTest_Check"));
//  	if (pCurData)
//  	{
//  		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
//  		m_pGroupBox->setChecked(nIsSelected);
//  	}
	m_pResolutionTable = new QSttMacroParaEditViewResolutionTable(this);
	m_pResolutionTable->setFont(*g_pSttGlobalFont);
	m_pResolutionTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pResolutionTable->m_pResolutionDataGroup = &m_pResolutionDataGroup;

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pResolutionTable);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
		
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));

	OpenBinBoutMapXml();
}

BOOL QSttMacroParaEditViewResolutionWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pResolutionDataGroup);
	}
	return TRUE;
}


void QSttMacroParaEditViewResolutionWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pResolutionDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	m_pResolutionTable->InitData(pParas);
}

void QSttMacroParaEditViewResolutionWidget::SaveParasXml()
{
// 	m_pResolutionDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pResolutionDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pResolutionDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pResolutionDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_Resolution_Paras.xml");
	m_pResolutionDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewResolutionWidget::OnViewTestStart()
{
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewResolutionWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewResolutionWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pResolutionDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewResolutionWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pResolutionDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pResolutionDataGroup.FindByID(_T("SoeTest_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	m_pResolutionTable->UpdateTable(&m_pResolutionDataGroup);

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewResolutionWidget::OpenBinBoutMapXml()
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

	m_pResolutionTable->InitData(&oDataGroup);

	CString strDatasetpath;
	stt_GetDataValueByID(&oDataGroup, _T("datasetpath"), strDatasetpath);
	m_pResolutionDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

BOOL QSttMacroParaEditViewResolutionWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	CDvmValues *pDvmValues = pReport->m_pValues;
	CString strSoeResolution;
	stt_GetDataValueByID(&m_pResolutionDataGroup, _T("SoeResolution"), strSoeResolution);
	CDvmValue *pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("设置分辨率");
	pDvmValue->m_strID = _T("SoeResolution");
	pDvmValue->m_strValue = strSoeResolution;
	pDvmValues->AddNewChild(pDvmValue);

	return TRUE;
}

void QSttMacroParaEditViewResolutionWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pResolutionDataGroup.SetDataValue(_T("SoeTest_Check"),(long)checked);	
}
