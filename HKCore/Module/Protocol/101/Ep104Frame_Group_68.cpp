#include "StdAfx.h"

#include "Ep104Frame_Group_68.h"

//////////////////////////////////////////////////////////////////////////
//
CEp104Frame_Group_68::CEp104Frame_Group_68(void)
{
	AddFrameAsdu(new CEp101Frame_68_Asdu01(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu0D(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu1E(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu24(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu2E(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu30(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu64(new CEp104Frame_68_Head(), NULL));
	AddFrameAsdu(new CEp101Frame_68_Asdu67(new CEp104Frame_68_Head(), NULL));
}

CEp104Frame_Group_68::~CEp104Frame_Group_68(void)
{

}


DWORD CEp104Frame_Group_68::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	return 1;
}

CEpFrameBase* CEp104Frame_Group_68::Match(PEPBUFFERPOS pBufferPos)
{
	if (Ep_EpBufferLeave(pBufferPos) < 1)
	{
		return NULL;
	}

	BYTE *pRcvBuffer = pBufferPos->pBuffer;

	if (Ep_EpBufferLeave(pBufferPos) < 6)
	{
		if (*pRcvBuffer == 0x68)
		{
			Ep_SetMatchStateNotFull(pBufferPos);
		}

		return NULL;
	}


	if (*pRcvBuffer != 0x68)
	{
		return NULL;
	}

	//长度L包括控制域、地址域、用户数据区的字节数
	//启动字符（68H） + 长度（L）+ 长度重复（L） + 启动字符（68H）+  帧校验和（CS） + 结束字符（16H）
	//共六个字符，如果长度小于最小的有效长度，表示长度不够，则返回NULL
	long n1 = Ep_EpBufferLeave(pBufferPos);
	long n2 = *(pRcvBuffer+EP_104_FRAME_68_POS_LENGTH) + 2;
	if (n1 < n2)
	{
		Ep_SetMatchStateNotFull(pBufferPos);
		return NULL;
	}

	Ep_OffsetEpBufferCurr(pBufferPos, 6);

	//遍历组的各报文帧，匹配
	return CEpFrameGroup::Match(pBufferPos);
}

DWORD CEp104Frame_Group_68::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0xE5;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

