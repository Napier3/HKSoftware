//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataAnalog.cpp  CIecCfgDataAnalog


#include "stdafx.h"
#include "IecCfgDataAnalog.h"

CIecCfgDataAnalog::CIecCfgDataAnalog()
{
	//初始化属性
	m_nDataUse = 0;
}

CIecCfgDataAnalog::~CIecCfgDataAnalog()
{
}

long CIecCfgDataAnalog::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDatasUseKey, oNode, m_nDataUse);

	return 0;
}

long CIecCfgDataAnalog::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDatasUseKey, oElement, m_nDataUse);

	return 0;
}

BOOL CIecCfgDataAnalog::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDataAnalog *p = (CIecCfgDataAnalog*)pObj;

	if(m_nDataUse != p->m_nDataUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDataAnalog::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataBase::CopyOwn(pDest);

	CIecCfgDataAnalog *p = (CIecCfgDataAnalog*)pDest;
	p->m_nDataUse = m_nDataUse;

	return TRUE;
}

CExBaseObject* CIecCfgDataAnalog::Clone()
{
	CIecCfgDataAnalog *p = new CIecCfgDataAnalog();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgDataAnalog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChsAnalogKey)
	{
		pNew = new CIecCfgChsAnalog();
	}


	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

void CIecCfgDataAnalog::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHSANALOG);
// 	CIecCfgDataBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfgChsAnalog();
		AddNewChild(m_pCfgChs);
	}
}

// 
// void CIecCfgDataAnalog::CalArtAmpDigdatas(CArtAmpDigdatas *pArtAmpDigdatas, long &nHdCnIndex)
// {
// 	POS pos = m_pCfgChs->GetHeadPosition();
// 	CIecCfgDataChBase *pCh = NULL;
// 	CArtAmpDigdata *pData = NULL;
// 	nHdCnIndex = 0;
// 	static long arrnHdIndex[] = {0x0A,0x0B,0x08,0x02,0x07,0x01,0x06,0x00,0x09,0x3,0x04,0x05};
// 
// 	while (pos != NULL)
// 	{
// 		pCh = (CIecCfgDataChBase *)m_pCfgChs->GetNext(pos);
// 
// 		if (pCh == NULL)
// 		{
// 			break;
// 		}
// 
// 		pData = pArtAmpDigdatas->AddArtAmpDigdata2(pCh->m_strAppChID, arrnHdIndex[nHdCnIndex]);
// 
// 		if (pData == NULL)
// 		{
// 			break;
// 		}
// 
// 		pCh->SetArtAmpDigdata(pData);
// 
// 		if (pCh->IsAppCh())
// 		{
// 				pData->m_nDigFlag = 1;
// 				pData->m_dwHcnCal = arrnHdIndex[nHdCnIndex];
// 				pCh->InitArtAmpDigdata(pData);
// 				pCh->CalMagAndOffset(pData);
// 		}
// 
// 		nHdCnIndex++;
// 	}
// }
