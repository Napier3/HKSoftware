// ShortDatasMngr.h : CShortDatasMngr ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
	
	//�궨��
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
