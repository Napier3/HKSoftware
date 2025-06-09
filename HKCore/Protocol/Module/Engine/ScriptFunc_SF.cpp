#include "StdAfx.h"
#include "ScriptFunc_SF.h"
#include <math.h>
#include "PpEngineDataMngrCntr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


WORD script_SF_ToBin(FLOAT fData, char *pBuffer)
{
	FLOAT fInt = 0;//��������
	FLOAT fDec = 0;//С������
	char csInt[64];//��������
	char csDec[64];//С������
	char *pcsInt = csInt;
	char *pcsDec = csDec;
	fData = fabsf(fData);
	fInt = floorf(fData);
	fDec = fData - fInt;

	//����С������
	if (fDec <= 0.000001)
	{
		*pcsDec = '0';
	}
	else
	{
		while(fDec > 0.000001)
		{
			fDec *= 2.0;
			if (fDec >= 1.0)
			{
				*pcsDec = '1';
				pcsDec++;
				fDec -= 1.0;
			}
			else
			{
				*pcsDec = '0';
				pcsDec++;
			}
		}
	}

	//������������
	if (fInt == 0.0)
	{
		*pcsInt = '0';
	}
	else
	{
		while(fInt != 1.0)
		{
			if (fmodf(fInt,2.0) == 1.0)
			{
				*pcsInt = '1';
				pcsInt++;
			}
			else
			{
				*pcsInt = '0';
				pcsInt++;
			}
			fInt /= 2.0;
			fInt = floorf(fInt);
		}

		*pcsInt = '1';
		pcsInt++;
	}

	*pcsInt = 0;
	*pcsDec = 0;
	
	char *pHead = csInt;
	char *pTail = pcsInt-1;
	char ch = 0;

	while (pHead < pTail)
	{
		ch = *pHead;
		*pHead = *pTail;
		*pTail = ch;
		pHead++;
		pTail--;
	}

	strcpy(pBuffer, csInt);
	strcat(pBuffer, csDec);

	return strlen(csInt);
}

DWORD script_SF_ToThreeFloat(FLOAT fData)
{
	BYTE  btSign = 0; //����λ
	BYTE  btExp = 0;//ָ��
	DWORD dwBase = 0;//����
	WORD wPointPos = 0;
	INT  nFindOne = -1;
	char csBinData[64];
	DWORD dwValue = 0;//����ֵ
	btSign = (fData<0.0)?1:0;
	//ת����������
	wPointPos = script_SF_ToBin(fData, csBinData);
	long nLen = strlen(csBinData);
	//������Ӧ�Ļ�����ָ��
	
	char *p = csBinData;

	while (*p != 0)
	{
		if (*p == '1')
		{
			nFindOne = p - csBinData;
			break;
		}
		p++;
	}

	if (nFindOne < 0)
	{
		dwValue = 0;
	}
	else
	{
		//ָ��
		if (nFindOne > wPointPos)
		{
			btExp = ((wPointPos- nFindOne)<-63) ? (-63) : (wPointPos - nFindOne);
			btExp = btExp & 0x7f;
		}
		else
		{
			btExp = ((wPointPos - nFindOne)>63) ? (63) : (wPointPos - nFindOne);
		}

		//����
		for (INT i= nFindOne; i< nLen; i++)
		{
			//ֻ�ܼ���16λ
			if ((i-nFindOne)>15)
				break;

			if (csBinData[i] == '1')
			{
				dwBase |= (1 << (15-i+nFindOne));
			}
		}

		dwValue = (dwBase & 0xffff) | (btExp << 16) | (btSign << 23);
	}

	return dwValue;
}

WORD script_SF_pcrc(BYTE *start,BYTE *end)
{
	WORD r2,r3;
	WORD r01=0;
	int bz,k=0;

	do
	{
		r2=start[k];
		r3=8;
BBB:
		bz=r2&0x80;
		r2<<=1;

		if(bz)
		{
			bz=r01&0x8000;
			if(bz) r01<<=1;
			else
			{
				r01^=0x810;
				r01<<=1;
				r01|=0x1;
			}
		}
		else
		{
			bz=r01&0x8000;
			if(!bz) r01<<=1;
			else
			{
				r01^=0x810;
				r01<<=1;
				r01|=0x1;
			}
		}
		r3--;
		if(r3!=0)  goto BBB;
		else k++;
	}while((BYTE *)(start+k)!=end);

	return r01;
}
