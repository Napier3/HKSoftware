//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasBase.cpp  CIecCfgDatasBase


#include "stdafx.h"
#include "IecCfgDatasBase.h"

CIecCfgDatasBase::CIecCfgDatasBase()
{
	//初始化属性
	m_nDatasCount = 0;
	m_nDatasUse = 1;

	//初始化成员变量
#ifdef IECFG_USE_KEYDB
	m_pMatchList = NULL;
#endif
}


CIecCfgDatasBase::~CIecCfgDatasBase()
{
#ifdef IECFG_USE_KEYDB

	if (m_pMatchList != NULL)
	{
		delete m_pMatchList;
		m_pMatchList = NULL;
	}
#endif
}

#ifdef IECFG_USE_KEYDB
void CIecCfgDatasBase::InitMatchList(CXKeyDB *pKeyDB)
{
	if (m_pMatchList == NULL)
	{
		m_pMatchList = new CXMatchList;
	}

	m_pMatchList->DeleteAll();

	POS pos = GetHeadPosition();
	CIecCfgDataBase *pIecCfgDataBase = NULL;

	while (pos != NULL)
	{
		pIecCfgDataBase = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(pIecCfgDataBase))
		{
			pIecCfgDataBase->InitMatchList(pKeyDB);
			m_pMatchList->Init(pIecCfgDataBase->m_pCfgChs, pKeyDB, NULL);//将所有子控制块的通道全部添加进去
		}
	}
}
#endif

long CIecCfgDatasBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDatasCountKey, oNode, m_nDatasCount);
	xml_GetAttibuteValue(pXmlKeys->m_strDatasUseKey, oNode, m_nDatasUse);
	return 0;
}

long CIecCfgDatasBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDatasCountKey, oElement, m_nDatasCount);
	xml_SetAttributeValue(pXmlKeys->m_strDatasUseKey, oElement, m_nDatasUse);
	return 0;
}

BOOL CIecCfgDatasBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgDatasBase *p = (CIecCfgDatasBase*)pObj;

	if(m_nDatasCount != p->m_nDatasCount)
	{
		return FALSE;
	}

	if(m_nDatasUse != p->m_nDatasUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDatasBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase *p = (CIecCfgDatasBase*)pDest;

	p->m_nDatasCount = m_nDatasCount;
	p->m_nDatasUse = m_nDatasUse;
	return TRUE;
}

void CIecCfgDatasBase::SetCount(long nCount, CExBaseList &oListTemp)
{
	long nOldCount = GetCount();
	long nIndex = 0;
	CIecCfgDataBase *pData = NULL;

	if (nOldCount == nCount)
	{
		return;
	}

	if (nCount > nOldCount)
	{
		for (nIndex=0; nIndex<nCount - nOldCount; nIndex++)
		{
			pData = CreateIecCfgData();
			pData->OpenCfgDefaultConfigFile();
			AddNewChild(pData);
		}

		return;
	}

	POS pos = FindIndex(nCount);
	POS posPrev = pos;

	while (pos != NULL)
	{
		pData = (CIecCfgDataBase*)GetNext(pos);
		oListTemp.AddTail(pData);
		RemoveAt(posPrev);
		posPrev = pos;
	}
}

void CIecCfgDatasBase::SetCount(long nCount)
{
	long nIndex = 0;
	CIecCfgDataBase *pData = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pData = CreateIecCfgData();
		pData->OpenCfgDefaultConfigFile();
		AddNewChild(pData);
	}
}

long CIecCfgDatasBase::GetCfgDataCount()
{
	if (m_nDatasUse == 0)
	{
		return 0;
	}

	CExBaseList oList;
	GetIecCfgDatas(oList);
	long nCount = oList.GetCount();
	oList.RemoveAll();

	return nCount;
}

BOOL CIecCfgDatasBase::SetCfgDataCount(long nSetCount ,long nFirstFiberNum,BOOL bSingleFiber)
{
	m_nDatasUse = 1;

	CExBaseList oList;
	GetIecCfgDatas(oList);
	SetCfgDataFiberNum(&oList,nFirstFiberNum,bSingleFiber);
	long nCurCount = oList.GetCount();

	if (nCurCount<nSetCount)
	{
//		SetCfgDataFiberNum(&oList,nFirstFiberNum,bSingleFiber);
		oList.RemoveAll();
		return FALSE;
	}

	if (nSetCount == nCurCount)
	{
//		SetCfgDataFiberNum(&oList,nFirstFiberNum,bSingleFiber);
		oList.RemoveAll();
		return TRUE;
	}

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		nIndex++;

		if (nIndex>nSetCount)
		{
			Delete(pCurObj);
		}
	}

	oList.RemoveAll();
	return TRUE;
}

BOOL CIecCfgDatasBase::SetCfgDataCountEx(long nSetCount ,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,BOOL bSingleFiber)
{
	m_nDatasUse = 1;
	CExBaseList oList;
	GetIecCfgDatas(oList);
	SetCfgDataFiberNumEx(&oList,nFiber1BeginIndex,nFiber2BeginIndex,nTotalFiberNum,bSingleFiber);
	long nCurCount = oList.GetCount();

	if (nCurCount<nSetCount)
	{
		oList.RemoveAll();
		return FALSE;
	}

	if (nSetCount == nCurCount)
	{
		oList.RemoveAll();
		return TRUE;
	}

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		nIndex++;

		if (nIndex>nSetCount)
		{
			Delete(pCurObj);
		}
	}

	oList.RemoveAll();
	return TRUE;
}

BOOL CIecCfgDatasBase::DeleteCfgDataByNum(long nDeleteNum)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		nIndex++;

		if (nIndex<=nDeleteNum)
		{
			Delete(pCurObj);
		}
	}

	oList.RemoveAll();
	return TRUE;
}

void CIecCfgDatasBase::SetCfgDataFiberNum(CExBaseList *pCfgDataList,long nFirstFiberNum,BOOL bSingleFiber)
{
   	CExBaseObject *pCurObj = NULL;
   	POS pos = pCfgDataList->GetHeadPosition();
   	long nIndex = nFirstFiberNum;
   	CIecCfgDataBase *pIecCfgDataBase = NULL;
   
   	while (pos != NULL)
   	{
   		pCurObj = pCfgDataList->GetNext(pos);
   		pIecCfgDataBase = (CIecCfgDataBase *)pCurObj;
   		pIecCfgDataBase->m_nFiberIndex = nIndex;
   
   		if (!bSingleFiber)
   		{
   			nIndex++;
   		}
   	}
}

void CIecCfgDatasBase::SetCfgDataFiberNumEx(CExBaseList *pCfgDataList,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,BOOL bSingleFiber)
{
	CExBaseObject *pCurObj = NULL;
	POS pos = pCfgDataList->GetHeadPosition();
	long nFiber1Index = nFiber1BeginIndex;
	long nFiber2Index = nFiber2BeginIndex;
	CIecCfgDataBase *pIecCfgDataBase = NULL;

	while (pos != NULL)
	{
		pCurObj = pCfgDataList->GetNext(pos);
		pIecCfgDataBase = (CIecCfgDataBase *)pCurObj;

		if (nFiber1Index>=nTotalFiberNum)//当前光口编号大于等于总光口数时,设置为从第一个光口循环输出
		{
			nFiber1Index = 0;
		}

		while(nFiber2Index>=8)//zhouhj 20201212 AT02D最大光口数6从光口3到光口8
		{
			nFiber2Index -= 6;
		}

		pIecCfgDataBase->m_nFiberIndex = nFiber1Index;
		pIecCfgDataBase->m_nFiber2Index = nFiber2Index;

		if (!bSingleFiber)
		{
			nFiber1Index++;
			nFiber2Index++;
		}
	}
}

BOOL CIecCfgDatasBase::IsCfgData(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	return IsCfgData(nClassID);
}

BOOL CIecCfgDatasBase::IsCfgData_Common(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	if ((nClassID == CFGCLASSID_CIECCFG91DATA)||(nClassID == CFGCLASSID_CIECCFG92DATA)||(nClassID == CFGCLASSID_CIECCFG6044DATA)
		||(nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)||(nClassID == CFGCLASSID_CIECCFG2MDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)
		||(nClassID == CFGCLASSID_CIECCFG2MINDATA)||(nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA)||(nClassID == CFGCLASSID_CIECCFGGINDATA)
		||(nClassID == CFGCLASSID_CIECCFGGOUTDATA)/*||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA*/)
//		||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDatasBase::IsCfgData_SV_GOOSECommon(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	if ((nClassID == CFGCLASSID_CIECCFG91DATA)||(nClassID == CFGCLASSID_CIECCFG92DATA)||(nClassID == CFGCLASSID_CIECCFG6044DATA)
		||/*(nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)||*/(nClassID == CFGCLASSID_CIECCFG2MDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)
		||(nClassID == CFGCLASSID_CIECCFG2MINDATA)/*||(nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA)*/||(nClassID == CFGCLASSID_CIECCFGGINDATA)
		||(nClassID == CFGCLASSID_CIECCFGGOUTDATA)/*||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA*/)
//		||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDatasBase::IsCfgData_6044Common(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	if ((nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)||(nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA))
	{
		return TRUE;
	}

	return FALSE;
}

void CIecCfgDatasBase::SetDataUse(long nUse, long nDataCount)	
{	
	m_nDatasUse = nUse;	

	if (m_nDatasUse == 0)
	{
		DeleteAll();
		return;
	}

	if (nDataCount <= 0)
	{
		nDataCount = GetCfgDataCount();
	}
	
	if (nDataCount > 0)
	{
// 		nDataCount = 1;
		CExBaseList oList;
		SetCount(nDataCount, oList);
		oList.RemoveAll();
	}
}

void CIecCfgDatasBase::DelteteContrlBlocks_Unselected()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->m_nUseFlag == 0)
			{
				Delete(p);
			}
		}
	}
}

BOOL CIecCfgDatasBase::HasContrlBlock_Selected()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData_Common(p))
		{
			if (p->m_nUseFlag)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CIecCfgDatasBase::HasContrlBlock_SV_GOOSESelected()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData_SV_GOOSECommon(p))
		{
			if (p->m_nUseFlag)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CIecCfgDatasBase::HasContrlBlock_FT3Selected()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData_6044Common(p))
		{
			if (p->m_nUseFlag)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}
BOOL CIecCfgDatasBase::HasRepeatCtrl(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->GetAppID() == dwAppID)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CIecCfgDatasBase::SetAllFiberIndex(long nFiberIndex)
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			p->m_nFiberIndex = nFiberIndex;
		}
	}
}

//void CIecCfgDatasBase::SetSelectState_AllCtrlBlock(long nUseFlag)
//{
//	POS pos = GetHeadPosition();
//	CIecCfgDataBase *p = NULL;
//
//	while (pos != NULL)
//	{
//		p = (CIecCfgDataBase *)GetNext(pos);
//
//		if (IsCfgData(p))
//		{
//			p->m_nUseFlag = nUseFlag;
//		}
//	}
//}

void CIecCfgDatasBase::SetSelectState_AllCtrlBlock(long nUseFlag, UINT nClassID)			//20240523 xueyangfan  根据插件数量判断全选默认勾选数量
{
	POS pos = GetHeadPosition();
	long nUseCount = 0;
	
	long nMaxCfgDataCount = GetMaxCfgDataCount(nClassID);
	while (pos != NULL)
	{
		CIecCfgDataBase *p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p) && p != NULL)
			{
				if (nUseCount < nMaxCfgDataCount)
				{
					p->m_nUseFlag = nUseFlag;
					nUseCount++;
				}
				else
				{
					p->m_nUseFlag = 0;
				}
			}
	} 
}

void CIecCfgDatasBase::DeleteRepeatCtrl(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->GetAppID() == dwAppID)
			{
				Delete(p);
			}
		}
	}
}

void CIecCfgDatasBase::GetIecCfgDatas(CExBaseList &oList)
{
	//如果不使用，则返回
	if (m_nDatasUse == 0)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			oList.AddTail(p);
		}
	}
}

CIecCfgDataBase* CIecCfgDatasBase::GetIecCfgData(long nIndex)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	CIecCfgDataBase *pData = (CIecCfgDataBase*)oList.GetAtIndex(nIndex);
	oList.RemoveAll();

	return pData;
}

long CIecCfgDatasBase::GetIecCfgDataIndex(CIecCfgDataBase *pIecCfgData)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	long nIndex = oList.FindIndex(pIecCfgData);
	oList.RemoveAll();

	return nIndex;
}

CIecCfgDataBase* CIecCfgDatasBase::AddNewIecCfgData()
{
	CIecCfgDataBase *pData = NULL;
	pData = CreateIecCfgData();
	pData->OpenCfgDefaultConfigFile();
	AddNewChild(pData);
	return pData;
}


BOOL CIecCfgDatasBase::DeleteCfgData(CIecCfgDataBase *pCfgData)
{
	POS pos = Find(pCfgData);

	if (pos == NULL)
	{
		return FALSE;
	}

	Delete(pCfgData);

	if (GetCfgDataCount() == 0)
	{
		SetDataUse(0);
	}

	return TRUE;
}

void CIecCfgDatasBase::GetFiberIndexUse(long nCount, long *pnFiberIndexUse)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);
	
	POS pos = oList.GetHeadPosition();
	CIecCfgDataBase *pCfgData = NULL;

	while (pos != NULL)
	{
		pCfgData = (CIecCfgDataBase *)oList.GetNext(pos);
		pnFiberIndexUse[pCfgData->m_nFiberIndex] = 1;
	}
	oList.RemoveAll();
}

void CIecCfgDatasBase::SetFiberIndexByFiber2Index()
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	POS pos = oList.GetHeadPosition();
	CIecCfgDataBase *pCfgData = NULL;

	while (pos != NULL)
	{
		pCfgData = (CIecCfgDataBase *)oList.GetNext(pos);
		pCfgData->m_nFiberIndex = pCfgData->m_nFiber2Index;
	}

	oList.RemoveAll();
}

void CIecCfgDatasBase::SetFiber2IndexByFiberIndex(long nOffset)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	POS pos = oList.GetHeadPosition();
	CIecCfgDataBase *pCfgData = NULL;

	while (pos != NULL)
	{
		pCfgData = (CIecCfgDataBase *)oList.GetNext(pos);
		pCfgData->m_nFiber2Index = (pCfgData->m_nFiberIndex+nOffset);
	}

	oList.RemoveAll();
}

BOOL CIecCfgDatasBase::CanAddCfgData(UINT nClassID)
{
	long nMaxCount = GetMaxCfgDataCount(nClassID);
	//long nCurrCount = GetCfgDataCount();
	long nCurrCount = GetUseDatasCount(nClassID);

	return (nMaxCount > nCurrCount);
}

BOOL CIecCfgDatasBase::CanAddCfgData()
{
	long nMaxCount = GetMaxCfgDataCount();
	//long nCurrCount = GetCfgDataCount();
	long nCurrCount = GetUseDatasCount();

	return (nMaxCount > nCurrCount);
}

#ifdef _PSX_IDE_QT_
void iecfg_IncreaseCfgData(long nDataID, unsigned long long &vValue, long nOffset=1, unsigned long long *pvMin=NULL, unsigned long long *pvMax=NULL)
{
	switch (nDataID)
	{
	case CFGDATAID_FIBER:
//		ASSERT (vValue.vt == VT_I4);
		vValue += nOffset;

		if (pvMin != NULL)
		{
//			ASSERT (pvMin->vt == VT_I4);

			if (nOffset < 0)
			{
				if (vValue < *pvMin)
				{
					vValue = *pvMax;
				}
			}
		}

		if (pvMax != NULL)
		{
//			ASSERT (pvMax->vt == VT_I4);

			if (nOffset > 0)
			{
				if (vValue > *pvMax)
				{
					vValue = *pvMin;
				}
			}
		}

		break;

	case CFGDATAID_APPID:
//		ASSERT (vValue.vt == VT_UI4);
		vValue += nOffset;

		// 		if (pvMin != NULL)
		// 		{
		// 			ASSERT (pvMin->vt == VT_UI4);
		// 
		// 			if (vValue.ulVal < pvMin->ulVal)
		// 			{
		// 				vValue.ulVal = pvMax->ulVal;
		// 			}
		// 		}

		if (pvMax != NULL)
		{
//			ASSERT (pvMax->vt == VT_UI4);

			if (nOffset > 0)
			{
				if (vValue > *pvMax)
				{
					vValue = *pvMin;
				}
			}
			else//if (nOffset < 0)
			{
				if (vValue > *pvMax)
				{
					vValue = *pvMax;
				}
			}
		}

		break;

	case CFGDATAID_SRCMAC:
	case CFGDATAID_DESTMAC:
//		ASSERT (vValue.vt == VT_UI8);
		vValue += nOffset;

		// 		if (vValue.ullVal >= 0x001000000000000)
		// 		{
		// 			vValue.ullVal = 0;
		// 		}
		if (pvMax != NULL)
		{
//			ASSERT (pvMax->vt == VT_UI8);

			if (nOffset > 0)
			{
				if (vValue > *pvMax)
				{
					vValue = *pvMin;
				}
			}
			else//if (nOffset < 0)
			{
				if (vValue > *pvMax)
				{
					vValue = *pvMax;
				}
			}
		}
		break;
	}
}
#else
void iecfg_IncreaseCfgData(long nDataID, VARIANT &vValue, long nOffset=1, VARIANT *pvMin=NULL, VARIANT *pvMax=NULL)
{
	switch (nDataID)
	{
	case CFGDATAID_FIBER:
		ASSERT (vValue.vt == VT_I4);
		vValue.lVal += nOffset;

		if (pvMin != NULL)
		{
			ASSERT (pvMin->vt == VT_I4);

			if (nOffset < 0)
			{
				if (vValue.lVal < pvMin->lVal)
				{
					vValue.lVal = pvMax->lVal;
				}
			}
		}

		if (pvMax != NULL)
		{
			ASSERT (pvMax->vt == VT_I4);

			if (nOffset > 0)
			{
				if (vValue.lVal > pvMax->lVal)
				{
					vValue.lVal = pvMin->lVal;
				}
			}
		}

		break;

	case CFGDATAID_APPID:
		ASSERT (vValue.vt == VT_UI4);
		vValue.ulVal += nOffset;

// 		if (pvMin != NULL)
// 		{
// 			ASSERT (pvMin->vt == VT_UI4);
// 
// 			if (vValue.ulVal < pvMin->ulVal)
// 			{
// 				vValue.ulVal = pvMax->ulVal;
// 			}
// 		}

		if (pvMax != NULL)
		{
			ASSERT (pvMax->vt == VT_UI4);

			if (nOffset > 0)
			{
				if (vValue.ulVal > pvMax->ulVal)
				{
					vValue.ulVal = pvMin->ulVal;
				}
			}
			else//if (nOffset < 0)
			{
				if (vValue.ulVal > pvMax->ulVal)
				{
					vValue.ulVal = pvMax->ulVal;
				}
			}
		}

		break;

	case CFGDATAID_SRCMAC:
	case CFGDATAID_DESTMAC:
		ASSERT (vValue.vt == VT_UI8);
		vValue.ullVal += nOffset;

// 		if (vValue.ullVal >= 0x001000000000000)
// 		{
// 			vValue.ullVal = 0;
// 		}
		if (pvMax != NULL)
		{
			ASSERT (pvMax->vt == VT_UI8);

			if (nOffset > 0)
			{
				if (vValue.ullVal > pvMax->ullVal)
				{
					vValue.ullVal = pvMin->ullVal;
				}
			}
			else//if (nOffset < 0)
			{
				if (vValue.ullVal > pvMax->ullVal)
				{
					vValue.ullVal = pvMax->ullVal;
				}
			}
		}
		break;
	}
}
#endif

CIecCfgDataBase* CIecCfgDatasBase::GetFirstIecCfgDataBase()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;
	CIecCfgDataBase *pFind = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CIecCfgDataBase* CIecCfgDatasBase::GetFirstIecCfgData_Sel()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;
	CIecCfgDataBase *pFind = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p)&&(p->m_nUseFlag))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CIecCfgDatasBase::UpdateFiberIdex2()
{
	POS pos = GetHeadPosition();
	CIecCfgDataBase *p = NULL;
	CIecCfgDataBase *pIecCfgDataBase= NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			pIecCfgDataBase = p;
			pIecCfgDataBase->m_nFiber2Index = pIecCfgDataBase->m_nFiberIndex;
		}
	}
}

#ifdef _PSX_IDE_QT_
void CIecCfgDatasBase::AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue, long nOffset, unsigned long long *pvMin, unsigned long long *pvMax)
{
	CIecCfgDataBase *p = NULL;
	p = GetFirstIecCfgDataBase();

	ASSERT (p != NULL);

	if( p == pCfgData)
	{
		return;
	}

	if (p == NULL)
	{
		return;
	}

	//获取第一个数据并且增加数据,如果数据获取失败，则返回
	if (!p->GetCfgDataValue(nDataID, vValue))
	{
		return;
	}

	iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
	long nCount = GetCfgDataCount();
	long nIndex = 0;

	while (HasCfgDataValue(pCfgData, nDataID, vValue))
	{
		iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
		nIndex++;

		if (nIndex >= nCount)
		{
			if (pvMin != NULL)
			{
//				if ((vValue.vt == VT_I4) && (pvMin->vt == VT_I4))
				{
					vValue = *pvMin;
				}
			}
			break;
		}
	}

	pCfgData->SetCfgDataValue(nDataID, vValue);
}

void CIecCfgDatasBase::AutoSetCfgDataValues(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue, long nOffset, unsigned long long *pvMin, unsigned long long *pvMax)
{
	CIecCfgDataBase *p = NULL;
	p = GetFirstIecCfgDataBase();

	ASSERT (p != NULL);

	if( p == pCfgData)
	{
		return;
	}

	if (p == NULL)
	{
		return;
	}

	//获取第一个数据并且增加数据,如果数据获取失败，则返回
	if (!p->GetCfgDataValue(nDataID, vValue))
	{
		return;
	}

	iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
	long nCount = GetCfgDataCount();
	long nIndex = 0;

	while (HasCfgDataValue(pCfgData, nDataID, vValue))
	{
		iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
		nIndex++;

		if (nIndex >= nCount)
		{
			if (pvMin != NULL)
			{
				//				if ((vValue.vt == VT_I4) && (pvMin->vt == VT_I4))
				{
					vValue = *pvMin;
				}
			}
			break;
		}
	}

	pCfgData->SetCfgDataValues(nDataID, vValue);
}


BOOL CIecCfgDatasBase::HasCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue)
{
	CIecCfgDataBase *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (p == pCfgData)
		{
			break;
		}

		if ( IsCfgData(p) )//&& (p != pCfgData) )
		{
			if (p->IsEqualCfgDataValue(nDataID, vValue))
			{
				bFind = TRUE;
				break;
			}
		}

	}

	return bFind;
}

BOOL CIecCfgDatasBase::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	CIecCfgDataBase *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (IsCfgData(p))
		{
			p->SetCfgDataValue(nDataID, vValue);
		}
	}

	return bFind;
}
#else
void CIecCfgDatasBase::AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, VARIANT &vValue, long nOffset, VARIANT *pvMin, VARIANT *pvMax)
{
	CIecCfgDataBase *p = NULL;
	p = GetFirstIecCfgDataBase();;

	ASSERT (p != NULL);

	if( p == pCfgData)
	{
		return;
	}

	if (p == NULL)
	{
		return;
	}

	//获取第一个数据并且增加数据,如果数据获取失败，则返回
	if (!p->GetCfgDataValue(nDataID, vValue))
	{
		return;
	}

	iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
	long nCount = GetCfgDataCount();
	long nIndex = 0;

	while (HasCfgDataValue(pCfgData, nDataID, vValue))
	{
		iecfg_IncreaseCfgData(nDataID, vValue, nOffset, pvMin, pvMax);
		nIndex++;

		if (nIndex >= nCount)
		{
			if (pvMin != NULL)
			{
				if ((vValue.vt == VT_I4) && (pvMin->vt == VT_I4))
				{
					vValue.lVal = pvMin->lVal;
				}
			}
			break;
		}
	}

	pCfgData->SetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfgDatasBase::HasCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, VARIANT &vValue)
{
	CIecCfgDataBase *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CIecCfgDataBase *)GetNext(pos);

		if (p == pCfgData)
		{
			break;
		}

		if ( IsCfgData(p) )//&& (p != pCfgData) )
		{
			if (p->IsEqualCfgDataValue(nDataID, vValue))
			{
				bFind = TRUE;
				break;
			}
		}

	}

	return bFind;
}

 BOOL CIecCfgDatasBase::SetCfgDataValue(long nDataID, VARIANT &vValue)
 {
	 CIecCfgDataBase *p = NULL;
	 POS pos = GetHeadPosition();
	 BOOL bFind = FALSE;

	 while (pos != NULL)
	 {
		 p = (CIecCfgDataBase *)GetNext(pos);
		 
		 if (IsCfgData(p))
		 {
			 p->SetCfgDataValue(nDataID, vValue);
		 }
	 }

	 return bFind;
 }

 //2021-6-21  lijunqing
 CIecCfgDataBase* CIecCfgDatasBase::FindCfgData(long nDataID, VARIANT &vValue)
 {
	 long nCount = GetCfgDataCount();
	 long nIndex = 0;
	 CIecCfgDataBase *p = NULL;
	 CIecCfgDataBase *pFind = NULL;

	 for (nIndex=0; nIndex<nCount; nIndex++)
	 {
		 p = GetIecCfgData(nIndex);

		 if (p->IsEqualCfgDataValue(nDataID, vValue))
		 {
			 pFind = p;
			 break;
		 }
	 }

	 return pFind;
 }

#endif

 long CIecCfgDatasBase::GetUseDatasCount()
 {
	 CExBaseList oList;

	GetUseDatas(oList);
	long nUseCount = oList.GetCount();
	oList.RemoveAll();

	return nUseCount;
 }

 long CIecCfgDatasBase::GetUseDatasCount(UINT nClassID)
 {
	 POS pos = GetHeadPosition();
	 CExBaseObject *pCurrObj = NULL;
	 CIecCfgDataBase *p = NULL;
	 long nCount = 0;

	 while (pos != NULL)
	 {
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != nClassID)
		{
			continue;
		}

		 p = (CIecCfgDataBase *)pCurrObj;

		 if (p->m_nUseFlag)
		 {
			 nCount++;
		 }
	 }

	 return nCount;
 }

 long CIecCfgDatasBase::GetUseDatas(CExBaseList &oListDatas)
 {
	 CExBaseList oList;
	 GetIecCfgDatas(oList);
	 POS pos = oList.GetHeadPosition();
	 CIecCfgDataBase *pData = NULL;

	 while (pos != NULL)
	 {
		 pData = (CIecCfgDataBase *)oList.GetNext(pos);

		 if (pData->m_nUseFlag > 0)
		 {
			 oListDatas.AddTail(pData);
		 }
	 }

	 oList.RemoveAll();

	 return oListDatas.GetCount();
 }

#ifdef _USE_IN_AT02D_MODE_
 BOOL CIecCfgDatasBase::HasCfgDataset_AT02D_Model(CDvmLogicDevice *pLDevice,const CString &strAppID)//周宏军 20200616  增加AT02配置
 {
	 POS pos = pLDevice->GetHeadPosition();
	 CDvmDataset *pCurDataset = NULL;
	 CExBaseObject *pCurObj = NULL;

	 while(pos)
	 {
		 pCurObj = pLDevice->GetNext(pos);

		 if (pCurObj->GetClassID() == DVMCLASSID_CDVMDATASET)
		 {
			 pCurDataset = (CDvmDataset *)pCurObj;

			 if (pCurDataset->m_strName.Find(strAppID)>=0)
			 {
				 return TRUE;
			 }
		 }
	 }

	 return FALSE;
 }
#endif
long CIecCfgDatasBase::GetDatasCount(UINT nClassID)
 {
	 POS pos = GetHeadPosition();
	 CExBaseObject *pCurrObj = NULL;
	 CIecCfgDataBase *p = NULL;
	 long nCount = 0;

	 while (pos != NULL)
	 {
		 pCurrObj = GetNext(pos);

		 if (pCurrObj->GetClassID() != nClassID)
		 {
			 continue;
		 }

		 p = (CIecCfgDataBase *)pCurrObj;

	     nCount++;
	 }

	 return nCount;
 }