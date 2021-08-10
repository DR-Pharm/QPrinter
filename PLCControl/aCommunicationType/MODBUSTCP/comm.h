/**********************************************************/
/* 通讯数据 */
/**********************************************************/
#define MODBUSTCP
//unsigned int == UDINT 4个字节
//int == DINT 4个字节 和long一样是4个字节 
//float == REAL 4个字节 double和longlong是8个字节
//unsigned char = USINT 8位 1个字节
//char == STRING
//char[40] == STRING[40] 8位 1个字节是1个字符占位
//bool == BOOL 1位
//short == INT 2个字节
//short == UINT 2个字节
/*#define UDINT unsigned int
#define DINT int
#define REAL float
#define USINT unsigned char
#define STRING char
#define INT short
#define UINT unsigned short
#define LREAL double*/
//#define BOOL bool

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
	unsigned short		second;
	unsigned short		minute;
	unsigned short		hour;
	unsigned short		day;
	unsigned short		month;
	unsigned short		year;
	unsigned short		weekday;	
}DateTimeStructTyp;

typedef struct
{
	unsigned int		GroupNo;
	unsigned int		GroupIndex;
	float		GroupAvg;			//组平均重量,g
	float		GroupMax;
	float		GroupMin;
	float		GroupMaxRatio;
	float		GroupMinRatio;
	float        GroupWeightDelta;
	unsigned int		Tag;				//表格标记
}Displaytyp;

typedef struct
{
	float		Weight[20];
	float		Avg;
}DisplayWeightTyp;

typedef struct
{
	bool		FeedTrigger;			//胶囊下落检测
	bool		SwingTrigger;			//摆臂位置检测
	bool		FeedTrigger1;			//胶囊下落检测1
}Input_typ;


//output
typedef	struct
{
	bool         CapGet;				//取料电磁铁    		86,1
	bool         AlarmOut;				//报警蜂鸣器    		87,1
	bool         StopSignal;			//停机信号    	    88,1
	bool         AlarmSignal;			//报警输出    		89,1
	bool         YellowAlarmout;		//黄灯报警    	    90,1
	bool         Baffle;				//挡板     			91,1
	bool         CapTurnValve;			//整形升降气缸    	92,
	bool         CapThickValve;			//测厚升降气缸    	93,
}Output_typ;


#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	unsigned short		enable;//1读取2写入	
	float		s_trg_stop[MAX_PULSE_SERVO];				//停止位置	
	float		Feed_shakeoffset;			//片剂摆动距离
	float		FeedTimeOut;				//下料超时时间,单位s	
	float		CapPickInterval;				//自动取料周期,单位s	
	float		CapBackInterval;				//成品返还周期,单位s	


	float		TireDelay;				//去皮延迟启动时间,单位s	
	float		ReadDelay;				//读数延迟启动时间,单位s	
	float		TireWaitTime;				//去皮等待时间,单位s	
	unsigned short		StopSignalDelay;				//连续几次超重或超轻后输出停机信号	

	int		Reserve[16];							//预留空间
}Comm_Machine_Para_typ;

typedef struct
{
	unsigned short		SysOveride;		//系统速度
	unsigned short		StableState;		//0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
	unsigned short		FeedOveride;   //下料速度

	unsigned int		PassCount;		//通过计数
	unsigned int		ProdCount;		//称重计数
	unsigned int		TOCount;		//过重计数
	unsigned int		TUCount;		//过轻计数
	unsigned int		RejectCount;		//剔废计数

	unsigned short		WorkMode;		//0:Normal，1：Debug
	unsigned short		GroupSet;		//每组测试胶囊数量
	unsigned short		GroupCounter;		//组落料数量
	unsigned short		TireMode;		//0:每组去皮重,1:每次称重去皮重

	float		TestInterval;		//测试间隔时间,单位s
	float		TOverload;		//超重重量,g
	float		TUnderload;		//超轻重量,g
	float		TDemand;		//期望重量,g

	int		DeltaSwing;		//位置偏差,未使用
	unsigned short		GroupWeightCounter;		//组称重数量
	unsigned short		GroupRejectCounter;		 //组踢废数量,指剔废处理,非剔废动作
	char		BatchName[40];		//批号字符串

	unsigned int		GroupNo;		//组号
	unsigned int		GroupIndex;		//组数量计数

	double		GroupSum;		//组总重
	float		GroupAvg;		//组平均重量,g
	float		GroupMax;		//组最大值
	float		GroupMin;		//组最小值
	float		GroupMaxRatio;		//组最大偏差
	float		GroupMinRatio;		//组最小偏差
	float		InterOverLoad;		//内控线，上限
	float		InterUnderLoad;		//内控线，下限

	bool		UsbOk;		//U盘准备好
	bool		UsbPrintOk;		//Print准备好
	bool		Feedmode;	//0 胶囊 1 片剂

	float		UserAnalogoutput;		//用户模拟量输入
	float		Adjustvalue;		//自动调整系数
	unsigned int		DeltaInput;		//装量调整偏差值
	unsigned short		MultiCount;     //下多粒

	int				Reserve[16];			//预留空间
}Comm_Run_Para_typ;

typedef struct
{
	int				Finished;				//本组结束
	int				GroupIndex;				//本组序号
	float				Weight;					//本次重量

	//plc相关
	DateTimeStructTyp	PLCTimeNow;				//PLC当前时间
	int				UsbPrintOk;				//打印机连接正常,0:未连接，1：已连接
	int				UsbOk;					//U盘连接正常,0:未连接，1：已连接

	//Scale Data
	float				ScaleResult;			//天平当前读数，单位g
	int				ScaleStableState;		//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	//Group Data
	Displaytyp			CapDataDisp;			//组数据

	//AxisStatus
	int				AxisFeedStep;			//下料电机状态机步骤
	int				AxisFeedErrorNo;		//下料电机错误代码
	int				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit
	
	int				AxisSwingStep;			//旋转电机状态机步骤
	int				AxisSwingErrorNo;		//旋转电机错误代码
	int				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit

	//MainCtrl etc
	int				MachineStep;			//系统运行状态机步骤
	float				TimeInterval;			//测量实际间隔时间

	int				AlarmStatus;			//0:无报警，1：一般报警，2：严重报警
	unsigned char				Alarm[16];				//报警位0-99，每一位对应一个报警,Alarm[0].0 ---- Alarm[13].3

	int				usertime;				//用户定义打印时间间隔(分钟)
	float				Rsd;					//相对标准偏差值


	int				Reserve[31];			//预留空间
}Comm_Status_typ;

typedef struct
{//照相处理结果
	unsigned int		OK;								//0:合格，1：不合格
	int		Reserve[16];					//预留空间
}Comm_Result_typ;

typedef struct
{
	DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
	unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位

	unsigned char		cmdScaleRead;					//秤读数命令,1:执行，自动复位
	unsigned char		cmdScaleTire;					//秤清零,1:执行，自动复位
	unsigned char		cmdScaleSetStable;				//设定秤稳定状态,1:执行，自动复位
//	USINT		paraScaleSetStable;				//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	unsigned char		cmdScaleCalibExt;				//秤外部校正,1:执行，自动复位
	unsigned char		cmdAxisFeedJogPos;				//下料正转点动，1:执行，0:停止
	unsigned char		cmdAxisFeedJogNeg;				//下料反转点动，1:执行，0:停止
	unsigned char		cmdAxisFeedRelMov;				//下料相对运动启动，1:执行，自动复位
	unsigned char		cmdAxisFeedPosMov;				//下料正向连续运动启动，1:执行，自动复位
	unsigned char		cmdAxisFeedStopMov;				//下料停止运动，1:执行，自动复位

	unsigned char		cmdAxisSwingJogPos;				//旋转正转点动，1:执行，0:停止
	unsigned char		cmdAxisSwingJogNeg;				//旋转反转点动，1:执行，0:停止
	unsigned char		cmdAxisSwingRelMov;				//旋转相对运动启动，1:执行，自动复位
	unsigned char		cmdAxisSwingPosMov;				//旋转正向连续运动启动，1:执行，自动复位
	unsigned char		cmdAxisSwingStopMov;			//旋转停止运动，1:执行，自动复位

	unsigned char		cmdFeedSingle;					//单粒下料，1:执行，自动复位
	unsigned char		cmdFeedSingleStop;				//单粒下料停止，1:执行，自动复位

	unsigned char		cmdSwing;						//旋转单工位,1:执行，自动复位
	unsigned char		cmdStart;						//启动称重，1:执行，自动复位
	unsigned char		cmdEStop;						//急停，1:执行，自动复位
	unsigned char		cmdStop;						//停止,1:执行，自动复位
	unsigned char		cmdInit;						//初始化，1:执行，自动复位
	unsigned char		cmdAlarmReset;					//报警复位,1:执行，自动复位
	unsigned char		cmdCounterZero;					//计数器清零,1:执行，自动复位
	unsigned char		cmdPrintStart;					//启动打印,1:执行，自动复位
	unsigned char		cmdPrintStartE;					//启动英文打印，1:执行，自动复位
	unsigned char		cmdCapClean;					//清空胶囊，1:执行，自动复位
	unsigned char		cmdAlogtest;					//模拟量输出测试,1:执行，自动复位

	unsigned char		LeftRightFeedSign;				//左右进料标志0左进料1右进料
	unsigned char		cmdSingleSelect;				//单称选择
	unsigned char		cmdLeftGetCap;					//左取囊动作
	unsigned char		cmdRightGetCap;					//右取囊动作
	unsigned char		cmdReject;						//踢废
	unsigned char		cmdFeedAmount;					//组称落料

	bool		cmdFeedShake;					//下料摇摆
	bool		cmdFeedshakestop;				//下料摇摆停止
	bool		cmdFeedshakelevel;				//下料摇摆水平
	bool		cmdFeedhome;					//下料寻参
	bool		cmdFeedFive;					//胶囊落料5粒
	bool		cmdFeedShakefive;				//片剂落料5粒

	int				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit

	int				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit


	Output_typ					Outputs;			//输出点

	unsigned char		Reserve[32];					//预留空间
}Comm_Machine_Cmd_typ;



typedef struct DataFromPC_typ
{
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,4,运行参数,100:应答
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Comm_Run_Para_typ			ActData;			//运行参数
	Comm_Machine_Cmd_typ		Machine_Cmd;		//命令
	Comm_Result_typ				PhotoResult;		//拍照处理结果
	int						Reserve[16];		//预留空间
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,100:应答
	//ActData名称修改，原Run_Para
	Comm_Run_Para_typ			ActData;			//运行数据
	Comm_Status_typ				Status;				//系统状态
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Input_typ					Inputs;				//输入点 
	Output_typ					Outputs;			//输出点 

	int						Reserve[16];		//预留空间

}DataToPC_typ;

#pragma pack()
//_GLOBAL			DataToPC_typ			DataToPC;


#endif

