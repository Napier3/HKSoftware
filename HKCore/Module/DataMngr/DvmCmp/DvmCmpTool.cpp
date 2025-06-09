//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmCmpTool.cpp  CDvmCmpTool


#include "stdafx.h"
#include "DvmCmpTool.h"
#include "..\..\API\FileApi.h"
#include "..\..\XLanguage\XLanguageResource.h"
#define COL_CMPTYPE 2
#define COL_STAND   3
#define COL_DEST    4

CDvmCmpResult::CDvmCmpResult(CString *pStand, CString *pDestCmp)
{
	m_pStand   = pStand;
	m_pDestCmp = pDestCmp;
	m_bCmpErr  = FALSE;

	Cmp();
}

CDvmCmpResult::~CDvmCmpResult()
{
	
}

void CDvmCmpResult::Cmp()
{
	m_bCmpErr = (*m_pDestCmp != *m_pStand);
}

BOOL CDvmCmpResult::IsCmpError()
{
	return m_bCmpErr;
}

CDvmCmpObj::CDvmCmpObj(CExBaseObject *pStand, CExBaseObject *pDestCmp)
{
	m_pStringCmp_Name = NULL;
	m_pStringCmp_ID   = NULL;
	m_pStand = pStand;
	m_pDestCmp = pDestCmp;
	m_nChildCmp = 0;
	m_bDataTypeCmpErr = FALSE;
	m_bMinCmpErr = FALSE;
	m_bMaxCmpErr = FALSE;
	m_bStepCmpErr = FALSE;
	m_bNameCmpErr = FALSE;
	m_bIDCmpErr = FALSE;

	m_hStand   = NULL;
	m_hDestCmp = NULL;
	m_nDestIndex = -1;
	m_nStandIndex = -1;

	CmpEx();
}

void CDvmCmpObj::CmpEx()
{
	m_bDataTypeCmpErr   = FALSE;
	m_bMinCmpErr = FALSE;
	m_bMaxCmpErr = FALSE;
	m_bStepCmpErr = FALSE;

	m_nCmpRate = 0;
	m_nChildCmp = 0;
	m_nCmpResult = 0;

	if (m_pStand != NULL && m_pDestCmp != NULL)
	{
		Cmp();
	}
}

CDvmCmpObj::~CDvmCmpObj()
{
	if (m_pStringCmp_Name != NULL)
	{
		delete m_pStringCmp_Name;
		m_pStringCmp_Name = NULL;
	}

	if (m_pStringCmp_ID != NULL)
	{
		delete m_pStringCmp_ID;
		m_pStringCmp_ID = NULL;
	}
}

void CDvmCmpObj::Cmp()
{
	if (CDvmCmpToolConfig::GetCmpWithID()==1)  //仅比较ID
	{
		m_bIDCmpErr = m_pStand->m_strID != m_pDestCmp->m_strID;
	}
	else 
	{
		m_bIDCmpErr = m_pStand->m_strID != m_pDestCmp->m_strID;

		if (CDvmCmpToolConfig::GetDvmCmdDataNameFull()==1)
		{
			m_bNameCmpErr = m_pStand->m_strName != m_pDestCmp->m_strName;
		}
		else
		{
			if(m_pStand->m_strName.GetLength()>0 && m_pDestCmp->m_strName.GetLength()==0 || 
			   m_pStand->m_strName.GetLength()==0 && m_pDestCmp->m_strName.GetLength()>0)
			{
				m_bNameCmpErr = 1;
			}
			else if (m_pStand->m_strName.GetLength()==0 && m_pDestCmp->m_strName.GetLength()==0)
			{
				m_bNameCmpErr = 0;
			}
			else if(m_pStand->m_strName.Find(m_pDestCmp->m_strName)<0 && m_pDestCmp->m_strName.Find(m_pStand->m_strName)<0)
			{
				m_bNameCmpErr = 1;
			}
		}
	}

	m_nCmpResult = 0;

	if (IsNameCmpError())
	{
		m_nCmpResult++;
	}

	if (IsIdCmpError())
	{
		m_nCmpResult++;
	}

	if (m_pStand->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		m_bDataTypeCmpErr = FALSE;
		m_bMaxCmpErr = FALSE;
		m_bMinCmpErr = FALSE;
		m_bStepCmpErr = FALSE;

		if ( ((CDvmData *)m_pStand)->m_strDataType !=  ((CDvmData *)m_pDestCmp)->m_strDataType )
		{
			m_bDataTypeCmpErr = TRUE;
			m_nCmpResult++;
		}
		else
		{
			m_bDataTypeCmpErr = FALSE;
		}
		
		//if ( ((CDvmData *)m_pStand)->m_strMax !=  ((CDvmData *)m_pDestCmp)->m_strMax )
		if (((CDvmData *)m_pStand)->m_strMax.GetLength() > 0)
		{
			if ( CString_To_double(((CDvmData *)m_pStand)->m_strMax) >  CString_To_double(((CDvmData *)m_pDestCmp)->m_strMax) )
			{
				m_bMaxCmpErr = TRUE;
				m_nCmpResult++;
			}
			else
			{
				m_bMaxCmpErr = FALSE;
			}
		}

		if (((CDvmData *)m_pStand)->m_strMin.GetLength() > 0)
		{
			//if ( ((CDvmData *)m_pStand)->m_strMin !=  ((CDvmData *)m_pDestCmp)->m_strMin )
			if ( CString_To_double(((CDvmData *)m_pStand)->m_strMin) <  CString_To_double(((CDvmData *)m_pDestCmp)->m_strMin) )
			{
				m_bMinCmpErr = TRUE;
				m_nCmpResult++;
			}
			else
			{
				m_bMinCmpErr = FALSE;
			}
		}

		if (((CDvmData *)m_pStand)->m_strStep.GetLength() > 0)
		{
			if ( CString_To_double(((CDvmData *)m_pStand)->m_strStep) <  CString_To_double(((CDvmData *)m_pDestCmp)->m_strStep) )
			{
				m_bStepCmpErr = TRUE;
				m_nCmpResult++;
			}
			else
			{
				m_bStepCmpErr = FALSE;
			}
		}

	}
	else if (m_pStand->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		if ( ((CDvmValue*)m_pStand)->m_strDataType !=  ((CDvmValue*)m_pDestCmp)->m_strDataType )
		{
			m_bDataTypeCmpErr = TRUE;
			m_nCmpResult++;
		}
		else
		{
			m_bDataTypeCmpErr = FALSE;
		}
	}
}

BOOL CDvmCmpObj::IsDvmLdeviceCmpObj()
{
	if (m_pStand != NULL)
	{
		return (m_pStand->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE);
	}

	if (m_pDestCmp != NULL)
	{
		return (m_pDestCmp->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE);
	}

	return FALSE;
}

BOOL CDvmCmpObj::IsDvmDatasetCmpObj()
{
	if (m_pStand != NULL)
	{
		return (m_pStand->GetClassID() == DVMCLASSID_CDVMDATASET);
	}

	if (m_pDestCmp != NULL)
	{
		return (m_pDestCmp->GetClassID() == DVMCLASSID_CDVMDATASET);
	}

	return FALSE;
}

CString CDvmCmpObj::GetDvmCmpID()
{
	if (m_pStand != NULL)
	{
		return m_pStand->m_strID;
	}

	if (m_pDestCmp != NULL)
	{
		return m_pDestCmp->m_strID;
	}

	ASSERT (FALSE);

	return _T("Error");
}

BOOL CDvmCmpObj::IsNameCmpError()
{
	return m_bNameCmpErr;
}

BOOL CDvmCmpObj::IsIdCmpError()
{
	return m_bIDCmpErr;
}

BOOL CDvmCmpObj::IsDataTypeCmpError()
{
	return m_bDataTypeCmpErr;
}

BOOL CDvmCmpObj::IsMinCmpError()
{
	return m_bMinCmpErr;
}

BOOL CDvmCmpObj::IsMaxCmpError()
{
	return m_bMaxCmpErr;
}

BOOL CDvmCmpObj::IsStepCmpError()
{
	return m_bStepCmpErr;
}

BOOL CDvmCmpObj::IsCmpError()
{
	if (IsCmpError_Own())
	{
		return TRUE;
	}

	if (IsCmpError_Child())
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CDvmCmpObj::IsCmpError_Own()
{
	if ( IsNameCmpError())
	{
		return TRUE;
	}

	if ( IsIdCmpError())
	{
		return TRUE;
	}

	if ( IsDataTypeCmpError())
	{
		return TRUE;
	}
/*
	if ( IsMinCmpError())
	{
		return TRUE;
	}

	if ( IsMaxCmpError())
	{
		return TRUE;
	}
*/
	return FALSE;
}

BOOL CDvmCmpObj::IsCmpError_Child()
{
	if (m_nCmpResult > 0)
	{
		return TRUE;
	}

	if (m_nChildCmp > 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CDvmCmpObj::StringCmp()
{
	if (m_pStand == NULL || m_pDestCmp == NULL)
	{
		return;
	}

	if (m_pStringCmp_ID != NULL)
	{
		return;
	}

	if ((m_pStand->m_strName.GetLength() > 0) && (m_pDestCmp->m_strName.GetLength() > 0) )
	{
		m_pStringCmp_Name = new CStringCmp;
		m_pStringCmp_Name->StrCmp(&m_pStand->m_strName, &m_pDestCmp->m_strName);
	}

	if (m_pStand->m_strID.GetLength() > 0 && m_pDestCmp->m_strID.GetLength() > 0)
	{
		m_pStringCmp_ID = new CStringCmp;
		m_pStringCmp_ID->StrCmp(&m_pStand->m_strID, &m_pDestCmp->m_strID);
	}
}

void CDvmCmpObj::FreeStringCmp()
{
	if (m_pStringCmp_Name != NULL)
	{
		delete m_pStringCmp_Name;
		m_pStringCmp_Name = NULL;
	}

	if (m_pStringCmp_ID != NULL)
	{
		delete m_pStringCmp_ID;
		m_pStringCmp_ID = NULL;
	}
}

CStringCmpBlocks* CDvmCmpObj::GetNameCmp_Stand()
{
	if (m_pStringCmp_Name == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_Name->m_oStrCmpBlks1;
}

CStringCmpBlocks* CDvmCmpObj::GetNameCmp_Dest()
{
	if (m_pStringCmp_Name == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_Name->m_oStrCmpBlks2;
}

CStringCmpBlocks* CDvmCmpObj::GetIDCmp_Stand()
{
	if (m_pStringCmp_ID == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_ID->m_oStrCmpBlks1;
}

CStringCmpBlocks* CDvmCmpObj::GetIDCmp_Dest()
{
	if (m_pStringCmp_ID == NULL)
	{
		return NULL;
	}

	return &m_pStringCmp_ID->m_oStrCmpBlks2;
}



BOOL CDvmCmpObj::IsInChild_Stand(CExBaseObject *pStand)
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)GetNext(pos);

		if (p->m_pStand == pStand)
		{
			return TRUE;
		}
	}

	return FALSE;
}

CDvmCmpObj* CDvmCmpObj::SetStand(CExBaseObject *pStand)
{
	if (m_pStand == pStand)
	{
		return NULL;
	}

	if (m_pStand != NULL)
	{
#ifdef exbase_not_use_m_dwReserved
		m_pStand->m_dwItemData = 0;
#else
		m_pStand->m_dwReserved = 0;
#endif
	}

	m_pStand = pStand;
#ifdef exbase_not_use_m_dwReserved
	m_pStand->m_dwItemData = 1;
#else
	m_pStand->m_dwReserved = 1;
#endif

	CmpEx();

	return RemoveParentStand(pStand);
}

CDvmCmpObj* CDvmCmpObj::SetDest(CExBaseObject *pDest)
{
	if (pDest == NULL)
	{

	}
	if (m_pDestCmp == pDest)
	{
		return NULL;
	}

	if (m_pDestCmp != NULL)
	{
#ifdef exbase_not_use_m_dwReserved
		m_pDestCmp->m_dwItemData = 0;
#else
		m_pDestCmp->m_dwReserved = 0;
#endif
	}

	m_pDestCmp = pDest;
#ifdef exbase_not_use_m_dwReserved
	m_pDestCmp->m_dwItemData = 1;
#else
	m_pDestCmp->m_dwReserved = 1;
#endif

	CmpEx();

	return RemoveParentDest(pDest);
}

CDvmCmpObj* CDvmCmpObj::RemoveParentStand(CExBaseObject *pStand)
{
	CDvmCmpObj *pParent = (CDvmCmpObj*)GetParent();
	POS pos = pParent->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	CDvmCmpObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)pParent->GetNext(pos);

		if (p == this)
		{
			continue;
		}

		if (p->m_pStand == pStand)
		{
			p->m_pStand = NULL;
			p->RemoveChildStand();
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmCmpObj* CDvmCmpObj::RemoveParentDest(CExBaseObject *pDest)
{
	CDvmCmpObj *pParent = (CDvmCmpObj*)GetParent();
	POS pos = pParent->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	CDvmCmpObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)pParent->GetNext(pos);

		if (p == this)
		{
			continue;
		}

		if (p->m_pDestCmp == pDest)
		{
			p->RemoveChildDest();
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CDvmCmpObj::RemoveChildDest()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *p = NULL;

	if (m_pDestCmp != NULL)
	{
#ifdef exbase_not_use_m_dwReserved
		m_pDestCmp->m_dwItemData = 0x0FFFFFFF;
#else
		m_pDestCmp->m_dwReserved = 0x0FFFFFFF;
#endif
	}

	if (m_pStand != NULL)
	{
#ifdef exbase_not_use_m_dwReserved
		m_pStand->m_dwItemData = 0x0FFFFFFF;
#else
		m_pStand->m_dwReserved = 0x0FFFFFFF;
#endif
	}

	m_pDestCmp = NULL;
	m_nCmpResult = 1;
	FreeStringCmp();

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)GetNext(pos);
		p->RemoveChildDest();
	}
}

void CDvmCmpObj::RemoveChildStand()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *p = NULL;
	m_pStand = NULL;
	m_nCmpResult = 1;

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)GetNext(pos);
		p->RemoveChildStand();
	}

	FreeStringCmp();
}

void CDvmCmpObj::GetCmpErrorNum(long &nCmpErrs)
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *p = NULL;
	while (pos != NULL)
	{
		p = (CDvmCmpObj *)GetNext(pos);
		nCmpErrs += p->m_nCmpResult;
		p->GetCmpErrorNum(nCmpErrs);
	}
}

CDvmCmpTool::CDvmCmpTool()
{
	m_pLdeviceDataType = NULL;
	m_pDatasetDataType = NULL;
	m_pDvmCmpValueKeyDataType = NULL;
	m_pDvmCmpFullNameIdKeyType = NULL;

	m_hStand   = NULL;
	m_hDestCmp = NULL;

	m_pStand   = NULL;
	m_pDestCmp = NULL;

	m_WordApp = NULL;
	m_doc     = NULL;

	m_dwCmpState = CMP_STATE_NONE;
	m_bKeyDbRef = FALSE;
}

CDvmCmpTool::~CDvmCmpTool()
{
	if (!m_bKeyDbRef)
	{
		delete m_pKeyDB;
		m_pKeyDB = NULL;
	}
}

void CDvmCmpTool::AttachKeyDB(CXKeyDB *pKeyDB)
{
	m_bKeyDbRef = TRUE;
	m_pKeyDB = pKeyDB;
}

void CDvmCmpTool::CmpDvmDevice(CDvmDevice *pStand, CDvmDevice *pDestCmp)
{
	OpenKeyDbFile();
	DeleteAll();

	m_pStand   = pStand;
	m_pDestCmp = pDestCmp;

	POS pos = pDestCmp->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;

	//遍历pDestCmp中的每一个Ldevice，与pStand比较
	while (pos != NULL)
	{
		pLdevice = (CDvmLogicDevice *)pDestCmp->GetNext(pos);
		CmpDvmLdevice(pStand, pLdevice);
	}

	//处理没有定义的Ldevcie
	AddOtherCmpObj_Stand(pStand, this);

	//打开映射关系文件，根据映射关系更新比较
	OpenDvmCmpMapFile();
	InitByDvmMap();
	AddOtherCmpObj_Stand();
	SortByStand();
}

void CDvmCmpTool::CmpDvmDevice_DsMap(CDvmDevice *pStand, CDvmDevice *pDestCmp)
{
	m_dwCmpState = CMP_STATE_DATASET;

	OpenKeyDbFile();
	DeleteAll();

	m_pStand   = pStand;
	m_pDestCmp = pDestCmp;

	POS pos = pDestCmp->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;

	//遍历pDestCmp中的每一个Ldevice，与pStand比较
	while (pos != NULL)
	{
		pLdevice = (CDvmLogicDevice *)pDestCmp->GetNext(pos);
		CmpDvmLdevice(pStand, pLdevice);
	}


}
void CDvmCmpTool::CmpDvmDevice_DsDataMap()
{
	m_dwCmpState = CMP_STATE_DATA;

	//处理没有定义的Ldevcie
	AddOtherCmpObj_Stand(m_pStand, this);

	//打开映射关系文件，根据映射关系更新比较
	OpenDvmCmpMapFile();
	InitByDvmMap();
	AddOtherCmpObj_Stand();
	SortByStand();

	m_dwCmpState = CMP_STATE_NONE;
}

void CDvmCmpTool::SortByStand()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *pLdCmp = NULL;
	POS posDsCmp = NULL;
	CDvmCmpObj *pDsCmp;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		//遍历ldevice的比较对象
		pLdCmp = (CDvmCmpObj *)GetNext(pos);

		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pDestCmp == NULL)
		{
			continue;
		}

		//遍历逻辑设备比较对象
		posDsCmp = pLdCmp->GetHeadPosition();

		while (posDsCmp != NULL)
		{
			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);

			if (pDsCmp->m_pStand == NULL)
			{
				continue;
			}

			SortByStand(pDsCmp, (CDvmDataset*)pDsCmp->m_pStand, (CDvmDataset*)pDsCmp->m_pDestCmp);
		}
	}
}

void CDvmCmpTool::SaveDvmCmpMapFile()
{
	CString strFile;
	strFile = m_pDestCmp->m_strID;
	strFile = ChangeFilePostfix(strFile, g_strDvmDataMapFilePostfix);

	m_oDvmDeviceMap.DeleteAll();
	CreateDvmMap();
	m_oDvmDeviceMap.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CDvmCmpTool::OpenDvmCmpMapFile()
{
	CString strFile;
	strFile = m_pDestCmp->m_strID;
	strFile = ChangeFilePostfix(strFile, g_strDvmDataMapFilePostfix);

	m_oDvmDeviceMap.DeleteAll();
	m_oDvmDeviceMap.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CDvmCmpTool::OpenDvmCmpValueKeyDataTypeFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("DvmCmpValueKeyDataType.xml");
	
	m_oDvmCmpValueKeyDataType.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CDvmCmpTool::OpenDvmCmpRptExportFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("DvmMapReportConfig.xml");

	m_oRptDstaset.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CDvmLogicDevice* CDvmCmpTool::FindCmpDvmLdevice(CDvmDevice *pStand, CDvmLogicDevice *pDestCmpLdevice)
{
	POS pos = pStand->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;
	CDvmCmpObj *pCmpObj = NULL;

	//先比较编号
	long nLdIndex = dvm_GetLdIndex(pDestCmpLdevice->m_strID);

	if (nLdIndex >= 0)
	{
		pLdevice = dvm_FindByLdIndex(pStand, nLdIndex);

		return pLdevice;
	}

	//if (pLdevice == NULL)
	{
		while (pos != NULL)
		{
			//遍历pStand的每一个Ldevice，判断是否可以与pDestCmpLdevice进行比较
			pLdevice = (CDvmLogicDevice *)pStand->GetNext(pos);
			nCmpRate = CanCmpDvmLdevice(pLdevice, pDestCmpLdevice);

			if (nCmpRate > 0)
			{
				CDvmCmpObj *pNew = new CDvmCmpObj(pLdevice, pDestCmpLdevice);
				pNew->m_nCmpRate = nCmpRate;
				listCmp.AddTail(pNew);
			}
		}

		//获取相似程度最高的
		pCmpObj = GetCmpMatchObject(listCmp);

		if (pCmpObj == NULL)
		{
			return NULL;
		}
		else
		{
			return (CDvmLogicDevice*)pCmpObj->m_pStand;
		}
	}
// 	else
// 	{
// 		return pLdevice;
// 	}

}


long CDvmCmpTool::CanCmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpLdevice);

	if (nCmp > 0)
	{
		return nCmp;
	}

	//比较逻辑设备的关键字
	long nKeyStand = GetLdeviceKey(pStand->m_strID);
	long nKeyDestCmp = GetLdeviceKey(pDestCmpLdevice->m_strID);

	if ((nKeyDestCmp == nKeyStand) && (nKeyStand != -1))
	{
		return 50;
	}
	else
	{
		return 0;
	}
}

CDvmCmpObj* CDvmCmpTool::CmpDvmLdevice(CDvmDevice *pStand, CDvmLogicDevice *pDestCmpLdevice)
{
	POS pos = pStand->GetHeadPosition();
	CDvmLogicDevice *pLdevice = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;

	//在pStand中找与pDestCmpLdevice相匹配的pLdevice
	pLdevice = FindCmpDvmLdevice(pStand, pDestCmpLdevice);

	if (pLdevice == NULL)
	{
		pDvmCmpObj = new CDvmCmpObj(NULL, pDestCmpLdevice);
		pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_DestCmp(pDestCmpLdevice, pDvmCmpObj);
		AddNewChild(pDvmCmpObj);
	}
	else
	{
		pDvmCmpObj = CmpDvmLdevice(pLdevice, pDestCmpLdevice);
		ASSERT( pDvmCmpObj != NULL);
		AddNewChild(pDvmCmpObj);
	}

	return pDvmCmpObj;
}


CDvmCmpObj* CDvmCmpTool::CmpDvmLdevice(CDvmLogicDevice *pStand, CDvmLogicDevice *pDestCmpLdevice)
{
	CDvmCmpObj *pDvmCmpObj = new CDvmCmpObj(pStand, pDestCmpLdevice);
	CDvmCmpObj *p = NULL;
	
	//比较数据集
	POS pos = pDestCmpLdevice->GetHeadPosition();
	CDvmDataset *pDvmDataset = NULL;

	while (pos!= NULL)
	{
		pDvmDataset = (CDvmDataset *)pDestCmpLdevice->GetNext(pos);
		p = CmpDvmDataset(pStand, pDvmDataset, pDvmCmpObj);

		if (p != NULL)
		{
			pDvmCmpObj->m_nChildCmp += p->IsCmpError();
		}
	}

	//添加没有匹配成功的dataset
	pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_Stand(pStand, pDvmCmpObj);

	return pDvmCmpObj;
}

//////////////////////////////////////////////////////////////////////////

CDvmDataset* CDvmCmpTool::FindCmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset)
{
	POS pos = pStand->GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;

	while (pos != NULL)
	{
		//遍历pStand的每一个Dataset，判断是否可以与pDestCmpDataset进行比较
		pDataset = (CDvmDataset *)pStand->GetNext(pos);
		nCmpRate = CanCmpDvmDataset(pDataset, pDestCmpDataset);

		if (nCmpRate > 0)
		{
			CDvmCmpObj *pNew = new CDvmCmpObj(pDataset, pDestCmpDataset);
			pNew->m_nCmpRate = nCmpRate;
			listCmp.AddTail(pNew);
		}
	}

	//获取相似程度最高的
	CDvmCmpObj *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmDataset*)pCmpObj->m_pStand;
	}
}

long CDvmCmpTool::CanCmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpDataset);

	if (nCmp > 0)
	{
		return nCmp;
	}

	//比较数据集的关键字
	long nKeyStand = GetDatasetKey(pStand->m_strID);
	long nKeyDestCmp = GetDatasetKey(pDestCmpDataset->m_strID);

	if ((nKeyDestCmp == nKeyStand) && (nKeyStand != -1))
	{
		return 50;
	}
	else
	{
		return 0;
	}
}

CDvmCmpObj* CDvmCmpTool::CmpDvmDataset(CDvmLogicDevice *pStand, CDvmDataset *pDestCmpDataset, CDvmCmpObj *pParent)
{
	POS pos = pStand->GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;

	//在pStand中查找可以与pDestCmpDataset比较的dataset
	pDataset = FindCmpDvmDataset(pStand, pDestCmpDataset);

	//无可以比较的dataset
	if (pDataset == NULL)
	{
		pDvmCmpObj = new CDvmCmpObj(NULL, pDestCmpDataset);
		pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_DestCmp(pDestCmpDataset, pDvmCmpObj);
		pParent->AddNewChild(pDvmCmpObj);
	}
	else
	{
		//比较dataset
		pDvmCmpObj = CmpDvmDataset(pDataset, pDestCmpDataset);
		ASSERT( pDvmCmpObj != NULL);

		if (pDvmCmpObj != NULL)
		{
			pParent->AddNewChild(pDvmCmpObj);
		}
	}

	return pDvmCmpObj;
}


CDvmCmpObj* CDvmCmpTool::CmpDvmDataset(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset)
{
	CDvmCmpObj *pDvmCmpObj = NULL;
	
	//比较名称
	pDvmCmpObj = CmpDvmDataset_Name(pStand, pDestCmpDataset);

	if (CDvmCmpToolConfig::GetCmpWithID() == 0)
	{
		//XMatch
		XMatchDataset(pStand, pDestCmpDataset);

		//比较数据集的数据
		POS pos = pDestCmpDataset->GetHeadPosition();
		CDvmData *pDvmData = NULL;
		CDvmCmpObj *p = NULL;

		while (pos!= NULL)
		{
			pDvmData = (CDvmData *)pDestCmpDataset->GetNext(pos);

#ifdef exbase_not_use_m_dwReserved
			if (pDvmData->m_dwItemData == 1)
#else
			if (pDvmData->m_dwReserved == 1)
#endif
			{
				continue;
			}

			p = CmpDvmData(pStand, pDvmData, pDvmCmpObj);

			if (p != NULL)
			{
				pDvmCmpObj->m_nChildCmp += p->IsCmpError();
			}
		}
	}


	//比较id
	CmpDvmDataset_ID(pStand, pDestCmpDataset, pDvmCmpObj);

	//pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_Stand(pStand, pDvmCmpObj);

	//按照标准进行排序
	//SortByStand(pDvmCmpObj, pStand, pDestCmpDataset);

	return pDvmCmpObj;
}

void CDvmCmpTool::SortByStand(CDvmCmpObj *pDvmCmpDataset, CDvmDataset *pDsStand, CDvmDataset *pDsDest)
{
	POS pos = pDsStand->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpObj *pDataCmp = NULL;
	CExBaseList listTemp;
	long nIndex = 0;

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pDsStand->GetNext(pos);
		pDataCmp = FindByStand(pDvmCmpDataset, pDvmData);

		if (pDataCmp != NULL)
		{
			pDataCmp->m_nStandIndex = nIndex;
			listTemp.AddTail(pDataCmp);
			nIndex++;
		}
	}

	listTemp.Append(pDvmCmpDataset);
	pDvmCmpDataset->RemoveAll();
	pDvmCmpDataset->Append(listTemp);
	listTemp.RemoveAll();

	pos = pDvmCmpDataset->GetHeadPosition();

	while (pos != NULL)
	{
		pDataCmp = (CDvmCmpObj *)pDvmCmpDataset->GetNext(pos);

		if (pDataCmp->m_pDestCmp != NULL)
		{
			pDataCmp->m_nDestIndex = pDsDest->FindIndex(pDataCmp->m_pDestCmp);
		}
	}
}

CDvmCmpObj* CDvmCmpTool::FindByStand(CDvmCmpObj *pDvmCmpDataset, CDvmData *pDvmData)
{
	CDvmCmpObj *p = NULL;
	CDvmCmpObj *pFind = NULL;
	POS pos = pDvmCmpDataset->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)pDvmCmpDataset->GetNext(pos);

		if (p->m_pStand == pDvmData)
		{
			pFind = p;
			break;
		}
	}

	pDvmCmpDataset->Remove(pFind);

	return pFind;
}


CDvmData* CDvmCmpTool::FindDvmData_Name(CDvmDataset *pDataset, const CString &strName, long nStandIdKey, BOOL bFullCmp)
{
	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	CExBaseObject *pFirstFind = NULL;
	long nDestKey = -1;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->m_strName == strName)
		{
#ifdef exbase_not_use_m_dwReserved
			if (p->m_dwItemData != 1)
#else
			if (p->m_dwReserved != 1)
#endif
			{
				if (CDvmCmpToolConfig::GetDvmCmdDataNameFull() == 1)
				{
					if (pFirstFind == NULL)
					{
						pFirstFind = p;
					}

					nDestKey = GetCmpFullNameIdKey(p->m_strID);

					if (nDestKey == nStandIdKey)
					{
						pFind = p;
						break;
					}
				}
				else
				{
					pFind = p;
					break;
				}

			}
		}
	}

	if (pFind == NULL && (!bFullCmp))
	{
		pFind = pFirstFind;
	}

	return (CDvmData*)pFind;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmDataset_Name(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset)
{
	CDvmCmpObj *pDvmCmpObj = new CDvmCmpObj(pStand, pDestCmpDataset);

	if (CDvmCmpToolConfig::GetCmpWithID() == 0)
	{
		//比较数据集的数据
		POS pos = pDestCmpDataset->GetHeadPosition();
		CDvmData *pDvmData = NULL;
		CDvmData *pFind = NULL;
		CDvmCmpObj *p = NULL;
		long nStandIdKey = -1;

		while (pos!= NULL)
		{
			pDvmData = (CDvmData *)pDestCmpDataset->GetNext(pos);
			nStandIdKey = GetCmpFullNameIdKey(pDvmData->m_strID);
			//pFind = (CDvmData *)pStand->FindByName(pDvmData->m_strName);
			pFind = FindDvmData_Name(pStand, pDvmData->m_strName, nStandIdKey, TRUE);

			if (pFind != NULL)
			{
				p = CmpDvmData(pFind, pDvmData);
				pDvmCmpObj->AddNewChild(p);
#ifdef exbase_not_use_m_dwReserved
				pFind->m_dwItemData = 1;
				pDvmData->m_dwItemData = 1;
#else
				pFind->m_dwReserved = 1;
				pDvmData->m_dwReserved = 1;
#endif
				pDvmCmpObj->m_nChildCmp += p->IsCmpError();
			}
		}
	}

	return pDvmCmpObj;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmDataset_ID(CDvmDataset *pStand, CDvmDataset *pDestCmpDataset, CDvmCmpObj *pDsCmpObj)
{
	//比较数据集的数据
	POS pos = pDestCmpDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmData *pFind = NULL;
	CDvmCmpObj *p = NULL;

	while (pos!= NULL)
	{
		pDvmData = (CDvmData *)pDestCmpDataset->GetNext(pos);

#ifdef exbase_not_use_m_dwReserved
		if (pDvmData->m_dwItemData == 1)
#else
		if (pDvmData->m_dwReserved == 1)
#endif
		{
			continue;
		}

		pFind = (CDvmData *)pStand->FindByID(pDvmData->m_strID);

		if (pFind != NULL)
		{
#ifdef exbase_not_use_m_dwReserved
			if (pFind->m_dwItemData == 1)
#else
			if (pFind->m_dwReserved == 1)
#endif
			{
				continue;
			}

			p = CmpDvmData(pFind, pDvmData);
			pDsCmpObj->AddNewChild(p);
#ifdef exbase_not_use_m_dwReserved
			pFind->m_dwItemData = 1;
			pDvmData->m_dwItemData = 1;
#else
			pFind->m_dwReserved = 1;
			pDvmData->m_dwReserved = 1;
#endif
			pDsCmpObj->m_nChildCmp += p->IsCmpError();
		}
	}

	return pDsCmpObj;
}

//////////////////////////////////////////////////////////////////////////
CDvmData* CDvmCmpTool::FindCmpDvmData(CDvmDataset *pStand, CDvmData *pDestCmpData, CDvmCmpObj *pParent)
{
	POS pos = pStand->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;

	if (CDvmCmpToolConfig::GetCmpWithID() == 1)
	{
		while (pos != NULL)
		{
			//遍历pStand的每一个Data，判断是否可以与pDestCmpData进行比较
			pData = (CDvmData *)pStand->GetNext(pos);

#ifdef exbase_not_use_m_dwReserved
			if (pData->m_dwItemData == 1)
#else
			if (pData->m_dwReserved == 1)
#endif
			{
				continue;
			}

			if (pParent->IsInChild_Stand(pData))
			{
				continue;
			}

			nCmpRate = CanCmpDvmObject_ID(pData, pDestCmpData);

			if (nCmpRate > 0)
			{
				CDvmCmpObj *pNew = new CDvmCmpObj(pData, pDestCmpData);
				pNew->m_nCmpRate = nCmpRate;
				listCmp.AddTail(pNew);
			}
		}
	}
	//XMastch获取
	//if (listCmp.GetCount() == 0)
	else //CDvmCmpToolConfig::GetCmpWithID() == 0
	{
		CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
		POS pos = pList->GetHeadPosition();
		CXMatchObject *pXMatch = NULL;
		CExBaseObject *pMatchRef = NULL;

		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)pList->GetNext(pos);

			if (pXMatch->m_pRefObject == pDestCmpData)
			{
				POS posMatch = pXMatch->m_listMacthRefObject.GetHeadPosition();
				
				while (posMatch != NULL)
				{
					pMatchRef = pXMatch->m_listMacthRefObject.GetNext(posMatch);

#ifdef exbase_not_use_m_dwReserved
					if (pMatchRef->m_dwItemData == 1)
#else
					if (pMatchRef->m_dwReserved == 1)
#endif
					{
						continue;;
					}

					CDvmCmpObj *pNew = new CDvmCmpObj(pMatchRef, pDestCmpData);
					pNew->m_nCmpRate = 100;
					listCmp.AddTail(pNew);
				}
			}
		}
	}

	//获取相似程度最高的
	CDvmCmpObj *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmData*)pCmpObj->m_pStand;
	}
}

long CDvmCmpTool::CanCmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData)
{
#ifdef exbase_not_use_m_dwReserved
	if (pStand->m_dwItemData == 1 || pDestCmpData->m_dwItemData == 1)
#else
	if (pStand->m_dwReserved == 1 || pDestCmpData->m_dwReserved == 1)
#endif
	{
		return 0;
	}

	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpData);

	return nCmp;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmData(CDvmDataset *pStand, CDvmData *pDestCmpData, CDvmCmpObj *pParent)
{
	POS pos = pStand->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;

	//查找可以与pDestCmpData比较的data
	pData = FindCmpDvmData(pStand, pDestCmpData, pParent);

	if (pData == NULL)
	{
		pDvmCmpObj = new CDvmCmpObj(NULL, pDestCmpData);
		pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_DestCmp(pDestCmpData, pDvmCmpObj);
		pParent->AddNewChild(pDvmCmpObj);
		pDvmCmpObj->m_nCmpResult += 1;
		//pDestCmpData->m_dwReserved = 1;
	}
	else
	{
		//比较Data
		pDvmCmpObj = CmpDvmData(pData, pDestCmpData);
		ASSERT( pDvmCmpObj != NULL);
		pParent->AddNewChild(pDvmCmpObj);
	}

	return pDvmCmpObj;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmData(CDvmData *pStand, CDvmData *pDestCmpData)
{
#ifdef exbase_not_use_m_dwReserved
	pStand->m_dwItemData = 1;
	pDestCmpData->m_dwItemData = 1;
#else
	pStand->m_dwReserved = 1;
	pDestCmpData->m_dwReserved = 1;
#endif

	CDvmCmpObj *pDvmCmpObj = new CDvmCmpObj(pStand, pDestCmpData);
	CDvmCmpObj *p = NULL;

	//比较名称、id

	//比较数据的属性
	POS pos = pDestCmpData->GetHeadPosition();
	CDvmValue *pDvmValue = NULL;

	if (pStand->m_strName.Find(g_sLangTxt_TimeLimit/*_T("时限")*/) >= 0)
	{
		int ii=0;
	}

	while (pos!= NULL)
	{
		pDvmValue = (CDvmValue*)pDestCmpData->GetNext(pos);
		p = CmpDvmValue(pStand, pDvmValue, pDvmCmpObj);
		pDvmCmpObj->m_nChildCmp += p->IsCmpError();
	}

	pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_Stand(pStand, pDvmCmpObj);

	return pDvmCmpObj;
}

void CDvmCmpTool::CmpDvmData(CDvmCmpObj *pDvmCmpObj)
{
	if (pDvmCmpObj == NULL)
	{
		return;
	}

	pDvmCmpObj->FreeStringCmp();
	CDvmData *pStand       = (CDvmData*)pDvmCmpObj->m_pStand;
	CDvmData *pDestCmpData = (CDvmData*)pDvmCmpObj->m_pDestCmp;
	CDvmCmpObj *p = NULL;

	//比较名称、id

	//比较数据的属性
	pDvmCmpObj->DeleteAll();

	if (pStand == NULL && pDestCmpData == NULL)
	{
		return;
	}

	if (pStand != NULL && pDestCmpData != NULL)
	{
		POS pos = pDestCmpData->GetHeadPosition();
		CDvmValue *pDvmValue = NULL;

		while (pos!= NULL)
		{
			pDvmValue = (CDvmValue*)pDestCmpData->GetNext(pos);
			p = CmpDvmValue(pStand, pDvmValue, pDvmCmpObj);
			pDvmCmpObj->m_nChildCmp += p->IsCmpError();
		}

		pDvmCmpObj->m_nChildCmp += AddOtherCmpObj_Stand(pStand, pDvmCmpObj);
	}
	else 
	{
		if (pStand != NULL)
		{
			POS pos = pStand->GetHeadPosition();
			CDvmValue *pDvmValue = NULL;

			while (pos!= NULL)
			{
				pDvmValue = (CDvmValue*)pStand->GetNext(pos);
				p = new CDvmCmpObj(pDvmValue, NULL);
				pDvmCmpObj->AddNewChild(p);
				p->m_nCmpResult = 1;
				pDvmCmpObj->m_nCmpResult++;
			}
		}
		else
		{
			POS pos = pDestCmpData->GetHeadPosition();
			CDvmValue *pDvmValue = NULL;

			while (pos!= NULL)
			{
				pDvmValue = (CDvmValue*)pStand->GetNext(pos);
				p = new CDvmCmpObj(NULL, pDestCmpData);
				pDvmCmpObj->AddNewChild(p);
				p->m_nCmpResult = 1;
				pDvmCmpObj->m_nCmpResult++;
			}
		}
	}

	if (pDvmCmpObj->m_pDestCmp != NULL)
	{
		CExBaseList *pDsDestCmp = (CExBaseList *)pDvmCmpObj->m_pDestCmp->GetParent();
		pDvmCmpObj->m_nDestIndex = pDsDestCmp->FindIndex(pDvmCmpObj->m_pDestCmp);
	}
}


//////////////////////////////////////////////////////////////////////////
CString CDvmCmpTool::GetDvmValueKey(CDvmValue *pDvmValue)
{
	POS pos = m_oDvmCmpValueKeyDataType.GetHeadPosition();
	CDataType *pDataType = NULL;
	CDataType *pFind     = NULL;
	CString strKey;

	while (pos != NULL)
	{
		pDataType = (CDataType *)m_oDvmCmpValueKeyDataType.GetNext(pos);

		if (pDvmValue->m_strID.Right(pDataType->m_strID.GetLength())  == pDataType->m_strID)
		{
			pFind = pDataType;
			break;
		}
	}

	if (pFind != NULL)
	{
		strKey = pFind->m_strID;
	}
	else
	{
		long nPos = pDvmValue->m_strID.ReverseFind('$');
		strKey = pDvmValue->m_strID.Mid(nPos);
	}

	return strKey;
}

CDvmValue* CDvmCmpTool::FindCmpDvmValue(CExBaseList *pStand, CDvmValue *pDestCmpValue)
{
	POS pos = pStand->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;
	CExBaseList listCmp;
	long nCmpRate = 0;
	CString strValueAttr = GetDvmValueKey(pDestCmpValue);
	long nLen = strValueAttr.GetLength();

	while (pos != NULL)
	{
		//遍历pStand的每一个Value，判断是否可以与pDestCmpValue进行比较
		pValue = (CDvmValue *)pStand->GetNext(pos);

#ifdef exbase_not_use_m_dwReserved
		if (pValue->m_dwItemData == 1)
#else
		if (pValue->m_dwReserved == 1)
#endif
		{
			continue;
		}

		nCmpRate = CanCmpDvmObject_ID(pValue, pDestCmpValue);

		if (nCmpRate > 0)
		{
			CDvmCmpObj *pNew = new CDvmCmpObj(pValue, pDestCmpValue);
			pNew->m_nCmpRate = 1;
			listCmp.AddTail(pNew);
			continue;
		}

		//if (nCmpRate > 0)
		if (pValue->m_strID.Right(nLen) == strValueAttr)
		{
			CDvmCmpObj *pNew = new CDvmCmpObj(pValue, pDestCmpValue);
			pNew->m_nCmpRate = 1;
			listCmp.AddTail(pNew);
		}
	}

	//获取相似程度最高的
	CDvmCmpObj *pCmpObj = GetCmpMatchObject(listCmp);

	if (pCmpObj == NULL)
	{
		return NULL;
	}
	else
	{
		return (CDvmValue*)pCmpObj->m_pStand;
	}
}

long CDvmCmpTool::CanCmpDvmValue(CDvmValue *pStand, CDvmValue *pDestCmpValue)
{
	//比较名称、ID
	long nCmp = CanCmpDvmObject(pStand, pDestCmpValue);

	return nCmp;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmValue(CDvmData *pStand, CDvmValue *pDestCmpValue, CDvmCmpObj *pParent)
{
	POS pos = pStand->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmCmpObj *pDvmCmpObj = NULL;

	//查找可以与pDestCmpValue比较的Value
	pValue = FindCmpDvmValue(pStand, pDestCmpValue);

	if (pValue == NULL)
	{
		pDvmCmpObj = new CDvmCmpObj(NULL, pDestCmpValue);
		//AddOtherCmpObj_DestCmp(pDestCmpValue, pDvmCmpObj);
		pParent->AddNewChild(pDvmCmpObj);
		pDvmCmpObj->m_nCmpResult = 1;
	}
	else
	{
		//比较Value
		pDvmCmpObj = CmpDvmValueEx(pValue, pDestCmpValue);
		ASSERT( pDvmCmpObj != NULL);
		pParent->AddNewChild(pDvmCmpObj);
	}

	return pDvmCmpObj;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmValueEx(CDvmValue *pStand, CDvmValue *pDestCmpValue)
{
#ifdef exbase_not_use_m_dwReserved
	pStand->m_dwItemData = 1;
	pDestCmpValue->m_dwItemData = 1;
#else
	pStand->m_dwReserved = 1;
	pDestCmpValue->m_dwReserved = 1;
#endif
	CDvmCmpObj *pDvmCmpObj = new CDvmCmpObj(pStand, pDestCmpValue);

	//比较名称、id

	//比较Value的属性，在此，不在深入比较
// 	POS pos = pDestCmpData->GetHeadPosition();
// 	CDvmValue *pDvmValue = NULL;
// 
// 	while (pos!= NULL)
// 	{
// 		pDvmValue = (CDvmValue*)pDestCmpData->GetNext(pos);
// 		CmpDvmData(pStand, pDvmValue, pDvmCmpObj);
// 	}

	return pDvmCmpObj;
}

CDvmCmpObj* CDvmCmpTool::CmpDvmValueVal(CDvmValue *pStand, CDvmValue *pDestCmpValue)
{
	return NULL;
}

CDvmCmpObj* CDvmCmpTool::GetCmpMatchObject(CExBaseList &listCmpObj)
{
	CDvmCmpObj *pFind = (CDvmCmpObj*)listCmpObj.GetHead();

	if (listCmpObj.GetCount() <= 1)
	{
		return pFind;
	}

	POS pos = listCmpObj.GetHeadPosition();
	CDvmCmpObj *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)listCmpObj.GetNext(pos);

		if (pFind->m_nCmpRate < p->m_nCmpRate)
		{
			pFind = p;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
const CString CDvmCmpTool::g_strLdeviceDataTypeID = _T("ldevice-key");
const CString CDvmCmpTool::g_strDatasetDataTypeID = _T("dataset-key");
const CString CDvmCmpTool::g_strDvmCmpValueKeyDataTypeID = _T("value-key");
const CString CDvmCmpTool::g_strDvmCmpFullNameIdKeyTypeID = _T("full-name-id-key");

//比较名称、ID
long CDvmCmpTool::CanCmpDvmObject(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	//名称相同
	if ( (pStand->m_strName.GetLength() > 0) && (pStand->m_strName == pDestCmpObj->m_strName) )
	{
		return 100;
	}

	//ID相同
// 	if ((pStand->m_strID.GetLength() > 0) && (pStand->m_strID == pDestCmpObj->m_strID))
// 	{
// 		return 90;
// 	}

	//名称包含
	if ((pStand->m_strName.Find(pDestCmpObj->m_strName) >= 0) && (pDestCmpObj->m_strName.GetLength() > 0))
	{
		return 80;
	}

	if ((pDestCmpObj->m_strName.Find(pStand->m_strName) >= 0) && (pStand->m_strName.GetLength() > 0))
	{
		return 80;
	}

	//ID包含
// 	if ((pStand->m_strID.Find(pDestCmpObj->m_strID) >= 0) && (pDestCmpObj->m_strID.GetLength() > 0))
// 	{
// 		return 70;
// 	}
// 
// 	if ((pDestCmpObj->m_strID.Find(pStand->m_strID) >= 0) && (pStand->m_strID.GetLength() > 0))
// 	{
// 		return 70;
// 	}


	return 0;
}

long CDvmCmpTool::CanCmpDvmObject_ID(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	//ID相同
	if ((pStand->m_strID.GetLength() > 0) && (pStand->m_strID == pDestCmpObj->m_strID))
	{
		return 100;
	}

	//ID包含
	if ((pStand->m_strID.Find(pDestCmpObj->m_strID) >= 0) && (pDestCmpObj->m_strID.GetLength() > 0))
	{
		return 90;
	}

	if ((pDestCmpObj->m_strID.Find(pStand->m_strID) >= 0) && (pStand->m_strID.GetLength() > 0))
	{
		return 90;
	}

	return 0;
}

void CDvmCmpTool::OpenKeyDataTypesFile(const CString &strFile)
{
	CString strPath;

	strPath = _P_GetConfigPath();
	strPath += strFile;

	m_oKeyDataTypes.OpenXmlFile(strPath, CDataMngrXmlRWKeys::CDataTypesKey(), CDataMngrXmlRWKeys::g_pXmlKeys);

	m_pDatasetDataType = (CDataType*)m_oKeyDataTypes.FindByID(g_strDatasetDataTypeID);
	m_pLdeviceDataType = (CDataType*)m_oKeyDataTypes.FindByID(g_strLdeviceDataTypeID);
	m_pDvmCmpValueKeyDataType = (CDataType*)m_oKeyDataTypes.FindByID(g_strDvmCmpValueKeyDataTypeID);
	m_pDvmCmpFullNameIdKeyType = (CDataType*)m_oKeyDataTypes.FindByID(g_strDvmCmpFullNameIdKeyTypeID);
}


long CDvmCmpTool::GetLdeviceKey(const CString &strText)
{
	return GetKey(m_pLdeviceDataType, strText);
}

long CDvmCmpTool::GetDatasetKey(const CString &strText)
{
	return GetKey(m_pDatasetDataType, strText);
}


long CDvmCmpTool::GetCmpFullNameIdKey(const CString &strText)
{
	if (m_pDvmCmpFullNameIdKeyType == NULL)
	{
		return -1;
	}

	CString strTemp = strText;
	strTemp.MakeLower();

	POS pos = m_pDvmCmpFullNameIdKeyType->GetHeadPosition();
	CDataTypeValue *pVal = NULL;
	long nIndex = 0, nIndexFind = -1;

	while (pos != NULL)
	{
		pVal = (CDataTypeValue *)m_pDvmCmpFullNameIdKeyType->GetNext(pos);

		if (strTemp.Find(pVal->m_strID) >= 0)
		{
#ifdef _UNICODE
			nIndexFind = _wtoi(pVal->m_strIndex);
#else
			nIndexFind = atoi(pVal->m_strIndex);
#endif
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}

long CDvmCmpTool::GetKey(CDataType *pDataType, const CString &strText)
{
	if (pDataType == NULL)
	{
		return -1;
	}

	POS pos = pDataType->GetHeadPosition();
	CDataTypeValue *pVal = NULL;
	long nIndex = 0, nIndexFind = -1;

	while (pos != NULL)
	{
		pVal = (CDataTypeValue *)pDataType->GetNext(pos);

		if (strText.Find(pVal->m_strID) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}

void CDvmCmpTool::AddOtherCmpObj_Stand()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *pLdCmp = NULL;
	POS posDsCmp = NULL;
	CDvmCmpObj *pDsCmp;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		//遍历ldevice的比较对象
		pLdCmp = (CDvmCmpObj *)GetNext(pos);

		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pDestCmp == NULL)
		{
			continue;
		}

		//遍历逻辑设备比较对象
		posDsCmp = pLdCmp->GetHeadPosition();

		while (posDsCmp != NULL)
		{
			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);

			if (pDsCmp->m_pStand == NULL)
			{
				continue;
			}

			AddOtherCmpObj_Stand((CExBaseList*)pDsCmp->m_pStand, pDsCmp);;
		}
	}
}

long CDvmCmpTool::AddOtherCmpObj_Stand(CExBaseList *pStand, CExBaseList *pListCmpObj)
{
	POS pos = pStand->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = pStand->GetClassID();
	long nCount = 0;

	while (pos != NULL)
	{
		p = pStand->GetNext(pos);

#ifdef exbase_not_use_m_dwReserved
		if (p->m_dwItemData == 1)
#else
		if (p->m_dwReserved == 1)
#endif
		{
			continue;
		}

		if (!IsStandInListCmpObj(p, pListCmpObj))
		{
			CDvmCmpObj *pNew = new CDvmCmpObj(p, NULL);
			pNew->m_nCmpResult = 1;
			pListCmpObj->AddNewChild(pNew);

			if (nClassID == DVMCLASSID_CDVMDEVICE
				|| nClassID == DVMCLASSID_CDVMLOGICDEVICE 
				|| nClassID == DVMCLASSID_CDVMDATASET
				|| nClassID == DVMCLASSID_CDVMDATA)
			{
				pNew->m_nChildCmp = AddOtherCmpObj_Stand((CExBaseList*)p, pNew);
				nCount++;
			}
		}
		
		//p->m_dwReserved = 1;
	}

	return nCount;
}

BOOL CDvmCmpTool::IsStandInListCmpObj(CExBaseObject *pStand, CExBaseList *pListCmpObj)
{
	POS pos = pListCmpObj->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)pListCmpObj->GetNext(pos);

		if (pStand == p->m_pStand)
		{
			bFind = TRUE;
		}
	}

	return bFind;
}


long CDvmCmpTool::AddOtherCmpObj_DestCmp(CExBaseList *pDestCmp, CExBaseList *pListCmpObj)
{
	POS pos = pDestCmp->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = pDestCmp->GetClassID();
	long nCount = 0;

	while (pos != NULL)
	{
		p = pDestCmp->GetNext(pos);

		if (!IsDestCmpInListCmpObj(p, pListCmpObj))
		{
			CDvmCmpObj *pNew = new CDvmCmpObj(NULL, p);
			pListCmpObj->AddNewChild(pNew);
			pNew->m_nCmpResult = 1;

			if (nClassID == DVMCLASSID_CDVMLOGICDEVICE 
				|| nClassID == DVMCLASSID_CDVMDATASET
				|| nClassID == DVMCLASSID_CDVMDATA)
			{
				pNew->m_nChildCmp = AddOtherCmpObj_DestCmp((CExBaseList*)p, pNew);
				nCount++;
			}
		}
	}

	return nCount;
}

BOOL CDvmCmpTool::IsDestCmpInListCmpObj(CExBaseObject *pDestCmp, CExBaseList *pListCmpObj)
{
	POS pos = pListCmpObj->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)pListCmpObj->GetNext(pos);

		if (pDestCmp == p->m_pDestCmp)
		{
			bFind = TRUE;
		}
	}

	return bFind;
}


void CDvmCmpTool::CreateDvmMap()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *pDvmCmp = NULL;

	//Dataset
	while (pos != NULL)
	{
		pDvmCmp = (CDvmCmpObj *)GetNext(pos);

		if (pDvmCmp->m_pStand == NULL)
		{
			continue;
		}

		CreateDvmMap_Ldevice(pDvmCmp);
	}
}

void CDvmCmpTool::CreateDvmMap_Ldevice(CDvmCmpObj *pDvmLdeviceCmp)
{
	CDvmDatasetMap *pDatasetMap = NULL;
	POS pos = pDvmLdeviceCmp->GetHeadPosition();
	CDvmCmpObj *pDsCmp = NULL;

	while (pos != NULL)
	{
		pDsCmp = (CDvmCmpObj *)pDvmLdeviceCmp->GetNext(pos);

		if (pDsCmp->m_pStand == NULL)
		{
			continue;
		}

		pDatasetMap = new CDvmDatasetMap();
		pDatasetMap->m_strName = pDsCmp->m_pStand->m_strName;
		pDatasetMap->m_strID = pDsCmp->m_pStand->m_strID;
		pDatasetMap->m_strLdvice    = pDvmLdeviceCmp->m_pStand->m_strID;

		if (pDvmLdeviceCmp->m_pDestCmp != NULL)
		{
			pDatasetMap->m_strLdviceMap = pDvmLdeviceCmp->m_pDestCmp->m_strID;
		}

		if (pDsCmp->m_pDestCmp != NULL)
		{
			pDatasetMap->m_strMapName = pDsCmp->m_pDestCmp->m_strName;
			pDatasetMap->m_strMapID   = pDsCmp->m_pDestCmp->m_strID;
		}

		m_oDvmDeviceMap.AddNewChild(pDatasetMap);
		CreateDvmMap(pDatasetMap, pDsCmp);
	}
}

void CDvmCmpTool::CreateDvmMap(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp)
{
	POS pos = pDvmDatasetCmp->GetHeadPosition();
	CDvmCmpObj *pDvmCmp = NULL;
	CDvmDataMap *pDataMap = NULL;

	//Dataset
	while (pos != NULL)
	{
		pDvmCmp = (CDvmCmpObj *)pDvmDatasetCmp->GetNext(pos);
	
		if (pDvmCmp->m_pStand == NULL || pDvmCmp->m_pDestCmp == NULL)
		{
			continue;
		}

		pDataMap = new CDvmDataMap();
		pDataMap->m_strName = pDvmCmp->m_pStand->m_strName;
		pDataMap->m_strID = pDvmCmp->m_pStand->m_strID;
		pDataMap->m_strMapName = pDvmCmp->m_pDestCmp->m_strName;
		pDataMap->m_strMapID = pDvmCmp->m_pDestCmp->m_strID;

		pMap->AddNewChild(pDataMap);
		CreateDvmMap(pDataMap, pDvmCmp);
	}
}

void CDvmCmpTool::CreateDvmMap(CDvmDataMap *pMap, CDvmCmpObj *pDvmDataCmp)
{
	POS pos = pDvmDataCmp->GetHeadPosition();
	CDvmCmpObj *pDvmCmp = NULL;
	CDvmValueMap *pValueMap = NULL;

	//Dataset
	while (pos != NULL)
	{
		pDvmCmp = (CDvmCmpObj *)pDvmDataCmp->GetNext(pos);

		if (pDvmCmp->m_pStand == NULL)
		{
			continue;
		}

		if (pDvmCmp->m_pDestCmp == NULL)
		{
			continue;
		}

		pValueMap = new CDvmValueMap();
		pValueMap->m_strName = pDvmCmp->m_pStand->m_strName;
		pValueMap->m_strID = pDvmCmp->m_pStand->m_strID;
		pValueMap->m_strMapName = pDvmCmp->m_pDestCmp->m_strName;
		pValueMap->m_strMapID = pDvmCmp->m_pDestCmp->m_strID;

		pMap->AddNewChild(pValueMap);
	}
}

//////////////////////////////////////////////////////////////////////////
//
void CDvmCmpTool::InitByDvmMap()
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *pLdCmp = NULL;
	POS posDsCmp = NULL;
	CDvmCmpObj *pDsCmp;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		//遍历ldevice的比较对象
		pLdCmp = (CDvmCmpObj *)GetNext(pos);

		if (pLdCmp->m_pStand == NULL || pLdCmp->m_pDestCmp == NULL)
		{
			continue;
		}

		//遍历逻辑设备比较对象
		posDsCmp = pLdCmp->GetHeadPosition();

		while (posDsCmp != NULL)
		{
			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);

			if (pDsCmp->m_pStand == NULL || pDsCmp->m_pDestCmp == NULL)
			{
				continue;
			}

			//数据集比较对象：查找数据映射关联对象
			pDsMap = m_oDvmDeviceMap.FindDsMap(pLdCmp->m_pStand->m_strID, pDsCmp->m_pStand->m_strID
				, pLdCmp->m_pDestCmp->m_strID, pDsCmp->m_pDestCmp->m_strID);

			if (pDsMap != NULL)
			{
				//根据数据集比较对象，数据集关联对象，更新数据集比较对象
				UpdateByMap_DsCmp(pDsMap, pDsCmp);
			}
		}
	}
}

void CDvmCmpTool::UpdateByMap_DsCmp(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDatasetCmp)
{
	POS pos = pDvmDatasetCmp->GetHeadPosition();
	CDvmCmpObj *pDvmDataCmp = NULL;
	CDvmDataset *pDsStand = (CDvmDataset*)pDvmDatasetCmp->m_pStand;
	CDvmDataset *pDsDest = (CDvmDataset*)pDvmDatasetCmp->m_pDestCmp;
	CDvmDataMap *pDaStandMap = NULL;
	CDvmData *pDestData = NULL;

	while (pos != NULL)
	{
		pDvmDataCmp = (CDvmCmpObj *)pDvmDatasetCmp->GetNext(pos);
		
		if (pDvmDataCmp->m_pStand == NULL)
		{
			continue;
		}

		//根据比较对象的Stand对象，查找映射关系中的DataMap对象
// 		if (pDvmDataCmp->m_pStand->m_strName.Find(_T("1时限")) >= 0)
// 		{
// 			int kk = 0;
// 		}

		pDaStandMap = pMap->FindMapData(pDvmDataCmp->m_pStand->m_strID);

		if (pDaStandMap == NULL)
		{
			continue;
		}

		//目标数据集中查找映射关系的数据对象
		pDestData = (CDvmData *)pDsDest->FindByID(pDaStandMap->m_strMapID);

		if (pDestData != NULL)
		{
			CDvmCmpObj *pFind = pDvmDataCmp->SetDest(pDestData);

			if (pFind != NULL)
			{
				CmpDvmData(pDvmDataCmp);
				CmpDvmData(pFind);
			}
		}
	}
}

void CDvmCmpTool::UpdateByMap_DataCmp(CDvmDatasetMap *pMap, CDvmCmpObj *pDvmDataCmp)
{

}


//////////////////////////////////////////////////////////////////////////

void CDvmCmpTool::OpenKeyDbFile()
{
	if (m_pKeyDB == NULL)
	{
		m_pKeyDB = new CXKeyDB();
		m_pKeyDB->OpenKeyDbFile(_T("RelayTestKeyDb.xml"), _T(""));
	}
}

void CDvmCmpTool::XMatchDataset(CDvmDataset *pDsStand, CDvmDataset *pDsDestCmp)
{
	m_oXMatchTool.Match(m_pKeyDB, pDsStand, pDsDestCmp, 70);
}

//////////////////////////////////////////////////////////////////////////
void CDvmCmpTool::ExportReportFile(const CString &strFile)
{
	CreateWordApplication(TRUE);

	if (!NewWordReportFile())
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDvmCmpObj *pLdCmp = NULL;
	POS posDsCmp = NULL;
	CDvmCmpObj *pDsCmp;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		//遍历ldevice的比较对象
		pLdCmp = (CDvmCmpObj *)GetNext(pos);

		if (pLdCmp->m_pDestCmp == NULL || pLdCmp->m_pStand == NULL)
		{
			continue;
		}


		if (pLdCmp->m_pStand->m_strID != pLdCmp->m_pDestCmp->m_strID)
		{
			CString strTitle;
			strTitle.Format(_T("%s : %s"), pLdCmp->m_pStand->m_strID, pLdCmp->m_pDestCmp->m_strID);
			InsertTitle(pLdCmp->m_pStand->m_strID , 1);
		}
		else
		{
			InsertTitle(pLdCmp->m_pStand->m_strID, 1);
		}

		//遍历逻辑设备比较对象
		posDsCmp = pLdCmp->GetHeadPosition();

		while (posDsCmp != NULL)
		{
			pDsCmp = (CDvmCmpObj *)pLdCmp->GetNext(posDsCmp);
			ExportReport_DsCmp(pDsCmp);
		}
	}

	//Doc文件保存
	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	

	m_doc.SaveAs(COleVariant(strFile), vOpt, vOpt, vOpt,
		vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
}

BOOL CDvmCmpTool::IsDsNeedWriteToReport(const CString &strID)
{
	POS pos = m_oRptDstaset.GetHeadPosition();
	CExBaseObject *p = NULL;
	BOOL bNeed = FALSE;

	while (pos != NULL)
	{
		p = (CExBaseObject *)m_oRptDstaset.GetNext(pos);

		if (p->m_strID.Find(strID) >= 0)
		{
			bNeed = TRUE;
			break;
		}
	}

	return bNeed;
}

void CDvmCmpTool::ExportReport_DsCmp(CDvmCmpObj *pDsCmp)
{
	if (pDsCmp->m_pStand == NULL || pDsCmp->m_pDestCmp == NULL)
	{
		return;
	}

	if (!IsDsNeedWriteToReport(pDsCmp->m_pStand->m_strID))
	{
		return;
	}

	if (!pDsCmp->IsCmpError_Child())
	{
		return;
	}

	CString strTitle;
	
	strTitle = pDsCmp->m_pStand->m_strID;

	if (pDsCmp->m_pDestCmp != NULL)
	{
		if (pDsCmp->m_pDestCmp->m_strID != pDsCmp->m_pStand->m_strID)
		{
			strTitle.AppendFormat(_T(" : %s"), pDsCmp->m_pDestCmp->m_strID);
		}
	}
	
	InsertTitle(strTitle, 2);
	POS pos = pDsCmp->GetHeadPosition();
	CDvmCmpObj *pDataCmp = NULL;

	long nVal = MSWord::wdWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = MSWord::wdAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 

	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	MSWord::Tables oTables = m_doc.GetTables();
	MSWord::Table oTable   = oTables.Add(oRange, 1, 4, &vTableBehavior, &vAutoFitBehavior);
	MSWord::Columns oCols = oTable.GetColumns();
	MSWord::Column  oCol  = NULL;
	
	try
	{
		oCol  = oCols.Item(1);
		float fWidth = oCol.GetWidth();
		float fWidthTotl = fWidth * 4;
		float fTemp = fWidth / 6;
		m_fWidthCol1 = fTemp;
		oCol.SetWidth(fTemp);
		fWidthTotl -= fTemp;
		//oCol.Select();
		//oSelection = m_WordApp.GetSelection();
		//oSelection.TypeText(_T("比较项"));

		oCol  = oCols.Item(2);
		fTemp = fWidth * 0.6f;
		fWidthTotl -= fTemp;
		oCol.SetWidth(fTemp);
		m_fWidthCol2 = fTemp;
		oCol.Select();
		//oSelection = m_WordApp.GetSelection();
		oSelection.TypeText(g_sLangTxt_ComparaObject/*_T("比较项")*/);

		oCol  = oCols.Item(3);
		fTemp = fWidthTotl / 2;
		oCol.SetWidth(fTemp);
		oCol.Select();
		//oSelection = m_WordApp.GetSelection();
		oSelection.TypeText(g_sLangTxt_StandardValue/*_T("标准值")*/);

		oCol  = oCols.Item(4);
		oCol.SetWidth(fTemp);
		oCol.Select();
		//oSelection = m_WordApp.GetSelection();
		oSelection.TypeText(g_sLangTxt_TureValue/*_T("实际值")*/);
		m_fWidthCol3 = m_fWidthCol4 = fTemp;
	}
	catch (...)
	{
		
	}
	
	long nRowIndex = 1;

	while (pos != NULL)
	{
		pDataCmp = (CDvmCmpObj *)pDsCmp->GetNext(pos);
		try
		{
			ExportReport_DataCmp(pDataCmp, oTable, nRowIndex);
		}
		catch (...)
		{

		}
	}
}

void CDvmCmpTool::MergeRow(MSWord::Row &oRow)
{
	MSWord::Cells oCells = oRow.GetCells();

	if (oCells.GetCount() == 3)
	{
		return;
	}

	MSWord::Cell  oCell = oCells.Item(1);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();

	long nVal;
	nVal = MSWord::wdCharacter;
	CComVariant vUnit(nVal); 
	CComVariant vCount(long(1)); 
	nVal = MSWord::wdExtend;
	CComVariant vExtend(nVal); 
	oSelection.MoveRight(&vUnit, &vCount, &vExtend);
	oCells = oSelection.GetCells();
	oCells.Merge();
}

void CDvmCmpTool::InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit)
{
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 
	oSelection.InsertRowsBelow(&vCount);
	MSWord::Rows oRows = oTable.GetRows();
	oRow = oRows.Item(oRows.GetCount());
	MSWord::Cells oCells = oRow.GetCells();
	
	if (!bSplit)
	{
		return;
	}

	if (oCells.GetCount() == 3)
	{
		CComVariant vCols(long(2)); 
		CComVariant vMergeBeforeSplit(long(0)); 
		MSWord::Cell oCell = oCells.Item(1);
		oCell.Select();
		oSelection = m_WordApp.GetSelection();
		oCells = oSelection.GetCells();
		oCells.Split(&vCount, &vCols, &vMergeBeforeSplit);

		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.SetWidth(m_fWidthCol1);

		oCell = oCells.Item(2);
		oCell.SetWidth(m_fWidthCol2);

		oCell = oCells.Item(3);
		oCell.SetWidth(m_fWidthCol3);

		oCell = oCells.Item(4);
		oCell.SetWidth(m_fWidthCol4);
	}
}

void CDvmCmpTool::GetRowCell(MSWord::Row &oRow, MSWord::Cell &oCell, long nIndex)
{
	MSWord::Cells oCells = oRow.GetCells();
	oCell = oCells.Item(nIndex);
}

void CDvmCmpTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(RGB(0, 0, 0));
	oSelection.TypeText(strText);
}

void CDvmCmpTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(color);
	oSelection.TypeText(strText);
	oFont.SetColor(RGB(0, 0, 0));
}

void CDvmCmpTool::SetRowCellText(MSWord::Row &oRow, long nIndex, CStringCmpBlocks *pStrCmpBlcks)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();

	POS pos = pStrCmpBlcks->GetHeadPosition();
	CStringCmpBlock *pStrCmpBlck = NULL;
	CString strText;
	MSWord::_Font oFont = oSelection.GetFont();

	ASSERT (pos != NULL);

	while (pos != NULL)
	{
		pStrCmpBlck = (CStringCmpBlock *)pStrCmpBlcks->GetNext(pos);
		strText = pStrCmpBlck->m_pStringRef->Mid(pStrCmpBlck->m_nBeginPos, pStrCmpBlck->m_nLength);

		if (pStrCmpBlck->IsMatch())
		{
			oFont.SetColor(RGB(0, 0, 0));
		}
		else
		{
			oFont.SetColor(RGB(255, 0, 0));
		}

		pStrCmpBlck->GetString(strText);
		oSelection.TypeText(strText);
	}

	oFont.SetColor(RGB(0, 0, 0));
}

void CDvmCmpTool::ExportReport_DataCmp(CDvmCmpObj *pDataCmp, MSWord::Table &oTable, long &nRowIndex)
{
	if (pDataCmp->m_pStand == NULL && pDataCmp->m_pDestCmp == NULL)
	{
		return;
	}

	long nRows = 0;
	MSWord::Rows oRows = oTable.GetRows();
	MSWord::Row  oRow  = NULL;
	MSWord::Cell oCell = NULL;
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 

	if (pDataCmp->m_pStand == NULL)
	{
		InsertRow(oRow, oTable, FALSE);
		MergeRow(oRow);
		SetRowCellText(oRow, 1,  g_sLangTxt_Name/*_T("名称")*/);
		SetRowCellText(oRow, 3, pDataCmp->m_pDestCmp->m_strName, RGB(255, 0, 0));
		nRowIndex++;
		return;
	}

	if (pDataCmp->m_pDestCmp == NULL)
	{
		InsertRow(oRow, oTable, FALSE);
		MergeRow(oRow);
		SetRowCellText(oRow, 1, g_sLangTxt_Name/*_T("名称")*/);
		SetRowCellText(oRow, 2, pDataCmp->m_pStand->m_strName, RGB(255, 0, 0));
		nRowIndex++;
		return;
	}

	pDataCmp->StringCmp();

	if (ExportReport_DataCmp_GetRows(pDataCmp) == 0)
	{
		return;
	}

	InsertRow(oRow, oTable, FALSE);
	MergeRow(oRow);
	SetRowCellText(oRow, 1, g_sLangTxt_Name/*_T("名称")*/);
	CDvmData *pStand = (CDvmData *)pDataCmp->m_pStand;
	CDvmData *pDest  = (CDvmData *)pDataCmp->m_pDestCmp;

	if (pDataCmp->IsNameCmpError())
	{
		SetRowCellText(oRow, 2, pDataCmp->GetNameCmp_Stand());
		SetRowCellText(oRow, 3, pDataCmp->GetNameCmp_Dest());
	}
	else
	{
		SetRowCellText(oRow, 2, pStand->m_strName);
		SetRowCellText(oRow, 3, pDest->m_strName);
	}

	nRowIndex++;

	if (pDataCmp->IsMaxCmpError())	
	{
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE, g_sLangTxt_MaxValue/*_T("最大值")*/);
		SetRowCellText(oRow, COL_STAND, pStand->m_strMax, RGB(255, 0, 0));
		SetRowCellText(oRow, COL_DEST, pDest->m_strMax, RGB(255, 0, 0));
		nRowIndex++;
	}

	if (pDataCmp->IsMinCmpError())
	{
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE, g_sLangTxt_MinValue/*_T("最小值")*/);
		SetRowCellText(oRow, COL_STAND, pStand->m_strMin, RGB(255, 0, 0));
		SetRowCellText(oRow, COL_DEST, pDest->m_strMin, RGB(255, 0, 0));
		nRowIndex++;
	}

	if (pDataCmp->IsStepCmpError())
	{
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE, g_sLangTxt_Step/*_T("步长")*/);
		SetRowCellText(oRow, COL_STAND, pStand->m_strStep, RGB(255, 0, 0));
		SetRowCellText(oRow, COL_DEST, pDest->m_strStep, RGB(255, 0, 0));
		nRowIndex++;
	}

	if (pDataCmp->m_nStandIndex != pDataCmp->m_nDestIndex && pDataCmp->m_nDestIndex >= 0)
	{
		CString strText;
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE, g_sLangTxt_Index/*_T("编号")*/);
		strText.Format(_T("%d"), pDataCmp->m_nStandIndex);
		SetRowCellText(oRow, COL_STAND, strText, RGB(255, 0, 0));
		strText.Format(_T("%d"), pDataCmp->m_nDestIndex);
		SetRowCellText(oRow, COL_DEST, strText, RGB(255, 0, 0));
		nRowIndex++;
	}

	if (m_oRptDstaset.m_nWriteMode == 0)
	{
		return;
	}

	POS pos = pDataCmp->GetHeadPosition();
	CDvmCmpObj *pValueCmp = NULL;

	while (pos != NULL)
	{
		pValueCmp = (CDvmCmpObj *)pDataCmp->GetNext(pos);
		ExportReport_ValueCmp(pValueCmp, oTable, nRowIndex);
	}
}


void CDvmCmpTool::ExportReport_ValueCmp(CDvmCmpObj *pValueCmp, MSWord::Table &oTable, long &nRowIndex)
{
	if (pValueCmp->m_pStand == NULL && pValueCmp->m_pDestCmp == NULL)
	{
		return;
	}

	long nRows = 0;
	MSWord::Rows oRows = oTable.GetRows();
	MSWord::Row  oRow  = NULL;
	MSWord::Cell oCell = NULL;
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 
	CString strKey;

	if (pValueCmp->m_pStand == NULL)
	{
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE, g_sLangTxt_Property/*_T("属性")*/);
		SetRowCellText(oRow, COL_DEST, pValueCmp->m_pDestCmp->m_strID, RGB(255, 0, 0));
		nRowIndex++;
		return;
	}

	if (pValueCmp->m_pDestCmp == NULL)
	{
		InsertRow(oRow, oTable);
		SetRowCellText(oRow, COL_CMPTYPE,g_sLangTxt_Property/* _T("属性")*/);
		SetRowCellText(oRow, COL_STAND, pValueCmp->m_pStand->m_strID, RGB(255, 0, 0));
		nRowIndex++;
		return;
	}

	CDvmValue *pStand = (CDvmValue *)pValueCmp->m_pStand;
	CDvmValue *pDest  = (CDvmValue *)pValueCmp->m_pDestCmp;

	if (pStand->m_strDataType == pDest->m_strDataType)
	{
		return;
	}

	strKey = GetDvmValueKey(pStand);

	InsertRow(oRow, oTable);
	SetRowCellText(oRow, COL_CMPTYPE, strKey);
	SetRowCellText(oRow, COL_STAND, pStand->m_strDataType);
	SetRowCellText(oRow, COL_DEST, pDest->m_strDataType);
}

long CDvmCmpTool::ExportReport_DataCmp_GetRows(CDvmCmpObj *pDataCmp)
{
	long nRowIndex = 0;

	if (pDataCmp->IsNameCmpError())
	{
		nRowIndex++;
	}

	CDvmData *pStand = (CDvmData *)pDataCmp->m_pStand;
	CDvmData *pDest  = (CDvmData *)pDataCmp->m_pDestCmp;

	if (pDataCmp->IsMaxCmpError())	
	{
		nRowIndex++;
	}

	if (pDataCmp->IsMinCmpError())
	{
		nRowIndex++;
	}

	if (pDataCmp->IsStepCmpError())
	{
		nRowIndex++;
	}

	if (m_oRptDstaset.m_nWriteMode == 0)
	{
		return nRowIndex++;
	}

	POS pos = pDataCmp->GetHeadPosition();
	CDvmCmpObj *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmCmpObj *)pDataCmp->GetNext(pos);

		if (p->m_pStand == NULL || p->m_pDestCmp == NULL)
		{
			nRowIndex++;
			continue;
		}

		if (((CDvmValue*)p->m_pStand)->m_strDataType != ((CDvmValue*)p->m_pDestCmp)->m_strDataType)
		{
			nRowIndex++;
		}
	}

	return nRowIndex++;
}

//目前不使用这种方式创建、打开word，因为这种方式下当word已打开时会弹出**已打开对话框。
BOOL CDvmCmpTool::CreateWordApplication(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		return TRUE;
	}

	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			AfxMessageBox(g_sLangTxt_UnStallWord/*L"没有安装Word"*/);
			return FALSE;
		}

		m_WordApp.SetVisible(bVisible);  //This shows the application.
	}
	catch (...)
	{
	}

	return TRUE;
}

BOOL CDvmCmpTool::ExitWordApplication()
{
	//关闭文档
	try
	{
		COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		if (m_doc != NULL)
		{
			m_doc.Close(vFalse,covOptional,covOptional);
		}

		m_doc = NULL;
	}
	catch (...)
	{
		m_doc = NULL;

		TRACE(L"Close word doc error...");
	}

	try
	{
		if(m_WordApp)
		{
			COleVariant covTrue((long)TRUE);
			COleVariant covFalse((long)FALSE);
			COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			m_WordApp.Quit(covFalse, covOptional, covOptional);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	return TRUE;
}

BOOL CDvmCmpTool::NewWordReportFile()
{
	if (m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_WordApp.SetVisible(TRUE);
	BOOL bTrue = TRUE;
	try
	{
		CComVariant Template(_T("")); 
		CComVariant NewTemplate(false),DocumentType(0),Visible;
		m_doc = docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	}
	catch(...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


void CDvmCmpTool::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	wordSelection = m_WordApp.GetSelection();
	wordSelection.EndKey(&vUnit, &vOpt);
	wordSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wordSelection.TypeText(strTitle);
		MSWord::Styles oStyles = m_doc.GetStyles();
		CString strStyle;
		strStyle.Format(g_sLangTxt_Title/*_T("标题 %d")*/, nTitleLevel);
		COleVariant vStyleID = strStyle;
		wordSelection.SetStyle(vStyleID);
	}
	else
	{
		MSWord::_Font font = wordSelection.GetFont();
		float fSize = font.GetSize();
		font.SetBold(TRUE);
		font.SetSize(16);
		wordSelection.TypeText(strTitle);
		font.SetSize(fSize);
		font.SetBold(FALSE);
	}

	wordSelection.TypeParagraph();
}

void CDvmCmpTool::GetCmpErrorNum(long &nCmpErrs)
{
	POS pos = GetHeadPosition();
	CDvmCmpObj *p = NULL;

	while (pos)
	{
		p = (CDvmCmpObj *)GetNext(pos);
		nCmpErrs += p->m_nCmpResult;
		p->GetCmpErrorNum(nCmpErrs);
	}
}
/*
Sub 宏1()
'
' 宏1 宏
'
'
Selection.Delete Unit:=wdCharacter, Count:=1
Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
Sub 宏2()
'
' 宏2 宏
'
'
Selection.PasteAndFormat (wdFormatOriginalFormatting)
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("标题 1")
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.TypeText Text:="支路4_"
Application.WindowState = wdWindowStateMinimize
Application.WindowState = wdWindowStateNormal
Selection.TypeText Text:="间隔接受压板"
Selection.Style = ActiveDocument.Styles("标题 2")
Selection.TypeParagraph
ActiveDocument.Tables.Add Range:=Selection.Range, NumRows:=3, NumColumns:= _
3, DefaultTableBehavior:=wdWord9TableBehavior, AutoFitBehavior:= _
wdAutoFitFixed
With Selection.Tables(1)
If .Style <> "网格型" Then
.Style = "网格型"
End If
.ApplyStyleHeadingRows = True
.ApplyStyleLastRow = False
.ApplyStyleFirstColumn = True
.ApplyStyleLastColumn = False
.ApplyStyleRowBands = True
.ApplyStyleColumnBands = False
End With
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("正文")
ActiveWindow.Close
End Sub
Sub 宏3()
'
' 宏3 宏
'
'
Selection.TypeText Text:="LLN"
Application.Keyboard (1033)
Selection.TypeText Text:="$dsSetting"
Selection.TypeParagraph
Selection.MoveUp Unit:=wdLine, Count:=1
Selection.Style = ActiveDocument.Styles("标题 1")
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.TypeText Text:="1,"
Application.Keyboard (2052)
Selection.TypeText Text:="支路4_间隔跳闸压板"
Selection.TypeParagraph
ActiveDocument.Tables.Add Range:=Selection.Range, NumRows:=4, NumColumns:= _
3, DefaultTableBehavior:=wdWord9TableBehavior, AutoFitBehavior:= _
wdAutoFitFixed
With Selection.Tables(1)
If .Style <> "网格型" Then
.Style = "网格型"
End If
.ApplyStyleHeadingRows = True
.ApplyStyleLastRow = False
.ApplyStyleFirstColumn = True
.ApplyStyleLastColumn = False
.ApplyStyleRowBands = True
.ApplyStyleColumnBands = False
End With
Selection.TypeText Text:="名称"
Selection.MoveRight Unit:=wdCharacter, Count:=1
Selection.TypeText Text:="支路4"
Selection.MoveLeft Unit:=wdCharacter, Count:=4, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=1, Extend:=wdExtend
Selection.MoveLeft Unit:=wdCharacter, Count:=1, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=1
Selection.TypeText Text:="_间隔接受压板"
Selection.MoveLeft Unit:=wdCharacter, Count:=13
Selection.MoveDown Unit:=wdLine, Count:=3, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=2, Extend:=wdExtend
With Selection.Tables(1)
.TopPadding = CentimetersToPoints(0)
.BottomPadding = CentimetersToPoints(0)
.LeftPadding = CentimetersToPoints(0.19)
.RightPadding = CentimetersToPoints(0.19)
.Spacing = 0
.AllowPageBreaks = True
.AllowAutoFit = True
End With
Selection.EscapeKey
End Sub


Sub 宏1()
'
' 宏1 宏
'
'
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.EndKey Unit:=wdLine, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=9, Extend:=wdExtend
Selection.Cells.Merge
Selection.MoveDown Unit:=wdLine, Count:=3
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
Selection.InsertRowsBelow 1
End Sub
Sub 宏2()
'
' 宏2 宏
'
'
Selection.MoveDown Unit:=wdLine, Count:=1
Selection.EndKey Unit:=wdLine, Extend:=wdExtend
Selection.MoveRight Unit:=wdCharacter, Count:=5, Extend:=wdExtend
Selection.Cells.Merge
End Sub

*/


//////////////////////////////////////////////////////////////////////////
//CDvmCmpToolConfig
CDvmCmpToolConfig* CDvmCmpToolConfig::g_pDvmCmpToolConfig = NULL;
long CDvmCmpToolConfig::g_nDvmCmpToolConfigRef = NULL;

#define g_strDvmCmpToolConfigFile  _T("DvmCmpToolConfig.xml")

CDvmCmpToolConfig::CDvmCmpToolConfig()
{
	m_nCmpWithID = 0;
	m_nDvmCmdDataNameFull = 1;
}

CDvmCmpToolConfig::~CDvmCmpToolConfig()
{

}

CDvmCmpToolConfig* CDvmCmpToolConfig::Create()
{
	g_nDvmCmpToolConfigRef++;

	if (g_nDvmCmpToolConfigRef == 1)
	{
		g_pDvmCmpToolConfig = new CDvmCmpToolConfig();
		g_pDvmCmpToolConfig->Open();
	}

	return g_pDvmCmpToolConfig;
}

void CDvmCmpToolConfig::Release()
{
	g_nDvmCmpToolConfigRef--;

	if (g_nDvmCmpToolConfigRef == 0)
	{
		delete g_pDvmCmpToolConfig;
		g_pDvmCmpToolConfig = NULL;
	}
}


long CDvmCmpToolConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys* pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_GetElementText(pXmlKeys->m_strCmpWithIDKey, oElement, m_nCmpWithID);
	xml_GetElementText(pXmlKeys->m_strDvmCmdDataNameFullKey, oElement, m_nDvmCmdDataNameFull);

	return 0;
}


long CDvmCmpToolConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys* pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_SetElementText(pXmlKeys->m_strCmpWithIDKey, oXMLDoc, oElement, m_nCmpWithID);
	xml_SetElementText(pXmlKeys->m_strDvmCmdDataNameFullKey, oXMLDoc, oElement, m_nDvmCmdDataNameFull);

	return 0;
}


long CDvmCmpToolConfig::Open()
{
	ASSERT (CDataMngrXmlRWKeys::g_pXmlKeys != NULL);

	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += g_strDvmCmpToolConfigFile;

	BOOL b = OpenXmlFile(m_strFile, CDataMngrXmlRWKeys::g_pXmlKeys->m_strDvmCmpToolConfigKey
		, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
		Save();
	}

	return b;
}

long CDvmCmpToolConfig::Save()
{
	ASSERT (CDataMngrXmlRWKeys::g_pXmlKeys != NULL);

	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	return 1;
}

long CDvmCmpToolConfig::GetCmpWithID()
{
	ASSERT (g_pDvmCmpToolConfig != NULL);
	return g_pDvmCmpToolConfig->m_nCmpWithID;
}

void CDvmCmpToolConfig::SetCmpWithID(long nVal)
{
	ASSERT (g_pDvmCmpToolConfig != NULL);
	g_pDvmCmpToolConfig->m_nCmpWithID = nVal;
	g_pDvmCmpToolConfig->Save();
}


long CDvmCmpToolConfig::GetDvmCmdDataNameFull()
{
	ASSERT (g_pDvmCmpToolConfig != NULL);
	return g_pDvmCmpToolConfig->m_nDvmCmdDataNameFull;
}

void CDvmCmpToolConfig::SetDvmCmdDataNameFull(long nVal)
{
	ASSERT (g_pDvmCmpToolConfig != NULL);
	g_pDvmCmpToolConfig->m_nDvmCmdDataNameFull = nVal;
	g_pDvmCmpToolConfig->Save();
}

