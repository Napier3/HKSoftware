#include "StdAfx.h"
#include "RptData.h"
#include "RptBkmk.h"
#include "../Device.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRptData::CRptData(void)
{
	m_nPrecision = _RPTDATA_PRECISION_INIT;
	m_nDataFill = 0;
}

CRptData::CRptData(const CString  &strName, const CString  &strID, const CString  &strPrecision)
{
	m_strName = strName;
	m_strID = strID;
	SetPrecision(strPrecision);
	m_nDataFill = 0;
}

CRptData::~CRptData(void)
{
	DeleteAll();
}

//新建标签对象,根据特定的规则自动生成IRptBkmk的标签
// CExBaseObject* CRptData::AddNew()
// {
// 	CRptBkmk *pRptBkmk = new CRptBkmk();
// 	ASSERT(pRptBkmk != NULL);
// 	AddTail(pRptBkmk);
// 	pRptBkmk->SetParent(this);
// 	
// 	return pRptBkmk;
// }

CExBaseObject* CRptData::AddNew2(const CString  strRptBkmk)
{
	CRptBkmk *pRptBkmk = new CRptBkmk();
	ASSERT(pRptBkmk != NULL);

	//pRptBkmk->m_strName = strRptBkmk;
	pRptBkmk->m_strID = strRptBkmk;
	pRptBkmk->m_strName = strRptBkmk;
	AddTail(pRptBkmk);
	pRptBkmk->SetParent(this);

	return pRptBkmk;
}

void CRptData::SetPrecision(long nPrecision)
{
	m_nPrecision = nPrecision;
	m_strPrecision.Format(_T("%d"), nPrecision);
}

void CRptData::SetPrecision(const CString &strPrecision)
{
	m_strPrecision = strPrecision;
	m_nPrecision = _RPTDATA_PRECISION_INIT;
}

long CRptData::GetPrecision()
{
	if (m_strPrecision.GetLength() > 0)
	{
		if (IsStringNumber(m_strPrecision))
		{
			m_nPrecision = CString_To_long(m_strPrecision);
		}
		else
		{
			CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
			CDataSet *pSysParas = pDevice->GetTestParas();
			CDataObj *pData = (CDataObj*)pSysParas->FindByID(m_strPrecision);

			if (pData != NULL)
			{
				m_nPrecision = CString_To_long(pData->m_strValue);
			}
		}
	}
	
	return m_nPrecision;
}


//ReadXML && WriteXML
long CRptData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(((CGbXMLKeys *)pXmlRWKeys)->m_strPrecisionKey, oNode, m_strPrecision);

	return 0;
}

CExBaseObject* CRptData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pKeys->m_strBkmkKey)
	{
		return new CRptBkmk();
	}
	else
	{
		return NULL;
	}

}

long CRptData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	
	//if (m_nPrecision != _RPTDATA_PRECISION_INIT)
	//{
		xml_SetAttributeValue(((CGbXMLKeys *)pXmlRWKeys)->m_strPrecisionKey, oElement, m_strPrecision);
	//}
	
	return 0;
}

long CRptData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_nPrecision);
		BinarySerializeCalLen(oBinaryBuffer,m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer,m_nDataFill);
		BinarySerializeCalLen(oBinaryBuffer,m_strPrecision);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer,m_nPrecision);
		BinarySerializeRead(oBinaryBuffer,m_strDataType);
		BinarySerializeRead(oBinaryBuffer,m_nDataFill);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_33)
		{
			BinarySerializeRead(oBinaryBuffer,m_strPrecision);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nPrecision);
		BinarySerializeWrite(oBinaryBuffer,m_strDataType);
		BinarySerializeWrite(oBinaryBuffer,m_nDataFill);
		BinarySerializeWrite(oBinaryBuffer,m_strPrecision);
	}

	return 0;
}

CExBaseObject* CRptData::CreateNewChild(long nClassID)
{
	if(nClassID == RPTCLASSID_RPTBKMK)
	{
		return new CRptBkmk();
	}

	return NULL;
}


CBaseObject* CRptData::Clone()
{
	CRptData *pNew = new CRptData();
	Copy(pNew);
	return pNew;
}


BOOL CRptData::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(this == pDest)
		return TRUE;

	((CRptData*)pDest)->m_nPrecision = m_nPrecision;
	((CRptData*)pDest)->m_strDataType = m_strDataType;
	((CRptData*)pDest)->m_nDataFill = m_nDataFill;
	((CRptData*)pDest)->m_strPrecision = m_strPrecision;

	CExBaseObject::CopyOwn(pDest);

	return TRUE;
}

void CRptData::ClearDWData()
{
	POS pos = GetHeadPosition();
	CRptBkmk *pBkmk = NULL;

	while (pos != NULL)
	{
		pBkmk = (CRptBkmk*)GetNext(pos);
		pBkmk->m_dwItemData = 0;
	}
}

CGbItemBase* CRptData::GetParentItem()
{
	CExBaseObject *pItem = (CExBaseObject*)GetAncestor(GBCLASSID_COMMCMD);

	if (pItem != NULL)
	{
		return (CGbItemBase *)pItem;
	}

	pItem = (CExBaseObject*)GetAncestor(GBCLASSID_SAFETY);

	if (pItem != NULL)
	{
		return (CGbItemBase *)pItem;
	}

	pItem = (CExBaseObject*)GetAncestor(GBCLASSID_MACROTEST);

	if (pItem != NULL)
	{
		return (CGbItemBase *)pItem;
	}

	pItem = (CExBaseObject*)GetAncestor(GBCLASSID_SYSPARAEDIT);

	if (pItem != NULL)
	{
		return (CGbItemBase *)pItem;
	}

	pItem = (CExBaseObject*)GetAncestor(GBCLASSID_ITEMS);

	if (pItem != NULL)
	{
		return (CGbItemBase *)pItem;
	}

	return NULL;
}
