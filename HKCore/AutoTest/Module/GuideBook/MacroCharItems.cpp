#include "StdAfx.h"
#include "MacroCharItems.h"
#include "Safety.h"
#include "MacroTest.h"
#include "SysParaEdit.h"
#include "CommCmd.h"
#include "GuideBook.h"
#include "Items.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "../Characteristic/CharacterDrawView.h"

#include "../XLanguageResourceAts.h"

//////////////////////////////////////////////////////////////////////////
//CMacroCharItemLineDef
CMacroCharItemLineDef::CMacroCharItemLineDef()
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
	m_nFlagAct = 0;
}

CMacroCharItemLineDef::~CMacroCharItemLineDef()
{

}


long CMacroCharItemLineDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);

//	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strAxisModeKey,oNode,m_strAxisMode);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXbKey,oNode,m_strParaIdXb);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYbKey,oNode,m_strParaIdYb);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXeKey,oNode,m_strParaIdXe);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYeKey,oNode,m_strParaIdYe);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXsetKey,oNode,m_strParaIdXset);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYsetKey,oNode,m_strParaIdYset);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXactKey,oNode,m_strParaIdXact);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYactKey,oNode,m_strParaIdYact);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdFlagActKey,oNode,m_strParaIdFlagAct);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXbKey,oNode,m_strParaIdSearchXb);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYbKey,oNode,m_strParaIdSearchYb);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchActbKey,oNode,m_strParaIdSearchActb);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXeKey,oNode,m_strParaIdSearchXe);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYeKey,oNode,m_strParaIdSearchYe);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchActeKey,oNode,m_strParaIdSearchActe);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXcKey,oNode,m_strParaIdSearchXc);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYcKey,oNode,m_strParaIdSearchYc);

	return 0;
}

long CMacroCharItemLineDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

// 	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strAxisModeKey,oElement,m_strAxisMode);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXbKey,oElement,m_strParaIdXb);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYbKey,oElement,m_strParaIdYb);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXeKey,oElement,m_strParaIdXe);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYeKey,oElement,m_strParaIdYe);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXsetKey,oElement,m_strParaIdXset);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYsetKey,oElement,m_strParaIdYset);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdXactKey,oElement,m_strParaIdXact);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdYactKey,oElement,m_strParaIdYact);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdFlagActKey,oElement,m_strParaIdFlagAct);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXbKey,oElement,m_strParaIdSearchXb);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYbKey,oElement,m_strParaIdSearchYb);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchActbKey,oElement,m_strParaIdSearchActb);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXeKey,oElement,m_strParaIdSearchXe);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYeKey,oElement,m_strParaIdSearchYe);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchActeKey,oElement,m_strParaIdSearchActe);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchXcKey,oElement,m_strParaIdSearchXc);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strParaIdSearchYcKey,oElement,m_strParaIdSearchYc);

	return 0;
}

BOOL CMacroCharItemLineDef::IsEqualOwn(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CMacroCharItemLineDef::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CMacroCharItemLineDef *p = (CMacroCharItemLineDef*)pDest;

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

CBaseObject* CMacroCharItemLineDef::Clone()
{
	CMacroCharItemLineDef* pNew = new CMacroCharItemLineDef();
	Copy(pNew);

	return pNew;
}


long CMacroCharItemLineDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CMacroCharItemLineDef::IsAxisMode_x_y()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_XY);
}

BOOL CMacroCharItemLineDef::IsAxisMode_r_angle()
{
	return (m_strAxisMode == MACRO_CHAR_TEST_AXISMODE_RANGLE);
}

BOOL CMacroCharItemLineDef::IsLineDef_point()
{
	return (m_strType == MACRO_CHAR_TEST_LINEDEF_POINT);
}

BOOL CMacroCharItemLineDef::IsLineDef_line()
{
	return (m_strType == MACRO_CHAR_TEST_LINEDEF_LINE);
}

void CMacroCharItemLineDef::ChangeValueXY(double &dX, double &dY)
{
	if (IsAxisMode_r_angle())
	{
		CComplexNumber oComplex(dX, dY, COMPLEX_MODE_DEGREE);
		oComplex.GetValue(dX, dY);
	}
}

void CMacroCharItemLineDef::InitSearchValues(CValues *pSearchReport)
{
	m_nSearchActb = TESTLINE_ACT_STATE_NONE;
	m_nSearchActe = TESTLINE_ACT_STATE_NONE;

	pSearchReport->GetValue(_T("flag-act"), m_nFlagAct);   //动作标记，由测试服务上报
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

////////////////////////////////////////////////////////////////////////////
//CMacroCharItems
CShortDatas* CMacroCharItems::g_pMacroCharItemsDatas = NULL;
long  CMacroCharItems::g_nMacroCharItemsDatas = 0;

CString  CMacroCharItems::g_strKeyParaIdXb   = _T("Vxb");
CString  CMacroCharItems::g_strKeyParaIdYb   = _T("Vyb");
CString  CMacroCharItems::g_strKeyParaIdXe   = _T("Vxe");
CString  CMacroCharItems::g_strKeyParaIdYe   = _T("Vye");
CString  CMacroCharItems::g_strKeyParaIdXset = _T("Vxset");
CString  CMacroCharItems::g_strKeyParaIdYset = _T("Vyset");
CString  CMacroCharItems::g_strKeyParaIdXact = _T("Vxact");
CString  CMacroCharItems::g_strKeyParaIdYact = _T("Vyact");
CString  CMacroCharItems::g_strKeyCharGraph  = _T("CharGraph");

void CMacroCharItems::CreateMacroCharItemsDatas()
{
	g_nMacroCharItemsDatas++;

	if (g_nMacroCharItemsDatas == 1)
	{
		g_pMacroCharItemsDatas = new CShortDatas();
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdXb, g_strKeyParaIdXb, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdYb, g_strKeyParaIdYb, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdXe, g_strKeyParaIdXe, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdYe, g_strKeyParaIdYe, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdXset, g_strKeyParaIdXset, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdYset, g_strKeyParaIdYset, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdXact, g_strKeyParaIdXact, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyParaIdYact, g_strKeyParaIdYact, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
		g_pMacroCharItemsDatas->AddNew2(g_strKeyCharGraph, g_strKeyCharGraph, _T(""), _T(""), _T(""), 0, _T(""), _T(""));
	}
}

void CMacroCharItems::ReleaseMacroCharItemsDatas()
{
	g_nMacroCharItemsDatas--;

	if (g_nMacroCharItemsDatas == 0)
	{
		delete g_pMacroCharItemsDatas;
		g_pMacroCharItemsDatas = NULL;
	}
}

CShortDatas* CMacroCharItems::GetMacroCharItemsDatas()
{
	ASSERT (g_pMacroCharItemsDatas != NULL);
	return g_pMacroCharItemsDatas;
}

CMacroCharItems::CMacroCharItems(void)
{
	m_pCharTemplate = NULL;
	m_pItemLineDef = NULL;
	m_pPara = NULL;
}

CMacroCharItems::~CMacroCharItems(void)
{
}

void CMacroCharItems::InitMacroID()
{
	ASSERT (m_pPara != NULL);
	m_pPara->InitMacroID();
}

CString CMacroCharItems::GetTestMacroID()
{
	if (m_pPara == NULL)
	{
		return _T("");
	}

	return m_pPara->GetMacroID();
}

long CMacroCharItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);
	
	//xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCharacteristicIDKey,oNode,m_strCharacteristicID);


	return 0;
}

long CMacroCharItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

	//xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCharacteristicIDKey,oElement,m_strCharacteristicID);


	return 0;
}

long CMacroCharItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);
	
	if (oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strCharacteristicID);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strCharacteristicID);
	}
	else
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strCharacteristicID);
	}

	return 0;
}

CExBaseObject* CMacroCharItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCMacroCharItemLineDefKey)
	{
		m_pItemLineDef = new CMacroCharItemLineDef();
		return m_pItemLineDef;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strParaKey)
	{
		m_pPara = new CMacroTestPara();
		return m_pPara;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->CCharacteristicTmplateKey())
	{
		return new CCharacteristicTmplate();
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->CCharacteristicKey())
	{
		m_pCharTemplate = new CCharacteristic();
		return m_pCharTemplate;
	}

	CExBaseObject *p = GbItems_CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	if (p != NULL)
	{
		return p;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CMacroCharItems::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_MACROCHARITEMLINEDEF)
	{
		CMacroCharItemLineDef* pLineDef = new CMacroCharItemLineDef();
		return pLineDef;
	}
	else if(nClassID == GBCLASSID_MACROPARA)
	{
		m_pPara = new CMacroTestPara();
		return m_pPara;
	}
	else if(nClassID == CHARCLASSID_CCHARACTERISTICTMPLATE)
	{
		return new CCharacteristicTmplate();
	}
	else if(nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		m_pCharTemplate = new CCharacteristic();
		return m_pCharTemplate;
	}

	CExBaseObject *p = GbItems_CreateNewChild(nClassID);

	if (p != NULL)
	{
		return p;
	}
	
	return CGbItemBase::CreateNewChild(nClassID);
}

CBaseObject* CMacroCharItems::Clone()
{
	CMacroCharItems* pMacroCharItems = new CMacroCharItems();
	Copy(pMacroCharItems);

	return pMacroCharItems;
}

BOOL CMacroCharItems::CanPaste(CExBaseObject *pObj)
{
	return FALSE;
}


BOOL CMacroCharItems::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}

	CGbItemBase::CopyOwn(pDest);
	CMacroCharItems *pItem = (CMacroCharItems*)pDest;

	//pItem->m_strCharacteristicID = m_strCharacteristicID;

	return TRUE;
}

void CMacroCharItems::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	//lijq 2020-3-13  转换：将CChaTmplate_to_Characteristic
	char_CChaTmplate_to_Characteristic(this);

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_MACROPARA:
			m_pPara = (CMacroTestPara*)p;
			break;

		case GBCLASSID_MACROCHARITEMLINEDEF:
			m_pItemLineDef = (CMacroCharItemLineDef *)p;
			break;

		case CHARCLASSID_CCHARACTERISTIC:
			m_pCharTemplate = (CCharacteristic *)p;
			break;

		default:
			break;
		}
	}

	if (m_pPara == NULL)
	{
		m_pPara = new CMacroTestPara();
		m_pPara->InitAfterRead();
		AddNewChild(m_pPara);
	}

	if (m_pItemLineDef == NULL)
	{
		m_pItemLineDef = new CMacroCharItemLineDef();
		m_pItemLineDef->InitAfterRead();
		AddNewChild(m_pItemLineDef);
	}
}

CCharacteristic* CMacroCharItems::SetCharacteristicTmplate(CCharacteristic *pCharTemp)
{
	if (m_pCharTemplate != NULL)
	{
		if (m_pCharTemplate->m_strID == pCharTemp->m_strID)
		{
			return m_pCharTemplate;
		}

		Delete(m_pCharTemplate);
		m_pCharTemplate = NULL;
	}

	m_pCharTemplate = (CCharacteristic *)pCharTemp->Clone();
	AddNewChild(m_pCharTemplate);

	return m_pCharTemplate;
}

CString CMacroCharItems::GetMacroTestDataID(const CString &strID)
{
	CString strParaID;

	if (strID == g_strKeyParaIdXb)//   = _T("Vxb");
	{
		strParaID = m_pItemLineDef->m_strParaIdXb;
	}
	else if (strID == g_strKeyParaIdYb)//   = _T("Vyb");
	{
		strParaID = m_pItemLineDef->m_strParaIdYb;
	}
	else if (strID == g_strKeyParaIdXe)//   = _T("Vxe");
	{
		strParaID = m_pItemLineDef->m_strParaIdXe;
	}
	else if (strID == g_strKeyParaIdYe)//   = _T("Vye");
	{
		strParaID = m_pItemLineDef->m_strParaIdYe;
	}
	else if (strID == g_strKeyParaIdXset)// = _T("Vxset");
	{
		strParaID = m_pItemLineDef->m_strParaIdXset;
	}
	else if (strID == g_strKeyParaIdYset)// = _T("Vyset");
	{
		strParaID = m_pItemLineDef->m_strParaIdYset;
	}
	else if (strID == g_strKeyParaIdXact)// = _T("Vxact");
	{
		strParaID = m_pItemLineDef->m_strParaIdXact;
	}
	else if (strID == g_strKeyParaIdYact)// = _T("Vyact");
	{
		strParaID = m_pItemLineDef->m_strParaIdYact;
	}

	if (strParaID.GetLength() == 0)
	{
		strParaID = strID;
	}

	return strParaID;
}

BOOL CMacroCharItems::WriteCharGraphFile()
{
	if (!IsAllMacroTestFinished())
	{
		return FALSE;
	}

#ifndef _PSX_QT_LINUX_
    CString strFile = char_test_GetCharGraphFile();

	char_view_WriteBitmapFile(m_pCharTemplate, 800, 800, strFile);
#endif

	return TRUE;
}

BOOL CMacroCharItems::IsAllMacroTestFinished()
{
	CExBaseList listMacroTest;
	GetAllMacroTestItems(&listMacroTest);

	POS pos = listMacroTest.GetHeadPosition();
	CMacroTest *pGbItem = NULL;
	BOOL bFinish = TRUE;

	while (pos != NULL)
	{
		pGbItem = (CMacroTest *)listMacroTest.GetNext(pos);

		if (!pGbItem->IsTestFinish())
		{
			bFinish = FALSE;
			break;
		}
	}

	listMacroTest.RemoveAll();

	return bFinish;
}

CMacroTestPara* CMacroCharItems::GetMacroTestPara()
{
	ASSERT (m_pPara != NULL);
	return m_pPara;
}

CMacroCharItemLineDef* CMacroCharItems::GetCMacroCharItemLineDef()
{
	ASSERT (m_pItemLineDef != NULL);
	return m_pItemLineDef;
}

CCharacteristic* CMacroCharItems::GetCharacteristicTmplate()
{
	ASSERT (m_pCharTemplate != NULL);
	return m_pCharTemplate;
}

void CMacroCharItems::InitMacroTestItems()
{
	if (m_pCharTemplate == NULL)
	{
		return;
	}

	m_pCharTemplate->InitVariableValues();
	m_pCharTemplate->CalCharElement(NULL);

	CCharacterArea *pCharArea = m_pCharTemplate->GetCharacterArea();
	CXDrawList *pDrawList = m_pCharTemplate->InitCharDrawElement_ForCalOnly();
	m_pCharTemplate->CalTestLines(NULL);
	pCharArea->InitCharDrawElementTestLines(pDrawList);

	CExBaseList listTestLine, listMacroTest;
	GetAllMacroTestItems(&listMacroTest);
	m_pCharTemplate->GetAllMacroTestLines(&listTestLine);

	ASSERT(listMacroTest.GetCount() == 0);

	POS pos = listTestLine.GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;

	CTestMacro* oTestMacro = Gb_GetMacroPtr(m_pPara);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)listTestLine.GetNext(pos);
		CreateMacroTestItem(pTestLine, oTestMacro);
	}

	listTestLine.RemoveAll();
	listMacroTest.RemoveAll();
}

void CMacroCharItems::UpdateMacroTestItems()
{
	m_pCharTemplate->InitVariableValues();
	m_pCharTemplate->CalCharElement(NULL);
	CXDrawList *pDrawList = m_pCharTemplate->InitCharDrawElement_ForCalOnly();
	CCharacterArea *pCharArea = m_pCharTemplate->GetCharacterArea();

	m_pCharTemplate->CalTestLines(NULL);
	pCharArea->InitCharDrawElementTestLines(pDrawList);

	CExBaseList listTestLine, listMacroTest;
	GetAllMacroTestItems(&listMacroTest);
	m_pCharTemplate->GetAllMacroTestLines(&listTestLine);

	ASSERT (listTestLine.GetCount() == listMacroTest.GetCount());

	POS posLine = listTestLine.GetHeadPosition();
	POS posTest = listMacroTest.GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	CMacroTest *pMacroTest = NULL;
	CTestMacro* pTestMacro = Gb_GetMacroPtr(m_pPara);

	while (posLine != NULL && posTest != NULL)
	{
		pTestLine = (CCharElementTestLine *)listTestLine.GetNext(posLine);
		pMacroTest = (CMacroTest *)listMacroTest.GetNext(posTest);
		UpateMacroTestItem(pTestLine, pMacroTest, pTestMacro);
	}

	listTestLine.RemoveAll();
	listMacroTest.RemoveAll();
}

void CMacroCharItems::InitTestLinesRef()
{
	m_pCharTemplate->CalCharElement(NULL);

	CExBaseList listTestLine, listMacroTest;
	GetAllMacroTestItems(&listMacroTest);
	m_pCharTemplate->GetAllMacroTestLines(&listTestLine);

	ASSERT (listTestLine.GetCount() == listMacroTest.GetCount());

	POS posLine = listTestLine.GetHeadPosition();
	POS posTest = listMacroTest.GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	CMacroTest *pMacroTest = NULL;

	while (posLine != NULL && posTest != NULL)
	{
		pTestLine = (CCharElementTestLine *)listTestLine.GetNext(posLine);
		pMacroTest = (CMacroTest *)listMacroTest.GetNext(posTest);
		pTestLine->m_pMacroTestItemRef = pMacroTest;
	}

	listTestLine.RemoveAll();
	listMacroTest.RemoveAll();
}

CMacroCharItemLineDef* CMacroCharItems::UpdateMacroTest(CMacroTest *pMacroTest, CValues *pSearchReport)
{
// 	CCharElementTestLine *pTestLine = FindTestLine(pMacroTest);
// 	ASSERT(pTestLine != NULL);
// 
// 	if (pTestLine == NULL)
// 	{
// 		return NULL;
// 	}

	m_pItemLineDef->m_fXact = 0.0;
	m_pItemLineDef->m_fYact = 0.0;
	m_pItemLineDef->m_nFlagAct = 0;
	m_pItemLineDef->InitSearchValues(pSearchReport);
	UpdateTestLineDef(pMacroTest);

	return m_pItemLineDef;
}

CCharElementTestLine* CMacroCharItems::UpdateMacroTest(CMacroTest *pMacroTest, CReport *pReport)
{
	CCharElementTestLine *pTestLine = FindTestLine(pMacroTest);
	ASSERT(pTestLine != NULL);

	if (pTestLine == NULL)
	{
		return NULL;
	}

	InitByMacroTestPara_r_angle(pReport->m_pValues, m_pItemLineDef->m_strParaIdXact, pTestLine->m_fXact
		, m_pItemLineDef->m_strParaIdYact, pTestLine->m_fYact
		, m_pItemLineDef->m_strParaIdFlagAct, pTestLine->m_nActState);
	
	m_pItemLineDef->m_fXact = pTestLine->m_fXact;
	m_pItemLineDef->m_fYact = pTestLine->m_fYact;
	m_pItemLineDef->m_nFlagAct = pTestLine->m_nActState;
	UpdateTestLineDef(pMacroTest);

	return pTestLine;
}

long CMacroCharItems::GetMacroTestIndex(CMacroTest *pMacroTest)
{
	CExBaseList listMacroTest;
	GetAllMacroTestItems(&listMacroTest);
	long nIndex = listMacroTest.FindIndex(pMacroTest);

	if (nIndex < 0)
	{
		nIndex=0;
	}

	listMacroTest.RemoveAll();
	return nIndex;
}

void CMacroCharItems::InitMacroTestIDByIndex()
{
	CExBaseList listMacroTest;
	GetAllMacroTestItems(&listMacroTest);
	long nIndex = 1;

	POS pos = listMacroTest.GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)listMacroTest.GetNext(pos);
		pMacroTest->m_strID.Format(_T("test%d"), nIndex);
		nIndex++;
	}

	listMacroTest.RemoveAll();
}

void CMacroCharItems::GetAllMacroTestItemsEx(CExBaseList *pList)
{
	GetAllMacroTestItems(pList);
}

void CMacroCharItems::GetAllMacroTestItems(CExBaseList *pList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_MACROTEST)
		{
			pList->AddTail(p);
		}
	}
}


void CMacroCharItems::CreateMacroTestItem(CCharElementTestLine *pTestLine, CTestMacro* pTestMacro)
{
	CMacroTest *pMacroTest = CMacroTest::_New(this);
	//反时限测试，采用的功能名称叫“动作时间”。此处暂时不显示功能名称
    //pMacroTest->m_strName.Format(_T("%s(%.4f,%.4f)"), pTestMacro->m_strName.GetString(), pTestLine->m_fXset, pTestLine->m_fYset);
	pMacroTest->m_strName.Format(_T("(%.4f,%.4f)"), pTestLine->m_fXset, pTestLine->m_fYset);
	pMacroTest->m_strID = pTestMacro->m_strID;
	AddNewChild(pMacroTest, TRUE);

	CMacroTestParaDatas *pMacroTestParaDatas = m_pPara->GetFaultParaDatas();
	CMacroTestParaDatas *pMacroTestParaDatas2 = pMacroTest->GetFaultParaDatas();
	pMacroTestParaDatas->Copy(pMacroTestParaDatas2);

	pMacroTest->SetTestMacroID(pTestMacro->m_strID);
	UpateMacroTestItem(pTestLine, pMacroTest, pTestMacro);
// 	CShortDatas *pFaultParas = pTestMacro->GetFaultParas();
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXb, pTestLine->m_fXb);
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYb, pTestLine->m_fYb);
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXe, pTestLine->m_fXe);
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYe, pTestLine->m_fYe);
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXset, pTestLine->m_fXset);
// 	AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYset, pTestLine->m_fYset);
 
}

void CMacroCharItems::AddMacroTestPara(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, double dValue)
{
	if (strParaID.GetLength() <= 1)
	{
		return;
	}

	CShortData *pData = NULL;

	pData = (CShortData*)pFaultParas->FindByID(strParaID);

	if (pData != NULL)
	{
		pData->m_strValue.Format(_T("%f"), dValue);
		pMacroTest->UpdateMacroTestParaData(pData, FALSE, FALSE);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CreatCharPara.GetString()/*_T("创建特性曲线搜索线：参数ID“%s”不存在")*/
                                   , strParaID.GetString());
	}
}

void CMacroCharItems::AddMacroTestPara_r_angle(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, double dValue, const CString &strParaID2, double dValue2)
{
	if (strParaID.GetLength() <= 1 || strParaID2.GetLength() <= 1)
	{
		return;
	}

	CShortData *pData = NULL;
	CShortData *pData2 = NULL;

	pData = (CShortData*)pFaultParas->FindByID(strParaID);
	pData2 = (CShortData*)pFaultParas->FindByID(strParaID2);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CreatCharPara.GetString()/*_T("创建特性曲线搜索线：参数ID“%s”不存在")*/
                                   , strParaID.GetString());
	}

	if (pData2 == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CreatCharPara.GetString()/*_T("创建特性曲线搜索线：参数ID“%s”不存在")*/
                                   , strParaID2.GetString());
	}

	if (pData2 == NULL || pData == NULL)
	{
		return;
	}

	CComplexNumber oComplexNumber;//(dValue, dValue2, COMPLEX_MODE_DEGREE);
	oComplexNumber.SetValue(dValue, dValue2);
	oComplexNumber.GetValueAngle(dValue, dValue2);

	pData->m_strValue.Format(_T("%f"), dValue);
	pData2->m_strValue.Format(_T("%f"), dValue2);

	pMacroTest->UpdateMacroTestParaData(pData, FALSE, FALSE);
	pMacroTest->UpdateMacroTestParaData(pData2, FALSE, FALSE);
}

void CMacroCharItems::InitByMacroTestPara_r_angle(CValues *pValues, const CString &strParaIDX, double &dValueX, const CString &strParaIDY, double &dValueY, const CString &strParaIDFlag, long &nValueFlag)
{
	BOOL bX = pValues->GetValue(strParaIDX, dValueX);
	BOOL bY = pValues->GetValue(strParaIDY, dValueY);
	BOOL bF = pValues->GetValue(strParaIDFlag, nValueFlag);

	CValue *pValue = (CValue*)pValues->FindByID(strParaIDFlag);

	if (pValue != NULL)
	{
		if (pValue->m_strValue == g_sLangTxt_Act/*_T("动作")*/)
		{
			nValueFlag = 1;
		}
		else if (pValue->m_strValue == g_sLangTxt_Unact/*_T("未动作")*/)
		{
			nValueFlag = 0;
		}
	}

	if (!bX)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
                                   , strParaIDX.GetString());
	}

	if (!bY)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
                                   , strParaIDY.GetString());
	}

	if (!bF)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
                                   , strParaIDFlag.GetString());
	}

	if (! (bX && bY && bF) )
	{
		return;
	}

	if (nValueFlag == 1)
	{
		if (m_pItemLineDef->IsAxisMode_r_angle())
		{
			CComplexNumber oComplex(dValueX, dValueY, COMPLEX_MODE_DEGREE);
			oComplex.GetValue(dValueX, dValueY);
		}
	}
}

void CMacroCharItems::AddMacroTestPara(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, const CString &strValue)
{
	if (strParaID.GetLength() <= 1)
	{
		return;
	}

	CShortData *pData = NULL;

	pData = (CShortData*)pFaultParas->FindByID(strParaID);

	if (pData != NULL)
	{
		pData->m_strValue = strValue;
		pMacroTest->UpdateMacroTestParaData(pData, FALSE, TRUE);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CreatCharPara.GetString()/*_T("创建特性曲线搜索线：参数ID“%s”不存在")*/
                                   , strParaID.GetString());
	}
}

void CMacroCharItems::UpateMacroTestItem(CCharElementTestLine *pTestLine, CMacroTest *pMacroTest, CTestMacro* pTestMacro)
{
	CShortDatas *pFaultParas = pTestMacro->GetFaultParas();
	pTestLine->m_pMacroTestItemRef = pMacroTest;

	if (m_pItemLineDef->IsAxisMode_r_angle())
	{
		AddMacroTestPara_r_angle(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXb, pTestLine->m_fXb
			, m_pItemLineDef->m_strParaIdYb, pTestLine->m_fYb);
		AddMacroTestPara_r_angle(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXe, pTestLine->m_fXe
			, m_pItemLineDef->m_strParaIdYe, pTestLine->m_fYe);
		AddMacroTestPara_r_angle(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXset, pTestLine->m_fXset
			, m_pItemLineDef->m_strParaIdYset, pTestLine->m_fYset);

		double dValue = pTestLine->m_fXset, dValue2 = pTestLine->m_fYset;
		CComplexNumber oComplexNumber;//(dValue, dValue2, COMPLEX_MODE_DEGREE);
		oComplexNumber.SetValue(dValue, dValue2);
		oComplexNumber.GetValueAngle(dValue, dValue2);

		//反时限测试，采用的功能名称叫“动作时间”。此处暂时不显示功能名称
		//pMacroTest->m_strName.Format(_T("%s(%.4f,%.4f)"), pTestMacro->m_strName.GetString(), dValue, dValue2);
		pMacroTest->m_strName.Format(_T("(%.4f,%.4f)"), dValue, dValue2);
	}
	else
	{
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXb, pTestLine->m_fXb);
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYb, pTestLine->m_fYb);
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXe, pTestLine->m_fXe);
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYe, pTestLine->m_fYe);
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdXset, pTestLine->m_fXset);
		AddMacroTestPara(pMacroTest, pFaultParas, m_pItemLineDef->m_strParaIdYset, pTestLine->m_fYset);

		//反时限测试，采用的功能名称叫“动作时间”。此处暂时不显示功能名称
		//pMacroTest->m_strName.Format(_T("%s(%.4f,%.4f)"), pTestMacro->m_strName.GetString(), pTestLine->m_fXset, pTestLine->m_fYset);
		pMacroTest->m_strName.Format(_T("(%.4f,%.4f)"), pTestLine->m_fXset, pTestLine->m_fYset);
	}
}

CCharElementTestLine* CMacroCharItems::FindTestLine(CMacroTest *pMacroTest)
{
	CCharElementTestLine *p = NULL, *pFind = NULL;
	CExBaseList listTestLine, listMacroTest;
	m_pCharTemplate->GetAllMacroTestLines(&listTestLine);
	GetAllMacroTestItems(&listMacroTest);

	POS pos = listTestLine.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCharElementTestLine *)listTestLine.GetNext(pos);

		if (p->m_pMacroTestItemRef == pMacroTest)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		long nIndex = listMacroTest.FindIndex(pMacroTest);
		pFind = (CCharElementTestLine *)listTestLine.GetAtIndex(nIndex);

		if (pFind != NULL)
		{
			pFind->m_pMacroTestItemRef = pMacroTest;
		}
	}

	listMacroTest.RemoveAll();
	listTestLine.RemoveAll();

	return pFind;
}

void CMacroCharItems::UpdateTestLineDef(CMacroTest *pMacroTest)
{
	CMacroTestParaDatas *pMacroTestParaDatas = pMacroTest->GetFaultParaDatas();
	//生成项目的时候，将对应ID的参数，赋值给了电气量项目的参数
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdXb, m_pItemLineDef->m_fXb);
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdYb, m_pItemLineDef->m_fYb);
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdXe, m_pItemLineDef->m_fXe);
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdYe, m_pItemLineDef->m_fYe);
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdXset, m_pItemLineDef->m_fXset);
	pMacroTestParaDatas->GetParaValue(m_pItemLineDef->m_strParaIdYset, m_pItemLineDef->m_fYset);

	if (m_pItemLineDef->IsLineDef_point())
	{
		m_pItemLineDef->m_nSearchActb = m_pItemLineDef->m_nFlagAct;
		m_pItemLineDef->m_nSearchActe = m_pItemLineDef->m_nFlagAct;

		m_pItemLineDef->m_fSearchXb = m_pItemLineDef->m_fXb;
		m_pItemLineDef->m_fSearchYb = m_pItemLineDef->m_fYb;
		m_pItemLineDef->m_fSearchXe = m_pItemLineDef->m_fXb;
		m_pItemLineDef->m_fSearchYe = m_pItemLineDef->m_fYb;
		m_pItemLineDef->m_fSearchXc = m_pItemLineDef->m_fXb;
		m_pItemLineDef->m_fSearchYc = m_pItemLineDef->m_fYb;
	}
}

long CMacroCharItems::GetItemTestCount()
{
	CItems *pItems = (CItems *)GetParent();

	return pItems->GetItemTestCount();
}

void CMacroCharItems::ClearReport(BOOL bBack)
{
	CGbItemBase::ClearReport(bBack);

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if(p->GetClassID() == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest*)p;
			pMacroTest->ClearReport(bBack);
		}
	}	
}

CString char_test_GetCharGraphFile()
{
	CString strFile;
	strFile = _P_GetBinPath();
    strFile.AppendFormat(_T("%s.bmp"), CMacroCharItems::g_strKeyCharGraph.GetString());

	return strFile;
}
