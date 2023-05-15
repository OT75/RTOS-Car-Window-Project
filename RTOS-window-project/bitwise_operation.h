#define Set_Bit(reg, bit)      reg |= ( 1U << bit)
#define Clear_Bit(reg, bit)      reg &= ~( 1U << bit)
#define Toggle_Bit(reg, bit)      reg ^= ( 1U << bit)
#define Get_Bit(reg, bit)      (reg & ( 1U << bit)) >> bit