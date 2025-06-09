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
		T data;//值
		XStackNode* next;//指向下一个节点的指针
	};

private:
	unsigned int m_nLength;
        XStackNode* node;//临时节点
        XStackNode* m_pHeadNode;//尾结点

public:
	CXStack()//初始化
	{
		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}

	unsigned int length()//栈元素的个数
	{
		return m_nLength;
	}

	void push(T x)//入栈
	{
                node=new XStackNode();
		node->data=x;
		node->next=m_pHeadNode;//把node变成头节点
		m_pHeadNode=node;
		++m_nLength;
	}

	bool isEmpty()//判断栈是否为空
	{
		return m_nLength==0;
	}
	void pop()//出栈
	{
		if(isEmpty()) return;
		node=m_pHeadNode;
		m_pHeadNode=m_pHeadNode->next;//头节点变成它的下一个节点
		delete(node);//删除头节点
		--m_nLength;
	}

	T top()//获得栈顶元素
	{
		if(!isEmpty())
			return m_pHeadNode->data;
	}

	void clear()//清空栈
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
		T *data;//值
		XStackNode* next;//指向下一个节点的指针
	};

private:
	unsigned int m_nLength;
        XStackNode* node;//临时节点
        XStackNode* m_pHeadNode;//尾结点

public:
	CXStackP()//初始化
	{
		node=NULL;
		m_pHeadNode=NULL;
		m_nLength=0;
	}

	unsigned int length()//栈元素的个数
	{
		return m_nLength;
	}

	void push(T *x)//入栈
	{
                node=new XStackNode();
		node->data=x;
		node->next=m_pHeadNode;//把node变成头节点
		m_pHeadNode=node;
		++m_nLength;
	}

	bool isEmpty()//判断栈是否为空
	{
		return m_nLength==0;
	}
        bool IsEmpty()//判断栈是否为空
        {
                return m_nLength==0;
        }

	T* pop()//出栈
	{
		if(isEmpty()) 
			return NULL;

		node=m_pHeadNode;
		T *data = node->data;
		m_pHeadNode=m_pHeadNode->next;//头节点变成它的下一个节点
		delete(node);//删除头节点
		--m_nLength;

		return data;
	}

	T* top()//获得栈顶元素
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

	void clear()//清空栈
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
