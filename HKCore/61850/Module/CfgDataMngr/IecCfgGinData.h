//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
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

	BOOL SetChMap(const CString &strChDesc,long nChMapIndex);//zhouhj 20220206 增加用于根据通道描述自动进行通道映射
	void InitBinChMaps();//zhouhj 20220327 初始化通道映射,在对开入量通道进行拷贝、粘贴操作后,需要将拷贝后的对象各通道映射进行初始化
	void CopyToGoutData(CIecCfgGooseDataBase *pGoutData);//2023.6.2 zhouhj 把订阅控制块数据拷贝到发布

	void GenerateGin_GroupDatas(CDataGroup *pGinChs);//将初始值填入DataGroup
	void ReadGin_GroupDatas(CDataGroup *pGinChs);//从DataGroup中获取初始值
//私有成员变量
private:

//私有成员变量访问方法
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//周宏军 20200616  增加AT02配置
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
        strName.Format(_T("GOOSEIN第%d组"), nIndex+1);
#else
		strName.Format(g_sLangTxt_GooseinGroup/*_T("GOOSEIN第%d组")*/, nIndex+1);
#endif
		return strName;
	}
};

