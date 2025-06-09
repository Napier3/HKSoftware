// DataTypeValue.h : CDataTypeValue 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "DataTypeXMLRWKeys.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CDataTypeValue

class ATL_NO_VTABLE CDataTypeValue :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataTypeValue, &CLSID_DataTypeValue>,
	public IDispatchImpl<IDataTypeValue, &IID_IDataTypeValue, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataTypeValue()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATATYPEVALUE)


BEGIN_COM_MAP(CDataTypeValue)
	COM_INTERFACE_ENTRY(IDataTypeValue)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CCOMOBJECT_METHODS(CDataTypeValue,IDataTypeValue)
	static CDataTypeValue* FromIDispatch(IDispatch* pIDisp) 
	{
		if(pIDisp == NULL) 
			return NULL; 
		CDataTypeValue *pDataTypeValue= NULL; 
		IDataTypeValue *pIDataTypeValue = NULL; 
		pIDisp -> QueryInterface(IID_IDataTypeValue,(void**) &pIDataTypeValue); 

		if(pIDataTypeValue == NULL) 
			return NULL; 
#ifdef _ATL_DEBUG_INTERFACES 
		_QIThunk *pThunk = (_QIThunk*) pIDataTypeValue; 
		pDataTypeValue = (CDataTypeValue*) pThunk -> m_pUnk; 
#else 
		pDataTypeValue = (CDataTypeValue*) pIDataTypeValue; 
#endif 
		pIDataTypeValue->Release(); 
		return pDataTypeValue; 
	}
	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	DECLARE_XML_METHODS(CDataTypeValue,CDataTypeXMLRWKeys);

	CComBSTR m_strName;
	CComBSTR m_strID;
	LONG     m_nIndex;
public:

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(get_Index)(LONG* pVal);
	STDMETHOD(put_Index)(LONG newVal);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
};

OBJECT_ENTRY_AUTO(__uuidof(DataTypeValue), CDataTypeValue)
