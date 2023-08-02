#include <windows.h>
#include<stdlib.h>
#include<stdio.h>

#define COSMETICS 1
#define GROCERY 2
#define MOBILES 3
#define FASHION 4
#define FURNITURE 5
#define APPLIANCES 6
#define ELECTRONICS 7

#define SWSITM 82
#define SWSLITM 83

#define CLOGIN 50
#define SLOGIN 51
#define CREG 52
#define SREG 53
#define MSCREEN 90
#define SELLERHOME 91
#define CUSTOMERHOME 92

#define CONFIRMORDER 54
#define SHWCART 56
#define SHWORD 57
#define SHWCATITM 58

#define SCOSMETICS 93
#define SGROCERY 94
#define SMOBILES 95
#define SFASHION 96
#define SFURNITURE 97
#define SAPPLIANCES 98
#define SELECTRONICS 99
/*HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;
*/
/* Funtion declared */
int  show_slected_itm();
int  show_search();
int  show_cart();
int  seller_hm();
int clogin();
int slogin();
int creg();
int sreg();
int start();
int  customer_hm();
int  schoose(int cty);
int  cnf_order();
int  show_orders();
int  show_cat_itm();
/*     end        */

int info;

int check(int win_num)
{
	switch(win_num)
	{
		case CLOGIN:
			clogin();
			break;
		case SLOGIN:
			slogin();
			break;
		case CREG:
			creg();
			break;
		case SREG:
			sreg();
			break;
		case CUSTOMERHOME:
			printf("{#nkc}");
			customer_hm();
			break;
		case SELLERHOME:
			seller_hm();
			break;
		case MSCREEN:
			start();
			break;
		case SCOSMETICS:
			schoose(0);
			break;
		case SGROCERY:
			schoose(1);
			break;
		case SMOBILES:
			schoose(2);
			break;
		case SFASHION:
			schoose(3);
			break;
		case SFURNITURE:
			schoose(4);
			break;
		case SAPPLIANCES:
			schoose(5);
			break;
		case SELECTRONICS:
			schoose(6);
			break;
		case COSMETICS:
			seller_hm();
			break;
		case GROCERY:
			seller_hm();
			break;
		case MOBILES:
			seller_hm();
			break;
		case FASHION:
			seller_hm();
			break;
		case FURNITURE:
			seller_hm();
			break;
		case APPLIANCES:
			seller_hm();
			break;
		case ELECTRONICS:
			seller_hm();
			break;
		case SWSITM:
			show_search();
			break;
		case SWSLITM:
			show_slected_itm();
			break;
		case CONFIRMORDER:
			cnf_order();
			break;
		case SHWCART:
			show_cart();
			break;
		case SHWORD:
			show_orders();
			break;
		case SHWCATITM:
			show_cat_itm();
			break;
		case 0:
			printf("Exit Successfully");
			break;
		default:
			printf("important: %d",win_num);
	}
	return 0;
}

int  show_cat_itm(){
	char pathcom[50];
	printf(" {sh catgry itm :%d}\n",info);
	sprintf(pathcom,"showitems.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d,hjk}",k);
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  show_orders(){
	char pathcom[50];
	printf(" {sh order itm :%d}\n",info);
	sprintf(pathcom,"shw_order.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d,hjk}",k);
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  show_cart(){
	char pathcom[50];
	printf(" {sh cart itm :%d}\n",info);
	sprintf(pathcom,"shw_cart.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d,hjk}",k);
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  cnf_order()
{
	char pathcom[50];
	sprintf(pathcom,"confirm_order.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	info=k/100;
	check(win_num);
	return 0;
}

int  show_slected_itm()
{
	char pathcom[50];
	printf(" {slect itm:%d}\n",info);
	sprintf(pathcom,"selected_itm.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	info=k/100;
	check(win_num);
	return 0;
}

int  show_search()
{
	char pathcom[50];
	printf(" {sh itm info:%d}\n",info);
	sprintf(pathcom,"shwsrchitm.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d,hjk}",k);
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  schoose(int cty)
{
	char pathcom[50];
	sprintf(pathcom,"add_itm.exe %d",info*10+cty);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  customer_hm()
{
	char pathcom[50];
	sprintf(pathcom,"customer_home.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  seller_hm()
{
	char pathcom[50];
	sprintf(pathcom,"seller_home.exe %d",info);
	int k=system(pathcom);
	int win_num=k%100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  clogin()
{
	int k=system("cslogin.exe");
	int win_num=k%100;
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  slogin()
{
	int k=system("srlogin.exe");
	int win_num=k%100;
	info=k/100;
	printf(" *{%d*}",k);
	check(win_num);
	return 0;
}
int  creg()
{
	int k=system("csreg.exe");
	int win_num=k%100;
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int  sreg()
{
	int k=system("slreg.exe");
	int win_num=k%100;
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
}

int start()	{
	int k=system("bscreen.exe");
	int win_num=k%100;
	info=k/100;
	printf(" {%d}",k);
	check(win_num);
	return 0;
} 

int main()
{
	start();	
	return 0;
}
//ES_READONLY
