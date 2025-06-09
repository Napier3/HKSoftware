//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttLicenseMngr.h  CSttLicenseMngr

#pragma once


#include "SttLicense.h"
#include "../../../../Module/XfileMngrBase/XFileMngr.h"

class CSttLicenseMngr : public CExBaseList
{
public:
	CSttLicenseMngr();
	virtual ~CSttLicenseMngr();

    bool m_bModifyFlag;

//���غ���
public:
    virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTLICENSEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttLicenseMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
    CString GetLicenseMngrFile();
    CXFileMngr *m_pLicenseFiles;

//˽�г�Ա�������ʷ���
public:
    CXFileMngr* GetLicenseFiles();
    void OpenLicenseMngrFile();
    void SaveLicenseMngrFile();

    CSttLicense* AddLicenseFile(const CString &strFile);
    bool AddLicense(CSttLicense *pLicense, bool &bIsNew);
};

extern CSttLicenseMngr *g_pSttLicenseMngr;
void stt_license_init_LicenseMngr();
void stt_license_free_LicenseMngr();
CString stt_get_license_files_path();


