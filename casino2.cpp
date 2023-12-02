#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>

// snake......hissSSSSS.......hissSSSSSSSS............hissssSSSSSSSSSS...............hissssSSSSSSSSSSSS..........hissssSSSSSSSSsssssssssss}



#include <stdio.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <windows.h>
#include <process.h>
 
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
 
int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
 
struct coordinate
{
    int x;
    int y;
    int direction;
};
 
typedef struct coordinate coordinate;
 
coordinate head, bend[500],food,body[30];



void Move()
{
    int a,i;
 
    do
    {
 
        Food();
        fflush(stdin);
 
        len=0;
 
        for(i=0; i<30; i++)
 
        {
 
            body[i].x=0;
 
            body[i].y=0;
 
            if(i==length)
 
                break;
 
        }
 
        Delay(length);
 
        Boarder();
 
        if(head.direction==RIGHT)
 
            Right();
 
        else if(head.direction==LEFT)
 
            Left();
 
        else if(head.direction==DOWN)
 
            Down();
 
        else if(head.direction==UP)
 
            Up();
 
        ExitGame();
 
    }
    while(!kbhit());
 
    a=getch();
 
    if(a==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
    key=getch();
 
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
 
    {
 
        bend_no++;
 
        bend[bend_no]=head;
 
        head.direction=key;
 
        if(key==UP)
 
            head.y--;
 
        if(key==DOWN)
 
            head.y++;
 
        if(key==RIGHT)
 
            head.x++;
 
        if(key==LEFT)
 
            head.x--;
 
        Move();
 
    }
 
    else if(key==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
 
    else
 
    {
 
        printf("\a");
 
        Move();
 
    }
}
 
void gotoxy(int x, int y)
{
 
    COORD coord;
 
    coord.X = x;
 
    coord.Y = y;
 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load()
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}
void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
 
            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
 
}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}
void Print()
{
    //GotoXY(10,12);
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}
void record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time
 
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}
int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}



// snake......hissSSSSS.......hissSSSSSSSS............hissssSSSSSSSSSS...............hissssSSSSSSSSSSSS..........hissssSSSSSSSSsssssssssss}






using namespace std;
class bank
{
    public:
    int bal;
    bank()
    {
        bal=100000;
    }
};
bank p1, p2;

class header
{
	public:
	casino()
	{
	cout<<"**********************************************************************************************";
	cout<<"\n\n\t\tWelcome To Our Game Zone\t||\tPlay And Win";
	cout<<"\n\n**********************************************************************************************\n\n";
	}

	tictactoe()
	{
	cout<<"**********************************************************************************************";
	cout<<"\n\n\t\t\t\t\tTic Tac Toe";
	cout<<"\n\n**********************************************************************************************\n\n\n\n\n\n";
	}

	dream11()
	{
	cout<<"**********************************************************************************************";
	cout<<"\n\n\t\tDream 11\t||\t\"Khelo Cricket Dimag Se\"";
	cout<<"\n\n**********************************************************************************************\n";
	}

	balance()
	{
	cout<<"**********************************************************************************************";
	cout<<"\n\n\t\t\t\tWallet Balance";
	cout<<"\n\n**********************************************************************************************";
	}

	footer(){cout<<"\n\n\n\n\n----------------------------------------------------------------------------------------------\n\n\n\n";}
    footer2(){cout<<"\n\n\n______________________________________________________________________________________________\n";}
    footer3(){cout<<"==============================================================================================\n";};
    footer4(){cout<<"**********************************************************************************************\n\n";}
};


class game
{
    public:


    int enter(char **a,int p)
{
	char n,num;
	if(p==1){cout<<"\n\tPlayer 1's turn: "; num='X';}
	else {cout<<"\n\tPlayer 2's turn: "; num='O';}
	cin>>n;    
	int i,j;
	for(i=0;i<3;i++)
	{
	for(j=0;j<3;j++)
	if(a[i][j]==n)
	{
		a[i][j]=num;
		return 0;
	}
	}
}

int winner(char **a)
{
	if((a[0][0]==a[0][1] && a[0][0]==a[0][2]) || (a[1][0]==a[1][1] && a[1][0]==a[1][2]) || (a[2][0]==a[2][1] && a[2][0]==a[2][2])) return 1;
	
	if((a[0][0]==a[1][0] && a[0][0]==a[2][0]) || (a[0][1]==a[1][1] && a[0][1]==a[2][1]) || (a[0][2]==a[1][2] && a[0][2]==a[2][2])) return 1;
	
	if((a[0][0]==a[1][1] && a[0][0]==a[2][2]) || (a[0][2]==a[1][1] && a[0][2]==a[2][0]))  return 1;
	
	if((a[1][0]==a[1][1] && a[1][0]==a[1][2]) ||
 (a[0][1]==a[1][1] && a[0][1]==a[2][1])) return 1;
	return 0;
}

void draw()
{
	cout<<"Match draw : Nobody won this game";
}

void display(char **a)
{
	cout<<"\t \t "<<a[0][0]<<" | "<<a[0][1]<<" | "<<a[0][2];
	cout<<"\n\t\t"<<"---|---|---"<<"\t  Player 1 symbol is: X \n";
	cout<<"\t \t "<<a[1][0]<<" | "<<a[1][1]<<" | "<<a[1][2]<<"\t  Player 2 symbol is: O";
	cout<<"\n\t\t"<<"---|---|---"<<endl;
	cout<<"\t \t "<<a[2][0]<<" | "<<a[2][1]<<" | "<<a[2][2];
	cout<<endl<<endl;
}

void end(char **a,int p)
{
	header dp;
	system("CLS");
	cout<<" \t    TIC-TAC-TOE  Game"<<"\n\n\n\n";
	display(a);
}

void set(char **a)
{
	char n='1';
	for(int i=0;i<3;i++)
	{
		a[i]=new char[3];
		for(int j=0;j<3;j++)
		{
		a[i][j]=n;
		n++;
		}
	}
}


};


class game2
{
	public:
	void team(vector<pair<string,int>> &v)
{
    v[0].first="1) Virat Kohli              ";
    v[1].first="2) Rohit Sharma             ";
    v[2].first="3) Jasprit Bumrah           ";
    v[3].first="4) Ravichandran Ashwin      ";
    v[4].first="5) Ravindra Jadeja          ";
    v[5].first="6) Cheteshwar Pujara        ";
    v[6].first="7) Ajinkya Rahane           ";
    v[7].first="8) Shikhar Dhawan           ";
    v[8].first="9) KL Rahul                 ";
    v[9].first="10) Mohammad Shami          ";
    v[10].first="11) Ishant Sharma           ";
    v[11].first="12) Rishabh Pant            ";
    v[12].first="13) Hardik Pandya           ";
    v[13].first="14) Wriddhiman Saha         ";
    v[14].first="15) Umesh Yadav             ";
    v[15].first="16) Bhuvaneshwar Kumar      ";
    v[16].first="17) Shardul Thakur          ";
    v[17].first="18) Mayank Agarwal          ";
    v[18].first="19) Kuldeep Yadav           ";
    v[19].first="20) Navdeep Saini           ";
    v[20].first="21) Deepak Chahar           ";
    v[21].first="22) Shubham Gill            ";
    v[22].first="23) Hanuma Vihari           ";
    v[23].first="24) Axar Patel              ";
    v[24].first="25) Shreyas Iyer            ";
    v[25].first="26) Washington Sundar       ";
    v[26].first="27) Yuzvenda Chahal         ";
    v[27].first="28) Mohammad Siraj          ";

    for(int i=0;i<v.size();i++)
    v[i].second=rand()%200;
}

void display(vector<pair<string,int>> v)
{
	header dp;
    system("CLS");
	dp.dream11();
	cout<<"\n\t\t\t    =: SCORES :=\n\t\t\t--------------------\n\n\n";
    for(int i=0;i<14;i++)
    cout<<v[i].first<<"= "<<v[i].second<<"\t\t"<<v[i+14].first<<"= "<<v[i+14].second<<endl;
}

};


int tictoe()
{
    char **a=new char*[3];
    game obj;
	header dp;

	system("CLS");
	dp.tictactoe();

	obj.set(a);
	obj.display(a);
	dp.footer();
	
    int winner=-1;
	for(int i=1;i<=9;i++)
	{
		if(i%2==1) obj.enter(a,1);
		else obj.enter(a,2);
		system("CLS");
	    dp.tictactoe();
		obj.display(a);
		dp.footer();
		if(obj.winner(a)) 
		{
			if(i%2) {obj.end(a,1);winner=1;break;}
			else {obj.end(a,2);winner=2;break;}
		}
		if(i==9)obj.end(a,0);
	}
    system("CLS");
    return winner;
}


int dream11()
{
	game2 obj;
	header dp;
    int n=28;
    vector<pair<string,int>> v(n);
    obj.team(v);

    system("CLS");
	dp.dream11();
	cout<<"\n\n";
    for(int i=0;i<14;i++)
    cout<<"\t"<<v[i].first<<"\t\t"<<v[i+14].first<<endl;

    vector<int> p1(11);
    vector<int> p2(11);
	dp.footer();
    cout<<"\nEnter the corresponding number to form your team of 11 Players:\n";
    cout<<"\nPlayer 1: "; 
    for(int i=0;i<11;i++)
    {
        int n;cin>>n;
        p1[i]=n-1;
    }
    cout<<"\nPlayer 2: ";
    for(int i=0;i<11;i++)
    {
        cin>>n;
        p2[i]=n-1;
    }

    int p1score=0,p2score=0;
    for(int i=0;i<p1.size();i++)
    {
        p1score=p1score+v[p1[i]].second;
        p2score=p2score+v[p2[i]].second;
    }
    system("CLS");
	dp.dream11();
    obj.display(v);
    cout<<"\n\n\t\tPlayer 1 score is: "<<p1score<<"\n\t\tPlayer 2 score is: "<<p2score<<"\n";
	if(p1score>p2score)return 1;
	if(p2score>p1score)return 2;
}


int guessno()
{
    system("CLS");
    header dp;
    int n,num,count=0;
    srand(time(0));
    num=rand()%100;
    dp.footer4();cout<<"\t\t    Guess The No\t||\t\"Win more by guessing minimum times\"\n\n";dp.footer4();
    cout<<"\n\tGuess the no :\n"<<endl;
    while(n!=num)
    {
        cin>>n;
        if(n>num)cout<<"Too high..\n\n";
        if(n<num)cout<<"Too low..\n\n";
        count++;
    }
    cout<<"\n";dp.footer3();cout<<"\t  Yes you guessed it right, it was \""<<num<<"\"";
    cout<<"\n\t  You guessed it in "<<count<<" attempts\n\n";dp.footer2();
    return 0;
}

int sudoku()
{
    return 2;
}

int snake()
{
    char key;
 
    Print();
 
    system("cls");
 
    load();
 
    length=5;
 
    head.x=25;
 
    head.y=20;
 
    head.direction=RIGHT;
 
    Boarder();
 
    Food(); //to generate food coordinates initially
 
    life=3; //number of extra lives
 
    bend[0]=head;
 
    Move();   //initialing initial bend coordinate
 
    return 0;
}


int stonepaperscissor()
{
    header dp;
    system("CLS");
    dp.footer4();cout<<"\t\t\tStone / Paper / Scissor\n\n";dp.footer4();
    class node{
        public: int data;
        node* next;
        node(int num){
            data=num;
            next=NULL;
        }
    };node *head= new node(1);
    head->next=new node(2);
    head->next->next=new node(3);
    head->next->next->next=head;

    cout<<"\n1: Stone\n2: Paper\n3: Scissor\n\n";
    int n;cin>>n;
    srand(time(0));
    int p=(rand()%3)+1;
    string s[4]={"","Stone","Paper","Scissor"};
    cout<<"\nYour's choice     : "<<s[n]<<"\nOpponent's choice : "<<s[p]<<"\n\n";
    cout<<"\n\n";dp.footer3();cout<<"\n\t\tResult : ";
    while(head->data!=n)head=head->next;
    if(n==p)cout<<"Match draw\n\n";
    else
    {
        if(head->next->data==p)cout<<"You loose\n\n";
        else cout<<"You win\n\n";
    }dp.footer3();
}

int accountbalance(string s1,string s2)
{
	header dp;
	system("CLS");
	dp.balance();
    cout<<"\n\n\n\n\t\t\t"<<s1<<"'s Total Gems: "<< p1.bal<<"\n\n\n\t\t\t"<<s2<<"'s Total Gems: "<<p2.bal<<endl;
	dp.footer();
    return 1;
}

int singleplayer()
{
	header dp;
	system("CLS");
    dp.footer4();cout<<"\t\t\t  Welcome to Singleplayer Zone\n\n";dp.footer4();cout<<"\n\n";
	int n,winner;
    while(1)
    {
        cout<<"\n\t\tChoose a game to play: \n\n\t\t 1. Guess no Game \n\t\t 2. Stone Paper Scissor \n\t\t 3. Snake \n\t\t 4. Exit the Singleplayer zone\n\n";
        cin>>n;
    switch(n)
    {
        case 1: guessno(); break;
        case 2: stonepaperscissor(); break;
        case 3: snake(); break;
        case 4: break;
    }
    if(n==4){system("CLS");return -1;}
    }
}

int casino()
{
	header dp;
    system("CLS");
	dp.casino();
    cout<<"\n\n\n\n\tChoose a game to play- \n\n";
    int n;
    cout<<"\n\t\t 1: TicTacToe \n\n\t\t 2: Dream11 \n\n";
    cin>>n;
	dp.footer();

    int amount;
    cout<<"\n\n Enter the Gem's Amount: ";
    cin>>amount;

    int winner;
    switch(n)
    {
        case 1: winner=tictoe(); break;
		case 2: winner=dream11(); break;
    }
    dp.footer2();
    if(winner==1)
    {
        cout<<"\n Congratulations!  Player 1 wins! \n\n";
        p1.bal=p1.bal+(2*amount);
        p2.bal=p2.bal-amount;
    }
    else if(winner==2)
    {
		cout<<"\n Congratulations!  Player 2 wins! \n\n";
        p1.bal=p1.bal+(2*amount);
        p2.bal=p2.bal-amount;
    }
	else cout<<"\n Match draw : Nobody won this game \n\n";
    dp.footer3();
    return 0;
}

int main()
{
    system("CLS");
    string s1,s2;
    cout<<"Enter Player 1 name: ";cin>>s1;
    cout<<"Enter Player 2 name: ";cin>>s2;cout<<"\n\n";
    header dp;
    system("CLS");dp.footer4();cout<<"\t\t\t    Welcome to Our Game Zone\n\n";dp.footer4();
    int n;
	while(1){
    cout<<"\n\n Enter the corresponding no for, \n\n\t 1: Entering the Game Zone, \n\t 2: Single Player Games, \n\t 3: Checking Gems Balance, \n\t 4: Exit \n\n";
    cin>>n;

    switch(n)
    {
        case 1: casino(); break;
        case 2: singleplayer(); break;
        case 3: accountbalance(s1,s2);break;
        case 4: exit(0); break;
    }
	}
}