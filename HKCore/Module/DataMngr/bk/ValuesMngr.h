// ValuesMngr.h : CValuesMngr 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "Values.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif


typedef CAtlComCoClassList<CValues> CVALUESLIST;
// CValuesMngr

class ATL_NO_VTABLE CValuesMngr :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CValuesMngr, &CLSID_ValuesMngr>,
	public IDispatchImpl<IValuesMngr, &IID_IValuesMngr, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CValuesMngr()
	{
	}
	//宏定义
	DECLARE_XML_METHODS(CValuesMngr,CValueXMLRWKeys);

DECLARE_REGISTRY_RESOURCEID(IDR_VALUESMNGR)


BEGIN_COM_MAP(CValuesMngr)
	COM_INTERFACE_ENTRY(IValuesMngr)
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
public:
	CVALUESLIST m_listChild;
public:
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIValues);
	STDMETHOD(AddNew)(IDispatch** pIValues);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, IDispatch** pIValues);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIValues);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIValues);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(BringToTail)(VARIANT* vIndex);
	STDMETHOD(BringToHead)(VARIANT* vIndex);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);

};

OBJECT_ENTRY_AUTO(__uuidof(ValuesMngr), CValuesMngr)
