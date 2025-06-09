//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttRptMapDatas.cpp  CSttRptMapDatas


#include "stdafx.h"
#include "SttRptMapDatas.h"
#include "../../../Module/DataMngr/DvmData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRptMapDatas::CSttRptMapDatas()
{
	//初始化属性

	//初始化成员变量
}

CSttRptMapDatas::~CSttRptMapDatas()
{
}

long CSttRptMapDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttRptMapDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttRptMapDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttRptMapDatas::InitAfterRead()
{
}

BOOL CSttRptMapDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttRptMapDatas *p = (CSttRptMapDatas*)pObj;

	return TRUE;
}

BOOL CSttRptMapDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttRptMapDatas *p = (CSttRptMapDatas*)pDest;

	return TRUE;
}

CBaseObject* CSttRptMapDatas::Clone()
{
	CSttRptMapDatas *p = new CSttRptMapDatas();
	Copy(p);
	return p;
}

CBaseObject* CSttRptMapDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttRptMapDatas *p = new CSttRptMapDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttRptMapDatas::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttRptMapDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

CExBaseObject* CSttRptMapDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}

	return pNew;
}
