//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawList.cpp  CXDrawList


#include "stdafx.h"
#include "XDrawList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawList::CXDrawList()
{
	//初始化属性

	//初始化成员变量
}

CXDrawList::~CXDrawList()
{
}

long CXDrawList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);

	return 0;
}

long CXDrawList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}

long CXDrawList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

BOOL CXDrawList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXDrawList *p = (CXDrawList*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CXDrawList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawList *p = (CXDrawList*)pDest;

	p->m_strID = m_strID;

	return TRUE;
}

CBaseObject* CXDrawList::Clone()
{
	CXDrawList *p = new CXDrawList();
	Copy(p);
	return p;
}

BOOL CXDrawList::CanPaste(UINT nClassID)
{
	if (nClassID == DWCLASSID_CXDRAWARC)
	{
		return TRUE;
	}

	if (nClassID == DWCLASSID_CXDRAWCIRCLE)
	{
		return TRUE;
	}

	if (nClassID == DWCLASSID_CXDRAWLINE)
	{
		return TRUE;
	}

	if (nClassID == DWCLASSID_CXDRAWPOINT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXDrawList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXDrawArcKey)
	{
		pNew = new CXDrawArc();
	}
	else if (strClassID == pXmlKeys->m_strCXDrawCircleKey)
	{
		pNew = new CXDrawCircle();
	}
	else if (strClassID == pXmlKeys->m_strCXDrawLineKey)
	{
		pNew = new CXDrawLine();
	}
	else if (strClassID == pXmlKeys->m_strCXDrawLineRKey)
	{
		pNew = new CXDrawLineR();
	}
	else if (strClassID == pXmlKeys->m_strCXDrawPointKey)
	{
		pNew = new CXDrawPoint();
	}
	else if (strClassID == pXmlKeys->m_strCXDrawListKey)
	{
		pNew = new CXDrawList();
	}

	return pNew;
}

CExBaseObject* CXDrawList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DWCLASSID_CXDRAWARC)
	{
		pNew = new CXDrawArc();
	}
	else if (nClassID == DWCLASSID_CXDRAWCIRCLE)
	{
		pNew = new CXDrawCircle();
	}
	else if (nClassID == DWCLASSID_CXDRAWLINE)
	{
		pNew = new CXDrawLine();
	}
	else if (nClassID == DWCLASSID_CXDRAWLINER)
	{
		pNew = new CXDrawLineR();
	}
	else if (nClassID == DWCLASSID_CXDRAWPOINT)
	{
		pNew = new CXDrawPoint();
	}
	else if (nClassID == DWCLASSID_CXDRAWLIST)
	{
		pNew = new CXDrawList();
	}

	return pNew;
}

void CXDrawList::SetPickState(BOOL bPick)
{
	CXDrawElement::SetPickState(bPick);
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->SetPickState(bPick);
	}
}

void CXDrawList::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->LogicPointToDevicePoint(pAxis);
	}
}

void CXDrawList::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->Draw(pDC, fZoomRatio, ptOffset);
	}
}

void CXDrawList::Pick(const CPoint &point, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->Pick(point, oList);
	}
}

void CXDrawList::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->GetLogicBorder(fMinX, fMinY, fMaxX, fMaxY);
	}
}

CXDrawPoint* CXDrawList::AddPoint(double x, double y)
{
	CXDrawPoint *p = new CXDrawPoint();
	p->m_fX = x;
	p->m_fY = y;
	AddNewChild(p);
	return p;
}

CXDrawText* CXDrawList::AddText(double x, double y, double w, double h, const CString &strText)
{
	CXDrawText *p = new CXDrawText();
	p->m_fX = x;
	p->m_fY = y;
	p->m_fWidth = w;
	p->m_fHeight = h;
	p->m_strText = strText;

	AddNewChild(p);
	return p;
}

void CXDrawList::InitDrawLineColor(const COLORREF &oColor)
{
	POS pos = GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase*)GetNext(pos);
		p->m_crForeColor = oColor;
	}
}

