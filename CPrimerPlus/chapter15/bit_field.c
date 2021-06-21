#include <stdio.h>

struct {
	unsigned int autfd : 1;
	unsigned int bldfc : 1;
	unsigned int undln : 1;
	unsigned int itals : 1;
} prnt;

struct {
	unsigned int code1 : 2;
	unsigned int code2 : 2;
	unsigned int code3 : 8;
} prcode;

struct {
	unsigned int field1	: 1;
	unsigned int		: 2;	//空隙
	unsigned int field2 : 1;
	unsigned int		: 0;
	unsigned int field3 : 1;	//存储在下一个unsigned int中
} stuff;


int main(void)
{
	prnt.itals = 0;
	prnt.undln = 1;

	prcode.code1 = 0;
	prcode.code2 = 3;
	prcode.code3 = 102;

	return 0;
}

/* 
笔记：
	1. 赋值不可超出字段可容纳范围		
	2. 如果声明的总位数超过一个unsigned int大小，则会用到下一个unsigned类型的存储位置
	3. 如果越界， 编译器会自动移动跨界字段保持unsigned int 边界对齐，导致第一个unsigned int
		中会留下一个未命名的“洞”
	4. 使用未命名的字段宽度填充未命名的洞，使用一个宽度为0的未命名字段迫使下一个字段与下一个整数对其
*/
