// DataTypes.h : CDataTypes ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "DataType.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif
#include "..\..\Module\AtlBaseClass\AtlComCoClassList.h"

typedef CAtlComCoClassList<CDataType> CDATATYPESLIST;
// CDataTypes

class ATL_NO_VTABLE CDataTypes :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataTypes, &CLSID_DataTypes>,
	public IDispatchImpl<IDataTypes, &IID_IDataTypes, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataTypes()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATATYPES)


BEGIN_COM_MAP(CDataTypes)
	COM_INTERFACE_ENTRY(IDataTypes)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_CCOMOBJECT_METHODS(CDataTypes,IDataTypes)
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CDataTypes,IDataTypes)
#else
	FROM_IDISPATCH_EX(CDataTypes,IDataTypes)
#endif

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	DECLARE_XML_METHODS(CDataTypes,CDataTypeXMLRWKeys);

	CDATATYPESLIST m_listChild;
public:

	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIDataType);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIDataType);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIDataType);
	STDMETHOD(AddNew)(IDispatch** pIDataType);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, IDispatch** pIDataType);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(Open)(BSTR bstrFile, IDispatch* pXmlKeys, ULONG* pnReturn);
	STDMETHOD(Save)(BSTR bstrFile, IDispatch* pXmlKeys, ULONG* pnReturn);
};

OBJECT_ENTRY_AUTO(__uuidof(DataTypes), CDataTypes)
