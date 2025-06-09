//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//重载函数
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

//私有成员变量
private:
	CIotPpNode *m_pIotPpNode;

//私有成员变量访问方法
public:
	CIotPpNode* GetIotPpNode()	{	return m_pIotPpNode;	}

	//timer时钟执行代码
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
