//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementTestLine.cpp  CCharElementTestLine


#include "stdafx.h"
#include "CharElementTestLine.h"
#include "../GuideBook/GuideBookDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementTestLine::CCharElementTestLine()
{
	//初始化属性
	m_strType = CHAR_TEST_LINE_TYPE_SYS;      
	m_fPos = 1;
	m_fRotateAngle = 0; 
	m_strAngleDef.Empty();   

	m_fXb = 0;
	m_fYb = 0;
	m_fXe = 0;
	m_fYe = 0;
	m_fXset = 0;
	m_fYset = 0;

	m_nActState = 0;
	m_fXact = 0;
	m_fYact = 0;

	//初始化成员变量
	m_pMacroTestItemRef = NULL;
	m_nTestLineID = -1;
}

CCharElementTestLine::~CCharElementTestLine()
{
}

long CCharElementTestLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strPosKey, oNode, m_fPos);
	xml_GetAttibuteValue(pXmlKeys->m_strRotateAngleKey, oNode, m_fRotateAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleDefKey, oNode, m_strAngleDef);

	return 0;
}

long CCharElementTestLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strPosKey, oElement, m_fPos);
	xml_SetAttributeValue(pXmlKeys->m_strRotateAngleKey, oElement, m_fRotateAngle);
	xml_SetAttributeValue(pXmlKeys->m_strAngleDefKey, oElement, m_strAngleDef);

	return 0;
}

BOOL CCharElementTestLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementTestLine *p = (CCharElementTestLine*)pObj;


	return TRUE;
}

BOOL CCharElementTestLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementTestLine *p = (CCharElementTestLine*)pDest;

	p->m_strType = m_strType;      

	//位置比例关系：sys=点编号，1~TestPoints；user=线位置，0<值范围<1
	p->m_fPos = m_fPos;

	//旋转的角度
	p->m_fRotateAngle = m_fRotateAngle; 

	//测试线角度定义：空，表示垂线或者角平分线；角度计算公式
	//起始点的x、y位置计算脚本，
	p->m_strAngleDef = m_strAngleDef;   
	p->m_strPosScpt = m_strPosScpt;

	//计算出来实际值，执行测试时的临时数值
	p->m_fXb = m_fXb;
	p->m_fYb = m_fYb;
	p->m_fXe = m_fXe;
	p->m_fYe = m_fYe;
	p->m_fXset = m_fXset;
	p->m_fYset = m_fYset;

	p->m_nActState = m_nActState;
	p->m_fXact = m_fXact;
	p->m_fYact = m_fYact;

	//关联的测试项目
	p->m_pMacroTestItemRef = m_pMacroTestItemRef;

	p->m_nTestLineID = m_nTestLineID;	

	return TRUE;
}

CBaseObject* CCharElementTestLine::Clone()
{
	CCharElementTestLine *p = new CCharElementTestLine();
	Copy(p);
	return p;
}

long CCharElementTestLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_fPos);
		BinarySerializeCalLen(oBinaryBuffer, m_fRotateAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngleDef);

		BinarySerializeCalLen(oBinaryBuffer, m_fXb);
		BinarySerializeCalLen(oBinaryBuffer, m_fYb);
		BinarySerializeCalLen(oBinaryBuffer, m_fXe);
		BinarySerializeCalLen(oBinaryBuffer, m_fYe);
		BinarySerializeCalLen(oBinaryBuffer, m_fXset);
		BinarySerializeCalLen(oBinaryBuffer, m_fYset);
		BinarySerializeCalLen(oBinaryBuffer, m_nActState);
		BinarySerializeCalLen(oBinaryBuffer, m_fYact);
		BinarySerializeCalLen(oBinaryBuffer, m_fXact);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestLineID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_fPos);
		BinarySerializeRead(oBinaryBuffer, m_fRotateAngle);
		BinarySerializeRead(oBinaryBuffer, m_strAngleDef);

		BinarySerializeRead(oBinaryBuffer, m_fXb);
		BinarySerializeRead(oBinaryBuffer, m_fYb);
		BinarySerializeRead(oBinaryBuffer, m_fXe);
		BinarySerializeRead(oBinaryBuffer, m_fYe);
		BinarySerializeRead(oBinaryBuffer, m_fXset);
		BinarySerializeRead(oBinaryBuffer, m_fYset);
		BinarySerializeRead(oBinaryBuffer, m_nActState);
		BinarySerializeRead(oBinaryBuffer, m_fYact);
		BinarySerializeRead(oBinaryBuffer, m_fXact);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_35)
		{
			BinarySerializeRead(oBinaryBuffer, m_nTestLineID);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_fPos);
		BinarySerializeWrite(oBinaryBuffer, m_fRotateAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strAngleDef);

		BinarySerializeWrite(oBinaryBuffer, m_fXb);
		BinarySerializeWrite(oBinaryBuffer, m_fYb);
		BinarySerializeWrite(oBinaryBuffer, m_fXe);
		BinarySerializeWrite(oBinaryBuffer, m_fYe);
		BinarySerializeWrite(oBinaryBuffer, m_fXset);
		BinarySerializeWrite(oBinaryBuffer, m_fYset);
		BinarySerializeWrite(oBinaryBuffer, m_nActState);
		BinarySerializeWrite(oBinaryBuffer, m_fYact);
		BinarySerializeWrite(oBinaryBuffer, m_fXact);
		BinarySerializeWrite(oBinaryBuffer, m_nTestLineID);
	}

	return 0;
}

// 
// CExBaseObject* CCharElementTestLine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject *pNew  = NULL;
// 	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
// 
// 
// 
// 	return pNew;
// }
// 
// CExBaseObject* CCharElementTestLine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 
// 	return pNew;
// }

long CCharElementTestLine::GetXDrawElement(CXDrawList *pDrawList)
{
	CXDrawLine *pXLine = NULL;
	CXDrawPoint *pXPoint = NULL;

	if (math_IsEqual(m_fXb, m_fXe) && math_IsEqual(m_fYb, m_fYe))
	{
		return 0;
	}

	pXLine = new CXDrawLine();
	pXLine->m_fYb = m_fYb;
	pXLine->m_fXb = m_fXb;
	pXLine->m_fYe = m_fYe;
	pXLine->m_fXe = m_fXe;
	pXLine->m_crForeColor = RGB(0, 0, 255);
	pDrawList->AddNewChild(pXLine);
	pXLine->m_pXDrawDataRef = this;

	if (TESTLINE_ACT_STATE_ACT == m_nActState)
	{
		pXPoint = new CXDrawPoint();
		pXPoint->m_fX = m_fXact;
		pXPoint->m_fY = m_fYact;
		pXPoint->m_dwDrawStyle = 0;
		pXPoint->m_crForeColor = RGB(255, 0, 0);
		pDrawList->AddNewChild(pXPoint);
		pXPoint->m_pXDrawDataRef = this;
		pXLine->m_crForeColor = RGB(192,192,192);
		return 2;
		//pXLine->m_nStyle = PS_DASH;
	}
	else
	{
		return 1;
	}
}

