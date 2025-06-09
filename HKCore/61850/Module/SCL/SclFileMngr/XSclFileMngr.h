//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XSclFileMngr.h  CXSclFileMngr

#pragma once

#include "SclFileMngrGlobal.h"


#include "XSclFileObj.h"

#define XSCL_FILE_MAX_MNGR_NUM          10000  //������������֧�ֵĵ����SCD�ļ�������

class CXSclFileMngr : public CExBaseList
{
public:
	CXSclFileMngr();
	virtual ~CXSclFileMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CXSCLFILEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSclFileMngrXmlRWKeys::CXSclFileMngrKey();     }
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
	BOOL m_bHasOpenCfgFile;//��¼�Ƿ��Ѵ򿪴������ļ�

//���Ա������ʷ���
public:
	BOOL OpenSclFileMngrCfg(const CString &strPath = _T(""));
	BOOL SaveSclFileMngrCfg(const CString &strPath = _T(""));
	BOOL ValidSetSelectState(CXSclFileObj *pXSclFileObj);
	void ClearAll_WithFolderFiles();
	CString GetCurrSelSsclFilePah();
	CString GetCurrSelTscdFilePah();
	CString GenerateSclFileObjID();//������ǰ����CXSclFileObj�Ӷ���,��1��ʼ���,���ɶ�Ӧ��ID
	void DelecteAll_UnExistTscd();//ɾ��tscd�����ڵĲ��Լ�¼
	void DelecteAll_RepeatScdTscd();//ɾ��scd·����tscd�ظ��Ĳ��Լ�¼
};

extern CXSclFileMngr g_oXSclFileMngr;

