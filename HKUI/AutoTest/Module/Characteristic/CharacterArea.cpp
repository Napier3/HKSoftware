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

    m_pTestObjects = NULL;
	m_bUseIntersectionTestPoint = /*FALSE*/ TRUE; 
	m_fErrorBandLen = 0.5;
    m_bShowErrBand = TRUE;
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
	CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);

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
		SerializeChildren(oBinaryBuffer);
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

	if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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
	else if (strClassID == pXmlKeys->m_strCCharElementRXIDGKey)
	{
		pNew = new CCharElementRXIDG();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementRICurveKey)
	{
		pNew = new CCharElementRICurve();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementLabIecCurveKey)
	{
		pNew = new CCharElementLabIecCurve();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementITKey)
	{
		pNew = new CCharElementIT();
	}
	else if (strClassID == pXmlKeys->m_strCCharElementI2TExKey)
	{
		pNew = new CCharElementI2TEx();
	}
	else if (strClassID == pXmlKeys->m_strCCharTestObjectsKey)
	{
		pNew = new CCharTestObjects();
	}
    else if (strClassID == pXmlKeys->m_strCCharElementExprFuncKey)//Expr
    {
        pNew = new CCharElementExpr();
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
	else if (nClassID == CHARCLASSID_CCHARELEMENTRXIDG)  //zhangyq 20240620
	{
		pNew = new CCharElementRXIDG();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		pNew = new CCharElementRICurve();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		pNew = new CCharElementLabIecCurve();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTIT)
	{
		pNew = new CCharElementIT();
	}
	else if (nClassID == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		pNew = new CCharElementI2TEx();
	}
	else if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
	{
		pNew = new CCharTestObjects();
	}
    else if (nClassID == CHARCLASSID_CCHARELEMENTEXPR)
    {
        pNew = new CCharElementExpr();
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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
		{
            m_pTestObjects = (CCharTestObjects *)pObj;
            Remove(m_pTestObjects);
		}
	}
}

BOOL CCharacterArea::CopyChildren(CBaseObject* pDest)
{
	BOOL bRet = CExBaseList::CopyChildren(pDest);

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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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

	while (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
	{
		//这个类对象，不是从CCharElement派生的，过滤掉
		pObj = GetNext(pos);
	}

	CCharElement *pCharElementPrev = (CCharElement *)pObj/*GetNext(pos)*/;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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
// 	CCharTestLine *pTestLine = AddTestLine(nTestLineID);//new CCharTestLine();
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

	CCharTestLine *pTestLine = AddTestLine(nTestLineID);//new CCharTestLine();
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
	CCharTestLine *pTestLine = AddTestLine(nTestLineID);
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
	CCharTestLine *pTestLine = AddTestLine(nTestLineID);
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

	CCharTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharTestLine();
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

	CCharTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharTestLine();

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

	CCharTestLine *pTestLine = AddTestLine(pXLine1, pXLine2);//new CCharTestLine();
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

void CCharacterArea::SetErrorBandLen(double ffErrorBandLen)
{ 
	m_fErrorBandLen = ffErrorBandLen; 

	//20241018 wanmj 同步到子节点的err-len
	POS pos = GetHeadPosition();
	CCharElement *pElementTemp = NULL;
	CString strErrLen;
	//strErrLen.setNum(m_fErrorBandLen);
	strErrLen.Format(_T("%f"), m_fErrorBandLen);
	while (pos != NULL)
	{
		pElementTemp = (CCharElement *)GetNext(pos);
		pElementTemp->m_strErrLength = strErrLen;
	}
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
	CCharTestLine *pTestLine = NULL;
	
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

CCharTestLine* CCharacterArea::FindBisectorTestLine(long nTestLineID)
{
	POS pos = m_pCharBisector->GetHeadPosition();
	CCharTestLine *p = NULL;
	CCharTestLine *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCharTestLine *)m_pCharBisector->GetNext(pos);

		if (p->m_nTestLineID == nTestLineID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CCharacterArea::InitTestLineID(CCharTestLine *pTestLine, CCharElement *pChar1, CCharElement *pChar2)
{
	long nTestLineID = char_GetTestLineID(pChar1, pChar2);
	pTestLine->m_nTestLineID = nTestLineID;
}

CCharTestLine* CCharacterArea::AddTestLine(CCharElement *pChar1, CCharElement *pChar2)
{
	long nTestLineID = char_GetTestLineID(pChar1, pChar2);
	return AddTestLine(nTestLineID);
}

CCharTestLine* CCharacterArea::AddTestLine(long nTestLineID)
{
	CCharTestLine *pFind = FindBisectorTestLine(nTestLineID);

	if (pFind == NULL)
	{
		pFind = new CCharTestLine();
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
	//2024-9-24 lijunqing 删除所有Element图元
	m_listCharElement.RemoveAll();
	m_listErrorOut.RemoveAll();
	m_listErrorIn.RemoveAll();

	if (NeedSolvEqation())
	{
		return InitCharDrawElement_Equation(pDrawList, bCalTestLines);
	}

	POS pos = GetHeadPosition();
	CCharElement *pCharElement = NULL;
	UINT nClassID = 0;
	bool bNeedCalErrorBand = true;

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
			bNeedCalErrorBand = false;
			InitCharDrawElement_Mho(pDrawList, (CCharElementMho*)pCharElement, bCalTestLines);
			break;

		case CHARCLASSID_CCHARELEMENTLENS:
			bNeedCalErrorBand = false;
			InitCharDrawElement_Lens(pDrawList, (CCharElementLens*)pCharElement, bCalTestLines);
			break;

        case CHARCLASSID_CCHARELEMENTEXPR:
            InitCharDrawElement_Expr(pDrawList, (CCharElementExpr*)pCharElement, bCalTestLines);
            break;
		case CHARCLASSID_CCHARELEMENTI2T:
		case CHARCLASSID_CCHARELEMENTIAC:
		case CHARCLASSID_CCHARELEMENTIEC:
		case CHARCLASSID_CCHARELEMENTIEEE:
		case CHARCLASSID_CCHARELEMENTINVOWNDEF:
		case CHARCLASSID_CCHARELEMENTUIVP://20211220 sf
		case CHARCLASSID_CCHARELEMENTDCOVERLOAD://20230912 cl
		case CHARCLASSID_CCHARELEMENTIUF:
		case CHARCLASSID_CCHARELEMENTRXIDG: //20240620 zhangyq
		case CHARCLASSID_CCHARELEMENTRICURVE:
		case CHARCLASSID_CCHARELEMENTLABIECCURVE:
		case CHARCLASSID_CCHARELEMENTIT:
		case CHARCLASSID_CCHARELEMENTI2TEx:
			InitCharDrawElement_Inverse(pDrawList, (CCharElementInverse*)pCharElement, bCalTestLines);
			break;
		}

	}

	if (bNeedCalErrorBand)
	{
		InitCharDrawElement_Equation_ErrBand(pDrawList);
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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
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
							 , CXDrawList *pDrawList, CCharacterArea *pArea)
{
	CXDrawDatas listDatas;
	CXDrawData_Point oPoint(0, 0);
	CXDrawData_Point *pPoint = NULL;

	if (pDrawElement2 == NULL)
	{
		pDrawElement2 = pCharElement2->CreateDrawElement();
		pArea->AddElementDraw(pDrawList, pDrawElement2);
	}

	pDrawData2 = pCharElement2->GetCXDrawDataBase();
	xdraw_SolveEquation(pDrawData1, pDrawData2, listDatas, true);

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
	AddElementDraw(pDrawList, pDrawElement1);

	while (pos != NULL)
	{
		pCharElement2 = (CCharElement *)GetNext(pos);
		Solv_CharElement_Equation(pCharElement1, pCharElement2, pDrawData1, pDrawData2, pDrawElement1
			, NULL, pDrawList, this);
	}

	pCharElement2 = (CCharElement *)GetHead();
	pDrawElement2 = (CXDrawBase *)pDrawList->GetHead();

	Solv_CharElement_Equation(pCharElement1, pCharElement2, pDrawData1, pDrawData2, pDrawElement1
		, pDrawElement2, pDrawList, this);

	//2024-9-25 lijunqing  计算误差线
	InitCharDrawElement_Equation_ErrBand(pDrawList);
}

long g_debug_cal_out = 1;
long g_debug_cal_in = 1;

void CCharacterArea::InitCharDrawElement_Equation_ErrBand(CXDrawList *pDrawList)
{
	//第一步：计算边界元素，平移直线、缩放圆弧
	POS pos = m_listCharElement.GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase *)m_listCharElement.GetNext(pos);
		CalErrorBand(p);
	}

	//第二步：处理边界中线段与圆弧的交接点
	if (g_debug_cal_out)
	{
		CalErrorBand_Arc(m_listErrorOut);
	}

	if (g_debug_cal_in)
	{
		CalErrorBand_Arc(m_listErrorIn);
	}

	//第三步：处理边界中线段之间的交接点
	CalErrorBand_Solv(m_listErrorOut);
	CalErrorBand_Solv(m_listErrorIn);

	//第四步：根据收尾相连的点进行排序
	//CXDrawXmlRWKeys::Create();
	//m_listErrorOut.SaveXmlFile(_T("D://char.xml"), CXDrawXmlRWKeys::g_pXmlKeys);
	CalErrorBand_SortBy_B_E(m_listErrorOut);
	CalErrorBand_SortBy_B_E(m_listErrorIn);
	//m_listErrorOut.SaveXmlFile(_T("D://char2.xml"), CXDrawXmlRWKeys::g_pXmlKeys);
	//CXDrawXmlRWKeys::Release();

	InitCharDrawElement_Equation_ErrBand_Adjust(m_listErrorOut);
	InitCharDrawElement_Equation_ErrBand_Adjust(m_listErrorIn);

    //20241015 wanmj 是否显示误差带
    if(m_bShowErrBand)
    {
		pDrawList->Append(m_listErrorOut);
		pDrawList->Append(m_listErrorIn);
    }
 
	//测试是否位于误差带内
	//bool b = IsPointInErrBand(2,4);
	//b = IsPointInErrBand(3,6);
	
	//测试：根据线段获取搜索线
/*	CExBaseList listTestLine;
	CXDrawData_Line oLine;
// 	oLine.SetBeginPoint(0.416, 1.956);
// 	oLine.SetEndPoint(0.416, 11.956);
	oLine.SetBeginPoint(0, 0);
	oLine.SetEndPoint(0, 10);
	oLine.Init_K_B_by_XY();
	oLine.Set_LineSegment();
	GetIntersectTestLine(&oLine, listTestLine);
*/
}

void CCharacterArea::InitCharDrawElement_Equation_ErrBand_Adjust(CXDrawList &oList)
{
	if (oList.GetCount() < 2)
	{
		return;
	}

	long nCount = oList.GetCount();

	if (nCount <= 3)
	{
		return;
	}

	long k1=0, k2=0;
	CXDrawBase *p1=NULL, *p2 = NULL;
	CXDrawDataBase *pDrawData1=NULL, *pDrawData2 = NULL;

	for (k1=2; k1<nCount; k1++)
	{
		p1 = (CXDrawBase *)oList.GetAtIndex(k1);
		pDrawData1 = p1->GetDrawData();

		if (InitCharDrawElement_Equation_ErrBand_Adjust(oList, p1))
		{//
			nCount = oList.GetCount();
			k1 = 2;
		}
	}
}

bool CCharacterArea::InitCharDrawElement_Equation_ErrBand_Adjust(CXDrawList &oList, CXDrawBase *pElement)
{
	long nCurr = oList.FindIndex(pElement);
	long k = 0, j=0;
	CXDrawDataBase *pDrawData1=NULL, *pDrawData2 = NULL;
	CXDrawBase *p = NULL;
	CXDrawDatas listPoints;
	CXDrawData_Point *pPoint = 0;

	pDrawData1 = pElement->GetDrawData();

	for (k=1; k <= nCurr-2; k++)
	{
		listPoints.DeleteAll();
		p = (CXDrawBase *)oList.GetAtIndex(k);
		pDrawData2 = p->GetDrawData();

		GetIntersectPoint2(pElement->GetDrawData(), listPoints, p->GetDrawData());

		if (listPoints.GetCount() > 0)
		{
			pPoint = (CXDrawData_Point*)listPoints.GetHead();

			for (j=k+1; j<nCurr; j++)
			{
				oList.DeleteAtIndex(k+1);
			}

			CXDrawBase *pPrev = (CXDrawBase*)oList.GetAtIndex(k);
			pPrev->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
			pElement->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);

			return true;
		}
	}

	return false;
}

//2024-9-24 lijunqing
void CCharacterArea::CalErrorBand(CXDrawBase *pDraw)
{
	UINT nType = pDraw->GetClassID();

	switch (nType)
	{
	case DWCLASSID_CXDRAWLINE:
		CalErrorBand((CXDrawLine*)pDraw);
		break;
	case DWCLASSID_CXDRAWARC:
		CalErrorBand((CXDrawArc*)pDraw);
		break;
	case DWCLASSID_CXDRAWCIRCLE:
		//CalErrorBand((CXDrawData_Circle*)pDrawData1);
		break;
	default:
		break;
	}
}

void CCharacterArea::CalErrorBand(CXDrawArc *pArc)
{//直接可能圆弧，然后再进行计算
	CXDrawArc *p = NULL;
	
	if (g_debug_cal_in)
	{
		p = new CXDrawArc();
		pArc->DataCopy(p);
		p->m_crForeColor = COLOR_ERR_BAND_LINE;
		m_listErrorIn.AddTail(p);
	}

	if (g_debug_cal_out)
	{
		p = new CXDrawArc();
		pArc->DataCopy(p);
		p->m_crForeColor = COLOR_ERR_BAND_LINE;
		m_listErrorOut.AddTail(p);
	}
}

void CCharacterArea::CalErrorBand(CXDrawLine *pLine)
{//线段的偏移
	CComplexNumber c;
	CXDrawLine *p = NULL;
	
	if (g_debug_cal_in)
	{
		c.SetValueAngle(m_fErrorBandLen, pLine->m_fAngle);
		p = new CXDrawLine();
		pLine->DataCopy(p);
		c.Rotate(90);
		p->m_fXb += c.m_fReal;
		p->m_fYb += c.m_fImaginary;
		p->m_fXe += c.m_fReal;
		p->m_fYe += c.m_fImaginary;
		p->Init_K_B_by_XY();
        p->m_nStyle = PS_DOT;
		p->m_crForeColor = COLOR_ERR_BAND_LINE;
		m_listErrorIn.AddTail(p);
	}

	if (g_debug_cal_out)
	{
		c.SetValueAngle(m_fErrorBandLen, pLine->m_fAngle);
		p = new CXDrawLine();
		pLine->DataCopy(p);
		c.Rotate(-90);
		p->m_fXb += c.m_fReal;
		p->m_fYb += c.m_fImaginary;
		p->m_fXe += c.m_fReal;
		p->m_fYe += c.m_fImaginary;
		p->Init_K_B_by_XY();
        p->m_nStyle = PS_DOT;
		p->m_crForeColor = COLOR_ERR_BAND_LINE;
		m_listErrorOut.AddTail(p);
	}
}

void CCharacterArea::CalErrorBand_Arc(CXDrawListEx &oList)
{
	long k = 0;
	long nCount = oList.GetCount();
	CXDrawBase *p = NULL, *p1 = NULL, *p2 = NULL;
	CXDrawLine *pLine1;
	CXDrawArc *pArc = NULL;
	CXDrawArc *pArc1 = NULL;
	double dLen = 0;
	double x, y;

	for (k=0; k<nCount; k++)
	{
		p = (CXDrawBase *)oList.GetAtIndex(k);

		if (p->GetClassID() != DWCLASSID_CXDRAWARC)
		{
			continue;
		}

		p1 = CalErrorBand_Arc_GetPrev(oList, k);
		pArc = (CXDrawArc *)p;

		if (p1->GetClassID() == DWCLASSID_CXDRAWLINE)
		{
			pLine1 = (CXDrawLine *)p1;
			pLine1->GetEndPoint(x, y);
		}
		else
		{
			pArc1 = (CXDrawArc*)p1;
			pArc1->GetEndPoint(x, y);
		}

		dLen = xdraw_CalLengthPoints(x, y, pArc->m_fXCenter, pArc->m_fYCenter);

		if (dLen > pArc->m_fXRadius)
		{
			pArc->m_fXRadius += m_fErrorBandLen;
			pArc->m_fYRadius += m_fErrorBandLen;
		}
		else
		{
			pArc->m_fXRadius -= m_fErrorBandLen;
			pArc->m_fYRadius -= m_fErrorBandLen;
		}
		
	}
}

CXDrawBase* CCharacterArea::CalErrorBand_Arc_GetPrev(CXDrawListEx &oList, long nIndex)
{
	if (nIndex == 0)
	{
		return (CXDrawBase*)oList.GetTail();
	}

	return (CXDrawBase*)oList.GetAt(nIndex-1);
}

CXDrawBase* CCharacterArea::CalErrorBand_Arc_GetNext(CXDrawListEx &oList, long nIndex)
{
	if (nIndex == oList.GetCount() - 1)
	{
		return (CXDrawBase*)oList.GetHead();
	}

	return (CXDrawBase*)oList.GetAt(nIndex+1);

}
void CCharacterArea::ErrBand_Solv_Equation_LL_Arc(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList, CXDrawData_Point *pPoint)
{
	double x,y;
	CXDrawBase *p = (CXDrawBase*)m_listCharElement.GetAtIndex(nIndex);
	CXDrawDataBase *p1 = p->GetDrawData();
	if (NULL == p1)//add wangtao 20241011
	{
		return;
	}
	CXDrawArc *pArc = new CXDrawArc();
	CXDrawData_Line oLine; //以线段1的终点、线段2的起点 作直线

	if (p1 == NULL)
	{
		//TODO：是否合理？
		return;
	}

	p1->GetEndPoint(pArc->m_fXCenter, pArc->m_fYCenter);
	pArc->m_fXRadius = m_fErrorBandLen;
	pArc->m_fYRadius = m_fErrorBandLen;
	pDrawData1->GetEndPoint(x, y);
	oLine.SetBeginPoint(x, y);
	pArc->SetBeginPoint(x, y);
	pDrawData2->GetBeginPoint(x, y);
	pArc->SetEndPoint(x, y);
	oLine.SetEndPoint(x, y);
	pDrawList->AddNewChild(pArc);
	oLine.Init_K_B_by_XY();
    pArc->m_nStyle = PS_DOT;
	pArc->m_crForeColor = COLOR_ERR_BAND_LINE;

	if (oLine.IsPointLeft(pArc->m_fXCenter, pArc->m_fYCenter))
	{//如果圆心在左边，则为CCW，否则为CW（时钟方向）
		pArc->m_nClockwise = ARC_CLOCKWISE_CW;
	}
	else
	{
		pArc->m_nClockwise = ARC_CLOCKWISE_CCW;
	}
}
void CCharacterArea::ErrBand_Solv_Equation(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList, CXDrawData_Point *pPoint)
{
	long nDataType1 = pDrawData1->GetDrawDataType();
	long nDataType2 = pDrawData2->GetDrawDataType();

	if (nDataType1 == XDRAW_DATA_LINE)
	{//第一个为线段
		if (nDataType2 == XDRAW_DATA_LINE)
		{//第二个为线段
			if (pDrawData1->IsPointIn(pPoint->m_fX, pPoint->m_fY))
			{//两个线段有交点，则求取交点
				pDrawData1->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
				pDrawData2->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
			}
			else
			{//两个线段没有交点，则使用原始定点为圆心，以线段1的终点、线段2的起点作为圆弧的起点和终点
				ErrBand_Solv_Equation_LL_Arc(pDrawData1, pDrawData2, nIndex, pDrawList, pPoint);
			}
		}
		else
		{//第二个为圆弧
			pDrawData1->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
			pDrawData2->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
			//CXDrawData_Arc *pArc = (CXDrawData_Line*)pDrawData2;
		}
	}
	else
	{
		pDrawData1->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
		pDrawData2->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
	}
}

void CCharacterArea::ErrBand_Solv_Equation(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList)
{
	CXDrawDatas listDatas;
	CXDrawData_Point oPoint(0, 0);
	CXDrawData_Point *pPoint = NULL;
	double x,y;
	pDrawData1->GetEndPoint(x, y);

	xdraw_SolveEquation(pDrawData1, pDrawData2, listDatas, false);

	if (listDatas.GetCount() == 0)
	{
		return;
	}

	
	if (listDatas.GetCount() == 1)
	{
		pPoint = (CXDrawData_Point *)listDatas.GetHead();
		ErrBand_Solv_Equation(pDrawData1, pDrawData2, nIndex, pDrawList, pPoint);
	}
	else//交点数大于1时,此时定只有2个曲线,且已形成闭合区域
	{//两个交点，位圆弧与圆弧、圆弧与线段，选择最短的点
		pPoint = (CXDrawData_Point*)listDatas.PickShortestPoint(x, y);
		pDrawData1->SetEndPoint(pPoint->m_fX, pPoint->m_fY);
		pDrawData2->SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
	}
}

void CCharacterArea::CalErrorBand_Solv(CXDrawListEx &oList)
{
	if (oList.GetCount() < 2)
	{
		return;
	}

	CXDrawListEx listTemp;
	listTemp.Append(oList);
	POS pos = listTemp.GetHeadPosition();
	CXDrawBase *p1=NULL, *p2 = NULL;
	long k = 0;
	long nCount = listTemp.GetCount();
	CXDrawDataBase *pDrawData2 = NULL;
	CXDrawBase *pDrawElement2 = NULL;

	for (k=0; k<nCount-1; k++)
	{
		p1 = (CXDrawBase *)listTemp.GetAtIndex(k);
		p2 = (CXDrawBase *)listTemp.GetAtIndex(k+1);
		ErrBand_Solv_Equation(p1->GetDrawData(), p2->GetDrawData(), k, &oList);
	}

	if (m_bAutoClose)
	{
		p1 = p2;
		p2 = (CXDrawBase *)listTemp.GetHead();
		ErrBand_Solv_Equation(p1->GetDrawData(), p2->GetDrawData(), nCount-1, &oList);
	}

	listTemp.RemoveAll();
}

void CCharacterArea::CalErrorBand_SortBy_B_E(CXDrawListEx &oList)
{
	if (oList.GetCount() < 2)
	{
		return;
	}

	CXDrawListEx listTemp;
	POS pos = oList.GetHeadPosition();
	CXDrawBase *p1=NULL, *p2 = NULL;
	long k = 0;
	CXDrawDataBase *pDrawData1, *pDrawData2;
	CXDrawBase *pDrawElement2 = NULL;

	p1 = (CXDrawBase *)oList.GetNext(pos);
	listTemp.AddTail(p1);
	double xb, yb, xe, ye;
	bool bFind = true;

	while (pos != NULL)
	{
		p2 = (CXDrawBase *)oList.GetNext(pos);
		pDrawData2 = p2->GetDrawData();
		pDrawData2->GetBeginPoint(xb, yb);
		
		//遍历listTemp，查找终点坐标等于p2起点坐标
		POS pos2 = listTemp.GetHeadPosition();
		bFind = false;

		while (pos2 != NULL)
		{
			p1 = (CXDrawBase *)listTemp.GetAt(pos2);
			pDrawData1 = p1->GetDrawData();
			pDrawData1->GetEndPoint(xe, ye);

			if (math_IsEqual(xb, xe) && math_IsEqual(yb, ye) )
			{
				listTemp.InsertAfter(pos2, p2);
				bFind = true;
				break;
			}

			listTemp.GetNext(pos2);
		}

		if (!bFind)
		{
			listTemp.AddTail(p2);
		}
	}

	oList.RemoveAll();
	oList.Append(listTemp);
	listTemp.RemoveAll();
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
	pXLine->Init_K_B_by_XY();
	pXLine->Set_LineSegment();  //线段

	AddElementDraw(pDrawList, pXLine);

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

	AddElementDraw(pDrawList, pXLine);

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

	AddElementDraw(pDrawList, pXCircle);

	//外部边界
	CXDrawCircle *p = (CXDrawCircle*)pXCircle->Clone();
	p->m_fXRadius += m_fErrorBandLen;
	p->m_fYRadius += m_fErrorBandLen;
	m_listErrorOut.AddNewChild(p);
	p->m_nStyle = PS_DOT;
	p->m_crForeColor = COLOR_ERR_BAND_LINE;

	//内部边界
	p = (CXDrawCircle*)pXCircle->Clone();
	p->m_fXRadius -= m_fErrorBandLen;
	p->m_fYRadius -= m_fErrorBandLen;
	p->m_nStyle = PS_DOT;
	p->m_crForeColor = COLOR_ERR_BAND_LINE;
	m_listErrorIn.AddNewChild(p);

    //20241015 wanmj 是否显示误差带
    if(m_bShowErrBand)
    {
		pDrawList->Append(m_listErrorOut);
		pDrawList->Append(m_listErrorIn);
    }

/*
	{//2024-10-19 lijunqing Debug GetIntersectTestLine
		CExBaseList listTestLine;
		CXDrawData_Line oLine;
		oLine.SetBeginPoint(0, 0);
		oLine.SetEndPoint(200, 549.495);
		oLine.Init_K_B_by_XY();
		oLine.Set_LineSegment();
		GetIntersectTestLine(&oLine, listTestLine);

		CXDrawDatas oListPoint;
		GetIntersectPoint(&oLine, oListPoint);
	}
*/

	if (!bCalTestLines)
	{
		return ;
	}

	InitCharDrawElementTestLines(pDrawList, pCharMho);
}

void CCharacterArea::InitCharDrawElement_Lens(CXDrawList *pDrawList, CCharElementLens *pCharLens, BOOL bCalTestLines)
{
	CXDrawList *pNewList = (CXDrawList*)pCharLens->CreateDrawElement();
	AddElementDraw(pDrawList, pNewList);

	CXDrawArc *pArc1 = (CXDrawArc*)pNewList->GetAtIndex(0);
	CXDrawArc *pArc2 = (CXDrawArc*)pNewList->GetAtIndex(1);

	//外部边界
	InitCharDrawElement_Lens_Err(pArc1, pArc2, m_fErrorBandLen, m_listErrorOut);


	//内部边界
	InitCharDrawElement_Lens_Err(pArc1, pArc2, -m_fErrorBandLen, m_listErrorIn);

	pDrawList->Append(m_listErrorOut);
	pDrawList->Append(m_listErrorIn);
}

void CCharacterArea::InitCharDrawElement_Lens_Err(CXDrawArc *pArc1, CXDrawArc *pArc2, double fErrLen, CXDrawListEx &oList)
{
	CXDrawArc *arc1 = (CXDrawArc*)pArc1->Clone();
	CXDrawArc *arc2 = (CXDrawArc*)pArc2->Clone();
	arc1->m_nStyle = PS_DOT;
	arc2->m_nStyle = PS_DOT;
	arc1->m_crForeColor = COLOR_ERR_BAND_LINE;
	arc2->m_crForeColor = COLOR_ERR_BAND_LINE;

	arc1->m_fXRadius += fErrLen;
	arc1->m_fYRadius += fErrLen;
	arc2->m_fXRadius += fErrLen;
	arc2->m_fYRadius += fErrLen;
	oList.AddNewChild(arc1);
	oList.AddNewChild(arc2);

	CXDrawDatas listPoints;
	xdraw_SolveEquation(arc1, arc2, listPoints, true);

	CXDrawData_Point *p1 = (CXDrawData_Point*)listPoints.GetAtIndex(0);
	CXDrawData_Point *p2 = (CXDrawData_Point*)listPoints.GetAtIndex(1);
	arc1->SetBeginPoint(p1->m_fX, p1->m_fY);
	arc1->SetEndPoint(p2->m_fX, p2->m_fY);
	arc2->SetBeginPoint(p2->m_fX, p2->m_fY);
	arc2->SetEndPoint(p1->m_fX, p1->m_fY);
}

void CCharacterArea::InitCharDrawElement_Inverse(CXDrawList *pDrawList, CCharElementInverse *pCharInverse, BOOL bCalTestLines)
{
	CXDrawPolyline *pDrawPolyline = (CXDrawPolyline*)pCharInverse->CreateDrawElement();
	pDrawPolyline->m_pXDrawDataRef = pCharInverse;//20230313 zhouhj  增加传递反时限特性曲线
	AddElementDraw(pDrawList, pDrawPolyline);

}

void CCharacterArea::InitCharDrawElementTestLines(CXDrawList *pDrawList, CCharElement *pCharElement)
{
	POS pos = pCharElement->GetHeadPosition();
	CCharTestLine *pTestLine = NULL;
	CXDrawLine *pXLine = NULL;
	CXDrawPoint *pXPoint = NULL;

	while (pos != NULL)
	{
		pTestLine = (CCharTestLine *)pCharElement->GetNext(pos);
		pTestLine->GetXDrawElement(pDrawList);
	}
}

void CCharacterArea::InitCharDrawElement_Expr(CXDrawList *pDrawList, CCharElementExpr *pCharExpr, BOOL bCalTestLines)
{
    CXDrawPolyline *pDrawPolyline = (CXDrawPolyline*)pCharExpr->CreateDrawElement();
    //pDrawPolyline->m_pXDrawDataRef = pCharInverse;//20230313 zhouhj  增加传递反时限特性曲线
    AddElementDraw(pDrawList, pDrawPolyline);
}


//2024-9-24 添加边界元素对象
void CCharacterArea::AddElementDraw(CXDrawList *pDrawList, CXDrawBase *pDrawBase)
{
	m_listCharElement.AddNewChild(pDrawBase);
	pDrawList->AddNewChild(pDrawBase);
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
			CCharTestLine *pTestLine = new CCharTestLine;

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
		CCharTestLine *pNew = new CCharTestLine;
		pNew->m_fXb = pCurrValLine->m_fXb;
		pNew->m_fYb = pCurrValLine->m_fYb;
		pNew->m_fXe = pCurrValLine->m_fXe;
		pNew->m_fYe = pCurrValLine->m_fYe;

		m_pUserDefTestDef->AddNewChild(pNew);
	}
}

void CCharacterArea::InitElementTestLines(CCharInterface *pCharInterface)
{
    if (m_pTestObjects == NULL)
	{
		return;
	}

    CCharTestPoints *pTestPoints = m_pTestObjects->GetCharTestPoints();

	if (pTestPoints == NULL)
	{
		return;
	}

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

		if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
		{
			//这个类对象，不是从CCharElement派生的，过滤掉
			continue;
		}

		return (CCharElement*)pObj;
	}

	return NULL;
}

//2024-9-26 lijunqing 求取线段与曲线的交点
void CCharacterArea::GetIntersectPoint(CXDrawData_Line *pLine, CXDrawDatas &oList, CXDrawDataBase *pCharElement, bool bJdgInLine)
{
	CXDrawDatas listDatas;
	CXDrawData_Point oPoint(0, 0);
	CXDrawData_Point *pPoint = NULL;
	listDatas.m_bAddPtWhenHasNone = bJdgInLine;

	xdraw_SolveEquation(pLine, pCharElement, listDatas, true);
	POS pos = listDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pPoint = (CXDrawData_Point *)listDatas.GetNext(pos);

		if (pCharElement->IsPointIn(pPoint->m_fX, pPoint->m_fY) )
		{
			if (bJdgInLine)
			{//是否判断在直线的区域之内
				if (pLine->IsPointIn(pPoint->m_fX, pPoint->m_fY))
				{
					oList.AddTail(pPoint);
					listDatas.Remove(pPoint);
				}
			}
			else
			{
				oList.AddTail(pPoint);
				listDatas.Remove(pPoint);
			}
		}
	}
}

void CCharacterArea::GetIntersectPoint2(CXDrawDataBase *pLine, CXDrawDatas &oList, CXDrawDataBase *pCharElement, bool bJdgInLine)
{
	CXDrawDatas listDatas;
	CXDrawData_Point oPoint(0, 0);
	CXDrawData_Point *pPoint = NULL;
	listDatas.m_bAddPtWhenHasNone = bJdgInLine;

	xdraw_SolveEquation(pLine, pCharElement, listDatas, true);
	POS pos = listDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pPoint = (CXDrawData_Point *)listDatas.GetNext(pos);

		if (pCharElement->IsPointIn(pPoint->m_fX, pPoint->m_fY) )
		{
			if (bJdgInLine)
			{//是否判断在直线的区域之内
				if (pLine->IsPointIn(pPoint->m_fX, pPoint->m_fY))
				{
					oList.AddTail(pPoint);
					listDatas.Remove(pPoint);
				}
			}
			else
			{
				oList.AddTail(pPoint);
				listDatas.Remove(pPoint);
			}
		}
	}
}

void CCharacterArea::GetIntersectPoint(CXDrawData_Line *pLine, CXDrawDatas &oList)
{
	POS pos = m_listCharElement.GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase *)m_listCharElement.GetNext(pos);
		GetIntersectPoint(pLine, oList, p->GetDrawData());
	}
}

bool CCharacterArea::IsPointInErrBand(double x, double y)
{
	CXDrawDatas listDatas, listPoints;
	CXDrawData_Line oLine;
	oLine.SetBeginPoint(x, y);
	oLine.Set_LineRay();
	oLine.SetEndPoint(x + 1, y+1); //随意定义一条射线
	oLine.Init_K_B_by_XY();

	m_listErrorIn.ToXDrawDatas(listDatas);
	m_listErrorOut.ToXDrawDatas(listDatas);

	xdraw_SolveIntersect(listDatas, &oLine, listPoints);
	listDatas.RemoveAll();

	long nCount = listPoints.GetCount();

	if (nCount % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//2024-10-11 lijunqing 获取线段与曲线的TestLine
long CCharacterArea::GetIntersectTestLine(CXDrawData_Line *pLine, CExBaseList &oList)
{
	CXDrawDatas listSet, listIn, listOut;
	GetIntersectTestLine(pLine, listSet, m_listCharElement, true);
	GetIntersectTestLine(pLine, listOut, m_listErrorOut, false);
	GetIntersectTestLine(pLine, listIn, m_listErrorIn, false);

	//没有交点
	if (listSet.GetCount() == 0)
	{
		return 0;
	}

	long nCount = listSet.GetCount();
	long k = 0;
	CXDrawData_Point *pPoint = NULL;
	CCharTestLine *pTestLine = NULL;
	CXDrawData_Point oPtIn, oPtOut;

	for (k=0; k<nCount; k++)
	{
		pPoint = (CXDrawData_Point *)listSet.GetAtIndex(k);

		if (FindTestLine(pLine, listIn, listOut, pPoint, oPtIn, oPtOut))
		{
			pTestLine = new CCharTestLine();
			pTestLine->SetTestLineUserDef();
			pTestLine->m_fXset = pPoint->m_fX;
			pTestLine->m_fYset = pPoint->m_fY;
			pTestLine->m_fXb = oPtIn.m_fX;
			pTestLine->m_fYb = oPtIn.m_fY;
			pTestLine->m_fXe = oPtOut.m_fX;
			pTestLine->m_fYe = oPtOut.m_fY;

			oList.AddTail(pTestLine);
		}
	}

	return nCount;
}

//满足的条件：
//从定值点出发，与Out只能有一个交点，与In没有交点，确定dAngleDir是否为外部误差线的点
//如果一个方向，与Out、In都有交点，则不是OutError区域
bool CCharacterArea::FindTestLine(CXDrawData_Line *pLine, CXDrawDatas &listIn, CXDrawDatas &listOut, CXDrawData_Point *pPoint
								  , CXDrawData_Point &oPtIn, CXDrawData_Point &oPtOut)
{
	double dAngleDir = 0;
	long nOutCount = FindTestLine(pLine, listOut, pPoint, dAngleDir, oPtOut);
	long nInCount = FindTestLine(pLine, listIn, pPoint, dAngleDir, oPtIn);

	if (nOutCount == 1 && nInCount == 0)
	{//listOut >> Out  listIn >> in
		nInCount = FindTestLineShortest(pLine, listIn, pPoint, dAngleDir+180, oPtIn);
		return (nInCount > 0);
	}

	if (nOutCount == 0 && nInCount == 1)
	{//listIn >> Out  listOut >> in
		nOutCount = FindTestLineShortest(pLine, listOut, pPoint, dAngleDir+180, oPtOut);
		return (nOutCount > 0);
	}

	nOutCount = FindTestLine(pLine, listOut, pPoint, dAngleDir+180, oPtOut);
	nInCount = FindTestLine(pLine, listIn, pPoint, dAngleDir+180, oPtIn);

	if (nOutCount == 1 && nInCount == 0)
	{//listOut >> Out  listIn >> in
		nInCount = FindTestLineShortest(pLine, listIn, pPoint, dAngleDir, oPtIn);
		return (nInCount > 0);
	}

	if (nOutCount == 0 && nInCount == 1)
	{//listIn >> Out  listOut >> in
		nInCount = FindTestLineShortest(pLine, listOut, pPoint, dAngleDir, oPtOut);
		return (nInCount > 0);
	}

	return false;
}

long CCharacterArea::FindTestLine(CXDrawData_Line *pLine, CXDrawDatas &listErr, CXDrawData_Point *pPoint, double dAngleDir
									   , CXDrawData_Point &oPtErr)
{
	CXDrawData_Line oLine;
	pLine->DataCopy(&oLine);
	oLine.SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
	oLine.Set_LineRay();
	oLine.Rotate(dAngleDir);

	CXDrawDatas listFind;
	CXDrawData_Point *p = NULL;

	POS pos = listErr.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXDrawData_Point *)listErr.GetNext(pos);

		if (oLine.IsPointIn(p->m_fX, p->m_fY))
		{
			listFind.AddTail(p);
		}
	}

	long nCount = listFind.GetCount();
	
	if (nCount == 1)
	{
		p = (CXDrawData_Point *)listFind.GetHead();
		p->DataCopy(&oPtErr);
	}

	listFind.RemoveAll();

	return nCount;
}
long CCharacterArea::FindTestLineShortest(CXDrawData_Line *pLine, CXDrawDatas &listErr, CXDrawData_Point *pPoint, double dAngleDir
								  , CXDrawData_Point &oPtErr)
{
	CXDrawData_Line oLine;
	pLine->DataCopy(&oLine);
	oLine.SetBeginPoint(pPoint->m_fX, pPoint->m_fY);
	oLine.Set_LineRay();
	oLine.Rotate(dAngleDir);

	CXDrawDatas listFind;
	CXDrawData_Point *p = NULL;

	POS pos = listErr.GetHeadPosition();
	double dLen = -1, dLenPrev = -1;

	while (pos != NULL)
	{
		p = (CXDrawData_Point *)listErr.GetNext(pos);

		if (oLine.IsPointIn(p->m_fX, p->m_fY))
		{
			listFind.AddTail(p);
			dLen = xdraw_CalLengthPoints(p->m_fX, p->m_fY, pPoint->m_fX, pPoint->m_fY);

			if (dLenPrev < 0)
			{
				dLenPrev = dLen;
				p->DataCopy(&oPtErr);
			}
			else if (dLen < dLenPrev)
			{
				p->DataCopy(&oPtErr);
				dLenPrev = dLen;
			}
		}
	}

	long nCount = listFind.GetCount();
	listFind.RemoveAll();

	return nCount;
}



void CCharacterArea::GetIntersectTestLine(CXDrawData_Line *pLine, CXDrawDatas &oListPoint, CXDrawListEx &listElement
										  , bool bJdgInLine)
{
	POS pos = listElement.GetHeadPosition();
	CXDrawBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXDrawBase *)listElement.GetNext(pos);
		GetIntersectPoint(pLine, oListPoint, p->GetDrawData(), bJdgInLine);
	}

	if (oListPoint.GetCount() <= 1)
	{
		return;
	}

	//曲线的交点，会得到两个相同的点，因此再次去掉重复的点
	pos = oListPoint.GetHeadPosition();
	CXDrawData_Point *p1 = NULL, *p2 = NULL;
	p1 = (CXDrawData_Point *)oListPoint.GetNext(pos);

	while (pos != NULL)
	{
		p2 = (CXDrawData_Point *)oListPoint.GetNext(pos);

		if (math_IsEqual(p1->m_fX, p2->m_fX) &&  math_IsEqual(p1->m_fY, p2->m_fY))
		{
			oListPoint.Delete(p1);
		}

		p1 = p2;
	}

	p2 = (CXDrawData_Point *)oListPoint.GetHead();

	if (math_IsEqual(p1->m_fX, p2->m_fX) && math_IsEqual(p1->m_fY, p2->m_fY) )
	{
		oListPoint.Delete(p1);
	}
}
