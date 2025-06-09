//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenNode.cpp  CGenNodeBase


#include "stdafx.h"
#include "GenNodeBase.h"
#include "ItemsGenBase.h"
#include "ItemsGenDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
测试模板生成定义的生成节点类，节点类可以嵌套，
嵌套的结构与模板的结构保持一致。一个Node类定义一个测试项目
*/
CGenNodeBase::CGenNodeBase()
{
	//初始化属性

	//初始化成员变量
	m_pItemsGenEnable = NULL;
	m_pItemsGenParaMap = NULL;
	m_pItemsGenNameAdd = NULL;

	m_pItemsGenParaMap_BK = NULL;

	m_pItemsGenCommCmd = NULL;
	m_pItemsGenSafety = NULL;
	m_pItemsGenSysParaEdit = NULL;
}

CGenNodeBase::~CGenNodeBase()
{
	if (m_pItemsGenParaMap_BK != NULL)
	{
		delete m_pItemsGenParaMap_BK;
		m_pItemsGenParaMap_BK = NULL;
	}
}

long CGenNodeBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CGenNodeBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CGenNodeBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CGenNodeBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
		{
			m_pItemsGenEnable = (CItemsGenEnable*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
		{
			m_pItemsGenParaMap = (CItemsGenParasMap*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
		{
			m_pItemsGenNameAdd = (CItemsGenNameAdd*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENCOMMCMD)
		{
			m_pItemsGenCommCmd = (CItemsGenCommCmd*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSYSPARAEDIT)
		{
			m_pItemsGenSysParaEdit = (CItemsGenSysParaEdit*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSAFETY)
		{
			m_pItemsGenSafety = (CItemsGenSafety*)p;
		}
	}

	if (m_pItemsGenParaMap_BK == NULL)
	{
		m_pItemsGenParaMap_BK = new CItemsGenParasMap;
	}

	if (m_pItemsGenParaMap != NULL)
	{
		m_pItemsGenParaMap_BK->DeleteAll();
		m_pItemsGenParaMap_BK->AppendClone(m_pItemsGenParaMap);
	}
}

BOOL CGenNodeBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGenNodeBase *p = (CGenNodeBase*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGenNodeBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGenNodeBase *p = (CGenNodeBase*)pDest;

	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CGenNodeBase::Clone()
{
	CGenNodeBase *p = new CGenNodeBase();
	Copy(p);
	return p;
}

CBaseObject* CGenNodeBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGenNodeBase *p = new CGenNodeBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CGenNodeBase::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENCOMMCMD)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSYSPARAEDIT)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSAFETY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGenNodeBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenEnableKey)
	{
		pNew = new CItemsGenEnable();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenParasMapKey)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenNameAddKey)
	{
		pNew = new CItemsGenNameAdd();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenCommCmdKey)
	{
		pNew = new CItemsGenCommCmd();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenSafetyKey)
	{
		pNew = new CItemsGenSafety();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenSysParaEditKey)
	{
		pNew = new CItemsGenSysParaEdit();
	}

	return pNew;
}

CExBaseObject* CGenNodeBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENENABLE)
	{
		pNew = new CItemsGenEnable();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD)
	{
		pNew = new CItemsGenNameAdd();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENCOMMCMD)
	{
		pNew = new CItemsGenCommCmd();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSYSPARAEDIT)
	{
		pNew = new CItemsGenSysParaEdit();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENSAFETY)
	{
		pNew = new CItemsGenSafety();
	}

	return pNew;
}

CString CGenNodeBase::GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	ASSERT(FALSE);

	return _T("");
}

CString CGenNodeBase::GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	ASSERT(FALSE);

	return _T("");
}

BOOL CGenNodeBase::IsEnable(CItemsGenInterface *pInterface)
{
	if (m_pItemsGenEnable == NULL)
	{
		return FALSE;
	}

	return m_pItemsGenEnable->IsEnable(pInterface);
}

CItemsGenInterface* CGenNodeBase::GetGenInterface()
{
	ASSERT(FALSE);

	return NULL;
}

CItemsGenInterface* CGenNodeBase::GetGenInterface_BK()
{
	ASSERT(FALSE);

	return NULL;
}

void CGenNodeBase::LogParasMapError()
{
	if (m_pItemsGenParaMap == NULL)
	{
		return;
	}

	m_pItemsGenParaMap->LogParasMapError(PARAMAP_LOG_LEVEL_INTERFACE);
}

void CGenNodeBase::InitParasMapByUIParas(CDataGroup *pUIParas)
{
	if (m_pItemsGenParaMap == NULL)
	{
		return;
	}

	m_pItemsGenParaMap->InitParaValueByUIParas(pUIParas);
}

void CGenNodeBase::InitParasMapByInterface(CItemsGenInterface *pInterface)
{
	if (m_pItemsGenParaMap == NULL)
	{
		return;
	}

	m_pItemsGenParaMap->InitParasMapByInterface(pInterface);
}

void CGenNodeBase::GetAllParasMap(CExBaseList &listParasMap)
{
	listParasMap.RemoveAll();

	if (m_pItemsGenParaMap == NULL)
	{
		return;
	}

	CExBaseObject *pParent = this;
	UINT nClassID = 0;
	CGenNodeBase *pParentNode = NULL;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if ( (nClassID & GBITEMSGENMNGRCLASSID_CGENNODEBASE) != GBITEMSGENMNGRCLASSID_CGENNODEBASE)
		{
			//说明是到了items-gen-define节点或items-gen-class节点
// 			CItemsGenBase *pItemsGenBase = (CItemsGenBase *)pParent;
// 			listParasMap.Append(pItemsGenBase->GetItemsGenParasMap());
			break;
		}

		pParentNode = (CGenNodeBase *)pParent;

		if (pParentNode->GetItemsGenParaMap() == NULL)
		{
			pParent = (CExBaseObject *)pParent->GetParent();
			continue;
		}

		listParasMap.Append(pParentNode->GetItemsGenParaMap());
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE)
	{
		CItemsGenDefine *pItemsGenDefine = (CItemsGenDefine*)pParent;
		listParasMap.Append(pItemsGenDefine->GetItemsGenParasMap());

		//当前正在执行的实例，参数映射也要添加过来
// 		CItemsGenInst *pInst = pItemsGenDefine->GetCurrentInst();
// 
// 		if (pInst != NULL)
// 		{
// 			listParasMap.Append(pInst->GetItemsGenParasMap());
// 		}
	}
}

void CGenNodeBase::InitParasMapByInterface_Ex(CItemsGenInterface *pInterface)
{
	if (m_pItemsGenParaMap == NULL)
	{
		return;
	}

	m_pItemsGenParaMap->InitParasMapByInterface_Ex(pInterface);
}

void CGenNodeBase::ResetParasMap()
{
	if (m_pItemsGenParaMap == NULL || m_pItemsGenParaMap_BK == NULL)
	{
		return;
	}

	m_pItemsGenParaMap->DeleteAll();
	m_pItemsGenParaMap->AppendCloneEx2(*m_pItemsGenParaMap_BK);
}