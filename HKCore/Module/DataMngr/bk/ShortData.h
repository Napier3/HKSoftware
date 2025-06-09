// ShortData.h : CShortData ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



#include "../../Module/AtlAPI/InterfaceMethodsDefine.h"
#include "DataXMLRWKeys.h"
// CShortData

class ATL_NO_VTABLE CShortData :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShortData, &CLSID_ShortData>,
	public IDispatchImpl<IShortData, &IID_IShortData, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IValue, &__uuidof(IValue), &LIBID_SystemTool, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CShortData()
	{
		m_strName = L"";
		m_strID = L"";
		m_strValue = L"";
		m_strUnit   = L"";
		m_strDataTypeID = L"";
		m_nReserved = 0;
		m_strFormat = L"";
		m_strReMark = L"";
		m_strDefaultValue = L"";
	}

	DECLARE_CCOMOBJECT_METHODS(CShortData,IShortData);
	NEW_CCOMOBJECT_COPY(CShortData,IShortData);
#ifdef _ATL_DEBUG_INTERFACES
	FROM_IDISPATCH(CShortData,IShortData)
#else
	FROM_IDISPATCH_EX(CShortData,IShortData)
#endif

	DECLARE_REGISTRY_RESOURCEID(IDR_SHORTDATA)


	BEGIN_COM_MAP(CShortData)
		COM_INTERFACE_ENTRY2(IValue,IShortData)
		COM_INTERFACE_ENTRY2(IDispatch, IShortData)
		COM_INTERFACE_ENTRY(IShortData)
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
	CComBSTR m_strID;
	CComBSTR m_strValue;
	CComBSTR m_strName;
	CComBSTR m_strUnit;
	CComBSTR m_strDataTypeID;
	long m_nReserved;
	CComBSTR m_strFormat;
	CComBSTR m_strReMark;
	CComBSTR m_strDefaultValue;

	BOOL _Copy(CShortData* pShortData);
	long _IsEqual(CShortData* pShortData);

	//XML��д
	DECLARE_XML_METHODS(CShortData,CDataXMLRWKeys);

	// IValue Methods
public:
	STDMETHOD(get_ID)( BSTR * pVal);
	STDMETHOD(put_ID)( BSTR newVal);
	STDMETHOD(get_Value)( BSTR * pVal);
	STDMETHOD(put_Value)( BSTR newVal);
	STDMETHOD(StringSerialize)( IDispatch * pIStringBuffer);
	STDMETHOD(BinarySerialize)( IDispatch * pIBinaryBuffer);
	STDMETHOD(XMLWrite)( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys);
	STDMETHOD(XMLRead)( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys);
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(get_Unit)(BSTR* pVal);
	STDMETHOD(put_Unit)(BSTR newVal);
	STDMETHOD(get_DataTypeID)(BSTR* pVal);
	STDMETHOD(put_DataTypeID)(BSTR newVal);
	STDMETHOD(get_Reserved)(LONG* pVal);
	STDMETHOD(put_Reserved)(LONG newVal);
	STDMETHOD(get_Format)(BSTR* pVal);
	STDMETHOD(put_Format)(BSTR newVal);
	STDMETHOD(IsEqual)(IDispatch* pISrcObj, LONG* pnEqual);
	STDMETHOD(get_Remark)(BSTR* pVal);
	STDMETHOD(put_Remark)(BSTR newVal);
	STDMETHOD(get_DefaultValue)(BSTR* pVal);
	STDMETHOD(put_DefaultValue)(BSTR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(ShortData), CShortData)
