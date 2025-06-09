// AnsiStringPrintf.h: interface for the CAnsiStringPrintf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_AnsiStringPrintf_h__)
#define _AnsiStringPrintf_h__

#include <math.h>
#include <string.h>
#include <stdarg.h>

class CAnsiStringPrintf
{
protected:
	char *m_pchData;
	char *m_lpBufCur;
	
	static const long NUMBER_TBUFFER_LENGTH;
	static const long DOUBLE_MAX_PRECISION;
	
	void Init();
	CAnsiStringPrintf();
	
public:
	CAnsiStringPrintf(char *pDestBuff);
	virtual ~CAnsiStringPrintf();
	void ResetBuffCurr()
	{
		m_lpBufCur = m_pchData;
	}
	
	//缓冲区的数据
#ifndef _PSX_IDE_QT_
    virtual long GetBuffer(VARIANT *pvarString);
	virtual long GetBuffer2(BSTR *pbstr);
#endif

	//缓冲区写方法
	virtual long WriteString(const char *pstrData);
#ifndef _PSX_IDE_QT_
    virtual long WriteString(BSTR &bstrData);
#endif

    virtual long WriteLong(long nVal, long nWidth, bool bFill0);
	virtual long WriteUnsignedLong(unsigned long nVal, long nWidth, bool bFill0);
	virtual long WriteHex(unsigned long nVal, long it, long nWidth, bool bFill0);
	virtual long WriteDouble(double dVal, long nWidth, bool bFill0, long nPrecision);
	virtual long WriteChar(char ch)
	{
		*m_lpBufCur = ch;
		m_lpBufCur += 1;
		return 1;
	}
	virtual long WriteWChar(wchar_t wch)
	{
		if (wch > 0x00FF)
		{
			*m_lpBufCur = ((wch >> 8) & 0xFF);
			m_lpBufCur++;
		}

		*m_lpBufCur = (wch & 0xFF);
		m_lpBufCur++;

		*m_lpBufCur = 0;

		return 2;
	}

	int sprintf(const char* fmt,...);
	
private:	
	typedef enum{
		IT_DECIMAL = 0,    //十进制
		IT_HEX     = 1,    //十六进制
		IT_OCTAL   = 2,    //八进制
		IT_BINARY  = 3,    //二进制
		IT_HEX_LOW = 4     //十六进制
	}INT_TYPE;
	
	//定义扫描机的动作
	typedef enum{
		XO_PAUSE = 0,    //暂停
			XO_CONTINUE = 1    //继续
	}XF_OPERA;
	
	//定义扫描机的状态
	typedef enum{
		XS_SKIP = 0,     //扫描前缀串
		XS_PROC = 1,     //需处理当前格式或前缀串
		XS_FLAG = 2,     //扫描添位符
		XS_WIDTH = 3,    //扫描占宽
		XS_PREC = 4,     //扫描精度
		XS_SIZE= 5,      //扫描整形指示
		XS_TYPE = 6,     //扫描格式符
		XS_TERM = 7      //扫描终止
	}XF_STATUS;   
	
	int _tk_sprintf(char flag,int width,int prec,char size,char type,va_list* parg);	

	//判断是否添位符
	bool s_is_flag(char ch)   
	{  return ((ch == '0' || ch == ' ' || ch == '#')? true : false);	}

	//判断是否是数字
	bool s_is_digit(char ch)  
	{  return   ((ch >= '0' && ch <= '9')? true : false);	}

	//判断是否是整形指示
	bool s_is_size(char ch)    
	{  return ((ch == 'h' || ch == 'l')? true : false);	}
	
	//判断是否是格式符
	bool s_is_type(char ch)    
	{  
		return ((ch == 'c' || ch == 'C' || ch == 'd' || ch == 'u' 
			|| ch == 'x' || ch == 'X' || ch == 'f'|| ch == 's' || ch == 'S'
			|| ch == 'b' || ch == 'B' || ch == 'o' || ch == 'O')? 1 : 0);	
	}
	
};


#endif // !defined(_AnsiStringPrintf_h__)
