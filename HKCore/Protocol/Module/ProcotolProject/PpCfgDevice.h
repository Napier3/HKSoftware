//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgDevice.h  CPpCfgDevice

#pragma once

#include "ClassProcotolProjectGlobal.h"

#include "../Engine/DeviceModel/DeviceCmmConfig.h"



class CPpCfgDevice : public CExBaseList
{
public:
	CPpCfgDevice();
	virtual ~CPpCfgDevice();
	//����ͨѶ��
	CDeviceCmmConfig* m_pDeviceCmmConfig;
	CString  m_strTemplateFile;
	CString  m_strDdvmFile;
	CExBaseObject* m_pEngineDataRef;

	CExBaseList m_listCmmCfg;

//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void AddDeviceCmmConfig(CDeviceCmmConfig *pCmmConfig);
	void SelectCmmCfgChannel(CExBaseList &listCmmCfgChannel);
};

