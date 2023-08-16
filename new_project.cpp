#include <iostream>
#include <fstream>
#include <string.h>
#include <limits>
#include <unistd.h>
#include <string>

using namespace std;
class ATM {

private :
string username;
string password;
int balance;

public :
string getUsername() const
{
    return username;
}
string getPasswords() const
{
    return password;
}
int getBalance()
{
    return balance;
}
void changebalance(int newbalance)
{
    balance=newbalance;
}

void get_data()
{  
    ifstream fin;

reusername :
    cout<<"Enter the username :";
    getline(cin,username);
    fin.open("new.txt",ios::in);
    if(fin.is_open())
    {
         ATM buff;
         fin.read((char *)&buff,sizeof(buff));
         while (fin.read((char*)&buff, sizeof(buff))) 
        {
            if(buff.getUsername()==username)
            {
                cout<<"Username already taken\n";
                fin.close();
                goto reusername;
            }
        }
        fin.close();
       
    }
    else
    {
        cout<<"FAILED TO OPEN\n";
        return ;
    }

repassword :

    cout<<"Enter the password :";
    getline(cin,password);
    fin.open("new.txt",ios::in);
    if(fin.is_open())
    {
         ATM buff;
         fin.read((char *)&buff,sizeof(buff));
         while (fin.read((char*)&buff, sizeof(buff))) 
        {
            if(buff.getPasswords()==password)
            {
                cout<<"Password already taken\n";
                fin.close();
                goto repassword;
            }
        }
       
    }
    else
    {
        cout<<"FAILED TO OPEN\n";
        return ;
    }

 cout<<"Enter your Balance :\n";
 cin>>balance;
 cin.ignore(numeric_limits<streamsize>::max(),'\n');

}
int viewbalace(string);
void add_user();
void viewAllUsers();
void deposit(string);
void withdraw(string);
void deleteUser(string);
int searchSpecificUser(string,string);


};

void ATM :: deleteUser(string username)
{
   ifstream fin;
   fin.open("new.txt",ios::in);
   if(!fin.is_open())
   {
      cout<<"FAILED TO OPEN FILE\n";
      return;

   }

   ofstream fout;
   fout.open("new_temp.txt",ios::out);
   if(!fout.is_open())
   {
      cout<<"FAILED TO OPEN  TEMPORARY FILE\n";
      return;
   }
   bool is_deleted=false;
   ATM buff;
   //fin.read((char *) &buff,sizeof(buff));
   while(fin.read((char *) &buff,sizeof(buff)))
   {
       if(buff.getUsername()==username)
      {
         is_deleted=true;
         cout<<"SUCCESFULLY ACCOUNT IS DELETED\n";

      }
      else
      {
        fout.write((char*) &buff,sizeof(buff));
      }

   }
   if(is_deleted==false)
   {
     cout<<"USERNAME NOT FOUND\n";
   }
   fout.close();
   fin.close();
   remove("new.txt");
   rename("new_temp.txt","new.txt");

}

void ATM ::viewAllUsers()
{
    ifstream fin;
    fin.open("new.txt",ios::in);
    if(fin.is_open())
    {
        ATM buff;
       // fin.read((char*) &buff,sizeof(buff));
        while(fin.read((char*) &buff,sizeof(buff)))
        {
            cout << "Username : " << buff.getUsername() << " ,Password : " << buff.getPasswords() << " ,Balance : " << buff.getBalance();
            cout<<endl;
        }
        fin.close();

    }
    else
    {
        cout<<"FAILED TO OPEN FILE\n";
        return ;
    }

}

void ATM :: add_user()
{
    ATM a;
    a.get_data();
    ofstream fout;
    fout.open("new.txt",ios::out|ios::app);
    if(!fout.is_open())
    {
        cout<<"FAILED TO OPEN FILE";
        return ;
    }

    fout.write((char*) &a,sizeof(a));
   
    fout.close();

}

void ATM :: withdraw(string username)
{

   ifstream fin;
   fin.open("new.txt",ios::in);
   if(!fin.is_open())
   {
      cout<<"FAILED TO OPEN FILE\n";
      return;

   }

   ofstream fout;
   fout.open("new_temp.txt",ios::out);
   if(!fout.is_open())
   {
      cout<<"FAILED TO OPEN  TEMPORARY FILE\n";
      return;
   }
   
   ATM buff;
  // fin.read((char *) &buff,sizeof(buff));
   while(fin.read((char *) &buff,sizeof(buff)))
   {
       if(buff.getUsername()==username)
      {
        int balance;
         cout<<"ENTER AMOUNT TO WITHDRAWAL :\n";
         cin>>balance;
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         if(buff.getBalance()<balance)
         {
             cout<<"INSUFFICENT BALANCE \n";
         }
         else
         {
            balance=buff.getBalance()-balance;
            buff.changebalance(balance);
            cout<<"WITHDRAWAL SUCCESSFULLY COMPLETED\n";
         }
         
         fout.write((char*) &buff,sizeof(buff));
      }
      else
      {
        fout.write((char*) &buff,sizeof(buff));
      }

   }

   fout.close();
   fin.close();
   remove("new.txt");
   rename("new_temp.txt","new.txt");

}

void ATM :: deposit(string username)
{
   ifstream fin;
   fin.open("new.txt",ios::in);
   if(!fin.is_open())
   {
      cout<<"FAILED TO OPEN FILE\n";
      return;

   }

   ofstream fout;
   fout.open("new_temp.txt",ios::out);
   if(!fout.is_open())
   {
      cout<<"FAILED TO OPEN TEMPOPRARY FILE\n";
      return;
   }
   
   ATM buff;
  // fin.read((char *) &buff,sizeof(buff));
   while(fin.read((char *) &buff,sizeof(buff)))
   {
       if(buff.getUsername()==username)
      {
         int balance;
         cout<<"ENTER AMOUNT TO DEPOSIT :\n";
         cin>>balance;
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         balance=buff.getBalance()+balance;
         buff.changebalance(balance);
         cout<<"AMOUNT DEPOSITED SUCCESSFULLY\n";
         fout.write((char*) &buff,sizeof(buff));
      }
      else
      {
        fout.write((char*) &buff,sizeof(buff));
      }

   }

   fout.close();
   fin.close();
   remove("new.txt");
   rename("new_temp.txt","new.txt");
    
}


int ATM :: viewbalace(string username)
{
   ifstream fin;
   fin.open("new.txt",ios::in);
   if(fin.is_open())
   {
        ATM buff;
       // fin.read((char*) &buff,sizeof(buff));
        while(fin.read((char*) &buff,sizeof(buff)))
        {
            if(buff.getUsername()==username)
            {
                fin.close();
                return buff.getBalance();
            }
        }
        fin.close();

   }
   else
   {
       cout<<"FAILED TO OPEN FILE\n";
       return -1;

   }

   return -1;
}

int ATM :: searchSpecificUser(string username,string password)
{
    ifstream fin;
    fin.open("new.txt",ios::in);
    if(fin.is_open())
    {
        ATM buff;
       // fin.read((char*) &buff,sizeof(buff));
        while(fin.read((char*) &buff,sizeof(buff)))
        {
            if(buff.getUsername()==username)
            {
                if(buff.getPasswords()==password)
                {
                    fin.close();
                    return 1;
                }
                else
                {
                    fin.close();
                    return 3;
                }
            }
        }
        fin.close();
    }
    else
    {
        cout<<"FAILED TO OPEN FILE\n";
        return 0;
    }

    return 2;

} 

void interface()
{

char ch1,ch2;
string pass,username;

mainmenu :

   cout<<"Welcome to ATM \n";
   cout<<"Login as :\n";
   cout<<"Admin : 1\n";
   cout<<"User : 2\n";
   cout<<"Exit : 3\n";

   
   cin>>ch1;
   cin.ignore(numeric_limits<streamsize>::max(),'\n');

if(ch1=='1')
{

adminRerun :

  cout<<"Enter password to Login as Admin :\n";
  getline(cin,pass);
  if(pass!="Bank@123")
  {
     cout<<"INVALID Password\n";
     goto adminRerun;
  }

  cout<<"\nWelcome Admin\n";

admin :

     cout<<"ENTER 1 -- ADD USER\n";
     cout<<"ENTER 2 -- VIEW ALL USERS\n";
     cout<<"ENTER 3 -- DELETE ACCOUNT\n";
     cout<<"ENTER 4 -- EXIT\n";
     cin>>ch2;
     cin.ignore(numeric_limits<streamsize>::max(),'\n');
     if(ch2=='1')
     {
         ATM a;
         a.add_user();
         goto admin;
     }
     else if(ch2=='2')
     {
        ATM a;
        a.viewAllUsers();
        goto admin;
     }
     else if(ch2=='3')
     {
        ATM a;
        cout<<"ENTER USERNAME TO BE DELETED :\n";
        getline(cin,username);
        a.deleteUser(username);
        goto admin;
     }
     else if(ch2=='4')
     {
        goto mainmenu;
     }

}
else if(ch1=='2')
{

userRerun :

           cout<<"ENTER YOUR USERNAME : \n";
           getline(cin,username);
           cout<<"ENTER YOUR PASSWORD : \n";
           getline(cin,pass);

           ATM a;
           int found=a.searchSpecificUser(username,pass);
           if(found!=1)
           {
              if(found==2)
              {
                  cout<<"INVALID USERNAME\n";
              }
              else if(found==3)
              {
                 cout<<"INVALID PASSWORD\n";
              }

              goto userRerun;
           }

user :

       cout<<"\nWELCOME "<<username<<'\n';
       cout<<"ENTER 1 -- VIEW BALANCE\n";
       cout<<"ENTER 2 -- DEPOSIT\n";
       cout<<"ENTER 3 -- WITHDRAWAL\n";
       cout<<"ENTER 4 -- EXIT\n";

       cin>>ch2;
       cin.ignore(numeric_limits<streamsize>::max(),'\n');

       if(ch2=='1')
       {
          ATM a;
          int balance=a.viewbalace(username);
          if(balance!=-1)
          {
             cout<<"CURRENT BALANCE -- "<<balance<<endl;
          }
          goto user;
       }
       else if(ch2=='2')
       {
          ATM a;
          a.deposit(username);
          goto user;
       }
       else if(ch2=='3')
       {
          ATM a;
          a.withdraw(username);
          goto user;

       }
       else if(ch2=='4')
       {

          goto mainmenu;
       }
}
else if(ch1=='3')
{

    return ;
}

}

int main()
{

   interface();
   
}
