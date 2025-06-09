#include "QIecDetcetWidget.h"
#include "..\Module\ScrollCtrl\ScrollComboBox.h"
#include "NGDSmartTestWinFrameBase.h"

QIecDetcetWidget::QIecDetcetWidget(QWidget *parent)
	: QWidget(parent)
{
	m_bDetect = TRUE;
	ui.setupUi(this);
	ui.m_Btn_StartDetect->setEnabled(FALSE);
	m_pGridIecCb = new CSttIecCbGrid(this);
	if (g_pSttGlobalFont != NULL)
	{
		m_pGridIecCb->setFont(*g_pSttGlobalFont);
		m_pGridIecCb->horizontalHeader()->setFont(*g_pSttGlobalFont);
	}
	m_pGridIecCb->InitGrid();
	ui.m_VCbGridLayout->insertWidget(0,m_pGridIecCb);
	m_pGridIecCb->AttachDataViewOptrInterface(this);
	connect(ui.m_Btn_StartDetect, SIGNAL(clicked()), this, SLOT(slot_On_m_BtnStartDetect_clicked()));
	connect(ui.m_Btn_StopDetect, SIGNAL(clicked()), this, SLOT(slot_On_m_BtnStopDetect_clicked()));
	connect(ui.m_Btn_ClearDetect, SIGNAL(clicked()), this, SLOT(slot_On_m_BtnClearDetect_clicked()));
}

QIecDetcetWidget::~QIecDetcetWidget()
{
}

void QIecDetcetWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	g_NGDSmartTestWin->m_SelectCbsChanged = TRUE;
}

void QIecDetcetWidget::slot_On_m_BtnStartDetect_clicked()
{
	m_bDetect = TRUE;
	g_NGDSmartTestWin->SendIecDetect(TRUE);
	ui.m_Btn_StartDetect->setEnabled(FALSE);
	ui.m_Btn_StopDetect->setEnabled(TRUE);
	ui.m_Btn_ClearDetect->setEnabled(TRUE);
}

void QIecDetcetWidget::slot_On_m_BtnStopDetect_clicked()
{
	m_bDetect = FALSE;
	g_NGDSmartTestWin->SendIecDetect(FALSE);
	ui.m_Btn_StartDetect->setEnabled(TRUE);
	ui.m_Btn_StopDetect->setEnabled(FALSE);
	ui.m_Btn_ClearDetect->setEnabled(TRUE);
}

void QIecDetcetWidget::slot_On_m_BtnClearDetect_clicked()
{
	if (m_pGridIecCb->m_bViewGoose == TRUE && m_pGridIecCb->m_bViewSmv == FALSE)
	{
		g_NGDSmartTestWin->RemoveCapGooseDevice();
	}
	else if (m_pGridIecCb->m_bViewSmv == TRUE && m_pGridIecCb->m_bViewGoose == FALSE)
	{
		g_NGDSmartTestWin->RemoveCap92Device();
	}
	if (m_bDetect == TRUE)
	{
		g_NGDSmartTestWin->SendIecDetect(TRUE);
	}
	m_pGridIecCb->ShowDatas(&g_NGDSmartTestWin->m_oX61850CapBase.m_oCapDeviceAll);
}
