#ifndef KANGRU_H
#define KANGRU_H

using namespace std;
struct list
{
	string item, price, quantity, discount;
	list* left, * right;
};
struct node
{
	string name, username, password, phonenumber, emailaddress,secQ,Ans,loggedin;
	int money;
	node* left;
	node* right;
	list l;
};
class Kangru
{
public:
	Kangru();
	bool AdminLogin();
	bool UserLogin(string &username);
	void SignUp();
	void Clear();
protected:
	string Filename();
	string name, username, emailaddress, password, phonenumber, line;
	string secQ, Ans;
	int loggedin, money, id;
	node* root;
	bool invalid, exiter;
	int count, search;
	char op;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
private:
	
	bool Username(string username);
	void ForgotPassword(string username);
	bool Password(string password) const;
	bool EmailAddress(string emailaddress) const;
	bool PhoneNumber(string phonenumber) const;
};
	char* stringtochar(string& name, char* ch);
#endif // !KANGRU_H

