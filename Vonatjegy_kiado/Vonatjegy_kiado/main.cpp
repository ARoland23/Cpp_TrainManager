#include <iostream>
#include "dintomb.hpp"
#include "vonat.h"
#include "jegy.h"
#include "memtrace.h"
#include "gtest_lite.h"

#define Max_Kocsiszam 50
#define vonatFile "vonatok.txt"
#define jegyekFile "jegyek.txt"
#define AR 4500


//#define TESZT

//Vonat konstruktor tesztelese
void TEST1()
{
	Vonat v1;
	EXPECT_EQ(1, v1.getJarat());
	EXPECT_EQ(1, v1.getKocsi());
	Vonat v2(10, 10);
	EXPECT_EQ(10, v2.getJarat());
	EXPECT_EQ(10, v2.getKocsi());
}
//Vonat ertekado operator tesztelese
void TEST2()
{
	Vonat v1(50, 50);
	Vonat v2;
	v2 = v1;
	EXPECT_EQ(v2.getJarat(), v1.getJarat());
	EXPECT_EQ(v2.getKocsi(), v1.getKocsi());
}
//Jegy ctor tesztelese
void TEST3()
{
	Jegy j1;
	EXPECT_EQ(1, j1.getVonat().getJarat());
	EXPECT_EQ(1, j1.getVonat().getKocsi());
	EXPECT_STREQ("Default", j1.getAllomasI().c_str());
	EXPECT_STREQ("Default", j1.getIdoI().c_str());

	Jegy j2(Vonat(10, 10), 10, "asd", "asd", "asdasd", "asdasd", 10000);
	EXPECT_EQ(10, j2.getVonat().getJarat());
	EXPECT_EQ(10, j2.getVonat().getKocsi());
	EXPECT_STREQ("asd", j2.getIdoI().c_str());
	EXPECT_STREQ("asdasd", j2.getAllomasI().c_str());
	EXPECT_EQ(10000, j2.getAr());
}
//jegy ertekado operator tesztelese
void TEST4()
{
	Jegy j1(Vonat(10, 10), 10, "asd", "asd", "asdasd", "asdasd", 10000);
	Jegy j2;
	j2 = j1;

	EXPECT_EQ(j1.getVonat().getJarat(), j2.getVonat().getJarat());
	EXPECT_EQ(j1.getVonat().getKocsi(), j2.getVonat().getKocsi());
	EXPECT_STREQ(j1.getAllomasI().c_str(), j2.getAllomasI().c_str());
	EXPECT_STREQ(j1.getIdoI().c_str(), j2.getIdoI().c_str());
}
//osszeadas operator tesztelese
void TEST5()
{
	int szam = 10;
	Jegy j1(Vonat(10, 10), 10, "asd", "asd", "asdasd", "asdasd", 10);
	int sum = szam + j1;
	EXPECT_EQ(20, sum);
}
//setterek tesztelese
void TEST6()
{
	Jegy j1;
	Vonat v1;
	j1.setHely(10);
	EXPECT_EQ(10, j1.getHely());

	j1.setHely(100);
	EXPECT_NE(100, j1.getHely());

	j1.setHely(-1);
	EXPECT_NE(-1, j1.getHely());

	v1.setJarat(10);
	EXPECT_EQ(10, v1.getJarat());

	v1.setJarat(-10);
	EXPECT_NE(-10, v1.getJarat());

	v1.setKocsiSzam(10);
	EXPECT_EQ(10, v1.getKocsi());

	v1.setKocsiSzam(-10);
	EXPECT_NE(-10, v1.getKocsi());
}
//DinTomb tesztek
void TEST7()
{
	DinTomb<int> it(10);
	EXPECT_EQ(10, it.getDb());

	it[0] = 10;
	EXPECT_EQ(10, *it.getTomb());

	DinTomb<int> it2 = it;		//masolo ctor teszt
	EXPECT_EQ(it2[0], it[0]);

	EXPECT_ANY_THROW( it[100] );
}
//DinTomb<Vonat> tesztek
void TEST8()
{
	DinTomb<Vonat>vt(3);
	Vonat v1(10, 10);
	Vonat v2(20, 20);
	Vonat v3(30, 30);
	vt[0] = v1;
	vt[1] = v2;
	vt[2] = v3;

	EXPECT_EQ(0,vt.benneVan(10)); //intet ad vissza
	EXPECT_EQ(-1, vt.benneVan(100)); //-1 ha hamis
	novel(vt);
	EXPECT_EQ(4, vt.getDb());
}
//DinTomb<Jegy> tesztek
void TEST9()
{
	DinTomb<Jegy>jt(3);
	Jegy j1(Vonat(10, 10), 10, "15", "16", "ASD", "ASD", 5000);
	Jegy j2(Vonat(11, 11), 10, "15", "16", "ASD", "ASD", 5000);
	Jegy j3(Vonat(12, 12), 10, "15", "16", "ASD", "ASD", 5000);
	jt[0] = j1;
	jt[1] = j2;
	jt[2] = j3;

	EXPECT_EQ(15000, jt.sum());
	EXPECT_TRUE(jt.foglalt(10, 10, 10));
	EXPECT_TRUE(!jt.foglalt(15, 15, 15));
	novel(jt);
	EXPECT_EQ(4, jt.getDb());
}
//file muvelet tesztek
void TEST10()
{
	DinTomb<Jegy>jt;
	DinTomb<Vonat>vt;

	EXPECT_ANY_THROW(jt.beolvas("valami.txt")); //nem letezo file-t probal megnyitni
	EXPECT_ANY_THROW(vt.beolvas("valami.txt"));

	EXPECT_NO_THROW( jt.beolvas("tesztJegy.txt") ); // letezo file-t nyit meg
	EXPECT_NO_THROW( vt.beolvas("tesztVonat.txt") );

	//jol olvassa-e be
	EXPECT_EQ(4, jt.getDb());
	EXPECT_EQ(6, vt.getDb());
	EXPECT_STREQ("asd", jt[0].getAllomasI().c_str());
	EXPECT_STREQ("dsa", jt[0].getAllomasE().c_str());
	EXPECT_EQ(4500, jt[0].getAr());

	EXPECT_EQ(10, vt[0].getJarat());
	EXPECT_EQ(10, vt[0].getKocsi());
	EXPECT_EQ(20, vt[1].getJarat());
	EXPECT_EQ(20, vt[1].getKocsi());

	//sikerul-e kiirni
	EXPECT_NO_THROW(jt.kiir("tesztJegy.txt"));
	EXPECT_NO_THROW(vt.kiir("tesztVonat.txt"));
}


int main()
{	
/*Automatizált tesztek*/
	TEST1();
	TEST2();
	TEST3();
	TEST4();
	TEST5();
	TEST6();
	TEST7();
	TEST8();
	TEST9();
	TEST10();

#ifndef TESZT




/*A fõ program innen kezdõdik*/


	DinTomb<Vonat> vonatTomb;
	DinTomb<Jegy> jegyTomb;

	try
	{
		vonatTomb.beolvas(vonatFile);
	}
	catch (const std::runtime_error&)
	{
		std::cout << "nem megfelelo a Vonat file!";
		return 10;
	}
	try
	{
		jegyTomb.beolvas(jegyekFile);
	}
	catch (const std::runtime_error&)
	{
		std::cout << "nem megfelelo a Jegy file!";
		return 11;
	}

	int hely;
	int jt;
	int ksz;
	String all1;
	String all2;
	String ido1;
	String ido2;
	int idx;
	char choice = ' ';
	

	while (choice!='0')
	{
		std::cout << "--------------------------------------\n"
			<< "Mit kivan tenni?\n"
			<< "Uj jarat felvetele:		(1)\n"
			<< "Jegy vasarlasa:			(2)\n"
			<< "Jegyek osszegzese:		(3)\n"
			<< "Kilepes:			(0)\n"
			<< "vonat es jegy tombok kiirasa:		(9)\n"
			<< "--------------------------------------\n";
		std::cin.clear();
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case '1':
			system("cls");

			std::cout << "A jarat szama? : ";
			std::cin >> jt;
			if ( std::cin.fail() )
			{
				std::cin.clear();
				break;
			}

			std::cout << "Mennyi kocsit huz? : ";
			std::cin >> ksz;
			if (std::cin.fail())
			{
				std::cin.clear();
				break;
			}

			idx = vonatTomb.benneVan(jt);

			if (idx>=0)
			{
				std::cout << "Mar van ilyen jarat\n";
				break;
			}
			if (ksz > Max_Kocsiszam || ksz<=0)
			{
				std::cout << "A jaratot nem tudtuk letrehozni! Nem huzhat tobbet 50 kocsinal!\n";
				break;
			}
			std::cout <<  std::endl;
			try
			{
				novel(vonatTomb);
			}
			catch (const std::runtime_error&)
			{
				std::cout << "A jaratot nem tudtuk letrehozni!\n";
				break;
			}
			vonatTomb[vonatTomb.getDb() - 1].setJarat(jt);				//az utolso elemet modositjuk
			vonatTomb[vonatTomb.getDb()-1].setKocsiSzam(ksz);
			std::cout << "Jarat letrehozva!\n";
			break;
		case '2':
			system("cls");
			std::cout << "Melyik Jaraton?\n";
			std::cin >> jt;
			if (std::cin.fail())
			{
				std::cin.clear();
				break;
			}
			
			std::cout << "Melyik kocsiba?\n";
			std::cin >> ksz;
			if (std::cin.fail())
			{
				std::cin.clear();
				break;
			}

			idx = vonatTomb.benneVan(jt);

			if (idx<0)
			{
				std::cout << "sajnos nincs ilyen vonat a nyilvantartasban!";
				break;
			}
			if (vonatTomb[idx].getKocsi() < ksz || ksz>Max_Kocsiszam)
			{
				std::cout << "Nincs ennyi kocsija a vonatnak!";
				break;
			}

			std::cout << "Melyik ulesre?\n";
			std::cin >> hely;
			if (std::cin.fail())
			{
				std::cin.clear();
				break;
			}
			if ( jegyTomb.foglalt(jt,ksz,hely) )
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
			try
			{
				novel(jegyTomb);
			}
			catch (const std::runtime_error&)
			{
				std::cout << "A helyet nem tudtuk lefoglalni a szamodra!\n";
				break;
			}

			jegyTomb[jegyTomb.getDb() - 1].setVonat(Vonat(jt, ksz));		//az utolso elemet modositjuk
			jegyTomb[jegyTomb.getDb() - 1].setHely(hely);
			jegyTomb[jegyTomb.getDb() - 1].setAllomasI(all1);
			jegyTomb[jegyTomb.getDb() - 1].setAllomasE(all2);
			jegyTomb[jegyTomb.getDb() - 1].setIdoI(ido1);
			jegyTomb[jegyTomb.getDb() - 1].setIdoE(ido2);
			jegyTomb[jegyTomb.getDb() -1].setAr(AR);


			std::cout << "Jegy elmentve\n";
			break;
		case '3':
			system("cls");
			std::cout << "A jegyek osszerteke: " << jegyTomb.sum() << std::endl;
			break;
		case '9':
			system("cls");
			std::cout << "vonat Tomb:\n";
			for (int i = 0; i < vonatTomb.getDb(); i++)
			{
				std::cout << vonatTomb[i].getJarat() << " | " << vonatTomb[i].getKocsi()<<" ; ";
			}
			std::cout << std::endl;

			std::cout << "Jegy Tomb:\n";
			for (int i = 0; i < jegyTomb.getDb(); i++)
			{
				std::cout << "indulas: " << jegyTomb[i].getAllomasI() << "\terkezes: " << jegyTomb[i].getAllomasE() << std::endl;
				std::cout << "indulas: " << jegyTomb[i].getIdoI() << "\terkezes: " << jegyTomb[i].getIdoE() << std::endl;
				std::cout << "hely: " << jegyTomb[i].getHely() << "\tjarat: " << jegyTomb[i].getVonat().getJarat() << "\tkocsiszam:" << jegyTomb[i].getVonat().getKocsi() << std::endl;
				std::cout << "ar: " << jegyTomb[i].getAr() << std::endl;

				std::cout << "--------------------------\n";
			}
			break;
		case '0':
			std::cout << "A program most kilep!";
			break;
		default:
			std::cout << "nem megfelelo opciot adtal meg!\n";
			break;
		}
	}

	try
	{
		vonatTomb.kiir(vonatFile);
	}
	catch (const std::runtime_error&)
	{
		std::cout << "Hiba a vonat file kiirasanal!";
		return 20;
	}
	try
	{
		jegyTomb.kiir(jegyekFile);
	}
	catch (const std::runtime_error&)
	{
		std::cout << "Hiba a jegy file kiirasanal!";
		return 21;
	}

#endif // !TESZT


}