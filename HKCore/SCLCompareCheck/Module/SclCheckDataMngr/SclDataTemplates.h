#pragma once
#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"

//////////////////////////////////////////////////////////DODetail////////////////////////////////////////////////////////////////////////////////////////////////
class CDODetail : public CExBaseObject
{
public:
	CDODetail();
	virtual ~CDODetail();


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_DODETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CDODetailKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};

//////////////////////////////////////////////////////////LNodeType////////////////////////////////////////////////////////////////////////////////////////////////

class CSclLNodeType : public CExBaseList
{
public:
	CSclLNodeType();
	virtual ~CSclLNodeType();


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_LNODETYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CLNodeTypeKey();     }

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


//////////////////////////////////////////////////////////DataTypeTemplates////////////////////////////////////////////////////////////////////////////////////////////////


class CDataTypeTmps : public CExBaseList
{
public:
	CDataTypeTmps();
	virtual ~CDataTypeTmps();

	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_TEMPLATES;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CDataTypeTmpsKey();     }

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

//////////////////////////////////////////////////////////DOType////////////////////////////////////////////////////////////////////////////////////////////////


class CSclDOType : public CExBaseList
{
public:
	CSclDOType();
	virtual ~CSclDOType();


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_DOTYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CDOTypeKey();     }

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


class CDADetail : public CExBaseObject
{
public:
	CDADetail();
	virtual ~CDADetail();

	long m_nObjType;
	CString m_strAddr;
	CString m_strBType;
	CString m_strValKind;
	long m_nCount;
	CString m_strFC;
	long m_nTrgOp;
	CString m_strValue;
	long m_nSGroup;


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_DADETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CDADetailKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};


//////////////////////////////////////////////////////////DAType////////////////////////////////////////////////////////////////////////////////////////////////


class CSclDAType : public CExBaseList
{
public:
	CSclDAType();
	virtual ~CSclDAType();


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_DATYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CDATypeKey();     }

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


class CBDADetail : public CExBaseObject
{
public:
	CBDADetail();
	virtual ~CBDADetail();

	CString m_strAddr;
	CString m_strBType;
	CString m_strValKind;
	long m_nCount;
	CString m_strValue;
	long m_nSGroup;


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_BDADETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CBDADetailKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};


//////////////////////////////////////////////////////////EnumType////////////////////////////////////////////////////////////////////////////////////////////////


class CSclEnumType : public CExBaseList
{
public:
	CSclEnumType();
	virtual ~CSclEnumType();


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_ENUMTYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CEnumTypeKey();     }

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



class CEnumVal : public CExBaseObject
{
public:
	CEnumVal();
	virtual ~CEnumVal();

	long m_nOrd;


	//重载函数
public:
	virtual UINT GetClassID() {    return DATATYPECLASSID_ENUMDETAIL;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CEnumValKey();     }

#ifdef XML_USE_TINYXML

	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);

#else

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

#endif
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////