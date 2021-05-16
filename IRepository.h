
#ifndef IRepository_HEADER
#define IRepository_HEADER

#include "User.h"
#include "ValidatorUser.h"
#include "ValidatorExceptii.h"
#include <vector>
#include <algorithm>
#include <fstream>

class RepoUser
{
private:
	ValidatorUser* validator;
	vector<User*> users;
	string filename;
public:
	RepoUser(ValidatorUser* v)
	{
		validator = v;
	};
	RepoUser(ValidatorUser* v, string fileName)
	{
		validator = v;
		filename = fileName;
	};
	~RepoUser()
	{
		for (unsigned int i = 0; i < users.size(); i++)
			delete[] users[i];
	};

	int getSize()
	{
		//loadFromFile();
		return users.size();
	};

	vector<User*> getAll()
	{
		loadFromFile();
		return users;
	};

	void add(User* u)
	{
		if (validator->validare(u) == 0)
		{
			users.push_back(u);
			saveToFile();
		}
		else
			throw ValidatorExceptii(validator->toString().c_str());
	};

	void update(User* oldUser, User* newUser)
	{
		//loadFromFile();
		bool gasit = false;
		if (this->validator->validare(newUser) == 0)
		{
			for (unsigned int i = 0; i < this->users.size(); i++)
			{
				if (*(this->users[i]) == *oldUser)
				{
					gasit = true;
					delete this->users[i];
					this->users[i] = newUser->clone();
					this->saveToFile();
					return;
				}
			}
		}
		else throw ValidatorExceptii(validator->toString().c_str());
		if (gasit == false)
		{
			throw ValidatorExceptii("User inexistent!");
		}
	};

	void del(User* u)
	{
		//loadFromFile();
		bool gasit = false;
		{
			for (unsigned int i = 0; i < this->users.size(); i++)
			{
				if (**(this->users.begin() + i) == *u)
				{
					gasit = true;
					delete this->users[i];
					this->users.erase(this->users.begin() + i);
					this->saveToFile();
					return;
				}
			}
		}
		if (gasit == false)
		{
			throw ValidatorExceptii("Utilizator inexistent! ");
		}
	}

	void emptyRepo()
	{
		for (int i = 0; i < this->getSize(); i++)
		{
			delete this->users[i];
		}
		this->users.clear();
	};

	void saveToFile()
	{
		ofstream f(this->filename);
		if (f.is_open())
		{
			for (User* u : this->users)
			{
				f << u->toStringDelimiter(" ") << endl;
			}
		}
	};

	void loadFromFile()
	{
		ifstream f(this->filename);
		if (f.is_open())
		{
			this->emptyRepo();
			string linie;
			string delim = " ";
			while (getline(f, linie))
			{
				int pos = linie.find(delim);
				string username = linie.substr(0, pos);
				linie = linie.erase(0, pos + 1);

				pos = linie.find(delim);
				string pasword = linie.substr(0, pos);
				linie = linie.erase(0, pos + 1);
				User* u = new User(username, pasword);
				try
				{
					this->add(u);
				}
				catch (ValidatorExceptii ex)
				{
					throw ex;
				}


			}
		}
	}

	int findUser(User* u)
	{
		this->loadFromFile();
		for (User* crt : users)
			if (*crt == *u)
				return 1;
		return -1;
	}
};
#endif