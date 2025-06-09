//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasSMV.h  CIecCfgDatasSMV

#pragma once

// #include "IecCfgDataMngrGlobal.h"

#include "IecCfgDatasBase.h"
#include "IecCfg91Data.h"
#include "IecCfg92Data.h"
#include "IecCfg6044Data.h"
#include "IecCfg6044CommonData.h"
#include "IecCfgSmvRates.h"
#include "IecCfg92InData.h"
#include "IecCfg2MData.h"
#include "../../../Module/DataMngr/DataGroup.h"

static const CString g_strSmvType91		= _T("9-1");
static const CString g_strSmvType92		= _T("9-2");
static const CString g_strSmvType6044	= _T("6044-8");
static const CString g_strSmvType6044Common	= _T("6044-8-common");
static const CString g_strSmvType2M	= _T("2M");

#define SMVTYPE_91              0
#define SMVTYPE_92              1
#define SMVTYPE_6044            2
#define SMVTYPE_6044_COMMON     3
#define SMVTYPE_2M              4

inline long iecfg_GetSmvTypeByString(const CString &strSmvType)
{
	if (strSmvType == g_strSmvType91)
	{
		return SMVTYPE_91;
	}

	if (strSmvType == g_strSmvType92)
	{
		return SMVTYPE_92;
	}

	if (strSmvType == g_strSmvType6044)
	{
		return SMVTYPE_6044;
	}

	if (strSmvType == g_strSmvType6044Common)
	{
		return SMVTYPE_6044_COMMON;
	}

	if (strSmvType == g_strSmvType2M)
	{
		return SMVTYPE_2M;
	}

	return SMVTYPE_92;
}

inline CString iecfg_GetSmvTypeByID(long nSmvID)
{
	if (nSmvID == SMVTYPE_91)
	{
		return g_strSmvType91;
	}

	if (nSmvID == SMVTYPE_92)
	{
		return g_strSmvType92;
	}

	if (nSmvID == SMVTYPE_6044)
	{
		return g_strSmvType6044;
	}

	if (nSmvID == SMVTYPE_6044_COMMON)
	{
		return g_strSmvType6044Common;
	}

	if (nSmvID == SMVTYPE_2M)
	{
		return g_strSmvType2M;
	}
	return g_strSmvType92;
}

class CIecCfgDatasSMV : public CIecCfgDatasBase
{
public:
	CIecCfgDatasSMV();
	virtual ~CIecCfgDatasSMV();


	CString  m_strSmvType;
	CString m_strFT3_ProtocolID;//20240712 suyang 增加永远判断当前FT3报文类型
	long  m_nFT3CRCType;//0-标准16字节校验，1-报文末尾校验，2-第一个数据块14字节校验
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASSMV;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasSMVKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual UINT GetIecCfgDataClassID();

	virtual BOOL IsCfgData(UINT nClassID)	{	return IsSmvData(nClassID);	}
	
	long GetSmvType()		{	return iecfg_GetSmvTypeByString(m_strSmvType);	}
	virtual long GetCurSmvTypeClassID();//获取当前报文类型的ClassID
	BOOL SetSmvType(long nSmvType);
	BOOL IsSmvType91()		{	return (SMVTYPE_91 == GetSmvType());	}
	BOOL IsSmvType92()		{	return (SMVTYPE_92 == GetSmvType());	}
	BOOL IsSmvType6044()		{	return (SMVTYPE_6044 == GetSmvType());	}
	BOOL IsSmvType6044Common()		{	return (SMVTYPE_6044_COMMON == GetSmvType());	}
	BOOL IsSmvType2M()		{	return (SMVTYPE_2M == GetSmvType());	}

	BOOL IsSmvData(UINT nClassID);
	BOOL IsSmvData(CExBaseObject *pObj);
	virtual BOOL IsSmvData_AllSmvType(CExBaseObject *pObj);//zhouhj 2023.10.18 此函数不判别当前SMV输出类型,只要是SMV类型即返回true
	virtual long GetMaxCfgDataCount()	{	return /*8*/g_nIecCfgSmvOut_91_92MaxNum;	}//wangtao 20240510 改成全局变量
	virtual long GetMaxCfgDataCount(UINT nClassID);
	virtual void ChangePosition(long nIndex1, long nIndex2);//对于链表中包含CIecCfgSmvRates对象的情况，序号将该对象放于最后

	void GenerateSmv_GroupDatas(CDataGroup *pSmv);
	void ReadSmv_GroupDatas(CDataGroup *pSmv);

//私有成员变量
protected:
	CIecCfgSmvRates *m_pIecCfgSmvRates;
	CIecCfgDataSmvCommon m_oIecCfgDataSmvCommon;
	void FreeCfgDatas();

//私有成员变量访问方法
public:
	void InitCfgDatasByCommon();
	void InitCommonFromCfgDatas();
	CIecCfgDataSmvCommon* GetCommonData()	{	return &m_oIecCfgDataSmvCommon;	}

	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();
	CIecCfgSmvRates* GetIecCfgSmvRates();

	virtual CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);
	virtual BOOL IsAppID_Repeat(DWORD dwAppID);
	CIecCfg92Data* FindByAppIDFiber(DWORD dwAppID,long nFiberIndex);//光口号小于0,则不判光口
	CIecCfgDataBase* FindByFiber_60044Common(long nFiberIndex);

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);// 周宏军 20200611 增加用于AT02D配置文件生成
	virtual void AddAT02D_dsSV(CDvmLogicDevice *pLDevice,long &nDatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	virtual BOOL IsAT02D_Invalid();
#endif
};

