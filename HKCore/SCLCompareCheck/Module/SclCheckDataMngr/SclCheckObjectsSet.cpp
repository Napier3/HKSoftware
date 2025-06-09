// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SclCheckObjectsSet.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"

//////////////////////////////////////////////////////////CSclCheckObjectsSet////////////////////////////////////////////////////////////////////////////////////////////////
CSclCheckObjectsSet::CSclCheckObjectsSet()
{
}

CSclCheckObjectsSet::~CSclCheckObjectsSet()
{
}

BOOL CSclCheckObjectsSet::OpenCheckConfigFile(CString strFile)
{
	if (strFile.IsEmpty())
	{
		strFile = _P_GetConfigPath();
		strFile += "SclCheckObjectsSet.xml";
	} 
	m_strName = strFile;
	return OpenXmlFile(strFile,CSclCheckMngrXmlRWKeys::g_pXmlKeys);	

}

BOOL CSclCheckObjectsSet::SaveCheckConfigFile()
{
	return SaveXmlFile(m_strName, CSclCheckMngrXmlRWKeys::g_pXmlKeys);
}

#ifdef XML_USE_TINYXML

long CSclCheckObjectsSet::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSclCheckObjectsSet::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn( oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#else

long CSclCheckObjectsSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSclCheckObjectsSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

#endif
CExBaseObject*CSclCheckObjectsSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCheckPathsKey)
	{
		pNew = new CCheckPaths();
	}
	else if (strClassID == pXmlKeys->m_strCSchemaChecksKey)
	{
		pNew = new CSchemaChecks();
	}
	else if (strClassID == pXmlKeys->m_strCDLT860ModelChecksKey)
	{
		pNew = new CDLT860ModelChecks();
	}
	else if (strClassID == pXmlKeys->m_strCProjAppModelChecksKey)
	{
		pNew = new CProjAppModelChecks();
	}
	else if (strClassID == pXmlKeys->m_strCVirLoopChecksKey)
	{
		pNew = new CVirLoopChecks();
	}
	return pNew;
}

CExBaseObject* CSclCheckObjectsSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CCHECKPATHS)
	{
		pNew = new CCheckPaths();
	}
	else if (nClassID == SCLCLASSID_CSCHEMACHECKS)
	{
		pNew = new CSchemaChecks();
	}
	else if (nClassID == SCLCLASSID_CDLT860MODELCHECKS)
	{
		pNew = new CDLT860ModelChecks();
	}
	else if (nClassID == SCLCLASSID_CPROJAPPMODELCHECKS)
	{
		pNew = new CProjAppModelChecks();
	}
	else if (nClassID == SCLCLASSID_CVIRLOOPCHECKS)
	{
		pNew = new CVirLoopChecks();
	}
	return pNew;
}

void CSclCheckObjectsSet::InitAfterRead()
{
	//	InitSvGsIns();
}
//////////////////////////////////////////////////////////CCheckPaths////////////////////////////////////////////////////////////////////////////////////////////////
CCheckPaths::CCheckPaths()
{
	m_strName = _T("SCL文件路径集");
	m_strID = _T("CheckPaths");
}

CCheckPaths::~CCheckPaths()
{
}

#ifdef XML_USE_TINYXML

long CCheckPaths::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CCheckPaths::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CCheckPaths::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CCheckPaths::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCheckPaths::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CCheckPaths::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CCheckPaths::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CCheckPaths::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCheckPaths *p = (CCheckPaths*)pObj;

	return TRUE;
}

BOOL CCheckPaths::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCheckPaths *p = (CCheckPaths*)pDest;

	return TRUE;
}

CBaseObject* CCheckPaths::Clone()
{
	CCheckPaths *p = new CCheckPaths();
	Copy(p);
	return p;
}

CExBaseObject* CCheckPaths::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSinglePathKey)
	{
		pNew = new CSinglePath();
	}

	return pNew;
}

CExBaseObject* CCheckPaths::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_SINGLEPATH)
	{
		pNew = new CSinglePath();
	}

	return pNew;
}

BOOL CCheckPaths::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CCHECKPATHS)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////CSchemaChecks////////////////////////////////////////////////////////////////////////////////////////////////
CSchemaChecks::CSchemaChecks()
{
	m_strName = _T("Schema语法检查");
	m_strID = _T("SchemaChecks");
}

CSchemaChecks::~CSchemaChecks()
{
}

#ifdef XML_USE_TINYXML

long CSchemaChecks::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSchemaChecks::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSchemaChecks::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CSchemaChecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSchemaChecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CSchemaChecks::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CSchemaChecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CSchemaChecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSchemaChecks *p = (CSchemaChecks*)pObj;

	return TRUE;
}

BOOL CSchemaChecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSchemaChecks *p = (CSchemaChecks*)pDest;

	return TRUE;
}

CBaseObject* CSchemaChecks::Clone()
{
	CSchemaChecks *p = new CSchemaChecks();
	Copy(p);
	return p;
}

CExBaseObject* CSchemaChecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSchemaObjectKey)
	{
		pNew = new CSchemaCheckObject();
	}

	return pNew;
}

CExBaseObject* CSchemaChecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_SCHEMACCHECKOBJECT)
	{
		pNew = new CSchemaCheckObject();
	}

	return pNew;
}

BOOL CSchemaChecks::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCHEMACHECKS)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////CDLT860ModelChecks////////////////////////////////////////////////////////////////////////////////////////////////


CDLT860ModelChecks::CDLT860ModelChecks()
{
	m_strName = _T("DL/T860模型一致性检查");
	m_strID = _T("DLT860ModelChecks");
}

CDLT860ModelChecks::~CDLT860ModelChecks()
{
}

#ifdef XML_USE_TINYXML

long CDLT860ModelChecks::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CDLT860ModelChecks::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CDLT860ModelChecks::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CDLT860ModelChecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDLT860ModelChecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CDLT860ModelChecks::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CDLT860ModelChecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CDLT860ModelChecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDLT860ModelChecks *p = (CDLT860ModelChecks*)pObj;

	return TRUE;
}

BOOL CDLT860ModelChecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDLT860ModelChecks *p = (CDLT860ModelChecks*)pDest;

	return TRUE;
}

CBaseObject* CDLT860ModelChecks::Clone()
{
	CDLT860ModelChecks *p = new CDLT860ModelChecks();
	Copy(p);
	return p;
}

CExBaseObject* CDLT860ModelChecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCCheckObjectKey)
	{
		pNew = new CCheckObject();
	}

	return pNew;
}

CExBaseObject* CDLT860ModelChecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		pNew = new CCheckObject();
	}

	return pNew;
}

BOOL CDLT860ModelChecks::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		return TRUE;
	}

	return FALSE;

}

//////////////////////////////////////////////////////////CProjAppModelChecks////////////////////////////////////////////////////////////////////////////////////////////////


CProjAppModelChecks::CProjAppModelChecks()
{
	m_strName = _T("工程应用模型规范性检查");
	m_strID = _T("ProjAppModelChecks");
}

CProjAppModelChecks::~CProjAppModelChecks()
{
}

#ifdef XML_USE_TINYXML

long CProjAppModelChecks::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CProjAppModelChecks::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CProjAppModelChecks::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CProjAppModelChecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CProjAppModelChecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CProjAppModelChecks::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CProjAppModelChecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CProjAppModelChecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CProjAppModelChecks *p = (CProjAppModelChecks*)pObj;

	return TRUE;
}

BOOL CProjAppModelChecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CProjAppModelChecks *p = (CProjAppModelChecks*)pDest;

	return TRUE;
}

CBaseObject* CProjAppModelChecks::Clone()
{
	CProjAppModelChecks *p = new CProjAppModelChecks();
	Copy(p);
	return p;
}

CExBaseObject* CProjAppModelChecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCCheckObjectKey)
	{
		pNew = new CCheckObject();
	}

	return pNew;
}

CExBaseObject* CProjAppModelChecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		pNew = new CCheckObject();
	}

	return pNew;
}

BOOL CProjAppModelChecks::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		return TRUE;
	}

	return FALSE;

}
//////////////////////////////////////////////////////////CVirLoopChecks////////////////////////////////////////////////////////////////////////////////////////////////
CVirLoopChecks::CVirLoopChecks()
{
	m_strName = _T("虚回路描述冲突检查");
	m_strID = _T("VirLoopChecks");
}

CVirLoopChecks::~CVirLoopChecks()
{
}

#ifdef XML_USE_TINYXML

long CVirLoopChecks::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CVirLoopChecks::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CVirLoopChecks::XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseList::XmlWriteChildren( oElement, pXmlRWKeys);
}

#else

long CVirLoopChecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CVirLoopChecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}
long CVirLoopChecks::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

#endif

long CVirLoopChecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CVirLoopChecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CVirLoopChecks *p = (CVirLoopChecks*)pObj;

	return TRUE;
}

BOOL CVirLoopChecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CVirLoopChecks *p = (CVirLoopChecks*)pDest;

	return TRUE;
}

CBaseObject* CVirLoopChecks::Clone()
{
	CVirLoopChecks *p = new CVirLoopChecks();
	Copy(p);
	return p;
}

CExBaseObject* CVirLoopChecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCCheckObjectKey)
	{
		pNew = new CCheckObject();
	}
	return pNew;
}

CExBaseObject* CVirLoopChecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		pNew = new CCheckObject();
	}
	return pNew;
}

BOOL CVirLoopChecks::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////CCheckObject/////////////////////////////////////////////////////////////////////////////////////

CCheckObject::CCheckObject()
{
	m_nChoose = 1;
}

CCheckObject::~CCheckObject()
{
}

#ifdef XML_USE_TINYXML

long CCheckObject::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChoose);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strErrorType);

	return 0;
}
long CCheckObject::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChoose);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strErrorType);

	return 0;
}

#else

long CCheckObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChoose);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strErrorType);
	return 0;
}

long CCheckObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChoose);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strErrorType);
	return 0;
}

#endif

BOOL CCheckObject::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCheckObject *p = (CCheckObject*)pDest;
	p->m_nChoose = m_nChoose;
	p->m_strErrorType = m_strErrorType;

	return TRUE;
}

CBaseObject* CCheckObject::Clone()
{
	CCheckObject *p = new CCheckObject();
	Copy(p);
	return p;
}

BOOL CCheckObject::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CCHECKOBJECT)
	{
		return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////CSchemaCheckObject/////////////////////////////////////////////////////////////////////////////////////

CSchemaCheckObject::CSchemaCheckObject()
{
	m_nChoose = 1;
}

CSchemaCheckObject::~CSchemaCheckObject()
{
}

#ifdef XML_USE_TINYXML

long CSchemaCheckObject::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChoose);
	xml_GetAttibuteValue(pXmlKeys->m_strVertionKey, oNode, m_strVertionType);
	xml_GetAttibuteValue(pXmlKeys->m_strMethodKey, oNode, m_strCheckType);

	return 0;
}
long CSchemaCheckObject::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChoose);
	xml_SetAttributeValue(pXmlKeys->m_strVertionKey, oElement, m_strVertionType);
	xml_SetAttributeValue(pXmlKeys->m_strMethodKey, oElement, m_strCheckType);

	return 0;
}

#else

long CSchemaCheckObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChoose);
	xml_GetAttibuteValue(pXmlKeys->m_strVertionKey, oNode, m_strVertionType);
	xml_GetAttibuteValue(pXmlKeys->m_strMethodKey, oNode, m_strCheckType);
	return 0;
}

long CSchemaCheckObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChoose);
	xml_SetAttributeValue(pXmlKeys->m_strVertionKey, oElement, m_strVertionType);
	xml_SetAttributeValue(pXmlKeys->m_strMethodKey, oElement, m_strCheckType);
	return 0;
}

#endif

BOOL CSchemaCheckObject::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSchemaCheckObject *p = (CSchemaCheckObject*)pDest;
	p->m_nChoose = m_nChoose;
	p->m_strVertionType = m_strVertionType;

	return TRUE;
}

CBaseObject* CSchemaCheckObject::Clone()
{
	CSchemaCheckObject *p = new CSchemaCheckObject();
	Copy(p);
	return p;
}

BOOL CSchemaCheckObject::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_CSCHEMACHECKS)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////CSinglePath/////////////////////////////////////////////////////////////////////////////////////

CSinglePath::CSinglePath()
{
}

CSinglePath::~CSinglePath()
{
}

#ifdef XML_USE_TINYXML

long CSinglePath::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strPathKey, oNode, m_strPath);
	return 0;
}
long CSinglePath::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strPathKey, oElement, m_strPath);
	return 0;
}

#else

long CSinglePath::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strPathKey, oNode, m_strPath);
	return 0;
}

long CSinglePath::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCheckMngrXmlRWKeys *pXmlKeys = (CSclCheckMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strPathKey, oElement, m_strPath);
	return 0;
}

#endif

BOOL CSinglePath::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSinglePath *p = (CSinglePath*)pDest;
	p->m_strPath = m_strPath;

	return TRUE;
}

CBaseObject* CSinglePath::Clone()
{
	CSinglePath *p = new CSinglePath();
	Copy(p);
	return p;
}

BOOL CSinglePath::CanPaste(UINT nClassID)
{
	if (nClassID == SCLCLASSID_SINGLEPATH)
	{
		return TRUE;
	}

	return FALSE;
}
//////////////////////////////////////////////////////////CAddTempsFiles/////////////////////////////////////////////////////////////////////////////////////

CAddTempsFiles::CAddTempsFiles()
{
}

CAddTempsFiles::~CAddTempsFiles()
{
}
//////////////////////////////////////////////////////////CAddTempsFile/////////////////////////////////////////////////////////////////////////////////////

CAddTempsFile::CAddTempsFile()
{
}

CAddTempsFile::~CAddTempsFile()
{
}
//////////////////////////////////////////////////////////CAddTempsDataTypes/////////////////////////////////////////////////////////////////////////////////////

CAddTempsDataTypes::CAddTempsDataTypes()
{
}

CAddTempsDataTypes::~CAddTempsDataTypes()
{
}
//////////////////////////////////////////////////////////CAddTempsElement/////////////////////////////////////////////////////////////////////////////////////

CAddTempsElement::CAddTempsElement()
{
	m_nChoose = 1;
}

CAddTempsElement::~CAddTempsElement()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////