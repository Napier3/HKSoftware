//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SensorPpDeviceType.cpp  CSensorPpDeviceType


#include "stdafx.h"
#include "SensorPpDeviceType.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSensorPpDeviceType::CSensorPpDeviceType()
{
	//初始化属性

	//初始化成员变量
}

CSensorPpDeviceType::~CSensorPpDeviceType()
{
}

BOOL CSensorPpDeviceType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSensorPpDeviceType *p = (CSensorPpDeviceType*)pObj;

	return TRUE;
}

BOOL CSensorPpDeviceType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSensorPpDeviceType *p = (CSensorPpDeviceType*)pDest;

	return TRUE;
}

CBaseObject* CSensorPpDeviceType::Clone()
{
	CSensorPpDeviceType *p = new CSensorPpDeviceType();
	Copy(p);
	return p;
}

CBaseObject* CSensorPpDeviceType::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSensorPpDeviceType *p = new CSensorPpDeviceType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSensorPpDeviceType::CanPaste(UINT nClassID)
{
	if (nClassID == PPCFGCLASSID_CSENSORPPPRASE)
	{
		return TRUE;
	}

	if (nClassID == PPCFGCLASSID_CSENSORPPPRODUCE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSensorPpDeviceType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPpCfgXmlRWKeys *pXmlKeys = (CPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSensorPpPraseKey)
	{
		pNew = new CSensorPpPrase();
	}
	else if (strClassID == pXmlKeys->m_strCSensorPpProduceKey)
	{
		pNew = new CSensorPpProduce();
	}

	return pNew;
}

CExBaseObject* CSensorPpDeviceType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == PPCFGCLASSID_CSENSORPPPRASE)
	{
		pNew = new CSensorPpPrase();
	}
	else if (nClassID == PPCFGCLASSID_CSENSORPPPRODUCE)
	{
		pNew = new CSensorPpProduce();
	}

	return pNew;
}

void CSensorPpDeviceType::GetNeedSubcribeTopic(CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CDvmDataset *p = NULL;

	while(pos != NULL)
	{
		p = (CDvmDataset *)GetNext(pos);

		if (p->GetClassID() != PPCFGCLASSID_CSENSORPPPRASE)
		{
			continue;
		}

		if (p->m_strID.Right(4) != ("_Ack"))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("传感器协议配置解析节点【%s】命名不合法"),p->m_strID);
			continue;
		}

		if (p->m_strID == _T("Monitor_Ack"))
		{
			continue;
		}

		if (oList.FindByID(p->m_strID) != NULL)
		{
			continue;
		}

		oList.AddTail(p);
	}
}

void CSensorPpDeviceType::GetWillPublicTopic(CDvmData &oList)
{
	POS pos = GetHeadPosition();
	CDvmDataset *p = NULL;

	while(pos != NULL)
	{
		p = (CDvmDataset *)GetNext(pos);

		if (p->GetClassID() != PPCFGCLASSID_CSENSORPPPRODUCE)
		{
			continue;
		}

		if (oList.FindByID(p->m_strID) != NULL)
		{
			continue;
		}

		oList.AddValue(p->m_strName,p->m_strID,p->m_strID);
	}
}