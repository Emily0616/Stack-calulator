#include<iostream>
#include<cmath>
#include<string>
#include<iomanip> //��ʽ���������
using namespace std;
void menu();//λ��calculate��������Ĳ˵���������
void guide();//λ�������������ָ������������

double D_Operate(double x,char op,double y)//˫Ŀ����������㶨��
{
	double a;//������
	switch(op)
	{
	case'+': a=x+y;break;
	case'-': a=x-y;break;
	case'*': a=x*y;break;
	case'/': a=x/y;break;
	case'^': a=pow(x,y);break;//����������˷��Ϳ���
	}//��Ϊ��������double�������� ��˲�����ȡģ����
	return a;     
}

double S_Operate(char op,double x)//ǰ׺��Ŀ����������㶨��
{
	double a;//������
	switch(op)
	{
	case's': a=sin(x);break;
	case'c': a=cos(x);break;
	case't': a=tan(x);break;
	case'l': a=log10(x);break;//��10Ϊ�׵Ķ���
	case'n': a=log(x);break;//��e��2.718281828��Ϊ�׵Ķ���
	case'#': a=-x;break;//ȡ���Ŵ��渺�� ����ΪһԪ����
	}
	return a;
}

char Precede(char op1,char op2) //�жϷ��ŵ����ȼ� op1�ڷ��صĽ��������� op2���ұ�
//�����ж�����������ȼ� �Ծ����ǰ������ѹջ ���ǰ�ջ�ڵ���������������м���
{
	if( ( (op1=='+'||op1=='-') && (op2=='+'||op2=='-'||op2==')'||op2=='=') ) ||\
		( (op1=='*'||op1=='/') && (op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='=') )\
		||(op1=='^'&&(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='='||op2=='s'||op2=='c'||op2=='t'||op2=='#'||op2=='l'||op2=='n'))\
		||((op1=='#'||op1=='s'||op1=='c'||op1=='t'||op1=='l'||op1=='n')&&(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='='||op2=='s'||op2=='c'||op2=='t'||op2=='#'||op2=='l'||op2=='n')))
		return '>';//��������� ջ����������ȼ����ڴ�������� �赯ջ
	if((op1=='('&&op2==')')||(op1=='='&&op2=='='))
		return '=';
	else
		return '<';
}

int illegal_char(string s,int i)//�Ƿ������ַ��ж�����
{
	int j=0;
	while(j<i)
	{
		if(s[j]>='0'&&s[j]<='9')
			j++;
		
		else if(s[j]=='+'||s[j]=='-'||s[j]=='*'||s[j]=='/'||s[j]=='.'||s[j]=='('||s[j]==')'||s[j]=='^'||s[j]=='!'||s[j]=='e'||s[j]=='#')
			j++;
		else if((s[j]=='p'&&s[j+1]=='i')||(s[j]=='l'&&s[j+1]=='n'))
			j+=2;
		
		else if((s[j]=='s'&&s[j+1]=='i'&&s[j+2]=='n')||(s[j]=='c'&&s[j+1]=='o'&&s[j+2]=='s')||(s[j]=='t'&&s[j+1]=='a'&&s[j+2]=='n')||(s[j]=='l'&&s[j+1]=='o'&&s[j+2]=='g'))
			j+=3;
		//���϶��Ǳ�׼�������ַ�������� ��������������ʽ���ַ� ���ǷǷ�����
		else
		{
			cout<<"������ֹ�����ڷǷ����ַ����룡����"<<endl;
			return 0;
		}
	}
	return 1;//û�зǷ��ַ� ����1 ���򷵻�0
}

int match(string s)//ջ�ṹ������ƥ���⺯��
{
	int i=0,top=0;
	char stack[50];
	while(s[i]!='\0') //'\0'���ַ���������
	{
		if(s[i]=='(')
		{
			stack[top]=s[i];
			top++;
		}
		//push ������ѹ��ջ��
		if(s[i]==')')
			if(stack[top-1]=='(')
			{
				int a=i+1;//���ã�
				stack[top-1]=NULL;
				top--;//����������ƥ��������ŵ�����top��ֵ����0
			}
			else
			{
				cout<<"������������"<<endl;
				return 0;//���������� ����ʧ�� ���طǷ�
			}//pop'('
			i++;
	}
	if (top!=0)
	{
		cout<<"������������"<<endl;
		return 0;//���������� ����ʧ�� ���طǷ�
	}
	return 1;//���غϷ�
}

class NUMstack//������ջ
{
public:
	double num[1000];
	int top;
	
	//��ʼ��ջ���ջ��ָ���õ�
	void start()
	{
		for(int i=0;i<1000;i++)
			num[i]=0;
		top=0;
	}
	
	void push(char a)//��Ϊ�ж�λ����������˲���һѹջ������ջ��ָ��
	{
		num[top]=num[top]*10+(a-'0');//���ַ�ת������Ϊÿ����ջ֮ǰҪ��10 ���Գ�ʼ��Ҫ��0
	}
	
	double pop()
	{
		top--;
		double number=num[top];
		num[top]=0;
		return number;
	}//��ջ���� ����ջ��Ԫ�� ջ����0 topָ���½�
	
	double getTop()//ȡջ��Ԫ�ص����ص�ջ
	{
		return num[top-1];
	}

	void lift()//����topָ��ĺ���
	{
		top++;
	}
};


class OPERstack//�����ջ
{
public:
	char oper[1000];
	int top;
	void start()//��ʼ������ջ���ջ�׷�һ"="�����ж���ʽ����
	{
		oper[0]='=';
		for(int i=1;i<1000;i++)
			oper[i]=NULL;
		top=1;//ջ��ָ������ջ�׵���һλ
	}
	
	void push(char a)
	{  
		oper[top]=a;
		top++;//������ջ��ͬһѹջ�Ϳ�������ָ��
	}

	char pop()
	{
		top--;
		char op=oper[top];
		oper[top]=NULL;
		return op;//��������� ���ڼ���
	}

	char getTop()
	{
		return oper[top-1];//ȡջ������ ������ջ �������ж����ȼ�
	}
};

void calculate(string equation)//��ʽ���㺯�����ؼ�������
{
	NUMstack number;//����������ջ����number
	OPERstack oper;//���������ջ����oper

	number.start();
	oper.start();//������ջ��ʼ��

	int i=0,len=0,k;
	char p,sig;
	double yuan1,yuan2;

	while(equation[i]!='\0')
	{
		len++;
		i++;
	}//�����ʽ����len

	if(equation[len-1]!='=')
	{
		cout<<"��������û��������ֹ����--�Ⱥš�=��"<<endl;
		return;//�����û�н������Ⱥ�"="
	}
	
	int le;
	le=illegal_char(equation,len-1);
	if(le==0)
		return;//�зǷ��ַ� �����к�������

	le=match(equation);
	if(le==0)
		return;//����ƥ��Ƿ� �����к�������

	for(i=0;i<len;i++)//����ȷ���Ϸ���ʼ������ʽ
	{
		if(equation[i]=='!')//�׳��Ǻ�׺��Ŀ������������м���
		{
			yuan1=number.pop();//����ջ��Ԫ�����׳�
			if (yuan1==0)
			{
				number.num[number.top]=0;//0�Ľ׳�Ϊ0 ѹ�����ջ
				number.lift();
			}
			else
			{
				number.num[number.top]=1;
				for(k=1;k<=yuan1;k++)//�׳�ѭ��
					number.num[number.top]=k*number.num[number.top];
				number.lift();//�����վ
			}
		}
		else if(equation[i]>='0'&&equation[i]<='9')
		{
			number.push(equation[i]);//ѹ�����ַ���ջ
			if((equation[i+1]<'0'||equation[i+1]>'9')&&equation[i+1]!='.')
				number.lift();//��������λ��������ȡ��Ϻ�������ջջ��ָ���������
		}
		else if(equation[i]=='p')
		{
			number.num[number.top]=3.1415926536;//piֵ���� Բ���� Ҫѹ������ջ
			number.lift();
			i++;//pi�������ַ�����Ҫ�ƶ�ɨ����ʽ��ָ��������һ��
		}
		else if(equation[i]=='e')
		{
			number.num[number.top]=2.718281828459;//e ��Ȼ�������� ѹ��������ջ
			number.lift();
		}
		else if(equation[i]=='.')//С��ѹջ����
		{
			int x=1;
			while(equation[i+x]>='0'&&equation[i+x]<='9')
			{
				number.num[number.top]+=((equation[i+x]-'0')/pow(10,x));//��xλС����ջ
				x++;
			}
			x--;
			number.lift();
			i=i+x;
		}
		else if(equation[i]=='(')
		{
			oper.push(equation[i]);//������������ѹջ
		}
		else//�� �׳� �������ж���Ϻ�����������ķ�������
		{
			if(oper.top==1)//�����ջΪ�������������������ջ
			{
				if(equation[i]=='l'&&equation[i+1]=='o')
					oper.push('l');
				else if(equation[i]=='l'&&equation[i+1]=='n')
					oper.push('n');//��Ϊlog��ln����Сд��ĸl��ͷ����Ҫ���������
				else
					oper.push(equation[i]);
			}
			else//�����ջ��Ϊ����Ҫ�������ȼ��ж�
			{
				char temp1=oper.getTop();//ȡ��ջ������
				char temp2;//����ջ����
				if(equation[i]=='l'&&equation[i+1]=='o')
					temp2='l';
				else if(equation[i]=='l'&&equation[i+1]=='n')
					temp2='n';//log��ln���ٴ�����
				else
					temp2=equation[i];
				p=Precede(temp1,temp2);
				if(p=='<')
					oper.push(temp2);//ջ�������ȼ��ϵ����ڴ�����������Ϳ�����ջ��
				if(p=='>'||p=='=')
				{
					char rep=p;//��ջ�������ȼ������ڴ���ջ�ķ��� �������ջ��ͣ�ص�ջ
					//��������ֱ�����ڴ���ջ����Ϊֹ rep���ڼ�¼�ȽϽ�� Ҫ��ν����ж�
					while((rep=='>'||p=='=')&&(oper.top-1>0))
					{ 
						sig=oper.pop();
						yuan1=number.pop();
						yuan2=number.getTop();//��ǰ��һ��������ֻҪȡ�ò�Ҫ������
						if(sig=='/'&&yuan1==0)//yuan1��˫Ŀ���������ĵڶ�����Ԫ
						{
							cout<<"����ʱ�����������˳���Ϊ0���������"<<endl;
							return;
						}
						if(sig=='^'&&yuan2<0&&yuan1>0&&yuan1<1&&(static_cast <int>(1/yuan1))%2==0)
							//�Ը�����ż�θ��ŵ�����
						{
							cout<<"����ʱ�����������˸�����ż�θ��ŵ��������"<<endl;
							return;
						}

						if(sig=='#'||sig=='s'||sig=='c'||sig=='t'||sig=='l'||sig=='n')//��Ϊǰ׺��Ŀ�����
						{
							double tt;
							tt=S_Operate(sig,yuan1);
							number.num[number.top]=tt;//������ѹ��ԭ��yuan1��ջ�ڵ�λ��
							number.lift();//����ָ��
							temp1=oper.getTop();
							rep=Precede(temp1,temp2);//�������ȼ�
						}
						else
						{
							number.num[(number.top)-1]=D_Operate(yuan2,sig,yuan1);
							temp1=oper.getTop();
							rep=Precede(temp1,temp2);//˫Ŀ������ļ���
						}
					}
					if(equation[i]==')')//���ջ�����������Ҫ����֮ƥ��������ŵ���ջ��
						oper.pop();
					else if(equation[i]=='l'&&equation[i+1]=='o')
						oper.push('l');//����log��l
					else if((equation[i]=='l')&&(equation[i+1]=='n'))
						oper.push('n');//����ln��n
					else
						oper.push(equation[i]);
				}
			}   
			if(equation[i]=='s'||equation[i]=='c'||equation[i]=='t'||(equation[i]=='l'&&equation[i+1]=='o'))
				i=i+2;
			if(equation[i]=='l'&&equation[i+1]=='n')
				i++;
			//���ڲ�ֹһ���ַ�������� sin log ln�ȵ� Ҫ�ƶ�ɨ����ʽ��ָ�� ������һ��������
		}
 }
 
 if(number.num[0]==ceil(number.num[0]))
	 cout<<equation<<number.num[0]<<endl;
 else
 {
	 cout<<equation<<fixed<<setprecision(8)<<number.num[0]<<endl;
 }//���������ƾ���8λС��
 
 //����ʱ������������վ������Ĵ����
}

void menu()//�˵�����
{
	cout<<"ʵ���Ϳ�ѧ��ʽ������"<<endl;
	
	cout<<endl;
	cout<<"��ӭʹ��o(��_��)o !!!"<<endl;
	cout<<"��ѡ������Ҫ�Ĺ��ܣ���0��1����2��"<<endl;
	cout<<"----------"<<endl;
	cout<<"1.ʹ��˵��"<<endl;
	cout<<"2.������ʽ"<<endl;
	cout<<"0.�˳�����"<<endl;
	cout<<"----------"<<endl;
	cout<<"���ѡ���ǣ�";
	int choice;
	cin>>choice;
	switch(choice)
	{
	case 0:return;
	case 1:guide();break;
	case 2:
		{
			system("cls");
			char go_on='y';
			string equation;
			while(go_on=='y')
			{
				cout<<endl<<endl<<"��������ʽ����=���Ⱥţ���������Ӣ��״̬�����룩"<<endl;
				cin>>equation;
				calculate(equation);
				cout<<"����ʹ������������y ��������n��";
				cin>>go_on;//����ѭ��������ʽ����
			}
			system("cls");
			menu();
		}
	}
	
}
void main()
{
	menu();
}

void guide()//����������˵����
{
	system("cls");
	cout<<"ʹ��˵����"<<endl;
	cout<<"������ʽʱ���밴�����й������룺"<<endl;
	cout<<"1.��������+�� -�� *�� /�����������룬�������»���(#)���棬ע�⽫����������𣻿�������()�綨���ȼ�"<<endl;
	cout<<"2.^��:���������³˷�����x^y(x��y�η�)��23^6����23��6�η�������Ҳ����������81^(1/4)[����81^0.25]��ʾ81��4�η�"<<endl;
	cout<<"3.!�׳�:6!��ʾ1*2*3*4*5*6��(1+3)!��ʾ4�Ľ׳ˣ������24��1+3!��ʾ1�ټ���3���׳˵Ľ������7"<<endl;
	cout<<"4.pi����Բ���ʣ���3.1415926536�������������û��Ƚ������Ǻ������㣻��������������sin����������cos����������tan��sin(pi/2)���Ƕ���֮�л��ȶ�Ӧ������ֵ��ע��һ��Ҫ�����ţ������������ƣ�"<<endl;
	cout<<"5.������10Ϊ�׵Ķ���������log����log1000=3��������e��2.718281828��Ϊ�׵���Ȼ����������ln����lne^4=4,ע��ָ��������Ҫ�淶����lne^4=4������(lne)^4=1��������ʽ�Ķ���Ҫ�ڶ������ź������ʽ����������ln(3+6*9)��������������Ϊ�׵Ķ��������ö������׹�ʽ������2Ϊ�ף�16�Ķ���������ln16/ln2����log16/log2�������4"<<endl;
	cout<<"6.��ֱ������e��pi����ֵ����"<<endl;
	cout<<"7.��������������ֻ��С����();������������[ ]�ʹ�����{ },����ʽһ��Ҫ�ԵȺţ�=������"<<endl;
	system("pause");
	system("cls");
	menu();
}