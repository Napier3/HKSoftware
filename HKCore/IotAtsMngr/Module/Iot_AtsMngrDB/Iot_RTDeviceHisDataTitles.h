//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_RTDeviceHisDataTitless.h  CIot_RTDeviceHisDataTitless

#pragma once

#include "Iot_AtsMngrGlobal.h"


#include "Iot_RTDeviceHisDataTitle.h"

class CIot_RTDeviceHisDataTitles : public CExBaseList
{
public:
	CIot_RTDeviceHisDataTitles();
	virtual ~CIot_RTDeviceHisDataTitles();


//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDEVICEHISDATATITLES;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitlesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitleKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataTitleKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL QueryRTDeviceHisDataTitlesByDeviceType(CXDbBaseLib *pXDbLib,long nIndex_DeviceType);
	BOOL InsertRtDeviceHisData(CXDbBaseLib *pXDbLib, const CString &strDeviceSN, CExBaseList *pParas);
};

