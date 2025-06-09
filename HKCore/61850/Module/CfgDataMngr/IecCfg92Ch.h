//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg92Ch.h  CIecCfg92Ch

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataSmvChBase.h"

/*
模拟的合并单元的通道描述
	m_strName：名称
	m_strID：地址
外部引用的通道描述：对应保护、测控的SVIN；地址、名称为空，表示此通道对当前配置来说不使用
	m_strAddrExternal：外部地址
	m_strDescExternal：外部名称
*/

class CIecCfg92Ch : public CIecCfgDataSmvChBase
{
public:
	CIecCfg92Ch();
	virtual ~CIecCfg92Ch();

	CString m_strAddrExternal;
	CString m_strDescExternal;
	long    m_nIndexExternal;
	DWORD   m_nQuality;
	long    m_nData;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92CH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg92ChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitCh();

//私有成员变量
private:

//私有成员变量访问方法
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);

	virtual void SetChTypeID(const CString &strLnClass);
	virtual void OnChTypeIDChanged(const CString &strChTypeID);
	long GetChAngType();//20221210 zhouhj 获取当前相位类别 A相1/2/3/4/5/6
};

