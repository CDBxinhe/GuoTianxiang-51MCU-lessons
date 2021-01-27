#include <reg52.h>
#include <stdio.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

uchar temp;
sbit beep=P2^3;
sbit D1=P1^0;
int i,j;

void delay(int n){
	uint x,y;
	for(x=0;x<n;x++)
        for(y=11059;y>0;y--);
}

void Program1(){
    //第一个发光管以间隔200ms闪烁
    D1=0;
    while (1){
        D1=1;
        delay(2);
        D1=0;
        delay(2);
    }
}

void Program2(){
    //8个发光管由上至下间隔1s流动，其中每个管亮500ms,灭500ms
    //亮时蜂鸣器响，灭时关闭蜂鸣器，一直重复下去
    temp=0xfe;
	P1=temp;
	while (1){
        delay(5);
		P1=temp;
        beep=0;
        delay(5);
        P1=0xff;
        beep=1;
        temp=_crol_(temp,1);
	}
}

void Program3(){
    //8个发光管来回流动，每个亮100ms
    //流动时蜂鸣器发出“滴滴”声
    temp=0xfe;
	P1=temp;
    while(1){
        while (1){
		    P1=temp;
            beep=0;
            delay(1);
            beep=1;
            delay(1);
            if(temp==0x7f) break;
            temp=_crol_(temp,1);
	    }
        while (1){
		    P1=temp;
            beep=0;
            delay(1);
            beep=1;
            delay(1);
            if(temp==0xfe) break;
            temp=_cror_(temp,1);
	    }
    }
   
}

void Program4(){
    //用8个发光管显示出8位二进制数累加的过程
    temp=0xfe;
	P1=temp;
    while (1){
            delay(5);
		    P1=temp;
            temp=temp-1;
            if(temp==0) break;
	    }
        P1=0x00;
}

void Program5(){
    //8个发光管间隔200ms由上至下，再由下至上，再重复一次。
    //然后全部熄灭再以300ms间隔全部闪烁5次。重复此过程。
    temp=0xfe;
	P1=temp;
    while(1){
        P1=0xff;
        for(i=0;i<2;i++){
            while (1){
		        P1=temp;
                delay(2);
                if(temp==0x7f) break;
                temp=_crol_(temp,1);
	        }
            while (1){
		        P1=temp;
                delay(2);
                if(temp==0xfe) break;
                temp=_cror_(temp,1);
	        }
        }
        P1=0xff;
        for(i=0;i<5;i++){
            P1=0xff;
            delay(3);
            P1=0X00;
            delay(3);
        }
    }
}

void Program6(){
    //间隔300ms第一次一个管亮流动一次，第二次两个管亮流动。
    //依次到8个管亮，然后重复整个过程。
    uchar temp1;
    int x;
    while(1){
        temp1=0xfe;
        x=1;
        for(i=0;i<8;i++){
            temp=0xfe;
            P1=temp1;
            x=2*x;
            temp1=temp1-x;
            for(j=0;j<8;j++){
                delay(3);
		        P1=temp;
                temp=_crol_(temp,1);
            }
            delay(3);
        }
    }
}

void Program7(){
    //间隔300ms先奇数亮再偶数亮，循环三次
    uchar temp1,temp2;
    for(i=0;i<3;i++){
        temp=0xfe;
        for(j=0;j<4;j++){
		    P1=temp;
            delay(3);
            temp=_crol_(temp,2);
        }
        temp=0xfd;
        for(j=0;j<4;j++){
		    P1=temp;
            delay(3);
            temp=_crol_(temp,2);
        }
    }
   //一个灯上下循环三次；
    for(i=0;i<3;i++){
        temp=0xfe;
        while (1){
		    P1=temp;
            delay(2);
            if(temp==0x7f) break;
            temp=_crol_(temp,1);
	    }
        while (1){
		    P1=temp;
            delay(2);
            if(temp==0xfe) break;
            temp=_cror_(temp,1);
	    }
    }
    //两个分别从两边往中间流动三次
    for(i=0;i<3;i++){
        temp1=0x0e,temp2=0x70;
        for(j=0;j<4;j++){
            temp=temp1+temp2;
            P1=temp;
            delay(3);
            temp1=_crol_(temp1,1)-15;
            temp2=_cror_(temp2,1)+120;
        }
    }
    //再从中间往两边流动三次
    for(i=0;i<3;i++){
        temp1=0xe0,temp2=0x07;
        for(j=0;j<4;j++){
            temp=temp1+temp2;
            temp1=_crol_(temp1,1)+15;
            temp2=_cror_(temp2,1)-120;
            P1=temp;
            delay(3);
        }
    }
    for(i=0;i<3;i++){
        P1=0xff;
        delay(3);
        P1=0x00;
        delay(3);
    }
    P1=0xff;
   //8个全部闪烁3次；关闭发光管，程序停止
}

void main(){
    //Program1();
    //Program2();
    //Program3();
    //Program4();
    //Program5();
    //Program6();
    Program7();
    while(1) P1=0xff;
}