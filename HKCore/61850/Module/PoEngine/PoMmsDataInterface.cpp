// PoDataInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "PoMmsDataInterface.h"

// CPoMmsDataInterface


CPoMmsDataInterface::CPoMmsDataInterface()
{
	m_pDataInterface = NULL;
}

CPoMmsDataInterface::~CPoMmsDataInterface()
{
}


void CPoMmsDataInterface::OnFinalRelease()
{

}


// CPoMmsDataInterface 消息处理程??

long CPoMmsDataInterface::Reset(void)
{
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->DeleteAll();
	}

	return 0;
}

long CPoMmsDataInterface::AddData(const CString &bstrID, const CString &bstrValue)
{
	long nCount = 0;

	if (m_pDataInterface != NULL)
	{
		AddData2(bstrID, bstrValue);
		nCount = m_pDataInterface->GetCount();
	}

	CString strID = bstrID;
	CString strValue = bstrValue;

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("AddDataInterface:[%s]=[%s][%d]"), strID, strValue, nCount);

	return 0;
}

void CPoMmsDataInterface::AddData2(const CString &strID, const CString &strValue)
{
	if (m_pDataInterface != NULL)
	{
		CValue *pVariable = new CValue();
		pVariable->m_strID = strID;
		pVariable->m_strValue = strValue;
		m_pDataInterface->AddHead(pVariable);
	}
}


//2020-5-21  lijunqing
void CPoMmsDataInterface::InitDataInterface(CDataGroup *pParas)
{
    if (m_pDataInterface == NULL)
    {
        return;
    }

    m_pDataInterface->DeleteAll();
    POS pos = pParas->GetHeadPosition();
    CExBaseObject *p = NULL;
    CDvmData *pData = NULL;

    while (pos != NULL)
    {
        p = (CExBaseObject*)pParas->GetNext(pos);

        if (p->GetClassID() == DVMCLASSID_CDVMDATA)
        {
            pData = (CDvmData*)p;
            AddData2(pData->m_strID, pData->m_strValue);
        }
    }
}

void CPoMmsDataInterface::InitDataInterface(CDvmData *pData)
{
    if (m_pDataInterface == NULL)
    {
        return;
    }

    m_pDataInterface->DeleteAll();
    POS pos = pData->GetHeadPosition();
    CExBaseObject *p = NULL;
    CDvmValue *pValue = NULL;

    while (pos != NULL)
    {
        p = (CExBaseObject*)pData->GetNext(pos);

        if (p->GetClassID() == DVMCLASSID_CDVMVALUE)
        {
            pValue = (CDvmValue*)p;
            AddData2(pValue->m_strID, pValue->m_strValue);
        }
    }
}
