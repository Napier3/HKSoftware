#pragma once
#include "DeviceCmmConfig.h"
//#include "PpDevice.h"
//#include "DeviceModelDefine.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../../../Module/DataMngr/DvmDevices.h"

/*
<device-model>
	<comm-config>
	</comm-config>
	<device tempfile="MonitorDeviceModel.xml">
	</device>
</device-model>
*/

// #define ATTRID_NUMOFSG      _T("NUMOFSG")
// #define ATTRID_ACTSG        _T("ACTSG")
// #define ATTRID_TMTOTAL      _T("TMTOTAL")
// #define ATTRID_TMEXEC       _T("TMEXEC")
// #define ATTRID_TMSEL        _T("TMSEL")
// #define ATTRID_ERRINFO      _T("ERRINFO")
// #define ATTRID_RECORD_PATH  _T("RECORD_PATH")
// 
// #define ATTRID_InfoEXEC  _T("InfoEXEC")
// #define ATTRID_InfoSEL  _T("InfoSEL")
// #define ATTRID_TimeGapEnaWrite  _T("TimeGapEnaWrite")
// #define ATTRID_TimeGapSelExec  _T("TimeGapSelExec")
// #define ATTRID_LogMmsMsg  _T("LogMmsMsg")
// 
// #define ATTRID_InfoSetSE  _T("InfoSetSE")
// #define ATTRID_InfoSetSG  _T("InfoSetSG")
// #define ATTRID_tmSetSE       _T("TMSETSE")
// #define ATTRID_tmSetSG        _T("TMSETSG")
// #define ATTRID_InfoWriteData  _T("InfoWriteData")
// #define ATTRID_TestLinkState  _T("TestLinkState")
// #define ATTRID_EnaReadBeforeWrite  _T("ReadBeforeEnaWrite")
// #define ATTRID_TEnaReadBeforeWrite  _T("ReadBeforeEnaWriteT")
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

/*
	2016-12-21
	如果是多数据模型文件，则m_pDevice作为报告设备
	用于专门处理soe、package等数据
*/
class CPpDvmDevice : public CExBaseList
{
public:
	CPpDvmDevice();
	virtual ~CPpDvmDevice();

public:
	CDvmDevice *m_pDevice;
	CDvmDevices *m_pDevices;
	UINT m_nDvmDeviceMode;// = PPTEMPLATE_DEVICEMODE_SINGLE

public:
	virtual UINT GetClassID(){return DMCLASSID_PPDEVICE;};
	BOOL OpenDeviceFile(const CString &strFile);
	void IinitProtocolTestDvmAttrs();
	CExBaseList* GetDeviceModel();

	BOOL GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue);
	BOOL SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue);

	BOOL IsDeviceModel_Single()	{	return PPTEMPLATE_DEVICEMODE_SINGLE == m_nDvmDeviceMode;	}
	BOOL IsDeviceModel_Multi()	{	return PPTEMPLATE_DEVICEMODE_MULTI == m_nDvmDeviceMode;	}
};


class CDevcieModel :	public CExBaseList
{
public:
	CDevcieModel(void);
	virtual ~CDevcieModel(void);

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICEMODEL;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelKey;     }


	//串行化;
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//打开文件
	BOOL OpenFile(const CString &strFile);
	//BOOL OpenXmlFile(const CString &strFile);

	//保存文件
	BOOL SaveFile(const CString &strFile);
	BOOL SaveXmlFile(const CString &strFile);
	BOOL Save();

	CDeviceCmmConfig* GetDeviceCmmConfig()
	{
		if (m_pDeviceCmmConfig == NULL)
		{
			m_pDeviceCmmConfig = new CDeviceCmmConfig();
			AddNewChild(m_pDeviceCmmConfig);
			m_pDeviceCmmConfig->AddConfigSerial();
		}

		return m_pDeviceCmmConfig;
	}

	CExBaseList* GetDevice()
	{
		if (m_pPpDevice == NULL)
		{
			m_pPpDevice = new CPpDvmDevice();
			AddNewChild(m_pPpDevice);
		}

		return m_pPpDevice->GetDeviceModel();
	}

	CPpDvmDevice* GetPpDevice()
	{
		if (m_pPpDevice == NULL)
		{
			m_pPpDevice = new CPpDvmDevice();
			AddNewChild(m_pPpDevice);
		}

		return m_pPpDevice;
	}

private:
	CDeviceCmmConfig *m_pDeviceCmmConfig;
	//CDvmDevice *m_pDevice;
	CPpDvmDevice *m_pPpDevice;

public:
	/************************************************************************/
	/* 2011-01-13 添加 用于点表编辑
	*/
	/************************************************************************/
	void InsertNodeToTreeCtrl(CTreeCtrl* pTreeCtrl,HTREEITEM htiParent);

    //2020-5-19  lijunqing
    BOOL InitCmmConfig(CDataGroup *pGroup);

private:
	CString m_strDeviceModelFile;
	CString GetDeviceCmmCfgFile();
};

CString pp_GetDeviceCmmCfgFile(const CString &strDeviceFile);
