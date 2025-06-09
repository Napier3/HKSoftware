// LongDatasMngr.h : CLongDatasMngr ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "LongDatas.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
	//XML��
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
