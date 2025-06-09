//RptTemp_NewPage.cpp  CRptTemp_NewPage


#include "stdafx.h"
#include "RptTemp_NewPage.h"

#ifdef _DEBUG
#undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_NewPage::CRptTemp_NewPage()
{
    //初始化属性

    //初始化成员变量
}

CRptTemp_NewPage::~CRptTemp_NewPage()
{

}

long CRptTemp_NewPage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

    return 0;
}

long CRptTemp_NewPage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

    return 0;
}

long CRptTemp_NewPage::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_NewPage::InitAfterRead()
{
}

BOOL CRptTemp_NewPage::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRptTemp_NewPage *p = (CRptTemp_NewPage*)pObj;

    return TRUE;
}

BOOL CRptTemp_NewPage::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRptTemp_NewPage *p = (CRptTemp_NewPage*)pDest;

    return TRUE;
}

CBaseObject* CRptTemp_NewPage::Clone()
{
    CRptTemp_NewPage *p = new CRptTemp_NewPage();
    Copy(p);
    return p;
}

CBaseObject* CRptTemp_NewPage::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
    CRptTemp_NewPage *p = new CRptTemp_NewPage();
    CopyEx(p, bCopyOwn, bCopyChildren);
    return p;
}
