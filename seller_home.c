#include <windows.h>
#include<stdio.h>
#include <time.h>
#include <commctrl.h>
#include<wingdi.h>
#include<math.h>
#include<Richedit.h>

#include "Layout.h"

#define SLIDEDRAWER 40
#define CLOSEDRAWER 42
#define DRAWER 0

#define COSMETICS 93
#define GROCERY 94
#define MOBILES 95
#define FASHION 96
#define FURNITURE 97
#define APPLIANCES 98
#define ELECTRONICS 99

#define BTHD8 8
#define BTHD9 9
#define BTHD10 10
#define BTHD11 11
#define BTHD12 12
#define BTHD13 13
#define BTHD14 14
#define BTL 15
#define BTR 16
#define LOGOUT 61
#define ADDED 62

#define SLDISP 45

#define SL 17
#define SR 18
#define CL 19
#define CR 20

#define SEARCH 23
#define SEARCHB 24
#define SLIDESHOW 25
#define BK 32

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND background_holder,sid_Edit,snm_Edit,itm_Search,drawer_b,cosmetics_b,grocery_b,mobiles_b,fashion_b,furniture_b,appliances_b,electronics_b;
HWND bt_hd8,bt_hd9,bt_hd10,bt_hd11,bt_hd12,bt_hd13,bt_hd14,search_b,slide_show,slide_drawer,drawerhd_b;
HWND bt_l,bt_r,win_glob,sl_b,sr_b,cl_b,cr_b,added_b,logout_b,display_lb;
int height=840,width=1552;
int appliance_bw=150,bt_13w=120;

int cur_pos;
int lgap=4,lshift=30,ushift=20,num=1;
static HWND hwndCombo, hwndStatic;
const wchar_t *cat[] = { L"Cloths", L"Appliences", L"gadgets", L"footwears", L"automobiles" };
 
char seller_id[15]="";   
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
	rd=fopen("./text_files/sellr.txt","r"); 		
	fseek(rd,cur_pos,SEEK_SET);
	fgets(line,199,rd)!=NULL;
	if(strlen(line)>0){
		int i=0;
		division[i] = strtok(line,"|");
		while(division[i]!=NULL)
		{
   			division[++i] = strtok(NULL,"|");
		} 
		strcpy(seller_id,division[1]);
		swprintf(handle_info,30,L"Seller ID: %hs",seller_id);
		printf("Seller ID: %s",seller_id);
		SetWindowTextW(display_lb, handle_info);
	}
	fclose(rd);	
}

void message_to_all()
{
	SendMessageW(background_holder, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(cosmetics_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(electronics_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(fashion_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(grocery_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(mobiles_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(appliances_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(furniture_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(added_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
 	SendMessageW(logout_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
 	SendMessageW(display_lb, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
 	SetWindowTextW(display_lb, handle_info);

	
}
void load_images()
{
	hli=(HBITMAP)LoadImageW(g_hinst,L"./resources/sellerhome.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	bimg=(HBITMAP)LoadImageW(NULL,L"./resources/gr.bmp",IMAGE_BITMAP,cid[GROCERY].w, cid[GROCERY].h,LR_LOADFROMFILE);
}

void insert_value(struct cinfo *comp, float x , float y, float width , float height ,int visibility) {
    comp->x = x;
    comp->y = y;
    comp->w = width;
    comp->h = height;
    comp->is_visible = visibility;
}

void fill_dimention()
{
	insert_value(&cid[BK],0, 0, 1352,600,1);	
	insert_value(&cid[COSMETICS],60, 315, 150, 140,1);
	insert_value(&cid[GROCERY],260, 315, 150, 140,1);
	insert_value(&cid[MOBILES],460, 315, 150, 140,1);
	insert_value(&cid[FASHION],659, 315, 150, 140,1);
	insert_value(&cid[FURNITURE],856, 315, 150, 140,1);
	insert_value(&cid[APPLIANCES],1056, 315, 150, 140,1);
	insert_value(&cid[ELECTRONICS],1255, 315, 150, 140,1);
	insert_value(&cid[ADDED],530, 545, 510, 140,1);
	insert_value(&cid[LOGOUT],1186, 545, 220, 140,1);
	insert_value(&cid[SLDISP],20, 30, 320, 40,1);
}
void create_controls(HWND hwnd)
{
	fill_dimention();
	load_images();
	
	background_holder=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        cid[BK].x, cid[BK].y, cid[BK].w,cid[BK].h ,
        hwnd,(HMENU) BK, NULL, NULL);        
	
        
	added_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
        cid[ADDED].x, cid[ADDED].y, cid[ADDED].w,cid[ADDED].h,
        hwnd,(HMENU) ADDED, NULL, NULL);
        
	logout_b=CreateWindow("Static", NULL, 
        WS_VISIBLE | WS_CHILD| SS_BITMAP|SS_NOTIFY,
        cid[LOGOUT].x, cid[LOGOUT].y, cid[LOGOUT].w,cid[LOGOUT].h,
	    hwnd, (HMENU) LOGOUT, NULL, NULL);

		    
    cosmetics_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[COSMETICS].x, cid[COSMETICS].y, cid[COSMETICS].w, cid[COSMETICS].h,        
	    hwnd, (HMENU) COSMETICS, NULL, NULL);
	
    
	grocery_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
        cid[GROCERY].x, cid[GROCERY].y, cid[GROCERY].w, cid[GROCERY].h,   
	    hwnd, (HMENU) GROCERY, NULL, NULL);
	
	
	mobiles_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[MOBILES].x, cid[MOBILES].y, cid[MOBILES].w, cid[MOBILES].h,        
	    hwnd, (HMENU) MOBILES, NULL, NULL);
	
	
	fashion_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[FASHION].x, cid[FASHION].y, cid[FASHION].w, cid[FASHION].h,        
	    hwnd, (HMENU) FASHION, NULL, NULL);
	
		
	furniture_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[FURNITURE].x, cid[FURNITURE].y, cid[FURNITURE].w, cid[FURNITURE].h,        
	    hwnd, (HMENU) FURNITURE, NULL, NULL);
	
	
	appliances_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[APPLIANCES].x, cid[APPLIANCES].y, cid[APPLIANCES].w, cid[APPLIANCES].h,        
	    hwnd, (HMENU) APPLIANCES, NULL, NULL);
	
	
	electronics_b=CreateWindow(TEXT("Static"), NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP|SS_NOTIFY,
	    cid[ELECTRONICS].x, cid[ELECTRONICS].y, cid[ELECTRONICS].w, cid[ELECTRONICS].h,        
	    hwnd, (HMENU) ELECTRONICS, NULL, NULL);	
	
	display_lb=CreateWindowW(L"Static",L"Seller id : ",
		WS_CHILD | WS_VISIBLE,
		cid[SLDISP].x, cid[SLDISP].y, cid[SLDISP].w, cid[SLDISP].h, 
		hwnd, (HMENU) SLDISP, NULL, NULL);

	
	HFONT hfFont = CreateFont(30,12,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
              
	SendDlgItemMessage(hwnd, SLDISP, WM_SETFONT, (WPARAM)hfFont, TRUE);
	read_user();
	message_to_all();
}

void resized(LPARAM lParam)
{
	//close_drawer();
	
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d)",width,height);  
	
	
	set_Layout(added_b,win_glob,cid[ADDED].x,cid[ADDED].y,cid[ADDED].w,cid[ADDED].h, width,height,0,0);
	set_Layout(logout_b,win_glob,cid[LOGOUT].x,cid[LOGOUT].y,cid[LOGOUT].w,cid[LOGOUT].h, width,height,0,0);
	set_Layout(cosmetics_b,win_glob,cid[COSMETICS].x,cid[COSMETICS].y,cid[COSMETICS].w,cid[COSMETICS].h, width,height,0,0);
	set_Layout(grocery_b,win_glob,cid[GROCERY].x,cid[GROCERY].y,cid[GROCERY].w,cid[GROCERY].h, width,height,0,0);
	set_Layout(mobiles_b,win_glob,cid[MOBILES].x,cid[MOBILES].y,cid[MOBILES].w,cid[MOBILES].h, width,height,0,0);
	set_Layout(fashion_b,win_glob,cid[FASHION].x,cid[FASHION].y,cid[FASHION].w,cid[FASHION].h, width,height,0,0);
	set_Layout(furniture_b,win_glob,cid[FURNITURE].x,cid[FURNITURE].y,cid[FURNITURE].w,cid[FURNITURE].h, width,height,0,0);
	set_Layout(appliances_b,win_glob,cid[APPLIANCES].x,cid[APPLIANCES].y,cid[APPLIANCES].w,cid[APPLIANCES].h, width,height,0,0);
	set_Layout(electronics_b,win_glob,cid[ELECTRONICS].x,cid[ELECTRONICS].y,cid[ELECTRONICS].w,cid[ELECTRONICS].h, width,height,0,0);
	
	set_Layout(display_lb,win_glob,cid[SLDISP].x,cid[SLDISP].y,cid[SLDISP].w,cid[SLDISP].h, width,height,30,SLDISP);
	load_images();
//	hli=(HBITMAP)LoadImageW(g_hinst,L"sellerhome.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	
	message_to_all();
}

void action(WPARAM wParam)
{
	switch(LOWORD(wParam)){

		case ADDED:
			
			break;
		case LOGOUT:
		    system("exit");
			PostQuitMessage(90);
			//PostQuitMessage(0);
			break;
		case COSMETICS:
			system("exit");
			PostQuitMessage(cur_pos*100+COSMETICS);
			break;
		case GROCERY:
			system("exit");
			PostQuitMessage(cur_pos*100+GROCERY);
			break;
		case MOBILES:
			system("exit");
			PostQuitMessage(cur_pos*100+MOBILES);
			break;
		case FASHION:
			system("exit");
			PostQuitMessage(cur_pos*100+FASHION);
			break;
		case FURNITURE:
			system("exit");
			PostQuitMessage(cur_pos*100+FURNITURE);
			break;
		case APPLIANCES:
			system("exit");
			PostQuitMessage(cur_pos*100+APPLIANCES);
			break;
		case ELECTRONICS:
			system("exit");
			PostQuitMessage(cur_pos*100+ELECTRONICS);
			break;

		
		
	}
	
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow )
{
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT( "Seller" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);

  g_hinst = hInstance;
  printf("-%s-",lpCmdLine);
  cur_pos=atoi(lpCmdLine);
  RegisterClass(&wc);
  CreateWindow( wc.lpszClassName, TEXT("Seller"),
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
		        SetTextColor((HDC)wParam, RGB(200, 2, 105));
		        return (LRESULT)( (HBRUSH)GetStockObject(NULL_BRUSH));  
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
