// ValuesMngr.h : CValuesMngr ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "Values.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
	//�궨��
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
