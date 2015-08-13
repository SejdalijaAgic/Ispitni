#include <iostream>
using namespace std;

struct Datum {
	int _dan, _mjesec, _godina;

	void Unos(int d, int m, int g) { 
		_dan = d; 
		_mjesec = m; 
		_godina = g; 
	}
	void Ispis() { 
		cout << _dan << "." << _mjesec << "." << _godina << endl; 
	}
};

struct Pitanje {
	char * _tekstPitanja;
	char * _odgovori[10];//maksimalno 10 odgovora 
	int _tacan;//lokacija tacnog odgovora - svako pitanje moze imati samo jedan tacan odgovor
	int _bodova; //broj bodova koje nosi pitanje 
	int _brojOdgovora;
	Datum _datumKreiranja;
	int _brojPitanja;

	

	void Unos(char *tekst, char *odgovori[], int tacan, int broj_odgovora, int bodova, Datum d) {

		if (_brojPitanja < 0) {
			_brojPitanja = 1;
			



			int duzina = strlen(tekst) + 1;
			_tekstPitanja = new char[duzina];
			strcpy_s(_tekstPitanja, duzina, tekst);

			_brojOdgovora = broj_odgovora;

			for (int i = 0; i < _brojOdgovora; i++) {
				int duzina = strlen(odgovori[i]) + 1;
				_odgovori[i] = new char[duzina];
				strcpy_s(_odgovori[i], duzina, odgovori[i]);
			}

		
			_datumKreiranja.Unos(d._dan, d._mjesec, d._godina);

			tacan -= 1;
			_tacan = tacan;
			_bodova = bodova;
		}
		else {
			_datumKreiranja.Unos(d._dan, d._mjesec, d._godina);



			int duzina = strlen(tekst) + 1;
			_tekstPitanja = new char[duzina];
			strcpy_s(_tekstPitanja, duzina, tekst);

			_brojOdgovora = broj_odgovora;

			for (int i = 0; i < _brojOdgovora; i++) {
				int duzina = strlen(odgovori[i]) + 1;
				_odgovori[i] = new char[duzina];
				strcpy_s(_odgovori[i], duzina, odgovori[i]);
			}

			

			tacan -= 1;
			_tacan = tacan;
			_bodova = bodova;
			_brojPitanja++;
		}


	}

	bool AddOdgovor(char *odgovor, bool tacan = false) {
		if (_brojOdgovora < 10 && tacan) {
			int duzina = strlen(odgovor) + 1;

			_odgovori[_brojOdgovora] = new char[duzina];
			strcpy_s(_odgovori[_brojOdgovora], duzina, odgovor);
			tacan = _brojOdgovora;
			_brojOdgovora++;


			cout << "Uspjesno ste dodali novi odgovor! [tacan odgovor]" << endl;
			return true;
		}
		else if (_brojOdgovora < 10) {
			int duzina = strlen(odgovor) + 1;

			
			_odgovori[_brojOdgovora] = new char[duzina];
			strcpy_s(_odgovori[_brojOdgovora], duzina, odgovor);
			_brojOdgovora++;


			cout << "Uspjesno ste dodali novi odgovor! [netacan odgovor]" << endl;
			return true;
		}

		cout << "Doslo je do greske pokusajte ponovo!" << endl;
		return false;
	}

	void RemoveOdgovor(int pozicija) {
		if (_tacan == pozicija) {
			cout << "Doslo je do greske, pokusajte ponovo!" << endl;
		}
		else {
			pozicija--;
			for (int i = pozicija; i < _brojOdgovora - 1; i++) {
				if (pozicija == i) {

					delete[] _odgovori[i];
					int duzina = strlen(_odgovori[i + 1]) + 1;
					_odgovori[i] = new char[duzina];

					strcpy_s(_odgovori[i], duzina, _odgovori[i + 1]);
					_odgovori[i + 1] = nullptr;

				}

			}
			_brojOdgovora--;
			cout << "Uspjesno ste uklonili odgovor!" << endl;
		}
	}



	void Ispis() {

		cout << "Datum kreiranja: ";
		_datumKreiranja.Ispis();

		cout << "Tekst pitanja: " << _tekstPitanja << endl;
		cout << "Odgovori: " << endl;
		for (int i = 0; i < _brojOdgovora; i++) {
			cout << "[" << i << "]" << _odgovori[i] << endl;
		}

		cout << "Tacan odgovor: " << _odgovori[_tacan] << endl;
		cout << "Broj bodova: " << _bodova << endl;
	}
};

struct Kandidat {
	char * _imePrezime;
	char _JMBG[14];
	void Unos(char * ip, char jmbg[]) {
		
		int duzina = strlen(ip) + 1;
		_imePrezime = new char[duzina];
		strcpy_s(_imePrezime, duzina, ip);

		for (int i = 0; i < 14; i++) {
			_JMBG[i] = jmbg[i];
		}
	}
	void Dealociraj() {
		delete[] _imePrezime; 
		_imePrezime = nullptr;
	}
	void Info() {
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "JMBG: " << _JMBG << endl;
	}

	void AddPitanje(Pitanje obj) {
		cout << "Pitanje: " << obj._tekstPitanja << endl;
		int kandidatovOdgovor;
		cout << "Unesite odgovor na postavljeno pitanje: ";
		cin >> kandidatovOdgovor;

		if (kandidatovOdgovor == obj._tacan) {
			obj._bodova++;
		}
	}

	
};


struct PrijemniIspit {
	Datum * _datumOdrzavanja;
	//kandidati prijavljeni za prijemni ispit 
	Kandidat * _prijavljeniKandidati[100];
	int _brojPrijavljenih;
	//uspjeh ostvaren na prijemnom ispitu za svakog pojedinog 
	//kandidata
	float * _uspjehKandidata[100];
	//prag prolaznosti na prijemnom ispitu npr. 60 procenata
	int _pragProlaznosti;
	
	


	void Unos(Datum obj, int prag) {
		_datumOdrzavanja = new Datum;
		_datumOdrzavanja->Unos(obj._dan, obj._mjesec, obj._godina);

		_pragProlaznosti = prag;
		_brojPrijavljenih = 0;

	}


	bool DodajKandidata(Kandidat obj) {
		if (_brojPrijavljenih < 100) {
			_prijavljeniKandidati[_brojPrijavljenih] = new Kandidat;
			_prijavljeniKandidati[_brojPrijavljenih++]->Unos(obj._imePrezime, obj._JMBG);
			cout << "Uspjesno ste dodali kandidata!" << endl;
			return true;
		}
		cout << "Nije moguce dodati novog kandidata!" << endl;
		return false;
	}




	
	void PokreniIspit(char *JMBG, Pitanje *obj, int brojPitanja) {

		for (int i = 0; i < brojPitanja; i++) {
			
			
		
			
			// Tekst pitanja i unos odgovora na postavljeno pitanje
			
		    /*	_prijavljeniKandidati[i]->AddPitanje(obj[i]);  */
			
			int odgovor;

			cout << "Pitanje: " << obj[i]._tekstPitanja << endl;
			cout << "Unesite odgovor: " << endl;

			cin >> odgovor;
			cin.ignore();


			if (odgovor == obj[i]._tacan) {
				obj[i]._bodova+=10;
			}
		}

	}

	float GetBrojBodova(Pitanje *obj, int brojPitanja) {

		float suma = 0;

		for (int i = 0; i < brojPitanja; i++) {
			suma += obj[i]._bodova;
		}

		return suma;

	}
	void Ispis() {
		cout << "Datum odrzavanja prijemnog ispita: "; _datumOdrzavanja->Ispis();
		cout << "Broj prijavljenih: " << _brojPrijavljenih << endl;
		for (int i = 0; i < _brojPrijavljenih; i++) {
			_prijavljeniKandidati[i]->Info();
		}
		cout << "Prag prolaznosti: " << _pragProlaznosti << endl;
	}
};
int main() {
	


	Datum obj;
	obj.Unos(7, 8, 2015);

	Kandidat obj1;
	obj1.Unos("Sejdalija Agic", "148822299726");

	Pitanje obj2;

	char *odgovori[] = { "Fakultet Informacijskih Tehnologija", "Fakultet Islamske teologije", "Fakultet Informatickih Tehnologija" };
	char *odgovori_1[] = { "13", "29", "15", "20" }; // 20 tacan
	
	Pitanje *obj_test = new Pitanje[2];

	obj_test[0].Unos("Koliko Sejdalija Agic ima godina: ", odgovori_1, 4, 4, 0, obj);
	obj_test[1].Unos("FIT je skracenica od: ", odgovori, 1, 3, 0, obj);
	
	/*obj2.RemoveOdgovor(4);*/

	obj_test[0].Ispis();

	obj_test[1].Ispis();

	PrijemniIspit obj3;

	obj3.Unos(obj, 60);
	obj3.DodajKandidata(obj1);
	obj3.Ispis();


	obj3.PokreniIspit("148822299726", obj_test, 2);

	cout << "Ukupno bodova: " << obj3.GetBrojBodova(obj_test, 2) << endl;

	return 0;
}
