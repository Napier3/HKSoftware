#pragma once
#include "SclCheckMngrGlobal.h"
#include "../../../Module/xml/tinyXml/tinyxml.h"

//////////////////////////////////////////////////////////TemplateFile1396////////////////////////////////////////////////////////////////////////////////////////////////
class CTemplateFile1396 : public CExBaseList
{
public:
	CTemplateFile1396();
	virtual ~CTemplateFile1396();

public:

	virtual UINT GetClassID()	{	return SCLCLASSID_CSCLFILEROOT;	}

	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSCLKey();     }


	BOOL OpenTemplateFile1396(const CString &strFile);
	BOOL SaveTemplateFile1396();

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();
	//初始化链接引用对象
};
//////////////////////////////////////////////////////////DataTypeTemplates////////////////////////////////////////////////////////////////////////////////////////////////


class CDataTypeTemplates : public CExBaseList
{
public:
	CDataTypeTemplates();
	virtual ~CDataTypeTemplates();

	BOOL m_bUTF8;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILETEMPLATES;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDataTypeTmpsKey();     }

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
//////////////////////////////////////////////////////////LNodeTypeT////////////////////////////////////////////////////////////////////////////////////////////////

class CLNodeTypeT : public CExBaseList
{
public:
	CLNodeTypeT();
	virtual ~CLNodeTypeT();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILELNODETYPET;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CLNodeTypeTKey();     }

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
//////////////////////////////////////////////////////////DOValueT////////////////////////////////////////////////////////////////////////////////////////////////
class CDOValueT : public CExBaseObject
{
public:
	CDOValueT();
	virtual ~CDOValueT();
	CString m_strMop;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_DOTVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDOTValueKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////DOType////////////////////////////////////////////////////////////////////////////////////////////////


class CDOType : public CExBaseList
{
public:
	CDOType();
	virtual ~CDOType();

	CString m_strErrorPos;
	CString m_strPrivateMSG;

	BOOL m_bUTF8;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILEDOTYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDOTypeKey();     }

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
//////////////////////////////////////////////////////////DADetail////////////////////////////////////////////////////////////////////////////////////////////////
class CDAValue : public CExBaseObject
{
public:
	CDAValue();
	virtual ~CDAValue();

	CString m_strDchg;
	CString m_strQchg;
	CString m_strBType;
	CString m_strFC;
	CString m_strValue;
	CString m_strErrorPos;

	BOOL m_bUTF8;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_DADETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDADValueKey();     }

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////SDOValue////////////////////////////////////////////////////////////////////////////////////////////////
class CSDOValue : public CExBaseObject
{
public:
	CSDOValue();
	virtual ~CSDOValue();

	CString m_strErrorPos;
	BOOL m_bUTF8;

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_SDODETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSDOValueKey();     }

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////DAType////////////////////////////////////////////////////////////////////////////////////////////////
class CDAType : public CExBaseList
{
public:
	CDAType();
	virtual ~CDAType();

	CString m_strErrorPos;
	CString m_strPrivateMSG;
	BOOL m_bUTF8;
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILEDATYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDATypeKey();     }

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
//////////////////////////////////////////////////////////BDADetail////////////////////////////////////////////////////////////////////////////////////////////////
class CBDAValue : public CExBaseObject
{
public:
	CBDAValue();
	virtual ~CBDAValue();
	CString m_strBType;

	CString m_strErrorPos;
	BOOL m_bUTF8;
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_BDADETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CBDAValueKey();     }

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////EnumType////////////////////////////////////////////////////////////////////////////////////////////////
class CEnumType : public CExBaseList
{
public:
	CEnumType();
	virtual ~CEnumType();

	CString m_strErrorPos;
	CString m_strPrivateMSG;
	BOOL m_bUTF8;
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILEENUMTYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CEnumTypeKey();     }

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
//////////////////////////////////////////////////////////EnumVal////////////////////////////////////////////////////////////////////////////////////////////////

class CEnumValue : public CExBaseObject
{
public:
	CEnumValue();
	virtual ~CEnumValue();

	CString m_strErrorPos;
	BOOL m_bUTF8;
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_ENUMDETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CEnumValKey();     }

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////LDevice////////////////////////////////////////////////////////////////////////////////////////////////
class CLDevice_Scl : public CExBaseObject
{
public:
	CLDevice_Scl();
	virtual ~CLDevice_Scl();
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_LDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CLDeviceKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////DataSet////////////////////////////////////////////////////////////////////////////////////////////////
class CDataSet_Scl : public CExBaseObject
{
public:
	CString m_strLcbname;
	CString m_strBrcbname;

	CDataSet_Scl();
	virtual ~CDataSet_Scl();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_DATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDataSetKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////CDC////////////////////////////////////////////////////////////////////////////////////////////////
class CCDC_Scl : public CExBaseObject
{
public:
	CCDC_Scl();
	virtual ~CCDC_Scl();

	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_CDC;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CCDCKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
//////////////////////////////////////////////////////////CSCLTemplates////////////////////////////////////////////////////////////////////////////////////////////////
class CSCLTemplates : public CExBaseList
{
public:
	CSCLTemplates();
	virtual ~CSCLTemplates();

	BOOL m_bUTF8;

public:

	virtual UINT GetClassID()	{	return SCLCLASSID_CSCLFILEROOT;	}

	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CSCLKey();     }


	BOOL OpenSclTemplatesFile(const CString &strFile);
	void OpenSclTemplatesFileByTinyRoot(TiXmlElement* pDocRoot);
	BOOL SaveSclTemplatesFile();

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
//////////////////////////////////////////////////////////LNodeType////////////////////////////////////////////////////////////////////////////////////////////////

class CLNodeType : public CExBaseList
{
public:
	CString m_strLnClass;
	CLNodeType();
	virtual ~CLNodeType();
	CString m_strErrorPos;
	CString m_strPrivateMSG;

	BOOL m_bUTF8;


	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILELNODETYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CLNodeTypeKey();     }

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
//////////////////////////////////////////////////////////DOValue////////////////////////////////////////////////////////////////////////////////////////////////
class CDOValue : public CExBaseObject
{
public:
	CString m_strType;
	CString m_strTransient;
	CDOValue();
	virtual ~CDOValue();
	CString m_strErrorPos;

	BOOL m_bUTF8;
	//重载函数
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CSCLFILE_DODETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CSclCheckMngrXmlRWKeys::CDOValueKey();     }

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////