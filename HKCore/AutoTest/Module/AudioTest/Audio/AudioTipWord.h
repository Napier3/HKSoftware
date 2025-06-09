//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AudioTipWord.h  CAudioTipWord

#pragma once

#include "VoiceWordGlobal.h"

#include "AudioData.h"

#include "AudioReplyKeyWord.h"

class CAudioTipWord : public CAudioData
{
public:
	CAudioTipWord();
	virtual ~CAudioTipWord();


	//CString  m_strValue;
	CString  m_strTip_Word_Id;
	CString  m_strOrder_Word_Id;
//���غ���
public:
	virtual UINT GetClassID() {    return VWCLASSID_CAUDIOTIPWORD;   }
	virtual BSTR GetXmlElementKey()  {      return CVoiceWordXmlRWKeys::CAudioTipWordKey();     }
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

