#pragma once
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttCmdWzd_CmdDataset :
	public CExBaseObject
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


class CSttCmdWzd_CmdDatasets :
	public CExBaseList
{
public:
	CSttCmdWzd_CmdDatasets(void);
	virtual ~CSttCmdWzd_CmdDatasets(void);

	CDataGroup *m_pCmdGrpRef;
	long m_nZoneIndex;  //��ֵ����
};