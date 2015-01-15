#ifndef DAC7716_H_
#define DAC7716_H_

/*----------Constants----------*/

static unsigned int const CHANNELS = 4; //How many channels there are

/*Masks and offsets*/
static unsigned int const DAC_FRAME_MSK = 0xFFFFFF; //24bits length frame
static unsigned int const DAC_AC_DATA_MSK = 0xFFF; //12bit of data
static unsigned int const DAC_AC_DATA_OFFSET = 4;
static unsigned int const DAC_ZERO_DATA_MSK = 0x1FF;
static unsigned int const DAC_ZERO_DATA_OFFSET = 0;
static unsigned int const DAC_GAIN_DATA_MSK = 0xFF;
static unsigned int const DAC_GAIN_DATA_OFFSET = 0;

/*Read/Write Option*/
static unsigned int const DAC_READ = 0x800000; //1 on 24bit
static unsigned int const DAC_WRITE = 0x000000; //0 on 24bit

/*Register Selector*/
static unsigned int const DAC_COMMAND_REG = 0;
static unsigned int const DAC_MONITOR_REG = 0x10000;

static unsigned int const DAC_AC0 = 0x40000;
static unsigned int const DAC_AC1 = 0x50000;
static unsigned int const DAC_AC2 = 0x60000;
static unsigned int const DAC_AC3 = 0x70000;

static unsigned int const DAC_ZERO_AC0 = 0x80000;
static unsigned int const DAC_ZERO_AC1 = 0x90000;
static unsigned int const DAC_ZERO_AC2 = 0xA0000;
static unsigned int const DAC_ZERO_AC3 = 0xB0000;

static unsigned int const DAC_GAIN_AC0 = 0xC0000;
static unsigned int const DAC_GAIN_AC1 = 0xD0000;
static unsigned int const DAC_GAIN_AC2 = 0xE0000;
static unsigned int const DAC_GAIN_AC3 = 0xF0000;

/*Command Register Values*/
static unsigned int const DAC_CR_A_B = 0x8000;
static unsigned int const DAC_CR_LD = 0x4000;
static unsigned int const DAC_CR_RST = 0x2000;
static unsigned int const DAC_CR_PD_A = 0x1000;
static unsigned int const DAC_CR_PD_B = 0x800;
static unsigned int const DAC_CR_GPIO1 = 0x200;
static unsigned int const DAC_CR_GPIO0 = 0x100;
static unsigned int const DAC_CR_DSDO = 0x80;
static unsigned int const DAC_CR_GAIN_AC3 = 0x20;
static unsigned int const DAC_CR_GAIN_AC2 = 0x10;
static unsigned int const DAC_CR_GAIN_AC1 = 0x8;
static unsigned int const DAC_CR_GAIN_AC0 = 0x4;

/*Monitor Register Values*/
#define DAC_MR_AIN = 0x800;
#define DAC_MR_AC0 = 0x1000;
#define DAC_MR_AC1 = 0x2000;
#define DAC_MR_AC2 = 0x4000;
#define DAC_MR_AC3 = 0x8000;
#define DAC_MR_DISABLED = 0;

/*Structures*/
typedef struct _DAC_Values
{
	int Channel_A0;
	int Channel_A1;
	int Channel_A2;
	int Channel_A3;
}DAC_Values;

/*Variables*/
static volatile DAC_Values DACValues;
static volatile DAC_Values DACValuesFromI2C;

/*Prototypes*/
unsigned int DAC_Prepare_Frame(unsigned int _RW, unsigned int _Reg_Address,unsigned int _Value);
void DAC_Update_Channel_To_Send(short* _Channel_To_Sedn);
void DAC_Prepare_EDMA(short int _PingPong,short _ChannelToSend, int* _PingBuff, int* _PongBuff, volatile DAC_Values _Values);
DAC_Values DAC_Fill_Values_With_Zeros(void);
void PrintfDACTransferInfo(short int _ChannelToSend, volatile short int _DAC_PingPong,int _ValueToSend );

#endif
