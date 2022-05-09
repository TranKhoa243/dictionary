#include<iostream>
#include<string>
#include<fstream>
using namespace std;

typedef struct data {
	string tu;
	string nghia;
}DATA;

class Cell {
	DATA key;
	Cell* next;
	Cell(string k, string h) {
		key.tu = k;
		key.nghia = h;
		next = NULL;
	}
	friend class HashTable;
};

class HashTable {
public:

	HashTable(int size = 100) {
		m = size;
		T = new Cell * [m];
		for (int i = 0; i < m; i++)
			T[i] = NULL;
	}

	~HashTable() {
		for (int i = 0; i < m; i++)
			if (T[i] != NULL)
				for (Cell* x = T[i]; x != NULL;) {
					Cell* y = x;
					x = x->next;
					delete y;
				}
		delete[] T;
	}

	bool Insert(string k, string h);

	int Search(string k);

	void Print();

	void Load_the_file_test(ifstream& filein, DATA& x);

	void Load_all_file(ifstream& filein);

	void Save_file(ofstream& outfile);

	void Update(string k, string h);

	void Delete(string k);

private:
	Cell** T;
	int m;
	int GetSlot(string k);
};

int HashTable::GetSlot(string k) {
	int tong = 0;
	for (int i = 0; i < k.length(); i++)
		tong += k[i];
	return tong % m;
}

void HashTable::Load_the_file_test(ifstream& filein, DATA& x) {
	getline(filein, x.tu, ',');
	getline(filein, x.nghia);
}

void HashTable::Load_all_file(ifstream& filein) {
	while (!filein.eof())
	{
		DATA x;
		Load_the_file_test(filein, x);
		Insert(x.tu, x.nghia);
	}
}

void HashTable::Save_file(ofstream& outfile) {
	int j = 0;
	while (j < 100) {
		for (Cell* cur = T[j]; cur != NULL; cur = cur->next) {
			outfile << cur->key.tu << "," << cur->key.nghia << "\n";
		}
		j++;
	}
}

bool HashTable::Insert(string k, string h) {
	int j = GetSlot(k);
	if (T[j] == NULL) {
		T[j] = new Cell(k, h);
		return true;
	}
	else {
		Cell* x = new Cell(k, h);
		x->next = T[j];
		T[j] = x;
		return true;
	}
}

int HashTable::Search(string k) {
	int j = GetSlot(k);
	for (Cell* cur = T[j]; cur != NULL; cur = cur->next)
		if (cur->key.tu == k) {
			cout << "\n\tTu tim kiem co trong danh sach:\n";
			cout << "\n\t" << k << " :" << cur->key.nghia << endl;
			return 1;
		}
	return -1;
}

void HashTable::Delete(string k) {
	int i, thay; Cell* p, * q;
	i = GetSlot(k);
	if (T[i != NULL]) cout << "\n\t" << k << " ko co trong tu dien.";
	else {
		if (T[i]->key.tu == k) { p = T[i]; T[i] = T[i]->next; delete p; }
		else {
			q = T[i]; p = q->next; thay = 0;
			while (p != NULL and !thay)
				if (p->key.tu == k) { thay = 1; q->next = p->next; delete p; }
				else { q = p; p = q->next; }
			if (!thay) cout << "\n\t" << k << " khong co trong tu dien.";
		}
	}
}

void HashTable::Update(string k, string h) {
	Delete(k);
	Insert(k, h);
}

void HashTable::Print() {
	for (int i = 0; i < m; i++) {
		cout << "Slot" << i << ": ";
		for (Cell* cur = T[i]; cur != NULL; cur = cur->next)
			cout << cur->key.tu << " ->";
		cout << "NULL\n";
	}
}

int main()
{
	HashTable BTL;
	ifstream filein;
	filein.open("Tudien.txt", ios::in);
	BTL.Load_all_file(filein);
	filein.close();
	BTL.Print();
	system("pause");
	int n;
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t =========== MENU ===========";
		cout << "\n\t\t1. Tra tu.";
		cout << "\n\t\t2. Sua doi tu.";
		cout << "\n\t\t3. Them tu moi.";
		cout << "\n\t\t4. Xoa tu.";
		cout << "\n\t\t0. Thoat va luu file.";
		cout << "\n\n\t\t =========== END ===========";
		cout << "\n\tVao lua chon:";
		cin >> n;
		string k, h;
		if (n == 1)
		{
			cout << "\n\tVao tu muon tra:";
			fflush(stdin); getline(cin, k);
			int bien = BTL.Search(k);
			if (bien == 1)
			 {
				BTL.Search(k);
			 }
			else 
			 {
				cout << "\n \t Tu nay khong co trong danh sach.\n";
				cout << "\n \t De them tu moi xin quay ve MENU va chon '3'.";
			 } 
			cout << "\n \n \t"; system("pause");
		 }
		else if (n == 2)
		 {
			cout << "\n \t Nhap tu muon sua doi:";
			fflush(stdin); getline(cin, k);
			if (BTL.Search(k) == 1)
			 {
				cout << "\n \t Moi nhap nghia moi cua tu:";
				fflush(stdin); getline(cin, h);
				BTL.Update(k, h);
			 }
			else
			 {
				cout << "\n \t Tu nay chua co trong danh sach.\n";
				cout << "\n \t Moi tro lai MENU chon '3' de them tu da.";
			 }
		 }
		else if (n == 3)
		 {
			cout << "\n \t Vao tu muon them:";
			fflush(stdin); getline(cin, k);
			cout << "\n \t Nhap nghia cua tu:";
			fflush(stdin); getline(cin, h);
			if (BTL.Search(k) != 1)
			 {
				BTL.Insert(k, h);
				cout << "\n \t Tu duoc them thanh cong.";
			 }
			else 
			 {
				cout << " \n \t Tu nay da co trong danh sach.";
				cout << "\n \t Neu muon dinh nghia lai tu moi ve MENU chon '2'.";
			 }
			cout << "\n\t"; system("pause");
		 }
		else if (n == 4)
		 {
			cout << "\n \t Nhap tu muon xoa:"; cin >> k;
			BTL.Delete(k);
			cout << " \n \t"; system("pause");
		 }
		else if (n == 0) 
		 {
			ofstream outfile;
			outfile.open("OUTPUT.txt", ios::out | ios::trunc);
			BTL.Save_file(outfile);
			outfile.close();
			cout << "\n\tFile da duoc luu vao tep OUTPUT.txt ,moi vao file day de doc du lieu.";
			break;
		 }
	}

	cout << "\n\t"; system("pause");
	return 0;
}



