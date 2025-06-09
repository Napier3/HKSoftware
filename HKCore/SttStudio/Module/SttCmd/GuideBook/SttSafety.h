//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSafety.h  CSttSafety

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

#include "SttCommCmd.h"

class CSttSafety : public CSttItemBase
{
public:
	CSttSafety();
	virtual ~CSttSafety();


	CString  m_strType;
	CString  m_strSoundFile;
	long  m_nManyDeviceTestMode;
//���غ���
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTSAFETY;   }
	virtual BSTR GetXmlElementKey();//  {      return CSttCmdDefineXmlRWKeys::CSttSafetyKey();     }
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
	CShortDatas*  m_pDatas;
	CShortDatas* GetDatas();
	void GetMsgs(CExBaseList *pListMsgs);
	void GetMsgs(CString &strMsgs);
	void AddNewMsg(const CString &strMsg);
	void UpdateMsgs(const CString &strMsg);
	void DeleteAllMsgs();

//���Ա������ʷ���
public:
};

