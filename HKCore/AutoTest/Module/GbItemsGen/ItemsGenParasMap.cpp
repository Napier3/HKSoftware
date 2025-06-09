//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	//��ʼ������

	//��ʼ����Ա����
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

//���ݽ����������ʼ������ӳ���ֵ
//shaolei 2025-4-2 ���õ��˴�ʱ����ȷ���β�pUIParas�У��Ѿ��Ǹ���groupǶ�׹�ϵ����data��·����Ϣ��ֵ��step������
//���β�pUIParas�д�ŵ����ݣ�ֻ��CDvmDataһ������
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

		//ID_Map�м�¼�ľ��ǽ��������ID�������ǽ������ID�ı��ʽ
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
			//format����¼���Ǳ��ʽ�����磺�����Ķ�ֵ��������ֵ�ı��ʽ����0.7*setting��
			//format�������Ǽ�¼�Ĺ�����ϵͳ���������磺NormVol��NormCur��ZeroVol��ZeroCur
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

		if (pData->m_strStep == strIDPath)  //step���Լ�¼����·����Ϣ
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

//���뵽�ú���ʱ��Interface�еĲ���ֵ���Ѿ�ͨ�����������ֵ��
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

		//�˴��Ѿ�ӳ����ģ�����ֱ������  shaolei 20220407
		//��Ϊͨ��Interface����ӳ�䣬�Ǹ��ݲ�ͬʵ������Interface�µ�����ӳ���para-map
		//ӳ�������para-map�е�ֵ�������ڵ�������Ŀ�Ĳ���
// 		if (pDataMap->m_nIsMapSucc == 1)
// 		{
// 			//˵���Ѿ�ͨ��������������й�һ��ӳ����
// 			continue;
// 		}
		pDataMap->m_nIsMapSucc = 0;

		if (pDataMap->m_strID_Map.IsEmpty())
		{
			pDataMap->m_nIsMapSucc = 1;
			continue;
		}

		//ID_Map�м�¼�ľ��ǽ��������ID
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
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ӳ�����ֵ��ȡʧ�ܣ��Ҳ���ӳ�������id-map == %s���������ӿ��У�û�� id == %s �Ĳ�����"),
					pDataMap->m_strID_Map.GetString(), pDataMap->m_strID_Map.GetString());
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����ӳ�����ֵ��ȡʧ�ܣ��Ҳ���ӳ�������id-map == %s������������У�û�� id == %s �Ĳ�����"),
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