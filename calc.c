#include "Stack.h"   
#include<math.h>
//TRUE 和 FALSE 在Stack.h中已定义 
//#define TRUE       1      
//#define FALSE      0 
#define   SIGN    2
#define   NUM     3
#define   LENGTH  9
typedef struct{
	int type;
	float data;
}Struct_List;
int check_brackets(char *);//检查括号是否匹配                                /*---01---*/
int find_elem(char,char *);//从给定数组中查找给定字符                        /*---02---*/
int struct_the_str(char *,Struct_List *);//把原始字符串表达式结构化，便于计算/*---03---*/ 
float calc(Struct_List *);//对结构化的表达式进行带优先级计算                 /*---04---*/
int part_calc(SqStack *,SqStack *);//查表后的一次内部二元计算，结果压栈      /*---05---*/ 
float add(float,float);                                                      /*---06---*/
float sub(float,float);                                                      /*---07---*/
float mul(float,float);                                                      /*---08---*/
float dive(float,float);                                                     /*---09---*/
float squ(float,float);//暂时未启用                                          /*---10---*/
float l(float,float);  //暂时未启用                                          /*---11---*/

char Brackets[20]={"()[]"};
char Sign[20]={"+-*/^|()#"};
//float (*operfuncp[10])(float,float)={add,sub,mul,dive,squ,l};
typedef float (*FP)(float,float);
FP operfuncp[10]={add,sub,mul,dive,squ,l};

char grade[LENGTH][LENGTH]=
/*          +   -   *   /   ^   |   (   )   #  */
/* + */ {  '>','>','<','<','<','<','<','>','>',
/* - */    '>','>','<','<','<','<','<','>','>', 	
/* * */    '>','>','>','>','<','<','<','>','>',
/* / */    '>','>','>','>','<','<','<','>','>',
/* ^ */    '>','>','>','>','<','<','<','>','>',
/* | */    '>','>','>','>','<','<','<','>','>',
/* ( */    '<','<','<','<','<','<','<','=','E',
/* ) */    '>','>','>','>','>','>','E','>','>',
/* # */    '<','<','<','<','<','<','<','E','='  };

main()
{   char str[80]; 
    Struct_List list[80]; 
    float result;
    
    printf("please input the mathematical expression:\n");
    gets(str);
    
    if(!check_brackets(str)) return 0; //括号不匹配，退出 
    struct_the_str(str,list); //结构化表达式 
    result = calc(list);  //开始计算 
    test(list); //用于测试，查看结构化链 
    printf("\n%s = %f",str,result);
}
int test(Struct_List *l)  //输出结构化串，用于测试 
{  int i=0;
   do
   {
   	 printf("%d: type:%d  data:%f\n",i,l[i].type,l[i].data);
   	 i++;
   }while(l[i].data!=8 || l[i].type!=SIGN);
   printf("%d: type:%d  data:%f\n",i,l[i].type,l[i].data);
}
int check_brackets(char *str)//检查括号是否匹配                              /*---01---*/
{   int i=0,index,pass=1;  
    float sign='?';//为了公用一个类型的栈，运算符也定义为float型 
    SqStack *s=CreateStack();//创建符号栈，检测表达式的括号是否匹配
    Push(s,'#');//防止上来先Pop，空栈返回 0，恰巧匹配 
	while(str[i])
    {   if((index=find_elem(str[i],Brackets))!=-1)
   	    {   if(!(index%2))  
		    {  Push(s,index);
			}
			else
			{  Pop(s,&sign);
			   if(index!=sign+1) 
			   { pass=0;
			     break;
			   }
			}
	    }
        i++;		    
    } 
    Pop(s,&sign); //检测完毕 
    if(!StackEmpty(s))  pass=0;//检测完所有符号，栈中还有剩余 
    DestroyStack(s);
    return pass; 

}
int find_elem(char c,char *arr) //从给定数组中查找给定字符                   /*---02---*/
{   int i=0;
    while(arr[i]) 
    { if(c==arr[i]) return i;
      i++;
	}
    return -1;
}
int struct_the_str(char *str,Struct_List *list)                              /*---03---*/
{   //把原始字符串表达式结构化，便于计算
    int i=0,j=0,k=0,index; 
    char number[16];
    
	while(str[i])
	{   if((index=find_elem(str[i],Sign))!=-1)  //运算符号处理 
	    {  list[j].type=SIGN;
	       list[j].data=(float)(index);
	       i++; 
		}
		else         //运算数处理 
		{   k=0;
		    do
		    {  number[k]=str[i];
			   k++; 
			   i++;
			   if(k==10) return 0; //操作数太大，超范围 
			}while(find_elem(str[i],Sign)==-1 && str[i]!=0);
		    number[k]=0;//字符串结尾补 0
			
			list[j].type=NUM;
			list[j].data=atof(number);
		} 
        j++;  //结构化串索引 加 1	
	} 
	list[j].type=SIGN;
	list[j].data=(float)find_elem('#',Sign);
	
    return 1;
}
float calc(Struct_List *list)//对结构化的表达式进行带优先级计算                 /*---04---*/
{   int i=0;
    float j,k,s=0.0,s_end,temp; 
    SqStack *S_Stack=CreateStack(); //符号栈 
	SqStack *D_Stack=CreateStack(); //数值栈
	float  result;
	
	Push(S_Stack,(float)find_elem('#',Sign)); //先压入一个 # 和结构化串的最后 #对应 
	s_end = (float)find_elem('#',Sign); 
	while( s!=s_end || !(list[i].type==SIGN && list[i].data==s_end) )
	{   if(list[i].type==NUM) //当前点为数字时，直接入数值栈 
	    {   Push(D_Stack,list[i].data);
	        i++;
		}
		else//当前点为符号时，与上一个符号对比优先级，决定入栈还是计算 
		{   GetTop(S_Stack,&j); //获取符号栈顶符号 
		    k=list[i].data;     //当前符号 
		    switch(grade[(int)j][(int)k])
			{   case '>': part_calc(S_Stack,D_Stack);     break;
			    case '<': Push(S_Stack,list[i].data);i++; break;
			    case '=': Pop(S_Stack,&temp);           i++; 
			} 
		}
		GetTop(S_Stack,&s);
	}
	Pop(D_Stack,&result);
    return result;
}
int part_calc(SqStack *ss,SqStack *ds)//查表后的一次内部二元计算，结果压栈      /*---05---*/ 
{   float f1,f2,s,result;
    
	Pop(ds,&f2);  //出栈第二个数  一定要注意顺序！！！ 
    Pop(ds,&f1);  //出栈第一个数 
    Pop(ss,&s);   //出栈计算符号 

    result=operfuncp[(int)s](f1,f2);  //采用函数指针数组，代替下面的switch 
/*  switch((int)s)
	{   case 0:  result=add(f1,f2); break;   
	    case 1:  result=sub(f1,f2); break;
	    case 2:  result=mul(f1,f2); break;
	    case 3:  result=dive(f1,f2);break;
	    // 4,5,6,7 未实现 
	} 
*/
	Push(ds,result); //计算结果放回数据栈 
	return 1;
}
float add(float f1,float f2)                                                  /*---06---*/
{   return f1+f2;          }
float sub(float f1,float f2)                                                  /*---07---*/
{   return f1-f2;          }
float mul(float f1,float f2)                                                  /*---08---*/
{   return f1*f2;          }
float dive(float f1,float f2)                                                 /*---09---*/
{   return f1/f2;          }
float squ(float f1,float f2)//暂时未启用                                      /*---10---*/
{   return pow(f1,f2);     }
float l(float f1,float f2) //暂时未启用                                       /*---11---*/
{   return log(f2)/log(f1);}
