//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttChMap.h  CSttChMap

#pragma once

#include "SttCmdDefineGlobal.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"


#include "SttHdChs.h"

#define MACROTYPE_Empty    0	//��
#define MACROTYPE_Analog   1	//ģ��
#define MACROTYPE_Digital  2	//����
#define MACROTYPE_Week     3	//С�ź�	
#define MACROTYPE_Mix      4	//���--С�ź�&����&ģ��


class CSttChMap : public CExBaseList
{
public:
	CSttChMap();
	virtual ~CSttChMap();


	CString  m_strAlias;

	//2021-5-1  lijunqing  Ϊ��ͨ��ӳ��ķ����ԣ����������Դ�ı��
	long m_nRsIndex;  
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCHMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttChMapKey();     }
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
	long GetRsIndexFromID();//zhouhj ��ID�л�ȡ��Դ���
	BOOL HasHdCh(const CString &strType, const CString &strChID);
	BOOL HasHdCh();
	CSttHdCh* FindHdCh(const CString &strType, const CString &strChID);//zhouhj ���Ҷ�Ӧ��Ӳ��ͨ��

	BOOL IsVoltageCh();
	BOOL IsCurrentCh();
	BOOL HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek);//���ݵ�ǰѡ���������ͣ��жϸ�ͨ���Ƿ�Ӧ�ô��������Դ
	BOOL HasMapHdResource(const CString &strHdChsID);
	BOOL HasMapHdResource(const char* cHdChsID);//sf 20211122 ����Unicode
	CSttHdCh* AddHdMapCh(const CString &strHdChsID,const CString &strHdRsName,const CString &strHdRsID);
	CString GetHdChsString(const CString &strHdChsID);//zhouhj ͨ��ӳ�������ʾ��ģ��������������ƴ�Ӻ���ַ���
	void InitHdChs_ByString(CString &strHdChsString,const CString &strHdChsID);//����1ΪӲ��ͨ���ַ���,��:"U1_1;U1_2;U1_3;",����2ΪӲ�����ͱ�ʶ
	CSttHdChs* GetHdChs(const CString &strHdChsID);
	CSttHdChs* GetHdChs(const char* cHdChsID);//sf 20211122 ����Unicode
	void SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue);//zhouhj 20210716 �������źű��һ��ֵ���߶���ֵ,����2Ϊ��ֵ�Ƿ�Ϊһ��ֵ
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//�ж��Ƿ����ģ�����������ģ��,Index��1��ʼ���  zhouhj20211005
	BOOL GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur);
	void UpdateWeekRateValue();
 	long GetMapChsType();//2023-11-13 suyang ��������ͨ��������ģ�� ���� ���ź� ��� ��  
};

long Global_GetCurrChType_Single(long nMixChType,long nHasAnalog,long nHasDigtal,long nWeek);//2023-11-28 suyang ��ȡ����ǰͨ��������
