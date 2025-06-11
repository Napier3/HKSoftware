//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttHdCh.h  CSttHdCh

#pragma once

#include "SttCmdDefineGlobal.h"


#include "../../../Module/DataMngr/DvmData.h"

//zhouhj 2023.8.3 �����������ź�ȱʡ���
#define STT_WEEK_USE_MODE_NORMAL                           0//��ͨ���ź�[120/7.07][30/7.07]
#define STT_WEEK_USE_MODE_DistriTerm                       1//����ն����ź�[1:1]


class CSttHdCh : public CExBaseList
{
public:
	CSttHdCh();
	virtual ~CSttHdCh();

	float m_fCoef;//20210602zhouhongjun Ӳ��ͨ��ϵ��,���ںϲ�������ѹͨ�����ʱʹ��


//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTHDCH;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttHdChKey();     }
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
	void SetTransRate_Weak(float fPrimValue,float fSecondValue);//zhouhj 20210714 �����������ͺű������
	float GetPrimaryValue_Float();
	float GetSecondaryValue_Float();
	CDvmData* GetPrimaryValue_DvmData();
	CDvmData* GetSecondaryValue_DvmData();
	void SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue);
	void UpdateWeekRateValue();
};


extern long g_nSttWeekUseMode;//zhouhj 2023.8.3 �����������źŵ�ȱʡ���