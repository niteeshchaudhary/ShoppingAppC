#include <windows.h>
#include<stdio.h>
#include <time.h>
#include <commctrl.h>
#include<wingdi.h>
#include<math.h>
#include<Richedit.h>
#include<string.h>

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

#define PNL 61

#define QUIT_CALL 11420

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND background_holder,sid_Edit,snm_Edit,itm_Search,drawer_b,display_lb;
HWND search_b,slide_show,slide_drawer,drawerhd_b,board;
HWND win_glob,cart_b,order_b;
int height=840,width=1552;
int appliance_bw=150,bt_13w=120,cur_pos=0;

COLORREF g_rgbText = RGB(0, 0, 0);

int lgap=4,lshift=30,ushift=20,num=1;
static HWND hwndCombo, hwndStatic;

char cus_name[15]=""; 
wchar_t handle_info[30]; 
    
HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg,slimg,slide_image;


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
	ShowWindow(drawer_b,SW_HIDE);
	
	ShowWindow(slide_drawer,SW_SHOW);
	ShowWindow(drawerhd_b,SW_SHOW);
	ShowWindow(cart_b,SW_SHOW);
	ShowWindow(order_b,SW_SHOW);
}

void close_drawer()
{	
	ShowWindow(drawer_b,SW_SHOW);
	
	ShowWindow(slide_drawer,SW_HIDE);
	ShowWindow(drawerhd_b,SW_HIDE);
	ShowWindow(cart_b,SW_HIDE);
	ShowWindow(order_b,SW_HIDE);
}

void message_to_all()
{
	SendMessageW(background_holder, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(slide_drawer, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slide_image);
	SetWindowTextW(display_lb, handle_info);
	HDC hdc = GetWindowDC(board);
	SendMessage(board, WM_PAINT, (WPARAM)hdc, 0);
	ReleaseDC(board,hdc);
	InvalidateRect (board, NULL, TRUE);
	UpdateWindow (itm_Search);
	UpdateWindow (board);
//0	RECT rc = { 0 };
//	GetClientRect(board, &rc);
//	RedrawWindow(board,rc,NULL,RDW_UPDATENOW);
	
}
void load_images()
{
	bimg=(HBITMAP)LoadImageW(NULL,L"./resources/gr.bmp",IMAGE_BITMAP,120,110,LR_LOADFROMFILE);
	hli=(HBITMAP)LoadImageW(g_hinst,L"./resources/orderresult.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
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
        0, 0, 1352,280,
        hwnd,(HMENU) BK, NULL, NULL);        
	insert_value(&cid[BK],0, 0, 1352,280,1);
        
	drawer_b=CreateWindow("Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
        1405, 30, 40, 40,   
	    hwnd, (HMENU) DRAWER, NULL, NULL);
	insert_value(&cid[DRAWER],1405, 30, 40, 40,1);
	
	search_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    968, 19, 50, 50,        
	    hwnd, (HMENU) SEARCHB, NULL, NULL);	
	insert_value(&cid[SEARCHB],968, 19, 50, 50,1);
	
	itm_Search=CreateWindowW(WC_EDITW, NULL,
		WS_CHILD | WS_VISIBLE | ES_CENTER,
		474, 21, 495, 50, 
		hwnd, (HMENU) SEARCH, NULL, NULL);
	insert_value(&cid[SEARCH],474, 21, 495, 50,1);
	//wchar_t wtosch[15];
	//swprintf(wtosch, 14, L"%hs",tosch);
	//SetWindowTextW(itm_Search,wtosch);
	
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
	ShowWindow(drawerhd_b,SW_HIDE);
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

	board=CreateWindow("panel", TEXT("Customer"),
	        WS_CHILD  | WS_VSCROLL| WS_BORDER | WS_VISIBLE,
	        5, 170, 990, 620,
			hwnd, (HMENU) PNL, g_hinst,0);
	insert_value(&cid[PNL],5, 170, 1000, 620,0);
	
	display_lb=CreateWindowW(L"Static",L"Customer name",
		WS_CHILD | WS_VISIBLE,
		20, 17, 200, 60, 
		hwnd, (HMENU) CSDISP, NULL, NULL);
		insert_value(&cid[CSDISP],20, 17, 200, 60,1);
	
	FILE * irc;
	char path[50],ln[300],ctri[8];
	char *divn[5];
	int ctritem=0;
	int found=0;
	sprintf(path,"./text_files/%s_orders.txt",cus_name);
	irc=fopen(path,"r");
	printf("\n{ %s * }",path);
	while(fgets(ln,299,irc)!=NULL)
	{
			if(strlen(ln)>0){
				int i=0;
				divn[i] = strtok(ln,"|");
				while(divn[i]!=NULL)
				{
		   			divn[++i] = strtok(NULL,"|");
				}
				strcpy(ctri,divn[1]);
				ctritem=atoi(ctri);
				strcpy(categ[ctritem%10].itm[ctritem/10].qty,divn[2]);
				strcpy(categ[ctritem%10].itm[ctritem/10].addss,divn[3]);
				printf("\n{ %s num=%d }",categ[ctritem%10].itm[ctritem/10].title,ctritem);
				HWND ws = CreateWindow("cslist2", NULL,
					WS_VISIBLE | WS_BORDER | WS_CHILD,
					0, 250*found, 1530, 250,
					board, (HMENU)100+found, 0, 0); 
					SendMessageW(board, SETINFO, 0, 0);
					itm_num++;
					SendMessageW(ws, SETINFO, ctritem, (LPARAM)&categ[ctritem%10].itm[ctritem/10]);	
				found++;
			}
			else{
				continue;
			}
	}		
	
	fclose(irc);	
		             
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
	
	set_Layout(board,win_glob,cid[PNL].x, cid[PNL].y, cid[PNL].w, cid[PNL].h, width,height,0,0);
	
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

    g_hinst = hInstance;
    //rdtempfile(tosch);
   // printf("^*#%s$^",tosch);
    printf("-%s-",lpCmdLine);
	cur_pos=atoi(lpCmdLine);
	printf("(%d pos)",cur_pos);
  
	WNDCLASS Wn= { 0 };
    Wn.hInstance     = hInstance;
	Wn.lpszClassName = "panel";
	Wn.lpfnWndProc   = WndPanel;
	Wn.hCursor       = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&Wn);
	
	WNDCLASS Wncl= { 0 };
    Wncl.hInstance     = hInstance;
	Wncl.lpszClassName = "cslist2";
	Wncl.lpfnWndProc   = WndCustomList2;
	Wncl.hCursor       = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&Wncl);

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


