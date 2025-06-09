//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawList.cpp  CXDrawElements


#include "stdafx.h"
#include "XDrawElements.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawElements::CXDrawElements()
{
	//初始化属性

	//初始化成员变量
}

CXDrawElements::~CXDrawElements()
{
}
// 
// long CXDrawElements::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
// 	return 0;
// }
// 
// long CXDrawElements::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
// 	return 0;
// }
// 
// long CXDrawElements::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 		BinarySerializeCalLen(oBinaryBuffer, m_strID);
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 		BinarySerializeRead(oBinaryBuffer, m_strID);
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 		BinarySerializeWrite(oBinaryBuffer, m_strID);
// 	}
// 	return 0;
// }
// 
// BOOL CXDrawElements::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	CXDrawElements *p = (CXDrawElements*)pObj;
// 
// 	if(m_strID != p->m_strID)
// 	{
// 		return FALSE;
// 	}
// 
// 
// 	return TRUE;
// }
// 
// BOOL CXDrawElements::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
// 
// 	CXDrawElements *p = (CXDrawElements*)pDest;
// 
// 	p->m_strID = m_strID;
// 
// 	return TRUE;
// }
// 
// CBaseObject* CXDrawElements::Clone()
// {
// 	CXDrawElements *p = new CXDrawElements();
// 	Copy(p);
// 	return p;
// }
// 
// BOOL CXDrawElements::CanPaste(UINT nClassID)
// {
// 	if (nClassID == DWCLASSID_CXDRAWARC)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (nClassID == DWCLASSID_CXDRAWCIRCLE)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (nClassID == DWCLASSID_CXDRAWLINE)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (nClassID == DWCLASSID_CXDRAWPOINT)
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }
// 
// CBaseObject* CXDrawElements::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CBaseObject *pNew  = NULL;
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 
// 	if (strClassID == pXmlKeys->m_strCXDrawArcKey)
// 	{
// 		pNew = new CXDrawArc();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCXDrawCircleKey)
// 	{
// 		pNew = new CXDrawCircle();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCXDrawLineKey)
// 	{
// 		pNew = new CXDrawLine();
// 	}
// 	else if (strClassID == pXmlKeys->m_strCXDrawPointKey)
// 	{
// 		pNew = new CXDrawPoint();
// 	}
// 
// 	return pNew;
// }
// 
// CBaseObject* CXDrawElements::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CBaseObject *pNew  = NULL;
// 
// 
// 	if (nClassID == DWCLASSID_CXDRAWARC)
// 	{
// 		pNew = new CXDrawArc();
// 	}
// 	else if (nClassID == DWCLASSID_CXDRAWCIRCLE)
// 	{
// 		pNew = new CXDrawCircle();
// 	}
// 	else if (nClassID == DWCLASSID_CXDRAWLINE)
// 	{
// 		pNew = new CXDrawLine();
// 	}
// 	else if (nClassID == DWCLASSID_CXDRAWPOINT)
// 	{
// 		pNew = new CXDrawPoint();
// 	}
// 
// 	return pNew;
// }
// 
// void CXDrawElements::LogicPointToDevicePoint(CAxisInterface *pAxis)
// {
// 	POS pos = GetHeadPosition();
// 	CXDrawElement *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CXDrawElement*)GetNext(pos);
// 		p->LogicPointToDevicePoint(pAxis);
// 	}
// }

void CXDrawElements::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawElement*)GetNext(pos);
		p->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
}

void CXDrawElements::Pick(const CPoint &point, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;

	if (!IsPointInRect(point))
	{
		return;
	}

	while (pos != NULL)
	{
		p = (CXDrawElement*)GetNext(pos);

		if (XDraw_Is_XDrawElement(p))
		{
			p->Pick(point, oList);
		}
	}
}

DWORD CXDrawElements::XCreateElementChildren(CExBaseList *pDatas, CWnd *pParentWnd)
{
	POS pos = pDatas->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXDrawElement *pNew = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDatas->GetNext(pos);
		pNew = XCreateChildElement(p, pParentWnd);

		if (pNew != NULL)
		{
			AddNewChild(pNew);
		}

		pNew->XCreateElement(p, pParentWnd);
	}

	return XCREATE_SUCC;
}

CSize CXDrawElements::CalLayoutChildren(CSize &szDraw)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawElement *)GetNext(pos);
		p->CalLayout(szDraw);
	}

	return szDraw;
}

void CXDrawElements::GetSize(CSize &sz, DWORD dwMode)
{
	sz.cx = sz.cy = 0;
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;
	CSize szElement;

	if (GETSIZE_MODE_XMAX_YADD == dwMode)
	{
		while (pos != NULL)
		{
			p = (CXDrawElement *)GetNext(pos);
			p->GetSize(szElement, dwMode);
			sz.cx = max(sz.cx, szElement.cx);
			sz.cy += szElement.cy;
		}
	}
	else if (GETSIZE_MODE_XADD_YMAX == dwMode)
	{
		while (pos != NULL)
		{
			p = (CXDrawElement *)GetNext(pos);
			p->GetSize(szElement, dwMode);
			sz.cx += szElement.cx;
			sz.cy = max(sz.cy, szElement.cy);
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = (CXDrawElement *)GetNext(pos);
			p->GetSize(szElement, dwMode);
			sz.cx += szElement.cx;
			sz.cy += szElement.cy;
		}
	}
}

CXDrawElement* CXDrawElements::QueryChildrenByXDrawDataRef(CExBaseObject *pDrawDataRef)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;
	CXDrawElement *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXDrawElement *)GetNext(pos);
		pFind = p->QueryByXDrawDataRef(pDrawDataRef);

		if (pFind != NULL)
		{
			break;
		}

	}

	return pFind;
}

