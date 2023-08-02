#include <windows.h>
#include <wchar.h>
#include<Richedit.h>

#include "prelate.h"

#define ICO 46
#define TL 47
#define PL 48
#define SL 49
#define CB 53
#define QN 58
#define ADS 59
#define CLSBK 54
#define SETINFO 10010

int g_scrollY=0;
int itm_num=0;

LRESULT CALLBACK WndPanel( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
  	switch(msg)  
  	{
	  	
		case WM_CREATE:
		{
			
		    RECT rc = { 0 };
		    GetClientRect(hWnd, &rc);
		    SCROLLINFO si = { 0 };
		    si.cbSize = sizeof(SCROLLINFO);
		    si.fMask = SIF_ALL;
		    si.nMin = 0;
		    si.nMax = 250*itm_num+10;
		    si.nPage = (rc.bottom - rc.top);
		    si.nPos = 0;
		    si.nTrackPos = 0;
		    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
    		return 0;
		}
		
	    case WM_COMMAND:
	    {
	
		   break;
	    }
	    case SETINFO:
	    case WM_SIZE:
  			{
  				RECT rc = { 0 };
			    GetClientRect(hWnd, &rc);
			    SCROLLINFO si = { 0 };
			    si.cbSize = sizeof(SCROLLINFO);
			    si.fMask = SIF_ALL;
			    si.nMin = 0;
			    si.nMax = 250*itm_num;
			    si.nPage = (rc.bottom - rc.top);
			    si.nPos = 0;
			    si.nTrackPos = 0;
			    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
  				break;
			}
	    case WM_PAINT:
	    	{
	    		break;
			}
	    case WM_VSCROLL:
		{
			int action = LOWORD(wParam);
		    HWND hScroll = (HWND)lParam;
		    int pos = -1;
		    if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK) {
		        pos = HIWORD(wParam);
		    } else if (action == SB_LINEDOWN) {
		        pos = g_scrollY + 30;
		    } else if (action == SB_LINEUP) {
		        pos = g_scrollY - 30;
		    } 
		    if (pos == -1)
		        break;
		    WCHAR buf[20];
		    SCROLLINFO si = { 0 };
		    si.cbSize = sizeof(SCROLLINFO);
		    si.fMask = SIF_POS;
		    si.nPos = pos;
		    si.nTrackPos = 0;
		    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		    GetScrollInfo(hWnd, SB_VERT, &si);
		    pos = si.nPos;
		    POINT pt;
		    pt.x = 0;
		    pt.y = pos - g_scrollY;
		    HDC hdc = GetDC(hWnd);
		    LPtoDP(hdc, &pt, 1);
		    ReleaseDC(hWnd, hdc);
		    ScrollWindow(hWnd, 0, -pt.y, NULL, NULL);
		    g_scrollY = pos;
		    return 0;
		}
	    case WM_DESTROY:
	    {
	         PostQuitMessage(0);
	         break;
	    }
    }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}
		
	
LRESULT CALLBACK WndCustomList( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
  	switch(msg)  
  	{	
		case WM_PAINT:
		{
			break;
		}
		case WM_CREATE:
		{
			lbp.height=250;
			lbp.width=1530;
			int lb_height=60;
			
			HWND back_grnd=CreateWindowW(L"Static", L"img", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        0, 0,lbp.width ,lbp.height,
		        hwnd, (HMENU) CLSBK, NULL, NULL);        
			lcinsert_value(&lcid[CLSBK],back_grnd,0, 0,lbp.width ,lbp.height,1);
	
		    HWND img_ico=CreateWindowW(L"Static", L"image", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        lbp.height*1.00/100, lbp.height*1.00/100,lbp.height*90.0/100 ,lbp.height*82.0/100,
		        hwnd, (HMENU) ICO, NULL, NULL);        
			lcinsert_value(&lcid[ICO],img_ico,lbp.height*1.00/100, lbp.height*1.00/100,lbp.height*90.0/100 ,lbp.height*82.0/100,1);
		
			
		
			HWND title_lb=CreateWindowW(L"Static",  L"TITLE", 
		        WS_VISIBLE | WS_CHILD ,
			    lbp.height,  lbp.height*2.00/100, 400, lb_height,        
			    hwnd, (HMENU) TL, NULL, NULL);
			lcinsert_value(&lcid[TL],title_lb,lbp.height,lbp.height*2.00/100, 400, lb_height,1);
			
			HWND price_lb=price_lb=CreateWindowW(L"Static",  L"Price", 
		        WS_VISIBLE | WS_CHILD ,
			    lbp.height,lbp.height*2.00/100+60, 400, lb_height,        
			    hwnd, (HMENU) PL, NULL, NULL);	
			lcinsert_value(&lcid[PL],price_lb,lbp.height, lbp.height*2.00/100+60, 400, lb_height,1);
			
			HWND sellid_lb=CreateWindowW(L"Static",  L"Sid", 
		        WS_VISIBLE | WS_CHILD,
			    lbp.height,  lbp.height*2.00/100+120, 400, lb_height,        
			    hwnd, (HMENU) SL, NULL, NULL);	
			lcinsert_value(&lcid[SL],sellid_lb,lbp.height,  lbp.height*2.00/100+120, 400, lb_height,1);
		
			HWND click_b=click_b=CreateWindowW(L"Static", L"CLB", 
		        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
			    0, 0, lbp.width, lbp.height,        
			    hwnd, (HMENU) CB, NULL, NULL);
			lcinsert_value(&lcid[CB],click_b,0, 0, lbp.width, lbp.height,1);
					             
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		    
		    HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/white_back.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
		
			SendMessageW(back_grnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
		
			SendDlgItemMessage(hwnd, 2, WM_SETFONT, (WPARAM)hfFont, TRUE);
			SendDlgItemMessage(hwnd, 3, WM_SETFONT, (WPARAM)hfFont, TRUE);
			
			HBITMAP hli=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/gr.bmp",IMAGE_BITMAP,lbp.height*90.0/100,lbp.height*82.0/100,LR_LOADFROMFILE);
			
			SendMessageW(img_ico, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
		  //	SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam);
			break;
		}
		
		case WM_SIZE:
  		{
  			lbp.width = LOWORD(lParam);
    		lbp.height = HIWORD(lParam);
    		printf("(%d %d)",lbp.width,lbp.height);  
  			set_ListLayout(lcid[ICO].hw,hwnd,lcid[ICO].x, lcid[ICO].y, lcid[ICO].w, lcid[ICO].h, lbp.width,lbp.height-lbp.height*10.00/100,0,0);
			
			set_ListLayout(lcid[TL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[TL].y,lcid[TL].w,lcid[TL].h, lbp.width,lbp.height,43,TL);
			set_ListLayout(lcid[PL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[PL].y,lcid[PL].w,lcid[PL].h,lbp.width,lbp.height,43,PL);
			set_ListLayout(lcid[SL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[SL].y,lcid[SL].w,lcid[SL].h, lbp.width,lbp.height,30,SL);
			set_ListLayout(lcid[CB].hw,hwnd,lcid[CB].x,lcid[CB].y,lcid[CB].w,lcid[CB].h, lbp.width,lbp.height,0,0);
			set_ListLayout(lcid[CLSBK].hw,hwnd,lcid[CLSBK].x,lcid[CLSBK].y,lcid[CLSBK].w,lcid[CLSBK].h, lbp.width,lbp.height,0,0);
			
		
			HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/white_back.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		              
		    SendMessageW(lcid[CLSBK].hw, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
			SendDlgItemMessage(hwnd, 2, WM_SETFONT, (WPARAM)hfFont, TRUE);
			SendDlgItemMessage(hwnd, 3, WM_SETFONT, (WPARAM)hfFont, TRUE);
			
			//SetWindowTextW(display_lb, handle_info);
			break;
		}
			
		case WM_CTLCOLORSTATIC:
		{
		    if( (HWND)lParam == GetDlgItem(hwnd, 47)||(HWND)lParam == GetDlgItem(hwnd, 48)||(HWND)lParam == GetDlgItem(hwnd, 49) )
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(200, 2, 105));
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH) );  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		   break;
		}
		case SETINFO:
		{
			struct items* s; //declare pointer-to-struct variable
  			s = (struct items*) lParam;
  			wchar_t jci[10];
  			wchar_t tl[18];
			wchar_t pr[18];
			wchar_t sd[30];
			wchar_t loc[200];
			printf("info @ %d-",wParam);
			swprintf(jci, 9, L"%d",wParam);
			swprintf(tl, 16, L"%hs",s->title);
			swprintf(pr, 16, L"Rs : %hs",s->price);
			swprintf(sd, 26, L"seller : %hs",s->seller_id);
			
			swprintf(loc, 200, L"%hs",s->location);
			printf("%d %s %s %s %s",wParam,s->title,s->price,s->seller_id,s->location);
			SetWindowTextW(hwnd,jci);
			SetWindowTextW(lcid[TL].hw,tl);
			SetWindowTextW(lcid[PL].hw,pr);
			SetWindowTextW(lcid[SL].hw,sd);
			HBITMAP hli=(HBITMAP)LoadImageW(NULL,loc,IMAGE_BITMAP,lbp.height,lbp.height,LR_LOADFROMFILE);
			SendMessageW(lcid[ICO].hw, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
			break;		
		}
	    case WM_COMMAND:
	    {
		    switch(LOWORD(wParam)){
				case CB:{
					char jcis[10];
					GetWindowText(hwnd,jcis,9);
					int jci=atoi(jcis);
					printf("CB Clicked @ s-%s-",jcis);
					printf("CB Clicked @ %d",jci);
					SendMessageW(GetParent(GetParent(hwnd)),11420,jci,jci);
					break;
				}
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

	
LRESULT CALLBACK WndCustomList2( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
  	switch(msg)  
  	{	
		case WM_PAINT:
		{
			break;
		}
		case WM_CREATE:
		{
			lbp.height=250;
			lbp.width=1530;
			int lb_height=60;
			
			HWND back_grnd=CreateWindowW(L"Static", L"img", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        0, 0,lbp.width ,lbp.height,
		        hwnd, (HMENU) CLSBK, NULL, NULL);        
			lcinsert_value(&lcid[CLSBK],back_grnd,0, 0,lbp.width ,lbp.height,1);
	
		    HWND img_ico=CreateWindowW(L"Static", L"image", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        lbp.height*1.00/100, lbp.height*1.00/100,lbp.height*90.0/100 ,lbp.height*82.0/100,
		        hwnd, (HMENU) ICO, NULL, NULL);        
			lcinsert_value(&lcid[ICO],img_ico,lbp.height*1.00/100, lbp.height*1.00/100,lbp.height*90.0/100 ,lbp.height*82.0/100,1);		
		
			HWND title_lb=CreateWindowW(L"Static",  L"TITLE", 
		        WS_VISIBLE | WS_CHILD ,
			    lbp.height,  lbp.height*2.00/100, 400, lb_height,        
			    hwnd, (HMENU) TL, NULL, NULL);
			lcinsert_value(&lcid[TL],title_lb,lbp.height,lbp.height*2.00/100, 400, lb_height,1);
			
			
			HWND price_lb=price_lb=CreateWindowW(L"Static",  L"Price", 
		        WS_VISIBLE | WS_CHILD ,
			    lbp.height,lbp.height*2.00/100+60, 400, lb_height,        
			    hwnd, (HMENU) PL, NULL, NULL);	
			lcinsert_value(&lcid[PL],price_lb,lbp.height, lbp.height*2.00/100+60, 400, lb_height,1);
			
			HWND quant_lb=price_lb=CreateWindowW(L"Static",  L"Price", 
		        WS_VISIBLE | WS_CHILD ,
			    lbp.height+lbp.height*2.00/100+60,lbp.height*2.00/100+60, 400, lb_height,        
			    hwnd, (HMENU) QN, NULL, NULL);	
			lcinsert_value(&lcid[QN],quant_lb,lbp.height, lbp.height*2.00/100+60, 400, lb_height,1);
			
			HWND sellid_lb=CreateWindowW(L"Static",  L"Sid", 
		        WS_VISIBLE | WS_CHILD,
			    lbp.height,  lbp.height*2.00/100+120, 400, lb_height,        
			    hwnd, (HMENU) SL, NULL, NULL);	
			lcinsert_value(&lcid[SL],sellid_lb,lbp.height,  lbp.height*2.00/100+120, 400, lb_height,1);
			
			HWND custad_lb=CreateWindowW(L"Static",  L"Sid", 
		        WS_VISIBLE | WS_CHILD,
			    lbp.height,  lbp.height*2.00/100+170, 400, lb_height,        
			    hwnd, (HMENU) ADS, NULL, NULL);	
			lcinsert_value(&lcid[ADS],custad_lb,lbp.height,  lbp.height*2.00/100+170, 400, lb_height,1);
		
			HWND click_b=click_b=CreateWindowW(L"Static", L"CLB", 
		        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
			    0, 0, lbp.width, lbp.height,        
			    hwnd, (HMENU) CB, NULL, NULL);
			lcinsert_value(&lcid[CB],click_b,0, 0, lbp.width, lbp.height,1);
					             
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		    
		    HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/white_back.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
		
			SendMessageW(back_grnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
		
			SendDlgItemMessage(hwnd, 2, WM_SETFONT, (WPARAM)hfFont, TRUE);
			SendDlgItemMessage(hwnd, 3, WM_SETFONT, (WPARAM)hfFont, TRUE);
			
			HBITMAP hli=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/gr.bmp",IMAGE_BITMAP,lbp.height*90.0/100,lbp.height*82.0/100,LR_LOADFROMFILE);
			
			SendMessageW(img_ico, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
		  //	SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam);
			break;
		}
		
		case WM_SIZE:
  		{
  			lbp.width = LOWORD(lParam);
    		lbp.height = HIWORD(lParam);
    		printf("(%d %d)",lbp.width,lbp.height);  
  			set_ListLayout(lcid[ICO].hw,hwnd,lcid[ICO].x, lcid[ICO].y, lcid[ICO].w, lcid[ICO].h, lbp.width,lbp.height-lbp.height*10.00/100,0,0);
			
			set_ListLayout(lcid[TL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[TL].y,lcid[TL].w,lcid[TL].h, lbp.width,lbp.height,43,TL);
			set_ListLayout(lcid[PL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[PL].y,lcid[PL].w,lcid[PL].h,lbp.width,lbp.height,43,PL);
			set_ListLayout(lcid[SL].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[SL].y,lcid[SL].w,lcid[SL].h, lbp.width,lbp.height,30,SL);
			set_ListLayout(lcid[CB].hw,hwnd,lcid[CB].x,lcid[CB].y,lcid[CB].w,lcid[CB].h, lbp.width,lbp.height,0,0);
			set_ListLayout(lcid[CLSBK].hw,hwnd,lcid[CLSBK].x,lcid[CLSBK].y,lcid[CLSBK].w,lcid[CLSBK].h, lbp.width,lbp.height,0,0);
			set_ListLayout(lcid[QN].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height)+lcid[QN].x,lcid[QN].y,lcid[QN].w,lcid[QN].h, lbp.width,lbp.height,43,QN);
			set_ListLayout(lcid[ADS].hw,hwnd,80+get_lc_wh(lcid[ICO].hw,lcid[ICO].h,lbp.height),lcid[ADS].y,lcid[ADS].w,lcid[ADS].h, lbp.width,lbp.height,0,0);
			
			HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/white_back.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		              
		    SendMessageW(lcid[CLSBK].hw, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
			SendDlgItemMessage(hwnd, 2, WM_SETFONT, (WPARAM)hfFont, TRUE);
			SendDlgItemMessage(hwnd, 3, WM_SETFONT, (WPARAM)hfFont, TRUE);
			
			//SetWindowTextW(display_lb, handle_info);
			break;
		}
			
		case WM_CTLCOLORSTATIC:
		{
		    if( (HWND)lParam == GetDlgItem(hwnd, 47)||(HWND)lParam == GetDlgItem(hwnd, 48)||
				(HWND)lParam == GetDlgItem(hwnd, 49)|| (HWND)lParam == GetDlgItem(hwnd, QN)|| (HWND)lParam == GetDlgItem(hwnd, ADS))
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(200, 2, 105));
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH) );  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		   break;
		}
		case SETINFO:
		{
			struct items* s; //declare pointer-to-struct variable
  			s = (struct items*) lParam;
  			wchar_t jci[10];
  			wchar_t tl[18];
			wchar_t pr[18];
			wchar_t qty[3];
			wchar_t sd[30];
			wchar_t loc[200];
			wchar_t addss[200];
			for(int i=0;i<strlen(s->addss);i++)
			{
				if(s->addss[i]=='$'){
				 s->addss[i]=' ';
				 i++;
				 s->addss[i]=' ';
				}
			}
			printf("info @ %d-",wParam);
			swprintf(jci, 9, L"%d",wParam);
			swprintf(tl, 16, L"%hs",s->title);
			swprintf(pr, 16, L"Rs : %hs",s->price);
			swprintf(qty, 16, L"Quantity : %hs",s->qty);
			swprintf(sd, 26, L"seller : %hs",s->seller_id);
			
			swprintf(loc, 200, L"%hs",s->location);
			swprintf(addss, 200, L"Delivered to: %hs",s->addss);
			printf("%d %s %s %s %s",wParam,s->title,s->price,s->seller_id,s->location);
			SetWindowTextW(hwnd,jci);
			SetWindowTextW(lcid[TL].hw,tl);
			SetWindowTextW(lcid[PL].hw,pr);
			SetWindowTextW(lcid[SL].hw,sd);
			SetWindowTextW(lcid[QN].hw,qty);
			SetWindowTextW(lcid[ADS].hw,addss);
			HBITMAP hli=(HBITMAP)LoadImageW(NULL,loc,IMAGE_BITMAP,lbp.height,lbp.height,LR_LOADFROMFILE);
			SendMessageW(lcid[ICO].hw, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
			break;		
		}
	    case WM_COMMAND:
	    {
		    switch(LOWORD(wParam)){
				case CB:{
					char jcis[10];
					GetWindowText(hwnd,jcis,9);
					int jci=atoi(jcis);
					printf("CB Clicked @ s-%s-",jcis);
					printf("CB Clicked @ %d",jci);
					SendMessageW(GetParent(GetParent(hwnd)),11420,jci,jci);
					break;
				}
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



LRESULT CALLBACK WndCustomBox( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	switch(msg)  
  	{	
		case WM_PAINT:
		{
			break;
		}
		case WM_CREATE:
		{
			lbp.height=1600;
			lbp.width=1600;
			int lb_height=60;
			
			HWND back_grnd=CreateWindowW(L"Static", L"img", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        0, 0,lbp.width ,lbp.height,
		        hwnd, (HMENU) CLSBK, NULL, NULL);        
			lcinsert_value(&lcid[CLSBK],back_grnd,0, 0,lbp.width ,lbp.height,1);
			
			HWND stor=CreateWindowW(L"Static", L"", 
		        WS_VISIBLE | WS_CHILD,
		        0, 0,0,0,
		        hwnd, (HMENU) 5, NULL, NULL);        
			lcinsert_value(&lcid[5],stor,0, 0,0 ,0,1);
	
		    HWND img_ico=CreateWindowW(L"Static", L"image", 
		        WS_VISIBLE | WS_CHILD|SS_BITMAP,
		        16, 16,194 ,140,
		        hwnd, (HMENU) ICO, NULL, NULL);        
			lcinsert_value(&lcid[ICO],img_ico,16, 16,194,140,1);
			
			
			HWND price_lb=price_lb=CreateWindowW(L"Static",  L"Price", 
		        WS_VISIBLE | WS_CHILD|SS_CENTER,
			    20,180, 170, 30,        
			    hwnd, (HMENU) PL, NULL, NULL);	
			lcinsert_value(&lcid[PL],price_lb,20,180, 170, 30,1);
			
			printf("%d %d",lbp.width,lbp.height);
			
			HWND click_b=CreateWindowW(L"Static", L"CLB", 
		        WS_VISIBLE | WS_CHILD|SS_NOTIFY|SS_BITMAP,
			    0, 0, lbp.width, lbp.height,        
			    hwnd, (HMENU) CB, NULL, NULL);
			lcinsert_value(&lcid[CB],click_b,0, 0, lbp.width, lbp.height,1);
					             
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		              CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		    
		    HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/box.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
		//	HBITMAP hli=(HBITMAP)LoadImageW(NULL,loc,IMAGE_BITMAP,lcid[ICO].w,lcid[ICO].h,LR_LOADFROMFILE);
			
			SendMessageW(back_grnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
		//	SendMessageW(img_ico, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
			SendDlgItemMessage(hwnd, PL, WM_SETFONT, (WPARAM)hfFont, TRUE);			
		//	
		  //	SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam);
		 break;
		}
		
		case WM_SIZE:
  		{
  			lbp.width = LOWORD(lParam);
    		lbp.height = HIWORD(lParam);
    		printf("(%d %d)",lbp.width,lbp.height);  
  			set_BoxLayout(GetDlgItem(hwnd, ICO),hwnd,lcid[ICO].x, lcid[ICO].y, lcid[ICO].w, lcid[ICO].h, lbp.width,lbp.height,0,0);
			set_BoxLayout(GetDlgItem(hwnd, PL),hwnd,lcid[PL].x,lcid[PL].y,lcid[PL].w,lcid[PL].h,lbp.width,lbp.height,20,PL);
			set_ListLayout(GetDlgItem(hwnd, CB),hwnd,lcid[CB].x,lcid[CB].y,230,230, lbp.width,lbp.height,80,CB);
			set_ListLayout(GetDlgItem(hwnd, CLSBK),hwnd,lcid[CLSBK].x,lcid[CLSBK].y,lcid[CLSBK].w,lcid[CLSBK].h, lbp.width,lbp.height,0,0);
			
		
			HBITMAP bkg=(HBITMAP)LoadImageW(NULL,L"D:/c_cpp_pro/csPoject/resources/box.bmp",IMAGE_BITMAP,lbp.width,lbp.height,LR_LOADFROMFILE);
			HFONT hfFont = CreateFont(43,15,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		    wchar_t loc[200];
		    GetWindowTextW(GetDlgItem(hwnd, 5),loc,198);
			if(!(wcslen(loc)>2))
		    {
		    	//set_ListLayout(GetDlgItem(hwnd, CB),hwnd,lcid[CB].x,lcid[CB].y,0,0, lbp.width,lbp.height,80,CB);
		    	SetWindowTextW(GetDlgItem(hwnd, PL),L"Not Available");
			}		    
		    HBITMAP hli=(HBITMAP)LoadImageW(NULL,loc,IMAGE_BITMAP,round(lcid[ICO].w*lbp.width/230),lcid[ICO].h*lbp.height/230,LR_LOADFROMFILE);			 
		    SendMessageW(GetDlgItem(hwnd, CLSBK),STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bkg);
		    SendMessageW(GetDlgItem(hwnd,ICO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
			sethf(hwnd,lcid[PL].w,lcid[PL].h,lbp.width,lbp.height,20,PL);
			UpdateWindow(GetDlgItem(hwnd, PL));
			break;
		}
			
		case WM_CTLCOLORSTATIC:
		{
		    if( (HWND)lParam == GetDlgItem(hwnd, 47)||(HWND)lParam == GetDlgItem(hwnd, 48)||(HWND)lParam == GetDlgItem(hwnd, 49) )
		    {
		        SetBkMode( (HDC)wParam, TRANSPARENT );  
		        SetTextColor((HDC)wParam, RGB(200, 2, 105));
		        return (LRESULT)( (HBRUSH)GetStockObject(WHITE_BRUSH) );  
		        // if edit control is in dialog procedure change LRESULT to INT_PTR
		    }
		   break;
		}
		case SETINFO:
		{
			struct items* s; //declare pointer-to-struct variable
  			s = (struct items*) lParam;
  			wchar_t jci[10];
			wchar_t pr[18];
			wchar_t loc[200];
			printf("info @ %d-",wParam);
			swprintf(jci, 9, L"%d",wParam);
			swprintf(pr, 16, L"Rs : %hs",s->price);
			swprintf(loc, 200, L"%hs",s->location);
			printf("%d %s %s %s %s",wParam,s->title,s->price,s->seller_id,s->location);
			SetWindowTextW(hwnd,jci);
			SetWindowTextW(GetDlgItem(hwnd, 5),loc);
			SetWindowTextW(GetDlgItem(hwnd, PL),pr);
			if(!(wcslen(loc)>2))
		    {
		    	//set_ListLayout(GetDlgItem(hwnd, CB),hwnd,lcid[CB].x,lcid[CB].y,0,0, lbp.width,lbp.height,80,CB);
		    	SetWindowTextW(GetDlgItem(hwnd, PL),L"Not Available");
			}
			HBITMAP hli=(HBITMAP)LoadImageW(NULL,loc,IMAGE_BITMAP,lbp.height,lbp.height,LR_LOADFROMFILE);
			SendMessageW(GetDlgItem(hwnd, ICO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hli);
			break;		
		}
	    case WM_COMMAND:
	    {
		    switch(LOWORD(wParam)){
				case CB:{
					wchar_t loc[200];
					char jcis[10];
				    GetWindowTextW(GetDlgItem(hwnd, 5),loc,198);
					if(!(wcslen(loc)>2))
				    {
				    	SetWindowTextW(GetDlgItem(hwnd, PL),L"Not Available");
					}	else{
						GetWindowText(hwnd,jcis,9);
						int jci=atoi(jcis);
						printf("CB Clicked @ s-%s-",jcis);
						SendMessageW(GetParent(hwnd),11420,jci,jci);
				    }
					break;
				}
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
