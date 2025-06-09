#include "SttSclCtrlsWidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "Grid/SclCtrlsSmvInGrid.h"
#include "Grid/SclCtrlsSmvOutGrid.h"
#include "Grid/SclCtrlsGooseInGrid.h"
#include "Grid/SclCtrlsGooseOutGrid.h"

#include "Grid/SclCtrlSmvOutChsGrid.h"
#include "Grid/SclCtrlSmvInChsGrid.h"
#include "Grid/SclCtrlGoutChsGrid.h"
#include "Grid/SclCtrlGInChsGrid.h"
#include "../../XLangResource_Native.h"


//#include "../SttTestCntrFrameBase.h"


QSttSclCtrlsWidget::QSttSclCtrlsWidget(long nCtrlsType,CExBaseList *pSelectedSclCtrlsRef,QFont oFont ,QWidget *parent)
	: QWidget(parent)
{
	m_pSelectedSclCtrlsRef = pSelectedSclCtrlsRef;
	m_nCtrlsType = nCtrlsType;
	m_pSclCtrlsGrid = NULL;
	m_pSplitter = NULL;

	m_oIecFont = oFont;
	setFont(m_oIecFont);

	InitUI();
}

QSttSclCtrlsWidget::~QSttSclCtrlsWidget()
{

}

void QSttSclCtrlsWidget::InitUI()
{
	m_pMainVLayout = new QVBoxLayout(this);
	m_pSplitter = new QSplitter(Qt::Vertical);
	setLayout(m_pMainVLayout);

	if (m_nCtrlsType == STT_SCL_CTRLS_TYPE_SMVIN)
	{
		m_pSclCtrlsGrid = new CSclCtrlsSmvInGrid(this);
		m_pSclCtrlsChGrid = new QSclCtrlSmvInChsGrid(this);
	}
	else if (m_nCtrlsType == STT_SCL_CTRLS_TYPE_SMVOUT)
	{
		m_pSclCtrlsGrid = new CSclCtrlsSmvOutGrid(this);
		m_pSclCtrlsChGrid = new QSclCtrlSmvOutChsGrid(this);
	}
	else if (m_nCtrlsType == STT_SCL_CTRLS_TYPE_GOOSEIN)
	{
		m_pSclCtrlsGrid = new CSclCtrlsGooseInGrid(this);
		m_pSclCtrlsChGrid = new QSclCtrlGInChsGrid(this);
	}
	else if (m_nCtrlsType == STT_SCL_CTRLS_TYPE_GOOSEOUT)
	{
		m_pSclCtrlsGrid = new CSclCtrlsGooseOutGrid(this);
		m_pSclCtrlsChGrid = new QSclCtrlGoutChsGrid(this);
	}
	else
		return;

	m_pSclCtrlsGrid->AttachDataViewOptrInterface(this);
	m_pSclCtrlsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pSclCtrlsGrid->setFont(*g_pSttGlobalFont/*m_oIecFont*/);
	m_pSclCtrlsGrid->InitGrid();
	m_pSclCtrlsGrid->Attach_SelCtrlsRef(m_pSelectedSclCtrlsRef);

	m_pSclCtrlsChGrid->AttachDataViewOptrInterface(this);
	m_pSclCtrlsChGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pSclCtrlsChGrid->setFont(*g_pSttGlobalFont/*m_oIecFont*/);
	m_pSclCtrlsChGrid->InitGrid();
	m_pSclCtrlsChGrid->Attach_SelCtrlsRef(m_pSelectedSclCtrlsRef);


	m_pSplitter->addWidget(m_pSclCtrlsGrid);
	//加入通道Widget
	m_pSplitter->addWidget(m_pSclCtrlsChGrid);
	QSplitterHandle *handle = m_pSplitter->handle(1); 
	handle->setToolTip(/* "已选中" */g_sLangTxt_Native_selected);
	handle->setAttribute(Qt::WA_Hover, true);
	m_pSplitter->setStyleSheet(	"QSplitter::handle:hover{background-color: black}");

	//m_pSclFileIED_Splitter->addWidget(m_pSclFileIedCtrls_TabWidget);
	m_pSplitter->setStretchFactor(0,5);
	m_pSplitter->setStretchFactor(1,5);

	m_pMainVLayout->addWidget(m_pSplitter);

	//2023/9/18 wjs 
	connect(this,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),this,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
}


void QSttSclCtrlsWidget::InitData(CSclCtrls* pSclCtrls)
{
	if (m_pSclCtrlsGrid == NULL)
	{
		return;
	}

	ASSERT(pSclCtrls);
	m_pSclCtrlsGrid->AttachDataViewOptrInterface(this);
	m_pSclCtrlsGrid->ShowDatas(pSclCtrls);
	m_pSclCtrlsGrid->SelectRow(1);
}

void QSttSclCtrlsWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
//	EnableAllButtons();
	if (m_pSclCtrlsGrid == NULL)
	{
		return;
	}

	if (m_pSclCtrlsGrid != pGridCtrl)
	{
		return;
	}

	CExBaseList *pCurrSelData =  (CExBaseList*)m_pSclCtrlsGrid->GetCurrSelData();

	if (pCurrSelData == NULL)
	{
		return;
	}

	emit sig_UpdateCB_ChDatas(pCurrSelData);//更新控制块通道数据
}

void QSttSclCtrlsWidget::ShowDatas(CSclCtrls* pSclCtrls)
{
	if (m_pSclCtrlsGrid == NULL)
	{
		return;
	}

	if(m_pSclCtrlsChGrid == NULL)
	{
		return;
	}

	m_pSclCtrlsGrid->ShowDatas(pSclCtrls);
	m_pSclCtrlsGrid->SelectRow(1);

	//获取通道数据
	m_pSclCtrlsChGrid->ShowDatas((CExBaseList*)pSclCtrls->GetHead());
	m_pSclCtrlsChGrid->SelectRow(1);

}

void QSttSclCtrlsWidget::UpdateSelectedState()
{
	if (m_pSclCtrlsGrid == NULL)
	{
		return;
	}

	if(m_pSclCtrlsChGrid == NULL)
	{
		return;
	}

	m_pSclCtrlsGrid->UpdateSelectedState();
	//m_pSclCtrlsChGrid->UpdateSelectedState();
}

void QSttSclCtrlsWidget::slot_UpdateCB_ChDatas(CExBaseList *pCB_Data)
{
	//根据当前所点击的数据，显示其通道数据
	m_pSclCtrlsChGrid->ShowDatas(pCB_Data);
	m_pSclCtrlsChGrid->SelectRow(1);
}


