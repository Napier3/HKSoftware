//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpTimer.h  CIotPpTimer

#pragma once

#include "IOTPPGlobal.h"

class CIotPpNode;
class CDvmDataset;

class CIotPpTimer : public CExBaseList
{
public:
	CIotPpTimer();
	virtual ~CIotPpTimer();


	CString  m_strType;
	CString  m_strJump_To;
	CString  m_strTime;
	long	 m_nTimeLong;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPTIMER;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpTimerKey();     }
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
	CIotPpNode *m_pIotPpNode;

//˽�г�Ա�������ʷ���
public:
	CIotPpNode* GetIotPpNode()	{	return m_pIotPpNode;	}

	//timerʱ��ִ�д���
private:
	DWORD m_dwTimerBegin;
	BOOL m_bTimerBegin;

public:
	void BeginTimer(DWORD dwCurrTick);
	void ResetTimer(DWORD dwCurrTick);
	void KillTimer();
	BOOL IsTimerOut(DWORD dwCurrTick);

	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
};

BOOL IsStringNum(const CString &str);
