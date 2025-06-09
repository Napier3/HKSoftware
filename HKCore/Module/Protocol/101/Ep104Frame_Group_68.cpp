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

	//����L���������򡢵�ַ���û����������ֽ���
	//�����ַ���68H�� + ���ȣ�L��+ �����ظ���L�� + �����ַ���68H��+  ֡У��ͣ�CS�� + �����ַ���16H��
	//�������ַ����������С����С����Ч���ȣ���ʾ���Ȳ������򷵻�NULL
	long n1 = Ep_EpBufferLeave(pBufferPos);
	long n2 = *(pRcvBuffer+EP_104_FRAME_68_POS_LENGTH) + 2;
	if (n1 < n2)
	{
		Ep_SetMatchStateNotFull(pBufferPos);
		return NULL;
	}

	Ep_OffsetEpBufferCurr(pBufferPos, 6);

	//������ĸ�����֡��ƥ��
	return CEpFrameGroup::Match(pBufferPos);
}

DWORD CEp104Frame_Group_68::Produce(PEPBUFFERPOS pBufferPos)
{
	BYTE *pRcvBuffer = Ep_GetEpBufferCurr(pBufferPos);
	*pRcvBuffer = 0xE5;

	return Ep_OffsetEpBufferCurr(pBufferPos, 1);
}

