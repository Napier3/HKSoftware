//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDatasMngr.h  CIecCfgDevice

#pragma once

#include "IecCfgDatasMngr.h"
#ifdef IecCfg_With_SCL  
#include "../SCL/SclIecCfgDatas.h"
#endif

#include "../../../Module/XfileMngrBase/XFileMngr.h"


class CIecCfgDevice : public CExBaseList
{
public:
	CIecCfgDevice();
	virtual ~CIecCfgDevice();

	BOOL m_bModified;
	long m_nDeviceID;
	long m_nType;//zhouhj 20201204 �����ļ���ʹ������  0��ʶ��ͨ�����������ļ���0��ʶAT02D�����ļ�

	CString m_strIcdFile;
#ifdef IecCfg_With_SCL
	CSclIed *m_pSclIed;
#endif

public:
	static CString GetIecfgDeviceFile(CWnd *pParent, CXFileMngr *pFileMngr);
#ifdef _use_CIecCfgTool
	static CString GetIecfgDeviceFile(CWnd *pParent);
#endif

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void SetFiber2IndexByFiberIndex(long nOffset);//zhouhj ����Fiber����Fiber2

#ifdef IecCfg_With_SCL
	void InitSclRef(CIecCfgDatasMngr *pIecCfgDatasMngr);
//˽�г�Ա����
private:
	void InitSclRef(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclIed *pIed);

	void InitSclRef(CIecCfgGinDatas *pGinDatas, CSclIed *pIed);
	void InitSclRef(CIecCfgDatasSMV *pDatasSMV, CSclIed *pIed);
	void InitSclRef(CIecCfgGoutDatas *pGoutDatas, CSclIed *pIed);

	void InitSclRef(CIecCfg92Data *pData92, CSclCtrlsSmvIn *pSclSvIns);

	void InitSclRef(CIecCfgGoutData *pCfgGout, CSclCtrlsGsIn *pSclGsIns);
#endif

	
//˽�г�Ա�������ʷ���
public:
	BOOL OpenIecCfgFile(const CString &strFile);
	BOOL SaveAsIecCfgFile();
	BOOL SaveAsIecCfgFile(const CString &strFile,BOOL bIsAT02D_CFG = FALSE);//�ܺ�� 20200616  ����AT02����

	CIecCfgDatasMngr* CreateIecCfgDatasMngr(long nCfgDataCount=1);
#ifdef IecCfg_With_SCL
	void SetSclIed(CSclIed *pIed);
#endif
	void InitIecfgDataType(CDataType *pDataType);
	void UpdateGinChMaps();//20220505 zhouhj  ���¿���ͨ��ӳ�� ��Ҫ���ڿ���ͨ��ӳ������ȫ�������޸ĺ�,�˴�ͳһ����

	//yyj
	CIecCfgDatasMngr* m_pCurrDatasMngr;
	void SetCurrDatasMngr(CIecCfgDatasMngr* pDatasMngr){	m_pCurrDatasMngr = pDatasMngr; }
	CIecCfgDatasMngr* GetCurrDatasMngr()	{	return m_pCurrDatasMngr;	}

	CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);
};
