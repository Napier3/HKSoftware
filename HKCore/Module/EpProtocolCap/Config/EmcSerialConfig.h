//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EmcSerialConfig.h  CEmcSerialConfig

#pragma once

#include "MonitorCapConfigGlobal.h"



class CEmcSerialConfig : public CExBaseObject
{
public:
	CEmcSerialConfig();
	virtual ~CEmcSerialConfig();


	long  m_nPort;
	long  m_nBaudRate;
	long  m_nByteSize;
	long  m_nStopBits;
	long  m_nParity;
	CString  m_strProtocol;
	long m_nDir; //����0=���ӷ���1=���Ʒ���

//���غ���
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCSERIALCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcSerialConfigKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

