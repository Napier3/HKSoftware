//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasGin.h  CIecCfgDatasGin

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDatasBase.h"
#include "IecCfgGinData.h"
#include "IecCfgGinAppChMaps.h"
#include "../../../Module/DataMngr/DvmLogicDevice.h"

class CIecCfgGinDatas : public CIecCfgDatasBase
{
public:
	CIecCfgGinDatas();
	virtual ~CIecCfgGinDatas();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASGIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasGinKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual UINT GetIecCfgDataClassID();
	virtual BOOL IsCfgData(UINT nClassID)	{	return (nClassID == CFGCLASSID_CIECCFGGINDATA);	}
	virtual BOOL IsCfgData(CExBaseObject *pObj);
	virtual long GetMaxCfgDataCount()	{	return /*16*/g_nIecCfgGinMaxNum;	}//wangtao 20240510 改成全局变量
	virtual long GetMaxCfgDataCount(UINT nClassID)	{	return /*16*/g_nIecCfgGinMaxNum;	}
	void GenerateGins_GroupDatas(CDataGroup *pGins);//将初始值填入DataGroup
	void ReadGins_GroupDatas(CDataGroup *pGins);
//私有成员变量
private:
	CIecCfgGinAppChMaps m_oIecCfgGinAppChMaps;

//私有成员变量访问方法
public:
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();

	CIecCfgGinAppChMaps* GetIecCfgGinAppChMaps()	{	return &m_oIecCfgGinAppChMaps;	}
	void InitGinAppChMaps();

	CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);
	BOOL SetCfgDataGinMap(const long nContrlBlockIndex,const long nFirstMapIndex,const long nMapNum);
	BOOL IsAppID_Repeat(DWORD dwAppID);
	CIecCfgDataBase* FindByAppIDFiber(DWORD dwAppID,long nFiberIndex);

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//周宏军 20200616  增加AT02配置
	void AddAT02D_dsGin(CDvmLogicDevice *pLDevice,long &nDatasetIndex);
	BOOL IsAT02D_Invalid();
#endif
};

