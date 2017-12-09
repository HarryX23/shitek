//============================================================================
// Name        : newmain.cpp
// Author      : Tomáš Jedlička
// Version     :
// Copyright   : Free 4 All
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <vector>

using namespace std;

char overeni_flow(char);


int main() {
    string radek;
    char flow;
    const char separator    = ' ';
    ofstream write_stream;


    cout << "Vita vas program rezervace mistnosti" << endl;

	cout << "------>>>>>SEZNAM POKOJU<<<<<--------" <<  endl;


    ifstream read_stream("pokoje.csv"); // otevření souboru pro cteni

    if(read_stream.fail()) {            //kontrola souboru
        cout << "Soubor nelze otevrit" <<endl;
        exit(1);
    }
    if(write_stream.fail()) {           //kontrola souboru
        cout << "Soubor nelze otevrit" <<endl;
        exit(1);
}

    cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(15) << setfill(separator)  << "Cislo pokoje" <<  right << setw(15) << setfill(separator) << "Kapacita " << right << setw(15) << setfill(separator) << "Cena" << endl;
    while (getline(read_stream, radek)) {
        //lokalní prom.
        int id;
        int patro;
        int cislo_pokoje;
        int kapacita;
        int cena;

            istringstream iss(radek);
            if (!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
            cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(15) << setfill(separator)  << cislo_pokoje <<  right << setw(15) << setfill(separator) << kapacita << right << setw(15) << setfill(separator) << cena << "Kč" << endl;
    }

read_stream.close();
// Ukončení  čteni
    cout << "Pro  vyhledavac napiste v " << endl;
    cout << "Pro  rezervaci napiste r " << endl;
    cin >> flow;

	if(overeni_flow(flow) == 'v')  {
            hledej:
                        int hledej_cena;
                        int hledej_kapacita;
                        int datum_d;
                        int datum_m;
                        int datum_r;
                        string radek2;
                        string line;


                        // 		VYHLEDÁVANÍ


                         cout << "-------VYHLEDAVANI-------" <<  endl;

                         cout << "-- Zadejte maximalni cenu: ";
                         cin >> hledej_cena;
                         if (cin.fail()) {
                            cout << "Spatne zadano, zadejte cislo" << endl;
                         }
                         cout << "-- Zadejte kapacitu (pocet osob): ";
                         cin >> hledej_kapacita;
                          if (cin.fail()) {
                            cout << "Spatne zadano, zadejte cislo" << endl;
                         }
                         cout << " -- Zadejte pozadovany den (dd mm rrrr postupne s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;

                            if(datum_d > 31 && datum_m > 12) {
                                    cout << "Spatne zadane datum" << endl;
                                    exit(1);
                            }









                         // otevreni pro ctení
                         ifstream pokoje_hled("pokoje.csv");

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(10) << setfill(separator)  << "Cislo pokoje" <<  right << setw(10) << setfill(separator) << "Kapacita " << right << setw(10) << setfill(separator) << "Cena" << endl;
                                 while(getline(pokoje_hled, radek2)) {
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                         istringstream iss2(radek2);
                                        if (!(iss2 >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                        if(cena <= hledej_cena and kapacita >= hledej_kapacita) {
                                             ifstream rezervace_dostupnost ("rezervace_data.csv", ios::in); //nactení souboru s rezervacemi
                                             while(getline(rezervace_dostupnost, line)) {
                                                 int mm, dd, rrrr;
                                                 istringstream iss(line);
                                                 if(!(iss >> id >> dd >> mm >> rrrr)) {break;}
                                                 if(dd == datum_d and mm == datum_m and rrrr == datum_r) {      //overeni obsazenosti
                                                     cout << left << id << "tento pokoj je obsazen" << endl;
                                                 }
                                                 else
                                                 cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(10) << setfill(separator)  << cislo_pokoje <<  right << setw(10) << setfill(separator) << kapacita << right << setw(10) << setfill(separator) << cena << "K�" << endl;
                                                 iss.clear();
                                             }
                                        rezervace_dostupnost.close(); }
                                        }

                                 pokoje_hled.close();

                              cout << "pokud chcete hledat znovu napiste v " << endl;
                              cout << "pro pokracovani v rezervaci r " << endl;
                              cin >> flow;
                              if(overeni_flow(flow) == 'v') {
                                  goto hledej;
                              }
        }



    // rezervace



    if(overeni_flow(flow) == 'r') {

         int rez_id;
         int datum_d;
         int datum_m;
         int datum_r;
         string line;
         int id, patro, cislo_pokoje, cena, kapacita;

			 cout << "-------REZERVACE-------" <<  endl;

			 cout << "Zadejte ID mistnosti: ";
			 cin >> rez_id;
			 if(cin.fail()){
                cout << "Spatne zadano" << endl;
			 }

                cout << " -- Zadej datum  (dd mm rr postupne s mezerou): "; // Opravit napsat na jeden ��dek je to shit
			 cin >> datum_d >> datum_m >> datum_r;

                        if(datum_d > 31 && datum_m > 12) {
                                    cout << "Spatne zadane datum" << endl;
                                    exit(1);
                            }


                     //otevreni cteni
                         ifstream rezervace_dostupnost("rezervace_data.csv", ios::in);
                         if(rezervace_dostupnost.fail()) {
                             cout << "soubor nelze otevrit" << endl;
                             exit(1);
                         }
                         while(getline(rezervace_dostupnost, line)){
                             istringstream iss3(line);
                         }


                         rezervace_dostupnost.close();


                         ifstream pokoje_info("pokoje.csv");
                         if(pokoje_info.fail()) {
                             cout << "soubor nelze otevřít" << endl;
                             exit(1);
                         }
                                   while(getline(pokoje_info, line)){
                                        istringstream iss(line);
                                        if(!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) {break;}
                                        if(id == rez_id) {

                   // vystup do HTML

			ofstream rezervace ("rezervace.html");


			 rezervace << "<!DOCTYPE html><html><head></head><body>";
			 rezervace << "<p>" << "Vase rezervace " << "</p>" << endl;
			 rezervace << "<p>" << "ID mistnosti: " << id << endl;
			 rezervace << "<p>" << "Patro: "<< patro << "</p>" << endl;
			 rezervace << "<p>" << "Konecna cena: " << cena << "Kc" << "</p>" << endl;
			 rezervace << "<p>" << "Datum: " << datum_d << "/" << datum_m << "/" << datum_r << "</p>" << endl;


			rezervace << "</body></html>";
			rezervace.close();


			 	 pokoje_info.close();


 			ofstream rezervace_data ("rezervace_data.csv", ios::out | ios::app);
                        if(rezervace_data.fail()) {
                            cout << "Do souboru nelze zapsat" <<endl;
                            exit(1);
                        }
			rezervace_data << rez_id << " " << datum_d << " " << datum_m << " " << datum_r << "\r\n";

			rezervace_data.close();

			cout << "Rezervace vytvorena" << endl;
                        iss.clear();
                                        }
                                   }
    }

	return 0;
}

/// fce
char overeni_flow(char flow) {
    if(flow != 'v' and flow != 'r') {
        cout << "Zadali jste spatně" << endl;
        cin >> flow;
        return(flow);
    }
    else return(flow);
};

