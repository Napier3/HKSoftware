//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjModule.h  CSttAdjModule

#pragma once

#include "SttAdjBase.h"

class CSttAdjModule : public CSttAdjBase
{
public:
	CSttAdjModule();
	virtual ~CSttAdjModule();

public:
	CDataGroup* GetModuleAttrs(CDataGroup *pModule);
	CDataGroup* GetModuleAttrs();
	void GetModuleAttrs(CDataGroup *pModule, BOOL bOnlyAttrs);
	CDataGroup* GetHdGear(const CString &strHdGearID);	
	CDataGroup* GetHdGearItem(const CString &strHdGearID);
	void DeleteHdGear(CDataGroup*pDataGroup, const CString &strHdGearID, long nValAdd=1);

	CDataGroup* AddNewHdGear(const CString &strHdGearID);
	CDataGroup* GetHdChDefine();
	CDataGroup* GetAdjustParas();
	CDataGroup* GetChDrvPos();

	CDataGroup* GetAdjTRange(long nIndex);
	CDataGroup* GetAdjTRange(const CString &strT_Range);
	CDataGroup* GetAdjChannel(const CString &strT_Range, const CString &strChID);
	CDataGroup* GetAdjChWaveAdjusts(const CString &strT_Range, const CString &strChID, const CString &strWaveID);
	
	//获取档位指针 2020-10-14 mym 
	CDataGroup* GetAdjChWaveAdjustsGear(const CString &strT_Range, const CString &strChID, const CString &strWaveID/*, const CString &strGearID*/); // 2020-10-13 mym 

	CDataGroup* AddNewChMap();
	CDataGroup* AddNewChMap(CDataGroup *pMaps);

	//添加驱动通道位置 2020-10-10
	CDvmData*   AddNewChDrvPos(CDataGroup *pMaps);
	CDvmData*   AddNewChDrvPos();

	//添加温区 2020-10-13 mym
	CDataGroup* AddNewTrang();		
	
	//添加档位 2020-10-14 mym
	CDataGroup* AddNewGear(const CString &strT_Range, const CString &strChID, const CString &strWaveID,  const CString &strGearID);
	CDataGroup* AddNewGear(CDataGroup *pSrcGear, CDataGroup *pParent, const CString &strGearID, const CString &strCountID);	
	CDataGroup* AddNewGear(CDataGroup *pSrcGear, CDataGroup *pParent);	
	CDataGroup* AddNewGear_AllChnel(	 const CString &strTrangeID);
	CDataGroup* AddNewGear_SingleChnel( const CString &strTrangeID , const CString &strChannelID);

	//2021-5-3 lijunqing
	CDataGroup* AddNewGear_AllChannel(CDataGroup *pTrange, CDataGroup *pAdjParas, const CString &strWaveID, CDataGroup *pSrcGear=NULL);
	CDataGroup* AddNewGear_SingleChannel(CDataGroup *pAdjParas, const CString &strWaveID, CDataGroup *pSrcGear=NULL);

	//delete 
	CDataGroup* DeleteGear(const CString &strTrangeID,  const CString &strChannelID,  const CString &strChWaveID, const CString &strCurID, int &nIndex);
	CDataGroup* DeleteGear_SingleGear( const CString &strTrangeID, const CString &strChannelID, const CString &strCurID, int &nIndex);
	CDataGroup* DeleteGear_AllGear( const CString &strTrangeID, int &nCmbChannelIndex, int &nCmbWaveIndex, const CString &strCurID, int &nIndex);

	//2021-5-3 lijunqing
	BOOL DeleteGear(CDataGroup *pParent, const CString &strGearID);	
	BOOL DeleteGear_AllChannel(CDataGroup *pTrange, CDataGroup *pAdjParas, const CString &strWaveID, const CString &strGearID);
	BOOL DeleteGear_SingleChannel(CDataGroup *pAdjParas, const CString &strWaveID, const CString &strGearID);

	void  SetTrangID_ChannelID(CString strChannelID[] , CString strChWaveID[]);

	CDvmData*  GetModuleType();
	CDvmData*  GetModuleType(CDataGroup *pModule);
	BOOL   GetModuleType(CString &strModuleType);
	BOOL GetModuleType(long &nModuleType);

	BOOL GetModel(CString &strModel);
	CDvmData*  GetModel();

	CDvmData*  GetModuleAttrByID(CDataGroup *pModule, const CString &strAttrID);

	CDvmData*  GetModuleChannelNum();
	CDvmData*  GetModuleChannelNum(CDataGroup *pModule);
	BOOL   GetModuleChannelNum(CString &strChannelNum);
	BOOL GetModuleChannelNum(long &nChannelNum);
	BOOL GetModuleChannelNum(long &nVolChNum,long &nCurChNum);//zhouhj 20211006 对于电压电流混合模块,需要从通道映射中获取
	void AddMaxVolCurrValue_VolCurrModule();//zhouhj 20220424  对电压电流混合插件增加交流、直流电压的最大值属性
	long		 GetModuleIndex();
	BOOL  GetModule_Type_Index(CString &strModuleType, long &nModuleIndex);
	long GetHarmCount();
	CDvmData*  GetHarmCount(CDataGroup *pModule);

	void InitChannelsID();
	void InitChannelsID(long nModuleIndex, const CString &strEeType, const CString &strID_Type, const CString &strID_Desc);

	// mym 2021-4-22 add ; 为了 获取 模块位置 ；
	CDvmData*  GetModulePos();
	CDvmData*  GetModulePos(CDataGroup *pModule);
	BOOL  GetModulePos(CString &strModulePos);
	BOOL  GetModulePos(long &nModulePos);
	BOOL  GetModule_Pos_Index(CString &strModulePos, long &nModulePos,  long &nModuleIndex);

	//2021-5-4  lijunqing  将模块类型由整数转换为字符串，兼容老版本校准系数文件
	void TransModuleTypeFromLongToString();

public:
	CString m_strChannelID[10];
	CString m_strChWaveID[40];
	int m_nWaveCnt;
	int m_nChannelCnt;

public:
	virtual void GetAttrs();
	virtual long GetModelType(){return STT_MODEL_TYPE_Module;}


public:
	virtual BOOL GetModifiedFlagOwn();
	virtual void SaveBaseObject();
protected:
	virtual void SetModifiedFlagOwn(BOOL bModified=TRUE);
	BOOL m_bModifiedFlag;

};
//2021-11-01  lijunqing
long stt_adj_HdChDef_GetNum(CDataGroup *pHdChDefine);
CString stt_adj_HdChDef_GetEeType(CDataGroup *pHdChDefine);
BOOL stt_adj_HdChDef_Is_Voltage(CDataGroup *pHdChDefine);
BOOL stt_adj_HdChDef_Is_Current(CDataGroup *pHdChDefine);

