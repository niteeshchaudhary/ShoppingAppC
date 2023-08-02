char cat[7][15]={"cosmestics","grocery","mobiles","fashion","furniture","appliances","electronics"};

struct user{
	char user_name[15];
    char user_pass[15];
};

struct seller{
	int cur;
    int no_of_sellers;
	struct user sellers[100];
}seller_info;

struct customer{
	int cur;
    int no_of_cust;
	struct user customers[100];
}customer_info;

struct items{
	char title[15];
	char des[200];
	char price[10];
	char location[200];
	char seller_id[15];
	char qty[4];
	char addss[200];
	//int category_number;
};

struct category{
	int itm_no;
	struct items itm[100];
}categ[7];

struct winlb_dim{
	float width;
	float height;
}lbp;
struct lccinfo{
	HWND hw;
	float x;
	float y;
	float w;
	float h;
	int is_visible;
}lcid[100];

void lcinsert_value(struct lccinfo *comp,HWND hw, float x , float y, float width , float height ,int visibility) {
	comp->hw = hw;
    comp->x = x;
    comp->y = y;
    comp->w = width;
    comp->h = height;
    comp->is_visible = visibility;
}

int add_toCart()
{
	//FILE * addtc;
	char line[100];
	char path[50];
	//sprintf(path,"D:/c_cpp_pro/csPoject/text_files/%s.txt",cat[cati]);
	//addtc=fopen(path,"a");
	//fprintf(addtc,"S|%ls|%ls|%ls|%ls|%s| ; \n",title,desc,price,img_loc,seller_id);
	//fclose(addtc);
}
int add_items(HWND title_Edit,HWND price_Edit,HWND des_Edit,HWND lb_err,wchar_t img_loc[],char seller_id[],int cati)
{
	wchar_t title[15];
	wchar_t desc[203];
	wchar_t price[15];
	GetWindowTextW(title_Edit, title, 13);
	GetWindowTextW(price_Edit, price, 13);
	GetWindowTextW(des_Edit, desc, 200);
	if (lstrlenW(title) != 0 && lstrlenW(price) != 0 && lstrlenW(desc) != 0 && lstrlenW(img_loc) != 0){
		for(int i=0;i<=200 && desc[i]!='\0';i++)
		{
			if(desc[i]=='\r')
			{
				desc[i]='$';
			}
			if(desc[i]=='\n')
			{
				desc[i]='$';
			}
		}
		printf("Product Name\n");
		printf("Product description: ");
		printf("Product Price: ");
		FILE * iadd;
		char line[100];
		char path[50];
		sprintf(path,"D:/csPoject/text_files/%s.txt",cat[cati]);
		iadd=fopen(path,"a");
		fprintf(iadd,"S|%ls|%ls|%ls|%ls|%s| ; \n",title,desc,price,img_loc,seller_id);
		fclose(iadd);	
	}
	else{
		SetWindowTextW(lb_err, L"*Please fill all details and choose product picture");
		return 0;
	}
	return 1;
}

int match(char to_match[],char wmatch[],int precis,int rprecis)
{
	int p=0,q=1,len=strlen(to_match),len2=strlen(wmatch);
	int count1[130],count2[130];
	
	for(int i=0;i<130;i++)
	{
		count1[i]=0;
		count2[i]=0;
	}
	
	for(int i=0;to_match[i]!='\0';i++)
	{
		if(wmatch[i]==to_match[i] && i==0)
			q+=2;
		else if(i==0)
			q-=2;
			
		if(wmatch[i]==to_match[i])
			q++;
		count1[(int)to_match[i]]++;
	}
	for(int i=0;wmatch[i]!='\0';i++)
	{
		count2[(int)wmatch[i]]++;
	}
	for(int i=20;i<130;i++)
	{
		if(count1[i]*count2[i])
		{
			p = count1[i]==count2[i] ? p+1 : p+0.5;
		}
	}
	p = (q != 1) ? p * q : p*0.5;
	if(count1[32])
		len=len/1.4;
	if(count2[32])
		len2=len2/1.4;
	if((p*100)/len>=precis && (p*100)/len2>=rprecis)//for precise increse 30 to 50 for p or both 40
		return 1;
	else
		return 0;
}



void show_product(int ci,int itm_ch)
{
	int quantity;
	char w_buy;
	char d_address[100];
	system("cls");
//	printf("\t\t%s\n---------\ndescription|  %s\n\nPrice=%s/-\tSeller Id=%s\n",categ[ci].itm[itm_ch].title,
//		categ[ci].itm[itm_ch].des,categ[ci].itm[itm_ch].price,categ[ci].itm[itm_ch].seller_id);
	printf("do u want to buy [Y/N]: OR add to cart[y/n]: ");
	fgetc(stdin);//dummy|used to overcome input skip problem 
	scanf("%c",&w_buy);
	
	if(w_buy=='Y'){
		printf("Enter quanitiy\n");
		scanf("%d",&quantity);
		printf("Enter deliver address with pin code\n");
		fgetc(stdin);//dummy|used to overcome input skip problem 
		fgets(d_address,99,stdin);
		d_address[strlen(d_address)-1]='\0';
	//	printf("\nOrder Confirmed, your bill = %d\nur oder will be delivered at %s\nthank u for ur puchase!!"
	//			,atoi(categ[ci].itm[itm_ch].price)*quantity,d_address);
	}	
}


void find_product()
{	
	system("cls");
	char title[15];
	printf("\nEnter ur product :");
	int found=0;
	fgetc(stdin);//dummy|used to overcome input skip problem 
	fgets(title,14,stdin);
	title[strlen(title)-1]='\0';
/*	for(int ci=0;ci<7;ci++)
	{
		for(int j=0;j<categ[ci].itm_no;j++){
			if(match(title,categ[ci].itm[j].title,50,50)){
				printf("{ %s num=%d }\n",categ[ci].itm[j].title,j*10+ci);//,strcmp(match(title,"nkc")," "));
				found++;
			}
		}
	}*/
	int chs,ci,j;
	if(found>0){
		printf("choose the one by entering num infront of ur choice : ");
		scanf("%d",&chs);
		ci=chs%10;
		j=chs/10;
		show_product(ci,j);
	}
	else{
		char desn;
		printf("no match found with this name !! \n ");
		printf("do u want to search other product or other name [y/n]: ");
				/*fgetc(stdin);*///dummy|used to overcome input skip problem 
		scanf("%c",&desn);
		if(desn=='y')
		{
			find_product();
		}
	}
}

void read_all()
{
	FILE* rd;
	char line[300];
	char path[50];
	int ln=0,ccpos=0,cppos=0;
	char *div[7];
	
	for(int ci=0;ci<7;ci++)
	{
		sprintf(path,"./text_files/%s.txt",cat[ci]);
		rd=fopen(path,"r");
		int l_no=0;
		while(fgets(line,299,rd)!=NULL)
		{
			cppos=ccpos;
			ccpos=ftell(rd);
			if(strlen(line)>0){
				int i=0;
				div[i] = strtok(line,"|");
				while(div[i]!=NULL)
				{
		   			div[++i] = strtok(NULL,"|");
				}
				strcpy(categ[ci].itm[l_no].title,div[1]);
				strcpy(categ[ci].itm[l_no].des,div[2]);
				strcpy(categ[ci].itm[l_no].price,div[3]);
				strcpy(categ[ci].itm[l_no].location,div[4]);
				strcpy(categ[ci].itm[l_no].seller_id,div[5]);
				l_no++;
			}
			else{
				continue;
			}
			categ[ci].itm_no=l_no;
		}
		fclose(rd);
	}
}

int addtocart(int ctritem,char us_id[])
{
	FILE * iaddc;
	char path[50];
	sprintf(path,"./text_files/%s_cart.txt",us_id);
	iaddc=fopen(path,"a");
	fprintf(iaddc,"%d \n",ctritem);
	fclose(iaddc);	
	return 1;
}


int addto_order(int ctritem,int qty,char address[],char us_id[])
{
	FILE * iaddo;
	char path[50];
	sprintf(path,"./text_files/%s_orders.txt",us_id);
	iaddo=fopen(path,"a");
	fprintf(iaddo,"O|%d|%d|%s| ; \n",ctritem,qty,address);
	fclose(iaddo);
	return 1;	
}

void tempfile(char str[])
{
	FILE *tp;
	tp=fopen("./text_files/temp.txt","w");
	fprintf(tp,"%s",str);
	fclose(tp);
}

void rdtempfile(char backstr[])
{
	FILE *tp;
	char str[14];
	tp=fopen("./text_files/temp.txt","r");
	if(fgets(str,13,tp)!=NULL)
	{
		if(strlen(str)>0){
			strcpy(backstr,str);
		}
	}
	fclose(tp);
}

int deltempfile()
{
   int r=-8,k=0;
   do{
	   r=remove("./text_files/temp.txt");
	   if(r==0){
	       printf("\ntemp removed");      
	       return 0;
	   }
	}
   while(k<3);
   
   printf("\nError deleting temp\n");
   
   return -1;
}


wchar_t* get_text(HWND hwnd)
{
	int lenT = GetWindowTextLengthW(hwnd) + 1;	
	wchar_t *h_text=(wchar_t *)malloc(sizeof(wchar_t)*lenT);
	GetWindowTextW(hwnd,h_text, lenT);
	return h_text;
}

