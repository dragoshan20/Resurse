#pragma once
#include "Resurse.h"
#include "ValidatorResurse.h"
#include "ValidatorExceptii.h"
#include <vector>

using namespace std;

class RepoFile
{
protected:
	vector<Resurse*> elemente;
	string filename;
	ValidatorResurse* validator;
public:
	RepoFile(ValidatorResurse*);
	RepoFile(string filename, ValidatorResurse*);
	~RepoFile();
	void setFileName(string filename);

	vector<Resurse*> getAll();
	int getSize();
	Resurse* getElement(int);
	void add(Resurse*);
	void update(Resurse* vechi, Resurse* Nou);
	void del(Resurse*);
	void emptyRepo();
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;
};