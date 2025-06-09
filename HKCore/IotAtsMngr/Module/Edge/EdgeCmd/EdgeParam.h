//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParam.h  CEdgeParam

#pragma once

#include "EdgeCmdMngrGlobal.h"

#include "EdgeParaDatas.h"

#include "EdgeParas.h"
#include "EdgeDev.h"
#include "EdgeCpu.h"
#include "EdgeMem.h"
#include "EdgeDisk.h"
#include "EdgeOs.h"
#include "EdgeLinks.h"
#include "EdgeMemUsed.h"
#include "EdgeTemperature.h"
#include "EdgeRepPeriod.h"
#include "EdgeFile.h"
#include "EdgeImage.h"
#include "EdgeWithApp.h"
#include "EdgeCpuLmt.h"
#include "EdgeMemLmt.h"
#include "EdgeDiskLmt.h"
#include "EdgeCfgCpu.h"
#include "EdgeCfgMem.h"
#include "EdgeCfgDisk.h"
#include "EdgeData.h"

#include "EdgeCmdErrorMngr.h"

class CEdgeParam : public CEdgeParaDatas
{
public:
	CEdgeParam();
	virtual ~CEdgeParam();


//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEPARAM;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeParamKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CEdgeParas *m_pEdgeParas;
	CEdgeCpu *m_pEdgeCpu;
	CEdgeCpuLmt *m_pEdgeCpuLmt;
	CEdgeDev *m_pEdgeDev;
	CEdgeDisk *m_pEdgeDisk;
	CEdgeDiskLmt *m_pEdgeDiskLmt;
	CEdgeFile *m_pEdgeFile;
	CEdgeImage *m_pEdgeImage;
	//yzj 2021-10-17 links数组特殊处理
	//CEdgeLinks *m_pEdgeLinks;
	CEdgeMem *m_pEdgeMem;
	CEdgeMemLmt *m_pEdgeMemLmt;
	CEdgeMemUsed *m_pEdgeMemUsed;
	CEdgeOs *m_pEdgeOs;
	CEdgeRepPeriod *m_pEdgeRepPeriod;
	CEdgeTemperature *m_pEdgeTemperature;
	CEdgeWithApp *m_pEdgeWithApp;
	//yzj 2021-9-6 增加cfgCpu等
	CEdgeCfgCpu* m_pEdgeCfgCpu;
	CEdgeCfgMem* m_pEdgeCfgMem;
	CEdgeCfgDisk* m_pEdgeCfgDisk;

	CJSON* m_pDeviceInfosJson;
	CJSON* m_pDeviceIdsJson;
	CJSON* m_pMountJson;
	CJSON* m_pDevJson;
	CJSON* m_pDeviceDataJson;
	CJSON* m_pContParaJson;
	CJSON* m_pLinksJson;
	CJSON* m_pLinkStateJson;
	CJSON* m_pAppsJson;
	CJSON* m_pContStatusJson;
	CJSON* m_pAppCfgsJson;

//私有成员变量访问方法
public:
	CEdgeParas* GetEdgeParas()	{	return m_pEdgeParas;	}
	void SetEdgeParas(CEdgeParas* pEdgeParas)	{	m_pEdgeParas = pEdgeParas; AddTail(pEdgeParas); }
	CEdgeCpu* GetEdgeCpu()	{	return m_pEdgeCpu;	}
	void SetEdgeCpu(CEdgeCpu* pEdgeCpu)	{	m_pEdgeCpu = pEdgeCpu; AddTail(pEdgeCpu); }
	CEdgeCpuLmt* GetEdgeCpuLmt()	{	return m_pEdgeCpuLmt;	}
	void SetEdgeCpuLmt(CEdgeCpuLmt* pEdgeCpuLmt)	{	m_pEdgeCpuLmt = pEdgeCpuLmt; AddTail(pEdgeCpuLmt);}
	CEdgeDev* GetEdgeDev()	{	return m_pEdgeDev;	}
	void SetEdgeDev(CEdgeDev* pEdgeDev)	{	m_pEdgeDev = pEdgeDev;AddTail(pEdgeDev);}
	CEdgeDisk* GetEdgeDisk()	{	return m_pEdgeDisk;	}
	void SetEdgeDisk(CEdgeDisk* pEdgeDisk)	{	m_pEdgeDisk = pEdgeDisk;AddTail(pEdgeDisk);}
	CEdgeDiskLmt* GetEdgeDiskLmt()	{	return m_pEdgeDiskLmt;	}
	void SetEdgeDiskLmt(CEdgeDiskLmt* pEdgeDiskLmt)	{	m_pEdgeDiskLmt = pEdgeDiskLmt;AddTail(pEdgeDiskLmt);}
	CEdgeFile* GetEdgeFile()	{	return m_pEdgeFile;	}
	void SetEdgeFile(CEdgeFile* pEdgeFile)	{	m_pEdgeFile = pEdgeFile;AddTail(pEdgeFile);}
	CEdgeImage* GetEdgeImage()	{	return m_pEdgeImage;	}
	void SetEdgeImage(CEdgeImage* pEdgeImage)	{	m_pEdgeImage = pEdgeImage;AddTail(pEdgeImage);}
	CEdgeMem* GetEdgeMem()	{	return m_pEdgeMem;	}
	void SetEdgeMem(CEdgeMem* pEdgeMem)	{	m_pEdgeMem = pEdgeMem;AddTail(pEdgeMem);}
	CEdgeMemLmt* GetEdgeMemLmt()	{	return m_pEdgeMemLmt;	}
	void SetEdgeMemLmt(CEdgeMemLmt* pEdgeMemLmt)	{	m_pEdgeMemLmt = pEdgeMemLmt;AddTail(pEdgeMemLmt);}
	CEdgeMemUsed* GetEdgeMemUsed()	{	return m_pEdgeMemUsed;	}
	void SetEdgeMemUsed(CEdgeMemUsed* pEdgeMemUsed)	{	m_pEdgeMemUsed = pEdgeMemUsed;AddTail(pEdgeMemUsed);}
	CEdgeOs* GetEdgeOs()	{	return m_pEdgeOs;	}
	void SetEdgeOs(CEdgeOs* pEdgeOs)	{	m_pEdgeOs = pEdgeOs;AddTail(pEdgeOs);}
	CEdgeRepPeriod* GetEdgeRepPeriod()	{	return m_pEdgeRepPeriod;	}
	void SetEdgeRepPeriod(CEdgeRepPeriod* pEdgeRepPeriod)	{	m_pEdgeRepPeriod = pEdgeRepPeriod;AddTail(pEdgeRepPeriod);}
	CEdgeTemperature* GetEdgeTemperature()	{	return m_pEdgeTemperature;	}
	void SetEdgeTemperature(CEdgeTemperature* pEdgeTemperature)	{	m_pEdgeTemperature = pEdgeTemperature;AddTail(pEdgeTemperature);}
	CEdgeWithApp* GetEdgeWithApp()	{	return m_pEdgeWithApp;	}
	void SetEdgeWithApp(CEdgeWithApp* pEdgeWithApp)	{	m_pEdgeWithApp = pEdgeWithApp;AddTail(pEdgeWithApp);}
	CEdgeCfgCpu* GetEdgeCfgCpu()	{	return m_pEdgeCfgCpu;	}
	void SetEdgeCfgCpu(CEdgeCfgCpu* pEdgeCfgCpu)	{	m_pEdgeCfgCpu = pEdgeCfgCpu; AddTail(pEdgeCfgCpu);}
	CEdgeCfgMem* GetEdgeCfgMem()	{	return m_pEdgeCfgMem;	}
	void SetEdgeCfgMem(CEdgeCfgMem* pEdgeCfgMem)	{	m_pEdgeCfgMem = pEdgeCfgMem; AddTail(pEdgeCfgMem);}
	CEdgeCfgDisk* GetEdgeCfgDisk()	{	return m_pEdgeCfgDisk;	}
	void SetEdgeCfgDisk(CEdgeCfgDisk* pEdgeCfgDisk)	{	m_pEdgeCfgDisk = pEdgeCfgDisk; AddTail(pEdgeCfgDisk);}

	CJSON* GetDeviceIdsJson()	{ return m_pDeviceIdsJson; }
	CJSON* GetMountJson()	{ return m_pMountJson; }
	CJSON* GetDevJson()	{ return m_pDevJson; }
	CJSON* GetDeviceDataJson()	{ return m_pDeviceDataJson; }
	CJSON* GetContParaJson()	{ return m_pContParaJson; }
	CJSON* GetLinksJson()	{ return m_pLinksJson; }
	CJSON* GetLinkStateJson()	{ return m_pLinkStateJson; }
	CJSON* GetAppsJson()	{ return m_pAppsJson; }
	CJSON* GetContStatusJson() {return m_pContStatusJson; }
	CJSON* GetAppCfgsJson() {return m_pAppCfgsJson; }
	CJSON* GetDeviceInfosJson() {return m_pDeviceInfosJson; }
	void SetContParaJson(CJSON* pContParaJson)	{ m_pContParaJson = pContParaJson; }
	void SetDeviceIdsJson(CJSON* pDeviceIdsJson)	{ m_pDeviceIdsJson = pDeviceIdsJson; }
	void SetMountJson(CJSON* pMountJson)	{ m_pMountJson = pMountJson; }
	void SetDevJson(CJSON* pDevJson)	{ m_pDevJson = pDevJson; }
	void SetDeviceDataJson(CJSON* pDeviceData)	{ m_pDeviceDataJson = pDeviceData; }
	void SetLinksJson(CJSON* pLinks)	{ m_pLinksJson = pLinks; }
	void SetLinkStateJson(CJSON* pLinkState)	{ m_pLinkStateJson = pLinkState; }
	void SetAppsJson(CJSON* pApps)	{ m_pAppsJson = pApps; }
	void SetContStatusJson(CJSON* pContStatusJson) { m_pContStatusJson = pContStatusJson; }
	void SetAppCfgsJson(CJSON* pAppCfgsJson) { m_pAppCfgsJson = pAppCfgsJson; }
	void SetDeviceInfosJson(CJSON* pDeviceInfosJson) { m_pDeviceInfosJson = pDeviceInfosJson; }
//属性变量访问方法
public:
};

