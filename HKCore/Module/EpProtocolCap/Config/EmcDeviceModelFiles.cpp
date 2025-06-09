//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcDeviceModelFiles.cpp  CEmcDeviceModelFiles


#include "stdafx.h"
#include "EmcDeviceModelFiles.h"

CEmcDeviceModelFiles::CEmcDeviceModelFiles()
{
	//初始化属性
	m_strName = _T("点表文件管理");
	m_strID = _T("EmcDeviceModelFiles");

	//初始化成员变量
}

CEmcDeviceModelFiles::~CEmcDeviceModelFiles()
{
}

long CEmcDeviceModelFiles::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcDeviceModelFiles::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcDeviceModelFiles::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEmcDeviceModelFiles::InitAfterRead()
{
}

BOOL CEmcDeviceModelFiles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcDeviceModelFiles *p = (CEmcDeviceModelFiles*)pObj;

	return TRUE;
}

BOOL CEmcDeviceModelFiles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcDeviceModelFiles *p = (CEmcDeviceModelFiles*)pDest;

	return TRUE;
}

CBaseObject* CEmcDeviceModelFiles::Clone()
{
	CEmcDeviceModelFiles *p = new CEmcDeviceModelFiles();
	Copy(p);
	return p;
}

BOOL CEmcDeviceModelFiles::CanPaste(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCDEVICEMODELFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEmcDeviceModelFiles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcDeviceModelFileKey)
	{
		pNew = new CEmcDeviceModelFile();
	}

	return pNew;
}

CExBaseObject* CEmcDeviceModelFiles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCDEVICEMODELFILE)
	{
		pNew = new CEmcDeviceModelFile();
	}

	return pNew;
}
