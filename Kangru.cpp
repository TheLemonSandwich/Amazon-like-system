#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <ctime>
#include <process.h>
#include "Kangru.h"
#include "Interface.h"
#include <conio.h>

using namespace std;

void Kangru::Clear()
{
	cout << endl;
	system("pause");
	system("cls");
}
//													ADMIN AND USER LOGIN 
Kangru::Kangru() : id(0) {};

bool Kangru::AdminLogin()
{
	cin.ignore();
	int search;
	do
	{
		Clear();
		invalid = false;
		ifstream admin(admindir + "Admin.txt");
		cout << "Username: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
			getline(admin, line);
			search = line.find("Username: ");
			if (search != string::npos)
			{
				search = line.find(": ");
				search += 2;
				if (username == (line.substr(search, line.length())))
				{
					getline(admin, line);
					search = line.find(": ");
					search += 2;
					if (password == (line.substr(search, line.length())))
					{
						return true;
					}
					else
					{
						cout << "\nWrong Password\n";
						return false;
					}
				}
				else
				{
					cout << "\nWrong Username\n";
					return false;
				}
			}
		admin.close();
	} while (invalid);
}

void Kangru::SignUp()
{
	cin.ignore();
	count = 0;
	char op;
	exiter = false;
	
	do
	{
		count++;
		if (count > 1)
		{
			cout << "\nDo you want to exit Sign-up?(y/n)";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				exiter = true;
				break;
			}
			cin.ignore();
		}
		cout << "\nUsername: ";
		getline(cin, username);
	} while (!Username(username));
	if (exiter) goto End;
	cout << "\nFull Name: ";
	getline(cin, name);
	count = 0;
	do
	{
		count++;
		if (count > 1)
		{
			cout << "\nDo you want to exit Sign-up?(y/n)";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				exiter = true;
				break;
			}
			cin.ignore();
		}
		cout << "\nPassword: ";
		getline(cin, password);
	}while(!Password(password));
	if (exiter) goto End;
	count = 0;
	do
	{
		count++;
		if (count > 1)
		{
			cout << "\nDo you want to exit Sign-up?(y/n)";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				exiter = true;
				break;
			}
			cin.ignore();
		}
		cout << "\nEmail address: ";
		getline(cin, emailaddress);
	} while (!EmailAddress(emailaddress));
	if (exiter) goto End;
	count = 0;
	do
	{
		count++;
		if (count > 1)
		{
			cout << "\nDo you want to exit Sign-up?(y/n)";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				exiter = true;
				break;
			}
			cin.ignore();
		}
		cout << "\nPhone Number: ";
		getline(cin, phonenumber);
	} while (!PhoneNumber(phonenumber));
	if (exiter) goto End;
	cout << "A Secret Question:-\n";
	getline(cin, secQ);
	cout << "Answer:-\n";
	getline(cin, Ans);
End: {}
	if (!exiter)
	{
		fstream file(admindir + "Users.txt", ios::out | ios::app);
		file << "ID: " << id << endl;
		file << "Username: " << username << endl;
		file << "Name: " << name << endl;
		file << "Code: " << password << endl;
		file << "Email Address: " << emailaddress << endl;
		file << "Phone Number: " << phonenumber << endl;
		file << "Money: $1500" << endl;
		file << "Q: " << secQ << endl;
		file << "Ans: " << Ans << endl;
		file.close();
		
		string directory = makedir + username;
		char* d = new char[directory.length()];
		d = stringtochar(directory, d);
		_mkdir(d);
		ofstream userdata(directory + "/" + username + ".txt");
		userdata << "ID: " << id << endl;
		userdata << "Username: " << username << endl;
		userdata << "Name: " << name << endl;
		userdata << "Code: " << password << endl;
		userdata << "Email Address: " << emailaddress << endl;
		userdata << "Phone Number: " << phonenumber << endl;
		userdata << "Money: $1500" << endl;
		userdata << "Q: " << secQ << endl;
		userdata << "Ans: " << Ans << endl;
		userdata << "Logged In: 0" << endl << endl;
		userdata.close();
	}

}

bool Kangru::Username(string username)
{
	if (username.length() < 4)
	{
		cout << "\nUsername must have atleast 4 characters\n";
		return false;
	}
	for (int i = 0; i < username.length(); i++)
	{
		if (username.at(i) == ' ')
		{
			cout << "\nUsername cannot have spaces\n";
			return false;
		}
	}
	int search;
	string line, user;
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		search = 0;
		getline(file, line);
		search = line.find("Username: ");
		if (search != string::npos)
		{
			id++;
			search = line.find(": ", 0);
			search += 2;
			user = "";
			for (int i = search; i < line.length(); i++)
				user += line.at(i);
			if (user == username)
			{
				cout << "User Already Taken\n";
				file.close();
				return false;
			}

		}
	}
	file.close();
	return true;
}

bool Kangru::Password(string password) const
{
	if (password.length() < 6)
	{
		cout << "\nPassword Must be Greater than 5 characters\n";
		return false;
	}
	else
	{
		// Other Conditions like including special letters and telling password's strength	
	}
	return true;
}

bool Kangru::EmailAddress(string emailaddress) const
{
	int counter = 0;
	for (int i = 0; i < emailaddress.length(); i++)
	{
		if (emailaddress.at(i) == ' ')
		{
			cout << "Email Address cannot have spaces\n";
			return false;
		}
		if (emailaddress.at(i) == '@')
			counter++;
	}
	if (counter != 1)
	{
		cout << "Invalid Email Address\n";
		return false;
	}
	string com = emailaddress.substr(emailaddress.length() - 4, emailaddress.length());
	if (com != ".com")
	{
		cout << "Invalid Email Address\n";
		return false;
	}
	int search;
	string line, email;
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		getline(file, line);
		search = line.find("Email Address: ", 0);
		if (search != string::npos)
		{
			search = line.find(": ", 0);
			search += 2;
			for (int i = search; i < line.length(); i++)
				email += line.at(i);
			if (email == emailaddress)
			{
				cout << "\nAlready In Use\n";
				return false;
			}
		}
	}
	file.close();
	return true;
}

bool Kangru::PhoneNumber(string phonenumber) const
{
	if (phonenumber.length() != 12 && phonenumber.at(0) != '+')
	{
		cout << "Invalid Number\n";
		return false;
	}
	if (phonenumber.length() != 14 && phonenumber.at(0) == '+')
	{
		cout << "Invalid Number\n";
		return false;
	}
	if(phonenumber.at(0) == '+')
		if (phonenumber.at(3) != '-')
		{
			cout << "Forgot to add '-'\n";
			return false;
		}
	if(phonenumber.at(0) != '+')
		if (phonenumber.at(4) != '-')
		{
			cout << "Forgot To add '-'\n";
			return false;
		}
	int search,counter = 0;
	string line, phone;
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		getline(file, line);
		search = line.find("Phone Number: ", 0);
		if (search != string::npos)
		{
			search = line.find(": ", 0);
			search += 2;
			for (int i = search; i < line.length(); i++)
				phone += line.at(i);
			if (phone == phonenumber)
			{
				counter++;
				if (counter > 3)
				{
					cout << "\nPhone Number is already used in 3 other accounts\n";
					return false;
				}
			}
		}
	}
	file.close();
	return true;
	return true;
}

void Kangru::ForgotPassword(string username)
{
	Clear();
	cin.ignore();
	cout << "Email Address: ";
	getline(cin, emailaddress);
	bool done = false;
	int search;
	string line, email,Q,Ans,Answer,pass;
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		if (done) break;
		search = 0;
		getline(file, line);
		if (line == "Username: " + username)
		{
			while (!file.eof())
			{
				getline(file, line);
				search = line.find("Code: ");
				if (search != string::npos)
				{
					if (done) break;
					search = line.find(": ");
					search += 2;
					pass = line.substr(search, line.length());
					getline(file, line);
					search = line.find("Email Address: ");
					if (search != string::npos)
					{
						search = line.find(": ");
						search += 2;
						email = line.substr(search, line.length());
						if (email == emailaddress)
						{
							while (!file.eof())
							{
								getline(file, line);
								search = line.find("secQ: ");
								if (search != string::npos)
								{
									cout << line << endl;
									getline(file, line);
									search = line.find(": ");
									search += 2;
									cout << "Ans: ";
									getline(cin, Ans);
									for (int i = search; i < line.length(); i++)
										Answer += line.at(i);
									if (Ans == Answer)
									{
										cout << "Password: " << pass << endl << endl;
										done = true;
										break;
									}
									else cout << "Wrong Answer\n";
								}
							}
						}
						else
						{
							cout << "Invalid Email Address\n";
							break;
						}
					}
				}
			}
		}
	}
	file.close();

}

bool Kangru::UserLogin(string &username)
{
	Clear();
	cin.ignore();
	invalid = false;
	cout << "Username: ";
	getline(cin, username);
	int search;
	string line, user;
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		search = 0;
		getline(file, line);
		search = line.find("Username: ");
		if (search != string::npos)
		{
			search = line.find(": ", 0);
			search += 2;
			user = line.substr(search, line.length());
			if (user == username)
			{
				string pass;
				cout << "Password: ";
				getline(cin, password);
				while (!file.eof())
				{
					getline(file, line);
					search = line.find("Code: ");
					if (search != string::npos)
					{
						search = line.find(": ", 0);
						search += 2;
						pass = "";
						for (int i = search; i < line.length(); i++)
							pass += line.at(i);
						if (pass == password)
							return true;
						else
						{
							cout << "Wrong Password\n";
							cout << "Forgot your Password?(y/n)\t";
							char op;
							cin >> op;
							if (op == 'y' || op == 'Y')
								ForgotPassword(user);
							invalid = true;
							break;
						}
					}
				}

			}
		}
	}
	file.close();
	if(!invalid)
		cout << "Username doesn't Exist\n";
	return false;
}

string Kangru::Filename()
{
	string filename = __FILE__;
	string file2;
	for (int i = 0; i < filename.length(); i++)
	{
		if (filename.at(i) == '\\')
			file2 += "/";
		else
			file2 += filename.at(i);

	}
	int search = file2.find("Project/");
	if (search != string::npos)
	{
		search += 8;
		file2 = file2.substr(0, search);
	}
	file2;
	return file2;
}