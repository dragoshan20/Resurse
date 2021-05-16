#pragma once
#include "RepositoryFile.h"

class RepoFileCSV : public RepoFile {
public:
	RepoFileCSV(ValidatorResurse*);
	RepoFileCSV(string filename, ValidatorResurse*);
	~RepoFileCSV();
	void loadFromFile();
	void saveToFile();
};