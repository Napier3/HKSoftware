#pragma once

#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DataType.h"
#include "../../SttTestSysGlobalPara.h"

#define STT_TEST_RESOURCE_TYPE_ASYNC                          0
#define STT_TEST_RESOURCE_TYPE_SYNC                           1
#define STT_TEST_RESOURCE_TYPE_4U3I                           2
#define STT_TEST_RESOURCE_TYPE_6U6I                           3

#define STT_TEST_RESOURCE_FILENAME_ASYNC                          _T("ChMapConfig.async")
#define STT_TEST_RESOURCE_FILENAME_SYNC                           _T("ChMapConfig.sync")
#define STT_TEST_RESOURCE_FILENAME_4U3I                           _T("ChMapConfig.4u3i")
#define STT_TEST_RESOURCE_FILENAME_6U6I                           _T("ChMapConfig.6u6i")




//同步模式，软件资源通道
//异步模式，硬件资源通道
class CSttChResource: public CExBaseObject
{
public:

	CSttChResource();
	virtual ~CSttChResource(void){}
	long GetChIndex();//通道编号,从1开始
	long GetChIndex_FromZero();//通道编号,从0开始
	BOOL IsVolCh();//通道类型是电压通道

	BOOL m_bHasMapHdRs;//判断当前是否映射了硬件资源

	long m_nHasMapType;//判断当前是通道类型是数字，模拟，小信号

};

class CSttChGroupResource: public CExBaseList//对软件资源分组,用于谐波模块
{
public:

	CSttChGroupResource(){}
	virtual ~CSttChGroupResource(void){}

	BOOL HasVolCh();///是否含有电压通道
	BOOL HasCurCh();//是否含有电流通道
	void GetVolChs(CSttChGroupResource *pListRef);
	void GetCurChs(CSttChGroupResource *pListRef);
	long GetHeadChIndex_FromZero();//获取全部通道中,第一个通道的Index,从所有通道标识中,找到最小的
};


class CSttTestResourceBase :public CExBaseList
{
public:
	CSttTestResourceBase(void);
	virtual ~CSttTestResourceBase(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_4U3I;}//获取当前软件资源类型
	virtual void CreateSoftResource();//创建软件资源
	virtual void CreateSoftResourceByChMaps(CExBaseList *pCExBaseList);//创建软件资源

virtual CString GetChMapsFilePostfix(){return _T("");}//获取映射文件扩展名
//	BOOL SetChNameByID(const CString &strID,const CString &strName);//根据软件资源ID查找对应软件资源,并设置其name值   zhouhj删除 该链表子对象不为CDvmData
	CSttChResource* AddNewData(const CString &strName,const CString &strID);
	void ClearAll();//删除全部软件资源,清空索引链表
	CString GetChMapFileName();//获取通道映射文件名称

	virtual void InitAfterCreated();//在创建完软件资源后,需要进行的初始化操作
	void InitGroup();//初始化所有通道分组
	void AddGradientChs(CDataType &oGradientChs, BOOL bUseAllFreq = FALSE);//获取全部递变通道(主要用于手动、谐波模块递变)
	void AddGradientSequence(CDataType &oGradientChs);//增加序分量递变通道
	void AddGradientLineVolt(CDataType &oGradientChs);//增加线电压递变通道
	void AddGradientChs_All(CDataType &oGradientChs);//获取全部递变通道(用于递变模块)
	void AddDcVoltageChs(CDataType &oDcVoltageChs);//增加电压保护电压通道 dxy 2023.10.8
	void AddDcCurrentChs(CDataType &oDcVoltageCurChs);//增加电压保护电流通道 dxy 2023.10.8
	void AddDCOverLoadCurChs(CDataType &oDCOverLoadChs);//cl20230921过负荷直流通道
	void AddACOverLoadCurChs(CDataType &oOverLoadChs);//cl20230921过负荷交流通道
	void AddGradientRemoteMeasChs(CDataType &oGradientChs);//增加遥测通道 zhangyq 2023.11.20
	void AddGradientPower(CDataType &oGradientChs);//增加功率递变通道 wangtao 2024.06.12
  
    long GetChIndexPowerByChName(CString strName,BOOL bVol);//增加功率根据通道名称获取通道Index wangtao 2024.06.12
	long GetChIndexSequenceByChName(CString strName,BOOL bVol);//根据通道名称获取通道Index,从0开始计数
	long GetChIndexLinevoltByChName(CString strName,BOOL bVol);

	long GetVolRsNum(){ return m_oVolChRsListRef.GetCount();}
	long GetVCurRsNum(){ return m_oCurChRsListRef.GetCount();}
	void GetCurrVolGroupNum(long &nCurrGroupNum,long &nVolGroupNum);

	CExBaseList m_oListGroups;//该链表中为全部分组,此处为索引方式，实际通道不在CMacroChGroup中删除

	CExBaseList m_oVolChRsListRef;//全部电压通道资源索引
	CExBaseList m_oCurChRsListRef;//全部电流通道资源索引

protected:
	void ClearGroups();

	void AddGradientCh(CDataType *pGradientChSelList,const CString &strChName,int nChRealIndex);
	void AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh,int nChRealIndex);
	void AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,int nChRealIndex);
	void AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,int nChRealIndex);
	void AddGradientCh_Plus(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,int nChRealIndex);
	void AddGradientCh(CDataType *pGradientChSelList,CSttChResource *pCh1,CSttChResource *pCh2,CSttChResource *pCh3,
		CSttChResource *pCh4,CSttChResource *pCh5,CSttChResource *pCh6,int nChRealIndex);

};
