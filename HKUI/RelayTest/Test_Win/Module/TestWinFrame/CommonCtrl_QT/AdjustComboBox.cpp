#include "AdjustComboBox.h"
#include<QAbstractItemView>


CAdjustComboBox::CAdjustComboBox(QWidget *parent):
QComboBox(parent)
{
}

void CAdjustComboBox::adjustItemWidth()
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
	setFixedWidth(max_len*pt_val*1.67+ 6);
}

long CAdjustComboBox::GetIndexByString(QString strText)
{
	QString strCurItemText;

	for(int idx=0;	idx < this->count();idx++)
	{
		strCurItemText = itemText(idx);

		if (strCurItemText == strText)
		{
			return idx;
		}	
	}

	return 0;
}