/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlcz -mabi=ilp32 -O3 -fno-inline -funroll-loops -g -mautogen-xxlcz" } */
/* { dg-final { scan-assembler "xl\.addibne" } } */

/* Regression test: *xl_addibne reads its output operand (the loop counter)
   inside the comparison while the second SET of the parallel writes it back,
   so operand 0 must be declared "+r" (in-out).  With the former pure output
   constraint "=r", regrename treated every match_dup occurrence as a separate
   output and opened several overlapping def-use chains for the same hard
   register at one insn, which later tripped the self-conflict assert
     gcc_assert (other != head)
   in merge_overlapping_regs (regrename.cc) during the register renumbering
   pass.  This shows up when the fused xl.addibne loop counter lives in a
   callee-saved register across calls after unrolling, e.g. a printf-style
   byte loop under LTO.  */

typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef struct {
    volatile uint32_t TXFIFO;
    volatile uint32_t RXFIFO;
    volatile uint32_t TXCTRL;
    volatile uint32_t RXCTRL;
} UART_TypeDef;

#define UART_TXFIFO_FULL (1u << 31)
#define SOC_DEBUG_UART ((UART_TypeDef *)0x10013000)

static int32_t uart_write(UART_TypeDef *uart, uint8_t val)
{
    if (__builtin_expect(uart == 0, 0))
        return -1;
    while (uart->TXFIFO & UART_TXFIFO_FULL)
        ;
    uart->TXFIFO = val;
    return 0;
}

int putchar(int dat)
{
    if (dat == '\n')
        uart_write(SOC_DEBUG_UART, '\r');
    uart_write(SOC_DEBUG_UART, dat);
    return dat;
}

long _write(int fd, const void *ptr, unsigned len)
{
    (void)fd;
    const uint8_t *writebuf = (const uint8_t *)ptr;
    for (unsigned i = 0; i < len; i++)
        putchar((int)writebuf[i]);
    return len;
}
