//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Values.cpp  CValues


#include "stdafx.h"
#include "Values.h"
#include "DataGroup.h"
#include "../MemBuffer/EquationBuffer.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CValues::CValues()
{
	//初始化属性

	//初始化成员变量
}

CValues::~CValues()
{
}

long CValues::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CValues::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CValues::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CValues::InitAfterRead()
{
}

BOOL CValues::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CValues *p = (CValues*)pObj;

	return TRUE;
}

BOOL CValues::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CValues *p = (CValues*)pDest;

	return TRUE;
}

CBaseObject* CValues::Clone()
{
	CValues *p = new CValues();
	Copy(p);
	return p;
}

long CValues::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CValues::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CValues::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCValueKey)
	{
		pNew = new CValue();
	}

	return pNew;
}

CExBaseObject* CValues::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CVALUE)
	{
		pNew = new CValue();
	}

	return pNew;
}


CValue* CValues::AddValue(const CString &strID, const CString &strValue)
{
 	 CValue *pValue = new  CValue();
 	 pValue->m_strValue = strValue;
 	 pValue->m_strID = strID;
 	 pValue->SetParent(this);
 	 AddTail(pValue);
 	 return pValue;
}

CValue* CValues::AddValue(const CString &strID, const CString &strName, const CString &strValue)
{
	CValue *pValue = new  CValue();
	pValue->m_strValue = strValue;
	pValue->m_strID = strID;
	pValue->m_strName = strName;
	pValue->SetParent(this);
	AddTail(pValue);
	return pValue;
}

void CValues::SetValuesByDatas(CValues *pValues)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pDest = NULL;
	CValue *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CValue *)pValues->GetNext(pos);
		pDest = (CValue *)FindByID(pSrc->m_strID);

		if (pDest != NULL)
		{
			pDest->m_strValue = pSrc->m_strValue;
		}
		else
		{
			pDest = (CValue *)pSrc->Clone();
			AddNewChild(pDest);
		}
	}
}

CString CValues::GetDatasString()
{
	CString strValues;
	POS pos = GetHeadPosition();
	CValue *p = NULL;

	while (pos != NULL)
	{
		p = (CValue *)GetNext(pos);
        strValues.AppendFormat(_T("%s=%s;"), p->m_strID.GetString(), p->m_strValue.GetString());
	}

	return strValues;
}

// class CDataGroup;
long CValues::SetValuesByString(const CString &strValues)
{
    long nLen = strValues.GetLength();

    if(nLen > 6)
    {
        CString strLeft = strValues.Left(6);

        if(strLeft == _T("<group"))
        {
            //如果是TestMacroUIParas模式，则strValues可以解析成一个Group
            //shaolei 20220221
            BOOL bRet = FALSE;
            CDataGroup oGroup;
            BSTR bstrText = strValues.AllocSysString();
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
            bRet = oGroup.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

        #ifdef _PSX_IDE_QT_
            delete bstrText;
        #else
            SysFreeString(bstrText);
        #endif
            if(bRet)
            {
                POS pos = oGroup.GetHeadPosition();
                CDvmData *pData = NULL;

                while(pos != NULL)
                {
                    pData = (CDvmData *)oGroup.GetNext(pos);
                    AddValue(pData->m_strID, pData->m_strValue);
                }

                return GetCount();
                //return SetValuesByGroup(&oGroup);
            }
        }
    }

	CEquationBuffer oEquation;
	oEquation.InitBuffer(strValues);

	POS pos = oEquation.GetHeadPosition();
	CEquationKey *pKey = NULL;

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oEquation.GetNext(pos);
		AddValue(pKey->GetKeyName(), pKey->GetKeyValue());
	}

	return GetCount();
}

// long CValues::SetValuesByGroup(CDataGroup *pGroup)
// {
//     POS pos = pGroup->GetHeadPosition();
//     CDvmData *pData = NULL;
// 
//     while(pos != NULL)
//     {
//         pData = (CDvmData *)pGroup->GetNext(pos);
//         AddValue(pData->m_strID, pData->m_strValue);
//     }
// 
//     return GetCount();
// }

BOOL CValues::SetValue(const CString &strID, const CString &strValue)
{
	CValue *pValue = (CValue*)FindByID(strID);

	if (pValue != NULL)
	{
		pValue->m_strValue = strValue;
	}

	return (pValue != NULL);
}

BOOL CValues::GetValue(const CString &strID, CString &strValue)
{
	CValue *pFind = (CValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	strValue = pFind->m_strValue;

	return TRUE;
}

BOOL CValues::GetValue(const CString &strID, double &dValue)
{
	CValue *pFind = (CValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	dValue = CString_To_double(pFind->m_strValue);

	return TRUE;
}


BOOL CValues::GetValue(const CString &strID, long &nValue)
{
	CValue *pFind = (CValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pFind->m_strValue);

	return TRUE;
}

