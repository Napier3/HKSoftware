#include "HarmParaTable.h"
#include "../SttTestCntrFrameBase.h"

QHarmParaTable::QHarmParaTable(QWidget *parent)
	: QWidget(parent)
{
	InitUI();

}

QHarmParaTable::~QHarmParaTable()
{

}


void QHarmParaTable::InitUI()
{
	m_pHBoxLayout_Main = new QHBoxLayout(this);
	this->setLayout(m_pHBoxLayout_Main);

	
	m_pUChannel = new QHarmTable(this);
	m_pUChannel->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pUChannel->setFont(*g_pSttGlobalFont);
	m_pHBoxLayout_Main->addWidget(m_pUChannel);

	m_pIChannel = new QHarmTable(this);
	m_pIChannel->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIChannel->setFont(*g_pSttGlobalFont);
	m_pHBoxLayout_Main->addWidget(m_pIChannel);
	
}


