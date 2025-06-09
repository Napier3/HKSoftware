//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenState.cpp  CUibGenState


#include "stdafx.h"
#include "UibGenState.h"

CUibGenState::CUibGenState()
{
	//初始化属性
	m_fTimeLong = 0;
	m_nMode = 0;

	//初始化成员变量
}

CUibGenState::~CUibGenState()
{
}

long CUibGenState::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTimeLongKey, oNode, m_fTimeLong);
	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_nMode);
	return 0;
}

long CUibGenState::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTimeLongKey, oElement, m_fTimeLong);
	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_nMode);
	return 0;
}

long CUibGenState::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fTimeLong);
		BinarySerializeCalLen(oBinaryBuffer, m_nMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fTimeLong);
		BinarySerializeRead(oBinaryBuffer, m_nMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fTimeLong);
		BinarySerializeWrite(oBinaryBuffer, m_nMode);
	}
	return 0;
}

void CUibGenState::InitAfterRead()
{
}

BOOL CUibGenState::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUibGenState *p = (CUibGenState*)pObj;

	if(m_fTimeLong != p->m_fTimeLong)
	{
		return FALSE;
	}

	if(m_nMode != p->m_nMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUibGenState::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUibGenState *p = (CUibGenState*)pDest;

	p->m_fTimeLong = m_fTimeLong;
	p->m_nMode = m_nMode;
	return TRUE;
}

CBaseObject* CUibGenState::Clone()
{
	CUibGenState *p = new CUibGenState();
	Copy(p);
	return p;
}

BOOL CUibGenState::CanPaste(UINT nClassID)
{
	if (nClassID == UIBGCLASSID_CUIBGENANALOG)
	{
		return TRUE;
	}

	if (nClassID == UIBGCLASSID_CUIBGENBINARY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUibGenState::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUibGenAnalogKey)
	{
		pNew = new CUibGenAnalog();
	}
	else if (strClassID == pXmlKeys->m_strCUibGenBinaryKey)
	{
		pNew = new CUibGenBinary();
	}

	return pNew;
}

CExBaseObject* CUibGenState::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UIBGCLASSID_CUIBGENANALOG)
	{
		pNew = new CUibGenAnalog();
	}
	else if (nClassID == UIBGCLASSID_CUIBGENBINARY)
	{
		pNew = new CUibGenBinary();
	}

	return pNew;
}


void CUibGenState::Generate(long &nUibGenIndex, long nSampRate)
{
	POS pos = GetHeadPosition();
	CUibChGenInterface *pCh = NULL;
	float fCount = m_fTimeLong * nSampRate;
	long nCount = (long)fCount;
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pCh = (CUibChGenInterface *)GetNext(pos);
			pCh->Generate(nUibGenIndex, nIndex);
		}

		nUibGenIndex++;
	}
}

void CUibGenState::InitGenerate(double dCoef_FreqAngleT)
{
	POS pos = GetHeadPosition();
	CUibChGenInterface *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CUibChGenInterface *)GetNext(pos);
		pCh->InitGenerate(dCoef_FreqAngleT);
	}
}

void CUibGenState::InitGenerate(long nChIndex, unsigned short *pnAttachBuffer)
{
	POS pos = GetHeadPosition();
	CUibChGenInterface *pCh = NULL;

	pCh = (CUibChGenInterface *)GetAtIndex(nChIndex);

	if (pCh != NULL)
	{
		pCh->m_pnAttachBuffer = pnAttachBuffer;
	}
}

void CUibGenState::GetAnalogs(CExBaseList &listAnalogs)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == UIBGCLASSID_CUIBGENANALOG)
		{
			listAnalogs.AddTail(p);
		}
	}
}

void CUibGenState::GetBinarys(CExBaseList &listBinarys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == UIBGCLASSID_CUIBGENBINARY)
		{
			listBinarys.AddTail(p);
		}
	}
}

