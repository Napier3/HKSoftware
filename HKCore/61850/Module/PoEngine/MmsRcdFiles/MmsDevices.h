//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MmsDevices.h  CMmsDevices

#pragma once

#include "MmsRcdFilesMngrGlobal.h"


#include "MmsDevice.h"

class CMmsDevices : public CExBaseList
{
public:
	CMmsDevices();
	virtual ~CMmsDevices();

	BOOL OpenMmsDevicesCfgFile();
	BOOL SaveMmsDevicesCfgFile();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CMMSDEVICES;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsRcdFilesMngrXmlRWKeys::CMmsDevicesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
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
};

