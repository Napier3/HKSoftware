//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGoutCh.h  CIecCfgGoutCh

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataGooseChBase.h"


class CIecCfgGoutCh : public CIecCfgDataGooseChBase
{
public:
	CIecCfgGoutCh();
	virtual ~CIecCfgGoutCh();

	CString m_strAddrExternal;
	CString m_strDescExternal;
	CString m_strDefaultValue;
	long    m_nIndexExternal;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOUTCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGoutChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();


//私有成员变量
private:

//私有成员变量访问方法
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
	BYTE Get_hbo();
	BOOL IsDefaultValue();
	void CheckDefautValue();//zhouhj 20210912 用于检查设置缺省值,如其不满足对应数据类型要求,则将其改为满足要求的字符串

// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// 	{
// 		pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_GOOSEOUT;
// 		return 0;
// 	}

protected:
	void CheckDefautValue_ChTypeSingle();
	void CheckDefautValue_ChTypeDouble();
	void CheckDefautValue_ChTypeQuality();
	void CheckDefautValue_ChTypeFloat();
	void CheckDefautValue_ChTypeString();
	void CheckDefautValue_ChTypeInteger();
	void CheckDefautValue_ChTypeUInteger();
};

