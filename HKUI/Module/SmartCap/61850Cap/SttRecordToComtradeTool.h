#pragma once

#include "../../BaseClass/ExBaseList.h"
#include "../../Record/Comtrade/ComtradeMngr.h"
#include "CapDevice/CapDeviceMngr.h"
#include "CapDevice/CapDeviceRecord.h"
#include "CapDevice/CapDeviceRcdCh.h"

//定义录波接受缓存，默认最大缓存为K，即K批量处理一次
#define COMTRADE_RCD_BUFFER_MAX_LEN   204800
#define STT_RECORD_COMTRADE_REPORTHEAD_POINT   24   //报告头长度
#define STT_RECORD_COMTRADE_RESERVE_POINT   50   //预留点数

#define STT_RECORD_COMTRADE_SAMPLE   _T("Sample")   //采样率
#define STT_RECORD_COMTRADE_ETYPE   _T("RecordType")   //通道类型
#define STT_RECORD_COMTRADE_CHANGTYPE   _T("ChAngType")   //相别
#define STT_RECORD_COMTRADE_PRIMEVALUE   _T("PrimValue")   //一次值
#define STT_RECORD_COMTRADE_SECONDVALUE   _T("SecondValue")   //二次值
//#define STT_RECORD_COMTRADE_MEASGEAR   _T("MeasGear")   //档位
//#define STT_RECORD_COMTRADE_CLAMPRATE   _T("ClampRate")   //夹钳比率
//#define STT_RECORD_COMTRADE_THRESHOLDS   _T("Thresholds")   //门槛值
#define STT_RECORD_COMTRADE_MODULEPOS   _T("Module")   //插件

class SttRecordToComtradeTool
{
public:
	SttRecordToComtradeTool();
	virtual ~SttRecordToComtradeTool();

	void InitRecordSrcDatas_at02dz(const CString &strSrcAt02dzFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList);
	void InitRecordSrcDatas_at02d(const CString &strSrcAt02dFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList);

	BOOL SaveContradeFile(const CString &strComtradeFile, bool bIsDeleteFile);//判断是否删除at02d文件

protected:
	void CreateComtradeFile();//创建comtrade文件对象

	void SetComtradeData(BYTE *pszReadChDatas, CCapDeviceRecord *pCapDeviceRecord, int nCurrPoint);//数据填充
	void SetComtradeAnalogData(CComtradeAnalogData *pDataBase, float fChDatas, int nCurrPoint);//模拟量通道数据填充
	void SetComtradeBinaryData(CComtradeBinaryData *pDataBase, CCapDeviceRcdCh *pCapDeviceRcdCh, float fChDatas, long nBinaryIndex, int nCurrPoint);//数字量通道数据填充

	long GetSrcFilePointNum();//根据文件大小和录波通道及模块，估算当前录波数据的点数
	int m_nModuleNum;//插件总数量

	CString m_strSrcAt02dFilePath;//存储录波数据的源文件
	CExBaseList *m_pRecordChList;//保存到Comtrade文件中的通道及通道顺序
	CCapDeviceMngr *m_pCapDeviceMngr;//录波插件管理模块
	CFile *m_pSrcAt02DFile;

	CRcdComtradeFile m_oRcdComtradeFile;//创建的comtrade链表
};



