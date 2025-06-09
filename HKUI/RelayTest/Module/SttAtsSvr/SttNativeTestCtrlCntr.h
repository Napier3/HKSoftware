#pragma once

#ifdef _PSX_IDE_QT_
#include "../../../AutoTest/Module/TestControl/TestControlBase.h"
#else
#include "../../../AutoTest/Module/TestControl/TestControl.h"
#endif

#ifdef _PSX_IDE_QT_
class CSttNativeTestCltlCntr: public CTestControlBase
#else
class CSttNativeTestCltlCntr: public CTestControl
#endif
{
public:
     CSttNativeTestCltlCntr();
    virtual ~CSttNativeTestCltlCntr();

public:
	//创建通讯规约引擎对象
	virtual void CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef);
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);

	virtual long TestItemSafety(CSafety* pItem);
	virtual long TestItemSysParaEdit(CSysParaEdit* pItem);

#ifndef _PSX_IDE_QT_
	virtual long CreateReportFill(const CString &strRptProgID, BOOL bExportWord=FALSE);
	virtual BOOL OpenWordReportFile(BOOL bExportWord=FALSE, const CString &strDocFile=_T(""));
#endif

};
