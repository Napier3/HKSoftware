//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvDataBase.h  CIecCfgSmvDataBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataBase.h"
#include "IecCfgAdvanceException.h"

#include "IecCfgDataSmvCommon.h"
#include "IecCfgAdvanceException.h"

#define STSMV_CHANNEL_NUM  12


class CIecCfgSmvDataBase : public CIecCfgDataBase
{
public:
	CIecCfgSmvDataBase();
	virtual ~CIecCfgSmvDataBase();


	float  m_fUNom;
	float  m_fINom;
	float  m_fFNom;
	float  m_fICenter;
	long  m_nSampleRate;
	long  m_nAsduNum;
	long  m_bNoQuality;
	float  m_fUNom2;
	float  m_fINom2;

	CIecCfgAdvanceException *m_pException;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSMVDATABASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSmvDataBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CIecCfgAdvanceException* GetAdvanceException();
	virtual void GetCommData(CIecCfgDataSmvCommon *pCommon);
	virtual void InitByCommData(CIecCfgDataSmvCommon *pCommon);
	virtual DWORD GetAppID() {return 0;}
	virtual BOOL OpenCfgDefaultConfigFile();
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex){}

	void EmptyChsName();
	//virtual void SetCfgDataValue(long nDataID, float dValue);

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif

	virtual void UpdateChsIndex();

//////////////////////////////////////////////////////////////////////////
//
public:
	void SetAbc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetPabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetSabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetTabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Setabc5(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Setabc6(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Set0(BOOL bSetU, BOOL bSetI);
	
	//2023/10/23 wjs 添加对直流电压、电流映射的处理
	void SetDcAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent);
	void GetDcUIChs(CStringArray &astrUChs, CStringArray &astrIChs, long nUIGroupIndex);
	void SetDcAbcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetDcPabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetDcSabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetDcTabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent);

	//从0开始标识,0代表第一组
	void SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3);//zhouhj 2023.12.26 切换通道映射 如从第1组切换到第二组
	
	void SetAbc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetPabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetSabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void SetTabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Setabc5(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Setabc6(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent);
	void Set0(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI);

protected:
	void GetUIChs(CStringArray &astrUChs, CStringArray &astrIChs, long nUIGroupIndex);
	void SetAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent);
	void SetAppCh(CExBaseList &oListCh,BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent);
	void SetAppCh_0(CExBaseList &oListCh,BOOL bSetU, BOOL bSetI);
	void SetAppCh_U(CExBaseList &oListCh, const CStringArray &astrIChs, BOOL bIntelligent);
	void SetAppCh_I(CExBaseList &oListCh, const CStringArray &astrIChs, BOOL bIntelligent);
};

