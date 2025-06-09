#pragma once

#include "../ProtocolBase/PxProtoDeviceBase.h"
#include "IotEdgeProtoServerBase.h"

#define ENGINE_TO_PX_EDGEV4	_T("EDGEV4")
#define ENGINE_TO_PX_EDGEV5	_T("EDGEV5")

#define CLASSID_EDGEPROTOCOLDEVICE  (CLASSID_LISTCLASS + 0X01000000)

class CEdgeProtoDevice: public CPxProtoDeviceBase
{//m_strID:DeviceID
public:
	CEdgeProtoDevice();
	virtual ~CEdgeProtoDevice();

	CString m_strDvmFile;
	CExBaseList m_listTopoDevice;
	CString m_strTopoID;//��ǰ���ԵĶ��豸
	CExBaseList m_listLib;//��ǰ�豸��Ч���ϱ��������ݼ�
	BOOL m_bIsOnline;//�豸�Ƿ��Ѿ�ͨ����֤
	long m_bIsTest;//�Ƿ��Ǳ�ѡ�в��Ե��豸
	CDataGroup* m_pLinkupReport;

	FILE* m_pReportFile; //��ű��ĵ��ļ�

public:
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	//��ʼ��Э�����ģ��
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	
	//��������ҵ�����߼�
	void ProcessPkg(char *pBuf,long nLen);

	virtual UINT GetClassID()	{	return CLASSID_EDGEPROTOCOLDEVICE;	}

	
};
