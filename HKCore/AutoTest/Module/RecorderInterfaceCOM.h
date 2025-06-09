// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#ifndef _Recorder_H__
#define _Recorder_H__

#include "RecorderInterface.h"

namespace Recorder
{
	class CRecorder : public COleDispatchDriver
	{
	public:
		CRecorder(){} // 调用 COleDispatchDriver 默认构造函数
		CRecorder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CRecorder(const CRecorder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IRecorder 方法
	public:
		long Config()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long SaveRecorder(LPCTSTR strFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFile);
			return result;
		}
		long OpenRecorder(LPCTSTR strFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFile);
			return result;
		}
		long Quit()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long IsConnectSucc()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long IsRecordFinish()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long ExecCmd(LPCTSTR strCmd, LPCTSTR strPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCmd, strPara);
			return result;
		}
		long AttachAsyncMsg(unsigned long hWndHandle, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWndHandle, nMsgID);
			return result;
		}
		CString GetResult()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString Select(LPCTSTR strPara)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strPara);
			return result;
		}
		CString Validate(LPCTSTR strPara)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strPara);
			return result;
		}
		long RcdCmpClear()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long RcdCmp(LPCTSTR strStdFile, LPCTSTR strTestFie)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strStdFile, strTestFie);
			return result;
		}
		long RcdAnalyse(LPCTSTR strRcdFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRcdFile);
			return result;
		}

		// IRecorder 属性
	public:

	};

};


class CRecorderCOM : public CRecorderInterface
{
public:
	CRecorderCOM()			{	m_oRecorder = NULL;	}
	virtual ~CRecorderCOM()	{	m_oRecorder = NULL;	}

public:
	Recorder::CRecorder m_oRecorder;

public:
	virtual long CreateCrecorder(LPCTSTR strProgID)
	{
		m_strRecordProgID = strProgID;
		m_oRecorder.CreateDispatch(strProgID);
		return 0;
	}
	virtual long Config()
	{
		return m_oRecorder.Config();
	}
	virtual long SaveRecorder(LPCTSTR strFile)
	{
		return m_oRecorder.SaveRecorder(strFile);
	}
	virtual long OpenRecorder(LPCTSTR strFile)
	{
		return m_oRecorder.OpenRecorder(strFile);
	}
	virtual long Quit()
	{
		return m_oRecorder.Quit();
	}
	virtual long IsConnectSucc()
	{
		return m_oRecorder.IsConnectSucc();
	}
	virtual long IsRecordFinish()
	{
		return m_oRecorder.IsRecordFinish();
	}
	virtual long ExecCmd(LPCTSTR strCmd, LPCTSTR strPara)
	{
		return m_oRecorder.ExecCmd(strCmd, strPara);
	}
	virtual long AttachAsyncMsg(unsigned long hWndHandle, unsigned long nMsgID)
	{
		return m_oRecorder.AttachAsyncMsg(hWndHandle, nMsgID);
	}
	virtual CString GetResult()
	{
		return m_oRecorder.GetResult();
	}
	virtual CString Select(LPCTSTR strPara)
	{
		return m_oRecorder.Select(strPara);
	}
	virtual CString Validate(LPCTSTR strPara)
	{
		return m_oRecorder.Validate(strPara);
	}

	virtual long RcdCmpClear()
	{
		return m_oRecorder.RcdCmpClear();
	}
	virtual long RcdCmp(const CString &strStdFile, const CString &strTestFie)
	{
		return m_oRecorder.RcdCmp(strStdFile, strTestFie);
	}
	virtual long RcdAnalyse(const CString &strRcdFile)
	{
		return m_oRecorder.RcdAnalyse(strRcdFile);
	}

};

#endif

