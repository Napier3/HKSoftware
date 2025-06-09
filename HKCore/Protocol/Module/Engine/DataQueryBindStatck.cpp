#include "StdAfx.h"
#include "DataQueryBindStatck.h"
#include "DeviceModel/DevcieModel.h"
#include "../XLanguageResourcePp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataQueryBind::CDataQueryBind()
{
	m_pData = NULL;
}

CDataQueryBind::~CDataQueryBind()
{

}

CDataQueryBindStatck::CDataQueryBindStatck(void)
{
	m_pDevice = NULL;
	m_nDatasetMode = PPTEMPLATE_DATASETMODE_TREE;
}

CDataQueryBindStatck::~CDataQueryBindStatck(void)
{
}

void CDataQueryBindStatck::SetBindCount(long nNewCount)
{
	long nCount = GetCount();
	long nIndex = 0;
	POS pos = NULL;

	if (nCount > nNewCount)
	{
		nNewCount = nCount - nNewCount;
		pos = GetTailPosition();
		
		for (nIndex=0; nIndex<nNewCount; nIndex++)
		{
			DeleteAt(pos);
			pos = GetTailPosition();
		}
	}
	else if (nNewCount > nCount)
	{
		nNewCount = nNewCount - nCount;

		for (nIndex=0; nIndex<nNewCount; nIndex++)
		{
			CDataQueryBind *pBind = new CDataQueryBind();
			AddTail(pBind);
		}
	}
	else
	{

	}
}

CDataQueryBind* CDataQueryBindStatck::SetBind(long nIndex, const CString &strDataType, const CString &strValue)
{
	CDataQueryBind *pBind = (CDataQueryBind*)GetAtIndex(nIndex);
	ASSERT (pBind != NULL);

	if (pBind == NULL)
	{
		return NULL;
	}

	if (pBind->m_strDataType == strDataType && pBind->m_strValue == strValue)
	{
		pBind->m_pData = NULL;//???????????????????????????
	}
	else
	{
		pBind->m_strDataType = strDataType;
		pBind->m_strValue = strValue;
		pBind->m_pData = NULL;
	}

	return pBind;
}

CExBaseObject* CDataQueryBindStatck::Query(BOOL bQueryDataNode)
{
	CDataQueryBind *pBind = (CDataQueryBind*)GetHead();
	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return NULL;
	}

	//CExBaseObject *pData = ((CPpDvmDevice*)m_pDevice)->GetDeviceModel();
	CExBaseObject *pData = m_pDevice;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		pBind = (CDataQueryBind*)GetAt(pos);

		if (bQueryDataNode)
		{
			if (pBind->m_strDataType == g_strVariableDataTypeItemIndexID)
			{
				break;
			}
		}

		//if (pBind->m_pData == NULL)
		{//如果当前关联的节点的数据为空
			ASSERT (pData->IsBaseList());

			pBind->m_pData = Query((CExBaseList*)pData, pBind);//从起伏对象中查找

			if (pBind->m_pData == NULL)
			{//没有找到，则退出
				break;
			}
			else
			{//找到，则继续往下查找
				pData = pBind->m_pData;
			}
		}
		//else
		//{
		//	pData = pBind->m_pData;
		//}

		pBind = (CDataQueryBind*)GetNext(pos);
	}

	pBind = (CDataQueryBind*)GetTail();

	if (pBind->m_pData == NULL && g_bLogBindQueryErrorInfor)
	{
		CString strLog = g_sLangTxt_DataBindRlship/*_T("数据绑定关系：")*/;
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pBind = (CDataQueryBind*)GetNext(pos);
            strLog.AppendFormat(_T("[%s=%s]"), pBind->m_strDataType.GetString(), pBind->m_strValue.GetString());
		}

        strLog += g_sLangTxt_NoCorrespondingData/*_T("没有对应的数据")*/;
		CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
		return NULL;
	}

	return pBind->m_pData;
}

CExBaseObject* CDataQueryBindStatck::GetDataQuery()
{
	POS pos = GetTailPosition();
	CExBaseObject *pDataQuery = NULL;
	CDataQueryBind *pBind =NULL;

	while (pos != NULL)
	{
		pBind = (CDataQueryBind*)GetPrev(pos);

		if (pBind->m_pData != NULL)
		{
			pDataQuery = pBind->m_pData;
			break;
		}
	}

	return pDataQuery;
}

CExBaseObject*  CDataQueryBindStatck::Query(CExBaseList *pList, CDataQueryBind *pBind)
{
	UINT nClassID = pList->GetClassID();
	CExBaseObject *pFind = NULL;

	if (pBind->m_strDataType.GetLength() <= 2)
	{
		return pList;
	}
	
	if (pList->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		long nIndex = CString_To_long(pBind->m_strValue);
		pFind = ((CDvmDataset*)pList)->FindByIndex(nIndex);
	}
	else if (pList->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE)
	{
		long nIndex = CString_To_long(pBind->m_strValue);
		pFind = ((CDvmLogicDevice*)pList)->FindByIndex(nIndex);
	}
	else if (pList->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		long nIndex = CString_To_long(pBind->m_strValue);
		pFind = ((CDvmDevice*)pList)->FindByIndex(nIndex);
	}
	else if (pList->GetClassID() == DVMCLASSID_CDVMDEVICES)
	{
		long nIndex = CString_To_long(pBind->m_strValue);
		pFind = ((CDvmDevices*)pList)->GetAtIndex(nIndex);

		if (pFind == NULL)
		{
			pFind = ((CDvmDevices*)pList)->FindByID(pBind->m_strValue);
		}
	}
	else
	{
		pFind = pList->FindByID(pBind->m_strValue);
	}

	return pFind;
}

void CDataQueryBindStatck::LogString(const CString &strTitle)
{
	if (!g_bLogBindQueryErrorInfor)
		return;

	CString strLog = strTitle;
	POS pos = GetHeadPosition();
	CDataQueryBind *pBind = NULL;

	while (pos != NULL)
	{
		pBind = (CDataQueryBind*)GetNext(pos);
        strLog.AppendFormat(_T("%s(%s) "), pBind->m_strDataType.GetString(), pBind->m_strValue.GetString());
	}

	CLogPrint::LogString(XLOGLEVEL_ERROR, strLog);
}
