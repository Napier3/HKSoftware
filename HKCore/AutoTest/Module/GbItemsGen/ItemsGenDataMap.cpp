//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenDataMap.cpp  CItemsGenDataMap


#include "stdafx.h"
#include "ItemsGenDataMap.h"
#include "ItemsGenData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenDataMap::CItemsGenDataMap()
{
	//��ʼ������

	//��ʼ����Ա����
	m_nIsMapSucc = 0;
	m_nKeepExpr = 0;
}

CItemsGenDataMap::~CItemsGenDataMap()
{
}

long CItemsGenDataMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strId_MapKey, oNode, m_strID_Map);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strKeepExprKey, oNode, m_nKeepExpr);
	return 0;
}

long CItemsGenDataMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strId_MapKey, oElement, m_strID_Map);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strKeepExprKey, oElement, m_nKeepExpr);
	return 0;
}

long CItemsGenDataMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID_Map);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_nKeepExpr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID_Map);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_nKeepExpr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID_Map);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_nKeepExpr);
	}
	return 0;
}

void CItemsGenDataMap::InitAfterRead()
{
}

BOOL CItemsGenDataMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenDataMap *p = (CItemsGenDataMap*)pObj;

	if(m_strID_Map != p->m_strID_Map)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_nKeepExpr != p->m_nKeepExpr)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CItemsGenDataMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CItemsGenDataMap *p = (CItemsGenDataMap*)pDest;

	p->m_strID_Map = m_strID_Map;
	p->m_strValue = m_strValue;
	p->m_nKeepExpr = m_nKeepExpr;
	return TRUE;
}

CBaseObject* CItemsGenDataMap::Clone()
{
	CItemsGenDataMap *p = new CItemsGenDataMap();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenDataMap::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenDataMap *p = new CItemsGenDataMap();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenDataMap::GetValue_String(CString &strValue, CDataGroup *pDataGroup)
{
	if (m_strID_Map.IsEmpty())
	{
		strValue = m_strValue;
		return TRUE;
	}

	CDvmData *pData = (CDvmData *)pDataGroup->FindByID(m_strID_Map);

	if (pData == NULL)
	{
		return FALSE;
	}

	strValue = pData->m_strValue;
	return TRUE;
}

BOOL CItemsGenDataMap::GetValue_Long(long &nValue, CDataGroup *pDataGroup)
{
	if (m_strID_Map.IsEmpty())
	{
		//û������ӳ��ģ�ֱ�ӷ���FALSE��Ӧ����ΪCString���Ͳ�ѯ��������ƴ����Ŀ����ʱ���Ͳ���ȷ
		return FALSE;
	}

	CDvmData *pData = (CDvmData *)pDataGroup->FindByID(m_strID_Map);

	if (pData == NULL)
	{
		return FALSE;
	}

	if (pData->m_strDataType != _T("long"))
	{
		return FALSE;
	}

	nValue = CString_To_long(pData->m_strValue);
	return TRUE;
}

BOOL CItemsGenDataMap::GetValue_Float(float &fValue, CDataGroup *pDataGroup)
{
	if (m_strID_Map.IsEmpty())
	{
		//û������ӳ��ģ�ֱ�ӷ���FALSE��Ӧ����ΪCString���Ͳ�ѯ��������ƴ����Ŀ����ʱ���Ͳ���ȷ
		return FALSE;
	}

	CDvmData *pData = (CDvmData *)pDataGroup->FindByID(m_strID_Map);

	if (pData == NULL)
	{
		return FALSE;
	}

	if (pData->m_strDataType != _T("float"))
	{
		return FALSE;
	}

	fValue = CString_To_double(pData->m_strValue);
	return TRUE;
}

BOOL CItemsGenDataMap::InitParaByExpression(CDataGroup *pUIParas)
{
	if (pUIParas == NULL)
	{
		return FALSE;
	}

	if (m_strID_Map.IsEmpty())
	{
		return FALSE;
	}

	CEpExpression oEpEpr;

	if (oEpEpr.ChangeEpExpression(m_strID_Map) == -1)
	{
		return FALSE;
	}

	return InitParaByExpression(&oEpEpr, pUIParas);
}

BOOL CItemsGenDataMap::InitParaByExpression(CEpExpression *pEpEpr, CDataGroup *pUIParas)
{
	if (pEpEpr == NULL || pUIParas == NULL)
	{
		return FALSE;
	}

	POS pos = pEpEpr->GetHeadPosition();

	while (pos != NULL)
	{
		CEpExpVariable *pEpVar = (CEpExpVariable *)pEpEpr->GetNext(pos);
		CDvmData *pData = (CDvmData *)pUIParas->FindByID(pEpVar->m_strVarID);

		if (pData == NULL)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("<<<<<<<<<<<<���ʽ����<<<<  %s  <<<<��������Ҳ���id = %s �Ĳ���"), m_strID_Map.GetString(), pEpVar->m_strVarID.GetString());
			return FALSE;
		}

#ifdef _UNICODE
		pEpVar->m_dValue = _wtof(pData->m_strValue);
#else
		pEpVar->m_dValue = atof(pData->m_strValue.GetString());
#endif
	}

	double dValue = 0.0;
	pEpEpr->Value(dValue);
	m_strValue.Format(_T("%.3f"), dValue);
	m_nIsMapSucc = 1;

	return TRUE;
}

BOOL CItemsGenDataMap::InitParasMapByInterface_Ex(CExBaseList *pInterface)
{
	if (pInterface == NULL)
	{
		return FALSE;
	}

	POS pos = pInterface->GetHeadPosition();
	BOOL bRet = FALSE;
	CItemsGenParasMap *pParasMap = (CItemsGenParasMap *)GetParent();

	while (pos != NULL)
	{
		CItemsGenData *pData = (CItemsGenData *)pInterface->GetNext(pos);

		//shaolei 2023-11-14 �˴��޸�Ϊ���ʽ����
		//����ӳ���ֵ�������ӿڲ�����ID�����ýӿڲ�����Vaule�����滻��Ӧ��ID
// 		if (m_strValue.Find(pData->m_strID) >= 0)
// 		{
// 			m_strValue.Replace(pData->m_strID, pData->m_strValue);
// 			m_nIsMapSucc = TRUE;
// 			bRet = TRUE;
// 		}

		//�ȴ���ȫƥ��
		if (m_strValue == pData->m_strID)
		{
			m_strValue = pData->m_strValue;
			m_nIsMapSucc = TRUE;
			bRet = TRUE;
			break;
		}
	}

	if (bRet)
	{
		return bRet;
	}

	//���Ҳ���ȫƥ��Ľӿڲ��������ձ��ʽ����
	CEpExpression oEpEpr;

	if (oEpEpr.ChangeEpExpression(m_strValue) == -1)
	{
		return FALSE;
	}

	//���ǲ��������ʽ
	if (!m_nKeepExpr)
	{
		POS posEpr = oEpEpr.GetHeadPosition();
		CString strValue;

		while (posEpr != NULL)
		{
			CEpExpVariable *pEpVar = (CEpExpVariable *)oEpEpr.GetNext(posEpr);

			//shaolei 2025-3-25������Rate�����ݣ������ȴ��Ѿ��ӽ���ӳ�������data-map�л�ȡ
			//���磺<data-map id="state1$I4$mag" id-map="" value="ISetting_Zone*Rate"/>
			//Rate�Ǹ��ݲ�ͬinst��ģ����ܴ�interface��ֱ��ӳ������������ͬ��inst�ǲ�ͬ�Ľ��������
			CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pParasMap->FindByID(pEpVar->m_strVarID);
			CItemsGenData *pData = NULL;

			if (pDataMap != NULL)
			{
				strValue = pDataMap->m_strValue;
			}
			else
			{
				pData = (CItemsGenData *)pInterface->FindByID(pEpVar->m_strVarID);

				if (pData != NULL)
				{
					strValue = pData->m_strValue;
				}
			}

			if (pData == NULL && pDataMap == NULL)
			{
				return FALSE;
			}
			
#ifdef _UNICODE
			pEpVar->m_dValue = _wtof(strValue);
#else
			pEpVar->m_dValue = atof(strValue.GetString());
#endif
		}

		double dValue = 0.0;
		oEpEpr.Value(dValue);
		m_strValue.Format(_T("%.6f"), dValue);
		bRet = TRUE;
		m_nIsMapSucc = TRUE;

		return bRet;
	}
	else
	{
		//��Ҫ�������ʽ
		POS posEpr = oEpEpr.GetHeadPosition();

		while (posEpr != NULL)
		{
			CEpExpVariable *pEpVar = (CEpExpVariable *)oEpEpr.GetNext(posEpr);
			CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(pEpVar->m_strVarID);

			if (pData == NULL)
			{
				return FALSE;
			}

			//�˴�����������bug��
			//1���滻ʱ������һ�����滻��������
			//2����һ���滻���ܸ���ǰһ�ε�
			m_strValue.Replace(pEpVar->m_strVarID, pData->m_strValue);
		}

		bRet = TRUE;
		m_nIsMapSucc = TRUE;

		return bRet;
	}
}

BOOL CItemsGenDataMap::InitParaByInterface_Expression(CExBaseList *pInterface)
{
	if (pInterface == NULL)
	{
		return FALSE;
	}

	if (m_strID_Map.IsEmpty())
	{
		return FALSE;
	}

	CEpExpression oEpEpr;

	if (oEpEpr.ChangeEpExpression(m_strID_Map) == -1)
	{
		return FALSE;
	}

	return InitParaByInterface_Expression(&oEpEpr, pInterface);
}

BOOL CItemsGenDataMap::InitParaByInterface_Expression(CEpExpression *pEpEpr, CExBaseList *pInterface)
{
	if (pEpEpr == NULL || pInterface == NULL)
	{
		return FALSE;
	}

	POS pos = pEpEpr->GetHeadPosition();

	while (pos != NULL)
	{
		CEpExpVariable *pEpVar = (CEpExpVariable *)pEpEpr->GetNext(pos);
		CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(pEpVar->m_strVarID);

		if (pData == NULL)
		{
			return FALSE;
		}

#ifdef _UNICODE
		pEpVar->m_dValue = _wtof(pData->m_strValue);
#else
		pEpVar->m_dValue = atof(pData->m_strValue.GetString());
#endif
	}

	double dValue = 0.0;
	pEpEpr->Value(dValue);
	m_strValue.Format(_T("%.3f"), dValue);

	return TRUE;
}

//�������ڸ�ͨѶ�������ɽڵ㣬���ͨѶ����ʹ�ã���interfaceӳ��
CItemsGenDataset::CItemsGenDataset()
{
	//��ʼ������
}

CItemsGenDataset::~CItemsGenDataset()
{
}

BOOL CItemsGenDataset::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CItemsGenDataMap::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenDataset::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenDataMap::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CItemsGenDataset::Clone()
{
	CItemsGenDataset *p = new CItemsGenDataset();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenDataset::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenDataset *p = new CItemsGenDataset();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}