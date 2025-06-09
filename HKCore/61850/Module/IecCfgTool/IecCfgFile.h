//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CIECCFGFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CIecCfgFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
#ifndef _PSX_IDE_QT_
	CFrameWnd *m_pRefFrameWnd;
#endif

//˽�г�Ա�������ʷ���
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
	virtual BOOL Save(BOOL bIsAT02D_CFG = FALSE);//�ܺ�� 20200616  ����AT02����
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
