// DataTypeXMLRWKeys.h : CDataTypeXMLRWKeys ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CDataTypeXMLRWKeys

class ATL_NO_VTABLE CDataTypeXMLRWKeys :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataTypeXMLRWKeys, &CLSID_DataTypeXMLRWKeys>,
	public IDispatchImpl<IDataTypeXMLRWKeys, &IID_IDataTypeXMLRWKeys, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataTypeXMLRWKeys()
	{
		m_strDataTypesElementKey = L"datatypes";
		m_strDataTypeElementKey = L"datatype";
		m_strValueElementKey = L"value";
		m_strDataTypeNameKey = L"name";
		m_strDataTypeIDKey = L"id";
		m_strValueNameKey = L"name";
		m_strValueIDKey = L"id";
		m_strValueIndexKey = L"index";
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATATYPEXMLRWKEYS)


BEGIN_COM_MAP(CDataTypeXMLRWKeys)
	COM_INTERFACE_ENTRY(IDataTypeXMLRWKeys)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	DECLARE_CCOMOBJECT_METHODS(CDataTypeXMLRWKeys,IDataTypeXMLRWKeys)

#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CDataTypeXMLRWKeys,IDataTypeXMLRWKeys)
#else
	FROM_IDISPATCH_EX(CDataTypeXMLRWKeys,IDataTypeXMLRWKeys)
#endif

//	static CDataTypeXMLRWKeys* FromIDispatch(IDispatch* pIDisp)
//	{
//		if (pIDisp==NULL)
//		{
//			return NULL;
//		}
//		CDataTypeXMLRWKeys* pXmlKeys = NULL;
//		IDataTypeXMLRWKeys* pIValueXmlKeys = NULL;
//
//		pIDisp->QueryInterface(IID_IDataTypeXMLRWKeys,(void**)&pIValueXmlKeys);
//#ifdef _ATL_DEBUG_INTERFACES
//		_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
//		pXmlKeys = (CDataTypeXMLRWKeys*)pThunk->m_pUnk;
//#else
//		pXmlKeys = (CValueXMLRWKeys*)pIValueXmlKeys;
//#endif
//		pIValueXmlKeys->Release();
//		return pXmlKeys;
//	}
public:
	CComBSTR m_strDataTypesElementKey;
	CComBSTR m_strDataTypeElementKey;
	CComBSTR m_strValueElementKey;
	CComBSTR m_strDataTypeNameKey;
	CComBSTR m_strDataTypeIDKey;
	CComBSTR m_strValueNameKey;
	CComBSTR m_strValueIDKey;
	CComBSTR m_strValueIndexKey;
	MSXML::IXMLDOMDocumentPtr m_DocPtr;
public:
	
	STDMETHOD(get_DataTypesElementKey)(BSTR* pVal);
	STDMETHOD(put_DataTypesElementKey)(BSTR newVal);
	STDMETHOD(get_DataTypeElementKey)(BSTR* pVal);
	STDMETHOD(put_DataTypeElementKey)(BSTR newVal);
	STDMETHOD(get_ValueElementKey)(BSTR* pVal);
	STDMETHOD(put_ValueElementKey)(BSTR newVal);
	STDMETHOD(get_DataTypeNameKey)(BSTR* pVal);
	STDMETHOD(put_DataTypeNameKey)(BSTR newVal);
	STDMETHOD(get_DataTypeIDKey)(BSTR* pVal);
	STDMETHOD(put_DataTypeIDKey)(BSTR newVal);
	STDMETHOD(get_ValueNameKey)(BSTR* pVal);
	STDMETHOD(put_ValueNameKey)(BSTR newVal);
	STDMETHOD(get_ValueIDKey)(BSTR* pVal);
	STDMETHOD(put_ValueIDKey)(BSTR newVal);
	STDMETHOD(get_ValueIndexKey)(BSTR* pVal);
	STDMETHOD(put_ValueIndexKey)(BSTR newVal);
	STDMETHOD(get_DocPtr)(IDispatch** pVal);
	STDMETHOD(put_DocPtr)(IDispatch* newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(DataTypeXMLRWKeys), CDataTypeXMLRWKeys)
