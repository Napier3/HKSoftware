//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValues.cpp  CDvmValues


#include "stdafx.h"
#include "DvmValues.h"
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


CDvmValues::CDvmValues()
{
	//初始化属性

	//初始化成员变量
}

CDvmValues::~CDvmValues()
{
}

long CDvmValues::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmValues::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDvmValues::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDvmValues::InitAfterRead()
{
}

BOOL CDvmValues::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmValues *p = (CDvmValues*)pObj;

	return TRUE;
}

BOOL CDvmValues::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmValues *p = (CDvmValues*)pDest;

	return TRUE;
}

CBaseObject* CDvmValues::Clone()
{
	CDvmValues *p = new CDvmValues();
	Copy(p);
	return p;
}

long CDvmValues::InitListCtrlColumns(CListCtrl *pListCtrl)
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

long CDvmValues::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CDvmValues::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCValueKey)
	{
		pNew = new CDvmValue();
	}

	return pNew;
}

CExBaseObject* CDvmValues::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		pNew = new CDvmValue();
	}

	return pNew;
}


CDvmValue* CDvmValues::AddValue(const CString &strID, const CString &strValue)
{
 	 CDvmValue *pValue = new  CDvmValue();
 	 pValue->m_strValue = strValue;
 	 pValue->m_strID = strID;
 	 pValue->SetParent(this);
 	 AddTail(pValue);
 	 return pValue;
}

CDvmValue* CDvmValues::AddValue(const CString &strID, const CString &strName, const CString &strValue)
{
	CDvmValue *pValue = new  CDvmValue();
	pValue->m_strValue = strValue;
	pValue->m_strID = strID;
	pValue->m_strName = strName;
	pValue->SetParent(this);
	AddTail(pValue);
	return pValue;
}

void CDvmValues::SetValuesByDatas(CDvmValues *pValues)
{
	POS pos = pValues->GetHeadPosition();
	CDvmValue *pDest = NULL;
	CDvmValue *pSrc = NULL;

	while (pos != NULL)
	{
		pSrc = (CDvmValue *)pValues->GetNext(pos);
		pDest = (CDvmValue *)FindByID(pSrc->m_strID);

		if (pDest != NULL)
		{
			pDest->m_strValue = pSrc->m_strValue;
		}
		else
		{
			pDest = (CDvmValue *)pSrc->Clone();
			AddNewChild(pDest);
		}
	}
}

CString CDvmValues::GetDatasString()
{
	CString strValues;
	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);
        strValues.AppendFormat(_T("%s=%s;"), p->m_strID.GetString(), p->m_strValue.GetString());
	}

	return strValues;
}

// class CDataGroup;
long CDvmValues::SetValuesByString(const CString &strValues)
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

BOOL CDvmValues::SetValue(const CString &strID, const CString &strValue)
{
	CDvmValue *pValue = (CDvmValue*)FindByID(strID);

	if (pValue != NULL)
	{
		pValue->m_strValue = strValue;
	}

	return (pValue != NULL);
}

BOOL CDvmValues::GetValue(const CString &strID, CString &strValue)
{
	CDvmValue *pFind = (CDvmValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	strValue = pFind->m_strValue;

	return TRUE;
}

BOOL CDvmValues::GetValue(const CString &strID, double &dValue)
{
	CDvmValue *pFind = (CDvmValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	dValue = CString_To_double(pFind->m_strValue);

	return TRUE;
}


BOOL CDvmValues::GetValue(const CString &strID, long &nValue)
{
	CDvmValue *pFind = (CDvmValue*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pFind->m_strValue);

	return TRUE;
}

