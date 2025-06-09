//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgTool.h  CIecCfgTool

#pragma once

#include "IecCfgToolGlobal.h"

#include "../../../Module/DataMngr/DataTypes.h"
#include "../../../Module/XfileMngrBase/XFileMngr.h"

#include "IecCfgFiles.h"
#include "SclFiles.h"

class CIecCfgTool : public CExBaseList
{
protected:
	CIecCfgTool();
	virtual ~CIecCfgTool();

	static long g_nIecCfgTollRef;

public:
	static CIecCfgTool* g_pIecCfgTool;
	static CIecCfgTool* Create(BOOL bIxml=TRUE, BOOL bIecfg=TRUE);
	static void Release(BOOL bSave=TRUE);
	static const CString g_strIecCfgSystemConfigFile;

	static void InitAutoSetUIChIndex();
	static void SetAutoSetUIChIndex(BOOL b);
	static void SetModelUseHarm(long nUseHarm);
	static void SetVerifyVolCurChannel(long nVerifyVolCurChannel);
	static void SetLinkGout(long nLinkGout);
	static void SetAutoOpenLast(long nAutoOpenLast);
	static BOOL GetAutoSetUIChIndex();
	static BOOL IsModelUseHarm();
	static BOOL IsVerifyVolCurChannel();
	static BOOL LinkGout();
	static BOOL IsAutoOpenLast();

	static void AdjustIecCfgFile(CIecCfgFile *pIecfgFile);
	static CIecCfgFile* NewIecCfgFile(const CString &strFileType=g_strIecCfgFilePostfix);
	static CIecCfgFile* NewIecCfgFile(CXFile *pXFile);
	static BOOL IsIecFileOpen(const CString &strFile);
	static CIecCfgFile* FindIecFile(const CString &strFile);
	static CIecCfgFile* OpenIecFile(const CString &strFile);
	static BOOL CloseIecFile(CIecCfgFile *pFile, BOOL bDelete);
	static BOOL SaveIecFile(CIecCfgFile *pFile);
	static BOOL SaveAsIecFile(CIecCfgFile *pFile);
	static BOOL HasFileInFolder(CXFolder *pFolder);

	static CXFileMngr* GetIecCfgFileMngr();
	static CXFileMngr* GetIecCfgDeviceFileMngr();
	static CIecCfgFiles* GetIecCfgFiles();
	static CSclFiles* GetSclFiles();
	static BOOL HasIecCfgFileModified(CString &strFiles);
	static CString GetIecCfgDownDllFile();
	static void SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile);
	static void SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile);

	static BOOL IsViewOnlyUsedInChs();
	static BOOL SetViewOnlyUsedInChs();
	static BOOL IsViewChsPath();
	static BOOL SetViewChsPath();//zhouhj 20211018 ��ʾͨ���ڲ�·��

	static BOOL FreeSclFileRead(CSclFile *pSclFile);
	static CString PopSelIecfgFile(CWnd *pParent);

//���غ���
public:
	virtual UINT GetClassID() {    return IFTCLASSID_CIECCFGTOOL;   }
	virtual BSTR GetXmlElementKey()  {      return CIecCfgToolXmlRWKeys::CIecCfgToolKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	long m_nAT02D_UseHarm;//�ܺ�� 20200614  AT02D����ģ��ʱ����г��
	long m_nAT02D_VerifyVolCurChannel;//�ܺ�� 20201128  AT02D���������ļ�ʱ��У����붼������ѹ����ͨ����������PNI302�������ļ�������ֻ������ѹͨ������ʱ����Ҫ��У�鹦��
	long m_nLinkGout;//�ܺ�� 20200622  ����Gout
	long m_nAutoOpenLast;//�ܺ��  20200914 �Ƿ��Զ����ϴδ򿪹��������ļ�

//˽�г�Ա����
private:
	CString  m_strUseDebug;
	CString  m_strAutoSetUIChIndex;
	BOOL m_bAutoSetUIChIndex;

	CIecCfgFiles *m_pIecCfgFiles;
	CSclFiles *m_pSclFiles;

	CXFileMngr m_oIecCfgFileMngr;
	CXFileMngr m_oIecCfgDeviceFileMngr;
	CString m_strIecCfgDownDllFile;

private:
	void _InitAutoSetUIChIndex()	{		m_bAutoSetUIChIndex = (m_strAutoSetUIChIndex != _T("manual"));	}
	void _SetAutoSetUIChIndex(BOOL b);
	void _SetModelUseHarm(long nUseHarm);
	void _SetVerifyVolCurChannel(long nVerifyVolCurChannel);
	void _SetLinkGout(long nLinkGout);
	void _SetAutoOpenLast(long nAutoOpenLast);
	BOOL _GetAutoSetUIChIndex()	{		return m_bAutoSetUIChIndex;	}

	void _AdjustIecCfgFile(CIecCfgFile *pIecfgFile);
	CIecCfgFile* _NewIecCfgFile(const CString &strFileType=g_strIecCfgFilePostfix);
	CIecCfgFile* _NewIecCfgFile(CXFile *pXFile);
	BOOL _IsIecFileOpen(const CString &strFile);
	CIecCfgFile* _OpenIecFile(const CString &strFile);
	CIecCfgFile* _FindIecFile(const CString &strFile);
	BOOL _CloseIecFile(CIecCfgFile *pFile, BOOL bDelete);
	BOOL _SaveIecFile(CIecCfgFile *pFile);
	BOOL _SaveAsIecFile(CIecCfgFile *pFile);
	BOOL _HasFileInFolder(CXFolder *pFolder);
	void _SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile);
	void _SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile);

private:
	void InitIecCfgTool(BOOL bIxml=TRUE, BOOL bIecfg=TRUE);
	void InitIecCfgTool_ixml();
	void InitIecCfgTool_iecfg();

	long Save();
	long Open();
	CString GetInitFile();
};

