//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysState_Gb.h  CSttSysState_Gb_Gb

#pragma once

#include "SttSysState.h"
#include "SttParas_Gb.h"

class CSttSysState_Gb : public CSttSysState
{
public:
	CSttSysState_Gb();
	CSttSysState_Gb(const CString &strRetType);
	virtual ~CSttSysState_Gb();

	static CXObjectRefBase* New()
	{
		return new CSttSysState_Gb();
	}

//重载函数
public:
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	//2023-9-9
	virtual CSttParas* NewSttParas();
};

/*
<sys-state name="" id="QueryItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data name="" id="ItemPath" data-type="" value="Device$ManulTest"/>
		<items name="" id="" tkid="65535" select="1">
			。。。。。。
			<safety name="接线提示" id="Safety" tkid="65535" select="0">
				<msg type="1"><![CDATA[
【提示人工进行操作的信息】
]]></msg>
				<datas name="" id="">
					<data name="变电站名称" id="Test1" data-type="" unit="" value="220KV晨阳站" format="" remark="" default="220KV晨阳站" reserved="1" time="0"/>
					<data name="主变名称" id="Test2" data-type="" unit="" value="1号主变" format="" remark="" default="1号主变" reserved="1" time="0"/>
					<data name="开关编号" id="Test3" data-type="" unit="" value="110" format="" remark="" default="110" reserved="1" time="0"/>
					<data name="data1" id="data1" data-type="combobox" unit="" value="eligible" format="Eligible" remark="" default="eligible" reserved="1" time="0" />
					<data name="data2" id="data2" data-type="combobox" unit="" value="right" format="Right" remark="" default="" reserved="1" time="0" />
				</datas>
			</safety>
。。。。。。
		</items>
		<data-types name="" id="">
			<data-type name="合格/不合格" id="Eligible">
				<value name="合格" id="eligible" index="1"/>
				<value name="不合格" id="inlegible" index="2"/>
			</data-type>
			<data-type name="正确/不正确" id="Right">
				<value name="正确" id="right" index="1"/>
				<value name="不正确" id="wrong" index="2"/>
			</data-type>
			。。。。。。
		</data-types>
	</paras>
</sys-state>
*/
