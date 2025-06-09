#pragma once
#include <vector>
using namespace std;

/*****************************
������ҵ���Ľ����ṹ�弰�ӿ�ʵ�֣�
����ο���������ҵ����Э��淶���ĵ�
*****************************/

//���ĸ�ʽ:SensorID[6B] DataLen[4b] FragInd[1b] PacketType[3b] Data CRC16
#define SENSOR_PKG_HEADLEN			7
#define SENSOR_PKG_INDEX_INFO		6
#define SENSOR_PKG_INDEX_DATA		SENSOR_PKG_HEADLEN
#define SENSOR_PKG_INDEX_FRAGDATA	(SENSOR_PKG_INDEX_DATA+4) //��Ƭͷռ4���ֽ�

#define SENSOR_PKG_INDEX_CTRLINFO	7
#define SENSOR_PKG_INDEX_CTRLDATA	(SENSOR_PKG_INDEX_CTRLINFO+1)

//��Ƭָʾ
#define SENSOR_PKG_Frag_NO				0x0
#define SENSOR_PKG_Frag_YES				0x1

//��������
#define SENSOR_PKG_TYPE_MONITOR			0x0
#define SENSOR_PKG_TYPE_MONITOR_ACK		0x1
#define SENSOR_PKG_TYPE_WARNING			0x2
#define SENSOR_PKG_TYPE_WARNING_ACK		0x3
#define SENSOR_PKG_TYPE_CONTROL			0x4
#define SENSOR_PKG_TYPE_CONTROL_ACK		0x5
#define SENSOR_PKG_TYPE_Frag_ACK		0x6

//���Ʊ�������
#define SENSOR_PKG_CTRLTYPE_COMMQUERYSET			0x1
#define SENSOR_PKG_CTRLTYPE_MONITORQUERY			0x2
#define SENSOR_PKG_CTRLTYPE_WARNINGQUERYSET			0x3
#define SENSOR_PKG_CTRLTYPE_TIMEQUERYSET			0x4
#define SENSOR_PKG_CTRLTYPE_SENSORIDQUERYSET		0x5
#define SENSOR_PKG_CTRLTYPE_RESET					0x6
#define SENSOR_PKG_CTRLTYPE_REQUESTADJUSTTIME		0x7


//����������ģ��ID
#define SENSOR_MODEL_ID_Attr			_T("Head")
#define SENSOR_MODEL_ID_FragInd			_T("FragInd")
#define SENSOR_MODEL_ID_PacketType		_T("PacketType")
#define SENSOR_MODEL_ID_CtrlType		_T("CtrlType")
#define SENSOR_MODEL_ID_RequestSetFlag	_T("RequestSetFlag")
#define SENSOR_MODEL_ID_AckStatus		_T("AckStatus")

//��������ID
#define SENSOR_MODEL_ID_ParaType		_T("ParaType")
#define SENSOR_MODEL_ID_DataType		_T("DataType")
#define SENSOR_MODEL_ID_Unit			_T("Unit")
#define SENSOR_MODEL_ID_Decimal			_T("Decimal")
#define SENSOR_MODEL_ID_DataFieldLen	_T("DataFieldLen")
#define SENSOR_MODEL_ID_DataLen			_T("DataLen")

////////////////////////////////////////

typedef union  
{  
	float fdata;  
	unsigned long ldata;  
}FloatLongType;

typedef union  
{  
	double fdata;  
	unsigned long long ldata;  
}DoubleLong64Type;

 /* 
��������fת��Ϊ4���ֽ����ݴ����byte[4]�� 
*/  
inline void Float_to_Byte(float f,unsigned char byte[])  
{  
    FloatLongType fl;  
    fl.fdata=f;  
    byte[0]=(unsigned char)fl.ldata;  
    byte[1]=(unsigned char)(fl.ldata>>8);  
    byte[2]=(unsigned char)(fl.ldata>>16);  
    byte[3]=(unsigned char)(fl.ldata>>24);  
}  
/* 
��4���ֽ�����byte[4]ת��Ϊ�����������*f�� 
*/  
inline void Byte_to_Float(float *f,unsigned char byte[])  
{  
    FloatLongType fl;  
    fl.ldata=0;  
    fl.ldata=byte[3];  
    fl.ldata=(fl.ldata<<8)|byte[2];  
    fl.ldata=(fl.ldata<<8)|byte[1];  
    fl.ldata=(fl.ldata<<8)|byte[0];  
    *f=fl.fdata;  
} 

inline void Double_to_Byte(double f,unsigned char byte[])  
{  
    DoubleLong64Type fl;  
    fl.fdata=f;  
    byte[0]=(unsigned char)fl.ldata;  
    byte[1]=(unsigned char)(fl.ldata>>8);  
    byte[2]=(unsigned char)(fl.ldata>>16);  
    byte[3]=(unsigned char)(fl.ldata>>24);  
	byte[4]=(unsigned char)(fl.ldata>>32);  
	byte[5]=(unsigned char)(fl.ldata>>40); 
	byte[6]=(unsigned char)(fl.ldata>>48);  
	byte[7]=(unsigned char)(fl.ldata>>56); 
}  

inline void Byte_to_Double(double *f,unsigned char byte[])  
{  
    FloatLongType fl;  
    fl.ldata=0;  
    fl.ldata=byte[7];  
    fl.ldata=(fl.ldata<<8)|byte[6];  
    fl.ldata=(fl.ldata<<8)|byte[5];  
    fl.ldata=(fl.ldata<<8)|byte[4];  
	fl.ldata=(fl.ldata<<8)|byte[3]; 
	fl.ldata=(fl.ldata<<8)|byte[2];  
	fl.ldata=(fl.ldata<<8)|byte[1];  
	fl.ldata=(fl.ldata<<8)|byte[0]; 
    *f=fl.fdata;  
} 

////////////////////////////////////

//������ÿ��������Ϣ�ṹ��
typedef struct _sensor_para_data_
{
	unsigned short m_nParaInfo;	//��������+���ݳ����Զ�ָʾλ
	int m_nDataLen;		//���ݳ���
	BYTE *m_pBuff;		//���ݲ���

	_sensor_para_data_()
	{
		m_nParaInfo = 0;
		m_nDataLen = 0;
		m_pBuff = NULL;
	}
	int GetSensorType(){ return (int)((m_nParaInfo >> 2) & 0x3fff);}
	int GetLengthFlag(){ return (int)(m_nParaInfo & 0x3);}
	int GetDataLen()   {return ((m_nDataLen == 0) ? 4:m_nDataLen);}
	void SetParaInfo(int nSensorType,int nLengthFlag){m_nParaInfo = (unsigned short)((nSensorType << 2) + nLengthFlag);}
}SensorParaData;

typedef struct _sensor_pkg_base_
{
	BYTE *m_pPkgBuf;	//�������Ļ��棬���Ƿְ�����ʱΪNULL
	int m_nPkgBufLen;	//�������ĳ���
	UINT m_nType;   //0-topic;1-info

	_sensor_pkg_base_()
	{
		m_pPkgBuf = NULL;
		m_nPkgBufLen = 0;
		m_nType = -1;
	}

}_SENSOR_PKG_BASE_;

//����Ժ�Ĵ�������������ֱ����ҵ�����ݵ�����ֵ������Ҫ��������������Э�顣ͨ�����������ҽ�������
typedef struct _sensor_pkg_topic_ : public _SENSOR_PKG_BASE_
{
	//������/v1/09988a010000339/service/data��Array������������""��"v1"��"09988a010000339"��"service"��"data"
	CStringArray m_arraySubTopic;  //�������ⶨ������������������Ŷ�Ӧ�������������������

	_sensor_pkg_topic_()
	{
		m_nType = 0;
	}

}_SENSOR_PKG_TOPIC_;

//������ҵ���Ľṹ�壬�ο�������ҵ����Э���ĵ�
typedef struct _sensor_pkg_info_ : public _SENSOR_PKG_BASE_
{//m_nCtrlType,m_nRequestSetFlagֻ���ǿ��Ʊ��Ĳ���Ч
	__int64 m_n64SensorID;
	int m_nPkgType;
	int m_nCtrlType;
	int m_nRequestSetFlag;
	BYTE *m_pFragSDUBuf;	//��Ƭ�����������ܻ���
	long m_nFragSDUBufLen;	//��Ƭ�������ݲ��ֳ���
	vector<SensorParaData *> vec;	//�����б�

	_sensor_pkg_info_()
	{
		m_nType = 1;
		m_n64SensorID = 0;
		m_nPkgType = 0;
		m_nCtrlType = 0;
		m_nRequestSetFlag = 0;
		m_pFragSDUBuf = NULL;
		m_nFragSDUBufLen = 0;
		vec.clear();
	}
	SensorParaData *FindSensorParaData(int nParaType)
	{//���ݲ������Ͷ�λƥ�����
		SensorParaData *pFind = NULL;
		int nCnt = vec.size();
		for (int i=0; i<nCnt; i++)
		{
			if (vec[i]->GetSensorType() == nParaType)
			{
				pFind = vec[i];
				break;
			}	
		}

		return pFind;
	}
	bool IsQueryMonitorAck()
	{
		return (m_nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK)
			&& (m_nCtrlType == SENSOR_PKG_CTRLTYPE_MONITORQUERY);
	}
	bool IsTimestampCmdAck()
	{
		return (m_nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK)
			&& (m_nCtrlType == SENSOR_PKG_CTRLTYPE_TIMEQUERYSET);
	}
	bool IsSensorIDCmdAck()
	{
		return (m_nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK)
			&& (m_nCtrlType == SENSOR_PKG_CTRLTYPE_SENSORIDQUERYSET);
	}
	bool IsSensorResetAck()
	{
		return (m_nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK)
			&& (m_nCtrlType == SENSOR_PKG_CTRLTYPE_RESET);
	}
	~_sensor_pkg_info_()
	{
		for(vector<SensorParaData *>::iterator it=vec.begin(); it!=vec.end(); it++)
		{
			if (NULL != *it)
			{
				delete *it;
				*it = NULL;
			}
		}
		vec.clear();

		if(m_pPkgBuf != NULL)
		{
			delete m_pPkgBuf;
			m_pPkgBuf = NULL;
		}
		if(m_pFragSDUBuf != NULL)
		{
			delete m_pFragSDUBuf;
			m_pFragSDUBuf = NULL;
		}
	}
}SensorPkgInfo;

inline int GetAckPkgRslt(SensorPkgInfo &oPkgInfo)
{//0:�ɹ���1��ʧ�ܣ�2����ʱ
	if (!(oPkgInfo.m_nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK))
	{
		return 0;
	}

	int nRet = 0;
	long nCtrlType = oPkgInfo.m_nCtrlType;
	// #define SENSOR_PKG_CTRLTYPE_COMMQUERYSET			0x1
	// #define SENSOR_PKG_CTRLTYPE_MONITORQUERY			0x2
	// #define SENSOR_PKG_CTRLTYPE_WARNINGQUERYSET			0x3
	// #define SENSOR_PKG_CTRLTYPE_TIMEQUERYSET			0x4
	// #define SENSOR_PKG_CTRLTYPE_SENSORIDQUERYSET		0x5
	// #define SENSOR_PKG_CTRLTYPE_RESET					0x6
	// #define SENSOR_PKG_CTRLTYPE_REQUESTADJUSTTIME		0x7
	switch (nCtrlType)
	{
	case SENSOR_PKG_CTRLTYPE_MONITORQUERY:
	case SENSOR_PKG_CTRLTYPE_RESET:
		if ((BYTE)oPkgInfo.vec[0]->m_pBuff[0] != 0xFF)
		{
			nRet = 1;
		}
		break;
	}

	return nRet;
}

//��Ƭͷ��Ϣ
typedef struct _sensor_frag_head_
{
	int m_nFlag;   //��Ƭ��־��ռǰ2�����ء�00-û�з�Ƭ��01-��һ����Ƭ��10-�������з�Ƭ��11-���һ����Ƭ
	int m_nSDUSeq;  //SDU����ţ���1��ʼ������ȡֵ��
	int m_nPriority;  //PDU�����ȼ���0-�ͣ�1-�ߣ�
	int m_nPDUSeq;   //PDU�����
	int m_nSize;   //�������ݣ���Ƭ���ĳ��ȣ��ֽ���
	BOOL IsFirstFrag(){return (m_nFlag == 0x1);}
	BOOL IsMidFrag(){return (m_nFlag == 0x2);}
	BOOL IsEndFrag(){return (m_nFlag == 0x3);}
}SensorFragHead;

inline bool IsPacketMonitorType(int nPkgType)
{
	return ((nPkgType == SENSOR_PKG_TYPE_MONITOR) 
		|| (nPkgType == SENSOR_PKG_TYPE_WARNING));
}

inline bool IsPacketCtrlType(int nPkgType)
{
	return ((nPkgType == SENSOR_PKG_TYPE_CONTROL) 
			|| (nPkgType == SENSOR_PKG_TYPE_CONTROL_ACK));
}

inline __int64 sensor_pkg_get_sensorid(BYTE *pPkg)
{
	__int64 n64SensorID = 0;
	n64SensorID =  (__int64)pPkg[0] << 40;
	n64SensorID += (__int64)pPkg[1] << 32;
	n64SensorID += (__int64)pPkg[2] << 24;
	n64SensorID += (__int64)pPkg[3] << 16;
	n64SensorID += (__int64)pPkg[4] << 8;
	n64SensorID += (__int64)pPkg[5];
	return n64SensorID;
}

inline CString sensor_pkg_get_sensorid_ex(BYTE *pPkg)
{
	CString strSensorID;
	CString strTemp1,strTemp2;
	__int64 n64SensorID = sensor_pkg_get_sensorid(pPkg);
	strTemp1.Format(_T("%06X"),n64SensorID & 0xffffff);
	long nLen = strTemp1.GetLength();
	strTemp2.Format(_T("%06X"),(n64SensorID>>24) & 0xffffff);

	strSensorID = strTemp2 + strTemp1;
	return strSensorID;
}

//������ID 6���ֽ�
inline void sensor_pkg_set_sensorid(BYTE *pPkg,__int64 n64SensorID)
{
	pPkg[0] = (n64SensorID >> 40) & 0xff;
	pPkg[1] = (n64SensorID >> 32) & 0xff;
	pPkg[2] = (n64SensorID >> 24) & 0xff;
	pPkg[3] = (n64SensorID >> 16) & 0xff;
	pPkg[4] = (n64SensorID >> 8) & 0xff;
	pPkg[5] = n64SensorID & 0xff;
}

//������ID��ǰ6���ֽ�
//��7���ֽڣ�ǰ4������Ϊ������������5������Ϊ��Ƭ��ʶ������������Ϊ��������
inline void sensor_pkg_get_info(BYTE *pPkg,int &nParaCnt,int &nFragInd,int &nPkgType)
{
	nParaCnt =  (pPkg[SENSOR_PKG_INDEX_INFO] >> 4) & 0xf;
	nFragInd =  (pPkg[SENSOR_PKG_INDEX_INFO] >> 3) & 0x1;
	nPkgType =  pPkg[SENSOR_PKG_INDEX_INFO] & 0x7;
}

inline void sensor_pkg_set_info(BYTE *pPkg,int nParaCnt,int nFragInd,int nPkgType)
{
	pPkg[SENSOR_PKG_INDEX_INFO] = ((nParaCnt << 4) & 0xf0)
									+ ((nFragInd << 3) & 0x80)
									+ (nPkgType & 0x7);
}

inline void sensor_pkg_get_ctrlinfo(BYTE *pPkg,int &nCtrlType,int &nRequestSetFlag)
{

	nCtrlType =  (pPkg[SENSOR_PKG_INDEX_CTRLINFO] >> 1) & 0x7f;
	nRequestSetFlag =  pPkg[SENSOR_PKG_INDEX_CTRLINFO] & 0x1;
}

inline void sensor_pkg_set_ctrlinfo(BYTE *pPkg,int nCtrlType,int nRequestSetFlag)
{
	pPkg[SENSOR_PKG_INDEX_CTRLINFO] = ((nCtrlType << 1) & 0xfe) + (nRequestSetFlag & 0x1);
}

// inline long sensor_pkt_get_paraData(BYTE *pPkg,long nOffset,SensorParaData *pParaData)
// {
// 	pParaData->m_nParaInfo = (pPkg[nOffset] << 8) + pPkg[nOffset+1];
// 
// 	nOffset += 2;
// 	pParaData->m_nDataLen = 0;
// 
// 	int nLengthFlag = pParaData->GetLengthFlag();
// 	for(int i=0; i<nLengthFlag; i++)
// 	{
// 		pParaData->m_nDataLen += pPkg[nOffset+i] << (8*i);
// 	}
// 	nOffset += nLengthFlag;
// 
// 
// 	pParaData->m_pBuff = pPkg + nOffset;
// 	if (pParaData->m_nDataLen == 0)
// 	{
// 		nOffset += 4;
// 	}
// 	else
// 	{
// 		nOffset += pParaData->m_nDataLen;
// 	}
// 	return nOffset;
// }

// inline long sensor_pkt_get_paraDatas(BYTE *pPkgData,int nParaCnt,vector<SensorParaData *> &vec)
// {
// 	long nReadPos = 0;
// 
// 	for (int i=0; i<nParaCnt; i++)
// 	{
// 		SensorParaData *pData = new SensorParaData;
// 		nReadPos = sensor_pkt_get_paraData(pPkgData,nReadPos,pData);
// 		vec.push_back(pData);
// 	}
// 
// 	return nReadPos;
// }

//��Ƭͷռ4���ֽ�
inline void sensor_pkg_get_fraghead(BYTE *pPkgData,SensorFragHead &oFragHead)
{
	oFragHead.m_nFlag = (pPkgData[0] >> 6) & 0x3;  
	oFragHead.m_nSDUSeq = pPkgData[0]  & 0x3f;
	oFragHead.m_nPriority = (pPkgData[1] >> 7) & 0x1;
	oFragHead.m_nPDUSeq = pPkgData[1]  & 0x7f;
	oFragHead.m_nSize = pPkgData[2] + (pPkgData[3] << 8);
}

inline void sensor_pkg_set_fraghead(BYTE *pPkgData,SensorFragHead &oFragHead)
{
	pPkgData[0] = ((oFragHead.m_nFlag << 6) & 0xC0) + (oFragHead.m_nSDUSeq & 0x3f);
	pPkgData[1] = ((oFragHead.m_nPriority << 7) & 0x80) + (oFragHead.m_nPDUSeq & 0x7f);
	pPkgData[2] = oFragHead.m_nSize & 0xff;
	pPkgData[3] = (oFragHead.m_nSize >> 8) & 0xff;
}

inline int sensor_pkt_get_intVal(SensorParaData *pParaData)
{
	int nDataLen = pParaData->GetDataLen();

	int nRet = 0;
	for (int i=0; i<nDataLen; i++)
	{
		nRet += pParaData->m_pBuff[i] << (i*8);
	}

	return nRet;
}

inline __int64 sensor_pkt_get_int64Val(SensorParaData *pParaData)
{
	int nDataLen = pParaData->GetDataLen();

	__int64 nRet = 0;
	for (int i=0; i<nDataLen; i++)
	{
		nRet += pParaData->m_pBuff[i] << (i*8);
	}

	return nRet;
}

inline float sensor_pkt_get_floatVal(SensorParaData *pParaData)
{
	float fVal = 0;
	Byte_to_Float(&fVal,pParaData->m_pBuff);
	return fVal;
}

inline double sensor_pkt_get_doubleVal(SensorParaData *pParaData)
{
	double fVal = 0;
	Byte_to_Double(&fVal,pParaData->m_pBuff);
	return fVal;
}

inline long sensor_pkt_set_intVal(BYTE *pPkg,long nOffset,int nData,int nDataLen=0)
{
	int nTempLen = nDataLen;
	if (nTempLen == 0)
	{
		nTempLen = 4;
	}

	for (int i=0; i<nTempLen; i++)
	{
		pPkg[nOffset+i] = (BYTE)((nData>>(8*i)) & 0xff);
	}

	return (nOffset + nTempLen);
}

inline long sensor_pkt_set_int64Val(BYTE *pPkg,long nOffset,__int64 nData,int nDataLen)
{
	int nTempLen = nDataLen;
	if (nTempLen > 8)
	{
		nTempLen = 8;
	}

	for (int i=0; i<nTempLen; i++)
	{
		pPkg[nOffset+i] = (BYTE)((nData>>(8*i)) & 0xff);
	}

	return (nOffset + nTempLen);
}

inline bool sensor_pkg_write_file(const CString &strFile,SensorParaData *pParaData)
{
	int nDataLen = pParaData->GetDataLen();

#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	FILE *pfile = fopen(pszFile, "w+b");
	delete pszFile;
#else
	FILE *pfile = fopen(strFile, "w+b");
#endif

	if (pfile != NULL)
	{
		fwrite(&nDataLen,sizeof(int),1,pfile);
		fwrite(pParaData->m_pBuff,1,nDataLen, pfile);
		fclose(pfile);
		return true;
	}

	return false;
}