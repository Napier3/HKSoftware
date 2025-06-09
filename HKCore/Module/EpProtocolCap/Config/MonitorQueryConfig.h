//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MonitorCapConfig.h  CMonitorQueryConfig

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EmcSerialsConfig.h"
#include "EmcNetsConfig.h"
#include "EmcNetDevices.h"
#include "EmcQueryProtocols.h"
#include "EmcDeviceModelFiles.h"
#include "EpCapYcAnalysisMngr.h"

class CMonitorQueryConfig : public CExBaseList
{
public:
	CMonitorQueryConfig();
	virtual ~CMonitorQueryConfig();

	CString m_strFile;
// 	CEmcSerialsConfig *m_pEmcSerialsConfig;
	CEmcNetsConfig *m_pEmcNetsConfig;
// 	CEmcNetDevices *m_pEmcNetDevices;
	CEmcQueryProtocols *m_pQueryProtocols;
	CEmcDeviceModelFiles *m_pEmcDeviceModelFiles;
	CEpCapYcAnalysisMngr *m_pEpCapYcAnalysisMngr;

	long m_nUseGenerator;

	//���غ���
public:
	virtual UINT GetClassID() {    return ECCLASSID_CMONITORQUERYCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CMonitorCapConfigKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
	void InitConfig();
	void SaveConfig();
};

