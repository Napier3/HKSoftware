//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSystemConfig.h  CSttSystemConfig

#pragma once

#include "SttSystemConfigGlobal.h"


#include "SttDevConfig.h"
#include "SttModuleUse.h"

class CSttSystemConfig : public CExBaseList
{
public:
	CSttSystemConfig();
	virtual ~CSttSystemConfig();


	float  m_fOpenDelayTime;
	CString  m_strCompanyName;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTSYSTEMCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttSystemConfigXmlRWKeys::CSttSystemConfigKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL OpenSystemConfig(const CString &strPath = _T(""));
	BOOL SaveSystemConfig(const CString &strPath = _T(""));

	CSttDevConfig* GetSttDevConfig();
	CString GetDevModel();
	void SetCurDevModel(const CString &strModel);
	BOOL IsDoubleClickEdit();
	long UseSclView();
	long GetLogPrintValue();
	long IsFt3PrimCodeValue();//chenling 20240416
	long GetLockMaps();//wangtao 20240507 �������ӳ���Get��Set
    void SetLockMaps(const long &nLockMaps);
	long GetSelSysPata();
	long GetHasFT3();
};

extern CSttSystemConfig g_oSttSystemConfig;

