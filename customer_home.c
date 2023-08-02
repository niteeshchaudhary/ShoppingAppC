#include <windows.h>
#include<stdio.h>
#include <time.h>
#include <commctrl.h>
#include<wingdi.h>
#include<math.h>
#include<Richedit.h>

#include "Layout.h"
#include "usefullfunc.h"

#define SLIDEDRAWER 40
#define CLOSEDRAWER 42
#define DRAWER 0
#define COSMETICS 1
#define GROCERY 2
#define MOBILES 3
#define FASHION 4
#define FURNITURE 5
#define APPLIANCES 6
#define ELECTRONICS 7
#define BTHD8 8
#define BTHD9 9
#define BTHD10 10
#define BTHD11 11
#define BTHD12 12
#define BTHD13 13
#define BTHD14 14
#define BTL 15
#define BTR 16

#define CART 17
#define ORDER 19

#define SEARCH 23
#define SEARCHB 24
#define SLIDESHOW 25
#define BK 32

#define CSDISP 45

#define CLOGIN 50
#define SLOGIN 51
#define CREG 52
#define SREG 53

#define QUIT_CALL 11420

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void message_to_all();

HWND background_holder,sid_Edit,snm_Edit,itm_Search,drawer_b,cosmetics_b,grocery_b,mobiles_b,fashion_b,furniture_b,appliances_b,electronics_b,display_lb;
HWND bt_hd8,bt_hd9,bt_hd10,bt_hd11,bt_hd12,bt_hd13,bt_hd14,search_b,slide_show,slide_drawer,drawerhd_b;
HWND bt_l,bt_r,win_glob,cart_b,order_b;
int height=840,width=1552;
int appliance_bw=150,bt_13w=120;


COLORREF g_rgbText = RGB(0, 0, 0);

char cus_name[15]=""; 
wchar_t handle_info[30]; 

int lgap=4,lshift=30,ushift=20,num=1,cur_pos=0;
static HWND hwndCombo, hwndStatic;
    
HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg,slimg,slide_image;

/*
hBitmap = LoadImage( NULL, _T( "c:\\Path\File.bmp" ), IMAGE_BITMAP, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE );

SIZE size;
BITMAP bmp;
GetObject( (HGDIOBJ)hBitmap, sizeof( BITMAP ), &bmp );
size.cx = bmp.bmWidth;
size.cy = bmp.bmHeight;
*/

struct cinfo{
	float x;
	float y;
	float w;
	float h;
	int is_visible;
}cid[100];


void read_user(){
	FILE* rd;
	char line[200];
	int ln=0,ccpos=0,cppos=0;
	char *division[5];
	rd=fopen("./text_files/cus.txt","r"); 		
	fseek(rd,cur_pos,SEEK_SET);
	fgets(line,199,rd)!=NULL;
	if(strlen(line)>0){
		int i=0;
		division[i] = strtok(line,"|");
		while(division[i]!=NULL)
		{
   			division[++i] = strtok(NULL,"|");
		} 
		strcpy(cus_name,division[1]);
		swprintf(handle_info,30,L"Customer Name\n=>%hs",cus_name);
		printf("Customer Name: %s,%ws",cus_name, handle_info);
		SetWindowTextW(display_lb, handle_info);
	}
	fclose(rd);	
}

void show_drawer()
{
	/*ShowWindow(bt_hd13,SW_HIDE);
	ShowWindow(appliances_b,SW_HIDE);
	*/
	set_Layout(appliances_b,win_glob,cid[APPLIANCES].x,cid[APPLIANCES].y,cid[APPLIANCES].w/2,cid[APPLIANCES].h, width,height,0,0);
	//set_Layout(bt_hd13,win_glob,cid[BTHD13].x,cid[BTHD13].y,cid[BTHD13].w/2,cid[BTHD13].h,width,height,0,0);
	
	ShowWindow(electronics_b,SW_HIDE);
	ShowWindow(bt_r,SW_HIDE);
	ShowWindow(drawer_b,SW_HIDE);
	ShowWindow(bt_hd14,SW_HIDE);
	
	ShowWindow(slide_drawer,SW_SHOW);
	ShowWindow(drawerhd_b,SW_SHOW);
	ShowWindow(cart_b,SW_SHOW);
	ShowWindow(order_b,SW_SHOW);
}

void close_drawer()
{	

	set_Layout(appliances_b,win_glob,cid[APPLIANCES].x,cid[APPLIANCES].y,cid[APPLIANCES].w,cid[APPLIANCES].h, width,height,0,0);
	//set_Layout(bt_hd13,win_glob,cid[BTHD13].x,cid[BTHD13].y,cid[BTHD13].w,cid[BTHD13].h,width,height,0,0);
	
	ShowWindow(electronics_b,SW_SHOW);
	ShowWindow(bt_r,SW_SHOW);
	ShowWindow(drawer_b,SW_SHOW);
	ShowWindow(bt_hd14,SW_SHOW);
	
	ShowWindow(slide_drawer,SW_HIDE);
	ShowWindow(drawerhd_b,SW_HIDE);
	ShowWindow(cart_b,SW_HIDE);
	ShowWindow(order_b,SW_HIDE);
}

void message_to_all()
{
	SendMessageW(background_holder, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(slide_drawer, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slide_image);
	SendMessageW(cosmetics_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(electronics_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(fashion_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(grocery_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(mobiles_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(appliances_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(furniture_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
    
	
 	
	SendMessageW(bt_l, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(bt_r, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(slide_show, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slimg);
	SendMessageW(slide_drawer, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slide_image);
	
	HDC hdc = GetWindowDC(slide_show);
	SendMessage(slide_show, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(slide_show,hdc);
	InvalidateRect (slide_show, NULL, TRUE);
	UpdateWindow (bt_hd8);
	
	hdc = GetWindowDC(bt_hd8);
	SendMessage(bt_hd8, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd8,hdc);
	InvalidateRect (bt_hd8, NULL, TRUE);
	UpdateWindow (bt_hd8);
	
	hdc = GetWindowDC(bt_hd9);
	SendMessage(bt_hd9, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd9,hdc);
	InvalidateRect (bt_hd9, NULL, TRUE);
	UpdateWindow (bt_hd9);
	
	hdc = GetWindowDC(bt_hd10);
	SendMessage(bt_hd10, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd10,hdc);
	InvalidateRect (bt_hd10, NULL, TRUE);
	UpdateWindow (bt_hd10);
	
	hdc = GetWindowDC(bt_hd11);
	SendMessage(bt_hd8, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd11,hdc);
	InvalidateRect (bt_hd11, NULL, TRUE);
	UpdateWindow (bt_hd11);
	
	hdc = GetWindowDC(bt_hd12);
	SendMessage(bt_hd12, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd12,hdc);
	InvalidateRect (bt_hd12, NULL, TRUE);
	UpdateWindow (bt_hd12);
	
	hdc = GetWindowDC(bt_hd13);
	SendMessage(bt_hd13, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd13,hdc);
	InvalidateRect (bt_hd13, NULL, TRUE);
	UpdateWindow (bt_hd13);
	
	hdc = GetWindowDC(bt_hd14);
	SendMessage(bt_hd14, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(bt_hd14,hdc);
	InvalidateRect (bt_hd14, NULL, TRUE);
	UpdateWindow (bt_hd14);
	
	SetWindowTextW(display_lb, handle_info);
	
}
void load_images()
{
	bimg=(HBITMAP)LoadImageW(NULL,L"./resources/gr.bmp",IMAGE_BITMAP,120,110,LR_LOADFROMFILE);
	slimg=(HBITMAP)LoadImageW(NULL,L"./resources/sld.bmp",IMAGE_BITMAP,width*1350/1530,height*220/801,LR_LOADFROMFILE);
	hli=(HBITMAP)LoadImageW(g_hinst,L"./resources/back_ground3.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	slide_image=(HBITMAP)LoadImageW(NULL,L"./resources/drawercus.bmp",IMAGE_BITMAP,width*400/1530,height,LR_LOADFROMFILE);
}

void insert_value(struct cinfo *comp, float x , float y, float width , float height ,int visibility) {
    comp->x = x;
    comp->y = y;
    comp->w = width;
    comp->h = height;
    comp->is_visible = visibility;
}

void create_controls(HWND hwnd)
{
	load_images();
	read_user();
	background_holder=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        0, 0, 1352,600 ,
        hwnd,(HMENU) BK, NULL, NULL);        
	insert_value(&cid[BK],0, 0, 1352,600,1);
        
	slide_show=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        90, 260, 1350, 220,
        hwnd,(HMENU) SLIDESHOW, NULL, NULL);
    insert_value(&cid[SLIDESHOW],90, 260, 1350, 220,1);
        
	drawer_b=CreateWindow("Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
        1405, 30, 40, 40,   
	    hwnd, (HMENU) DRAWER, NULL, NULL);
	insert_value(&cid[DRAWER],1405, 30, 40, 40,1);
		    
    cosmetics_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    60, 100, 150, 140,        
	    hwnd, (HMENU) COSMETICS, NULL, NULL);
	insert_value(&cid[COSMETICS],60, 100, 150, 140,1);
    
	grocery_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
        260, 100, 150, 140,   
	    hwnd, (HMENU) GROCERY, NULL, NULL);
	insert_value(&cid[GROCERY],260, 100, 150, 140,1);
	
	mobiles_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    460, 100, 150, 140,        
	    hwnd, (HMENU) MOBILES, NULL, NULL);
	insert_value(&cid[MOBILES],460, 100, 150, 140,1);
	
	fashion_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    659, 100, 150, 140,        
	    hwnd, (HMENU) FASHION, NULL, NULL);
	insert_value(&cid[FASHION],659, 100, 150, 140,1);
		
	furniture_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    856, 100, 150, 140,        
	    hwnd, (HMENU) FURNITURE, NULL, NULL);
	insert_value(&cid[FURNITURE],856, 100, 150, 140,1);
	
	appliances_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    1056, 100, 150, 140,        
	    hwnd, (HMENU) APPLIANCES, NULL, NULL);
	insert_value(&cid[APPLIANCES],1056, 100, 150, 140,1);
	
	electronics_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    1255, 100, 150, 140,        
	    hwnd, (HMENU) ELECTRONICS, NULL, NULL);	
	insert_value(&cid[ELECTRONICS],1255, 100, 150, 140,1);
	
	srand(time(0));
	int dealcat=rand()%7,dealitm=1,dealc=0;
	
	while(!(categ[dealcat].itm_no>7))
	{
		dealcat=rand()%7;
		dealc++;
	}
	
	bt_hd8=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    80, 590, 160, 150,        
	    hwnd, (HMENU) BTHD8, NULL, NULL);
	insert_value(&cid[BTHD8],80, 590, 160, 150,1);
	
	SendMessageW(bt_hd8, SETINFO, 0*10+dealcat, (LPARAM)&categ[dealcat].itm[0]);	
		
	bt_hd9=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    280, 590, 160, 150,        
	    hwnd, (HMENU) BTHD9, NULL, NULL);
	insert_value(&cid[BTHD9],280,590, 160, 150,1);
	
	SendMessageW(bt_hd9, SETINFO, 1*10+dealcat, (LPARAM)&categ[dealcat].itm[1]);	
	
	bt_hd10=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    480,590, 160, 150,        
	    hwnd, (HMENU) BTHD10, NULL, NULL);	
	insert_value(&cid[BTHD10],480, 590, 160, 150,1);
	
	SendMessageW(bt_hd10, SETINFO, 10*2+dealcat, (LPARAM)&categ[dealcat].itm[2]);	
	
	bt_hd11=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    680, 590, 160, 150,        
	    hwnd, (HMENU) BTHD11, NULL, NULL);
	insert_value(&cid[BTHD11],680, 590, 160, 150,1);
	
	SendMessageW(bt_hd11, SETINFO, 3*10+dealcat, (LPARAM)&categ[dealcat].itm[3]);	
		     
	bt_hd12=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    875, 590, 160, 150,        
	    hwnd, (HMENU) BTHD12, NULL, NULL);	
	insert_value(&cid[BTHD12],875, 590, 160, 150,1);
	
	SendMessageW(bt_hd12, SETINFO, 4*10+dealcat, (LPARAM)&categ[dealcat].itm[4]);	
	
	bt_hd13=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    1075, 590, 160, 150,        
	    hwnd, (HMENU) BTHD13, NULL, NULL);	
	insert_value(&cid[BTHD13],1075, 590, 160, 150,1);
	
	SendMessageW(bt_hd13, SETINFO, 5*10+dealcat, (LPARAM)&categ[dealcat].itm[5]);	
	
	bt_hd14=CreateWindow("csbox", NULL, 
        WS_VISIBLE | WS_CHILD,
	    1275, 590, 160, 150,        
	    hwnd, (HMENU) BTHD14, NULL, NULL);	     
	insert_value(&cid[BTHD14],1275, 590, 160, 150,1);
			
	SendMessageW(bt_hd14, SETINFO,6*10+dealcat, (LPARAM)&categ[dealcat].itm[6]);	
			
	bt_l=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD |SS_BITMAP,
	    16, 325, 50, 80,        
	    hwnd, (HMENU) BTL, NULL, NULL);
	insert_value(&cid[BTL],16, 325, 50, 80,1);
	
	bt_r=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    1464, 325, 50, 80,        
	    hwnd, (HMENU)BTR , NULL, NULL);
	insert_value(&cid[BTR],1464, 325, 50, 80,1);
	
	search_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    968, 19, 50, 50,        
	    hwnd, (HMENU) SEARCHB, NULL, NULL);	
	insert_value(&cid[SEARCHB],968, 19, 50, 50,1);

	itm_Search=CreateWindowW(WC_EDITW, NULL,
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		500, 19, 495, 50, 
		hwnd, (HMENU) SEARCH, NULL, NULL);
	insert_value(&cid[SEARCH],474, 19, 495, 50,1);
	SendMessage(itm_Search, EM_SETLIMITTEXT, 13, TRUE); 
	
	slide_drawer=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        1165, 0, 408, 800,
        hwnd,(HMENU) SLIDEDRAWER, NULL, NULL);   
    ShowWindow(slide_drawer,SW_HIDE);
    insert_value(&cid[SLIDEDRAWER],1165, 0, 408, 800,1);
    /************************************DRAWER BUTTONS******************************/
	
	drawerhd_b=CreateWindow("Static", NULL, 
        WS_VISIBLE | WS_CHILD| SS_BITMAP|SS_NOTIFY,
        1170, 10, 70, 60,   
	    hwnd, (HMENU) CLOSEDRAWER, NULL, NULL);
//	ShowWindow(drawerhd_b,SW_HIDE);
	insert_value(&cid[CLOSEDRAWER],1170, 10, 70, 60,0);
	
	cart_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD| SS_BITMAP|SS_NOTIFY,
	    1180, 115, 350, 120,        
	    hwnd, (HMENU) CART, NULL, NULL);	  
		ShowWindow(cart_b,SW_HIDE);   
	insert_value(&cid[CART],1180, 115, 350, 120,0);
	
	order_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    1180, 263, 350, 120,        
	    hwnd, (HMENU) ORDER, NULL, NULL);	 
		ShowWindow(order_b,SW_HIDE);    
	insert_value(&cid[ORDER],1180, 263, 350, 120,0);

	
/************************************DRAWER BUTTONS******************************/

	display_lb=CreateWindowW(L"Static",L"Customer name",
		WS_CHILD | WS_VISIBLE,
		cid[CSDISP].x, cid[CSDISP].y, cid[CSDISP].w, cid[CSDISP].h, 
		hwnd, (HMENU) CSDISP, NULL, NULL);
		insert_value(&cid[CSDISP],20, 17, 200, 60,1);
	
	HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
              
	SendDlgItemMessage(hwnd, 23, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendMessage(sid_Edit, EM_SETLIMITTEXT, 60, TRUE);  
	
	message_to_all();
}

void resized(LPARAM lParam)
{
	close_drawer();
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d)",width,height);  
	
	set_Layout(drawer_b,win_glob,cid[DRAWER].x, cid[DRAWER].y, cid[DRAWER].w, cid[DRAWER].h, width,height,0,0);
	set_Layout(drawerhd_b,win_glob,cid[CLOSEDRAWER].x, cid[CLOSEDRAWER].y, cid[CLOSEDRAWER].w, cid[CLOSEDRAWER].h, width,height,0,0);
	set_Layout(search_b,win_glob,cid[SEARCHB].x, cid[SEARCHB].y, cid[SEARCHB].w, cid[SEARCHB].h, width,height,0,0);
	
	set_Layout(cosmetics_b,win_glob,cid[COSMETICS].x,cid[COSMETICS].y,cid[COSMETICS].w,cid[COSMETICS].h, width,height,0,0);
	set_Layout(grocery_b,win_glob,cid[GROCERY].x,cid[GROCERY].y,cid[GROCERY].w,cid[GROCERY].h, width,height,0,0);
	set_Layout(mobiles_b,win_glob,cid[MOBILES].x,cid[MOBILES].y,cid[MOBILES].w,cid[MOBILES].h, width,height,0,0);
	set_Layout(fashion_b,win_glob,cid[FASHION].x,cid[FASHION].y,cid[FASHION].w,cid[FASHION].h, width,height,0,0);
	set_Layout(furniture_b,win_glob,cid[FURNITURE].x,cid[FURNITURE].y,cid[FURNITURE].w,cid[FURNITURE].h, width,height,0,0);
	set_Layout(appliances_b,win_glob,cid[APPLIANCES].x,cid[APPLIANCES].y,cid[APPLIANCES].w,cid[APPLIANCES].h, width,height,0,0);
	set_Layout(electronics_b,win_glob,cid[ELECTRONICS].x,cid[ELECTRONICS].y,cid[ELECTRONICS].w,cid[ELECTRONICS].h, width,height,0,0);
	
	set_Layout(bt_hd8,win_glob,cid[BTHD8].x,cid[BTHD8].y,cid[BTHD8].w,cid[BTHD8].h, width,height,0,0);
	set_Layout(bt_hd9,win_glob,cid[BTHD9].x,cid[BTHD9].y,cid[BTHD9].w,cid[BTHD9].h, width,height,0,0);
	set_Layout(bt_hd10,win_glob,cid[BTHD10].x,cid[BTHD10].y,cid[BTHD10].w,cid[BTHD10].h, width,height,0,0);
	set_Layout(bt_hd11,win_glob,cid[BTHD11].x,cid[BTHD11].y,cid[BTHD11].w,cid[BTHD11].h, width,height,0,0);
	set_Layout(bt_hd12,win_glob,cid[BTHD12].x,cid[BTHD12].y,cid[BTHD12].w,cid[BTHD12].h, width,height,0,0);
	set_Layout(bt_hd13,win_glob,cid[BTHD13].x,cid[BTHD13].y,cid[BTHD13].w,cid[BTHD13].h, width,height,0,0);
	set_Layout(bt_hd14,win_glob,cid[BTHD14].x,cid[BTHD14].y,cid[BTHD14].w,cid[BTHD14].h, width,height,0,0);
	
	set_Layout(slide_show,win_glob,cid[SLIDESHOW].x,cid[SLIDESHOW].y,cid[SLIDESHOW].w,cid[SLIDESHOW].h, width,height,0,0);
	
	set_Layout(bt_l,win_glob,cid[BTL].x,cid[BTL].y,cid[BTL].w,cid[BTL].h, width,height,0,0);
	set_Layout(bt_r,win_glob,cid[BTR].x,cid[BTR].y,cid[BTR].w,cid[BTR].h, width,height,0,0);
	
	set_Layout(cart_b,win_glob,cid[CART].x,cid[CART].y,cid[CART].w,cid[CART].h, width,height,0,0);
	set_Layout(order_b,win_glob,cid[ORDER].x,cid[ORDER].y,cid[ORDER].w,cid[ORDER].h, width,height,0,0);
	
	set_Layout(slide_drawer,win_glob,cid[SLIDEDRAWER].x,cid[SLIDEDRAWER].y,cid[SLIDEDRAWER].w,cid[SLIDEDRAWER].h, width,height,0,0);
	
	set_Layout(display_lb,win_glob,cid[CSDISP].x,cid[CSDISP].y,cid[CSDISP].w,cid[CSDISP].h, width,height,30,CSDISP);
	
	load_images();
	
	message_to_all();
	
	set_Layout(itm_Search,win_glob,cid[SEARCH].x, cid[SEARCH].y, cid[SEARCH].w, cid[SEARCH].h, width,height,45,SEARCH);
/*	set_Layout(itm_Name,win_glob,625, 290, 340, 50, width,height,45,NAME);
	set_Layout(itm_Pass,win_glob,625, 423, 340, 50, width,height,45,PASS);
	set_Layout(lb_err,win_glob, 625, 590, 250,20, width,height,0,0);*/
	
//	UpdateWindow(itm_Pass);

}

void action(WPARAM wParam)
{
	switch(LOWORD(wParam)){

		case CLOSEDRAWER:
			close_drawer();
			break;
		case DRAWER:
			show_drawer();	
			break;
		case CART:
			PostQuitMessage(cur_pos*100+56);
			break;
		case ORDER:
			PostQuitMessage(cur_pos*100+57);
			break;
		case COSMETICS:
			PostQuitMessage(cur_pos*1000+58);
			break;
		case GROCERY:
			PostQuitMessage(cur_pos*1000+1*100+58);
			break;
		case MOBILES:
			PostQuitMessage(cur_pos*1000+2*100+58);
			break;
		case FASHION:
			PostQuitMessage(cur_pos*1000+3*100+58);
			break;
		case FURNITURE:
			PostQuitMessage(cur_pos*1000+4*100+58);
			break;
		case APPLIANCES:
			PostQuitMessage(cur_pos*1000+5*100+58);
			break;
		case ELECTRONICS:
			PostQuitMessage(cur_pos*1000+6*100+58);
			break;
		case SEARCHB:
		{
			wchar_t wsitm[15];
			GetWindowTextW(itm_Search, wsitm, 15);
			char sitm[15];
			sprintf(sitm, "%ls",wsitm);
			tempfile(sitm);
			PostQuitMessage(cur_pos*100+82);
			break;
		}
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
	}
	
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow )
{
  read_all();
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT( "Customer" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);
  
  	WNDCLASS Wncl= { 0 };
    Wncl.hInstance     = hInstance;
	Wncl.lpszClassName = "csbox";
	Wncl.lpfnWndProc   = WndCustomBox;
	Wncl.hCursor       = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&Wncl);


  g_hinst = hInstance;
  printf("-%s-",lpCmdLine);
  cur_pos=atoi(lpCmdLine);
  
  RegisterClass(&wc);
  CreateWindow( wc.lpszClassName, TEXT("Customer"),
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                0, 0, width, height, 0, 0, hInstance, 0);  

  while( GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int) msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	
    
  	switch(msg)  
  	{	
			
		case WM_CTLCOLORSTATIC:
		{
		    if( (HWND)lParam == GetDlgItem(hwnd, 45) )
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(255, 255, 255));
		        SetDCBrushColor((HDC)wParam,RGB(0, 176, 240));
		        return (LRESULT)( (HBRUSH)GetStockObject(DC_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		   break;
		}
		
  		case WM_SIZE:
  			{
  				//int height=600,width=1000;
  				resized(lParam);
				
			}
		case WM_PAINT:
		{
			//	slide_image=(HBITMAP)LoadImageW(NULL,L"drawer.bmp",IMAGE_BITMAP,width*400/1530,800,LR_LOADFROMFILE);
			//	SendMessageW(slide_drawer, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slide_image);
			break;
		}
		case WM_CREATE:
		{
			win_glob=hwnd;
		    create_controls(hwnd);
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam); 
		    break;
		}
		
		case QUIT_CALL:
		{
		//	printf("arjklieved ");
			printf("arrieved (%d)",wParam*100+83);
			PostQuitMessage(cur_pos*100000+wParam*100+83);
			break;		
		}
	
	    case WM_COMMAND:
	    {
		   action(wParam);
		   if (HIWORD(wParam) == CBN_SELCHANGE) {      
             
                
            }
            
             break;
	    }
	
	    case WM_DESTROY:
	    {
	    	
	        PostQuitMessage(0);
	        break;
	    }
    }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
