//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataGin.h  CIecCfgDataGin

#pragma once
#include "../../../Module/DataMngr/DataGroup.h"

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgGooseDataBase.h"

#include "IecCfgGinChs.h"

#include"../../Module/XLanguageResourceIec.h"
#include "../../../Module/DataMngr/DvmDataset.h"

class CIecCfgGinData : public CIecCfgGooseDataBase
{
public:
	CIecCfgGinData();
	virtual ~CIecCfgGinData();


	long  m_nUseMacSrcAddr;
	long  m_nUseMacDestAddr;
	long  m_nUseDataSet;
	long  m_nUseAppID;
	long  m_nUseGocbRef;
	long  m_nUseGooseID;

	long  m_nAnalyze;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGINDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataGinKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CString GetCfgDefaultConfigFile()	{	return _T("CfgGin.xml");	}
	virtual void InitAfterRead();

	BOOL SetChMap(const CString &strChDesc,long nChMapIndex);//zhouhj 20220206 �������ڸ���ͨ�������Զ�����ͨ��ӳ��
	void InitBinChMaps();//zhouhj 20220327 ��ʼ��ͨ��ӳ��,�ڶԿ�����ͨ�����п�����ճ��������,��Ҫ��������Ķ����ͨ��ӳ����г�ʼ��
	void CopyToGoutData(CIecCfgGooseDataBase *pGoutData);//2023.6.2 zhouhj �Ѷ��Ŀ��ƿ����ݿ���������

	void GenerateGin_GroupDatas(CDataGroup *pGinChs);//����ʼֵ����DataGroup
	void ReadGin_GroupDatas(CDataGroup *pGinChs);//��DataGroup�л�ȡ��ʼֵ
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
	void AddAT02D_Dataset(CDvmDataset *pCurDataset);
	void AT02D_MapChannelID(CIecCfgGinData *pIecCfgGinData);
	void AT02D_CopyToGoutData(CExBaseList *pGoutData);
	void AT02D_AddChannelData(CDvmDataset *pCurDataset,CIecCfgGinCh *pIecCfgGinCh);
	long GetAppChIDGin_Index(const CString &strAppID_Index);
#endif

	BOOL SetCfgDataGinMap(const long &nFirstMapIndex,const long &nMapNum);

	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
        strName.Format(_T("GOOSEIN(%d): %s"), nIndex, m_strDestAddress.GetString());
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
#ifdef NOT_USE_XLANGUAGE
        strName.Format(_T("GOOSEIN��%d��"), nIndex+1);
#else
		strName.Format(g_sLangTxt_GooseinGroup/*_T("GOOSEIN��%d��")*/, nIndex+1);
#endif
		return strName;
	}
};

