//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGinCh.h  CIecCfgGinCh

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataGooseChBase.h"


class CIecCfgGinCh : public CIecCfgDataGooseChBase
{
public:
	CIecCfgGinCh();
	virtual ~CIecCfgGinCh();

	int m_nColIndex;	//列序
	int m_nPos;			//位
	CString  m_strAppChIDText;
	CString m_strDefaultValue;//数值，增加初始值
	CString m_strExternAddr;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGINCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgGinChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	DWORD   GetGinAppID();
	void    SetGinAppID(DWORD dwAppID);
	void InitAppIDText();
	virtual void InitAfterRead();

	void   SetBinString(const CString &strBinID);
	void   AddBinString(const CString &strBinID);
	void   RemoveBinString(const CString &strBinID);
	int GetChPos();
	void CopyToGoutCh(CIecCfgDataGooseChBase *pGoutCh);//2023.6.2 zhouhj 把订阅控制块数据拷贝到发布
//私有成员变量
private:

//私有成员变量访问方法
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
	//virtual void SetDataTypeByName(const CString &strName);
	virtual void InitDataTypeName(BOOL bInitBin=FALSE);
	BOOL IsDefaultValue();
	void CheckDefautValue();//zhouhj 20210912 用于检查设置缺省值,如其不满足对应数据类型要求,则将其改为满足要求的字符串
// 	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// 	{
// 		pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_GOOSEIN;
// 		return 0;
// 	}
protected:
	void CheckDefautValue_ChTypeSingle();
	void CheckDefautValue_ChTypeDouble();
	void CheckDefautValue_ChTypeQuality();
	void CheckDefautValue_ChTypeFloat();
	void CheckDefautValue_ChTypeString();
	void CheckDefautValue_ChTypeInteger();
	void CheckDefautValue_ChTypeUInteger();
};

