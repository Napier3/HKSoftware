// BaseList.cpp: implementation of the CBaseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseList::CBaseList()
{

}

CBaseList::~CBaseList()
{
	DeleteAll();
}

void CBaseList::Append(CBaseList &oListSrc)
{
	POS pos = oListSrc.GetHeadPosition();
	CBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		AddTail(pObj);
	}
}

void CBaseList::AppendClone(CBaseList &oListSrc)
{
	POS pos = oListSrc.GetHeadPosition();
	CBaseObject *pObj = NULL;
	CBaseObject *pObjNew = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		pObjNew = (CBaseObject*)pObj->Clone();
		AddTail(pObjNew);
	}
}

CBaseObject* CBaseList::CreateNewChild(CXmlRWNodeBase &oNode, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CString strNodeName;
	strNodeName = oNode.GetNodeName();
	return CreateNewChild(strNodeName, bAddToTail, pXmlRWKeys);
}

CBaseObject* CBaseList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)    {    return NULL;     }
CBaseObject* CBaseList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)            {    return NULL;     }

CBaseObject* CBaseList::AddNew(long nClassID)
{
	CBaseObject *pNew = CreateNewChild(nClassID);

	if (pNew != NULL)
	{
		pNew->SetParent(this);
		AddTail(pNew);
	}

	return pNew;
}


long CBaseList::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	long nCount = oNodes.GetNodeNum();
	long nIndex = 0;
	CBaseObject *pNew = NULL;
	CXmlRWNodeBase *pNode = NULL;
	CString strNodeName;
	BOOL bAddToTail = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNode = oNodes.GetChild(nIndex);

		if (pNode == NULL)
		{
			continue;
		}

		pNew = CreateNewChild(*pNode, bAddToTail, pXmlRWKeys);

		if (pNew != NULL && bAddToTail)
		{
			pNew->SetParent(this);
			AddNode(pNew);
		}

		if (pNew)
		{
			pNew->XmlRead(*pNode, pXmlRWKeys);
		}

		bAddToTail = TRUE;
	}

	return 0;
}

//WriteXml
long CBaseList::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


long CBaseList::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	CBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nClassID = 0;
	long nCount = 0;
	long nIndex = 0;
	
	if (oBinaryBuffer.IsCalSizeMode())
	{
		nCount = GetCount();
		oBinaryBuffer.AddBufferLength(sizeof(nCount));
		oBinaryBuffer.AddBufferLength(sizeof(nClassID) * nCount);

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			pObj = GetNext(pos);
			pObj->Serialize(oBinaryBuffer);
		}
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		nCount = oBinaryBuffer.GetLong();
		
		for (nIndex=0;nIndex<nCount;nIndex++)
		{
			nClassID = oBinaryBuffer.GetLong();
			pObj = CreateNewChild(nClassID);
			ASSERT (pObj != NULL);
			pObj->SetParent(this);
			pObj->Serialize(oBinaryBuffer);
			AddNode(pObj);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		nCount = GetCount();
		oBinaryBuffer.PutLong(nCount);
		
		while (pos)
		{
			pObj = GetNext(pos);
			nClassID = pObj->GetClassID();
			oBinaryBuffer.PutLong(nClassID);
			pObj->Serialize(oBinaryBuffer);
		}
	}
	
	return 0;
}


BOOL CBaseList::CopyChildren(CBaseObject* pDest)
{
	if (pDest->IsBaseObject() || IsBaseObject())
	{
		return FALSE;
	}

	CBaseList *pList = (CBaseList*)pDest;
	CBaseObject *pObj = NULL;
	CBaseObject *pNew = NULL;
	POS pos = GetHeadPosition();
	pList->DeleteAll();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pNew = pObj->Clone();
		if (pNew != NULL)
		{
			pList->AddTail(pNew);
			pNew->SetParent(pList);
		}
	}

	return TRUE;
}


BOOL CBaseList::IsEqualChildren(CBaseObject* pObj)
{
	if (pObj->IsBaseObject() && IsBaseObject())
	{
		return TRUE;
	}

	if (pObj->IsBaseObject() || IsBaseObject())
	{
		return FALSE;
	}

	CBaseList *pList = (CBaseList*)pObj;
	CBaseObject *pObja = NULL, *pObjb = NULL;

	if (GetCount() != pList->GetCount())
	{
		return FALSE;
	}

	POS posa = GetHeadPosition();
	POS posb = pList->GetHeadPosition();

	while (posa != NULL && posb != NULL)
	{
		pObja = GetNext(posa);
		pObjb = GetNext(posb);
		ASSERT(pObja != NULL);
		ASSERT(pObjb != NULL);
		if (pObja->IsEqual(pObj) == FALSE)
		{
			return FALSE;
		}
	}

	if (posa == NULL && posb == NULL)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CBaseList::CanPaste(UINT nClassID)
{
	return FALSE;
}

BOOL CBaseList::CanPaste(CBaseObject *pObj)
{
	if (pObj == NULL)	
	{
		return FALSE;
	}

	return CanPaste(pObj->GetClassID());
}

BOOL CBaseList::CanPaste(CBaseList *pList)
{
	CBaseObject *pObj = NULL;
	POS pos = pList->GetHeadPosition();
	BOOL bCanPaste = TRUE;

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);

		if (!CanPaste(pObj))
		{
			bCanPaste = FALSE;
			break;
		}
	}

	return bCanPaste;
}

CBaseObject* CBaseList::Paste(CBaseObject *pObj)
{
	if (!CanPaste(pObj))
	{
		return NULL;
	}

	CBaseObject *pNew = (CBaseObject*)pObj->Clone();
	AddNewChild(pNew);

	return pNew;
}

CBaseObject* CBaseList::Paste(CBaseList *pList)
{
	if (!CanPaste(pList))
	{
		return NULL;
	}

	CBaseObject *pNew = NULL;
	CBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();
	
	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		pNew = (CBaseObject*)p->Clone();
		AddNewChild(pNew);
	}
	
	return pNew;
}

CBaseObject* CBaseList::Clone()
{
	CBaseList *pList = new CBaseList();
	Copy(pList);
	return pList;
}

CBaseObject* CBaseList::AddNewChild(CBaseObject *pNew)
{
	AddTail(pNew);
	pNew->SetParent(this);
	return pNew;
}

CBaseObject* CBaseList::FindByClassID(DWORD dwClassID)
{
	CBaseObject *p = NULL;
	CBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (dwClassID == p->GetClassID())
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}
