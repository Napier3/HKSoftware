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
功能：进行相关大数的初始化
入口参数：无
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::InitInt(void)
{
	SetZero(ZEROVALUE);						//对大数变量zerovalue清零
	memset(mZEROVALUE,0,MLENGTH);
	SetZero(ONEVALUE);                      //对大数变量ONEVALUE进行清零
	ONEVALUE[DATALENGTH-1]=1;				//ONEVALUE的最后一位为1
	SetZero(TWOVALUE);						//将TOWVALUE进行清零
    TWOVALUE[DATALENGTH-1]=2;				//TOWVALUE的最后一位为2
	SetZero(EIGHTVALUE);					//对EIGHTVALUE进行清零
    EIGHTVALUE[DATALENGTH-1]=8;				//最后一位为8
	return ;
}

/*---------------------------------------------------------------------------
功能：将一个大数A转换为相应的字符串形式
入口参数：大数A
返回值：相对应的字符串
----------------------------------------------------------------------------*/
CString CRsaA::PrtInt(byteint A)
{
	long i=0;
	int m,n;

	while(i<DATALENGTH && A[i]==0)          //跳过大数开始的空白0
		i++;

	if(i<DATALENGTH)
		m=DATALENGTH-i;                     //求出有用的大数长度
	n=0;
											//注意到这里的i已经是数组中第一个非零元素的对应位置，
	CString str;							//因此下面的循环就是从数组中
											//存放的数的最高位开始输出。
	while(i<DATALENGTH)
	{
		str.AppendFormat(_T("%c"), A[i]+'0');
		i++;
	}

	return str;
}

/*---------------------------------------------------------------------------
功能：大数A与大数B相乘，结果放入C中 A×B->C
入口参数：被乘数A和乘数B，结果C
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::Multiply(byteint A,byteint B,byteint C)
{
	long i,j,w;
	int X,Y,Z;
	int Avalid=0;								//Avalid=validating bits of A
	int Bvalid=0;								//Avalid=validating bits of B
	while (A[Avalid]==0 && Avalid<DATALENGTH)
		Avalid++;								//计算Avalid
	while (B[Bvalid]==0 && Bvalid<DATALENGTH)
		Bvalid++;								//计算Bvalid

	SetZero(C);									//将C清零初始化
	
	for(i=DATALENGTH-1;i>=Avalid;i--)
		for(j=DATALENGTH-1;j>=Bvalid;j--)       //逐位进行相乘运算
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
功能：将指定的自定义的大数进行0初始化
入口参数：大数A名
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::SetZero(byteint A)  
{
	memset(A,0,DATALENGTH);                    //调用系统函数进行初始化
}

/*---------------------------------------------------------------------------
功能：将大数B拷贝到大数A中
入口参数：大数A，大数B
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::IntCpy(byteint A,byteint B)
{
	memcpy(A,B,DATALENGTH);                    //调用系统函数完成拷贝
}

/*---------------------------------------------------------------------------
功能：A＋B的结果送C
入口参数：大数A,B,C
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::Plus(byteint A,byteint B,byteint C)
{
	long i;//,w;
	int X,Y,Z,m,n,valid;
	m=IntValid(A);                 //计算A的长度         
	n=IntValid(B);                 //计算B的长度
	valid=(m>n)?m+1:n+1;           //计算时要以最长的数为准
	SetZero(C);                    //将C清零
	for(i=DATALENGTH-1;i>=DATALENGTH-valid;i--)
	{
		X=A[i]+B[i];               //按位相加
		Y=X/10;
		Z=X-10*Y;

		C[i]=C[i]+Z;               //计算进位
		C[i-1]=C[i-1]+Y;
	}
}

/*---------------------------------------------------------------------------
功能：大数SA减去大数SB，结果放入SC
入口参数：被减数SA，减数SB，差SC
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::Substract(byteint SA,byteint SB,byteint SC)
{
	byteint buf;
	long i,j;
	int X;
	IntCpy(buf,SA);                  //将SA的内容拷贝到buf中
	SetZero(SC);                 //SC清零初始化
	for(i=DATALENGTH-1;i>=0;i--)	
	{
		if(buf[i]<SB[i])             //如果最低位不够减
		{
			buf[i]=buf[i]+10;        //向高位借1
			if(buf[i-1]>0)           //如果高位够减，直接减1
				(buf[i-1])--;    
			else                     //否则一直找到够减的位
			{
				j=i-1;
				while(buf[j]==0)     //j不会出现越界，是因为保证了最高位不为0
					buf[j--]=9;
				buf[j]=buf[j]-1;
			}
		}
		X=buf[i]-SB[i];              //将各位减的结果存入SC中
		SC[i]=X;
	}
}

/*---------------------------------------------------------------------------
功能：比较两个大数A和B的大小
入口参数：大数A和大数B
返回值：A>B:return 1 ; A=B:return 0 ; A<B:return -1
----------------------------------------------------------------------------*/
int CRsaA::IntCmp(byteint A,byteint B)
{
	int stat;
	stat=memcmp(A,B,DATALENGTH);    //系统函数
	if(stat==0)
		return 0;
	if(stat>0)
		return 1;
	return -1;
}

/*---------------------------------------------------------------------------
功能：得到一个大数的非零位数
入口参数：大数validtemp
返回值：大数中非零的位数
----------------------------------------------------------------------------*/
int CRsaA::IntValid(byteint validtemp)
{
	long i=0;
	while(validtemp[i]==0 && i<DATALENGTH)
		i++;
	return DATALENGTH-i;
}

/*---------------------------------------------------------------------------
功能：计算大数A÷B的结果，余数放在C中，商在D中
入口参数：被除数A，除数B，余数C，商D
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::SetMode(byteint A,byteint B,byteint C,byteint D)
{
	long i,j,k;
	int valid_1,valid_2,valid,sbits,cmpval;
	byteint buf1,buf2;
    
	SetZero(buf1);  SetZero(buf2);
	SetZero(D);                       //将大数D进行清零初始化
    IntCpy(C,A);                      //将被除数A拷贝到C中
	valid_2=IntValid(B);              //计算B(除数)的位数,
	while((cmpval=IntCmp(C,B))>0)     //变除法为减法,每减一次就判断是否有C>B,如果满足就继续减。
	{
		valid_1=IntValid(C);          //计算C(被除数)的位数,因为它的位数在循环过程中是变化的
		                              //做减法后(C-B)仍然存放在C中
		valid=valid_1-valid_2;        //C的长度与B的长度的差（该值最小为0）
		if(valid>0)                   //如果被除数比除数的位数多
		{
			i=DATALENGTH-valid_1;     //被除数前导零的个数
			j=DATALENGTH-valid_2;     //除数前导零的个数，作下标指示器
			sbits=0;
			for(k=j;k<DATALENGTH;k++)
			{
				if(C[i]>B[j])         //从C和B的最高位开始依次比较对应位的大小，判断是否够减
					break;
				if(C[i]<B[j])
				{
					sbits=1;          //如果不够减，那么C就退一位，再做减法
					break;
				}
				i++;j++;              //当C和B的最高位相等时,就比较二者的次高位
			}
			valid=valid-sbits;
			SetZero(buf1);            //buf1清零
			for(i=valid;i<DATALENGTH;i++)
			{
				j=i-valid;
				buf1[j]=B[i];         //buf1中存放的是B左移若干位之后得到的值
				                      //如果够减,则B左移后最高位与C的最高位对齐,
				                      //否则与C的次高位对齐
			}
		}
		else
			IntCpy(buf1,B);           //当C和B的位数相同时,就直接把B放入缓冲区buf1中

		D[DATALENGTH-1-valid]++;      //这里保存的是在某一位上所做的减法的次数，每做一次就加1
		Substract(C,buf1,buf2);       //不论C的长度与B的长度的差是否大于0，都要做减法，直到C<=B
		IntCpy(C,buf2);
	}
	if(cmpval==0)                     //两个数相等
	{
		SetZero(C);                   //余数为0
		D[DATALENGTH-1]++;            //商为1
	}
}

/*---------------------------------------------------------------------------
功能：随机地产生一个大数奇数，长度为num，最高位不是0，存放在RandomA中
入口参数：大数A，长度num
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::IntRandom(byteint RandomA,int num)
{
	int i;
	SetZero(RandomA);                     //将RandomA清零
	
	while(!(RandomA[DATALENGTH-1]%2))     //判断条件保证RandomA的最后一位数是奇数
		RandomA[DATALENGTH-1]=rand()%10;  //如果最后一位是偶数，则从新产生最后一位
    while(!(RandomA[DATALENGTH-num]))     //判断条件保证RandomA最高位不是0
		RandomA[DATALENGTH-num]=rand()%10;//如果最高位是0,则从新产生最高位

	i=DATALENGTH-2;
	while(i>=DATALENGTH-num+1)            //循环产生从次低位开始到次高位的所有位上的数
		RandomA[i--]=rand()%10;
}

/*---------------------------------------------------------------------------
功能：将质数类型B拷贝到A中，实现类型转换
入口参数：大数A，质数类型B
返回值：无
----------------------------------------------------------------------------*/
//功能：将数B拷贝到大数A，实现类型转换
void CRsaA::LoadInt(byteint A,mtype B)
{
	long i,j;
	SetZero(A);                  //A进行清零初始化
	i=DATALENGTH-1;
	j=MLENGTH-1;
	while(j>0)                   //循环拷贝各位数字
	{
		A[i--]=B[j--];
	}
}

/*---------------------------------------------------------------------------
功能：该函数用来从集合[1,b-1]中产生若干个用于检测的数，存放在Model[]中
入口参数：无
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::Mdata()
{
	long i,j;                     //Randomly choose a set of 100 numbers in [1,b-1]
	int k=MLENGTH-2;
	
	memset(Model,0,TESTNUM*MLENGTH);  //这个函数在这里用来将整个数组清零，进行初始化
	srand( (unsigned)time( NULL ) );  //进行随机函数的初始化
	for(i=0;i<TESTNUM;i++)            //TESTNUM为需要产生的个数
	{
		for(j=MLENGTH-1;j>=k;j--)
		{
			Model[i][j]=rand()%10;    //注意这里与测试素数的程序中的区别，
		}
		if((memcmp(Model[i],mZEROVALUE,MLENGTH))==0)  
			i--;
		k--;                          //保证所产生的数不为0
		if (k<0) k=MLENGTH-2;
	}
	
}

/*---------------------------------------------------------------------------
功能：该函数用来将十进制的大整数转换成二进制的数
入口参数：需转换的大数B，二进制结果flag[400]
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::TransBi(byteint B,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp;
	long i;
	SetZero(buf);  SetZero(result);  SetZero(temp);
	memset(flag,0,400);                     //将flag数组清零

	i=399;
	IntCpy(buf,B);                          //将B拷贝到buf中
	while(IntCmp(buf,ZEROVALUE)==1)         //如果buf内容为0
	{
		SetMode(buf,TWOVALUE,temp,result);  //将buf进行大数的模2运算，商在result中，余数temp
		flag[i]=temp[DATALENGTH-1];         
		IntCpy(buf,result);                 //对商继续进行模2运算
		i--;
	}
	flag[i]=-1;                             //设置一个标志位，表明二进制数的开始
}

/*---------------------------------------------------------------------------
功能：该函数用来进行模幂算法，A为底数，模为c，二进制的指数B存放在数组flag中
入口参数：底数A，模C，结果D，二进制质数flag[400]
返回值：A^B=1(mod C),返回1；A^B=p-1(mod C),返回2；否则返回0
----------------------------------------------------------------------------*/
int CRsaA::PowerMode(byteint A,byteint C,byteint D,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp,P;
	long i;
	SetZero(D);   SetZero(buf); SetZero(result); SetZero(temp); SetZero(P);  //将D清零

	IntCpy(temp,A);                       //将A的值拷贝到temp中
	if(flag[399]==1)                      //最低位为1，拷贝本身，flag[i]只有1或者0两种情况
		IntCpy(result,A);
	else								  //最低位为0，则幂为1
		IntCpy(result,ONEVALUE);
	i=398;
	while(flag[i]!=-1)                    //判断是否已经到达指数尽头
	{
		Multiply(temp,temp,buf);          //temp*temp->buf 
		SetMode(buf,C,temp,P);            //buf%c余数->temp,商->p
		if(flag[i]!=0)                    //如果该位不是0，则将其和前一步低一位的结果进行乘法运算
		{                                 //否则，将其作为该位的模，在高一位的运算中，只要进行一次
			Multiply(temp,result,buf);    //平方运算，就可以得到高一位的模
			SetMode(buf,C,result,P);
		}
		i--;
	}                                     //result中存放的是最终结果
	IntCpy(buf,C);
	IntCpy(D,result);
	Substract(buf,ONEVALUE,temp);
	if(IntCmp(result,ONEVALUE)==0)        //p mod n=1，判断是否有A^B=1(mod C)
		return 1;
	if(IntCmp(result,temp)==0)            //p mod n=-1[p-1=-1(mod p)]，判断是否有A^B=p-1(mod C)
		return 2;
	return 0;
}

/*---------------------------------------------------------------------------
功能：产生一个质数
入口参数：大数Prm
返回值：产生成功，返回0
----------------------------------------------------------------------------*/
int CRsaA::Prime(byteint Prm)
{
	int i,k,ok;
	signed char flag[400];
	byteint A,B,D,buf1,buf2;
	SetZero(A); SetZero(B); SetZero(D); SetZero(buf1); SetZero(buf2);
	
	while(1)                                 //一直循环直到找到一个素数为止
	{
		int pass=0;
		srand( (unsigned)time( NULL ) );     //初始化srand
		IntRandom(B,MLENGTH);                //随机产生一个大数B  try b if prime,B是一个奇数

		IntCpy(Prm,B);                       //将B拷贝到prm中 C=N result prime
		Substract(B,ONEVALUE,buf1);          //将B-ONEVALUE的结果放到buf1中
		SetMode(buf1,TWOVALUE,buf2,B);       //B=(B-1)/2的商,buf2=(B-1)/2的余数=0
		TransBi(B,flag);                     //将B转换为二进制大数
		ok=1;
		for(i=0;i<TESTNUM;i++)
		{
			LoadInt(A,Model[i]);             //将数组Model中的第i+1个数读取到A中
			k=PowerMode(A,Prm,D,flag);       //(A^flag) mod Prm ->D
			if(k!=1 && k!=2)                 //不符合判定规则
			{
				ok=0;
				break;
			}
			if(k==1)                         //判定条件1，G=A^(n-1)/2=1
			{
			}
			if(k==2)                         //判定条件2，G=A^(n-1)/2=p-1
			{
			}
		
		}
		if (ok)//if(ok && pass_2)
		{
			return 0;
		}//for循环用来检测IntRandom(B,MLENGTH)产生的数B是否是一个素数	
	}
}

/*---------------------------------------------------------------------------
功能：计算公钥PK
入口参数：$(r)的值在Rvalue中，私钥SK，公钥PK
返回值：成功找到，返回1
----------------------------------------------------------------------------*/
int CRsaA::ComputingPK(byteint Rvalue,byteint SK,byteint PK)
{
	long i;
	byteint PA,PB,PC,buf1,temp,buf2;
	SetZero(PK); SetZero(PA); SetZero(PB); SetZero(PC); SetZero(buf1);   //清零初始化
	SetZero(temp); SetZero(buf2);
	while(1)
	{
		IntRandom(SK,SKLENGTH);        //随机产生一个大数奇数作为Generated secret key

		IntCpy(PB,SK);
		IntCpy(PA,Rvalue);
		while(1)
		{
			SetMode(PA,PB,PC,PK);     //PA=PB*PK+PC
			i=IntCmp(PC,ONEVALUE);
			if(i==0)                  //PC=1, i=0
				break;                //满足条件，是互质的
			i=IntCmp(PC,ZEROVALUE);
			if(i==0)
			{
				i=-1;                 //PC=0,i=-1
				break;                //不满足互质条件，跳出循环，从新生成一个随机数
			}
			IntCpy(PA,PB);            //按照欧几里的定理继续判断

			IntCpy(PB,PC);
		}
		if(i==0)                      //满足，跳出查找循环
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
功能：计算模R
入口参数：产生的质数p，q，模R
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::ComputingR(byteint p,byteint q,byteint R)
{
	Multiply(p,q,R);              // R=p*q, public mode number
}

/*---------------------------------------------------------------------------
功能：计算$(r)
入口参数：质数p，质数q，模$(r)放在Rvalue
返回值：无
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
功能：将接受的字符串转换为大数类型
入口参数：大数result,字符串input
返回值：数的长度
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
功能：实现加密，解密运算功能
入口参数：明文(大数类型source)，模R，秘钥key，结果desti
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::RsaDo(byteint source,byteint R,byteint key,byteint desti)
{
	TransBi(key,flag);
	PowerMode(source,R,desti,flag);
}

/*---------------------------------------------------------------------------
功能：将长整形的数转换为大数类型
入口参数：大数类型result,长整形input
返回值：成功，返回数的长度，否则返回0；
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
功能：将十六进制的串转换为数值
入口参数：字符串指针
返回值：成功，返回数
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
功能：将数串转换为相应的字符串
入口参数：字符串str
返回值：返回转换的结果；
----------------------------------------------------------------------------*/
CString CRsaA::Ip2os(CString str)
{
	int strlen=str.GetLength(),quotient=0,remainder=0;
	unsigned long num=0,temp=0;
	unsigned int k=1;
	CString strResult;

	for(int i=strlen;i>0;i--)  //得到相应的数字串,存放在num中
	{
		temp = (str.GetAt(i-1) - '0');
			num += temp*k;

		k *= 10;
	}

	//采用模除的方式,求得相应的十六进制数
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
功能：产生RSA秘钥对
入口参数：存放结果的字符串地址 
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::GenKeys(CString& pk,CString& sk,CString& R)
{
	byteint m_p,m_q,m_R,m_Rvalue,m_PK,m_SK;
	SetZero(m_p);      //对大数变量进行清零初始化
	SetZero(m_q);
    SetZero(m_R);
    SetZero(m_Rvalue);
    SetZero(m_PK);
    SetZero(m_SK);

	Mdata();         //生成比较数表
	//AfxMessageBox("开始计算质数P...");
	Prime(m_p);        //生成素数p q
	//AfxMessageBox("开始计算质数Q...");
	Prime(m_q);

	//AfxMessageBox("开始计算模R...");
	ComputingR(m_p,m_q,m_R); //计算模R
	//AfxMessageBox("开始计算模r");
	ComputingRvalue(m_p,m_q,m_Rvalue);  //计算r
	//AfxMessageBox("开始计算秘钥SK,PK");
	ComputingPK(m_Rvalue,m_PK,m_SK);    // Generate PK and SK
	
	//CGenKeyBusyDlg dlg1;
	//g1.DoModal();
	R=PrtInt(m_R);
	pk=PrtInt(m_PK);
	sk=PrtInt(m_SK);
	return ;

}

/*---------------------------------------------------------------------------
功能：实现加密功能接口
入口参数：明文字符串source，模字符串R，秘钥字符串key，结果字符串数组result
返回值：无
----------------------------------------------------------------------------*/
int CRsaA::RsaEncrypt(CString& source,const char *key,const char *R,CStringArray& result)
{
	unsigned char* pstr;
	int j;//sourcelen,j;
	byteint m_key,m_R,desti,aa;
	SetZero(desti);                         //将大数变量清零初始化
	SetZero(aa);
	//SetZero(bb);
	SetZero(m_key);
	SetZero(m_R);

	pstr = (unsigned char*)(LPCTSTR)source; //得到字符串数据的指针
	j = source.GetLength()/4;               //得到数组的元素个数

	result.SetSize(j,1);
	Getinput(m_key,key);                    //将字符串转换为大数类型
	Getinput(m_R,R);
	
	for(int i=0;i<j;i++)
	{
		Getinput1(desti,Os2ip(pstr));       //将四个字节的输入转换为大数类型数值
		RsaDo(desti,m_R,m_key,aa);          //进行加密运算
		result.SetAt(i,PrtInt(aa));         //将结果存放到数组中
		SetZero(desti);  SetZero(aa);
		pstr += 4;
	}
	return j;
}

/*---------------------------------------------------------------------------
功能：实现解密功能接口
入口参数：密文字符串数组source，秘钥字符串sk，模字符串R，
返回值：结果字符串数组result
----------------------------------------------------------------------------*/
CString CRsaA::RsaDecrypt(CStringArray& source,const char* sk,const char* R)
{
	int index=0;
	CString result;
	byteint m_sk,m_r,desti,aa;
	SetZero(m_sk);  SetZero(m_r); SetZero(desti); SetZero(aa);  //SetZero(bb);

	index=source.GetSize();   //得到数组的元素个数
	Getinput(m_sk,sk);        //将字符串转换为大数类型
	Getinput(m_r,R);

	for(int i=0;i<index;i++)
	{
		Getinput(desti,source.GetAt(i));   //将加密结果转换为大数类型
		RsaDo(desti,m_r,m_sk,aa);          //解密运算
		result += Ip2os(PrtInt(aa));       //组合初始明文
		SetZero(aa);  SetZero(desti);
	}

	return result;        //返回明文串
}

/*---------------------------------------------------------------------------
功能：生成一个秘钥存贮文件
入口参数：无
返回值：无
----------------------------------------------------------------------------*/
void CRsaA::GenKeysTable()
{
	CStringArray RArray,SKArray,PKArray;
	CString r,pk,sk;
	int j=1,i;      //参数j表示产生的秘钥对的个数
	unsigned char strlength;
	//设置数组的元素个数
	RArray.SetSize(j,1);	SKArray.SetSize(j,1);	PKArray.SetSize(j,1);
	
	/*-----------------------------------------------------------------------
	文件格式为：
	长度   秘钥   长度   秘钥......
	----   ----   ----   ----
	1byte  nbyte  1byte  nbyte       (中间无空格,R,SK,PK)
	*/
	CFile file;

	for(i=0;i<j;i++)
	{
		GenKeys(pk,sk,r);  //循环产生秘钥
		RArray.SetAt(i,r); SKArray.SetAt(i,sk); PKArray.SetAt(i,pk);		
	}

	//if(file.Open("c:\\key.txt",CFile::modeCreate|CFile::modeReadWrite)==0)
	if(file.Open("key.txt",CFile::modeCreate|CFile::modeReadWrite)==0)
	{
		AfxMessageBox("open file error!");  //打开文件失败
		return;
	}
	

	for(i=0;i<j;i++)
	{                //循环写入结果
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
	file.Read(&strlen1,1);  //读出R长度
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //读出R
	r=pbuffer;
	delete pbuffer;

	file.Read(&strlen1,1);  //读出SK长度
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //读出SK
	sk=pbuffer;
	delete pbuffer;

	file.Read(&strlen1,1);  //读出PK长度
	len = (int)strlen1;

	pbuffer = new char[len+1];
	pbuffer[len]='\0';
	file.Read(pbuffer,len);  //读出PK
	pk=pbuffer;
	delete pbuffer;

	file.Close();
}	