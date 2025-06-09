#if !defined(_CSclToModelTool_h__)
#define _CSclToModelTool_h__

#if _MSC_VER > 1000
#pragma once


#endif // _MSC_VER > 1000

#include "ModelWriteXml.h"

#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "SclReadDlg.h"
#include "SclIED.h"

#include <list>

class CSclIED;


#define WM_SCLTOMODEL_READ_FINISH   (WM_USER + 1414)
#define SCLTOMODEL_READ_SHOW      0
#define SCLTOMODEL_READ_DELCTRLS  1
#define SCLTOMODEL_READ_FINISH    2


class CSclToModelTool : public CExBaseList
{
public:
	CSclToModelTool();
	virtual ~CSclToModelTool();
public:
	CString m_strFile;
	CExBaseList m_oSclIEDs;

protected:
	CSclReadDlg  *m_pSclReadDlg;
	SCL_INFO		m_SclInfo;
	BOOL m_bCan_Free_SCL_INFO;
	CWnd            *m_pOwnerWnd;

	void ReadAllIedAddr();
	void Free_SCL_INFO();

public:
	BOOL 	ReadSclFile(const CString &strFile, CWnd *pOwnerWnd);
	static UINT ReadSCLThread (LPVOID pParam );
	SCL_INFO* GetSclInfo(){return &m_SclInfo;}
	void GetAndSaveDeviceModel(CString &strSclFilePath,CString &strDeviceModelPath,CString &strIEDName);

	BOOL GetIED_ModelFile(CSclIED *pSclIED,CString &strIEDModelPath);
};

extern ST_BOOLEAN g_bUseSmemEnable;//zhj 20200209
#endif
