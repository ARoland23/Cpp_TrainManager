#include <iostream>
#include "dintomb.hpp"
#include "vonat.h"
#include "jegy.h"
#include "memtrace.h"
int main()
{	

	DinTomb<Vonat> vonatTomb(10);
	DinTomb<Jegy> jegyTomb(10);

	bool sikeres = false;
	char choice = ' ';
	int ar=4500;
	int hely;
	int jt;
	int ksz;
	String all1;
	String all2;
	String ido1;
	String ido2;

	/*DinTomb<int> intTomb1(4);
	intTomb1[0] = 1; intTomb1[1] = 1; intTomb1[2] = 2; intTomb1[3] = 2;
	DinTomb<int> intTomb2 = intTomb1;
	std::cout << "tomb1:	tomb2:\n";
	for (size_t i = 0; i < 4; i++)
	{
		std::cout << intTomb1[i] << "	"<<intTomb2[i]<<"\n";
	}
	std::cout<<intTomb1.getDb();*/


	while (choice!='0')
	{
		std::cout << "--------------------------------------\n"
			<< "Mit kivan tenni?\n"
			<< "Uj jarat felvetele:		(1)\n"
			<< "Jegy vasarlasa:			(2)\n"
			<< "Jegyek osszegzese:		(3)\n"
			<< "Kilepes:			(0)\n"
			<< "--------------------------------------\n";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		
		case '1':
			system("cls");
			std::cout << "A jarat szama? : ";
			std::cin >> jt;
			if (!vonatTomb.benneVan(jt))
			{
				std::cout << "Mar van ilyen vonat a nyilvantartasban!\n";
				break;
			}
			vonatTomb[0].setJarat(jt);
			std::cout << "Mennyi kocsit huz? : ";
			std::cin >> ksz;

			if (ksz > 50)
			{
				std::cout << "Nem huzhat tobbet 50 kocsinal!\n";
				break;
			}
			std::cout <<  std::endl;
			vonatTomb[0].setKocsiSzam(jt);
			//letreHoz(vonatTomb);
			std::cout << "Jarat letrehozva!\n";
			break;

		case '2':
			system("cls");
			std::cout << "Melyik Jaraton?\n";
			std::cin >> jt;
			std::cout << "Melyik melyik kocsiba?\n";
			std::cin >> ksz;
			std::cout << "Melyik helyre?\n";
			std::cin >> hely;
			if (!jegyTomb.foglalt(jt,ksz,hely))
			{
				std::cout << "Sajnos ez a hely mar foglalt!\n";
				break;
			}
			std::cout << "Melyik allomasrol?\n";
			std::cin >> all1;
			std::cout << "Melyik allomasra?\n";
			std::cin >> all2;
			std::cout << "Mikortol?\n";
			std::cin >> ido1;
			std::cout << "Meddig?\n";
			std::cin >> ido2;

			sikeres=elad(jegyTomb);
			std::cout << "A helyet lefoglaltuk a szamodra!\n";
			break;
		case '3':
			system("cls");
			std::cout << "A jegyek osszerteke: "<<jegyTomb.sum()*ar<<std::endl;
			break;
		default:
			break;
		}
	}



}