//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicLib.cpp  CCharacteristicLib


#include "stdafx.h"
#include "CharacteristicLib.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const CString CCharacteristicLib::g_strDefaultLibFile = _T("Characteristic-lib.xml");

CCharacterArea* CCharacteristicLib::g_pGlobalCharAreaSrc = NULL;
long CCharacteristicLib::g_nGlobalCharAreaSrcRef = 0;

CCharacterArea* CCharacteristicLib::GetGlobalCharAreaSrc()
{
	ASSERT (g_pGlobalCharAreaSrc != NULL);
	return g_pGlobalCharAreaSrc;
}

void CCharacteristicLib::CreateGlobalCharAreaSrc()
{
	g_nGlobalCharAreaSrcRef++;

	if (g_nGlobalCharAreaSrcRef == 1)
	{
		g_pGlobalCharAreaSrc = new CCharacterArea();

		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementLined());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementMho());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementLens());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementArcd());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementLiner());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementLine());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementLinep());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementArc());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementArcp());

		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementI2T());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementIAC());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementIEC());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementIEEE());

//#ifdef CHARELEUIVP
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementUIVP());
//#endif
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementInvOwnDef());
		g_pGlobalCharAreaSrc->AddNewChild(new CCharElementDCOverLoad());//cl20230912

	}
}

void CCharacteristicLib::ReleaseGlobalCharAreaSrc()
{
	g_nGlobalCharAreaSrcRef--;

	if (g_nGlobalCharAreaSrcRef == 0)
	{
		delete g_pGlobalCharAreaSrc;
		g_pGlobalCharAreaSrc = NULL;
	}
}

CCharacteristicLib::CCharacteristicLib()
{
	//初始化属性

	//初始化成员变量
}

CCharacteristicLib::~CCharacteristicLib()
{
}

long CCharacteristicLib::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacterFolder::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristicLib::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacterFolder::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristicLib::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CCharacteristicLib::InitAfterRead()
{
	char_CChaTmplate_to_Characteristic(this);
}

BOOL CCharacteristicLib::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacteristicLib *p = (CCharacteristicLib*)pObj;

	return TRUE;
}

BOOL CCharacteristicLib::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacterFolder::CopyOwn(pDest);
	CCharacteristicLib *p = (CCharacteristicLib*)pDest;

	return TRUE;
}

CBaseObject* CCharacteristicLib::Clone()
{
	CCharacteristicLib *p = new CCharacteristicLib();
	Copy(p);
	return p;
}

CExBaseObject* CCharacteristicLib::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CCharacterFolder::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CCharacteristicLib::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return CCharacterFolder::CreateNewChild(nClassID);
}


CString CCharacteristicLib::GetLibFile(const CString &strLibFile)
{
	CString strFile;
	strFile = _P_GetLibraryPath();

	if (strLibFile.GetLength() > 4)
	{
		strFile += strLibFile;
	}
	else
	{
		strFile += g_strDefaultLibFile;
	}

	return strFile;
}

BOOL CCharacteristicLib::OpenCharLibFile(const CString &strLibFile)
{
    if (strLibFile.GetLength() > 5)
    {
        if (IsFileExist(strLibFile))
        {
               m_strLibFile = strLibFile;
        }
    }

    if (m_strLibFile.GetLength() == 0)
    {
        CString strFile = GetLibFile(strLibFile);
        m_strLibFile = strFile;
    }

    return OpenXmlFile(m_strLibFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
}

BOOL CCharacteristicLib::SaveCharLibFile(const CString &strLibFile)
{
	if (strLibFile.GetLength() > 8)
	{
		return SaveXmlFile(strLibFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		return SaveXmlFile(m_strLibFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
	}
}

