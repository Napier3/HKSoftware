#pragma once
#include "SclCheckMngrGlobal.h"

//////////////////////////////////////////////////////////CSclCheckObjectsSet////////////////////////////////////////////////////////////////////////////////////////////////
class CSclCheckObjectsSet : public CExBaseList
{
public:
	CSclCheckObjectsSet();
	virtual ~CSclCheckObjectsSet();

public:

	virtual UINT GetClassID()	{	return SCLCLASSID_CCHECKOBJECTSSET;	}

	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSclCheckObjectsSetKey();     }


	BOOL OpenCheckConfigFile (CString strFile = "");
	BOOL SaveCheckConfigFile();

#ifdef XML_USE_TINYXML

	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();
	//初始化链接引用对象
};

//////////////////////////////////////////////////////////CCheckPaths////////////////////////////////////////////////////////////////////////////////////////////////
class CCheckPaths : public CExBaseList
{
public:
	CCheckPaths();
	virtual ~CCheckPaths();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CCHECKPATHS;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CCheckPathsKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
};
//////////////////////////////////////////////////////////CSchemaChecks////////////////////////////////////////////////////////////////////////////////////////////////
class CSchemaChecks : public CExBaseList
{
public:
	CSchemaChecks();
	virtual ~CSchemaChecks();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCHEMACHECKS;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSchemaChecksKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
};
//////////////////////////////////////////////////////////CDLT860ModelChecks////////////////////////////////////////////////////////////////////////////////////////////////
class CDLT860ModelChecks : public CExBaseList
{
public:
	CDLT860ModelChecks();
	virtual ~CDLT860ModelChecks();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CDLT860MODELCHECKS;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDLT860ModelChecksKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

};
//////////////////////////////////////////////////////////CProjAppModelChecks////////////////////////////////////////////////////////////////////////////////////////////////
class CProjAppModelChecks : public CExBaseList
{
public:
	CProjAppModelChecks();
	virtual ~CProjAppModelChecks();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CPROJAPPMODELCHECKS;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CProjAppModelChecksKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

};
//////////////////////////////////////////////////////////CVirLoopChecks////////////////////////////////////////////////////////////////////////////////////////////////
class CVirLoopChecks : public CExBaseList
{
public:
	CVirLoopChecks();
	virtual ~CVirLoopChecks();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CVIRLOOPCHECKS;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CVirLoopChecksKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

};
//////////////////////////////////////////////////////////CCheckObject////////////////////////////////////////////////////////////////////////////////////////////////
class CCheckObject : public CExBaseList
{
public:
	CCheckObject();
	virtual ~CCheckObject();
	CString m_strErrorType;
	long m_nChoose;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CCHECKOBJECT;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CCheckObjectKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
};
//////////////////////////////////////////////////////////CSchemaCheckObject////////////////////////////////////////////////////////////////////////////////////////////////
class CSchemaCheckObject : public CExBaseList
{
public:
	CSchemaCheckObject();
	virtual ~CSchemaCheckObject();
	CString m_strVertionType;
	CString m_strCheckType;
	long m_nChoose;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_SCHEMACCHECKOBJECT;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSchemaObjectKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
};
//////////////////////////////////////////////////////////CSinglePath////////////////////////////////////////////////////////////////////////////////////////////////
class CSinglePath : public CExBaseList
{
public:
	CSinglePath();
	virtual ~CSinglePath();
	CString m_strPath;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_SINGLEPATH;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSinglePathKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
};
//////////////////////////////////////////////////////////CAddTempsFiles////////////////////////////////////////////////////////////////////////////////////////////////
class CAddTempsFiles : public CExBaseList
{
public:
	CAddTempsFiles();
	virtual ~CAddTempsFiles();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_ADDTEMPLATESFILES;   }
};
//////////////////////////////////////////////////////////CAddTempsFile////////////////////////////////////////////////////////////////////////////////////////////////
class CAddTempsFile : public CExBaseList
{
public:

	CAddTempsFile();
	virtual ~CAddTempsFile();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_ADDTEMPLATESFILE;   }
};
//////////////////////////////////////////////////////////CAddTempsDataTypes////////////////////////////////////////////////////////////////////////////////////////////////
class CAddTempsDataTypes : public CExBaseList
{
public:
	CAddTempsDataTypes();
	virtual ~CAddTempsDataTypes();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_ADDTEMPLATESDATATYPES;   }
};
//////////////////////////////////////////////////////////CAddTempsElement////////////////////////////////////////////////////////////////////////////////////////////////
class CAddTempsElement : public CExBaseList
{
public:
	long m_nChoose;

	CAddTempsElement();
	virtual ~CAddTempsElement();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_ADDTEMPLATESELEMENT;   }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////