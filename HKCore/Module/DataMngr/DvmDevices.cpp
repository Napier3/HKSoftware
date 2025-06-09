//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDevices.cpp  CDvmDevices


#include "stdafx.h"
#include "DvmDevices.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDvmDevices::CDvmDevices()
{
	//初始化属性

	m_strName = _T("device-models");
	//初始化成员变量

}

CDvmDevices::~CDvmDevices()
{
	int i = 0;
}

long CDvmDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmDevices::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CDvmDevices::Serialize(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::Serialize(oBinaryBuffer);

	return 0;
}

long CDvmDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CDvmDevices::InitAfterRead()
{

}

BOOL CDvmDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmDevices *p = (CDvmDevices*)pObj;

	return TRUE;
}

BOOL CDvmDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmDevices *p = (CDvmDevices*)pDest;

	return TRUE;
}

CBaseObject* CDvmDevices::Clone()
{
	CDvmDevices *p = new CDvmDevices();
	Copy(p);
	return p;
}

BOOL CDvmDevices::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDvmDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDeviceKey)
	{
		pNew = new CDvmDevice();
		return pNew;
	}

	if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
		return pNew;
	}

	return pNew;
}

CExBaseObject* CDvmDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMDEVICE)
	{
		pNew = new CDvmDevice();
	}

	return pNew;
}
 
 CDvmDevice* CDvmDevices::FindByIndex(long nIndex)
 {
 	CDvmDevice *p = NULL;
 	CDvmDevice *pFind = NULL;
 	POS pos = GetHeadPosition();
 
 	while (pos != NULL)
 	{
 		p = (CDvmDevice *)GetNext(pos);
 
 		if (p->GetIndex() == nIndex)
 		{
 			pFind = p;
 			break;
 		}
 	}
 
 	return pFind;
 }


 CDvmDevice* CDvmDevices::AddNewDevice(CDvmDevice *pSrc)
 {
	 CDvmDevice *pData = NULL;

	 if (pSrc != NULL)
	 {
		 pData = (CDvmDevice *)pSrc->Clone();
	 }
	 else
	 {
		 pData = new CDvmDevice();
	 }

	 AddNewChild(pData);

	 return pData;
 }
