// Tags.h : CTags ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "ValueXMLRWKeys.h"
#include "Tag.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
	//XML���� �궨��
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
