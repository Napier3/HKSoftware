#ifndef INTERFACE_METHODS_DEFINE
#define INTERFACE_METHODS_DEFINE

//#include "..\..\Module\AtlAPI\XMLApi.h"

//接口通用方法 宏定义
#define NEW_CCOMOBJECT(class_name,interface_name) \
	static class_name* _new_##class_name () \
	{ \
	CComObject < class_name > *p##class_name = NULL;\
	CComObject < class_name > :: CreateInstance( &p##class_name);\
	return p##class_name;\
	} \

#define NEW_CCOMOBJECT_COPY(class_name,interface_name) \
	static class_name* _new_##class_name (class_name* pSrc) \
	{ \
		class_name *p##class_name = _new_##class_name();\
		p##class_name->_Copy(pSrc);\
		return p##class_name; \
	} \

#define NEW_IDISPATCH(class_name,interface_name) \
	static IDispatch* _new_IDispatch() \
	{ \
		IDispatch* pTemp = NULL; \
		class_name *p##class_name = _new_##class_name(); \
		ATLASSERT(p##class_name != NULL); \
		if(p##class_name != NULL) \
			p##class_name -> QueryInterface (IID_IDispatch,(void**) &pTemp); \
		return pTemp; \
	} \

#define QUERY_IDISPATCH(class_name,interface_name)\
	IDispatch* _QueryIDispatch(){IDispatch *pTemp = NULL;QueryInterface(IID_IDispatch,(void**)&pTemp);return pTemp;}\

#define DECLARE_CCOMOBJECT_METHODS(class_name,interface_name) \
	NEW_CCOMOBJECT(class_name,interface_name) \
	NEW_IDISPATCH(class_name,interface_name) \
	QUERY_IDISPATCH(class_name,interface_name) \

//FormIDispatch函数宏,FROM_IDISPATCHEX为未定义_ATL_DEBUG_INTERFACE_使用
#define FROM_IDISPATCH(class_name,interface_name)\
	static class_name* FromIDispatch(IDispatch* pIDisp)\
	{\
		if(pIDisp == NULL)\
			return NULL;\
			class_name *pValue= NULL;\
			interface_name *pIValue = NULL;\
			pIDisp -> QueryInterface(IID_##interface_name,(void**) &pIValue);\
		if(pIValue == NULL)\
			return NULL;\
		_QIThunk *pThunk = (_QIThunk*) pIValue;\
		pValue = (class_name*)(interface_name*) pThunk -> m_pUnk;\
		pIValue->Release();\
		return pValue;\
	}\

#define FROM_IDISPATCH_EX(class_name,interface_name)\
	static class_name* FromIDispatch(IDispatch* pIDisp)\
	{\
	if(pIDisp == NULL) \
	return NULL; \
	class_name *pValue= NULL;\
	interface_name *pIValue = NULL;\
	pIDisp -> QueryInterface(IID_##interface_name,(void**) &pIValue); \
	if(pIValue == NULL) \
	return NULL; \
	pValue = (class_name*) pIValue; \
	pIValue->Release(); \
	return pValue; \
	}\

//集合类相关读写方法
#define INITVALUENAME(class_name)\
	class_name* pLongData = NULL;\
	CDataTypes* pDataTypes = CDataTypes::FromIDispatch(pIDataTypes);\
	CDataType* pDataType = NULL;\
	int nCount = m_listChild.GetCount();\
	int nTypes = pDataTypes->m_listChild.GetCount();\
	for (int i=0;i<nCount;i++)\
	{	\
		pLongData = m_listChild.GetAtIndex(i);\
		for (int j=0;j<nTypes;j++)\
		{\
			pDataType = pDataTypes->m_listChild.GetAtIndex(i);\
			if (pDataType!=NULL)\
			{\
				if (pLongData->m_strID==pDataType->m_strID)\
				{\
					pLongData->m_strValueName = pDataType->m_strName;\
					break;\
				}\
			}\
		}\
	}\

#define  SETVALUESBYDATAS(class_name,para_name)\
	class_name* pLongData = NULL;\
	int nCount = m_listChild.GetCount();\
	class_name* pLongDataEx = NULL;\
	class_name##s* pLongDatasEx = NULL;\
	pLongDatasEx = FromIDispatch(para_name);\
	int nCountEx = pLongDatasEx->m_listChild.GetCount();\
	for (int i=0;i<nCount;i++)\
	{\
		pLongData = m_listChild.GetAtIndex(i);\
		for (int j =0;j<nCountEx;j++)\
		{\
			pLongDataEx = pLongDatasEx->m_listChild.GetAtIndex(i);\
			if (pLongDataEx!=NULL)\
			{\
				if (pLongData->m_strID==pLongDataEx->m_strID)\
				{\
					pLongData->m_strValue=pLongDataEx->m_strValue;\
					break;\
				}\
			}\
		}\
	}\

#define SETVALUESBYEQUATION(class_name,pIEquation)\
	CWEquationBuffer* pEquationBuf = CEquation::FromIDispatch(pIEquation);\
	CWEqtnKey* pEqtnKey = NULL;\
	int nCountEqt = pEquationBuf->GetKeyCount();\
	class_name* pLongData = NULL;\
	int nCount = m_listChild.GetCount();\
	for (int j=0;j<nCountEqt;j++)\
	{\
		pEqtnKey = pEquationBuf->FindEquationKey(j);\
		pLongData = m_listChild.FindByID(pEqtnKey->m_strKeyName);\
		if (pLongData!=NULL)\
		{\
			pLongData->m_strValue = pEqtnKey->m_strKeyValue.Copy();\
		}\
	}\

#define SETVALUESBYSTRING(para_name)\
	LONG n;\
	CComObject<CEquation>* pEquation = NULL;\
	CComObject<CEquation>::CreateInstance(&pEquation);\
	pEquation->SetEquation(para_name,&n);\
	IDispatchPtr pIDisp=NULL;\
	pEquation->QueryInterface(IID_IDispatch,(void**)&pIDisp);\
	SetValuesByEquation(pIDisp);\

#define GETITEM(class_name,pata1,para2)\
	class_name* pvalue = NULL;\
	pvalue = m_listChild.GetAtIndex(pata1);\
	pvalue->QueryInterface(IID_IDispatch,(void**)para2);\

#define FINDBYID(class_name,pata1,para2)\
		class_name *pData = NULL;\
		pData = m_listChild.FindByID(pata1);\
	if (pData != NULL)\
	{\
		*para2 = pData->_QueryIDispatch();\
	}\
	else\
	{\
		*para2 = NULL;\
	}\

#define FINDBYNAME(class_name,pata1,para2)\
	class_name *pData = NULL;\
	pData = m_listChild.FindByName(pata1);\
	if (pData != NULL)\
	{\
	*para2 = pData->_QueryIDispatch();\
	}\
	else\
	{\
	*para2 = NULL;\
	}\

#define ADDNEW(class_name,para)\
	class_name *pData = class_name::_new_##class_name();\
	if (pData != NULL)\
	{\
		*para = pData->_QueryIDispatch();\
		m_listChild.AddTail(pData);\
	}\

#define DELETEELEMENT(para1,para2)\
	m_listChild.Delete(para1, para2);\

#define DELETEALL\
	m_listChild.DeleteAll();\

//XML相关读写方法的声明
#define CREATE_NEW_CHILD(class_name,xmlkey_type) \
	IDispatch* class_name##::_CreateNewChild(MSXML::IXMLDOMNodePtr &oNode,xmlkey_type *pXmlRWKeys);\

#define XML_READ_OWN(class_name,xmlkey_type) \
	long class_name##::_XmlReadOwn(const MSXML::IXMLDOMNodePtr &oNode,xmlkey_type *pXmlRWKeys);\

#define XML_READ(class_name,xmlkey_type) \
	long class_name##::_XmlRead(const MSXML::IXMLDOMNodePtr &oNode,xmlkey_type *pXmlRWKeys) { \
	_XmlReadOwn(oNode, pXmlRWKeys); \
	MSXML::IXMLDOMNodeListPtr oChildren = oNode->GetchildNodes(); \
	_XmlReadChildren(oChildren, pXmlRWKeys); \
	return 0; \
	} \

#define XML_READ_EX(class_name,xmlkey_type) \
	long class_name##::_XmlRead(const MSXML::IXMLDOMNodePtr &oNode,xmlkey_type *pXmlRWKeys); \

#define XML_READ_CHILDREN(class_name,xmlkey_type) \
	long class_name##::_XmlReadChildren(const MSXML::IXMLDOMNodeListPtr &oNodes,xmlkey_type *pXmlRWKeys);\

#define XML_WRITE_OWN(class_name,xmlkey_type) \
	long class_name##::_XmlWriteOwn(MSXML::IXMLDOMElementPtr &oNode,xmlkey_type *pXmlRWKeys);\

#define XML_WRITE_CHILDREN(class_name,xmlkey_type) \
	long class_name##::_XmlWriteChildren(MSXML::IXMLDOMElementPtr &oNodes, xmlkey_type *pXmlRWKeys);\

#define XML_WRITE(class_name,xmlkey_type) \
	long class_name##::_XmlWrite(MSXML::IXMLDOMElementPtr &oNode,xmlkey_type *pXmlRWKeys){ \
	_XmlWriteOwn(oNode, pXmlRWKeys); \
	_XmlWriteChildren(oNode, pXmlRWKeys); \
	return 0; \
	} \

#define XML_WRITE_EX(class_name,xmlkey_type) \
	long class_name##::_XmlWrite(MSXML::IXMLDOMElementPtr &oNode,xmlkey_type *pXmlRWKeys); \


#define XML_READ_CHILDREN_CODE(oNodes,pXmlRWKeys)\
	long nCount = oNodes->Getlength();\
	long nIndex = 0;\
	IDispatch *pNew = NULL;\
	MSXML::IXMLDOMNodePtr oNode = NULL;\
	for (nIndex=0; nIndex<nCount; nIndex++)\
	{\
		oNode = oNodes->Getitem(nIndex);\
		pNew = _CreateNewChild(oNode,pXmlRWKeys);\
	}\

#define XML_CREATE_NEW_CHILD_CODE(child_name,DataElementKey,para1,para2)\
	_bstr_t strNodeName;\
	strNodeName = para1->GetnodeName();\
	IDispatch* pNew = NULL;\
	CComBSTR bstrNodeName = strNodeName.GetBSTR();\
	if (bstrNodeName == DataElementKey)\
	{\
	child_name *pVal = child_name::_new_##child_name();\
		pVal->_XmlRead(para1, para2);\
		if(m_listChild.FindByID(pVal->m_strID)==NULL)\
		m_listChild.AddTail(pVal);\
		else\
		delete pVal;\
	}\
	return pNew;\

#define  XML_WRITE_CHILDREN_CODE(child_name,ChildrenElementKey,para1,para2)\
	MSXML::IXMLDOMElementPtr oData;\
	int nCount = m_listChild.GetCount();\
	child_name* pValue = NULL;\
	MSXML::IXMLDOMDocumentPtr oXMLDoc = para2->m_oXMLDoc;\
	for (int i=0;i<nCount;i++)\
	{\
	pValue = m_listChild.GetAtIndex(i);\
	oData = oXMLDoc->createElement(_bstr_t(ChildrenElementKey));\
	para1->appendChild(oData);\
	pValue->_XmlWrite(oData,para2);\
	}\

#define XML_INTERFACE_WRITE(pIXMLElement,pIXMLKeys)\
	MSXML::IXMLDOMElementPtr pIElement;\
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMElement),(void**)&pIElement);\
	CDataXMLRWKeys* pXmlKeys = NULL;\
	pXmlKeys = CDataXMLRWKeys::FromIDispatch(pIXMLKeys);\
	_XmlWrite(pIElement,pXmlKeys);\

#define XML_INTERFACE_READ(pIXMLElement,pIXMLKeys)\
	MSXML::IXMLDOMNodePtr pIElement;\
	pIXMLElement->QueryInterface(__uuidof(MSXML::IXMLDOMNodePtr),(void**)&pIElement);\
	CDataXMLRWKeys* pXmlKeys = NULL;\
	pXmlKeys = CDataXMLRWKeys::FromIDispatch(pIXMLKeys);\
	_XmlRead(pIElement,pXmlKeys);\

#define DECLARE_XML_METHODS(class_name,xmlkey_type) \
	CREATE_NEW_CHILD(class_name,xmlkey_type) \
	XML_READ_OWN(class_name,xmlkey_type) \
	XML_READ(class_name,xmlkey_type) \
	XML_READ_CHILDREN(class_name,xmlkey_type) \
	XML_WRITE_OWN(class_name,xmlkey_type) \
	XML_WRITE_CHILDREN(class_name,xmlkey_type) \
	XML_WRITE(class_name,xmlkey_type) \

#define DECLARE_XML_METHODS_EX(class_name,xmlkey_type) \
	CREATE_NEW_CHILD(class_name,xmlkey_type) \
	XML_READ_OWN(class_name,xmlkey_type) \
	XML_READ_EX(class_name,xmlkey_type) \
	XML_READ_CHILDREN(class_name,xmlkey_type) \
	XML_WRITE_OWN(class_name,xmlkey_type) \
	XML_WRITE_CHILDREN(class_name,xmlkey_type) \
	XML_WRITE_EX(class_name,xmlkey_type) \



//CGBaseObject头文件宏定义
#define DECLARE_CGBBASEOBJECT_METHODS(class_name)\
	virtual void _Free(void);\
	class_name* _Clone(void);\
	virtual long _Copy(CGbBaseObject* pDesObj);\
	virtual long _IsEqual(CGbBaseObject* pObj);

#define DELCARE_CGBBASEOBJECT_SERIALIZE_METHODS()\
	virtual long _BinaryserializeOwn(SystemTool::IBinarySerialBufferPtr& oBinaryBuff);\
	virtual long _XmlReadOwn(const MSXML2::IXMLDOMNodePtr& oNode);\
	virtual long _XmlWriteOwn(MSXML2::IXMLDOMNodePtr& oNode);\

#define DELCARE_CGBBASEOBJECT_SERIALIZE_METHODS_EX()\
	virtual long _BinarySerialize(SystemTool::IBinarySerialBufferPtr &oBinaryBuff);\
	virtual long _BinarySerializeOwn(SystemTool::IBinarySerialBufferPtr& oBinaryBuff);\
	virtual long _BinarySerializeChildren(SystemTool::IBinarySerialBufferPtr &oBinaryBuff);\
	virtual long _XMLRead(MSXML2::IXMLDOMNodePtr &oNode);\
	virtual long _XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode);\
	virtual long _XMLReadChildren(MSXML2::IXMLDOMNodeListPtr &oNodes);\
	virtual long _XMLWrite(MSXML2::IXMLDOMNodePtr &oNode);\
	virtual long _XmlWriteOwn(MSXML2::IXMLDOMNodePtr &oNode);\
	virtual long _XMLWriteChildren(MSXML2::IXMLDOMNodePtr &oNode);\

//创建子对象函数声明
#define DECLARE_CREATENEWCHILDOBJECT_METHODS()\
virtual CGbBaseObject* _CreateNewChildObject(const CComBSTR &strClassID, BOOL &bAddToTail);\
virtual IGbNode* _CreateNewChildObject(long nClassID, BOOL &bAddToTail);\


//基本函数实现宏
#define CLONEINTERFACEMETHODS(class_name,Idispatch,ret)\
	class_name *pObject = NULL;\
	pObject = _Clone();\
	if(pObject != NULL)\
		*Idispatch = pObject->_QueryIDispatch();\
	else\
		*Idispatch = NULL;\

#define COPYINTERFACEMETHODS(class_name,Idispatch,ret)\
	class_name* pObject = NULL;\
	pObject = FromIDispatch(Idispatch);\
	ATLASSERT(pObject!=NULL);\
	_Copy(pObject);\

#define ISEQUALINTERFACEMETHODS(class_name,Idispatch,ret)\
	class_name* pObject = NULL;\
	pObject = FromIDispatch(Idispatch);\
	ATLASSERT(pObject != NULL);\
	if(pObject != NULL)\
		*ret = _IsEqual(pObject);\
	else\
		*ret = 0;\

#endif