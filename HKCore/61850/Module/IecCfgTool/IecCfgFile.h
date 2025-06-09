//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFile.h  CIecCfgFile

#pragma once

#include "IecCfgToolGlobal.h"

#include "../CfgDataMngr/IecCfgDevice.h"

class CIecCfgFile : public CExBaseObject
{
public:
	CIecCfgFile();
	virtual ~CIecCfgFile();

	CIecCfgDatasMngr *m_pIecCfgDatasMngr;

//重载函数
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CIECCFGFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CIecCfgFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
#ifndef _PSX_IDE_QT_
	CFrameWnd *m_pRefFrameWnd;
#endif

//私有成员变量访问方法
public:
#ifndef _PSX_IDE_QT_
	void SetRefFrameWnd(CFrameWnd *pRefRameWnd)	{	m_pRefFrameWnd = pRefRameWnd;	}
	CFrameWnd* GetRefFrameWnd()					{	return m_pRefFrameWnd;			}
#endif
	void CreateDefaultCfgDataMngr();
	
	void SetIecCfgSmvRates(CIecCfgSmvRates *pRates);
	void SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon);
	void SetIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr);

public:
	virtual BOOL IsModified();

	virtual void SetModified(BOOL bModified=TRUE);
	virtual BOOL Save(BOOL bIsAT02D_CFG = FALSE);//周宏军 20200616  增加AT02配置
	virtual BOOL SaveAs(const CString &strFile,BOOL bIsAT02D_CFG = FALSE);
	virtual BOOL Open(const CString &strFile);
	virtual BOOL Open();

	virtual CString GetName();
};

class CIecCfgFileDevice : public CIecCfgFile
{
public:
	CIecCfgFileDevice();
	virtual ~CIecCfgFileDevice();

	virtual UINT GetClassID() {    return IFTCLASSID_CIECCFGFILE_DEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CIecCfgFileDeviceKey();     }

protected:
	CExBaseList m_listIecfgFile;
	CIecCfgDevice *m_pIecCfgDevice;

public:
	CIecCfgFile* AddIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr);
	CIecCfgFile* FindIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr);
	BOOL DeleteIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr);
	CIecCfgDevice* GetIecCfgDevice()	{	return m_pIecCfgDevice;	}

	BOOL CloseIecFile(CIecCfgFile *pFile, BOOL bDelete);
	long GetOpenFileCount()	{	return m_listIecfgFile.GetCount();	}
	CExBaseList* GetListIecfgFile()	{	return &m_listIecfgFile;	}

public:
	virtual BOOL IsModified();
	virtual void SetModified(BOOL bModified=TRUE);
	virtual BOOL Save(BOOL bIsAT02D_CFG);
	virtual BOOL SaveAs(const CString &strFile,BOOL bIsAT02D_CFG = FALSE);
	virtual BOOL Open(const CString &strFile);
	virtual BOOL Open();

	CIecCfgDatasMngr* CreateIecCfgDatasMngr();
};

CIecCfgDatasSMV* iecfg_GetIecCfgDatasSMV(CIecCfgFile *pIecCfgFile);
CIecCfgDatasSmvIn* iecfg_GetIecCfgDatasSmvIn(CIecCfgFile *pIecCfgFile);
BOOL iecfg_IsIecfgFileDevice(const CString &strFile);
