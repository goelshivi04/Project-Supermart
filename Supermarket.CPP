#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>

void main_menu_1();
void main_menu();
class product
{
 private:
   int pno;
   char name[50];
   float price,tax,disc;
 public:
   int qty;
   void create_product();
   void show_product();
   long cal();

   int  retpno()
   {return pno;}

   float retprice()
   {return price;}

   char* retname()
   {return name;}

   int retdis()
   {return disc;}
};
fstream f;
product p;
//-------------------------------------------------------------
//Function to take input
void product::create_product()
{
    cout<<"\n\nEnter the Product no.: ";
    cin>>pno;
    cout<<"\nEnter the Name of the Product: ";
    gets(name);
    cout<<"\nEnter the Price of the Product: ";
    cin>>price;
    cout<<"\nEnter the Discount (%) ";
    cin>>disc;
    cout<<"\nEnter Quantity of the Product: ";
    cin>>qty;
}
//----------------------------------------------------------
//Function to show Output
void product::show_product()
{
    cout<<"\n\nProduct No.: "<<pno;
    cout<<"\nName of The Product: "<<name;
    cout<<"\nPrice of The Product: "<<price;
    cout<<"\nDiscount: "<<disc;
    cout<<"\nQuantity of the Product: "<<qty;
}

//----------------------------------------------------------------------
//   Function to calculate number of products

long product::cal()
{
  long n;
  f.open("Shop.dat",ios::in|ios::binary);
  f.seekg(0,ios::end);
  n=f.tellg()/sizeof(p);
  f.close();
  return n;
}

//----------------------------------------------------------------
//    Function to write into the file

void write_product()
{
  f.open("Shop.dat",ios::out|ios::app);
  p.create_product();
  f.write((char*)&p,sizeof(p));
  f.close();
  cout<<"\n\nThe Product has been created ";
  getch();
}


//---------------------------------------------------------------
//   Function to read all records from file

void display_all()
{   int c=1;
    clrscr();
    cout<<"\n\n\n\t\t--------------------Details of all Record------------------\n\n";
    f.open("Shop.dat",ios::in);
    while(f.read((char*)&p,sizeof(p)))
    {
      cout<<"\nDetails of record "<<c<<" : \n";
      p.show_product();
      cout<<"\n\n-------------------------------------------\n";
      getch();
      c++;
    }
    f.close();
    getch();
}


//--------------------------------------------------------------
//   Function to read particular record from file

void display(int n)
{
    int flag=0;
    f.open("Shop.dat",ios::in);
    while(f.read((char*)&p,sizeof(p)))
	{
	 if(p.retpno()==n)
		{
		 clrscr();
		 p.show_product();
		 flag=1;
		}
	 }
    f.close();
  if(flag==0)
    cout<<"\n\nRecord does not exist!!";
 getch();
}


//---------------------------------------------------------------
//   Function to modify record of file

void modify_product()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\n\tEnter the Product No. of the product to be modified: ";
    cin>>no;
    f.open("Shop.dat",ios::in|ios::out);
    while(f.read((char*)&p,sizeof(p)) && found==0)
      {
	 if(p.retpno()==no)
	   {
	    p.show_product();
	    cout<<"\nEnter The New Details of Product:"<<endl;
	    p.create_product();
	    int pos=-1*sizeof(p);
	    f.seekp(pos,ios::cur);
	    f.write((char*)&p,sizeof(p));
	    cout<<"\n\n\tRecord Updated Succesfully!!";
	    found=1;
	   }
       }
    f.close();
    if(found==0)
    cout<<"\n\n Record Not Found!! ";
    getch();
}


//---------------------------------------------------------------
//    Function to delete record of file
void delete_product()
{ clrscr();
  product pr;
  char ch='y';
  int temp=0;
  ifstream f;
  int i,rnum;
  cout<<"\n\n\nEnter Product no. which is to deleted: ";
  cin>>rnum;
  f.open("Shop.dat",ios::binary);
  while(f.read((char*)&pr,sizeof(pr)))
  {
    if(pr.retpno()==rnum)
    { temp=1;
      break;}

  }
  if(temp==1)
 {pr.show_product();
 cout<<"\n\n\nAre you sure you want to delete this record(Y/N) ? ";
  cin>>ch; }
  else
  {  cout<<"\n\t\tRecord not found!!!"; getch();return;}
  if(ch=='y'|| ch=='Y')
{
  long n=pr.cal();
 ifstream fin;
   ofstream fout;
  fin.open("Shop.dat",ios::binary);
  if(!fin)
  cerr<<"File does not exist";
  fout.open("temp.dat",ios::binary);
  for(i=0;i<n;i++)
  {
    fin.read((char*)&pr,sizeof(pr));
    if(pr.retpno()!=rnum)
      fout.write((char*)&pr,sizeof(pr));
 }

  fin.close();
fout.close();
  remove("Shop.dat");
  rename("temp.dat","Shop.dat");
 cout<<"\n\tRecord deleted sucessfully!!!";
 getch();
}
}


//---------------------------------------------------------------
//    Function to display product price list


void menu()
 {
     clrscr();
     f.open("Shop.dat",ios::in);
     if(!f)
     {
       cout<<"\n\n\n\t\t\tERROR!!!";
       cout<<"THE SHOP IS EMPTY. THERE ARE NO PRODUCTS";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\tPRODUCT MENU\n\n";
     cout<<"--------------------------------------------------------\n";
     cout<<"P.NO.\t\tNAME\t\tPRICE\t\tQUANTITY\n";
     cout<<"--------------------------------------------------------\n";

     while(f.read((char*)&p,sizeof(p)))
     {
       cout<<p.retpno()<<"\t\t"<<p.retname()<<"\t\t";
       cout<<p.retprice()<<"\t\t"<<p.qty<<endl;
     }
     f.close();
}

//----------------------------------------------------------------------
//         Function to place order

void place_order()
{  fstream fp;
   product pr;
   int flag=0;
   int  p_list[50],quan[50],c=0;
   float amt,damt,total=0;
   char ch='Y';
   menu();
   cout<<"\n================================";
   cout<<"\n    PLACE YOUR ORDER";
   cout<<"\n================================\n";
   do
    {
	 start:
	 cout<<"\n\nEnter The Product No.: ";
	 cin>>p_list[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 fp.open("Shop.dat",ios::binary|ios::in|ios::out);
	 fp.seekg(0,ios::beg);
	 long r=pr.cal();
	 for(int i=1;i<=r;i++)
	 {
	    long place=fp.tellg();
	    fp.read((char*)&pr,sizeof(pr));
	if(pr.retpno()!=p_list[c])
	    {flag=1;}
	     if(pr.retpno()==p_list[c])
	    {  flag=0;
	       if(pr.qty>=quan[c])
	       {
		 pr.qty=pr.qty-quan[c];
		 fp.seekp(place);
		 fp.write((char*)&pr,sizeof(pr));
		 break;
	       }
	       else
	       {
		 cout<<"\nThere is Less Quantity Available of this product.";
		 fp.close();
		 goto start;
	       }

	     }
	  }
	  if(flag==1)
	 cout<<"\n\tProduct does not exist!!";
    fp.close();
    c++;
    cout<<"\n\nDo You Want To Order Another Product ? (y/n)";
    cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order!!";getch();clrscr();
      cout<<"\n\n********************************INVOICE**************************************\n";
      cout<<"\n-------------------------------------------------------------------------------";
      cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \t\tAmount after discount";
      cout<<"\n--------------------------------------------------------------------------------";
      for(int x=0;x<c;x++)
	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==p_list[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<p_list[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t   "<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\t\t\t\t\t\tTOTAL = "<<total;
    getch();
    }


//---------------------------------------------------------------
//    	Front page

void intro()
{
 clrscr();
 cout<<"\n\n************************************************************************";
 cout<<"\n\n\n\t\t\t     SUPER MARKET BILLING ";
 cout<<"\n\n\t\t\t            PROJECT";
 cout<<"\n\n\t\t\t     MADE BY : SHIVI GOEL";
 cout<<"\n\n************************************************************************";
 getch();
}


//---------------------------------------------------------------
//    	Admin menu function
void admin_menu()
{
  clrscr();
  char c;
  cout<<"\n\n\n\t\t\tADMIN MENU";
  cout<<"\n\n\t\t\t1.CREATE PRODUCT";
  cout<<"\n\n\t\t\t2.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t\t\t3.QUERY ";
  cout<<"\n\n\t\t\t4.MODIFY PRODUCT";
  cout<<"\n\n\t\t\t5.DELETE PRODUCT";
  cout<<"\n\n\t\t\t6.VIEW PRODUCT MENU";
  cout<<"\n\n\t\t\t7.EXIT";
  cout<<"\n\n\t\tPlease Enter Your Choice (1-7) ";
  c=getch();
  switch(c)
  {
    case '1':
     clrscr();
     write_product();
     break;

    case '2':
     display_all();
     break;

    case '3':
     int num;
     clrscr();
     cout<<"\n\n\tPlease Enter The Product No. ";
     cin>>num;
     display(num);
     break;

    case '4':
     modify_product();
     break;

    case '5':
     delete_product();
     break;

    case '6':
     menu();
     getch();

    case '7':main_menu();
     break;

    default:
     cout<<"\a";
     admin_menu();
  }
 admin_menu();
}
//----------------------------------------------------------------
//         Function to access admin function
void main_menu_1()
{
 char ch;
 clrscr();
 char user[30],pass[30];
 cout<<"\n\n\n\t\t\t\tLOGIN PAGE";
 cout<<"\n\n\t\tEnter Username: ";
 cin>>user;
 cout<<"\n\t\tEnter password: ";
 cin>>pass;
 if((strcmp(user,"ABCD")==0)&&(strcmp(pass,"1234")==0))
 {
  admin_menu();
 }
 else
 {
   cout<<"\n\t\tInvalid Credentials !!! ";
   cout<<"\n\t\tDo you want to retry (Y/N): ";
   cin>>ch;

 if(ch=='y'|| ch=='Y')
 { main_menu();}
 else
 { exit(0); }
 }
 getch();
 }


//-----------------------------------------------------------------
//     Main function of the program

void main()
{
  intro();
  main_menu();
}

//------------------------------------------------------------------
void main_menu()
{
  char ch;
  do
    {
	  clrscr();
	  cout<<"\n\n\n\n****************************SUPER MARKET BILLING*****************************";
	  cout<<"\n\n\n\t\t\t\tMAIN MENU";
	  cout<<"\n\n\t\t01. CUSTOMER";
	  cout<<"\n\n\t\t02. ADMINISTRATOR";
	  cout<<"\n\n\t\t03. EXIT";
	  cout<<"\n\n\t\tSelect Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
			   place_order();
			   getch();
			   break;
		  case '2': main_menu_1();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
}

//--------------------------------------------------------------------
//        The End
