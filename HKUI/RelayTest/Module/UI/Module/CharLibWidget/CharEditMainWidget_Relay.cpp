#include "CharEditMainWidget_Relay.h"

#include "CharEditWidget_None.h"
#include "CharEditWidget_Distance.h"
#include "CharEditWidget_Inverse.h"
#include "CharEditWidget_Diff.h"
#include "CharEditWidget_Syn.h"

QCharEditMainWidget_Relay::QCharEditMainWidget_Relay(QWidget* pParent) : QCharEditMainWidget(pParent)
{

}

QCharEditMainWidget_Relay::~QCharEditMainWidget_Relay()
{

}

void QCharEditMainWidget_Relay::InitCharacteristicsLib(const CString &strCharLibFile)
{
	if (strCharLibFile.GetLength() == 0)
	{
		if (m_pCharacteristicsLib != NULL)
		{
			delete m_pCharacteristicsLib;
			m_pCharacteristicsLib = NULL;
		}
	}
	else
	{
		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += strCharLibFile;

		if (m_pCharacteristicsLib == NULL)
		{
			m_pCharacteristicsLib = new CCharacteristicLib();
		}
		else
		{
			m_pCharacteristicsLib->DeleteAll();
		}

		m_pCharacteristicsLib->OpenXmlFile(strFile, CCharacteristicXmlRWKeys::CCharacteristicLibKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	CreateCharEditWidgetByLib();
}

void QCharEditMainWidget_Relay::CreateCharEditWidgetByLib()
{
	CString strLibID;

	if (m_pCharacteristicsLib == NULL)
	{
		strLibID = _T("none");
	}
	else
	{
		strLibID = m_pCharacteristicsLib->m_strID;
	}


	if (m_strLastCharLibID.GetLength() != 0)
	{
		if (m_strLastCharLibID == strLibID)
		{//没有改变，则返回
			return;
		}

		ui.m_layoutLeft->removeWidget(m_pCharEditWidget->m_pCharEditWidget);
		m_pCharEditWidget->DeleteCharEditWidget();
		m_pCharEditWidget = NULL;
	}

	if (strLibID == "none")
	{
		m_pCharEditWidget = new QCharEditWidget_None();
	}
	else if (strLibID == "distance")
	{
		m_pCharEditWidget = new QCharEditWidget_Distance();
	}
	else if (strLibID == "inverse")
	{
		m_pCharEditWidget = new QCharEditWidget_Inverse();
	}
	else if (strLibID == "diff")
	{
		m_pCharEditWidget = new QCharEditWidget_Diff();
	}
	else if (strLibID == "syn")
	{
		m_pCharEditWidget = new QCharEditWidget_Syn();
	}

	if (m_pCharEditWidget != NULL)
	{
		ui.m_layoutLeft->addWidget(m_pCharEditWidget->m_pCharEditWidget);
	}
}

void QCharEditMainWidget_Relay::ShowCharacteristics(CCharacteristics *pCharacteristics)
{
	
}

