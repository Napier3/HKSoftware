#ifndef CHMAPSANALOGQUCIKGRID_H
#define CHMAPSANALOGQUCIKGRID_H

#include "../../../../Module/SttCmd/SttChMaps.h"

#include <QTableWidget>
#include <QComboBox>
#include <QItemDelegate>
#include <QMouseEvent>
#include <QStylePainter>

enum MoudleType{AnalogMoudle_U = 0, AnalogMoudle_I, WeakMoudle_U, WeakMoudle_I};

struct ModuleGroupInfo {
	int moduleNumber;
	int groupNumber;
};

class QCenterComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit QCenterComboBox(QWidget *parent = 0);
	~QCenterComboBox();
	bool QCenterComboBox::eventFilter(QObject *watched, QEvent *event) override;
private:
	bool m_bPopupVisible;
};

class CChMapsAnalogQuickGrid : public QTableWidget
{
	Q_OBJECT
public:
	explicit CChMapsAnalogQuickGrid(int nType = 0, QWidget *parent = 0);
	~CChMapsAnalogQuickGrid();

	void InitGrid(long nType, CSttChMaps *pChMaps);//初始化表格
	void InsertItem(long nType, QStringList strList);
	void InitChMapsState(long nType, CSttChMaps *pChMaps);
	void UpdateComboxIndex(long nType);//根据通道实际情况刷新combox下拉选择index
	QCenterComboBox* NewErrorType();//初始化combox内容
	void ComboxModelStyle(QCenterComboBox *pCombox);//下拉框风格初始化

public:
	QList<QCenterComboBox*> m_pComboBoxList1;
	QList<QCenterComboBox*> m_pComboBoxList2;
	CSttChMaps *m_pSttChMaps;
	QVector<ModuleGroupInfo> m_nModuleVolGroupInfo;
	QVector<ModuleGroupInfo> m_nModuleCurGroupInfo;
	QCenterComboBox* m_pComBox;
	int m_nType;
private:
	QVector<QVector<int>> m_nVolChIsMap;//记录Ua1, Ua2等的通道映射状态(有映射值)
	QVector<QVector<int>> m_nVolChIsMap2;
	QVector<QVector<int>> m_nCurChIsMap;//记录Ia1, Ia2等的通道映射状态
	QVector<QVector<int>> m_nCurChIsMap2;//记录Ia1, Ia2等的通道映射状态

	QVector<int> m_nVolChIsNullNum;//记录电压表前三个软件通道映射都为空的状态
	QVector<int> m_nVolChIsNullNum2;//记录电压表前三组软件通道映射都为空的状态
	QVector<int> m_nCurChIsNullNum;//记录电流表前三个软件通道映射都为空的状态
	QVector<int> m_nCurChIsNullNum2;//记录电流表前三组软件通道映射都为空的状态

signals:
	void sig_ChMapStateIsChanged(long nVolCurrType, int nMoudleTag, int nGroupIndex, int nChBeginIndex, int nselect, bool bIsAppend);
public slots:
	void slot_comboxIndexChanged(QString strText);
	void slot_UpdateAnalogUComboxState(CSttChMaps *pSttChMaps);
	void slot_UpdateAnalogIComboxState(CSttChMaps *pSttChMaps);
};

#endif