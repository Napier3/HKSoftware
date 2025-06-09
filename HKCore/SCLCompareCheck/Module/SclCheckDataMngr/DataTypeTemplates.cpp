// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DataTypeTemplates.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

// bool UTF8ToMultiByte(CString &srcStr)
// {
// 	signed int iTextLen = 0;
// 	unsigned short wszGBK[256] = {0};
// 
// 	memset(wszGBK, 0, 256);
// 
// 	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
// 	memset(wszGBK, 0, iTextLen * 2 + 2); 
// 	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 
// 
// 	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
// 	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, (LPSTR)(LPCSTR)srcStr, iTextLen, NULL, NULL); 
// 
// 	return true;
// }

//////////////////////////////////////////////////////////TemplateFile1396////////////////////////////////////////////////////////////////////////////////////////////////
CTemplateFile1396::CTemplateFile1396()
{

}

CTemplateFile1396::~CTemplateFile1396()
{


}

BOOL CTemplateFile1396::OpenTemplateFile1396(const CString &strFile)
{
	long nIndex = strFile.ReverseFind('\\');
	m_strName = strFile.Mid(nIndex+1);
	return OpenXmlFile(strFile,CSclCheckMngrXmlRWKeys::g_pXmlKeys);	

}

BOOL CTemplateFile1396::SaveTemplateFile1396()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += m_strName;
	strFile = ChangeFilePostfix(strFile, "xml");

	return SaveXmlFile(strFile, CSclCheckMngrXmlRWKeys::g_pXmlKeys);
}

#ifdef XML_USE_TINYXML

long CTemplateFile1396::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CTemplateFile1396::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn( oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#else

long CTemplateFile1396::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CTemplateFile1396::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#endif
CExBaseObject*CTemplateFile1396::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDataTypeTmpsKey)
	{
		pNew = new CDataTypeTemplates();
		((CDataTypeTemplates*)pNew)->m_bUTF8 = TRUE;
	}
	else if (strClassID == pXmlKeys->m_strCLDeviceKey)
	{
		pNew = new CLDevice_Scl();
	}
	else if (strClassID == pXmlKeys->m_strCDataSetKey)
	{
		pNew = new CDataSet_Scl();
	}
	else if (strClassID == pXmlKeys->m_strCCDCKey)
	{
		pNew = new CCDC_Scl();
	}

	return pNew;
}

CExBaseObject* CTemplateFile1396::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILETEMPLATES)
	{
		pNew = new CDataTypeTemplates();
	}
	else if (nClassID == SCLCLASSID_CSCLFILE_LDEVICE)
	{
		pNew = new CLDevice_Scl();
	}
	else if (nClassID == SCLCLASSID_CSCLFILE_DATASET)
	{
		pNew = new CDataSet_Scl();
	}
	else if (nClassID == SCLCLASSID_CSCLFILE_CDC)
	{
		pNew = new CCDC_Scl();
	}
	return pNew;
}

void CTemplateFile1396::InitAfterRead()
{
//	InitSvGsIns();
}
//////////////////////////////////////////////////////////DataTypeTemplates////////////////////////////////////////////////////////////////////////////////////////////////


CDataTypeTemplates::CDataTypeTemplates()
{
	m_strName = /*_T("数据类型模板库")*/g_sLangTxt_SCLCompare_DataTypeTemplates;
	m_strID = _T("DataTypeTemplates");

	//初始化属性
	m_bUTF8 = FALSE;
}

CDataTypeTemplates::~CDataTypeTemplates()
{
}

#ifdef XML_USE_TINYXML

long CDataTypeTemplates::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}
long CDataTypeTemplates::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;



	return 0;
}
long CDataTypeTemplates::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CDataTypeTemplates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CDataTypeTemplates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}
long CDataTypeTemplates::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CDataTypeTemplates::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDataTypeTemplates::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDataTypeTemplates *p = (CDataTypeTemplates*)pObj;

	return TRUE;
}

BOOL CDataTypeTemplates::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDataTypeTemplates *p = (CDataTypeTemplates*)pDest;

	return TRUE;
}

CBaseObject* CDataTypeTemplates::Clone()
{
	CDataTypeTemplates *p = new CDataTypeTemplates();
	Copy(p);
	return p;
}

CExBaseObject* CDataTypeTemplates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCLNodeTypeTKey)
	{
		pNew = new CLNodeTypeT();
	}
	else if (strClassID == pXmlKeys->m_strCDOTypeKey)
	{
		pNew = new CDOType();
		((CDOType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (strClassID == pXmlKeys->m_strCDATypeKey)
	{
		pNew = new CDAType();
		((CDAType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (strClassID == pXmlKeys->m_strCEnumTypeKey)
	{
		pNew = new CEnumType();
		((CEnumType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (strClassID == pXmlKeys->m_strCLNodeTypeKey)
	{
		pNew = new CLNodeType();
		((CLNodeType*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

CExBaseObject* CDataTypeTemplates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILELNODETYPET)
	{
		pNew = new CLNodeTypeT();
	}
	else if (nClassID == SCLCLASSID_CSCLFILEDOTYPE)
	{
		pNew = new CDOType();
		((CDOType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (nClassID == SCLCLASSID_CSCLFILEDATYPE)
	{
		pNew = new CDAType();
		((CDAType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (nClassID == SCLCLASSID_CSCLFILEENUMTYPE)
	{
		pNew = new CEnumType();
		((CEnumType*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (nClassID == SCLCLASSID_CSCLFILELNODETYPE)
	{
		pNew = new CLNodeType();
		((CLNodeType*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

BOOL CDataTypeTemplates::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILELNODETYPET)
	{
		return TRUE;
	}
	else if (nClassID == SCLCLASSID_CSCLFILEDOTYPE)
	{
		return TRUE;
	}
	else if (nClassID == SCLCLASSID_CSCLFILEDATYPE)
	{
		return TRUE;
	}
	else if (nClassID == SCLCLASSID_CSCLFILEENUMTYPE)
	{
		return TRUE;
	}
	else if (nClassID == SCLCLASSID_CSCLFILELNODETYPE)
	{
		return TRUE;
	}

	return FALSE;

}
//////////////////////////////////////////////////////////LNodeTypeT/////////////////////////////////////////////////////////////////////////////////////

CLNodeTypeT::CLNodeTypeT()
{
	m_strName = _T("逻辑节点类型T");
	m_strID = _T("LNodeTypeT");

	//初始化属性
}

CLNodeTypeT::~CLNodeTypeT()
{
}

#ifdef XML_USE_TINYXML

long CLNodeTypeT::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	//	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strID);

	return 0;
}
long CLNodeTypeT::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	//	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strID);

	return 0;
}
long CLNodeTypeT::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CLNodeTypeT::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	//	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strID);


	return 0;
}

long CLNodeTypeT::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	//	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strID);

	return 0;
}
long CLNodeTypeT::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CLNodeTypeT::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CLNodeTypeT::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CLNodeTypeT *p = (CLNodeTypeT*)pObj;

	return TRUE;
}

BOOL CLNodeTypeT::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CLNodeTypeT *p = (CLNodeTypeT*)pDest;

	return TRUE;
}

CBaseObject* CLNodeTypeT::Clone()
{
	CLNodeTypeT *p = new CLNodeTypeT();
	Copy(p);
	return p;
}

CExBaseObject* CLNodeTypeT::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDOTValueKey)
	{
		pNew = new CDOValueT();
	}

	return pNew;
}

CExBaseObject* CLNodeTypeT::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILE_DOTVALUE)
	{
		pNew = new CDOValueT();
	}

	return pNew;
}

BOOL CLNodeTypeT::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_DOTVALUE)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////DOValueT/////////////////////////////////////////////////////////////////////////////////////
CDOValueT::CDOValueT()
{
	//初始化属性
}

CDOValueT::~CDOValueT()
{
}

#ifdef XML_USE_TINYXML

long CDOValueT::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID );
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode,m_strName );
	xml_GetAttibuteValue(pXmlKeys->m_strMopKey, oNode,m_strMop );
	return 0;
}

long CDOValueT::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID );
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement,m_strName );
	xml_SetAttributeValue(pXmlKeys->m_strMopKey, oElement,m_strMop );
	return 0;
}

#else

long CDOValueT::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode,m_strID );
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, m_strName );
	xml_GetAttibuteValue(pXmlKeys->m_strMopKey, oNode,m_strMop );
	return 0;
}

long CDOValueT::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID );
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strMopKey, oElement,m_strMop );
	return 0;
}

#endif
//////////////////////////////////////////////////////////DOType////////////////////////////////////////////////////////////////////////////////////////////////

CDOType::CDOType()
{
	m_strName = _T("数据对象类型");
	m_strID = _T("DOType");

	//初始化属性
	m_bUTF8 = FALSE;
}

CDOType::~CDOType()
{
}

#ifdef XML_USE_TINYXML

long CDOType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, m_strName);
	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	xml_GetAttibuteValue(pXmlKeys->m_strPrivateMSGKey, oNode, m_strPrivateMSG);
	if(m_bUTF8)
	{
		UTF8ToMultiByte(m_strPrivateMSG);
	}

	return 0;
}
long CDOType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strPrivateMSGKey, oElement, m_strPrivateMSG);

	return 0;
}
long CDOType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CDOType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, m_strName);


	return 0;
}

long CDOType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, m_strName);



	return 0;
}
long CDOType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CDOType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDOType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDOType *p = (CDOType*)pObj;

	return TRUE;
}

BOOL CDOType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDOType *p = (CDOType*)pDest;
	p->m_strPrivateMSG = m_strErrorPos;
	p->m_strErrorPos = m_strErrorPos;

	return TRUE;
}

CBaseObject* CDOType::Clone()
{
	CDOType *p = new CDOType();
	Copy(p);
	return p;
}

CExBaseObject* CDOType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDAValueKey)
	{
		pNew = new CDAValue();
		((CDAValue*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (strClassID == pXmlKeys->m_strCSDOValueKey)
	{
		pNew = new CSDOValue();
		((CSDOValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

CExBaseObject* CDOType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILE_DADETAIL)
	{
		pNew = new CDAValue();
		((CDAValue*)pNew)->m_bUTF8 = m_bUTF8;
	}
	else if (nClassID == SCLCLASSID_CSCLFILE_SDODETAIL)
	{
		pNew = new CSDOValue();
		((CSDOValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

BOOL CDOType::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_DADETAIL)
	{
		return TRUE;
	}
	else if (nClassID == SCLCLASSID_CSCLFILE_SDODETAIL)
	{
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////DAValue////////////////////////////////////////////////////////////////////////////////////////////////


CDAValue::CDAValue()
{
	//初始化属性
	m_bUTF8 =FALSE;
}

CDAValue::~CDAValue()
{
}

BOOL CDAValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDAValue *p = (CDAValue*)pDest;
	p->m_strErrorPos = m_strErrorPos;
	p->m_strBType = m_strBType;
	p->m_strDchg = m_strDchg;
	p->m_strQchg = m_strQchg;
	p->m_strFC = m_strFC;
	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CDAValue::Clone()
{
	CDAValue *p = new CDAValue();
	Copy(p);
	return p;
}

BOOL CDAValue::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_DADETAIL)
	{
		return TRUE;
	}
	return FALSE;
}

#ifdef XML_USE_TINYXML

long CDAValue::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDchgKey, oNode, m_strDchg);
	xml_GetAttibuteValue(pXmlKeys->m_strFCKey, oNode, m_strFC);
	xml_GetAttibuteValue(pXmlKeys->m_strQchgKey, oNode, m_strQchg);
	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);

	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	return 0;
}

long CDAValue::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	}
	
	if (!m_strDchg.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDchgKey, oElement, m_strDchg);
	}
	
	xml_SetAttributeValue(pXmlKeys->m_strFCKey, oElement, m_strFC);
	if (!m_strQchg.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strQchgKey, oElement, m_strQchg);
	}
	
	if (!m_strValue.IsEmpty())
	{
		xml_SetElementText(pXmlKeys->m_strValueKey, oElement, m_strValue);
	}
	
	return 0;
}

#else

long CDAValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDchgKey, oNode, m_strDchg);
	xml_GetAttibuteValue(pXmlKeys->m_strFCKey, oNode, m_strFC);
	xml_GetAttibuteValue(pXmlKeys->m_strQchgKey, oNode, m_strQchg);
	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CDAValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	}

	if (!m_strDchg.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDchgKey, oElement, m_strDchg);
	}

	xml_SetAttributeValue(pXmlKeys->m_strFCKey, oElement, m_strFC);
	if (!m_strQchg.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strQchgKey, oElement, m_strQchg);
	}

	if (!m_strValue.IsEmpty())
	{
		xml_SetElementText(pXmlKeys->m_strValueKey,oXMLDoc, oElement, m_strValue);
	}
	return 0;
}

#endif

//////////////////////////////////////////////////////////SDOValue////////////////////////////////////////////////////////////////////////////////////////////////


CSDOValue::CSDOValue()
{
	//初始化属性
	m_bUTF8 = FALSE;
}

CSDOValue::~CSDOValue()
{
}

BOOL CSDOValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSDOValue *p = (CSDOValue*)pDest;
	p->m_strErrorPos = m_strErrorPos;

	return TRUE;
}

CBaseObject* CSDOValue::Clone()
{
	CSDOValue *p = new CSDOValue();
	Copy(p);
	return p;
}

BOOL CSDOValue::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_SDODETAIL)
	{
		return TRUE;
	}
	return FALSE;
}

#ifdef XML_USE_TINYXML

long CSDOValue::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);

	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	return 0;
}

long CSDOValue::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	return 0;
}

#else

long CSDOValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);
	return 0;
}

long CSDOValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	return 0;
}

#endif
//////////////////////////////////////////////////////////DAType////////////////////////////////////////////////////////////////////////////////////////////////


CDAType::CDAType()
{
	m_strName = _T("数据属性类型");
	m_strID = _T("DAType");

	//初始化属性
	m_bUTF8 =FALSE;
}

CDAType::~CDAType()
{
}

#ifdef XML_USE_TINYXML

long CDAType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	m_strName = m_strID;
	xml_GetAttibuteValue(pXmlKeys->m_strPrivateMSGKey, oNode, m_strPrivateMSG);
	if(m_bUTF8)
	{
		UTF8ToMultiByte(m_strPrivateMSG);
	}

	return 0;
}
long CDAType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strPrivateMSGKey, oElement, m_strPrivateMSG);
	
	return 0;
}
long CDAType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CDAType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;


	return 0;
}

long CDAType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}
long CDAType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CDAType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDAType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDAType *p = (CDAType*)pObj;

	return TRUE;
}

BOOL CDAType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDAType *p = (CDAType*)pDest;
	p->m_strErrorPos = m_strErrorPos;
	p->m_strPrivateMSG = m_strPrivateMSG;

	return TRUE;
}

CBaseObject* CDAType::Clone()
{
	CDAType *p = new CDAType();
	Copy(p);
	return p;
}

CExBaseObject* CDAType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBDAValueKey)
	{
		pNew = new CBDAValue();
		((CBDAValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

CExBaseObject* CDAType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILE_BDADETAIL)
	{
		pNew = new CBDAValue();
		((CBDAValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

BOOL CDAType::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_BDADETAIL)
	{
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////BDADetail////////////////////////////////////////////////////////////////////////////////////////////////


CBDAValue::CBDAValue()
{
	//初始化属性
	m_bUTF8 = FALSE;
}

CBDAValue::~CBDAValue()
{
}

BOOL CBDAValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CBDAValue *p = (CBDAValue*)pDest;
	p->m_strErrorPos = m_strErrorPos;
	p->m_strBType = m_strBType;

	return TRUE;
}

CBaseObject* CBDAValue::Clone()
{
	CBDAValue *p = new CBDAValue();
	Copy(p);
	return p;
}

BOOL CBDAValue::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_BDADETAIL)
	{
		return TRUE;
	}
	return FALSE;
}

#ifdef XML_USE_TINYXML

long CBDAValue::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);

	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	return 0;
}

long CBDAValue::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	}
	return 0;
}

#else

long CBDAValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strBTypeKey, oNode, m_strBType);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strName);
	return 0;
}

long CBDAValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strBTypeKey, oElement, m_strBType);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strName);
	}
	return 0;
}

#endif


//////////////////////////////////////////////////////////EnumType////////////////////////////////////////////////////////////////////////////////////////////////




CEnumType::CEnumType()
{
	m_strName = _T("枚举类型");
	m_strID = _T("EnumType");

	//初始化属性
	m_bUTF8 = FALSE;
}

CEnumType::~CEnumType()
{
}

#ifdef XML_USE_TINYXML

long CEnumType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);

	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	m_strName = m_strID;
	xml_GetAttibuteValue(pXmlKeys->m_strPrivateMSGKey, oNode, m_strPrivateMSG);
	if(m_bUTF8)
	{
		UTF8ToMultiByte(m_strPrivateMSG);
	}


	return 0;
}
long CEnumType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	xml_SetAttributeValue(pXmlKeys->m_strPrivateMSGKey, oElement, m_strPrivateMSG);

	return 0;
}
long CEnumType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CEnumType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	m_strName = m_strID;


	return 0;
}

long CEnumType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);



	return 0;
}
long CEnumType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CEnumType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CEnumType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEnumType *p = (CEnumType*)pObj;

	return TRUE;
}

BOOL CEnumType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEnumType *p = (CEnumType*)pDest;

	return TRUE;
}

CBaseObject* CEnumType::Clone()
{
	CEnumType *p = new CEnumType();
	Copy(p);
	return p;
}

CExBaseObject* CEnumType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEnumValKey)
	{
		pNew = new CEnumValue();
		((CEnumValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

CExBaseObject* CEnumType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILE_ENUMDETAIL)
	{
		pNew = new CEnumValue();
		((CEnumValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

BOOL CEnumType::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_ENUMDETAIL)
	{
		return TRUE;
	}

	return FALSE;
}



//////////////////////////////////////////////////////////EnumVal////////////////////////////////////////////////////////////////////////////////////////////////


CEnumValue::CEnumValue()
{
	//初始化属性
	m_bUTF8 = FALSE;
}

CEnumValue::~CEnumValue()
{
}

BOOL CEnumValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEnumValue *p = (CEnumValue*)pDest;
	p->m_strErrorPos = m_strErrorPos;

	return TRUE;
}

CBaseObject* CEnumValue::Clone()
{
	CEnumValue *p = new CEnumValue();
	Copy(p);
	return p;
}

BOOL CEnumValue::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_ENUMDETAIL)
	{
		return TRUE;
	}
	return FALSE;
}


#ifdef XML_USE_TINYXML

long CEnumValue::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOrdKey, oNode, m_strID);

	xml_GetRowAndColumn(oNode ,m_strErrorPos);

	const TiXmlNode* nodeValue;
	nodeValue = oNode->FirstChild();

	if (nodeValue)
	{
		m_strName = nodeValue->Value();
		if (m_bUTF8)
		{
			UTF8ToMultiByte(m_strName);
		}
		
	}
	return 0;
}

long CEnumValue::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOrdKey, oElement, m_strID);
	if (!m_strName.IsEmpty())
	{
		oElement->SetTextChild(m_strName);
	}

	return 0;
}

#else

long CEnumValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOrdKey, oNode, m_strID);
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
//	UTF8ToMultiByte(m_strName);
	return 0;
}

long CEnumValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOrdKey, oElement, m_strID);

	if (!m_strName.IsEmpty())
	{
		xml_SetElementText(pXmlKeys->m_strNameKey,oXMLDoc, oElement, m_strName);
	}
	
	return 0;
}

#endif
//////////////////////////////////////////////////////////LDevice////////////////////////////////////////////////////////////////////////////////////////////////


CLDevice_Scl::CLDevice_Scl()
{
	//初始化属性
}

CLDevice_Scl::~CLDevice_Scl()
{
}

#ifdef XML_USE_TINYXML

long CLDevice_Scl::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
	UTF8ToMultiByte(m_strName);
	return 0;
}

long CLDevice_Scl::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	return 0;
}

#else

long CLDevice_Scl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
//	UTF8ToMultiByte(m_strName);
	return 0;
}

long CLDevice_Scl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	return 0;
}

#endif
//////////////////////////////////////////////////////////DataSet////////////////////////////////////////////////////////////////////////////////////////////////


CDataSet_Scl::CDataSet_Scl()
{
	//初始化属性
}

CDataSet_Scl::~CDataSet_Scl()
{
}

#ifdef XML_USE_TINYXML

long CDataSet_Scl::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
	UTF8ToMultiByte(m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strBrcbnameKey, oNode, m_strBrcbname);
	xml_GetAttibuteValue(pXmlKeys->m_strLcbnameKey, oNode, m_strLcbname);
	UTF8ToMultiByte(m_strLcbname);
	return 0;
}

long CDataSet_Scl::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strBrcbnameKey, oElement, m_strBrcbname);
	xml_SetAttributeValue(pXmlKeys->m_strLcbnameKey, oElement, m_strLcbname);
	return 0;
}

#else

long CDataSet_Scl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
//	UTF8ToMultiByte(m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strBrcbnameKey, oNode, m_strBrcbname);
	xml_GetAttibuteValue(pXmlKeys->m_strLcbnameKey, oNode, m_strLcbname);
//	UTF8ToMultiByte(m_strLcbname);
	return 0;
}

long CDataSet_Scl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strBrcbnameKey, oElement, m_strBrcbname);
	xml_SetAttributeValue(pXmlKeys->m_strLcbnameKey, oElement, m_strLcbname);
	return 0;
}

#endif
//////////////////////////////////////////////////////////CDC////////////////////////////////////////////////////////////////////////////////////////////////


CCDC_Scl::CCDC_Scl()
{
	//初始化属性
}

CCDC_Scl::~CCDC_Scl()
{
}

#ifdef XML_USE_TINYXML

long CCDC_Scl::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
	UTF8ToMultiByte(m_strName);
	return 0;
}

long CCDC_Scl::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	return 0;
}

#else

long CCDC_Scl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
//	UTF8ToMultiByte(m_strName);
	return 0;
}

long CCDC_Scl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	return 0;
}

#endif
//////////////////////////////////////////////////////////CSCLTemplates////////////////////////////////////////////////////////////////////////////////////////////////
CSCLTemplates::CSCLTemplates()
{
	m_bUTF8 = FALSE;
}

CSCLTemplates::~CSCLTemplates()
{
}

BOOL CSCLTemplates::OpenSclTemplatesFile(const CString &strFile)
{
	m_strName = strFile;
	return OpenXmlFile(strFile,CSclCheckMngrXmlRWKeys::g_pXmlKeys);	
}

void CSCLTemplates::OpenSclTemplatesFileByTinyRoot(TiXmlElement* pDocRoot)
{
//	XmlRead(pDocRoot, CSclCheckMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CSCLTemplates::SaveSclTemplatesFile()
{
// 	CString strFile;
// 	strFile = _P_GetLibraryPath();
// 	strFile += m_strName;
// 	strFile = ChangeFilePostfix(strFile, "xml");

	return SaveXmlFile(m_strName, CSclCheckMngrXmlRWKeys::g_pXmlKeys /*,"GB2312"*/);
}

#ifdef XML_USE_TINYXML

long CSCLTemplates::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSCLTemplates::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn( oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#else

long CSCLTemplates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSCLTemplates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#endif
CExBaseObject*CSCLTemplates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDataTypeTmpsKey)
	{
		pNew = new CDataTypeTemplates();
		((CDataTypeTemplates*)pNew)->m_bUTF8 = m_bUTF8;
	}
	return pNew;
}

CExBaseObject* CSCLTemplates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILETEMPLATES)
	{
		pNew = new CDataTypeTemplates();
		((CDataTypeTemplates*)pNew)->m_bUTF8 = m_bUTF8;
	}
	return pNew;
}

void CSCLTemplates::InitAfterRead()
{
	//	InitSvGsIns();
}
//////////////////////////////////////////////////////////LNodeType/////////////////////////////////////////////////////////////////////////////////////

CLNodeType::CLNodeType()
{
	m_strName = _T("逻辑节点类型T");
	m_strID = _T("LNodeType");

	m_bUTF8 = FALSE;

	//初始化属性
}

CLNodeType::~CLNodeType()
{
}

#ifdef XML_USE_TINYXML

long CLNodeType::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);

	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strLnClass);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);

	xml_GetAttibuteValue(pXmlKeys->m_strPrivateMSGKey, oNode, m_strPrivateMSG);
	if (m_bUTF8)
	{
		UTF8ToMultiByte(m_strID);
		UTF8ToMultiByte(m_strName);
		UTF8ToMultiByte(m_strPrivateMSG);
	}

	xml_GetRowAndColumn(oNode ,m_strErrorPos);

	return 0;
}
long CLNodeType::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strLnClass);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	}
	xml_SetAttributeValue(pXmlKeys->m_strPrivateMSGKey, oElement, m_strPrivateMSG);

	return 0;
}
long CLNodeType::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CLNodeType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
//	UTF8ToMultiByte(m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLnClassKey, oNode, m_strLnClass);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
//	UTF8ToMultiByte(m_strName);
	return 0;
}

long CLNodeType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLnClassKey, oElement, m_strLnClass);
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	}
	return 0;
}
long CLNodeType::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CLNodeType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CLNodeType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CLNodeType *p = (CLNodeType*)pObj;

	return TRUE;
}

BOOL CLNodeType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CLNodeType *p = (CLNodeType*)pDest;
	p->m_strPrivateMSG = m_strPrivateMSG;
	p->m_strLnClass = m_strLnClass;
	p->m_strErrorPos = m_strErrorPos;

	return TRUE;
}

CBaseObject* CLNodeType::Clone()
{
	CLNodeType *p = new CLNodeType();
	Copy(p);
	return p;
}

CExBaseObject* CLNodeType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDOValueKey)
	{
		pNew = new CDOValue();
		((CDOValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

CExBaseObject* CLNodeType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CSCLFILE_DODETAIL)
	{
		pNew = new CDOValue();
		((CDOValue*)pNew)->m_bUTF8 = m_bUTF8;
	}

	return pNew;
}

BOOL CLNodeType::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_DODETAIL)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////DOValue////////////////////////////////////////////////////////////////////////////////////////////
CDOValue::CDOValue()
{
	//初始化属性
	m_bUTF8 = FALSE;
}

CDOValue::~CDOValue()
{
}

BOOL CDOValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDOValue *p = (CDOValue*)pDest;
	p->m_strErrorPos = m_strErrorPos;
	p->m_strType = m_strType;
	p->m_strTransient = m_strTransient;

	return TRUE;
}

CBaseObject* CDOValue::Clone()
{
	CDOValue *p = new CDOValue();
	Copy(p);
	return p;
}

BOOL CDOValue::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCLFILE_DODETAIL)
	{
		return TRUE;
	}

	return FALSE;
}

#ifdef XML_USE_TINYXML

long CDOValue::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID );
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode,m_strName );

	if(m_bUTF8)
	{
		UTF8ToMultiByte(m_strName);
	}
	
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode,m_strType );
	xml_GetAttibuteValue(pXmlKeys->m_strTransientKey, oNode,m_strTransient );

	xml_GetRowAndColumn(oNode ,m_strErrorPos);
	return 0;
}

long CDOValue::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID );
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement,m_strName );
	}
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement,m_strType );
	if (!m_strTransient.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTransientKey, oElement,m_strTransient );
	}
	return 0;
}

#else

long CDOValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID );
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode,m_strName );
//	UTF8ToMultiByte(m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode,m_strType );
	xml_GetAttibuteValue(pXmlKeys->m_strTransientKey, oNode,m_strTransient );
	return 0;
}

long CDOValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID );
	if (!m_strName.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement,m_strName );
	}
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement,m_strType );
	if (!m_strTransient.IsEmpty())
	{
		xml_SetAttributeValue(pXmlKeys->m_strTransientKey, oElement,m_strTransient );
	}
	return 0;
}

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////