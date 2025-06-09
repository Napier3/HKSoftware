//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapesBase.cpp  CVFlowShapesBase


#include "stdafx.h"
#include "VFlowShapesBase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVFlowShapesBase::CVFlowShapesBase()
{
	//初始化属性

	//初始化成员变量
}

CVFlowShapesBase::~CVFlowShapesBase()
{
}

long CVFlowShapesBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapesBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVFlowShapesBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CVFlowShapesBase::InitAfterRead()
{
}

BOOL CVFlowShapesBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVFlowShapesBase *p = (CVFlowShapesBase*)pObj;

	return TRUE;
}

BOOL CVFlowShapesBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CVFlowShapesBase *p = (CVFlowShapesBase*)pDest;

	return TRUE;
}

CBaseObject* CVFlowShapesBase::Clone()
{
	CVFlowShapesBase *p = new CVFlowShapesBase();
	Copy(p);
	return p;
}

CBaseObject* CVFlowShapesBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CVFlowShapesBase *p = new CVFlowShapesBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CVFlowShapesBase::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CVFlowShapesBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CLogicShapeMngrXmlRWKeys *pXmlKeys = (CLogicShapeMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CVFlowShapesBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CVFlowShapeBase* CVFlowShapesBase::FindByVisioID(long nVisioID)
{
	CVFlowShapeBase* pShapeBase = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pShapeBase = (CVFlowShapeBase*)GetNext(pos);

		if (pShapeBase->m_nVisioID == nVisioID)
		{
			return pShapeBase;
		}
	}

	return NULL;
}

CVFlowShapeBase* CVFlowShapesBase::FindByData1(const CString &strData1)
{
	CVFlowShapeBase* pShapeBase = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pShapeBase = (CVFlowShapeBase*)GetNext(pos);

		if (pShapeBase->m_strData1 == strData1)
		{
			return pShapeBase;
		}
	}

	return NULL;
}

BOOL CVFlowShapesBase::UpdateAllShapes()
{
	CVFlowShapeBase *pCurShape = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurShape = (CVFlowShapeBase *)GetNext(pos);
		pCurShape->UpdateLineType_Color();
	}

	return TRUE;
}

BOOL CVFlowShapesBase::SetValueByID(const CString &strID,const CString &strValue)
{
	CVFlowShapeBase* pShapeBase = (CVFlowShapeBase*)FindByID(strID);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	pShapeBase->m_strData3 = strValue;
	return TRUE;
}

BOOL CVFlowShapesBase::GetValueByID(const CString &strID,CString &strValue)
{
	CVFlowShapeBase* pShapeBase = (CVFlowShapeBase*)FindByID(strID);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	pShapeBase->m_strData3 = strValue;
	return TRUE;
}

BOOL CVFlowShapesBase::SetValueByData1(const CString &strData1,const CString &strValue)
{
	CVFlowShapeBase* pShapeBase = FindByData1(strData1);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	pShapeBase->m_strData3 = strValue;
	return TRUE;
}

BOOL CVFlowShapesBase::SetValueByID_UI(const CString &strID,const CString &strValue)
{
	CVFlowShapeBase* pShapeBase = (CVFlowShapeBase*)FindByID(strID);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	return pShapeBase->SetData3_UI(strValue);
}

BOOL CVFlowShapesBase::SetValueByData1_UI(const CString &strData1,const CString &strValue)
{
	CVFlowShapeBase* pShapeBase = FindByData1(strData1);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	return pShapeBase->SetData3_UI(strValue);
}

BOOL CVFlowShapesBase::GetValueByData1_UI(const CString &strData1,CString &strValue)
{
	CVFlowShapeBase* pShapeBase = FindByData1(strData1);

	if (pShapeBase == NULL)
	{
		return FALSE;
	}

	return pShapeBase->GetData3_UI(strValue);
}



