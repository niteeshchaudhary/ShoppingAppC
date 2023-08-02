#include <windows.h>
#include <math.h>
void set_Layout(HWND hwnd,HWND winhwnd,int x,int y,int wd,int ht,int win_wd,int win_ht,int ftsize,int i_d)
{
	float fa=((wd*ht*1.0)/(1536*801))*win_wd*win_ht;
	MoveWindow (hwnd, ((x*1.0)/1536)*win_wd,  ((y*1.0)/801)*win_ht,round(wd*win_wd/1536), ht*win_ht/801,TRUE);
	 if(ftsize>0){
	 	ftsize=(int)(ftsize*sqrt(fa*ht/wd)/ht);
	 	int ftl=(int)((ftsize*12/30)*sqrt(fa*wd/ht)/wd);
	 	if(ftl<8)
	 	{
	 		ftl=8;
		}

	 	if(ftsize<5)
	 	{
	 		ftsize=5;
		}
	 	HFONT hfFont;
	 	if(i_d!=20){
		hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
         }
         else{
         	hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Arial Black"));
		 }
	 	SendDlgItemMessage(winhwnd, i_d, WM_SETFONT, (WPARAM)hfFont, TRUE);
	 	UpdateWindow(hwnd);
	 }	
}


void set_ListLayout(HWND hwnd,HWND winhwnd,int x,int y,int wd,int ht,int win_wd,int win_ht,int ftsize,int i_d)
{
	float fa=((wd*ht*1.0)/(1536*250))*win_wd*win_ht;
	MoveWindow (hwnd, x,  ((y*1.0)/230)*win_ht,ht*win_wd/230, ht*win_ht/230,TRUE);
	 if(ftsize>0){
	 	ftsize=(int)(ftsize*sqrt(fa*ht/wd)/ht);
	 	int ftl=(int)((ftsize*16/30)*sqrt(fa*wd/ht)/wd);
	 	HFONT hfFont;
	 	if(i_d!=20){
		hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
         }
         else{
         	hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		 }
	 	SendDlgItemMessage(winhwnd, i_d, WM_SETFONT, (WPARAM)hfFont, TRUE);
	 	UpdateWindow(hwnd);
	 }	
}

void set_BoxLayout(HWND hwnd,HWND winhwnd,int x,int y,int wd,int ht,int win_wd,int win_ht,int ftsize,int i_d)
{
	float fa=((wd*ht*1.0)/(230*230))*win_wd*win_ht;
	MoveWindow (hwnd, ((x*1.0)/230)*win_wd,  ((y*1.0)/230)*win_ht,round(wd*win_wd/230), ht*win_ht/230,TRUE);
	 if(ftsize>0){
	 	ftsize=(int)(ftsize*sqrt(fa*ht/wd)/ht);
	 	int ftl=(int)((ftsize*16/30)*sqrt(fa*wd/ht)/wd);
	 	HFONT hfFont;
	 	if(ftl<8)
	 	{
	 		ftl=8;
		}
		else if(ftl>25)
	 	{
	 		ftl=25;
		}
	 	if(ftsize<5)
	 	{
	 		ftsize=5;
		}
		else if(ftsize>43)
	 	{
	 		ftsize=43;
		}
	 	if(i_d!=20){
		hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
         }
         else{
         	hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		 }
	 	SendDlgItemMessage(winhwnd, i_d, WM_SETFONT, (WPARAM)hfFont, TRUE);
	 	UpdateWindow(hwnd);
	 }	
}

void set_Layout_Arialratio(HWND hwnd,HWND winhwnd,int x,int y,int wd,int ht,int win_wd,int win_ht,int ftsize,int i_d)
{
	float fa=((wd*ht*1.0)/(1536*801))*win_wd*win_ht;
	MoveWindow (hwnd, ((x*1.0)/1536)*win_wd,  ((y*1.0)/801)*win_ht, sqrt(fa*wd/ht), sqrt(fa*ht/wd),TRUE);
	 if(ftsize>0){
	 	ftsize=(int)(ftsize*sqrt(fa*ht/wd)/ht);
	 	int ftl=(int)((ftsize*25/45)*sqrt(fa*wd/ht)/wd);
	 	HFONT hfFont;
	 	if(i_d!=20){
		hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
         }
         else{
         	hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Arial Black"));
		 }
	 	SendDlgItemMessage(winhwnd, i_d, WM_SETFONT, (WPARAM)hfFont, TRUE);
	 	UpdateWindow(hwnd);
	 }	
}

void sethf(HWND winhwnd,int wd,int ht,int win_wd,int win_ht,int ftsize,int i_d)
{
	float fa=((wd*ht*1.0)/(230*230))*win_wd*win_ht;
	 	ftsize=(int)(ftsize*sqrt(fa*ht/wd)/ht);
	 	int ftl=(int)((ftsize*16/30)*sqrt(fa*wd/ht)/wd);
	 	HFONT hfFont;
	 	if(ftl<8)
	 	{
	 		ftl=8;
		}
		else if(ftl>25)
	 	{
	 		ftl=25;
		}
	 	if(ftsize<5)
	 	{
	 		ftsize=5;
		}
		else if(ftsize>43)
	 	{
	 		ftsize=43;
		}
	 	if(i_d!=20){
		hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
         }
         else{
         	hfFont = CreateFont(ftsize,ftl,0,0,10,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
             CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Algerian"));
		 }
		SendDlgItemMessage(winhwnd, i_d, WM_SETFONT, (WPARAM)hfFont, TRUE);
}

float get_c_x(HWND hwnd,int x,int win_wd)
{
	return ((x*1.0)/1536)*win_wd;
}
float get_c_y(HWND hwnd,int y,int win_ht)
{
	return ((y*1.0)/801)*win_ht;
}
float get_c_w(HWND hwnd,int wd,int win_wd)
{
	return round(wd*win_wd/1536);
}
float get_c_h(HWND hwnd,int ht,int win_ht)
{
	return ht*win_ht/801;
}
float get_lc_wh(HWND hwnd,int ht,int win_ht)
{
	return ht*win_ht/211;
}
