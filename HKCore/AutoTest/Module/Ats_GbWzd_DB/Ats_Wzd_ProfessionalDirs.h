//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_ProfessionalDirs.h  CAts_Wzd_ProfessionalDirs

#pragma once

#include "AtsGbWizrdGlobal.h"


#include "Ats_Wzd_ProfessionalDir.h"

class CAts_Wzd_ProfessionalDirs : public CExBaseList
{
public:
	CAts_Wzd_ProfessionalDirs();
	virtual ~CAts_Wzd_ProfessionalDirs();


//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIRS;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_ProfessionalDirsKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_ProfessionalDirKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_ProfessionalDirKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

