//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.h  CIecCfgData6044

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgSmvDataBase.h"

#include "IecCfg6044Chs.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CIecCfg6044CommonData : public CIecCfgSmvDataBase
{
public:
	CIecCfg6044CommonData();
	virtual ~CIecCfg6044CommonData();

	long m_nDelayTime;//20220805 zhouhj 在南瑞2M中作为Idx 值范围0~21
	long m_nSmpCntType;//20220805 zhouhj 在南瑞2M中作为地址码值 值范围0~255
	long m_nSmpDataLen;  
	long m_nBlockType;//20220805 zhouhj  在南瑞2M中作为报文类别 0-数据报文、1-命令报文
	long m_nSCP;
	long m_nSCM;
	long m_nSV;
	long m_nBaudRate;
	double m_dInomProt;
	double m_dInomMeas;
	long m_nDcVol;
	long m_nDcCur;
	long m_nDcNeuatralVol;//直流中性母线电压码值
	double m_dDcVolPrim;
	double m_dDcCurPrim;
	double m_dDcNeutralPrim;
	CString m_strProtocolID;//20230420 zhouhj  协议ID,有该ID对应的通道数和通道描述不允许修改

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData6044CommonKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg6044Common.xml");	}

	void GenerateCommon_GroupDatas(CDataGroup *pCommonChs);
	void ReadCommon_GroupDatas(CDataGroup *pCommonChs);
	long GetPkgLenth();
	long GetPkgLenth(long nFT3CrcType);//20240802 suyang 增加CRC类型 0-标准16字节校验，1-报文末尾校验，2-第一个数据块14字节校验

//私有成员变量
// private:
// 	long m_nFT3CrcType;//20240806 suyang 增加传入CRC类型
//私有成员变量访问方法
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
		strName.Format(_T("6044-8-Common(%d)"), nIndex);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("FT3Common第%d组"), nIndex+1);
		return strName;
	}

	virtual void GetCommData(CIecCfgDataSmvCommon *pCommon);
	virtual void InitByCommData(CIecCfgDataSmvCommon *pCommon);

// 	virtual long GetFT3CrcType()
// 	{
// 		return  m_nFT3CrcType;
// 	}

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValuee);
	virtual BOOL SetCfgDataValues(long nDataID, unsigned long long &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//周宏军 2024.3.2  增加AT02配置
#endif

};

