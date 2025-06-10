#include "SttReplayAdjustComboBox.h"
#include<QAbstractItemView>


CSttReplayAdjustComboBox::CSttReplayAdjustComboBox(QWidget *parent):
QComboBox(parent)
{
}

void CSttReplayAdjustComboBox::adjustItemWidth()
{
	int max_len=0;
	for(int idx=0;	idx < this->count();idx++)
	{
		if(max_len < this->itemText(idx).length())
		{
			max_len = this->itemText(idx).length();
		}	
	}

	int pt_val = this->font().pointSize();//��ȡ����İ�ֵ
//	this->view()->setFixedWidth(max_len*pt_val*1.67);//���ַ���*ÿ���ַ��Ŀ��(��)*1.67��������

	if (max_len>20)//�����ʾ25�ֽڳ���
	{
		max_len = 20;
	}

	if (max_len < 8)//��С��ʾ8���ֽڳ���
	{
		max_len = 8;
	}

	long nMaxWidth = max_len*pt_val+ 6;
	setFixedWidth(nMaxWidth);
}