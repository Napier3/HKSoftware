//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
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

//私有成员变量
private:
	

//私有成员变量访问方法
public:
	CPpCfgDevice* FindpPpCfgDevice(CExBaseObject *pDataRef);
	void InitAllCmdCfgChannels();

	void SaveCfgDevicesFile(const CString &strFile);
	void OpenCfgDevicesFile(const CString &strFile);
};

