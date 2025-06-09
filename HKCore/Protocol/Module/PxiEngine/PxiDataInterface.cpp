// PoDataInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiDataInterface.h"


// CPxiDataInterface

CPxiDataInterface::CPxiDataInterface()
{
	m_pDataInterface = NULL;
}

CPxiDataInterface::~CPxiDataInterface()
{
}


void CPxiDataInterface::OnFinalRelease()
{

}

// CPxiDataInterface 消息处理程序

long CPxiDataInterface::Reset(void)
{
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->DeleteAll();
	}

	return 0;
}

long CPxiDataInterface::AddData(const CString &bstrID, const CString &bstrValue)
{
	if (m_pDataInterface != NULL)
	{
		AddData2(bstrID, bstrValue);
	}

	CString strID = bstrID;
	CString strValue = bstrValue;

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("AddDataInterface:[%s]=[%s]"), strID.GetString(), strValue.GetString());
	
	return 0;
}

void CPxiDataInterface::AddData2(const CString &strID, const CString &strValue)
{
	if (m_pDataInterface != NULL)
	{
		CBbVariable *pVariable = new CBbVariable();
		pVariable->m_strID = strID;
		pVariable->m_strValue = strValue;
		m_pDataInterface->AddHead(pVariable);
	}
}

//2020-5-21  lijunqing
void CPxiDataInterface::InitDataInterface(CDataGroup *pParas)
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

void CPxiDataInterface::InitDataInterface(CDvmData *pData)
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

