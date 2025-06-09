//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenInst.cpp  CItemsGenInst


#include "stdafx.h"
#include "ItemsGenInst.h"
#include "MacroItemsGen.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenInst::CItemsGenInst()
{
	//��ʼ������
	m_nNewItems = 0;

	//��ʼ����Ա����
	m_pItemsGenNameAdd = NULL;
	m_pItemsGenParasMap = NULL;
}

CItemsGenInst::~CItemsGenInst()
{
}

long CItemsGenInst::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNew_ItemsKey, oNode, m_nNewItems);
	xml_GetAttibuteValue(pXmlKeys->m_strClassKey, oNode, m_strClass);
	xml_GetAttibuteValue(pXmlKeys->m_strCCharacteristicKey, oNode, m_strCharacteristic);
	return 0;
}

long CItemsGenInst::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNew_ItemsKey, oElement, m_nNewItems);
	xml_SetAttributeValue(pXmlKeys->m_strClassKey, oElement, m_strClass);
	xml_SetAttributeValue(pXmlKeys->m_strCCharacteristicKey, oElement, m_strCharacteristic);
	return 0;
}

long CItemsGenInst::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nNewItems);
		BinarySerializeCalLen(oBinaryBuffer, m_strClass);
		BinarySerializeCalLen(oBinaryBuffer, m_strCharacteristic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nNewItems);
		BinarySerializeRead(oBinaryBuffer, m_strClass);
		BinarySerializeRead(oBinaryBuffer, m_strCharacteristic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nNewItems);
		BinarySerializeWrite(oBinaryBuffer, m_strClass);
		BinarySerializeWrite(oBinaryBuffer, m_strCharacteristic);
	}
	return 0;
}

void CItemsGenInst::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
		{
			m_pItemsGenNameAdd = (CItemsGenNameAdd*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
		{
			m_pItemsGenParasMap = (CItemsGenParasMap*)p;
		}
	}

	if (m_pItemsGenNameAdd == NULL)
	{
		m_pItemsGenNameAdd = (CItemsGenNameAdd*)AddNewChild(new CItemsGenNameAdd());
	}

	if (m_pItemsGenParasMap == NULL)
	{
		m_pItemsGenParasMap = (CItemsGenParasMap*)AddNewChild(new CItemsGenParasMap());
	}

}

BOOL CItemsGenInst::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenInst *p = (CItemsGenInst*)pObj;

	if(m_nNewItems != p->m_nNewItems)
	{
		return FALSE;
	}

	if(m_strClass != p->m_strClass)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenInst::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenInst *p = (CItemsGenInst*)pDest;

	p->m_nNewItems = m_nNewItems;
	p->m_strClass = m_strClass;
	return TRUE;
}

CBaseObject* CItemsGenInst::Clone()
{
	CItemsGenInst *p = new CItemsGenInst();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenInst::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenInst *p = new CItemsGenInst();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenInst::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenInst::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenParasMapKey)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenNameAddKey)
	{
		pNew = new CItemsGenNameAdd();
	}

	return pNew;
}

CExBaseObject* CItemsGenInst::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
	{
		pNew = new CItemsGenNameAdd();
	}

	return pNew;
}

BOOL CItemsGenInst::IsEnable(CDataGroup *pDataGroup)
{
	if (pDataGroup == NULL)
	{
		return FALSE;
	}

	//�ж�ʹ��ʱ����ͨ������������βΣ���ʼ������ӳ��Ĳ���
	InitInterfaceByUIParas(pDataGroup);
	CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)GetParent();

	if (IsClassMode_Class())
	{
		CItemsGenClass *pClass = pMacroItemsGen->GetItemsGenClass();

		if (pClass == NULL)
		{
			return FALSE;
		}

		return pClass->IsEnable();
	}
	else if(IsClassMode_Define())
	{
		CItemsGenDefine *pDefine = pMacroItemsGen->GetItemsGenDefine();

		if (pDefine == NULL)
		{
			return FALSE;
		}

		return pDefine->IsEnable();
	}
	else
	{
		return FALSE;
	}
}

void CItemsGenInst::InitInterfaceByUIParas(CDataGroup *pUIParas)
{
	if (m_pItemsGenParasMap == NULL)
	{
		return;
	}

	m_pItemsGenParasMap->InitParaValueByUIParas(pUIParas);
	CItemsGenInterface *pInterface = GetInterface();

	if (pInterface == NULL)
	{
		return;
	}

	//��ʼ������ӳ���Ӧ������ID����ʼ�����ݽӿڣ���ʱ��ģ�����е����ݽӿ�Ϊ��ǰ��ʵ������
	pInterface->InitDataValue(m_pItemsGenParasMap);
}

CItemsGenInterface* CItemsGenInst::GetInterface()
{
	CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)GetParent();

	if (IsClassMode_Class())
	{
		CItemsGenClass *pClass = pMacroItemsGen->GetItemsGenClass();

		if (pClass == NULL)
		{
			return NULL;
		}

		return pClass->GetItemsGenInterface();
	}
	else if (IsClassMode_Define())
	{
		CItemsGenDefine *pDefine = pMacroItemsGen->GetItemsGenDefine();

		if (pDefine == NULL)
		{
			return NULL;
		}

		return pDefine->GetItemsGenInterface();
	}
	else
	{
		return NULL;
	}
}

CString CItemsGenInst::GetNameAdd_Name(CDataGroup *pDataGroup)
{
	CString strText;

	if (m_pItemsGenNameAdd != NULL)
	{
		strText = m_pItemsGenNameAdd->GetNameAdd_Name(NULL, pDataGroup);
	}

	return strText;
}

CString CItemsGenInst::GetNameAdd_ID(CDataGroup *pDataGroup)
{
	CString strText;

	if (m_pItemsGenNameAdd != NULL)
	{
		strText = m_pItemsGenNameAdd->GetNameAdd_ID(NULL, pDataGroup);
	}

	return strText;
}