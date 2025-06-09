//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg6044Ch.h  CIecCfg6044Ch

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataSmvChBase.h"


class CIecCfg6044CommonCh : public CIecCfgDataSmvChBase
{
public:
	CIecCfg6044CommonCh();
	virtual ~CIecCfg6044CommonCh();

	long m_nChLenth;
	long m_nValue;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg6044CommonChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);
	virtual void SetChTypeID(const CString &strLnClass);
	virtual void InitAfterRead();
	long GetChAngType();//202434 zhouhj 获取当前相位类别 A相1/2/3/4/5/6

};

