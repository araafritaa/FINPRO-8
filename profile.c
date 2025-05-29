#include <stdio.h>
#include <string.h>

// Struktur data untuk menyimpan profil user
struct User {
    char nama[50];               // Nama lengkap pengguna
    char fase[15];               // Fase pemakaian (Behel/Retainer)
    char periode[30];            // Riwayat atau periode pemakaian
    char ortodontis[50];         // Nama ortodontis (boleh dikosongkan)
    char tanggal_kontrol[11];    // Tanggal terakhir kontrol
    int frekuensi_kontrol;       // Pilihan frekuensi kontrol (30, 45, atau 60 hari)
};

// Fungsi untuk menyimpan profil ke dalam file
void simpanProfil(struct User user) {
    FILE *fp;

    // Buka file "log_profil.txt" dalam mode tulis (overwrite)
    fp = fopen("log_profil.txt", "w");

    if (fp != NULL) {
        // Tulis semua data ke dalam file, satu data per baris
        fprintf(fp, "%s\n", user.nama);
        fprintf(fp, "%s\n", user.fase);
        fprintf(fp, "%s\n", user.periode);
        fprintf(fp, "%s\n", user.ortodontis);
        fprintf(fp, "%s\n", user.tanggal_kontrol);
        fprintf(fp, "%d\n", user.frekuensi_kontrol);

        // Tutup file setelah selesai menulis
        fclose(fp);
        printf("Profil berhasil disimpan!\n");
    } else {
        // Jika file gagal dibuka
        printf("Gagal menyimpan profil.\n");
    }
}

// Fungsi untuk input awal saat program dijalankan pertama kali
void inputAwalProfil(struct User *user) {
    int pilihanFase;

    printf("=== INPUT AWAL / PROFIL ===\n");

    // Input nama lengkap pengguna
    printf("Nama lengkap: ");
    fgets(user->nama, 50, stdin);
    user->nama[strcspn(user->nama, "\n")] = '\0';  // Hapus newline dari input

    // Pilihan fase pemakaian
    printf("Fase saat ini:\n");
    printf("[1] Pakai behel\n");
    printf("[2] Pakai retainer\n");
    printf("Pilihanmu (1/2): ");
    scanf("%d", &pilihanFase);
    getchar(); // Hapus newline setelah scanf

    // Simpan fase berdasarkan input
    if (pilihanFase == 1) {
        strcpy(user->fase, "Behel");
    } else if (pilihanFase == 2) {
        strcpy(user->fase, "Retainer");
    } else {
        strcpy(user->fase, "Tidak Diketahui"); // fallback kalau input salah
    }

    // Input periode pemakaian
    printf("Periode pemakaian (riwayat): ");
    fgets(user->periode, 30, stdin);
    user->periode[strcspn(user->periode, "\n")] = '\0';

    // Input nama ortodontis (boleh dikosongkan)
    printf("Nama ortodontis (opsional): ");
    fgets(user->ortodontis, 50, stdin);
    user->ortodontis[strcspn(user->ortodontis, "\n")] = '\0';

    // Input tanggal terakhir kontrol
    printf("Terakhir controlling (dd-mm-yyyy): ");
    fgets(user->tanggal_kontrol, 11, stdin);
    user->tanggal_kontrol[strcspn(user->tanggal_kontrol, "\n")] = '\0';

    // Input frekuensi kontrol rutin
    printf("Frekuensi kontrol rutin (30 / 45 / 60 hari): ");
    scanf("%d", &user->frekuensi_kontrol);
    getchar(); // Hapus newline setelah scanf

    // Simpan profil yang telah diinput
    simpanProfil(*user);
}
