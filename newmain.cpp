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
    

    cout << "Vítá vás program Rezervace Pokojů" << endl;

	cout << "------SEZNAM POKOJŮ--------" <<  endl;

// otevření souboru pro cteni
    ifstream read_stream("pokoje.csv");

    if(read_stream.fail()) {
        cout << "Soubor pokoje.csv nelze otevřít" <<endl;
        exit(1);
    }
    

    cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(15) << setfill(separator)  << "Číslo pokoje" <<  right << setw(15) << setfill(separator) << "Kapacita " << right << setw(15) << setfill(separator) << "Cena" << endl;
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










		
    cout << "Pro  Vyhledávač napište v " << endl;
    cout << "Pro  Rezervace napište r " << endl;
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


                         cout << "-------VYHLEDÁVANí-------" <<  endl;

                         cout << "-- Zadej maximaln� cenu: ";
                         cin >> hledej_cena;
                         cout << "-- Zadej kapacitu (počet osob): ";
                         cin >> hledej_kapacita;
                         cout << " -- Zadej požadovaný den (dd.mm.rrrr postupně s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;
                         
                         
                         
                        
                         
                         
                        

                         // otevreni pro ctení
                         ifstream pokoje_hled("pokoje.csv");

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(10) << setfill(separator)  << "��slo pokoje" <<  right << setw(10) << setfill(separator) << "Kapacita " << right << setw(10) << setfill(separator) << "Cena" << endl;
                                 while(getline(pokoje_hled, radek2)) {
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                         istringstream iss2(radek2);
                                        if (!(iss2 >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                        if(cena <= hledej_cena and kapacita >= hledej_kapacita) {
                            //nactení rezervací
                                             ifstream rezervace_dostupnost ("rezervace_data.csv", ios::in);
                                             getline(rezervace_dostupnost, line);
                                                 int por_id, mm, dd, rrrr;
                                                 istringstream iss(line);
                                                 if(!(iss >> id >> dd >> mm >> rrrr)) {break;}
                                                 if(id == por_id and dd == datum_d and mm == datum_m and rrrr == datum_r) {   
                                                     cout << left << id << " " << "tento pokoj obsazen" << endl;
                                                     iss.clear();
                                                 }
                                                 else
                                                 cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(10) << setfill(separator)  << cislo_pokoje <<  right << setw(10) << setfill(separator) << kapacita << right << setw(10) << setfill(separator) << cena << "K�" << endl;
                                                 iss.clear();
                                             
                                        rezervace_dostupnost.close(); }
                                        }
                         
                                 pokoje_hled.close();
                                 
                              cout << "pokud chceš hledat znovu napiš v " << endl;
                              cout << "pro pokračovaní v rezervaci r " << endl;
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
         
         rezerv:
			 cout << "-------REZERVACE-------" <<  endl;

			 cout << "Zadejte ID m�stnosti: ";
			 cin >> rez_id;
                         
                          cout << " -- Zadej datum  (dd.mm.rr postupn�): "; // Opravit napsat na jeden ��dek je to shit 
			 cin >> datum_d >> datum_m >> datum_r;
                         
                     //otevreni cteni
                         ifstream rezervace_dostupnost("rezervace_data.csv", ios::in);
                         if(rezervace_dostupnost.fail()) {
                             cout << "soubor nelze otevrít" << endl;
                             exit(1);
                         }
                         while(getline(rezervace_dostupnost, line)){
                             istringstream iss3(line);
                             int id, dd, mm, rrrr;
                             if(!(iss3 >> id >> dd >> mm >> rrrr)){break;}
                             if(id == rez_id and dd == datum_d and mm == datum_m and rrrr == datum_r){
                                 cout << "tento pokoje je na toto datum obsazen zvolte jiné datum" << endl;
                                 iss3.clear();
                                 goto rezerv;
                             }
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
			 rezervace << "<p>" << "Vaše rezervace " << "</p>" << endl;
			 rezervace << "<p>" << "ID místnosti: " << id << endl;
			 rezervace << "<p>" << "Patro: "<< patro << "</p>" << endl;
			 rezervace << "<p>" << "Konečna cena: " << cena << "Kč" << "</p>" << endl;                    
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

			cout << "Rezervace vytvořena" << endl;
                        iss.clear();
                                        }
                                   }	
    }
    
	return 0;
}

/// fce
char overeni_flow(char flow) {
    if(flow != 'v' and flow != 'r') {
        cout << "Zadali jste Špatně" << endl;
        cin >> flow;
        return(flow);
    }
    else return(flow);
};

