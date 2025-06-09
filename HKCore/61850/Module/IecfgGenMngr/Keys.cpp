//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Keys.cpp  CKeys


#include "stdafx.h"
#include "Keys.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CKeys::CKeys()
{
	//初始化属性

	//初始化成员变量
}

CKeys::~CKeys()
{
}

long CKeys::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CKeys::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CKeys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CKeys::InitAfterRead()
{
}

BOOL CKeys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CKeys *p = (CKeys*)pObj;

	return TRUE;
}

BOOL CKeys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CKeys *p = (CKeys*)pDest;

	return TRUE;
}

CBaseObject* CKeys::Clone()
{
	CKeys *p = new CKeys();
	Copy(p);
	return p;
}

CBaseObject* CKeys::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CKeys *p = new CKeys();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CKeys::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CKeys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCKeyKey)
	{
		pNew = new CKey();
	}

	return pNew;
}

CExBaseObject* CKeys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CKEY)
	{
		pNew = new CKey();
	}

	return pNew;
}
CExBaseObject* CKeys::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CKey();

	return pNew;
}

void CKeys::GetKeys(CStringArray &astrDesc)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);
		astrDesc.Add(pCurObj->m_strName);
	}
}

CIecCfgDataBase* CKeys::FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase)
{
	POS pos = pIecCfgDatasBase->GetHeadPosition();
	CIecCfgDataBase *pIecCfgDataBase = NULL;

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

				if (IsMatchSuccess(pCfgDataCh->m_strName))
				{
					return pIecCfgDataBase;
				}
			}
		}
	}

	return NULL;
}

BOOL CKeys::IsMatchSuccess(const CString &strName)
{
	POS pos = GetHeadPosition();
	CKey *pCurObj = NULL;

	while(pos)
	{
		pCurObj = (CKey*)GetNext(pos);

		if (pCurObj->IsMatchSuccess(strName)/*strName.Find(pCurObj->m_strName)>=0*/)
		{
			return TRUE;
		}
	}

	return FALSE;
}