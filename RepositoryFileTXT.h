#pragma once
#include "RepositoryFile.h"

class RepoFileTXT : public RepoFile {
public:
	RepoFileTXT(ValidatorResurse*);
	RepoFileTXT(string filename, ValidatorResurse*);
	~RepoFileTXT();
	void loadFromFile();
	void saveToFile();
};