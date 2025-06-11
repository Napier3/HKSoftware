#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "GuideBook/GuideBookDefine.h"
#include "GuideBook/GuideBookInterface.h"
#include "AutoTestXMLRWKeys.h"
#include "TCtrlCntrDefine.h"
#include "../Module/SttGlobalDef.h"

#ifndef  _not_use_autotest_
#include "../Module/SmartTestInterface/ProtocolEngineInterface.h"
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
#include "../../SttStudio/Module/SmartTestInterface/PpSttIotEngine.h"
#define CXProtocolDevice CPpSttIotDevice
#else
#define CXProtocolDevice CProtocolDeviceInterface
#endif

#define DeviceRefs_InitBy_NONE            0
#define DeviceRefs_InitBy_CreateTest     1
#define DeviceRefs_InitBy_CommConfig   2
#define DeviceRefs_InitBy_CPUS             3

class CPpDeviceRef : public CExBaseObject
{
public:
#ifndef  _not_use_autotest_
	//PpEngine::IDevicePtr m_oPpDevice;
	CXProtocolDevice *m_oPpDevice;
	DWORD m_dwID;;
	BOOL m_bIsInConnecting;

#ifndef _PSX_QT_LINUX_
	//2020-11-25 lijunqing
	CPpSttCommConfig m_oCommConfig;   //2023-3-16  lijunqing CDataGroup >> CPpSttCommConfig
#endif
#endif

	CString m_strPpTemplateFile;
	CString m_strDeviceModelFile;
	CString m_strPpEngineProgID;
	CString m_strSrcDeviceModelFile;
	CString m_strEngineMode;   //2023-8-21  lijunqing 增加引擎模式属性

public:
	CPpDeviceRef();
	virtual ~CPpDeviceRef();

	void ReleaseDevice()
	{
#ifndef  _not_use_autotest_
		if (m_oPpDevice != NULL)
		{
			m_oPpDevice->Release();
			m_oPpDevice = NULL;
		}
#endif
	}

public:
	virtual UINT GetClassID()	{	return CLASSID_PPDEVICEREF;	}
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCPpDeviceRefKey;;	}
	BOOL IsDeviceConnectSucc();
	BOOL IsPpDeviceCommError();
	void ValidatePpEngineProgID(const CString &strPpEngineProgID);

#ifndef  _not_use_autotest_
	long SetCommConfig(CDataGroup *pCmmConfig);
	long SetCommConfig(const CString &strCommConfig);
	void CommConfig();
	void SetConnectState(BOOL bState);
	CString GetCommConfig();
	CString GetCommConfigEx();
	void SetPpDeviceCommError(BOOL bState);

private:
	BOOL m_bConnected;
	BOOL m_bPpDeviceCommError;

#endif

public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

};

class CPpDeviceRefs : public CExBaseList
{
public:
	CPpDeviceRefs();
	virtual ~CPpDeviceRefs()	{								}

	BOOL m_bPpxmlAdvance;  //2023-8-21  感觉这个没有什么用途，暂时保留
	long m_nInitBy;  //CPpDeviceRefs根据什么进行初始化的

public:
	void CreateAllDeviceForEdit(CExBaseList &oListCpus, const CString &strPpEngineID);
	void ReleaseAllDevice();

	void InitBy_NONE()	{	m_nInitBy = DeviceRefs_InitBy_NONE;		}
	void InitBy_CreateTest()	{	m_nInitBy = DeviceRefs_InitBy_CreateTest;		}
	void InitBy_CommConfig()	{	m_nInitBy = DeviceRefs_InitBy_CommConfig;		}
	void InitBy_CPUS()	{	m_nInitBy = DeviceRefs_InitBy_CPUS;		}

	BOOL HasInit()	{	return m_nInitBy != DeviceRefs_InitBy_NONE;	}
	BOOL HasInit_ByCreateTest()	{	return m_nInitBy == DeviceRefs_InitBy_CreateTest;	}

#ifndef  _not_use_autotest_
	BOOL IsAllDeviceConnectSucc();
	void CreateAllDevice(CExBaseList &oListCpus, const CString &strPpEngineID
		, const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strEngineMode, BOOL bUseOwn);
	CProtocolDeviceInterface* FindByID(DWORD dwID);
	CPpDeviceRef* FindPpDeviceRef(DWORD dwID);
	CPpDeviceRef* GetPpDeviceRefToConnect();
	CPpDeviceRef* GetPpDeviceConnecting();
	
	CProtocolDeviceInterface* Find(long nDeviceIndex, long nCommCmdCurrDeviceIndex);
#endif

	BOOL ValidatePpDeviceRefs();

public:
	virtual UINT GetClassID()	{	return CLASSID_PPDEVICEREFS;	}
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCPpDeviceRefsKey;	}

	virtual BOOL CopyOwn(CBaseObject* pDest);

};
