//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenNameAdd.cpp  CItemsGenNameAdd


#include "stdafx.h"
#include "ItemsGenNameAdd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenNameAdd::CItemsGenNameAdd()
{
	//��ʼ������

	//��ʼ����Ա����
}

CItemsGenNameAdd::~CItemsGenNameAdd()
{
}

long CItemsGenNameAdd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);  //2022-3-11  shaolei
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	//xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	return 0;
}

long CItemsGenNameAdd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);  //2022-3-11  lijunqing
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	//xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	return 0;
}

long CItemsGenNameAdd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strText);
	}
	return 0;
}

void CItemsGenNameAdd::InitAfterRead()
{
}

BOOL CItemsGenNameAdd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseList::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenNameAdd *p = (CItemsGenNameAdd*)pObj;

// 	if(m_strText != p->m_strText)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

BOOL CItemsGenNameAdd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);
	CItemsGenNameAdd *p = (CItemsGenNameAdd*)pDest;

	//p->m_strText = m_strText;
	return TRUE;
}

CBaseObject* CItemsGenNameAdd::Clone()
{
	CItemsGenNameAdd *p = new CItemsGenNameAdd();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenNameAdd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenNameAdd *p = new CItemsGenNameAdd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenNameAdd::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEITEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenNameAdd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenNameItemKey)
	{
		pNew = new CItemsGenNameItem();
	}

	return pNew;
}

CExBaseObject* CItemsGenNameAdd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEITEM)
	{
		pNew = new CItemsGenNameItem();
	}

	return pNew;
}

CString CItemsGenNameAdd::GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	if (pParasMap == NULL)
	{
		return m_strName;
	}

	CString strText = m_strName;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CItemsGenNameItem *pNameItem = (CItemsGenNameItem *)GetNext(pos);
		CItemsGenDataMap *pData = (CItemsGenDataMap *)pParasMap->FindByID(pNameItem->m_strID_Data);

		if (pData == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("ƴ��NameAdd�ֶΣ��Ҳ�����Ӧ������%s��"), pNameItem->m_strID_Data.GetString());
			continue;
		}

		//�˴�ƴ�Ӳ�����Ŀ�����ƣ���Ϊ��֪����Ӧ�������������ͣ��ֱ����Long Float���л�ȡ������������ƥ��ʱ������ΪTRUE��
		//���򣬵����ַ�������
		strText = pNameItem->m_strNameHead + strText;

		if (pDataGroup == NULL)
		{
			strText += pNameItem->m_strNameTail;
			continue;
		}

		long nValue = 0;
		BOOL bRet = pData->GetValue_Long(nValue, pDataGroup);

		if (bRet)
		{
			strText.AppendFormat(pNameItem->m_strFormat, nValue);
		}
		else
		{
			float fValue = 1.0;
			bRet = pData->GetValue_Float(fValue, pDataGroup);

			if (bRet)
			{
				strText.AppendFormat(pNameItem->m_strFormat, fValue);
			}
			else
			{
				CString strValue;
				pData->GetValue_String(strValue, pDataGroup);
                strText.AppendFormat(_T("%s"), strValue.GetString());
			}
		}

		strText += pNameItem->m_strNameTail;
	}

	return strText;
}

CString CItemsGenNameAdd::GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	if (pParasMap == NULL)
	{
		return m_strID;
	}

	CString strText = m_strID;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CItemsGenNameItem *pNameItem = (CItemsGenNameItem *)GetNext(pos);
		CItemsGenDataMap *pData = (CItemsGenDataMap *)pParasMap->FindByID(pNameItem->m_strID_Data);

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("ƴ��NameAdd�ֶΣ��Ҳ�����Ӧ������%s��"), pNameItem->m_strID_Data.GetString());
			continue;
		}

		//�˴�ƴ�Ӳ�����Ŀ�����ƣ���Ϊ��֪����Ӧ�������������ͣ��ֱ����Long Float���л�ȡ������������ƥ��ʱ������ΪTRUE��
		//���򣬵����ַ�������
		strText = pNameItem->m_strIDHead + strText;

		if (pDataGroup == NULL)
		{
			strText += pNameItem->m_strIDTail;
			continue;
		}

		long nValue = 0;
		BOOL bRet = pData->GetValue_Long(nValue, pDataGroup);

		if (bRet)
		{
			strText.AppendFormat(pNameItem->m_strFormat, nValue);
		}
		else
		{
			float fValue = 1.0;
			bRet = pData->GetValue_Float(fValue, pDataGroup);

			if (bRet)
			{
				strText.AppendFormat(pNameItem->m_strFormat, fValue);
			}
			else
			{
				CString strValue;
				pData->GetValue_String(strValue, pDataGroup);
				strText.AppendFormat(_T("%s"), strValue.GetString());
			}
		}

		strText += pNameItem->m_strIDTail;
	}

	return strText;
}
