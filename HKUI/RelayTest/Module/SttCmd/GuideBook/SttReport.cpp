#include "stdafx.h"
#include "SttReport.h"
#include "../SttRptMapDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttReport::CSttReport()
{
	m_pValues = NULL;
	m_pRptDvmDataset = NULL;
}

CSttReport::~CSttReport()
{
}

//重写父类方法
long CSttReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strBeginTimeKey,oNode,m_strBeginTime);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey,oNode,m_strEndTime);
	return 0;
}

long CSttReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strBeginTimeKey,oElement,m_strBeginTime);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey,oElement,m_strEndTime);
	return 0;
}

long CSttReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strBeginTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strEndTime);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strBeginTime);
		BinarySerializeRead(oBinaryBuffer, m_strEndTime);
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strBeginTime);
		BinarySerializeWrite(oBinaryBuffer, m_strEndTime);
	}
	return 0;
}

void CSttReport::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDVMVALUES)
		{
			m_pValues = (CDvmValues *)p;
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			m_pRptDvmDataset = (CDvmDataset *)p;
		}
	}

	if (m_pValues == NULL)
	{
		m_pValues = new CDvmValues();
		AddNewChild(m_pValues);
	}
	if (m_pRptDvmDataset == NULL)
	{
		m_pRptDvmDataset = new CDvmDataset();
		AddNewChild(m_pRptDvmDataset);
	}

	//对于原先的模板，打开时，自动添加默认的报告
	//AddRptValues_ErrorCal();
}

BOOL CSttReport::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(pDest == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDest);

	CSttReport* pSttReport = (CSttReport*)pDest;
	pSttReport->m_strBeginTime = m_strBeginTime;
	pSttReport->m_strEndTime = m_strEndTime;

	return TRUE;
}

CBaseObject* CSttReport::Clone()
{
	CSttReport* pSttReport = new CSttReport();
	Copy(pSttReport);
	return pSttReport;
}

CBaseObject* CSttReport::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttReport *p = new CSttReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CSttReport::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCValuesKey)
	{
		m_pValues = new CDvmValues();
		return m_pValues;
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		m_pRptDvmDataset = new CDvmDataset();
		return m_pRptDvmDataset;
	}
	else if (strClassID == pXmlKeys->m_strCSttRptMapDatasKey)
	{
		return new CSttRptMapDatas();
	}

	return NULL;
}

CExBaseObject* CSttReport::CreateNewChild(long nClassID)
{
	if(nClassID == DTMCLASSID_CDVMVALUES)
	{
		m_pValues = new CDvmValues();
		return m_pValues;
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		m_pRptDvmDataset = new CDvmDataset();
		return m_pRptDvmDataset;
	}
	else if (nClassID == STTCMDCLASSID_CSTTRPTMAPDATAS)
	{
		return new CSttRptMapDatas();
	}

	return NULL;
}

void CSttReport::InitValues(CValues *pSrc)
{
    if (m_pValues == NULL)
    {
        m_pValues = new CDvmValues();
        AddNewChild(m_pValues);
    }

	if (pSrc != NULL)
	{
		//m_pValues->AppendCloneEx(*pSrc);
		POS pos = pSrc->GetHeadPosition();

		while (pos != NULL)
		{
			CValue *pValue = (CValue *)pSrc->GetNext(pos);
			m_pValues->AddValue(pValue->m_strID, pValue->m_strName, pValue->m_strValue);
		}
	}
}

void CSttReport::InitRptDvmDataset(CDvmDataset *pSrc)
{
	if (pSrc == NULL)
	{
		return;
	}

    if (m_pRptDvmDataset == NULL)
    {
        m_pRptDvmDataset = new CDvmDataset();
        AddNewChild(m_pRptDvmDataset);
    }

    m_pRptDvmDataset->AppendCloneEx(*pSrc);
}

void CSttReport::InitReport(CDataGroup *pDataGroup)
{
	InitValues(NULL);
	m_pValues->DeleteAll();
	
	POS pos = pDataGroup->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataGroup->GetNext(pos);
		m_pValues->AddValue(pData->m_strID, pData->m_strValue);
	}
}

CDvmValue* CSttReport::FindValueByID(const CString &strID)
{
	CDvmValues *pDvmValues = (CDvmValues*)FindByClassID(DTMCLASSID_CDVMVALUES);

	if (pDvmValues == NULL)
	{
		return NULL;
	}

	return (CDvmValue*)pDvmValues->FindByID(strID);
}

//报告中，增加几个固定的结果值，用于绑定误差判断的计算值
BOOL CSttReport::AddRptValues_ErrorCal()
{
	if (m_pValues == NULL)
	{
		return FALSE;
	}

	m_pValues->AddValue(_T("AbsRsltCal1"), _T(""));
	m_pValues->AddValue(_T("AbsRsltCal2"), _T(""));
	m_pValues->AddValue(_T("RelRsltCal1"), _T(""));
	m_pValues->AddValue(_T("RelRsltCal2"), _T(""));

	return TRUE;
}