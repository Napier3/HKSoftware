#pragma once

#include "../../BaseClass/ExBaseList.h"
#include "../../Record/Comtrade/ComtradeMngr.h"
#include "CapDevice/CapDeviceMngr.h"
#include "CapDevice/CapDeviceRecord.h"
#include "CapDevice/CapDeviceRcdCh.h"

//����¼�����ܻ��棬Ĭ����󻺴�ΪK����K��������һ��
#define COMTRADE_RCD_BUFFER_MAX_LEN   204800
#define STT_RECORD_COMTRADE_REPORTHEAD_POINT   24   //����ͷ����
#define STT_RECORD_COMTRADE_RESERVE_POINT   50   //Ԥ������

#define STT_RECORD_COMTRADE_SAMPLE   _T("Sample")   //������
#define STT_RECORD_COMTRADE_ETYPE   _T("RecordType")   //ͨ������
#define STT_RECORD_COMTRADE_CHANGTYPE   _T("ChAngType")   //���
#define STT_RECORD_COMTRADE_PRIMEVALUE   _T("PrimValue")   //һ��ֵ
#define STT_RECORD_COMTRADE_SECONDVALUE   _T("SecondValue")   //����ֵ
//#define STT_RECORD_COMTRADE_MEASGEAR   _T("MeasGear")   //��λ
//#define STT_RECORD_COMTRADE_CLAMPRATE   _T("ClampRate")   //��ǯ����
//#define STT_RECORD_COMTRADE_THRESHOLDS   _T("Thresholds")   //�ż�ֵ
#define STT_RECORD_COMTRADE_MODULEPOS   _T("Module")   //���

class SttRecordToComtradeTool
{
public:
	SttRecordToComtradeTool();
	virtual ~SttRecordToComtradeTool();

	void InitRecordSrcDatas_at02dz(const CString &strSrcAt02dzFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList);
	void InitRecordSrcDatas_at02d(const CString &strSrcAt02dFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList);

	BOOL SaveContradeFile(const CString &strComtradeFile, bool bIsDeleteFile);//�ж��Ƿ�ɾ��at02d�ļ�

protected:
	void CreateComtradeFile();//����comtrade�ļ�����

	void SetComtradeData(BYTE *pszReadChDatas, CCapDeviceRecord *pCapDeviceRecord, int nCurrPoint);//�������
	void SetComtradeAnalogData(CComtradeAnalogData *pDataBase, float fChDatas, int nCurrPoint);//ģ����ͨ���������
	void SetComtradeBinaryData(CComtradeBinaryData *pDataBase, CCapDeviceRcdCh *pCapDeviceRcdCh, float fChDatas, long nBinaryIndex, int nCurrPoint);//������ͨ���������

	long GetSrcFilePointNum();//�����ļ���С��¼��ͨ����ģ�飬���㵱ǰ¼�����ݵĵ���
	int m_nModuleNum;//���������

	CString m_strSrcAt02dFilePath;//�洢¼�����ݵ�Դ�ļ�
	CExBaseList *m_pRecordChList;//���浽Comtrade�ļ��е�ͨ����ͨ��˳��
	CCapDeviceMngr *m_pCapDeviceMngr;//¼���������ģ��
	CFile *m_pSrcAt02DFile;

	CRcdComtradeFile m_oRcdComtradeFile;//������comtrade����
};



