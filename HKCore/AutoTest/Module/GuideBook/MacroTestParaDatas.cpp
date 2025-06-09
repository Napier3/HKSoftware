#include "stdafx.h"
#include "MacroTestParaDatas.h"
#include "Script/GbScriptFunctions.h"
#include "MacroTestParaData.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMacroTestParaDatas::CMacroTestParaDatas()
{

}

CMacroTestParaDatas::~CMacroTestParaDatas()
{

}

long CMacroTestParaDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CMacroTestParaDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CMacroTestParaDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	return 0;
}

void CMacroTestParaDatas::InitAfterRead()
{

	UpdateMacroTestParaDatas();
}


CExBaseObject* CMacroTestParaDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaTableParaKey)
	{
		CMacroTestParaData* pPara = new CMacroTestParaData;
		return pPara;
	}

	return NULL;
}

CExBaseObject* CMacroTestParaDatas::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_FAULTPARAS_PARA)
	{	
		CMacroTestParaData* pPara = new CMacroTestParaData;
		return pPara;
	}

	return NULL;
}



BOOL CMacroTestParaDatas::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CMacroTestParaDatas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn (pDesObj);

	return TRUE;
}

CBaseObject* CMacroTestParaDatas::Clone()
{
	CMacroTestParaDatas* pFaultPara = new CMacroTestParaDatas();
	Copy(pFaultPara);

	return pFaultPara;
}

CExBaseObject* CMacroTestParaDatas::FindParaById(const CString &strID)
{
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		CExBaseObject* pObj = GetNext(pos);

		if (pObj->GetClassID() == GBCLASSID_FAULTPARAS_PARA)
		{
			if (pObj->m_strID == strID)
			{
				return pObj;
			}
		}
	}

	return NULL;
}

CExBaseObject* CMacroTestParaDatas::FindSysVarByPathID(const CString& strID)
{
	POS pos = GetHeadPosition();


	return NULL;
}

CExBaseObject* CMacroTestParaDatas::AddPara(CShortData *pData)
{
	CString strIDPath = pData->m_strID;

	if (pData->GetAncestor(TMCLASSID_CTMFAULTPARASEX) != NULL)
	{
		strIDPath = pData->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
	}

	return AddPara(strIDPath);
}

CExBaseObject* CMacroTestParaDatas::AddPara(const CString &strID)
{
	CMacroTestParaData* pPara = NULL;

	pPara = (CMacroTestParaData*)FindParaById(strID);

	if (pPara == NULL)
	{
		pPara = new CMacroTestParaData;
		pPara->SetParent(this);
		AddTail(pPara);
		pPara->m_strName = strID;
		pPara->m_strID = strID;
	}

	return pPara;
}

void CMacroTestParaDatas::SetToDatasValue(CTestMacro* pTestMacro, BOOL bUseDefaultVal)
{
	POS pos = GetHeadPosition();
	CShortData  *pData = NULL;
	long nIndex = 0;
	CMacroTestParaData *pPara = NULL;

	CExBaseList listNew, listDelete, listChanged;

	while (pos != NULL)
	{
		pPara = (CMacroTestParaData*)GetNext(pos);
		pTestMacro->OnSetParaValue(pPara->m_strID, pPara->m_strExpression, listNew, listDelete, listChanged);
		listNew.RemoveAll();
		listDelete.DeleteAll();

		// 		if (pPara == NULL)
		// 		{
		// 			if (bUseDefaultVal)
		// 			{
		// 				pData->m_strValue = pData->m_strDefaultValue;
		// 			}
		// 		}
		// 		else
		// 		{
		// 			pPara->SetToDataValue(pData);
		// 		}
	}

	pTestMacro->ResetDatas(listChanged);

	listChanged.RemoveAll();
}

void CMacroTestParaDatas::SetToDatasValue(CShortDatas *pDatas, BOOL bUseDefaultVal)
{
	POS pos = GetHeadPosition();
	CShortData  *pData = NULL;
	long nCount = pDatas->GetCount();
	long nIndex = 0;
	CMacroTestParaData *pPara = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pData = (CShortData*)pDatas->GetAtIndex(nIndex);

		SetToDatasValue(pData, 0, bUseDefaultVal);
	}
}

void CMacroTestParaDatas::SetToDatasValue(CShortData *pData, UINT nRootClassID, BOOL bUseDefaultVal)
{
	CMacroTestParaData *pPara = NULL;
	
	if (nRootClassID == 0)
	{
		pPara = (CMacroTestParaData*)FindByID(pData->m_strID);
	}
	else
	{
		pPara = (CMacroTestParaData*)FindByID(pData->GetIDPathEx(nRootClassID, FALSE));
	}

	if (pPara == NULL)
	{
		if (bUseDefaultVal)
		{
			pData->m_strValue = pData->m_strDefaultValue;
		}
	}
	else
	{
		pPara->SetToDataValue(pData);
	}
}

void CMacroTestParaDatas::SetToDatasValue(CDataGroup *pDataGroup, UINT nRootClassID, BOOL bUseDefaultVal)
{
	POS pos = GetHeadPosition();
	long nCount = pDataGroup->GetCount();
	long nIndex = 0;
	CExBaseObject *pObj = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObj = pDataGroup->GetAtIndex(nIndex);
		UINT nClassID = pObj->GetClassID();

		if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			SetToDatasValue((CShortData *)pObj, nRootClassID, bUseDefaultVal);
		}
		else if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			SetToDatasValue((CDataGroup *)pObj, nRootClassID, bUseDefaultVal);
		}
	}
}

void CMacroTestParaDatas::ResetMacroTestParaData()
{
	DeleteAll();
}

void CMacroTestParaDatas::UpdateMacroTestParaData(const CShortData  *pData, BOOL bShowLog, BOOL bUseDefaultValue)
{
	CMacroTestParaData *pPara = NULL;
	CString strTemp;
	CString strIDPath = pData->m_strID;
	CShortData *pTemp = (CShortData*)pData;

	if (pTemp->GetAncestor(TMCLASSID_CTMFAULTPARASEX) != NULL)
	{
		strIDPath = pTemp->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
	}

	if (bUseDefaultValue)
	{
		if (pData->m_strValue == pData->m_strDefaultValue)
		{
			pPara = (CMacroTestParaData*)FindByID(strIDPath);

			if (pPara != NULL)
			{
				strTemp = pPara->m_strExpression;
				Delete(pPara);
			}
		}
		else
		{
			pPara = (CMacroTestParaData*)AddPara(strIDPath);
			strTemp = pPara->m_strExpression;
			pPara->SetExpression(pData->m_strValue);
		}
	}
	else
	{
		pPara = (CMacroTestParaData*)AddPara(strIDPath);
		strTemp = pPara->m_strExpression;
		pPara->SetExpression(pData->m_strValue);
	}

	if (!bShowLog)
	{
		return;
	}

	CExBaseObject *p = (CExBaseObject*)GetAncestor(GBCLASSID_MACROTEST);
	CString strMacro;

	if (p != NULL)
	{
		strMacro = p->m_strName;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ParaMdf2.GetString()/*_T("[%s]²ÎÊýÐÞ¸Ä£º [%s] ==[%s] ->[%s]")*/
		, strMacro.GetString(), pData->m_strName.GetString(), strTemp.GetString(), pData->m_strValue.GetString());
}

void CMacroTestParaDatas::UpdateMacroTestParaData(const CString &strID, const CString &strValue, BOOL bShowLog, BOOL bUseDefaultValue)
{
	CMacroTestParaData *pPara = NULL;
	pPara = (CMacroTestParaData*)AddPara(strID);
	pPara->SetExpression(strValue);
}

void CMacroTestParaDatas::UpdateMacroTestParaDatas()
{
	POS pos = GetHeadPosition();
	POS posPrev = NULL;
	CExBaseObject* pObj = NULL;

	while(pos != NULL)
	{
		posPrev = pos;
		pObj = GetNext(pos);

		if (pObj->m_strID.GetLength() == 0 && pObj->m_strName.GetLength() == 0)
		{
			delete pObj;
			RemoveAt(posPrev);
		}
	}
}

void CMacroTestParaDatas::UpdateMacroTestParaDataUser(const CShortData  *pData)
{
	CMacroTestParaData *pPara = NULL;

	pPara = (CMacroTestParaData*)FindByID(pData->m_strID);

	if (pPara == NULL)
	{
		pPara = (CMacroTestParaData*)AddPara(pData->m_strID);
	}

	pPara->AddMacroTestParaDataUser(pData->m_strValue);
}

CExBaseObject* CMacroTestParaDatas::FindMacroTestParaData(const CShortData  *pData)
{
	CMacroTestParaData *pFind = (CMacroTestParaData*)FindByID(pData->m_strID);

	return pFind;
}


BOOL CMacroTestParaDatas::GetParaValue(const CString &strID, double &dValue)
{
	CMacroTestParaData *pFind = (CMacroTestParaData*)FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	dValue = CString_To_double(pFind->m_strExpression);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CMacroTestParaDatasUser
CMacroTestParaDatasUser::CMacroTestParaDatasUser()
{

}

CMacroTestParaDatasUser::~CMacroTestParaDatasUser()
{

}

CBaseObject* CMacroTestParaDatasUser::Clone()
{
	CMacroTestParaDatasUser *pNew = new CMacroTestParaDatasUser();
	Copy(pNew);
	return pNew;
}


