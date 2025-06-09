// DataXMLRWKeys.h : CDataXMLRWKeys 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CDataXMLRWKeys

class ATL_NO_VTABLE CDataXMLRWKeys :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataXMLRWKeys, &CLSID_DataXMLRWKeys>,
	public IDispatchImpl<IDataXMLRWKeys, &IID_IDataXMLRWKeys, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataXMLRWKeys()
	{
		m_strNameKey = L"name";
		m_strIDKey = L"id";
		m_strUnitKey = L"unit";
		m_strValueKey = L"value";
		m_strValueNameKey = L"valuename";
		m_strDefaultValueKey = L"default";
		m_strScriptKey = L"script";
		m_strDataTypeIDKey = L"datatype";
		m_strMessageKey = L"message";
		m_strTypeKey = L"type";
		m_strShowKey = L"show";
		m_strEnableKey = L"enable";
		m_strReservedKey = L"reserved";
		m_strReserved2Key = L"reserved2";
		m_strFormatKey = L"format";
		m_strRemarkKey = L"remark";
		m_strDataElementKey = L"data";
		m_strDatasElementKey = L"datas";
		m_strDatasNameAttrKey = L"name";
		m_strDatasIDAttrKey = L"id";
		m_strDatasMngrElementKey = L"datasmngr";
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATAXMLRWKEYS)


BEGIN_COM_MAP(CDataXMLRWKeys)
	COM_INTERFACE_ENTRY(IDataXMLRWKeys)
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

	static CDataXMLRWKeys* FromIDispatch(IDispatch* pIDisp)
	{
		if (pIDisp==NULL)
		{
			return NULL;
		}
		CDataXMLRWKeys* pXmlKeys = NULL;
		IDataXMLRWKeys* pIValueXmlKeys = NULL;

		pIDisp->QueryInterface(IID_IDataXMLRWKeys,(void**)&pIValueXmlKeys);
		ATLASSERT(pIValueXmlKeys!=NULL);

#ifdef _ATL_DEBUG_INTERFACES
		_QIThunk* pThunk = (_QIThunk*)pIValueXmlKeys;
		pXmlKeys = (CDataXMLRWKeys*)pThunk->m_pUnk;
#else
		pXmlKeys = (CDataXMLRWKeys*)pIValueXmlKeys;
#endif
		pIValueXmlKeys->Release();
		return pXmlKeys;
	}
public:
	CComBSTR m_strNameKey;
	CComBSTR m_strIDKey;
	CComBSTR m_strUnitKey;
	CComBSTR m_strValueKey;
	CComBSTR m_strValueNameKey;
	CComBSTR m_strDefaultValueKey;
	CComBSTR m_strScriptKey;
	CComBSTR m_strDataTypeIDKey;
	CComBSTR m_strMessageKey;
	CComBSTR m_strTypeKey;
	CComBSTR m_strShowKey;
	CComBSTR m_strEnableKey;
	CComBSTR m_strReservedKey;
	CComBSTR m_strReserved2Key;
	CComBSTR m_strFormatKey;
	CComBSTR m_strRemarkKey;
	CComBSTR m_strDataElementKey;
	CComBSTR m_strDatasElementKey;
	CComBSTR m_strDatasNameAttrKey;
	CComBSTR m_strDatasIDAttrKey;
	CComBSTR m_strDatasMngrElementKey;
	MSXML::IXMLDOMDocumentPtr m_oXMLDoc;

	STDMETHOD(get_NameKey)(BSTR* pVal);
	STDMETHOD(put_NameKey)(BSTR newVal);
	STDMETHOD(get_IDKey)(BSTR* pVal);
	STDMETHOD(put_IDKey)(BSTR newVal);
	STDMETHOD(get_UnitKey)(BSTR* pVal);
	STDMETHOD(put_UnitKey)(BSTR newVal);
	STDMETHOD(get_ValueKey)(BSTR* pVal);
	STDMETHOD(put_ValueKey)(BSTR newVal);
	STDMETHOD(get_ValueNameKey)(BSTR* pVal);
	STDMETHOD(put_ValueNameKey)(BSTR newVal);
	STDMETHOD(get_DefaultValueKey)(BSTR* pVal);
	STDMETHOD(put_DefaultValueKey)(BSTR newVal);
	STDMETHOD(get_ScriptKey)(BSTR* pVal);
	STDMETHOD(put_ScriptKey)(BSTR newVal);
	STDMETHOD(get_DataTypeIDKey)(BSTR* pVal);
	STDMETHOD(put_DataTypeIDKey)(BSTR newVal);
	STDMETHOD(get_MessageKey)(BSTR* pVal);
	STDMETHOD(put_MessageKey)(BSTR newVal);
	STDMETHOD(get_TypeKey)(BSTR* pVal);
	STDMETHOD(put_TypeKey)(BSTR newVal);
	STDMETHOD(get_ShowKey)(BSTR* pVal);
	STDMETHOD(put_ShowKey)(BSTR newVal);
	STDMETHOD(get_EnableKey)(BSTR* pVal);
	STDMETHOD(put_EnableKey)(BSTR newVal);
	STDMETHOD(get_ReservedKey)(BSTR* pVal);
	STDMETHOD(put_ReservedKey)(BSTR newVal);
	STDMETHOD(get_Reserved2Key)(BSTR* pVal);
	STDMETHOD(put_Reserved2Key)(BSTR newVal);
	STDMETHOD(get_FormatKey)(BSTR* pVal);
	STDMETHOD(put_FormatKey)(BSTR newVal);
	STDMETHOD(get_DataElementKey)(BSTR* pVal);
	STDMETHOD(put_DataElementKey)(BSTR newVal);
	STDMETHOD(get_DatasElementKey)(BSTR* pVal);
	STDMETHOD(put_DatasElementKey)(BSTR newVal);
	STDMETHOD(get_DatasNameAttrKey)(BSTR* pVal);
	STDMETHOD(put_DatasNameAttrKey)(BSTR newVal);
	STDMETHOD(get_DatasIDAttrKey)(BSTR* pVal);
	STDMETHOD(put_DatasIDAttrKey)(BSTR newVal);
	STDMETHOD(get_DatasMngrElementKey)(BSTR* pVal);
	STDMETHOD(put_DatasMngrElementKey)(BSTR newVal);

	STDMETHOD(get_DocPtr)(IDispatch** pVal);
	STDMETHOD(put_DocPtr)(IDispatch* newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(DataXMLRWKeys), CDataXMLRWKeys)

