#include "StdAfx.h"

#include "Ep101Frame_Group_68.h"

//////////////////////////////////////////////////////////////////////////
//
CEp101Frame_Group_68::CEp101Frame_Group_68(void)
{
	AddFrameAsdu(new CEp101Frame_68_Asdu01(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu0D(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu1E(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu24(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu2E(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu30(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu64(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	AddFrameAsdu(new CEp101Frame_68_Asdu67(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
	
	//空报文
	AddFrameAsdu(new CEp101Frame_68_Asdu00(new CEp101Frame_68_Head(), new CEp101Frame_68_Tail()));
}

CEp101Frame_Group_68::~CEp101Frame_Group_68(void)
{

}


DWORD CEp101Frame_Group_68::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	return 1;
}

CEpFrameBase* CEp101Frame_Group_68::Match(PEPBUFFERPOS pBufferPos)
{
	if (Ep_EpBufferLeave(pBufferPos) < 1)
	{
		return NULL;
	}

	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);

	if (Ep_EpBufferLeave(pBufferPos) < 9)
	{
		if (*pRcvBuffer == 0x68)
		{
			Ep_SetMatchStateNotFull(pBufferPos);
		}

		return NULL;
	}


	if (*pRcvBuffer != 0x68 && *(pRcvBuffer+EP_101_FRAME_68_POS_START2) != 0x68)
	{
		return NULL;
	}

	//长度L包括控制域、地址域、用户数据区的字节数
	//启动字符（68H） + 长度（L）+ 长度重复（L） + 启动字符（68H）+  帧校验和（CS） + 结束字符（16H）
	//共六个字符，如果长度小于最小的有效长度，表示长度不够，则返回NULL
	long n1 = Ep_EpBufferLeave(pBufferPos);
	long n2 = *(pRcvBuffer+EP_101_FRAME_68_POS_LENGTH1) + 6;
	if (n1 < n2)
	{
		Ep_SetMatchStateNotFull(pBufferPos);
		return NULL;
	}

	Ep_OffsetEpBufferCurr(pBufferPos, 6);

	//遍历组的各报文帧，匹配
	return CEpFrameGroup::Match(pBufferPos);
}

DWORD CEp101Frame_Group_68::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0xE5;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

