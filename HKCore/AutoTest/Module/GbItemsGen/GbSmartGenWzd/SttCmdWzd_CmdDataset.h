#pragma once

#include "GbSmartGenWzdGlobal.h"

class CSttCmdWzd_CmdDataset : public CExBaseObject
{
public:
	CSttCmdWzd_CmdDataset(void);
	virtual ~CSttCmdWzd_CmdDataset(void);

	CDataGroup *m_pCmdGrpRef;
	long m_nSelect;   //�Ƿ�ѡ��������read��registerָ��

	//�������ԣ�ֻ������registerָ��
	long m_nChange;   //������ָ��Ƿ�仯����
	long m_nQuqlity;  //������ָ��Ƿ�Ʒ������
	long m_nPeriod;   //������ָ��Ƿ���������
	long m_nPeriod_Time; //������ָ��������͵����ڣ���λms
};

//�ʼ����ƣ�����д���һ�����ݼ���һ�����衣���ڶ�������е����ݼ�Ϊһ������
class CSttCmdWzd_Step :	public CExBaseList
{
public:
	CSttCmdWzd_Step(void);
	virtual ~CSttCmdWzd_Step(void);

	/*  ����дָ��
		�ڵ����һ��ʱ�����ݲ����Ƿ��޸ģ�value��default-value�Ƚϣ�����ɾ��m_pCmdGrpRef��δ�޸ĵĲ�����
		���������һ����ʱ����Ҫͨ��m_pCmdGrpBk����ԭ��ɾ���Ĳ������Ա������޸�
	*/
	CDataGroup *m_pCmdGrpRef;
	CDataGroup *m_pCmdGrpBk;  //���ݵĲ�����Ϣ
	long m_nZoneIndex;  //��ֵ����
	CString m_strDelayBft;  //ͨѶǰ��ʱ
	CString m_strDelayAft;  //ͨѶ����ʱ

	CString m_strType; //�������ͣ�_AfterTest_   _BeforeTest_

	//дָ��������һ����ʱ���ָ�����Ĳ���
	void RecoverCmdGrpRef();
};


