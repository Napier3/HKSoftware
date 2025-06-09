//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataSmvChBase.h  CIecCfgDataSmvChBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataChBase.h"
#include <math.h>


class CIecCfgDataSmvChBase : public CIecCfgDataChBase
{
public:
	CIecCfgDataSmvChBase();
	virtual ~CIecCfgDataSmvChBase();


	CString  m_strChType;
	float  m_fCoef;
	long   m_nUseException;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASMVCHBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataSmvChBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();
	virtual long GetPhID(UINT nDefault=UI_CH_INDEX_A);
	virtual void InitCh();

protected:
	CString InitForSclRead_AppID(long &nUChIndex, long &nIChIndex);
	CString InitForSclRead_ChType();
	CString InitForSclRead_ChType(const CString &strName);

//私有成员变量
private:
	CString InitForSclRead_AppID_Ph();
	CString InitForSclRead_AppID_UI();
	CString InitForSclRead_AppID_Index(BOOL bIsUCh, long &nUChIndex, long &nIChIndex, CString &strPhase);

//私有成员变量访问方法
public:
// 	virtual BYTE GetChFlagHcn(long &nFlag, long &nHcn);
	virtual WORD GetAppChIndex();
// 	virtual DWORD InitArtAmpDigdata(CArtAmpDigdata *pData);
	virtual CString GetChTypeID()	{	return m_strID;	}
	virtual void SetChTypeID(const CString &strLnClass)	{};
	virtual void OnChTypeIDChanged(const CString &strChTypeID)	{};
	virtual void SetAppChIndex(long nIndex);
	virtual void InitChTypeID_Name(const CString &strName=_T(""));

public:
	//2023/10/24 wjs set直流电压、电流
	void SetDcAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent=TRUE);

	void SetAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent=TRUE);
	void SetAppCh_U(const CStringArray &astrUChs, long &nChIndex, long nMaxChs=3, BOOL bIntelligent=TRUE);
	void SetAppCh_I(const CStringArray &astrIChs, long &nChIndex, long nMaxChs=3, BOOL bIntelligent=TRUE);
	void SetAppCh_0(BOOL bSetU, BOOL bSetI);

	//从0开始标识,0代表第一组
	void SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3);//切换通道映射 zhouhj 2023.12.27

protected:
	void SetAppCh(const CStringArray &astrChs);
};

