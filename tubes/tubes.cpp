#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
/// PROGRAM PERPUSTAKAAN
// Deklarasi Struct Node untuk buku
struct Node
{
    string judul;
    string penulis;
    long long int isbn;
    string namaPeminjam;
    long long int nimPeminjam;
    Node *next;
};
Node *head;
Node *tail;
queue<Node *> bukuQueue;

// Inisialisasi Node
void init()
{
    head = NULL;
    tail = NULL;
}

// Pengecekan
bool isEmpty()
{
    if (head == NULL)
        return true;
    else
        return false;
}

// Tambah data Buku
void tambahdataBuku(string judul, long long int isbn, string penulis)
{
    cout << "- Tambah Data Buku -" << endl;
    cout << "Masukkan Judul Buku: ";
    cin >> judul;
    cout << "Masukkan Nomer ISBN: ";
    cin >> isbn;
    cout << "Masukan Nama Penulis: ";
    cin >> penulis;
    // Buat Node baru
    Node *baru = new Node;
    baru->judul = judul;
    baru->isbn = isbn;
    baru->penulis = penulis;
    baru->next = NULL;
    if (isEmpty() == true)
    {
        head = tail = baru;
        tail->next = NULL;
    }

    else
    {
        tail->next = baru;
        tail = baru;
    }
    cout << "Buku Dengan " << judul << " berhasil diinput!" << endl;
}

// Hitung Jumlah List
int hitungList()
{
    Node *hitung;
    hitung = head;
    int jumlah = 0;
    while (hitung != NULL)
    {
        jumlah++;
        hitung = hitung->next;
    }
    return jumlah;
}

// Ubah Data Buku revisi
void ubahdataBuku(string judul, long long int isbn, string penulis, int posisi)
{
    cout << "- Tambah Data Buku -" << endl;
    cout << "Masukkan Judul Buku: ";
    cin >> judul;
    cout << "Masukkan Nomer ISBN: ";
    cin >> isbn;
    cout << "Masukan Nama Penulis: ";
    cin >> penulis;
    Node *bantu;
    if (isEmpty() == 0)
    {

        if (posisi < 1 || posisi > hitungList())
        {
            cout << "Posisi di luar jangkauan" << endl;
        }
        else if (posisi == 1)
        {
            cout << "Posisi bukan posisi tengah" << endl;
        }
        else
        {
            bantu = head;
            int nomor = 1;
            while (nomor < posisi)
            {
                bantu = bantu->next;
                nomor++;
            }
            string dataLama = bantu->judul;
            bantu->judul = judul;
            bantu->isbn = isbn;
            bantu->penulis = penulis;
            cout << "Data pada posisi " << posisi << " Dengan Nama " << dataLama << " berhasil diganti dengan data " << judul << "!" << endl;
        }
    }
    else
    {
        cout << "List masih kosong!" << endl;
    }
}

// Hapus Data Buku pake queue
void hapusBuku(int posisi)
{
    if (isEmpty())
    {
        cout << "List masih kosong!" << endl;
        return;
    }
    if (posisi < 1 || posisi > hitungList())
    {
        cout << "Posisi di luar jangkauan" << endl;
        return;
    }
    Node *temp = head;
    Node *prev = NULL;
    int nomor = 1;
    if (posisi == 1)
    {
        head = temp->next;
        bukuQueue.push(temp);
        cout << "Buku pada posisi " << posisi << " berhasil dihapus!" << endl;
        return;
    }
    while (temp != NULL && nomor < posisi)
    {
        prev = temp;
        temp = temp->next;
        nomor++;
    }
    prev->next = temp->next;
    if (temp == tail)
    {
        tail = prev;
    }
    bukuQueue.push(temp);
    cout << "Buku pada posisi " << posisi << " berhasil dihapus!" << endl;
}

// Tampilkan List
void tampil()
{
    Node *bantu = head;
    if (isEmpty() == false)
    {
        int no = 1;
        cout << "No. | " << setw(20) << left << "Judul"
             << " | " << setw(15) << left << "ISBN"
             << " | " << setw(15) << left << "Penulis" << endl;
        cout << "----|----------------------|-----------------|------------" << endl;
        while (bantu != NULL)
        {
            cout << setw(3) << right << no++ << " | " << setw(20) << left << bantu->judul << " | " << setw(15) << left << bantu->isbn << " | " << setw(15) << left << bantu->penulis << endl;
            bantu = bantu->next;
        }
    }
    else
    {
        cout << "List masih kosong!" << endl;
    }
}

// Pinjam Buku
void pinjamBuku(int posisi, string namaPeminjam, int long long nimPeminjam)
{
    if (isEmpty())
    {
        cout << "List masih kosong!" << endl;
        return;
    }
    cout << "Masukkan posisi buku yang ingin dipinjam: ";
    cin >> posisi;
    if (posisi < 1 || posisi > hitungList())
    {
        cout << "Posisi di luar jangkauan" << endl;
        return;
    }
    Node *temp = head;
    int nomor = 1;
    while (temp != NULL && nomor < posisi)
    {
        temp = temp->next;
        nomor++;
    }
    if (temp != NULL)
    {
        cout << "Masukkan Nama Peminjam: ";
        cin >> namaPeminjam;
        cout << "Masukkan NIM Peminjam: ";
        cin >> nimPeminjam;

        // Tambahkan data nama peminjam dan NIM peminjam ke dalam buku
        temp->namaPeminjam = namaPeminjam;
        temp->nimPeminjam = nimPeminjam;

        bukuQueue.push(temp);
        cout << "Buku '" << temp->judul << "' berhasil dipinjam oleh " << namaPeminjam << " (NIM: " << nimPeminjam << ")!" << endl;
        // Menghapus buku dari linked list
        hapusBuku(posisi);
    }
    else
    {
        cout << "Buku tidak ditemukan!" << endl;
    }
}

// Kembalikan Buku
void kembalikanBuku(long long int isbn)
{
    if (bukuQueue.empty())
    {
        cout << "Tidak ada buku yang dipinjam" << endl;
        return;
    }

    Node *buku = NULL;

    // Mencari buku dengan ISBN yang sesuai
    Node *temp = bukuQueue.front();
    while (temp != NULL)
    {
        if (temp->isbn == isbn)
        {
            buku = temp;
            break;
        }
        temp = temp->next;
    }

    if (buku == NULL)
    {
        cout << "Buku dengan ISBN tersebut tidak perlu dikembalikan!" << endl;
        return;
    }

    // Menghapus buku dari queue
    bukuQueue.pop();

    if (isEmpty())
    {
        head = buku;
        tail = buku;
        buku->next = NULL;
    }
    else
    {
        tail->next = buku;
        tail = buku;
        buku->next = NULL;
    }
    cout << "Buku dengan ISBN " << isbn << " berhasil dikembalikan!" << endl;
}

// Daftar Buku yang dipinjam
void daftarBukuDipinjam()
{
    if (bukuQueue.empty())
    {
        cout << "Tidak ada buku yang sedang dipinjam saat ini." << endl;
        return;
    }
    cout << "Daftar Buku yang Dipinjam: " << endl;
    int nomor = 1;
    queue<Node *> tempQueue = bukuQueue;
    while (!tempQueue.empty())
    {
        Node *buku = tempQueue.front();
        cout << nomor << ". "
             << "Judul: " << buku->judul << ", ISBN: " << buku->isbn << ", Penulis: " << buku->penulis << endl;
        tempQueue.pop();
        nomor++;
    }
}

int main()
{
    int pilihan, posisi;
    long long int isbn, nimPeminjam;
    string judul, namaPeminjam, penulis;
    while (true)
    {
        cout << "\nPerpustakaan" << endl;
        cout << "1. Tambah Data Buku" << endl;
        cout << "2. Ubah Data Buku" << endl;
        cout << "3. Hapus Data Buku" << endl;
        cout << "4. Tampilkan Data Buku" << endl;
        cout << "5. Pinjam Buku" << endl;
        cout << "6. Kembalikan Buku" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahdataBuku(judul, isbn, penulis);
            break;
        case 2:
            tampil();
            cout << "Masukan Posisi yang akan diubah: ";
            cin >> posisi;
            ubahdataBuku(judul, isbn, penulis, posisi);
            break;
        case 3:
            tampil();
            cout << "Masukan Posisi Buku yang ingin dihapus: ";
            cin >> posisi;
            hapusBuku(posisi);
            break;
        case 4:
            tampil();
            break;

        case 5:
            tampil();
            pinjamBuku(posisi, namaPeminjam, nimPeminjam);
            break;

        case 6:
            daftarBukuDipinjam();
            cout << "Masukkan ISBN buku yang ingin dikembalikan: ";
            cin >> isbn;
            kembalikanBuku(isbn);
            break;

        case 0:
            cout << "Terima Kasih";
            exit(0);
            break;

        default:
            cout << " Maaf Pilihan Tidak Tersedia";
            break;
        }
    }

    return 0;
}