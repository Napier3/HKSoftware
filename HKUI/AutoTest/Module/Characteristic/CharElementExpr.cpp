//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementDiff.cpp  CCharElementDiff


#include "stdafx.h"
#include "CharElementExpr.h"
#include "CharacteristicTmplate.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementExpr::CCharElementExpr()
{
    //初始化属性
    m_strID = CHAR_ELEMENT_ID_DIFF;

#ifndef NOT_USE_XLANGUAGE
    m_strName = g_sLangTxt_Expr/*_T("表达式（Expr）")*/;
#else
    m_strName = _T("表达式（Expr）");
#endif

    // m_nType = CURVE_LINE_TYPE_LINE_SEGMENT;

    m_bIsStdExpr = FALSE;
    m_strExpr = _T("");
}

CCharElementExpr::~CCharElementExpr()
{

}

long CCharElementExpr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

    CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
    xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
    xml_GetAttibuteValue(pXmlKeys->m_strXeKey, oNode, m_strXe);
    xml_GetAttibuteValue(pXmlKeys->m_strYeKey, oNode, m_strYe);
    xml_GetAttibuteValue(pXmlKeys->m_strExprKey, oNode, m_strExpr);
    return 0;
}

long CCharElementExpr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
    CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
    xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
    xml_SetAttributeValue(pXmlKeys->m_strXeKey, oElement, m_strXe);
    xml_SetAttributeValue(pXmlKeys->m_strYeKey, oElement, m_strYe);
    xml_SetAttributeValue(pXmlKeys->m_strExprKey, oElement, m_strExpr);
    return 0;
}

void CCharElementExpr::InitAfterRead()
{

}

BOOL CCharElementExpr::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CCharElementExpr *p = (CCharElementExpr*)pObj;

    return TRUE;
}

BOOL CCharElementExpr::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CCharElement::CopyOwn(pDest);
    CCharElementExpr *p = (CCharElementExpr*)pDest;

    p->m_strXb = m_strXb;
    p->m_strYb = m_strYb;
    p->m_strXe = m_strXe;
    p->m_strYe = m_strYe;
    p->m_strExpr = m_strExpr;
    p->m_strScript = m_strScript;
    p->m_strArrayExprRefIDs.RemoveAll();
    p->m_strArrayExprRefIDs.Copy(m_strArrayExprRefIDs);
    p->m_bIsStdExpr = m_bIsStdExpr;
//    p->m_FunctionSignatures = m_FunctionSignatures;
    return TRUE;
}

CBaseObject* CCharElementExpr::Clone()
{
    CCharElementExpr *p = new CCharElementExpr();
    Copy(p);
    return p;
}

long CCharElementExpr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
    CCharElement::SerializeOwn(oBinaryBuffer);

    if(oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, m_strXb);
        BinarySerializeCalLen(oBinaryBuffer, m_strYb);
        BinarySerializeCalLen(oBinaryBuffer, m_strXe);
        BinarySerializeCalLen(oBinaryBuffer, m_strYe);
        BinarySerializeCalLen(oBinaryBuffer, m_strExpr);
    }
    else if(oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, m_strXb);
        BinarySerializeRead(oBinaryBuffer, m_strYb);
        BinarySerializeRead(oBinaryBuffer, m_strXe);
        BinarySerializeRead(oBinaryBuffer, m_strYe);
        BinarySerializeRead(oBinaryBuffer, m_strExpr);
        //2020-3-14  特性曲线的改进，兼容之前版本的二进制文件  lijq
        //#define GBVERSION_1_39        0X00010027
        //因为引用和包含的关系，不添加
        //如果单独使用，则可以不处理
        if (0 < oBinaryBuffer.m_dwVersion && oBinaryBuffer.m_dwVersion < 0X00010027)
        {
            BinarySerializeRead(oBinaryBuffer, m_fXb);
            BinarySerializeRead(oBinaryBuffer, m_fYb);
            BinarySerializeRead(oBinaryBuffer, m_fXe);
            BinarySerializeRead(oBinaryBuffer, m_fYe);
            //BinarySerializeRead(oBinaryBuffer, m_strExpr);
        }
    }
    else if(oBinaryBuffer.IsWriteMode())
    {
        BinarySerializeWrite(oBinaryBuffer, m_strXb);
        BinarySerializeWrite(oBinaryBuffer, m_strYb);
        BinarySerializeWrite(oBinaryBuffer, m_strXe);
        BinarySerializeWrite(oBinaryBuffer, m_strYe);
        BinarySerializeWrite(oBinaryBuffer, m_strExpr);
    }

    return 0;
}
CString CCharElementExpr::ReturnXml()
{
    CString str;
    str.Format(_T("Expr Xb=\"%s\" Yb=\"%s\" Xe=\"%s\" Ye=\"%s\" Expr=\"%s\" ")
               ,m_strXb.GetString(),m_strYb.GetString(),m_strXe.GetString()
               ,m_strYe.GetString(),m_strExpr.GetString());
    return str;
}

void CCharElementExpr::Draw(CDC *pDC)
{

}

BOOL CCharElementExpr::GetStdExprResult(double dX, double &dY)
{
    CCharacteristic *pCharTemp = (CCharacteristic*)GetAncestor(CHARCLASSID_CCHARACTERISTIC);
    ASSERT( pCharTemp != NULL );
    CCharInterface* pCharInterface = pCharTemp->GetCharInterface();

	if (m_strExpr.GetLength() == 0)
	{
		return FALSE;
	}

	CEpExpression oEpExp;

	if (oEpExp.ChangeEpExpression(m_strExpr) == -1)
	{
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式【%s】 错误")
#endif
			, m_strExpr.GetString());
		return FALSE;
	}

	CString strValue;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (pCharInterface->GetVariableValue(pExpVar->m_strVarID, strValue))
		{
			pExpVar->m_dValue = CString_To_double(strValue);
		}
		else
		{
//			if (bLogError)
			{

#ifndef NOT_USE_XLANGUAGE
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/
#else
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式变量【%s】 错误")
#endif
					, pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	pExpVar = oEpExp.FindVariable(_T("X"));

	if (pExpVar != NULL)
	{
		pExpVar->m_dValue = dX;
	}
	else
	{
		bTrue = FALSE;
	}

    oEpExp.Value(/*dX*/dY);//获取结果应该给dY，而不是dX
	return bTrue;
}

double CCharElementExpr::GetStdExprResult(double &dVal)
{
    CCharacteristic *pCharTemp = (CCharacteristic*)GetAncestor(CHARCLASSID_CCHARACTERISTIC);
    ASSERT( pCharTemp != NULL );
    CCharInterface* pCharInterface = pCharTemp->GetCharInterface();
    CCharInterfaceVariable *pVariable = NULL;
    if(m_bIsStdExpr)
    {
        pVariable = (CCharInterfaceVariable*)pCharInterface->FindByID(GetXVarIDPath());
        if(pVariable != NULL)
        {
            CString RefValue;
            RefValue.Format(_T("%lf"),dVal);
            pVariable->m_strValue = RefValue;
        }
    }
    else
    {
        pVariable = (CCharInterfaceVariable*)pCharInterface->FindByID(_T("X"));
        if(pVariable != NULL)
        {
            CString RefValue;
            RefValue.Format(_T("%lf"),dVal);
            pVariable->m_strValue = RefValue;
        }
    }

    double dExprResult;
    pCharTemp->CalCharElementExpression(m_strExpr, dExprResult, TRUE);
    return dExprResult;
}

CString CCharElementExpr::GetXVarIDPath()
{
    for(int i = 0 ;i < m_strArrayExprRefIDs.GetCount(); ++i)
    {
        if(m_strArrayExprRefIDs.GetAt(i).GetAt(0) == _T('X') )
        {
            return m_strArrayExprRefIDs.GetAt(i);
        }
    }
    return _T("");
}

CXDrawBase* CCharElementExpr::CreateDrawElement()
{
    CXDrawPolyline *pNew = new CXDrawPolyline();
    m_pDataRef = pNew;

    CXDrawData_Points::DataCopy(pNew);

    return (CXDrawBase*)m_pDataRef;
}

void CCharElementExpr::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
    CCharacteristic *pChar = (CCharacteristic*)GetAncestor(CHARCLASSID_CCHARACTERISTIC);
    m_bIsAutoClose = pChar->m_nAutoClose;
    //计算自身数据
    CalCharElementExpression(m_strXb, m_fXb, TRUE);
    CalCharElementExpression(m_strXe, m_fXe, TRUE);
    CalCharElementExpression(m_strYb, m_fYb, TRUE);
    CalCharElementExpression(m_strYe, m_fYe, TRUE);
	CalExprPolyline();
}

void CCharElementExpr::CalExprPolyline()
{
    m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
    double dIbias = m_fXb, dIdiff = 0;
    SetPointsMax(200); //初始化为200点
    BOOL bTrue = TRUE;
    //计算差动部分
    while (bTrue)
    {
        bTrue = IncreaseX(dIbias);
		dIdiff = CalExpr(dIbias);
        if (dIdiff < 0)
        {
            continue;
        }

        if (dIdiff > m_fYe)
        {
            continue;
        }

        if (!HasPoints())
        {
            ExpandPointsMax(50);
        }

        AddPoint(dIbias, dIdiff);
    }

    //AddPointEx(dIbias, dIdiff);
}

BOOL CCharElementExpr::IncreaseX(double &dValX)
{
    double dStand = (m_fXe-m_fXb)/m_nPointsMax;

    if (dValX >= m_fXe)
    {
        return FALSE;
    }

    dValX += dStand;

    return TRUE;
}
double CCharElementExpr::CalExpr(double dVal)
{
    //无论是不是标准的，暂时全部按标准处理    
//    double dY = 0.0f;
//    GetStdExprResult(dVal, dY);
//    return dY;
    //此处仍然调用之前的方法，GetStdExprResult(dVal, dY)存在问题
    //ID_33_08/100*X3+IS1 对于类型类似的表达式，GetStdExprResult(dVal, dY)只会在interface中查找参数X3，而不是调用IncreaseX对其进行赋值，而X3应该是对应变量X
    //对于一次的表达式没有影响，但是如果是二次以上的就有问题。
    //m_bIsStdExpr变量在能调用VB代码前仍然需要。
    return GetStdExprResult(dVal);
}

void CCharElementExpr::BeforeCalTestLines()
{
	DeleteAll();

	if ((fabs(m_fXb - m_fXe)<0.00001f))//起始位置为终点位置相同时,不可均分
	{
		return;
	}

	double dBegin = m_fXb;
	double dEnd = m_fXe;
	double dStep = (m_fXe - m_fXb) / (m_nTestPoints+1);
	double dPos = dBegin + dStep;

	while (TRUE)
	{
		CCharTestLine *pTestLine = new CCharTestLine;
		AddNewChild(pTestLine);
		pTestLine->m_fPos = dPos;
		dPos += dStep;

		if (fabs(dPos - dEnd)<0.00001f)//当前值和终值相同时,则不再添加
		{
			break;
		}

		if ((dBegin > dEnd) && (dPos <= dEnd))
		{
			break;
		}
		else if ((dBegin < dEnd) && (dPos >= dEnd))
		{
			break;
		}
	}
}

void CCharElementExpr::CalTestLines(UINT nTestLineMode)
{
	POS pos = GetHeadPosition();
	CCharTestLine *pTestLine = NULL;
	double dValue1 = 0.0f;
	double dErrorLenth = GetErrorLength();

	while (pos != NULL)
	{
		pTestLine = (CCharTestLine *)GetNext(pos);

		pTestLine->m_fXset = pTestLine->m_fPos;
		pTestLine->m_fXb = pTestLine->m_fPos;
		pTestLine->m_fYset = CalExpr(pTestLine->m_fPos);
		pTestLine->m_fXe = pTestLine->m_fPos;

		pTestLine->m_fYb = pTestLine->m_fYset + dErrorLenth / 2;
		pTestLine->m_fYe = pTestLine->m_fYset - dErrorLenth / 2;

		pTestLine->m_fXact = pTestLine->m_fPos;
		pTestLine->m_fYact = pTestLine->m_fYset;
	}
}
