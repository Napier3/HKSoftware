//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasBase.h  CIecCfgDatasBase

#pragma once


#include "IecCfgDataMngrGlobal.h"
#include "IecCfgDataBase.h"

#include "../../../Module/DataMngr/DvmLogicDevice.h"

#ifdef IECFG_USE_KEYDB
#include "../../../Module/KeyDb/XKeyDB.h"
#include "../../../Module/KeyDb/XMatchList.h"
#endif

class CIecCfgDatasBase : public CExBaseList
{
public:
	CIecCfgDatasBase();
	virtual ~CIecCfgDatasBase();

#ifdef IECFG_USE_KEYDB
	CXMatchList *m_pMatchList;
	void InitMatchList(CXKeyDB *pKeyDB);
#endif

	long  m_nDatasCount;
	long  m_nDatasUse;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual void SetCount(long nCount, CExBaseList &oListTemp);
	virtual void SetCount(long nCount);
	virtual CIecCfgDataBase* CreateIecCfgData() = 0;
	virtual UINT GetIecCfgDataClassID() = 0;
	virtual void GetIecCfgDatas(CExBaseList &oList);
	virtual BOOL DeleteCfgData(CIecCfgDataBase *pCfgData);
	virtual long GetCfgDataCount();
	virtual BOOL SetCfgDataCount(long nCount ,long nFirstFiberNum,BOOL bSingleFiber);  //zhouhongjun   设置CfgData的数量【参数1:总控制块数;参数2:第一个光口号;参数3:是否同一个光口】
	virtual BOOL SetCfgDataCountEx(long nCount ,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,
		BOOL bSingleFiber);  //zhouhongjun   设置CfgData的数量【参数1:总控制块数;参数2:Fiber1起始光口号;参数3:Fiber2起始光口号;参数4:是否同一个光口】
	virtual void SetCfgDataFiberNum(CExBaseList *pCfgDataList,long nFirstFiberNum,BOOL bSingleFiber);//zhouhongjun  设置CfgData的数量【参数1:总控制块数;参数2:第一个光口号;参数3:是否同一个光口】
	virtual void SetCfgDataFiberNumEx(CExBaseList *pCfgDataList,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,
		BOOL bSingleFiber);//zhouhongjun  设置CfgData的数量【参数1:总控制块数;参数2:Fiber1起始光口号;参数3:Fiber2起始光口号;参数4:是否同一个光口】
	virtual BOOL DeleteCfgDataByNum(long nDeleteNum);
	virtual CIecCfgDataBase* GetIecCfgData(long nIndex);
	virtual long GetIecCfgDataIndex(CIecCfgDataBase *pIecCfgData);
	virtual CIecCfgDataBase* AddNewIecCfgData();

	virtual BOOL IsCfgData(UINT nClassID) = 0;
	virtual BOOL IsCfgData(CExBaseObject *pObj);//此函数中会根据当前选择的报告类别过滤,需要与当前选择的类别一致才返回true
	virtual BOOL IsCfgData_Common(CExBaseObject *pObj);//20230423 zhouhj 此函数中不区分类别,只要是继承自CIecCfgDataBase的类对象都返回
	virtual BOOL IsCfgData_6044Common(CExBaseObject *pObj);//20240520 suyang 此函数中区分类别FT3
	virtual BOOL IsCfgData_SV_GOOSECommon(CExBaseObject *pObj);//20240520 suyang 此函数中区分类别SV GOOSE


	virtual CIecCfgDataBase* GetFirstIecCfgDataBase();
	virtual CIecCfgDataBase* GetFirstIecCfgData_Sel();//zhouhj 20211208 获取第一个选择的

	virtual void GetFiberIndexUse(long nCount, long *pnFiberIndexUse);
	virtual void SetFiberIndexByFiber2Index();//zhouhj 20201205 将FiberIndex改为Fiber2Index 主要用于AT02D
	virtual void SetFiber2IndexByFiberIndex(long nOffset);//zhouhj 20201205 将FiberIndex改为Fiber2Index 主要用于AT02D
	virtual BOOL CanAddCfgData(UINT nClassID);
	virtual BOOL CanAddCfgData();
	virtual long GetMaxCfgDataCount() = 0;
	virtual long GetMaxCfgDataCount(UINT nClassID) = 0;
	virtual BOOL IsAppID_Repeat(DWORD dwAppID){return FALSE;}//zhouhj 20211018判断当前AppID是否重复

	void UpdateFiberIdex2();//20220611 将光口标识1设置值,指向光口标识2

//私有成员变量
private:

//私有成员变量访问方法
public:
	void SetDataUse(long nUse, long nDataCount=0);
	long GetDataUse()				{	return m_nDatasUse;	}
	void DelteteContrlBlocks_Unselected();//zhouhj 20210528删除未选择的控制块
	BOOL HasContrlBlock_Selected();//判断是否包含选择的控制块
	BOOL HasContrlBlock_FT3Selected();//判断是否包含选择FT3的控制块
	BOOL HasContrlBlock_SV_GOOSESelected();//判断是否包含选择goose sv的控制块
	void DeleteRepeatCtrl(DWORD dwAppID);
	BOOL HasRepeatCtrl(DWORD dwAppID);
	void SetAllFiberIndex(long nFiberIndex);//设置全部控制块的输出光口
	void SetSelectState_AllCtrlBlock(long nUseFlag, UINT nClassID);// zhouhj 20220211 设置全部控制块选择状态

#ifdef _PSX_IDE_QT_
	virtual void AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue, long nOffset=1, unsigned long long *pvMin=NULL, unsigned long long *pvMax=NULL);
	virtual void AutoSetCfgDataValues(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue, long nOffset=1, unsigned long long *pvMin=NULL, unsigned long long *pvMax=NULL);
	virtual BOOL HasCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, unsigned long long &vValue);
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual void AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, VARIANT &vValue, long nOffset=1, VARIANT *pvMin=NULL, VARIANT *pvMax=NULL);
	virtual BOOL HasCfgDataValue(CIecCfgDataBase *pCfgData, long nDataID, VARIANT &vValue);
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValue);

	//2021-6-21  lijunqing
	virtual CIecCfgDataBase* FindCfgData(long nDataID, VARIANT &vValue);
#endif

	virtual long GetUseDatasCount();
	virtual long GetUseDatasCount(UINT nClassID);
    virtual long GetDatasCount(UINT nClassID);//wangtao 20240516 根据获取当前参数类型添加的数量
	virtual long GetUseDatas(CExBaseList &oListDatas);
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData) = 0;
	virtual BOOL ValidateFiberIndex() = 0;
#ifdef _USE_IN_AT02D_MODE_
protected:
	BOOL HasCfgDataset_AT02D_Model(CDvmLogicDevice *pLDevice,const CString &strAppID);//周宏军 20200616  增加AT02配置
#endif
};

