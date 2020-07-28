#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Kangru.h"
#include "Interface.h"

using namespace std;

int main()
{
	string username;
	Kangru k;
	Interface f;
	char op;
	do
	{
		cout << "1. Admin Login\n";
		cout << "\n2. User Login\n";
		cout << "\n3. Create a new account\n";
		cout << "\n4. Exit\n";
		cout << "\nOption: ";
		cin >> op;
		switch (op)
		{
		case '1':
			if (k.AdminLogin())
				f.AdminInterface();
			break;
		case '2':
			if (k.UserLogin(username))
			{
				f.LoginInfo(username);
				f.UserInterface(username);
			}
			break;
		case '3':
			k.SignUp();
			break;
		case '4':
			exit(1);
		default:
			cout << "Choose from the following\n";
			k.Clear();
		}
		k.Clear();
	} while (true);
}