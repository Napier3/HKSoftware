// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

// CFtpSvrCom 包装类
#pragma once

class CFtpSvrCom : public COleDispatchDriver
{
public:
	CFtpSvrCom(){} // 调用 COleDispatchDriver 默认构造函数
	CFtpSvrCom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFtpSvrCom(const CFtpSvrCom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 属性
public:

	// 操作
public:


	// IFtpSvrCom 方法
public:
	long InitFtpServer(LPCTSTR strPath, long nType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath, nType);
		return result;
	}
	long StartFtpServer(LPCTSTR strPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath);
		return result;
	}

	// IFtpSvrCom 属性
public:

};
