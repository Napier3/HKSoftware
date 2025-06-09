//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SensorPpConfig.h  CSensorPpConfig

#pragma once

#include "PpCfgGlobal.h"


#include "SensorPpDeviceType.h"

class CSensorPpConfig : public CExBaseList
{
public:
	CSensorPpConfig();
	virtual ~CSensorPpConfig();


//���غ���
public:
	virtual UINT GetClassID() {    return PPCFGCLASSID_CSENSORPPCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CPpCfgXmlRWKeys::CSensorPpConfigKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	void GetNeedSubcribeTopic(CExBaseList &oList);
	void GetWillPublicTopic(CDvmData &oList);
};

