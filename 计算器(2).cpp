#include<iostream>
#include<cmath>
#include<string>
#include<iomanip> //格式化输入输出
using namespace std;
void menu();//位于calculate函数后面的菜单函数声明
void guide();//位于主函数后面的指导函数的声明

double D_Operate(double x,char op,double y)//双目运算符的运算定义
{
	double a;//计算结果
	switch(op)
	{
	case'+': a=x+y;break;
	case'-': a=x-y;break;
	case'*': a=x*y;break;
	case'/': a=x/y;break;
	case'^': a=pow(x,y);break;//幂运算包括乘方和开方
	}//因为都是利用double进行运算 因此不定义取模运算
	return a;     
}

double S_Operate(char op,double x)//前缀单目运算符的运算定义
{
	double a;//计算结果
	switch(op)
	{
	case's': a=sin(x);break;
	case'c': a=cos(x);break;
	case't': a=tan(x);break;
	case'l': a=log10(x);break;//以10为底的对数
	case'n': a=log(x);break;//以e（2.718281828）为底的对数
	case'#': a=-x;break;//取井号代替负号 定义为一元运算
	}
	return a;
}

char Precede(char op1,char op2) //判断符号的优先级 op1在返回的结果符的左边 op2在右边
//用于判定运算符的优先级 以决定是把运算符压栈 还是把栈内的运算符弹出来进行计算
{
	if( ( (op1=='+'||op1=='-') && (op2=='+'||op2=='-'||op2==')'||op2=='=') ) ||\
		( (op1=='*'||op1=='/') && (op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='=') )\
		||(op1=='^'&&(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='='||op2=='s'||op2=='c'||op2=='t'||op2=='#'||op2=='l'||op2=='n'))\
		||((op1=='#'||op1=='s'||op1=='c'||op1=='t'||op1=='l'||op1=='n')&&(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='='||op2=='s'||op2=='c'||op2=='t'||op2=='#'||op2=='l'||op2=='n')))
		return '>';//上述情况下 栈顶运算符优先级高于待定运算符 需弹栈
	if((op1=='('&&op2==')')||(op1=='='&&op2=='='))
		return '=';
	else
		return '<';
}

int illegal_char(string s,int i)//非法输入字符判定函数
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
		//以上都是标准的数字字符和运算符 如若存在其他形式的字符 则是非法输入
		else
		{
			cout<<"程序终止，存在非法的字符输入！！！"<<endl;
			return 0;
		}
	}
	return 1;//没有非法字符 返回1 否则返回0
}

int match(string s)//栈结构的括号匹配检测函数
{
	int i=0,top=0;
	char stack[50];
	while(s[i]!='\0') //'\0'是字符串结束符
	{
		if(s[i]=='(')
		{
			stack[top]=s[i];
			top++;
		}
		//push 左括号压入栈内
		if(s[i]==')')
			if(stack[top-1]=='(')
			{
				int a=i+1;//作用？
				stack[top-1]=NULL;
				top--;//把与右括号匹配的左括号弹掉后，top的值返回0
			}
			else
			{
				cout<<"括号输入有误"<<endl;
				return 0;//多了右括号 括号失陪 返回非法
			}//pop'('
			i++;
	}
	if (top!=0)
	{
		cout<<"括号输入有误"<<endl;
		return 0;//多了左括号 括号失陪 返回非法
	}
	return 1;//返回合法
}

class NUMstack//运算数栈
{
public:
	double num[1000];
	int top;
	
	//初始化栈清空栈顶指针置底
	void start()
	{
		for(int i=0;i<1000;i++)
			num[i]=0;
		top=0;
	}
	
	void push(char a)//因为有多位数的运算因此不能一压栈就提升栈顶指针
	{
		num[top]=num[top]*10+(a-'0');//把字符转成数因为每次入栈之前要乘10 所以初始化要清0
	}
	
	double pop()
	{
		top--;
		double number=num[top];
		num[top]=0;
		return number;
	}//弹栈函数 弹掉栈顶元素 栈顶归0 top指针下降
	
	double getTop()//取栈顶元素但不必弹栈
	{
		return num[top-1];
	}

	void lift()//提升top指针的函数
	{
		top++;
	}
};


class OPERstack//运算符栈
{
public:
	char oper[1000];
	int top;
	void start()//初始化函数栈清空栈底放一"="用于判定算式结束
	{
		oper[0]='=';
		for(int i=1;i<1000;i++)
			oper[i]=NULL;
		top=1;//栈顶指针置于栈底的上一位
	}
	
	void push(char a)
	{  
		oper[top]=a;
		top++;//与数字栈不同一压栈就可以提升指针
	}

	char pop()
	{
		top--;
		char op=oper[top];
		oper[top]=NULL;
		return op;//弹出计算符 用于计算
	}

	char getTop()
	{
		return oper[top-1];//取栈顶符号 但不弹栈 可用于判定优先级
	}
};

void calculate(string equation)//算式计算函数（关键函数）
{
	NUMstack number;//定义运算数栈变量number
	OPERstack oper;//定义运算符栈变量oper

	number.start();
	oper.start();//把两个栈初始化

	int i=0,len=0,k;
	char p,sig;
	double yuan1,yuan2;

	while(equation[i]!='\0')
	{
		len++;
		i++;
	}//计算等式长度len

	if(equation[len-1]!='=')
	{
		cout<<"输入有误没有输入终止符号--等号“=”"<<endl;
		return;//检测有没有结束符等号"="
	}
	
	int le;
	le=illegal_char(equation,len-1);
	if(le==0)
		return;//有非法字符 不进行后续计算

	le=match(equation);
	if(le==0)
		return;//括号匹配非法 不进行后续计算

	for(i=0;i<len;i++)//初步确定合法后开始计算算式
	{
		if(equation[i]=='!')//阶乘是后缀单目运算符单独进行计算
		{
			yuan1=number.pop();//弹出栈顶元素做阶乘
			if (yuan1==0)
			{
				number.num[number.top]=0;//0的阶乘为0 压结果入栈
				number.lift();
			}
			else
			{
				number.num[number.top]=1;
				for(k=1;k<=yuan1;k++)//阶乘循环
					number.num[number.top]=k*number.num[number.top];
				number.lift();//结果入站
			}
		}
		else if(equation[i]>='0'&&equation[i]<='9')
		{
			number.push(equation[i]);//压数字字符入栈
			if((equation[i+1]<'0'||equation[i+1]>'9')&&equation[i+1]!='.')
				number.lift();//当整个多位运算数读取完毕后，运算数栈栈顶指针才能提升
		}
		else if(equation[i]=='p')
		{
			number.num[number.top]=3.1415926536;//pi值即π 圆周率 要压入数字栈
			number.lift();
			i++;//pi是两个字符所以要移动扫描算式的指针往后跳一个
		}
		else if(equation[i]=='e')
		{
			number.num[number.top]=2.718281828459;//e 自然对数底数 压入运算数栈
			number.lift();
		}
		else if(equation[i]=='.')//小数压栈代码
		{
			int x=1;
			while(equation[i+x]>='0'&&equation[i+x]<='9')
			{
				number.num[number.top]+=((equation[i+x]-'0')/pow(10,x));//第x位小数入栈
				x++;
			}
			x--;
			number.lift();
			i=i+x;
		}
		else if(equation[i]=='(')
		{
			oper.push(equation[i]);//左括号无条件压栈
		}
		else//数 阶乘 左括号判断完毕后其他运算符的分类讨论
		{
			if(oper.top==1)//运算符栈为空运算符可以无条件入栈
			{
				if(equation[i]=='l'&&equation[i+1]=='o')
					oper.push('l');
				else if(equation[i]=='l'&&equation[i+1]=='n')
					oper.push('n');//因为log和ln都是小写字母l开头所以要分情况讨论
				else
					oper.push(equation[i]);
			}
			else//运算符栈不为空则要进行优先级判断
			{
				char temp1=oper.getTop();//取出栈顶符号
				char temp2;//待入栈符号
				if(equation[i]=='l'&&equation[i+1]=='o')
					temp2='l';
				else if(equation[i]=='l'&&equation[i+1]=='n')
					temp2='n';//log与ln的再次讨论
				else
					temp2=equation[i];
				p=Precede(temp1,temp2);
				if(p=='<')
					oper.push(temp2);//栈顶符优先级较低现在待定的运算符就可以入栈了
				if(p=='>'||p=='=')
				{
					char rep=p;//当栈顶符优先级不低于待入栈的符号 则运算符栈不停地弹栈
					//进行运算直到低于待入栈符号为止 rep用于记录比较结果 要多次进行判断
					while((rep=='>'||p=='=')&&(oper.top-1>0))
					{ 
						sig=oper.pop();
						yuan1=number.pop();
						yuan2=number.getTop();//靠前的一个运算数只要取得不要弹出来
						if(sig=='/'&&yuan1==0)//yuan1是双目运算符后面的第二运算元
						{
							cout<<"计算时出错！！出现了除数为0的情况！！"<<endl;
							return;
						}
						if(sig=='^'&&yuan2<0&&yuan1>0&&yuan1<1&&(static_cast <int>(1/yuan1))%2==0)
							//对负数开偶次根号的限制
						{
							cout<<"计算时出错！！出现了负数开偶次根号的情况！！"<<endl;
							return;
						}

						if(sig=='#'||sig=='s'||sig=='c'||sig=='t'||sig=='l'||sig=='n')//若为前缀单目运算符
						{
							double tt;
							tt=S_Operate(sig,yuan1);
							number.num[number.top]=tt;//运算结果压回原来yuan1在栈内的位置
							number.lift();//提升指针
							temp1=oper.getTop();
							rep=Precede(temp1,temp2);//再判优先级
						}
						else
						{
							number.num[(number.top)-1]=D_Operate(yuan2,sig,yuan1);
							temp1=oper.getTop();
							rep=Precede(temp1,temp2);//双目运算符的计算
						}
					}
					if(equation[i]==')')//如果栈外符是右括号要把与之匹配的左括号弹出栈外
						oper.pop();
					else if(equation[i]=='l'&&equation[i+1]=='o')
						oper.push('l');//代表log的l
					else if((equation[i]=='l')&&(equation[i+1]=='n'))
						oper.push('n');//代表ln的n
					else
						oper.push(equation[i]);
				}
			}   
			if(equation[i]=='s'||equation[i]=='c'||equation[i]=='t'||(equation[i]=='l'&&equation[i+1]=='o'))
				i=i+2;
			if(equation[i]=='l'&&equation[i+1]=='n')
				i++;
			//对于不止一个字符的运算符 sin log ln等等 要移动扫描算式的指针 往后跳一个或两个
		}
 }
 
 if(number.num[0]==ceil(number.num[0]))
	 cout<<equation<<number.num[0]<<endl;
 else
 {
	 cout<<equation<<fixed<<setprecision(8)<<number.num[0]<<endl;
 }//输出结果控制精度8位小数
 
 //调试时检查运算结束后站内情况的代码段
}

void menu()//菜单函数
{
	cout<<"实数型科学算式计算器"<<endl;
	
	cout<<endl;
	cout<<"欢迎使用o(∩_∩)o !!!"<<endl;
	cout<<"请选择你需要的功能：（0，1或者2）"<<endl;
	cout<<"----------"<<endl;
	cout<<"1.使用说明"<<endl;
	cout<<"2.计算算式"<<endl;
	cout<<"0.退出程序"<<endl;
	cout<<"----------"<<endl;
	cout<<"你的选择是：";
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
				cout<<endl<<endl<<"请输入算式，以=（等号）结束：（英文状态下输入）"<<endl;
				cin>>equation;
				calculate(equation);
				cout<<"继续使用吗？是请输入y 否则输入n：";
				cin>>go_on;//可以循环进行算式计算
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

void guide()//输入规则介绍说明书
{
	system("cls");
	cout<<"使用说明："<<endl;
	cout<<"输入算式时，请按照下列规则输入："<<endl;
	cout<<"1.四则运算+加 -减 *乘 /除按常规输入，负号用下划线(#)代替，注意将其与减号区别；可用括号()界定优先级"<<endl;
	cout<<"2.^幂:幂运算如下乘方输入x^y(x的y次方)如23^6就是23的6次方；开方也这样输入如81^(1/4)[或者81^0.25]表示81开4次方"<<endl;
	cout<<"3.!阶乘:6!表示1*2*3*4*5*6；(1+3)!表示4的阶乘，结果是24；1+3!表示1再加上3做阶乘的结果，是7"<<endl;
	cout<<"4.pi代表圆周率，即3.1415926536，本计算器利用弧度进行三角函数计算；计算正弦请输入sin，余弦输入cos，正切输入tan；sin(pi/2)就是二分之π弧度对应的正弦值（注意一定要打括号）其他依此类推；"<<endl;
	cout<<"5.计算以10为底的对数请输入log，如log1000=3，计算以e（2.718281828）为底的自然对数请输入ln，如lne^4=4,注意指数的输入要规范，如lne^4=4，但是(lne)^4=1，计算算式的对数要在对数符号后面把算式括起来，如ln(3+6*9)，计算以其他数为底的对数可利用对数换底公式，如以2为底，16的对数可输入ln16/ln2或者log16/log2结果都是4"<<endl;
	cout<<"6.可直接输入e和pi做数值计算"<<endl;
	cout<<"7.本计算器的括号只有小括号();不接受中括号[ ]和大括号{ },且算式一定要以等号（=）结束"<<endl;
	system("pause");
	system("cls");
	menu();
}