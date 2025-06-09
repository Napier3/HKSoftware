#pragma once
#include <vector>
class CAbnormalPos
{
public:
	CAbnormalPos(void);
public:
	~CAbnormalPos(void);
public:
	CString m_strMacDes;
	CString m_strMacSRC;
	CString m_strAPPID;
 	int          m_nAllNum;
	int          m_nGooseBitChangePos;
	CString GetInfor();
////////////////////////////////SMV////////////////////////////////////////////
	std::vector<int> m_AbnormalGlobalPos;//�쳣(���������򣬶�ʧͬ���ź�)
	std::vector<int> m_AbnormalCurContentPos;//�쳣(���������򣬶�ʧͬ���ź�)

	std::vector<int> m_LostPointGlobalPos;//����
	std::vector<int> m_LostPointCurContentPos;//����

	std::vector<int> m_SetpOutGlobalPos;//ʧ��
	std::vector<int> m_SetpOutCurContentPos;//ʧ��

	std::vector<int> m_ErrorNumGlobalPos;//����
	std::vector<int> m_ErrorNumContentPos;//����

	std::vector<int> m_LostSmSycGlobalPos;//��ʧͬ���ź�
	std::vector<int> m_LostSmSycContentPos;//��ʧͬ���ź�

	std::vector<int> m_SMVFactorChangeGlobalPos;//Ʒ���쳣
	std::vector<int> m_SMVFactorChangeContentPos;//Ʒ���쳣


	std::vector<int> m_SMVFlyPointGlobalPos;//�ɵ�
	std::vector<int> m_SMVFlyPointContentPos;//�ɵ�

/////////////////////////////////GOOSE////////////////////////////////////////////
	std::vector<int> m_GooseBitChangeGlobalPos;//��λ
	std::vector<int> m_GooseBitChangeContentPos;//��λ

	std::vector<int> m_GooseTimeDelayGlobalPos;//GOOSE ��ʱ
	std::vector<int> m_GooseTimeDelayContentPos;//GOOSE ��ʱ

	std::vector<int> m_GooseTimeLiveEqual0GlobalPos;//GOOSE ��ʱ
	std::vector<int> m_GooseTimeLiveEqual0ContentPos;//GOOSE ��ʱ

	std::vector<int> m_GooseBreakGlobalPos;//GOOSE �ж�
	std::vector<int> m_GooseBreakContentPos;//GOOSE �ж�

	std::vector<int> m_GooseBitChangeAndCountErrorGlobalPos;//��λ
	std::vector<int> m_GooseBitChangeAndCountErrorContentPos;//��λ

	std::vector<int> m_GooseVitrualBitChangeAndCountErrorGlobalPos;//���λ
	std::vector<int> m_GooseVitrualBitChangeAndCountErrorContentPos;//���λ


	std::vector<int> m_GooseBitChangeAndFirstValueErrorGlobalPos;//��λ��ֵ����
	std::vector<int> m_GooseBitChangeAndFirstValueErrorContentPos;//��λ��ֵ����

	std::vector<int> m_GooseLostSTNumGlobalPos;//STNum��ʧ
	std::vector<int> m_GooseLostSTNumContentPos;//STNum

	std::vector<int> m_GooseBitChangeLostSTNumGlobalPos;//��λ/STNum��ʧ
	std::vector<int> m_GooseBitChangeLostSTNumContentPos;//��λ/STNum

	std::vector<int> m_GooseSqNumRepeatGlobalPos;//SqNum�ظ�
	std::vector<int> m_GooseSqNumRepeatContentPos;//SqNum�ظ�

	std::vector<int> m_GooseLostSqNumGlobalPos;//SqNum��ʧ
	std::vector<int> m_GooseLostSqNumContentPos;//SqNum��ʧ

	std::vector<int> m_GooseClockUnSyncGlobalPos;//ʱ��δͬ��
	std::vector<int> m_GooseClockUnSyncContentPos;//ʱ��δͬ��

	std::vector<int> m_GooseClockErrorGlobalPos; //ʱ�ӹ���
	std::vector<int> m_GooseClockErrorContentPos;//ʱ�ӹ���

	std::vector<int> m_GooseClockAbnormalGlobalPos; //ʱ���쳣
	std::vector<int> m_GooseClockAbnormalContentPos;//ʱ���쳣
};
