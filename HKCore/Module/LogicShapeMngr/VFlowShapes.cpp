//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapes.cpp  CVFlowShapes


#include "stdafx.h"
#include "VFlowShapes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapes::CVFlowShapes()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShapes::~CVFlowShapes()
{
}

long CVFlowShapes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapesBase::XmlReadOwn(oNode, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVFlowShapesBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CVFlowShapesBase::SerializeOwn(oBinaryBuffer);
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

void CVFlowShapes::InitAfterRead()
{
}

BOOL CVFlowShapes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CVFlowShapesBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapes *p = (CVFlowShapes*)pObj;

	return TRUE;
}

BOOL CVFlowShapes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVFlowShapesBase::CopyOwn(pDest);

	CVFlowShapes *p = (CVFlowShapes*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShapes::Clone()
{
	CVFlowShapes *p = new CVFlowShapes();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapes *p = new CVFlowShapes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapes::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPE_DATA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPE_LOGIC)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPE_EXPRESSION)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPE_BRANCH)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CVFLOWSHAPE_THRESHOLD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CVFlowShapes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCVFlowShapeLineKey)
	{
		pNew = new CVFlowShapeLine();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShape_DataKey)
	{
		pNew = new CVFlowShape_Data();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShape_LogicKey)
	{
		pNew = new CVFlowShape_Logic();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShape_ExpressionKey)
	{
		pNew = new CVFlowShape_Expression();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShape_BranchKey)
	{
		pNew = new CVFlowShape_Branch();
	}
	else if (strClassID == pXmlKeys->m_strCVFlowShape_ThresholdKey)
	{
		pNew = new CVFlowShape_Threshold();
	}

	return pNew;
}

CExBaseObject* CVFlowShapes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CVFLOWSHAPELINE)
	{
		pNew = new CVFlowShapeLine();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPE_DATA)
	{
		pNew = new CVFlowShape_Data();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPE_LOGIC)
	{
		pNew = new CVFlowShape_Logic();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPE_EXPRESSION)
	{
		pNew = new CVFlowShape_Expression();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPE_BRANCH)
	{
		pNew = new CVFlowShape_Branch();
	}
	else if (nClassID == MNGRCLASSID_CVFLOWSHAPE_THRESHOLD)
	{
		pNew = new CVFlowShape_Threshold();
	}

	return pNew;
}

void CVFlowShapes::InitShapes()
{
	CVFlowShape *pCurShape = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurShape = (CVFlowShape *)GetNext(pos);
		pCurShape->m_bHasAttachCalc = FALSE;
	}
}

void CVFlowShapes::GetAllResultShapes(CVFlowShapes *pResultRefShapes)
{
	CVFlowShape *pCurShape = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurShape = (CVFlowShape *)GetNext(pos);

		if (!pCurShape->m_bHasAttachCalc)
		{
			if (pCurShape->m_oOutLines.GetCount() == 0)
			{
				pCurShape->m_bHasAttachCalc = TRUE;
				pResultRefShapes->AddTail(pCurShape);
			}
		}
	}
}

