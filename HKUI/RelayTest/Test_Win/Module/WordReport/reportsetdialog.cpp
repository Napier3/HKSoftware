#include "reportsetdialog.h"

ReportSetDialog::ReportSetDialog(reportSetPara para,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_reportsetpara = para;
	init();
	connect(ui.treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
	connect(ui.pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_pbn_OkClicked()));
	connect(ui.pbn_Cancle,SIGNAL(clicked()),this,SLOT(slot_pbn_CancleClicked()));
}

ReportSetDialog::~ReportSetDialog()
{

}

void ReportSetDialog::init()
{
	ui.treeWidget->clear();//初始化树形控件
	ui.treeWidget->expandAll();
	ui.treeWidget->setHeaderLabel(tr("内容选择"));
	//定义第一个树形组
	group1 = new QTreeWidgetItem(ui.treeWidget);
	group1->setText(0,tr("测试对象信息"));//树形控件显示的文本信息
	group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	group1->setExpanded(true);
	
	//第一组子项
	subItem11 = new QTreeWidgetItem(group1);
	subItem11->setText(0,tr("变电站信息"));//树形控件显示的文本信息
	subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelTransStationInfo)
	{
		subItem11->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem11->setCheckState(0,Qt::Unchecked);
	}

	subItem12 = new QTreeWidgetItem(group1);
	subItem12->setText(0,tr("装置信息"));//树形控件显示的文本信息
	subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelDeviceInfo)
	{
		subItem12->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem12->setCheckState(0,Qt::Unchecked);
	}

	subItem13 = new QTreeWidgetItem(group1);
	subItem13->setText(0,tr("额定值"));//树形控件显示的文本信息
	subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelRating)
	{
		subItem13->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem13->setCheckState(0,Qt::Unchecked);
	}

	subItem14 = new QTreeWidgetItem(group1);
	subItem14->setText(0,tr("测试设备信息"));//树形控件显示的文本信息
	subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelTestDeviceInfo)
	{
		subItem14->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem14->setCheckState(0,Qt::Unchecked);
	}

	updateParentItem(subItem11);

	//定义第二个树形组
	group2 = new QTreeWidgetItem(ui.treeWidget);
	group2->setText(0,tr("试验参数"));//树形控件显示的文本信息
	group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	group2->setExpanded(true);
	
	//第二组子项
	subItem21 = new QTreeWidgetItem(group2);
	subItem21->setText(0,tr("试验名称"));//树形控件显示的文本信息
	subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelTestName)
	{
		subItem21->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem21->setCheckState(0,Qt::Unchecked);
	}

	subItem22 = new QTreeWidgetItem(group2);
	subItem22->setText(0,tr("通用参数"));//树形控件显示的文本信息
	subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelCommonPara)
	{
		subItem22->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem22->setCheckState(0,Qt::Unchecked);
	}

	subItem23 = new QTreeWidgetItem(group2);
	subItem23->setText(0,tr("整定值"));//树形控件显示的文本信息
	subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelMarkPara)
	{
		subItem23->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem23->setCheckState(0,Qt::Unchecked);
	}
	
	subItem24 = new QTreeWidgetItem(group2);
	subItem24->setText(0,tr("开关量"));//树形控件显示的文本信息
	subItem24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelSwitchPara)
	{
		subItem24->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem24->setCheckState(0,Qt::Unchecked);
	}
	updateParentItem(subItem21);

	//定义第三个树形组
	group3 = new QTreeWidgetItem(ui.treeWidget);
	group3->setText(0,tr("测试结果"));//树形控件显示的文本信息
	group3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	group3->setExpanded(true);
	
	//第三组子项
	subItem31 = new QTreeWidgetItem(group3);
	subItem31->setText(0,tr("测试项参数"));//树形控件显示的文本信息
	subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelTestItemPara)
	{
		subItem31->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem31->setCheckState(0,Qt::Unchecked);
	}

	subItem32 = new QTreeWidgetItem(group3);
	subItem32->setText(0,tr("测试项结果"));//树形控件显示的文本信息
	subItem32->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);//设置树形控件子项的属性
	if (m_reportsetpara.bSelTestItemResult)
	{
		subItem32->setCheckState(0,Qt::Checked);
	}
	else
	{
		subItem32->setCheckState(0,Qt::Unchecked);
	}
	updateParentItem(subItem31);
	ui.lne_ReportTitle->setText(m_reportsetpara.strReportTitle);
	ui.lne_TransStationName->setText(m_reportsetpara.strTransStationName);
	ui.lne_TransStationAddress->setText(m_reportsetpara.strTransStationAddress);
	ui.lne_ReturnCircuitName->setText(m_reportsetpara.strReturnCircuitName);
	ui.lne_ReturnCircuitAddress->setText(m_reportsetpara.strReturnCircuitAddress);
	ui.lne_TestPersionName->setText(m_reportsetpara.strTestPersionName);

	ui.lne_DeviceTestedName->setText(m_reportsetpara.strDeviceTestedName);
	ui.lne_DeviceTestedID->setText(m_reportsetpara.strDeviceTestedID);
	ui.lne_DeviceTestedAddress->setText(m_reportsetpara.strDeviceTestedAddress);
	ui.lne_Manufacturer->setText(m_reportsetpara.strManufacturer);
	ui.lne_SerialNumber->setText(m_reportsetpara.strSerialNumber);
	ui.lne_CustomOrderID->setText(m_reportsetpara.strCustomOrderID);
	ui.lne_AddInfo->setText(m_reportsetpara.strAddInfo);
}

void ReportSetDialog::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem* parent = item->parent();
	if (parent == NULL)
	{
		return;
	}
	int selectedCount = 0;
	int childCount = parent->childCount();
	for (int i = 0; i<childCount; i++)//判断有多少个子项被选中
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			selectedCount ++;
		}
	}
	if (selectedCount<=0)								//如果没有子项被选中，父项设置为未选中状态
	{
		parent->setCheckState(0,Qt::Unchecked);
	}
	else if (selectedCount>0 &&selectedCount<childCount)//如果有部分子项没有被选中，父项设置为部分选中状态，即用灰色显示
	{
		parent->setCheckState(0,Qt::PartiallyChecked);
	}
	else if (selectedCount == childCount)				//如果子项全部被选中，父项则设置为选中状态
	{
		parent->setCheckState(0,Qt::Checked);
	}
}

void ReportSetDialog::treeItemChanged(QTreeWidgetItem* item,int column)
{
	if (Qt::Checked == item->checkState(0))
	{
		int count = item->childCount();//返回子项的个数
		if (count>0)
		{
			for (int i = 0;i<count;i++)
			{
				item->child(i)->setCheckState(0,Qt::Checked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
	else if (Qt::Unchecked == item->checkState(0))
	{
		int count = item->childCount();
		if (count>0)
		{
			for (int i = 0; i<count;i++)
			{
				item->child(i)->setCheckState(0,Qt::Unchecked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
}

void ReportSetDialog::slot_pbn_OkClicked()
{
	if (group1->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestObject = false;
	}
	else
	{
		m_reportsetpara.bSelTestObject = true;
	}
	if (subItem11->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTransStationInfo = false;
	}
	else
	{
		m_reportsetpara.bSelTransStationInfo = true;
	}
	if (subItem12->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelDeviceInfo = false;
	}
	else
	{
		m_reportsetpara.bSelDeviceInfo = true;
	}
	if (subItem13->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelRating = false;
	}
	else
	{
		m_reportsetpara.bSelRating = true;
	}
	if (subItem14->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestDeviceInfo = false;
	}
	else
	{
		m_reportsetpara.bSelTestDeviceInfo = true;
	}
	if (group2->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestPara = false;
	}
	else
	{
		m_reportsetpara.bSelTestPara = true;
	}
	if (subItem21->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestName = false;
	}
	else
	{
		m_reportsetpara.bSelTestName = true;
	}
	if (subItem22->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelCommonPara = false;
	}
	else
	{
		m_reportsetpara.bSelCommonPara = true;
	}
	if (subItem23->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelMarkPara = false;
	}
	else
	{
		m_reportsetpara.bSelMarkPara = true;
	}
	if (subItem24->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelSwitchPara = false;
	}
	else
	{
		m_reportsetpara.bSelSwitchPara = true;
	}
	if (group3->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestResult = false;
	}
	else
	{
		m_reportsetpara.bSelTestResult = true;
	}
	if (subItem31->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestItemPara = false;
	}
	else
	{
		m_reportsetpara.bSelTestItemPara = true;
	}
	if (subItem32->checkState(0) == Qt::Unchecked)
	{
		m_reportsetpara.bSelTestItemResult = false;
	}
	else
	{
		m_reportsetpara.bSelTestItemResult = true;
	}
	m_reportsetpara.strReportTitle = ui.lne_ReportTitle->text();
	m_reportsetpara.strTransStationName = ui.lne_TransStationName->text();
	m_reportsetpara.strTransStationAddress = ui.lne_TransStationAddress->text();
	m_reportsetpara.strReturnCircuitName = ui.lne_ReturnCircuitName->text();
	m_reportsetpara.strReturnCircuitAddress = ui.lne_ReturnCircuitAddress->text();
	m_reportsetpara.strTestPersionName = ui.lne_TestPersionName->text();

	m_reportsetpara.strDeviceTestedName = ui.lne_DeviceTestedName->text();
	m_reportsetpara.strDeviceTestedID = ui.lne_DeviceTestedID->text();
	m_reportsetpara.strDeviceTestedAddress = ui.lne_DeviceTestedAddress->text();
	m_reportsetpara.strManufacturer = ui.lne_Manufacturer->text();
	m_reportsetpara.strSerialNumber = ui.lne_SerialNumber->text();
	m_reportsetpara.strCustomOrderID = ui.lne_CustomOrderID->text();
	m_reportsetpara.strAddInfo = ui.lne_AddInfo->text();

	emit sig_ReportSetParaOkClicked(m_reportsetpara);

	close();
}

void ReportSetDialog::slot_pbn_CancleClicked()
{
	close();
}