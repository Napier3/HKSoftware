//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecfgGenMngr.cpp  CIecfgGenMngr


#include "stdafx.h"
#include "IecfgGenMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecfgGenMngr g_oIecfgGenMngr;

CIecfgGenMngr::CIecfgGenMngr()
{
	//初始化属性

	//初始化成员变量
}

CIecfgGenMngr::~CIecfgGenMngr()
{
}

long CIecfgGenMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecfgGenMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecfgGenMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecfgGenMngr::InitAfterRead()
{
}

BOOL CIecfgGenMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecfgGenMngr *p = (CIecfgGenMngr*)pObj;

	return TRUE;
}

BOOL CIecfgGenMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecfgGenMngr *p = (CIecfgGenMngr*)pDest;

	return TRUE;
}

CBaseObject* CIecfgGenMngr::Clone()
{
	CIecfgGenMngr *p = new CIecfgGenMngr();
	Copy(p);
	return p;
}

CBaseObject* CIecfgGenMngr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecfgGenMngr *p = new CIecfgGenMngr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecfgGenMngr::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CDEVICETYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecfgGenMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDeviceTypeKey)
	{
		pNew = new CDeviceType();
	}

	return pNew;
}

CExBaseObject* CIecfgGenMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CDEVICETYPE)
	{
		pNew = new CDeviceType();
	}

	return pNew;
}
CExBaseObject* CIecfgGenMngr::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CDeviceType();

	return pNew;
}

BOOL CIecfgGenMngr::OpenIecfgGenMnrFile(const CString &strIecfgGenMnrFile)
{
	if (strIecfgGenMnrFile.IsEmpty())
	{
		m_strID = _P_GetConfigPath();
		m_strID += IECFG_GEN_MNGR_FILE_NAME_DEFAULT;

	}
	else
	{
		m_strID = strIecfgGenMnrFile;
	}

	return OpenXmlFile(m_strID,CIecfgGenMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CIecfgGenMngr::Generate(CIecCfgDevice *pIecfgDevice,const CString &strIedName)
{
	CExBaseObject *pCurrObj = NULL;
	CDeviceType *pCurDeivce = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurrObj = GetNext(pos);

		if (strIedName.Find(pCurrObj->m_strID) == 0)
		{
			pCurDeivce = (CDeviceType *)pCurrObj;
			return pCurDeivce->GenerateIecfgDevice(pIecfgDevice);
		}

	}

	return FALSE;
}




