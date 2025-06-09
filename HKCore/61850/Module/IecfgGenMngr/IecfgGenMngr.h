//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecfgGenMngr.h  CIecfgGenMngr

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "DeviceType.h"

#define IECFG_GEN_MNGR_FILE_NAME_DEFAULT                  _T("iecfg-generate-mngr.xml")                  



class CIecfgGenMngr : public CExBaseList
{
public:
	CIecfgGenMngr();
	virtual ~CIecfgGenMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CIECFGGENMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecfgGenMngrKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CIecfgGenMngrKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIecfgGenMngrXmlRWKeys::CDeviceTypeKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL Generate(CIecCfgDevice *pIecfgDevice,const CString &strIedName);

//���Ա������ʷ���
public:
	BOOL OpenIecfgGenMnrFile(const CString &strIecfgGenMnrFile = NULL);
};

extern CIecfgGenMngr g_oIecfgGenMngr;