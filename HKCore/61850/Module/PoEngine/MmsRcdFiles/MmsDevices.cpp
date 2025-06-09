//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsDevices.cpp  CMmsDevices


#include "stdafx.h"
#include "MmsDevices.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CMmsDevices::CMmsDevices()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("MMS-Devices");
	m_strID = _T("MMS-Devices");
}

CMmsDevices::~CMmsDevices()
{
}

long CMmsDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMmsDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMmsDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMmsDevices::InitAfterRead()
{
}

BOOL CMmsDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMmsDevices *p = (CMmsDevices*)pObj;

	return TRUE;
}

BOOL CMmsDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMmsDevices *p = (CMmsDevices*)pDest;

	return TRUE;
}

CBaseObject* CMmsDevices::Clone()
{
	CMmsDevices *p = new CMmsDevices();
	Copy(p);
	return p;
}

BOOL CMmsDevices::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CMMSDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMmsDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMmsRcdFilesMngrXmlRWKeys *pXmlKeys = (CMmsRcdFilesMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMmsDeviceKey)
	{
		pNew = new CMmsDevice();
	}

	return pNew;
}

CExBaseObject* CMmsDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CMMSDEVICE)
	{
		pNew = new CMmsDevice();
	}

	return pNew;
}

BOOL CMmsDevices::OpenMmsDevicesCfgFile()
{
	CString strMmsDevsSavePath;
	strMmsDevsSavePath = _P_GetConfigPath();
	strMmsDevsSavePath += _T("MmsRcdFiles.xml");
	return OpenXmlFile(strMmsDevsSavePath ,CMmsRcdFilesMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CMmsDevices::SaveMmsDevicesCfgFile()
{
	CString strMmsDevsSavePath;
	strMmsDevsSavePath = _P_GetConfigPath();
	strMmsDevsSavePath += _T("MmsRcdFiles.xml");
	return SaveXmlFile(strMmsDevsSavePath ,CMmsRcdFilesMngrXmlRWKeys::g_pXmlKeys);
}

