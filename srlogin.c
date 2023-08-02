#include <windows.h>
#include<stdio.h>
#include <time.h>
#include <commctrl.h>
#include<wingdi.h>
#include<math.h>
#include<Richedit.h>

#include"Layout.h"

#define SLIDEDRAWER 40
#define CLOSEDRAWER 42
#define DRAWER 0
#define SUBMIT 2
#define BACK 3
#define NME 24
#define PASS 23
#define ERR 29

#define SL 17
#define SR 18
#define CL 19
#define CR 20


char *dim[5];
int lno=0,cpos=0,ppos=0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hl,drawer_b,submit_b,bt_hd3,lb_err,back_b,slide_drawer,drawerhd_b,sl_b,sr_b,cl_b,cr_b;

HWND itm_Pass,win_glob,itm_Nme;

int height=840,width=1552;

int ft_size=42;


HFONT hfFont;

COLORREF g_rgbText = RGB(0, 0, 0);

int lgap=4,lshift=30,ushift=20,num=1;

static HWND hwndCombo, hwndStatic;

    
HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg,wtbk,slide_image;

struct cinfo{
	float x;
	float y;
	float w;
	float h;
	int is_visible;
}cid[100];

int verify(int s_c,wchar_t ID[],wchar_t pass[])
{
	FILE * vf;
	char line[100];
	char i_d[15],pa_ss[15];
	sprintf(i_d, "%ls",ID);
	sprintf(pa_ss,"%ls",pass);
	if(s_c==1){
		vf=fopen("./text_files/sellr.txt","r");
	}
	else if(s_c==2)
	{
		vf=fopen("./text_files/cus.txt","r");
	}
	printf("\nVerification reached\n");
	while(fgets(line,99,vf)!=NULL)
	{
		ppos=cpos;
		int i=0;
		dim[i] = strtok(line,"|");
		while(dim[i]!=NULL)
		{
   			dim[++i] = strtok(NULL,"|");
		}
		cpos=ftell(vf);
		if(!strcmp(dim[1],i_d))
		{
			if(!strcmp(dim[2],pa_ss)){
				printf("\nyou are successfully verified\n");
				fclose(vf);
				SetWindowTextW(itm_Nme, L"");
				SetWindowTextW(itm_Pass, L"");
				system("exit");
		     	PostQuitMessage(ppos*100+91);
				return 1;
			}
			return 2;
		}
	}
	return 0;
}

void seller_login()
{
	wchar_t c_nm[15];
	wchar_t c_ps[15];
	int k=3;
		//system("cls");
		printf("Enter name(of 6 letters)\n");
		//scanf("%s",&c_nm);
		printf("Enter password\n");
		//scanf("%s",&c_ps);
		GetWindowTextW(itm_Nme, c_nm, 13);
		GetWindowTextW(itm_Pass, c_ps, 13);
	//	printf("{%ls},{%ls}",c_nm,c_ps);
		if (lstrlenW(c_nm) != 0 && lstrlenW(c_ps) != 0){
			k=verify(1,c_nm,c_ps);
		}
		else{
			SetWindowTextW(lb_err, L"*Please fill all details");
		}
	switch(k){
			case 2:
    			
  				SetWindowTextW(lb_err, L"*name didn't match password"); 
				printf("name didn't match password\n");
				break;
			case 0:
				SetWindowTextW(lb_err, L"*no account for this user name");
				printf("no account for this user name\n");
				break;
		}
}


void message_to_all()
{

	SendMessageW(hl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(drawer_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(submit_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(back_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(lb_err, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) wtbk);
 	SendMessageW(slide_drawer, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) slide_image);
	 //SendMessageW(bt_hd3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
}
void load_images()
{
	hli=(HBITMAP)LoadImageW(g_hinst,L"./resources/lgin.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	bimg=(HBITMAP)LoadImageW(NULL,L"./resources/gr.bmp",IMAGE_BITMAP,120,110,LR_LOADFROMFILE);
	//wtbk=(HBITMAP)LoadImageW(NULL,L"yl_back.bmp",IMAGE_BITMAP,250,40,LR_LOADFROMFILE);
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
	
	
	/*CreateWindow(TEXT("button"), TEXT("Seller"),    
			             WS_VISIBLE | WS_CHILD ,
			             width/2, height/3+25, 80, 25,        
			             hwnd, (HMENU) 2, NULL, NULL);*/ 
	/*bt_hd=CreateWindow("Button", NULL, 
        WS_VISIBLE | WS_CHILD|BS_BITMAP,
	    80, 100, 120, 110,        
	    hwnd, (HMENU) 1, NULL, NULL);*/		
		
	hl=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        0, 0, 1352,600 ,
        hwnd,(HMENU) 32, NULL, NULL);
	
	submit_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    800, 540, 175, 60,        
	    hwnd, (HMENU) SUBMIT, NULL, NULL);
	
	back_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    800, 610, 175, 60,        
	    hwnd, (HMENU)BACK, NULL, NULL);
	    
	lb_err=CreateWindowW(L"Static",L"nkc", 
        WS_CHILD | WS_VISIBLE|SS_CENTER,//|SS_BITMAP,//|WM_ERASEBKGND,
        //630, 590, 250,40 ,
        0,90,1530,30,
        hwnd, (HMENU) ERR, NULL, NULL);
        ShowWindow (lb_err, SW_HIDE);

	itm_Nme=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
	625, 289, 340, 50, hwnd, (HMENU) NME, NULL, NULL);
	
	itm_Pass=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE |ES_PASSWORD,
	625, 423, 340, 50, hwnd, (HMENU) PASS, NULL, NULL);
	
	hfFont = CreateFont(ft_size,25,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
              
	SendDlgItemMessage(hwnd, PASS, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, NME, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendMessage(itm_Nme, EM_SETLIMITTEXT, 13, TRUE);  
	SendMessage(itm_Pass, EM_SETLIMITTEXT, 13, TRUE);  
	message_to_all();
}

void resized(LPARAM lParam)
{
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d){%d %d}",width,height,LOWORD(submit_b),HIWORD(submit_b));
	load_images();
	message_to_all();
	set_Layout(submit_b,win_glob,800, 540, 175, 60, width,height,0,0);
	set_Layout(back_b,win_glob,800, 610, 175, 60, width,height,0,0);
	set_Layout(drawer_b,win_glob,1405, 30, 40, 40, width,height,0,0);
	set_Layout(itm_Nme,win_glob,625, 289, 340, 50, width,height,45,NME);
	set_Layout(itm_Pass,win_glob,625, 423, 340, 50, width,height,45,PASS);
	set_Layout(lb_err,win_glob, 0,90,1530,30, width,height,25,ERR);
	
	UpdateWindow(itm_Pass);
	//UpdateWindow(itm_Name);
	
}

void action(WPARAM wParam,LPARAM lParam)
{
	switch(LOWORD(wParam)){
		
		case SUBMIT:
			ShowWindow (lb_err, SW_SHOW);
			seller_login(); 
			break;
		case BACK:
			system("exit");
			PostQuitMessage(90);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
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
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT( "Seller" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);

  g_hinst = hInstance;
  
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
  		case WM_SIZE:
  		{
  				//int height=600,width=1000;
  				resized(lParam);
				break;
		}
		case WM_CREATE:
		{
			load_images();
			win_glob=hwnd;
		    create_controls(hwnd); 
		    SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam); 
		    break;
		}
		case WM_PAINT:{
			break;
		}
	
	    case WM_COMMAND:
	    {
		   action(wParam,lParam);
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

