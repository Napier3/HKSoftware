//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDataGout.h  CIecCfgDataGout

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgGooseDataBase.h"

#include "IecCfgGoutChs.h"
#include"../../Module/XLanguageResourceIec.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CIecCfgGoutData : public CIecCfgGooseDataBase
{
public:
	CIecCfgGoutData();
	virtual ~CIecCfgGoutData();


	long  m_nEntrust;
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOUTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDataGoutKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("CfgGout.xml");	}

	void GenerateGout_GroupDatas(CDataGroup *pGoutChs);//����ʼֵ����DataGroup
	void ReadGout_GroupDatas(CDataGroup *pGoutChs);//��DataGroup�л�ȡ��ʼֵ
	virtual BOOL OpenCfgDefaultConfigFile();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
	void AddAT02D_Dataset(CDvmDataset *pCurDataset);
	void AT02D_MapChannelID(CIecCfgGoutData *pIecCfgGoutData);
	void AT02D_CopyToGinData(CExBaseList *pGinData);
	long GetAppChIDGin_Index(const CString &strAppID_Index);
	void AT02D_AddChannelData(CDvmDataset *pCurDataset,CIecCfgGoutCh *pIecCfgGoutCh);
#endif

	BOOL SetCfgDataGoutMap(const long &nFirstMapIndex,const long &nMapNum);
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
        strName.Format(_T("GOOSEOUT(%d): %s"), nIndex, m_strDestAddress.GetString());
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
#ifdef NOT_USE_XLANGUAGE
        strName.Format(_T("GOOSEOUT��%d��"), nIndex+1);
#else
		strName.Format(g_sLangTxt_GooseoutGroup/*_T("GOOSEOUT��%d��")*/, nIndex+1);
#endif

		return strName;
	}
};

