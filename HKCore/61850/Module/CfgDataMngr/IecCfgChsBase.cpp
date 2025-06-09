//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsBase.cpp  CIecCfgChsBase


#include "stdafx.h"
#include "IecCfgChsBase.h"

CIecCfgChsBase::CIecCfgChsBase()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgChsBase::~CIecCfgChsBase()
{
}

long CIecCfgChsBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgChsBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgChsBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgChsBase *p = (CIecCfgChsBase*)pObj;

	return TRUE;
}

BOOL CIecCfgChsBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgChsBase *p = (CIecCfgChsBase*)pDest;

	return TRUE;
}


void CIecCfgChsBase::RemoveTailCh(long nCountRemove, CExBaseList &oListRemove)
{
	CIecCfgDataChBase *pCh = CreateChannel();
	ASSERT (pCh != NULL);
	RemoveTail(pCh->GetClassID(), nCountRemove, oListRemove);
	delete pCh;
}

BOOL CIecCfgChsBase::SetChannelNum(long nChannelNum)
{
	long nOldNum = GetCount();

	if (nChannelNum == nOldNum)
	{
		return FALSE;
	}

	if (nOldNum > nChannelNum)
	{
		CExBaseList oListRemove;
		RemoveTailCh(nOldNum - nChannelNum, oListRemove);
		oListRemove.DeleteAll();
		return TRUE;
	}

	long nIndex = 0;
	long nCount = nChannelNum - nOldNum;
	CIecCfgDataChBase *pCh = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pCh = CreateChannel();
		pCh->m_nIndex = nIndex+nOldNum;
		pCh->InitCh();
		AddNewChild(pCh);
	}

	return TRUE;
}

 void CIecCfgChsBase::InitChs()
 {
	 POS pos = GetHeadPosition();
	 CIecCfgDataChBase *p = NULL;
	 long nIndex = 0;

	 while (pos != NULL)
	 {
		p = (CIecCfgDataChBase*)GetNext(pos);
		p->m_nIndex = nIndex;
		p->InitCh();
		nIndex++;
	 }
 }

long CIecCfgChsBase::GetChannels(CExBaseList &oListCh)
{
	CIecCfgDataChBase *pCh = CreateChannel();
	ASSERT (pCh != NULL);
	UINT cChClassID = pCh->GetClassID();
	delete pCh;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == cChClassID)
		{
			oListCh.AddTail(p);
		}
	}

	return oListCh.GetCount();
}


long CIecCfgChsBase::GetUsedChsCount()
{
	CIecCfgDataChBase *pCh = CreateChannel();
	ASSERT (pCh != NULL);
	UINT cChClassID = pCh->GetClassID();
	delete pCh;
	long nCount = 0;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCh = (CIecCfgDataChBase*)GetNext(pos);

		if (pCh->GetClassID() == cChClassID)
		{
			if (pCh->m_strAppChID != g_strAppChID_None)
			{
				nCount++;
			}
		}
	}

	return nCount;
}
