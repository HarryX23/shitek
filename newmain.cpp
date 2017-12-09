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


using namespace std;

char overeni_flow(char);
int overení_den_proti_mesici(int, int); //overení jestli má mesíc 30 nebo 31 a jestli je datum správně
bool overeni_rok(); ///rozmezí 1800 až 2200 let našeho letopočtu
bool overeni_mesíc(); // rozmenzí 1 až 12
bool overeni_kapacita(); // rozmezí 1 až 100
bool overeni_cena(); //rozmezi 1 až 30 mil.
bool overeni_id(); // 


int main() {
    string radek;
    char flow;
    const char separator    = ' ';
    
    

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
// Ukončení  čtení	
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
                        string radek;
                        string line;

                        // 		VYHLEDÁVANÍ

                         cout << "-------VYHLEDÁVANí-------" <<  endl;

                         cout << "-- Zadej maximalní cenu: ";
                         cin >> hledej_cena;
                         cout << "-- Zadej kapacitu (počet osob): ";
                         cin >> hledej_kapacita;
                         cout << " -- Zadej požadovaný den (dd.mm.rrrr postupně s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;
                      
                        //tady začíná problém

     // otevreni pro ctení
                         ifstream pokoje_hled("pokoje.csv");
                         if(pokoje_hled.fail()) {
                             cout << "soubor 'pokoje.csv' nelze otevrít" << endl;
                             exit(1);
                         }

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(10) << setfill(separator)  << "��slo pokoje" <<  right << setw(10) << setfill(separator) << "Kapacita " << right << setw(10) << setfill(separator) << "Cena" << endl;
                                 while(getline(pokoje_hled, radek)) {
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                         istringstream iss2(radek);
                                        if (!(iss2 >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                        if(cena <= hledej_cena and overeni_kapacita(kapacita) >= hledej_kapacita) {
        //nactení rezervací
                                             ifstream rezervace_dostupnost ("rezervace_data.csv", ios::in);
                                             if(rezervace_dostupnost.fail()) {
                                                 cout << "soubor 'rezervace_data.csv' nelze otevrít" << endl;
                                                 exit(1);
                                             }
                                             while(getline(rezervace_dostupnost, line)) {
                                                 int por_id, mm, dd, rrrr;
                                                 istringstream iss(line);
                                                 if(!(iss >> id >> dd >> mm >> rrrr)) {break;}
                                                 if(id == por_id and dd == overeni_den_proti_mesici(datum_m, datum_d) and mm == overeni_mesic(datum_m) and rrrr == overeni_rok(datum_r)) {   
                                                     cout << left << id << " " << "tento pokoj obsazen" << endl;
                                                     iss2.clear();
                                                 }
                                                 else
                                                 cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(10) << setfill(separator)  << cislo_pokoje <<  right << setw(10) << setfill(separator) << kapacita << right << setw(10) << setfill(separator) << cena << "K�" << endl;
                                                 iss2.clear();
                                             }
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
 
    //tady končí muj problém
    
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
                         
                          cout << " -- Zadej datum  (dd.mm.rr postupn�): "; 
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
                             if(id == rez_id and dd == overeni_den_proti_mesici(datum_m, datum_d) and mm == overeni_mesic(datum_m) and rrrr == overeni_rok(datum_r)){
                                 cout << "tento pokoje je na toto datum obsazen zvolte jiné datum" << endl;
                                 iss3.clear();
                                 goto rezerv;
                             }
                         }
                         
                           
                         rezervace_dostupnost.close();
                         
                         
                         ifstream pokoje_info("pokoje.csv");
                         if(pokoje_info.fail()) {
                             cout << "soubor 'pokoje.csv' nelze otevřít" << endl;
                             exit(1);
                         }
                                   while(getline(pokoje_info, line)){ 
                                        istringstream iss(line);
                                        if(!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) {break;}
                                        if(id == rez_id) {
                                                        
			 cout << "<p>" << "Vaše rezervace " << "</p>" << endl;
			 cout << "<p>" << "ID místnosti: " << id << endl;
			 cout << "<p>" << "Patro: "<< patro << "</p>" << endl;
			 cout << "<p>" << "Konečna cena: " << cena << "Kč" << "</p>" << endl;                    
			 cout << "<p>" << "Datum: " << datum_d << "/" << datum_m << "/" << datum_r << "</p>" << endl;
                
			 	 pokoje_info.close();
 			ofstream rezervace_data ("rezervace_data.csv", ios::out | ios::app);
                        if(rezervace_data.fail()) {
                            cout << "Do souboru nelze 'rezervace_data.csv' zapsat" <<endl;
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
int overeni_den_proti_mesici(int mesic, int den) {
        if(mesic <= 12 and mesic >= 1) {
         cout << "spatne zadaný mesíc 1-12 zadejte znovu" << endl;
            cin >> mesic;
        }
        if(!(den <= 31 and den >= 1)) {
            cout << "zadal jsi den spatně zadej znova" << endl;
            cin >> den;       
        }
        if(!((den == 31) and (mesic == 1 or 3 or 5 or 7 or 8 or 10 or 12))) {
                cout << "zadaný mesic nemá 31 dnů zadejte den znova" << endl;
            cin >> den;
        } 
        return(den);
};

int overeni_rok(int rok) {
    if(!(rok <= 2200 and rok >= 1800)) {
      
    return(rok);
};

int overeni_mesic(int mesic) {
    if(mesic <= 12 and mesic >= 1) {
        
        }
    return(mesic);
};

int overeni_kapacita(int kapacita) {
  if(!(kapacita <= 100 and kapacita >= 1)){
    
  }  
  return(kapacita);
};

int overeni_cena(int cena) {
    if(!(cena <= 30000000 nad cena >= 1)) {
       
    }
    return(cena);
};


