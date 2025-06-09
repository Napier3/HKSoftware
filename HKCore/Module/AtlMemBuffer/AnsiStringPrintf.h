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
	
	//������������
#ifndef _PSX_IDE_QT_
    virtual long GetBuffer(VARIANT *pvarString);
	virtual long GetBuffer2(BSTR *pbstr);
#endif

	//������д����
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
		IT_DECIMAL = 0,    //ʮ����
		IT_HEX     = 1,    //ʮ������
		IT_OCTAL   = 2,    //�˽���
		IT_BINARY  = 3,    //������
		IT_HEX_LOW = 4     //ʮ������
	}INT_TYPE;
	
	//����ɨ����Ķ���
	typedef enum{
		XO_PAUSE = 0,    //��ͣ
			XO_CONTINUE = 1    //����
	}XF_OPERA;
	
	//����ɨ�����״̬
	typedef enum{
		XS_SKIP = 0,     //ɨ��ǰ׺��
		XS_PROC = 1,     //�账��ǰ��ʽ��ǰ׺��
		XS_FLAG = 2,     //ɨ����λ��
		XS_WIDTH = 3,    //ɨ��ռ��
		XS_PREC = 4,     //ɨ�辫��
		XS_SIZE= 5,      //ɨ������ָʾ
		XS_TYPE = 6,     //ɨ���ʽ��
		XS_TERM = 7      //ɨ����ֹ
	}XF_STATUS;   
	
	int _tk_sprintf(char flag,int width,int prec,char size,char type,va_list* parg);	

	//�ж��Ƿ���λ��
	bool s_is_flag(char ch)   
	{  return ((ch == '0' || ch == ' ' || ch == '#')? true : false);	}

	//�ж��Ƿ�������
	bool s_is_digit(char ch)  
	{  return   ((ch >= '0' && ch <= '9')? true : false);	}

	//�ж��Ƿ�������ָʾ
	bool s_is_size(char ch)    
	{  return ((ch == 'h' || ch == 'l')? true : false);	}
	
	//�ж��Ƿ��Ǹ�ʽ��
	bool s_is_type(char ch)    
	{  
		return ((ch == 'c' || ch == 'C' || ch == 'd' || ch == 'u' 
			|| ch == 'x' || ch == 'X' || ch == 'f'|| ch == 's' || ch == 'S'
			|| ch == 'b' || ch == 'B' || ch == 'o' || ch == 'O')? 1 : 0);	
	}
	
};


#endif // !defined(_AnsiStringPrintf_h__)
