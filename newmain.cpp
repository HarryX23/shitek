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
bool overeni_den_proti_mesici(int, int); //overení jestli má mesíc 30 nebo 31 a jestli je datum správně
bool overeni_rok(int); ///rozmezí 1800 až 2200 let našeho letopočtu
bool overeni_mesic(int); // rozmenzí 1 až 12
bool overeni_kapacita(int); // rozmezí 1 až 100
bool overeni_cena(int); //rozmezi 1 až 30 mil.
bool overeni_id(int); //  rozmezí 1 až 100
int chyb_hlaska(string); // nový vstup 


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
    cout << "-----------------------------------------" << endl; 
    cout << "Pro  Vyhledávač napište v " << endl;
    cout << "Pro  Rezervace napište r " << endl;
    cout << "Pro export nejblížích rezervací dané místnosti napište e " << endl;
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
                         while(!(overeni_cena(hledej_cena))) {
                             string druh = "cena";
                             hledej_cena = chyb_hlaska(druh);
                         }
                         
                         cout << "-- Zadej kapacitu (počet osob): ";
                         cin >> hledej_kapacita;
                         while(!(overeni_kapacita(hledej_kapacita))) {
                             string druh = "kapacita";
                             hledej_kapacita = chyb_hlaska(druh);
                         }
                         
                         cout << " -- Zadej požadovaný den (dd.mm.rrrr postupně s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;
                         while(!(overeni_rok(datum_r))) {
                             string druh = "rok";
                             datum_r = chyb_hlaska(druh);
                         }
                         while(!(overeni_mesic(datum_m))) {
                             string druh = "mesic";
                             datum_m = chyb_hlaska(druh);
                         }
                         while(!(overeni_den_proti_mesici(datum_m, datum_d))) {
                             string druh = "den";
                             datum_d = chyb_hlaska(druh);
                         }
                         
                      
                        //tady začíná problém

     // otevreni pro ctení
                         ifstream pokoje_hled("pokoje.csv");
                         if(pokoje_hled.fail()) {
                             cout << "soubor 'pokoje.csv' nelze otevrít" << endl;
                             exit(1);
                         }

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(10) << setfill(separator)  << "Cislo pokoje" <<  right << setw(10) << setfill(separator) << "Kapacita " << right << setw(10) << setfill(separator) << "Cena" << endl;
                                 while(getline(pokoje_hled, radek)) {
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                         istringstream iss2(radek);
                                        if (!(iss2 >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                        if(cena <= hledej_cena and kapacita >= hledej_kapacita) {
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
                                                 if(!(id == por_id and dd == datum_d and mm == datum_m and rrrr == datum_r)) {   
                                                     cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(10) << setfill(separator)  << cislo_pokoje <<  right << setw(10) << setfill(separator) << kapacita << right << setw(10) << setfill(separator) << cena << "K�" << endl;
                                                     iss.clear();
                                                 }
                                                 
                                             }
                                        rezervace_dostupnost.close(); }
                                        }
                         
                                 pokoje_hled.close();
                              cout << "------------------------------------------" << endl;
                              cout << "pokud chceš hledat znovu napiš v " << endl;
                              cout << "pro pokračovaní v rezervaci r " << endl;
                              cout << "pro export rezervací dané mistnosti e " << endl;
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

			 cout << "Zadejte ID mistnosti: ";
			 cin >> rez_id;
                         while(!(overeni_id(rez_id))){
                             string druh = "id";
                             rez_id = chyb_hlaska(druh);
                         }
                         
                          cout << " -- Zadej datum  (dd.mm.rr postupně): "; 
			 cin >> datum_d >> datum_m >> datum_r;
                         while(!(overeni_rok(datum_r))) {
                             string druh = "rok";
                             datum_r = chyb_hlaska(druh);
                         }
                         while(!(overeni_mesic(datum_m))) {
                             string druh = "mesic";
                             datum_m = chyb_hlaska(druh);
                         }
                         while(!(overeni_den_proti_mesici(datum_m, datum_d))) {
                             string druh = "den";
                             datum_d = chyb_hlaska(druh);
                         }
                         
             
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
                             cout << "soubor 'pokoje.csv' nelze otevřít" << endl;
                             exit(1);
                         }
                                   while(getline(pokoje_info, line)){ 
                                        istringstream iss(line);
                                        if(!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) {break;}
                                        if(id == rez_id) {
                                                        
			 cout << "Vaše rezervace " << endl;
			 cout << "ID místnosti: " << id << endl;
			 cout << "Patro: "<< patro << endl;
                         cout << "Čislo pookoje. " << cislo_pokoje << endl;
			 cout << "Konečna cena: " << cena << "Kč" << endl;                    
			 cout << "Datum: " << datum_d << "/" << datum_m << "/" << datum_r << endl;
                
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
                              cout << "-------------------------------------" << endl;
                              cout << "pokud chceš rezervovat znovu napiš r " << endl;
                              cout << "pokud chceš hledat znovu napiš v " << endl;
                              cout << "pro export rezervací dané mistnosti e " << endl;
                              cin >> flow;
                              if(overeni_flow(flow) == 'r') {
                                  goto rezerv;
                              }
                              if(overeni_flow(flow) == 'v') {
                                  goto hledej;
                              }
    }
    
    
    //export do HTML
    
    if(overeni_flow(flow) == 'e') {
        string cesta;
        int get_id;
        string line;
        
        cout << "----------------------------" << endl;
        cout << "Export rezervací do HTML" << endl;
        cout << "zadejte umístění souboru(př. \"c:/cesta/nazev.html\"  ): ";
        cin >> cesta;
        cout << "Zadejte id místnosti: ";
        cin >> get_id;
        while(!(overeni_id(get_id))) {
            string druh = "id";
            get_id = chyb_hlaska(druh);
        }
        
        ifstream rezervace("rezervace_data.csv", ios::in);
        if(rezervace.fail()) {
            cout << "soubor 'rezervace_data.csv' nelze otevřít" << endl;
            exit(1);
        }
        
        ofstream html(cesta, ios::out);
        html << "<html><head><title>Rezervace místnosti ID: " << get_id << "</title></head><body>" << endl;
        html << "<p>Tabulka Rezervaci</p>" << endl;
        html << "<table>" << endl;
        html << "<tr><th><b>ID</b></th><th><b>Den</b></th><th><b>Mesic</b></th><th><b>Rok</b></th></tr>" << endl;
        
        while(getline(rezervace, line)) {
            int id, dd, mm, rrrr;
            istringstream iss(line);
            if(!(iss >> id >> dd >> mm >> rrrr)) {break;}
            if(id == get_id) {
                //export 
                html << "<tr><td>" << id << "</td><td>" << dd << "</td><td>" << mm << "</td><td>" << rrrr << "</td></tr>" << endl;
            }
            
        }   cout << "soubor uspesne vytvoren v: " << cesta << endl;
        
        html << "</table>" << endl;
        html << "</body></html>" << endl;
        html.close();
        
    }
    
	return 0;
}

/// fce
char overeni_flow(char flow) {
    if(flow != 'v' and flow != 'r' and flow != 'e') {
        cout << "Zadali jste Špatně" << endl;
        cin >> flow;
        return(flow);
    }
    else return(flow);
};
bool overeni_den_proti_mesici(int mesic, int den) {
        if(overeni_mesic(mesic)) {
            if(den <= 31 and den >= 1) {
                return(true);     
            }
            if((den == 31) and (mesic == 1 or 3 or 5 or 7 or 8 or 10 or 12)) {
                return(true);
            } 
            if((den > 28) and (mesic == 2)) {
                return(true);
            }
        
        return(false);
        }
};

bool overeni_rok(int rok) {
    if(rok <= 2200 and rok >= 1800) {
        return(true);
    }
    return(false);
};

bool overeni_mesic(int mesic) {
    if(mesic <= 12 and mesic >= 1) {
        return(true);
        }
    return(false);
};

bool overeni_kapacita(int kapacita) {
    if(kapacita <= 100 and kapacita >= 1){
        return(true);
    }  
    return(false);
};

bool overeni_cena(int cena) {
    if(cena <= 30000000 and cena >= 1) {
        return(true);
    }
    return(false);
};

bool overeni_id(int id) {
    if(id <= 100 and id >= 1){
        return(true);
    }
    return(false);
};

int chyb_hlaska(string druh) {
    int new_data;
    cout << "zadali jste spatne" << " " << druh << " " << "prosím zadejte znovu : ";
    cin >> new_data;
    return(new_data);
};    


