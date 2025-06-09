//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSysParas.h  CIecCfgSysParas

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgPrimRates.h"
#include "IecCfgPrimRatesIn.h"
#include "IecCfgFiberParas.h"
#include "IecCfgFiberParasIn.h"



class CIecCfgSysParas : public CExBaseList
{
public:
	CIecCfgSysParas();
	virtual ~CIecCfgSysParas();


	long  m_nPkgSendType;
//	long  m_nSecSyn;
// 	long  m_nBCodeLogic;
// 	long  m_nIec1588Type;
	long  m_nPrimParas;//参数设置选择 0-二次值 1-一次值,缺省采用二次值(与系统参数中的该值定义相反)
	long  m_nPrimOutput;//报文输出选择 0-二次值 1-一次值,缺省采用一次值(与系统参数中的该值定义相反)
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSYSPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSysParasKey();     }
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
	CIecCfgPrimRates *m_pPrimRates;
	CIecCfgPrimRatesIn *m_pPrimRatesIn;
	CIecCfgFiberParas *m_pFiberParas;
	CIecCfgFiberParasIn *m_pFiberParasIn;
//私有成员变量访问方法
public:
	CIecCfgPrimRates* GetPrimRates();
	CIecCfgPrimRatesIn* GetPrimRatesIn();
	CIecCfgFiberParas* GetFiberParas();
	CIecCfgFiberParasIn* GetFiberParasIn();
//属性变量访问方法
public:
	void InitPrimRatesFiberParas(long nCT_GroupNum,long nPT_GroupNum,long nFiberLC_Num,long nFiberST_Num);//zhouhj 20210316 初始化CT、PT变比及光口映射参数
};

