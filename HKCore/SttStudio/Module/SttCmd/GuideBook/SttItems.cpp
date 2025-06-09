//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttItems.cpp  CSttItems


#include "stdafx.h"
#include "SttItems.h"
#include "../../../../Module/BaseClass/ComplexNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//CMacroCharItemLineDef
CSttMacroCharItemLineDef::CSttMacroCharItemLineDef()
{
	m_fXb = 0;
	m_fYb = 0;
	m_fXe = 0;
	m_fYe = 0;
	m_fXset = 0;
	m_fYset = 0;
	m_fXact = 0;
	m_fYact = 0;

	m_fSearchXb = 0;
	m_fSearchYb = 0;
	m_nSearchActb = 0;
	m_fSearchXe = 0;
	m_fSearchYe = 0;
	m_nSearchActe = 0;
	m_fSearchXc = 0;
	m_fSearchYc = 0;
}

CSttMacroCharItemLineDef::~CSttMacroCharItemLineDef()
{

}


long CSttMacroCharItemLineDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	//	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strAxisModeKey,oNode,m_strAxisMode);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXbKey,oNode,m_strParaIdXb);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYbKey,oNode,m_strParaIdYb);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXeKey,oNode,m_strParaIdXe);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYeKey,oNode,m_strParaIdYe);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXsetKey,oNode,m_strParaIdXset);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYsetKey,oNode,m_strParaIdYset);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXactKey,oNode,m_strParaIdXact);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYactKey,oNode,m_strParaIdYact);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdFlagActKey,oNode,m_strParaIdFlagAct);

	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXbKey,oNode,m_strParaIdSearchXb);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYbKey,oNode,m_strParaIdSearchYb);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActbKey,oNode,m_strParaIdSearchActb);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXeKey,oNode,m_strParaIdSearchXe);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYeKey,oNode,m_strParaIdSearchYe);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActeKey,oNode,m_strParaIdSearchActe);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXcKey,oNode,m_strParaIdSearchXc);
	xml_GetAttibuteValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYcKey,oNode,m_strParaIdSearchYc);

	return 0;
}

long CSttMacroCharItemLineDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	// 	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strTypeKey,oElement,m_strType);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strAxisModeKey,oElement,m_strAxisMode);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXbKey,oElement,m_strParaIdXb);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYbKey,oElement,m_strParaIdYb);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXeKey,oElement,m_strParaIdXe);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYeKey,oElement,m_strParaIdYe);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXsetKey,oElement,m_strParaIdXset);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYsetKey,oElement,m_strParaIdYset);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdXactKey,oElement,m_strParaIdXact);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdYactKey,oElement,m_strParaIdYact);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdFlagActKey,oElement,m_strParaIdFlagAct);

	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXbKey,oElement,m_strParaIdSearchXb);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYbKey,oElement,m_strParaIdSearchYb);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActbKey,oElement,m_strParaIdSearchActb);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXeKey,oElement,m_strParaIdSearchXe);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYeKey,oElement,m_strParaIdSearchYe);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActeKey,oElement,m_strParaIdSearchActe);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXcKey,oElement,m_strParaIdSearchXc);
	xml_SetAttributeValue(CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYcKey,oElement,m_strParaIdSearchYc);

	return 0;
}

BOOL CSttMacroCharItemLineDef::IsEqualOwn(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CSttMacroCharItemLineDef::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CSttMacroCharItemLineDef *p = (CSttMacroCharItemLineDef*)pDest;

	p->m_strType = m_strType;
	p->m_strAxisMode = m_strAxisMode;
	p->m_strParaIdXb = m_strParaIdXb;
	p->m_strParaIdYb = m_strParaIdYb;
	p->m_strParaIdXe = m_strParaIdXe;
	p->m_strParaIdYe = m_strParaIdYe;
	p->m_strParaIdXset = m_strParaIdXset;
	p->m_strParaIdYset = m_strParaIdYset;
	p->m_strParaIdXact = m_strParaIdXact;
	p->m_strParaIdYact = m_strParaIdYact;
	p->m_strParaIdFlagAct = m_strParaIdFlagAct;

	p->m_strParaIdSearchXb = m_strParaIdSearchXb;
	p->m_strParaIdSearchYb = m_strParaIdSearchYb;
	p->m_strParaIdSearchActb = m_strParaIdSearchActb;
	p->m_strParaIdSearchXe = m_strParaIdSearchXe;
	p->m_strParaIdSearchYe = m_strParaIdSearchYe;
	p->m_strParaIdSearchActe = m_strParaIdSearchActe;
	p->m_strParaIdSearchXc = m_strParaIdSearchXc;
	p->m_strParaIdSearchYc = m_strParaIdSearchYc;

	return TRUE;
}

CBaseObject* CSttMacroCharItemLineDef::Clone()
{
	CSttMacroCharItemLineDef* pNew = new CSttMacroCharItemLineDef();
	Copy(pNew);

	return pNew;
}


long CSttMacroCharItemLineDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strAxisMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdXe);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdYe);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdXset);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdYset);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdXact);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdYact);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdFlagAct);

		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchActb);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchXe);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchYe);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchActe);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchXc);
		BinarySerializeCalLen(oBinaryBuffer, m_strParaIdSearchYc);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strAxisMode);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdXb);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdYb);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdXe);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdYe);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdXset);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdYset);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdXact);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdYact);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdFlagAct);

		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchXb);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchYb);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchActb);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchXe);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchYe);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchActe);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchXc);
		BinarySerializeRead(oBinaryBuffer, m_strParaIdSearchYc);
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strAxisMode);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdXb);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdYb);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdXe);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdYe);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdXset);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdYset);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdXact);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdYact);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdFlagAct);

		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchXb);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchYb);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchActb);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchXe);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchYe);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchActe);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchXc);
		BinarySerializeWrite(oBinaryBuffer, m_strParaIdSearchYc);
	}

	return 0;
}

BOOL CSttMacroCharItemLineDef::IsAxisMode_x_y()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_XY);
}

BOOL CSttMacroCharItemLineDef::IsAxisMode_r_angle()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_RANGLE);
}

void CSttMacroCharItemLineDef::ChangeValueXY(double &dX, double &dY)
{
	if (IsAxisMode_r_angle())
	{
		CComplexNumber oComplex(dX, dY, COMPLEX_MODE_DEGREE);
		oComplex.GetValue(dX, dY);
	}
}

void CSttMacroCharItemLineDef::InitSearchValues(CValues *pSearchReport)
{
	m_nSearchActb = TESTLINE_ACT_STATE_NONE;
	m_nSearchActe = TESTLINE_ACT_STATE_NONE;

	pSearchReport->GetValue(m_strParaIdSearchXb, m_fSearchXb);
	pSearchReport->GetValue(m_strParaIdSearchYb, m_fSearchYb);
	pSearchReport->GetValue(m_strParaIdSearchActb, m_nSearchActb);
	pSearchReport->GetValue(m_strParaIdSearchXe, m_fSearchXe);
	pSearchReport->GetValue(m_strParaIdSearchYe, m_fSearchYe);
	pSearchReport->GetValue(m_strParaIdSearchActe, m_nSearchActe);
	pSearchReport->GetValue(m_strParaIdSearchXc, m_fSearchXc);
	pSearchReport->GetValue(m_strParaIdSearchYc, m_fSearchYc);

	ChangeValueXY(m_fSearchXb, m_fSearchYb);
	ChangeValueXY(m_fSearchXc, m_fSearchYc);
	ChangeValueXY(m_fSearchXe, m_fSearchYe);
}

/*
<group name="" id="SearchLine">
	<data name="" id="x-b" value="" />
	<data name="" id="y-b" value="" />
	<data name="" id="x-e" value="" />
	<data name="" id="y-e" value="" />
	<data name="" id="x-set" value="" />
	<data name="" id="y-set" value="" />
	<data name="" id="x-act" value="" />
	<data name="" id="y-act" value="" />
	<data name="" id="flag-act" value="" />
	<data name="" id="search-x-b" value="" />
	<data name="" id="search-y-b" value="" />
	<data name="" id="search-actb" value="" />
	<data name="" id="search-x-e" value="" />
	<data name="" id="search-y-e" value="" />
	<data name="" id="search-acte" value="" />
	<data name="" id="search-x-c" value="" />
	<data name="" id="search-y-c" value="" />
</group>
*/
void CSttMacroCharItemLineDef::GetSearchValues(CValues *pSearchLine)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = CSttCmdDefineXmlRWKeys::g_pXmlKeys;

// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdXbKey, m_fXb);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdYbKey, m_fYb);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdXeKey, m_fXe);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdYeKey, m_fYe);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdXsetKey, m_fXset);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdYsetKey, m_fYset);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdXactKey, m_fXact);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdYactKey, m_fYact);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdFlagActKey, m_nFlagAct);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchXbKey, m_fSearchXb);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchYbKey, m_fSearchYb);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchActbKey, m_nSearchActb);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchXeKey, m_fSearchXe);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchYeKey, m_fSearchYe);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchActeKey, m_nSearchActe);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchXcKey, m_fSearchXc);
// 	pSearchLine->GetValue(	pXmlKeys->m_strParaIdSearchYcKey, m_fSearchYc);
	pSearchLine->GetValue("x-b",	m_fXb);
	pSearchLine->GetValue("y-b",	m_fYb);
	pSearchLine->GetValue("x-e",	m_fXe);
	pSearchLine->GetValue("y-e",	m_fYe);
	pSearchLine->GetValue("x-set",	m_fXset);
	pSearchLine->GetValue("y-set",	m_fYset);
	pSearchLine->GetValue("x-act",	m_fXact);
	pSearchLine->GetValue("y-act",	m_fYact);
	pSearchLine->GetValue("flag-act",	m_nFlagAct);
	pSearchLine->GetValue("search-x-b",	m_fSearchXb);
	pSearchLine->GetValue("search-y-b",	m_fSearchYb);
	pSearchLine->GetValue("search-actb",	m_nSearchActb);
	pSearchLine->GetValue("search-x-e",	m_fSearchXe);
	pSearchLine->GetValue("search-y-e",	m_fSearchYe);
	pSearchLine->GetValue("search-acte",	m_nSearchActe);
	pSearchLine->GetValue("search-x-c",	m_fSearchXc);
	pSearchLine->GetValue("search-y-c",	m_fSearchYc);

}

//////////////////////////////////////////////////////////////////////////
//CSttItems
CSttItems::CSttItems()
{
	//初始化属性
	m_nTestTimes = 1;//测试次数，=1表示测一次
	//初始化成员变量
	m_nRptTitle = 0;
	m_nTitleLevel = 1;
}

CSttItems::~CSttItems()
{
}

long CSttItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strCharacteristicIDKey, oNode, m_strCharacteristicID);
	xml_GetAttibuteValue(pXmlKeys->m_strStxmlFileKey, oNode, m_strstxmlFile);
	xml_GetAttibuteValue(pXmlKeys->m_strWzdMapFileKey, oNode, m_strWzdMapFile);
	xml_GetAttibuteValue(pXmlKeys->m_strActLogicKey, oNode, m_strActLogic);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nTestTimes);

	//shaolei 2023-6-20
	xml_GetAttibuteValue(pXmlKeys->m_strRptTitleKey, oNode, m_nRptTitle);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleLevelKey, oNode, m_nTitleLevel);

	return 0;
}

long CSttItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

//shaolei 2023-2-27  注释此处，保留所有属性
// 	if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
// 	{
// 		return 0;
// 	}

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strCharacteristicIDKey, oElement, m_strCharacteristicID);
	xml_SetAttributeValue(pXmlKeys->m_strStxmlFileKey, oElement, m_strstxmlFile);
	xml_SetAttributeValue(pXmlKeys->m_strWzdMapFileKey, oElement, m_strWzdMapFile);
	xml_SetAttributeValue(pXmlKeys->m_strActLogicKey, oElement, m_strActLogic);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nTestTimes);

	//shaolei 2023-6-20
	xml_SetAttributeValue(pXmlKeys->m_strRptTitleKey, oElement, m_nRptTitle);
	xml_SetAttributeValue(pXmlKeys->m_strTitleLevelKey, oElement, m_nTitleLevel);
	return 0;
}

long CSttItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strCharacteristicID);
		BinarySerializeCalLen(oBinaryBuffer, m_strstxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strWzdMapFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strActLogic);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_nRptTitle);
		BinarySerializeCalLen(oBinaryBuffer, m_nTitleLevel);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strCharacteristicID);
		BinarySerializeRead(oBinaryBuffer, m_strstxmlFile);
		BinarySerializeRead(oBinaryBuffer, m_strWzdMapFile);
		BinarySerializeRead(oBinaryBuffer, m_strActLogic);
		BinarySerializeRead(oBinaryBuffer, m_nTestTimes);
		BinarySerializeRead(oBinaryBuffer, m_nRptTitle);
		BinarySerializeRead(oBinaryBuffer, m_nTitleLevel);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strCharacteristicID);
		BinarySerializeWrite(oBinaryBuffer, m_strstxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strWzdMapFile);
		BinarySerializeWrite(oBinaryBuffer, m_strActLogic);
		BinarySerializeWrite(oBinaryBuffer, m_nTestTimes);
		BinarySerializeWrite(oBinaryBuffer, m_nRptTitle);
		BinarySerializeWrite(oBinaryBuffer, m_nTitleLevel);
	}
	return 0;
}

long CSttItems::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
		{
			//只获取项目目录的情况下，不需要特性曲线相关以及测试功能参数
			//2022-10-14  lijunqing
			if (nClassID == STTGBXMLCLASSID_CSTTTESTMACROUIPARAS
				/*|| nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS*/)// zhouhj 20221024 更新测试报告时,需要使用特性曲线的测试项,不删除此类测试项
				//|| nClassID == STTGBXMLCLASSID_CSTTREPORTMAP
				//|| nClassID == STTCMDCLASSID_REPORTS)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

// void CSttItems::CloneCharacteristics(CExBaseList *pCharacteristics)
// {
// 	CSttTestMacroCharParas *pSttTestMacroCharParas = (CSttTestMacroCharParas*)FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS);
// 
// 	if (pSttTestMacroCharParas == NULL)
// 	{
// 		return;
// 	}
// 
// // 	POS pos = GetHeadPosition();
// // 	CExBaseObject *pObj = NULL;
// // 	CSttItems *pCurrChildItems = NULL;
// // 	CSttMacroCharItems *pSttMacroCharItems = NULL;
// // 	UINT nClassID = 0;
// // 
// // 	while (pos != NULL)
// // 	{
// // 		pObj = GetNext(pos);
// // 
// // 		if (pObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
// // 		{
// // 			pCurrChildItems = (CSttItems *)pObj;
// // 			pCurrChildItems->CloneCharacteristics(pCharacteristics);
// // 		}
// // 		else if (pObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
// // 		{
// // 			pSttMacroCharItems = (CSttMacroCharItems*)pObj;
// // 			pSttMacroCharItems->CloneCharacteristics(pCharacteristics);
// // 		}
// // 	}
// }

void CSttItems::InitAfterRead()
{
	CSttItemBase::InitAfterRead();
}

BOOL CSttItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttItems *p = (CSttItems*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strCharacteristicID != p->m_strCharacteristicID)
	{
		return FALSE;
	}

	if(m_strstxmlFile != p->m_strstxmlFile)
	{
		return FALSE;
	}

	if(m_strWzdMapFile != p->m_strWzdMapFile)
	{
		return FALSE;
	}

	if(m_strActLogic != p->m_strActLogic)
	{
		return FALSE;
	}

	if(m_nTestTimes != p->m_nTestTimes)
	{
		return FALSE;
	}

	if(m_nRptTitle != p->m_nRptTitle)
	{
		return FALSE;
	}

	if(m_nTitleLevel != p->m_nTitleLevel)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttItems *p = (CSttItems*)pDest;

	p->m_strType = m_strType;
	p->m_strCharacteristicID = m_strCharacteristicID;
	p->m_strstxmlFile = m_strstxmlFile;
	p->m_strWzdMapFile = m_strWzdMapFile;
	p->m_strActLogic = m_strActLogic;
	p->m_nTestTimes = m_nTestTimes;
	p->m_nRptTitle = m_nRptTitle;
	p->m_nTitleLevel = m_nTitleLevel;
	return TRUE;
}

CBaseObject* CSttItems::Clone()
{
	CSttItems *p = new CSttItems();
	Copy(p);
	return p;
}

CBaseObject* CSttItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttItems *p = new CSttItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttItems::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttItemsKey)
	{
		pNew = new CSttItems();
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroTestKey)
	{
		pNew = new CSttMacroTest();
	}
	else if (strClassID == pXmlKeys->m_strCSttSafetyKey)
	{
		pNew = new CSttSafety();
	}
	else if (strClassID == pXmlKeys->m_strCSttCommCmdKey)
	{
		pNew = new CSttCommCmd();
	}
	else if (strClassID == pXmlKeys->m_strCSttSysParaEditKey)
	{
		pNew = new CSttSysParaEdit();
	}
	else if (strClassID == pXmlKeys->m_strTestMacroUiParasKey)
	{
		pNew = new CSttTestMacroUiParas();
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroCharItemsKey)
	{
		pNew = new CSttMacroCharItems();
	}
	else if (strClassID == pXmlKeys->m_strTestMacroCharParasKey)
	{
		pNew = new CSttTestMacroCharParas();
	}
// 	else if (strClassID == pXmlKeys->m_strCMacroCharItemLineDefKey)
// 	{//通过ItemStateChange事件处理绘图
// 		pNew = new CSttMacroCharItemLineDef();
// 	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		pNew = new CSttItems();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		pNew = new CSttMacroTest();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		pNew = new CSttSafety();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		pNew = new CSttCommCmd();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
	{
		pNew = new CSttSysParaEdit();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTTESTMACROUIPARAS)
	{
		pNew = new CSttTestMacroUiParas();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
	{
		pNew = new CSttMacroCharItems();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS)
	{
		pNew = new CSttTestMacroCharParas();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

CSttMacroCharItemLineDef* CSttItems::GetMacroCharItemLineDef()
{
	CSttMacroCharItemLineDef *p = (CSttMacroCharItemLineDef*)FindByClassID(STTGBXMLCLASSID_MACROCHARITEMLINEDEF);
	return p;
}

BOOL CSttItems::IsTypeNone()
{
	return (m_strType == GBITEMS_NODETYPE_NONE);
}

BOOL CSttItems::IsTypeRootNode()
{
	return (m_strType == GBITEMS_NODETYPE_ROOTNODE);
}

BOOL CSttItems::IsTypeItems()
{
	return (m_strType == GBITEMS_NODETYPE_ITEMS);
}

CSttTestMacroUiParas* CSttItems::GetSttTestMacroUiParas(BOOL bCreate)
{
	CSttTestMacroUiParas* pUIParas = (CSttTestMacroUiParas *)FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);

	if (pUIParas == NULL)
	{
		if (bCreate)
		{
			pUIParas = new CSttTestMacroUiParas();
			AddNewChild(pUIParas);
		}
	}

	return pUIParas;
}

CSttTestMacroCharParas* CSttItems::GetSttTestMacroCharParas(BOOL bCreate)
{
	CSttTestMacroCharParas* pCharParas = (CSttTestMacroCharParas *)FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS);

	if (pCharParas == NULL)
	{
		if (bCreate)
		{
			pCharParas = new CSttTestMacroCharParas();
			AddNewChild(pCharParas);
		}
	}

	return pCharParas;
}

long CSttItems::GetItemTestCount()
{
	long nTestTimes = m_nTestTimes;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();
	UINT nClassID = pParent->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems *)pParent;
		nTestTimes = nTestTimes * pItems->GetItemTestCount();
	}

	return nTestTimes;
}

long CSttItems::SelectChildrenItems(const CString &strPath, CExBaseList &oListDest)
{
	CExBaseObject *p = NULL;
	CSttItemBase *pItem = NULL;
	POS pos = GetHeadPosition();

	if (strPath.GetLength() == 0)
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			p = GetNext(pos);

			if (Stt_IsItemsBaseClassID(p->GetClassID()))
			{
				oListDest.AddTail(pItem);
			}
		}
	}
	else
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pItem = (CSttItemBase*)GetNext(pos);
			ASSERT(pItem != NULL);

			if (Stt_IsItemsBaseClassID(p->GetClassID()))
			{
				pItem->SelectItems(strPath, oListDest);
			}
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CSttItemsEmpty
CSttItemsEmpty::CSttItemsEmpty()
{

}

CSttItemsEmpty::~CSttItemsEmpty()
{

}


long CSttItemsEmpty::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return 0;
}


//2022-3-28  lijunqing
CSttItems* stt_gb_new_items(CExBaseList *pParent, const CString &strName, const CString &strID)
{
	CSttItems *pNew = new CSttItems();
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strType = GBITEMS_NODETYPE_ITEMS;

	if (pParent != NULL)
	{
		pParent->AddNewChild(pNew);
	}

	return pNew;
}

//2022-7-25  lijunqing 获得特性曲线节点Items
CSttItems* stt_gb_get_ancestor_items_has_char(CExBaseObject *pItem)
{
	CExBaseObject *pParent = (CExBaseObject*)pItem->GetParent();
	CSttItems *pFind = NULL;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			break;
		}

		if ( ( (CSttItems*)pParent)->m_strCharacteristicID.GetLength() > 0)
		{
			pFind = (CSttItems*)pParent;
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}
	
	return pFind;
}

