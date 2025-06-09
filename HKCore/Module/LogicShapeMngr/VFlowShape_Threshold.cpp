//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShape_Threshold.cpp  CVFlowShape_Threshold


#include "stdafx.h"
#include "VFlowShape_Threshold.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShape_Threshold::CVFlowShape_Threshold()
{
	//��ʼ������

	//��ʼ����Ա����
}

CVFlowShape_Threshold::~CVFlowShape_Threshold()
{
}

long CVFlowShape_Threshold::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape_Logic::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Threshold::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShape_Logic::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShape_Threshold::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShape_Logic::SerializeOwn(oBinaryBuffer);
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

void CVFlowShape_Threshold::InitAfterRead()
{
}

BOOL CVFlowShape_Threshold::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShape_Logic::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShape_Threshold *p = (CVFlowShape_Threshold*)pObj;

	return TRUE;
}

BOOL CVFlowShape_Threshold::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShape_Logic::CopyOwn(pDest);

	CVFlowShape_Threshold *p = (CVFlowShape_Threshold*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShape_Threshold::Clone()
{
	CVFlowShape_Threshold *p = new CVFlowShape_Threshold();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShape_Threshold::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShape_Threshold *p = new CVFlowShape_Threshold();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShape_Threshold::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShape_Threshold::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShape_Threshold::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

long CVFlowShape_Threshold::CalcThresholdValue()
{
	CVFlowShapeProperty *pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_SETTING_VALUE);

	if (pProperty == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���Žڵ�Shape(%s)ȱ������ֵ����."),m_strName);
		return 0;
	}

	double dSettingValue = 0,dRealValue = 0;
	CString strValue,strUnit;
	Global_GetValueUnit(pProperty->m_strValue,strValue,strUnit);
	dSettingValue = CString_To_double(strValue);

	pProperty = (CVFlowShapeProperty*)FindByID(VFLOW_VISIO_REAL_VALUE);

	if (pProperty == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���Žڵ�Shape(%s)ȱ��ʵ��ֵ����."),m_strName);
		return 0;
	}

	Global_GetValueUnit(pProperty->m_strValue,strValue,strUnit);
	dRealValue = CString_To_double(strValue);

	long nValue = 0;

	if (dRealValue>dSettingValue)//���ʵ��ֵ��������ֵ���������߼�Ҫ�󣬴�ʱ��Ҫ��������Ƿ������߼�Ҫ��
	{
		nValue = CalcLogicValue();
	} 

	m_strData3.Format(_T("%ld"),nValue);
	return nValue;
}

void CVFlowShape_Threshold::UpdateLineType_Color()
{
	long nValue = CalcThresholdValue();
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
