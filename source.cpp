#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include <unordered_map>
#include<algorithm>
#include<sstream>
using namespace std;
class IFile {
	virtual void saveToFile(fstream& file) = 0;//metoda virtuala pura
	virtual void restoreFromFile(fstream& file) = 0;//metoda virtuala pura
};

class Ingredient :IFile
{
	string denumire = "-";
	char* unitateMasura = nullptr;
	bool esteVegan = false;
	float cantitateStoc = 0.0;

public:

	
	Ingredient() //CONSTR FARA PARAM
	{

	}
	Ingredient(string denumire)//constr cu un param
	{
		if (!denumire.empty())
			this->denumire = denumire;

	}

	Ingredient(string denumire, char* unitateMasura, bool esteVegan, float cantitateStoc)//CONSTR CU PARAM
	{
		if (!denumire.empty())
			this->denumire = denumire;
		if (unitateMasura != nullptr)
		{
			this->unitateMasura = new char[strlen(unitateMasura) + 1];
			strcpy(this->unitateMasura, unitateMasura);
		}
		this->esteVegan = esteVegan;
		this->cantitateStoc = cantitateStoc;

	}

	Ingredient(const Ingredient& i)//CONST COPY
	{
		if (!denumire.empty())
			this->denumire = i.denumire;
		if (i.unitateMasura != nullptr)
		{
			this->unitateMasura = new char[strlen(i.unitateMasura) + 1];
			strcpy(this->unitateMasura, i.unitateMasura);
		}
		this->esteVegan = i.esteVegan;
		this->cantitateStoc = i.cantitateStoc;
	}




	Ingredient& operator=(const Ingredient& i)//OP =
	{
		if (this != &i)
		{
			delete[]this->unitateMasura;
			this->unitateMasura = nullptr;
			this->denumire = i.denumire;
			if (i.unitateMasura != nullptr)
			{
				this->unitateMasura = new char[strlen(i.unitateMasura) + 1];
				strcpy(this->unitateMasura, i.unitateMasura);

			}
			this->esteVegan = i.esteVegan;
			this->cantitateStoc = i.cantitateStoc;
		}
		return *this;
	}

	void adaugaCantitate(float cantitateNoua)//METODA GENERICA 1 --adauga la cantitatea deja existenta
	{
		if (cantitateNoua > 0 && this->cantitateStoc > 0)//verificare
			this->cantitateStoc = this->cantitateStoc + cantitateNoua;
	}

	bool esteInStoc() //METODA GENERICA 2
	{
		if (this->cantitateStoc > 0)//verificare
			return true;
		return false;
	}

	void setDenumire(string denumireNoua)
	{
		if (!denumireNoua.empty())//verificare
			this->denumire = denumireNoua;
	}

	string getDenumire()
	{
		if (!this->denumire.empty())//verif
			return this->denumire;
	}
	void setUnitateMasura(const char* unitateNoua)//pentru obiectele facute cu constr fara param sau modifica pt cele cu param
	{
		if (unitateNoua != nullptr)
		{
			delete[]this->unitateMasura;
			this->unitateMasura = nullptr;
			char buffer[100];//folosesc buffer ca sa mi fie mai usor sa gestionez memoria
			strcpy(buffer, unitateNoua);
			this->unitateMasura = new char[strlen(buffer) + 1];
			strcpy(this->unitateMasura, buffer);
		}
		else cout << "\nIntroduceti iar unitatea corecta: ";
	}
	const char* getUnitateMasura()
	{
		if (strlen(this->unitateMasura) >= 1)
			return this->unitateMasura;

	}

	void setEsteVegan(bool EsteVegan)
	{
		if (EsteVegan == false || EsteVegan == true)
			this->esteVegan = EsteVegan;
		else cout << "\nTrebuie sa dati valoarea 0 sau 1";
	}

	bool getEsteVegan()
	{
		if (this->esteVegan == 1)
			return true;
		else return false;
	}

	void setCantitateStoc(float cantitateStocNoua)
	{
		if (cantitateStocNoua >= 0)//nu ma lasa sa dau stocului valori negative
			this->cantitateStoc = cantitateStocNoua;
		else cout << "\nValoarea din stoc nu poate fi negativa ";
	}
	float getCantitateStoc()
	{
		if (this->cantitateStoc >= 0)
			return this->cantitateStoc;
	}

	friend ostream& operator<<(ostream& out, const Ingredient& i) //op<<
	{
		out << "\n***************************************";
		out << "\nDenumire ingredient: " << i.denumire;
		out << "\nUnitatea de masura este: ";
		if (i.unitateMasura != nullptr)
			out << i.unitateMasura;
		else out << "-";
		out << "\nProdusul este vegan 0-NU \ 1-DA: " << i.esteVegan;
		out << "\nCantitatea din stoc este de: " << i.cantitateStoc;
		out << "\n***************************************";
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Ingredient& i) //op<<
	{

		out << i.denumire;
		if (i.unitateMasura != nullptr)
			out << i.unitateMasura;
		else out << "-";
		out << i.esteVegan;
		out << i.cantitateStoc;
		return out;
	}
	friend istream& operator>>(istream& in, Ingredient& i)//op>>
	{
		delete[]i.unitateMasura;
		i.unitateMasura = nullptr;
		cout << "\nIntroduceti denumirea: ";
		in >> i.denumire;
		cout << "\nIntroduceti unitatea de masura: ";
		char buffer[100];
		in >> buffer;
		i.unitateMasura = new char[strlen(buffer) + 1];
		strcpy(i.unitateMasura, buffer);
		cout << "\nIngredientul este sau nu vegan? 0-NU \ 1-DA: ";
		in >> i.esteVegan;
		cout << "\nIntroduceti cantitatea din stoc:";
		in >> i.cantitateStoc;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Ingredient& i)//op>>
	{
		delete[]i.unitateMasura;
		i.unitateMasura = nullptr;
		in >> i.denumire;
		char buffer[100];
		in >> buffer;
		i.unitateMasura = new char[strlen(buffer) + 1];
		strcpy(i.unitateMasura, buffer);
		in >> i.esteVegan;
		in >> i.cantitateStoc;
		return in;
	}


	void saveToFile(fstream& file) {
		int lgd = this->denumire.length() + 1;
		file.write((char*)&lgd, sizeof(int));
		file.write(this->denumire.data(), lgd);

		int lg = strlen(this->unitateMasura) + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->unitateMasura, lg);
		file.write((char*)&this->esteVegan, sizeof(bool));
		file.write((char*)&this->cantitateStoc, sizeof(float));


	}
	void restoreFromFile(fstream& file) {
		int lgd;
		file.read((char*)&lgd, sizeof(int));

		char* bufferD = new char[lgd];
		file.read(bufferD, lgd);

		this->denumire = bufferD;
		delete[] bufferD;

		int lg;
		file.read((char*)&lg, sizeof(int));

		char* buffer = new char[lg];
		file.read(buffer, lg);

		delete[] this->unitateMasura;
		this->unitateMasura = new char[lg];
		strcpy(this->unitateMasura, buffer);

		delete[] buffer;
		file.read((char*)&this->esteVegan, sizeof(bool));
		file.read((char*)&this->cantitateStoc, sizeof(float));
	}

	Ingredient& operator++()
	{
		this->cantitateStoc++;
		return *this;
	}
	Ingredient operator++(int) {
		Ingredient copie = *this;
		this->cantitateStoc++;
		return copie;
	}
	Ingredient operator+(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			Ingredient rez = *this;
			rez.cantitateStoc += stocSuplimentar;
			return rez;
		}
	}

	friend bool operator>(float stoc, Ingredient i) {
		return stoc > i.cantitateStoc;
	}
	bool operator!()
	{
		return !esteVegan;
	}
	bool verificaStocDisponibil(float cantitateNecesara) const {
		return this->cantitateStoc >= cantitateNecesara;
	}
	void scadeCantitateStoc(float cantitate) {
		this->cantitateStoc -= cantitate;
	}

	~Ingredient()//DESTRUCTOR
	{
		delete[]this->unitateMasura;
		this->unitateMasura = nullptr;
	}
	bool operator==(const Ingredient& i) {
		return (this->denumire == i.denumire &&
			(this->unitateMasura == i.unitateMasura || (unitateMasura != nullptr && i.unitateMasura != nullptr && strcmp(unitateMasura, i.unitateMasura) == 0)) &&
			esteVegan == i.esteVegan &&
			cantitateStoc == i.cantitateStoc);
	}

};
class Retetar:IFile
{
	string denumire = "-";
	int nrIngrediente = 0;
	Ingredient* listaIngrediente = nullptr;
	float* cantitateReteta = nullptr;

public:
	Retetar()
	{}
	Retetar(string denumire)
	{
		if (!denumire.empty())
			this->denumire = denumire;
	}
	Retetar(string denumire, int nrIngrediente, Ingredient* listaIngrediente, float* cantitateReteta)//const cu param
	{
		if (!denumire.empty())
			this->denumire = denumire;
		this->nrIngrediente = nrIngrediente;
		if (listaIngrediente != nullptr)
		{
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = listaIngrediente[i];
		}
		if (cantitateReteta != nullptr)
		{
			this->cantitateReteta = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->cantitateReteta[i] = cantitateReteta[i];
		}


	}
	Retetar(const Retetar& r)//constr copy
	{
		if (!r.denumire.empty())
			this->denumire = r.denumire;
		this->nrIngrediente = r.nrIngrediente;
		if (r.listaIngrediente != nullptr)
		{
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = r.listaIngrediente[i];
		}
		if (r.cantitateReteta != nullptr)
		{
			this->cantitateReteta = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->cantitateReteta[i] = r.cantitateReteta[i];
		}

	}
	Retetar& operator=(const Retetar& r)//op=
	{
		if (this != &r)
		{
			delete[]this->cantitateReteta;
			this->cantitateReteta = nullptr;
			delete[]this->listaIngrediente;
			this->listaIngrediente = nullptr;
			if (!r.denumire.empty())
				this->denumire = r.denumire;
			this->nrIngrediente = r.nrIngrediente;
			if (r.listaIngrediente != nullptr)
			{
				this->listaIngrediente = new Ingredient[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->listaIngrediente[i] = r.listaIngrediente[i];
			}
			if (r.cantitateReteta != nullptr)
			{
				this->cantitateReteta = new float[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->cantitateReteta[i] = r.cantitateReteta[i];
			}

		}
		return *this;
	}


	friend istream& operator>>(istream& in, Retetar& r)//op>>
	{
		delete[]r.listaIngrediente;
		r.listaIngrediente = nullptr;
		delete[]r.cantitateReteta;
		r.cantitateReteta = nullptr;
		cout << "\nDati denumirea preparatului pentru reteta:";
		in.ignore();
		getline(in, r.denumire);
		cout << "\nDati numarul de ingrediente necesare prepararii: ";
		in >> r.nrIngrediente;
		if (r.nrIngrediente != 0)
		{
			r.listaIngrediente = new Ingredient[r.nrIngrediente];
			for (int i = 0; i < r.nrIngrediente; i++)
			{
				cout << "\nPentru ingredientul " << i + 1 << " dati urmatoarele valori:";
				in >> r.listaIngrediente[i];
			}
			cout << "\nDati cantitatea necesara fiecarui ingredient: ";
			r.cantitateReteta = new float[r.nrIngrediente];
			for (int i = 0; i < r.nrIngrediente; i++)
				in >> r.cantitateReteta[i];

		}
		return in;
	}

	friend ostream& operator<<(ostream& out, const Retetar& r)//op<<
	{
		out << "\nDenumirea preparatului:";
		if (!r.denumire.empty())
			out << r.denumire;
		else out << "-";
		out << "\nNumarul de ingrediente: ";
		if (r.nrIngrediente != 0)
		{
			out << r.nrIngrediente;
			cout << "\nNumele ingredientelor sunt: ";
			for (int i = 0; i < r.nrIngrediente; i++)
				out << r.listaIngrediente[i].getDenumire() << " ";
			cout << "\nCantitatile aferente sunt: ";
			for (int i = 0; i < r.nrIngrediente; i++)
				out << r.cantitateReteta[i] << "  ||  ";

		}
		else out << "\nNu are ingredienta, aferent nu exista lista lor sau cantitatile";
		return out;
	}
	string getDenumire()const//am adaugat const pentru a putea afisa preparatele din meniu
	{
		if (!denumire.empty())
			return this->denumire;
	}
	void setDenumire(string denumireNoua)
	{
		if (!denumire.empty())
			this->denumire = denumire;
	}
	Ingredient* getListaIngrediente()
	{
		if (this->listaIngrediente != nullptr)
			return this->listaIngrediente; // Returneaza pointer la lista de ingrediente
	}
	void setListaIngrediente(const Ingredient* listaIngrediente, int nrIngrediente)
	{
		if (nrIngrediente > 0) {
			delete[] this->listaIngrediente;
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->listaIngrediente[i] = listaIngrediente[i];
			}
		}
	}
	int getNrIngrediente()
	{
		if (this->nrIngrediente >= 0)
			return this->nrIngrediente; // Returneaza numarul de ingrediente
	}
	void setNrIngrediente(int nrNou)
	{
		if (nrNou > 0)
			this->nrIngrediente = nrNou;
	}
	float getCantitateReteta(int i)// pe asta il folosesc sa mi intoarca cantitatea unui ingredient pt actualizarea stocului
	{
		if (i >= 0 && i < this->nrIngrediente)
		{
			if (this->cantitateReteta[i] > 0)
				return this->cantitateReteta[i];
		}
		else {
			return 0;
		}
	}
	float* getCantitatiReteta()//pe asta il folosesc de disponibilitate!!
	{
		if (this->cantitateReteta != nullptr) {
			float* copieCantitati = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				copieCantitati[i] = cantitateReteta[i];
			}
			return copieCantitati;
		}
		else {
			return nullptr;
		}
	}
	void setCantitateReteta(const float* cantitatiReteta, int nrIngrediente)
	{
		if (nrIngrediente > 0) {
			delete[] this->cantitateReteta;
			this->nrIngrediente = nrIngrediente;
			this->cantitateReteta = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->cantitateReteta[i] = cantitatiReteta[i];
			}
		}
	}


	void scadeCantitateStoc()//METODA GENERICA 1
	{   //nu am pus verificari pentru ca apelez functia abia dupa ce verific daca ingredientele necesare sunt in stoc si daca am stoc suficient
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			float cantitateaStoc = this->listaIngrediente[i].getCantitateStoc();
			float cantitateReteta = this->cantitateReteta[i];
			float cantitateNoua = cantitateaStoc - cantitateReteta;
			this->listaIngrediente[i].setCantitateStoc(cantitateNoua);
		}
	}

	void afisareUnitatiMasura()//METODA GENERICA 2
	{
		cout << "\n------------------------";
		if (listaIngrediente != nullptr)
		{
			cout << "\nUnitati de masura pentru ingredientele din reteta:\n";
			for (int i = 0; i < nrIngrediente; i++)
			{
				cout << listaIngrediente[i].getUnitateMasura() << "\n";
			}
		}
		else
		{
			cout << "Nu exista ingrediente in reteta.\n";
		}
		cout << "\n------------------------";
	}
	void saveToFile(fstream& file)  {
		int lgd = this->denumire.length() + 1;
		file.write((char*)&lgd, sizeof(int));
		file.write(this->denumire.data(), lgd);
		file.write((char*)&this->nrIngrediente, sizeof(int));

		if (this->listaIngrediente != nullptr) {
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->listaIngrediente[i].saveToFile(file);
			}
		}

		if (this->cantitateReteta != nullptr) {
			file.write((char*)this->cantitateReteta, sizeof(float) * this->nrIngrediente);
		}
	}

	void restoreFromFile(fstream& file) {
		int lgd;
		file.read((char*)&lgd, sizeof(int));

		char* bufferD = new char[lgd];
		file.read(bufferD, lgd);

		this->denumire = bufferD;
		delete[] bufferD;

		file.read((char*)&this->nrIngrediente, sizeof(int));

		delete[] this->listaIngrediente;
		this->listaIngrediente = new Ingredient[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->listaIngrediente[i].restoreFromFile(file); // Folosirea metodei restoreFromFile direct pentru a citi din fișier
		}

		delete[] this->cantitateReteta;
		this->cantitateReteta = new float[this->nrIngrediente];
		file.read((char*)this->cantitateReteta, sizeof(float) * this->nrIngrediente);
	}


	~Retetar()//DESTRUCTOR
	{
		delete[]this->cantitateReteta;
		this->cantitateReteta = nullptr;
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}
};
class Preparat
{
	Retetar reteta;
	float pret = 0;
	string* listaAlergeni = nullptr;
	static float PretMediuPreparate;

public:
	Preparat()
	{}
	Preparat(float pret)
	{
		if (pret > 0)
			this->pret = pret;
	}

	Preparat(Retetar reteta, float pret)
	{
		this->reteta = reteta;
		this->pret = pret;
	}

	Preparat(const Preparat& p)
	{
		this->reteta = p.reteta;
		this->pret = p.pret;
	}
	Preparat& operator=(const Preparat& p)
	{
		if (this != &p)
		{
			this->reteta = p.reteta;
			this->pret = p.pret;
		}
		return *this;
	}
	friend istream& operator>>(istream& in, Preparat& p)
	{
		in >> p.reteta;
		cout << "\nDati pretul preparatului: ";
		in >> p.pret;
		return in;

	}
	friend ostream& operator<<(ostream& out, const Preparat& p)
	{
		cout << "\nPreparatul are urmatoarea reteta: ";
		out << p.reteta;
		cout << "\nPreparatul are urmatorul pret: ";
		out << p.pret;
		return out;

	}
	void setPreNou(float pretNou)
	{
		if (pretNou > 0)
			this->pret = pretNou;
	}
	float getPret()
	{
		if (this->pret > 0)
			return this->pret;
	}
	void setListaAlergeni(const string* listaAlergeni, int nrAlergeni)
	{
		delete[] this->listaAlergeni;

		if (nrAlergeni > 0 && listaAlergeni != nullptr)
		{
			this->listaAlergeni = new string[nrAlergeni];
			for (int i = 0; i < nrAlergeni; i++)
			{
				this->listaAlergeni[i] = listaAlergeni[i];
			}
		}
		else
		{
			this->listaAlergeni = nullptr;
		}
	}


	const string* getListaAlergeni()
	{
		if (this->listaAlergeni != nullptr)
			return this->listaAlergeni;
	}
	void setReteta(const Retetar& retetaNoua)
	{
		this->reteta = retetaNoua;
	}

	Retetar getReteta()const
	{
		return this->reteta;
	}

	static void setPretMediu(float pretMediuNou) {
		if (pretMediuNou > 0) {
			Preparat::PretMediuPreparate = pretMediuNou;
		}
	}
	~Preparat()
	{

		delete[]this->listaAlergeni;
		this->listaAlergeni = nullptr;
	}

};
float Preparat::PretMediuPreparate = 33;


class Restaurant
{
	Ingredient* stocuri = nullptr;//stocul restaurantului
	int nrIngredienteStoc = 0;
public:
	Restaurant()
	{}
	Restaurant(int nrIngredienteStoc)
	{
		if (nrIngredienteStoc > 0)
			this->nrIngredienteStoc = nrIngredienteStoc;
	}
	Restaurant(Ingredient* stocuri, int nrIngredienteStoc)//constr cu param
	{
		if (nrIngredienteStoc > 0 && stocuri != nullptr) {
			this->nrIngredienteStoc = nrIngredienteStoc;
			this->stocuri = new Ingredient[this->nrIngredienteStoc];
			for (int i = 0; i < this->nrIngredienteStoc; i++)
				this->stocuri[i] = stocuri[i];
      	}
	}

	Restaurant(const Restaurant& r)
	{
		if (r.nrIngredienteStoc > 0 && r.stocuri != nullptr) {
			this->nrIngredienteStoc = r.nrIngredienteStoc;
			this->stocuri = new Ingredient[this->nrIngredienteStoc];
			for (int i = 0; i < this->nrIngredienteStoc; i++)
				this->stocuri[i] = r.stocuri[i];
		}
	}

	Restaurant& operator=(const Restaurant& r)
	{
		if (this != &r)
		{
			if (r.nrIngredienteStoc > 0 && r.stocuri != nullptr) {
				this->nrIngredienteStoc = r.nrIngredienteStoc;
				this->stocuri = new Ingredient[this->nrIngredienteStoc];
				for (int i = 0; i < this->nrIngredienteStoc; i++)
					this->stocuri[i] = r.stocuri[i];
			}
		}
		return *this;
	}


	friend istream& operator>>(istream& in, Restaurant& r)//op>>
	{
		cout << "\nDati numarul ingredientelor din stoc: ";
		in >> r.nrIngredienteStoc;
		r.stocuri = new Ingredient[r.nrIngredienteStoc];
		cout << "\nCititi ingredientele: ";
		for (int i = 0; i < r.nrIngredienteStoc; i++)
			in >> r.stocuri[i];
		return in;

	}

	friend ostream& operator<<(ostream& out, const Restaurant& r)//op<<
	{
		out << "\n-----------------STOCUL:-----------------";
		for (int i = 0; i < r.nrIngredienteStoc; i++)
			out << r.stocuri[i] << endl;
		out << "---------------------------------------\n";

		return out;

	}

	void adaugaIngredientInStoc(const Ingredient& ingredient)//METODA GENERICA 1
	{
		Ingredient* newStocuri = new Ingredient[this->nrIngredienteStoc + 1];//facem un vector cu dimensiunea fostului v+1

		// Copiem ingredientele existente în noul vector
		for (int i = 0; i < this->nrIngredienteStoc; i++)
			newStocuri[i] = this->stocuri[i];
		newStocuri[this->nrIngredienteStoc] = ingredient;
		delete[] this->stocuri;

		// Actualizam pointerul la noul vector
		this->stocuri = newStocuri;

		//marim si nr de ingrediente
		this->nrIngredienteStoc++;
	}

	bool existaIngredientInStoc(const string& denumireIngredient, float cantitateNecesara)//METODA GENERICA 2
	{
		for (int i = 0; i < nrIngredienteStoc; ++i)
		{
			if (stocuri[i].getDenumire() == denumireIngredient)
			{
				if (stocuri[i].getCantitateStoc() >= cantitateNecesara)
				{
					return true; // Suficienta cantitate in stoc
				}
				else
				{
					return false; // Cantitate insuficienta in stoc
				}
			}
		}
		return false;
	}

	void setNrIngredienteStoc(int nrNou)
	{
		if (nrNou > 0)
			this->nrIngredienteStoc = nrNou;
	}
	int getNrIngredienteStoc()
	{
		if (this->nrIngredienteStoc > 0)
			return this->nrIngredienteStoc;
	}

	Ingredient getStoc(int i)
	{
		if (i >= 0 && i < this->nrIngredienteStoc)
			return this->stocuri[i];
	}
	void afiseazaStoc()
	{
		cout << "Stocul actual al restaurantului:\n";
		for (int i = 0; i < nrIngredienteStoc; ++i)
		{
			cout << stocuri[i].getDenumire() << ": " << stocuri[i].getCantitateStoc() << " " << stocuri[i].getUnitateMasura() << "\n";
		}
	}
	void actualizeazaStoc(const string& denumire, float cantitate) {
		for (int i = 0; i < this->nrIngredienteStoc; i++) {
			if (this->stocuri[i].getDenumire() == denumire) {
				if (this->stocuri[i].getCantitateStoc() >= cantitate) {
					this->stocuri[i].setCantitateStoc(this->stocuri[i].getCantitateStoc() - cantitate);
					cout << "Stocul pentru " << denumire << " a fost actualizat cu succes.\n";
				}
				else {
					cout << "Nu exista suficient " << denumire << " in stoc.\n";
				}
				return;
			}
		}

		cout << "Ingredientul " << denumire << " nu a fost gasit in stoc.\n";
	}
	
	void raportStocSubLimita(float limita, const string& numeFisierRaport)
	{
		ofstream fisierRaport(numeFisierRaport);
		if (!fisierRaport)
		{
			cout << "Eroare la deschiderea fisierului " << numeFisierRaport << "\n";
			return;
		}
		cout << "\n1. ********** RAPORT STOC INGREDIENTE SUB LIMITA **********\n";
		fisierRaport << "\n********** RAPORT STOC INGREDIENTE SUB LIMITA **********\n";

		for (int i = 0; i < this->nrIngredienteStoc; i++)
		{
			if (this->stocuri[i].getCantitateStoc() <= limita && strcmp(this->stocuri[i].getUnitateMasura(), "gram") == 0)
			{
				cout << this->stocuri[i].getDenumire() << ": " << this->stocuri[i].getCantitateStoc()
					<< " " << this->stocuri[i].getUnitateMasura() << "\n";

				fisierRaport << this->stocuri[i].getDenumire() << ": " << this->stocuri[i].getCantitateStoc()
					<< " " << this->stocuri[i].getUnitateMasura() << "\n";
			}
		}

		fisierRaport << "***********************************************\n";
		fisierRaport.close();
	}
	
	~Restaurant()
	{
		if (this->stocuri != nullptr) {
			delete[] this->stocuri;
			this->stocuri = nullptr;
		}

	}
};

class Meniu
{
	Preparat* preparate = nullptr;
	int nrPreparate = 0;
public:
	Meniu()
	{}
	Meniu(int nrPreparate)
	{
		if (nrPreparate > 0)
			this->nrPreparate = nrPreparate;
	}
	Meniu(Preparat* preparate, int nrPreparate)
	{
		if (nrPreparate > 0 && preparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->preparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preparate[i] = preparate[i];
		}
	}
	Meniu(const Meniu& m)//constr copy
	{
		this->nrPreparate = m.nrPreparate;
		this->preparate = new Preparat[this->nrPreparate];
		for (int i = 0; i < this->nrPreparate; i++)
			this->preparate[i] = m.preparate[i];
	}
	Meniu& operator=(const Meniu& m)//op=
	{
		if (this != &m)
		{
			this->nrPreparate = m.nrPreparate;
			this->preparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->preparate[i] = m.preparate[i];
		}
		return *this;
	}
	friend istream& operator>>(istream& in, Meniu& m)//op>>
	{
		cout << "\nDati nr preparate din meniu:";
		in >> m.nrPreparate;
		m.preparate = new Preparat[m.nrPreparate];
		cout << "\nCititi ingredientele: ";
		for (int i = 0; i < m.nrPreparate; i++)
			in >> m.preparate[i];
		return in;
	}

	friend ostream& operator<<(ostream& out, const Meniu& m)//op<<
	{
		out << "\n---------------------MENIU--------------------";
		for (int i = 0; i < m.nrPreparate; ++i) {
			out << "\n*";
			out << m.preparate[i].getReteta().getDenumire() << "............................." << m.preparate[i].getPret() << " lei" << "\n";
		}
		return out;
	}

	void setNrPreparate(int nrNou)
	{
		if (nrNou > 0)
			this->nrPreparate = nrNou;
	}

	int getNrPreparate()
	{
		if (this->nrPreparate > 0)
			return this->nrPreparate;
	}
	Preparat getPreparat(int i)
	{
		if (i >= 0 && i < this->nrPreparate)
			return this->preparate[i];
	}
	void setPreparat(int i, const Preparat& preparatNou)//adaug pe pozitia i un preparat nou
	{
		if (i >= 0 && i < this->nrPreparate)
		{
			this->preparate[i] = preparatNou;
		}
	}
	float operator[](int pozitie)
	{
		if (pozitie > 0 && pozitie < this->nrPreparate)
			return this->preparate[pozitie].getPret();
	}
	~Meniu()
	{
		delete[]this->preparate;
		this->preparate = nullptr;
	}
};
class Comanda
{
private:
	static Meniu meniu;
	Preparat* preparateComandate = nullptr;
	int* cantitatiComandate = nullptr;
	int nrPreparateComandate = 0;
	const int id;
	static int primulID;
	static set<int>numereMasaUnice;
	int numarMasa;
	static Restaurant restaurant;

public:
	Comanda() :id(primulID++)
	{
		this->numarMasa = genereazaNumarMasaUnic();
	}
	Comanda(int id, int nrPreparateComandate) :id(id)
	{
		if (nrPreparateComandate > 0)
			this->nrPreparateComandate = nrPreparateComandate;
	}
	Comanda(int id, Preparat* preparateComandate, int* cantitatiComandate, int nrPreparateComandate) :id(id)
	{
		this->nrPreparateComandate = nrPreparateComandate;
		this->preparateComandate = new Preparat[this->nrPreparateComandate];
		for (int i = 0; i < this->nrPreparateComandate; i++)
			this->preparateComandate[i] = preparateComandate[i];
		this->cantitatiComandate = new int[this->nrPreparateComandate];
		for (int i = 0; i < this->nrPreparateComandate; i++)
			this->cantitatiComandate[i] = cantitatiComandate[i];
		

	}

	Comanda(const Comanda& c) :id(id)
	{
		if (c.nrPreparateComandate > 0 && c.preparateComandate != nullptr)
		{
			this->nrPreparateComandate = c.nrPreparateComandate;
			this->preparateComandate = new Preparat[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->preparateComandate[i] = c.preparateComandate[i];
			this->cantitatiComandate = new int[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->cantitatiComandate[i] = c.cantitatiComandate[i];
		}
		

	}

	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			if (c.nrPreparateComandate > 0 && c.preparateComandate != nullptr)
			{
				this->nrPreparateComandate = c.nrPreparateComandate;
				this->preparateComandate = new Preparat[this->nrPreparateComandate];
				for (int i = 0; i < this->nrPreparateComandate; i++)
					this->preparateComandate[i] = c.preparateComandate[i];
				this->cantitatiComandate = new int[this->nrPreparateComandate];
				for (int i = 0; i < this->nrPreparateComandate; i++)
					this->cantitatiComandate[i] = c.cantitatiComandate[i];
			}
			

		}
		return *this;
	}
	void sortareProfitPreparate(vector<pair<string, float>>& profitPreparate) {
		int n = profitPreparate.size();
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < n - i - 1; ++j) {
				if (profitPreparate[j].second < profitPreparate[j + 1].second) {
					// Schimbă locurile între perechile (nume, profit)
					swap(profitPreparate[j], profitPreparate[j + 1]);
				}
			}
		}
	}

	void raportProfitPreparate(const string& numeFisierRaport) {
		ofstream fisierRaport(numeFisierRaport, ios::app);
		if (!fisierRaport) {
			cout << "Eroare la deschiderea fisierului " << numeFisierRaport << "\n";
			return;
		}
		if (nrPreparateComandate == 0) {
			cout << "Nu exista comenzi plasate pentru a genera un raport de profit.\n";
			return;
		}

		vector<pair<string, float>> profitPreparate;

		for (int i = 0; i < nrPreparateComandate; i++) {
			float costPreparat = preparateComandate[i].getPret() * cantitatiComandate[i];
			profitPreparate.push_back({ preparateComandate[i].getReteta().getDenumire(), costPreparat });
		}
	
		sortareProfitPreparate(profitPreparate);
		
		cout << "\n2. ********** RAPORT PREPARATE PROFITABILE **********\n";
		fisierRaport << "\n********** RAPORT PREPARATE PROFITABILE **********\n";
		for (const auto& pereche : profitPreparate) {
			cout << pereche.first << ": " << pereche.second << " lei\n";
			fisierRaport << pereche.first << ": " << pereche.second << " lei\n";
		}
		cout << "***********************************************\n";
		fisierRaport << "***********************************************\n";
		
		fisierRaport.close();
	}
	void citesteRaportFrecventa(const string& numeFisierRaport) {
		ifstream fisierRaport(numeFisierRaport);
		if (!fisierRaport) {
			cout << "Eroare la deschiderea fisierului " << numeFisierRaport << "\n";
			return;
		}

		unordered_map<string, int> frecventaPreparate;

		string line;
		while (getline(fisierRaport, line)) {
			if (line.find("RAPORT PREPARATE PROFITABILE") != string::npos) {
				// Cautăm linia care începe un nou raport
				continue;
			}

			size_t pos = line.find(":");
			if (pos != string::npos) {
				// Extragem numele preparatului
				string preparat = line.substr(0, pos);
				// Incrementăm frecvența în unordered_map
				frecventaPreparate[preparat]++;
			}
		}

		// Sortăm map-ul în funcție de valorile asociate cheilor
		vector<pair<string, int>> preparateSortate(
			frecventaPreparate.begin(),
			frecventaPreparate.end()
		);

		sort(preparateSortate.begin(), preparateSortate.end(),
			[](const pair<string, int>& a, const pair<string, int>& b) {
				return a.second > b.second;  // Sortare descrescătoare după frecvență
			}
		);

		// Afișăm preparatele ordonate după frecvență
		cout << "\n4. ********** RAPORT FRECVENTA PREPARATE **********\n";
		for (const auto& pereche : preparateSortate) {
			cout << pereche.first << ": " << pereche.second << " ori\n";
		}
		cout << "***********************************************\n";

		fisierRaport.close();
	}

	void afiseazaPreparatulCuCelMaiMareVenit(const string& numeFisierRaport) {
		ifstream fisierRaport(numeFisierRaport);
		if (!fisierRaport) {
			cout << "Eroare la deschiderea fisierului " << numeFisierRaport << "\n";
			return;
		}

		unordered_map<string, float> venituriPreparate; // Map pentru a stoca veniturile pentru fiecare preparat

		string linie;
		while (getline(fisierRaport, linie)) {
			size_t pozitieStart = linie.find(':');
			if (pozitieStart != string::npos) {
				size_t pozitieSfarsit = linie.find("lei", pozitieStart);
				if (pozitieSfarsit != string::npos) {
					string numePreparat = linie.substr(0, pozitieStart);
					float venit = stof(linie.substr(pozitieStart + 1, pozitieSfarsit - pozitieStart - 1));
					venituriPreparate[numePreparat] += venit;
				}
			}
		}

		fisierRaport.close();

		// Găsirea preparatului cu cel mai mare venit
		string preparatCuCelMaiMareVenit;
		float celMaiMareVenit = 0.0;

		for (const auto& entry : venituriPreparate) {
			if (entry.second > celMaiMareVenit) {
				celMaiMareVenit = entry.second;
				preparatCuCelMaiMareVenit = entry.first;
			}
		}

		// Afisare rezultat
		if (!preparatCuCelMaiMareVenit.empty()) {
			cout << "\n5. **********RAPORT PREPARAT/VENIT**********\n";
			cout << "\nPreparatul care aduce cel mai mult venit este: " << preparatCuCelMaiMareVenit << endl;
			cout << "\n******************************************";
		}
		else {
			cout << "Nu s-a putut determina preparatul cu cel mai mare venit." << endl;
		}
	}
	void raportIngredienteUtilizate(const string& numeFisierRaport) {
		ofstream fisierRaport(numeFisierRaport, ios::app);
		if (!fisierRaport) {
			cout << "Eroare la deschiderea fisierului " << numeFisierRaport << "\n";
			return;
		}
		if (nrPreparateComandate == 0) {
			cout << "Nu exista comenzi plasate pentru a genera un raport de ingrediente.\n";
			return;
		}

		unordered_map<string, float> cantitatiIngrediente;  // Map pentru a stoca cantitatile de ingrediente

		for (int i = 0; i < nrPreparateComandate; i++) {
			Retetar reteta = preparateComandate[i].getReteta();
			Ingredient* listaIngrediente = reteta.getListaIngrediente();
			float* cantitatiReteta = reteta.getCantitatiReteta();

			for (int j = 0; j < reteta.getNrIngrediente(); j++) {
				string numeIngredient = listaIngrediente[j].getDenumire();
				float cantitateNecesara = cantitatiReteta[j] * cantitatiComandate[i];

				cantitatiIngrediente[numeIngredient] += cantitateNecesara;
			}
		}

		// Sortam map-ul în functie de cantitatile asociate cheilor
		vector<pair<string, float>> ingredienteSortate(
			cantitatiIngrediente.begin(),
			cantitatiIngrediente.end()
		);

		sort(ingredienteSortate.begin(), ingredienteSortate.end(),
			[](const pair<string, float>& a, const pair<string, float>& b) {
				return a.second > b.second;  // Sortare descrescătoare după cantitate
			}
		);

		// Afisam ingrediente ordonate dupa cantitate
		cout << "\n3. ********** RAPORT INGREDIENTE UTILIZATE **********\n";
		fisierRaport << "\n********** RAPORT INGREDIENTE UTILIZATE **********\n";
		for (const auto& pereche : ingredienteSortate) {
			cout << pereche.first << ": " << pereche.second << " unitati\n";
			fisierRaport << pereche.first << ": " << pereche.second << " unitati\n";
		}
		cout << "***********************************************\n";
		fisierRaport << "***********************************************\n";

		fisierRaport.close();
	}


	void salveazaInFisierCSV(const string& numeFisier) const {
		ofstream file(numeFisier, ios_base::app);

		if (file.is_open()) {
			file << "ID,NumarMasa,Preparat,Cantitate\n";

			for (int i = 0; i < nrPreparateComandate; i++) {
				file << id << "," << numarMasa << "," << preparateComandate[i].getReteta().getDenumire() << ","
					<< cantitatiComandate[i] << "\n";
			}

			file.close();
			cout << "Comanda a fost salvata cu succes in fisierul CSV.\n";
		}
		else {
			cout << "Eroare la deschiderea fisierului pentru scriere.\n";
		}
	}

	static int genereazaNumarMasaUnic() {
		int numarMasa;
		do {
			numarMasa = rand() % 100 + 1; 
		} while (numereMasaUnice.find(numarMasa) != numereMasaUnice.end());

		numereMasaUnice.insert(numarMasa);
		return numarMasa;
	}
	friend istream& operator>>(istream& in, Comanda& c)
	{
		cout << Comanda::meniu;

		while (true) {
			string denumirePreparat;
			int nrPortii = 0;

			cout << "\nDati numele preparatului (sau 'stop' pentru a opri comanda): ";
			in.ignore();
			getline(in, denumirePreparat);

			if (denumirePreparat == "stop") {
				break;
			}

			bool preparatGasit = false;
			for (int j = 0; j < c.meniu.getNrPreparate(); j++) {
				if (denumirePreparat == c.meniu.getPreparat(j).getReteta().getDenumire()) {
					cout << "\nDati numarul de portii pentru " << c.meniu.getPreparat(j).getReteta().getDenumire() << ": ";
					in >> nrPortii;
					if (nrPortii <= 0)
					{
						cout << "\nNu poate fi negativ, incercati iar:";

					}
						c.adaugaPreparat(c.meniu.getPreparat(j), nrPortii,restaurant);
						preparatGasit = true;

						char raspuns;
						cout << "\nMai doriti ceva? (1->DA // 0->NU): ";
						in >> raspuns;

						if (raspuns == '0') {
							return in;  // Utilizatorul a decis sa nu mai adauge preparate
						}

						break;					
				}
			}

			if (!preparatGasit) {
				cout << "\nNu exista preparatul " << denumirePreparat << " in meniu. Te rog sa alegi alt preparat.\n";
			}
		}

		return in;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c)//op<<
	{
		out << "\n*************COMANDA DUMNEAVOASTREA*************" << endl;
		out << "\n#####ID COMANDA#####: " << c.id << endl;
		out << "\n-----NR MASA: " << c.numarMasa << " -----" << endl;
		for (int i = 0; i < c.nrPreparateComandate; i++)
			out << c.preparateComandate[i].getReteta().getDenumire() << "    -->  " << c.cantitatiComandate[i] << " bucati" << endl;
		out << "\n*******************************************" << endl;
		return out;

	}

	bool verificaAdaugare(const Preparat& preparat, int cantitate)
	{
		Retetar reteta = preparat.getReteta();
		Ingredient* listaIngrediente = reteta.getListaIngrediente();
		float* cantitatiReteta = reteta.getCantitatiReteta();
		bool stocSuficient = true;

		for (int i = 0; i < reteta.getNrIngrediente(); i++) {
			Ingredient ingredient = listaIngrediente[i];
			float cantitateNecesara = cantitatiReteta[i] * cantitate;

			if (ingredient.getCantitateStoc() < cantitateNecesara)
				return false;
			return true;
		}
	}

	void adaugaPreparat(const Preparat& preparat, int cantitate, const Restaurant& Restaurant)
	{
		if (cantitate > 0)
		{
			Retetar reteta = preparat.getReteta();
			Ingredient* listaIngrediente = reteta.getListaIngrediente();
			float* cantitatiReteta = reteta.getCantitatiReteta();
			bool stocSuficient = true;

			for (int i = 0; i < reteta.getNrIngrediente(); i++) {
				Ingredient ingredient = listaIngrediente[i];
				float cantitateNecesara = cantitatiReteta[i] * cantitate;

				if (ingredient.getCantitateStoc() < cantitateNecesara) {
					stocSuficient = false;
					cout << "Stoc insuficient pentru " << ingredient.getDenumire() << endl;
					break;
				}
			}
			if (stocSuficient) {
				Preparat* newPreparate = new Preparat[this->nrPreparateComandate + 1];
				int* newCantitati = new int[this->nrPreparateComandate + 1];

				for (int i = 0; i < nrPreparateComandate; ++i)
				{
					newPreparate[i] = this->preparateComandate[i];
					newCantitati[i] = this->cantitatiComandate[i];
				}

				newPreparate[this->nrPreparateComandate] = preparat;
				newCantitati[this->nrPreparateComandate] = cantitate;

				delete[] this->preparateComandate;
				this->preparateComandate = nullptr;
				delete[] this->cantitatiComandate;
				this->cantitatiComandate = nullptr;

				this->preparateComandate = newPreparate;
				this->cantitatiComandate = newCantitati;

				this->nrPreparateComandate++;
			}
			else {
				char raspunsContinuare;
				cout << "Continuati comanda? 1=>DA/0=>NU ";
				cin >> raspunsContinuare;

				if (raspunsContinuare == 0) {
					return;
				}
			}
		}
	}


	bool verificaDisponibilitate(Restaurant& restaurant) {
		bool ok = true;

		for (int i = 0; i < nrPreparateComandate && ok; ++i) {
			Retetar reteta = preparateComandate[i].getReteta();
			Ingredient* listaIngrediente = reteta.getListaIngrediente();
			float* cantitatiReteta = reteta.getCantitatiReteta();

			for (int j = 0; j < reteta.getNrIngrediente(); j++) {
				Ingredient ingredient = listaIngrediente[j];
				float cantitateNecesara = cantitatiReteta[j] * this->cantitatiComandate[i];

				if (!restaurant.existaIngredientInStoc(ingredient.getDenumire(), cantitateNecesara)) {
					ok = false;
					break;
				}
			}
		}

		if (!ok) {
			cout << "Nu exista cantitate suficienta pentru unul sau mai multe ingrediente.Puteti comanda altceva =)\n";	
		}
		else {
			for (int k = 0; k < nrPreparateComandate; ++k) {
				Retetar reteta = preparateComandate[k].getReteta();
				Ingredient* listaIngrediente = reteta.getListaIngrediente();
				float* cantitatiReteta = reteta.getCantitatiReteta();

				for (int l = 0; l < reteta.getNrIngrediente(); l++) {
					Ingredient ingredient = listaIngrediente[l];
					float cantitateNecesara = cantitatiReteta[l] * this->cantitatiComandate[k];
					restaurant.actualizeazaStoc(ingredient.getDenumire(), cantitateNecesara);
				}
			}

			cout << "Comanda poate fi onorata. Toate ingredientele sunt disponibile in cantitatea necesara.\n";
		}

		return ok;
	}

	static void setMeniu(Meniu meniuNou)
	{
		if (meniuNou.getNrPreparate() > 0)
			Comanda::meniu = meniuNou;
		
	}
	static void setRestaurant(Restaurant restaurantNou)
	{
		Comanda::restaurant = restaurantNou;
	}
	Meniu getMeniu()
	{
		return this->meniu;
	}

	void setCantitatiComandate(const int* cantitati, int nrPreparate) {
		if (cantitati != nullptr)
		{
			delete[] this->cantitatiComandate;
			this->cantitatiComandate = new int[nrPreparate];
			for (int i = 0; i < nrPreparate; i++) {
				cantitatiComandate[i] = cantitati[i];
			}
			this->nrPreparateComandate = nrPreparate;
		}
	}
	int* getCantitatiComandate() {

		if (this->cantitatiComandate != nullptr)
			return this->cantitatiComandate;
	}

	int getNrPreparateComandate()
	{
		if (this->nrPreparateComandate > 0)
			return this->nrPreparateComandate;
	}
	void setNrPreparateComandate(int nrNou)
	{
		if (nrNou > 0)
			this->nrPreparateComandate = nrNou;
	}
	static void stergeNumarMasaUnic(int numarMasa) {
		numereMasaUnice.erase(numarMasa);
	}

	~Comanda()
	{
		delete[] this->preparateComandate;
		this->preparateComandate = nullptr;
		delete[]this->cantitatiComandate;
		this->cantitatiComandate = nullptr;
		stergeNumarMasaUnic(numarMasa);
	}
	
};
int Comanda::primulID = 1;
Meniu Comanda::meniu;
set<int> Comanda::numereMasaUnice;
Restaurant Comanda::restaurant;

int main(int argc, char* argv[]) {
	string Ingrediente = argv[1];
	string Retete = argv[2];

	ifstream f(Ingrediente);
	ifstream r(Retete);
	ifstream rtg("rating.csv");
	string numePreparatMeniu;
	string linie;
  
	int numarIngrediente;
	f >> numarIngrediente;
	if (!f) {
		cout << "Eroare la citire numarIngrediente" << endl;
		return 1;
	}
	f.ignore();
	vector<Ingredient> listaIngrediente;
	map<string, Ingredient> mapaIngrediente;
	for (int i = 0; i < numarIngrediente; i++) {
		string denumireIngredient;
		char* unitateMasura;
		bool esteVegan;
		float cantitateStoc;
		char buffer[100];

		f >> denumireIngredient;
		f >> buffer;
		unitateMasura = new char[strlen(buffer) + 1];
		strcpy(unitateMasura, buffer);
		f >> esteVegan >> cantitateStoc;


		Ingredient ingredient(denumireIngredient, unitateMasura, esteVegan, cantitateStoc);
		listaIngrediente.push_back(ingredient);
		mapaIngrediente[ingredient.getDenumire()] = ingredient;
		f.ignore();
		delete[] unitateMasura;

	}

	int numarRetete;
	r >> numarRetete;
	if (!r) {
		cout << "Eroare la citire nrRetete" << endl;
		return 1;
	}
	vector<Retetar> listaRetete;

	for (int i = 0; i < numarRetete; i++) {
		string numeReteta;
		int numarIngredienteReteta;
		r >> numeReteta >> numarIngredienteReteta;

		Ingredient* ingredienteReteta = new Ingredient[numarIngredienteReteta];
		float* cantitatiReteta = new float[numarIngredienteReteta];

		for (int j = 0; j < numarIngredienteReteta; j++) {
			string numeIngredient;
			float cantitate;
			r >> numeIngredient >> cantitate;

			if (mapaIngrediente.find(numeIngredient) != mapaIngrediente.end()) {
				ingredienteReteta[j] = mapaIngrediente[numeIngredient];
				cantitatiReteta[j] = cantitate;
			}
			else {
				cout << "Ingredientul " << numeIngredient << " nu a fost gasit in lista de ingrediente." << endl;

			}


		}

		Retetar reteta(numeReteta, numarIngredienteReteta, ingredienteReteta, cantitatiReteta);
		listaRetete.push_back(reteta);

		delete[] ingredienteReteta;
		delete[] cantitatiReteta;
	}
	
	/*vector<Retetar>::iterator itRetete;
	for (itRetete = listaRetete.begin(); itRetete != listaRetete.end(); itRetete++) {
		cout << *itRetete << endl;}*/

    Preparat Chec(listaRetete[1], 20);
	Preparat Pizza(listaRetete[0], 30);
	Preparat Salata(listaRetete[2], 25);
	Preparat Burger(listaRetete[3], 32);
	
	
	

	Restaurant RestaurantulMeu;
	for (int i = 0; i < numarIngrediente; i++) {
		RestaurantulMeu.adaugaIngredientInStoc(listaIngrediente[i]);
	}
	
	Preparat preparate1[] = { Chec,Pizza,Salata,Burger };
	Meniu MeniulMeu(preparate1, 4);
	Comanda::setMeniu(MeniulMeu);
	Comanda::setRestaurant(RestaurantulMeu);
	
	//------------------COMANDA----------------------------------------
	bool ok = false;
	cout << endl << "Plasati o comanda? (1->DA \\ 0->NU)";
	cin >> ok;

	while (ok) {
		Comanda comandaNoua;
		cin >> comandaNoua;

		if (!comandaNoua.verificaDisponibilitate(RestaurantulMeu)) {
			cout << "Doriti sa continuati comanda? (1->DA \\ 0->NU)";
			cin >> ok;

			if (!ok)
				break;  
		}
		else {
			
			cout << comandaNoua;
			cout << "\n============================================\n";
			RestaurantulMeu.raportStocSubLimita(200,"StocSubLimita");
            comandaNoua.raportProfitPreparate("Profitabilitate");
			comandaNoua.raportIngredienteUtilizate("IngredienteComandaInCurs");
			comandaNoua.citesteRaportFrecventa("Profitabilitate");
			comandaNoua.afiseazaPreparatulCuCelMaiMareVenit("Profitabilitate");
			comandaNoua.salveazaInFisierCSV("Comenzi");
			cout << "\nMai plasati o comanda? (1->DA \\ 0->NU)";
			cin >> ok;

			if (!ok)
				break;  
		}
	}

	cout << "\n******************~MULTUMIM CA ATI TRECUT PE LA NOI!~******************";
	cout << endl;
	RestaurantulMeu.afiseazaStoc();
	//AFISEZ STOCUL DUPA CE AM PLASAT COMANDA

	/*IFile* filePointer; /////Pentru ingrediente
	fstream file("colectie.bin", ios::out | ios::binary);
    for (auto& ingredient : listaIngrediente) {

		ingredient.saveToFile(file);
		
	}
	file.close();

	fstream file("colectie.bin", ios::in | ios::binary);
	for (auto& ingredient : listaIngrediente) {

		ingredient.restoreFromFile(file);
		cout<<ingredient;
	}
	*/   

	/*
fstream file2("colectie2.bin", ios::out | ios::binary);
for (auto& reteta : listaRetete) {

	reteta.saveToFile(file2);}
	
fstream file2("colectie2.bin", ios::in | ios::binary);
	for (auto& reteta : listaRetete) {

		reteta.restoreFromFile(file2);
		cout << reteta;
	}

	file2.close();


	*/

	/////PRELUARE DIN CSV
	while (getline(rtg, linie)) {
		istringstream linieStream(linie);

		string numePreparatMeniu;
		float rating;

		// Citirea datelor pentru fiecare linie a fisierului CSV
		cout << "\n=========RATING PREPARATE=============\n";
		if (getline(linieStream, numePreparatMeniu, ',') && (linieStream >> rating)) {
			cout << "Preparat: " << numePreparatMeniu <<"        -->       " << " Rating: " << rating <<" * "<< endl;
		}
		else {
			cout << "Eroare la citirea din linia CSV: " << linie << endl;
		}
		cout << "\n====================================\n";
	}
	rtg.close();
	f.close();
	r.close();

	return 0;
}
