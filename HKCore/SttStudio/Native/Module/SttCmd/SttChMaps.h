//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttChMaps.h  CSttChMaps

#pragma once

#include "SttCmdDefineGlobal.h"


#include "SttChMap.h"

class CSttChMaps : public CExBaseList
{
public:
	CSttChMaps();
	virtual ~CSttChMaps();


//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCHMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttChMapsKey();     }
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
	CSttChMap* FindByHdCh(long nType, const CString &strChID);
	CSttChMap* FindByHdCh(const CString &strType, const CString &strChID);
	CSttChMap* FindByHdCh(const CString &strType, const CString &strChID,float &fHdChCoef);//�������ڻ�ȡӲ��ͨ��ϵ��

	CSttChMap* GetChMap(const CString &strSoftRsID);//������ͨ��
	CSttChMap* AddChMap(const CString &strSoftRsName,const CString &strSoftRsID);

	CSttChMap* AddChMap_FindByID(const CString &strSoftRsName,const CString &strSoftRsID);//zhouhj 20211110 ������������Դ,�ȸ���ID����,������ҵ�

	void SetChCountU(long nChNum);
	void SetChCountI(long nChNum);

	BOOL OpenChMapsFile(const CString &strChMapsPath);
	BOOL SaveChMapsFile(const CString &strChMapsPath);
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//�ж��Ƿ����ģ�����������ģ��,Index��1��ʼ���  zhouhj20211005

	void SortByRsIndex();//����RsIndex��������ͨ��������������
	BOOL HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek);//���ݵ�ǰѡ���������ͣ��жϸ�ͨ���Ƿ�Ӧ�ô��������Դ
	BOOL GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur);

	//2022-9-19  lijunqing
	BOOL SetChMapsString(const CString &strChMaps);
	long GetChNum(const CString &strChID);//��ȡ��ѹ�����ͨ��������
	void UpdateWeekRateValue();//���ź�һ��ֵ�����ֵ�޸ĺ�,���������ϵ��(��ҳ�����´���)

	//2024-5-6 wangtao
    void UpdateAliasByName();//���±�����ʹ����Name����һ��
};

