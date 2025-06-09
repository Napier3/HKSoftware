#ifndef _Recorder_PpEngine_H__
#define _Recorder_PpEngine_H__

#include "TestControlBase.h"
#include "RecorderInterface.h"


class CRecorderPpEngine : public CRecorderInterface
{
public:
	CRecorderPpEngine()						{	m_pTestControl = NULL;	} 
	virtual ~CRecorderPpEngine()	{	}
	
	// 属性
public:
	CTestControlBase *m_pTestControl;
	
	// 操作
public:


	// IRecorder 方法
public:
	virtual long CreateCrecorder(LPCTSTR strProgID)
	{
		m_strRecordProgID = strProgID;
		return 0;
	}
	virtual long Config()
	{
		return 0;
	}
	virtual long SaveRecorder(LPCTSTR strFile)
	{
		if (m_pTestControl != NULL)
		{
			return 0;
		}
		
		CProtocolDeviceInterface* oPpDevice = m_pTestControl->GetDevicePtr();

		if (oPpDevice == NULL)
		{
			return 0;
		}

		CProtocolParasInterface* oDataInterface = oPpDevice->GetDataInterface();
		oDataInterface->Reset();
		
		if (oDataInterface == NULL)
		{
			return 0;
		}
	
		oDataInterface->AddData(_T("path"), strFile);
		m_pTestControl->Out_RunProcedure(_T("record_file"), _T(""), 0, 0, ProcedureType_TestItem);
		oDataInterface->Release();
		
		return 0;
	}
	virtual long OpenRecorder(LPCTSTR strFile)
	{
		return 0;
	}
	virtual long Quit()
	{
		return 0;
	}
	virtual long IsConnectSucc()
	{
		if (m_pTestControl != NULL)
		{
			return 0;
		}

		CProtocolDeviceInterface* oPpDevice = m_pTestControl->GetDevicePtr();

		if (oPpDevice == NULL)
		{
			return 0;
		}

		return oPpDevice->IsConnectSuccessful();
	}
	virtual long IsRecordFinish()
	{
		return 0;
	}
	virtual long ExecCmd(LPCTSTR strCmd, LPCTSTR strPara)
	{
		return 0;
	}
	virtual long AttachAsyncMsg(unsigned long hWndHandle, unsigned long nMsgID)
	{
		return 0;
	}
	virtual CString GetResult()
	{
		return _T("");
	}
	virtual CString Select(LPCTSTR strPara)
	{
		return _T("");
	}
	virtual CString Validate(LPCTSTR strPara)
	{
		return _T("");
	}
	virtual long RcdCmpClear()	{	return 0;	}
	virtual long RcdCmp(const CString &strStdFile, const CString &strTestFie)	{	return 0;	}
	virtual long RcdAnalyse(const CString &strRcdFile)	{	return 0;	}
	// IRecorder 属性
public:

};

static CString g_strRecorderPpEngineProgID = _T("System.PpEngine");

#endif

