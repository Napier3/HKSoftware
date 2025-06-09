#ifndef CHMAPSGRID_H
#define CHMAPSGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/SttCmd/SttChMaps.h"
#include "QChMapsAnalogQuickGrid.h"

#define CHMAPS_GRID_COLS		4
#define CHMAPS_GRID_ANALOG      1
#define CHMAPS_GRID_WEEK        3

class CChMapsGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CChMapsGrid(CSttChMaps *pChMaps, QWidget* pparent);
	virtual ~CChMapsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	CSttChMaps* m_oSttChMaps;

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	//编辑处理函数
	static void EndEditCell_ChMapsString (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	void SendEditCellHasChanged(int nRow, int nCol, CString strText);
signals:
	void sig_AnalogUEndEditCellHasChanged(CSttChMaps *pSttChMaps);//若修改第一列电压映射状态，发送信号，刷新通道映射快捷设置模拟量电压表
	void sig_AnalogIEndEditCellHasChanged(CSttChMaps *pSttChMaps);//若修改第一列电流映射状态，发送信号，刷新通道映射快捷设置模拟量电压表
	void sig_WeakEndEditCellHasChanged(CSttChMaps *pSttChMaps);//若修改第三列通道映射状态，发送信号，刷新通道映射快捷设置电压表

public slots:
	void slot_UpdateDefaultMaps(long nType, int nMoudleTag, int nGroupIndex, int nChBeginIndex,int nselect, bool bIsAppend);
};

#endif // CHMAPSGRID_H
