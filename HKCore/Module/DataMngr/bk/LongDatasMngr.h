// LongDatasMngr.h : CLongDatasMngr 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "LongDatas.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif


typedef CAtlComCoClassList<CLongDatas> CLLONGDATASLIST;
// CLongDatasMngr

class ATL_NO_VTABLE CLongDatasMngr :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongDatasMngr, &CLSID_LongDatasMngr>,
	public IDispatchImpl<ILongDatasMngr, &IID_ILongDatasMngr, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CLongDatasMngr()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LONGDATASMNGR)


BEGIN_COM_MAP(CLongDatasMngr)
	COM_INTERFACE_ENTRY(ILongDatasMngr)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	//XML宏
	DECLARE_XML_METHODS(CLongDatasMngr,CDataXMLRWKeys);
	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
public:
	CLLONGDATASLIST m_listChild;
public:
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pILongDatas);
	STDMETHOD(AddNew)(IDispatch** pILongDatas);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, IDispatch** pILongDatas);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pILongDatas);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pILongDatas);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(BringToTail)(VARIANT* vIndex);
	STDMETHOD(BringToHead)(VARIANT* vIndex);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
};

OBJECT_ENTRY_AUTO(__uuidof(LongDatasMngr), CLongDatasMngr)
