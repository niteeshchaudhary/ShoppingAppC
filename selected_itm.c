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
#include"usefullfunc.h"

#define CART 1
#define BUY 2
#define BACK 3
#define TITLE 22
#define PRICE 23
#define DES 24
#define ERR 29
#define BK 32
#define PRODIMG 76
#define CSDISP 45

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void message_to_all();
void load_images();

HWND hl,lb_err,title_lb,buy_b,cart_b,drawer_b,back_b,add_b,display_lb,imgh,display_lb;

HWND price_lb,des_Edit,win_glob;

int height=840,width=1552,cur_pos=0;

int ft_size=35;


char *dim[5];
char cus_name[15]=""; 
wchar_t handle_info[30]; 
wchar_t img_loc[200];

int proitm=0;
int lno=0,cpos=0,ppos=0;


HFONT hfFont;

COLORREF g_rgbText = RGB(0, 0, 0);

int lgap=4,lshift=30,ushift=20,num=1;
int cur_pos,ctgry;

static HWND hwndCombo, hwndStatic;
  

HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg,pimg;

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
	printf("C%d)",cur_pos);
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

void message_to_all()
{

	SendMessageW(hl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(buy_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(cart_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(add_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(back_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	if(wcslen(img_loc)>0)
	{
		printf(";-kd-;");
		SendMessageW(imgh, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)pimg);
	}
	SetWindowTextW(display_lb, handle_info);
	SetWindowTextW(title_lb,get_text(title_lb));
	SetWindowTextW(price_lb,get_text(price_lb));
	SetWindowTextW(des_Edit,get_text(des_Edit) );
	
	UpdateWindow(title_lb);
	UpdateWindow(price_lb);
	UpdateWindow(des_Edit);
	UpdateWindow(lb_err);
	
}

void load_images()
{
	hli=(HBITMAP)LoadImageW(NULL,L"D:/csPoject/resources/shwitm2.bmp",IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	bimg=(HBITMAP)LoadImageW(NULL,L"D:/csPoject/resources/shwitm2.bmp",IMAGE_BITMAP,cid[PRODIMG].w,cid[PRODIMG].h,LR_LOADFROMFILE);
	pimg=(HBITMAP)LoadImageW(NULL,img_loc,IMAGE_BITMAP,get_c_w(imgh,cid[PRODIMG].w,width),cid[PRODIMG].h,LR_LOADFROMFILE);
	printf(";-kc-;");
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
	insert_value(&cid[BK],0, 0, 1532,801 ,1);	
	insert_value(&cid[TITLE],485, 230, 247, 55,1);
	insert_value(&cid[PRICE],485, 308, 247, 55,1);
	insert_value(&cid[DES],150, 423, 584, 235,1);
	insert_value(&cid[BUY],907, 680, 240, 75,1);
	insert_value(&cid[CART],1183, 680, 245, 75,1);
	insert_value(&cid[BACK],1380, 33, 50, 50,1);
	insert_value(&cid[CSDISP],20, 17, 200, 60,1);
	insert_value(&cid[ERR],50,100,700,30,1);
	insert_value(&cid[PRODIMG],1010, 250, 330, 370,1);
}

void create_controls(HWND hwnd)
{
	wchar_t tl[18];
	wchar_t pr[18];
	wchar_t sd[30];
	wchar_t descr[200];
	struct items* st; 
	
	for(int i=0;i<strlen(categ[ctgry].itm[proitm].des);i++)
	{
		if(categ[ctgry].itm[proitm].des[i]=='$'){
			categ[ctgry].itm[proitm].des[i]='\r';
			i++;
			categ[ctgry].itm[proitm].des[i]='\n';
		}
	}
  	st = (struct items*)&categ[ctgry].itm[proitm];
	//swprintf(jci, 9, L"%d",wParam);
	pimg=(HBITMAP)LoadImageW(NULL,img_loc,IMAGE_BITMAP,cid[PRODIMG].w,cid[PRODIMG].h,LR_LOADFROMFILE);
	swprintf(tl, 16, L"%hs",st->title);
	swprintf(pr, 16, L"Rs : %hs",st->price);
	swprintf(sd, 26, L"seller : %hs",st->seller_id);
	swprintf(descr, 198, L"%hs",st->des);
	swprintf(img_loc, 200, L"%hs",st->location);
	printf("-:%hs:%s-",img_loc,categ[ctgry].itm[proitm].location);
	fill_dimention();
	load_images();
		
		
	hl=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD |SS_BITMAP,
        cid[BK].x, cid[BK].y, cid[BK].w,cid[BK].h ,
        hwnd,(HMENU) BK, NULL, NULL);
    
    imgh=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD |SS_BITMAP,
       cid[PRODIMG].x, cid[PRODIMG].y, cid[PRODIMG].w,cid[PRODIMG].h,
        hwnd,(HMENU) PRODIMG, NULL, NULL);
        
    SendMessageW(imgh, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)pimg);
	
	lb_err=CreateWindowW(L"Static",L"", 
        WS_CHILD | SS_CENTER,
        cid[ERR].x, cid[ERR].y, cid[ERR].w,cid[ERR].h,
        hwnd, (HMENU) ERR, NULL, NULL);
        ShowWindow (lb_err, SW_HIDE);
    
	back_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
        cid[BACK].x, cid[BACK].y, cid[BACK].w,cid[BACK].h,   
	    hwnd, (HMENU) BACK, NULL, NULL);

	buy_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
	    cid[BUY].x, cid[BUY].y, cid[BUY].w,cid[BUY].h,        
	    hwnd, (HMENU) BUY, NULL, NULL);
	
	cart_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
	    cid[CART].x, cid[CART].y, cid[CART].w,cid[CART].h,        
	    hwnd, (HMENU) CART, NULL, NULL);
	    
	title_lb= CreateWindowW(L"Static", tl, 
        WS_CHILD | WS_VISIBLE,
        cid[TITLE].x, cid[TITLE].y, cid[TITLE].w,cid[TITLE].h , 
		hwnd, (HMENU) TITLE,NULL, NULL);
	
	price_lb=CreateWindowW(L"Static", pr,
		WS_CHILD | WS_VISIBLE ,
		cid[PRICE].x, cid[PRICE].y, cid[PRICE].w,cid[PRICE].h , 
		hwnd, (HMENU) PRICE, NULL, NULL);

	des_Edit=CreateWindowW(WC_EDITW, descr,
	 	WS_CHILD | WS_VISIBLE|ES_MULTILINE|WS_VSCROLL|ES_READONLY,
		cid[DES].x, cid[DES].y, cid[DES].w,cid[DES].h , 
		hwnd, (HMENU) DES, NULL, NULL);
	
	display_lb=CreateWindowW(L"Static",L"Customer name",
		WS_CHILD | WS_VISIBLE,
		cid[CSDISP].x, cid[CSDISP].y, cid[CSDISP].w, cid[CSDISP].h, 
		hwnd, (HMENU) CSDISP, NULL, NULL);
		
	hfFont = CreateFont(ft_size,18,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
              
	SendDlgItemMessage(hwnd, DES, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, TITLE, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, PRICE, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendMessage(price_lb, EM_SETLIMITTEXT, 15, TRUE);  
	SendMessage(des_Edit, EM_SETLIMITTEXT, 170, TRUE);  
	SendMessage(title_lb, EM_SETLIMITTEXT, 15, TRUE);  
	
	read_user();
	message_to_all();
}

void resized(LPARAM lParam)
{
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d)",width,height);
	load_images();
	
	set_Layout(buy_b,win_glob,cid[BUY].x, cid[BUY].y, cid[BUY].w,cid[BUY].h, width,height,0,0);
	set_Layout(cart_b,win_glob,cid[CART].x, cid[CART].y, cid[CART].w,cid[CART].h, width,height,0,0);
	
	set_Layout(back_b,win_glob,cid[BACK].x, cid[BACK].y, cid[BACK].w,cid[BACK].h, width,height,0,0);
	
	set_Layout(title_lb,win_glob,cid[TITLE].x,cid[TITLE].y,cid[TITLE].w,cid[TITLE].h, width,height,35,TITLE);
	set_Layout(price_lb,win_glob,cid[PRICE].x,cid[PRICE].y,cid[PRICE].w,cid[PRICE].h, width,height,35,PRICE);
	set_Layout(des_Edit,win_glob,cid[DES].x,cid[DES].y,cid[DES].w,cid[DES].h, width,height,35,DES);
	
	set_Layout(display_lb,win_glob,cid[CSDISP].x,cid[CSDISP].y,cid[CSDISP].w,cid[CSDISP].h, width,height,30,CSDISP);
	
	set_Layout(imgh,win_glob,cid[PRODIMG].x,cid[PRODIMG].y,cid[PRODIMG].w,cid[PRODIMG].h, width,height,0,0);
	
	set_Layout(lb_err,win_glob, cid[ERR].x, cid[ERR].y, cid[ERR].w,cid[ERR].h, width,height,30,ERR);
	message_to_all();
}

void action(WPARAM wParam,HWND hwnd)
{
	
	
	switch(LOWORD(wParam)){
		
		case BUY:
		{
			int dn=0;
			PostQuitMessage(cur_pos*100000+(proitm*10+ctgry)*100+54);
			break;
		}
		
		case BACK:
			system("exit");
			PostQuitMessage(cur_pos*100+92);
			break;
		case CART:
		{
			int b,dn;
			dn=addtocart(proitm*10+ctgry,cus_name);
			//ShowWindow (lb_err, SW_SHOW);
			if(dn){
				b=MessageBox(hwnd, "Item Successfully added to cart", "Continue", MB_OK);
			}
			break;
			break;
		}
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
  read_all();
  MSG  msg ;    
  WNDCLASS wc = {0};
  wc.lpszClassName = TEXT( "Customer" );
  wc.hInstance     = hInstance ;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc   = WndProc ;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);

  g_hinst = hInstance;
  printf("*-*-%d-",lpCmdLine);
  printf("-'%s'-",lpCmdLine);
  proitm=(atoi(lpCmdLine)/10)%100;
  ctgry=atoi(lpCmdLine)%10;
  cur_pos=atoi(lpCmdLine)/1000;
  //swprintf(cat_loc,95,L"D:/c_cpp_pro/csPoject/resources/%hs.bmp",cat[ctgry]);
  
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
		case WM_CTLCOLORSTATIC:
		{
		    if( (HWND)lParam == GetDlgItem(hwnd, CSDISP))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(255, 255, 252));
		        SetDCBrushColor((HDC)wParam,0x00f0b000);
		        return (LRESULT)( (HBRUSH)GetStockObject(DC_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		    if( (HWND)lParam == GetDlgItem(hwnd, ERR))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(255, 250, 0));
		        SetDCBrushColor((HDC)wParam,0x00c07000);
		        return (LRESULT)( (HBRUSH)GetStockObject(DC_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		    if( (HWND)lParam == GetDlgItem(hwnd, TITLE))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(0,0,0));
		        SetDCBrushColor((HDC)wParam,0x00c07000);
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		    if( (HWND)lParam == GetDlgItem(hwnd, PRICE))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(255, 0,0));
		        SetDCBrushColor((HDC)wParam,0x00c07000);
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		    if( (HWND)lParam == GetDlgItem(hwnd, DES))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(0,0,0));
		        SetDCBrushColor((HDC)wParam,0x00c07000);
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH));  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
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
