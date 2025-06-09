// ShortDatas.h : CShortDatas ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "DataXMLRWKeys.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

#include "ShortData.h"

typedef CAtlComCoClassList<CShortData> CSHORTDATALIST;

// CShortDatas

class ATL_NO_VTABLE CShortDatas :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShortDatas, &CLSID_ShortDatas>,
	public IDispatchImpl<IShortDatas, &IID_IShortDatas, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CShortDatas()
	{
		m_strName = L"";
		m_strID = L"";
	}
	DECLARE_CCOMOBJECT_METHODS(CShortDatas,IShortDatas);
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CShortDatas,IShortDatas)
#else
	FROM_IDISPATCH_EX(CShortDatas,IShortDatas)
#endif

DECLARE_REGISTRY_RESOURCEID(IDR_SHORTDATAS)


BEGIN_COM_MAP(CShortDatas)
	COM_INTERFACE_ENTRY(IShortDatas)
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
	//XML��д�궨��
	DECLARE_XML_METHODS(CShortDatas,CDataXMLRWKeys);
public:
	CComBSTR m_strName;
	CComBSTR m_strID;
	CSHORTDATALIST m_listChild;
	int _Append(CShortDatas* pShortDatas);
	int _CloneAppend(CShortDatas* pShortDatas);

	void _BinarySerializeChild(IDispatch* pIBinaryBuffer);
	void _StringSerializeChild(IDispatch* pIStringBuffer);
public:
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_ID)(BSTR* pVal);
	STDMETHOD(put_ID)(BSTR newVal);
	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIShortData);
	STDMETHOD(FindByName)(BSTR bstrName, IDispatch** pIShortData);
	STDMETHOD(FindByID)(BSTR bstrID, IDispatch** pIShortData);
	STDMETHOD(AddNew)(IDispatch** pIShortData);
	STDMETHOD(AddNew2)(BSTR strName,BSTR strID, BSTR strUnit, BSTR strDataTypeID, BSTR strValue, LONG nReserved,BSTR bstrFormat,BSTR bstrRemark, IDispatch** pNew);
	STDMETHOD(Delete)(VARIANT* vIndex, LONG* pnReturn);
	STDMETHOD(Append)(IDispatch* pIShortDatas);
	STDMETHOD(Clone)(IDispatch** pIShortDatas);
	STDMETHOD(SetValueByName)(BSTR bstrName, BSTR bstrValue);
	STDMETHOD(SetValueByID)(BSTR bstrID, BSTR bstrValue);
	STDMETHOD(DeleteAll)(void);
	STDMETHOD(ChangePosition)(VARIANT* vIndex1, VARIANT* vIndex2);
	STDMETHOD(SetValuesByDatas)(IDispatch* pIShortDatas);
	STDMETHOD(SetValuesByEquation)(IDispatch* pIEquation);
	STDMETHOD(SetValuesByString)(BSTR bstrValues);
	STDMETHOD(GetDatasString)(LONG nNameFormat, LONG nWithUnit, BSTR* pbstrValues);
	STDMETHOD(StringSerialize)(IDispatch* pStringBuffer, LONG nNameFormat, LONG nWithUnit);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
	STDMETHOD(XMLWrite)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(XMLRead)(IDispatch* pIXMLElement, IDispatch* pIXMLKeys);
	STDMETHOD(SetValuesByValues)(IDispatch* pIValues);
	STDMETHOD(GetValues)(IDispatch** pIValues);

	STDMETHOD(IsEqual)(IDispatch* pISrcObj, LONG* pnEqual);
};

OBJECT_ENTRY_AUTO(__uuidof(ShortDatas), CShortDatas)
