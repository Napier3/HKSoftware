#include "RemoteMeasParaTable.h"
#include "../SttTestCntrFrameBase.h"

QRemoteMeasParaTable::QRemoteMeasParaTable(QWidget *parent)
	: QWidget(parent)
{
	m_pUIParaWidget = NULL;		//��ѹ��������
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
	m_pTabWidget->removeTab(0);//��ɾ���յ�ռλwidget
	CString strText;
	xlang_GetLangStrByFile(strText, "Manual_IV");
	m_pTabWidget->insertTab(0, m_pUIParaWidget, strText);
	m_pTabWidget->setCurrentIndex(0);
}


