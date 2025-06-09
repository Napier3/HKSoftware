#ifndef WORDENGINE_H
#define WORDENGINE_H

#include <QObject>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

class WordEngine : public QObject
{
	Q_OBJECT

public:
	WordEngine(QObject *parent);
	~WordEngine();

	bool openword(QString templatePath,bool bVisable);
	bool close();

    void inserText(QString text);
    void setFontSize(int fontsize);
    void setFontBold(bool flag);
    void setParagraphAlignment(int flag);//0 居中 1：居左 2：居右
    void inserEnter();//插入回车
    void inserTitle(QString text);
    void inserHeading1(QString text);//插入一级标题
	void inserHeading2(QString text);//插入二级标题
    void insertPic(QString picPath);

	//gridflag=true:有边框 gridflag：无边框  
	//表格自动拉伸列flag 0固定  1根据内容调整  2 根据窗口调整
    QAxObject* insertTable(int row,int column,bool gridflag,int flag);
    void setTableAlignment(QAxObject *table,int flag);//0:居中 2：右对齐 3：左对齐
	void setTableRowAlignment(QAxObject *table, int row,int flag);//0:居中 2：右对齐 3：左对齐
    void setTableRowFontBold(QAxObject *table,int row,bool flag);
	void SetTableCellString(QAxObject *table, int row,int column,QString text);
	void SetTableString(QAxObject *table,QList<QStringList> list);
	void setTableColumnWidth(QAxObject *table, int column,int width);
	//合并单元格
	void MergTableCell(QAxObject *table,int startRow,int endRow,int startColumn,int endColumn);
    void moveForEnd();//光标移到末尾
	
private:
	bool m_bOpened;
	QAxWidget *word;
	QAxObject * documents;
	QAxObject * document;
};

#endif // WORDENGINE_H
