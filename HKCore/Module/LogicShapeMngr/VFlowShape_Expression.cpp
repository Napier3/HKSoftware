//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShape_Expression.cpp  CVFlowShape_Expression


#include "stdafx.h"
#include "VFlowShape_Expression.h"
#include "../Expression/EpExpression.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape_Expression::CVFlowShape_Expression()
{
	//��ʼ������

	//��ʼ����Ա����
}

CVFlowShape_Expression::~CVFlowShape_Expression()
{
}

long CVFlowShape_Expression::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Expression::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Expression::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShape::SerializeOwn(oBinaryBuffer);
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

void CVFlowShape_Expression::InitAfterRead()
{
}

BOOL CVFlowShape_Expression::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShape::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape_Expression *p = (CVFlowShape_Expression*)pObj;

	return TRUE;
}

BOOL CVFlowShape_Expression::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShape::CopyOwn(pDest);

	CVFlowShape_Expression *p = (CVFlowShape_Expression*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape_Expression::Clone()
{
	CVFlowShape_Expression *p = new CVFlowShape_Expression();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape_Expression::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape_Expression *p = new CVFlowShape_Expression();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape_Expression::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape_Expression::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape_Expression::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

void CVFlowShape_Expression::UpdateLineType_Color()
{
	CalcExpressionValue();
 	double nValue = CString_To_long(m_strData3);//�˴�����Ҫ��������,��Ҫ��������������ش��룻
// 	m_strData3.Format(_T("%ld"),nValue);
	CVFlowShape::UpdateLineType_Color();

	if (nValue>0)
	{
		SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_TRUE);
		SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_TRUE);
	} 
	else
	{
		SetShapeLineType(VISIO_SHAPE_SHOW_LINE_TYPE_FALSE);
		SetShapeColor(VISIO_SHAPE_SHOW_TYPE_COLOR_FALSE);
	}

	m_oOutLines.UpdateAllShapes();
}

BOOL CVFlowShape_Expression::CalcExpressionValue()
{
	CEpExpression oEpExp;

	if (m_strData1.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��������ڵ�(%s)��Ӧ�ı��ʽΪ��."),m_strID);
		return FALSE;
	}

	if (oEpExp.ChangeEpExpression(m_strData1) == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ǰ��������ڵ�(%s)��Ӧ�ı��ʽ��%s�� ����."),m_strID, m_strData1.GetString());
		return FALSE;
	}

	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	CVFlowShapeBase *pCurLine = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);
		pCurLine = (CVFlowShapeBase*)m_oInLines.FindByID(pExpVar->m_strVarID);

		if (pCurLine == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ǰ��������ڵ�(%s)��Ӧ���ʽ������%s��δ�ҵ�."),m_strID, pExpVar->m_strVarID.GetString());
			bTrue = FALSE;
			continue;
		}

#ifdef _UNICODE
		pExpVar->m_dValue = _wtof(pCurLine->m_strData3);
#else
		pExpVar->m_dValue = atof(pCurLine->m_strData3.GetString());
#endif
	}

	double dValue = 0;
	oEpExp.Value(dValue);
	m_strData3.Format(_T("%lf"),dValue);
	return bTrue;
}