//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasSMV.h  CIecCfgDatasSmvIn

#pragma once

#include "IecCfgSMVDatas.h"
#include "IecCfg2MInData.h"
#include "IecCfg6044CommonInData.h"

class CIecCfgDatasSmvIn : public CIecCfgDatasSMV
{
public:
	CIecCfgDatasSmvIn();
	virtual ~CIecCfgDatasSmvIn();

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASSMVINPUT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasSmvInKey();     }
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
	
	virtual long GetCurSmvTypeClassID();//获取当前报文类型的ClassID

	virtual long GetMaxCfgDataCount()	{	return 8;	}
	virtual long GetMaxCfgDataCount(UINT nClassID);
	virtual void ChangePosition(long nIndex1, long nIndex2);//对于链表中包含CIecCfgSmvRates对象的情况，序号将该对象放于最后

//私有成员变量访问方法
public:
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();

	virtual CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);
	virtual BOOL IsAppID_Repeat(DWORD dwAppID);

	virtual BOOL IsSmvData_AllSmvType(CExBaseObject *pObj);//zhouhj 2023.10.18 此函数不判别当前SMV输出类型,只要是SMV类型即返回true

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);// 周宏军 20200611 增加用于AT02D配置文件生成
	virtual void AddAT02D_dsSV(CDvmLogicDevice *pLDevice,long &nDatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	virtual BOOL IsAT02D_Invalid();
#endif
};

