#include <iostream>
using namespace std;

class Cvor {
	struct Elem {
		int cvor;
		Elem* sledeci;
		Elem(int cvor_) :cvor(cvor_) {
			sledeci = nullptr;
		}
	};
	struct Zaglavlje {
		int CvorZaglavlja;
		int broj_cvorova;
		Elem* prvi;
		Zaglavlje(int cvorZaglavlja_) :CvorZaglavlja(cvorZaglavlja_) {
			broj_cvorova = 0;
		};
	};
	Zaglavlje* cvorGrafa;
	int cvorGrafa_;
	void kopiraj(const Cvor& l) {
		cvorGrafa->broj_cvorova = l.cvorGrafa->broj_cvorova;
		Elem* tek = l.cvorGrafa->prvi;
		while (tek) {
			Elem* novi = new Elem(*tek);

		}
	}
	void premesti(Cvor& l) {
		cvorGrafa->prvi = l.cvorGrafa->prvi;
		cvorGrafa->broj_cvorova = l.cvorGrafa->broj_cvorova;
	}
public:
	Cvor(int CvorGrafa_) :cvorGrafa_(CvorGrafa_) {
		cvorGrafa = new Zaglavlje(CvorGrafa_);
		cvorGrafa->prvi = nullptr;

	}
	Cvor(const Cvor& l){
		kopiraj(l);
	}
	Cvor(Cvor&& l) {
		premesti(l);
	}
	Cvor& dodaj_cvor(int n) {
		Elem* novi = new Elem(n);
		if (cvorGrafa->prvi == nullptr) {
			cvorGrafa->prvi = novi;
			cvorGrafa->broj_cvorova++;
			return *this;
		}
		if (novi->cvor <= cvorGrafa->prvi->cvor) {
			novi->sledeci = cvorGrafa->prvi;
			cvorGrafa->prvi = novi;
			cvorGrafa->broj_cvorova++;
			return *this;
		}
		else
		{
			Elem* tek = cvorGrafa->prvi;
			while (tek->sledeci != nullptr && novi->cvor > tek->sledeci->cvor) {
				tek = tek->sledeci;
			}
			novi->sledeci = tek->sledeci;
			tek->sledeci = novi;
			cvorGrafa->broj_cvorova++;
			return *this;
		}
	}
	Cvor& brisi_cvor(int n) {
		if (!postoji(n)) {
			//std::cout << "Element " << n << " ne postoji u listi, i stoga ne moze biti obrisan. Probajte ponovo! " << std::endl;
			return *this;
		}
		else {
			Elem* tek = cvorGrafa->prvi;
			Elem* preth = tek;
			while (tek) {
				if (cvorGrafa->prvi->cvor == n) {
					Elem* stari = cvorGrafa->prvi;
					cvorGrafa->prvi = cvorGrafa->prvi->sledeci;
					delete stari;
					cvorGrafa->broj_cvorova--;
					return *this;
				}
				if (tek->cvor == n) {
					preth->sledeci = tek->sledeci;
					delete tek;
					cvorGrafa->broj_cvorova--;
					return *this;
				}
				preth = tek;
				tek = tek->sledeci;
			}
		}
	}
	Cvor& operator=(const Cvor& l) {
		if (this != &l) {
			brisi();
			kopiraj(l);
		}
		return *this;
	}
	Cvor& operator=(Cvor&& l) {
		if (this != &l) {
			brisi();
			premesti(l);
		}
		return *this;
	}
	void brisi() {
		if (cvorGrafa->prvi != nullptr) {
			while (cvorGrafa->prvi) {
				Elem* stari = cvorGrafa->prvi;
				cvorGrafa->prvi = cvorGrafa->prvi->sledeci;
				delete stari;
			}
			cvorGrafa->prvi = nullptr;
			cvorGrafa->broj_cvorova = 0;
		}
	}
	friend std::ostream& operator<<(std::ostream& ot, Cvor& l) {
		l.pisi(ot);
		return ot;
		/*Elem* tek = l.prvi;
		while (tek) {
			ot << tek->cvor;
			if (tek->sledeci/* != nullptr)
				ot << " -> ";
			tek = tek->sledeci;
		}
		return ot;
	}*/
	}
	bool postoji(int n) {
		Elem* tek = cvorGrafa->prvi;
		while (tek) {
			if (tek->cvor == n) return true;
			else tek = tek->sledeci;
		}
		return false;
	}
	void pisi(std::ostream& ot) {
		Elem* tek = cvorGrafa->prvi;
		ot << "Cvor " << cvorGrafa_ << ": ";
		while (tek) {
			ot << tek->cvor;
			if (tek->sledeci != nullptr)
				ot << " -> ";
			tek = tek->sledeci;
		}
	}
	void brisi_zaglavlje() {
		cvorGrafa->prvi = nullptr;
		cvorGrafa->broj_cvorova = 0;
		delete cvorGrafa;
	}
	int cvorGrafaa()const {
		return cvorGrafa_;
	}
};


class Graf {
private:
	int velicina;
	Cvor ** niz;
public:
	Graf(int velicina_) :velicina(velicina_) {
		niz = new Cvor*[velicina_];
		for (int i = 0; i < velicina_; i++) {
			niz[i] = new Cvor(i + 1);
		}
	}
	friend std::ostream& operator<< (std::ostream& ot, const Graf& g) {
		for (int i = 0; i < g.velicina; i++) {
			g.niz[i]->pisi(ot);
			ot << std::endl;
		}
		return ot;
	}
	int dohv_velicinu() const {
		return velicina;
	}
	void brisi_put(int M, int N) {
		int i = -1, j = -1;
		for (int a = 0; a < velicina; i++) {
			if (niz[a]->cvorGrafaa() == M) i = a;
		}
		for (int a = 0; a < velicina; i++) {
			if (niz[a]->cvorGrafaa() == N) j = a;
		}
		if (i == -1 && j == -1)cout << "Nazalost, takav cvor ne postoji u grafu. Probajte ponovo! ";
		else
		{
			if (niz[i]->postoji(N) || niz[j]->postoji(M)) {
				niz[i]->brisi_cvor(N);
				niz[j]->brisi_cvor(M);
				cout << "Put uspjesno obrisan! " << endl;
			}
			else {
				cout << "Put za unesene cvorove ne postoji! Probajte ponovo. " << endl;
			}
		}
	}
	void dodaj_cvor() {
		Cvor** pomniz;
		pomniz = new Cvor*[velicina + 1];
		for (int i = 0; i < velicina; i++) {
			pomniz[i] = niz[i];
		}
		pomniz[velicina] = new Cvor(niz[velicina - 1]->cvorGrafaa() + 1);
		velicina++;
		niz = pomniz;
	}
	void obrisi_cvor(int n)
	{
			int m = -1;
			for (int a = 0; a < velicina; a++) {
				if (niz[a]->cvorGrafaa() == n) {
					m = a+1;
				}
			}
			if (m != -1) {
				for (int i = 0; i < velicina; i++) {
					niz[i]->brisi_cvor(n);
				}
				Cvor** pomniz = new Cvor*[velicina - 1];
				for (int i = 0; i < m - 1; i++) {
					pomniz[i] = niz[i];
				}

				for (int i = m - 1; i < velicina; i++) {
					pomniz[i] = niz[i + 1];
				}
				niz[m - 1] = nullptr;
				delete niz[m - 1];
				velicina--;
				niz = pomniz;
				cout << "Cvor je uspjesno obrisan. " << endl;
			}
			else cout << "Takav cvor ne postoji u grafu! " << endl;
	}
	~Graf() {
		for (int i = 0; i < velicina; i++) {
			niz[i]->brisi();
			niz[i]->brisi_zaglavlje();
			delete niz[i];
		}
		delete[] niz;
		niz = nullptr;
	}
	void dodaj_put(int M, int N) {
		if (M > velicina || N > velicina||M<=0 ||N<=0) {
			std::cout << "Put van granica! Probajte ponovo " << std::endl;
		}
		else {
			int i = -1, j = -1;
			for (int a = 0; a < velicina; a++) {
				if (niz[a]->cvorGrafaa() == M) i = a ;
			}
			for (int a = 0; a < velicina; a++) {
				if (niz[a]->cvorGrafaa() == N) j = a ;
			}
			if (i == -1 && j == -1) cout << "Takvi cvorovi ne postoje u grafu. Probajte ponovo! " << endl;
			else {
				if (niz[i]->postoji(N) || niz[j]->postoji(M)) {
					std::cout << "Put vec postoji. Probajte ponovo! " << std::endl;
				}
				else {
					if (i != j) {
						niz[i]->dodaj_cvor(N);
						niz[j]->dodaj_cvor(M);
						cout << "Put uspjesno dodan! " << endl;
					}
					else {
						niz[i]->dodaj_cvor(N);
						cout << "Put uspjesno dodan! " << endl;
					}
				}
			}
		}
	}
};
void brisigraf(Graf* g1) {
	g1->~Graf();
}

int main() {
	Graf* g1 = nullptr;
	while (true) {
		int ulaz;
		cout << endl
			<< "[1] Kreiraj graf " << endl
			<< "[2] Dodaj cvor u graf " << endl
			<< "[3] Izbrisi cvor iz grafa " << endl
			<< "[4] Dodaj granu izmedju 2 cvora " << endl
			<< "[5] Izbrisi granu izmedju 2 cvora " << endl
			<< "[6] Ispisi reprezentaciju grafa " << endl
			<< "[7] Obrisi graf iz memorije " << endl
			<< "[8] Kraj rada " << endl;
		cout << " =================================== " << endl;
		cout << "Unesite naredbu: " << endl;
		cin >> ulaz;
		switch (ulaz) {

		case 1:
			if (g1 == nullptr) {
				int n;
				cout << "Unesite dimenziju grafa: ";
				cin >> n;
				g1 = new Graf(n);
				break;
			}
			else {
				cout << "Graf je vec kreiran! " << endl;
				break;
			}

		case 2:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				g1->dodaj_cvor();
				cout << "Cvor je uspjesno dodan! " << endl;
				break;
			}
		case 3:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				cout << "Unesite cvor koji zelite da obrisete: " << endl;
				int cvor;
				cin >> cvor;
				g1->obrisi_cvor(cvor);
				break;
			}
		case 4:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				cout << "Unesite cvorove izmedju kojih se nalazi grana: " << endl;
				int a, b;
				cin >> a >> b;
				g1->dodaj_put(a, b);
				break;
			}
		case 5:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				cout << "Unesite cvorove izmedju kojih se nalazi grana koju zelite da obrisete: ";
				int c, d;
				cin >> c >> d;
				g1->brisi_put(c, d);
				break;
			}
		case 6:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				cout << *g1;
				break;
			}
		case 7:
			if (g1 == nullptr) {
				cout << "GRAF NE POSTOJI U MEMORIJI! PRVO KREIRAJTE GRAF! ";
				break;
			}
			else {
				brisigraf(g1);
				cout << "Graf je uspjesno obrisan! " << endl;
				g1 = nullptr;
				break;
			}
		case 8:

			cout << "Dovidjenja! " << endl;
			system("Pause");
			exit(10);

		default:
			cout << "NEDOZVOLJENA NAREDBA! " << endl;
			break;
		}
	}


}

