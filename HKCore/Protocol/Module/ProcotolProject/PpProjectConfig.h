//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpProjectConfig.h  CPpProjectConfig

#pragma once

#include "ClassProcotolProjectGlobal.h"


#include "PpCfgDevices.h"
#include "PpCfgOptrsMngr.h"

class CPpProjectConfig : public CExBaseList
{
public:
	CPpProjectConfig();
	virtual ~CPpProjectConfig();

	BOOL m_bCreated;
//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPPROJECTCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpProjectConfigKey();     }
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
	CPpCfgDevices *m_pPpCfgDevices;
	CPpCfgOptrsMngr *m_pPpCfgOptrsMngr;
	CString m_strPpCfgFilePath;
	
//˽�г�Ա�������ʷ���
public:
	CPpCfgDevices* GetPpCfgDevices();
	CPpCfgOptrsMngr* GetPpCfgOptrsMngr();
	CString GetPpCfgFilePath()	{	return m_strPpCfgFilePath;	}
	
	void NewPpProjectConfig();
	BOOL OpenProjectDB(const CString &strFile);
	BOOL SaveProjectDB(const CString &strFile=_T(""));
	BOOL Save();
	BOOL IsCreated()	{	return m_bCreated;	}
	void ProjectUnload();
};

