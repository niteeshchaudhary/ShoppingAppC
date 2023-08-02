#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define SELLCONST 1
#define CUSTCONST 2

char *dim[6];//index 1 id/name , 2 pass
int lno=0,cpos=0,ppos=0;
char us_id[15];
char cat[7][15]={"cosmestics","grocery","mobiles","fashion","furniture","appliances","electronics"};
void find_product();
struct items{
	char title[15];
	char des[200];
	char price[10];
	char location[100];
	char seller_id[15];
	//int category_number;
};
struct category{
	int itm_no;
	struct items itm[100];
}categ[7];

struct orderdata{
	struct items in_cart[100];
    struct items bought[100];
};

struct user{
	char user_name[15];
    char user_pass[15];
    struct orderdata orders;
};

struct seller{
      int no_of_sellers;
	  struct user sellers[100];
}seller_info;

struct customer{
    int no_of_cust;
	struct user customers[100];
}customer_info;

void read_user(int who){
	FILE* rd;
	char line[200];
		
	int ln=0,ccpos=0,cppos=0;
	char *division[5];
	if(who==1){
		rd=fopen("./text_files/sellr.txt","r"); 
	}
	else{	
		rd=fopen("./text_files/cus.txt","r"); 
	}		
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
			if(who==1){
				strcpy(seller_info.sellers[l_no].user_name,division[1]);
				strcpy(seller_info.sellers[l_no].user_pass,division[2]);
				l_no++;  
			} 
			else if(who==2){
				strcpy(customer_info.customers[l_no].user_name,division[1]);
				strcpy(customer_info.customers[l_no].user_pass,division[2]);
				l_no++;
			}
		}
		else{
			continue;
		}	
	}
	if(who==1){
		seller_info.no_of_sellers=l_no; 
	} 
	else if(who==2){
		customer_info.no_of_cust=l_no; 
	}
	fclose(rd);	
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
int check(int who,char name[20])
{    
	if(who==1){
		for(int i=0;i<seller_info.no_of_sellers;i++){
			if(!strcmp(name,seller_info.sellers[i].user_name)){
					printf("This user already exists\n");
					return 1;
			} 
		}
	}
	else{ 
	    for(int i=0;i<customer_info.no_of_cust;i++){
			if(!strcmp(name,customer_info.customers[i].user_name)){
				printf("This user already exists\n");
				return 1;
            } 
	    } 
    }  
	return 0;
}

int addtocart(int ctritem)
{
	FILE * iaddc;
	char path[50];
	sprintf(path,"./text_files/%s_cart.txt",us_id);
	iaddc=fopen(path,"a");
	fprintf(iaddc,"%d\n",ctritem);
	fclose(iaddc);	
	return 0;
}

int addto_order(int ctritem,int qty,char address[])
{
	FILE * iaddo;
	char path[50];
	sprintf(path,"./text_files/%s_orders.txt",us_id);
	iaddo=fopen(path,"a");
	fprintf(iaddo,"O|%d|%d|%s| ; \n",ctritem,qty,address);
	fclose(iaddo);
	return 0;	
}

void show_product(int ci,int itm_ch)
{
	int quantity;
	char w_buy;
	char d_address[100];
	system("cls");
	for(int i=0;i<strlen(categ[ci].itm[itm_ch].des);i++)
	{
		if(categ[ci].itm[itm_ch].des[i]=='$'){
			categ[ci].itm[itm_ch].des[i]='\r';
			i++;
			categ[ci].itm[itm_ch].des[i]='\n';
		}
	}
	printf("\t\t%s\n---------\ndescription:-------\n  %s\n\nPrice=%s/-\tSeller Id=%s\n",categ[ci].itm[itm_ch].title,
		categ[ci].itm[itm_ch].des,categ[ci].itm[itm_ch].price,categ[ci].itm[itm_ch].seller_id);
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
		printf("\nOrder Confirmed, your bill = %d\nur oder will be delivered at %s\nthank u for ur puchase!!"
				,atoi(categ[ci].itm[itm_ch].price)*quantity,d_address);
		addto_order(itm_ch*10+ci,quantity,d_address);
	}	
	else if(w_buy=='y')
	{
		addtocart(itm_ch*10+ci);
		printf("\nItem added to ur cart!!");
	}
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

void add_items(int cati)
{
	char title[15];
	char des[200];
	char price[10];
	char location[100]="abcd";
	printf("Product Name\n");
	fgetc(stdin);//dummy|used to overcome input skip problem 
	fgets(title,14,stdin);
	printf("Product description: ");
	fgets(des,199,stdin);
	printf("Product Price: ");
	fgets(price,9,stdin);
	FILE * iadd;
	char line[100];
	char path[50];
	sprintf(path,"./text_files/%s.txt",cat[cati]);
	iadd=fopen(path,"a");
	title[strlen(title)-1]='\0';
	des[strlen(des)-1]='\0';
	price[strlen(price)-1]='\0';
	printf("\n%s",dim[1]);
	fprintf(iadd,"S|%s|%s|%s|%s|%s| ; \n",title,des,price,location,us_id);
	fclose(iadd);	
}

int verify(int s_c,char ID[],char pass[])
{
	FILE * vf;
	char line[100];
	if(s_c==SELLCONST){
		vf=fopen("./text_files/sellr.txt","r");
	}
	else if(s_c==CUSTCONST)
	{
		vf=fopen("./text_files/cus.txt","r");
	}
	
	while(fgets(line,99,vf)!=NULL)
	{
		ppos=cpos;
		cpos=ftell(vf);
		if(strlen(line)>0){
			int i=0;
			dim[i] = strtok(line,"|");
			while(dim[i]!=NULL)
			{
	   			dim[++i] = strtok(NULL,"|");
			}
			if(!strcmp(dim[1],ID))
			{
				if(!strcmp(dim[2],pass)){
					printf("\nyou are successfully verified\n");
					strcpy(us_id,ID);
					fclose(vf);
					return 1;
				}
				fclose(vf);
				return 2;
			}
		}
		else{
			continue;
		}
	}
	fclose(vf);
	return 0;
}
void save(int s_c,char ID[],char pass[],char address[])
{
	FILE *sv;
	if(s_c==SELLCONST)
	{
		sv=fopen("./text_files/sellr.txt","a");
	}
	else if(s_c==CUSTCONST)
	{
		sv=fopen("./text_files/cus.txt","a");
	}
	fprintf(sv,"A|%s|%s|%s| ; \n",ID,pass,address);
	fclose(sv);
}

void seller_reg()
{
	int res=0;
	char s_nm[15],s_ps[15],s_cps[15],s_address[60];
	read_user(SELLCONST);
	do{
	printf("Enter name(of 10 letters)\n");	
	scanf("%s",&s_nm);
	}while(check(SELLCONST,s_nm));
	
	do{
		if(res>0){
			printf("password and confirm password didn't matched'");
		}
		printf("Enter password(max 10 letters)\n");
		scanf("%s",&s_ps);
		printf("Enter confirm password\n");
		scanf("%s",&s_cps);
		res++;
	}while(strcmp(s_ps,s_cps));
	
	printf("Enter your location with pincode(max 50 letters)\n");
	fgetc(stdin);//dummy|used to overcome input skip problem 
	fgets(s_address,59,stdin);
	s_address[strlen(s_address)-1]='\0';
	save(SELLCONST,s_nm,s_ps,s_address);
}

void customer_reg()
{
	int res=0;
	char c_nm[15],c_ps[15],c_cps[15],c_address[60];
	read_user(CUSTCONST);
	do{
	printf("Enter name(of 10 letters)\n");
	scanf("%s",&c_nm);
	}while(check(CUSTCONST,c_nm));
	
	do{
		if(res>0){
			printf("password and confirm password didn't matched'");
		}
		printf("Enter password(max 10 letters)\n");
		scanf("%s",&c_ps);
		printf("Enter confirm password\n");
		scanf("%s",&c_cps);
		res++;
	}while(strcmp(c_ps,c_cps));
	printf("Enter your location with pincode(max 50 letters)\n");
	fgetc(stdin);//dummy|used to overcome input skip problem 
	fgets(c_address,59,stdin);
	c_address[strlen(c_address)-1]='\0';
	save(CUSTCONST,c_nm,c_ps,c_address);
}

void seller_login()
{
	char s_nm[15], s_ps[15];
	int k=3;
	do{	
		system("cls");
		switch(k){
			case 2:
				printf("ID didn't match password\n");
				break;
			case 0:
				printf("no account for this seller ID\n");
		}
		printf("Enter ID(of 10 letters)\n");
		scanf("%s",&s_nm);
		printf("Enter password(max 10 letters)\n");
		scanf("%s",&s_ps);
		k=verify(SELLCONST,s_nm,s_ps);
	}while(k!=1);
}

void customer_login()
{
	char c_nm[15];
	char c_ps[15];
	int k=3;
	do{	
		system("cls");
		switch(k){
			case 2:
				printf("name didn't match password\n");
				break;
			case 0:
				printf("no account for this user name\n");
		}
		printf("Enter name(of 10 letters)\n");
		scanf("%s",&c_nm);
		printf("Enter password(max 10 letters)\n");
		scanf("%s",&c_ps);
		k=verify(CUSTCONST,c_nm,c_ps);
	}while(k!=1);
}
void choose_categories()
{
	int chs;	
	system("cls");
	printf("choose\n");
	for(int i=0;i<7;i++)
	{
		printf("(%s %d)\n",cat[i],i);
	}
	scanf("%d",&chs);	
	add_items(chs);
}
void showcart(){
	FILE * irc;
	char path[50];
	int ctritem=0;
	sprintf(path,"./text_files/%s_cart.txt",us_id);
	irc=fopen(path,"r");
		
	int found=0;
	for(int j=0;fscanf(irc,"%d",&ctritem)==1;j++){
		printf("\n{\n\t%d\n\tname: %s\n\tprice:%s\n\tsellerid: %s\n}",ctritem,categ[ctritem%10].itm[ctritem/10].title,
				categ[ctritem%10].itm[ctritem/10].price,
				categ[ctritem%10].itm[ctritem/10].seller_id);
		found++;
	}
	printf("\nenter the number above product name to select\n");
	int chs,ci,j;
	scanf("%d",&chs);
	ci=chs%10;
	j=chs/10;
	show_product(ci,j);
	
	fclose(irc);
	getch();
}
void showOders(){
	FILE * irc;
	char path[50],ln[300],ctri[8];
	char *divn[5];
	int ctritem=0;
	int found=0;
	sprintf(path,"./text_files/%s_orders.txt",us_id);
	irc=fopen(path,"r");
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
				for(int i=0;i<strlen(divn[3]);i++)
				{
					if(divn[3][i]=='$'){
					 divn[3][i]=' ';
					 i++;
					 divn[3][i]=' ';
					}
				}			
				printf("\n{\n\tname: %s\n\tprice:%s\n\tdeleverd to: %s\n\tquantity:%s\n\tsellerid: %s\n}",categ[ctritem%10].itm[ctritem/10].title,
				categ[ctritem%10].itm[ctritem/10].price,
				divn[3],divn[2],
				categ[ctritem%10].itm[ctritem/10].seller_id);
				found++;
			}
			else{
				continue;
			}
	}		
	
	fclose(irc);
	getch();
}
void showProducts(){
	int found =0;
	for(int ci=0;ci<7;ci++)
	{
		for(int j=0;j<categ[ci].itm_no;j++){
				printf("{ %s num=%d }\n",categ[ci].itm[j].title,j*10+ci);//,strcmp(match(title,"nkc")," "));
				found++;
		}
	}
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
void find_product()
{	
	system("cls");
	char title[15];
	printf("\nEnter ur product or\n enter 1 to see cart or\n 2 to see ur oders or\n enter 3 to see all products or\n enter 4 to exit:\n");
	int found=0;
	fgetc(stdin);//dummy|used to overcome input skip problem 
	fgets(title,14,stdin);
	if(title[0]=='1')
	{
		showcart();
		return;
	}
	else if(title[0]=='2')
	{
		showOders();
		find_product();
		return;
	}
	else if(title[0]=='3')
	{
		showProducts();
		return;
	}
	else if(title[0]=='4')
	{
		exit(0);
	}
	title[strlen(title)-1]='\0';
	
	for(int ci=0;ci<7;ci++)
	{
		for(int j=0;j<categ[ci].itm_no;j++){
			if(match(title,categ[ci].itm[j].title,50,50)){
				printf("{ %s num=%d }\n",categ[ci].itm[j].title,j*10+ci);//,strcmp(match(title,"nkc")," "));
				found++;
			}
		}
	}
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

int main()
{
	int who;
	read_all();
	printf("Select customer[1L,11R], seller[2L,22R]\n");
	scanf("%d",&who);
	switch(who){
		case 1:
			customer_login();
			find_product();
			break;
		case 2:
			seller_login();
			char w_buy; 
			do{
				choose_categories();
				printf("do u want to add more items [y/n]: ");
				/*fgetc(stdin);;*///dummy|used to overcome input skip problem 
				scanf("%c",&w_buy);
			}while(w_buy=='y');
			break;
		case 11:
			customer_reg();
			break;
		case 22:
			seller_reg();
			break;		
	}
	return 0;
}



