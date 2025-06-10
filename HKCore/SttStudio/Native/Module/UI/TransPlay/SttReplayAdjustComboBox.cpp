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

	int pt_val = this->font().pointSize();//获取字体的磅值
//	this->view()->setFixedWidth(max_len*pt_val*1.67);//（字符数*每个字符的宽度(磅)*1.67）个像素

	if (max_len>20)//最大显示25字节长度
	{
		max_len = 20;
	}

	if (max_len < 8)//最小显示8个字节长度
	{
		max_len = 8;
	}

	long nMaxWidth = max_len*pt_val+ 6;
	setFixedWidth(nMaxWidth);
}