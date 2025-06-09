//#include "StdAfx.h"
#include "../../../Module/OSInterface/QT/stdafx.h"
#include "SttParaObjectsGroup.h"
/*
#include "TestBase.h"
#include "ParaTranConfig/ParaTranConfig.h"
*/

CSttParaObjectsGroup::CSttParaObjectsGroup(void)
{
	
}

CSttParaObjectsGroup::~CSttParaObjectsGroup(void)
{
}

void CSttParaObjectsGroup::GetParameter(CString &strParameter, BOOL bOnlyGetChange)
{
	POS pos = GetHeadPosition();
	CSttParaObject *pPara = NULL;
	CExBaseObject *p = NULL;
	CString strIDPath;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)p)->GetParameter(strParameter, bOnlyGetChange);
		}
		else
		{
			pPara = (CSttParaObject*)p;

			if (bOnlyGetChange)
			{
				if (pPara->IsParaChanged())
				{
					GetParaIDPath(strIDPath, pPara);
					strParameter.AppendFormat(_T("%s=%s;"), strIDPath, pPara->m_varValue.ToString());
				}
			}
			else
			{
				GetParaIDPath(strIDPath, pPara);
				strParameter.AppendFormat(_T("%s=%s;"), strIDPath, pPara->m_varValue.ToString());
			}
		}
	}
}

CSttParaObjectsGroup* CSttParaObjectsGroup::RegisterGroup(const CString &strName, const CString &strID, const CString &strDataType, LPVOID pItemData)
{
	CSttParaObjectsGroup *pNew = new CSttParaObjectsGroup();

    if (g_nParaRegisterDescInfor == REGSTER_MODE_ALL)
    {
        pNew->m_strName = strName;
    }
    else if (g_nParaRegisterDescInfor == REGSTER_MODE_NAME_EQ_ID)
    {
        pNew->m_strName = strID;
    }
    else
    {
    }

	pNew->m_strID = strID;
	pNew->m_strDataType = strDataType;
	pNew->m_dwItemData = (DWORD)pItemData;

	AddNewChild(pNew/*, TRUE*/);

	return pNew;
}

CExBaseObject* CSttParaObjectsGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CMacroXmlKeys::g_pMacroXmlKeys->m_strParaGroupKey)
	{
		return new CSttParaObjectsGroup();
	}

	if(strClassID == CMacroXmlKeys::g_pMacroXmlKeys->m_strParaKey)
	{
		return new CSttParaObject();
	}

	return NULL;
}

BSTR CSttParaObjectsGroup::GetXmlElementKey() 
{
	if (m_strXmlElementName != NULL)
	{
		return m_strXmlElementName;	
	}
	else
	{
		return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaGroupKey;
	}
}


long CSttParaObjectsGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttParaObjects::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroXmlKeys *pOnlyCtrlXmlKeys = (CMacroXmlKeys *)pXmlRWKeys;
	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oNode, m_strDataType);
// 	xml_GetAttibuteValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oNode, m_strCounterVar);

	return 0;
}

long CSttParaObjectsGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttParaObjects::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroXmlKeys *pOnlyCtrlXmlKeys = (CMacroXmlKeys *)pXmlRWKeys;
	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oElement, m_strDataType);
// 	xml_SetAttributeValue(pOnlyCtrlXmlKeys->m_strParaDataTypeKey, oElement, m_strCounterVar);

	return 0;
}


void CSttParaObjectsGroup::GetReportEx(CString &strReport)
{
	CSttParaObject* pPara = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)p)->GetReportEx(strReport);
		}
		else
		{
			pPara = (CSttParaObject*)p;
			strReport.AppendFormat(_T("%s=%s;"), GetParaIDPath(pPara), pPara->m_varValue.ToString());
		}
	}
}


void CSttParaObjectsGroup::GetReportEx(CStringSerializeBuffer &oBinaryBuffer)
{
	CSttParaObject* pObject = NULL;
	POS pos = GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pObject = (CSttParaObject*)GetNext(pos);

		if (pObject->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)pObject)->GetReportEx(oBinaryBuffer);
		}
		else
		{
			strValue = pObject->m_varValue.ToString();
/*//2024-5-21  lijunqing
			strValue = CSttParaTranConfig::DataTypeValueTrans2(pObject->m_strDataTypeID,strValue);
*/

// 			oBinaryBuffer << pObject->m_strID;
			oBinaryBuffer << GetParaIDPath(pObject);
			oBinaryBuffer << _T("=");
			oBinaryBuffer << strValue;
			oBinaryBuffer << _T(";");
		}
	}
}

CString CSttParaObjectsGroup::GetParaIDPath(CSttParaObject *pPara)
{
	CString strPath;
	GetParaIDPath(strPath, pPara);
	return strPath;
}

void CSttParaObjectsGroup::GetParaIDPath(CString &strPath, CSttParaObject *pPara)
{
	strPath.Empty();
	CExBaseObject *pParent = pPara;
	CString strTemp;
	
	while (pParent != NULL)
	{
		if (pParent->m_strID.GetLength() == 0)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strID);
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent->GetClassID() != PARACLASSID_PARAGROUP)
		{
			break;
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}

}

void CSttParaObjectsGroup::Parser(CEquationBuffer *pEquation)
{
	CSttParaObject* pPara = NULL;
	POS pos = GetHeadPosition();
	CString strValue;
	CExBaseObject *p = NULL;

	CString strPath;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != PARACLASSID_PARAGROUP)
		{
			pPara = (CSttParaObject*)p;
			strValue = _T("");
			GetParaIDPath(strPath, pPara);
			pEquation->ParseString(strPath, strValue);

			if(strValue.GetLength() > 0)
			{
/*//2024-5-21  lijunqing
				strValue = CSttParaTranConfig::DataTypeValueTrans(pPara->m_strDataTypeID,strValue);
*/
				pPara->SetParaValue(strValue, FALSE);
			
/*//2024-5-21  lijunqing
				if (pPara->m_strCreateGroup.GetLength() > 0)
				{
					CTestBaseInterface *pTestBase = (CTestBaseInterface*)GetTestBaseInterface();//GetAncestor(TMCLASSID_TESTBASE);
// 					ASSERT (pTestBase != NULL);	BBBB

					if (pTestBase != NULL)
					{
						pTestBase->OnSetParaValue(pPara);
					}
				}
*/
			}
		}
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)p)->Parser(pEquation);
		}
	}
}

void CSttParaObjectsGroup::SetParas(CDataGroup *pParas)
{
    POS pos = GetHeadPosition();
    CExBaseObject *p = NULL;
    CExBaseObject *pFind = NULL;

    while (pos != NULL)
    {
        p = GetNext(pos);
        pFind = (CExBaseObject*)pParas->FindByID(p->m_strID);

        if (pFind != NULL)
        {
            InitPara(p, pFind);
        }
    }
}

void CSttParaObjectsGroup::InitPara(CExBaseObject *pDestPara, CExBaseObject *pSrcPara)
{
    UINT nClassIDDest = pDestPara->GetClassID();
    UINT nSrcClassID = pSrcPara->GetClassID();

    if (nClassIDDest ==PARACLASSID_PARAGROUP && nSrcClassID ==  DTMCLASSID_CDATAGROUP)
    {
       // CSttParaObjectsGroup * temp = ((CSttParaObjectsGroup*)pSrcPara);
        ((CSttParaObjectsGroup*)pDestPara)->SetParas((CDataGroup*)pSrcPara);
        return;
    }

    if (nClassIDDest ==PARACLASSID_PARA && nSrcClassID ==  DVMCLASSID_CDVMDATA)
    {
        CSttParaObject *pSttPara = (CSttParaObject*)pDestPara;
        CDvmData *pData = (CDvmData*)pSrcPara;

       pSttPara->SetParaValue(pData->m_strValue, 0);
        return;
    }
}

void CSttParaObjectsGroup::InitDefault()
{
	CSttParaObject* pPara = NULL;
	POS pos = GetHeadPosition();
	CString strValue;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)p)->InitDefault();
		}
		else
		{
			pPara = (CSttParaObject*)p;
			pPara->SetParaValue(pPara->m_strDefaultValue);
		}
	}
}
// 
// void CSttParaObjectsGroup::ReadParas(CXmlRWNodeBase &oNode, BSTR bstrParasKey)
// {
// 	MSXML2::IXMLDOMNodeListPtr oParas = NULL;
// 	MSXML2::IXMLDOMNodePtr oTemp = NULL;
// 	MSXML2::IXMLDOMNodeListPtr oChildList = oNode->GetchildNodes();
// 	long nCount = oChildList->Getlength();
// 	long nIndex = 0;
// 
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		oTemp = oChildList->Getitem(nIndex);
// 		_bstr_t bstrID = oTemp->GetnodeName();
// 
// 		if (wcscmp(bstrID, bstrParasKey) == 0)
// 		{
// 			oParas = oTemp->GetchildNodes();
// 			break;
// 		}
// 	}
// 
// 	if(oParas == NULL)
// 	{
// 		return;
// 	}
// 
// 	ReadParasGroup(oParas);
// }

void CSttParaObjectsGroup::ReadParas(CXmlRWNodeListBase &oParas)
{
	CXmlRWNodeBase *oTemp = NULL;
	long nCount = oParas.GetNodeNum();
	long nIndex = 0;
	CString strID, strValue;
	CExBaseObject *pObj = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oTemp = oParas.GetChild(nIndex);
		xml_GetAttibuteValue(CMacroXmlKeys::g_pMacroXmlKeys->m_strIDKey, *oTemp, strID);
		pObj = FindByID(strID);

		if (pObj == NULL)
		{
			continue;
		}

		if (pObj->GetClassID() == PARACLASSID_PARAGROUP)
		{
			((CSttParaObjectsGroup*)pObj)->ReadParas(*((CXmlRWNodeListBase*)oTemp));
		}
		else
		{
			xml_GetAttibuteValue(CMacroXmlKeys::g_pMacroXmlKeys->m_strParaValueKey, *oTemp, strValue);
			((CSttParaObject*)pObj)->SetParaValue(strValue, FALSE);
		}
	}
}

void CSttParaObjectsGroup::DeleteAllGroup(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			if (((CSttParaObjectsGroup*)p)->m_strDataType == strDataType)
			{
				DeleteAt(posPrev);
			}
		}
	}
}

long CSttParaObjectsGroup::GetGroupCount(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			if (((CSttParaObjectsGroup*)p)->m_strDataType == strDataType)
			{
				nCount++;
			}
		}
	}

	return nCount;
}

CSttParaObjectsGroup* CSttParaObjectsGroup::GetGroup(const CString &strDataType, long nIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCurrIndex = 0;
	CSttParaObjectsGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PARACLASSID_PARAGROUP)
		{
			if (((CSttParaObjectsGroup*)p)->m_strDataType == strDataType)
			{
				if (nCurrIndex == nIndex)
				{
					pFind = (CSttParaObjectsGroup *)p;
					break;
				}

				nCurrIndex++;
			}
		}
	}

	return pFind;
}

BOOL CSttParaObjectsGroup::DeleteGroup(const CString &strDataType, long nIndex)
{
	CSttParaObjectsGroup *pFind = GetGroup(strDataType, nIndex);

	if (pFind == NULL)
	{
		return FALSE;
	}

	Delete(pFind);

	return TRUE;
}

CTestBaseInterface* CSttParaObjectsGroup::GetTestBaseInterface()
{
	CExBaseObject *pParent = NULL;
	CTestBaseInterface *pTestBase = NULL;

	pParent = (CExBaseObject *)GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == PARACLASSID_PARAGROUP)
		{
			pParent = (CExBaseObject *)pParent->GetParent();
		}	
		else
		{
			pTestBase = (CTestBaseInterface *)pParent->m_dwItemData;
			break;
		}
	}

	return pTestBase;
}

CDataGroup* CSttParaObjectsGroup::ToDataGroup()
{
    CDataGroup *pNewGroup = new CDataGroup();
    ToDataGroup(pNewGroup);

    return pNewGroup;
}

 void CSttParaObjectsGroup::ToDataGroup(CDataGroup *pDataGroup)
 {
     pDataGroup->m_strName = m_strName;
     pDataGroup->m_strID = m_strID;
     pDataGroup->m_strDataType = m_strDataType;

     POS pos = GetHeadPosition();
     CExBaseObject *p = NULL;
     CDataGroup *pGroup = 0;
     CDvmData *pData = 0;

     while (pos != NULL)
     {
         p = GetNext(pos);

         if (p->GetClassID() == PARACLASSID_PARAGROUP)
         {
             pGroup = ((CSttParaObjectsGroup*)p)->ToDataGroup();
             pDataGroup->AddNewChild(pGroup);
         }
         else
         {
             pData = ((CSttParaObject*)p)->ToDvmData();
             pDataGroup->AddNewChild(pData);
         }
     }
 }
