// LongData.h : CLongData 的声明

#pragma once
#include "resource.h"       // 主符号

#include "SystemTool_i.h"
#include"..\..\Module\AtlAPI\InterfaceMethodsDefine.h"
#include "DataXMLRWKeys.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif



// CLongData

class ATL_NO_VTABLE CLongData :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongData, &CLSID_LongData>,
	public IDispatchImpl<ILongData, &IID_ILongData, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IShortData, &__uuidof(IShortData), &LIBID_SystemTool, /* wMajor = */ 1, /* wMinor = */ 0>,
	public IDispatchImpl<IValue, &__uuidof(IValue), &LIBID_SystemTool, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	CLongData():m_strID(L""),m_strName(L""),m_strUnit(L""),m_strValueName(L""),m_strValue(L""),
				m_strScript(L""),m_strMessage(L""),m_strDataTypeDomain(L""),m_strDataTypeID(L""),
				m_nReserved(0),m_nReserved2(0),m_sShow(0),m_sEnable(0),m_sType(0),m_strFormat(L"")
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LONGDATA)


	BEGIN_COM_MAP(CLongData)
		COM_INTERFACE_ENTRY2(IShortData,ILongData)
		COM_INTERFACE_ENTRY2(IValue,ILongData)
		COM_INTERFACE_ENTRY2(IDispatch,ILongData)	
		COM_INTERFACE_ENTRY(ILongData)	
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_CCOMOBJECT_METHODS(CLongData,ILongData)

	NEW_CCOMOBJECT_COPY(CLongData,ILongData)
	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	//xml读写
	DECLARE_XML_METHODS(CLongData,CDataXMLRWKeys);

	CComBSTR m_strID;
	CComBSTR m_strValue;
	CComBSTR m_strName;
	CComBSTR m_strUnit;
	CComBSTR m_strDataTypeID;
	long     m_nReserved;
	CComBSTR m_strFormat;
	CComBSTR m_strValueName;
	CComBSTR m_strDefaultValue;
	CComBSTR m_strScript;
	CComBSTR m_strDataTypeDomain;
	CComBSTR m_strMessage;
	short    m_sType;
	short    m_sShow;
	short    m_sEnable;
	long	 m_nReserved2;
public:

	static CLongData* FromIDispatch(IDispatch* pIDisp) 
	{
		if(pIDisp == NULL) 
			return NULL; 
		CLongData *pLongData= NULL; 
		ILongData *pILongData = NULL; 
		pIDisp -> QueryInterface(IID_ILongData,(void**) &pILongData); 

		if(pILongData == NULL) 
			return NULL; 
#ifdef _ATL_DEBUG_INTERFACES 
		_QIThunk *pThunk = (_QIThunk*) pILongData; 
		pLongData = (CLongData*)(ILongData *)pThunk -> m_pUnk; 
#else 
		pLongData = (CLongData*) pILongData; 
#endif 
		pILongData->Release(); 
		return pLongData; 
	}
	// IShortData Methods
	BOOL _Copy(CLongData* pLongData)
	{
		ATLASSERT((pLongData!=this)&&(pLongData!=NULL));
		m_strID = pLongData->m_strID;
		m_strValue = pLongData->m_strValue;
		m_strName = pLongData->m_strName;
		m_strUnit = pLongData->m_strUnit;
		m_strDataTypeID = pLongData->m_strDataTypeID;
		m_nReserved = pLongData->m_nReserved;
		m_strFormat = pLongData->m_strFormat;
		m_strValueName = pLongData->m_strValueName;
		m_strDefaultValue = pLongData->m_strDefaultValue;
		m_strScript = pLongData->m_strScript;
		m_strDataTypeDomain = pLongData->m_strDataTypeDomain;
		m_strMessage = pLongData->m_strMessage;
		m_sType = pLongData->m_sType;
		m_sShow = pLongData->m_sShow;
		m_sEnable = pLongData->m_sEnable;
		m_nReserved2 = pLongData->m_nReserved2;
		return 0;
	}
public:
	STDMETHOD(get_Name)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strName;
		return S_OK;
	}
	STDMETHOD(put_Name)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strName = newVal;
		return S_OK;
	}
	STDMETHOD(get_Unit)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strUnit;
		return S_OK;
	}
	STDMETHOD(put_Unit)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strUnit = newVal;
		return S_OK;
	}
	STDMETHOD(get_DataTypeID)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strDataTypeID;
		return S_OK;
	}
	STDMETHOD(put_DataTypeID)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strDataTypeID = newVal;
		return S_OK;
	}
	STDMETHOD(get_Reserved)( LONG * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_nReserved;
		return S_OK;
	}
	STDMETHOD(put_Reserved)( LONG newVal)
	{
		// 在此处添加函数实现。
		m_nReserved = newVal;
		return S_OK;
	}
	STDMETHOD(get_Format)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strFormat;
		return S_OK;
	}
	STDMETHOD(put_Format)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strFormat = newVal;
		return S_OK;
	}

	// IValue Methods
public:
	STDMETHOD(get_ID)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strID.Copy();
		return S_OK;
	}
	STDMETHOD(put_ID)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strID = newVal;
		return S_OK;
	}
	STDMETHOD(get_Value)( BSTR * pVal)
	{
		// 在此处添加函数实现。
		*pVal = m_strValue;
		return S_OK;
	}
	STDMETHOD(put_Value)( BSTR newVal)
	{
		// 在此处添加函数实现。
		m_strValue = newVal;
		return S_OK;
	}
	STDMETHOD(StringSerialize)( IDispatch * pIStringBuffer)
	{
		// 在此处添加函数实现。
		return S_OK;
	}
	STDMETHOD(BinarySerialize)( IDispatch * pIBinaryBuffer)
	{
		// 在此处添加函数实现。
		return S_OK;
	}
	STDMETHOD(XMLWrite)( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys)
	{
		// 在此处添加函数实现。
		XML_INTERFACE_WRITE(pIXMLElement,pIXMLKeys);
		return S_OK;
	}
	STDMETHOD(XMLRead)( IDispatch * pIXMLElement,  IDispatch * pIXMLKeys)
	{
		// 在此处添加函数实现。
		XML_INTERFACE_READ(pIXMLElement,pIXMLKeys)
		return S_OK;
	}
	STDMETHOD(get_ValueName)(BSTR* pVal);
	STDMETHOD(put_ValueName)(BSTR newVal);
	STDMETHOD(get_DefaultValue)(BSTR* pVal);
	STDMETHOD(put_DefaultValue)(BSTR newVal);
	STDMETHOD(get_Script)(BSTR* pVal);
	STDMETHOD(put_Script)(BSTR newVal);
	STDMETHOD(get_DataTypeDomain)(BSTR* pVal);
	STDMETHOD(put_DataTypeDomain)(BSTR newVal);
	STDMETHOD(get_Message)(BSTR* pVal);
	STDMETHOD(put_Message)(BSTR newVal);
	STDMETHOD(get_Type)(SHORT* pVal);
	STDMETHOD(put_Type)(SHORT newVal);
	STDMETHOD(get_Show)(SHORT* pVal);
	STDMETHOD(put_Show)(SHORT newVal);
	STDMETHOD(get_Enable)(SHORT* pVal);
	STDMETHOD(put_Enable)(SHORT newVal);
	STDMETHOD(get_Reserved2)(LONG* pVal);
	STDMETHOD(put_Reserved2)(LONG newVal);
	STDMETHOD(IsEqual)(IDispatch* pISrcObj, LONG* pnEqual);
	STDMETHOD(get_Remark)(BSTR* pVal);
	STDMETHOD(put_Remark)(BSTR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(LongData), CLongData)
