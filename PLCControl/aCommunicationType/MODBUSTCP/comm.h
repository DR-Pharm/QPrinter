/**********************************************************/
/* ͨѶ���� */
/**********************************************************/
#define MODBUSTCP
//unsigned int == UDINT 4���ֽ�
//int == DINT 4���ֽ� ��longһ����4���ֽ� 
//float == REAL 4���ֽ� double��longlong��8���ֽ�
//unsigned char = USINT 8λ 1���ֽ�
//char == STRING
//char[40] == STRING[40] 8λ 1���ֽ���1���ַ�ռλ
//bool == BOOL 1λ
//short == INT 2���ֽ�
//short == UINT 2���ֽ�
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

enum MODBUSTCPREGISTERS
{
	DTPLC_second = 1,    // UINT
	DTPLC_minute,    // UINT
	DTPLC_hour,    // UINT
	DTPLC_day,    // UINT
	DTPLC_month,    // UINT
	DTPLC_year,    // UINT
	DTPLC_weekday,    // UINT
	GroupDone, //������� UINT
	ActData_GroupSum,    //���� LREAL
	ActData_GroupSum_Reserve1,    //���� LREAL
	ActData_GroupSum_Reserve2,    //���� LREAL
	ActData_GroupSum_Reserve3,    //���� LREAL
	FeedCounter,   //�Ѿ��������������cmdFeedFive���� UINT
	ActData_ThickRejectCount,   //����޷ϼ����� UDINT
	ActData_ThickRejectCount_Reserve,
	ActData_RejectBoxCnt,   //�޷Ϻ������� UDINT
	ActData_RejectBoxCnt_Reserve,
	ActData_FeedAmount,   //nƬ���� UINT
	
	ActData_GroupNo,   // UDINT
	ActData_GroupNo_Reserve,
	ActData_GroupIndex,   // UDINT
	ActData_GroupIndex_Reserve,
	Machine_step,  //���� UINT
	ActData_PassCount,   //ͨ������ UDINT
	ActData_PassCount_Reserve,
	ActData_ProdCount,   //���ؼ��� UDINT
	ActData_ProdCount_Reserve,
	ActData_TOCount,   //���ؼ��� UDINT
	ActData_TOCount_Reserve,
	ActData_TUCount,   //������� UDINT
	ActData_TUCount_Reserve,
	ActData_RejectCount,   //�޷ϼ��� UDINT
	ActData_RejectCount_Reserve,
	ActData_GroupAvg,   //��ƽ������g REAL
	ActData_GroupAvg_Reserve,
	ActData_GroupMax,   // REAL
	ActData_GroupMax_Reserve,
	ActData_GroupMin,   // REAL
	ActData_GroupMin_Reserve,
	ActData_GroupMaxRatio,   // REAL
	ActData_GroupMaxRatio_Reserve,
	ActData_GroupMinRatio,   // REAL
	ActData_GroupMinRatio_Reserve,
	ActData_HardnessChkCnt,   //Ӳ�ȼ����� UINT
	HMU_ResultForce,   //�������Ӳ�ȵ�λN REAL
	HMU_ResultForce_Reserve,
	HMU_ResultDiam,   //�������ֱ�� REAL
	HMU_ResultDiam_Reserve,
	HMU_ActForce,   //��ǰӲ�ȵ�λN REAL
	HMU_ActForce_Reserve,
	TMU_ThicknessResult,   //��Ƚ�� REAL
	TMU_ThicknessResult_Reserve,
	AlarmStatus,   //����״̬ UINT

	ActData_SysOveride,   //ϵͳ�ٶ� UINT
	ActData_GroupSet,   //ÿ����Խ������� UINT
	ActData_GroupCounter,   //���������� UINT
	ActData_TestInterval,   //���Լ��ʱ�䵥λs UINT
	ActData_TOverload,   //��������g REAL
	ActData_TOverload_Reserve,
	ActData_TUnderload,   //��������g REAL
	ActData_TUnderload_Reserve,
	ActData_TDemand,   //��������g REAL
	ActData_TDemand_Reserve,
	ActData_InterOverLoad,   //�ڿ��ߣ����� REAL
	ActData_InterOverLoad_Reserve,
	ActData_InterUnderLoad,   //�ڿ��ߣ����� REAL
	ActData_InterUnderLoad_Reserve,

	ActData_UserAnalogoutput,   //�û�ģ�������� REAL
	ActData_UserAnalogoutput_Reserve,
	ActData_Adjustvalue,   //�Զ�����ϵ�� REAL
	ActData_Adjustvalue_Reserve,
	ActData_DeltaInput,   //װ������ƫ��ֵ UDINT
	ActData_DeltaInput_Reserve,

	ActData_HMU_Zero,   //Ӳ�Ȳ��Դ�������� DINT
	ActData_HMU_Zero_Reserve,
	ActData_HMU_K,   //Ӳ�Ȳ���K REAL
	ActData_HMU_K_Reserve,
	ActData_TMU_Zero,   //��Ȳ��Դ�������� DINT
	ActData_TMU_Zero_Reserve,
	ActData_TMU_K,   //��Ȳ���K REAL
	ActData_TMU_K_Reserve,

	ActData_SetPillDiam,   //�趨Ƭ�� DINT
	ActData_SetPillDiam_Reserve,
	ActData_PillDiamOffset,   //Ƭ������ƫ�� DINT
	ActData_PillDiamOffset_Reserve,

	ActData_HardnessChkNum,   //Ӳ�ȼ���趨���� UINT
	ActData_RecipeNo,   //�䷽�� UINT
	ActData_reserve,   // UINT
	ActData_ThickUpperLimit,   //������� REAL
	ActData_ThickUpperLimit_Reserve,
	ActData_ThickUnderLimit,   //������� REAL
	ActData_ThickUnderLimit_Reserve,

	HMU_paraCalibForce,   //У������ REAL
	HMU_paraCalibForce_Reserve,
	TMU_calibThickness,   //У����ȵ�λmm REAL
	TMU_calibThickness_Reserve,

	System_enable,    //��ȡ�뱣�� UINT
	System_StopSignalDelay,    //�������γ��ػ�������ͣ���ź� UINT
	System_paraTurnUpSpd,    //�������ٶ� UINT
	System_paraTurnDnSpd,    //�������ٶ� UINT
	System_s_trg_stop0,    //�������ƫ�� REAL
	System_s_trg_stop0_Reserve,
	System_s_trg_stop1,    //ת�����ƫ�� REAL
	System_s_trg_stop1_Reserve,
	System_s_trg_stop2,    //�������ƫ�� REAL
	System_s_trg_stop2_Reserve,
	System_s_trg_stop3,    //�Ƹ����ƫ�� REAL
	System_s_trg_stop3_Reserve,

	System_FeedTimeOut,    //���ϳ�ʱʱ��,��λs REAL
	System_FeedTimeOut_Reserve,
	System_CapPickInterval,    //�Զ�ȡ������,��λs REAL
	System_CapPickInterval_Reserve,
	System_CapBackInterval,    //��Ʒ��������,��λs REAL
	System_CapBackInterval_Reserve,
	System_TireDelay,    //ȥƤ�ӳ�����ʱ��,��λs REAL
	System_TireDelay_Reserve,
	System_ReadDelay,    //�����ӳ�����ʱ��,��λs REAL
	System_ReadDelay_Reserve,
	System_TireWaitTime,    //ȥƤ�ȴ�ʱ��,��λs REAL
	System_TireWaitTime_Reserve,
	System_paraTurnUpPosition,    //������λ�� DINT
	System_paraTurnUpPosition_Reserve,
	System_paraTurnDnPosition,    //������λ�� DINT
	System_paraTurnDnPosition_Reserve,
	System_paraPushDestPosition,    //ѹƬ�ͽ����λ�� DINT
	System_paraPushDestPosition_Reserve,
	System_ForceThresholdSlow,    //ѹ����ֵ1,��⵽��ѹ����,���� REAL
	System_ForceThresholdSlow_Reserve,
	System_CapThickValve_t1,    //������׶����ӳ� REAL
	System_CapThickValve_t1_Reserve,
	System_CapThickValve_t2,    //������׸�λ�ӳ� REAL
	System_CapThickValve_t2_Reserve,
	System_CapTurnValve_t1,    //�����������׶����ӳ� REAL
	System_CapTurnValve_t1_Reserve,
	System_CapTurnValve_t2,    //�����������׸�λ�ӳ� REAL
	System_CapTurnValve_t2_Reserve,
	
	System_HMU_Zero,    //Ӳ�Ȳ��Դ�������� DINT
	System_HMU_Zero_Reserve,
	System_HMU_K,    //Ӳ�Ȳ���K REAL
	System_HMU_K_Reserve,
	System_TMU_Zero,    //��Ȳ��Դ�������� DINT
	System_TMU_Zero_Reserve,
	System_TMU_K,    //��Ȳ���K REAL
	System_TMU_K_Reserve,
	System_SetPillDiam,    //�趨Ƭ�� REAL
	System_SetPillDiam_Reserve,
	System_PillDiamOffset,    //Ƭ������ƫ�� REAL
	System_PillDiamOffset_Reserve,

	System_HMU_PressStopPercent,    //Ӳ�Ȳ�����ֹͣѹƬ�������ٷֱ�10-100 REAL
	System_HMU_PressStopPercent_Reserve,
	System_PrintIntervel,    //�û������ӡʱ����(����) REAL
	System_PrintIntervel_Reserve,
	System_RejectBoxFullNum,    //�޷Ϻ������� DINT
	System_RejectBoxFullNum_Reserve,
	Scale_Result,  //���� REAL
	Scale_Result_Reserve,
	axis0_s_rel,  //���ϲ�����
	axis0_s_rel_Reserve,
	axis1_s_rel,  //ת�̲�����
	axis1_s_rel_Reserve,
	Recipe_enable,//�䷽��ȡ1,2���� UDINT
	Recipe_enable_Reserve
};

enum MODBUSTCPCOILS
{
	Alarm1 = 1, Alarm2, Alarm3, Alarm4, Alarm5, Alarm6, Alarm7, Alarm8, Alarm9, Alarm10,
	Alarm11, Alarm12, Alarm13, Alarm14, Alarm15, Alarm16, Alarm17, Alarm18, Alarm19, Alarm20,
	Alarm21, Alarm22, Alarm23, Alarm24, Alarm25, Alarm26, Alarm27, Alarm28, Alarm29, Alarm30,
	Alarm31, Alarm32, Alarm33, Alarm34, Alarm35, Alarm36, Alarm37, Alarm38, Alarm39, Alarm40,
	Alarm41, Alarm42, Alarm43, Alarm44, Alarm45, Alarm46, Alarm47, Alarm48, Alarm49, Alarm50,

	Input_FeedTrigger,    //���������� BOOL
	Input_PressTrigger,    //Ӳ�ȼ��λ����λ BOOL
	Input_stCapThickValve,     //�������BOOL
	Input_stCapTurnValve,     //Ӳ������BOOL
	Input_SwingTrigger,    //�ڱ�λ�ü�� BOOL
	Input_TouchCalib,    //����������У�� BOOL
	Input_TurnTrigger,    //����λ����λ BOOL

	DTChanged,  //HMI�趨����ʱ��
	ActData_enHMU,   //Ӳ�ȼ��ʹ�� BOOL
	ActData_enTMU,   //��ȼ��ʹ�� BOOL
	HMU_cmdStart,   //����Ӳ�Ȳ��� BOOL
	HMU_cmdStop,   //ֹͣ BOOL
	HMU_cmdHome,   //Ӳ�Ȳ���ϵͳѰ�� BOOL
	HMU_cmdZero,   //�趨��� BOOL
	HMU_cmdCalibStd,   //У����׼ BOOL
	HMU_cmdTurn,   //��Ƭ BOOL
	HMU_cmdReject,   //�޷��� BOOL
	Machine_cmdStart,   //���� BOOL
	Machine_cmdEStop,   //ֹͣ BOOL
	TMU_cmdStart,   //������Ȳ��� BOOL
	TMU_cmdStop,   //ֹͣ BOOL
	TMU_cmdZero,   //�趨��� BOOL
	TMU_cmdCalib,   //У����׼ BOOL
	AlarmReset,    //BOOL
	cmdFeedSingle,   //���� BOOL
	cmdFeedFive,   //��������5 BOOL
	cmdFeedSingleStop,   //����ֹͣ BOOL
	cmdSwing,   //ת����תһ��λ BOOL
	SetCounterZero,   //�������� BOOL
	cmdCapClean,   //���ҷ��� BOOL
	cmdGetCap,   //ȡ�ң����Ҷ��� BOOL
	cmdSetIP,   //�趨ip���� BOOL
	FeedDone,    //BOOL
	CmdAlogtest,   //ģ�������� BOOL
	cmdFeedAmount,   //��N������ BOOL


	Output_CapGet,       //ȡ�ϵ����    BOOL
	Output_AlarmOut,       //����������    BOOL
	Output_StopSignal,       //ͣ���ź�    BOOL
	Output_AlarmSignal,       //�������    BOOL
	Output_YellowAlarmout,       //�ƵƱ���    BOOL
	Output_Baffle,       //����    BOOL
	Output_CapTurnValve,       //������������    BOOL
	Output_CapThickValve,       //�����������    BOOL

	axis_fun_axis0_com_rel_pos_start,     //���ϲ���
	axis_fun_axis0_com_jog_pos,     //��������㶯
	axis_fun_axis0_com_jog_neg,     //���Ϸ���㶯
	axis_fun_axis0_com_pos_move,     //������������
	axis_fun_axis1_com_rel_pos_start,     //ת�̲���
	axis_fun_axis1_com_jog_pos,     //ת������㶯
	axis_fun_axis1_com_jog_neg,     //ת�̷���㶯
	axis_fun_axis1_com_pos_move,     //ת����������
	axis_fun_axis1_com_stop_move,     //ת��ֹͣ
	axis_fun_axis2_com_jog_neg,     //��ת��ת
	axis_fun_axis2_com_jog_pos,     //��ת��ת
	axis_fun_axis3_com_jog_neg,     //ѹƬ��ת
	axis_fun_axis3_com_jog_pos,     //ѹƬ��ת
	Scale_cmdTire,				//������
	Scale_cmdCalibExt,     //���ⲿУ��
};
#define			MAX_PULSE_SERVO		2
#pragma pack(4)
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
	float		GroupAvg;			//��ƽ������,g
	float		GroupMax;
	float		GroupMin;
	float		GroupMaxRatio;
	float		GroupMinRatio;
	float        GroupWeightDelta;
	unsigned int		Tag;				//�����
}Displaytyp;

typedef struct
{
	float		Weight[20];
	float		Avg;
}DisplayWeightTyp;

typedef struct
{
	bool		FeedTrigger;			//����������
	bool		SwingTrigger;			//�ڱ�λ�ü��
	bool		FeedTrigger1;			//����������1
}Input_typ;


//output
typedef	struct
{
	bool         CapGet;				//ȡ�ϵ����    		86,1
	bool         AlarmOut;				//����������    		87,1
	bool         StopSignal;			//ͣ���ź�    	    88,1
	bool         AlarmSignal;			//�������    		89,1
	bool         YellowAlarmout;		//�ƵƱ���    	    90,1
	bool         Baffle;				//����     			91,1
	bool         CapTurnValve;			//������������    	92,
	bool         CapThickValve;			//�����������    	93,
}Output_typ;


#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	unsigned short		enable;//1��ȡ2д��	
	float		s_trg_stop[MAX_PULSE_SERVO];				//ֹͣλ��	
	float		Feed_shakeoffset;			//Ƭ���ڶ�����
	float		FeedTimeOut;				//���ϳ�ʱʱ��,��λs	
	float		CapPickInterval;				//�Զ�ȡ������,��λs	
	float		CapBackInterval;				//��Ʒ��������,��λs	


	float		TireDelay;				//ȥƤ�ӳ�����ʱ��,��λs	
	float		ReadDelay;				//�����ӳ�����ʱ��,��λs	
	float		TireWaitTime;				//ȥƤ�ȴ�ʱ��,��λs	
	unsigned short		StopSignalDelay;				//�������γ��ػ�������ͣ���ź�	

	int		Reserve[16];							//Ԥ���ռ�
}Comm_Machine_Para_typ;

typedef struct
{
	unsigned short		SysOveride;		//ϵͳ�ٶ�
	unsigned short		StableState;		//0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�
	unsigned short		FeedOveride;   //�����ٶ�

	unsigned int		PassCount;		//ͨ������
	unsigned int		ProdCount;		//���ؼ���
	unsigned int		TOCount;		//���ؼ���
	unsigned int		TUCount;		//�������
	unsigned int		RejectCount;		//�޷ϼ���

	unsigned short		WorkMode;		//0:Normal��1��Debug
	unsigned short		GroupSet;		//ÿ����Խ�������
	unsigned short		GroupCounter;		//����������
	unsigned short		TireMode;		//0:ÿ��ȥƤ��,1:ÿ�γ���ȥƤ��

	float		TestInterval;		//���Լ��ʱ��,��λs
	float		TOverload;		//��������,g
	float		TUnderload;		//��������,g
	float		TDemand;		//��������,g

	int		DeltaSwing;		//λ��ƫ��,δʹ��
	unsigned short		GroupWeightCounter;		//���������
	unsigned short		GroupRejectCounter;		 //���߷�����,ָ�޷ϴ���,���޷϶���
	char		BatchName[40];		//�����ַ���

	unsigned int		GroupNo;		//���
	unsigned int		GroupIndex;		//����������

	double		GroupSum;		//������
	float		GroupAvg;		//��ƽ������,g
	float		GroupMax;		//�����ֵ
	float		GroupMin;		//����Сֵ
	float		GroupMaxRatio;		//�����ƫ��
	float		GroupMinRatio;		//����Сƫ��
	float		InterOverLoad;		//�ڿ��ߣ�����
	float		InterUnderLoad;		//�ڿ��ߣ�����

	bool		UsbOk;		//U��׼����
	bool		UsbPrintOk;		//Print׼����
	bool		Feedmode;	//0 ���� 1 Ƭ��

	float		UserAnalogoutput;		//�û�ģ��������
	float		Adjustvalue;		//�Զ�����ϵ��
	unsigned int		DeltaInput;		//װ������ƫ��ֵ
	unsigned short		MultiCount;     //�¶���

	int				Reserve[16];			//Ԥ���ռ�
}Comm_Run_Para_typ;

typedef struct
{
	int				Finished;				//�������
	int				GroupIndex;				//�������
	float				Weight;					//��������

	//plc���
	DateTimeStructTyp	PLCTimeNow;				//PLC��ǰʱ��
	int				UsbPrintOk;				//��ӡ����������,0:δ���ӣ�1��������
	int				UsbOk;					//U����������,0:δ���ӣ�1��������

	//Scale Data
	float				ScaleResult;			//��ƽ��ǰ��������λg
	int				ScaleStableState;		//��ƽ��ǰ�ȶ�״̬,0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�

	//Group Data
	Displaytyp			CapDataDisp;			//������

	//AxisStatus
	int				AxisFeedStep;			//���ϵ��״̬������
	int				AxisFeedErrorNo;		//���ϵ���������
	int				AxisFeedRelMovDistance;	//���ϵ������˶����룬��λunit
	
	int				AxisSwingStep;			//��ת���״̬������
	int				AxisSwingErrorNo;		//��ת����������
	int				AxisSwingRelMovDistance;//��ת�������˶����룬��λunit

	//MainCtrl etc
	int				MachineStep;			//ϵͳ����״̬������
	float				TimeInterval;			//����ʵ�ʼ��ʱ��

	int				AlarmStatus;			//0:�ޱ�����1��һ�㱨����2�����ر���
	unsigned char				Alarm[16];				//����λ0-99��ÿһλ��Ӧһ������,Alarm[0].0 ---- Alarm[13].3

	int				usertime;				//�û������ӡʱ����(����)
	float				Rsd;					//��Ա�׼ƫ��ֵ


	int				Reserve[31];			//Ԥ���ռ�
}Comm_Status_typ;

typedef struct
{//���ദ����
	unsigned int		OK;								//0:�ϸ�1�����ϸ�
	int		Reserve[16];					//Ԥ���ռ�
}Comm_Result_typ;

typedef struct
{
	DateTimeStructTyp		DateTimeSet;		//�趨����ʱ��Ŀ��
	unsigned char		cmdChangeDT;					//�޸�����ʱ��,1:ִ�У��Զ���λ

	unsigned char		cmdScaleRead;					//�Ӷ�������,1:ִ�У��Զ���λ
	unsigned char		cmdScaleTire;					//������,1:ִ�У��Զ���λ
	unsigned char		cmdScaleSetStable;				//�趨���ȶ�״̬,1:ִ�У��Զ���λ
//	USINT		paraScaleSetStable;				//�ȶ�״̬�趨Ŀ�꣬0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�

	unsigned char		cmdScaleCalibExt;				//���ⲿУ��,1:ִ�У��Զ���λ
	unsigned char		cmdAxisFeedJogPos;				//������ת�㶯��1:ִ�У�0:ֹͣ
	unsigned char		cmdAxisFeedJogNeg;				//���Ϸ�ת�㶯��1:ִ�У�0:ֹͣ
	unsigned char		cmdAxisFeedRelMov;				//��������˶�������1:ִ�У��Զ���λ
	unsigned char		cmdAxisFeedPosMov;				//�������������˶�������1:ִ�У��Զ���λ
	unsigned char		cmdAxisFeedStopMov;				//����ֹͣ�˶���1:ִ�У��Զ���λ

	unsigned char		cmdAxisSwingJogPos;				//��ת��ת�㶯��1:ִ�У�0:ֹͣ
	unsigned char		cmdAxisSwingJogNeg;				//��ת��ת�㶯��1:ִ�У�0:ֹͣ
	unsigned char		cmdAxisSwingRelMov;				//��ת����˶�������1:ִ�У��Զ���λ
	unsigned char		cmdAxisSwingPosMov;				//��ת���������˶�������1:ִ�У��Զ���λ
	unsigned char		cmdAxisSwingStopMov;			//��תֹͣ�˶���1:ִ�У��Զ���λ

	unsigned char		cmdFeedSingle;					//�������ϣ�1:ִ�У��Զ���λ
	//unsigned char		cmdFeedSingleStop;				//��������ֹͣ��1:ִ�У��Զ���λ

	unsigned char		cmdSwing;						//��ת����λ,1:ִ�У��Զ���λ
	unsigned char		cmdStart;						//�������أ�1:ִ�У��Զ���λ
	unsigned char		cmdEStop;						//��ͣ��1:ִ�У��Զ���λ
	unsigned char		cmdStop;						//ֹͣ,1:ִ�У��Զ���λ
	unsigned char		cmdInit;						//��ʼ����1:ִ�У��Զ���λ
	unsigned char		cmdAlarmReset;					//������λ,1:ִ�У��Զ���λ
	unsigned char		cmdCounterZero;					//����������,1:ִ�У��Զ���λ
	unsigned char		cmdPrintStart;					//������ӡ,1:ִ�У��Զ���λ
	unsigned char		cmdPrintStartE;					//����Ӣ�Ĵ�ӡ��1:ִ�У��Զ���λ
	unsigned char		cmdCapClean;					//��ս��ң�1:ִ�У��Զ���λ
	unsigned char		cmdAlogtest;					//ģ�����������,1:ִ�У��Զ���λ

	unsigned char		LeftRightFeedSign;				//���ҽ��ϱ�־0�����1�ҽ���
	unsigned char		cmdSingleSelect;				//����ѡ��
	unsigned char		cmdLeftGetCap;					//��ȡ�Ҷ���
	unsigned char		cmdRightGetCap;					//��ȡ�Ҷ���
	unsigned char		cmdReject;						//�߷�
	unsigned char		cmdFeedAmount;					//�������

	bool		cmdFeedShake;					//����ҡ��
	bool		cmdFeedshakestop;				//����ҡ��ֹͣ
	bool		cmdFeedshakelevel;				//����ҡ��ˮƽ
	bool		cmdFeedhome;					//����Ѱ��
	bool		cmdFeedFive;					//��������5��
	bool		cmdFeedShakefive;				//Ƭ������5��

	int				AxisFeedRelMovDistance;	//���ϵ������˶����룬��λunit

	int				AxisSwingRelMovDistance;//��ת�������˶����룬��λunit


	Output_typ					Outputs;			//�����

	unsigned char		Reserve[32];					//Ԥ���ռ�
}Comm_Machine_Cmd_typ;



typedef struct DataFromPC_typ
{
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,4,���в���,100:Ӧ��
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Comm_Run_Para_typ			ActData;			//���в���
	Comm_Machine_Cmd_typ		Machine_Cmd;		//����
	Comm_Result_typ				PhotoResult;		//���մ�����
	int						Reserve[16];		//Ԥ���ռ�
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,100:Ӧ��
	//ActData�����޸ģ�ԭRun_Para
	Comm_Run_Para_typ			ActData;			//��������
	Comm_Status_typ				Status;				//ϵͳ״̬
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Input_typ					Inputs;				//����� 
	Output_typ					Outputs;			//����� 

	int						Reserve[16];		//Ԥ���ռ�

}DataToPC_typ;

#pragma pack()
//_GLOBAL			DataToPC_typ			DataToPC;


#endif

