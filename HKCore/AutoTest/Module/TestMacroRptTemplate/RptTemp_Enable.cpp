//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Enable.cpp  CRptTemp_Enable


#include "stdafx.h"
#include "RptTemp_Enable.h"
#include <math.h>
#include "../../Module/DataMngr/DvmData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CRptTemp_ParaOptr::CRptTemp_ParaOptr()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_ParaOptr::~CRptTemp_ParaOptr()
{
}

long CRptTemp_ParaOptr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strCRptTemp_ValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CRptTemp_ParaOptr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strCRptTemp_ValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CRptTemp_ParaOptr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CRptTemp_ParaOptr::InitAfterRead()
{
}

BOOL CRptTemp_ParaOptr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_ParaOptr *p = (CRptTemp_ParaOptr*)pObj;

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_ParaOptr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_ParaOptr *p = (CRptTemp_ParaOptr*)pDest;

	p->m_strOptr = m_strOptr;
	p->m_strValue = m_strValue;
	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CRptTemp_ParaOptr::Clone()
{
	CRptTemp_ParaOptr *p = new CRptTemp_ParaOptr();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ParaOptr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ParaOptr *p = new CRptTemp_ParaOptr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ParaOptr::IsEnable(CExBaseList *pParas)
{
	if (pParas == NULL)
	{
		return FALSE;
	}

	CDvmData *pData = (CDvmData*)pParas->FindByID(m_strID);

	if (pData == NULL)
	{
		pData = (CDvmData *)pParas->FindByIDPathEx(DTMCLASSID_CDATAGROUP, FALSE, m_strID);

		if (pData == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("使能失败！找不到参数【%s】"), m_strID.GetString());
			return FALSE;
		}
	}

	double dValue = CString_To_double(m_strValue);
	double dDataValue = CString_To_double(pData->m_strValue);

	if (IsEnable_Optr_Eql())
	{
		return ( (fabs(dValue - dDataValue)) <= 0.000001 );
	}
	else if (IsEnable_Optr_UnEql())
	{
		return ( (fabs(dValue - dDataValue)) > 0.000001 );
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRptTemp_Enable::CRptTemp_Enable()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_Enable::~CRptTemp_Enable()
{
}

long CRptTemp_Enable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	return 0;
}

long CRptTemp_Enable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	return 0;
}

long CRptTemp_Enable::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
	}
	return 0;
}

void CRptTemp_Enable::InitAfterRead()
{
}

BOOL CRptTemp_Enable::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Enable *p = (CRptTemp_Enable*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Enable::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Enable *p = (CRptTemp_Enable*)pDest;

	p->m_strMode = m_strMode;
	return TRUE;
}

CBaseObject* CRptTemp_Enable::Clone()
{
	CRptTemp_Enable *p = new CRptTemp_Enable();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Enable::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Enable *p = new CRptTemp_Enable();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Enable::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_PARAOPTR)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Enable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ParaOptrKey)
	{
		pNew = new CRptTemp_ParaOptr();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_EnableKey)
	{
		pNew = new CRptTemp_Enable();
	}
	return pNew;
}

CExBaseObject* CRptTemp_Enable::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_PARAOPTR)
	{
		pNew = new CRptTemp_ParaOptr();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		pNew = new CRptTemp_Enable();
	}

	return pNew;
}

BOOL CRptTemp_Enable::IsEnable(CExBaseList *pParas)
{
	if (IsEnableMode_And())
	{
		return IsEnable_And(pParas);
	}

	if (IsEnableMode_Or())
	{
		return IsEnable_Or(pParas);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Invalid Enable Mode  [%s]"), m_strMode.GetString());
	return FALSE;
}

//And模式下，要求所有的数据都使能成功
BOOL CRptTemp_Enable::IsEnable_And(CExBaseList *pParas)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	BOOL bEnable = FALSE;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_PARAOPTR)
		{
			CRptTemp_ParaOptr *pParaOptr = (CRptTemp_ParaOptr *)pObj;
			bEnable = pParaOptr->IsEnable(pParas);
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			CRptTemp_Enable *pEnable = (CRptTemp_Enable *)pObj;
			bEnable = pEnable->IsEnable(pParas);
		}
		
		if (!bEnable)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//Or模式下，只要有一个数据使能成功即可
BOOL CRptTemp_Enable::IsEnable_Or(CExBaseList *pParas)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	BOOL bEnable = TRUE;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_PARAOPTR)
		{
			CRptTemp_ParaOptr *pParaOptr = (CRptTemp_ParaOptr *)pObj;
		bEnable = pParaOptr->IsEnable(pParas);
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			CRptTemp_Enable *pEnable = (CRptTemp_Enable *)pObj;
			bEnable = pEnable->IsEnable(pParas);
		}

		if (bEnable)
		{
			break;
		}
	}

	return bEnable;
}
