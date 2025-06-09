#pragma once
#include "../../../../../Module/API/StringApi.h"

class CInternationalCharactInterface
{
public:
	CInternationalCharactInterface(void);
	virtual ~CInternationalCharactInterface(void);

	//��Ӿ��뱣�������������Ӧ���Ե�,����1���ݵ�ǰ������·��,����2��3��Ӧ����ֵ���翹ֵ������4��Ӧ�������ͣ�����5��Ӧ���� ����6��Ӧ��ǰ���Ե�״̬
	virtual void AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);

	virtual void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);

	//��Ӿ������������������Ӧ���Ե�, ����1���ݵ�ǰ������·��, ����2��3��Ӧ��ʼ�����ֵ���翹ֵ������4��5��Ӧ��ֵ�����翹ֵ������6��Ӧ�������ͣ�����7��Ӧ����
	virtual void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);

	// ɾ�����Ե� / ��
	virtual void DeleteTestData(const CString &strIDPath);
	//ͬ�ڸ�������ѹ�����Ƶ�����,�������߽�����ʾ
	virtual void UpdateTestCharParas_Syn(double dDFzd, double dDVzd);
	//����ָ����������,���ڲ��Թ��ܶ�Ӧ�����������ߵ����,�������ƶ�\г���ƶ�
	virtual void UpdateCharacteristic(const CString &strCharID);
	//add wangtao 20240924��Ĳ�������ӵ���������ͼ
	virtual void AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240924��Ĳ��Ե���ӵ���������ͼ
//	virtual void AddUpdateTestPoint_Diff(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);
	virtual void UpdateCharacterisByFaultType(int nFaultType);//20241012 luozibing δ��Ӳ��Ե�ʱ���½�����ʾ���߹�������

public slots:
    virtual void slot_UpdateDrawCharacters();   //20241015 wanmj

};