// TagsMngr.h : CTagsMngr ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "Tags.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CTagsMngr
typedef CAtlComCoClassList<CTags> CTAGSLIST;

class ATL_NO_VTABLE CTagsMngr :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTagsMngr, &CLSID_TagsMngr>,
	public IDispatchImpl<ITagsMngr, &IID_ITagsMngr, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTagsMngr()
	{
		m_strID = L"id";
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TAGSMNGR)


BEGIN_COM_MAP(CTagsMngr)
	COM_INTERFACE_ENTRY(ITagsMngr)
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

	DECLARE_CCOMOBJECT_METHODS(CTagsMngr,ITagsMngr)
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CTagsMngr,ITagsMngr)
#else
	FROM_IDISPATCH_EX(CTagsMngr,ITagsMngr)
#endif

		//XML���� �궨��
		DECLARE_XML_METHODS(CTagsMngr,CValueXMLRWKeys);

	CTAGSLIST m_listChild;
	CComBSTR m_strID;

	static const WCHAR* g_pstrKeyID;
	static const WCHAR* g_pstrKeyTagsMngr;
	void _BinarySerializeChild(IDispatch* pIBinaryBuffer);

public:	
 
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIValues);
	STDMETHOD(AddNew)(IDispatch** pIValues);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, IDispatch** pIValues);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIValues);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIValues);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(BrindToTail)(VARIANT* vIndex);
	STDMETHOD(BringToHead)(VARIANT* vIndex);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(DeleteAll)(void);
	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(TagsMngr), CTagsMngr)
