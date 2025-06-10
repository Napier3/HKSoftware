#ifndef ScrollComboBox_H
#define ScrollComboBox_H

#include "ScrollListView.h"
#include <QComboBox>
#include <QStandardItemModel>

class QScrollComboBox : public QComboBox
{
	Q_OBJECT
private:
	QScrollListView* m_pListView;
	QStandardItemModel* m_pModel;
	long m_nLastIndex;
	bool m_bIsScrolling;
	bool m_bFirstHidePopup;
	bool m_bIgnoreFirstHidePopup;//忽略第一次隐藏Popup,表格中双击表格单元格创建QScrollComboBox对象时,直接显示Popup会自动调用hidePopup
	
public:
	explicit QScrollComboBox(QWidget* pParent = NULL,bool bwidthflag=true);
	virtual ~QScrollComboBox();

	bool IsScrolling() { return m_bIsScrolling; }
	void SetIgnoreFirstHidePopup(bool bIgnore){ m_bIgnoreFirstHidePopup = bIgnore;}//20220428 zhouhj 表格中双击表格单元格创建QScrollComboBox对象时使用
	void SetBoxSize(long nFontSize = 0, long nItemSize = 0);
	void SetDefaultVisibleItems();
	void SetCoboboxVertScrollWidth(long nComBoxVertWidth,long nHeights);

	void setFixedWidth_All(long nComboxWidth,long nListView);
	//如果后期需要用到tip来显示项的全部字符串,则启用该函数
	//virtual void addItem(const QString &text, const QVariant &userData = QVariant());

protected:
	void mousePressEvent(QMouseEvent *ev);
	virtual void hidePopup();
//	void mouseMoveEvent(QMouseEvent *event);
//	void mouseReleaseEvent(QMouseEvent *event);
public slots:
	void slot_IndexChanged(int index);

};

void ComboBox_SetSize(long nFontSize, long nItemSize, QComboBox *pComboBox);
extern long Global_GetComBoxItemHeight();//获取Combox控件中单个Item高度
extern QFont *g_pSttGlobalFont; 

#endif//!ScrollComboBox_H
