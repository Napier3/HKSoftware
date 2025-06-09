// BaseObject.cpp: implementation of the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseObject.h"
#include "../API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//从XML节点中读取关键字

const char* CXmlRWKeys::g_pszNameKeyString  = "name";
const char* CXmlRWKeys::g_pszIDKeyString    = "id";

long CXmlRWKeys::ReadFromXmlFile(const CString &strFile)
{
	return 0;
}

//从XML节点中读取关键字
#ifdef XML_USE_MSXML
// long CXmlRWKeys::ReadXml(CXmlRWNodeBase & &oNode)
// {
// 	return 0;
// }
#endif

BSTR GetXml();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CBaseObject::CBaseObject()
{
	m_pParent = NULL;
}

CBaseObject::~CBaseObject()
{

}

CBaseObject* CBaseObject::GetAncestor(UINT nClassID)
{
	CBaseObject *pAncestor = NULL;
	CBaseObject *pAncestorFind = NULL;

	pAncestor = this;//m_pParent;

	while (pAncestor != NULL)
	{
		if (nClassID == pAncestor->GetClassID())
		{
			pAncestorFind = pAncestor;
			break;
		}

		pAncestor = pAncestor->GetParent();
	}

	return pAncestorFind;
}

CBaseObject* CBaseObject::GetAncestorEx(UINT nClassID)
{
	CBaseObject *pAncestor = NULL;
	CBaseObject *pAncestorFind = NULL;

	pAncestor = m_pParent;

	while (pAncestor != NULL)
	{
		if (nClassID == (pAncestor->GetClassID() & nClassID) )
		{
			pAncestorFind = pAncestor;
			break;
		}

		pAncestor = pAncestor->GetParent();
	}

	return pAncestorFind;
}

/*
 *	根据节点的深度获取祖先节点
 *  节点的深度：
 *           例如：A->B->C->D->E->F
 *                 F为叶子节点对象，E为F的Ancestor，其深度为0
 *                 D为F的Ancestor，其深度为1
 *                 B为F的Ancestor，其深度为3
 */
CBaseObject* CBaseObject::GetAncestorByDepth(long nDepth)
{
	CBaseObject *pAncestor = NULL;
	CBaseObject *pAncestorFind = NULL;
	
	pAncestor = m_pParent;
	long nTemp = nDepth;
	
	while (pAncestor != NULL)
	{
		if (nTemp == 0)
		{
			pAncestorFind = pAncestor;
			break;
		}

		pAncestor = pAncestor->GetParent();

		nTemp--;
	}
	
	return pAncestorFind;
}

long CBaseObject::GetDepth()
{
	CBaseObject *pTemp = NULL;
	CBaseObject *pParent = GetParent();
	long nDepth = 0;
	
	while (pParent != NULL)
	{
		pTemp = pParent->GetParent();
		
		if (pTemp == NULL)
		{
			break;
		}
		
		nDepth++;
		pParent = pTemp;
	}

	return nDepth;
}

CBaseObject* CBaseObject::GetRoot()
{
	CBaseObject *pTemp = NULL;
	CBaseObject *pRoot = this;

	while (pRoot != NULL)
	{
		pTemp = pRoot->GetParent();

		if (pTemp == NULL)
		{
			break;
		}

		pRoot = pTemp;
	}

	return pRoot;
}

BOOL CBaseObject::HasParent(CBaseObject *pParent)
{
	CBaseObject *pTemp = GetParent();

	while (pTemp != NULL)
	{
		if (pTemp == pParent)
		{
			return TRUE;
		}

		pTemp = pTemp->GetParent();
	}

	return FALSE;
}

long CBaseObject::XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	try
	{
		XmlReadOwn(oNode, pXmlRWKeys);
	}
	catch (...)
	{
#ifndef _PSX_IDE_QT_
        TRACE("Read xml error......");
#endif
    }

	try
	{
		CXmlRWNodeListBase *pChildNodeList = oNode.GetChildNodes();
		XmlReadChildren(*pChildNodeList, pXmlRWKeys);
	}
	catch (...)
	{
#ifndef _PSX_IDE_QT_
        TRACE("Read xml error......");
#endif
    }

	InitAfterRead();

	return 0;
}

long CBaseObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CBaseObject::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


//2020-12-1  lijunqing
long CBaseObject::XmlWriteEx(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, CXmlRWKeys *pXmlRWKeys, CXmlRWElementBase* &pRetElement)
{
	BSTR pszElementKey = GetXmlElementKey();
	ASSERT(pszElementKey != NULL);

	if (pszElementKey == NULL)
	{
		return -1;
	}

#ifdef _UNICODE
	if (lstrlen(pszElementKey) == 0)
	{
		return -1;
	}
#else
	if (wcslen(pszElementKey) == 0)
	{
		return -1;
	}
#endif

	pRetElement = oXMLDoc.CreateElement(pszElementKey,&oParent);
	XmlWriteOwn(oXMLDoc, *pRetElement, pXmlRWKeys);

	return 0;
}


long CBaseObject::XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys)
{
	ASSERT(pszElementKey != NULL);

	if (pszElementKey == NULL)
	{
		return -1;
	}

#ifdef _UNICODE
	if (lstrlen(pszElementKey) == 0)
	{
		return -1;
	}
#else
	if (wcslen(pszElementKey) == 0)
	{
		return -1;
	}
#endif

	CXmlRWElementBase *pElement = oXMLDoc.CreateElement(pszElementKey,&oParent);

	XmlWriteOwn(oXMLDoc, *pElement, pXmlRWKeys);
	XmlWriteChildren(oXMLDoc, *pElement, pXmlRWKeys);

	return 0;
}

long CBaseObject::XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, CXmlRWKeys *pXmlRWKeys)
{
	//2020-12-1  lijunqing  如下的代码，就不调用XmlWriteEx了
	BSTR pszElementKey = GetXmlElementKey();
	return XmlWrite(oXMLDoc, oParent, pszElementKey, pXmlRWKeys);
}

long CBaseObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	
	return 0;
}

long CBaseObject::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
};


long CBaseObject::Serialize(CBinarySerialBuffer &oBinaryBuffer)
{
	SerializeOwn(oBinaryBuffer);
	SerializeChildren(oBinaryBuffer);
	
	if (oBinaryBuffer.IsReadMode())
	{
		InitAfterRead();
	}

	return 0;
}

long CBaseObject::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}

long CBaseObject::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{ 
	return 0;
}


long CBaseObject::SerializeRead(char *pBuffer, long nLen)
{
	CBinarySerialBuffer oBinaryBuffer;
	oBinaryBuffer.AttachBuffer(pBuffer, nLen);
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	oBinaryBuffer.SetReadMode();

	return SerializeRead(oBinaryBuffer);
}

long CBaseObject::SerializeRead(CBinarySerialBuffer &oBinaryBuffer)
{
	ASSERT (oBinaryBuffer.IsReadMode());
	return Serialize(oBinaryBuffer);
}

long CBaseObject::SerializeWrite(CBinarySerialBuffer &oBinaryBuffer)
{
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	oBinaryBuffer.SetCalSizeMode();
	Serialize(oBinaryBuffer);
	oBinaryBuffer.AllocBuffer(0);
	oBinaryBuffer.SetWriteMode();
	Serialize(oBinaryBuffer);

	return 0;
}

#ifdef _DBLIB_USE_SHAREMEM_
long CBaseObject::SerializeWrite(CShareMemSerialize *pBinaryBuffer)
{
	pBinaryBuffer->SetCharSet(CHAR_SET_ASCII);
	pBinaryBuffer->ResetBufferPointer();
	pBinaryBuffer->SetWriteMode();
	Serialize(*pBinaryBuffer);

	return 0;
}
#endif

BOOL CBaseObject::BinarySerializeReadFromFile(const CString &strFile)
{
	CBinarySerialBuffer oBuffer;

	return FALSE;
// 	if (oBuffer->(strFile))
// 	{
// 		oBuffer.SetModeRead();
// 		Serialize(oBuffer);
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
}

BOOL CBaseObject::BinarySerializeWriteToFile(const CString &strFile)
{
// 	CBinarySerialBuffer oBuffer;
// 
// 	oBuffer.SetModeCalSize();
// 	Serialize(oBuffer);
// 	oBuffer.AllocMemBuffer(0);
// 	oBuffer.SetModeWrite();
// 	Serialize(oBuffer);
// 
// 	return oBuffer.WriteToFile(strFile);
	return FALSE;
}

BOOL CBaseObject::CopyEx(CBaseObject* pDest, BOOL bCopyOwn,BOOL bCopyChildren)	
{
	if (bCopyOwn)
	{
		CopyOwn(pDest); 
	}

	if (bCopyChildren)
	{
		CopyChildren(pDest); 
		pDest->InitAfterRead(); 
	}
	
	return TRUE;
}

BOOL CBaseObject::CopyOwn(CBaseObject* pDest)	
{
	return TRUE;
}

BOOL CBaseObject::CopyChildren(CBaseObject* pDest)
{
	return TRUE;
}

BOOL CBaseObject::UpdateOwn(CBaseObject* pDest)
{	
	return TRUE;
}

BOOL CBaseObject::UpdateChildren(CBaseObject* pDest)
{
	return TRUE;
}

BOOL CBaseObject::IsSame(CBaseObject* pObj)
{
	return FALSE;
}

CBaseObject* CBaseObject::FindSame(CBaseObject* pObj)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 对比

long CBaseObject::ValCmp(CBaseObject* pRightObj)
{
	ASSERT (FALSE);
	return 1;
}

long CBaseObject::ValCmp(CBaseObject* pRightObj, DWORD dwAttrID)
{
	ASSERT (FALSE);
	return 1;
}

long CBaseObject::ValCmp(CBaseObject* pRightObj, const CString &strAttrID)
{
	ASSERT (FALSE);
	return 1;
}

BOOL CBaseObject::IsEqual(CBaseObject* pObj)
{
	if (IsEqualOwn(pObj) == FALSE)
	{
		return FALSE;
	}
	if (IsEqualChildren(pObj) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseObject::IsEqualOwn(CBaseObject* pObj)
{	
	return TRUE;
}

BOOL CBaseObject::IsEqualChildren(CBaseObject* pObj)	
{
	return TRUE;
}


//msxml调用
BOOL CBaseObject::OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	if (!IsFileExist(strFile))
	{
		//2022-11-25  lijunqing
#ifdef _DEBUG
		CString strMsg = _T("File error :") + strFile;
		CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
#endif
		return FALSE;
	}

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDoc;
			return FALSE;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	
	if (bstrElementKey != NULL)
	{
		pDocRoot = pDocRoot->GetChildNode(bstrElementKey);
	}
	else
	{
		delete pRWDoc;
		return FALSE;
		//pDocRoot = pRWDoc->GetDocNode();
	}

	if (pDocRoot == NULL)
	{
		delete pRWDoc;
		return FALSE;
	}

	if(!pDocRoot->IsValid())
	{
		delete pRWDoc;
		return FALSE;
	}

	XmlRead(*pDocRoot, pXmlRWKeys);

	delete pRWDoc;

	return TRUE;
}

BOOL CBaseObject::OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	BSTR bstrElementKey = GetXmlElementKey();//虚函数，利用多态直接调用子类的此函数，返回静态成员变量的值；实际操作为{      return CXLanguageXmlRWKeys::CXLanguageMngrKey();     }
	return OpenXmlFile(strFile, bstrElementKey, pXmlRWKeys,nXmlRWType);//中间参数为刚刚在语言关键子里静态变量指针指向的对象成员变量的值；其对应了根节点的名称；
}

BOOL CBaseObject::SaveXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys ,const long &nXmlRWType)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

	try
	{
		CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

		CXmlRWElementBase *pElement = pRWDoc->GetDocElement();
		XmlWrite(*pRWDoc,*pElement,pXmlRWKeys);

		ClearFileReadOnlyAttr(strFile);

		CString strPath = GetPathFromFilePathName(strFile);
		CreateAllDirectories(strPath);

		pRWDoc->SaveXml(strFile);

		delete pRWDoc;
	}
	catch (...)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, ("Save  [%s]  Failed!"), strFile);
		return 0;
	}
	
	return 1;
}

BSTR CBaseObject::GetXml(CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
	XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);
	CString strXML;
	pRWDoc->GetXml(strXML);
	delete pRWDoc;
	return strXML.AllocSysString();
}

void CBaseObject::GetXml(CXmlRWKeys *pXmlRWKeys, CString &bstrXml,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
	XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);
	pRWDoc->GetXml(bstrXml);
	delete pRWDoc;
}

//xxy 20200516:生成ppszRetBuffer为utf-8字节流
long CBaseObject::GetXml(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
	XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);

	long nLen = pRWDoc->GetXml(ppszRetBuffer, nOffset);
	delete pRWDoc;
	return nLen;
}

long CBaseObject::GetXml_UTF8(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
	XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);

	long nLen = pRWDoc->GetXml(ppszRetBuffer, nOffset);
	delete pRWDoc;
	return nLen;
}

long CBaseObject::GetXml_ASCII(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
	CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
	XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);

	long nLen = pRWDoc->GetXml_ASCII(ppszRetBuffer, nOffset);
	delete pRWDoc;
	return nLen;
}

BOOL CBaseObject::SetXml(CXmlRWDocBase *pRWDoc, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys)
{
    CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

    if (bstrElementKey != NULL)
    {
        pDocRoot = pDocRoot->GetChildNode(bstrElementKey);
    }
    else
    {
        pDocRoot = pRWDoc->GetDocNode();
    }

	//2020-06-21  lijunqing
	if (pDocRoot == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetXml Error: oDocRoot == NULL"));
		return 0;
	}

    if(!pDocRoot->IsValid())
    {
#ifndef _PSX_IDE_QT_
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetXml Error: oDocRoot == NULL"));

//         if (wcslen(strXml) <= 2048)
//         {
//             CString strTemp;
//             strTemp = strXml;
//             CLogPrint::LogString(XLOGLEVEL_TRACE, strTemp);
//         }
#endif

        return FALSE;
    }

    XmlRead(*pDocRoot, pXmlRWKeys);

    return TRUE;
}

BOOL CBaseObject::SetXml(const CString &strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	BSTR bstrXml = strXml.AllocSysString();

	BOOL bRet = SetXml(bstrXml, pXmlRWKeys, nXmlRWType);

#ifdef _PSX_IDE_QT_
	delete bstrXml;
#else
	SysFreeString(bstrXml);
#endif

	return bRet;
}

BOOL CBaseObject::SetXml(BSTR strXml, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	if (wcslen(strXml) == 0)
	{
		return FALSE;
	}

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	if (!pRWDoc->SetXml(strXml))
	{
		delete pRWDoc;
		return FALSE;
	}

    BOOL bRet = SetXml(pRWDoc, bstrElementKey, pXmlRWKeys);
    delete pRWDoc;

    return bRet;

//	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
//
//	if (bstrElementKey != NULL)
//	{
//		pDocRoot = pDocRoot->GetChildNode(bstrElementKey);
//	}
//	else
//	{
//		pDocRoot = pRWDoc->GetDocNode();
//	}
//
//	if(!pDocRoot->IsValid())
//	{
//#ifndef _PSX_IDE_QT_
//        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetXml Error: oDocRoot == NULL"));
//
//		if (wcslen(strXml) <= 2048)
//		{
//			CString strTemp;
//			strTemp = strXml;
//			CLogPrint::LogString(XLOGLEVEL_TRACE, strTemp);
//		}
//#endif
//
//		delete pRWDoc;
//		return FALSE;
//	}
//
//	XmlRead(*pDocRoot, pXmlRWKeys);
//	delete pRWDoc;
//
//	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CBaseObject::SetXml(_bstr_t &strXml,BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	if (!pRWDoc->SetXml(strXml))
	{
		delete pRWDoc;
		return FALSE;
	}

    BOOL bRet = SetXml(pRWDoc, bstrElementKey, pXmlRWKeys);
    delete pRWDoc;

    return bRet;

//	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

//	if (bstrElementKey != NULL)
//	{
//		pDocRoot = pDocRoot->GetChildNode(bstrElementKey);
//	}
//	else
//	{
//		pDocRoot = pRWDoc->GetDocNode();
//	}

//	if(!pDocRoot->IsValid())
//	{
//		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetXml Error: oDocRoot == NULL"));

//		if (wcslen(strXml) <= 2048)
//		{
//			CString strTemp;
//            strTemp = (LPCSTR)strXml;
//			CLogPrint::LogString(XLOGLEVEL_TRACE, strTemp);
//		}

//		delete pRWDoc;
//		return FALSE;
//	}

//	XmlRead(*pDocRoot, pXmlRWKeys);
//	delete pRWDoc;
//	return TRUE;
}
#endif


BOOL CBaseObject::SetXml(BSTR strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	BSTR bstrElementKey = GetXmlElementKey();

	return SetXml(strXml, bstrElementKey, pXmlRWKeys,nXmlRWType);
}

#ifndef _PSX_IDE_QT_
BOOL CBaseObject::SetXml(_bstr_t &strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	BSTR bstrElementKey = GetXmlElementKey();

	return SetXml(strXml, bstrElementKey, pXmlRWKeys,nXmlRWType);
}
#endif

BOOL CBaseObject::SetXml_ASCII(char *strXml,long nLen, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
//     if (strlen(strXml) == 0)
//     {
//         return FALSE;
//     }

    CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

    if (!pRWDoc->SetXml_ASCII(strXml,nLen))
    {
        delete pRWDoc;
        return FALSE;
    }

    BSTR bstrElementKey = GetXmlElementKey();
    BOOL bRet = SetXml(pRWDoc, bstrElementKey, pXmlRWKeys);
    delete pRWDoc;

    return bRet;
}

BOOL CBaseObject::SetXml_UTF8(char *strXml,long nLen, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
//    if (strlen(strXml) == 0)
//    {
//        return FALSE;
//    }

    CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	if (!pRWDoc->SetXml_UTF8(strXml,nLen))
    {
        delete pRWDoc;
        return FALSE;
    }

    BSTR bstrElementKey = GetXmlElementKey();
    BOOL bRet = SetXml(pRWDoc, bstrElementKey, pXmlRWKeys);
    delete pRWDoc;

    return bRet;
}

void CBaseObject::SetModifiedFlag(BOOL bModified)
{
	CBaseObject *pRoot = GetRoot();

	pRoot->SetModifiedFlagOwn(bModified);
}

void CBaseObject::SetModifiedFlagOwn(BOOL bModified)
{

}

BOOL CBaseObject::GetModifiedFlagOwn()
{
	return FALSE;
}

void CBaseObject::SaveBaseObject()
{
	SetModifiedFlagOwn(FALSE);
}

//2021-5-5  lijunqing  可以获取自身节点是否被改变，也可以获取根节点的状态
//这样方便使用任意层级对象判断是否被编辑
BOOL CBaseObject::GetModifiedFlag(BOOL bRoot)
{
	if (bRoot)
	{
		CBaseObject *pRoot = GetRoot();
		return pRoot->GetModifiedFlagOwn();
	}
	else
	{
		return GetModifiedFlagOwn();
	}
}

