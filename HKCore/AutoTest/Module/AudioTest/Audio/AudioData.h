//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AudioData.h  CAudioData

#pragma once

#include "VoiceWordGlobal.h"



class CAudioData : public CExBaseList
{
public:
	CAudioData();
	virtual ~CAudioData();

	CString  m_strData_Type;
	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return VWCLASSID_CAUDIODATA;   }
	virtual BSTR GetXmlElementKey()  {      return CVoiceWordXmlRWKeys::CAudioDataKey();     }
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
	//���ܴ���  
	int m_nFunctionFlag;
	//��ǰ���� ������ 1 �û� 2 ��������  Ĭ��ֵ -1
	int m_nPersonFlag;
	//��ǰ����         Ĭ��ֵ -1
	int m_nCurrentStep;
	//��ǰ������    Ĭ��ֵ -1
	int m_nStepFlag;
	//��ȷ����Ϣ���ش� 1 ȷ�� 0 ��  Ĭ��ֵ  -1
	int m_nConfirmFlag;
	//��ǰ������Ϣ
	CString m_strResultMess;
	//��ǰȷ�ϺõĲ���  û��ȷ��Ϊ��  ""
	CString m_strParaValue;

};

