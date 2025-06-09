//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgDevices.h  CPpCfgDevices

#pragma once

#include "ClassProcotolProjectGlobal.h"


#include "PpCfgDevice.h"

class CPpCfgDevices : public CExBaseList
{
public:
	CPpCfgDevices();
	virtual ~CPpCfgDevices();
	
	CExBaseList m_listCmmCfgChannel;
	CString m_strCfgDevicesFile;

//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGDEVICES;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgDevicesKey();     }
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
	CPpCfgDevice* FindpPpCfgDevice(CExBaseObject *pDataRef);
	void InitAllCmdCfgChannels();

	void SaveCfgDevicesFile(const CString &strFile);
	void OpenCfgDevicesFile(const CString &strFile);
};

