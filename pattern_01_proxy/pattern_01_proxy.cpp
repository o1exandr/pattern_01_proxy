/*
Завдання 1.

Створити класи Клієнт, Банк, Рахунок(номер рахунку, пароль, сума). 
У класі Рахунок визначити методи отримання інформації про кошти на рахунку та зняття з рахунку певної суми.
Створити клас Банкомат, який надаватиме сервіси зняття грошей та інформації по рахунку певному клієнту. 
Використати патерн Proxy.

*/


#include "stdafx.h"
#include <iostream> 
#include <string>

using namespace std;

class Client
{
private:
	string nameClient;
public:

	string getNameClient()
	{
		return nameClient;
	}

	void setNameClient(string name)
	{
		nameClient = name;
	}
};

class Bank
{
private:
	string nameBank;
public:

	string getNameBank()
	{
		return nameBank;
	}

	void setNameBank(string name)
	{
		nameBank = name;
	}
};

class Account : public Client, public Bank
{
private:
	int id;
	int pass;
	int money;
public:
	
	Account(int id, int pass, int money, string nameClient, string nameBank)
	{
		setId(id);
		setPass(pass);
		setMoney(money);
		setNameClient(nameClient);
		setNameBank(nameBank);
	}

	Account()
	{}

	int getId()
	{
		return id;
	}

	void setId(int Id)
	{
		id = Id;
	}

	int getPass()
	{
		return pass;
	}

	void setPass(int p)
	{
		pass = p;
	}

	int getMoney()
	{
		return money;
	}

	void setMoney(int m)
	{
		money = m;
	}

	void showMoney(int id, int pass)
	{
		if (getId() == id && getPass() == pass)
			cout << "Bank:\t\t" << Bank::getNameBank() << "\nClient:\t\t" << Client::getNameClient() << "\nBalance:\t" << getMoney() << "\n\t-----\n";
		else
			cout << "\nWrong password\n";
	}

	void giveMoney(int id, int pass, int money)
	{
		if (getId() == id && getPass() == pass)
		{
			if (money <= getMoney())
			{
				cout << "\nTake you money:\t" << money << endl;
				setMoney(getMoney() - money);
			}
			else
				cout << "Not enough money on your account\n";
			showMoney(id, pass);
		}
		else
			cout << "\nWrong password\n";
	}
};

class ATM : public Account
{
private:
	Account * account;
public:

	ATM(Account acc)
	{
		account = new Account(acc.getId(), acc.getPass(), acc.getMoney(), acc.getNameClient(), acc.getNameBank());
	}

	void showMoney(int id, int pass)
	{
		account->showMoney(id, pass);
	}

	void giveMoney(int id, int pass, int money)
	{
		account->giveMoney(id, pass, money);
	}

	virtual ~ATM() 
	{
		delete account;
	}
};


int main()
{
	Account a(123456, 1111, 100000, "Mykola Mykolayovych", "Global Bank");

	ATM * proxy = new ATM(a);

	proxy->showMoney(123456, 1111);
	proxy->giveMoney(123456, 1111, 5000);

	delete proxy;


	cout << endl;
	system("pause");
	return 0;

}






