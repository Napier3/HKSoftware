//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceChBase.h  CCapDeviceChBase

#pragma once

#include "CapDeviceGlobal.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataChBase.h"
#include "../../../DataMngr/DvmDataset.h"


#define CAP_DATASET_MAP_ID_dsSV1                  _T("dsSV1")
#define CAP_DATASET_MAP_ID_dsSV                  _T("dsSV")
#define CAP_DATASET_MAP_ID_DISCRETE    _T("dsDiscrete")
#define CAP_DATASET_MAP_ID_SVERR          _T("dsSVErr")
#define CAP_DATASET_MAP_ID_GSERR          _T("dsGooseErr")
#define CAP_DATASET_MAP_ID_GOUT                  _T("dsGout")
#define CAP_DATASET_MAP_ID_GIN                  _T("dsGin")
#define CAP_DATASET_MAP_ID_THD                  _T("dsTHD")
#define CAP_DATASET_MAP_ID_SVINST                  _T("dsSVInst")
#define CAP_DATASET_MAP_ID_SVDELAY               _T("dsSVDelay")
#define  CAP_DATASET_MAP_ID_State             _T("dsState")
#define  CAP_DATASET_MAP_ID_Report             _T("report")
#define  CAP_DATASET_MAP_ID_SVSYN            _T("dsSVSyn")
#define  CAP_DATASET_MAP_ID_GSSYN            _T("dsGooseSyn")
#define  CAP_DATASET_MAP_ID_LinkState            _T("dsLinkState")
#define  CAP_DATASET_MAP_ID_IecDetect            _T("dsIecDetect")
#define  CAP_DATASET_MAP_ID_RcdStep6U6I           _T("dsRcdStep6U6I")
#define	 CAP_DATASET_MAP_ID_TestFunSelect			_T("dsFunSelect")//2024-4-30 zhouyangyong
#define  CAP_DATASET_MAP_ID_RcdStepResponse       _T("dsResponseTimeRlt")
#define  CAP_DATASET_MAP_ID_MUTime            _T("dsTime")
#define  CAP_DATASET_MAP_ID_dsMUTimeRlt       _T("dsMUTimeRlt")
#define  CAP_DATASET_MAP_ID_dsCurrErrorRange       _T("dsCurrErrorRange")
#define  CAP_DATASET_MAP_ID_dsErrorRanges       _T("dsErrorRanges")
#define  CAP_DATASET_MAP_ID_IEDTest           _T("dsIEDTest")
#define  CAP_DATASET_MAP_ID_GIN1            _T("dsGin1")
#define  CAP_DATASET_MAP_ID_GOUT1           _T("dsGout1")
#define  CAP_DATASET_MAP_ID_dsStateValueChangedRlt      _T("dsStateValueChangedRlt")


#define  CAP_DATASET_MAP_ID_GOCSTC           _T("dsGoCstc")
#define  CAP_DATASET_MAP_ID_SVCSTC           _T("dsSVCstc")
#define  CAP_DATASET_MAP_ID_SVHis            _T("dsSVHis")//zhouhj 2023.10.13 ��ʷ����

//lijunqing 2022-5-8  lijunqing
#define  CAP_DATASET_MAP_ID_Power           _T("Power")
#define  CAP_DATASET_MAP_ID_Vector           _T("Vector")
#define  CAP_DATASET_MAP_ID_AD				_T("AD")
#define  CAP_DATASET_MAP_ID_AD_DMAG				_T("dmag") 
#define  CAP_DATASET_MAP_ID_AD_DANG				_T("dang") 
#define  CAP_DATASET_MAP_ID_AD_DMAG_ABS		_T("dmag_abs") 
#define  CAP_DATASET_MAP_ID_AD_DANG_ABS		_T("dang_abs") 
#define  CAP_DATASET_MAP_ID_Vector_Positive           _T("Positive")
#define  CAP_DATASET_MAP_ID_Vector_Negative           _T("Negative")
#define  CAP_DATASET_MAP_ID_Vector_Zero           _T("Zero")

//����ͨ��
#define CAPDEVICE_CHTYPE_I   0
//��ѹͨ��
#define CAPDEVICE_CHTYPE_U   1
//ʱ��ͨ��
#define CAPDEVICE_CHTYPE_T	 2
//������ͨ��
#define CAPDEVICE_CHTYPE_B	 3
//δ֪ͨ������
#define CAPDEVICE_CHTYPE_N   4






//2022-5-26  lijunqing
#define IEC_PkgAnalyze_ID_Test			"Test"
#define IEC_PkgAnalyze_ID_DevVersion		"DevVersion"
#define IEC_PkgAnalyze_ID_PDUlength		"PDUlength"
#define IEC_PkgAnalyze_ID_Channel			"Channel"
#define IEC_PkgAnalyze_ID_VLAN_ID			"VLAN_ID"
#define IEC_PkgAnalyze_ID_VLANPriority		"VLANPriority"
#define IEC_PkgAnalyze_ID_SynState			"SynState"
#define IEC_PkgAnalyze_ID_SampRate		"SampRate"
#define IEC_PkgAnalyze_ID_ASDUNumber	"ASDUNumber"
#define IEC_PkgAnalyze_ID_DstMAC			"DstMAC"
#define IEC_PkgAnalyze_ID_SVID				"SVID"
#define IEC_PkgAnalyze_ID_ContrlRef				"ContrlRef"
#define IEC_PkgAnalyze_ID_GOOSEID				"GOOSEID"
#define IEC_PkgAnalyze_ID_DataSet				"DataSet"//wangtao add 20240509 ����̽������DataSet�ȶ�

inline CString cap_iefcgdata_id_to_ds_id(const CString &strIecfgDataID)
{
	CString strTmp;
	strTmp = strIecfgDataID;

	if (strIecfgDataID.GetLength()>0)
	{
		strTmp = strIecfgDataID.Left(strIecfgDataID.GetLength()-1);
	}

	if (strTmp == _T("SVAccuracyTest"))				//����׼ȷ�Ȳ���
	{
		return CAP_DATASET_MAP_ID_SVINST;								
	}
	else if(strTmp == _T("ThdTest"))				//�����ʲ���
	{
		return _T("dsTHD");
	}
	else if (strTmp == _T("DispersionTest"))		//��ɢ�Ȳ���
	{
		return _T("dsDiscrete");
	}
	else if (strTmp == _T("SvDelayTest"))			//SV��ʱ����
	{
		return _T("dsSVDelay");
	}
	else if (strTmp == _T("SVSnyTest"))				//SVͬ�������
	{
		return _T("dsSVSyn");
	}
	else if (strTmp == _T("GooseSnyTest"))			//GOOSEͬ�������
	{
		return _T("dsGooseSyn");
	}
	else if (strTmp == _T("TimeMeasureTest"))		//ʱ�����׼ȷ�Ȳ���
	{
		return _T("dsState");
	}
	else if(strTmp == _T("GooseCstcTest"))			//GOOSE����һ����
	{
		return _T("dsGoCstc");
	}
	else if (strTmp == _T("SvAbnormalTest"))		//�ɼ������쳣ģ��
	{
		return _T("dsSVErr");
	}
	else if(strTmp == _T("GooseErrorTest"))			//GOOSE�����쳣ģ��
	{
		return _T("dsGooseErr");
	}
	else
	{
		return _T("");
	}
}

BOOL Is_SvDataSetID(const CString &strID);
BOOL Is_SvDataset(CDvmDataset *pDataset);

BOOL Is_GsDataSetID(const CString &strID, const CString &strGsTypeID);
BOOL Is_GsDataSetID_Gin(const CString &strID);
BOOL Is_GsDataSetID_Gout(const CString &strID);
BOOL Is_GsDataSetID(const CString &strID);
BOOL Is_GsDataset(CDvmDataset *pDataset);

class CCapRecordInterface
{
public:
	virtual void CapRecord(WORD wValue) = 0;
	virtual void CapRecord(long wValue) = 0;
	virtual void CapRecord(float fValue) = 0;
	virtual void CapRecord(double dValue) = 0;
	virtual void CapRecord(WORD wValue, long nPos) = 0;
	virtual void CapRecord(long wValue, long nPos) = 0;
	virtual void CapRecord(float fValue, long nPos) = 0;
	virtual void CapRecord(double dValue, long nPos) = 0;
	virtual void SetPosition(long nPos, long nDataCount) = 0;
};

//ץ��ͨ�����󣬼�̽�⵽��ͨ������m_pCapRecordΪץ�����ݴ洢����
//ץ�������У�����ÿ��ͨ���Ĳ������ݶ���Ҫ���棬ֻ����ͼ�¼ѡ���ͨ��
//��¼�������ݵ�ͨ������ΪCCapDeviceChRecord��m_pCapRecord��
class CCapDeviceChBase : public CExBaseObject
{
public:
	CCapDeviceChBase();
	virtual ~CCapDeviceChBase();

	long m_nSelect;
	long m_nChType;
	UINT m_nLength;

	long m_nMatchState;	//0-��ʼδƥ�䣻1-ƥ��ɹ���2-���ࣻ3-ȱ��
	CExBaseObject *m_pRefDvmData;   //�������豸����ģ�Ͷ���

	void AttachIecCfgDataCh(CIecCfgDataChBase *pCfgDataCh);
	void InitNameID(const CString& strID);
	void InitNameID(long nDvIndex, long nChIndex);
	void SetMatchState(long nMatchState)	{	m_nMatchState = nMatchState;  }

	virtual void InitChannel(CIecCfgDataChBase *pIecCfgDataCh);
	virtual void InitChannel(CDvmData *pChData);
	virtual void InitChannelAttrs(CDvmData *pChData);
	virtual void UpdateChTypeAndLength(WORD wChType,WORD wLength);
	virtual void InitAfterSetChType(){}//20220611 ������ͨ�����ͺ�,����ͨ����Ҫ���г�ʼ��,��SMV����

private:
	CCapRecordInterface *m_pCapRecord;

//���غ���
public:
	void SetSelect(long nSelect)		
	{	
		m_nSelect = nSelect;	
// 		if (nSelect == 0)
// 		{
// 			m_pCapRecord = NULL;
// 		}
	}
	long GetSelect()					{	return m_nSelect;		}
	void AttachCapRecord(CCapRecordInterface *pRecord)	{	m_pCapRecord = pRecord;	}

	void CapRecord(long wValue)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->CapRecord(wValue);
		}
	}
	void CapRecord(long wValue, long nPos)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->CapRecord(wValue, nPos);
		}
	}

	void SetPosition(long nPos, long nDataCount)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->SetPosition(nPos, nDataCount);
		}
	}
};

