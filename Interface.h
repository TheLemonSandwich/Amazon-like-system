#ifndef INTERFACE_H
#define INTERFACE_H
#include "Kangru.h"

using namespace std;
class Interface :public Kangru
{
public:
	void LoginInfo(string& username);
	void UserInterface(string& username);
	void AdminInterface();
protected:
	int quantity;
private:
	string find, owner;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
};
	string Filename();
	void Newitem();
	void Requests();
	void CheckComplains();
	void UserList();
	void Search();
	void DeleteUser();
	void SizeIncrease(string*& items, int& size);
	void ComplainMenu(string& username);
	void SizeIncrease(float*& items, int& size);
	int IsANumber(string s, int& n);
	float IsANumber(string& s, float& n);
	void NewItem(string username);
	void TransferMoney(int* ownerid, int ownercount, float* oprice, int* oquan);
	void SellerMode(string username);
	void SizeIncrease(int*& items, int& size);
	void NewMemberMessageGenerator();
	void Checkout(string username);
	float TotalMoneyRequired(string username);
	bool SearchP(string& name, char op, string& owner, int& id, int& quan);
	void ChooseByID(string& username);
	void RemoveEverything(string username);
	void RemoveFromCart(string username);
	void Signout(string username);
	bool Checkifexists(string username, string find);
	void Seecart(string username);
#endif // !INTERFACE_H
