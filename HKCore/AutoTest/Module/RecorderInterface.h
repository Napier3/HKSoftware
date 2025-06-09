// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#ifndef _Recorder_Interface_H__
#define _Recorder_Interface_H__

class CRecorderInterface
{
public:
	CString m_strRecordProgID;

	// 属性
public:

	// 操作
public:


	// IRecorder 方法
public:
	virtual long CreateCrecorder(LPCTSTR strProgID) = 0;
	virtual long Config() = 0;
	virtual long SaveRecorder(LPCTSTR strFile) = 0;
	virtual long OpenRecorder(LPCTSTR strFile) = 0;
	virtual long Quit() = 0;
	virtual long IsConnectSucc() = 0;
	virtual long IsRecordFinish() = 0;
	virtual long ExecCmd(LPCTSTR strCmd, LPCTSTR strPara) = 0;
	virtual long AttachAsyncMsg(unsigned long hWndHandle, unsigned long nMsgID) = 0;
	virtual CString GetResult() = 0;
	virtual CString Select(LPCTSTR strPara) = 0;
	virtual CString Validate(LPCTSTR strPara) = 0;
	virtual long RcdCmpClear() = 0;
	virtual long RcdCmp(const CString &strStdFile, const CString &strTestFie) = 0;
	virtual long RcdAnalyse(const CString &strRcdFile) = 0;
	// IRecorder 属性
public:


};

static const CString g_strRecordResultKey = _T("RecordFile");
static const CString g_strRecordComtradePath = _T("Comtrade");
static const CString g_strRecordCmpStdFile = _T("rcd-file-std");
static const CString g_strRecordCmpTestFile = _T("rcd-file-test");
static const CString g_strRecordDefaultComtradeFile = _T("CurrentRecord.dat");

static const CString g_strPpEngineRecordFilePathKey = _T("rcd-file-path");

enum tagRecordState
{
	rcdStateConnectFailed = 0,
	rcdStateConnectSuccess = 1,
	rcdStateRecordFailed = 2,
	rcdStateRecordSuccess = 3
};

#endif

