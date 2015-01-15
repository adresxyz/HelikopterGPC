/*Constants*/

#define CPLD_BASE_ADDR   0x90080000     // TBCE1, EMIFA
#define REGA_USER        0              // User reg, led/switch
#define REGA_DC          1              // Daughter card
#define REGA_CODEC_L     2              // Codec low byte
#define REGA_CODEC_H     3              // Codec high byte
#define REGA_VER         4              // Board/Fpga version
#define REGA_MISC        6              // Misc
#define REG_MASK         0x000000FF     // Byte mask

/*Variables*/
typedef volatile char CPLD_DTYPE;       // 8-bit access to cpld

/*Prototypes*/
int	CPLD_WriteMisc(int DcReg);

