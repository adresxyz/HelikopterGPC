#include "CPLD.h"

int	CPLD_WriteMisc( int DcReg )
{
    CPLD_DTYPE *pCPLD = (CPLD_DTYPE *)CPLD_BASE_ADDR;

    pCPLD[REGA_MISC] = DcReg;

    return( (int)DcReg & 0xFF );
}
