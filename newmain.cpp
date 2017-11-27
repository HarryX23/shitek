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

bool overeni_flow(char);
int overeni_datum_d(int);
int overeni_datum_m(int);
int overeni_datum_r(int);

int main() {
    string radek;
    char flow;
    const char separator    = ' ';
    int global_patro;
    int global_cislo_pokoje;
    int global_kapacita;
    int global_id;
    int global_cena;

    cout << "Vítá vás program Rezervace Privat" << endl;

	cout << "------SEZNAM POKOJŮ--------" <<  endl;

// otevření souboru pro cteni
ifstream pokoje ("pokoje.csv");	

    cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(30) << setfill(separator)  << "Číslo pokoje" <<  right << setw(15) << setfill(separator) << "Kapacita " << right << setw(15) << setfill(separator) << "Cena" << endl;
    while (getline(pokoje, radek)) {
        //lokalní prom.
        int id;
        int patro;
        int cislo_pokoje;
        int kapacita;
        int cena;

            istringstream iss(radek);
            if (!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
            cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(30) << setfill(separator)  << cislo_pokoje <<  right << setw(15) << setfill(separator) << kapacita << right << setw(15) << setfill(separator) << cena << "K�" << endl;
    }
    
pokoje.close();
// Ukončení  čteni
		
    cout << "Pro  Vyhledávač napište v " << endl;
    cout << "Pro  Rezervace napište r " << endl;
    cin >> flow;		


	if(overeni_flow(flow) == true) {
          if(flow = 'v') {
               
                        int hledej_cena;
                        int hledej_kapacita;
                        int datum_d;
                        int datum_m;
                        int datum_r;
                        string radek;


                        // 		VYHLEDÁVANÍ


                         cout << "-------VYHLEDÁVANí-------" <<  endl;

                         cout << "-- Zadej maximaln� cenu: ";
                         cin >> hledej_cena;
                         cout << "-- Zadej kapacitu (po�et osob): ";
                         cin >> hledej_kapacita;
                         cout << " -- Zadej po�adovan� den (dd.mm.rr postupn� s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;


                         // otevreni pro ctení
                         ifstream pokoje_hled("pokoje.csv");

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(10) << setfill(separator)  << "��slo pokoje" <<  right << setw(10) << setfill(separator) << "Kapacita " << right << setw(10) << setfill(separator) << "Cena" << endl;
                                 while(getline(pokoje_hled, radek)) {
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                         istringstream iss(radek);
                                        if (!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                            if(cena <= hledej_cena and kapacita >= hledej_kapacita) {
                                                        cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(10) << setfill(separator)  << cislo_pokoje <<  right << setw(10) << setfill(separator) << kapacita << right << setw(10) << setfill(separator) << cena << "K�" << endl;
                                                  }
                                 }
                                 pokoje_hled.close();
                }	
        }
    if(overeni_flow(flow) == true) {	
        if (flow == 'r') {
					 int id;
					 int patro;
					 int cislo_pokoje;
					 int kapacita;
					 int cena;
					 int rez_id;
					 int datum_d;
					 int datum_m;
					 int datum_r;
					 string radek;

			 cout << "-------REZERVACE-------" <<  endl;

			 cout << "Zadejte ID m�stnosti: ";
			 cin >> rez_id;

			 	 //otevreni souboru s mistnostmi kvuli info;
			 ifstream pokoje_info ("pokoje,csv");
			 	 while(getline(pokoje_info, radek)) {

			 		 istringstream iss(radek);
			 		 if(!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
			 		 	 if(!(rez_id != id)) {
			 		 		 global_patro = patro;
			 		 		 global_cislo_pokoje = cislo_pokoje;
			 		 		 global_kapacita = kapacita;
			 		 		 global_cena = cena;
			 		 	 }

			 	 }

			 	 pokoje_info.close();

			 cout << " -- Zadej datum  (dd.mm.rr postupn�): "; // Opravit napsat na jeden ��dek je to shit :)
			 cin >> datum_d >> datum_m >> datum_r;

			 // vystup do HTML
			 ofstream rezervace ("rezervace.html");

			 rezervace << "<!DOCTYPE html><html><head></head><body>";
			 rezervace << "<p>" << "Va�e rezervace " << "</p>" << endl;
			 rezervace << "<p>" << "ID m�stnosti: " << rez_id << endl;
			 rezervace << "<p>" << "Patro: "<< global_patro << "</p>" << endl;
			 rezervace << "<p>" << "Kone�n� cena: " << global_cena << "K�" << "</p>" << endl;
			 rezervace << "<p>" << "Datum: " << datum_d << "/" << datum_m << "/" << datum_r << "</p>" << endl;

			rezervace << "</body></html>";
			rezervace.close();

			ofstream rezervace_data ("rezervace_data.csv", ios::out | ios::app);
			rezervace_data << endl << rez_id << " " << datum_d << " " << datum_m << " " << datum_r << "\r\n";

			rezervace_data.close();

			cout << "Rezervace vytvo�ena" << endl;


	}
    }    
    
	return 0;
}

///fce///////
bool overeni_flow(char flow) {
    if(flow != 'v' and flow != 'v') {
        cout << "Zadali jste Špatně" << endl;
        return(false);
    }
    return(true);
};
int overeni_datum_d(int den) {
    if(den =< 0){
        return(den);
      }
    else if(den > 31){
            den = 31;
        return(den);
    }
}
