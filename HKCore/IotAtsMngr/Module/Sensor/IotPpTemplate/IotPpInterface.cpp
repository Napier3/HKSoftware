//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpInterface.cpp  CIotPpInterface


#include "stdafx.h"
#include "IotPpInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpInterface::CIotPpInterface()
{
	//初始化属性

	//初始化成员变量
}

CIotPpInterface::~CIotPpInterface()
{
}

long CIotPpInterface::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpInterface::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpInterface::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIotPpInterface::InitAfterRead()
{
}

BOOL CIotPpInterface::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpInterface *p = (CIotPpInterface*)pObj;

	return TRUE;
}

BOOL CIotPpInterface::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpInterface *p = (CIotPpInterface*)pDest;

	return TRUE;
}

CBaseObject* CIotPpInterface::Clone()
{
	CIotPpInterface *p = new CIotPpInterface();
	Copy(p);
	return p;
}

CBaseObject* CIotPpInterface::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpInterface *p = new CIotPpInterface();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpInterface::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpInterface::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpValueKey)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}

CExBaseObject* CIotPpInterface::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}

void CIotPpInterface::UpdateInterfaceValue(CExBaseList *pSrcInterface)
{
	if (pSrcInterface == NULL)
	{
		return;
	}

	POS pos = pSrcInterface->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CIotPpValue *pDstValue = NULL;

	while(pos != NULL)
	{
		pValue = (CDvmValue *)pSrcInterface->GetNext(pos);

		pDstValue = (CIotPpValue *)FindByID(pValue->m_strID);
		if (pDstValue != NULL)
		{
			pDstValue->m_strValue = pValue->m_strValue;
		}
	}
}

void CIotPpInterface::UpdateValueByDataset(CDvmDataset *pSrcDataset)
{
	if (pSrcDataset == NULL)
	{
		return;
	}

	POS pos = pSrcDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CIotPpValue *pDstValue = NULL;

	while(pos != NULL)
	{
		pData = (CDvmData *)pSrcDataset->GetNext(pos);

		pDstValue = (CIotPpValue *)FindByID(pData->m_strID);
		if (pDstValue != NULL)
		{
			pDstValue->m_strValue = pData->m_strValue;
		}
	}
}

BOOL CIotPpInterface::GetValueByID(const CString &strID,CString &strValue)
{
	CIotPpValue *pFind = (CIotPpValue *)FindByID(strID);
	if (pFind == NULL)
	{
		return FALSE;
	}

	strValue = pFind->m_strValue;

	return TRUE;
}

BOOL CIotPpInterface::GetValueByID(const CString &strID,long &nValue)
{
	CString strValue = _T("");
	BOOL bRet = GetValueByID(strID,strValue);

	if (bRet)
	{
		nValue = CString_To_long(strValue);
	}

	return bRet;
}