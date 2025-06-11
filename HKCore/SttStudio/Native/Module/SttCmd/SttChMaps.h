//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttChMaps.h  CSttChMaps

#pragma once

#include "SttCmdDefineGlobal.h"


#include "SttChMap.h"

#define MAPS_MAX_BINARYIN_COUNT		20
#define MAPS_MAX_BINARYOUT_COUNT		20
#define MAPS_MAX_ExBINARY_COUNT		256//�����չ����������,�����Դ����256in,256out,���8����չģ��

#define	MAPS_BINARY_TYPE_BIN		0
#define	MAPS_BINARY_TYPE_EXBIN		1
#define	MAPS_BINARY_TYPE_BOUT		2
#define	MAPS_BINARY_TYPE_EXBOUT		3

#define	MAPS_BINARY_ID_BIN			"Bin"
#define	MAPS_BINARY_ID_BINEX		"BinEx"
#define	MAPS_BINARY_ID_BOUT			"Bout"
#define	MAPS_BINARY_ID_BOUTEX		"BoutEx"


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
	//20240904 huangliang �ֱ��¼ģ���������롢����
	//QChar m_szBinDesc[MAPS_MAX_BINARYIN_COUNT][256];
	//QChar m_szBinExDesc[MAPS_MAX_ExBINARY_COUNT][256];
	//QChar m_szBoutDesc[MAPS_MAX_BINARYOUT_COUNT][256];
	//QChar m_szBoutExDesc[MAPS_MAX_ExBINARY_COUNT][256];
	CString m_szBinDesc[MAPS_MAX_BINARYIN_COUNT];
	CString m_szBinExDesc[MAPS_MAX_ExBINARY_COUNT];
	CString m_szBoutDesc[MAPS_MAX_BINARYOUT_COUNT];
	CString m_szBoutExDesc[MAPS_MAX_ExBINARY_COUNT];

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

	void SaveSyncChMapsFile(const CString &strChMapsPath);
	void Save4U3IChMapsFile(const CString &strChMapsPath);
	void Save6U6IChMapsFile(const CString &strChMapsPath);

	void SortByRsIndex();//����RsIndex��������ͨ��������������
	BOOL HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek);//���ݵ�ǰѡ���������ͣ��жϸ�ͨ���Ƿ�Ӧ�ô��������Դ
	BOOL HasMapHdResource(const CString &strHdChsID);
	BOOL GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur);

	//2022-9-19  lijunqing
	BOOL SetChMapsString(const CString &strChMaps);
	long GetChNum(const CString &strChID);//��ȡ��ѹ�����ͨ��������
	void UpdateWeekRateValue();//���ź�һ��ֵ�����ֵ�޸ĺ�,���������ϵ��(��ҳ�����´���)

	//2024-5-6 wangtao
    void UpdateAliasByName();//���±�����ʹ����Name����һ��

	//20240904 huangliang 
	void CreateDefaultBinBoutMaps();	//����Ĭ��ֵ
	void ClearBinBoutMaps();	//ɾ������������������
	CString GetBinBoutNameForIndex(int iBin, int nIndex);	//��ȡ���뿪��

	void CopyBinBout(CBaseObject* pDest);	//20240921 huangliang �������뿪��

	void CreateBinToList(CExBaseList *plistBin);
	void CreateBinExToList(CExBaseList *plistBin);
	void CreateBoutToList(CExBaseList *plistBout);
	void CreateBoutExToList(CExBaseList *plistBout);

	void ReadListToBin(CExBaseList *plistBin);
	void ReadListToBinEx(CExBaseList *plistBin);
	void ReadListToBout(CExBaseList *plistBout);
	void ReadListToBoutEx(CExBaseList *plistBout);
};

void Global_UpdateWeekRateValue(CExBaseList *pAnalogChMapList);
//zhouhj 2024.11.16 ɾ����ȫ�ֺ���,�ڶ�Ӧ����ʵ��
//BOOL Global_HasMapHdResource(CExBaseList *pAnalogChMapList,long nHasAnalog, long nHasDigital, long nHasWeek);//���ݵ�ǰѡ���������ͣ��жϸ�ͨ���Ƿ�Ӧ�ô��������Դ
BOOL Global_GetMaxValue_WeekRates(CExBaseList *pAnalogChMapList, double &dMaxVol, double &dMaxCur);
BOOL Global_HasAnalogCurrModuleHdCh(CExBaseList *pAnalogChMapList, long nModuleIndex);//�ж��Ƿ����ģ�����������ģ��,Index��1��ʼ���  zhouhj20211005
long Global_GetChNum(CExBaseList *pAnalogChMapList, const CString &strChID);//��ȡ��ѹ�����ͨ��������

