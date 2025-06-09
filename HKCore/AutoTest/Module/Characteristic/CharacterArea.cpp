//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterArea.cpp  CCharacterArea


#include "stdafx.h"
#include "CharacterArea.h"
#include "Characteristic.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#include "../GuideBook/GuideBookDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharacterArea::CCharacterArea()
{
	//初始化属性
	m_pCharBisector = new CCharElement();
	m_pCharBisector->SetParent(this);

	m_pUserDefTestDef = new CCharElement();
	m_pUserDefTestDef->SetParent(this);

	//初始化成员变量
	m_pDrawListRef = NULL;
	m_bAutoClose = TRUE;
	m_bHasSerializeChildren = FALSE;
	m_bDrawListRefOwn = FALSE;

	m_pTestLines = NULL;
	m_bUseIntersectionTestPoint = /*FALSE*/ TRUE; 
}

CCharacterArea::~CCharacterArea()
{
	if (m_pCharBisector != NULL)
	{
		delete m_pCharBisector;
		m_pCharBisector = NULL;
	}

	if(m_pUserDefTestDef != NULL)
	{
		delete m_pUserDefTestDef;
		m_pUserDefTestDef = NULL;
	}

	if (m_bDrawListRefOwn)
	{
		delete m_pDrawListRef;
		m_pDrawListRef = NULL;
	}

	if (m_pTestLines != NULL)
	{
		delete m_pTestLines;
		m_pTestLines = NULL;
	}
}

long CCharacterArea::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacterArea::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacterArea::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_pTestLines != NULL)
	{
		AddNewChild(m_pTestLines);
	}

	CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);

	if (m_pTestLines != NULL)
	{
		Remove(m_pTestLines);
	}

	return 0;
}

/*
2020-08-04  李俊庆
原因未明，应该是某个时间，修改程序的时候不注意，导致
m_pUserDefTestDef对象与CCharacterArea存储的时候出现冲突，因此做异常处理
*/
long CCharacterArea::Serialize(CBinarySerialBuffer &oBinaryBuffer)
{
	m_bHasSerializeChildren = FALSE;
	SerializeOwn(oBinaryBuffer);

	if (!m_bHasSerializeChildren)
	{
		if (m_pTestLines != NULL)
		{
			AddNewChild(m_pTestLines);
		}

		SerializeChildren(oBinaryBuffer);

		if (m_pTestLines != NULL)
		{
			Remove(m_pTestLines);
		}
	}

	if (oBinaryBuffer.IsReadMode())
	{
		InitAfterRead();
	}

	return 0;
}

long CCharacterArea::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		m_pCharBisector->Serialize(oBinaryBuffer);
		m_pUserDefTestDef->Serialize(oBinaryBuffer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_35)
		{
			m_pCharBisector->Serialize(oBinaryBuffer);
			long nPos = oBinaryBuffer.Tell();
			BOOL bError = FALSE;

			try
			{
				m_pUserDefTestDef->Serialize(oBinaryBuffer);
			}
			catch (...)
			{
				bError = TRUE;
			}
			
			if (bError)
			{
				oBinaryBuffer.SeekTo(nPos);
				SerializeChildren(oBinaryBuffer);
				m_bHasSerializeChildren = TRUE;
			}
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		m_pCharBisector->Serialize(oBinaryBuffer);
		m_pUserDefTestDef->Serialize(oBinaryBuffer);
	}

	return 0;
}

BOOL CCharacterArea::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacterArea *p = (CCharacterArea*)pObj;

	return TRUE;
}

BOOL CCharacterArea::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacterArea *p = (CCharacterArea*)pDest;

	return TRUE;
}

CBaseObject* CCharacterArea::Clone()
{
	CCharacterArea *p = new CCharacterArea();
	Copy(p);
	return p;
}

CBaseObject* CCharacterArea::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCharacterArea *p = new CCharacterArea();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCharacterArea::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARELEMENTLENS)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARC)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARCD)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTARCP)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINE)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINED)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTLINER)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTMHO)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacterArea::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharElementLensKey)
	{
		pNew = new CCharElementLens();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcKey)
	{
		pNew = new CCharElementArc();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcdKey)
	{
		pNew = new CCharElementArcd();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementArcpKey)
	{
		pNew = new CCharElementArcp();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLineKey)
	{
		pNew = new CCharElementLine();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLinepKey)
	{
		pNew = new CCharElementLinep();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLinedKey)
	{
		pNew = new CCharElementLined();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLinerKey)
	{
		pNew = new CCharElementLiner();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementMhoKey)
	{
		pNew = new CCharElementMho();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementI2TKey)
	{
		pNew = new CCharElementI2T();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementIACKey)
	{
		pNew = new CCharElementIAC();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementIECKey)
	{
		pNew = new CCharElementIEC();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementIEEEKey)
	{
		pNew = new CCharElementIEEE();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementInvOwnDefKey) //自定义曲线
	{
		pNew = new CCharElementInvOwnDef();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementUIVPKey) //sf 20211213
	{
		pNew = new CCharElementUIVP();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementDCOverLoadKey) //cl20230912
	{
		pNew = new CCharElementDCOverLoad();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementIUFKey) 
	{
		pNew = new CCharElementIUF();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementTestLinesKey)
	{
		pNew = new CCharElementTestLines();
	}
	

	return pNew;
}

CExBaseObject* CCharacterArea::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARELEMENTLENS)
	{
		pNew = new CCharElementLens();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARC)
	{
		pNew = new CCharElementArc();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARCD)
	{
		pNew = new CCharElementArcd();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTARCP)
	{
		pNew = new CCharElementArcp();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINE)
	{
		pNew = new CCharElementLine();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINED)
	{
		pNew = new CCharElementLined();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLINER)
	{
		pNew = new CCharElementLiner();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTMHO)
	{
		pNew = new CCharElementMho();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTI2T)
	{
		pNew = new CCharElementI2T();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTIAC)
	{
		pNew = new CCharElementIAC();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTIEC)
	{
		pNew = new CCharElementIEC();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTIEEE)
	{
		pNew = new CCharElementIEEE();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTINVOWNDEF) //自定义曲线
	{
		pNew = new CCharElementInvOwnDef();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTUIVP) //sf 20211213
	{
		pNew = new CCharElementUIVP();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTDCOVERLOAD) //cl20230912
	{
		pNew = new CCharElementDCOverLoad();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTIUF) 
	{
		pNew = new CCharElementIUF();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
	{
		pNew = new CCharElementTestLines();
	}
	return pNew;
}

long CCharacterArea::InsertToListCtrl(CListCtrl *pListCtrl)
{
	CString strElementIndex;
	CString strXml;
	CCharElement *pObj;
	long lItemIndex = 0;

	pListCtrl->DeleteAllItems();

	POS pos = GetHeadPosition();
	while(pos)
	{
		pObj =(CCharElement *)GetNext(pos);

		UINT nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		strElementIndex.Format(_T("%d"), lItemIndex+1);
		strXml = pObj->ReturnXml();
		pListCtrl->InsertItem( lItemIndex,strElementIndex );
		pListCtrl->SetItemText(lItemIndex, 1, strXml);
		pListCtrl->SetItemData(lItemIndex, (DWORD)pObj);
		lItemIndex ++;
	}
	return lItemIndex;
}


long CCharacterArea::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("Num"));
	pListCtrl->SetColumnWidth(0, 66);

#ifndef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(1, g_sLangTxt_ParaCurve/*_T("曲线参数")*/);
#else
	pListCtrl->InsertColumn(1, _T("曲线参数"));
#endif

	pListCtrl->SetColumnWidth(1, 250);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

void CCharacterArea::InitAfterRead()
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			CCharElementTestLines *pTestLines = (CCharElementTestLines *)pObj;
			m_pTestLines = pTestLines;

			Remove(pTestLines);
		}
	}
}

BOOL CCharacterArea::CopyChildren(CBaseObject* pDest)
{
	if (m_pTestLines != NULL)
	{
		AddNewChild(m_pTestLines);
	}

	BOOL bRet = CExBaseList::CopyChildren(pDest);

	if (m_pTestLines != NULL)
	{
		Remove(m_pTestLines);
	}

	return bRet;
}

BOOL CCharacterArea::IsAutoclose()
{
	CCharacteristic *pCharacteristic = (CCharacteristic*)GetParent();
	ASSERT (pCharacteristic != NULL);

	return pCharacteristic->IsAutoclose();
}

void CCharacterArea::CalCharElement(CExBaseList *pDrawList, UINT nTestLineMode)
{
	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		pCharElement = (CCharElement *)pObj;/*GetNext(pos);*/
		pCharElement->CalByExpression(FALSE, pDrawList);
	}

	//2020-03-10 lijq
	//CalTestLines(nTestLineMode);
}

void CCharacterArea::CalTestLines(UINT nTestLineMode)
{
	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	long nCharElementID = 1;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		pCharElement = (CCharElement *)pObj;/*GetNext(pos);*/
		pCharElement->m_nCharElementID = nCharElementID;

		pCharElement->BeforeCalTestLines();
		pCharElement->CalTestLines(nTestLineMode);
		nCharElementID++;
	}

	if (m_nCount < 1)
	{
		return;
	}

	if (m_nCount == 1)
	{
		InitCharDrawElementsLine((CCharElement*)GetHead(), nTestLineMode);
		return;
	}

	pos = GetHeadPosition();
	pObj = GetNext(pos);
	nClassID = pObj->GetClassID();

	while (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
	{
		//这个类对象，不是从CCharElement派生的，过滤掉
		pObj = GetNext(pos);
	}

	CCharElement *pCharElementPrev = (CCharElement *)pObj/*GetNext(pos)*/;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		pCharElement = (CCharElement *)pObj/*GetNext(pos)*/;
		//lijq 2020-3-12
		//InitCharDrawElementsLine(pCharElementPrev, pCharElement, nTestLineMode);
		InitCharDrawElementsLineEx(pCharElementPrev, pCharElement, nTestLineMode);
		pCharElementPrev = pCharElement;
	}

	pCharElement = GetFirstCharElemet();
	
	if (IsAutoclose())
	{
		//lijq 2020-3-12
		//InitCharDrawElementsLine(pCharElementPrev, pCharElement, nTestLineMode);
		InitCharDrawElementsLineEx(pCharElementPrev, pCharElement, nTestLineMode);
	}
}

void CCharacterArea::InitCharDrawElementsLine(CCharElement *pChar1, CCharElement *pChar2, UINT nTestLineMode)
{
	UINT nClassID1 = pChar1->GetClassID();
	UINT nClassID2 = pChar2->GetClassID();

	double dErrLen = max(pChar1->m_dErrLength , pChar2->m_dErrLength);

	if (nClassID1 == CHARCLASSID_CCHARELEMENTLINED && nClassID2 == CHARCLASSID_CCHARELEMENTLINED)
	{
		InitCharDrawLined2Line((CCharElementLined*)pChar1, (CCharElementLined*)pChar2, dErrLen, nTestLineMode);
	}
	else if (nClassID1 == CHARCLASSID_CCHARELEMENTLINED && nClassID2 == CHARCLASSID_CCHARELEMENTLINER)
	{
		InitCharDrawLined2Line((CCharElementLined*)pChar1, (CCharElementLiner*)pChar2, dErrLen, nTestLineMode);
	}
}

void char_Get_Char_XDrawDataBase(CCharElement *pChar, CXDrawDataBase* &pDrawData)
{
	ASSERT (pChar != NULL);
	ASSERT (pChar->m_pDataRef != NULL);

	if (pChar->m_pDataRef == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("char [%s] m_pDataRef == NULL"), pChar->m_strID.GetString());
		return;
	}

	UINT nClassID = pChar->m_pDataRef->GetClassID();

	switch (nClassID)
	{
	case DWCLASSID_CXDRAWLINE:
		pDrawData = (CXDrawLine*)pChar->m_pDataRef;
		{
			CXDrawData_Line *pLine = (CXDrawData_Line*)pDrawData;
			pLine->Init_K_B_by_XY();
		}
		break;

	case DWCLASSID_CXDRAWARC:
		pDrawData = (CXDrawArc*)pChar->m_pDataRef;
		break;

	case DWCLASSID_CXDRAWCIRCLE:
		pDrawData = (CXDrawCircle*)pChar->m_pDataRef;
		break;

	default:
		pDrawData = NULL;
	}
}

void CCharacterArea::InitCharDrawElementsLineEx(CCharElement *pChar1, CCharElement *pChar2, UINT nTestLineMode)
{
	UINT nClassID1 = pChar1->GetClassID();
	UINT nClassID2 = pChar2->GetClassID();
	CXDrawDataBase *pDrawData1 = NULL;
	CXDrawDataBase *pDrawData2 = NULL;
	
	char_Get_Char_XDrawDataBase(pChar1, pDrawData1);
	char_Get_Char_XDrawDataBase(pChar2, pDrawData2);
	
	double dErrLen = max(pChar1->m_dErrLength , pChar2->m_dErrLength);

	if (pDrawData1 == NULL || pDrawData2 == NULL)
	{
		return;
	}

	long nTestLineID = char_GetTestLineID(pChar1, pChar2);

	if (m_bUseIntersectionTestPoint)
	{
	if(nTestLineMode == CHAR_TESTLINE_MODE_INDEX_VERT)
	{
		InitCharDrawElementsLineEx_Vert(pDrawData1, pDrawData2, dErrLen, nTestLineID);
		return;
	}
	else if (nTestLineMode == CHAR_TESTLINE_MODE_INDEX_HORZ)
	{
		InitCharDrawElementsLineEx_Horz(pDrawData1, pDrawData2, dErrLen, nTestLineID);
		return;
	}

	DWORD dwDrawType1 = pDrawData1->GetDrawDataType();
	DWORD dwDrawType2 = pDrawData2->GetDrawDataType();

	switch (dwDrawType1)
	{
	case XDRAW_DATA_LINE:
		switch (dwDrawType2)
		{
		case XDRAW_DATA_LINE:
			InitCharDrawElementsLineEx((CXDrawData_Line*)pDrawData1, (CXDrawData_Line*)pDrawData2, dErrLen, nTestLineMode, nTestLineID);
			break;

		case XDRAW_DATA_ARC:
			InitCharDrawElementsLineEx((CXDrawData_Line*)pDrawData1, (CXDrawData_Arc*)pDrawData2, dErrLen, nTestLineMode, nTestLineID);
			break;

		}
		break;

	case XDRAW_DATA_ARC:
		switch (dwDrawType2)
		{
		case XDRAW_DATA_LINE:
			InitCharDrawElementsLineEx((CXDrawData_Arc*)pDrawData1, (CXDrawData_Line*)pDrawData2, dErrLen, nTestLineMode, nTestLineID);
			break;

		case XDRAW_DATA_ARC:
			InitCharDrawElementsLineEx((CXDrawData_Arc*)pDrawData1, (CXDrawData_Arc*)pDrawData2, dErrLen, nTestLineMode, nTestLineID);
			break;

		}
		break;

	}
	}
	
// 	if (nClassID1 == CHARCLASSID_CCHARELEMENTLINED && nClassID2 == CHARCLASSID_CCHARELEMENTLINED)
// 	{
// 		InitCharDrawLined2Line((CCharElementLined*)pChar1, (CCharElementLined*)pChar2, dErrLen, nTestLineMode);
// 	}
// 	else if (nClassID1 == CHARCLASSID_CCHARELEMENTLINED && nClassID2 == CHARCLASSID_CCHARELEMENTLINER)
// 	{
// 		InitCharDrawLined2Line((CCharElementLined*)pChar1, (CCharElementLiner*)pChar2, dErrLen, nTestLineMode);
// 	}
}

void CCharacterArea::InitCharDrawElementsLineEx(CXDrawData_Line *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID)
{
	double x, y;
	pDrawData1->GetEndPoint(x, y);

	//垂线与直线的平分线
	InitCharDrawElementsLineEx_Plumb(x, y, pDrawData1, pDrawData2, dErrLen, nTestLineID);

// 	double dX1 = pDrawData1->m_fXb - pDrawData1->m_fXe;
// 	double dY1 = pDrawData1->m_fYb - pDrawData1->m_fYe;
// 	double dX2 = pDrawData2->m_fXe - pDrawData2->m_fXb;
// 	double dY2 = pDrawData2->m_fYe - pDrawData2->m_fYb;
// 
// 	CComplexNumber oC1(dX1, dY1);
// 	CComplexNumber oC2(dX2, dY2);
// 
// 	double dAngle1 = oC1.GetRadianAngle();
// 	double dAngle2 = oC2.GetRadianAngle();
// 	double dAngle = (dAngle1 + dAngle2) / 2;
// 	CComplexNumber oC3(dErrLen, dAngle, COMPLEX_MODE_RADIAN);
// 
// 	CCharElementTestLine *pTestLine = AddTestLine(nTestLineID);//new CCharElementTestLine();
// 	oC3.GetValue(pTestLine->m_fXb, pTestLine->m_fYb);
// 	oC3.Rotate(180);
// 	oC3.GetValue(pTestLine->m_fXe, pTestLine->m_fYe);
// 
// 	pTestLine->m_fXb += pDrawData1->m_fXe;
// 	pTestLine->m_fXe += pDrawData1->m_fXe;
// 	pTestLine->m_fYb += pDrawData1->m_fYe;
// 	pTestLine->m_fYe += pDrawData1->m_fYe;
// 
// 	pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
// 	pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
}

void CCharacterArea::InitCharDrawElementsLineEx(CXDrawData_Line *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID)
{
	double x, y;
	pDrawData1->GetEndPoint(x, y);
	InitCharDrawElementsLineEx(x, y, pDrawData1, pDrawData2, dErrLen, nTestLineMode, nTestLineID);
}

void CCharacterArea::InitCharDrawElementsLineEx(CXDrawData_Arc *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID)
{
	double x, y;
	pDrawData1->GetEndPoint(x, y);
	InitCharDrawElementsLineEx(x, y, pDrawData2, pDrawData1, dErrLen, nTestLineMode, nTestLineID);
}

void CCharacterArea::InitCharDrawElementsLineEx(CXDrawData_Arc *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID)
{
	double x, y;
	pDrawData1->GetEndPoint(x, y);

	//圆弧在x、y点的切线
	CXDrawData_Line oLine1, oLine2;
	pDrawData1->GetTangent(x, y, oLine1);
	pDrawData2->GetTangent(x, y, oLine2);

	//垂线与直线的平分线
	InitCharDrawElementsLineEx_Plumb(x, y, &oLine1, &oLine2, dErrLen, nTestLineID);
}

void CCharacterArea::InitCharDrawElementsLineEx_Plumb(double x, double y, CXDrawData_Line *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, long nTestLineID)
{
	double dAngle1 = pDrawData1->m_fAngle;
	double dAngle2 = pDrawData2->m_fAngle;
	MakeAngleTo360(dAngle1);
	MakeAngleTo360(dAngle2);
	double dAngle = (dAngle1 + dAngle2) / 2;
	CComplexNumber oError(dErrLen, dAngle, COMPLEX_MODE_DEGREE);
	oError.Rotate(-90);
	double x2, y2;
	oError.GetValue(x2, y2);

	CCharElementTestLine *pTestLine = AddTestLine(nTestLineID);//new CCharElementTestLine();
	pTestLine->m_fXset = x;
	pTestLine->m_fYset = y;

	pTestLine->m_fXb = x + x2;
	pTestLine->m_fXe = x - x2;

	pTestLine->m_fYb = y + y2;
	pTestLine->m_fYe = y - y2;
}

void CCharacterArea::InitCharDrawElementsLineEx(double x, double y, CXDrawData_Line *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID)
{
	//圆弧在x、y点的切线
	CXDrawData_Line oLine2;
	pDrawData2->GetTangent(x, y, oLine2);

	//垂线与直线的平分线
	InitCharDrawElementsLineEx_Plumb(x, y, pDrawData1, &oLine2, dErrLen, nTestLineID);
}

void CCharacterArea::InitCharDrawElementsLineEx_Vert(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, double dErrLen, long nTestLineID)
{
	CCharElementTestLine *pTestLine = AddTestLine(nTestLineID);
	double x, y;
	pDrawData1->GetEndPoint(x, y);
	
	pTestLine->m_fXset = x;
	pTestLine->m_fYset = y;

	pTestLine->m_fXb = x;
	pTestLine->m_fXe = x;
	pTestLine->m_fYb = y + dErrLen;
	pTestLine->m_fYe = y - dErrLen;
}

void CCharacterArea::InitCharDrawElementsLineEx_Horz(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, double dErrLen, long nTestLineID)
{
	CCharElementTestLine *pTestLine = AddTestLine(nTestLineID);
	double x, y;
	pDrawData1->GetEndPoint(x, y);

	pTestLine->m_fXset = x;
	pTestLine->m_fYset = y;

	pTestLine->m_fXb = x + dErrLen;
	pTestLine->m_fXe = x - dErrLen;
	pTestLine->m_fYb = y;
	pTestLine->m_fYe = y;
}

void CCharacterArea::InitCharDrawLined2Line(CCharElementLined *pXLine1, CCharElementLined *pXLine2, double dErrorLen, UINT nTestLineMode)
{
	BOOL bEqual = TRUE;

	if (!math_IsEqual(pXLine1->m_fXe, pXLine2->m_fXb))
	{
		bEqual = FALSE;
	}

	if (!math_IsEqual(pXLine1->m_fYe, pXLine2->m_fYb))
	{
		bEqual = FALSE;
	}

	if (!bEqual)
	{
		return;
	}

	switch(nTestLineMode)
	{
	case CHAR_TESTLINE_MODE_INDEX_PLUMB:
		InitCharDrawLined2Line_Plumb(pXLine1, pXLine2, dErrorLen);
		break;

	case CHAR_TESTLINE_MODE_INDEX_VERT:
		InitCharDrawLined2Line_Vert(pXLine1, pXLine2, dErrorLen);
		break;

	case CHAR_TESTLINE_MODE_INDEX_HORZ:
		InitCharDrawLined2Line_Horz(pXLine1, pXLine2, dErrorLen);
		break;

	default:
		InitCharDrawLined2Line_Plumb(pXLine1, pXLine2, dErrorLen);
		break;
	}
}


void CCharacterArea::InitCharDrawLined2Line(CCharElementLined *pXLine1, CCharElementLiner *pXLine2, double dErrorLen, UINT nTestLineMode)
{
	CCharElementLined oLined;
	oLined.m_fXb = pXLine2->m_fXb;
	oLined.m_fYb = pXLine2->m_fYb;
	oLined.m_fXe = oLined.m_fXb + pXLine2->m_fLengthUse * cos(pXLine2->m_fAngle * _PI_D_180);
	oLined.m_fYe = oLined.m_fYb + pXLine2->m_fLengthUse * sin(pXLine2->m_fAngle * _PI_D_180);
	InitCharDrawLined2Line(pXLine1, &oLined, dErrorLen, nTestLineMode);
}


void CCharacterArea::InitCharDrawLined2Line_Plumb(CCharElementLined *pXLine1, CCharElementLined *pXLine2, double dErrorLen)
{
	double dX1 = pXLine1->m_fXb - pXLine1->m_fXe;
	double dY1 = pXLine1->m_fYb - pXLine1->m_fYe;
	double dX2 = pXLine2->m_fXe - pXLine2->m_fXb;
	double dY2 = pXLine2->m_fYe - pXLine2->m_fYb;

	CComplexNumber oC1(dX1, dY1);
	CComplexNumber oC2(dX2, dY2);

	double dAngle1 = oC1.GetRadianAngle();
	double dAngle2 = oC2.GetRadianAngle();
	double dAngle = (dAngle1 + dAngle2) / 2;
	CComplexNumber oC3(dErrorLen, dAngle, COMPLEX_MODE_RADIAN);

	CCharElementTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharElementTestLine();
	oC3.GetValue(pTestLine->m_fXb, pTestLine->m_fYb);
	oC3.Rotate(180);
	oC3.GetValue(pTestLine->m_fXe, pTestLine->m_fYe);

	pTestLine->m_fXb += pXLine1->m_fXe;
	pTestLine->m_fXe += pXLine1->m_fXe;
	pTestLine->m_fYb += pXLine1->m_fYe;
	pTestLine->m_fYe += pXLine1->m_fYe;

	pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
	pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
}

void CCharacterArea::InitCharDrawLined2Line_Vert(CCharElementLined *pXLine1, CCharElementLined *pXLine2, double dErrorLen)
{
// 	BOOL bEqual = TRUE;
// 
// 	if (!math_IsEqual(pXLine1->m_fXe, pXLine2->m_fXb))
// 	{
// 		bEqual = FALSE;
// 	}
// 
// 	if (!math_IsEqual(pXLine1->m_fYe, pXLine2->m_fYb))
// 	{
// 		bEqual = FALSE;
// 	}
// 
// 	if (!bEqual)
// 	{
// 		return;
// 	}

	CCharElementTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharElementTestLine();

	//dErrorLen /= 2;
	pTestLine->m_fXset = pXLine1->m_fXe;
	pTestLine->m_fYset = pXLine1->m_fYe;

	pTestLine->m_fXb = pTestLine->m_fXset;
	pTestLine->m_fXe = pTestLine->m_fXset;
	pTestLine->m_fYb = pTestLine->m_fYset + dErrorLen;
	pTestLine->m_fYe = pTestLine->m_fYset - dErrorLen;
}

void CCharacterArea::InitCharDrawLined2Line_Horz(CCharElementLined *pXLine1, CCharElementLined *pXLine2, double dErrorLen)
{
// 	BOOL bEqual = TRUE;
// 
// 	if (!math_IsEqual(pXLine1->m_fXe, pXLine2->m_fXb))
// 	{
// 		bEqual = FALSE;
// 	}
// 
// 	if (!math_IsEqual(pXLine1->m_fYe, pXLine2->m_fYb))
// 	{
// 		bEqual = FALSE;
// 	}
// 
// 	if (!bEqual)
// 	{
// 		return;
// 	}

	double dX1 = pXLine1->m_fXb - pXLine1->m_fXe;
	double dY1 = pXLine1->m_fYb - pXLine1->m_fYe;
	double dX2 = pXLine2->m_fXe - pXLine2->m_fXb;
	double dY2 = pXLine2->m_fYe - pXLine2->m_fYb;

	CComplexNumber oC1(dX1, dY1);
	CComplexNumber oC2(dX2, dY2);

	double dAngle1 = oC1.GetRadianAngle();
	double dAngle2 = oC2.GetRadianAngle();
	double dAngle = (dAngle1 + dAngle2) / 2;
	CComplexNumber oC3(dErrorLen, dAngle, COMPLEX_MODE_RADIAN);

	CCharElementTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharElementTestLine();
	oC3.GetValue(pTestLine->m_fXb, pTestLine->m_fYb);
	oC3.Rotate(180);
	oC3.GetValue(pTestLine->m_fXe, pTestLine->m_fYe);

	pTestLine->m_fXb += pXLine1->m_fXe;
	pTestLine->m_fXe += pXLine1->m_fXe;
	pTestLine->m_fYb += pXLine1->m_fYe;
	pTestLine->m_fYe += pXLine1->m_fYe;

	pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
	pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
}

void CCharacterArea::GetAllMacroTestLines(CExBaseList *pList)
{
	POS pos = GetHeadPosition();
	CCharElement *pElement = NULL;

	while (pos != NULL)
	{
		pElement = (CCharElement *)pList->GetNext(pos);
		pList->Append(pElement);
	}

	if (m_pCharBisector != NULL)
	{
		pList->Append(m_pCharBisector);
	}

	//xujinqiang0327: 需要加上m_pUserDefTestDef吗？
}

void CCharacterArea::InitCharDrawElementsLine(CCharElement *pChar, UINT nTestLineMode)
{
	if (pChar->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
	{
		InitCharDrawElementsLine((CCharElementLens*)pChar, nTestLineMode);
	}
}

void CCharacterArea::InitCharDrawElementsLine(CCharElementLens *pCharLens, UINT nTestLineMode)
{
	long nTestLineID = 65537;
	CComplexNumber c1(pCharLens->m_fForwardReach+pCharLens->m_dErrLength, pCharLens->m_fAngle, COMPLEX_MODE_DEGREE);
	CCharElementTestLine *pTestLine = NULL;
	
	pTestLine = AddTestLine(nTestLineID);
	c1.GetValue(pTestLine->m_fXb, pTestLine->m_fYb);
	c1.SetValueAngle(pCharLens->m_fForwardReach, pCharLens->m_fAngle, COMPLEX_MODE_DEGREE);
	c1.GetValue(pTestLine->m_fXset, pTestLine->m_fYset);
	c1.SetValueAngle(pCharLens->m_fForwardReach - pCharLens->m_dErrLength, pCharLens->m_fAngle, COMPLEX_MODE_DEGREE);
	c1.GetValue(pTestLine->m_fXe, pTestLine->m_fYe);

	nTestLineID = 65538;
	pTestLine = AddTestLine(nTestLineID);
	c1.SetValueAngle(pCharLens->m_fOffset+pCharLens->m_dErrLength, pCharLens->m_fAngle-180, COMPLEX_MODE_DEGREE);
	c1.GetValue(pTestLine->m_fXb, pTestLine->m_fYb);
	c1.SetValueAngle(pCharLens->m_fOffset, pCharLens->m_fAngle-180, COMPLEX_MODE_DEGREE);
	c1.GetValue(pTestLine->m_fXset, pTestLine->m_fYset);
	c1.SetValueAngle(pCharLens->m_fOffset - pCharLens->m_dErrLength, pCharLens->m_fAngle-180, COMPLEX_MODE_DEGREE);
	c1.GetValue(pTestLine->m_fXe, pTestLine->m_fYe);
}

CCharElementTestLine* CCharacterArea::FindBisectorTestLine(long nTestLineID)
{
	POS pos = m_pCharBisector->GetHeadPosition();
	CCharElementTestLine *p = NULL;
	CCharElementTestLine *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCharElementTestLine *)m_pCharBisector->GetNext(pos);

		if (p->m_nTestLineID == nTestLineID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CCharacterArea::InitTestLineID(CCharElementTestLine *pTestLine, CCharElement *pChar1, CCharElement *pChar2)
{
	long nTestLineID = char_GetTestLineID(pChar1, pChar2);
	pTestLine->m_nTestLineID = nTestLineID;
}

CCharElementTestLine* CCharacterArea::AddTestLine(CCharElement *pChar1, CCharElement *pChar2)
{
	long nTestLineID = char_GetTestLineID(pChar1, pChar2);
	return AddTestLine(nTestLineID);
}

CCharElementTestLine* CCharacterArea::AddTestLine(long nTestLineID)
{
	CCharElementTestLine *pFind = FindBisectorTestLine(nTestLineID);

	if (pFind == NULL)
	{
		pFind = new CCharElementTestLine();
		pFind->m_nTestLineID = nTestLineID;
		m_pCharBisector->AddNewChild(pFind);
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//
CExBaseList* CCharacterArea::CreateDrawListRef()
{
	if (m_pDrawListRef != NULL)
	{
		return m_pDrawListRef;
	}

	m_pDrawListRef = new CXDrawList();
	m_bDrawListRefOwn = TRUE;

	return m_pDrawListRef;
}

CExBaseList* CCharacterArea::DettachDrawListRef()
{
	if (m_bDrawListRefOwn)
	{
		m_bDrawListRefOwn = FALSE;
		return m_pDrawListRef;
	}
	else
	{
		return NULL;
	}
}

void CCharacterArea::InitCharDrawElement(CXDrawList *pDrawList, BOOL bCalTestLines)
{
	if (NeedSolvEqation())
	{
		return InitCharDrawElement_Equation(pDrawList, bCalTestLines);
	}

	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pCharElement = (CCharElement *)GetNext(pos);
		nClassID = pCharElement->GetClassID();

		switch(nClassID)
		{
		case CHARCLASSID_CCHARELEMENTLINED:
			InitCharDrawElement_LineD(pDrawList, (CCharElementLined*)pCharElement, bCalTestLines);
			break;

		case CHARCLASSID_CCHARELEMENTLINER:
			InitCharDrawElement_LineR(pDrawList, (CCharElementLiner*)pCharElement, bCalTestLines);
			break;

		case CHARCLASSID_CCHARELEMENTMHO:
			InitCharDrawElement_Mho(pDrawList, (CCharElementMho*)pCharElement, bCalTestLines);
			break;

		case CHARCLASSID_CCHARELEMENTLENS:
			InitCharDrawElement_Lens(pDrawList, (CCharElementLens*)pCharElement, bCalTestLines);
			break;

		case CHARCLASSID_CCHARELEMENTI2T:
		case CHARCLASSID_CCHARELEMENTIAC:
		case CHARCLASSID_CCHARELEMENTIEC:
		case CHARCLASSID_CCHARELEMENTIEEE:
		case CHARCLASSID_CCHARELEMENTINVOWNDEF:
		case CHARCLASSID_CCHARELEMENTUIVP://20211220 sf
		case CHARCLASSID_CCHARELEMENTDCOVERLOAD://20230912 cl
		case CHARCLASSID_CCHARELEMENTIUF:
			InitCharDrawElement_Inverse(pDrawList, (CCharElementInverse*)pCharElement, bCalTestLines);
			break;
		}

	}

	if (!bCalTestLines)
	{
		return ;
	}

	InitCharDrawElementTestLines(pDrawList, GetCharBisector());
}

void CCharacterArea::InitCharDrawElementTestLines(CXDrawList *pDrawList)
{
	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		pCharElement = (CCharElement *)pObj/*GetNext(pos)*/;
		InitCharDrawElementTestLines(pDrawList, pCharElement);
	}

	InitCharDrawElementTestLines(pDrawList, GetCharBisector());
}

BOOL CCharacterArea::NeedSolvEqation()
{
	BOOL bNeedSolvEquation = FALSE;
	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pCharElement = (CCharElement *)GetNext(pos);
		nClassID = pCharElement->GetClassID();

		if (    nClassID == CHARCLASSID_CCHARELEMENTLINE
			|| nClassID == CHARCLASSID_CCHARELEMENTLINER
			|| nClassID == CHARCLASSID_CCHARELEMENTLINE
			|| nClassID == CHARCLASSID_CCHARELEMENTARC
			|| nClassID == CHARCLASSID_CCHARELEMENTARCP)
		{
			bNeedSolvEquation = TRUE;
			break;
		}
	}

	return bNeedSolvEquation;
}

void Solv_CharElement_Equation(CCharElement* &pCharElement1, CCharElement *pCharElement2
							 , CXDrawDataBase* &pDrawData1, CXDrawDataBase *pDrawData2
							 , CXDrawBase* &pDrawElement1, CXDrawBase *pDrawElement2
							 , CXDrawList *pDrawList)
{
	CXDrawDatas listDatas;
	CXDrawData_Point oPoint(0, 0);
	CXDrawData_Point *pPoint = NULL;

	if (pDrawElement2 == NULL)
	{
		pDrawElement2 = pCharElement2->CreateDrawElement();
		pDrawList->AddNewChild(pDrawElement2);
	}

	pDrawData2 = pCharElement2->GetCXDrawDataBase();
	xdraw_SolveEquation(pDrawData1, pDrawData2, listDatas);

	if (listDatas.GetCount() == 0)
	{
		pDrawElement1->SetEndPoint(0, 0);
		pDrawElement2->SetBeginPoint(0, 0);
		pDrawElement1 = pDrawElement2;
		pDrawData1 = pDrawData2;
		return;
	}

	pDrawData1 = pDrawData2;

	if (listDatas.GetCount() == 1)
	{
		pPoint = (CXDrawData_Point *)listDatas.GetHead();
	}
	else//交点数大于1时,此时定只有2个曲线,且已形成闭合区域
	{
		if ((pDrawElement2->GetClassID() == DWCLASSID_CXDRAWARC)||
			(pDrawElement2->GetClassID() == DWCLASSID_CXDRAWARC))//20230408 zhouhj 特性曲线的交点数大于1,且第2个曲线为圆弧或者圆的情况下,获取第二个点,进行处理
		{
			pPoint = (CXDrawData_Point *)listDatas.GetTail();
		} 
		else
		{
			pPoint = (CXDrawData_Point *)listDatas.GetHead();
		}
// 		CXDrawData_Point *pPoint1 = (CXDrawData_Point *)listDatas.GetHead();
// 		CXDrawData_Point *pPoint2 = (CXDrawData_Point *)listDatas.GetTail();
// 
// 		if (pDrawElement1->GetClassID() == DWCLASSID_CXDRAWARC)
// 		{
// 		}
// 
// 		pDrawElement1->SetEndPoint(pPoint1->m_fX, pPoint1->m_fY);
// 		pDrawElement2->SetBeginPoint(pPoint1->m_fX, pPoint1->m_fY);
// 
// 		pDrawElement1->SetBeginPoint(pPoint2->m_fX, pPoint2->m_fY);
// 		pDrawElement2->SetEndPoint(pPoint2->m_fX, pPoint2->m_fY);
	}
	
 	pDrawElement1->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
 	pDrawElement2->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
	pDrawElement1 = pDrawElement2;
}

void CCharacterArea::InitCharDrawElement_Equation(CXDrawList *pDrawList, BOOL bCalTestLines)
{
	//暂时不考虑一个圆弧、或者圆的问题

// 	if (GetCount() < 3)
// 	{
// 		return;
// 	}

	POS pos = GetHeadPosition();
	CCharElement *pCharElement1 = (CCharElement *)GetNext(pos);
	CCharElement *pCharElement2 = NULL;
	CXDrawDataBase *pDrawData1 = pCharElement1->GetCXDrawDataBase();
	CXDrawDataBase *pDrawData2 = NULL;
	CXDrawBase *pDrawElement1 = pCharElement1->CreateDrawElement();
	CXDrawBase *pDrawElement2 = NULL;
	pDrawList->AddNewChild(pDrawElement1);

	while (pos != NULL)
	{
		pCharElement2 = (CCharElement *)GetNext(pos);
		Solv_CharElement_Equation(pCharElement1, pCharElement2, pDrawData1, pDrawData2, pDrawElement1, NULL, pDrawList);
	}

	pCharElement2 = (CCharElement *)GetHead();
	pDrawElement2 = (CXDrawBase *)pDrawList->GetHead();

	Solv_CharElement_Equation(pCharElement1, pCharElement2, pDrawData1, pDrawData2, pDrawElement1, pDrawElement2, pDrawList);
}

void CCharacterArea::InitCharDrawElement_LineD(CXDrawList *pDrawList, CCharElementLined *pCharLined, BOOL bCalTestLines)
{
	CXDrawLine *pXLine = new CXDrawLine();

	pXLine->m_fXb = pCharLined->m_fXb;
	pXLine->m_fYb = pCharLined->m_fYb;
	pXLine->m_fXe = pCharLined->m_fXe;
	pXLine->m_fYe = pCharLined->m_fYe;
	pXLine->m_pXDrawDataRef = pCharLined;
	pCharLined->m_pDataRef = pXLine;

	pDrawList->AddNewChild(pXLine);

	if (!bCalTestLines)
	{
		return ;
	}

	InitCharDrawElementTestLines(pDrawList, pCharLined);
}

void CCharacterArea::InitCharDrawElement_LineR(CXDrawList *pDrawList, CCharElementLiner *pCharLiner, BOOL bCalTestLines)
{
	CXDrawLineR *pXLine = new CXDrawLineR();

	pXLine->m_fXb = pCharLiner->m_fXb;
	pXLine->m_fYb = pCharLiner->m_fYb;
	pCharLiner->GetXeYe(pXLine->m_fXe, pXLine->m_fYe);
	pXLine->m_pXDrawDataRef = pCharLiner;
	pCharLiner->m_pDataRef = pXLine;

	pDrawList->AddNewChild(pXLine);

	if (!bCalTestLines)
	{
		return ;
	}

	InitCharDrawElementTestLines(pDrawList, pCharLiner);
}

void CCharacterArea::InitCharDrawElement_Mho(CXDrawList *pDrawList, CCharElementMho *pCharMho, BOOL bCalTestLines)
{
	CXDrawCircle *pXCircle = new CXDrawCircle();

	pXCircle->m_fXCenter = pCharMho->m_fXCenter;
	pXCircle->m_fYCenter = pCharMho->m_fYCenter;
	pXCircle->m_fXRadius = pCharMho->m_fXRadius;
	pXCircle->m_fYRadius = pCharMho->m_fYRadius;
	pXCircle->m_pXDrawDataRef = pCharMho;
	pCharMho->m_pDataRef = pXCircle;

	pDrawList->AddNewChild(pXCircle);

	if (!bCalTestLines)
	{
		return ;
	}

	InitCharDrawElementTestLines(pDrawList, pCharMho);
}

void CCharacterArea::InitCharDrawElement_Lens(CXDrawList *pDrawList, CCharElementLens *pCharLens, BOOL bCalTestLines)
{
	CXDrawList *pNewList = (CXDrawList*)pCharLens->CreateDrawElement();
	pDrawList->AddNewChild(pNewList);

// 	CCharElementArc *pCharArc1 = pCharLens->GetCharElementArc1();
// 	CCharElementArc *pCharArc2 = pCharLens->GetCharElementArc2();
//
// 	InitCharDrawElementTestLines(pDrawList, pCharArc1);
// 	InitCharDrawElementTestLines(pDrawList, pCharArc2);
}

void CCharacterArea::InitCharDrawElement_Inverse(CXDrawList *pDrawList, CCharElementInverse *pCharInverse, BOOL bCalTestLines)
{
	CXDrawPolyline *pDrawPolyline = (CXDrawPolyline*)pCharInverse->CreateDrawElement();
	pDrawPolyline->m_pXDrawDataRef = pCharInverse;//20230313 zhouhj  增加传递反时限特性曲线
	pDrawList->AddNewChild(pDrawPolyline);

}

void CCharacterArea::InitCharDrawElementTestLines(CXDrawList *pDrawList, CCharElement *pCharElement)
{
	POS pos = pCharElement->GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	CXDrawLine *pXLine = NULL;
	CXDrawPoint *pXPoint = NULL;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)pCharElement->GetNext(pos);
		pTestLine->GetXDrawElement(pDrawList);
	}
}


//添加特性曲线与测试测试项目的接口
//2020-3-19
void CCharacterArea::DeleteAllTestLines()
{
	if(m_pUserDefTestDef != NULL)
	{
		m_pUserDefTestDef->DeleteAll();
	}
}

void CCharacterArea::AddTestLines(CXDrawData_Line *pValRange, double dLenStep)
{
	if(m_pUserDefTestDef != NULL && pValRange != NULL && dLenStep != 0)
	{
		double  fXb, fYb, fXe, fYe;
		fXb = pValRange->m_fXb;
		fYb = pValRange->m_fYb;
		fXe = pValRange->m_fXe;
		fYe = pValRange->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		double dErrorLen = 0.2; //默认

		for(int i=0;i<=dX/dLenStep;i++)
		{
			CCharElementTestLine *pTestLine = new CCharElementTestLine;

			pTestLine->m_fXb = fXb + i * dLenStep;
			pTestLine->m_fYb = dY/dX * pTestLine->m_fXb + dErrorLen;

			pTestLine->m_fXe = pTestLine->m_fXb;
			pTestLine->m_fYe = pTestLine->m_fYb - 2 * dErrorLen;

			pTestLine->m_nTestLineID = i;

			m_pUserDefTestDef->AddNewChild(pTestLine);
		}
	}
}

void CCharacterArea::AddTestLine(CXDrawData_Line *pCurrValLine)
{	
	if(m_pUserDefTestDef != NULL && pCurrValLine != NULL)
	{
		CCharElementTestLine *pNew = new CCharElementTestLine;
		pNew->m_fXb = pCurrValLine->m_fXb;
		pNew->m_fYb = pCurrValLine->m_fYb;
		pNew->m_fXe = pCurrValLine->m_fXe;
		pNew->m_fYe = pCurrValLine->m_fYe;

		m_pUserDefTestDef->AddNewChild(pNew);
	}
}

void CCharacterArea::InitElementTestLines(CCharInterface *pCharInterface)
{
	if (m_pTestLines == NULL)
	{
		return;
	}

	CXCharElementTestPoints *pTestPoints = m_pTestLines->GetCharElementTestPoints();

	InitElementTestLines_CalValue(pCharInterface, pTestPoints->m_strFrom, pTestPoints->m_dFrom);
	InitElementTestLines_CalValue(pCharInterface, pTestPoints->m_strTo, pTestPoints->m_dTo);
	InitElementTestLines_CalValue(pCharInterface, pTestPoints->m_strStep, pTestPoints->m_dStep);

	// 	CCharInterfaceVariable *pVariable = (CCharInterfaceVariable *)pCharInterface->FindByID(pTestPoints->m_strFrom);
// 
// 	if (pVariable != NULL)
// 	{
// 		pTestPoints->m_dFrom = CString_To_double(pVariable->m_strValue);
// 	}
// 
// 	pVariable = (CCharInterfaceVariable *)pCharInterface->FindByID(pTestPoints->m_strTo);
// 
// 	if (pVariable != NULL)
// 	{
// 		pTestPoints->m_dTo = CString_To_double(pVariable->m_strValue);
// 	}
// 
// 	pVariable = (CCharInterfaceVariable *)pCharInterface->FindByID(pTestPoints->m_strStep);
// 
// 	if (pVariable != NULL)
// 	{
// 		pTestPoints->m_dStep = CString_To_double(pVariable->m_strValue);
// 	}
}

void CCharacterArea::InitElementTestLines_CalValue(CCharInterface *pCharInterface, const CString& strExpression, double &dValue)
{
	CCharInterfaceVariable *pVariable = NULL;

	CEpExpression oEpExp;

	if (oEpExp.ChangeEpExpression(strExpression) == -1)
	{
		return;
	}

	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);
		pVariable = (CCharInterfaceVariable *)pCharInterface->FindByID(pExpVar->m_strVarID);

		if (pVariable != NULL)
		{
#ifdef _UNICODE
			pExpVar->m_dValue = _wtof(pVariable->m_strValue);
#else
			pExpVar->m_dValue = atof(pVariable->m_strValue.GetString());
#endif
		}
	}

	oEpExp.Value(dValue);
}

//shaolei 2023-9-18 
CCharElement* CCharacterArea::GetFirstCharElemet()
{
	CExBaseObject *pObj;
	long lItemIndex = 0;

	POS pos = GetHeadPosition();
	while(pos)
	{
		pObj = GetNext(pos);
		UINT nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINES)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		return (CCharElement*)pObj;
	}

	return NULL;
}
