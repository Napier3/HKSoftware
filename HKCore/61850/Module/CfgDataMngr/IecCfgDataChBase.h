//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataChBase.h  CIecCfgDataChBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "../GlobalDataMngr/IecGlobalDataMngr.h"

class CIecCfgDataChBase : public CExBaseObject
{
public:
	CIecCfgDataChBase();
	virtual ~CIecCfgDataChBase();


	long  m_nUseFlag;
	long  m_nIndex;
	CString  m_strAppChID;
	CString  m_strDevChID;
	CString  m_strMapDataID;

	CExBaseObject *m_pScdObjRef; //关联的SCD数据对象

	CExBaseObject* GetAncestorIecCfgData();
	
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATACHBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataChBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitCh();


//私有成员变量
private:
// 	CArtAmpDigdata *m_pArtAmpDigdata;

//私有成员变量访问方法
public:
// 	virtual BYTE GetChFlagHcn(long &nFlag, long &nHcn)	{	nFlag = 1;	nHcn = 0x7F;	return 0xFF;	}
	virtual BOOL IsChUse();
	virtual BOOL IsTimeCh();
	virtual BOOL IsZeroCh();
	virtual BOOL IsAppCh();
	virtual BOOL IsUCh();
	virtual BOOL IsICh();
	virtual BOOL IsTCh();

// 	virtual void SetArtAmpDigdata(CArtAmpDigdata *pArtAmpDigdata)	{	m_pArtAmpDigdata = pArtAmpDigdata;	}
// 	virtual DWORD InitArtAmpDigdata(CArtAmpDigdata *pArtAmpDigdata);
// 	virtual DWORD CalMagAndOffset(CArtAmpDigdata *pArtAmpDigdata);
// 	virtual DWORD GetMagAndOffset(float &dwMag, float &dwOffset);

	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);

private:
//	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
//	virtual DWORD CalMagAndOffset(float &dwMag, float &dwOffset);

};

