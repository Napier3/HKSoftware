#include "RemoteMeasParaTable.h"
#include "../SttTestCntrFrameBase.h"

QRemoteMeasParaTable::QRemoteMeasParaTable(QWidget *parent)
	: QWidget(parent)
{
	m_pUIParaWidget = NULL;		//电压电流设置
	m_pTabWidget = NULL;

}

QRemoteMeasParaTable::~QRemoteMeasParaTable()
{

}


void QRemoteMeasParaTable::InitUI()
{
	if (m_pUIParaWidget != NULL)
	{
		delete m_pUIParaWidget;
		m_pUIParaWidget = NULL;
	}

	m_pUIParaWidget = new RemoteMeasParaSet(m_pTabWidget);
	m_pTabWidget->removeTab(0);//先删除空的占位widget
	CString strText;
	xlang_GetLangStrByFile(strText, "Manual_IV");
	m_pTabWidget->insertTab(0, m_pUIParaWidget, strText);
	m_pTabWidget->setCurrentIndex(0);
}


