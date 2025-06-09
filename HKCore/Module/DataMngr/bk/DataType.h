// DataType.h : CDataType ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "DataTypeValue.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif


typedef CAtlComCoClassList<CDataTypeValue> CDATATYPEVALUELIST;
// CDataType

class ATL_NO_VTABLE CDataType :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataType, &CLSID_DataType>,
	public IDispatchImpl<IDataType, &IID_IDataType, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataType()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATATYPE)


BEGIN_COM_MAP(CDataType)
	COM_INTERFACE_ENTRY(IDataType)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CCOMOBJECT_METHODS(CDataType,IDataType)
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CDataType,IDataType)
#else
	FROM_IDISPATCH_EX(CDataType,IDataType)
#endif

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	DECLARE_XML_METHODS(CDataType,CDataTypeXMLRWKeys);
public:
	CComBSTR m_strID;
	CComBSTR m_strName;
	CDATATYPEVALUELIST m_listChild;

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIDataTypeValue);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIDataTypeValue);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIDataTypeValue);
	STDMETHOD(AddNew)(IDispatch** pIDataTypeValue);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, LONG nIndex, IDispatch** pIDataTypeValue);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(DeleteAll)(void);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
};

OBJECT_ENTRY_AUTO(__uuidof(DataType), CDataType)
