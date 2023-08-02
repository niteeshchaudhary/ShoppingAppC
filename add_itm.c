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

#define DRAWER 1
#define SUBMIT 2
#define ADD 72
#define BACK 3
#define TITLE 22
#define PRICE 23
#define DES 24
#define ERR 29
#define BK 32
#define PRODIMG 75
#define SLDISP 45

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void message_to_all();
void load_images();

HWND hl,lb_err,title_Edit,submit_b,drawer_b,back_b,add_b,display_lb,prod_img_handler;

HWND price_Edit,des_Edit,win_glob;

int height=840,width=1552;

int ft_size=35;


char *dim[5];
char seller_id[15];
wchar_t handle_info[30];
wchar_t img_loc[100];
wchar_t cat_loc[100];

int lno=0,cpos=0,ppos=0;


HFONT hfFont;

COLORREF g_rgbText = RGB(0, 0, 0);

int lgap=4,lshift=30,ushift=20,num=1;
int cur_pos,ctgry;

static HWND hwndCombo, hwndStatic; 

HDC hDc; 

HINSTANCE g_hinst;

HBITMAP hli,bimg,p_img;

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

int check(wchar_t  name[])
{    
	char nm[15];
	sprintf(nm, "%ls",name);
	for(int i=0;i<seller_info.no_of_sellers;i++){
		if(!strcmp(nm,seller_info.sellers[i].user_name)){
			printf("This user already exists\n");
			return 1;
		} 
	}
	return 0;
}

void save(wchar_t ID[],wchar_t pass[])
{
	FILE *sv;
	sv=fopen("./text_files/sellr.txt","a");
	fprintf(sv,"A|%ls|%ls| | ; \n",ID,pass);
	fclose(sv);
}

void LoadFile(char* file) {
	swprintf(img_loc,100,L"%hs",file);
	printf(" $${");
	//wcsncpy(img_loc,file,wcslen(file));
	fputws ( img_loc, stdout );
		if(wcslen(img_loc)>0)
	{
		p_img=(HBITMAP)LoadImageW(NULL,img_loc,IMAGE_BITMAP,cid[PRODIMG].w,cid[PRODIMG].h,LR_LOADFROMFILE);
	//	HBITMAP garbage=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/yl_back.bmp",IMAGE_BITMAP, cid[PRODIMG].w,cid[PRODIMG].h,LR_LOADFROMFILE);
	}
	
	printf("}$$");
  	//load_images();
  	message_to_all();
  
}

void OpenDialog(HWND hwnd) {

  OPENFILENAME ofn;
  TCHAR szFile[MAX_PATH];

  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.lpstrFile = szFile;
  ofn.lpstrFile[0] = '\0';
  ofn.hwndOwner = hwnd;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0BMP FILES\0*.bmp\0");
  ofn.nFilterIndex = 1;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrFileTitle = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if(GetOpenFileName(&ofn))
      LoadFile(ofn.lpstrFile);
}

void message_to_all()
{

	SendMessageW(hl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
	SendMessageW(submit_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
	SendMessageW(add_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	SendMessageW(back_b, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bimg);
 	if(wcslen(img_loc)>0)
	{
		SendMessageW(prod_img_handler, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) p_img);
	}
	SetWindowTextW(display_lb, handle_info);
	SetWindowTextW(title_Edit,get_text(title_Edit) );
	SetWindowTextW(price_Edit,get_text(price_Edit) );
	SetWindowTextW(des_Edit,get_text(des_Edit) );
	UpdateWindow(title_Edit);
	UpdateWindow(price_Edit);
	UpdateWindow(des_Edit);
	UpdateWindow(lb_err);
	
}
void load_images()
{
	hli=(HBITMAP)LoadImageW(NULL,cat_loc,IMAGE_BITMAP,width,height,LR_LOADFROMFILE);
	bimg=(HBITMAP)LoadImageW(NULL,L"D:/csPoject/resources/gr.bmp",IMAGE_BITMAP,120,110,LR_LOADFROMFILE);
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
	insert_value(&cid[TITLE],485, 230, 247, 45,1);
	insert_value(&cid[PRICE],485, 308, 247, 45,1);
	insert_value(&cid[DES],150, 422, 581, 200,1);
	insert_value(&cid[SUBMIT],631, 660, 170, 80,1);
	insert_value(&cid[BACK],1380, 33, 50, 50,1);
	insert_value(&cid[ADD],890, 650, 120, 100,1);
	insert_value(&cid[SLDISP],20, 30, 320, 40,1);
	insert_value(&cid[ERR],50,100,700,30,1);
	insert_value(&cid[PRODIMG],1010, 290, 330, 320,1);
/*	insert_value(&cid[FASHION],659, 315, 150, 140,1);
	insert_value(&cid[FURNITURE],856, 315, 150, 140,1);
	insert_value(&cid[APPLIANCES],1056, 315, 150, 140,1);
	insert_value(&cid[ELECTRONICS],1255, 315, 150, 140,1);
	insert_value(&cid[ADDED],530, 545, 510, 140,1);
	insert_value(&cid[LOGOUT],1186, 545, 220, 140,1);
	insert_value(&cid[SLDISP],20, 30, 320, 40,1);*/
}


void create_controls(HWND hwnd)
{
	load_images();
	fill_dimention();	
	
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
        cid[BK].x, cid[BK].y, cid[BK].w,cid[BK].h ,
        hwnd,(HMENU) BK, NULL, NULL);
    
    prod_img_handler=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        cid[PRODIMG].x, cid[PRODIMG].y, cid[PRODIMG].w,cid[PRODIMG].h,
        hwnd,(HMENU) PRODIMG, NULL, NULL);
	
	lb_err=CreateWindowW(L"Static",L"", 
        WS_CHILD | WS_VISIBLE|SS_CENTER,
        cid[ERR].x, cid[ERR].y, cid[ERR].w,cid[ERR].h,
        hwnd, (HMENU) ERR, NULL, NULL);
        ShowWindow (lb_err, SW_HIDE);
    
	back_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
        cid[BACK].x, cid[BACK].y, cid[BACK].w,cid[BACK].h,   
	    hwnd, (HMENU) BACK, NULL, NULL);

	submit_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    cid[SUBMIT].x, cid[SUBMIT].y, cid[SUBMIT].w,cid[SUBMIT].h,        
	    hwnd, (HMENU) SUBMIT, NULL, NULL);
	
	add_b=CreateWindowW(L"Static", NULL, 
        WS_VISIBLE | WS_CHILD|SS_BITMAP|SS_NOTIFY,
	    cid[ADD].x, cid[ADD].y, cid[ADD].w,cid[ADD].h,        
	    hwnd, (HMENU) ADD, NULL, NULL);
	    
	title_Edit= CreateWindowW(L"Edit", NULL, 
        WS_CHILD | WS_VISIBLE,
        cid[TITLE].x, cid[TITLE].y, cid[TITLE].w,cid[TITLE].h , 
		hwnd, (HMENU) TITLE,NULL, NULL);
      
	/*itm_Edit=CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE |WS_BORDER,
	630, 280, 300, 50, hwnd, (HMENU) NAME, NULL, NULL);*/
	
	price_Edit=CreateWindowW(WC_EDITW, NULL,
		WS_CHILD | WS_VISIBLE ,
		cid[PRICE].x, cid[PRICE].y, cid[PRICE].w,cid[PRICE].h , 
		hwnd, (HMENU) PRICE, NULL, NULL);

	des_Edit=CreateWindowW(WC_EDITW, NULL,
	 	WS_CHILD | WS_VISIBLE|ES_MULTILINE|WS_VSCROLL,
		cid[DES].x, cid[DES].y, cid[DES].w,cid[DES].h , 
		hwnd, (HMENU) DES, NULL, NULL);
	
	display_lb=CreateWindowW(L"Static",L"Seller id : ",
		WS_CHILD | WS_VISIBLE,
		cid[SLDISP].x, cid[SLDISP].y, cid[SLDISP].w, cid[SLDISP].h, 
		hwnd, (HMENU) SLDISP, NULL, NULL);
		
	hfFont = CreateFont(ft_size,18,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
              
	SendDlgItemMessage(hwnd, DES, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, TITLE, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendDlgItemMessage(hwnd, PRICE, WM_SETFONT, (WPARAM)hfFont, TRUE);
	SendMessage(price_Edit, EM_SETLIMITTEXT, 15, TRUE);  
	SendMessage(des_Edit, EM_SETLIMITTEXT, 170, TRUE);  
	SendMessage(title_Edit, EM_SETLIMITTEXT, 15, TRUE);  
	
	read_user();
	message_to_all();
}

void resized(LPARAM lParam)
{
	width = LOWORD(lParam);
    height = HIWORD(lParam);
    printf("(%d %d)",width,height);
	load_images();
	set_Layout(submit_b,win_glob,cid[SUBMIT].x, cid[SUBMIT].y, cid[SUBMIT].w,cid[SUBMIT].h, width,height,0,0);
	set_Layout(back_b,win_glob,cid[BACK].x, cid[BACK].y, cid[BACK].w,cid[BACK].h, width,height,0,0);
	set_Layout(add_b,win_glob,cid[ADD].x, cid[ADD].y, cid[ADD].w,cid[ADD].h, width,height,0,0);
	
	set_Layout(title_Edit,win_glob,cid[TITLE].x,cid[TITLE].y,cid[TITLE].w,cid[TITLE].h, width,height,35,TITLE);
	set_Layout(price_Edit,win_glob,cid[PRICE].x,cid[PRICE].y,cid[PRICE].w,cid[PRICE].h, width,height,35,PRICE);
	set_Layout(des_Edit,win_glob,cid[DES].x,cid[DES].y,cid[DES].w,cid[DES].h, width,height,35,DES);
	
	set_Layout(display_lb,win_glob,cid[SLDISP].x,cid[SLDISP].y,cid[SLDISP].w,cid[SLDISP].h, width,height,30,SLDISP);
	
	set_Layout( prod_img_handler,win_glob,cid[PRODIMG].x,cid[PRODIMG].y,cid[PRODIMG].w,cid[PRODIMG].h, width,height,0,0);
	
	set_Layout(lb_err,win_glob, cid[ERR].x, cid[ERR].y, cid[ERR].w,cid[ERR].h, width,height,30,ERR);
	
	message_to_all();
}

void action(WPARAM wParam,HWND hwnd)
{
	int b,dn;
	
	switch(LOWORD(wParam)){
		
		case SUBMIT:
			dn=add_items(title_Edit,price_Edit,des_Edit,lb_err,img_loc,seller_id,ctgry);
			ShowWindow (lb_err, SW_SHOW);
			if(dn){
				b=MessageBox(hwnd, "Item Successfully added", "Continue", MB_OK);
				if(b==1){
					PostQuitMessage(cur_pos*100+91);
				}
				else{
					PostQuitMessage(cur_pos*100+91);
				}
			}
			break;
			
		case BACK:
			system("exit");
			PostQuitMessage(cur_pos*100+91);
			break;
			
		case ADD:
			
			printf("nk");
			OpenDialog(hwnd);
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
  printf("-%s-",lpCmdLine);
  cur_pos=atoi(lpCmdLine)/10;
  ctgry=atoi(lpCmdLine)%10;
  swprintf(cat_loc,95,L"D:/csPoject/resources/%hs.bmp",cat[ctgry]);
  
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
		    if( (HWND)lParam == GetDlgItem(hwnd, SLDISP) )
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(250, 250, 250));
		        SetDCBrushColor((HDC)wParam,0x00f0b000);
		        return (LRESULT)( (HBRUSH)GetStockObject(DC_BRUSH) );  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		    else if( (HWND)lParam == GetDlgItem(hwnd, ERR) )
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(255, 250, 0));
		        SetDCBrushColor((HDC)wParam,0x00c07000);
		        return (LRESULT)( (HBRUSH)GetStockObject(DC_BRUSH) );  
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
