// DataTypes.h : CDataTypes 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include "DataType.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
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
