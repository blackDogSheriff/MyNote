#include <stdio.h>
int main(void)
{
	//只允许MASK中打开的位显示
	int flag = 10
	flags = flags & MASK;
	//flags &= MASK;

	ch &= 0xff;
	ch &= 0377;

	//打开位:按位或（和1按位或一定打开）
	flags = flags & MASK;

	//关闭位:按位与（和0按位与一定关闭）
	flags = flags & ~MASK;

	//切换位:按位异或（和0不变，和1相反）
	flags = flags ^ MASK;

	//检查位:检查对应的位是否为1
	if (flags & MASK) == MASK)

	return 0;
}
