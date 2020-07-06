#include<stdio.h>
#include<stdlib.h>             //可以改为单链表 

#define STACK_INIT_SIZE  100 //存储空间初始分配量
#define STACK_INCREMENT  10  //存储空间分配增量
#define TRUE       1
#define FALSE      0
//此代码为线性表实现栈的演示，鼓励同学们尝试用链表实现 
//栈可用于数制转换、括号匹配检验，带优先级表达式计算、迷宫求解等等
//思考 递归的实现原理及从操作系统角度递归的优缺点 
typedef int ElemType;
typedef struct{
    ElemType *base;   //栈底指针 
	ElemType *top;    //栈顶指针 
	int stacksize;	  //当前分配的存储空间 
}SqStack; 
SqStack *CreateStack();            //创建一个栈                ok 
int InitStack(SqStack *);          //初始化一个空栈            ok
int DestroyStack(SqStack *);       //销毁 S 栈                 ok
int ClearStack(SqStack *);         //清空 S 栈                 ok
int StackEmpty(SqStack *);         //判断是否是空栈            ok 
int StackLength(SqStack *);        //返回栈的长度              ok 
int GetTop(SqStack *,ElemType *);  //若栈不空，获取栈顶节点    ok
int Push(SqStack *,ElemType);      //入栈                      ok
int Pop(SqStack *,ElemType *);     //出栈                      ok
int StackTraverse(SqStack *S,int (*)(ElemType *)); //遍历栈    ok
int printElem(ElemType *);  //该函数应该在具体开发中实现，此为样例，不应该存在于头文件 

SqStack *CreateStack()  //创建栈 
{   SqStack *s;
    s=(SqStack *)malloc(sizeof(SqStack));
    InitStack(s);
    return s;
    
}
int InitStack(SqStack *S)       
{   S->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    if(!S->base) return 0;  //申请存储空间失败返回 
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;          //链表实现时可增加length变量，表示当前栈长 
    return 1;
}
int GetTop(SqStack *S,ElemType *e)
{   if(S->top == S->base) return 0;//空栈 
    *e = *(S->top-1);
	return 1; 
}
int Push(SqStack *S,ElemType e)//入栈
{    //插入节点 e ，栈顶入栈 
     if(S->top-S->base>=S->stacksize)  //栈已满 
     {   S->base = (ElemType *)realloc(S->base,(S->stacksize+STACK_INCREMENT)*sizeof(ElemType));
         if(!S->base) {printf("N"); return 0;} //扩充栈空间失败 
         S->top = S->base + S->stacksize;
         S->stacksize += STACK_INCREMENT;
	 }
     *S->top++=e;  //节点入栈  
     return 1; 
}
int Pop(SqStack *S,ElemType *e)//出栈 
{   if(S->top == S->base)  return 0; //空栈
    //*e = *--S->top; 
    *e=*S->top;*S->top--;  //指针指向栈顶的上一位 
    return 1;
}
int StackLength(SqStack *S)  //返回栈的长度
{  return S->top-S->base; 
}
int StackEmpty(SqStack *S)   //判断是否是空栈  
{  return  S->top==S->base;
}
int DestroyStack(SqStack *S) //销毁 S 栈 
{   free(S->base);
    S->base=NULL;
    S->top=NULL;
	S->stacksize=0;
    return 1;
}
int ClearStack(SqStack *S)   //清空 S 栈
{   S->top=S->base; 
    return 1; 
}
int StackTraverse(SqStack *S,int (*method)(ElemType *)) //遍历栈
{   ElemType *p;
    p=S->base;
    while(p!=S->top)
    {  method(p);
       p++;
	}
} 
int printElem(ElemType *e)  //该函数应该在具体开发中实现，此为样例，不应该存在于头文件 
{  printf("-->%d",*e);
}
main()
{   SqStack *s;
    int n=1;
    s=CreateStack(); 
    Push(s,1);
    Push(s,2);
    Push(s,5);
    Push(s,6);
    Push(s,7);
    //Pop(s,&n);
    //Pop(s,&n);
    StackTraverse(s,printElem);

}
