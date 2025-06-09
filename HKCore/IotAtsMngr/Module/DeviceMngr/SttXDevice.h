//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttXDevice.h  CSttXDevice

#pragma once

#include "../../../Module/DataMngr/DataGroup.h"

#define WM_IOT_DEVICEMGR_ADD   (WM_USER+743)
#define WM_IOT_DEVICEMGR_DELETE   (WM_USER+744)
#define WM_IOT_DEVICEMGR_UPDATE   (WM_USER+745)

#define STTX_DEVICE_ATTRID_SN  _T("SN")
#define STTX_DEVICE_ATTRID_Model  _T("Model")
#define STTX_DEVICE_ATTRID_Type  _T("Type")
#define STTX_DEVICE_ATTRID_CategoryID  _T("CategoryID")

class CSttXDevice : public CDataGroup
{
public:
	CSttXDevice();
	virtual ~CSttXDevice();

	long m_nSelect;
	CString m_strSN;
	CString m_strModel;
	CString m_strType;
	CString m_strCategoryID;

//���غ���
public:
	virtual BOOL CopyOwn(CBaseObject* pDest);

	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CString GetSN();
	CString GetModel();
	CString GetType();
	CString GetCategoryID();

	void SetSN(const CString &strValue);
	void SetModel(const CString &strValue);
	void SetType(const CString &strValue);
	void SetCategoryID(const CString &strValue);

	void InitDevice();
};

