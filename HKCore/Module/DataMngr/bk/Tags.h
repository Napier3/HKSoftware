// Tags.h : CTags 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "ValueXMLRWKeys.h"
#include "Tag.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif


typedef CAtlComCoClassList<CTag> CTAGLIST;
// CTags

class ATL_NO_VTABLE CTags :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTags, &CLSID_Tags>,
	public IDispatchImpl<ITags, &IID_ITags, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTags()
	{
		m_strID = L"";
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TAGS)


BEGIN_COM_MAP(CTags)
	COM_INTERFACE_ENTRY(ITags)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_CCOMOBJECT_METHODS(CTags,ITags)
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CTags,ITags)
#else
	FROM_IDISPATCH_EX(CTags,ITags)
#endif

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	
	

public:
	//XML方法 宏定义
	DECLARE_XML_METHODS(CTags,CValueXMLRWKeys);

	CTAGLIST m_listChild;
	CComBSTR m_strID;

	static const WCHAR* g_pstrKeyID;
	static const WCHAR* g_pstrKeyTag;
	static const WCHAR* g_pstrKeyTags;
	
	int _Append(CTags* pValues);
	int _CloneAppend(CTags* pSrcValues);

	void _BinarySerializeChild(IDispatch* pIBinaryBuffer);
	void _StringSerializeChild(IDispatch* pIStringBuffer);
	
public:

	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(Add)(BSTR strID, BSTR strDataType, BSTR strValue, IDispatch** pITag);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement,IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement,IDispatch* pIXMLKeys);
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIValue);
	STDMETHOD(FindByID)(BSTR strID, IDispatch** pIValue);
	STDMETHOD(AddNew)(IDispatch** pIValue);
	STDMETHOD(AddNew2)(BSTR strID, BSTR strValue, BSTR strDataType, IDispatch** pIValue);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(Append)(IDispatch* pIValues);
	STDMETHOD(Clone)(IDispatch** pIValues);
	STDMETHOD(DeleteAll)(void);
	STDMETHOD(GetValues)(IDispatch** pIValues);
};

OBJECT_ENTRY_AUTO(__uuidof(Tags), CTags)
