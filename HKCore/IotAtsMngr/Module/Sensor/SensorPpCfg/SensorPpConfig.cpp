//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SensorPpConfig.cpp  CSensorPpConfig


#include "stdafx.h"
#include "SensorPpConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSensorPpConfig::CSensorPpConfig()
{
	//初始化属性

	//初始化成员变量
}

CSensorPpConfig::~CSensorPpConfig()
{
}

BOOL CSensorPpConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSensorPpConfig *p = (CSensorPpConfig*)pObj;

	return TRUE;
}

BOOL CSensorPpConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSensorPpConfig *p = (CSensorPpConfig*)pDest;

	return TRUE;
}

CBaseObject* CSensorPpConfig::Clone()
{
	CSensorPpConfig *p = new CSensorPpConfig();
	Copy(p);
	return p;
}

CBaseObject* CSensorPpConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSensorPpConfig *p = new CSensorPpConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSensorPpConfig::CanPaste(UINT nClassID)
{
	if (nClassID == PPCFGCLASSID_CSENSORPPDEVICETYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSensorPpConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPpCfgXmlRWKeys *pXmlKeys = (CPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSensorPpDeviceTypeKey)
	{
		pNew = new CSensorPpDeviceType();
	}

	return pNew;
}

CExBaseObject* CSensorPpConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == PPCFGCLASSID_CSENSORPPDEVICETYPE)
	{
		pNew = new CSensorPpDeviceType();
	}

	return pNew;
}

void CSensorPpConfig::GetNeedSubcribeTopic(CExBaseList &oList)
{
	oList.RemoveAll();

	POS pos = GetHeadPosition();
	CSensorPpDeviceType *p = NULL;

	while(pos != NULL)
	{
		p = (CSensorPpDeviceType *)GetNext(pos);

		p->GetNeedSubcribeTopic(oList);
	}
}

void CSensorPpConfig::GetWillPublicTopic(CDvmData &oList)
{
	oList.RemoveAll();

	POS pos = GetHeadPosition();
	CSensorPpDeviceType *p = NULL;

	while(pos != NULL)
	{
		p = (CSensorPpDeviceType *)GetNext(pos);

		p->GetWillPublicTopic(oList);
	}
}