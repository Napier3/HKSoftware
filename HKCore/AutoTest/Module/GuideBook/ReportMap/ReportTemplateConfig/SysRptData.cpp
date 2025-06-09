//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SysRptData.cpp  CSysRptData


#include "stdafx.h"
#include "SysRptData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSysRptData::CSysRptData()
{
	//初始化属性

	//初始化成员变量
}

CSysRptData::~CSysRptData()
{
}

long CSysRptData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSysRptData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CSysRptData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSysRptData *p = (CSysRptData*)pDest;

	return TRUE;
}

BOOL CSysRptData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSysRptData *p = (CSysRptData*)pObj;

	return TRUE;
}

CBaseObject* CSysRptData::Clone()
{
	CSysRptData *p = new CSysRptData();
	Copy(p);
	return p;
}

