//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AudioFlowWord.h  CAudioFlowWord

#pragma once

#include "VoiceWordGlobal.h"

#include "AudioData.h"

#include "AudioWord.h"

class CAudioFlowWord : public CAudioData
{
public:
	CAudioFlowWord();
	virtual ~CAudioFlowWord();


	CString  m_strFlag;
	CString  m_strTip_Word_Id;
	CString  m_strOrder_Word_Id;
//���غ���
public:
	virtual UINT GetClassID() {    return VWCLASSID_CAUDIOFLOWWORD;   }
	virtual BSTR GetXmlElementKey()  {      return CVoiceWordXmlRWKeys::CAudioFlowWordKey();     }
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

//˽�г�Ա�������ʷ���
public:
};

