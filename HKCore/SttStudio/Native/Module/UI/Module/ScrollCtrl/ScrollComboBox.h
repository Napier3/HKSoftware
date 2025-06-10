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
	bool m_bIgnoreFirstHidePopup;//���Ե�һ������Popup,�����˫�����Ԫ�񴴽�QScrollComboBox����ʱ,ֱ����ʾPopup���Զ�����hidePopup
	
public:
	explicit QScrollComboBox(QWidget* pParent = NULL,bool bwidthflag=true);
	virtual ~QScrollComboBox();

	bool IsScrolling() { return m_bIsScrolling; }
	void SetIgnoreFirstHidePopup(bool bIgnore){ m_bIgnoreFirstHidePopup = bIgnore;}//20220428 zhouhj �����˫�����Ԫ�񴴽�QScrollComboBox����ʱʹ��
	void SetBoxSize(long nFontSize = 0, long nItemSize = 0);
	void SetDefaultVisibleItems();
	void SetCoboboxVertScrollWidth(long nComBoxVertWidth,long nHeights);

	void setFixedWidth_All(long nComboxWidth,long nListView);
	//���������Ҫ�õ�tip����ʾ���ȫ���ַ���,�����øú���
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
extern long Global_GetComBoxItemHeight();//��ȡCombox�ؼ��е���Item�߶�
extern QFont *g_pSttGlobalFont; 

#endif//!ScrollComboBox_H
