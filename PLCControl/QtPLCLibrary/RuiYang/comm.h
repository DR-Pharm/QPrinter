/**********************************************************/
/* 通讯数据 */
/**********************************************************/
//unsigned int == UDINT 4个字节
//int == DINT 4个字节 和long一样是4个字节 
//float == REAL 4个字节 double和longlong是8个字节
//unsigned char = USINT 8位 1个字节
//char == STRING
//char[40] == STRING[40] 8位 1个字节是1个字符占位
//bool == BOOL 1位
//short == INT 2个字节
//short == UINT 2个字节
#define UDINT unsigned int
#define DINT int
#define REAL float
#define USINT unsigned char
#define STRING char
#define INT short
#define UINT short
#define LREAL double

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))

#ifndef _COMM_H_

#define	_COMM_H_

#pragma pack(4)
#define			MAX_PULSE_SERVO		2
typedef struct
{
	UINT		second;
	UINT		minute;
	UINT		hour;
	UINT		day;
	UINT		month;
	UINT		year;
	UINT		weekday;	/*0:Sunday--6:Saturday*/
}DateTimeStructTyp;

typedef struct
{
	UDINT		GroupNo;
	UDINT		GroupIndex;
	REAL		GroupAvg;			//组平均重量,g
	REAL		GroupMax;
	REAL		GroupMin;
	REAL		GroupMaxRatio;
	REAL		GroupMinRatio;
	REAL        GroupWeightDelta;
	UDINT		Tag;				//表格标记
}Displaytyp;

typedef struct
{
	REAL		Weight[20];
	REAL		Avg;
}DisplayWeightTyp;

typedef struct
{
	bool		FeedTrigger;			//胶囊下落检测
	bool		SwingTrigger;			//摆臂位置检测
}Input_typ;


//output
typedef	struct
{
	bool		Reject;					//排废电磁铁
	bool		ChannelSwith;			//胶囊通道切换
	bool		Vaccum;					//真空发生器
	bool		CapGet;					//取料电磁铁
	bool		CapGetValve;			//取料电磁阀
	bool		CapBackValve;			//回料电磁阀
	bool		AlarmOut;				//报警蜂鸣器
	bool		StopSignal;				//停机信号
	bool		AlarmSignal;			//报警输出
	bool        YellowAlarmout;			//黄灯报警
	bool		Baffle;					//挡板
	bool		LeftFeed;				//左取料
	bool		RightFeed;				//右取料
	bool		LeftAbsorb;				//左抽取
	bool		RightAbsorb;			//右抽取
	INT			Analogoutput;			//模拟量输出
}Output_typ;


/**********************************************************/
/* 通讯数据 */
/**********************************************************/
#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	REAL		s_trg_stop[MAX_PULSE_SERVO];				//停止位置	
	REAL		FeedTimeOut;				//下料超时时间,单位s	
	REAL		CapPickInterval;				//自动取料周期,单位s	
	REAL		CapBackInterval;				//成品返还周期,单位s	
	REAL		CapAbsorbInterval;				//抽取时间	
	REAL		TireDelay;				//去皮延迟启动时间,单位s	
	REAL		ReadDelay;				//读数延迟启动时间,单位s	
	REAL		TireWaitTime;				//去皮等待时间,单位s	
	UINT		StopSignalDelay;				//连续几次超重或超轻后输出停机信号	
	REAL		CapPickInterval2;				//抽取时间2	
	DINT		PillPickCount;				//取料计数	
	DINT		PillPickCount2;				//取料计数2	
	UINT		StartCapNum;				//开机胶囊取数	
	UINT		StartPillNum;				//开机片剂取数	
	UINT		enable;				//1读取2写入	
	UINT		temp;				//no use	


	DINT		Reserve[16];							//预留空间
}Comm_Machine_Para_typ;

typedef struct
{
	UINT		SysOveride;		//系统速度
	UINT		StableState;		//0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
	UDINT		PassCount;		//通过计数
	UDINT		ProdCount;		//称重计数
	UDINT		TOCount;		//过重计数
	UDINT		TUCount;		//过轻计数
	UDINT		RejectCount;		//剔废计数
	UINT		WorkMode;		//0:片剂，1：胶囊
	UINT		GroupSet;		//每组测试胶囊数量
	UINT		GroupCounter;		//组落料数量
	UINT		TireMode;		//0:每组去皮重,1:每次称重去皮重
	REAL		TestInterval;		//测试间隔时间,单位s
	REAL		TOverload;		//超重重量,g
	REAL		TUnderload;		//超轻重量,g
	REAL		TDemand;		//期望重量,g
	DINT		DeltaSwing;		//位置偏差,未使用
	UINT		GroupWeightCounter;		//组称重数量
	UINT		GroupRejectCounter;		 //组踢废数量,指剔废处理,非剔废动作
	STRING		BatchName[40];		//批号字符串
	UDINT		GroupNo;		//组号
	UDINT		GroupIndex;		//组数量计数
	LREAL		GroupSum;		//组总重
	REAL		GroupAvg;		//组平均重量,g
	REAL		GroupMax;		//组最大值
	REAL		GroupMin;		//组最小值
	REAL		GroupMaxRatio;		//组最大偏差
	REAL		GroupMinRatio;		//组最小偏差
	REAL		InterOverLoad;		//内控线，上限
	REAL		InterUnderLoad;		//内控线，下限
	bool		UsbOk;		//U盘准备好
	bool		UsbPrintOk;		//Print准备好
	REAL		UserAnalogoutput;		//用户模拟量输入
	REAL		Adjustvalue;		//自动调整系数
	UDINT		DeltaInput;		//装量调整偏差值
	REAL		TestInterval2;		//测试间隔时间2,单位s
	UINT		GroupSet2;		//每组测试胶囊数量2
	UINT		CurrentGroup;		//当前工作对应哪个组间隔，0：组1，1：组2
	REAL		EmptyCapAvgWeight;		//空胶囊壳均重
	UINT		enGroupMode;		//0:普通模式，1:组称模式
	UINT		GroupAmount;		//组称数量


	DINT				Reserve[16];			//预留空间
}Comm_Run_Para_typ;

typedef struct
{
	DINT				Finished;				//本组结束
	DINT				GroupIndex;				//本组序号
	REAL				Weight;					//本次重量

	//plc相关
	DateTimeStructTyp	PLCTimeNow;				//PLC当前时间
	DINT				UsbPrintOk;				//打印机连接正常,0:未连接，1：已连接
	DINT				UsbOk;					//U盘连接正常,0:未连接，1：已连接

	//Scale Data
	REAL				ScaleResult;			//天平当前读数，单位g
	DINT				ScaleStableState;		//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	//Group Data
	Displaytyp			CapDataDisp;			//组数据

	//AxisStatus
	DINT				AxisFeedStep;			//下料电机状态机步骤
	DINT				AxisFeedErrorNo;		//下料电机错误代码
	DINT				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit

	DINT				AxisSwingStep;			//旋转电机状态机步骤
	DINT				AxisSwingErrorNo;		//旋转电机错误代码
	DINT				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit

	//MainCtrl etc
	DINT				MachineStep;			//系统运行状态机步骤
	REAL				TimeInterval;			//测量实际间隔时间

	DINT				AlarmStatus;			//0:无报警，1：一般报警，2：严重报警
	USINT				Alarm[16];				//报警位0-99，每一位对应一个报警,Alarm[0].0 ---- Alarm[13].3

	DINT				usertime;				//用户定义打印时间间隔(分钟)
	REAL				Rsd;					//相对标准偏差值


	DINT				Reserve[31];			//预留空间
}Comm_Status_typ;

typedef struct
{//照相处理结果
	UDINT		OK;								//0:合格，1：不合格
	DINT		Reserve[16];					//预留空间
}Comm_Result_typ;

typedef struct
{
	DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
	USINT		cmdChangeDT;					//修改日期时间,1:执行，自动复位

	USINT		cmdScaleRead;					//秤读数命令,1:执行，自动复位
	USINT		cmdScaleTire;					//秤清零,1:执行，自动复位
	USINT		cmdScaleSetStable;				//设定秤稳定状态,1:执行，自动复位
//	USINT		paraScaleSetStable;				//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	USINT		cmdScaleCalibExt;				//秤外部校正,1:执行，自动复位
	USINT		cmdAxisFeedJogPos;				//下料正转点动，1:执行，0:停止
	USINT		cmdAxisFeedJogNeg;				//下料反转点动，1:执行，0:停止
	USINT		cmdAxisFeedRelMov;				//下料相对运动启动，1:执行，自动复位
	USINT		cmdAxisFeedPosMov;				//下料正向连续运动启动，1:执行，自动复位
	USINT		cmdAxisFeedStopMov;				//下料停止运动，1:执行，自动复位

	USINT		cmdAxisSwingJogPos;				//旋转正转点动，1:执行，0:停止
	USINT		cmdAxisSwingJogNeg;				//旋转反转点动，1:执行，0:停止
	USINT		cmdAxisSwingRelMov;				//旋转相对运动启动，1:执行，自动复位
	USINT		cmdAxisSwingPosMov;				//旋转正向连续运动启动，1:执行，自动复位
	USINT		cmdAxisSwingStopMov;			//旋转停止运动，1:执行，自动复位

	USINT		cmdFeedSingle;					//单粒下料，1:执行，自动复位
	USINT		cmdFeedSingleStop;				//单粒下料停止，1:执行，自动复位

	USINT		cmdSwing;						//旋转单工位,1:执行，自动复位
	USINT		cmdStart;						//启动称重，1:执行，自动复位
	USINT		cmdEStop;						//急停，1:执行，自动复位
	USINT		cmdStop;						//停止,1:执行，自动复位
	USINT		cmdInit;						//初始化，1:执行，自动复位
	USINT		cmdAlarmReset;					//报警复位,1:执行，自动复位
	USINT		cmdCounterZero;					//计数器清零,1:执行，自动复位
	USINT		cmdPrintStart;					//启动打印,1:执行，自动复位
	USINT		cmdPrintStartE;					//启动英文打印，1:执行，自动复位
	USINT		cmdCapClean;					//清空胶囊，1:执行，自动复位
	USINT		cmdAlogtest;					//模拟量输出测试,1:执行，自动复位

	USINT		LeftRightFeedSign;				//左右进料标志0左进料1右进料
	USINT		cmdSingleSelect;				//单称选择
	USINT		cmdLeftGetCap;					//左取囊动作
	USINT		cmdRightGetCap;					//右取囊动作
	USINT		cmdReject;						//踢废
	USINT		cmdFeedAmount;					//组称落料
	Output_typ					Outputs;			//输出点

	DINT				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit

	DINT				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit



	USINT		Reserve[32];					//预留空间
}Comm_Machine_Cmd_typ;



typedef struct DataFromPC_typ
{
	UDINT						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,4,运行参数,100:应答
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Comm_Run_Para_typ			ActData;			//运行参数
	Comm_Machine_Cmd_typ		Machine_Cmd;		//命令
	Comm_Result_typ				PhotoResult;		//拍照处理结果
	DINT						Reserve[16];		//预留空间
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	UDINT						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,100:应答
	//ActData名称修改，原Run_Para
	Comm_Run_Para_typ			ActData;			//运行数据
	Comm_Status_typ				Status;				//系统状态
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Input_typ					Inputs;				//输入点 
	Output_typ					Outputs;			//输出点 

	DINT						Reserve[16];		//预留空间

}DataToPC_typ;

#pragma pack()
//_GLOBAL			DataToPC_typ			DataToPC;


#endif

