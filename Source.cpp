/*8. Magazine. Se considera nr_mag magazine. Fiecare are un numar de produse. Sa se verifice care magazin are cele mai multe produse exclusive 
(nu apar decât în magazinul respectiv). Cititi dintr-un fisier în câte un vector de std::string produsele pentru fiecare magazin. Afisati în final
magazinul cu cele mai multe produse exclusive si care sunt aceste produse. (1.5p)*/

#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>

void readData(std::vector<std::vector<std::string>>& vectorMagazine, int& nrMagazine)
{
	std::ifstream fin("date.in");
	std::string stringAjutor;
	int dimensiuneMagazin;

	fin >> nrMagazine;
	vectorMagazine.resize(nrMagazine);

	for (int index = 0; index < vectorMagazine.size(); index++)
	{
		fin >> dimensiuneMagazin;
		vectorMagazine[index].resize(dimensiuneMagazin);

		for (int indexMagazin = 0; indexMagazin < vectorMagazine[index].size(); indexMagazin++)
		{
			fin >> stringAjutor;

			if (stringAjutor != "")
			{
				vectorMagazine[index][indexMagazin] = stringAjutor;
			}

			else
			{
				return;
			}
		}
	}
}

void putToSet(std::vector<std::unordered_set<std::string>>& setMagazine, std::vector<std::vector<std::string>> vectorMagazine)
{
	setMagazine.resize(vectorMagazine.size());

	for (int index = 0; index < vectorMagazine.size(); index++)
	{
		for (int indexMagazin = 0; indexMagazin < vectorMagazine[index].size(); indexMagazin++)
		{
			setMagazine[index].insert(vectorMagazine[index][indexMagazin]);
		}
	}
}

void mostExclusiveProducts(std::vector<std::unordered_set<std::string>>setMagazine)
{
	int magazinulExclusivist;

	std::vector<int>mostExclusiveMagazin;
	mostExclusiveMagazin.resize(setMagazine.size());

	std::unordered_set<std::string>produseMagazinExclusivist;

	for (int index = 0; index < setMagazine.size(); index++)
	{
		for (auto produs : setMagazine[index])
		{
			for (int indexMagazin = 0; indexMagazin < setMagazine.size(); indexMagazin++)
			{
				for (auto produs2 : setMagazine[indexMagazin])
				{
					if (index != indexMagazin)
					{
						if (produs == produs2)
						{
							mostExclusiveMagazin[index]++;
						}
					}
				}
			}
		}
	}

	int min = 999999999;
	for (int index = 0; index < mostExclusiveMagazin.size(); index++)
	{
		if (mostExclusiveMagazin[index] < min)
		{
			min = mostExclusiveMagazin[index];
			magazinulExclusivist = index;
		}
	}

	std::cout << "Magazinul cu cele mai multe produse care nu se gasesc in celalalte magazine este magazinul : " << magazinulExclusivist << std::endl;
	int ok;

	for (auto produs : setMagazine[magazinulExclusivist])
	{
		ok = 0;
		for (int indexMagazin = 0; indexMagazin < setMagazine.size(); indexMagazin++)
		{
			for (auto produs2 : setMagazine[indexMagazin])
			{
				if (magazinulExclusivist != indexMagazin)
				{
					if (produs == produs2)
					{
						ok = 1;
					}
				}
			}
		}

		if (ok == 0)
		{
			produseMagazinExclusivist.insert(produs);
		}
	}

	for (auto produs : produseMagazinExclusivist)
	{
		std::cout << produs << ' ';
	}

	std::cout << std::endl;
}

void printMagazine(std::vector<std::vector<std::string>>vectorMagazine)
{
	for (int index = 0; index < vectorMagazine.size(); index++)
	{
		for (int indexMagazin = 0; indexMagazin < vectorMagazine[index].size(); indexMagazin++)
		{
			std::cout << vectorMagazine[index][indexMagazin] << ' ';
		}
		std::cout << std::endl;
	}
}

void printSet(std::vector<std::unordered_set<std::string>>setMagazine)
{
	for (int index = 0; index < setMagazine.size(); index++)
	{
		for (auto produs : setMagazine[index])
		{
			std::cout << produs << ' ';
		}

		std::cout << std::endl;
	}
}

int main()
{
	int nrMagazine;
	std::vector<std::vector<std::string>>vectorMagazine;
	std::vector<std::unordered_set<std::string>>setMagazine;

	readData(vectorMagazine, nrMagazine);
	//printMagazine(vectorMagazine);

	std::cout << "Se printeaza produsele din magazine : " << std::endl;

	putToSet(setMagazine, vectorMagazine);

	printSet(setMagazine);

	std::cout << std::endl;

	mostExclusiveProducts(setMagazine);

	return 0;
}