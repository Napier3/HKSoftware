#include "stdafx.h"
#include "ItemsGenCharItemLine.h"

CItemsGenCharItemLine::CItemsGenCharItemLine(void)
{
}

CItemsGenCharItemLine::~CItemsGenCharItemLine(void)
{
}

long CItemsGenCharItemLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys);

	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strAxisModeKey,oNode,m_strAxisMode);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXbKey,oNode,m_strParaIdXb);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYbKey,oNode,m_strParaIdYb);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXeKey,oNode,m_strParaIdXe);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYeKey,oNode,m_strParaIdYe);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXsetKey,oNode,m_strParaIdXset);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYsetKey,oNode,m_strParaIdYset);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXactKey,oNode,m_strParaIdXact);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYactKey,oNode,m_strParaIdYact);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdFlagActKey,oNode,m_strParaIdFlagAct);

	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXbKey,oNode,m_strParaIdSearchXb);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYbKey,oNode,m_strParaIdSearchYb);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActbKey,oNode,m_strParaIdSearchActb);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXeKey,oNode,m_strParaIdSearchXe);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYeKey,oNode,m_strParaIdSearchYe);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActeKey,oNode,m_strParaIdSearchActe);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXcKey,oNode,m_strParaIdSearchXc);
	xml_GetAttibuteValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYcKey,oNode,m_strParaIdSearchYc);

	return 0;
}

long CItemsGenCharItemLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys);

	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strTypeKey,oElement,m_strType);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strAxisModeKey,oElement,m_strAxisMode);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXbKey,oElement,m_strParaIdXb);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYbKey,oElement,m_strParaIdYb);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXeKey,oElement,m_strParaIdXe);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYeKey,oElement,m_strParaIdYe);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXsetKey,oElement,m_strParaIdXset);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYsetKey,oElement,m_strParaIdYset);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdXactKey,oElement,m_strParaIdXact);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdYactKey,oElement,m_strParaIdYact);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdFlagActKey,oElement,m_strParaIdFlagAct);

	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXbKey,oElement,m_strParaIdSearchXb);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYbKey,oElement,m_strParaIdSearchYb);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActbKey,oElement,m_strParaIdSearchActb);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXeKey,oElement,m_strParaIdSearchXe);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYeKey,oElement,m_strParaIdSearchYe);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchActeKey,oElement,m_strParaIdSearchActe);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchXcKey,oElement,m_strParaIdSearchXc);
	xml_SetAttributeValue(CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strParaIdSearchYcKey,oElement,m_strParaIdSearchYc);

	return 0;
}

BOOL CItemsGenCharItemLine::IsEqualOwn(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CItemsGenCharItemLine::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CItemsGenCharItemLine *p = (CItemsGenCharItemLine*)pDest;

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

CBaseObject* CItemsGenCharItemLine::Clone()
{
	CItemsGenCharItemLine* pNew = new CItemsGenCharItemLine();
	Copy(pNew);

	return pNew;
}


long CItemsGenCharItemLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CItemsGenCharItemLine::IsAxisMode_x_y()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_XY);
}

BOOL CItemsGenCharItemLine::IsAxisMode_r_angle()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_RANGLE);
}