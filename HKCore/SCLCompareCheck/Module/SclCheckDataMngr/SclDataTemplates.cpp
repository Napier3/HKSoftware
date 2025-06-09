// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SclDataTemplates.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

//////////////////////////////////////////////////////////DODetail/////////////////////////////////////////////////////////////////////////////////////
CDODetail::CDODetail()
{
	//初始化属性
}

CDODetail::~CDODetail()
{
}

#ifdef XML_USE_TINYXML

long CDODetail::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);

	return 0;
}

long CDODetail::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);

	return 0;
}

#else

long CDODetail::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);


	return 0;
}

long CDODetail::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);


	return 0;
}

#endif


//////////////////////////////////////////////////////////LNodeType/////////////////////////////////////////////////////////////////////////////////////

CSclLNodeType::CSclLNodeType()
{
	m_strName = _T("逻辑节点类型");
	m_strID = _T("LNodeType");

	//初始化属性
}

CSclLNodeType::~CSclLNodeType()
{
}

#ifdef XML_USE_TINYXML

long CSclLNodeType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strName);

	return 0;
}
long CSclLNodeType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strName);

	return 0;
}
long CSclLNodeType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CSclLNodeType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strName);
	

	return 0;
}

long CSclLNodeType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strName);
	


	return 0;
}
long CSclLNodeType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CSclLNodeType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSclLNodeType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclLNodeType *p = (CSclLNodeType*)pObj;

	return TRUE;
}

BOOL CSclLNodeType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclLNodeType *p = (CSclLNodeType*)pDest;

	return TRUE;
}

CBaseObject* CSclLNodeType::Clone()
{
	CSclLNodeType *p = new CSclLNodeType();
	Copy(p);
	return p;
}

CExBaseObject* CSclLNodeType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDODetailKey)
	{
		pNew = new CDODetail();
	}

	return pNew;
}

CExBaseObject* CSclLNodeType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DATATYPECLASSID_DODETAIL)
	{
		pNew = new CDODetail();
	}

	return pNew;
}

BOOL CSclLNodeType::CanPaste(UINT nClassID)
{
	if (nClassID == DATATYPECLASSID_DODETAIL)
	{
		return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////DataTypeTemplates////////////////////////////////////////////////////////////////////////////////////////////////


CDataTypeTmps::CDataTypeTmps()
{
	m_strName = /*_T("数据类型模板库")*/g_sLangTxt_SCLCompare_DataTypeTemplates;
	m_strID = _T("DataTypeTemplates");

	//初始化属性
}

CDataTypeTmps::~CDataTypeTmps()
{
}

#ifdef XML_USE_TINYXML

long CDataTypeTmps::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}
long CDataTypeTmps::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;



	return 0;
}
long CDataTypeTmps::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CDataTypeTmps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CDataTypeTmps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}
long CDataTypeTmps::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CDataTypeTmps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDataTypeTmps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDataTypeTmps *p = (CDataTypeTmps*)pObj;

	return TRUE;
}

BOOL CDataTypeTmps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDataTypeTmps *p = (CDataTypeTmps*)pDest;

	return TRUE;
}

CBaseObject* CDataTypeTmps::Clone()
{
	CDataTypeTmps *p = new CDataTypeTmps();
	Copy(p);
	return p;
}

CExBaseObject* CDataTypeTmps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCLNodeTypeKey)
	{
		pNew = new CSclLNodeType();
	}
	else if (strClassID == pXmlKeys->m_strCDOTypeKey)
	{
		pNew = new CSclDOType();
	}
	else if (strClassID == pXmlKeys->m_strCDATypeKey)
	{
		pNew = new CSclDAType();
	}
	else if (strClassID == pXmlKeys->m_strCEnumTypeKey)
	{
		pNew = new CSclEnumType();
	}

	return pNew;
}

CExBaseObject* CDataTypeTmps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DATATYPECLASSID_LNODETYPE)
	{
		pNew = new CSclLNodeType();
	}
	else if (nClassID == DATATYPECLASSID_DOTYPE)
	{
		pNew = new CSclDOType();
	}
	else if (nClassID == DATATYPECLASSID_DATYPE)
	{
		pNew = new CSclDAType();
	}
	else if (nClassID == DATATYPECLASSID_ENUMTYPE)
	{
		pNew = new CSclEnumType();
	}

	return pNew;
}

BOOL CDataTypeTmps::CanPaste(UINT nClassID)
{
	if (nClassID == DATATYPECLASSID_LNODETYPE)
	{
		return TRUE;
	}
	else if (nClassID == DATATYPECLASSID_DOTYPE)
	{
		return TRUE;
	}
	else if (nClassID == DATATYPECLASSID_DATYPE)
	{
		return TRUE;
	}
	else if (nClassID == DATATYPECLASSID_ENUMTYPE)
	{
		return TRUE;
	}

	return FALSE;

}
//////////////////////////////////////////////////////////DOType////////////////////////////////////////////////////////////////////////////////////////////////

CSclDOType::CSclDOType()
{
	m_strName = _T("数据对象类型");
	m_strID = _T("DOType");

	//初始化属性
}

CSclDOType::~CSclDOType()
{
}

#ifdef XML_USE_TINYXML

long CSclDOType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, m_strName);

	return 0;
}
long CSclDOType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, m_strName);

	return 0;
}
long CSclDOType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CSclDOType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, m_strName);


	return 0;
}

long CSclDOType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, m_strName);



	return 0;
}
long CSclDOType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CSclDOType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSclDOType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclDOType *p = (CSclDOType*)pObj;

	return TRUE;
}

BOOL CSclDOType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclDOType *p = (CSclDOType*)pDest;

	return TRUE;
}

CBaseObject* CSclDOType::Clone()
{
	CSclDOType *p = new CSclDOType();
	Copy(p);
	return p;
}

CExBaseObject* CSclDOType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDADetailKey)
	{
		pNew = new CDADetail();
	}

	return pNew;
}

CExBaseObject* CSclDOType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DATATYPECLASSID_DADETAIL)
	{
		pNew = new CDADetail();
	}

	return pNew;
}

BOOL CSclDOType::CanPaste(UINT nClassID)
{
	if (nClassID == DATATYPECLASSID_DADETAIL)
	{
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////DADetail////////////////////////////////////////////////////////////////////////////////////////////////


CDADetail::CDADetail()
{
	//初始化属性
	m_nObjType = 0;
	m_nCount = 0;
	m_nTrgOp = 0;

}

CDADetail::~CDADetail()
{
}

#ifdef XML_USE_TINYXML

long CDADetail::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strObjTypeKey, oNode, m_nObjType);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strSAddrKey, oNode, m_strAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strValKindKey, oNode, m_strValKind);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCountKey, oNode, m_nCount);
	xml_GetAttibuteValue(pXmlKeys->m_strFCKey, oNode, m_strFC);
	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOp);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSGroupKey, oNode, m_nSGroup);

	return 0;
}

long CDADetail::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strObjTypeKey, oElement, m_nObjType);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strSAddrKey, oElement, m_strAddr);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	xml_SetAttributeValue(pXmlKeys->m_strValKindKey, oElement, m_strValKind);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCountKey, oElement, m_nCount);
	xml_SetAttributeValue(pXmlKeys->m_strFCKey, oElement, m_strFC);
	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOp);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strSGroupKey, oElement, m_nSGroup);

	return 0;
}

#else

long CDADetail::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strObjTypeKey, oNode, m_nObjType);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strSAddrKey, oNode, m_strAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strValKindKey, oNode, m_strValKind);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCountKey, oNode, m_nCount);
	xml_GetAttibuteValue(pXmlKeys->m_strFCKey, oNode, m_strFC);
	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOp);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSGroupKey, oNode, m_nSGroup);


	return 0;
}

long CDADetail::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strObjTypeKey, oElement, m_nObjType);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strSAddrKey, oElement, m_strAddr);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	xml_SetAttributeValue(pXmlKeys->m_strValKindKey, oElement, m_strValKind);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCountKey, oElement, m_nCount);
	xml_SetAttributeValue(pXmlKeys->m_strFCKey, oElement, m_strFC);
	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOp);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strSGroupKey, oElement, m_nSGroup);


	return 0;
}

#endif


//////////////////////////////////////////////////////////DAType////////////////////////////////////////////////////////////////////////////////////////////////


CSclDAType::CSclDAType()
{
	m_strName = _T("数据属性类型");
	m_strID = _T("DAType");

	//初始化属性
}

CSclDAType::~CSclDAType()
{
}

#ifdef XML_USE_TINYXML

long CSclDAType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;

	return 0;
}
long CSclDAType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}
long CSclDAType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CSclDAType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;


	return 0;
}

long CSclDAType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);



	return 0;
}
long CSclDAType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CSclDAType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSclDAType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclDAType *p = (CSclDAType*)pObj;

	return TRUE;
}

BOOL CSclDAType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclDAType *p = (CSclDAType*)pDest;

	return TRUE;
}

CBaseObject* CSclDAType::Clone()
{
	CSclDAType *p = new CSclDAType();
	Copy(p);
	return p;
}

CExBaseObject* CSclDAType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBDADetailKey)
	{
		pNew = new CBDADetail();
	}

	return pNew;
}

CExBaseObject* CSclDAType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DATATYPECLASSID_BDADETAIL)
	{
		pNew = new CBDADetail();
	}

	return pNew;
}

BOOL CSclDAType::CanPaste(UINT nClassID)
{
	if (nClassID == DATATYPECLASSID_BDADETAIL)
	{
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////BDADetail////////////////////////////////////////////////////////////////////////////////////////////////


CBDADetail::CBDADetail()
{
	//初始化属性
	m_nCount = 0;

}

CBDADetail::~CBDADetail()
{
}

#ifdef XML_USE_TINYXML

long CBDADetail::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strSAddrKey, oNode, m_strAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strValKindKey, oNode, m_strValKind);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCountKey, oNode, m_nCount);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSGroupKey, oNode, m_nSGroup);

	return 0;
}

long CBDADetail::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strSAddrKey, oElement, m_strAddr);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	xml_SetAttributeValue(pXmlKeys->m_strValKindKey, oElement, m_strValKind);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCountKey, oElement, m_nCount);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strSGroupKey, oElement, m_nSGroup);

	return 0;
}

#else

long CBDADetail::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strSAddrKey, oNode, m_strAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strValKindKey, oNode, m_strValKind);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCountKey, oNode, m_nCount);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSGroupKey, oNode, m_nSGroup);


	return 0;
}

long CBDADetail::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strSAddrKey, oElement, m_strAddr);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	xml_SetAttributeValue(pXmlKeys->m_strValKindKey, oElement, m_strValKind);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCountKey, oElement, m_nCount);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strSGroupKey, oElement, m_nSGroup);


	return 0;
}

#endif


//////////////////////////////////////////////////////////EnumType////////////////////////////////////////////////////////////////////////////////////////////////




CSclEnumType::CSclEnumType()
{
	m_strName = _T("枚举类型");
	m_strID = _T("EnumType");

	//初始化属性
}

CSclEnumType::~CSclEnumType()
{
}

#ifdef XML_USE_TINYXML

long CSclEnumType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;

	return 0;
}
long CSclEnumType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}
long CSclEnumType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CSclEnumType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;


	return 0;
}

long CSclEnumType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);



	return 0;
}
long CSclEnumType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CSclEnumType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSclEnumType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclEnumType *p = (CSclEnumType*)pObj;

	return TRUE;
}

BOOL CSclEnumType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclEnumType *p = (CSclEnumType*)pDest;

	return TRUE;
}

CBaseObject* CSclEnumType::Clone()
{
	CSclEnumType *p = new CSclEnumType();
	Copy(p);
	return p;
}

CExBaseObject* CSclEnumType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEnumValKey)
	{
		pNew = new CEnumVal();
	}

	return pNew;
}

CExBaseObject* CSclEnumType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DATATYPECLASSID_ENUMDETAIL)
	{
		pNew = new CEnumVal();
	}

	return pNew;
}

BOOL CSclEnumType::CanPaste(UINT nClassID)
{
	if (nClassID == DATATYPECLASSID_ENUMDETAIL)
	{
		return TRUE;
	}

	return FALSE;
}



//////////////////////////////////////////////////////////EnumVal////////////////////////////////////////////////////////////////////////////////////////////////


CEnumVal::CEnumVal()
{
	//初始化属性
	m_nOrd = 0;

}

CEnumVal::~CEnumVal()
{
}

#ifdef XML_USE_TINYXML

long CEnumVal::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOrdKey, oNode, m_nOrd);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);


	return 0;
}

long CEnumVal::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOrdKey, oElement, m_nOrd);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);



	return 0;
}

#else

long CEnumVal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOrdKey, oNode, m_nOrd);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);



	return 0;
}

long CEnumVal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOrdKey, oElement, m_nOrd);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	


	return 0;
}

#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////