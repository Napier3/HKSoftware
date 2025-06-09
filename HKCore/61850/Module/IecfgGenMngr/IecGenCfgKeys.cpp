//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgKeys.cpp  CIecGenCfgKeys


#include "stdafx.h"
#include "IecGenCfgKeys.h"
#include "../CfgDataMngr/IecCfgGoutCh.h"
#include "../CfgDataMngr/IecCfg92Ch.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgKeys::CIecGenCfgKeys()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgKeys::~CIecGenCfgKeys()
{
}

long CIecGenCfgKeys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgKeys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgKeys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecGenCfgKeys::InitAfterRead()
{
}

BOOL CIecGenCfgKeys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecGenCfgKeys *p = (CIecGenCfgKeys*)pObj;

	return TRUE;
}

BOOL CIecGenCfgKeys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecGenCfgKeys *p = (CIecGenCfgKeys*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgKeys::Clone()
{
	CIecGenCfgKeys *p = new CIecGenCfgKeys();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgKeys::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgKeys *p = new CIecGenCfgKeys();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgKeys::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenCfgKeys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgKeyKey)
	{
		pNew = new CIecGenCfgKey();
	}

	return pNew;
}

CExBaseObject* CIecGenCfgKeys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGKEY)
	{
		pNew = new CIecGenCfgKey();
	}

	return pNew;
}
CExBaseObject* CIecGenCfgKeys::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIecGenCfgKey();

	return pNew;
}

void CIecGenCfgKeys::GetKeys(CStringArray &astrDesc)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);
		astrDesc.Add(pCurObj->m_strName);
	}
}

CIecCfgDataBase* CIecGenCfgKeys::FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase)
{
	POS pos = pIecCfgDatasBase->GetHeadPosition();
	CIecCfgDataBase *pIecCfgDataBase = NULL;
	CIecCfg92Ch *pIecCfg92Ch = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	CString strMatchString;

	while (pos != NULL)
	{
		pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasBase->GetNext(pos);

		if (pIecCfgDatasBase->IsCfgData(pIecCfgDataBase->GetClassID()))
		{
			CIecCfgDataChBase* pCfgDataCh = NULL;
			ASSERT(pIecCfgDataBase->m_pCfgChs);

			POS pos_ch = pIecCfgDataBase->m_pCfgChs->GetHeadPosition();

			while(pos_ch)
			{
				pCfgDataCh = (CIecCfgDataChBase*)pIecCfgDataBase->m_pCfgChs->GetNext(pos_ch);
				strMatchString = pCfgDataCh->m_strName;

				if (pCfgDataCh->GetClassID() == CFGCLASSID_CIECCFG92CH)
				{
					pIecCfg92Ch = (CIecCfg92Ch *)pCfgDataCh;
					strMatchString += pIecCfg92Ch->m_strDescExternal;
				}
				else if (pCfgDataCh->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
				{
					pIecCfgGoutCh = (CIecCfgGoutCh *)pCfgDataCh;
					strMatchString += pIecCfgGoutCh->m_strDescExternal;
				}

				if (IsMatchSuccess(strMatchString))
				{
					return pIecCfgDataBase;
				}
			}
		}
	}

	return NULL;
}

BOOL CIecGenCfgKeys::IsMatchSuccess(const CString &strName)
{
	POS pos = GetHeadPosition();
	CIecGenCfgKey *pCurObj = NULL;

	while(pos)
	{
		pCurObj = (CIecGenCfgKey*)GetNext(pos);

		if (pCurObj->IsMatchSuccess(strName)/*strName.Find(pCurObj->m_strName)>=0*/)
		{
			return TRUE;
		}
	}

	return FALSE;
}