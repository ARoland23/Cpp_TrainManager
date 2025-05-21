#ifndef DINTOMB_GUARD
#define DINTOMB_GUARD


#include <iostream>
#include <fstream>
#include "memtrace.h"
#include "string5.h"
#include "vonat.h"
#include "jegy.h"



template <typename T>
class DinTomb {
	T* tomb;
	int db;
public:
	DinTomb(int d=1):db(d) { tomb = new T[db]; }
///masolo ctor
	DinTomb(const DinTomb& dt)
	{
		this->db = dt.db;
		this->tomb = new T[db];

		for (int i = 0; i < db; i++)
		{
			this->tomb[i] = dt.tomb[i];
		}
	}
	~DinTomb() { delete[] tomb; }

	T& operator[](int i) { if (i >= db || i < 0) throw std::runtime_error("tul indexeles");  return tomb[i]; }

	int getDb() { return db; }
	void setDb(int d) {  db=d; }
	T* getTomb() { return tomb; }
	void setTomb(T* t) { tomb = t; }
};


///Megnoveli a referenciakent kapott DinTombot
///@param  DinTomb referencia
template<typename T>
void novel(DinTomb<T>& dtomb)
{
		int dbUj = dtomb.getDb() + 1;	//uj meret
		T* pt = new T[dbUj];
		for (int i = 0; i < dtomb.getDb(); i++)
		{
			pt[i] = dtomb[i];
		}
		dtomb.setDb(dbUj);
		delete[] dtomb.getTomb();
		dtomb.setTomb(pt);
}

template<>										// T=jegy
class DinTomb<Jegy> {
	Jegy* tomb;
	int db;
public:
	DinTomb(int d = 1):db(d) { tomb = new Jegy[db]; }
	~DinTomb() { delete[] tomb; }

///@param 1. jarat szama 
///@param 2. kocsi szama
///@param 3. hely szama
///@return van-e ilyen foglalas feljegyezve a tombben
	bool foglalt(int jarat, int kocsi, int hely)
	{
		for (int i = 0; i < this->getDb(); i++)
		{
			if (tomb[i].getHely() == hely && tomb[i].getVonat().getJarat() == jarat && tomb[i].getVonat().getKocsi() == kocsi) //szerepelt-e ez a kombinacio mar
				return true;
		}
		return false;
	}

///osszegzi a tombben levo jegyek arat
///@return osszes jegy ara.
	int sum() 
	{
		int sum = 0;
		for (int i = 0; i < this->db; i++)
		{
			sum = sum + tomb[i];
		}
		return sum;
	}

	Jegy& operator[](int i) { return tomb[i]; if (i >= db || i < 0) throw std::runtime_error("tul indexeles"); }
	int getDb() { return db; }
	void setDb(int d) { db = d; }
	Jegy* getTomb() { return tomb; }
	void setTomb(Jegy* j) { tomb = j; }

	///kiirja a megadott nevvel rendelkezo fajlba a tomb tartalmat;
	///tomb eleme egy sor
	///@param fajl neve 
	void kiir(String name)
	{
		std::ofstream file(name.c_str());

		if (!file)
		{
			std::cout << "nem sikerult megnyitni a file-t!\n";
			throw std::runtime_error("nem sikerult megnyitni!");
		}

		file << db << "\t";
		for (int i = 0; i < db; i++)
		{
			file << tomb[i].getVonat().getJarat() << "\t" << tomb[i].getVonat().getKocsi() << "\t" << tomb[i].getHely() << "\t"
				 << tomb[i].getIdoI() << "\t" << tomb[i].getIdoE() << "\t"
				 << tomb[i].getAllomasI() << "\t" << tomb[i].getAllomasE() << "\t"
				 << tomb[i].getAr() << "\t";
		}

		file.close();
	}


	///beolvassa a megadott nevvel rendelkezo fajlbol a tomb tartalmat;
	///tomb eleme egy sor
	///@param fajl neve 
	void beolvas(String name)
	{
		std::ifstream file(name.c_str());

		if (!file)
		{
			std::cout << "nem sikerult megnyitni a file-t!\n";
			throw std::runtime_error("nem sikerult megnyitni a file-t");
		}


		int jt, ksz, hely, ar, darab;
		String ido1, ido2, all1, all2;

		if (!(file >> darab))					//meret beolvasasa
		{
			throw std::runtime_error("nem jo meret");
		}
		this->db = darab;
		

		Jegy* utomb = new Jegy[db];

		for (int i = 0; i < db; i++)
		{
			file >> jt >> ksz >> hely
				 >> ido1 >> ido2
				 >> all1 >> all2
				 >> ar;

			Jegy j (Vonat(jt, ksz), hely, ido1, ido2, all1, all2, ar);
			utomb[i] = j;
		}

		delete[] this->tomb;
		this->tomb = utomb;

		file.close();
	}

};

template<>											// T=Vonat
class DinTomb<Vonat> {
	Vonat* tomb;
	int db;
public:
	DinTomb(int d = 1):db(d) { tomb = new Vonat[db]; }
	~DinTomb() { delete[] tomb; }				

///@param  jarat szama 
///@return az adott jarat indexe. Ha nincs ilyen jarat akkor negativ.
	int benneVan(int jt)
	{
		for (int i = 0; i < db; i++)
		{
			if (this->tomb[i].getJarat() == jt)
				return i;
		}
		return -1; 
	}


	Vonat& operator[](int i) { return tomb[i]; if (i >= db || i < 0) throw std::runtime_error("tul indexeles");
	}
	int getDb() { return db; }
	void setDb(int d) { db = d; }
	Vonat* getTomb() { return tomb; }
	void setTomb(Vonat* v) { tomb = v; }

///kiirja a megadott nevvel rendelkezo fajlba a tomb tartalmat;
///tomb eleme egy sor
///@param fajl neve 
	void kiir(String name)
	{
		std::ofstream file(name.c_str());

		if (!file)
		{
			std::cout << "nem sikerult megnyitni a file-t!\n";
			throw std::runtime_error("nem sikerult megnyitni a file-t");
		}

		file << db << "\t";
		for (int i = 0; i < db; i++)
		{
			file << tomb[i].getJarat() << "\t" << tomb[i].getKocsi() << "\t";
		}

		file.close();
	}


///beolvassa a megadott nevvel rendelkezo fajlbol a tomb tartalmat;
///tomb eleme egy sor
///@param fajl neve 
//@return sikeres volt-e a muvelet. Ha nem sikeres kivetelt dob.
	void beolvas(String name) 
	{ 
		std::ifstream file(name.c_str());

		if (!file)
		{
			std::cout << "nem sikerult megnyitni a file-t!\n";
			throw std::runtime_error("nem sikerult megnyitni a file-t");
		}


		int jt, ksz, darab;

			if ( !(file >> darab) )					//meret beolvasasa
				throw std::runtime_error("nem jo meret");
		this->db = darab;

		Vonat* utomb = new Vonat[db];
		for (int i = 0; i < db; i++)
		{
			file >> jt  >> ksz;

			Vonat v(jt, ksz);
			utomb[i] = v;
		}

		delete[] this->tomb;
		this->tomb = utomb;

		file.close();
	}

};

#endif // !DINTOMB_GUARD
