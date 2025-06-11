#include "SttMacroParaEditViewDualPositionWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewDualPositionWidget::QSttMacroParaEditViewDualPositionWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pDualPositionTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewDualPositionWidget::~QSttMacroParaEditViewDualPositionWidget()
{

}

void QSttMacroParaEditViewDualPositionWidget::InitUI()
{
	CString strText;

	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("Ë«Î»ÖÃÒ£ÐÅ²âÊÔ");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

//  	CDvmData* pCurData = (CDvmData*)m_pDualPositionDataGroup.FindByID(_T("Remote_DualPosition_Check"));
//  	if (pCurData)
//  	{
//  		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
//  		m_pGroupBox->setChecked(nIsSelected);
//  	}
	m_pDualPositionTable = new QSttMacroParaEditViewDualPositionTable(this);
	m_pDualPositionTable->setFont(*g_pSttGlobalFont);
	m_pDualPositionTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pDualPositionTable->m_pDualPositionDataGroup = &m_pDualPositionDataGroup;

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pDualPositionTable);
	m_pGroupBox->setLayout(pVBoxLayout);
	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	OpenBinBoutMapXml();
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
}

BOOL QSttMacroParaEditViewDualPositionWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pDualPositionDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewDualPositionWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pDualPositionDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	m_pDualPositionTable->InitData(pParas);
}

void QSttMacroParaEditViewDualPositionWidget::SaveParasXml()
{
// 	m_pDualPositionDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pDualPositionDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pDualPositionDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pDualPositionDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_DualPosition_Paras.xml");
	m_pDualPositionDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewDualPositionWidget::OnViewTestStart()
{	
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewDualPositionWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewDualPositionWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pDualPositionDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pDualPositionDataGroup.FindByID(_T("Remote_DualPosition_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	m_pDualPositionTable->UpdateTable(&m_pDualPositionDataGroup);

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewDualPositionWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pDualPositionDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewDualPositionWidget::OpenBinBoutMapXml()
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

	m_pDualPositionTable->InitData(&oDataGroup);

	CString strDatasetpath;
	stt_GetDataValueByID(&oDataGroup, _T("datasetpath"), strDatasetpath);
	m_pDualPositionDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

void QSttMacroParaEditViewDualPositionWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pDualPositionDataGroup.SetDataValue(_T("Remote_DualPosition_Check"),(long)checked);	
}
