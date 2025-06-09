#ifndef CharEditMainWidget_H
#define CharEditMainWidget_H

#include <QWidget>
#include <QItemDelegate>
#include "ui_CharEditMainWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "QImpCharactWidget.h"
#include "CharEditWidgetBase.h"

/*  2022-9-5  lijunqing
基础框架，后续对于电能质量等没有特性曲线图的部分，可以将特性曲线功能放到子类，例如QCharEditMainWidget_RElay
*/

class QCharEditMainWidget : public QWidget
{
	Q_OBJECT
public:
	QCharEditMainWidget(QWidget* pParent = NULL);
	virtual ~QCharEditMainWidget();

	Ui::QCharEditMainWidget ui;

public:
	BOOL m_bSetting;
//	CCharacteristic *m_pCurrCharaObj;
//	CCharInterface *m_pInterface;
//	CCharacterArea *m_pCharArea;
//	CCharInterface *m_pInterfacebak;
//	CCharacterArea *m_pCharAreabak;

	QStringList m_PeriodList;
	QStringList m_ErrorPhaseList;
	QList<QComboBox*> m_CmbListParaNo;
	QList<QComboBox*> m_CmbListFaultPha;

	QImpCharactWidget* m_pImpCharactWidget;
//	CString m_strLastCharaID;
	CString m_strCharParasFile;//测试功能对应的特性曲线文件的路径,用于保存

//	int m_nZKCurrentRow;
	BOOL m_bCharChanged;
	CString m_strUI_ID;//界面功能ID

public:
	void UpdateZKFeature(CCharacteristic *pObj,BOOL bSetting);
//	void DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, const CString& strCharLib);
//	void DrawSearchPointPoint(CPoint ptCur, const CString& strCharLib);
//	void DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, CCharacteristic* pChar);
//	void DrawSearchPointPoint(CPoint ptCur, CCharacteristic* pChar);
	void UpdateCharAxisType(const CString& strAxis,BOOL bLockXY);
	void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);
	void AddTestResultPoint(CExBaseList* pValue);//添加测试结果点

	void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据

	//2022-9-3  lijunqing
	void InitCharacteristicsLib(const CString &strUI_ID,const CString &strCharLibFile);//参数1为界面参数功能ID
	void ShowCharacteristics(CCharacteristics *pCharacteristics);
	CString GetCharLibID();
	void UpdateAxisDesc(const CString &strXAxisName, const CString &strYAxisName, 
		const CString &strAxisTitle,CString strUniuX,CString strUnitY);//更新坐标轴描述
	BOOL IsViewTestLines();
	void UI_SetActiveElement(CXDrawElement *pElement);

protected:
	void CreateCharEditWidgetUI_ID(const CString &strUI_ID);

	CCharacteristicLib *m_pCharacteristicsLib;
	QCharEditWidgetBase *m_pCharEditWidget;
//	CString m_strLastCharLibID;

private:
	void InitUI();
	void InitTableWidget();
	void InitCharactWidget();
	void InitConnect();

	void AddCharacter(CCharacteristic *pChar);
	CXDrawList* GetDrawListByID(const CString& strID);
	void RemoveCurrWidget();

signals:
//	void sig_CharChanged(CExBaseObject *pCharacteristic);
	// 	void sig_UpdataCheck(bool, bool, bool);
public slots:
//	void slot_CharChanged();
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic,int bCharChanged);//调用该槽函数可设置参数是否改变
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic);//调用该槽函数,默认参数已改变
	void slot_LeftButtonDown();
};

#endif//!CharEditMainWidget_H