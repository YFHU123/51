#include "seg.h"
#include <intrins.h>

sbit DIN = P2^0;     //数据串出引脚
sbit CS = P2^1;     //片选端
sbit CLK = P2^2;    //移位时钟端



//写数据函数
void write_data(unsigned char addr,unsigned char dat)
{
    unsigned char i;
    CS = 0;        // 先写地址，片选置低，串行数据加载到移位寄存器
    for(i = 0; i < 8; i++) //
    {
        CLK = 0;     //时钟上升沿数据移入内部移位寄存器
        addr <<= 1;    //待发送的地址，每次左移一次，高位在前发送，
        DIN = CY;    //数据移位后，如果有溢出，则可以从进位位CY中获得溢出的数据位
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;    //下降沿时数据从DOUT移出
    }
    for(i = 0; i < 8; i++)
    {
        CLK = 0;   //
        dat <<= 1;   //发送数据
        DIN = CY;
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;
    }
    CS = 1;      //CS上升沿，数据锁存
}
//初始化函数
void init_max7221(void)
{
    write_data(0x09,0xff);    //编码模式
    write_data(0x0a,0x07);    //亮度控制
    write_data(0x0b,0x07);    //扫描数码管的位数
    write_data(0x0c,0x01);     //工作模式
}
