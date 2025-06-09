//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDatasSMV.h  CIecCfgDatasSmvIn

#pragma once

#include "IecCfgSMVDatas.h"
#include "IecCfg2MInData.h"
#include "IecCfg6044CommonInData.h"

class CIecCfgDatasSmvIn : public CIecCfgDatasSMV
{
public:
	CIecCfgDatasSmvIn();
	virtual ~CIecCfgDatasSmvIn();

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASSMVINPUT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasSmvInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual UINT GetIecCfgDataClassID();

	virtual BOOL IsCfgData(UINT nClassID)	{	return IsSmvData(nClassID);	}
	
	virtual long GetCurSmvTypeClassID();//��ȡ��ǰ�������͵�ClassID

	virtual long GetMaxCfgDataCount()	{	return 8;	}
	virtual long GetMaxCfgDataCount(UINT nClassID);
	virtual void ChangePosition(long nIndex1, long nIndex2);//���������а���CIecCfgSmvRates������������Ž��ö���������

//˽�г�Ա�������ʷ���
public:
	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();

	virtual CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);
	virtual BOOL IsAppID_Repeat(DWORD dwAppID);

	virtual BOOL IsSmvData_AllSmvType(CExBaseObject *pObj);//zhouhj 2023.10.18 �˺������б�ǰSMV�������,ֻҪ��SMV���ͼ�����true

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);// �ܺ�� 20200611 ��������AT02D�����ļ�����
	virtual void AddAT02D_dsSV(CDvmLogicDevice *pLDevice,long &nDatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	virtual BOOL IsAT02D_Invalid();
#endif
};

