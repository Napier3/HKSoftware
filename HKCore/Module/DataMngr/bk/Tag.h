// Tag.h : CTag 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "ValueXMLRWKeys.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CTag

class ATL_NO_VTABLE CTag :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTag, &CLSID_Tag>,
	public IDispatchImpl<ITag, &IID_ITag, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTag()
	{
		m_strID = L"";
		m_strDataType = L"";
		m_strValue = L"";
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TAG)


BEGIN_COM_MAP(CTag)
	COM_INTERFACE_ENTRY(ITag)
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

	DECLARE_CCOMOBJECT_METHODS(CTag,ITag)
#ifdef _ATL_DEBUG_INTERFACES
		FROM_IDISPATCH(CTag,ITag)
#else
		FROM_IDISPATCH_EX(CTag,ITag)
#endif
	
	//XML方法 宏定义
	DECLARE_XML_METHODS(CTag,CValueXMLRWKeys);

	CComBSTR m_strID;
	CComBSTR m_strDataType;
	CComBSTR m_strValue;

	BOOL _Copy(CTag* pTag);
	long _IsEqual(CTag* pTag);

	static const WCHAR* g_pstrKeyID;
	static const WCHAR* g_pstrKeyDataType;
	static const WCHAR* g_pstrKeyValue;

	static CTag* _new_CTag(CTag* pSrc)
	{
		CTag *pData = _new_CTag();
		pData->_Copy(pSrc);
		return pData;
	}

public:

	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(get_DataType)(BSTR* pVal);
	STDMETHOD(put_DataType)(BSTR newVal);
	STDMETHOD(get_Value)(BSTR* pVal);
	STDMETHOD(put_Value)(BSTR newVal);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
};

OBJECT_ENTRY_AUTO(__uuidof(Tag), CTag)
