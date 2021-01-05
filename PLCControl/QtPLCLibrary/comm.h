/**********************************************************/
/* ͨѶ���� */
/**********************************************************/

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))
#ifndef _COMM_H_
#define	_COMM_H_

#define		NUM_OF_CHANNEL				30
#define		NUM_OF_FLASH				3

//input
typedef struct
{
	bool		FeedTrigger;			//����������
	bool		SwingTrigger;			//�ڱ�λ�ü��
}Input_typ;


//output
typedef	struct
{	
	bool		Inveter;					//��Ƶ����ͣ
	bool		ClipValve;					//�н���
	bool		UpValve;					//������
	bool		DropValve;					//���ҷ�
	
	bool		LampRed;					//���
	bool		LampYellow;					//�Ƶ�
	bool		LampGreen;					//�̵�
	bool		Buzzer;						//������
	bool		Photo;						//����
	
	bool		Flash[NUM_OF_FLASH];		//��Դ
	bool		Reject[NUM_OF_CHANNEL];		//�޷�
	
}Output_typ;


/**********************************************************/
/* ͨѶ���� */
/**********************************************************/
#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	int		FeedAxisHomeOffset;		//�ͽ���Ѱ��ƫ��,��λ0.01��
	
	int		ClipPhase1;				//�н����׶�����λ,��λ0.01��
	int		ClipPhase2;				//�н������ͷ���λ,��λ0.01��
	int		UpPhase1;				//̧�����׶�����λ,��λ0.01��
	int		UpPhase2;				//̧�������ͷ���λ,��λ0.01��
	int		DropPhase1;				//�������׶�����λ,��λ0.01��
	int		DropPhase2;				//���������ͷ���λ,��λ0.01��
	
	float		tClip1;					//�н����׶����ӳ�,��λms
	float		tClip2;					//�н������ͷ��ӳ�,��λms
	float		tUp1;					//̧�����׶����ӳ�,��λms
	float		tUp2;					//̧�������ͷ��ӳ�,��λms
	float		tDrop1;					//�������׶����ӳ�,��λms
	float		tDrop2;					//̧�������ͷ��ӳ�,��λms
	
	int		FeedLength;				//�ͽ����ȣ���λ0.01mm
	
	float		FlashTime;				//����ʱ��,��λms
	float		PhotoTime;				//����ʱ��,��λms
	float		RejectTime;				//�޷Ϸ�����ʱ��,��λms
	
	float		PhotoDelay;				//������ÿ�ʼ����,��λms
	int		PhotoPhase;				//�����������λ,��λ0.01��	
	int		RejectPhase;			//�޷���λ,��λ0.01��
	
	int		PhotoTimes;				//ÿ�����������,1-10
	
	float		RotateSpeed;			//����ٶȶ�Ӧ��ת�ٶ�, RPM
	int		DisableForceReject;		//�ر�ǿ���޷�,1:�ر�

	int		CapCheckAlarmTime;		//���Ҽ�ⱨ��ʱ�䣬��λms

	int		RejectFallingTime;		//�޷Ͻ�������ʱ�䣬��λms


	float	PhotoInterval;			//���ռ���Ƕȣ����ת�ң���λ:��,��Χ1-360�ȡ�

	int Reserve[16]; //Ԥ���ռ�
}Comm_Machine_Para_typ;

typedef struct
{
	int		RunSpeed;				//�����ٶ�
	int		SysPhase;				//��ǰϵͳ��λ
	int		enPhoto;				//����ʹ�� 0:ֹͣ����, 1:��ʼ����
	int		enReject;				//�޷�ʹ��, 0:ֹͣ�޷�, 1:��ʼ�޷�
	int		enFeed;					//�϶�ʹ��
	int		enRotate;				//ת��ʹ��
	unsigned int		CheckCount;				//������
	unsigned int		RejectCount;			//�޷ϼ���
	unsigned int		ForceRejectCount;		//ǿ���޷ϼ���	
	int Reserve[16]; //Ԥ���ռ�
}Comm_Run_Para_typ;

typedef struct
{
	unsigned int		AlarmStatus;			//����״̬,0:�ޱ�����1:Warning, 2,Fatal Error
	unsigned char		Alarm[16];				//����λ0-99��ÿһλ��Ӧһ������,Alarm[0].0 ---- Alarm[13].3
	
	unsigned int		ServoErrorNum[2];		//�ŷ���������
	unsigned int		SysPhase;				//ϵͳ��λ
	unsigned int		HomeOK;					//Ѱ�γɹ�

	unsigned int		CommStep;				//ͨѶ״̬
	unsigned int		NoDataCounter;			//�����ݼ���
	unsigned int		SendCounter;			//���ͱ��ļ���
	unsigned int		RecvCounter;			//���ձ��ļ���
	unsigned int		RecvTelLength;			//���ձ��ĳ���

	unsigned int		CommStep2;				//ͨѶ״̬2
	unsigned int		NoDataCounter2;			//�����ݼ���2
	unsigned int		SendCounter2;			//���ͱ��ļ���2
	unsigned int		RecvCounter2;			//���ձ��ļ���2
	unsigned int		RecvTelLength2;			//���ձ��ĳ���2

	unsigned int		RejectTelCount;			//���յ��޷ϱ��ĵļ�����
	unsigned int		RejectTelRecivedPhase;	//���յ��޷ϱ��ĵ���λ
	unsigned int		ServoState[2];			//�ŷ�״̬
	unsigned int		RejectCounter[NUM_OF_CHANNEL]; //ͨ���޷ϼ��� useless for me
	int Reserve[32]; //Ԥ���ռ�
}Comm_Status_typ;

typedef struct
{
	unsigned char		cmdHome;							//Ѱ��,1:Ѱ������
	unsigned char		cmdStart;							//����,1:��������
	unsigned char		cmdStop;							//ֹͣ,ͣ��0��λ,1:ֹͣ
	unsigned char		cmdEStop;							//����ֹͣ(����ֹͣ), 1:ֹͣ
	unsigned char		cmdJog;								//�㶯����, 1,����,0,ֹͣ
	unsigned char		cmdErrorAck;						//������λ, 1:��λ
	unsigned char		cmdResetCounter;					//��λ��������, 1:��λ
	unsigned char		cmdParaSave;						//������������, 1:����
	unsigned char		cmdParaLoad;						//������ȡ����, 1:��ȡ
	unsigned char		cmdTestKick[NUM_OF_CHANNEL];		//�ֶ��޷�, 1:Push, 2:Back
	unsigned char		cmdTestFlash[NUM_OF_FLASH];			//�ֶ�����, 1:����,�Զ���λ
	unsigned char		cmdTestValveUp;						//�ֶ���������, 1:Push, 2:Back
	unsigned char		cmdTestValveClip;					//�ֶ��н�����, 1:Push, 2:Back
	unsigned char		cmdTestValveDrop;					//�ֶ���������, 1:Push, 2:Back
	unsigned char		cmdTestInverter;					//�ֶ������϶�����, 1:Start, 2:Stop
	unsigned char		cmdTestLampRead;					//�ֶ�������, 1:��� , 2: ��λ
	unsigned char		cmdTestLampYellow;					//�ֶ��Ƶ����, 1:��� , 2: ��λ
	unsigned char		cmdTestLampGreen;					//�ֶ��̵����, 1:��� , 2: ��λ
	unsigned char		cmdTestBuzzer;						//�ֶ����������, 1:��� , 2: ��λ
	unsigned char		cmdTestPhoto;						//�ֶ�����, 1:��� , 2: ��λ
	unsigned char		cmdTestFlashPhoto;					//�ֶ����������, 1:����
	unsigned char		cmdTestCapPhoto;					//�ֶ���������
	unsigned char		cmdRotateCtl;						//�ֶ�ת����ͣ
	unsigned char		cmdSetAlarm;								//�ֶ����������ţ��������㴥������Χ1-99

	unsigned char Reserve[32]; //Ԥ���ռ�
}Comm_Machine_Cmd_typ;

typedef struct
{//���ദ����
	unsigned char		Alarm[4];				//4bytes=32bits,ÿһλ��Ӧһ��ͨ��,0:ͨ��,1:�޷�
	unsigned int		id;						//���id

	int Reserve[16]; //Ԥ���ռ�
}Comm_Result_typ;

typedef struct DataFromPC_typ
{
	unsigned int						Dummy;				//ռ��
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,4,���в���,100:Ӧ��
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ���� 2
	Comm_Run_Para_typ			Run_Para;			//���в��� 4
	Comm_Machine_Cmd_typ		Machine_Cmd;		//���� 1
	Comm_Result_typ				PhotoResult;		//���մ����� 3
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,100:Ӧ��
	Comm_Run_Para_typ			ActData;			//��������
	Comm_Status_typ				Status;				//ϵͳ״̬	
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Input_typ					Inputs;				//����� 
	Output_typ					Outputs;			//����� 	
	bool operator==(const DataToPC_typ &data)
	{
		if (Status.HomeOK != data.Status.HomeOK)return false;
		if (Telegram_typ!= data.Telegram_typ)return false; 
		if (Status.AlarmStatus != data.Status.AlarmStatus)return false;
		if (ActData.CheckCount != data.ActData.CheckCount)return false;
		if (ActData.RunSpeed != data.ActData.RunSpeed)return false;
		return true;
	}
}DataToPC_typ;

//_GLOBAL			DataToPC_typ			DataToPC;


#endif

