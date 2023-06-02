#include "seg.h"
#include <intrins.h>

sbit DIN = P2^0;     //���ݴ�������
sbit CS = P2^1;     //Ƭѡ��
sbit CLK = P2^2;    //��λʱ�Ӷ�



//д���ݺ���
void write_data(unsigned char addr,unsigned char dat)
{
    unsigned char i;
    CS = 0;        // ��д��ַ��Ƭѡ�õͣ��������ݼ��ص���λ�Ĵ���
    for(i = 0; i < 8; i++) //
    {
        CLK = 0;     //ʱ�����������������ڲ���λ�Ĵ���
        addr <<= 1;    //�����͵ĵ�ַ��ÿ������һ�Σ���λ��ǰ���ͣ�
        DIN = CY;    //������λ����������������Դӽ�λλCY�л�����������λ
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;    //�½���ʱ���ݴ�DOUT�Ƴ�
    }
    for(i = 0; i < 8; i++)
    {
        CLK = 0;   //
        dat <<= 1;   //��������
        DIN = CY;
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;
    }
    CS = 1;      //CS�����أ���������
}
//��ʼ������
void init_max7221(void)
{
    write_data(0x09,0xff);    //����ģʽ
    write_data(0x0a,0x07);    //���ȿ���
    write_data(0x0b,0x07);    //ɨ������ܵ�λ��
    write_data(0x0c,0x01);     //����ģʽ
}
