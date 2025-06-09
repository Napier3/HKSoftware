//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RTDeviceHisDataTitles.cpp  CIot_RTDeviceHisDataTitles


#include "stdafx.h"
#include "Iot_RTDeviceHisDataTitles.h"
#include "Iot_RTDeviceHisData.h"
#include "..\..\..\Module\DataMngr\DvmData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RTDeviceHisDataTitles::CIot_RTDeviceHisDataTitles()
{
	//初始化属性

	//初始化成员变量
}

CIot_RTDeviceHisDataTitles::~CIot_RTDeviceHisDataTitles()
{
}

long CIot_RTDeviceHisDataTitles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RTDeviceHisDataTitles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_RTDeviceHisDataTitles::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_RTDeviceHisDataTitles::InitAfterRead()
{
}

BOOL CIot_RTDeviceHisDataTitles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RTDeviceHisDataTitles *p = (CIot_RTDeviceHisDataTitles*)pObj;

	return TRUE;
}

BOOL CIot_RTDeviceHisDataTitles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RTDeviceHisDataTitles *p = (CIot_RTDeviceHisDataTitles*)pDest;

	return TRUE;
}

CBaseObject* CIot_RTDeviceHisDataTitles::Clone()
{
	CIot_RTDeviceHisDataTitles *p = new CIot_RTDeviceHisDataTitles();
	Copy(p);
	return p;
}

CBaseObject* CIot_RTDeviceHisDataTitles::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RTDeviceHisDataTitles *p = new CIot_RTDeviceHisDataTitles();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_RTDeviceHisDataTitles::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_RTDEVICEHISDATATITLE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_RTDeviceHisDataTitles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RTDeviceHisDataTitleKey)
	{
		pNew = new CIot_RTDeviceHisDataTitle();
	}

	return pNew;
}

CExBaseObject* CIot_RTDeviceHisDataTitles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_RTDEVICEHISDATATITLE)
	{
		pNew = new CIot_RTDeviceHisDataTitle();
	}

	return pNew;
}

CExBaseObject* CIot_RTDeviceHisDataTitles::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_RTDeviceHisDataTitle();

	return pNew;
}

BOOL CIot_RTDeviceHisDataTitles::QueryRTDeviceHisDataTitlesByDeviceType(CXDbBaseLib *pXDbLib,long nIndex_DeviceType)
{
	CString strRTDeviceHisDataTitleTable;
	CString strIndex_Device_Type, strSql;

	strRTDeviceHisDataTitleTable = CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitleKey();
	strIndex_Device_Type = CIot_AtsMngrXmlRWKeys::Index_Device_TypeKey();

	strSql.Format(_T("select * from %s where %s=%d"),
		strRTDeviceHisDataTitleTable, strIndex_Device_Type, nIndex_DeviceType);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_RTDeviceHisDataTitles::InsertRtDeviceHisData(CXDbBaseLib *pXDbLib, const CString &strDeviceSN, CExBaseList *pParas)
{
	CIot_RTDeviceHisDataTitle *pDataTitle = NULL;
	CIot_RTDeviceHisData oHisData;
	oHisData.m_strSn = strDeviceSN;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDataTitle = (CIot_RTDeviceHisDataTitle *)GetNext(pos);
		CDvmData *pData = (CDvmData *)pParas->FindByID(pDataTitle->m_strDataID);

		if (pData != NULL)
		{
			oHisData.UpdateValue(pDataTitle->m_strData, pData->m_strValue);
		}
	}

	::GetLocalTime(&oHisData.m_tmTm_Update);
	return oHisData.DB_Insert(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}
