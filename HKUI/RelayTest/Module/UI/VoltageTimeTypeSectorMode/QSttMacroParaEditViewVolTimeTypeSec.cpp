#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameAPI.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"
#include "QSttMacroParaEditViewVolTimeTypeSec.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_4U3I.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFAStateSequenceGroupGrid.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFATestResultViewGroupGrid.h"

QSttMacroParaEditViewVolTimeTypeSec *g_pVolTimeTypeSecTestMain = NULL;

QSttMacroParaEditViewVolTimeTypeSec::QSttMacroParaEditViewVolTimeTypeSec(QWidget *parent)
{
	m_pFAStateSequenceGroupGrid = NULL;
	m_pFATestResultViewGroupGrid = NULL;	
	g_pVolTimeTypeSecTestMain = this;
	InitUI();
	
	SetData(CreateTestParas(GetMacroID()));
	OpenTestTestMngrFile(m_strDefaultParaFile);
	SetDatas(0);
	g_pVolTimeTypeSecTestMain->m_pTestItemWidget->slot_TableWidgetClicked(0,1);
}

QSttMacroParaEditViewVolTimeTypeSec::~QSttMacroParaEditViewVolTimeTypeSec()
{
	
}

void QSttMacroParaEditViewVolTimeTypeSec::InitUI()
{
	m_pTestWidget = new QTabWidget(this);
	m_pTestWidget->setFont(*g_pSttGlobalFont);

	m_pFACommonSpyWidget = new QTabWidget(this);
	m_pFACommonSpyWidget->setFont(*g_pSttGlobalFont);

	m_pVolTimeTypeSecSplitter = new QSplitter(Qt::Horizontal, this);
	setLayout(new QHBoxLayout);
	layout()->addWidget(m_pVolTimeTypeSecSplitter);

 	m_pVolTimeTypeSecSplitter->setStretchFactor(0, 1);
 	m_pVolTimeTypeSecSplitter->setStretchFactor(1, 1); 

	m_pVolTimeTypeSecSplitter->addWidget(m_pTestWidget);
	m_pVolTimeTypeSecSplitter->addWidget(m_pFACommonSpyWidget);

 	//m_pTestWidget->setMinimumSize(455, 0);
 	m_pFACommonSpyWidget->setMinimumSize(570, 0);

	// 测试项目
	m_pTestItemLayout = new QHBoxLayout();
	m_pTestItemWidget = new QSttVoltageTimeGroupTestItemWidget(m_pTestWidget);
	m_pTestItemWidget->setLayout(m_pTestItemLayout);
	m_pTestWidget->addTab(m_pTestItemWidget, "测试项目");
	m_pTestItemWidget->InitSOEDatas();

	// 测试结果视图
	m_pTestResultViewWidget = new QWidget(m_pFACommonSpyWidget);
	m_pTestResulLayout = new QHBoxLayout();
	m_pTestResultViewWidget->setLayout(m_pTestResulLayout);
	m_pFATestResultViewGroupGrid = new QSttFATestResultViewGroupGrid(m_pTestResultViewWidget);
	m_pFATestResultViewGroupGrid->InitGrid();
	m_pTestResulLayout->addWidget(m_pFATestResultViewGroupGrid);
	m_pFACommonSpyWidget->addTab(m_pTestResultViewWidget, "测试结果试图");

	// 状态序列设置
	m_pStateSequenceWidget = new QWidget(m_pFACommonSpyWidget);
	m_pStateLayout = new QHBoxLayout();
	m_pStateSequenceWidget->setLayout(m_pStateLayout);
	m_pFAStateSequenceGroupGrid = new QSttFAStateSequenceGroupGrid(m_pStateSequenceWidget);
	m_pFAStateSequenceGroupGrid->InitGrid();
	m_pStateLayout->addWidget(m_pFAStateSequenceGroupGrid);
	m_pFACommonSpyWidget->addTab(m_pStateSequenceWidget, "状态序列设置");
	
	//m_pFACommonSpyWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

	adjustSize();
}

void QSttMacroParaEditViewVolTimeTypeSec::startInit()
{
	/*m_pSttFAParasSetDialog->ui->m_editRatedVol->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editRatedVol->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editResidualVol->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editRatedCur->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editFaultCur->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editFailureCur->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editErrorTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editxTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_edityTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editzTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editxlTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_editsTime->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermPowerVol->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermLoadVol->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermCloseOutput->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermOpenOutput->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermCloseSignal->setEnabled(true);
	m_pSttFAParasSetDialog->ui->m_cmbTermQuantileSignal->setEnabled(true);*/
}

void QSttMacroParaEditViewVolTimeTypeSec::stopInit()
{
	/*m_pSttFAParasSetDialog->ui->m_editRatedVol->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editRatedVol->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editResidualVol->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editRatedCur->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editFaultCur->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editFailureCur->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editErrorTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editxTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_edityTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editzTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editxlTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_editsTime->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermPowerVol->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermLoadVol->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermCloseOutput->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermOpenOutput->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermCloseSignal->setEnabled(false);
	m_pSttFAParasSetDialog->ui->m_cmbTermQuantileSignal->setEnabled(false);*/
}

void QSttMacroParaEditViewVolTimeTypeSec::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize_base(&m_oTmtFaParasSet->m_oFaParasSet, &oRead);
	}

	stt_Frame_ClearInfoWidget();	

	UpdateFaParasSet(); 
}

void QSttMacroParaEditViewVolTimeTypeSec::GetDatas(CDataGroup *pParas)
{
	//GetAtsCmdDataParas(pParas);
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
 	m_pTestItemWidget->m_oVolTimeTypeSecDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateFaParasSet()
{
// 	if (m_pSttFAParasSetDialog)
// 	{
// 		m_pSttFAParasSetDialog->SetData(&m_oTmtFaParasSet->m_oFaParasSet);
// 	}
}

void QSttMacroParaEditViewVolTimeTypeSec::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
																	long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_fa_paras_set_test *pFaParas = (tmt_fa_paras_set_test*)pParas;

 	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
 	{
 		stt_xml_serialize_base(&pFaParas->m_oFaParasSet, pMacroParas);//文件的读写
		  
 	}
	else if (pParas->m_nSelected)
	{
		stt_xml_serialize_base(&pFaParas->m_oFaParasSet, pMacroParas);	//测试参数下发

	}
}

void QSttMacroParaEditViewVolTimeTypeSec::OnViewTestStart()
{
	startInit();

	//m_pTestItemWidget->SaveXmlParas();
}

void QSttMacroParaEditViewVolTimeTypeSec::OnViewTestStop()
{
	stopInit();
}

void QSttMacroParaEditViewVolTimeTypeSec::SetData(PTMT_PARAS_HEAD pCur)
{
	ASSERT(m_pCur != NULL);
	m_oTmtFaParasSet = (tmt_FaParasSetTest*)pCur;
}

PTMT_PARAS_HEAD QSttMacroParaEditViewVolTimeTypeSec::CreateTestParas(const char * pszMacroID)
{
	PTMT_PARAS_HEAD pNewTest = new tmt_fa_paras_set_test;
	strcpy(pNewTest->m_oRsltExprMngr.m_pszExprGroupID, _T("Common"));
	return pNewTest;
}
