#include<stdio.h>
#include<stdlib.h>             //���Ը�Ϊ������ 

#define STACK_INIT_SIZE  100 //�洢�ռ��ʼ������
#define STACK_INCREMENT  10  //�洢�ռ��������
#define TRUE       1
#define FALSE      0
//�˴���Ϊ���Ա�ʵ��ջ����ʾ������ͬѧ�ǳ���������ʵ�� 
//ջ����������ת��������ƥ����飬�����ȼ����ʽ���㡢�Թ����ȵ�
//˼�� �ݹ��ʵ��ԭ���Ӳ���ϵͳ�Ƕȵݹ����ȱ�� 
typedef int ElemType;
typedef struct{
    ElemType *base;   //ջ��ָ�� 
	ElemType *top;    //ջ��ָ�� 
	int stacksize;	  //��ǰ����Ĵ洢�ռ� 
}SqStack; 
SqStack *CreateStack();            //����һ��ջ                ok 
int InitStack(SqStack *);          //��ʼ��һ����ջ            ok
int DestroyStack(SqStack *);       //���� S ջ                 ok
int ClearStack(SqStack *);         //��� S ջ                 ok
int StackEmpty(SqStack *);         //�ж��Ƿ��ǿ�ջ            ok 
int StackLength(SqStack *);        //����ջ�ĳ���              ok 
int GetTop(SqStack *,ElemType *);  //��ջ���գ���ȡջ���ڵ�    ok
int Push(SqStack *,ElemType);      //��ջ                      ok
int Pop(SqStack *,ElemType *);     //��ջ                      ok
int StackTraverse(SqStack *S,int (*)(ElemType *)); //����ջ    ok
int printElem(ElemType *);  //�ú���Ӧ���ھ��忪����ʵ�֣���Ϊ��������Ӧ�ô�����ͷ�ļ� 

SqStack *CreateStack()  //����ջ 
{   SqStack *s;
    s=(SqStack *)malloc(sizeof(SqStack));
    InitStack(s);
    return s;
    
}
int InitStack(SqStack *S)       
{   S->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    if(!S->base) return 0;  //����洢�ռ�ʧ�ܷ��� 
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;          //����ʵ��ʱ������length��������ʾ��ǰջ�� 
    return 1;
}
int GetTop(SqStack *S,ElemType *e)
{   if(S->top == S->base) return 0;//��ջ 
    *e = *(S->top-1);
	return 1; 
}
int Push(SqStack *S,ElemType e)//��ջ
{    //����ڵ� e ��ջ����ջ 
     if(S->top-S->base>=S->stacksize)  //ջ���� 
     {   S->base = (ElemType *)realloc(S->base,(S->stacksize+STACK_INCREMENT)*sizeof(ElemType));
         if(!S->base) {printf("N"); return 0;} //����ջ�ռ�ʧ�� 
         S->top = S->base + S->stacksize;
         S->stacksize += STACK_INCREMENT;
	 }
     *S->top++=e;  //�ڵ���ջ  
     return 1; 
}
int Pop(SqStack *S,ElemType *e)//��ջ 
{   if(S->top == S->base)  return 0; //��ջ
    //*e = *--S->top; 
    *e=*S->top;*S->top--;  //ָ��ָ��ջ������һλ 
    return 1;
}
int StackLength(SqStack *S)  //����ջ�ĳ���
{  return S->top-S->base; 
}
int StackEmpty(SqStack *S)   //�ж��Ƿ��ǿ�ջ  
{  return  S->top==S->base;
}
int DestroyStack(SqStack *S) //���� S ջ 
{   free(S->base);
    S->base=NULL;
    S->top=NULL;
	S->stacksize=0;
    return 1;
}
int ClearStack(SqStack *S)   //��� S ջ
{   S->top=S->base; 
    return 1; 
}
int StackTraverse(SqStack *S,int (*method)(ElemType *)) //����ջ
{   ElemType *p;
    p=S->base;
    while(p!=S->top)
    {  method(p);
       p++;
	}
} 
int printElem(ElemType *e)  //�ú���Ӧ���ھ��忪����ʵ�֣���Ϊ��������Ӧ�ô�����ͷ�ļ� 
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
