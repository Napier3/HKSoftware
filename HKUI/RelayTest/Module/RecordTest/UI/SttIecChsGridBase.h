#ifndef SttIecChsGridBase_H
#define SttIecChsGridBase_H

#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/System/TickCount32.h"

class CSttIecChsGridBase : public QExBaseListGridBase
{
public:
	CSttIecChsGridBase(QWidget* pparent);
	virtual ~CSttIecChsGridBase();
	
	static CString g_strEmptyString;

public:
	virtual void ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision = -1);
	virtual void UpdateAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID);
	virtual void ShowAttrValue(CDvmValue *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision = -1);
	virtual void UpdateAttrValue(CDvmValue *pData, int nRow, int nCol, const CString &strAttrID);
	virtual void UpdateDatas();
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	virtual CDataType* FindDataType(const CString &strDataType);
	virtual void Show_StaticDoubleString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString,long nPrecision);
	virtual void Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);//与之前数值比较,如有改变,则改变颜色为红色,否则为黑色

	void SetItemPic_RefCh(int nRow,int nCol,BOOL bUsePic = TRUE);//设置表格参考通道图片,参数3为是否使用图片,可用于清除图片
	void LoadRefChPic();

protected:
	virtual void mouseReleaseEventBase(QMouseEvent *);
	virtual CExBaseList* GetCurrCapDevice();
	QIcon  m_oRefChPic_Icon;
	CTickCount32 m_oTickCount;
};

#endif // SttIecChsGridBase_H
