//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg92InData.h  IecCfg92InData

#pragma once

#include "IecCfg92Data.h"

class CIecCfg92InData : public CIecCfg92Data
{
public:
	CIecCfg92InData();
	virtual ~CIecCfg92InData();
	long m_nInitUseFlag;//增加判断是否初始化使用标记,在探测到指定AppID控制块后,如果该控制块在之前已经设置过勾选通道,则以之前为准

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92INPUTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData92InKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg92In.xml");	}
	virtual DWORD GetAppID() {return m_dwAppID;}

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void GetQualityList(CIecCfg92ChQualityList *pList);

#ifdef _USE_IN_AT02D_MODE_
	virtual void AddAT02D_Dataset(CDvmDataset *pCurDataset,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	virtual void AT02D_MapChannelID(CIecCfg92Data *pIecCfg92Data);
	virtual BOOL HasCurAndVolChannelType();
#endif

};

