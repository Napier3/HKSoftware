#if !defined(AFX_RSAA_H__081D9EE0_1245_11D5_80AC_0000E8810675__INCLUDED_)
#define AFX_RSAA_H__081D9EE0_1245_11D5_80AC_0000E8810675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
// _MSC_VER > 1000
// RsaA.h : header file
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const long  DATALENGTH=350;   //大数类型的长度
const long  MLENGTH=10;       //质数的长度
const long  TESTNUM=30;       //测试质数时的比较的次数
const long  SKLENGTH=4;       //私钥的长度

typedef signed char byteint[DATALENGTH];   //定义大数类型
typedef signed char mtype[MLENGTH];        //定义质数的大数类型


//extern "C" __declspec(dllexport) void RsaAGenKeys(CString& pk,CString& sk,CString& R); //提供给服务器使用的秘钥产生函数
//extern "C" __declspec(dllexport) int RsaAEncrypt(CString& source,const char* key,const char* R,CStringArray& result);//加密
//extern "C" __declspec(dllexport) CString RsaADecrypt(CStringArray& source,const char* sk,const char* R);//解密

/////////////////////////////////////////////////////////////////////////////
// CRsaA command target
//实现RSA算法的类
class CRsaA : public CCmdTarget
{
	DECLARE_DYNCREATE(CRsaA)

	CRsaA();    // protected constructor used by dynamic creation

// 成员函数
private:
	void InitInt(void);                      //基本数据常量的初始化
	int IntValid(byteint validtemp);         //返回大数validtemp的非零位的个数
	int IntCmp(byteint A,byteint B);         //比较大数A和B是否相等
	//自定义类型的基本运算
	void Plus(byteint A,byteint B,byteint C);             //C=A+B
	void Substract(byteint SA,byteint SB,byteint SC);     //SC=SA-SB
	void Multiply(byteint A,byteint B,byteint C);         //C=A*B
	void SetMode(byteint A,byteint B,byteint C,byteint D);//C=A%B
	int PowerMode(byteint A,byteint C,byteint D,signed char flag[400]);//computing A^B mod C-->D
	
	void IntRandom(byteint RandomA,int num);                //随机产生一个大数
	void LoadInt(byteint A,mtype B);                        //将质数类型转换为大数类型
	void TransBi(byteint B,signed char flag[400]);          //将大数B转换为二进制形式
	void Mdata();                                           //产生用于生成质数中进行比较的数
	int Prime(byteint Prm);                                 //产生一个长度为MLENGTH的质数
	int ComputingPK(byteint Rvalue,byteint SK,byteint PK);  //计算公钥PK
	void ComputingR(byteint p,byteint q,byteint R);         //计算模值R
	void ComputingRvalue(byteint p,byteint q,byteint Rvalue); //计算$(r)
	void IntCpy(byteint A1,byteint B1);      //将大数B1的值拷贝到大数A1中
	void SetZero(byteint A);                 //将大数A清零
	CString PrtInt(byteint A);               //将一个大数类型转换为一个CString类型
	int Getinput(byteint result,CString input);             //将字符串转换为对应的大数形式
	int Getinput1(byteint result,unsigned long input);               //将长整形数转换为对应的大数形式
	void RsaDo(byteint source,byteint R,byteint key,byteint desti); //实现加解密
	unsigned long Os2ip(unsigned char* pstr);
	CString Ip2os(CString str);
	
public:
	void GenKeys(CString& pk,CString& sk,CString& R); //提供给服务器使用的秘钥产生函数
	int RsaEncrypt(CString& source,const char* key,const char* R,CStringArray& result);//加密
	CString RsaDecrypt(CStringArray& source,const char* sk,const char* R);//解密
	void GenKeysTable();                             //生成秘钥对文件
	void LoadKeysFromFile(CString& r,CString& sk,CString& pk);

//成员变量	
private:
	byteint ONEVALUE;
	byteint ZEROVALUE;
	byteint TWOVALUE;
	byteint EIGHTVALUE; //O,1,2,8 constant
	
	mtype Model[TESTNUM];  //TESTNUM big number to be compared
	mtype mZEROVALUE,tempModel;  //0 constant
	
	signed char flag[400];
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsaA)
	//}}AFX_VIRTUAL

// Implementation
//protected:
	virtual ~CRsaA();

	// Generated message map functions
	//{{AFX_MSG(CRsaA)
//	afx_msg LONG OnComputing(WPARAM wParam, LPARAM lParam);
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSAA_H__081D9EE0_1245_11D5_80AC_0000E8810675__INCLUDED_)