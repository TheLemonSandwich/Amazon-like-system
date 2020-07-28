#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <direct.h>
#include "Kangru.h"
#include "Interface.h"

using namespace std;

void Interface::LoginInfo(string& username)
{
	ifstream file(makedir + username + "/" + username + ".txt");
	ofstream temp(makedir + username + "/" + "temp.txt", ios::out);
	if (file.is_open())
		while (!file.eof())
		{
			getline(file, line);
			search = line.find("Logged In: ");
			if (search != string::npos)
			{
				int log;
				search = line.find(": ");
				search += 2;
				if (line.length() > 11)
				{
					log = stoi(line.substr(search, line.length()));
					if (!log)
						NewMemberMessageGenerator();
					log++;
					temp << "Logged In: " << log << endl;
				}
			}
			else temp << line << endl;
		}
	else
		cout << "Couldn't open file\n";

	file.close();
	temp.close();
	string filename = username + ".txt";
	string filepath = makedir + username + "/" + filename;
	remove(filepath.c_str());
	string tempo = makedir + username + "/" + "temp.txt";
	rename(tempo.c_str(), filepath.c_str());
}

void Interface::UserInterface(string& username)
{
	do
	{
		Clear();
		cout << "A. Buyer Mode\n";
		cout << "\nB. Seller Mode\n";
		cout << "\nC. Complain Menu\n";
		cout << "\nD. Exit\n";
		cout << "\nChoose: ";
		string choice;
		getline(cin, choice);
		if (choice == "A" || choice == "a" || choice == "1")
		{
			int money;
			ofstream cart(makedir + username + "/Cart.txt", ios::out);
			cart.close();
			do
			{
				Clear();
				fstream file(admindir + "KangruList.txt");
				while (!file.eof())
				{
					getline(file, line);
					cout << line << endl;
				}
				file.close();
				cout << "\n1. Search\n";
			//	cout << "\n2.Filter (Not Working ATM)\n";
			//	cout << "\n3. Sort (Not Working ATM)\n";
				cout << "\n4.See Cart\n";
				cout << "\n5. Type ID Number to Add to Cart\n";
				cout << "\n6. Remove From Cart\n";
				cout << "\n7. Remove Everything From Cart\n";
				cout << "\n8. Money Required To Buy Things In Cart\n";
				cout << "\n9. Checkout\n";
				cout << "\n10. Signout\n";
				cout << "\n11. Main Menu\n";
				cout << "\nChoose: ";
				getline(cin, choice);
				int choose;
				// Dont Ask What This Is
				{
					if (choice.length() < 3)
					{
						if (choice.length() == 1)
						{
							if (int(choice.at(0)) > 47 && int(choice.at(0)) < 58)
								choose = stoi(choice);
							else
							{
								cout << "Choose from the following\n";
								continue;
							}
						}
						else if (choice.length() == 2)
						{
							if (int(choice.at(0)) > 47 && int(choice.at(0)) < 58)
							{
								if (int(choice.at(1)) > 47 && int(choice.at(1)) < 58)
									choose = stoi(choice);
								else
								{
									cout << "Choose from the following\n";
									continue;
								}
							}
							else
							{
								cout << "Choose from the following\n";
								continue;
							}
						}
						else
						{
							cout << "Choose from the following\n";
							continue;
						}
					}
					else
					{
						cout << "Choose from the following\n";
						continue;
					}
				}
				switch (choose)
				{
				case 1:
					cout << "\n\n1. Search by  Product Name\n";
					cout << "\n2. Search by Owner Name\n";
					cout << "\nChoose: ";
					cin >> op;
					cin.ignore();
					cout << ">>\t";
					getline(cin, find);
					int quan;
					if (SearchP(find, op, owner, id, quan))
						ChooseByID(username);
					else cout << "\nCouldn't find\n";
					break;
				case 2:

					break;
				case 3:

					break;
				case 4:
					system("cls");
					Seecart(username);
					break;
				case 5:
					ChooseByID(username);
					break;
				case 6:
					RemoveFromCart(username);
					break;
				case 7:
					RemoveEverything(username);
					break;
				case 8:
					money = TotalMoneyRequired(username);
					if (money == -1);
					else
						cout << "Total Money Required = " << money << endl;
					break;
				case 9:
					Checkout(username);
					break;
				case 10:
					Signout(username);
					break;
				case 11:
					break;
				default:
					cout << "Choose from the following\n";
				}
			} while (true);
		}
		else if (choice == "B" || choice == "b" || choice == "2")
		{
			string newprice, discount, quantity;
			do
			{
				cout << "\n1.Put An Item On Kangru\n";
				cout << "\n2. Back to Main Menu\n";
				getline(cin, choice);
				if (choice == "1")
				{
					system("cls");
					cout << "1. From Bought Items\n";
					cout << "\n2. Introduce a new item\n";
					cout << "\n3. Go Back\n";
					getline(cin, choice);
					if (choice == "1")
					{
						ifstream List(makedir + username + "/List.txt");
						while (!List.eof())
						{
							getline(List, line);
							cout << line << endl;
						}
						List.close();
						SellerMode(username);
					}
					else if (choice == "2")
						NewItem(username);
					else if (choice == "3")
						break;
					else cout << "Choose from the following\n";
				}
					
				else if (choice == "2")
					break;
				else cout << "Choose from the following\n";
			} while (true);
		}
		else if (choice == "C" || choice == "c" || choice == "3")
			ComplainMenu(username);
		else if (choice == "D" || choice == "d" || choice == "4")
			exit(1);
		else cout << "Choose from the following\n";
	} while (true);
}

void Interface::AdminInterface()
{
	bool Menu = false;
	do
	{
		Clear();
		cout << "1. List of Users\n";
		cout << "\n2. Search a User\n";
		cout << "\n3. Disable a User\n";
		cout << "\n4. Complain Menu\n";
		cout << "\n5. Requests\n";
		cout << "\n6. Supply a new product\n";
		cout << "\n7. Main Menu\n";
		cin >> op;
		switch (op)
		{
		case '1':
			UserList();
			break;
		case '2':
			Search();
			break;
		case '3':
			DeleteUser();
			break;
		case '4':
			CheckComplains();
			break;
		case '5':
			Requests();
			break;
		case '6':
			Newitem();
			break;
		case '7':
			Menu = true;
			break;
		default:
			cout << "Choose from the following\n";
			system("pause");
		}
		if (Menu)
			break;
	} while (true);
}

void Newitem()
{
	system("pause");
	string dir = Filename();
	string admindir = dir + "Admin/";
	string name, quantity, price, moni;
	string op, line;
	cin.ignore();
	int search, search2, q;
	float p, money;
	cout << "Product Name: ";
	getline(cin, name);
	while (true)
	{
		cout << "Price: $";
		getline(cin, price);
		cout << "Quantity: ";
		getline(cin, quantity);
		p = IsANumber(price, p);
		q = IsANumber(quantity, q);
		if (p == -1 || q == -1)
			cout << "\nInvalid Price or Quantity\n";
		else break;
	}
	ifstream List(admindir + "KangruList.txt");
	int max = 0;
	int id;

	//													ADDING IN KANGRU LIST

	while (!List.eof())
	{
		getline(List, line);
		if (search = line.find("ID: ") != string::npos)
		{
			search = line.find("_");
			search++;
			id = stoi(line.substr(search, line.length()));
			if (id > max)
				max = id;
		}
	}
	List.close();
	ofstream KangruList(admindir + "KangruList.txt", ios::out | ios::app);
	KangruList << "ID: " << 0 << "_" << ++max << endl;
	KangruList << "Owner: Kangru\n";
	KangruList << "Name: " << name << endl;
	KangruList << "Price: $" << p << endl;
	KangruList << "Quantity: " << quantity << endl;
	KangruList << "Discount: N/A\n\n";
	KangruList.close();
	cout << "\nProduct Added!\n";
}

void Requests()
{
	system("cls");
	string line;
	string dir = Filename();
	string admindir = dir + "Admin/";
	ifstream request(admindir + "Request.txt");
	while (!request.eof())
	{
		getline(request, line);
		cout << line << endl;
	}
}

void CheckComplains()
{
	system("cls");
	string line;
	string dir = Filename();
	string admindir = dir + "Admin/";
	ifstream complains(admindir + "Complains.txt");
	while (!complains.eof())
	{
		getline(complains, line);
		cout << line << endl;
	}
}

void DeleteUser()
{
	system("cls");
	cin.ignore();
	string line,username;
	int search;
	string id;
	string userfile, tempfile;
	char op;
	cout << "ID: ";
	getline(cin, id);
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	ifstream file(admindir + "Users.txt");
	ofstream temp(admindir + "temp.txt");

													//	DELETING FROM ADMIN

	while (!file.eof())
	{
		getline(file, line);
		search = line.find("ID: " + id);
		if (search != string::npos)
		{
			cout << "Are you sure? (Y/N)\t";
			cin >> op;
			if (op == 'Y' || op == 'y') do
			{
				
				if (search = line.find("Username: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					username = line.substr(search, line.length());
				}
				getline(file, line);
			}
			while (search = line.find("ID: ") == string::npos && !file.eof());
			temp << line << endl;
		}
		else temp << line << endl;
	}
	file.close();
	temp.close();
	userfile = admindir + "Users.txt";
	tempfile = admindir + "temp.txt";
	remove(userfile.c_str());
	rename(tempfile.c_str(), userfile.c_str());

													//	DISABLING FROM USER'S DATA

	string users = makedir + username + "/" + username + ".txt";
	tempfile = admindir + "Disabled/" + username;
	_mkdir(tempfile.c_str());
	ifstream Ufile(users);
	ofstream tempo(tempfile + "/" + username + ".txt");
	while (!Ufile.eof())
	{
		getline(Ufile, line);
		tempo << line << endl;
	}
	Ufile.close();
	tempo.close();
	remove(users.c_str());
	string list = makedir + username + "/List.txt";
	ofstream templist(tempfile + "/List.txt");
	ifstream Ulist(list);
	getline(Ulist, line);
	if (line.length() == 0 || line == "\0");
	else
	{
		templist << line << endl;
		while (!Ulist.eof())
		{
			getline(Ulist, line);
			templist << line << endl;
		}
	}
	templist.close();
	Ulist.close();
	remove(list.c_str());
	cout << "\nUser Disabled!\n";
}

void Search()
{
	system("cls");
	cin.ignore();
	string line,username;
	int search;
	string id;
	cout << "Username: ";
	getline(cin, username);
	string dir = Filename();
	string admindir = dir + "Admin/";
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		getline(file, line);
		search = line.find("ID: ");
		if (search != string::npos)
			id = line;
		search = line.find("Username: " + username);
		if (search != string::npos)
		{
			cout << id << endl;
			do
			{
				cout << line << endl;
				getline(file, line);
			} while (search = line.find("secQ: ") == string::npos && !file.eof());
		}
	}
}

void UserList()
{
	system("cls");
	string line;
	int search;
	int count = 1;
	string dir = Filename();
	string admindir = dir + "Admin/";
	ifstream file(admindir + "Users.txt");
	while (!file.eof())
	{
		getline(file, line);
		search = line.find("Username: ");
		if (search != string::npos)
		{
			search = line.find(": ");
			search += 2;
			cout << count++ << ") " << line.substr(search,line.length()) << endl;
		}
	}
}

void ComplainMenu(string& username)
{
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	string complain,reason;
	char op;
	system("cls");
	cout << "1. Report A User\n";
	cout << "\n2. Complain about a product\n";
	cout << "\n3. Request A New Item From Admin\n";
	cout << "\n4. Other\n";
	ofstream file(admindir + "Complains.txt", ios::out | ios::app);
	ofstream request(admindir + "Request.txt", ios::out | ios::app);
	cin >> op;
	
	cin.ignore();
	switch (op)
	{
		
	case '1':
		file << "By: " << username << endl;
		cout << "Name of the User: ";
		file << "Name of the User: ";
		getline(cin, complain);
		file << complain << endl;
		cout << "Reason: ";
		file << "Reason: ";
		getline(cin, reason);
		file << reason << endl << endl;
		cout << "\nThankyou for Letting Us Know!\n";
		break;
	case '2':
		file << "By: " << username << endl;
		cout << "Product Name: ";
		file << "Product Name: ";
		getline(cin, complain);
		file << complain << endl;
		cout << "Reason: ";
		file << "Reason: ";
		getline(cin, reason);
		file << reason << endl << endl;
		cout << "\nThankyou for Letting Us Know!\n";
		break;
	case '3':
		request << "By: " << username << endl;
		cout << "Product Name: ";
		request << "Product Name: ";
		getline(cin, complain);
		request << complain << endl << endl;
		cout << "\nThankyou for Letting Us Know!\n";
		break;
	case '4':
		file << "By: " << username << endl;
		cout << "Write Down Your Complain Down Here\n";
		file << "Complain: ";
		getline(cin, complain);
		file << complain << endl;
		break;
	default:
		cout << "Invalid Choice\n";
		break;
	}
	file.close();
	request.close();
}

void NewItem(string username)
{
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	string name, quantity, price, moni;
	string op, line;
	int search, search2, q;
	float p,money;
	cout << "Notice: 5% of the total money will be deducted from your account. 10% of the price multiplied by the quantity you introduce will be deduced from your account\n";
	cout << "Do you want to proceed? (Y/N)\t";
	getline(cin, op);
	if (op == "Y" || op == "y")
	{
		cout << "Product Name: ";
		getline(cin, name);
		while (true)
		{
			cout << "Price: $";
			getline(cin, price);
			cout << "Quantity: ";
			getline(cin, quantity);
			p = IsANumber(price, p);
			q = IsANumber(quantity, q);
			if (p == -1 || q == -1)
				cout << "\nInvalid Price or Quantity\n";
			else break;
		}
											//	DEDUCTING MONEY FROM USER

		ifstream user(makedir + username + "/" + username + ".txt");
		ofstream usertemp(makedir + username + "/usertemp.txt");
		bool invalid = false;
		int userid;
		while (!user.eof())
		{
			getline(user, line);
			if (search = line.find("ID: ") != string::npos)
			{
				search = line.find(": ");
				search += 2;
				userid = stoi(line.substr(search, line.length()));
			}
			if (search = line.find("Money: ") != string::npos)
			{
				search = line.find("$");
				search++;
				moni = line.substr(search, line.length());
				money = IsANumber(moni, money);
				if ((float(money) - (((p * float(q)) / 100) * 10) - (float(money) / 100) * 10) >= 0)
				usertemp << "Money: $" << money - (((p * float(q)) / 100) * 10) - ((float(money) / 100) * 5) << endl;
				else
				{
					invalid = true;
					usertemp << line << endl;
					cout << "\nYou dont have enough money\n";
					cout << "Money To be Deducted: " << (((p * float(q)) / 100) * 10) - ((float(money) / 100) * 5) << endl;
					cout << "Your Money: " << money << endl;
				}
			}
			else usertemp << line << endl;
		}
		user.close();
		usertemp.close();
		string userlocation = makedir + username + "/" + username + ".txt";
		string temp = makedir + username + "/usertemp.txt";
		remove(userlocation.c_str());
		rename(temp.c_str(), userlocation.c_str());

		if (!invalid)
		{
												// DEDUCTING MONEY FROM ADMIN USERS

			ifstream ausers(admindir + "Users.txt");
			ofstream atemp(admindir + "temp.txt");
			while (!ausers.eof())
			{
				getline(ausers, line);
				if (line == "Username: " + username)
				{
					do
					{
						if (search = line.find("Money: ") != string::npos)
						{
							atemp << "Money: " << float(money) - (((p * float(q)) / 100) * 10) - (float(money) / 100) * 10 << endl;
							break;
						}
						else atemp << line << endl;
						getline(ausers, line);
					} while (true);
				}
				else atemp << line << endl;
			}
			ausers.close();
			atemp.close();
			string adminusers = admindir + "Users.txt";
			temp = admindir + "temp.txt";
			remove(adminusers.c_str());
			rename(temp.c_str(), adminusers.c_str());

												// ADDING IN KANGRU LIST

			ifstream List(admindir + "KangruList.txt");
			int max = 0;
			int id;
			while (!List.eof())
			{
				getline(List, line);
				if (search = line.find("ID: ") != string::npos)
				{
					search = line.find("_");
					search++;
					id = stoi(line.substr(search, line.length()));
					if (id > max)
						max = id;
				}
			}
			List.close();
			ofstream KangruList(admindir + "KangruList.txt", ios::out | ios::app);
			KangruList << "ID: " << userid << "_" << ++max << endl;
			KangruList << "Owner: " << username << endl;
			KangruList << "Name: " << name << endl;
			KangruList << "Price: $" << p << endl;
			KangruList << "Quantity: " << quantity << endl;
			KangruList << "Discount: N/A\n\n";
			KangruList.close();
			cout << "Money Left: " << float(money) - (((p * float(q)) / 100) * 10) - ((float(money) / 100) * 5) << endl;
			cout << "Product Added!\n";
		}
	}
}

int IsANumber(string s, int &n)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) > 57 || s.at(i) < 48)
			return -1;
	}
	n = stoi(s);
	return n;
}

float IsANumber(string &s, float& n)
{
	bool invalid = false;
	int dot = 0;
	int search;
	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) == 46)
			dot++;
		else if ((s.at(i) > 57 || s.at(i) < 48) && s.at(i) != 46)
			invalid = true;
		if (dot > 1)
			invalid = true;
	}
	int num, divider;
	if (!invalid)
	{
		search = s.find(".");
		if (search != string::npos)
		{
			n = stoi(s.substr(0, search));
			divider = num = stoi(s.substr(search + 1, s.length()));
			while (divider > 1)
				divider /= 10;
			n += divider;
			
		}
		else
		{
			num = stoi(s);
			n = num;
		}
	}
	else return - 1;
	return n;
}

void SellerMode(string username)
{
	bool invalid;
	string line, choice, newprice, quantity;
	int search;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	do
	{
		invalid = false;
		cout << "Type ID To Select: ";
		getline(cin, choice);
		for (int i = 0; i < choice.length(); i++)
			if (!invalid)
			{
				if ((int(choice.at(i)) == 95))
				{
					invalid = false;
				}
				else if (int(choice.at(i)) > 57 || int(choice.at(i)) < 48)
				{
					cout << "Invalid ID\n";
					invalid = true;
				}
			}
	} while (invalid);
	invalid = false;
	ifstream List(makedir + username + "/List.txt");
	while (!List.eof())
	{
		getline(List, line);
		if (line == "ID: " + choice)
		{
			do
			{
				search = line.find("Price: ");
				if (search != string::npos)
				{
					search = line.find(": ");
					search += 3;
					cout << "Old Price: $" << line.substr(search, line.length());
					do
					{
						invalid = false;
						cout << "\nNew Price: $";
						int dotcount = 0;
						getline(cin, newprice);
						for (int i = 0; i < newprice.length(); i++)
							if (!invalid)
							{
								if (int(newprice.at(i)) == 46)
								{
									if (!dotcount)
										invalid = false;
									else invalid = true;
									dotcount++;
								}
								if (int(newprice.at(i)) > 57 || int(newprice.at(i)) < 48 || dotcount > 1)
								{
									cout << "Invalid Price\n";
									invalid = true;
								}
							}
					} while (invalid);
					getline(List, line);
					int quan;
					if (search != string::npos)
					{
						search = line.find(": ");
						search += 2;
						quan = stoi(line.substr(search, line.length()));
						cout << line << endl;
						do
						{
							invalid = false;
							cout << "\nQuantity you want to put on List: ";
							getline(cin, quantity);
							for (int i = 0; i < quantity.length(); i++)
								if (!invalid)
									if (int(quantity.at(i)) > 57 || int(quantity.at(i)) < 48)
									{
										cout << "Invalid Quantity\n";
										invalid = true;
									}
						} while (invalid);
						int Quantity = stoi(quantity);
						if (Quantity > quan)
						{
							cout << "You don't Have Enough\n";
						}
						else if (Quantity == 0);
						else if (Quantity <= quan)
						{
							ofstream file(admindir + "KangruList.txt", ios::out | ios::app);
							ofstream tList(makedir + username + "/temp.txt");
							List.close();
							List.open(makedir + username + "/List.txt");
							while (!List.eof())
							{
								getline(List, line);
								if (line == "ID: " + choice)
								{
									do
									{

										if (search = line.find("Price: ") != string::npos)
										{
											file << "Price: $" << newprice << endl;
											tList << line << endl;
										}
										else if (search = line.find("Quantity: ") != string::npos)
										{
											file << "Quantity: " << quantity << endl;
											tList << "Quantity: " << quan - Quantity << endl;
										}
										else
										{
											file << line << endl;
											tList << line << endl;
										}
										getline(List, line);
									} while (search = line.find("ID: ") == string::npos && !List.eof());
									tList << line << endl;
								}
								else tList << line << endl;
							}
							List.close();
							tList.close();
							file.close();
							string listlocation = makedir + username + "/List.txt";
							string tempList = makedir + username + "/temp.txt";
							remove(listlocation.c_str());
							rename(tempList.c_str(), listlocation.c_str());
						}
					}
				}
				getline(List, line);
			} while (search = line.find("ID: ") && !List.eof());
		}
	}
}

void Checkout(string username)
{
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	int search, ownercount, search2, pcount, qcount;
	float mymoney;
	string line;
	char op;
	float moneyrequired = TotalMoneyRequired(username);
	if (moneyrequired != -1)
	{
										//	TAKING OWNER ID'S, PRICES AND QUANTITIES

		int ownersize = 5, quansize = 5, pricesize = 5;
		ownercount = pcount = qcount = 0;
		int* ownerid = new int[ownersize];
		float* oprice = new float[pricesize];
		int* oquan = new int[quansize];
		string price;
		ifstream cart(makedir + username + "/Cart.txt");
		while (!cart.eof())
		{
			getline(cart, line);

			search = line.find("ID: ");
			if (search != string::npos)
			{
				search = line.find(": ");
				search += 2;
				search2 = line.find("_");
				*(ownerid + ownercount) = stoi(line.substr(search, search2));
				ownercount++;
				if (ownercount == ownersize)
					SizeIncrease(ownerid, ownersize);
			}
			search = line.find("Price: ");
			if (search != string::npos)
			{
				search = line.find("$");
				search++;
				price = line.substr(search, line.length());
				*(oprice + pcount) = IsANumber(price, *(oprice + pcount));
				pcount++;
				if (pcount == pricesize)
					SizeIncrease(oprice, pricesize);
			}
			search = line.find("Quantity: ");
			if (search != string::npos)
			{
				search = line.find(": ");
				search += 2;
				*(oquan + qcount) = stoi(line.substr(search, line.length()));
				qcount++;
				if (qcount == quansize)
					SizeIncrease(oquan, quansize);
			}

			cout << line << endl;
		}
		cart.close();
		for (int i = 0; i < ownercount; i++)
		{
			cout << "Owner ID: " << *(ownerid + i) << endl;
			cout << "Price: " << *(oprice + i) << endl;
			cout << "Quantity: " << *(oquan + i) << endl;
		}
		cout << "\nNow getting users money\n";
		system("pause");
															//	GETTING USER'S MONEY

		ifstream user(makedir + username + "/" + username + ".txt");
		ofstream usertemp(makedir + username + "/temp.txt", ios::out);
		string moni;
		while (!user.eof())
		{
			getline(user, line);
			search = line.find("$");
			if (search != string::npos)
			{
				search++;
				moni = (line.substr(search, line.length()));
				mymoney = IsANumber(moni, mymoney);
				if (mymoney >= moneyrequired)
				{
					cout << "Money Required: " << moneyrequired << endl;
					cout << "\nMy Money: " << mymoney << endl;
					cout << "\nMoney After Purchase: " << mymoney - moneyrequired << endl;
					cout << "Do you want to make the purchase? (Y/N)\t";
					cin >> op;
					if (op == 'Y' || op == 'y')
						usertemp << "Money: $" << mymoney - moneyrequired << endl;
					else usertemp << line << endl;
				}
				else
				{
					op = 'N';
					cout << "Money Required: " << moneyrequired << endl;
					cout << "\nMy Money: " << mymoney << endl;
					cout << "\nMoney After Purchase: " << mymoney - moneyrequired << endl;
					cout << "\nNot Enough Money!\n";
					usertemp << line << endl;
				}
			}
			else usertemp << line << endl;
		}
		user.close();
		usertemp.close();
		string userlocation = makedir + username + "/" + username + ".txt";
		string usertemplocation = makedir + username + "/temp.txt";
		remove(userlocation.c_str());
		rename(usertemplocation.c_str(), userlocation.c_str());
		cout << "\nNow getting users money from admin users list\n";
		system("pause");
		bool done = false;
		if (mymoney >= moneyrequired && (op == 'y' || op == 'Y'))
		{
													//	GETTING USER'S MONEY FROM ADMIN
			int userid;
			ifstream usersinfo(admindir + "Users.txt");
			ofstream tempusersinfo(admindir + "userstemp.txt");
			while (!usersinfo.eof())
			{
				getline(usersinfo, line);
				
				if (search = line.find("ID: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					userid = stoi(line.substr(search, line.length()));
					tempusersinfo << line << endl;
				}
				else if (search = line.find("Username: " + username) != string::npos)
				{
					do
					{
						if (!done)
						{
							search = line.find("Money: ");
							if (search != string::npos)
							{
								tempusersinfo << "Money: $" << mymoney - moneyrequired << endl;
								done = true;
							}
							else tempusersinfo << line << endl;
						}
						else tempusersinfo << line << endl;
						getline(usersinfo, line);
					} while (!usersinfo.eof());
					tempusersinfo << line << endl;
				}
				else tempusersinfo << line << endl;

			}
			usersinfo.close();
			tempusersinfo.close();
			string adminusers = admindir + "Users.txt";
			string adminuserstemp = admindir + "userstemp.txt";
			remove(adminusers.c_str());
			rename(adminuserstemp.c_str(), adminusers.c_str());
			cout << "\nNow: add money to list\n";
			system("pause");

														//	ADDING ITEMS IN LIST
			int idsize = 5,idcount = 0,quans = 5,quanc = 0;
			int* quantity = new int[quans];
			string* IDs = new string[idsize];
			ofstream List(makedir + username + "/List.txt", ios::out | ios::app);
			ifstream Cart(makedir + username + "/Cart.txt");
			int pid;
			while (!Cart.eof())
			{
				getline(Cart, line);
				
				if (search = line.find("ID: ") != string::npos)
				{
					*(IDs + idcount) = line;
					idcount++;
					if (idcount == idsize)
						SizeIncrease(IDs, idsize);
					search = line.find("_");
					search++;
					pid = stoi(line.substr(search, line.length()));
					List << "ID: " << userid << "_" << pid << endl;
				}
				else if (search = line.find("Quantity: ") != string::npos)
				{
					search = line.find(": ");
					search += 2;
					*(quantity + quanc) = stoi(line.substr(search, line.length()));
					quanc++;
					if (quanc == quans)
						SizeIncrease(quantity, quans);
					List << line << endl;
				}
				else if (search = line.find("Owner: ") != string::npos)
					List << "Owner: " << username << endl;
				else List << line << endl;
			}
			Cart.close();
			List.close();
			cout << "Now removing items from kangru list\n";
			system("pause");
												//	REMOVING FROM KANGRU LIST

			ifstream Kangrulist(admindir + "KangruList.txt");
			ofstream Ktemp(admindir + "Ktemp.txt");
			int kmoney,q;
			bool changed = false;
			while (!Kangrulist.eof())
			{
				getline(Kangrulist, line);
				for (int i = 0; i < idcount; i++)
				{
					if (line == *(IDs + i))
					{
						do
						{
							search = line.find("Quantity: ");
							if (search != string::npos)
							{
								search = line.find(": ");
								search += 2;
								q = stoi(line.substr(search, line.length()));
								Ktemp << "Quantity: " << q - *(quantity + i) << endl;
							}
							else Ktemp << line << endl;
							getline(Kangrulist, line);
						} while (search = line.find("Discount: ") == string::npos && !Kangrulist.eof());
						break;
					}
				}
				Ktemp << line << endl;
			}
			Kangrulist.close();
			Ktemp.close();
			string Klocation = admindir + "KangruList.txt";
			string Ktempolocation = admindir + "Ktemp.txt";
			remove(Klocation.c_str());
			rename(Ktempolocation.c_str(), Klocation.c_str());
			cout << "\nNow giving money to owners\n";
			system("pause");
													//	GIVING MONEY TO THE OWNERS
			TransferMoney(ownerid, ownercount, oprice, oquan);

		}
	}
	else cout << "Cart is empty\n";
}

void TransferMoney(int* ownerid, int ownercount, float* oprice, int* oquan)
{
	float amoney;
	string line;
	int search;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	string moni;
	for (int i = 0; i < ownercount; i++)
	{
		if (*(ownerid + i) == 0)
		{
			ifstream Admin(admindir + "Admin.txt");
			ofstream Atemp(admindir + "Atemp.txt");
			while (!Admin.eof())
			{
				getline(Admin, line);
				search = line.find("Money: ");
				if (search != string::npos)
				{
					search = line.find("$");
					search++;
					moni = (line.substr(search, line.length()));
					amoney = IsANumber(moni, amoney);
					Atemp << "Money: $" << amoney + (*(oprice + i) * float((*(oquan + i)))) << endl;
				}
				else Atemp << line << endl;
			}
			Admin.close();
			Atemp.close();
			string locationadmin = admindir + "Admin.txt";
			string tempoadmin = admindir + "Atemp.txt";
			remove(locationadmin.c_str());
			rename(tempoadmin.c_str(), locationadmin.c_str());
		}
		else
		{
			//	ADDING MONEY IN ADMIN'S USERS LIST

			string userowner;
			int usermoney;
			bool found = false;
			ifstream Usersinfo(admindir + "Users.txt");
			ofstream tempousersinfo(admindir + "Utemp.txt");
			while (!Usersinfo.eof())
			{
				
				getline(Usersinfo, line);
				search = line.find("ID: " + *(ownerid + i));
				if (!found)
				{
					if (search != string::npos)
					{
						found = true;
						do
						{

							if (search = line.find("Username: ") != string::npos)
							{
								search = line.find(": ");
								search += 2;
								userowner = line.substr(search, line.length());
								tempousersinfo << line << endl;
							}
							else if (search = line.find("Money: ") != string::npos)
							{
								search = line.find("$");
								search++;
								moni = (line.substr(search, line.length()));
								usermoney = IsANumber(moni, usermoney);
								tempousersinfo << "Money: $" << usermoney + (*(oprice + i) * float((*(oquan + i)))) << endl;
							}
							else tempousersinfo << line << endl;
							getline(Usersinfo, line);
						} while (search = line.find("ID: ") == string::npos && !Usersinfo.eof());
						if (!Usersinfo.eof())
							tempousersinfo << line << endl;
					}
					else tempousersinfo << line << endl;
				}
				else tempousersinfo << line << endl;

			}
			Usersinfo.close();
			tempousersinfo.close();
			string ulocation = admindir + "Users.txt";
			remove(ulocation.c_str());
			string tempouser = admindir + "Utemp.txt";
			rename(tempouser.c_str(), ulocation.c_str());

										//	ADDING MONEY IN PERSONAL USER ID'S

			ifstream personaluser(makedir + userowner + "/" + userowner + ".txt");
			ofstream ptemp(makedir + userowner + "/temp.txt");
			while (!personaluser.eof())
			{
				getline(personaluser, line);
				search = line.find("Money: ");
				if (search != string::npos)
				{
					search = line.find("$");
					search++;
					ptemp << "Money: $" << usermoney + (*(oprice + i) * float((*(oquan + i)))) << endl;
				}
				else ptemp << line << endl;
			}
			personaluser.close();
			ptemp.close();
			string puser = makedir + userowner + "/" + userowner + ".txt";
			string ptempo = makedir + userowner + "/temp.txt";
			remove(puser.c_str());
			rename(ptempo.c_str(), puser.c_str());
		}
	}
}

void SizeIncrease(string*& items, int& size)
{
	string* temp = new string[size * 2];
	for (int i = 0; i < size; i++)
		temp[i] = items[i];
	items = temp;
	size *= 2;
}

void SizeIncrease(int*& items, int& size)
{
	int* temp = new int[size * 2];
	for (int i = 0; i < size; i++)
		temp[i] = items[i];
	items = temp;
	size *= 2;
}

void SizeIncrease(float*& items, int& size)
{
	float* temp = new float[size * 2];
	for (int i = 0; i < size; i++)
		temp[i] = items[i];
	items = temp;
	size *= 2;
}

float TotalMoneyRequired(string username)
{
	string line,moni;
	float money = 0, totalmoney = 0;
	int search, quantity = 0;
	string dir = Filename();
	string makedir = dir + "Data/";
	ifstream cart(makedir + username + "/Cart.txt");
	bool invalid = false;
	getline(cart, line);
	if (line.length() == 0 || line == "\0")
	{
		cout << "\nThere is nothing in the cart\n";
		invalid = true;
	}
	if (!invalid)
	{
		while (!cart.eof())
		{
			getline(cart, line);
			if (search = line.find("Quantity: ") != string::npos)
			{
				search = line.find(": ");
				search += 2;
				quantity = stoi(line.substr(search, line.length()));
			}
			if (search = line.find("Price: ") != string::npos)
			{
				search = line.find(": ");
				search += 3;
				moni = (line.substr(search, line.length()));
				money = IsANumber(moni, money);
			}
			if (quantity && money)
			{
				totalmoney += money * float(quantity);
				money = quantity = 0;
			}

		}
		return totalmoney;
	}
	return -1;
}

void Signout(string username)
{
	cout << "Signing Out will remove anything and everything in Cart\n";
	cout << "Are you sure? (y/n)\t";
	char op;
	cin >> op;
	if (op == 'y' || op == 'Y')
	{
		RemoveEverything(username);
		cout << "Signing out\n";
		system("pause");
		exit(1);
	}
}

void RemoveFromCart(string username)
{
	int choose, count = 0;
	string line;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	ifstream cart(makedir + username + "/Cart.txt");
	system("cls");
	while (!cart.eof())
	{
		getline(cart, line);
		cout << line << endl;
	}
	cart.close();
	cout << "\n\nType the ID number of the item you want to remove: ";
	string choice;
	bool invalid = false;
	getline(cin, choice);
	for (int i = 0; i < choice.length(); i++)
		if (!invalid)
			if (choice.at(i) > 57 || choice.at(i) < 48)
			{
				cout << "Invalid ID\n";
				invalid = true;
			}
	if (!invalid)
	{
		cart.open(makedir + username + "/Cart.txt");
		bool found = false;
		getline(cart, line);
		if (line.length() == 0 || line == "\0")
		{
			cout << "There is nothing in the cart\n";
			invalid = true;
		}
		else if (line == "ID: " + choice)
			found = true;
		if (!invalid)
			while (!cart.eof())
			{
				getline(cart, line);
				if (!found)
					count++;
				cout << "Line Number: " << count << endl;
				cout << line << endl;
				if (line == ("ID: " + choice))
					found = true;
			}
		system("pause");
		cart.close();
		if (found)
		{
			int i = 0;
			int search;
			ofstream temp(makedir + username + "/temp.txt");
			cart.open(makedir + username + "/Cart.txt");
			while (!cart.eof())
			{
				getline(cart, line);
				i++;
				if (i == count + 1)
				{
					do
					{
						getline(cart, line);
					} while ((search = line.find("ID: ")) == string::npos && !cart.eof());
					temp << line << endl;
				}
				else if (i == count);
				else temp << line << endl;
			}
			cart.close();
			temp.close();
			string cartlocation = makedir + username + "/Cart.txt";
			string templocation = makedir + username + "/temp.txt";
			remove(cartlocation.c_str());
			rename(templocation.c_str(), cartlocation.c_str());
		}
		else
		{
			cout << "\nItem Not Found\n";
		}
	}
	else cout << endl;

}

void RemoveEverything(string username)
{
	string dir = Filename();
	string makedir = dir + "Data/";
	string cart = makedir + username + "/Cart.txt";
	remove(cart.c_str());
}

void ChooseByID(string& username)
{
	string line, listline;
	int search;
	int quantity;
	int count = 0, counter = 0;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	string id;
	bool found = false;
	cout << "\nEnter ID To Add Item To The Cart: ";
	getline(cin, id);
	system("cls");
	int quan;
	ifstream file(admindir + "KangruList.txt");
	while (!file.eof())
	{
		getline(file, listline);
		if (listline == "ID: " + id)
		{
			found = true;
			do
			{
				search = listline.find("Quantity: ");
				if (search != string::npos)
				{
					search = listline.find(": ");
					search += 2;
					quan = stoi(listline.substr(search, listline.length()));
				}
				cout << listline << endl;
				getline(file, listline);

			} while ((search = listline.find("ID: ")) == string::npos && !file.eof());
			break;
		}
	}
	file.close();
	if (found)
	{
		found = false;

		cout << "How many?\t";
		cin >> quantity;
		if (quan >= quantity)
		{
			ifstream cart(makedir + username + "/Cart.txt");
			bool nothing = false;
			getline(cart, line);
			if (line.length() == 0 || line == "\0")
				nothing = true;
			if (line == "ID: " + id)
				counter++;
			cart.close();
			if (nothing)
			{
				ofstream Cart(makedir + username + "/Cart.txt");
				file.open(admindir + "KangruList.txt");
				while (!file.eof())
				{
					getline(file, listline);
					if (listline == "ID: " + id)
					{
						do
						{
							search = listline.find("Quantity: ");
							if (search != string::npos)
							{
								Cart << "Quantity: " << quantity << endl;
							}
							else Cart << listline << endl;
							getline(file, listline);
						} while ((search = listline.find("ID: ") == string::npos) && !file.eof());
						Cart.close();
						break;

					}
				}
			}
			else
			{
				if (!counter)
				{
					ofstream Cart(makedir + username + "/Cart.txt", ios::out | ios::app);
					file.open(admindir + "KangruList.txt");
					while (!file.eof())
					{
						getline(file, listline);
						if (listline == "ID: " + id)
						{
							do
							{
								search = listline.find("Quantity: ");
								if (search != string::npos)
								{
									Cart << "Quantity: " << quantity << endl;
								}
								else Cart << listline << endl;
								getline(file, listline);
							} while ((search = listline.find("ID: ") == string::npos));
							Cart.close();
							break;

						}
					}
				}
				else
				{
					counter = 0;
					ifstream CART(makedir + username + "/Cart.txt");
					ofstream tempcart(makedir + username + "/temp.txt");
					while (!CART.eof())
					{
						getline(CART, line);
						search = line.find("ID: " + id);
						if (search != string::npos)
						{
							tempcart << line << endl;
							while (!CART.eof())
							{
								getline(CART, line);
								if (!counter)
								{
									search = line.find("Quantity: ");
									if (search != string::npos)
									{
										counter++;
										search = line.find(": ");
										search += 2;
										int amount = stoi(line.substr(search, line.length()));
										if (amount + quantity <= quan)
											tempcart << "Quantity: " << amount + quantity << endl;
										else
										{
											cout << "Exceeding the quantity available\n";
											tempcart << line << endl;
										}
									}
									else tempcart << line << endl;
								}
								else tempcart << line << endl;

							}
						}
						else tempcart << line << endl;
					}
					CART.close();
					tempcart.close();
					string crt = makedir + username + "/Cart.txt";
					string tmp = makedir + username + "/temp.txt";
					remove(crt.c_str());
					rename(tmp.c_str(), crt.c_str());
				}
			}
		}
		else cout << "Not Enough\n";
		file.close();
		counter = 0;
	}
	else cout << "\nItem not found!\n";
	cin.ignore();
}

bool Checkifexists(string username, string find)
{
	string line, listline;
	int search;
	int count = 0;
	bool found = false;
	string dir = Filename();
	string makedir = dir + "Data/";
	string admindir = dir + "Admin/";
	ifstream seecart(makedir + username + "/Cart.txt");
	ofstream tempcart(makedir + username + "/temp.txt");
	getline(seecart, line);
	if (line.length() == 0 || line == "\0")
		return false;
	while (!seecart.eof())
	{
		getline(seecart, line);
		if (line == "Name: " + find)
		{
			found = true;
			while (!seecart.eof())
			{
				search = line.find("Quantity: ");
				if (search != string::npos)
				{
					search = line.find(": ");
					search += 2;
					int quantity = stoi(line.substr(search, line.length()));
					quantity++;
					tempcart << "Quantity: " << quantity << endl;
					ifstream file(admindir + "KangruList.txt");
					ofstream temp(admindir + "temp.txt");
					while (!file.eof())
					{
						getline(file, listline);
						if (listline == "Name: " + find)
						{
							while (!file.eof())
							{
								if (count == 0)
								{
									search = listline.find("Quantity: ");
									if (search != string::npos)
									{
										search = listline.find(": ");
										search += 2;
										int quantity = stoi(listline.substr(search, listline.length()));
										quantity--;
										temp << "Quantity: " << quantity << endl;
										count++;
									}
									else temp << listline << endl;
								}
								else temp << listline << endl;
								getline(file, listline);
							}
							file.close();
							temp.close();
						}
						else temp << listline << endl;
					}

					string listname = admindir + "KangruList.txt";
					remove(listname.c_str());
					string tempname = admindir + "temp.txt";
					rename(tempname.c_str(), listname.c_str());

				}
				else tempcart << line << endl;
				getline(seecart, line);
			}

		}
		else tempcart << line << endl;
	}
	seecart.close();
	tempcart.close();
	string cartname = makedir + username + "/Cart.txt";
	remove(cartname.c_str());
	string tempcartname = makedir + username + "/temp.txt";
	rename(tempcartname.c_str(), cartname.c_str());
	return found;
}

void Seecart(string username)
{
	string line;
	string dir = "D:/Softwares/Visual Studio Projects/C++/Project/Data/";
	ifstream seecart(dir + username + "/Cart.txt");
	getline(seecart, line);
	if (line.length() == 0 || line == "\0")
		cout << "There is nothing in the cart\n";
	else
	{
		cout << line << endl;

		while (!seecart.eof())
		{
			getline(seecart, line);
			cout << line << endl;
		}
	}
}

void NewMemberMessageGenerator()
{
	srand(time(0));
	int random = (rand() % 5) + 1;
	switch (random)
	{
	case 1:
		cout << "\nWe are delighted to have you among us. On behalf of all the members and the management, ";
		cout << "we would like to extend our warmest welcome and good wishes!\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	case 2:
		cout << "\nWelcome to Kangru! We are thrilled to have you. ";
		cout << "You’re going to be a valuable asset to our company and we can’t wait to see all that you accomplish.\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	case 3:
		cout << "\nThe entire team of Kangru is thrilled to welcome you on board. ";
		cout << "We hope you’ll do some amazing works here!\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	case 4:
		cout << "\nA warm welcome and lots of good wishes on becoming part of our growing team. ";
		cout << "Congratulations on behalf of all the members. We are all happy and excited about ";
		cout << "your inputs and contribution to our company.\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	case 5:
		cout << "\nWe just heard that our company got an awesome new customer, and guess what? That's you. Welcome aboard!\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	default:
		cout << "Welcome to Kangru!\n";
		cout << "\nAs a welcome gift, we give you $1500. Spend wisely :)\n";
		break;
	}
}

bool SearchP(string& find, char op, string& owner, int& id, int& quan)
{
	string admindir = "D:/Softwares/Visual Studio Projects/C++/Project/Admin/";
	string line, sub;
	int search;
	bool found = false;
	ifstream file(admindir + "KangruList.txt");
	while (!file.eof())
	{
		getline(file, line);
		if (op == '1')
		{
			if (!found)
			{
				search = line.find("ID: ");
				if (search != string::npos)
				{
					search = line.find(": ");
					search += 2;
					id = stoi(line.substr(search, line.length()));
				}
				search = line.find("Owner: ");
				if (search != string::npos)
				{
					search = line.find(": ");
					search += 2;
					owner = line.substr(search, line.length());
				}
			}
			search = line.find("Name: ");
			if (search != string::npos)
			{
				if (line == ("Name: " + find))
				{
					found = true;
					do
					{
						search = line.find("Quantity: ");
						if (search != string::npos)
						{
							search = line.find(": ");
							search += 2;
							quan = stoi(line.substr(search, line.length()));
						}
						cout << line << endl;
						getline(file, line);
					} while ((search = line.find("ID: ") == string::npos) && (!file.eof()));
				}
			}
		}
		else if (op == '2')
		{
			search = line.find("ID: ");
			if (search != string::npos)
			{
				search = line.find(": ");
				search += 2;
				id = stoi(line.substr(search, line.length()));
			}
			search = line.find("Owner: ");
			if (search != string::npos)
			{
				search = line.find(": ");
				search += 2;
				owner = line.substr(search, line.length());
			}
			search = line.find("Owner: ");
			if (search != string::npos)
			{
				if (line == ("Owner: " + find))
				{
					found = true;
					cout << endl;
					do
					{
						search = line.find("Quantity: ");
						if (search != string::npos)
						{
							search = line.find(": ");
							search += 2;
							quan = stoi(line.substr(search, line.length()));
						}
						cout << line << endl;
						getline(file, line);
					} while ((search = line.find("ID: ") == string::npos) && (!file.eof()));
				}
			}
		}
	}
	file.close();
	return found;
}

char* stringtochar(string& name, char* ch)
{
	for (int i = 0; i < strlen(ch); i++)
	{
		if (i == name.length())
			ch[i] = NULL;
		else
			ch[i] = name.at(i);
	}
	return ch;
}

string Filename()
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