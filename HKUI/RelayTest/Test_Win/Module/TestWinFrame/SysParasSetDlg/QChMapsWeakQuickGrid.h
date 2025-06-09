#ifndef CHMAPSWEAKQUCIKGRID_H
#define CHMAPSWEAKQUCIKGRID_H

#include "../../../../Module/SttCmd/SttChMaps.h"
#include "QChMapsAnalogQuickGrid.h"

#include <QTableWidget>
#include <QComboBox>

class CChMapsWeakQuickGrid : public QTableWidget
{
	Q_OBJECT
public:
	explicit CChMapsWeakQuickGrid(QWidget *parent = 0);
	~CChMapsWeakQuickGrid();

	void InitGrid(CSttChMaps *pChMaps);//初始化表格行列
	void InsertItem(QStringList strList);//插入表格每一项
	void InitChMapsState(CSttChMaps *pChMaps);
	void UpdateComboxIndex();
	QCenterComboBox* NewErrorType();
	void ComboxModelStyle(QCenterComboBox *pCombox);//下拉框风格初始化

	CSttChMaps *m_pSttChMaps;
	QVector<ModuleGroupInfo> m_nModuleGroupInfo;
private:
	QVector<QVector<int>> m_nVolChIsMap;//记录Ua1, Ua2等的通道映射状态(有映射值)
	QVector<QVector<int>> m_nVolChIsMap2;
	QVector<QVector<int>> m_nCurChIsMap;//记录Ia1, Ia2等的通道映射状态
	QVector<QVector<int>> m_nCurChIsMap2;//记录Ia1, Ia2等的通道映射状态
	QVector<int> m_nVolChIsNullNum;//记录弱信号表前三个电压软件通道映射都为空的状态
	QVector<int> m_nVolChIsNullNum2;//记录弱信号表后三个电压软件通道映射都为空的状态
	QVector<int> m_nCurChIsNullNum;//记录弱信号表前三个电流软件通道映射都为空的状态
	QVector<int> m_nCurChIsNullNum2;//记录弱信号表前三个电流软件通道映射都为空的状态

signals:
	void sig_WeakChMapStateIsChanged(long nVolCurrType, int nMoudleTag, int nGroupIndex, int nChBeginIndex, int nselect, bool bIsAppend);
public slots:
	void slot_comboxIndexChanged(QString strText);
	void slot_UpdateWeakComboxState(CSttChMaps *pSttChMaps);
};

#endif