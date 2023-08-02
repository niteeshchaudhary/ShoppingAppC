#include <windows.h>
#include<stdio.h>
#include <wchar.h>
#include <time.h>
#include <commctrl.h>
#include<wingdi.h>
#include<math.h>
#include<Richedit.h>
#include<string.h>

#include"Layout.h"

#define DRAWER 1
#define SUBMIT 2
#define BACK 3
#define NAME 22
#define PASS 23
#define CPASS 24
#define ERR 29

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hl,lb_err,cnm_Edit,submit_b,drawer_b,back_b;

HWND itm_Pass,itm_cPass,win_glob;

int height=840,width=1552;

int ft_size=42;


char *dim[5];
int lno=0,cpos=0,ppos=0;


HFONT hfFont;

COLORREF g_rgbText = RGB(0, 0, 0);

int lgap=4,lshift=30,ushift=20,num=1;
static HWND hwndCombo, hwndStatic;
  

HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg;

/*
hBitmap = LoadImage( NULL, _T( "c:\\Path\File.bmp" ), IMAGE_BITMAP, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE );

SIZE size;
BITMAP bmp;
GetObject( (HGDIOBJ)hBitmap, sizeof( BITMAP ), &bmp );
size.cx = bmp.bmWidth;
size.cy = bmp.bmHeight;
*/
struct user{
	char user_name[15];
    char user_pass[15];
};

struct customer{
	int cur;
    int no_of_cust;
	struct user customers[100];
}customer_info;


void read_user(){
	FILE* rd;
	char line[200];	
	int ln=0,ccpos=0,cppos=0;
	char *division[5];
	rd=fopen("./text_files/cus.txt","r"); 		
	int l_no=0;
	while(fgets(line,199,rd)!=NULL)
	{
		cppos=ccpos;
		ccpos=ftell(rd);
		if(strlen(line)>0){
			int i=0;
			division[i] = strtok(line,"|");
			while(division[i]!=NULL)
			{
	   			division[++i] = strtok(NULL,"|");
			} 
				strcpy(customer_info.customers[l_no].user_name,division[1]);
				strcpy(customer_info.customers[l_no].user_pass,division[2]);
				l_no++;  
		}
		else{
			continue;
		}	
	}
	customer_info.no_of_cust=l_no; 
	customer_info.cur=ccpos;
	printf("%d",customer_info.no_of_cust);
	
	fclose(rd);	
}

int check(wchar_t  name[])
{    
	char nm[15];
	sprintf(nm, "%ls",name);
	for(int i=0;i<customer_info.no_of_cust;i++){
		if(!strcmp(nm,customer_info.customers[i].user_name)){
			printf("This user already exists\n");
			return 1;
		} 
	}
	return 0;
}

void save(wchar_t ID[],wchar_t pass[])
{
	FILE *sv;
	sv=fopen("./text_files/cus.txt","a");
	fprintf(sv,"A|%ls|%ls| | ; \n",ID,pass);
	fclose(sv);
}


void customer_reg(HWND hwnd)
{
	int s_len = GetWindowTextLengthW(cnm_Edit) + 1;
	int p_len = GetWindowTextLengthW(itm_Pass) + 1;
	int cp_len = GetWindowTextLengthW(itm_cPass) + 1;
	wchar_t s_nm[s_len];
	wchar_t s_ps[p_len];
	wchar_t s_cps[cp_len];
	
	GetWindowTextW(cnm_Edit, s_nm, s_len);
	GetWindowTextW(itm_Pass, s_ps, p_len);
	GetWindowTextW(itm_cPass, s_cps, cp_len);
	
	if(check(s_nm))
	{
		SetWindowTextW(lb_err, L"*User name already exist");
		return;
	}	
	
	if (lstrlenW(s_nm) != 0 && lstrlenW(s_ps) != 0 && lstrlenW(s_cps) != 0) {
		if(!wcscmp(s_ps,s_cps))
		{
			save(s_nm,s_ps);
			SetWindowTextW(cnm_Edit, L"");
			SetWindowTextW(itm_Pass, L"");
			SetWindowTextW(itm_cPass, L"");
			system("exit");
		    PostQuitMessage(customer_info.cur*100+92);
		}
		else
		{
			SetWindowTextW(lb_err, L"*password didn't matched confirm password");
		}
	}
	else{
		SetWindowTextW(lb_err, L"*Please fill all details");
	}
	printf("Enter ID(of 6 letters) %ls %ls %d \n",s_nm,s_ps,lstrlenW(s_nm));
	printf("Enter password\n");
	printf("Enter confirm password\n");
}


void message_to_all()
{

	SendMessageW(hl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(submit_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(drawer_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(back_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);

	
}
void load_images()
{
	hli=(HBITMAP)LoadImageW(NULL,L"./resources/cregs.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	bimg=(HBITMAP)LoadImageW(NULL,L"./resources/gr.bmp",IMAGE_BITMAP,120,110,LR_LOADFROMFILE);
}




void create_controls(HWND hwnd)
{
	load_images();
	
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
	
	lb_err=CreateWindowW(L"Static",L"nkc", 
        WS_CHILD | WS_VISIBLE|SS_CENTER,//|SS_BITMAP,//|WM_ERASEBKGND,
        //630, 590, 250,40 ,
         0,90,1530,30,
        hwnd, (HMENU) ERR, NULL, NULL);
        ShowWindow (lb_err, SW_HIDE);

	submit_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    650, 628, 170, 60,        
	    hwnd, (HMENU) SUBMIT, NULL, NULL);
	
	back_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    837, 628, 170, 60,        
	    hwnd, (HMENU) BACK, NULL, NULL);
	    
	cnm_Edit= CreateWindowW(L"Edit", NULL, 
        WS_CHILD | WS_VISIBLE ,
        625, 275, 330, 51, 
		hwnd, (HMENU) NAME,NULL, NULL);
    
    
	/*itm_Edit=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE |WS_BORDER,
	630, 280, 300, 50, hwnd, (HMENU) NAME, NULL, NULL);*/
	
	itm_Pass=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE |ES_PASSWORD,
		625, 380, 330, 51, 
		hwnd, (HMENU) PASS, NULL, NULL);

	itm_cPass=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE|ES_PASSWORD,
		625, 498, 330, 51, 
		hwnd, (HMENU) CPASS, NULL, NULL);
		
	hfFont = CreateFont(ft_size,18,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
              
	SendDlgItemMessage(hwnd, PASS, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, CPASS, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, NAME, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendMessage(itm_cPass, EM_SETLIMITTEXT, 15, TRUE);  
	SendMessage(cnm_Edit, EM_SETLIMITTEXT, 15, TRUE);  
	SendMessage(itm_Pass, EM_SETLIMITTEXT, 15, TRUE);  
	
	message_to_all();

}

void resized(LPARAM lParam)
{
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d)",width,height);
	load_images();
	message_to_all();
	set_Layout(submit_b,win_glob,650, 628, 170, 60, width,height,0,0);
	set_Layout(back_b,win_glob,837, 628, 170, 60, width,height,0,0);
	set_Layout(drawer_b,win_glob,1405, 30, 40, 40, width,height,0,0);
	set_Layout(cnm_Edit,win_glob,625, 275, 330, 51, width,height,45,NAME);
	set_Layout(itm_Pass,win_glob,625, 380, 330, 51, width,height,45,PASS);
	set_Layout(itm_cPass,win_glob,625, 498, 330, 51, width,height,45,CPASS);
	set_Layout(lb_err,win_glob, 0,90,1530,30, width,height,25,ERR);
	UpdateWindow(itm_Pass);
	UpdateWindow(cnm_Edit);
	UpdateWindow(lb_err);
}

void action(WPARAM wParam,HWND hwnd)
{
	switch(LOWORD(wParam)){
		
		case DRAWER:
			
			break;
		case SUBMIT:
			ShowWindow (lb_err, SW_SHOW);
			customer_reg(hwnd);
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
  wc.lpszClassName = TEXT( "Customer" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);

  g_hinst = hInstance;
  
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

  		case WM_SIZE:
  		{
  				resized(lParam);
				break;
		}
		case WM_CREATE:
		{
			read_user();
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
		   action(wParam,hwnd);
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
