﻿// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#import "I:\\EXCEL.EXE" no_namespace
// CconCriteria 包装类

class CconCriteria : public COleDispatchDriver
{
public:
	CconCriteria(){} // 调用 COleDispatchDriver 默认构造函数
	CconCriteria(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CconCriteria(const CconCriteria& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 属性
public:

	// 操作
public:


	// IconCriteria 方法
public:
	long get_Count()
	{
		long result;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Default(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}

	// IconCriteria 属性
public:

};
