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
	unsigned char		cmdFeedSingleStop;				//��������ֹͣ��1:ִ�У��Զ���λ

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

