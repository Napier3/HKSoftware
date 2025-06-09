//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroMaps.cpp  CMacroMaps


#include "stdafx.h"
#include "MacroMaps.h"

CMacroMaps::CMacroMaps()
{
	//初始化属性

	//初始化成员变量
	m_bModifiedFlag = FALSE;
}

CMacroMaps::~CMacroMaps()
{
}

long CMacroMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMacroMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMacroMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMacroMaps::InitAfterRead()
{
}

BOOL CMacroMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMacroMaps *p = (CMacroMaps*)pObj;

	return TRUE;
}

BOOL CMacroMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMacroMaps *p = (CMacroMaps*)pDest;

	return TRUE;
}

CBaseObject* CMacroMaps::Clone()
{
	CMacroMaps *p = new CMacroMaps();
	Copy(p);
	return p;
}

BOOL CMacroMaps::CanPaste(UINT nClassID)
{
	if (nClassID == MPCLASSID_CMACROMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMacroMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroMapMngrXmlRWKeys *pXmlKeys = (CMacroMapMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMacroMapKey)
	{
		pNew = new CMacroMap();
	}

	return pNew;
}

CExBaseObject* CMacroMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MPCLASSID_CMACROMAP)
	{
		pNew = new CMacroMap();
	}

	return pNew;
}

CString CMacroMaps::GetMapFilePath()
{
	CString strFilePath;
	strFilePath = _P_GetLibraryPath();
	strFilePath += _T("PowerTestAtsMacroMap.xml");

	return strFilePath;
}

void CMacroMaps::OpenMacroMaps()
{
	DeleteAll();

	CString strFilePath = GetMapFilePath();

	OpenXmlFile(strFilePath ,  CMacroMapMngrXmlRWKeys::CMacroMapsKey(), CMacroMapMngrXmlRWKeys::g_pXmlKeys);
}


void CMacroMaps::SaveMapFile()
{
	CString strFilePath = GetMapFilePath();

	SaveXmlFile(strFilePath, CMacroMapMngrXmlRWKeys::g_pXmlKeys);
}

CMacroMap* CMacroMaps::FindMacroMap(const CString &strPttMacroID)
{
	CMacroMap *pFind = (CMacroMap*)FindByID(strPttMacroID);

	return pFind;
}

CMacroMap* CMacroMaps::FindMacroMapByMapID(const CString &strMapID)
{
	CMacroMap *pFind = NULL;
	CMacroMap *pCurObj = NULL;
	POS pos_Cur = GetHeadPosition();

	while(pos_Cur)
	{
		pCurObj = (CMacroMap*)GetNext(pos_Cur);

		if (pCurObj->m_strMapID == strMapID)
		{
			pFind = pCurObj;
			break;
		}
	}

	return pFind;
}

