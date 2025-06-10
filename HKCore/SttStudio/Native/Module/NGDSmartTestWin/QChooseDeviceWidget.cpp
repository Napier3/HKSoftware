#include "QChooseDeviceWidget.h"

QChooseDeviceWidget::QChooseDeviceWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pSclStation = NULL;
	ui.setupUi(this);
	m_pIecDevicesGrid = new QIecDevicesGrid(this);
	m_pIecDevicesGrid->InitGrid();
	ui.m_VLayout_DevGrid->addWidget(m_pIecDevicesGrid);
	m_pIecDevicesGrid->AttachDataViewOptrInterface(this);
}

QChooseDeviceWidget::~QChooseDeviceWidget()
{

}

void QChooseDeviceWidget::SetSCLStation(CSclStation *pSclStation)
{
	m_pSclStation = pSclStation;
}

void QChooseDeviceWidget::UpdateIEDGrids()
{
	m_pIecDevicesGrid->ShowDatas(m_pSclStation);
}

void QChooseDeviceWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	m_pIecDevicesGrid->UpdateSelectState(nRow);
}
