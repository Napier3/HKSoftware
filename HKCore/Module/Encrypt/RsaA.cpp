// RsaA.cpp : implementation file
//

#include "stdafx.h"
//#include "RSATest1.h"
#include "RsaA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsaA

IMPLEMENT_DYNCREATE(CRsaA, CCmdTarget)

CRsaA::CRsaA()
{
	InitInt();
		
}

CRsaA::~CRsaA()
{

}


BEGIN_MESSAGE_MAP(CRsaA, CCmdTarget)
	//{{AFX_MSG_MAP(CRsaA)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
		//ON_MESSAGE(WM_COMPUTING,OnComputing)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRsaA message handlers

/*----------------------------------------------------------------------------
���ܣ�������ش����ĳ�ʼ��
��ڲ�������
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::InitInt(void)
{
	SetZero(ZEROVALUE);						//�Դ�������zerovalue����
	memset(mZEROVALUE,0,MLENGTH);
	SetZero(ONEVALUE);                      //�Դ�������ONEVALUE��������
	ONEVALUE[DATALENGTH-1]=1;				//ONEVALUE�����һλΪ1
	SetZero(TWOVALUE);						//��TOWVALUE��������
    TWOVALUE[DATALENGTH-1]=2;				//TOWVALUE�����һλΪ2
	SetZero(EIGHTVALUE);					//��EIGHTVALUE��������
    EIGHTVALUE[DATALENGTH-1]=8;				//���һλΪ8
	return ;
}

/*---------------------------------------------------------------------------
���ܣ���һ������Aת��Ϊ��Ӧ���ַ�����ʽ
��ڲ���������A
����ֵ�����Ӧ���ַ���
----------------------------------------------------------------------------*/
CString CRsaA::PrtInt(byteint A)
{
	long i=0;
	int m,n;

	while(i<DATALENGTH && A[i]==0)          //����������ʼ�Ŀհ�0
		i++;

	if(i<DATALENGTH)
		m=DATALENGTH-i;                     //������õĴ�������
	n=0;
											//ע�⵽�����i�Ѿ��������е�һ������Ԫ�صĶ�Ӧλ�ã�
	CString str;							//��������ѭ�����Ǵ�������
											//��ŵ��������λ��ʼ�����
	while(i<DATALENGTH)
	{
		str.AppendFormat(_T("%c"), A[i]+'0');
		i++;
	}

	return str;
}

/*---------------------------------------------------------------------------
���ܣ�����A�����B��ˣ��������C�� A��B->C
��ڲ�����������A�ͳ���B�����C
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::Multiply(byteint A,byteint B,byteint C)
{
	long i,j,w;
	int X,Y,Z;
	int Avalid=0;								//Avalid=validating bits of A
	int Bvalid=0;								//Avalid=validating bits of B
	while (A[Avalid]==0 && Avalid<DATALENGTH)
		Avalid++;								//����Avalid
	while (B[Bvalid]==0 && Bvalid<DATALENGTH)
		Bvalid++;								//����Bvalid

	SetZero(C);									//��C�����ʼ��
	
	for(i=DATALENGTH-1;i>=Avalid;i--)
		for(j=DATALENGTH-1;j>=Bvalid;j--)       //��λ�����������
		{
			X=A[i]*B[j];        
			Y=X/10;
			Z=X-10*Y;
			w=i+j-(DATALENGTH-1);
			C[w]=C[w]+Z;
			C[w-1]=C[w-1]+(C[w]/10)+Y;
			C[w]=C[w]-(C[w]/10)*10;
		}
	return;
}

/*---------------------------------------------------------------------------
���ܣ���ָ�����Զ���Ĵ�������0��ʼ��
��ڲ���������A��
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::SetZero(byteint A)  
{
	memset(A,0,DATALENGTH);                    //����ϵͳ�������г�ʼ��
}

/*---------------------------------------------------------------------------
���ܣ�������B����������A��
��ڲ���������A������B
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::IntCpy(byteint A,byteint B)
{
	memcpy(A,B,DATALENGTH);                    //����ϵͳ������ɿ���
}

/*---------------------------------------------------------------------------
���ܣ�A��B�Ľ����C
��ڲ���������A,B,C
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::Plus(byteint A,byteint B,byteint C)
{
	long i;//,w;
	int X,Y,Z,m,n,valid;
	m=IntValid(A);                 //����A�ĳ���         
	n=IntValid(B);                 //����B�ĳ���
	valid=(m>n)?m+1:n+1;           //����ʱҪ�������Ϊ׼
	SetZero(C);                    //��C����
	for(i=DATALENGTH-1;i>=DATALENGTH-valid;i--)
	{
		X=A[i]+B[i];               //��λ���
		Y=X/10;
		Z=X-10*Y;

		C[i]=C[i]+Z;               //�����λ
		C[i-1]=C[i-1]+Y;
	}
}

/*---------------------------------------------------------------------------
���ܣ�����SA��ȥ����SB���������SC
��ڲ�����������SA������SB����SC
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::Substract(byteint SA,byteint SB,byteint SC)
{
	byteint buf;
	long i,j;
	int X;
	IntCpy(buf,SA);                  //��SA�����ݿ�����buf��
	SetZero(SC);                 //SC�����ʼ��
	for(i=DATALENGTH-1;i>=0;i--)	
	{
		if(buf[i]<SB[i])             //������λ������
		{
			buf[i]=buf[i]+10;        //���λ��1
			if(buf[i-1]>0)           //�����λ������ֱ�Ӽ�1
				(buf[i-1])--;    
			else                     //����һֱ�ҵ�������λ
			{
				j=i-1;
				while(buf[j]==0)     //j�������Խ�磬����Ϊ��֤�����λ��Ϊ0
					buf[j--]=9;
				buf[j]=buf[j]-1;
			}
		}
		X=buf[i]-SB[i];              //����λ���Ľ������SC��
		SC[i]=X;
	}
}

/*---------------------------------------------------------------------------
���ܣ��Ƚ���������A��B�Ĵ�С
��ڲ���������A�ʹ���B
����ֵ��A>B:return 1 ; A=B:return 0 ; A<B:return -1
----------------------------------------------------------------------------*/
int CRsaA::IntCmp(byteint A,byteint B)
{
	int stat;
	stat=memcmp(A,B,DATALENGTH);    //ϵͳ����
	if(stat==0)
		return 0;
	if(stat>0)
		return 1;
	return -1;
}

/*---------------------------------------------------------------------------
���ܣ��õ�һ�������ķ���λ��
��ڲ���������validtemp
����ֵ�������з����λ��
----------------------------------------------------------------------------*/
int CRsaA::IntValid(byteint validtemp)
{
	long i=0;
	while(validtemp[i]==0 && i<DATALENGTH)
		i++;
	return DATALENGTH-i;
}

/*---------------------------------------------------------------------------
���ܣ��������A��B�Ľ������������C�У�����D��
��ڲ�����������A������B������C����D
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::SetMode(byteint A,byteint B,byteint C,byteint D)
{
	long i,j,k;
	int valid_1,valid_2,valid,sbits,cmpval;
	byteint buf1,buf2;
    
	SetZero(buf1);  SetZero(buf2);
	SetZero(D);                       //������D���������ʼ��
    IntCpy(C,A);                      //��������A������C��
	valid_2=IntValid(B);              //����B(����)��λ��,
	while((cmpval=IntCmp(C,B))>0)     //�����Ϊ����,ÿ��һ�ξ��ж��Ƿ���C>B,�������ͼ�������
	{
		valid_1=IntValid(C);          //����C(������)��λ��,��Ϊ����λ����ѭ���������Ǳ仯��
		                              //��������(C-B)��Ȼ�����C��
		valid=valid_1-valid_2;        //C�ĳ�����B�ĳ��ȵĲ��ֵ��СΪ0��
		if(valid>0)                   //����������ȳ�����λ����
		{
			i=DATALENGTH-valid_1;     //������ǰ����ĸ���
			j=DATALENGTH-valid_2;     //����ǰ����ĸ��������±�ָʾ��
			sbits=0;
			for(k=j;k<DATALENGTH;k++)
			{
				if(C[i]>B[j])         //��C��B�����λ��ʼ���αȽ϶�Ӧλ�Ĵ�С���ж��Ƿ񹻼�
					break;
				if(C[i]<B[j])
				{
					sbits=1;          //�������������ôC����һλ����������
					break;
				}
				i++;j++;              //��C��B�����λ���ʱ,�ͱȽ϶��ߵĴθ�λ
			}
			valid=valid-sbits;
			SetZero(buf1);            //buf1����
			for(i=valid;i<DATALENGTH;i++)
			{
				j=i-valid;
				buf1[j]=B[i];         //buf1�д�ŵ���B��������λ֮��õ���ֵ
				                      //�������,��B���ƺ����λ��C�����λ����,
				                      //������C�Ĵθ�λ����
			}
		}
		else
			IntCpy(buf1,B);           //��C��B��λ����ͬʱ,��ֱ�Ӱ�B���뻺����buf1��

		D[DATALENGTH-1-valid]++;      //���ﱣ�������ĳһλ�������ļ����Ĵ�����ÿ��һ�ξͼ�1
		Substract(C,buf1,buf2);       //����C�ĳ�����B�ĳ��ȵĲ��Ƿ����0����Ҫ��������ֱ��C<=B
		IntCpy(C,buf2);
	}
	if(cmpval==0)                     //���������
	{
		SetZero(C);                   //����Ϊ0
		D[DATALENGTH-1]++;            //��Ϊ1
	}
}

/*---------------------------------------------------------------------------
���ܣ�����ز���һ����������������Ϊnum�����λ����0�������RandomA��
��ڲ���������A������num
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::IntRandom(byteint RandomA,int num)
{
	int i;
	SetZero(RandomA);                     //��RandomA����
	
	while(!(RandomA[DATALENGTH-1]%2))     //�ж�������֤RandomA�����һλ��������
		RandomA[DATALENGTH-1]=rand()%10;  //������һλ��ż��������²������һλ
    while(!(RandomA[DATALENGTH-num]))     //�ж�������֤RandomA���λ����0
		RandomA[DATALENGTH-num]=rand()%10;//������λ��0,����²������λ

	i=DATALENGTH-2;
	while(i>=DATALENGTH-num+1)            //ѭ�������Ӵε�λ��ʼ���θ�λ������λ�ϵ���
		RandomA[i--]=rand()%10;
}

/*---------------------------------------------------------------------------
���ܣ�����������B������A�У�ʵ������ת��
��ڲ���������A����������B
����ֵ����
----------------------------------------------------------------------------*/
//���ܣ�����B����������A��ʵ������ת��
void CRsaA::LoadInt(byteint A,mtype B)
{
	long i,j;
	SetZero(A);                  //A���������ʼ��
	i=DATALENGTH-1;
	j=MLENGTH-1;
	while(j>0)                   //ѭ��������λ����
	{
		A[i--]=B[j--];
	}
}

/*---------------------------------------------------------------------------
���ܣ��ú��������Ӽ���[1,b-1]�в������ɸ����ڼ������������Model[]��
��ڲ�������
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::Mdata()
{
	long i,j;                     //Randomly choose a set of 100 numbers in [1,b-1]
	int k=MLENGTH-2;
	
	memset(Model,0,TESTNUM*MLENGTH);  //������������������������������㣬���г�ʼ��
	srand( (unsigned)time( NULL ) );  //������������ĳ�ʼ��
	for(i=0;i<TESTNUM;i++)            //TESTNUMΪ��Ҫ�����ĸ���
	{
		for(j=MLENGTH-1;j>=k;j--)
		{
			Model[i][j]=rand()%10;    //ע����������������ĳ����е�����
		}
		if((memcmp(Model[i],mZEROVALUE,MLENGTH))==0)  
			i--;
		k--;                          //��֤������������Ϊ0
		if (k<0) k=MLENGTH-2;
	}
	
}

/*---------------------------------------------------------------------------
���ܣ��ú���������ʮ���ƵĴ�����ת���ɶ����Ƶ���
��ڲ�������ת���Ĵ���B�������ƽ��flag[400]
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::TransBi(byteint B,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp;
	long i;
	SetZero(buf);  SetZero(result);  SetZero(temp);
	memset(flag,0,400);                     //��flag��������

	i=399;
	IntCpy(buf,B);                          //��B������buf��
	while(IntCmp(buf,ZEROVALUE)==1)         //���buf����Ϊ0
	{
		SetMode(buf,TWOVALUE,temp,result);  //��buf���д�����ģ2���㣬����result�У�����temp
		flag[i]=temp[DATALENGTH-1];         
		IntCpy(buf,result);                 //���̼�������ģ2����
		i--;
	}
	flag[i]=-1;                             //����һ����־λ���������������Ŀ�ʼ
}

/*---------------------------------------------------------------------------
���ܣ��ú�����������ģ���㷨��AΪ������ģΪc�������Ƶ�ָ��B���������flag��
��ڲ���������A��ģC�����D������������flag[400]
����ֵ��A^B=1(mod C),����1��A^B=p-1(mod C),����2�����򷵻�0
----------------------------------------------------------------------------*/
int CRsaA::PowerMode(byteint A,byteint C,byteint D,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp,P;
	long i;
	SetZero(D);   SetZero(buf); SetZero(result); SetZero(temp); SetZero(P);  //��D����

	IntCpy(temp,A);                       //��A��ֵ������temp��
	if(flag[399]==1)                      //���λΪ1����������flag[i]ֻ��1����0�������
		IntCpy(result,A);
	else								  //���λΪ0������Ϊ1
		IntCpy(result,ONEVALUE);
	i=398;
	while(flag[i]!=-1)                    //�ж��Ƿ��Ѿ�����ָ����ͷ
	{
		Multiply(temp,temp,buf);          //temp*temp->buf 
		SetMode(buf,C,temp,P);            //buf%c����->temp,��->p
		if(flag[i]!=0)                    //�����λ����0�������ǰһ����һλ�Ľ�����г˷�����
		{                                 //���򣬽�����Ϊ��λ��ģ���ڸ�һλ�������У�ֻҪ����һ��
			Multiply(temp,result,buf);    //ƽ�����㣬�Ϳ��Եõ���һλ��ģ
			SetMode(buf,C,result,P);
		}
		i--;
	}                                     //result�д�ŵ������ս��
	IntCpy(buf,C);
	IntCpy(D,result);
	Substract(buf,ONEVALUE,temp);
	if(IntCmp(result,ONEVALUE)==0)        //p mod n=1���ж��Ƿ���A^B=1(mod C)
		return 1;
	if(IntCmp(result,temp)==0)            //p mod n=-1[p-1=-1(mod p)]���ж��Ƿ���A^B=p-1(mod C)
		return 2;
	return 0;
}

/*---------------------------------------------------------------------------
���ܣ�����һ������
��ڲ���������Prm
����ֵ�������ɹ�������0
----------------------------------------------------------------------------*/
int CRsaA::Prime(byteint Prm)
{
	int i,k,ok;
	signed char flag[400];
	byteint A,B,D,buf1,buf2;
	SetZero(A); SetZero(B); SetZero(D); SetZero(buf1); SetZero(buf2);
	
	while(1)                                 //һֱѭ��ֱ���ҵ�һ������Ϊֹ
	{
		int pass=0;
		srand( (unsigned)time( NULL ) );     //��ʼ��srand
		IntRandom(B,MLENGTH);                //�������һ������B  try b if prime,B��һ������

		IntCpy(Prm,B);                       //��B������prm�� C=N result prime
		Substract(B,ONEVALUE,buf1);          //��B-ONEVALUE�Ľ���ŵ�buf1��
		SetMode(buf1,TWOVALUE,buf2,B);       //B=(B-1)/2����,buf2=(B-1)/2������=0
		TransBi(B,flag);                     //��Bת��Ϊ�����ƴ���
		ok=1;
		for(i=0;i<TESTNUM;i++)
		{
			LoadInt(A,Model[i]);             //������Model�еĵ�i+1������ȡ��A��
			k=PowerMode(A,Prm,D,flag);       //(A^flag) mod Prm ->D
			if(k!=1 && k!=2)                 //�������ж�����
			{
				ok=0;
				break;
			}
			if(k==1)                         //�ж�����1��G=A^(n-1)/2=1
			{
			}
			if(k==2)                         //�ж�����2��G=A^(n-1)/2=p-1
			{
			}
		
		}
		if (ok)//if(ok && pass_2)
		{
			return 0;
		}//forѭ���������IntRandom(B,MLENGTH)��������B�Ƿ���һ������	
	}
}

/*---------------------------------------------------------------------------
���ܣ����㹫ԿPK
��ڲ�����$(r)��ֵ��Rvalue�У�˽ԿSK����ԿPK
����ֵ���ɹ��ҵ�������1
----------------------------------------------------------------------------*/
int CRsaA::ComputingPK(byteint Rvalue,byteint SK,byteint PK)
{
	long i;
	byteint PA,PB,PC,buf1,temp,buf2;
	SetZero(PK); SetZero(PA); SetZero(PB); SetZero(PC); SetZero(buf1);   //�����ʼ��
	SetZero(temp); SetZero(buf2);
	while(1)
	{
		IntRandom(SK,SKLENGTH);        //�������һ������������ΪGenerated secret key

		IntCpy(PB,SK);
		IntCpy(PA,Rvalue);
		while(1)
		{
			SetMode(PA,PB,PC,PK);     //PA=PB*PK+PC
			i=IntCmp(PC,ONEVALUE);
			if(i==0)                  //PC=1, i=0
				break;                //�����������ǻ��ʵ�
			i=IntCmp(PC,ZEROVALUE);
			if(i==0)
			{
				i=-1;                 //PC=0,i=-1
				break;                //�����㻥������������ѭ������������һ�������
			}
			IntCpy(PA,PB);            //����ŷ����Ķ�������ж�

			IntCpy(PB,PC);
		}
		if(i==0)                      //���㣬��������ѭ��
			break;
	}

	IntCpy(temp,ONEVALUE);
	IntCpy(PA,Rvalue);
	IntCpy(PB,SK);
	while(1)
	{
		Multiply(PA,temp,buf1);  //buf1=PA*temp
		Plus(buf1,ONEVALUE,buf2);//buf2=(PA*temp)+1
		SetMode(buf2,PB,buf1,PK);//buf=((PA*temp)+1)%PB
		if(IntCmp(buf1,ZEROVALUE)==0)
			break;
		Plus(temp,ONEVALUE,buf1);
		IntCpy(temp,buf1);
	}
	return 1;                   //SK and PK found
}


/*---------------------------------------------------------------------------
���ܣ�����ģR
��ڲ���������������p��q��ģR
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::ComputingR(byteint p,byteint q,byteint R)
{
	Multiply(p,q,R);              // R=p*q, public mode number
}

/*---------------------------------------------------------------------------
���ܣ�����$(r)
��ڲ���������p������q��ģ$(r)����Rvalue
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::ComputingRvalue(byteint p,byteint q,byteint Rvalue)
{
	byteint buf1,buf2;
	SetZero(buf1); SetZero(buf2);

	Substract(p,ONEVALUE,buf1);   // buf1=p-1
	Substract(q,ONEVALUE,buf2);   // buf2=q-1
	Multiply(buf1,buf2,Rvalue);   // Rvalue=(p-1)*(q-1)
}

/*---------------------------------------------------------------------------
���ܣ������ܵ��ַ���ת��Ϊ��������
��ڲ���������result,�ַ���input
����ֵ�����ĳ���
----------------------------------------------------------------------------*/
int CRsaA::Getinput(byteint result,CString input)
{
	int i=DATALENGTH,m=0;
	long strlen;
	int j = 0;
	strlen=input.GetLength();
	
	if(strlen==0) 
	{
		return 0;
	}
	else
	{
		for( j=0;j<strlen;j++)
		{
			result[i-strlen+j] = (input.GetAt(j)-'0');
		}
		return j;
	}
}

/*---------------------------------------------------------------------------
���ܣ�ʵ�ּ��ܣ��������㹦��
��ڲ���������(��������source)��ģR����Կkey�����desti
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::RsaDo(byteint source,byteint R,byteint key,byteint desti)
{
	TransBi(key,flag);
	PowerMode(source,R,desti,flag);
}

/*---------------------------------------------------------------------------
���ܣ��������ε���ת��Ϊ��������
��ڲ�������������result,������input
����ֵ���ɹ����������ĳ��ȣ����򷵻�0��
----------------------------------------------------------------------------*/
int CRsaA::Getinput1(byteint result,unsigned long input)
{
	int i=DATALENGTH-1,m=0;
	long j=0;
	int k=0;
	
	if(input)
	{
		do
		{
			j=input/10;
			k=input-j*10;
			result[i]=k;
			i--;
			m++;
			input=j;
		}while(j);
		return m;
	}
	else
		return 0;
}

/*---------------------------------------------------------------------------
���ܣ���ʮ�����ƵĴ�ת��Ϊ��ֵ
��ڲ������ַ���ָ��
����ֵ���ɹ���������
----------------------------------------------------------------------------*/
unsigned long CRsaA::Os2ip(unsigned char* pstr)
{
	unsigned long ch=0;
	unsigned int j=0;
	unsigned long k=1;
	for(int i=0;i<4;i++)
	{
		j = (unsigned int) (*(pstr+3-i));
	/*	if( (*(pstr+3-i))>='0'&&(*(pstr+3-i))<='9')
			j = (*(pstr+3-i)) - '0';
		if( (*(pstr+3-i))>='a'&&(*(pstr+3-i))<='f') 
			j = (*(pstr+3-i)) - 'a'+10;
		if( (*(pstr+3-i))>='A'&&(*(pstr+3-i))<='F')
			j = (*(pstr+3-i)) - 'A'+10;*/
		ch += j*k;
		k*=256;
	}
	return ch;
} 

/*---------------------------------------------------------------------------
���ܣ�������ת��Ϊ��Ӧ���ַ���
��ڲ������ַ���str
����ֵ������ת���Ľ����
----------------------------------------------------------------------------*/
CString CRsaA::Ip2os(CString str)
{
	int strlen=str.GetLength(),quotient=0,remainder=0;
	unsigned long num=0,temp=0;
	unsigned int k=1;
	CString strResult;

	for(int i=strlen;i>0;i--)  //�õ���Ӧ�����ִ�,�����num��
	{
		temp = (str.GetAt(i-1) - '0');
			num += temp*k;

		k *= 10;
	}

	//����ģ���ķ�ʽ,�����Ӧ��ʮ��������
	for(int j=0;j<4;j++)
	{
		quotient = num/256;
		remainder = num - quotient*256;
		/*if(remainder>=0&&remainder<=9)
			strResult.Insert(0,(remainder+'0'));
		if(remainder>=10&&remainder<=15)
			strResult.Insert(0,(remainder-10+'a'));*/
		strResult.Insert(0,(unsigned char)remainder);
		num = quotient;
	}
	
	return strResult; 
}

/*---------------------------------------------------------------------------
���ܣ�����RSA��Կ��
��ڲ�������Ž�����ַ�����ַ 
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::GenKeys(CString& pk,CString& sk,CString& R)
{
	byteint m_p,m_q,m_R,m_Rvalue,m_PK,m_SK;
	SetZero(m_p);      //�Դ����������������ʼ��
	SetZero(m_q);
    SetZero(m_R);
    SetZero(m_Rvalue);
    SetZero(m_PK);
    SetZero(m_SK);

	Mdata();         //���ɱȽ�����
	//AfxMessageBox("��ʼ��������P...");
	Prime(m_p);        //��������p q
	//AfxMessageBox("��ʼ��������Q...");
	Prime(m_q);

	//AfxMessageBox("��ʼ����ģR...");
	ComputingR(m_p,m_q,m_R); //����ģR
	//AfxMessageBox("��ʼ����ģr");
	ComputingRvalue(m_p,m_q,m_Rvalue);  //����r
	//AfxMessageBox("��ʼ������ԿSK,PK");
	ComputingPK(m_Rvalue,m_PK,m_SK);    // Generate PK and SK
	
	//CGenKeyBusyDlg dlg1;
	//g1.DoModal();
	R=PrtInt(m_R);
	pk=PrtInt(m_PK);
	sk=PrtInt(m_SK);
	return ;

}

/*---------------------------------------------------------------------------
���ܣ�ʵ�ּ��ܹ��ܽӿ�
��ڲ����������ַ���source��ģ�ַ���R����Կ�ַ���key������ַ�������result
����ֵ����
----------------------------------------------------------------------------*/
int CRsaA::RsaEncrypt(CString& source,const char *key,const char *R,CStringArray& result)
{
	unsigned char* pstr;
	int j;//sourcelen,j;
	byteint m_key,m_R,desti,aa;
	SetZero(desti);                         //���������������ʼ��
	SetZero(aa);
	//SetZero(bb);
	SetZero(m_key);
	SetZero(m_R);

	pstr = (unsigned char*)(LPCTSTR)source; //�õ��ַ������ݵ�ָ��
	j = source.GetLength()/4;               //�õ������Ԫ�ظ���

	result.SetSize(j,1);
	Getinput(m_key,key);                    //���ַ���ת��Ϊ��������
	Getinput(m_R,R);
	
	for(int i=0;i<j;i++)
	{
		Getinput1(desti,Os2ip(pstr));       //���ĸ��ֽڵ�����ת��Ϊ����������ֵ
		RsaDo(desti,m_R,m_key,aa);          //���м�������
		result.SetAt(i,PrtInt(aa));         //�������ŵ�������
		SetZero(desti);  SetZero(aa);
		pstr += 4;
	}
	return j;
}

/*---------------------------------------------------------------------------
���ܣ�ʵ�ֽ��ܹ��ܽӿ�
��ڲ����������ַ�������source����Կ�ַ���sk��ģ�ַ���R��
����ֵ������ַ�������result
----------------------------------------------------------------------------*/
CString CRsaA::RsaDecrypt(CStringArray& source,const char* sk,const char* R)
{
	int index=0;
	CString result;
	byteint m_sk,m_r,desti,aa;
	SetZero(m_sk);  SetZero(m_r); SetZero(desti); SetZero(aa);  //SetZero(bb);

	index=source.GetSize();   //�õ������Ԫ�ظ���
	Getinput(m_sk,sk);        //���ַ���ת��Ϊ��������
	Getinput(m_r,R);

	for(int i=0;i<index;i++)
	{
		Getinput(desti,source.GetAt(i));   //�����ܽ��ת��Ϊ��������
		RsaDo(desti,m_r,m_sk,aa);          //��������
		result += Ip2os(PrtInt(aa));       //��ϳ�ʼ����
		SetZero(aa);  SetZero(desti);
	}

	return result;        //�������Ĵ�
}

/*---------------------------------------------------------------------------
���ܣ�����һ����Կ�����ļ�
��ڲ�������
����ֵ����
----------------------------------------------------------------------------*/
void CRsaA::GenKeysTable()
{
	CStringArray RArray,SKArray,PKArray;
	CString r,pk,sk;
	int j=1,i;      //����j��ʾ��������Կ�Եĸ���
	unsigned char strlength;
	//���������Ԫ�ظ���
	RArray.SetSize(j,1);	SKArray.SetSize(j,1);	PKArray.SetSize(j,1);
	
	/*-----------------------------------------------------------------------
	�ļ���ʽΪ��
	����   ��Կ   ����   ��Կ......
	----   ----   ----   ----
	1byte  nbyte  1byte  nbyte       (�м��޿ո�,R,SK,PK)
	*/
	CFile file;

	for(i=0;i<j;i++)
	{
		GenKeys(pk,sk,r);  //ѭ��������Կ
		RArray.SetAt(i,r); SKArray.SetAt(i,sk); PKArray.SetAt(i,pk);		
	}

	//if(file.Open("c:\\key.txt",CFile::modeCreate|CFile::modeReadWrite)==0)
	if(file.Open("key.txt",CFile::modeCreate|CFile::modeReadWrite)==0)
	{
		AfxMessageBox("open file error!");  //���ļ�ʧ��
		return;
	}
	

	for(i=0;i<j;i++)
	{                //ѭ��д����
		strlength = (unsigned char)(RArray.GetAt(i)).GetLength();
		file.Write(&strlength,1);
		
		file.Write(RArray.GetAt(i),(RArray.GetAt(i)).GetLength());
		
		strlength = (unsigned char)(SKArray.GetAt(i)).GetLength();
		file.Write(&strlength,1);
		
		file.Write(SKArray.GetAt(i),(SKArray.GetAt(i)).GetLength());
		
		strlength = (unsigned char)(PKArray.GetAt(i)).GetLength();
		file.Write(&strlength,1);
		
		file.Write(PKArray.GetAt(i),(PKArray.GetAt(i)).GetLength());
	}
	
	file.Close();
}

void CRsaA::LoadKeysFromFile(CString& r,CString& sk,CString& pk)
{
	int            j=10,len;
	char           *pbuffer;
	unsigned char  strlen1;
	
	CFile          file;
	CFileException e;
	CString        strFileName;
	if(file.Open("c:\\key.txt",CFile::modeRead)==0)
	{	
		AfxMessageBox("File(key.txt)could not be opened" );
	}
	file.Read(&strlen1,1);  //����R����
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //����R
	r=pbuffer;
	delete pbuffer;

	file.Read(&strlen1,1);  //����SK����
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //����SK
	sk=pbuffer;
	delete pbuffer;

	file.Read(&strlen1,1);  //����PK����
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //����PK
	pk=pbuffer;
	delete pbuffer;

	file.Close();
}	