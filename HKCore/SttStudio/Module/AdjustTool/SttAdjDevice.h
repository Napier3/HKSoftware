//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAdjDevice.h  CSttAdjDevice

#pragma once

#include "SttAdjBase.h"
#define STT_ADJ_DEVICE_CLASSID	0x123456

class CSttAdjDevice : public CSttAdjBase
{
public:
	CSttAdjDevice();
	virtual ~CSttAdjDevice();

public:
	virtual UINT GetClassID()	{return STT_ADJ_DEVICE_CLASSID;	}
	BOOL OpenSttAdjFile(const CString &strFile);
	BOOL SaveSttAdjFile(const CString &strFile);
	BOOL SaveSttAdjFile();
	CDataGroup* GetDeviceAttrs();
	CDataGroup* GetBoutTrunOnValueDef();
	void GetDeviceVersioninfors(CDataGroup &oDeviceInfors);  //2022-3-18  lijunqing

	//2021-5-4  lijunqing  ��ģ������������ת��Ϊ�ַ����������ϰ汾У׼ϵ���ļ�
	void TransModuleTypeFromLongToString();

	CDataGroup* AddModule(const CString &strSelModuleClass);
	CDataGroup* ReplaceModule(CDataGroup *pOldModule, const CString &strSelModuleClass);
	long GetModuleCount();
	long GetModuleIndex(CDataGroup *pModule);
	CDataGroup* DeleteModule(CDataGroup *pModule);
	CDataGroup* GetModule(const CString &strModuleType, long nModuleIndex);
	CDataGroup* GetModule2(const CString &strModuleType, long nModulePos);

	CString GetAdjFileName();
	virtual BOOL GetModifiedFlagOwn();
	virtual void SaveBaseObject();
 	void  ImportOldRatio(const CString &strFile);
 	void GetNewModuleNameID( CString &strName,  CString &strID);
 	void AddOldRatio(const CString &strFile);

public:
	CDataGroup *m_pDataGroupOldRatio;

protected:
	virtual void SetModifiedFlagOwn(BOOL bModified=TRUE);
	BOOL m_bModifiedFlag;

public:
	virtual void GetAttrs();
	virtual long GetModelType(){return STT_MODEL_TYPE_Device;}
	BOOL IsIntegrationDevice();
	BOOL IsSttAdjModuleObj(CExBaseObject *pObj);//�жϵ�ǰ�����Ƿ�Ϊģ�����
	BOOL SortModules();//zhouhj ����λ��Index������ģ���������
	void AddMaxVolCurrValue_VolCurrModule();//zhouhj 20220424  �Ե�ѹ������ϲ�����ӽ�����ֱ����ѹ�����ֵ����
	BOOL GetAllModules(CExBaseList *pCurModuleListRef,const CString &strModuleType);//zhouhj ���ݲ�ͬ��ģ������,��ȡdevice��ȫ��ģ��
	BOOL GetAllModules(CExBaseList *pCurModuleListRef,const long &nModuleType);//zhouhj ���ݲ�ͬ��ģ������,��ȡdevice��ȫ��ģ��
	BOOL GetAllModules(CExBaseList *pCurModuleList);

public:
	//2022-2-9  lijunqing 
	void InitChannelsID();
	BOOL CheckModulePos();

private:
	void GetModuleTypes(CExBaseList *pModuleList, CUIntArray &arModuleType);
	void InitModuleChannelsID(CDataGroup *pModule, long nModuleType, long nIndex);
	void AddModuleType(CUIntArray &arModuleType, long nModuleType);
};

