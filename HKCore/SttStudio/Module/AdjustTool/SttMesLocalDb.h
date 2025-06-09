//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMesLocalDb.h  CSttMesLocalDb

#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/DataMngr/DataTypes.h"

#define STT_MES_LOCAL_DB_SttModuleType  _T("SttModuleType")
#define STT_MES_LOCAL_DB_SttModuleClass  _T("SttModuleClass")
#define STT_MES_LOCAL_DB_SttModel  _T("SttModel")

class CSttMesLocalDb : public CExBaseList
{
private:
	CSttMesLocalDb();
	virtual ~CSttMesLocalDb();

	static long g_nSttMesLocalDb;
	static CSttMesLocalDb* g_pSttMesLocalDb;

	CDataGroup *m_pSttMesLocalDB;

	//2021-5-5  lijunqing  已经打开的模块类型系数文件
	CExBaseList m_listModuleClassOpened;
private:
	CDataType m_oHdGearType;
	CDataType m_oChannelDataType;
	CDataType m_oChWaveDataType;
	CDataType m_oGearDataType;
	CDataType m_oChannelSwitchDataType;
	CDataType m_oTRangeDataType;
// 	CDataType m_oWorkModeDataType;
// 	CDataType m_oEeTypeDataType;
// 	CDataType m_oModuleTypeDataType; //模块类型

	CDataTypes m_oDataTypes;

	void InitHdGearType();
	void InitChannelDataType();
	void InitChWaveDataType();
	void InitGearDataType();
	void InitTRangeDataType();
	void InitWorkModeDataType();
	void InitEeTypeDataType();
	void InitModuleTypeDataType();

public:
	static CSttMesLocalDb* Create();
	static CSttMesLocalDb* GetMesLocalDb();
	static void Release();

	static CString GetMesLocalDbPath();
	static CString GetMesLocalDbPath_Model();
	static CString GetMesLocalDbPath_ModuleType();
	static CString GetMesLocalDbFile();
	static CString GetMesLocalDbPath_ModuleClassFile(const CString &strSttModuleClass);

	static CDataGroup* GetSttModuleTypes();
	static CDataGroup* GetSttModuleClasses();
	static CDataGroup* GetSttModels();

	static CDataType* FindDataType(const CString &strID);

	static CDataType* GetHdGearType()	{	return &g_pSttMesLocalDb->m_oHdGearType;	}
	static CDataType* GetChannelDataType()	{	return &g_pSttMesLocalDb->m_oChannelDataType;	}
	static CDataType* GetChannelSwitchDataType()	{	return &g_pSttMesLocalDb->m_oChannelSwitchDataType;	}
	static CDataType* GetChWaveDataType()	{	return &g_pSttMesLocalDb->m_oChWaveDataType;	}
	static CDataType* GetChWaveDataType(CDataType *pDataType, long nHarmCount);
	static CDataType* GetGearDataType()	{	return &g_pSttMesLocalDb->m_oGearDataType;	}
	static CDataType* GetTrangeDataType()	{	return &g_pSttMesLocalDb->m_oTRangeDataType;	}
// 	static CDataType* GetWorkModeDataType()	{	return &g_pSttMesLocalDb->m_oWorkModeDataType;	}
// 	static CDataType* GetEeTypeDataType()	{	return &g_pSttMesLocalDb->m_oEeTypeDataType;	}

	static BOOL OpenSttModuleClass(CDataGroup *pNew, const CString &strSttModuleClass);
	static CDataGroup* CreateSttModuleClass(const CString &strSttModuleClass);
	static CDataGroup* OpenSttModuleClass(const CString &strSttModuleClass);
	static CDataGroup* OpenSttModuleClass(CDataGroup *pModuleClass);
	static BOOL SaveSttModuleClassFile(CDataGroup *pModuleClass);

	//2020-10-13 lijunqing
	static CDvmData* FindModuleTypeData(const CString &strModuleType);
	static CDvmData* FindModuleTypeData(long nModuleType);
	static CString GetModuleType_ChID_Desc(const CString &strModuleType);

//////////////////////////////////////////////////////////////////////////
//mym
	static CDvmData* AddNewModuleType();
	static CDvmData* AddNewModuleType(CDataGroup *pModuleType);
	static long   DeleteModuleTypeByIndex(int nDataIndex);
	static CDvmData* AddNewModuleType(int nFalg);


	static CDataGroup* AddNewModuleClass();
	static CDataGroup* AddNewModuleClass(CDataGroup *pModuleClass);
	static CDataGroup* AddNewModuleClass2(CDataGroup *pSrcModuleClass);
	static CDvmData* AddNewModuleClassData(CDataGroup* pDataGroup);
	//static long   DeleteModuleClass_data_ByIndex(CDataGroup *pDataGroup, int nDataIndex);
	static CDataGroup *   DeleteModuleClass(CDataGroup *pDataGroup);
	static long   GetModuleClassesIndex(CDataGroup *pDataGroup);

	static CDataGroup* AddNewMode();
	static CDataGroup* AddNewMode(CDataGroup *pMode);
	static CDataGroup * DeleteMode(CDataGroup * pDataGroup);
	static long   GetModeIndex(CDataGroup * pDataGroup);

public:
	void InitSttMesLocalDB();
	void SaveSttMesLocalDB();
	virtual BOOL GetModifiedFlagOwn();
	virtual void SaveBaseObject();


protected:
	virtual void SetModifiedFlagOwn(BOOL bModified=TRUE);

	BOOL m_bModifiedFlag;
};

