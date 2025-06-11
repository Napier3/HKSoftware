#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/DataMngr/DataType.h"
#include "../../SttTestSysGlobalPara.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"

#define STT_TEST_RESOURCE_TYPE_ASYNC                          0
#define STT_TEST_RESOURCE_TYPE_SYNC                           1
#define STT_TEST_RESOURCE_TYPE_4U3I                           2
#define STT_TEST_RESOURCE_TYPE_6U6I                           3

#define STT_TEST_RESOURCE_FILENAME_ASYNC                          _T("ChMapConfig.async")
#define STT_TEST_RESOURCE_FILENAME_SYNC                           _T("ChMapConfig.sync")
#define STT_TEST_RESOURCE_FILENAME_4U3I                           _T("ChMapConfig.4u3i")
#define STT_TEST_RESOURCE_FILENAME_6U6I                           _T("ChMapConfig.6u6i")




//ͬ��ģʽ�������Դͨ��
//�첽ģʽ��Ӳ����Դͨ��
class CSttChResource: public CExBaseObject
{
public:

	CSttChResource();
	virtual ~CSttChResource(void){}
	long GetChIndex();//ͨ�����,��1��ʼ
	long GetChIndex_FromZero();//ͨ�����,��0��ʼ
	BOOL IsVolCh();//ͨ�������ǵ�ѹͨ��

	BOOL m_bHasMapHdRs;//�жϵ�ǰ�Ƿ�ӳ����Ӳ����Դ

	long m_nHasMapType;//�жϵ�ǰ��ͨ�����������֣�ģ�⣬С�ź�

};

class CSttChGroupResource: public CExBaseList//�������Դ����,����г��ģ��
{
public:

	CSttChGroupResource(){}
	virtual ~CSttChGroupResource(void){}

	BOOL HasVolCh();///�Ƿ��е�ѹͨ��
	BOOL HasCurCh();//�Ƿ��е���ͨ��
	void GetVolChs(CSttChGroupResource *pListRef);
	void GetCurChs(CSttChGroupResource *pListRef);
	long GetHeadChIndex_FromZero();//��ȡȫ��ͨ����,��һ��ͨ����Index,������ͨ����ʶ��,�ҵ���С��
};


class CSttTestResourceBase :public CExBaseList
{
public:
	CSttTestResourceBase(void);
	virtual ~CSttTestResourceBase(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_4U3I;}//��ȡ��ǰ�����Դ����
	virtual void CreateSoftResource();//���������Դ
	virtual void CreateSoftResourceByChMaps(CExBaseList *pCExBaseList);//���������Դ

virtual CString GetChMapsFilePostfix(){return _T("");}//��ȡӳ���ļ���չ��
//	BOOL SetChNameByID(const CString &strID,const CString &strName);//���������ԴID���Ҷ�Ӧ�����Դ,��������nameֵ   zhouhjɾ�� �������Ӷ���ΪCDvmData
	CSttChResource* AddNewData(const CString &strName,const CString &strID);
	void ClearAll();//ɾ��ȫ�������Դ,�����������
	CString GetChMapFileName();//��ȡͨ��ӳ���ļ�����

	virtual void InitAfterCreated();//�ڴ����������Դ��,��Ҫ���еĳ�ʼ������
	void InitGroup();//��ʼ������ͨ������
	void AddGradientChs(CDataType &oGradientChs, BOOL bUseAllFreq = FALSE);//��ȡȫ���ݱ�ͨ��(��Ҫ�����ֶ���г��ģ��ݱ�)
	void AddGradientSequence(CDataType &oGradientChs);//����������ݱ�ͨ��
	void AddGradientLineVolt(CDataType &oGradientChs);//�����ߵ�ѹ�ݱ�ͨ��
	void AddGradientChs_All(CDataType &oGradientChs);//��ȡȫ���ݱ�ͨ��(���ڵݱ�ģ��)
	void AddDcVoltageChs(CDataType &oDcVoltageChs);//���ӵ�ѹ������ѹͨ�� dxy 2023.10.8
	void AddDcCurrentChs(CDataType &oDcVoltageCurChs);//���ӵ�ѹ��������ͨ�� dxy 2023.10.8
	void AddDCOverLoadCurChs(CDataType &oDCOverLoadChs);//cl20230921������ֱ��ͨ��
	void AddACOverLoadCurChs(CDataType &oOverLoadChs);//cl20230921�����ɽ���ͨ��
	void AddGradientRemoteMeasChs(CDataType &oGradientChs);//����ң��ͨ�� zhangyq 2023.11.20
	void AddGradientPower(CDataType &oGradientChs);//���ӹ��ʵݱ�ͨ�� wangtao 2024.06.12
  
    long GetChIndexPowerByChName(CString strName,BOOL bVol);//���ӹ��ʸ���ͨ�����ƻ�ȡͨ��Index wangtao 2024.06.12
	long GetChIndexSequenceByChName(CString strName,BOOL bVol);//����ͨ�����ƻ�ȡͨ��Index,��0��ʼ����
	long GetChIndexLinevoltByChName(CString strName,BOOL bVol);

	long GetVolRsNum(){ return m_oVolChRsListRef.GetCount();}
	long GetVCurRsNum(){ return m_oCurChRsListRef.GetCount();}
	void GetCurrVolGroupNum(long &nCurrGroupNum,long &nVolGroupNum);

	CExBaseList m_oListGroups;//��������Ϊȫ������,�˴�Ϊ������ʽ��ʵ��ͨ������CMacroChGroup��ɾ��

	CExBaseList m_oVolChRsListRef;//ȫ����ѹͨ����Դ����
	CExBaseList m_oCurChRsListRef;//ȫ������ͨ����Դ����

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
