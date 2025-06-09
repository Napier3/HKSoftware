// ShortDatasMngr.h : CShortDatasMngr 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

#include "ShortDatas.h"
typedef CAtlComCoClassList<CShortDatas> CSHORTDATASLIST;
// CShortDatasMngr

class ATL_NO_VTABLE CShortDatasMngr :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShortDatasMngr, &CLSID_ShortDatasMngr>,
	public IDispatchImpl<IShortDatasMngr, &IID_IShortDatasMngr, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CShortDatasMngr()
	{
	}
	
	//宏定义
	DECLARE_CCOMOBJECT_METHODS(CShortDatasMngr,IShortDatas);
	DECLARE_XML_METHODS(CShortDatasMngr,CDataXMLRWKeys);
	static CShortDatas* FromIDispatch(IDispatch* pIDisp) 
	{
		if(pIDisp == NULL) 
			return NULL; 
		CShortDatas *pValues= NULL; 
		IShortDatas *pIValues = NULL; 
		pIDisp -> QueryInterface(IID_IValues,(void**) &pIValues); 

		if(pIValues == NULL) 
			return NULL; 
#ifdef _ATL_DEBUG_INTERFACES 
		_QIThunk *pThunk = (_QIThunk*) pIValues; 
		pValues = (CShortDatas*) pThunk -> m_pUnk; 
#else 
		pValues = (CShortDatas*) pIValues; 
#endif 
		pIValues->Release(); 
		return pValues; 
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SHORTDATASMNGR)


BEGIN_COM_MAP(CShortDatasMngr)
	COM_INTERFACE_ENTRY(IShortDatasMngr)
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
	CSHORTDATASLIST m_listChild;

public:
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIValues);
	STDMETHOD(AddNew)(IDispatch** pNew);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID,IDispatch** pNew);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIShortDatas);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIShortDatas);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(BringToTail)(VARIANT* vIndex);
	STDMETHOD(BringToHead)(VARIANT* vIndex);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);

};

OBJECT_ENTRY_AUTO(__uuidof(ShortDatasMngr), CShortDatasMngr)
