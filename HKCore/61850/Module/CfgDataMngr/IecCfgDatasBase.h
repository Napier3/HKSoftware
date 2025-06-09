//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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
	virtual BOOL SetCfgDataCount(long nCount ,long nFirstFiberNum,BOOL bSingleFiber);  //zhouhongjun   ����CfgData������������1:�ܿ��ƿ���;����2:��һ����ں�;����3:�Ƿ�ͬһ����ڡ�
	virtual BOOL SetCfgDataCountEx(long nCount ,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,
		BOOL bSingleFiber);  //zhouhongjun   ����CfgData������������1:�ܿ��ƿ���;����2:Fiber1��ʼ��ں�;����3:Fiber2��ʼ��ں�;����4:�Ƿ�ͬһ����ڡ�
	virtual void SetCfgDataFiberNum(CExBaseList *pCfgDataList,long nFirstFiberNum,BOOL bSingleFiber);//zhouhongjun  ����CfgData������������1:�ܿ��ƿ���;����2:��һ����ں�;����3:�Ƿ�ͬһ����ڡ�
	virtual void SetCfgDataFiberNumEx(CExBaseList *pCfgDataList,long nFiber1BeginIndex,long nFiber2BeginIndex,long nTotalFiberNum,
		BOOL bSingleFiber);//zhouhongjun  ����CfgData������������1:�ܿ��ƿ���;����2:Fiber1��ʼ��ں�;����3:Fiber2��ʼ��ں�;����4:�Ƿ�ͬһ����ڡ�
	virtual BOOL DeleteCfgDataByNum(long nDeleteNum);
	virtual CIecCfgDataBase* GetIecCfgData(long nIndex);
	virtual long GetIecCfgDataIndex(CIecCfgDataBase *pIecCfgData);
	virtual CIecCfgDataBase* AddNewIecCfgData();

	virtual BOOL IsCfgData(UINT nClassID) = 0;
	virtual BOOL IsCfgData(CExBaseObject *pObj);//�˺����л���ݵ�ǰѡ��ı���������,��Ҫ�뵱ǰѡ������һ�²ŷ���true
	virtual BOOL IsCfgData_Common(CExBaseObject *pObj);//20230423 zhouhj �˺����в��������,ֻҪ�Ǽ̳���CIecCfgDataBase������󶼷���
	virtual BOOL IsCfgData_6044Common(CExBaseObject *pObj);//20240520 suyang �˺������������FT3
	virtual BOOL IsCfgData_SV_GOOSECommon(CExBaseObject *pObj);//20240520 suyang �˺������������SV GOOSE


	virtual CIecCfgDataBase* GetFirstIecCfgDataBase();
	virtual CIecCfgDataBase* GetFirstIecCfgData_Sel();//zhouhj 20211208 ��ȡ��һ��ѡ���

	virtual void GetFiberIndexUse(long nCount, long *pnFiberIndexUse);
	virtual void SetFiberIndexByFiber2Index();//zhouhj 20201205 ��FiberIndex��ΪFiber2Index ��Ҫ����AT02D
	virtual void SetFiber2IndexByFiberIndex(long nOffset);//zhouhj 20201205 ��FiberIndex��ΪFiber2Index ��Ҫ����AT02D
	virtual BOOL CanAddCfgData(UINT nClassID);
	virtual BOOL CanAddCfgData();
	virtual long GetMaxCfgDataCount() = 0;
	virtual long GetMaxCfgDataCount(UINT nClassID) = 0;
	virtual BOOL IsAppID_Repeat(DWORD dwAppID){return FALSE;}//zhouhj 20211018�жϵ�ǰAppID�Ƿ��ظ�

	void UpdateFiberIdex2();//20220611 ����ڱ�ʶ1����ֵ,ָ���ڱ�ʶ2

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetDataUse(long nUse, long nDataCount=0);
	long GetDataUse()				{	return m_nDatasUse;	}
	void DelteteContrlBlocks_Unselected();//zhouhj 20210528ɾ��δѡ��Ŀ��ƿ�
	BOOL HasContrlBlock_Selected();//�ж��Ƿ����ѡ��Ŀ��ƿ�
	BOOL HasContrlBlock_FT3Selected();//�ж��Ƿ����ѡ��FT3�Ŀ��ƿ�
	BOOL HasContrlBlock_SV_GOOSESelected();//�ж��Ƿ����ѡ��goose sv�Ŀ��ƿ�
	void DeleteRepeatCtrl(DWORD dwAppID);
	BOOL HasRepeatCtrl(DWORD dwAppID);
	void SetAllFiberIndex(long nFiberIndex);//����ȫ�����ƿ��������
	void SetSelectState_AllCtrlBlock(long nUseFlag, UINT nClassID);// zhouhj 20220211 ����ȫ�����ƿ�ѡ��״̬

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
    virtual long GetDatasCount(UINT nClassID);//wangtao 20240516 ���ݻ�ȡ��ǰ����������ӵ�����
	virtual long GetUseDatas(CExBaseList &oListDatas);
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData) = 0;
	virtual BOOL ValidateFiberIndex() = 0;
#ifdef _USE_IN_AT02D_MODE_
protected:
	BOOL HasCfgDataset_AT02D_Model(CDvmLogicDevice *pLDevice,const CString &strAppID);//�ܺ�� 20200616  ����AT02����
#endif
};

