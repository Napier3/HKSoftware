#include "SttMacroParaEditViewParaRecallWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewParaRecallWidget::QSttMacroParaEditViewParaRecallWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pParaRecallTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewParaRecallWidget::~QSttMacroParaEditViewParaRecallWidget()
{

}

void QSttMacroParaEditViewParaRecallWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("固有参数调阅");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

//  	CDvmData* pCurData = (CDvmData*)m_pParaRecallDataGroup.FindByID(_T("ParaRecall_Check"));
//  	if (pCurData)
//  	{
//  		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
//  		m_pGroupBox->setChecked(nIsSelected);
//  	}
	m_pParaRecallTable = new QSttMacroParaEditViewParaRecallTable(this);
	m_pParaRecallTable->setFont(*g_pSttGlobalFont);
	m_pParaRecallTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pParaRecallTable->m_pParaRecallDataGroup = &m_pParaRecallDataGroup;

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pParaRecallTable);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
		
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));

	OpenBinBoutMapXml();
}

BOOL QSttMacroParaEditViewParaRecallWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pParaRecallDataGroup);
	}
	return TRUE;
}



void QSttMacroParaEditViewParaRecallWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsSetting");
		m_pParaRecallDataGroup.SetDataValue(_T("datasetpathdsSetting"),strDatasetpath);
	}

	m_pParaRecallTable->InitData(pParas);
}

void QSttMacroParaEditViewParaRecallWidget::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_ParaRecall_Paras.xml");
	m_pParaRecallDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewParaRecallWidget::OnViewTestStart()
{
	m_pGroupBox->setDisabled(true);
}

void QSttMacroParaEditViewParaRecallWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
}

void QSttMacroParaEditViewParaRecallWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pParaRecallDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewParaRecallWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewParaRecallWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pParaRecallDataGroup);	
	}
	CDvmData* pCurData = (CDvmData*)m_pParaRecallDataGroup.FindByID(_T("ParaRecall_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}
}

//BOOL QSttMacroParaEditViewParaRecallWidget::GetDatas_Reports( CSttReport *pReport,const CString &strItemID /*= ""*/ )
//{
	//CDvmValues *pDvmValues = pReport->m_pValues;
	//CString strSoeResolution;
	//stt_GetDataValueByID(&m_pParaRecallDataGroup, _T("SoeResolution"), strSoeResolution);
	//CDvmValue *pDvmValue = new CDvmValue;
	//pDvmValue->m_strName = _T("设置分辨率");
	//pDvmValue->m_strID = _T("SoeResolution");
	//pDvmValue->m_strValue = strSoeResolution;
	//pDvmValues->AddNewChild(pDvmValue);

//	return TRUE;
//}

void QSttMacroParaEditViewParaRecallWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pParaRecallDataGroup.SetDataValue(_T("ParaRecall_Check"),(long)checked);	
}
