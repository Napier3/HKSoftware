// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XSTACK_H__)
#define _XSTACK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class T>
class CXStack
{
private:
	class XStackNode
	{
	public:
		XStackNode():next(NULL){}
		T data;//ֵ
		XStackNode* next;//ָ����һ���ڵ��ָ��
	};

private:
	unsigned int m_nLength;
        XStackNode* node;//��ʱ�ڵ�
        XStackNode* m_pHeadNode;//β���

public:
	CXStack()//��ʼ��
	{
		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}

	unsigned int length()//ջԪ�صĸ���
	{
		return m_nLength;
	}

	void push(T x)//��ջ
	{
                node=new XStackNode();
		node->data=x;
		node->next=m_pHeadNode;//��node���ͷ�ڵ�
		m_pHeadNode=node;
		++m_nLength;
	}

	bool isEmpty()//�ж�ջ�Ƿ�Ϊ��
	{
		return m_nLength==0;
	}
	void pop()//��ջ
	{
		if(isEmpty()) return;
		node=m_pHeadNode;
		m_pHeadNode=m_pHeadNode->next;//ͷ�ڵ���������һ���ڵ�
		delete(node);//ɾ��ͷ�ڵ�
		--m_nLength;
	}

	T top()//���ջ��Ԫ��
	{
		if(!isEmpty())
			return m_pHeadNode->data;
	}

	void clear()//���ջ
	{
		while(m_pHeadNode!=NULL)
		{
			node=m_pHeadNode;
			m_pHeadNode=m_pHeadNode->next;
			delete(node);
		}

		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}
};


template<class T>
class CXStackP
{
private:
	class XStackNode
	{
	public:
		XStackNode():next(NULL){}
		T *data;//ֵ
		XStackNode* next;//ָ����һ���ڵ��ָ��
	};

private:
	unsigned int m_nLength;
        XStackNode* node;//��ʱ�ڵ�
        XStackNode* m_pHeadNode;//β���

public:
	CXStackP()//��ʼ��
	{
		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}

	unsigned int length()//ջԪ�صĸ���
	{
		return m_nLength;
	}

	void push(T *x)//��ջ
	{
                node=new XStackNode();
		node->data=x;
		node->next=m_pHeadNode;//��node���ͷ�ڵ�
		m_pHeadNode=node;
		++m_nLength;
	}

	bool isEmpty()//�ж�ջ�Ƿ�Ϊ��
	{
		return m_nLength==0;
	}
        bool IsEmpty()//�ж�ջ�Ƿ�Ϊ��
        {
                return m_nLength==0;
        }

	T* pop()//��ջ
	{
		if(isEmpty()) 
			return NULL;

		node=m_pHeadNode;
		T *data = node->data;
		m_pHeadNode=m_pHeadNode->next;//ͷ�ڵ���������һ���ڵ�
		delete(node);//ɾ��ͷ�ڵ�
		--m_nLength;

		return data;
	}

	T* top()//���ջ��Ԫ��
	{
		if(isEmpty())
		{
			return NULL;
		}
		else
		{
			return m_pHeadNode->data;
		}
	}

	void clear()//���ջ
	{
		while(m_pHeadNode!=NULL)
		{
			node=m_pHeadNode;
			m_pHeadNode=m_pHeadNode->next;
			delete(node);
		}

		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}

	void Push(T *x)
	{
		push(x);
	}

	T* Pop()
	{
		return pop();
	}

	BOOL HasMoreElements()
	{
		return (m_nLength > 0);
	}

	T* NextTop()
	{
		if (m_pHeadNode == NULL)
		{
			return NULL;
		}

		if (m_pHeadNode->next == NULL)
		{
			return NULL;
		}

		return m_pHeadNode->next->data;
	}

	void Pop2Push(T *x)
	{
		T *p = NULL;

		if (m_nLength >= 2) 
		{
			p = pop();
			delete p;
			p = pop();
			delete p;
			push(x);
		}
		else
		{
			push(x);	
		}
	}

	void Empty()
	{
		clear();
	}

	T* Peek()
	{
		return top();
	}
};

#endif // !defined(_XSTACK_H__)
