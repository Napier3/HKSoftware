//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenParasMap.cpp  CItemsGenParasMap


#include "stdafx.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenParasMap::CItemsGenParasMap()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenParasMap::~CItemsGenParasMap()
{
}

long CItemsGenParasMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenParasMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenParasMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CItemsGenParasMap::InitAfterRead()
{
}

BOOL CItemsGenParasMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenParasMap *p = (CItemsGenParasMap*)pObj;

	return TRUE;
}

BOOL CItemsGenParasMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenParasMap *p = (CItemsGenParasMap*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenParasMap::Clone()
{
	CItemsGenParasMap *p = new CItemsGenParasMap();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenParasMap::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenParasMap *p = new CItemsGenParasMap();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenParasMap::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenParasMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenDataMapKey)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}

CExBaseObject* CItemsGenParasMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}

BOOL CItemsGenParasMap::GetParaValueByID(const CString &strID, CDataGroup *pDataGroup, CString &strValue)
{
	CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)FindByID(strID);

	if (pDataMap == NULL)
	{
		return FALSE;
	}

	if (!pDataMap->m_strID_Map.IsEmpty())
	{
		strValue = pDataMap->m_strValue;
		return TRUE;
	}

	CDvmData *pData = (CDvmData *)pDataGroup->FindByID(pDataMap->m_strID_Map);

	if (pData == NULL)
	{
		return FALSE;
	}

	strValue = pData->m_strValue;

	return TRUE;
}

//根据界面参数，初始化参数映射的值
//shaolei 2025-4-2 调用到此处时，需确保形参pUIParas中，已经是根据group嵌套关系，将data的路径信息赋值给step属性了
//且形参pUIParas中存放的数据，只有CDvmData一种类型
void CItemsGenParasMap::InitParaValueByUIParas(CDataGroup *pUIParas)
{
	if (pUIParas == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CItemsGenDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CItemsGenDataMap *)GetNext(pos);
		pDataMap->m_nIsMapSucc = 0;

		if (pDataMap->m_strID_Map.IsEmpty())
		{
			pDataMap->m_nIsMapSucc = 1;
			continue;
		}

		//ID_Map中记录的就是界面参数的ID，或者是界面参数ID的表达式
		CDvmData *pData = (CDvmData *)pUIParas->FindByID(pDataMap->m_strID_Map);

		if (pData == NULL)
		{
			pData = GetDataByIDPath_Sort(pUIParas, pDataMap->m_strID_Map);
		}

		if (pData == NULL)
		{
			pDataMap->InitParaByExpression(pUIParas);
			continue;
		}

		pDataMap->m_nIsMapSucc = 1;
		
		if (pData->m_strFormat.GetLength() > 0)
		{
			//format，记录的是表达式。例如：关联的定值及关联定值的表达式。“0.7*setting”
			//format，可能是记录的关联的系统参数，比如：NormVol、NormCur、ZeroVol、ZeroCur
			pDataMap->m_strValue = pData->m_strFormat;
		}
		else
		{
			pDataMap->m_strValue = pData->m_strValue;
		}
	}
}

CDvmData* CItemsGenParasMap::GetDataByIDPath_Sort(CDataGroup *pUIParas, const CString &strIDPath)
{
	POS pos = pUIParas->GetHeadPosition();
	CDvmData *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = (CExBaseObject *)pUIParas->GetNext(pos);
		nClassID = pObj->GetClassID();
		ASSERT(nClassID == DVMCLASSID_CDVMDATA);
		CDvmData *pData = (CDvmData *)pObj;

		if (pData->m_strStep == strIDPath)  //step属性记录的是路径信息
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}

CDvmData* CItemsGenParasMap::GetDataByIDPath(CDataGroup *pUIParas, const CString &strIDPath)
{
	CString strDataPath;
	POS pos = pUIParas->GetHeadPosition();
	CDvmData *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = (CExBaseObject *)pUIParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			strDataPath = pData->GetIDPathEx(pUIParas, FALSE);

			if (strDataPath == strIDPath)
			{
				pFind = pData;
				break;
			}
		}
		
		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGrp = (CDataGroup *)pObj;
			pFind = GetDataByIDPathEx(pUIParas, pGrp, strIDPath);

			if (pFind != NULL)
			{
				break;
			}
		}
		
	}

	return pFind;
}

CDvmData* CItemsGenParasMap::GetDataByIDPathEx(CDataGroup *pUIParas, CDataGroup *pGrp, const CString &strIDPath)
{
	CString strDataPath;
	POS pos = pGrp->GetHeadPosition();
	CDvmData *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = (CExBaseObject *)pGrp->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			strDataPath = pData->GetIDPathEx(pUIParas, FALSE);

			if (strDataPath == strIDPath)
			{
				pFind = pData;
				break;
			}
		}

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGrpChild = (CDataGroup *)pObj;
			pFind = GetDataByIDPathEx(pUIParas, pGrpChild, strIDPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

//进入到该函数时，Interface中的参数值，已经通过界面参数赋值了
void CItemsGenParasMap::InitParasMapByInterface(CItemsGenInterface *pInterface)
{
	if (pInterface == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CItemsGenDataMap *pDataMap = NULL;
	CItemsGenData *pData = NULL;

	while (pos != NULL)
	{
		pDataMap = (CItemsGenDataMap *)GetNext(pos);

		//此处已经映射过的，不能直接跳过  shaolei 20220407
		//因为通过Interface进行映射，是根据不同实例，将Interface下的数据映射给para-map
		//映射结束后，para-map中的值，将用于电气量项目的参数
// 		if (pDataMap->m_nIsMapSucc == 1)
// 		{
// 			//说明已经通过界面参数，进行过一次映射了
// 			continue;
// 		}
		pDataMap->m_nIsMapSucc = 0;

		if (pDataMap->m_strID_Map.IsEmpty())
		{
			pDataMap->m_nIsMapSucc = 1;
			continue;
		}

		//ID_Map中记录的就是界面参数的ID
		pData = (CItemsGenData *)pInterface->FindByID(pDataMap->m_strID_Map);

		if (pData == NULL)
		{
			continue;
		}

		pDataMap->m_nIsMapSucc = 1;
		pDataMap->m_strValue = pData->m_strValue;
	}
}

void CItemsGenParasMap::LogParasMapError(UINT nLogLevel)
{
	POS pos = GetHeadPosition();
	CItemsGenDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CItemsGenDataMap *)GetNext(pos);

		if (pDataMap->m_strID_Map.IsEmpty())
		{
			continue;
		}

		if (pDataMap->m_nIsMapSucc != 1)
		{
			if (nLogLevel == PARAMAP_LOG_LEVEL_INTERFACE)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数映射参数值获取失败，找不到映射参数【id-map == %s】！参数接口中，没有 id == %s 的参数！"),
					pDataMap->m_strID_Map.GetString(), pDataMap->m_strID_Map.GetString());
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数映射参数值获取失败，找不到映射参数【id-map == %s】！界面参数中，没有 id == %s 的参数！"),
					pDataMap->m_strID_Map.GetString(), pDataMap->m_strID_Map.GetString());
			}

			continue;
		}
	}
}

void CItemsGenParasMap::InitParasMapByInterface_Ex(CItemsGenInterface *pInterface)
{
	if (pInterface == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CItemsGenDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CItemsGenDataMap *)GetNext(pos);
		pDataMap->InitParasMapByInterface_Ex(pInterface);
	}
}