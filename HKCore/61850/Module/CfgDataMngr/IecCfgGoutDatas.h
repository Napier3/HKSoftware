//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasGout.h  CIecCfgDatasGout

#pragma once
#include "../../../Module/DataMngr/DataGroup.h"

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDatasBase.h"

#include "IecCfgGoutData.h"
#include "../../../Module/DataMngr/DvmLogicDevice.h"

class CIecCfgGoutDatas : public CIecCfgDatasBase
{
public:
	CIecCfgGoutDatas();
	virtual ~CIecCfgGoutDatas();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASGOUT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasGoutKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn,BOOL bCopyChildren);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual UINT GetIecCfgDataClassID();

	virtual BOOL IsCfgData(UINT nClassID)	{	return (nClassID == CFGCLASSID_CIECCFGGOUTDATA);	}
	virtual BOOL IsCfgData(CExBaseObject *pObj);
	virtual long GetMaxCfgDataCount()	{	return /*50*//*16*/g_nIecCfgGoutMaxNum;	}
	virtual long GetMaxCfgDataCount(UINT nClassID)	{	return /*50*//*16*/g_nIecCfgGoutMaxNum;	}
	void GenerateGouts_GroupDatas(CDataGroup *pGouts);//将初始值填入DataGroup
	void ReadGouts_GroupDatas(CDataGroup *pGouts);//从DataGroup中获取初始值

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();

	CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID,UINT nCMT,UINT nChCount);
	BOOL SetCfgDataGoutMap(const long nContrlBlockIndex,const long nFirstMapIndex,const long nMapNum);
	BOOL IsAppID_Repeat(DWORD dwAppID);
	CIecCfgDataBase* FindByAppIDFiber(DWORD dwAppID,long nFiberIndex);

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex);//周宏军 20200616  增加AT02配置
	void AddAT02D_dsGout(CDvmLogicDevice *pLDevice,long &nDatasetIndex);
	BOOL IsAT02D_Invalid();
#endif
};

