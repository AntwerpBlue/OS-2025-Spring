/* 
 * 与 UART 相关的输出
 * 调用inb和outb函数，实现下面的uart的三个函数
 */
extern unsigned char inb(unsigned short int port_from);
extern void outb (unsigned short int port_to, unsigned char value);

#define UART_BASE 0x3F8

// UART 寄存器偏移量
#define UART_TX_REG (UART_BASE + 0) // 发送寄存器
#define UART_RX_REG (UART_BASE + 0) // 接收寄存器
#define UART_LSR_REG (UART_BASE + 5) // 线路状态寄存器

#define UART_LSR_TX_EMPTY (1 << 5) // 发送寄存器空标志
#define UART_LSR_RX_READY (1 << 0) // 接收寄存器数据就绪标志

void uart_put_char(unsigned char c) {
    // 等待发送寄存器为空
    while ((inb(UART_LSR_REG) & UART_LSR_TX_EMPTY) == 0);

    // 发送字符
    outb(UART_TX_REG, c);
}

unsigned char uart_get_char(void) {
    // 等待接收寄存器数据就绪
    while ((inb(UART_LSR_REG) & UART_LSR_RX_READY) == 0);

    // 读取字符
    return inb(UART_RX_REG);
}

// 发送一个字符串
void uart_put_chars(char *str) {
    while (*str) {
        uart_put_char(*str); // 发送当前字符
        str++;               // 移动到下一个字符
    }
}