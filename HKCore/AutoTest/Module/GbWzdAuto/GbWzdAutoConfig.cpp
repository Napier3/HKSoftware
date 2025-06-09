//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbWzdAutoConfig.cpp  CGbWzdAutoConfig


#include "stdafx.h"
#include "GbWzdAutoConfig.h"
#include "..\..\..\Module\API\FileApi.h"
#include "..\GuideBook\ScriptText.h"
#include "..\GuideBook\ItemMngr.h"
#include "..\GuideBook\ItemParaMngr.h"

CGbWzdAutoConfig::CGbWzdAutoConfig()
{
	//初始化属性

	//初始化成员变量
	m_pScriptLocalLib = NULL;
	m_nDICount = 0;
	m_nDOCount = 0;
	m_nEnaCount = 0;
}

CGbWzdAutoConfig::~CGbWzdAutoConfig()
{
}

long CGbWzdAutoConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml_FileKey, oNode, m_strGbxmlFile);
	xml_GetAttibuteValue(pXmlKeys->m_strRel_PathKey, oNode, m_strRel_Path);
	xml_GetAttibuteValue(pXmlKeys->m_strAutoKey, oNode, m_strAuto);
	xml_GetAttibuteValue(pXmlKeys->m_strDICountKey, oNode, m_nDICount);
	xml_GetAttibuteValue(pXmlKeys->m_strDOCountKey, oNode, m_nDOCount);
	xml_GetAttibuteValue(pXmlKeys->m_strEnaCountKey, oNode, m_nEnaCount);
	xml_GetAttibuteValue(pXmlKeys->m_strBmkDITestKey, oNode, m_strBmk_DITest);
	xml_GetAttibuteValue(pXmlKeys->m_strBmkDOTestKey, oNode, m_strBmk_DOTest);
	return 0;
}

long CGbWzdAutoConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvmFile);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml_FileKey, oElement, m_strGbxmlFile);
	xml_SetAttributeValue(pXmlKeys->m_strRel_PathKey, oElement, m_strRel_Path);
	xml_SetAttributeValue(pXmlKeys->m_strAutoKey, oElement, m_strAuto);
	xml_SetAttributeValue(pXmlKeys->m_strDICountKey, oElement, m_nDICount);
	xml_SetAttributeValue(pXmlKeys->m_strDOCountKey, oElement, m_nDOCount);
	xml_SetAttributeValue(pXmlKeys->m_strEnaCountKey, oElement, m_nEnaCount);
	xml_SetAttributeValue(pXmlKeys->m_strBmkDITestKey, oElement, m_strBmk_DITest);
	xml_SetAttributeValue(pXmlKeys->m_strBmkDOTestKey, oElement, m_strBmk_DOTest);
	return 0;
}

long CGbWzdAutoConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strRel_Path);
		BinarySerializeCalLen(oBinaryBuffer, m_strAuto);
		BinarySerializeCalLen(oBinaryBuffer, m_nDICount);
		BinarySerializeCalLen(oBinaryBuffer, m_nDOCount);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnaCount);
		BinarySerializeCalLen(oBinaryBuffer, m_strBmk_DITest);
		BinarySerializeCalLen(oBinaryBuffer, m_strBmk_DOTest);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDvmFile);
		BinarySerializeRead(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeRead(oBinaryBuffer, m_strRel_Path);
		BinarySerializeRead(oBinaryBuffer, m_strAuto);
		BinarySerializeRead(oBinaryBuffer, m_nDICount);
		BinarySerializeRead(oBinaryBuffer, m_nDOCount);
		BinarySerializeRead(oBinaryBuffer, m_nEnaCount);
		BinarySerializeRead(oBinaryBuffer, m_strBmk_DITest);
		BinarySerializeRead(oBinaryBuffer, m_strBmk_DOTest);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFile);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strRel_Path);
		BinarySerializeWrite(oBinaryBuffer, m_strAuto);
		BinarySerializeWrite(oBinaryBuffer, m_nDICount);
		BinarySerializeWrite(oBinaryBuffer, m_nDOCount);
		BinarySerializeWrite(oBinaryBuffer, m_nEnaCount);
		BinarySerializeWrite(oBinaryBuffer, m_strBmk_DITest);
		BinarySerializeWrite(oBinaryBuffer, m_strBmk_DOTest);
	}
	return 0;
}

void CGbWzdAutoConfig::InitAfterRead()
{
}

BOOL CGbWzdAutoConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdAutoConfig *p = (CGbWzdAutoConfig*)pObj;

	if(m_strDvmFile != p->m_strDvmFile)
	{
		return FALSE;
	}

	if(m_strGbxmlFile != p->m_strGbxmlFile)
	{
		return FALSE;
	}

	if(m_strRel_Path != p->m_strRel_Path)
	{
		return FALSE;
	}

	if(m_strAuto != p->m_strAuto)
	{
		return FALSE;
	}

	if(m_nDICount != p->m_nDICount)
	{
		return FALSE;
	}

	if(m_nDOCount != p->m_nDOCount)
	{
		return FALSE;
	}

	if(m_nEnaCount != p->m_nEnaCount)
	{
		return FALSE;
	}

	if (m_strBmk_DITest != p->m_strBmk_DITest)
	{
		return FALSE;
	}

	if (m_strBmk_DOTest != p->m_strBmk_DOTest)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdAutoConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGbWzdAutoConfig *p = (CGbWzdAutoConfig*)pDest;

	p->m_strDvmFile = m_strDvmFile;
	p->m_strGbxmlFile = m_strGbxmlFile;
	p->m_strRel_Path = m_strRel_Path;
	p->m_strAuto = m_strAuto;
	p->m_nDICount = m_nDICount;
	p->m_nDOCount = m_nDOCount;
	p->m_nEnaCount = m_nEnaCount;
	p->m_strBmk_DITest = m_strBmk_DITest;
	p,m_strBmk_DOTest = m_strBmk_DOTest;
	return TRUE;
}

CBaseObject* CGbWzdAutoConfig::Clone()
{
	CGbWzdAutoConfig *p = new CGbWzdAutoConfig();
	Copy(p);
	return p;
}

BOOL CGbWzdAutoConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CGBWZDAUTOTEMPLATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGbWzdAutoConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbWzdAutoTemplateKey)
	{
		pNew = new CGbWzdAutoTemplate();
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strScriptMngrKey)
	{
		ASSERT (m_pScriptLocalLib == NULL);
		m_pScriptLocalLib = new CScriptTextMngr;
		pNew = m_pScriptLocalLib;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strItemMngrKey)
	{
		pNew = new CTestItemMngr();
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strItemParaMngrKey)
	{
		pNew = new CTestItemParaMngr();
	}

	return pNew;
}

CExBaseObject* CGbWzdAutoConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CGBWZDAUTOTEMPLATE)
	{
		pNew = new CGbWzdAutoTemplate();
	}
	else if (nClassID == GBCLASSID_SCRIPT_TEXT_MNGR)
	{
		ASSERT (m_pScriptLocalLib == NULL);
		m_pScriptLocalLib = new CScriptTextMngr;
		pNew = m_pScriptLocalLib;
	}
	else if (nClassID == GBCLASSID_TESTITEMMNGR)
	{
		pNew = new CTestItemMngr();
	}
	else if (nClassID == GBCLASSID_TESTITEMPARAMNGR)
	{
		pNew = new CTestItemParaMngr();
	}

	return pNew;
}

CGbWzdAutoTemplate* CGbWzdAutoConfig::AddGbWzdAutoTemplate(const CString &strName, const CString &strID
														   , const CString &strGbxmlFile, long nBinOffset, long nBoutOffset)
{
	CGbWzdAutoTemplate *pNew = new CGbWzdAutoTemplate();

// 	long nCount = FindTemplateByNameHas(strName);
// 
// 	if (nCount > 0)
// 	{
// 		CString strAppendName = strName;
// 		CString strAppendID = strID;
// 		strAppendName.AppendFormat(_T("-%d"), nCount);
// 		strAppendID.AppendFormat(_T("-%d"), nCount);
// 		pNew->m_strName = strAppendName;
// 		pNew->m_strID = strAppendID;
// 	}
// 	else
// 	{
// 		pNew->m_strName = strName;
// 		pNew->m_strID = strID;
// 	}
	
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strGbxmlFile = strGbxmlFile;
	pNew->m_nBinOffset = nBinOffset;
	pNew->m_nBoutOffset = nBoutOffset;
	AddNewChild(pNew);

	return pNew;
}

CString CGbWzdAutoConfig::GetDvmFile()
{
	CString strDvmFile;

	if (IsFileExist(m_strDvmFile))
	{
		strDvmFile = m_strDvmFile;
	}
	else
	{
		strDvmFile = _P_GetLibraryPath();
		strDvmFile +=m_strDvmFile;
	}

	return strDvmFile;
}


CString CGbWzdAutoConfig::GetGbxmlFile()
{
	CString strGbxmlFile;

	strGbxmlFile = _P_GetTemplatePath();

	//根据四方要求，大模板最后生成的路径在Template根目录下，注释此处
	//ShaoL 2019.04.23
// 	if (m_strRel_Path.GetLength() > 0)
// 	{
// 		strGbxmlFile.AppendFormat(_T("%s"), m_strRel_Path);
// 	}

	if (strGbxmlFile.Left(1) != '\\')
	{
		strGbxmlFile += _T("\\");
	}

	strGbxmlFile +=m_strGbxmlFile;

	return strGbxmlFile;
}

long CGbWzdAutoConfig::FindTemplateByNameHas(const CString &strName)
{
	CGbWzdAutoTemplate *pFind = NULL;
	long nCount = 0;
	long nLength = strName.GetLength();

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pFind = (CGbWzdAutoTemplate *)GetNext(pos);
		
		if (pFind->m_strName.Left(nLength) == strName)
		{
			nCount++;
		}
	}

	return nCount;
}