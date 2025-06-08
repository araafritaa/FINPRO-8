#include "Profile.h"
#include <string.h>
#include <stdlib.h>

// fungsi buat nyimpen profil ke file
void simpanProfil(struct User user) {
    FILE *fp = fopen("log_profil.txt", "w"); // buka file, mode tulis

    if (fp != NULL) {
        // tulis data profil ke file, satu baris satu data
        fprintf(fp, "%s\n", user.nama);
        fprintf(fp, "%s\n", user.fase);
        fprintf(fp, "%s\n", user.periode);
        fprintf(fp, "%s\n", user.ortodontis);
        fprintf(fp, "%s\n", user.tanggal_kontrol);
        fprintf(fp, "%d\n", user.frekuensi_kontrol);
        fclose(fp); // jangan lupa ditutup yaa
        printf("Profil berhasil disimpan!\n");
    } else {
        // kalau file-nya gagal dibuka
        printf("Gagal menyimpan profil.\n");
    }
}

// fungsi buat ngecek apakah udah ada profil sebelumnya
int bacaProfil(struct User *user) {
    FILE *fp = fopen("log_profil.txt", "r"); // buka file dalam mode baca
    if (fp == NULL) return 0; // file belum ada

    // cek ukuran file, kalau 0 berarti kosong
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    if (size == 0) {
        fclose(fp);
        return 0; // file-nya kosong
    }

    // baca data dari file, terus hapus newline di tiap input
    fgets(user->nama, 50, fp);
    user->nama[strcspn(user->nama, "\n")] = '\0';

    fgets(user->fase, 15, fp);
    user->fase[strcspn(user->fase, "\n")] = '\0';

    fgets(user->periode, 30, fp);
    user->periode[strcspn(user->periode, "\n")] = '\0';

    fgets(user->ortodontis, 50, fp);
    user->ortodontis[strcspn(user->ortodontis, "\n")] = '\0';

    fgets(user->tanggal_kontrol, 11, fp);
    user->tanggal_kontrol[strcspn(user->tanggal_kontrol, "\n")] = '\0';

    fscanf(fp, "%d", &user->frekuensi_kontrol); // ini integer jadi pakai fscanf

    fclose(fp); // done baca data
    return 1; // profil berhasil dibaca
}

// fungsi buat input awal kalau belum ada data
void inputAwalProfil(struct User *user) {
    int pilihanFase;

    printf("\n===== INPUT AWAL / PROFIL =====\n");

    // input nama
    printf("Nama lengkap: ");
    fgets(user->nama, 50, stdin);
    user->nama[strcspn(user->nama, "\n")] = '\0';

    // pilih fase
    printf("Fase saat ini:\n");
    printf("[1] Pakai behel\n");
    printf("[2] Pakai retainer\n");
    printf("Pilihanmu (1/2): ");
    scanf("%d", &pilihanFase);
    getchar(); // buang newline dari buffer

    // simpan fase
    if (pilihanFase == 1) {
        strcpy(user->fase, "Behel");
    } else if (pilihanFase == 2) {
        strcpy(user->fase, "Retainer");
    } else {
        strcpy(user->fase, "Tidak Diketahui"); // fallback kalau salah input
    }

    // input periode
    printf("Periode pemakaian (riwayat): ");
    fgets(user->periode, 30, stdin);
    user->periode[strcspn(user->periode, "\n")] = '\0';

    // input ortodontis (boleh kosong)
    printf("Nama ortodontis (opsional): ");
    fgets(user->ortodontis, 50, stdin);
    user->ortodontis[strcspn(user->ortodontis, "\n")] = '\0';

    // input tanggal kontrol terakhir
    printf("Terakhir controlling (dd/mm/yyyy): ");
    fgets(user->tanggal_kontrol, 11, stdin);
    user->tanggal_kontrol[strcspn(user->tanggal_kontrol, "\n")] = '\0';

    // input frekuensi kontrol
    printf("Frekuensi kontrol rutin (30 / 45 / 60 hari): ");
    scanf("%d", &user->frekuensi_kontrol);
    getchar(); // bersihin newline

    // simpan datanya ke file
    simpanProfil(*user);
}