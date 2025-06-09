
#ifndef _PQD_EXAMP_H_
#define _PQD_EXAMP_H_

#include <stdio.h>
#include "pqdif_ph.h"
#include "..\BaseClass\BaseList.h"
#include "pqdif_id.h"
#include "..\..\Module\BaseClass\WSerializeBuff.h"
#include "math.h"


// #define  _LOG_PQDIF_
#define _PQDIF_USE_BUFFER_

// #include "pqdifr.h"

//  IMPORTANT NOTE
//  ==============
//  The typedefs and MAX_ definitions used here are limits for the
//  sample code itself. They are *NOT* inherent limits in the PQDIF
//  format.
//
typedef char    BUFFER64    [ 128 ];
typedef char    BUFFER512   [ 512 ];
typedef long    BOOL4;

#define MAX_COUNT_CHANNELS      64  // Used only in PQDIFw
#define MAX_COUNT_SERIES        8   // Used only in PQDIFw
#define MAX_COUNT_TRANSDUCERS   8
#define MAX_COUNT_CALIBRATIONS  8

#define MAX_COUNT_PTS_FULLSCALE (MAX_COUNT_CHANNELS)
#define MAX_COUNT_PTS_NOISEFLR  (MAX_COUNT_CHANNELS)
#define MAX_COUNT_PTS_FREQRESP  16
#define MAX_COUNT_PTS_APPLIED   16

#define MAX_COUNT_PTS_MEASURED  2048 // Used only in PQDIFw


class container_example : public CBaseObject
{
public:
	container_example(){};
	virtual ~container_example(){};

	void Init()
	{
		iFormatVersionMajor = 0;
		iFormatVersionMinor = 0;
		ZeroMemory(szFileName, sizeof(BUFFER512));
		ZeroMemory(szLanguage, sizeof(BUFFER64));
		ZeroMemory(&tsCreation, sizeof(ts));
		ZeroMemory(&tsLastSaved, sizeof(ts));
		nTimesSaved = 0;
		compStyleRecordLevel = 0;
		compAlgZlig = 0;
	}
public:
    INT4    iFormatVersionMajor;        //  Version number of this file format
    INT4    iFormatVersionMinor;        //      "    "

    BUFFER512    szFileName;             //  Original file name

    ts          tsCreation;             //  Optional time of creation of container
    ts          tsLastSaved;            //  Optional time of last write to container
    INT4        nTimesSaved;            //  Number of times container written to

    BUFFER64    szLanguage;             //  preferred language for display
	
	INT4	compStyleRecordLevel;
	INT4	compAlgZlig;

public:
	virtual CBaseObject* Clone()
	{
		container_example* pClone = new container_example();
		Copy(pClone);
		return pClone;
	}

	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		container_example *p = (container_example*)pDest;
		strcpy(p->szFileName, szFileName);
		strcpy(p->szLanguage, szLanguage);
		p->iFormatVersionMajor = iFormatVersionMajor;    
		p->iFormatVersionMinor = iFormatVersionMinor;
		p->tsCreation = tsCreation;    
		p->tsLastSaved = tsLastSaved;    
		p->nTimesSaved = nTimesSaved; 
		p->compStyleRecordLevel = compStyleRecordLevel;    
		p->compAlgZlig = compAlgZlig; 

		return TRUE;
	}

};

class series_defn : public CBaseObject
{
public:
	series_defn()
	{
		ZeroMemory(&idValueType, sizeof(GUID));
		ZeroMemory(&idCharacteristicType, sizeof(GUID));
		idQuantityUnits = 0;
		idMethod = 0;
		idGreekPrefix = 0;
	};
	virtual ~series_defn(){};

public:
	GUID    idValueType;            //  ID_SERIES_VALUE_TYPE_ ...
    UINT4   idQuantityUnits;        //  volts, amps, etc.
    GUID    idCharacteristicType;   //  ...
	UINT4   idMethod;               //  values, scaled values, start/increment
	UINT4   idGreekPrefix;          //  femto, pico, nano, etc.

public:
	virtual CBaseObject* Clone()
	{
		series_defn* pClone = new series_defn();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		series_defn *p = (series_defn*)pDest;
		p->idValueType = idValueType;    
		p->idQuantityUnits = idQuantityUnits;
		p->idCharacteristicType = idCharacteristicType;    
		p->idMethod = idMethod;    
		p->idGreekPrefix = idGreekPrefix;    

		return TRUE;
	}

	BOOL Get_Characteristic(CString &strCharacteristic)
	{
		size_t i;
		strCharacteristic = _T("ID_QC_NONE");
		BOOL bFind = FALSE;
		size_t characteristicNum = sizeof(valCStr_characteristic) / sizeof(STRUCT_GuidCString);

		for ( i = 0; i < characteristicNum; ++i )
		{
			if ( PQDIF_IsEqualGUID( idCharacteristicType, valCStr_characteristic[i].value ) ) 
			{
				strCharacteristic = (CString)valCStr_characteristic[i].cstr;
				bFind = TRUE;
				break;
			}
		}

		return bFind;
	}

	BOOL Get_TypeValue( CString &strTypeValue )
	{
		BOOL bFind = FALSE;
		strTypeValue = _T("ID_SERIES_VALUE_TYPE_NONE");

		size_t num = sizeof(valCStr_valuetype) / sizeof(STRUCT_GuidCString);
		for ( size_t i = 0; i < num; ++i )
		{
			if ( PQDIF_IsEqualGUID( idValueType, valCStr_valuetype[i].value ) ) 
			{
				strTypeValue = (CString)valCStr_valuetype[i].cstr;
				bFind = TRUE;
				break;
			}
		}

		return bFind;
	}
};

typedef CTLinkList<series_defn> list_series_defn;

class channel_defn : public CBaseList
{
public:
	channel_defn()
	{
		szChannelName.Empty();
		//ZeroMemory(szChannelName, sizeof(BUFFER64));
		idPhase = 0;
		ZeroMemory(&idQuantityType, sizeof(GUID));
		idQuantityMeasured = 0;
		nSeries = 0;
	};
	virtual ~channel_defn()
	{
		nSeries = 0;
	};

public:
    //BUFFER64    szChannelName;      //  Channel name
	CString     szChannelName;
    UINT4       idPhase;            //  Phase or other name
    GUID        idQuantityType;     //  ID_QT_VALUELOG ID_QT_WAVEFORM
	UINT4       idQuantityMeasured; // 

    //  Series definitions
    long            nSeries;
    //series_defn *   asd;
	//list_series_defn  asd;

public:
	virtual CBaseObject* Clone()
	{
		channel_defn* pClone = new channel_defn();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		channel_defn *p = (channel_defn*)pDest;
		//strcpy(p->szChannelName, szChannelName);
		p->szChannelName = szChannelName;    
		p->idPhase = idPhase;    
		p->idQuantityType = idQuantityType;
		p->idQuantityMeasured = idQuantityMeasured;    
		p->nSeries = nSeries;    

		return TRUE;
	}

	series_defn* add()
	{
		series_defn *p = new series_defn();
		AddTail(p);
		return p;
	}

	series_defn* Get_series(long nIndex)
	{
		return (series_defn*)GetAtIndex(nIndex);
	}

	long GetSeriesIndex(const GUID &guidCur)
	{
		POS pos = GetHeadPosition();
		series_defn *pSeriesDefn = NULL;
		long nSeriesIndex = 0;

		while(pos)
		{
			pSeriesDefn = (series_defn *)GetNext(pos);

			if ( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, guidCur))
			{
				return nSeriesIndex;
			}

			nSeriesIndex++;
		}

		return -1;
	}
};

typedef CTLinkList<channel_defn> list_channel_defn;

class datasource_example : public CBaseList
{
public:
	datasource_example(){Init();};
	virtual ~datasource_example(){};

	void Init()
	{
		ZeroMemory(&idType, sizeof(GUID));
		ZeroMemory(&idVendorID, sizeof(GUID));
		ZeroMemory(&idEquipID, sizeof(GUID));
		nChannel = 0;
	}
public:
   GUID                idType;             //  measure, manual, simulate - required
    GUID                idVendorID;         //  Registered ID of vendor (implicit in equipment ID?)
    GUID                idEquipID;          //  Registered ID of equipment, program

    INT4                nChannel;
   // channel_defn *      acd;
	//list_channel_defn     acd;
	CString strStdFile;

public:
	virtual CBaseObject* Clone()
	{
		datasource_example* pClone = new datasource_example();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		datasource_example *p = (datasource_example*)pDest;
		p->idType = idType;    
		p->idVendorID = idVendorID;
		p->idEquipID = idEquipID;    
		p->nChannel = nChannel;

		return TRUE;
	}

	channel_defn* add()
	{
		channel_defn *p = new channel_defn();
		AddTail(p);
		return p;
	}

	channel_defn* Get_channel(long nIndex)
	{
		return (channel_defn*)GetAtIndex(nIndex);
	}

	BOOL Get_channel(const CString &strChID,channel_defn **ppCurCh,long &nChIndex)
	{
		POS pos = GetHeadPosition();
		channel_defn *pCurCh = NULL;
		nChIndex = 0;

		while(pos)
		{
			pCurCh = (channel_defn *)GetNext(pos);

			if (pCurCh->szChannelName == strChID)
			{
				*ppCurCh = pCurCh;
				return TRUE;
			}

			nChIndex++;
		}

		return FALSE;
	}

	channel_defn* Get_channel(const CString &strChID)
	{
		POS pos = GetHeadPosition();
		channel_defn *pCurCh = NULL;

		while(pos)
		{
			pCurCh = (channel_defn *)GetNext(pos);

			if (pCurCh->szChannelName == strChID)
			{
				return pCurCh;
			}
		}

		return NULL;
	}

	long Get_channel_index(const CString &strChID)
	{
		POS pos = GetHeadPosition();
		channel_defn *pCurCh = NULL;
		long nChIndex = 0;

		while(pos)
		{
			pCurCh = (channel_defn *)GetNext(pos);

			if (pCurCh->szChannelName == strChID)
			{
				return nChIndex;
			}

			nChIndex++;
		}

		return -1;
	}
};


// RECORD TYPE: MONITORSETTINGS
class mon_sett_one_channel : public CBaseObject
{
public:
	mon_sett_one_channel(){};
	virtual ~mon_sett_one_channel(){};

};

typedef CTLinkList<mon_sett_one_channel> list_mon_sett_one_channel;

class monitorsettings_example : public CBaseList
{
public:
	monitorsettings_example(){Init();};
	virtual ~monitorsettings_example(){};

	void Init()
	{
		ZeroMemory(&tsEffective, sizeof(ts));
		ZeroMemory(&tsInstalled, sizeof(ts));
		bUseCalibration = 0;
		bUseTransducer = 0;
		nChannel = 0;
	}

public:
    ts      tsEffective;        //  The date/time these settings became effective
    ts      tsInstalled;        //  If a monitor, time put in service
    BOOL4   bUseCalibration;    //  Flag indicating whether calibration data
                                //  should be used to compensate channel data
    BOOL4   bUseTransducer;     //  Flag indicating whether transducer data
                                //  should be used to compensate channel data

    long                    nChannel;
    //mon_sett_one_channel *  ams;
	//list_mon_sett_one_channel  ams;

public:
	virtual CBaseObject* Clone()
	{
		monitorsettings_example* pClone = new monitorsettings_example();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		monitorsettings_example *p = (monitorsettings_example*)pDest;
		p->tsEffective = tsEffective;           //  Creation time for this record
		p->tsInstalled = tsInstalled;
		p->bUseCalibration = bUseCalibration;          //  If triggered data, trigger time
		p->bUseTransducer = bUseTransducer;
		p->nChannel = nChannel;

		return TRUE;
	}

	mon_sett_one_channel* add()
	{
		mon_sett_one_channel *p = new mon_sett_one_channel();
		AddTail(p);
		return p;
	}
};

extern   time_t s_observation_tsStart;

// RECORD TYPE: OBSERVATION
class series_instance: public CBaseObject
{
public:
	series_instance()
	{
		paData = NULL;
		IsTime = 0;
		dScale = 1;
		dOffset = 0;
		nTotalValues = 0;       //  Total values (in case ID_SERIES_METHOD_INCREMENT is used)
		typePhysical = 0;
		shared = 0;             //  Is the data shared with another series?
		idxSharedChannel = 0;
		idxSharedSeries = 0;
		paData = NULL;             //  [nValues or nTotalValues]
		nTotalValues = 0;
	};
	virtual ~series_instance()
	{
		if (paData != NULL)
		{
			delete paData;
		}
	};

	void Set_paData(double *p)
	{
		if (paData != NULL)
		{
			delete paData;
		}

		paData = p;
	}
public:
	REAL8       dScale;             //  Multiply data by scale to get value
    REAL8       dOffset;            //  Add offset to scaled result
    // SIZE4       nValues;            //  Physical values in array
    SIZE4       nTotalValues;       //  Total values (in case ID_SERIES_METHOD_INCREMENT is used)
    UINT4       typePhysical;
    BOOL        shared;             //  Is the data shared with another series?
    UINT4       idxSharedChannel;
    UINT4       idxSharedSeries;

    double *    paData;             //  [nValues or nTotalValues]
	int         IsTime;
public:
	virtual CBaseObject* Clone()
	{
		series_instance* pClone = new series_instance();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		series_instance *p = (series_instance*)pDest;
		p->dScale = dScale;           //  Creation time for this record
		p->dOffset = dOffset;
		//p->nValues = nTotalValues;          //  If triggered data, trigger time
		p->nTotalValues = nTotalValues;
		p->typePhysical = typePhysical;
		p->shared = shared;
		p->idxSharedChannel = idxSharedChannel;
		p->idxSharedSeries = idxSharedSeries;
		p->IsTime = IsTime;
		
		if (p->paData != NULL)
		{
		delete p->paData;
		}

		p->paData = paData;

		if (paData != NULL)
		{
			for (long nIndex = 0; nIndex<nTotalValues; nIndex++)
			{
				p->paData[nIndex] =/* s_observation_tsStart + */paData[nIndex];
			}
		}

		paData = NULL;

		return TRUE;
	}

	void InitTmtimeSeries(const time_t &tsStart)
	{
		IsTime = 1;

		if (paData == NULL)
		{
			return;
		}

		for (long nIndex = 0; nIndex<nTotalValues; nIndex++)
		{
			paData[nIndex] = (double)(tsStart + paData[nIndex]);
		}
	}

	void AppendDatas(series_instance *pSrc)
	{
		if (pSrc->nTotalValues <= 0)
		{
			return;
		}

		long nNewValues = nTotalValues + pSrc->nTotalValues;
		double *pNewData = new double[nNewValues];

		if (paData != NULL)
		{
			memcpy(pNewData, paData, sizeof(double)*nTotalValues);
		}

		if (pSrc->paData != NULL)
		{
			memcpy(pNewData + nTotalValues, pSrc->paData, sizeof(double)*pSrc->nTotalValues);
		}

		delete paData;
		paData = pNewData;
		nTotalValues += pSrc->nTotalValues;

		if (nTotalValues < 0)
		{
			nTotalValues = nTotalValues;
		}
// 		if (nTotalValues== 10)
// 		{
// 			nTotalValues++;
// 			nTotalValues--;
// 		}

	}
};

typedef CTLinkList<series_instance> list_series_instance;

static BOOL g_b_channel_instance_error = 0;

class channel_instance : public CBaseList
{
public:
	channel_instance(){};
	virtual ~channel_instance(){};

public:
    UINT4           idxChannel;         //  Channel definition used for this channel
    UINT4           idxChannelDefn;     //  Channel definition (in data source) used for this channel
	REAL8			channelFreq;
    SIZE4           nSeries;
    //series_instance *   asi;
	//list_series_instance  asi;

public:
	virtual CBaseObject* Clone()
	{
		channel_instance* pClone = new channel_instance();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		channel_instance *p = (channel_instance*)pDest;
		p->idxChannel = idxChannel;           //  Creation time for this record
		p->idxChannelDefn = idxChannelDefn;
		p->channelFreq = channelFreq;          //  If triggered data, trigger time
		p->nSeries = nSeries;

		return TRUE;
	}


	series_instance* add()
	{
		series_instance *p = new series_instance();
		AddTail(p);
		return p;
	}

	series_instance* Get_series(long nIndex)
	{
		return (series_instance*)GetAtIndex(nIndex);
	}

	series_instance* Get_series_time()
	{
		POS pos = GetHeadPosition();
		series_instance *pSeries = NULL;

		while(pos)
		{
			pSeries = (series_instance *)GetNext(pos);

			if (pSeries->IsTime)
			{
				return pSeries;
			}
		}

		return NULL;
	}

	void InitTmtimeSeries(int timeSeries,const time_t &tsStart)
	{
		series_instance *p = (series_instance*)GetAtIndex(timeSeries);
		g_b_channel_instance_error = 0;

		if (p == NULL)
		{
			g_b_channel_instance_error = 1;
			return;
		}

		if (p->paData == NULL || p->nTotalValues < 0)
		{
			g_b_channel_instance_error = 1;
			return;
		}
		
		p->InitTmtimeSeries(tsStart);
	}

	void AppendChannelDatas(channel_instance *pSrc)
	{
		long nCount1 = GetCount();
		long nIndex = 0;
		series_instance *p1 = NULL, *p2 = NULL;

		for (nIndex=0; nIndex<nCount1; nIndex++)
		{
			p1 = (series_instance *)GetAtIndex(nIndex);
			p2 = (series_instance *)pSrc->GetAtIndex(nIndex);

			if (p1 == NULL || p2 ==NULL)
			{
				break;
			}

			p1->AppendDatas(p2);
		}
	}

	double GeSerialValue(long nSeriesIndex, long keyQueryIndex)
	{
		series_instance *p = (series_instance*)GetAtIndex(nSeriesIndex);

		if (p == NULL)
		{
			return 0;
		}

		if (p->nTotalValues <= keyQueryIndex)
		{
			return 0;
		}

		if (p->paData == NULL)
		{
			return 0;
		}

		return p->paData[keyQueryIndex];
	}
};

typedef CTLinkList<channel_instance> list_channel_instance;

class observation_example : public CBaseList
{
public:
	observation_example(){};
	virtual ~observation_example(){};

	void Init()
	{
		szName.Empty();
		//ZeroMemory(szName, sizeof(BUFFER64));
		ZeroMemory(&tsCreate, sizeof(ts));
		ZeroMemory(&tsStart, sizeof(time_t));
		ZeroMemory(&tsTrigger, sizeof(ts));
		triggerMethod = 0;
		iTriggered = 0;
		idxTriggerChannel = 0;
		nChannels = 0;
	}
public:
	//BUFFER64    szName;             //  Name for this observation
	CString     szName;

    ts          tsCreate;           //  Creation time for this record
    //ts          tsStart;            //  Starting time stamp of data in series
	time_t      tsStart;
	ts          tsTrigger;          //  If triggered data, trigger time

	UINT4       triggerMethod;

    UINT4       iTriggered;         //  Was the observation triggered?
    UINT4       idxTriggerChannel;  //  If triggered data, trigger channel id

    long                nChannels;
    //channel_instance *  aci;
	//list_channel_instance aci;

public:
	virtual CBaseObject* Clone()
	{
		observation_example* pClone = new observation_example();
		Copy(pClone);
		return pClone;
	}
	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		if (this == pDest)
		{
			return TRUE;
		}

		observation_example *p = (observation_example*)pDest;
		//strcpy(p->szName, szName);             //  Name for this observation
		p->szName = szName;
		p->tsCreate = tsCreate;           //  Creation time for this record
		p->tsStart = tsStart;
		p->tsTrigger = tsTrigger;          //  If triggered data, trigger time
		p->triggerMethod = triggerMethod;
		p->iTriggered = iTriggered;         //  Was the observation triggered?
		p->idxTriggerChannel = idxTriggerChannel;  //  If triggered data, trigger channel id

		return TRUE;
	}

	channel_instance* add()
	{
		channel_instance *p = new channel_instance();
		AddTail(p);
		return p;
	}

	channel_instance* Get_channel(long ch)
	{
		channel_instance *pch = (channel_instance*)GetAtIndex(ch);

		return pch;
	}

	series_instance* Get_series(long ch, long series)
	{
		channel_instance *pch = (channel_instance*)GetAtIndex(ch);

		if (pch == NULL)
		{
			return NULL;
		}

		return (series_instance*)pch->GetAtIndex(series);
	}
	
	channel_instance* FindChannel(channel_instance *pSrc)
	{
		POS pos = GetHeadPosition();
		channel_instance *p = NULL, *pFind = NULL;

		while (pos != NULL)
		{
			p = (channel_instance *)GetNext(pos);

			//20230511 zhouhj 浮点数判断相等需要用绝对值差处理,并且会有误差,此处不再判频率
			if (/*(fabs(p->channelFreq - pSrc->channelFreq) <0.00001f) &&*/ (p->idxChannelDefn == pSrc->idxChannelDefn))
			{
				pFind = p;
				break;
			}
		}

		return pFind;
	}

	void InitTmtimeSeries(int timeSeries, time_t &tsStart)
	{
		POS pos = GetHeadPosition();
		channel_instance *p = NULL;

		while (pos != NULL)
		{
			p = (channel_instance *)GetNext(pos);
			p->InitTmtimeSeries(timeSeries, tsStart);
		}
	}

	void AppendChannelDatas(channel_instance *pSrc)
	{
		channel_instance *pFind = FindChannel(pSrc);

		if (pFind == NULL)
		{
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(pFind == NULL)"));
			AddTail(pSrc->Clone());
		}
		else
		{
			pFind->AppendChannelDatas(pSrc);
		}
	}
};


#endif // _PQD_EXAMP_H_