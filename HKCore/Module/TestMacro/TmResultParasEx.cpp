//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmResultEx.cpp  CTmResultEx


#include "stdafx.h"
#include "TmResultParasEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmResultParasEx::CTmResultParasEx()
{
	//初始化属性

	//初始化成员变量
}

CTmResultParasEx::~CTmResultParasEx()
{
}
// 
// long CTmResultParasEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CTmResultParasEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CTmResultParasEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	CDataGroup::SerializeOwn(oBinaryBuffer);
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 	}
// 	return 0;
// }
// 
// void CTmResultParasEx::InitAfterRead()
// {
// }
// 
// BOOL CTmResultParasEx::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (!CDataGroup::IsEqualOwn(pObj))
// 	{
// 		return FALSE;
// 	}
// 
// 	CTmResultParasEx *p = (CTmResultParasEx*)pObj;
// 
// 	return TRUE;
// }
// 
// BOOL CTmResultParasEx::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
// 
// 	CDataGroup::CopyOwn(pDest);
// 
// 	CTmResultParasEx *p = (CTmResultParasEx*)pDest;
// 
// 	return TRUE;
// }

CBaseObject* CTmResultParasEx::Clone()
{
	CTmResultParasEx *p = new CTmResultParasEx();
	Copy(p);
	return p;
}
// 
// CExBaseObject* CTmResultParasEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject *pNew  = NULL;
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 
// 
// 	return pNew;
// }
// 
// CExBaseObject* CTmResultParasEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 
// 	return pNew;
// }
