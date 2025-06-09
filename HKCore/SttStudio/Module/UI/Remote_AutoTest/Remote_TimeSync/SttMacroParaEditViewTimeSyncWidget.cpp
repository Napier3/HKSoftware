#include "SttMacroParaEditViewTimeSyncWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewTimeSyncWidget::QSttMacroParaEditViewTimeSyncWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pTimeSyncTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewTimeSyncWidget::~QSttMacroParaEditViewTimeSyncWidget()
{

}

void QSttMacroParaEditViewTimeSyncWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("对时功能测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

//  	CDvmData* pCurData = (CDvmData*)m_pTimeSyncDataGroup.FindByID(_T("TimeSync_Check"));
//  	if (pCurData)
//  	{
//  		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
//  		m_pGroupBox->setChecked(nIsSelected);
//  	}
	m_pTimeSyncTable = new QSttMacroParaEditViewTimeSyncTable(this);
	m_pTimeSyncTable->setFont(*g_pSttGlobalFont);
	m_pTimeSyncTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pTimeSyncTable->m_pTimeSyncDataGroup = &m_pTimeSyncDataGroup;

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pTimeSyncTable);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
		
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));

	OpenBinBoutMapXml();
}

BOOL QSttMacroParaEditViewTimeSyncWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pTimeSyncDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewTimeSyncWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewTimeSyncWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath,strDatasetpathdsEna;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pTimeSyncDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	strDatasetpathdsEna = strDatasetpath;
	int pos = strDatasetpathdsEna.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpathdsEna = strDatasetpathdsEna.Left(pos+1);
		strDatasetpathdsEna = strDatasetpathdsEna + _T("dsEna");
		m_pTimeSyncDataGroup.SetDataValue(_T("datasetpathdsEna"),strDatasetpathdsEna);
	}

	m_pTimeSyncTable->InitData(pParas);
}

void QSttMacroParaEditViewTimeSyncWidget::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_TimeSync_Paras.xml");
	m_pTimeSyncDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewTimeSyncWidget::OnViewTestStart()
{
	m_pGroupBox->setDisabled(true);
}

void QSttMacroParaEditViewTimeSyncWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
}

void QSttMacroParaEditViewTimeSyncWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pTimeSyncDataGroup.CopyChildren(pParas);
}


BOOL QSttMacroParaEditViewTimeSyncWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
 	CDvmValues *pDvmValues = pReport->m_pValues;
 	CString strValue;
 	stt_GetDataValueByID(&m_pTimeSyncDataGroup, _T("IncorrectTimeFormat"), strValue);
 	CDvmValue *pDvmValue = new CDvmValue;
 	pDvmValue->m_strName = _T("错误时标格式");
 	pDvmValue->m_strID = _T("IncorrectTimeFormat");
 	pDvmValue->m_strValue = strValue;
 	pDvmValues->AddNewChild(pDvmValue);

	return TRUE;
}

void QSttMacroParaEditViewTimeSyncWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pTimeSyncDataGroup);	
	}

	CDvmData* pCurData = (CDvmData*)m_pTimeSyncDataGroup.FindByID(_T("TimeSync_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}
}

void QSttMacroParaEditViewTimeSyncWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pTimeSyncDataGroup.SetDataValue(_T("TimeSync_Check"),(long)checked);	
}
