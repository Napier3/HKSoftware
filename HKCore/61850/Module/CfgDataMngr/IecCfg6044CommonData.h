//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	long m_nDelayTime;//20220805 zhouhj ������2M����ΪIdx ֵ��Χ0~21
	long m_nSmpCntType;//20220805 zhouhj ������2M����Ϊ��ַ��ֵ ֵ��Χ0~255
	long m_nSmpDataLen;  
	long m_nBlockType;//20220805 zhouhj  ������2M����Ϊ������� 0-���ݱ��ġ�1-�����
	long m_nSCP;
	long m_nSCM;
	long m_nSV;
	long m_nBaudRate;
	double m_dInomProt;
	double m_dInomMeas;
	long m_nDcVol;
	long m_nDcCur;
	long m_nDcNeuatralVol;//ֱ������ĸ�ߵ�ѹ��ֵ
	double m_dDcVolPrim;
	double m_dDcCurPrim;
	double m_dDcNeutralPrim;
	CString m_strProtocolID;//20230420 zhouhj  Э��ID,�и�ID��Ӧ��ͨ������ͨ�������������޸�

//���غ���
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
	long GetPkgLenth(long nFT3CrcType);//20240802 suyang ����CRC���� 0-��׼16�ֽ�У�飬1-����ĩβУ�飬2-��һ�����ݿ�14�ֽ�У��

//˽�г�Ա����
// private:
// 	long m_nFT3CrcType;//20240806 suyang ���Ӵ���CRC����
//˽�г�Ա�������ʷ���
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
		strName.Format(_T("FT3Common��%d��"), nIndex+1);
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
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//�ܺ�� 2024.3.2  ����AT02����
#endif

};

