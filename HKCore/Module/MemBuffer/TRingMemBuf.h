#ifndef CTRINGMEMBUG_H
#define CTRINGMEMBUG_H

template <class T>
class CTRingMemBuf
{
private:
	T* m_arrData;//�������

	unsigned int m_nDataCount;
	unsigned int m_nReadPos;
	unsigned int m_nWritePos;

public:
	CTRingMemBuf()
	{
		m_nDataCount = 0;
		m_nReadPos = 0;
		m_nWritePos = 0;
		m_arrData = NULL;
	}
	virtual ~CTRingMemBuf()
	{
		FreeBuff();
	}

public:
	void Create(long nLen);		//����һ��len��Ԫ�ص�T����
	void FreeBuff()
	{
		if (m_arrData != NULL)
		{
			delete m_arrData;
			m_arrData = NULL;
		}
	}
	T GetRead();				//��ȡ��ǰreadָ���Ԫ��
	void Append(T obj);			//��ǰwrite��λ��д��Ԫ��
	long GetDataCount()
	{
		return m_nDataCount;
	}
	long CanRead()
	{
		return (m_nReadPos!= m_nWritePos);
	}
	void Clear()
	{
		m_nReadPos = m_nWritePos;
//		m_nCurCount = 0;
	}
};

template <class T>
void CTRingMemBuf<T>::Create(long nLen)
{
	FreeBuff();
	m_arrData = new T[nLen];

	//for (int i = 0; i < nLen; i++)
	//{
	//	m_arrData[i] = 0;
	//}

	m_nDataCount = nLen;
}

template <class T>
T CTRingMemBuf<T>::GetRead()
{
	T obj = m_arrData[m_nReadPos];

	if(m_nWritePos > m_nReadPos)
	{
		//��д��λ���ڶ�ȡλ�õĺ�
		m_nReadPos++;
	}
	else if(m_nWritePos < m_nReadPos)
	{
		//��д��λ���ڶ�ȡλ�õ�ǰ��
		if((m_nReadPos + 1) < m_nDataCount)
		{
			m_nReadPos++;
		}
		else
		{
			m_nReadPos = 0;
		}
	}

	return obj;
}

template <class T>
void CTRingMemBuf<T>::Append(T obj)
{
	m_arrData[m_nWritePos] = obj;
	m_nWritePos++;
//	m_nCurCount++;
	if(m_nWritePos == m_nDataCount)
	{
		m_nWritePos = 0;
	}
}

#endif//!CTRINGMEMBUG_H