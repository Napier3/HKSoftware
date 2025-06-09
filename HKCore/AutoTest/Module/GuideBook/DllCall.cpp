#include "stdafx.h"
#include "DllCall.h"
#include "Device.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const CString CDllCall::g_strDllPathSubID = _T("DllCall");
const CString CDllCall::g_strDllFilePostfix = _T(".dll");

CDllCall::CDllCall()
{
	m_strParaType = CGbParaTypeMngr::g_strDllCallParaTypeNone;
}

CDllCall::~CDllCall()
{
	
}

long CDllCall::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaTypeKey,oNode,m_strParaType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strFuncNameKey,oNode,m_strFuncName);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strResultFileKey,oNode,m_strResultFile);
	xml_GetCDATA(oNode, m_strParaData);
	
	return 0;
}

long CDllCall::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaTypeKey, oElement, m_strParaType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strFuncNameKey, oElement, m_strFuncName);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strResultFileKey, oElement, m_strResultFile);

	xml_SetCDATA(oXMLDoc, oElement, m_strParaData);

	return 0;
}

long CDllCall::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFuncName);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaType);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaData);	
		BinarySerializeCalLen(oBinaryBuffer, m_strResultFile);	
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFuncName);
		BinarySerializeRead(oBinaryBuffer, m_strParaType);
		BinarySerializeRead(oBinaryBuffer, m_strParaData);
		BinarySerializeRead(oBinaryBuffer, m_strResultFile);
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFuncName);
		BinarySerializeWrite(oBinaryBuffer, m_strParaType);
		BinarySerializeWrite(oBinaryBuffer, m_strParaData);
		BinarySerializeWrite(oBinaryBuffer, m_strResultFile);
	}

	return 0;
}

BOOL CDllCall::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CDllCall::CopyOwn(CBaseObject* pDesObj)
{
	CExBaseObject::CopyOwn(pDesObj);

	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}
	
	CDllCall* pDllCall = (CDllCall*)pDesObj;

	pDllCall->m_strFuncName =  m_strFuncName;
	pDllCall->m_strParaType =  m_strParaType;
	pDllCall->m_strParaData =  m_strParaData;
	pDllCall->m_strResultFile =  m_strResultFile;

	return TRUE;
}

CBaseObject* CDllCall::Clone()
{
	CDllCall* pDllCall = new CDllCall();

	Copy(pDllCall);

	return pDllCall;
}


CString CDllCall::GetDllFilePath()
{
	CString strDllPath;
	strDllPath = _P_GetBinPath();
	strDllPath += g_strDllPathSubID;
    strDllPath += _P_FOLDER_PATH_SEPARATOR_;

	if (m_strID.Find(g_strDllFilePostfix) > 0)
	{
		strDllPath += m_strID;
	}
	else
	{
		strDllPath += m_strID;
		strDllPath += g_strDllFilePostfix;
	}

	return strDllPath;
}

BOOL CDllCall::IsDllPathValid(CString &strPath)
{
	strPath = GetDllFilePath();

	return IsFileExist(strPath);
	//CFileFind find;
	//return find.FindFile(strPath);
}

BOOL CDllCall::IsDllPathValid()
{
	CString strPath;
	//CFileFind find;

	strPath = GetDllFilePath();
	return IsFileExist(strPath);
	//return find.FindFile(strPath);
}



CString CDllCall::GetParaFilePath()
{
	CString strDllPath;

	if (IsParaTypeFile())
	{
		strDllPath = _P_GetBinPath();
		strDllPath += g_strDllPathSubID;
        strDllPath += _P_FOLDER_PATH_SEPARATOR_;
		strDllPath += m_strParaData;
	}

	return strDllPath;
}

BOOL CDllCall::IsParaFilePathValid(CString &strPath)
{
	strPath = GetParaFilePath();
	return IsFileExist(strPath);
	//CFileFind find;
	//return find.FindFile(strPath);
}

BOOL CDllCall::IsParaFilePathValid()
{
	CString strPath;
	//CFileFind find;

	strPath = GetParaFilePath();
	return IsFileExist(strPath);
	//return find.FindFile(strPath);
}

