#include "Stack.h"   
#include<math.h>
//TRUE �� FALSE ��Stack.h���Ѷ��� 
//#define TRUE       1      
//#define FALSE      0 
#define   SIGN    2
#define   NUM     3
#define   LENGTH  9
typedef struct{
	int type;
	float data;
}Struct_List;
int check_brackets(char *);//��������Ƿ�ƥ��                                /*---01---*/
int find_elem(char,char *);//�Ӹ��������в��Ҹ����ַ�                        /*---02---*/
int struct_the_str(char *,Struct_List *);//��ԭʼ�ַ������ʽ�ṹ�������ڼ���/*---03---*/ 
float calc(Struct_List *);//�Խṹ���ı��ʽ���д����ȼ�����                 /*---04---*/
int part_calc(SqStack *,SqStack *);//�����һ���ڲ���Ԫ���㣬���ѹջ      /*---05---*/ 
float add(float,float);                                                      /*---06---*/
float sub(float,float);                                                      /*---07---*/
float mul(float,float);                                                      /*---08---*/
float dive(float,float);                                                     /*---09---*/
float squ(float,float);//��ʱδ����                                          /*---10---*/
float l(float,float);  //��ʱδ����                                          /*---11---*/

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
    
    if(!check_brackets(str)) return 0; //���Ų�ƥ�䣬�˳� 
    struct_the_str(str,list); //�ṹ�����ʽ 
    result = calc(list);  //��ʼ���� 
    test(list); //���ڲ��ԣ��鿴�ṹ���� 
    printf("\n%s = %f",str,result);
}
int test(Struct_List *l)  //����ṹ���������ڲ��� 
{  int i=0;
   do
   {
   	 printf("%d: type:%d  data:%f\n",i,l[i].type,l[i].data);
   	 i++;
   }while(l[i].data!=8 || l[i].type!=SIGN);
   printf("%d: type:%d  data:%f\n",i,l[i].type,l[i].data);
}
int check_brackets(char *str)//��������Ƿ�ƥ��                              /*---01---*/
{   int i=0,index,pass=1;  
    float sign='?';//Ϊ�˹���һ�����͵�ջ�������Ҳ����Ϊfloat�� 
    SqStack *s=CreateStack();//��������ջ�������ʽ�������Ƿ�ƥ��
    Push(s,'#');//��ֹ������Pop����ջ���� 0��ǡ��ƥ�� 
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
    Pop(s,&sign); //������ 
    if(!StackEmpty(s))  pass=0;//��������з��ţ�ջ�л���ʣ�� 
    DestroyStack(s);
    return pass; 

}
int find_elem(char c,char *arr) //�Ӹ��������в��Ҹ����ַ�                   /*---02---*/
{   int i=0;
    while(arr[i]) 
    { if(c==arr[i]) return i;
      i++;
	}
    return -1;
}
int struct_the_str(char *str,Struct_List *list)                              /*---03---*/
{   //��ԭʼ�ַ������ʽ�ṹ�������ڼ���
    int i=0,j=0,k=0,index; 
    char number[16];
    
	while(str[i])
	{   if((index=find_elem(str[i],Sign))!=-1)  //������Ŵ��� 
	    {  list[j].type=SIGN;
	       list[j].data=(float)(index);
	       i++; 
		}
		else         //���������� 
		{   k=0;
		    do
		    {  number[k]=str[i];
			   k++; 
			   i++;
			   if(k==10) return 0; //������̫�󣬳���Χ 
			}while(find_elem(str[i],Sign)==-1 && str[i]!=0);
		    number[k]=0;//�ַ�����β�� 0
			
			list[j].type=NUM;
			list[j].data=atof(number);
		} 
        j++;  //�ṹ�������� �� 1	
	} 
	list[j].type=SIGN;
	list[j].data=(float)find_elem('#',Sign);
	
    return 1;
}
float calc(Struct_List *list)//�Խṹ���ı��ʽ���д����ȼ�����                 /*---04---*/
{   int i=0;
    float j,k,s=0.0,s_end,temp; 
    SqStack *S_Stack=CreateStack(); //����ջ 
	SqStack *D_Stack=CreateStack(); //��ֵջ
	float  result;
	
	Push(S_Stack,(float)find_elem('#',Sign)); //��ѹ��һ�� # �ͽṹ��������� #��Ӧ 
	s_end = (float)find_elem('#',Sign); 
	while( s!=s_end || !(list[i].type==SIGN && list[i].data==s_end) )
	{   if(list[i].type==NUM) //��ǰ��Ϊ����ʱ��ֱ������ֵջ 
	    {   Push(D_Stack,list[i].data);
	        i++;
		}
		else//��ǰ��Ϊ����ʱ������һ�����ŶԱ����ȼ���������ջ���Ǽ��� 
		{   GetTop(S_Stack,&j); //��ȡ����ջ������ 
		    k=list[i].data;     //��ǰ���� 
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
int part_calc(SqStack *ss,SqStack *ds)//�����һ���ڲ���Ԫ���㣬���ѹջ      /*---05---*/ 
{   float f1,f2,s,result;
    
	Pop(ds,&f2);  //��ջ�ڶ�����  һ��Ҫע��˳�򣡣��� 
    Pop(ds,&f1);  //��ջ��һ���� 
    Pop(ss,&s);   //��ջ������� 

    result=operfuncp[(int)s](f1,f2);  //���ú���ָ�����飬���������switch 
/*  switch((int)s)
	{   case 0:  result=add(f1,f2); break;   
	    case 1:  result=sub(f1,f2); break;
	    case 2:  result=mul(f1,f2); break;
	    case 3:  result=dive(f1,f2);break;
	    // 4,5,6,7 δʵ�� 
	} 
*/
	Push(ds,result); //�������Ż�����ջ 
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
float squ(float f1,float f2)//��ʱδ����                                      /*---10---*/
{   return pow(f1,f2);     }
float l(float f1,float f2) //��ʱδ����                                       /*---11---*/
{   return log(f2)/log(f1);}
