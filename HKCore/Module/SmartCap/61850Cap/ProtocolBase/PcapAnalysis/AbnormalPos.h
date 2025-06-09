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
	std::vector<int> m_AbnormalGlobalPos;//异常(丢包，错序，丢失同步信号)
	std::vector<int> m_AbnormalCurContentPos;//异常(丢包，错序，丢失同步信号)

	std::vector<int> m_LostPointGlobalPos;//丢包
	std::vector<int> m_LostPointCurContentPos;//丢包

	std::vector<int> m_SetpOutGlobalPos;//失步
	std::vector<int> m_SetpOutCurContentPos;//失步

	std::vector<int> m_ErrorNumGlobalPos;//错序
	std::vector<int> m_ErrorNumContentPos;//错序

	std::vector<int> m_LostSmSycGlobalPos;//丢失同步信号
	std::vector<int> m_LostSmSycContentPos;//丢失同步信号

	std::vector<int> m_SMVFactorChangeGlobalPos;//品质异常
	std::vector<int> m_SMVFactorChangeContentPos;//品质异常


	std::vector<int> m_SMVFlyPointGlobalPos;//飞点
	std::vector<int> m_SMVFlyPointContentPos;//飞点

/////////////////////////////////GOOSE////////////////////////////////////////////
	std::vector<int> m_GooseBitChangeGlobalPos;//变位
	std::vector<int> m_GooseBitChangeContentPos;//变位

	std::vector<int> m_GooseTimeDelayGlobalPos;//GOOSE 延时
	std::vector<int> m_GooseTimeDelayContentPos;//GOOSE 延时

	std::vector<int> m_GooseTimeLiveEqual0GlobalPos;//GOOSE 延时
	std::vector<int> m_GooseTimeLiveEqual0ContentPos;//GOOSE 延时

	std::vector<int> m_GooseBreakGlobalPos;//GOOSE 中断
	std::vector<int> m_GooseBreakContentPos;//GOOSE 中断

	std::vector<int> m_GooseBitChangeAndCountErrorGlobalPos;//变位
	std::vector<int> m_GooseBitChangeAndCountErrorContentPos;//变位

	std::vector<int> m_GooseVitrualBitChangeAndCountErrorGlobalPos;//虚变位
	std::vector<int> m_GooseVitrualBitChangeAndCountErrorContentPos;//虚变位


	std::vector<int> m_GooseBitChangeAndFirstValueErrorGlobalPos;//变位初值错误
	std::vector<int> m_GooseBitChangeAndFirstValueErrorContentPos;//变位初值错误

	std::vector<int> m_GooseLostSTNumGlobalPos;//STNum丢失
	std::vector<int> m_GooseLostSTNumContentPos;//STNum

	std::vector<int> m_GooseBitChangeLostSTNumGlobalPos;//变位/STNum丢失
	std::vector<int> m_GooseBitChangeLostSTNumContentPos;//变位/STNum

	std::vector<int> m_GooseSqNumRepeatGlobalPos;//SqNum重复
	std::vector<int> m_GooseSqNumRepeatContentPos;//SqNum重复

	std::vector<int> m_GooseLostSqNumGlobalPos;//SqNum丢失
	std::vector<int> m_GooseLostSqNumContentPos;//SqNum丢失

	std::vector<int> m_GooseClockUnSyncGlobalPos;//时钟未同步
	std::vector<int> m_GooseClockUnSyncContentPos;//时钟未同步

	std::vector<int> m_GooseClockErrorGlobalPos; //时钟故障
	std::vector<int> m_GooseClockErrorContentPos;//时钟故障

	std::vector<int> m_GooseClockAbnormalGlobalPos; //时钟异常
	std::vector<int> m_GooseClockAbnormalContentPos;//时钟异常
};
