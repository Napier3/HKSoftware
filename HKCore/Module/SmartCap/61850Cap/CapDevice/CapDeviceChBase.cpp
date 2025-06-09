//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChBase.cpp  CCapDeviceChBase


#include "stdafx.h"
#include "CapDeviceChBase.h"

BOOL Is_DsID_Numbers(const CString &strID, long nPos)
{
	CString strTemp = strID.Mid(nPos);
	long nCount = strTemp.GetLength();
	long k = 0;

	for (k=0; k<nCount; k++)
	{
		char ch = strTemp.GetAt(k);

		if (ch < '0' || '9' < ch)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL Is_SvDataSetID(const CString &strID)
{
	if (strID.Find(CAP_DATASET_MAP_ID_dsSV) < 0)
	{
		return FALSE;
	}

	if (strID.GetLength() == 4)
	{
		return TRUE;
	}

	//增加了dsSV1$Power等数据集，因此需要判断后面的字符全部为数字才正确
	return Is_DsID_Numbers(strID, 4);
}

BOOL Is_SvDataset(CDvmDataset *pDataset)
{
	return Is_SvDataSetID(pDataset->m_strID);
}


BOOL Is_GsDataSetID(const CString &strID, const CString &strGsTypeID)
{
	if (strGsTypeID == strID)
	{
		return TRUE;
	}

	if (strID.Find(strGsTypeID) < 0)
	{
		return FALSE;
	}

	return Is_DsID_Numbers(strID, strGsTypeID.GetLength());
}


BOOL Is_GsDataSetID_Gin(const CString &strID)
{
	return Is_GsDataSetID(strID, CAP_DATASET_MAP_ID_GIN);
}

BOOL Is_GsDataSetID_Gout(const CString &strID)
{
	return Is_GsDataSetID(strID, CAP_DATASET_MAP_ID_GOUT);
}

BOOL Is_GsDataSetID(const CString &strID)
{
	if (Is_GsDataSetID_Gout(strID))
	{
		return TRUE;
	}

	if (Is_GsDataSetID_Gin(strID))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL Is_GsDataset(CDvmDataset *pDataset)
{
	if (pDataset->m_strID.Find(CAP_DATASET_MAP_ID_GOUT) < 0)//dsGout
	{
		return FALSE;
	}

	if (pDataset->m_strID.GetLength() == 6)
	{
		return TRUE;
	}

	return Is_DsID_Numbers(pDataset->m_strID, 6);
}

CCapDeviceChBase::CCapDeviceChBase()
{
	//初始化属性
	m_nSelect = 1;
	m_nChType = CAPDEVICE_CHTYPE_N;
	m_nLength = 0;

	//初始化成员变量
	m_pCapRecord = NULL;

	m_nMatchState = MATCH_STATE_NONE;
	m_pRefDvmData = NULL;   //关联的设备数据模型对象
}

CCapDeviceChBase::~CCapDeviceChBase()
{
}

void CCapDeviceChBase::AttachIecCfgDataCh(CIecCfgDataChBase *pCfgDataCh)
{	
	if(pCfgDataCh == NULL)
	{
		return;
	}

	InitChannel(pCfgDataCh);
}

void CCapDeviceChBase::InitNameID(const CString& strID)
{ 
	m_strName = m_strID = strID;
}

void CCapDeviceChBase::InitNameID(long nDvIndex, long nChIndex)
{ 
	m_strName.Format(_T("%d"), nChIndex);
	m_strName = _T("通道") + m_strName;

	switch (m_nChType)
	{
	case CAPDEVICE_CHTYPE_N:
		m_strID.Format(_T("DV%d_Ch%d"), nDvIndex, nChIndex);
		break;

	case CAPDEVICE_CHTYPE_U:
		m_strID.Format(_T("DV%d_U%d"), nDvIndex, nChIndex);
		break;

	case CAPDEVICE_CHTYPE_I:
		m_strID.Format(_T("DV%d_I%d"), nDvIndex, nChIndex);
		break;

	case CAPDEVICE_CHTYPE_B:
		m_strID.Format(_T("DV%d_B%d"), nDvIndex, nChIndex);
		break;
	}
	
}

void CCapDeviceChBase::InitChannel(CIecCfgDataChBase *pIecCfgDataCh)
{
	ASSERT(pIecCfgDataCh != NULL);

	if (pIecCfgDataCh)
	{
		m_strName = pIecCfgDataCh->m_strName;
		m_strID = pIecCfgDataCh->m_strID;

		if (pIecCfgDataCh->IsTimeCh())
		{
			m_nChType = CAPDEVICE_CHTYPE_T;
		}
		else if (pIecCfgDataCh->IsUCh())
		{
			m_nChType = CAPDEVICE_CHTYPE_U;
		}
		else if (pIecCfgDataCh->IsICh())
		{
			m_nChType = CAPDEVICE_CHTYPE_I;
		}

//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s;%s;%d;%s"),m_strID.GetString(),m_strName.GetString(),m_nChType,pIecCfgDataCh->m_strAppChID.GetString());
	}
}

void CCapDeviceChBase::InitChannel(CDvmData *pChData)
{
	pChData->m_strName = m_strName;
	pChData->m_strID = m_strID;

	InitChannelAttrs(pChData);
}

void CCapDeviceChBase::InitChannelAttrs(CDvmData *pChData)
{

}

void CCapDeviceChBase::UpdateChTypeAndLength(WORD wChType,WORD wLength)
{
	m_nChType = wChType;
}
