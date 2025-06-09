//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91Ch.h  CIecCfg91Ch

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataSmvChBase.h"


class CIecCfg91Ch : public CIecCfgDataSmvChBase
{
public:
	CIecCfg91Ch();
	virtual ~CIecCfg91Ch();


	DWORD  m_dwStateWord;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91CH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91ChKey();     }
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

};

