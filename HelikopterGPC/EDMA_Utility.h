#ifndef EDMA_UTILITY_H
#define EDMA_UTILITY_H

/*EDMA Handlers*/
static EDMA_Handle hEdmaADC; 		/* Handle for the McBSP receive EDMA reload parameters  */
static EDMA_Handle hEdmaADCPing; 	/* Handle for the McBSP receive EDMA reload parameters  */
static EDMA_Handle hEdmaADCPong; 	/* Handle for the McBSP receive EDMA reload parameters  */

static EDMA_Handle hEdmaDAC; 		/* Handle for the McBSP receive EDMA reload parameters  */
static EDMA_Handle hEdmaDACPing; 	/* Handle for the McBSP receive EDMA reload parameters  */
static EDMA_Handle hEdmaDACPong; 	/* Handle for the McBSP receive EDMA reload parameters  */

static EDMA_Handle hEdmaI2CRec;
static EDMA_Handle hEdmaI2CRecPing;
static EDMA_Handle hEdmaI2CRecPong;

static EDMA_Handle hEdmaI2CTrans;
static EDMA_Handle hEdmaI2CTransPing;
static EDMA_Handle hEdmaI2CTransPong;

/*Variables*/

/*ADC EDMA buffers*/
#pragma DATA_SECTION (ADC_Ping, ".buffers");
#pragma DATA_SECTION (ADC_Pong, ".buffers");

#pragma DATA_ALIGN(ADC_Ping,128);
#pragma DATA_ALIGN(ADC_Pong,128);

static int ADC_Ping = 0;
static int ADC_Pong = 0;

static volatile short int ADC_PingPong = 0;

/*DAC EDMA buffers*/
#pragma DATA_SECTION (DAC_Ping, ".buffers");
#pragma DATA_SECTION (DAC_Pong, ".buffers");

#pragma DATA_ALIGN(DAC_Ping,128);
#pragma DATA_ALIGN(DAC_Pong,128);

static int DAC_Ping;
static int DAC_Pong;

static volatile short int DAC_PingPong = 0;
static short int DAC_Channel_To_Send = 0;

/*I2C EDMA buffers*/
#pragma DATA_SECTION (I2C_RecPing, ".buffers");
#pragma DATA_SECTION (I2C_RecPong, ".buffers");

#pragma DATA_ALIGN(I2C_RecPing,128);
#pragma DATA_ALIGN(I2C_RecPong,128);

static int I2C_RecPing;
static int I2C_RecPong;

#pragma DATA_SECTION (I2C_TransPing, ".buffers");
#pragma DATA_SECTION (I2C_TransPong, ".buffers");

#pragma DATA_ALIGN(I2C_TransPing,128);
#pragma DATA_ALIGN(I2C_TransPong,128);

static int I2C_TransPing[4];
static int I2C_TransPong[4];

/*EDMA Interrupts numbers*/
#define EDMA_ADC_IRQ 8
#define EDMA_DAC_IRQ 9
#define EDMA_I2C_REC_IRQ 7
#define EDMA_I2C_TRANS_IRQ 6

/*EDMA help functions*/
Uint32 EDMAADCConfOpt(void);
Uint32 EDMADACConfOpt(void);
Uint32 EDMI2CRecConfOpt(void);
Uint32 EDMI2CTransConfOpt(void);

void enableIRQ_EDMA(void);
void stopEdma(EDMA_Handle* _Handler, int _EDMA_IRQ, EDMA_Handle* _HPing, EDMA_Handle* _HPong);

#endif
