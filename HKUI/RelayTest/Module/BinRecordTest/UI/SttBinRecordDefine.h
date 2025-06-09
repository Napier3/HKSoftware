#ifndef QSTTBINRECORDDEFINE_H
#define QSTTBINRECORDDEFINE_H

#define STT_BINRECORD_ID_CHANNELINFORMATION                 "ChannelInformation"     //通道信息
#define STT_BINRECORD_ID_MODULE								"Module"				 //插件信息
#define STT_BINRECORD_ID_CHANNELNAME						"ChannelName"            //通道名称
#define STT_BINRECORD_ID_CHANGTYPE							"ChAngType"				 //相别
#define STT_BINRECORD_ID_RECORDTYPE							"RecordType"             //记录类型
#define STT_BINRECORD_ID_MEASGEAR							"MeasGear"               //档位
#define STT_BINRECORD_ID_CLAMPRATE							"ClampRate"              //夹钳比率
#define STT_BINRECORD_ID_THRESHOLDS							"Thresholds"             //门槛值
#define STT_BINRECORD_ID_PRIMVALUE							"PrimValue"              //一次侧
#define STT_BINRECORD_ID_SECONDVALUE						"SecondValue"            //二次侧
#define STT_BINRECORD_ID_RECORDTIMETYPE						"RecordTimeType"         //记录时长类型(0-全部 1-自定义)
#define STT_BINRECORD_ID_CUSTOMIZETIME						"CustomizeTime"          //自定义记录时长
#define STT_BINRECORD_ID_BINRECORDTYPE						"BinRecordType"          //开关量通道类型(0-按全部 1-按插件)
#define STT_BINRECORD_ID_RECORDALL							"RecordAll"              //按全部(1-排列在最前 0-排列在最后)
#define STT_BINRECORD_ID_RECORDPLUG							"RecordPlug"             //按插件（0-主板插件 1-扩展插件）
#define STT_BINRECORD_ID_DISPLAYTYPE						"DisplayType"            //显示方式类型(0-一次 1-二次)
#define STT_BINRECORD_ID_DEFAULTSAVEPATH					"DefaultSavePath"        //默认保存路径
#define STT_BINRECORD_ID_BINRECORDFILENAME					"BinRecordFileName"      //文件名称
#define STT_BINRECORD_ID_RECORDTRIGGERTYPE					"RecordTriggerType"      //录波触发方式类型
#define STT_BINRECORD_ID_RECORDTRIGGERHOUR					"RecordTriggerHour"      //GPS/B码时
#define STT_BINRECORD_ID_RECORDTRIGGERMINUTE				"RecordTriggerMinute"    //GPS/B码分
#define STT_BINRECORD_ID_RECORDTRIGGERSECOND				"RecordTriggerSecond"    //GPS/B码秒


#define STT_BINRECORD_ID_ETYPE								"EType"					//记录类型
#define STT_BINRECORD_ID_ETYPEID							"ETypeID"				//记录类型ID
#define STT_BINRECORD_ID_INVALID							"invalid"				//无效
#define STT_BINRECORD_ID_VOL								"Vol"					//电压
#define STT_BINRECORD_ID_CUR								"Cur"					//电流
#define STT_BINRECORD_ID_BINPASSIVE							"BinPassive"			//开关量无源
#define STT_BINRECORD_ID_BINACTIVE							"BinActive"				//开关量有源
#define STT_BINRECORD_ID_VOLTGEAR							"VoltGear"				//电压档位
#define STT_BINRECORD_ID_VOLTGEARID							"VoltGearID"			//电压档位ID
#define STT_BINRECORD_ID_CURGEAR							"CurGear"				//电流档位
#define STT_BINRECORD_ID_CURGEARID							"CurGearID"				//电流档位ID
#define STT_BINRECORD_ID_VOLONE								"VolOne"				//电压档位1
#define STT_BINRECORD_ID_VOLTWO								"VolTwo"				//电压档位2
#define STT_BINRECORD_ID_VOLTHREE							"VolThree"				//电压档位3
#define STT_BINRECORD_ID_VOLFOUR							"VolFour"				//电压档位4
#define STT_BINRECORD_ID_VORFIVE							"VorFive"				//电压档位5
#define STT_BINRECORD_ID_CURONE								"CurOne"				//电流档位1
#define STT_BINRECORD_ID_CURTWO								"CurTwo"				//电流档位2
#define STT_BINRECORD_ID_CURTHREE							"CurThree"				//电流档位3
#define STT_BINRECORD_ID_CURFOUR							"CurFour"				//电流档位4
#define STT_BINRECORD_ID_CURFIVE							"CurFive"				//电流档位5
#define STT_BINRECORD_ID_CHANGTYPE							"ChAngType"				//相位
#define STT_BINRECORD_ID_CHANGTYPEID						"ChAngTypeID"			//相位ID
#define STT_BINRECORD_ID_CHANGONE							"ChAngOne"				//---
#define STT_BINRECORD_ID_CHANGTWO							"ChAngTwo"				//A
#define STT_BINRECORD_ID_CHANGTHREE							"ChAngThree"			//B
#define STT_BINRECORD_ID_CHANGFOUR							"ChAngFour"				//C
#define STT_BINRECORD_ID_CHANGFIVE							"ChAngFive"				//零序

#define STT_BINRECORD_ID_STRZERO							"0"						//"0"
#define STT_BINRECORD_ID_STRONE								"1"						//"1"
#define STT_BINRECORD_ID_STRTWO								"2"						//"2"
#define STT_BINRECORD_ID_STRTHREE							"3"						//"3"
#define STT_BINRECORD_ID_STRFOUR							"4"						//"4"
#define STT_BINRECORD_ID_STRFIVE							"5.00"					//"5.00"
#define STT_BINRECORD_ID_STRTEN								"10"					//"10"
#define STT_BINRECORD_ID_STRONEHUNDRED						"100"					//"100"
#define STT_BINRECORD_ID_STRONETHOUSAND						"1000.00"				//"1000.00"


#define STT_BINRECORD_ID_STRSIXHUNDREDV						"600V"					//"600V"
#define STT_BINRECORD_ID_STRONETHOUSANDV					"100V"					//"100V"
#define STT_BINRECORD_ID_STRTENV							"10V"					//"10V"	
#define STT_BINRECORD_ID_STRONEV							"1V"					//"1V"
#define STT_BINRECORD_ID_STRZERODOTONEV						"0.1V"					//"0.1V"	

#define STT_BINRECORD_ID_STRSIXHUNDREDA						"600A"					//"600A"
#define STT_BINRECORD_ID_STRONETHOUSANDA					"100A"					//"100A"
#define STT_BINRECORD_ID_STRTENA							"10A"					//"10A"	
#define STT_BINRECORD_ID_STRONEA							"1A"					//"1A"
#define STT_BINRECORD_ID_STRZERODOTONEA						"0.1A"					//"0.1A"	

#define STT_BINRECORD_ID_STRA								"A"						//"A"	
#define STT_BINRECORD_ID_STRB								"B"						//"B"
#define STT_BINRECORD_ID_STRC								"C"						//"C"
#define STT_BINRECORD_ID_SPACE								"-----"					//空白
#define STT_BINRECORD_ID_dsSV1								"dsSV1"					//"dsSV1"	
#define STT_BINRECORD_ID_ModuleAttrs						"ModuleAttrs"			//"ModuleAttrs"	
#define STT_BINRECORD_ID_ModuleType							"ModuleType"			//"ModuleType"	
#define STT_BINRECORD_ID_Model								"Model"					//"Model"	
#define STT_BINRECORD_ID_ModulePos							"ModulePos"				//"ModulePos"	
#define STT_BINRECORD_ID_SwitchIn							"SwitchIn"				//"SwitchIn"
#define STT_BINRECORD_ID_SwitchVolt							"SwitchVolt"			//"SwitchVolt"

#define STT_BINRECORD_ID_NZERO								0						//0
#define STT_BINRECORD_ID_NONE								1						//1
#define STT_BINRECORD_ID_NTWO								2						//2
#define STT_BINRECORD_ID_NTHREE								3						//3
#define STT_BINRECORD_ID_NFOUR								4						//4
#define STT_BINRECORD_ID_NFIVE								5						//5
#define STT_BINRECORD_ID_NSIX								6						//6
#define STT_BINRECORD_ID_NSIXDOTTWENTYTHREE					6.23					//6.23
#define STT_BINRECORD_ID_NEIGHT								8						//8
#define STT_BINRECORD_ID_ONEHUNDRED							100						//100
#define STT_BINRECORD_ID_ONETHOUSAND						1000					//1000
#define STT_BINRECORD_ID_TENTHOUSAND						10000					//10000
#define STT_BINRECORD_ID_HUNDREDTHOUSAND					100000					//100000
#define STT_BINRECORD_ID_SIXHUNDREDTHOUSAND					600000					//600000

#define STT_BINRECORD_ID_FSIXHUNDRED						600.0f					//600.0f
#define STT_BINRECORD_ID_FONETHOUSAND						100.0f					//100.0f
#define STT_BINRECORD_ID_FTEN								10.0f					//10.0f
#define STT_BINRECORD_ID_FONE								1.0f					//10.0f
#define STT_BINRECORD_ID_FZERODOTONE						0.1f					//0.1f

#define STT_BINRECORD_ID_FOURTHOUSAND						4000					//4000


#endif