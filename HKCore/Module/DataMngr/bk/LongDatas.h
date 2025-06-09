// LongDatas.h : CLongDatas ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

#include "LongData.h"
#include "..\..\Module\AtlAPI\InterfaceMethodsDefine.h"
#include "..\..\Module\AtlBaseClass\AtlComCoClassList.h"

// CLongDatas

typedef CAtlComCoClassList<CLongData> CLONGDATALIST;

class ATL_NO_VTABLE CLongDatas :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongDatas, &CLSID_LongDatas>,
	public IDispatchImpl<ILongDatas, &IID_ILongDatas, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CLongDatas()
	{
		m_strID = L"";
		m_strName = L"";
		m_strScript = L"";
		m_sEnable = 1;
		m_sShow = 1;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LONGDATAS)


BEGIN_COM_MAP(CLongDatas)
	COM_INTERFACE_ENTRY(ILongDatas)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_CCOMOBJECT_METHODS(CLongDatas,ILongDatas)
	DECLARE_XML_METHODS(CLongDatas,CDataXMLRWKeys);

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComBSTR m_strID;
	CComBSTR m_strName;
	CComBSTR m_strScript;
	short    m_sEnable;
	short	 m_sShow;
	CLONGDATALIST m_listChild;

#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CLongDatas,ILongDatas)
#else
	FROM_IDISPATCH_EX(CLongDatas,ILongDatas)
#endif

	int _Append(CLongDatas* pValues);
	int _CloneAppend(CLongDatas* pValues);
public:

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(get_Script)(BSTR* pVal);
	STDMETHOD(put_Script)(BSTR newVal);
	STDMETHOD(get_Show)(SHORT* pVal);
	STDMETHOD(put_Show)(SHORT newVal);
	STDMETHOD(get_Enable)(SHORT* pVal);
	STDMETHOD(put_Enable)(SHORT newVal);
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pILongData);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pILongData);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pILongData);
	STDMETHOD(AddNew)(IDispatch** pILongData);
	STDMETHOD(AddNew2)(BSTR bstrName, BSTR bstrID, BSTR bstrDataTypeID, BSTR bstrUnit, BSTR bstrValue, IDispatch** pILongData);
	STDMETHOD(AddNew3)(BSTR bstrName, BSTR bstrID, BSTR bstrUnit, BSTR bstrDataTypeID, BSTR bstrValue, BSTR bstrValueName, BSTR bstrDefaultValue, BSTR bstrScript, BSTR bstrDataTypeDomain, BSTR bstrMessage, SHORT nType, SHORT nShow, SHORT nEnable, LONG nReserved, LONG nReserved2, BSTR strFormat, IDispatch** pILongData);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(Append)(IDispatch* pILongDatas);
	STDMETHOD(Clone)(IDispatch** pILongDatas);
	STDMETHOD(SetValueByName)(BSTR bstrName, BSTR bstrValue);
	STDMETHOD(SetValueByID)(BSTR bstrID, BSTR bstrValue);
	STDMETHOD(DeleteAll)(void);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(ReSetValues)(void);
	STDMETHOD(InitValueName)(IDispatch* pIDataTypes);
	STDMETHOD(SetValuesByDatas)(IDispatch* pILongDatas);
	STDMETHOD(SetValuesByEquation)(IDispatch* pIEquation);
	STDMETHOD(SetValuesByString)(BSTR bstrValues);
	STDMETHOD(GetDatasString)(LONG nNameFormat,LONG nValueFormat, LONG nWithUnit, BSTR* pbstrValues);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);

};

OBJECT_ENTRY_AUTO(__uuidof(LongDatas), CLongDatas)
