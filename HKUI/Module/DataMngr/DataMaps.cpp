//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataMaps.cpp  CDataMaps


#include "stdafx.h"
#include "DataMaps.h"

CDataMaps::CDataMaps()
{
	//初始化属性

	//初始化成员变量
}

CDataMaps::~CDataMaps()
{
}

long CDataMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	return 0;
}

long CDataMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	return 0;
}

long CDataMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}
	return 0;
}

void CDataMaps::InitAfterRead()
{
}

BOOL CDataMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDataMaps *p = (CDataMaps*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDataMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataMaps *p = (CDataMaps*)pDest;

	p->m_strDataType = m_strDataType;
	return TRUE;
}

CBaseObject* CDataMaps::Clone()
{
	CDataMaps *p = new CDataMaps();
	Copy(p);
	return p;
}

BOOL CDataMaps::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CDataMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXDataMapKey)
	{
		pNew = new CXDataMap();
	}

	return pNew;
}

CExBaseObject* CDataMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DTMCLASSID_CXDATAMAP)
	{
		pNew = new CXDataMap();
	}

	return pNew;
}

CXDataMap *CDataMaps::FindAddressChild(CVariantDataAddress oVarDataAddr, bool bDel)
{
	CString strSrcAdd,strDesAdd;
	POS pos = GetHeadPosition();
	while(pos)
	{
		CXDataMap *pObj = (CXDataMap *)GetNext(pos);
		if(pObj != NULL)
		{
			if (pObj->m_varDataAddr.vt == oVarDataAddr.vt)
			{
				strSrcAdd.Format("%p", pObj->m_varDataAddr.fltVal); 
				strDesAdd.Format("%p", oVarDataAddr.fltVal);

				if(strSrcAdd == strDesAdd)
				{
					if(bDel)
					{
						Delete(pObj);
						return NULL;
					}
					return pObj;
				}
			}
		}
	}
	return NULL;
}
CXDataMap *CDataMaps::AddAddressChild(CVariantDataAddress oVarDataAddr)
{
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
	{
		pObject = new CXDataMap();
		pObject->m_strID.Format("CXDataMap-%d",GetCount());
		pObject->m_varDataAddr = oVarDataAddr;
		AddTail(pObject);
	}
	return pObject;
}

void CDataMaps::AddAddressChild(const CString &strFormat, CString &strAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&strAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, short &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, long &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, int &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, unsigned int &unAttrVal)
{
	//CVariantDataAddress oVarDataAddr = CVariantDataAddress(&unAttrVal);
	//CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	//pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, double &dAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&dAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, float &fAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&fAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, char *strAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(strAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}
void CDataMaps::AddAddressChild(const CString &strFormat, bool &bAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&bAttrVal);
	CXDataMap * pObject = AddAddressChild(oVarDataAddr);
	pObject->m_strMapID = strFormat;
}

CString CDataMaps::GetAddressFormat(CString &strAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&strAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(short &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(long &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(int &nAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&nAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(unsigned int &unAttrVal)
{
	//CVariantDataAddress oVarDataAddr = CVariantDataAddress(&unAttrVal);
	//CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	//if(pObject == NULL)
	//	return "";
	//return pObject->m_strMapID;
	return "";
}
CString CDataMaps::GetAddressFormat(double &dAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&dAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(float &fAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&fAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}
CString CDataMaps::GetAddressFormat(char *strAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(strAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if(pObject == NULL)
		return "";
	return pObject->m_strMapID;
}CString CDataMaps::GetAddressFormat(bool &bAttrVal)
{
	CVariantDataAddress oVarDataAddr = CVariantDataAddress(&bAttrVal);
	CXDataMap * pObject = FindAddressChild(oVarDataAddr);
	if (pObject == NULL)
		return "";
	return pObject->m_strMapID;
}