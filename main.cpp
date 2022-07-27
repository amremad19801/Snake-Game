/*
    Snake Game implemented using Doubly Linked List in C++.
*/

#include<iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

//  Map dimensions
int height = 25;
int width = 100;

//  Variables to tell if the game is over or not
int gameover = 0;
int gameover2 = 0;

//  The number of fruits eaten by the first snake in both modes
int counter;
//  The number of fruits eaten by the second snake in the multi player mode
int counter2;

//  Single player Mode or Multi player Mode
int choice;

//  The directions of the first snake
int leftflag = 0;
int rightflag = 0;
int upflag = 0;
int downflag = 0;

//  The directions of the second snake in the multi player mode
int leftflag2 = 0;
int rightflag2 = 0;
int upflag2 = 0;
int downflag2 = 0;

//  The number of the remaining fruits
short fruitcount = 25;

class Snake{
    //  The position of the first snake
	int x,y;
	//  The position of the fruit
	int fx,fy;
    //  The position of the poisonous fruit
	int fx2,fy2;
	//  The position of the second snake in the multi player Mode
	int x2,y2;
	//  The names of the players
	char playername[50],playername2[50];

	//  Doubly Linked List
	struct node{
	    //  The position of each node in the doubly linked list (Snake)
		int nx,ny;
		struct node *next;
		struct node *back;
	};
	//  The head of the first snake
	struct node *head = NULL;
    //  The head of the second snake in the multi player mode
	struct node *head2 = NULL;

	//  gotoxy function is used to place the cursor at the desired location on the screen.
	void gotoxy(int x,int y){
		COORD pos = {x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
		//  textcolour function is used to change the color of the text.
	void textcolour(int k){
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,k);
	}
    /*
        COLOR               INT VALUES
        -------------------------------
        BLACK                   0
        BLUE                    1
        GREEN                   2
        CYAN                    3
        RED                     4
        MAGENTA                 5
        BROWN                   6
        LIGHTGRAY               7
        DARKGRAY                8
        LIGHTBLUE               9
        LIGHTGREEN             10
        LIGHTCYAN              11
        LIGHTRED               12
        LIGHTMAGENTA           13
        YELLOW                 14
        WHITE                  15
	*/
	//  This function is used to display the name(s) and the score(s) of the player(s) during the game.
	void nameandscore(){
		gotoxy(101,0);
		textcolour(10);
		cout<<"Made by EECE";
		textcolour(6);
		gotoxy(101,2);
		cout<<playername<<"'s score = "<<counter*100;
		if(choice == 2){
			gotoxy(101,4);
			cout<<playername2<<"'s score = "<<counter2*100;
			gotoxy(101,6);
			cout<<"Remained Fruits : ";
			gotoxy(117,6);
			cout<<"  ";
			gotoxy(117,6);
			cout<<fruitcount;
		}
	}
	public:
    //  This function is used to create the frame/wall of the game.
	void window(){
		if(choice == 1)
            textcolour(4);
		else
            textcolour(1);
        for(int i = 0;i <= width;i++){
			gotoxy(i,0);
			cout<<"Û";
			gotoxy(i,height);
			cout<<"Û";
		}
		for(int i = 0;i <= height;i++){
			gotoxy(0,i);
			cout<<"Û";
			gotoxy(width,i);
			cout<<"Û";
		}
	}
	//  This function is used to setup the variables at the beginning of the game for the single player mode.
	void setup(){
		counter = 0;
		gameover = 0;
		resetflag();
		nameandscore();
		head = new node;
		head->nx = width/2;
		head->ny = height/2;
		head->next = NULL;
		head->back = NULL;
		x = width / 2;
		y = height / 2;
		//  It is used to generate the position of the fruit at the beginning of the game.
		label1:
		    //  rand function is used to generate random numbers.
		    fx = rand() % width;
		if((fx == 0) || (fx == width))
            //  goto statement is used to jump from anywhere to anywhere within a function.
            goto label1;
		label2:
		    // rand function is used to generate random numbers.
		    fy = rand() % height;
		if((fy == 0) || (fy == height))
            //  goto statement is used to jump from anywhere to anywhere within a function.
            goto label2;
        //  It is used to generate the position of the poisonous fruit at the beginning of the game.
		label3:
		    //  rand function is used to generate random numbers.
		    fx2 = rand() % width;
		if((fx2 == 0) || (fx2 == width) || (fx2 == fx))
            //  goto statement is used to jump from anywhere to anywhere within a function.
            goto label3;
		label4:
		    // rand function is used to generate random numbers.
		    fy2 = rand() % height;
		if((fy2 == 0) || (fy2 == height) || (fy2 == fy))
            //  goto statement is used to jump from anywhere to anywhere within a function.
            goto label4;
	}
	//  This function is used to setup the variables at the beginning of the game for the multi player mode.
	void setup2(){
		resetflag2();
		gameover2 = 0;
		counter2 = 0;
		fruitcount = 25;
		head2 = new node;
		head2->nx = ((width / 2) + 5);
		head2->ny = ((height / 2) + 5);
		head2->next = NULL;
		head2->back = NULL;
		x2 = ((width / 2) + 5);
		y2 = ((height / 2) + 5);
	}
	//  This function is used to draw/display the snake.
	void drawlist(struct node *h,int k){
		textcolour(k);
		struct node *ptr;
		ptr = h;
		while(ptr != NULL){
			gotoxy(ptr->nx,ptr->ny);
			cout<<"Û";
			ptr = ptr->next;
		}
	}
	//  This function is used to destroy/clear the last node of the snake.
	void destroylist(struct node *h){
		struct node *ptr;
		ptr = h;
		while(ptr != NULL){
			gotoxy(ptr->nx,ptr->ny);
			cout<<" ";
			ptr = ptr->next;
		}
	}
	//  This function is used to destroy/clear the fruit.
	void destroyfruit(int x,int y){
        gotoxy(x,y);
        cout<<" ";
	}
	//  This function is used to display both the snake and the fruit during the game.
	void draw(){
		drawlist(head,2);
		drawlist(head2,5);
		gotoxy(fx,fy);
		textcolour(4);
		cout<<"@";
        gotoxy(fx2,fy2);
		textcolour(3);
		cout<<"@";
		//  sleep function is responsible for the speed of the snake.
		Sleep(70);
		//  These functions are used to update the positions of the snake and the fruit during the game.
		destroylist(head);
		destroylist(head2);
		destroyfruit(fx,fy);
        destroyfruit(fx2,fy2);
	}
	//  This function is used to reset the directions of the first snake.
	void resetflag(){
		upflag = 0;
		downflag = 0;
		leftflag = 0;
		rightflag = 0;
	}
    //  This function is used to reset the directions of the second snake in the multi player mode.
    void resetflag2(){
		upflag2 = 0;
		downflag2 = 0;
		leftflag2 = 0;
		rightflag2 = 0;
	}
	//  This function is used to determine the direction of the snake during the game.
	void play(){
		int h;
		char ch;
		//  kbhit  function is used to determine if a key has been pressed or not.
		if(kbhit()){
            //  getch  function is used to return the ASCII value of the key pressed.
			ch = getch();
			h = ch;
			switch(h){
				case 72:    //  ASCII code for up arrow key
				    if(downflag != 1){
                        resetflag();
                        upflag = 1;
                    }
                    break;
				case 80:    //  ASCII code for down arrow key
				    if(upflag != 1){
                        resetflag();
                        downflag = 1;
				    }
				    break;
				case 75:    //  ASCII code for left arrow key
				    if(rightflag != 1){
                        resetflag();
                        leftflag = 1;
                    }
                    break;
				case 77:    //  ASCII code for right arrow key
				    if(leftflag != 1){
                        resetflag();
                        rightflag = 1;
                    }
                    break;
				case 119:   //  ASCII code for w key
				    if(downflag2 != 1){
                        resetflag2();
                        upflag2 = 1;
				    }
                    break;
				case 115:   //  ASCII code for s key
				    if(upflag2 != 1){
                        resetflag2();
                        downflag2 = 1;
                    }
                    break;
				case 97:    //  ASCII code for a key
				    if(rightflag2 != 1){
                        resetflag2();
                        leftflag2 = 1;
				    }
                    break;
				case 100:   //  ASCII code for d key
				    if(leftflag2 != 1){
                        resetflag2();
                        rightflag2 = 1;
                    }
                    break;
				default:
				    break;
			}
		}
	}
	//  This function is used to create the frame of the window.
	void box(int m1,int n1,int m2,int n2){
        for(int i = m1;i <= m2;i++){
			gotoxy(i,n1);
			cout<<"Û";
			gotoxy(i,n2);
			cout<<"Û";
		}
		for(int i = n1;i <= n2;i++){
			gotoxy(m1,i);
			cout<<"Û";
			gotoxy(m2,i);
			cout<<"Û";
		}
	}
	//  This function is used to display the choice window.
	void welcome(){
		textcolour(5);
		box(((width / 2) - (width/4)),((height / 2) - (height / 4)),((width / 2) + (width / 4)),((height / 2) + (height / 4)));
		textcolour(10);
		gotoxy(((width / 2) - 18),((height / 2) - 10));
		cout<<"*** WELCOME TO SNAKE GAME BY EECE ***";
		textcolour(9);
		gotoxy(((width / 2) - 18),((height / 2) - 3));
		cout<<"Press 1 for Single player Mode \n";
		gotoxy(((width / 2) - 18),((height / 2) - 1));
		cout<<"Press 2 for Multi player Mode \n";
		gotoxy((width / 2),((height / 2) + 1));
		cin>>choice;
		//  cls is used to clear the screen/terminal.
		system("cls");
	}
	//  This function is used to display the single player mode window.
	void welcome1(){
		textcolour(5);
		box(((width / 2) - (width/4)),((height / 2) - (height / 4)),((width / 2) + (width / 4)),((height / 2) + (height / 4)));
		textcolour(6);
		gotoxy(((width / 2) - 19),((height / 2) - 3));
		cout<<"WELCOME TO SNAKE GAME SINGLE PLAYER MODE";
		textcolour(8);
		gotoxy(((width / 2) - 19),(height / 2));
		cout<<"Enter Your Name :";
        gotoxy(((width / 2) - 1),(height / 2));
		cin>>playername;
        //  cls is used to clear the screen/terminal.
		system("cls");
	}
	//  This function is used to display the multi player mode window.
	void welcome2(){
		textcolour(5);
		box(((width / 2) - (width/4)),((height / 2) - (height / 4)),((width / 2) + (width / 4)),((height / 2) + (height / 4)));
		textcolour(6);
		gotoxy(((width / 2) - 18),((height / 2) - 3));
		cout<<"WELCOME TO SNAKE GAME MULTIPLAYER MODE";
		textcolour(8);
		gotoxy(((width / 2) - 18),(height / 2));
		cout<<"Enter Player1 Name :";
		gotoxy(((width / 2) - 18),((height / 2) + 2));
		cout<<"Enter Player2 Name :";
		gotoxy(((width / 2) + 3),(height / 2));
		cin>>playername;
		gotoxy(((width / 2) + 3),((height / 2) + 2));
		cin>>playername2;
        //  cls is used to clear the screen/terminal.
		system("cls");
	}
	//  This function is used to display the stats at the end of the game.
    char end(){
		char c;
		gotoxy(((width / 2) - 4),((height / 2) - 4));
		cout<<"GAME OVER \n";
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		if(choice == 1){
            textcolour(1);
            gotoxy(((width / 2) - 17),((height / 2) - 2));
            cout<<"Your score : "<<counter*100;
		}
		else if(choice == 2){
            textcolour(1);
            gotoxy(((width / 2) - 17),((height / 2) - 2));
            cout<<playername<<" 's score : "<<counter*100;
			gotoxy(((width / 2) - 17),(height / 2));
			cout<<playername2<<" 's score : "<<counter2*100;
			textcolour(4);
			if(gameover != 0){
				gotoxy(((width / 2) - 17),((height / 2) + 2));
				cout<<playername<<" has lost!";
			}
			else{
				gotoxy(((width / 2) - 17),((height / 2) + 2));
				cout<<playername2<<" has lost!";
			}
			if(fruitcount == 0){
				textcolour(4);
				gotoxy(((width / 2) - 17),((height / 2) + 2));
				if(counter>counter2){
					cout<<playername<<" has won!";
				}
				else{
					cout<<playername2<<" has won!";
				}
            }
		}
		textcolour(6);
		gotoxy(((width / 2) - 17),((height / 2) + 4));
		cout<<"Do you want to Play again ? (Y/N) : ";
		cin>>c;
        //  cls is used to clear the screen/terminal.
		system("cls");
		return c;
	}
	//  This function is used to determine the position of the snake according to its direction during the game.
	void run(){
		if(upflag == 1)
            y--;
		else if(downflag == 1)
            y++;
		else if(leftflag == 1)
            x--;
		else if(rightflag == 1)
            x++;
        if(upflag2 == 1)
            y2--;
		else if(downflag2 == 1)
            y2++;
		else if(leftflag2 == 1)
            x2--;
		else if(rightflag2 == 1)
            x2++;
	}
	//  This function is used to move the snake during the game.
	void dolist(struct node *h,int pp,int qq){
		struct node *ptr,*prev;
		ptr = h;
		prev = h;
		while(ptr->next != NULL){
			prev = ptr;
			ptr = ptr->next;
		}
		while(prev != h){
			ptr->nx = prev->nx;
			ptr->ny = prev->ny;
			prev = prev->back;
			ptr = ptr->back;
		}
		ptr->nx = prev->nx;
		ptr->ny = prev->ny;
		prev->nx = pp;
		prev->ny = qq;
	}
    //  This function is used to reset the position of the first snake in the multi player mode, when it touches the wall.
	void drawagain(){
		if(x == width)
			x = 1;
		if(x == 0)
			x = width - 1;
		if(y == 0)
			y = height - 1;
		if(y == height)
			y = 1;
	}
	//  This function is used to reset the position of the second snake, when it touches the wall.
	void drawagain2(){
		if(x2 == width)
			x2 = 1;
		if(x2 == 0)
			x2 = width - 1;
		if(y2 == 0)
			y2 = height - 1;
		if(y2 == height)
			y2 = 1;
	}
	//  This function is used to generate the position of the fruit during the game.
	void generatefruit(){
        label1:
            // rand function is used to generate random numbers.
			fx = rand() % width;
			if((fx == 0) || (fx == width))
                //  goto statement is used to jump from anywhere to anywhere within a function.
                goto label1;
        label2:
            // rand function is used to generate random numbers.
			fy = rand() % height;
			if((fy == 0) || (fy == height))
                //  goto statement is used to jump from anywhere to anywhere within a function.
                goto label2;
	}
    //  This function is used to generate the position of the poisonous fruit during the game.
	void generatefruit2(){
        label1:
            // rand function is used to generate random numbers.
            fx2 = rand() % width;
			if((fx2 == 0) || (fx2 == width) || (fx2 == fx))
                goto label1;
        label2:
            // rand function is used to generate random numbers.
			fy2 = rand() % height;
			if((fy2 == 0) || (fy2 == height) || (fy2 == fy))
                goto label2;
	}
    //  This function is used to check the number of fruits eaten.
	void checkfcount(){
	    //  If the snake has eaten all the fruits, the game will be over.
		if(fruitcount == 0){
			gameover = 1;
			gameover2 = 1;
		}
	}
	//  This function is used to check up the first snake during the game.
	void checkup()
	{
	    //  If the first snake touches the wall in the single player mode, the game will be over.
		if(choice == 1){
			if((x == width) || (x == 0))
                gameover = 1;
			if((y == height) || (y == 0))
                gameover = 1;
		}
        drawagain();
		struct node *h;
		h = head->next;
		while(h != NULL){
            //  If the first snake touches its body, the game will be over.
			if((x == h->nx) && (y == h->ny)){
				gameover = 1;
				break;
			}
			h = h->next;
		}
        //  If the first snake has eaten a poisonous fruit, its length will decrease(deleting the last node from the doubly linked list).
        if((x == fx2) && (y == fy2)){
            h = head;
            if(h->next == NULL){
                h = NULL;
                gameover = 1;
            }
            else{
                struct node *ptr = head;
                while(ptr->next->next != NULL){
                    ptr = ptr->next;
                }
                struct node *lastnode = ptr->next;
                ptr->next = NULL;
                delete lastnode;
            }
            generatefruit();
            generatefruit2();
            if(counter == 0)
                counter = 0;
            else
                counter--;
			nameandscore();
		}
        //  If the first snake has eaten all the fruits in the multi player mode, the game will be over.
        if((x == fx) && (y == fy)){
			if(choice == 2){
				fruitcount--;
				checkfcount();
			}
            //  If the first snake has eaten a fruit, its length will increase(adding a node to the doubly linked list).
			struct node *t,*ptr,*prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
            ptr = head;
            prev = head;
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = t;
            t->back = ptr;
            generatefruit();
            generatefruit2();
			counter++;
			nameandscore();
		}
			dolist(head,x,y);
    }
    //  This function is used to check up the second snake during the game.
    void checkup2(){
		drawagain2();
		struct node *h;
		h = head2->next;
		while(h != NULL){
            //  If the second snake touches its body, the game will be over.
			if((x2 == h->nx) && (y2 == h->ny)){
				gameover2 = 1;
				break;
			}
			h = h->next;
		}
        //  If the second snake has eaten a poisonous fruit, its length will decrease (deleting the last node from the doubly linked list).
        if((x2 == fx2) && (y2 == fy2)){
            h = head2;
            if(h->next == NULL){
                h = NULL;
                gameover2 = 1;
            }
            else{
                struct node *ptr = head2;
                while(ptr->next->next != NULL){
                    ptr = ptr->next;
                }
                struct node *lastnode = ptr->next;
                ptr->next = NULL;
                delete lastnode;
            }
            generatefruit();
            generatefruit2();
            if(counter2 == 0)
                counter2 = 0;
            else
                counter2--;
            nameandscore();
		}
        //  If the second snake has eaten all the fruits in the multi player mode, the game will be over.
		if((x2 == fx) && (y2 == fy)){
			fruitcount--;
			checkfcount();
			struct node *t,*ptr,*prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
            ptr = head2;
            prev = head2;
            //  If the second snake has eaten a fruit, its length will increase(adding a node to the doubly linked list).
            while(ptr->next != NULL){
					ptr = ptr->next;
            }
            ptr->next = t;
            t->back = ptr;
            generatefruit();
            generatefruit2();
            counter2++;
            nameandscore();
		}
			dolist(head2,x2,y2);
    }
    //  The game loop for the single player mode
	void game1(){
		char ch;
		welcome1();
		do{
			setup();
			window();
			while(gameover != 1){
				draw();
				play();
				run();
				checkup();
			}
			ch = end();
        }while((ch == 'y') || (ch == 'Y'));
	}
	//  The game loop for the multi player player mode
	void game2(){
		char ch;
		welcome2();
		do{
            setup();
			setup2();
			window();
			while((gameover != 1) && (gameover2 != 1)){
                draw();
                play();
                run();
                checkup();
                checkup2();
            }
            ch = end();
        }while((ch == 'y') || (ch == 'Y'));
    }

};

int main(){
	Snake s;
	s.welcome();
	if(choice == 1){
		s.game1();
	}
	if(choice == 2){
		s.game2();
	}
	//  exit is used to terminate the program.
	system("exit");
}
