#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//DEKLARASIKAN TIPE DATA KUMPULAN DISINI
struct tanggal{
    int hari;
    int bulan;
    int tahun;
};

struct acc{
    char username[200];
    char nickname[200];
    char password[200];
};

struct data_peminjam{
    char username[200];
    char nickname[200];
    char nama_buku[300];
    char genre[50];
    struct tanggal pinjam;
    struct tanggal kembali;
    int denda;
};

struct data_buku{
    char nama_buku[300];
    char deskripsi[600];
    struct tanggal masuk;
    int stok;
    char jenis[25];     //JENIS BUKU FIKSI ATAU NONFIKSI
    char genre[25];  //JENIS BUKU YANG DIBUAT
    char subgenre[25];     //GENRE BUKU
};

//DEKLARASIKAN ARRAY DISINI
char jenis[2][50] = {"Fiksi", "Non-Fiksi"};
char genre[4][50] = {"Komik", "Novel", "Buku Pelajaran", "Ensiklopedia"};
char subgenre[8][50]= {"Manga", "Action", "Fantasi", "Romance", "IPA", "IPS", "Ensiklopedia Indonesia", "Ensiklopedia Dunia"};

//DEKLARASIKAN VARIABEL GLOBAL DISINI
int limit = 3;
int pilih, valid, finish;

//DEKLARASIKAN USERNAME DAN ADMIN DISINI
struct acc admin = {"admin", "admin", "admin"};

//DEKLARASIKAN FUNGSI ADMIN DISINI
void login_admin(int limit);
void menu_admin(char *username, char *nickname);
void tambah_buku(char *username, char *nickname);
void hapus_buku(char *username, char *nickname);
void daftar_pinjam(char *username, char *nickname);
void lihat_feedback(char *username, char *nickname);
void kasih_denda(char *username, char *nickname);

//DEKLARASIKAN FUNGSI USER DISINI
void reg_user();
void login_user(int limit);
void menu_user(char *username, char *nickname);
void pinjam_buku(char *username, char *nickname);
void kembalikan_buku(char *username, char *nickname);
void ubah_password(char *username, char *nickname);
void hapus_akun(char *username, char *nickname);
void lihat_denda(char *username, char *nickname);

//DEKLARASIKAN FUNGSI PEMBANTU/SHARED DISINI
void logo();
void hal_utama();
void menu_login();
void exit_acc();
void exit_app();
void tanggal(struct data_buku *data_buku);
void jenis_buku(struct data_buku *data_buku);
void genre_buku(struct data_buku *data_buku);
void subgenre_buku(struct data_buku *data_buku);
void lihat_buku(char *username, char *nickname);

int main(){}

//JELASKAN FUNGSI ADMIN DISINI
void login_admin(int limit){
    struct acc input;
    logo();
    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    if(strcmp(input.username, admin.username) == 0 && strcmp(input.password, admin.password) == 0){
        menu_admin(admin.username, admin.nickname);
    }else{
        logo();
        if(limit > 0){
            printf("Maaf, username atau password salah! Kesempatan login tersisa %d lagi", limit-1);
            login_admin(limit-1);
        }else{
            puts("Maaf, kesempatan login sudah habis! Program akan berhenti...");
        }
    }
}

void menu_admin(char *username, char *nickname){
    logo();
    puts("Selamat datang, Admin!");
    puts("--------- MENU BUKU ---------");
    puts("1. Tambah buku");
    puts("2. Hapus buku");
    puts("3. Lihat peminjam buku");
    puts("4. Lihat feedback");
    puts("5. Beri denda");

    puts("-------- KELUAR ---------");
    puts("6. Keluar dari akun");
    puts("7. Keluar dari aplikasi");
    printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

    switch(pilih){
        case 1  : tambah_buku(username, nickname); break;
        case 2  : hapus_buku(username, nickname); break;
        case 3  : daftar_pinjam(username, nickname); break;
        case 4  : lihat_feedback(username, nickname); break;
        case 5  : kasih_denda(username, nickname); break;
        case 6  : exit_acc(username,nickname); break;
        case 7  : exit_app(username,nickname); break;
        default : puts("Pilihan salah! Coba lagi!"); menu_admin(username,nickname);
    }
}

void tambah_buku(char *username, char *nickname){
    logo();

    //DEKLARASIKAN FILE DAN VARIABEL BUKU DISINI
    FILE *daftar_buku;
    int banyak_buku;
    struct data_buku *input;

    daftar_buku = fopen("data_buku.dat", "ab");

    puts("Halo admin! Mari kita data buku yang masuk sekarang");
    printf("Banyak buku : "); scanf("%d", &banyak_buku);getchar();

    input = (struct data_buku*) malloc(banyak_buku*sizeof(struct data_buku));

    for(int a=0;a<banyak_buku;a++){
        printf("========================= BUKU KE-%d ===========================\n", a+1);
        printf("Masukkan nama buku      : "); gets(input->nama_buku);
        printf("Masukkan deskripsi buku : "); gets(input->deskripsi);
        tanggal(&input[a]); //proses input tanggal buku
        printf("Masukkan stok buku      : "); scanf("%d", &input->stok); getchar();
        jenis_buku(&input[a]);
        genre_buku(&input[a]);
        subgenre_buku(&input[a]);
    }

    for(int a=0; a < banyak_buku; a++){
        if(fwrite(&input[a], sizeof(struct data_buku), 1, daftar_buku) != 0){
            finish = 1;
        }else{
            finish = 0;
            break;
        }
    }

    if(finish == 0){
        printf("Penulisan file error!");
    }

    fclose(daftar_buku);
    free(input);

    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_admin(username,nickname);
}

void hapus_buku(char *username, char *nickname){
    logo();
    
    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_admin(username,nickname);
}
void daftar_pinjam(char *username, char *nickname){
    logo();

    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_admin(username,nickname);
}
void lihat_feedback(char *username, char *nickname){
    logo();

    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_admin(username,nickname);
}
void kasih_denda(char *username, char *nickname){
    logo();

    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_admin(username,nickname);
}

void exit_acc(char *username, char *nickname);

//JELASKAN FUNGSI USER DISINI
void reg_user(){
    logo();
}

void menu_user(char *username, char *nickname){
    logo();

    puts("Tekan tombol apa saja untuk kembali ke menu utama..."); getchar();
    menu_user(username,nickname);
}
//JELASKAN FUNGSI PEMBANTU DISINI
void logo(){
    system("cls");
    puts("==============================================================================================================================");
    printf("  /$$$$$$                                          /$$       /$$ /$$                                             \n");
    printf(" /$$__  $$                                         | $$      |__/| $$                                             \n");
    printf("| $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$ | $$       /$$| $$$$$$$   /$$$$$$  /$$$$$$   /$$$$$$  /$$   /$$\n");
    printf("| $$ /$$$$ /$$__  $$ /$$__  $$ /$$__  $$| $$__    $$ | $$      | $$| $$__  $$ /$$__  $$|____  $$ /$$__  $$| $$  | $$\n");
    printf("| $$|_  $$| $$  \\__/| $$$$$$$$| $$$$$$$$| $$  \\ $$| $$      | $$| $$  \\ $$| $$  \\__/ /$$$$$$$| $$  \\__/| $$  | $$\n");
    printf("| $$  \\ $$| $$      | $$_____/| $$_____/| $$  |  $$| $$      | $$| $$  | $$| $$      /$$__  $$| $$      | $$  | $$\n");
    printf("|  $$$$$$/| $$      |  $$$$$$$|  $$$$$$$| $$  |   $$| $$$$$$$$| $$| $$$$$$$/| $$     |  $$$$$$$| $$      |  $$$$$$$\n");
    printf(" \\______/ |__/       \\_______/ \\_______/|__/  |__/|________/|__/|_______/ |__/      \\_______/|__/       \\____  $$\n");
    printf("                                                                                                        /$$  | $$\n");
    printf("                                                                                                       |  $$$$$$/\n");
    printf("                                                                                                        \\______/\n");
    puts("==============================================================================================================================");
}

void hal_utama(){
    logo();
    puts("MENU REGISTRASI/LOGIN AKUN\n1. REGISTRASI\n2. LOGIN : "); scanf("%d", &pilih);

    if(pilih == 1){
        reg_user();
    }else if(pilih == 2){
        menu_login();
    }
}



void tanggal(struct data_buku *data_buku){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    data_buku->masuk.hari = tm.tm_mday;
    data_buku->masuk.bulan = tm.tm_mon+1;
    data_buku->masuk.tahun = tm.tm_year+1900;
}

void jenis_buku(struct data_buku *data_buku){
    puts("---------------------- JENIS BUKU -----------------------");
    puts("1. Fiksi\n2. Non-Fiksi"); printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

    if(pilih > 2){
        printf("Pilihan salah!");
        jenis_buku(data_buku);
    }else{
        strcpy(data_buku->jenis, jenis[pilih-1]);
    }
}

void genre_buku(struct data_buku *data_buku){
    puts("---------------------- GENRE BUKU -----------------------");
    puts("1. Komik\n2. Novel\n3. Buku Pelajaran\n4. Ensiklopedia"); printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

    if(pilih > 4){
        printf("Pilihan salah!");
        jenis_buku(data_buku);
    }else{
        strcpy(data_buku->genre, genre[pilih-1]);
    }
}


void subgenre_buku(struct data_buku *data_buku){
    puts("---------------------- SUBGENRE BUKU -----------------------");
    puts("1. Manga\n2. Action\n3. Fantasi\n4. Romance\n5. IPA\n6. IPS\n7. Ensiklopedia Indonesia\n8. Ensiklopedia Dunia"); printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

    if(pilih > 8){
        printf("Pilihan salah!");
        jenis_buku(data_buku);
    }else{
        strcpy(data_buku->subgenre, subgenre[pilih-1]);
    }
}

void exit_acc(char *username, char *nickname){
    logo();
    puts("Apakah anda yakin ingin keluar?\n1. Ya\n2. Tidak : "); scanf("%d", &pilih); getchar();

    if(pilih == 1){
        menu_login();
    }else if(pilih == 2){
        if(strcmp(username, admin.username) == 0 && strcmp(nickname, admin.nickname) == 0){
            menu_admin(username,nickname);
        }else{
            menu_user(username, nickname);
        }
    }else{
        puts("Pilihan salah! Silahkan pilih pilihan yang benar!");
        exit_acc(username,nickname);
    }
}

void exit_app(char *username, char *nickname){
    logo();
    puts("Apakah anda yakin ingin keluar?\n1. Ya\n2. Tidak : "); scanf("%d", &pilih); getchar();

    if(pilih == 1){
        exit(0);
    }else if(pilih == 2){
        if(strcmp(username, admin.username) == 0 && strcmp(nickname, admin.nickname) == 0){
            menu_admin(username,nickname);
        }else{
            menu_user(username, nickname);
        }
    }else{
        puts("Pilihan salah! Silahkan pilih pilihan yang benar!");
        exit_acc(username,nickname);
    }
}