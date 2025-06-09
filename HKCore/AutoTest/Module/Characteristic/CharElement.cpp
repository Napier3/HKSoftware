//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElement.cpp  CCharElement


#include "stdafx.h"
#include "CharElement.h"
#include "CharacteristicTmplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElement::CCharElement()
{
	//初始化属性
	m_nTestPoints = 4;
	m_nUserTestPoints = 0;
	m_strErrLength = _T("0.2");
	m_nErrorLengthType = CHAR_ERROR_LENGTH_TYPE_ABS;
	m_dErrLength = 0.2;

	//初始化成员变量
	m_pDataRef = NULL;

	m_nCharElementID = -1;
}

CCharElement::~CCharElement()
{
}

long CCharElement::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	xml_GetAttibuteValue(pXmlKeys->m_strTestPointsKey, oNode, m_nTestPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strErrLengthKey, oNode, m_strErrLength);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorLengthTypeKey, oNode, m_nErrorLengthType);

	return 0;
}

long CCharElement::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	xml_SetAttributeValue(pXmlKeys->m_strTestPointsKey, oElement, m_nTestPoints);
	xml_SetAttributeValue(pXmlKeys->m_strErrLengthKey, oElement, m_strErrLength);
	xml_SetAttributeValue(pXmlKeys->m_strErrorLengthTypeKey, oElement, m_nErrorLengthType);

	return 0;
}

BOOL CCharElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElement *p = (CCharElement*)pDest;

	p->m_strDir = m_strDir;
	p->m_nTestPoints = m_nTestPoints;
	p->m_strErrLength = m_strErrLength;
	p->m_nErrorLengthType = m_nErrorLengthType;
	p->m_nCharElementID = m_nCharElementID;
	p->m_nPointUsePolorAxis = m_nPointUsePolorAxis;
// 	p->m_strID = m_strID;
// 	p->m_strName = m_strName;

	return TRUE;
}

CBaseObject* CCharElement::Clone()
{
	CCharElement *p = new CCharElement();
	Copy(p);
	return p;
}


CExBaseObject* CCharElement::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCCharElementTestLineKey)
	{
		pNew = new CCharElementTestLine();
	}

	return pNew;
}

CExBaseObject* CCharElement::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARELEMENTTESTLINE)
	{
		pNew = new CCharElementTestLine();
	}

	return pNew;
}

long CCharElement::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDir);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrLength);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestPoints);
		BinarySerializeCalLen(oBinaryBuffer, m_nErrorLengthType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDir);
		BinarySerializeRead(oBinaryBuffer, m_strErrLength);
		BinarySerializeRead(oBinaryBuffer, m_nTestPoints);

		BinarySerializeRead(oBinaryBuffer, m_nErrorLengthType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDir);
		BinarySerializeWrite(oBinaryBuffer, m_strErrLength);
		BinarySerializeWrite(oBinaryBuffer, m_nTestPoints);
		BinarySerializeWrite(oBinaryBuffer, m_nErrorLengthType);
	}

	return 0;
}

long CCharElement::InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->InsertItem( lItemIndex,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, ReturnXml());
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

long CCharElement::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText( lItemIndex,0,strTemp );
	pListCtrl->SetItemText(lItemIndex, 1, ReturnXml());
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CString CCharElement::ReturnXml()
{
	return _T("");
}

void CCharElement::Draw(CDC *pDC)
{
}

void CCharElement::GetBeginPoint(CString &strX, CString &strY)
{
	if(m_pDataRef == NULL)
	{
		strX = _T("0");
		strY = _T("0");
	}
	else
	{
		double xb,yb;
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
		xb = pLine->m_fXb;
		yb = pLine->m_fYb;

		strX.Format(_T("%lf"), xb);
		strY.Format(_T("%lf"), yb);
	}
}

void CCharElement::GetEndPoint(CString &strX, CString &strY)
{
	if(m_pDataRef == NULL)
	{
		strX = _T("0");
		strY = _T("0");
	}
	else
	{
		double xe,ye;
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
		xe = pLine->m_fXe;
		ye = pLine->m_fYe;

		strX.Format(_T("%lf"), xe);
		strY.Format(_T("%lf"), ye);
	}
}

void CCharElement::SetBeginPoint(const CString &strX, const CString &strY)
{
	if(m_pDataRef == NULL)
	{
		return;
	}
	else
	{
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
		pLine->m_fXb = CString_To_double(strX);
		pLine->m_fYb = CString_To_double(strY);
	}
}

void CCharElement::SetEndPoint(const CString &strX, const CString &strY)
{
	if(m_pDataRef == NULL)
	{
		return;
	}
	else
	{
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
		pLine->m_fXe = CString_To_double(strX);
		pLine->m_fYe = CString_To_double(strY);
	}
}

void CCharElement::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	ASSERT (FALSE);
}

void CCharElement::CalTestLines_Plumb()
{
	if(m_pDataRef == NULL)
	{
		return;
	}
	else
	{
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;

		double  fXb, fYb,fXe ,fYe;
		fXb = pLine->m_fXb;
		fYb = pLine->m_fYb;
		fXe = pLine->m_fXe;
		fYe = pLine->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		CComplexNumber oC1, oC2;
		oC1.SetValue(fXb, fYb);
		oC2.SetValue(fXe, fYe);
		oC2 = oC2 - oC1;
		double dAngle = oC2.GetRadianAngle();

		double dErrorLen = GetErrorLength();

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;
		double dXg = dX / (m_nTestPoints + 1);
		double dYg = dY / (m_nTestPoints + 1);
		double dR90 = dAngle + _PI_D_180 * 90;
		//	double dR270 = dAngle - _PI_D_180 * 90;

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;

			CComplexNumber oComplex(dErrorLen,dR90, COMPLEX_MODE_RADIAN);
			pTestLine->m_fXb = dX + oComplex.m_fReal;
			pTestLine->m_fYb = dY + oComplex.m_fImaginary;

			oComplex.Rotate(180, COMPLEX_MODE_DEGREE);

			pTestLine->m_fXe = dX + oComplex.m_fReal;
			pTestLine->m_fYe = dY + oComplex.m_fImaginary;

			pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
			pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
		}
	}
}

void CCharElement::CalTestLines_Vert()
{
	CString strfXb, strfYb, strfXe, strfYe;
	double  fXb, fYb, fXe, fYe;

	GetBeginPoint(strfXb, strfYb);
	GetEndPoint(strfXe, strfYe);

	fXb = CString_To_double(strfXb);
	fYb = CString_To_double(strfYb);
	fXe = CString_To_double(strfXe);
	fYe = CString_To_double(strfYe);

	double dX = fXe - fXb;
	double dY = fYe - fYb;

	double dErrorLen = GetErrorLength();
	//dErrorLen /= 2;

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);

		if (pTestLine->IsTestLineUserDef())
		{
			dX = pTestLine->m_fPos;
		}
		else
		{
			dX = fXb + pTestLine->m_fPos * dXg;
		}
		
		dY = fYb + pTestLine->m_fPos * dYg;
		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX ;
		pTestLine->m_fYb = dY + dErrorLen;

		pTestLine->m_fXe = dX;
		pTestLine->m_fYe = dY - dErrorLen;
	}
}

void CCharElement::CalTestLines_Horz()
{
	CString strfXb, strfYb, strfXe, strfYe;
	double  fXb, fYb, fXe, fYe;

	GetBeginPoint(strfXb, strfYb);
	GetEndPoint(strfXe, strfYe);

	fXb = CString_To_double(strfXb);
	fYb = CString_To_double(strfYb);
	fXe = CString_To_double(strfXe);
	fYe = CString_To_double(strfYe);

	double dX = fXe - fXb;
	double dY = fYe - fYb;

	double dErrorLen = GetErrorLength();
	//dErrorLen /= 2;

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dX = fXb + pTestLine->m_fPos * dXg;

		if (pTestLine->IsTestLineUserDef())
		{
			dY = pTestLine->m_fPos;
		}
		else
		{
			dY = fYb + pTestLine->m_fPos * dYg;
		}

		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX + dErrorLen ;
		pTestLine->m_fYb = dY;

		pTestLine->m_fXe = dX - dErrorLen;
		pTestLine->m_fYe = dY;
	}
}

CXDrawDataBase* CCharElement::GetCXDrawDataBase()
{
	ASSERT (FALSE);
	return NULL;
}

CXDrawBase* CCharElement::CreateDrawElement()
{
	ASSERT (FALSE);
	return NULL;
}

BOOL CCharElement::CalCharElementExpression(CString &strExpression,double &dValue, BOOL bLogError)
{
	CCharacteristic *pCharTemp = (CCharacteristic*)GetAncestor(CHARCLASSID_CCHARACTERISTIC);
	ASSERT( pCharTemp != NULL );
	return pCharTemp->CalCharElementExpression(strExpression, dValue, bLogError);
}

double CCharElement::GetErrorLength()
{
	m_dErrLength = 0.2;
	CalCharElementExpression(m_strErrLength, m_dErrLength, TRUE);

	return m_dErrLength;
}

void CCharElement::SetTestPoint(long nPoints)
{
// 	if (nPoints < 1)//zhouhj 2023.7.25 系统自动生成点数量设置为0时,确保自定义点仍在
// 	{
// 		m_nTestPoints = 0;
// 		DeleteAll();
// 		return;
// 	}

	long nCurrPoints = GetTestLines_Sys();
	long nIndex = 0;

	if (nCurrPoints == nPoints)
	{
		return;
	}

	//2023-3-2  lijunqing
	//区分sys和用户自定一部分，只设置系统测试点的数量，对于自定义添加点，不修改
	CExBaseList oListSys, oListOther;
	SelectLines(oListSys, oListOther);
	RemoveAll();  //清空当前对象链表

	//删除中间的点数
	if (nCurrPoints > nPoints)
	{
		long nCount = nCurrPoints - nPoints;
		long nDelIndex=(nCurrPoints - nCount) / 2;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			oListSys.DeleteAt(nDelIndex);
		}
	}
	else
	{
		long nCount = nPoints - nCurrPoints;
		long nAddIndex= nCurrPoints / 2;
		CCharElementTestLine *pNew = NULL;
		POS posInsert = oListSys.FindIndex(nAddIndex);

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			pNew = new CCharElementTestLine();
			oListSys.InsertAfter(posInsert, pNew);
			pNew->SetParent(this);
		}
	}

	m_nTestPoints = nPoints;
	CCharElementTestLine *pLine = NULL;
	POS pos = oListSys.GetHeadPosition();
	nIndex=1;

	while (pos != NULL)
	{
		pLine = (CCharElementTestLine *)oListSys.GetNext(pos);
		pLine->m_fPos = nIndex;
		nIndex++;
	}

	Append(oListSys);
	Append(oListOther);
	oListSys.RemoveAll();
	oListOther.RemoveAll();
}

void CCharElement::SetUserTestPoint(long nPoints)
{
	m_nUserTestPoints = nPoints;
}

long CCharElement::GetUserTestPoints()
{
	return m_nUserTestPoints;
}

//////////////////////////////////////////////////////////////////////////
//
long CCharElement::GetTestLines_Sys()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CHARCLASSID_CCHARELEMENTTESTLINE)
		{
			if ( ((CCharElementTestLine*)p)->IsTestLineSys())
			{
				nCount++;
			}
		}
	}

	return nCount;
}

void CCharElement::SelectLines(CExBaseList &oListSys, CExBaseList &oListOther)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CHARCLASSID_CCHARELEMENTTESTLINE)
		{
			if ( ((CCharElementTestLine*)p)->IsTestLineSys())
			{
				oListSys.AddTail(p);
			}
			else
			{
				oListOther.AddTail(p);
			}
		}
		else
		{
			oListOther.AddTail(p);
		}
	}
}

void CCharElement::BeforeCalTestLines()
{
	if (GetTestLines_Sys() != m_nTestPoints)
	{
		SetTestPoint(m_nTestPoints);
	}
}

void CCharElement::CalTestLines(UINT nTestLineMode)
{

	switch (nTestLineMode)
	{
	case CHAR_TESTLINE_MODE_INDEX_PLUMB:
		CalTestLines_Plumb();
		break;

	case CHAR_TESTLINE_MODE_INDEX_VERT:
		CalTestLines_Vert();
		break;

	case CHAR_TESTLINE_MODE_INDEX_HORZ:
		CalTestLines_Horz();
		break;

	default:
		CalTestLines_Plumb();
		break;
	}

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		pTestLine->m_nTestLineID = char_GetTestLineID(this, nIndex);//m_nCharElementID * 255 + nIndex;
		nIndex++;
	}
}

void CCharElement::CalTestLines_Plumb_Arc(CXDrawData_Arc *pOwnArc)
{
	double dAngleGap = 0;
	long nPoints = m_nTestPoints + 1;

	double fAngleBegin, fAngleEnd;

	//单位为角度（不是弧度）
	if (pOwnArc->IsCW())
	{
		fAngleEnd = pOwnArc->m_fAngleBegin;
		fAngleBegin = pOwnArc->m_fAngleEnd;
	}
	else
	{
		fAngleBegin = pOwnArc->m_fAngleBegin;
		fAngleEnd = pOwnArc->m_fAngleEnd;
	}

	double fXCenter = pOwnArc->m_fXCenter;
	double  fYCenter = pOwnArc->m_fYCenter;
	double  fXRadius = pOwnArc->m_fXRadius;

	if (fAngleEnd > fAngleBegin)
	{
		dAngleGap = (fAngleEnd - fAngleBegin) / nPoints;
	}
	else
	{
		dAngleGap = (fAngleEnd + 360 - fAngleBegin) / nPoints;
	}

	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dAngle = 0, dX = 0, dY = 0, dXg = 0, dYg = 0;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dAngle = fAngleBegin + pTestLine->m_fPos * dAngleGap;

		dXg = dErrorLen * cos(dAngle * _PI_D_180);
		dYg = dErrorLen * sin(dAngle * _PI_D_180);

		pTestLine->m_fXset = fXCenter + fXRadius * cos(dAngle * _PI_D_180);
		pTestLine->m_fYset = fYCenter + fXRadius * sin(dAngle * _PI_D_180);
		pTestLine->m_fXb = pTestLine->m_fXset + dXg;
		pTestLine->m_fYb = pTestLine->m_fYset + dYg;
		pTestLine->m_fXe = pTestLine->m_fXset - dXg;
		pTestLine->m_fYe = pTestLine->m_fYset - dYg;
	}
}

void CCharElement::CalTestLines_Plumb_Line(CXDrawData_Line *pOwnLine)
{
	double  fXb, fYb,fXe ,fYe;
	fXb = pOwnLine->m_fXb;
	fYb = pOwnLine->m_fYb;
	fXe = pOwnLine->m_fXe;
	fYe = pOwnLine->m_fYe;

	double dX = fXe - fXb;
	double dY = fYe - fYb;

	CComplexNumber oC1, oC2;
	oC1.SetValue(fXb, fYb);
	oC2.SetValue(fXe, fYe);
	oC2 = oC2 - oC1;
	double dAngle = oC2.GetRadianAngle();

	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);
	double dR90 = dAngle + _PI_D_180 * 90;
	//	double dR270 = dAngle - _PI_D_180 * 90;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dX = fXb + pTestLine->m_fPos * dXg;
		dY = fYb + pTestLine->m_fPos * dYg;

		CComplexNumber oComplex(dErrorLen,dR90, COMPLEX_MODE_RADIAN);
		pTestLine->m_fXb = dX + oComplex.m_fReal;
		pTestLine->m_fYb = dY + oComplex.m_fImaginary;

		oComplex.Rotate(180, COMPLEX_MODE_DEGREE);

		pTestLine->m_fXe = dX + oComplex.m_fReal;
		pTestLine->m_fYe = dY + oComplex.m_fImaginary;

		pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
		pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
	}
}

/*
以下的函数实现的功能为：
	1、根据传入的数值区间（使用CXDrawData_Line定义的起点和终点）以及每步的计算步长，计算测试线或者测试点；
	2、添加一批次的测试线或者测试点时，CXDrawData_Line必须为线段，即定义了xb、yb、xe、ye
	3、添加一个测试点或者是一个测试线的时候，为求取传入的线与曲线的交点
	4、测试线：如果起点、终点、定值相同，则为测试点，否则为测试线
*/
//根据传入的始值和终值进行计算：计算一批次的测试线
void CCharElement::CalTestLines(CXDrawData_Line *pValRange, double dLenStep, UINT nTestLineMode)
{
	switch (nTestLineMode)
	{
	case CHAR_TESTLINE_MODE_INDEX_PLUMB:
		CalTestLines_Plumb(pValRange, dLenStep);
		break;

	case CHAR_TESTLINE_MODE_INDEX_VERT:
		CalTestLines_Vert(pValRange, dLenStep);
		break;

	case CHAR_TESTLINE_MODE_INDEX_HORZ:
		CalTestLines_Horz(pValRange, dLenStep);
		break;

	default:
		CalTestLines_Plumb(pValRange, dLenStep);
		break;
	}

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		pTestLine->m_nTestLineID = char_GetTestLineID(this, nIndex);//m_nCharElementID * 255 + nIndex;
		nIndex++;
	}
}

void CCharElement::CalTestLines_Plumb(CXDrawData_Line *pValRange, double dLenStep) //一般
{
	if(pValRange == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;
		fXb = pValRange->m_fXb;
		fYb = pValRange->m_fYb;
		fXe = pValRange->m_fXe;
		fYe = pValRange->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		CComplexNumber oC1, oC2;
		oC1.SetValue(fXb, fYb);
		oC2.SetValue(fXe, fYe);
		oC2 = oC2 - oC1;
		double dAngle = oC2.GetRadianAngle();

		double dErrorLen = GetErrorLength();

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;

		double dXg = dX * dLenStep / sqrt(pow(dX, 2) + pow(dY, 2)); //利用相似等比例计算
		double dYg = dY * dLenStep / sqrt(pow(dX, 2) + pow(dY, 2));

		double dR90 = dAngle + _PI_D_180 * 90;
		//	double dR270 = dAngle - _PI_D_180 * 90;

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;

			if(dX > fXe || dY > fYe)
			{
				break;
			}

			CComplexNumber oComplex(dErrorLen,dR90, COMPLEX_MODE_RADIAN);
			pTestLine->m_fXb = dX + oComplex.m_fReal;
			pTestLine->m_fYb = dY + oComplex.m_fImaginary;

			oComplex.Rotate(180, COMPLEX_MODE_DEGREE);

			pTestLine->m_fXe = dX + oComplex.m_fReal;
			pTestLine->m_fYe = dY + oComplex.m_fImaginary;

			pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
			pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
		}
	}
}

void CCharElement::CalTestLines_Vert(CXDrawData_Line *pValRange, double dLenStep) //垂直
{
	if(pValRange == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;

		fXb = pValRange->m_fXb;
		fYb = pValRange->m_fYb;
		fXe = pValRange->m_fXe;
		fYe = pValRange->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		double dErrorLen = GetErrorLength();
		//dErrorLen /= 2;

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;

		double dXg = dLenStep;
		double dYg = dLenStep * dY / dX;

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;

			if(dX > fXe || dY > fYe)
			{
				break;
			}

			pTestLine->m_fXset = dX;
			pTestLine->m_fYset = dY;

			pTestLine->m_fXb = dX ;
			pTestLine->m_fYb = dY + dErrorLen;

			pTestLine->m_fXe = dX;
			pTestLine->m_fYe = dY - dErrorLen;
		}
	}
}

void CCharElement::CalTestLines_Horz(CXDrawData_Line *pValRange, double dLenStep) //水平
{
	if(pValRange == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;

		fXb = pValRange->m_fXb;
		fYb = pValRange->m_fYb;
		fXe = pValRange->m_fXe;
		fYe = pValRange->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		double dErrorLen = GetErrorLength();
		//dErrorLen /= 2;

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;

		double dXg = dLenStep * dX / dY;
		double dYg = dLenStep;

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;

			if(dX > fXe || dY > fYe)
			{
				break;
			}

			pTestLine->m_fXset = dX;
			pTestLine->m_fYset = dY;

			pTestLine->m_fXb = dX + dErrorLen ;
			pTestLine->m_fYb = dY;

			pTestLine->m_fXe = dX - dErrorLen;
			pTestLine->m_fYe = dY;
		}
	}
}

//根据传入的当前位置定义进行计算：计算一个点的测试线
void CCharElement::CalTestLine(CXDrawData_Line *pCurrValLine, UINT nTestLineMode)
{
	switch (nTestLineMode)
	{
	case CHAR_TESTLINE_MODE_INDEX_PLUMB:
		CalTestLine_Plumb(pCurrValLine);
		break;

	case CHAR_TESTLINE_MODE_INDEX_VERT:
		CalTestLine_Vert(pCurrValLine);
		break;

	case CHAR_TESTLINE_MODE_INDEX_HORZ:
		CalTestLine_Horz(pCurrValLine);
		break;

	default:
		CalTestLine_Plumb(pCurrValLine);
		break;
	}

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		pTestLine->m_nTestLineID = char_GetTestLineID(this, nIndex);//m_nCharElementID * 255 + nIndex;
		nIndex++;
	}
}

void CCharElement::CalTestLine_Plumb(CXDrawData_Line *pCurrValLine)
{
	if(pCurrValLine == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;
		fXb = pCurrValLine->m_fXb;
		fYb = pCurrValLine->m_fYb;
		fXe = pCurrValLine->m_fXe;
		fYe = pCurrValLine->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		CComplexNumber oC1, oC2;
		oC1.SetValue(fXb, fYb);
		oC2.SetValue(fXe, fYe);
		oC2 = oC2 - oC1;
		double dAngle = oC2.GetRadianAngle();

		double dErrorLen = GetErrorLength();

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;
		double dXg = dX / (m_nTestPoints + 1);
		double dYg = dY / (m_nTestPoints + 1);
		double dR90 = dAngle + _PI_D_180 * 90;
		//	double dR270 = dAngle - _PI_D_180 * 90;

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;

			CComplexNumber oComplex(dErrorLen,dR90, COMPLEX_MODE_RADIAN);
			pTestLine->m_fXb = dX + oComplex.m_fReal;
			pTestLine->m_fYb = dY + oComplex.m_fImaginary;

			oComplex.Rotate(180, COMPLEX_MODE_DEGREE);

			pTestLine->m_fXe = dX + oComplex.m_fReal;
			pTestLine->m_fYe = dY + oComplex.m_fImaginary;

			pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
			pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
		}
	}
}

void CCharElement::CalTestLine_Vert(CXDrawData_Line *pCurrValLine)
{
	if(pCurrValLine == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;

		fXb = pCurrValLine->m_fXb;
		fYb = pCurrValLine->m_fYb;
		fXe = pCurrValLine->m_fXe;
		fYe = pCurrValLine->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		double dErrorLen = GetErrorLength();
		//dErrorLen /= 2;

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;
		double dXg = dX / (m_nTestPoints + 1);
		double dYg = dY / (m_nTestPoints + 1);

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;
			pTestLine->m_fXset = dX;
			pTestLine->m_fYset = dY;

			pTestLine->m_fXb = dX ;
			pTestLine->m_fYb = dY + dErrorLen;

			pTestLine->m_fXe = dX;
			pTestLine->m_fYe = dY - dErrorLen;
		}
	}
}

void CCharElement::CalTestLine_Horz(CXDrawData_Line *pCurrValLine)
{
	if(pCurrValLine == NULL)
	{
		return;
	}
	else
	{
		double  fXb, fYb, fXe, fYe;

		fXb = pCurrValLine->m_fXb;
		fYb = pCurrValLine->m_fYb;
		fXe = pCurrValLine->m_fXe;
		fYe = pCurrValLine->m_fYe;

		double dX = fXe - fXb;
		double dY = fYe - fYb;

		double dErrorLen = GetErrorLength();
		//dErrorLen /= 2;

		POS pos = GetHeadPosition();
		CCharElementTestLine *pTestLine = NULL;
		double dXg = dX / (m_nTestPoints + 1);
		double dYg = dY / (m_nTestPoints + 1);

		while (pos != NULL)
		{
			pTestLine = (CCharElementTestLine *)GetNext(pos);
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;
			pTestLine->m_fXset = dX;
			pTestLine->m_fYset = dY;

			pTestLine->m_fXb = dX + dErrorLen ;
			pTestLine->m_fYb = dY;

			pTestLine->m_fXe = dX - dErrorLen;
			pTestLine->m_fYe = dY;
		}
	}
}
