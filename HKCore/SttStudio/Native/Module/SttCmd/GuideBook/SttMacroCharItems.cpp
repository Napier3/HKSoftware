//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroCharItems.cpp  CSttMacroCharItems


#include "stdafx.h"
#include "SttMacroCharItems.h"
//#include "../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "SttItems.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCharacteristic::CSttCharacteristic()
{
	//初始化属性

	//初始化成员变量

	m_strTestLineMode = _T("plumb")/*CHAR_TESTLINE_MODE_ID_PLUMB*/;
	m_strIndex = _T("1");
	m_nAutoClose = 0;

	m_fXMin = 0;
	m_fXMax = 10;
	m_fYMin = 0;
	m_fYMax = 10;

	m_bXMin = FALSE;
	m_bXMax = FALSE;
	m_bYMin = FALSE;
	m_bYMax = FALSE;
}

CSttCharacteristic::~CSttCharacteristic()
{

}

long CSttCharacteristic::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strAutoCloseKey, oNode, m_nAutoClose);
	xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
	xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_strXMin);
	xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_strXMax);
	xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_strYMin);
	xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_strYMax);
	xml_GetAttibuteValue(pXmlKeys->m_strTestLineModeKey, oNode, m_strTestLineMode);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_strIndex);


	return 0;
}

long CSttCharacteristic::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strAutoCloseKey, oElement, m_nAutoClose);
	xml_SetAttributeValue(pXmlKeys->m_strAxisKey, oElement, m_strAxis);
	xml_SetAttributeValue(pXmlKeys->m_strXMinKey, oElement, m_strXMin);
	xml_SetAttributeValue(pXmlKeys->m_strXMaxKey, oElement, m_strXMax);
	xml_SetAttributeValue(pXmlKeys->m_strYMinKey, oElement, m_strYMin);
	xml_SetAttributeValue(pXmlKeys->m_strYMaxKey, oElement, m_strYMax);
	xml_SetAttributeValue(pXmlKeys->m_strTestLineModeKey, oElement, m_strTestLineMode);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_strIndex);

	return 0;
}

void CSttCharacteristic::InitAfterRead()
{

}


BOOL CSttCharacteristic::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttCharacteristic *p = (CSttCharacteristic*)pObj;


	return TRUE;
}

BOOL CSttCharacteristic::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttCharacteristic *p = (CSttCharacteristic*)pDest;
	p->m_nAutoClose = m_nAutoClose;
	p->m_strAxis = m_strAxis;
	p->m_strXMin = m_strXMin;
	p->m_strXMax = m_strXMax;
	p->m_strYMin = m_strYMin;
	p->m_strYMax = m_strYMax;
	p->m_strTestLineMode = m_strTestLineMode;
	p->m_strIndex = m_strIndex;

	p->m_fXMin = m_fXMin;
	p->m_fXMax = m_fXMax;
	p->m_fYMin = m_fYMin;
	p->m_fYMax = m_fYMax;

	return TRUE;
}

CBaseObject* CSttCharacteristic::Clone()
{
	CSttCharacteristic *p = new CSttCharacteristic();
	Copy(p);
	return p;
}

BOOL CSttCharacteristic::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttCharacteristic::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return pNew;
}

CExBaseObject* CSttCharacteristic::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	return pNew;
}


long CSttCharacteristic::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nAutoClose);
		BinarySerializeCalLen(oBinaryBuffer, m_strAxis);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeCalLen(oBinaryBuffer, m_fXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nAutoClose);
		BinarySerializeRead(oBinaryBuffer, m_strAxis);
		BinarySerializeRead(oBinaryBuffer, m_strXMin);
		BinarySerializeRead(oBinaryBuffer, m_strXMax);
		BinarySerializeRead(oBinaryBuffer, m_strYMin);
		BinarySerializeRead(oBinaryBuffer, m_strYMax);
		BinarySerializeRead(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeRead(oBinaryBuffer, m_fXMin);
		BinarySerializeRead(oBinaryBuffer, m_fXMax);
		BinarySerializeRead(oBinaryBuffer, m_fYMin);
		BinarySerializeRead(oBinaryBuffer, m_fYMax);
		BinarySerializeRead(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nAutoClose);
		BinarySerializeWrite(oBinaryBuffer, m_strAxis);
		BinarySerializeWrite(oBinaryBuffer, m_strXMin);
		BinarySerializeWrite(oBinaryBuffer, m_strXMax);
		BinarySerializeWrite(oBinaryBuffer, m_strYMin);
		BinarySerializeWrite(oBinaryBuffer, m_strYMax);
		BinarySerializeWrite(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeWrite(oBinaryBuffer, m_fXMin);
		BinarySerializeWrite(oBinaryBuffer, m_fXMax);
		BinarySerializeWrite(oBinaryBuffer, m_fYMin);
		BinarySerializeWrite(oBinaryBuffer, m_fYMax);

		BinarySerializeWrite(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
CSttMacroCharItems::CSttMacroCharItems()
{
	//初始化属性

	//初始化成员变量
}

CSttMacroCharItems::~CSttMacroCharItems()
{
}

BSTR CSttMacroCharItems::GetXmlElementKey()
{
	if (CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(NULL))
	{
		return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
	}
	else
	{
		return CSttCmdDefineXmlRWKeys::CSttMacroCharItemsKey(); 
	}
}

long CSttMacroCharItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroCharItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroCharItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

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

void CSttMacroCharItems::InitAfterRead()
{
	CSttItemBase::InitAfterRead();
}

BOOL CSttMacroCharItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttMacroCharItems *p = (CSttMacroCharItems*)pObj;

	return TRUE;
}

BOOL CSttMacroCharItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttMacroCharItems *p = (CSttMacroCharItems*)pDest;

	return TRUE;
}

CBaseObject* CSttMacroCharItems::Clone()
{
	CSttMacroCharItems *p = new CSttMacroCharItems();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroCharItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroCharItems *p = new CSttMacroCharItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroCharItems::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTCHARACTERISTIC)
	{
		return TRUE;
	}

	return CSttItemBase::CanPaste(nClassID);
}

CExBaseObject* CSttMacroCharItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttMacroTestKey)
	{
		pNew = new CSttMacroTest();
	}
	else if (strClassID == pXmlKeys->m_strCSttCharacteristicKey)
	{
		pNew = new CSttCharacteristic();
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

long CSttMacroCharItems::GetItemTestCount()
{
	CSttItems *pItems = (CSttItems *)GetParent();

	return pItems->GetItemTestCount();
}

// void CSttMacroCharItems::CloneCharacteristics(CExBaseList *pCharacteristics)
// {
// 	CSttContents *pSttContents = (CSttContents*)FindByClassID(STTGBXMLCLASSID_CSTTCONTENTS);
// 
// 	if (pSttContents == NULL)
// 	{
// 		return;
// 	}
// 
// 	CCharacteristic oCCharacteristic;
// 	oCCharacteristic.SetXml(pSttContents->m_strText,CCharacteristicXmlRWKeys::g_pXmlKeys);
// 
// 	//判断是否为阻抗类,如果不为阻抗类,则查找ID,对应ID不存在时,进行克隆
// 	if ((oCCharacteristic.m_strID != _T("LN"))&&(oCCharacteristic.m_strID != _T("LL"))
// 		&&(oCCharacteristic.m_strID != _T("ALL")))
// 	{
// 		if (pCharacteristics->FindByID(oCCharacteristic.m_strID) == NULL)
// 		{
// 			pCharacteristics->AddNewChild((CExBaseObject*)oCCharacteristic.Clone());
// 		}
// 
// 		return;
// 	}
// 
// 	POS pos = pCharacteristics->GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 	CSttCharacteristic *pCurrChar = NULL,*pFindChar = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = pCharacteristics->GetNext(pos);
// 
// 		if (pObj->GetClassID() != STTGBXMLCLASSID_CSTTCHARACTERISTIC)
// 		{
// 			continue;
// 		}
// 
// 		pCurrChar = (CSttCharacteristic *)pObj;
// 
// 		if ((pCurrChar->m_strID == oCCharacteristic.m_strID)&&
// 			(pCurrChar->m_strIndex == oCCharacteristic.m_strIndex))
// 		{
// 			pFindChar = pCurrChar;
// 			break;
// 		}
// 	}
// 
// 	if (pFindChar == NULL)
// 	{
// 		pCharacteristics->AddNewChild((CExBaseObject*)oCCharacteristic.Clone());
// 	}
// 
// }

CExBaseObject* CSttMacroCharItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		pNew = new CSttMacroTest();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTCHARACTERISTIC)
	{
		pNew = new CSttCharacteristic();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}
