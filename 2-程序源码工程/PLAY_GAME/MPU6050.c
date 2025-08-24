#include "MPU6050.h"
#include "Soft_I2C.h"
#include "oled.h"

void MPU_Delay_Ms(uint16_t Milliseconds)	//
{
    while(Milliseconds--)
        delay_ms(1);
}

//IIC����д
//reg:Ҫд��ļĴ�����ַ
//len:Ҫд��ĳ���
//buf:Ҫд������ݵ��׵�ַ
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Write_Len(uint8_t reg, uint8_t len, uint8_t* buf)
{
    return i2c_mem_write(MPU_ADDR, reg, buf, len);
}

//IIC������
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Read_Len(uint8_t reg, uint8_t len, uint8_t* buf)
{
    return i2c_mem_read(MPU_ADDR, reg, buf, len);
}

//IICдһ���ֽ�
//reg:�Ĵ�����ַ
//Data:����
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t Data)
{
    return i2c_mem_write(MPU_ADDR, reg, &Data, 1);
}

//IIC��һ���ֽ�
//reg:�Ĵ�����ַ
//����ֵ:����������
//uint8_t MPU_Read_Byte(uint8_t reg)
//{
//	uint8_t res;
//	i2c_mem_read(MPU_ADDR, reg, &res, 1);
//	return res;
//}

//д��8λ�Ĵ�����һ��λ
uint8_t MPU_Write_Bit(uint8_t addr, uint8_t bitNum, uint8_t Data)
{
    return i2c_write_bit(MPU_ADDR, addr, bitNum, Data);
}

//д��8λ�Ĵ����Ķ��λ
uint8_t MPU_Write_Bits(uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t Data)
{
    return i2c_write_bits(MPU_ADDR, addr, bitStart, length, Data);
}

//��ȡһ��λ��8λ�����ļĴ���
uint8_t MPU_Read_Bit(uint8_t addr, uint8_t bitNum, uint8_t* Data)
{
    return i2c_read_bit(MPU_ADDR, addr, bitNum, Data);
}

//��ȡ8λ�Ĵ����Ķ��λ
uint8_t MPU_Read_Bits(uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t* Data)
{
    return i2c_read_bits(MPU_ADDR, addr, bitStart, length, Data);
}

