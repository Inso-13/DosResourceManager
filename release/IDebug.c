/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-8
    说明：为SVGA下的调试提供方便
*/


#include<DOS.H>
#include"IDebug.h"

/*
    函数功能：记录当前代码被执行的次数, 并在第n次执行时进入调试模式
    输入参数：n——当前代码需要执行的次数
    输出参数：无
    返回值：无
*/
void IDebug(int n)
{
    static int count;
    
    if(++count==n)
    {
        //断点区
        delay(10);
    }
}