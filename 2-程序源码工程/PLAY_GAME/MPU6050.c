#include "MPU6050.h"
#include "Soft_I2C.h"
#include "oled.h"

void MPU_Delay_Ms(uint16_t Milliseconds)	//
{
    while(Milliseconds--)
        delay_ms(1);
}

//IIC连续写
//reg:要写入的寄存器地址
//len:要写入的长度
//buf:要写入的数据的首地址
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t reg, uint8_t len, uint8_t* buf)
{
    return i2c_mem_write(MPU_ADDR, reg, buf, len);
}

//IIC连续读
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t reg, uint8_t len, uint8_t* buf)
{
    return i2c_mem_read(MPU_ADDR, reg, buf, len);
}

//IIC写一个字节
//reg:寄存器地址
//Data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t Data)
{
    return i2c_mem_write(MPU_ADDR, reg, &Data, 1);
}

//IIC读一个字节
//reg:寄存器地址
//返回值:读到的数据
//uint8_t MPU_Read_Byte(uint8_t reg)
//{
//	uint8_t res;
//	i2c_mem_read(MPU_ADDR, reg, &res, 1);
//	return res;
//}

//写入8位寄存器的一个位
uint8_t MPU_Write_Bit(uint8_t addr, uint8_t bitNum, uint8_t Data)
{
    return i2c_write_bit(MPU_ADDR, addr, bitNum, Data);
}

//写入8位寄存器的多个位
uint8_t MPU_Write_Bits(uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t Data)
{
    return i2c_write_bits(MPU_ADDR, addr, bitStart, length, Data);
}

//读取一个位从8位器件的寄存器
uint8_t MPU_Read_Bit(uint8_t addr, uint8_t bitNum, uint8_t* Data)
{
    return i2c_read_bit(MPU_ADDR, addr, bitNum, Data);
}

//读取8位寄存器的多个位
uint8_t MPU_Read_Bits(uint8_t addr, uint8_t bitStart, uint8_t length, uint8_t* Data)
{
    return i2c_read_bits(MPU_ADDR, addr, bitStart, length, Data);
}

