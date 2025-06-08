#include "PerawatanReminder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Deklarasi fungsi internal yang hanya digunakan di file ini
void dailyChecklist(const char *fase);
void updateHasilKontrol(struct User* user);
void tulisLog(const char *logEntry);
void tampilkanLogBaru(const char *judul, const char *logBaru);

// Fungsi menu untuk memilih Daily Checklist atau Update Kontrol
void menuPerawatan(const char *fase, struct User* user) {
    int pilihan;

    do {
        printf("\nMENU PERAWATAN\n");
        printf("1. Daily Checklist\n");
        printf("2. Update Hasil Kontrol\n");
        printf("3. Kembali\n");
        printf("Pilih salah satu (1-3): ");
        scanf("%d", &pilihan);
        getchar(); // Buang newline

        switch (pilihan) {
            case 1:
                dailyChecklist(fase);
                break;
            case 2:
                updateHasilKontrol(user);
                break;
            case 3:
                printf("Kembali ke menu sebelumnya...\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 3);
}

// Fungsi untuk menambahkan log ke satu file log_perawatan.txt
void tulisLog(const char *logEntry) {
    FILE *fp = fopen("log_perawatan.txt", "a"); // mode append
    if (fp != NULL) {
        fprintf(fp, "%s\n", logEntry);
        fclose(fp);
    } else {
        printf("Gagal menyimpan log ke log_perawatan.txt\n");
    }
}

// Fungsi untuk menampilkan log baru
void tampilkanLogBaru(const char *judul, const char *logBaru) {
    printf("===============================================\n");
    printf("%s\n", judul);
    printf("%s\n", logBaru);
    printf("===============================================\n");
}

// Menu 1: Daily Checklist
void dailyChecklist(const char *fase) {
    char tanggal[12];
    int frekuensi;
    char log[300];
    
    // Ambil tanggal dari tanggalSekarang
    formatTanggal(tanggal, tanggalSekarang);
    printf("\nTanggal: %s\n", tanggal);

    printf("Frekuensi sikat gigi hari ini: ");
    scanf("%d", &frekuensi);
    getchar();

    // Tambahkan log sikat gigi
    sprintf(log, "[SIKAT GIGI] %s - %d kali", tanggal, frekuensi);
    tulisLog(log);
    tampilkanLogBaru("Rekap Hari Ini - Sikat Gigi", log);

    printf("Data tersimpan.\n");

    if (frekuensi >= 2) {
        printf("Kamu sudah memenuhi target hari ini! Great Job!\n");
    } else {
        printf("Masih kurang %d kali, Jangan lupa sikat gigi!\n", 2 - frekuensi);
    }

    // Jika fase adalah Retainer, tambahkan pertanyaan
    if (strcmp(fase, "Retainer") == 0) {
        char pakaiRetainer[10];
        printf("\nSudah menggunakan retainer hari ini? (y/n): ");
        fgets(pakaiRetainer, sizeof(pakaiRetainer), stdin);
        pakaiRetainer[strcspn(pakaiRetainer, "\n")] = '\0';

        sprintf(log, "[RETAINER] %s - %s", tanggal, pakaiRetainer);
        tulisLog(log);
        tampilkanLogBaru("Rekap Hari Ini - Retainer", log);

        if (strcmp(pakaiRetainer, "y") == 0 || strcmp(pakaiRetainer, "Y") == 0) {
            printf("Great Job!\n");
        } else {
            printf("Jangan lupa menggunakan retainer sebelum tidur!\n");
        }
    }

}

// Menu 2: Update hasil controlling
void updateHasilKontrol(struct User* user) {
    char tanggal[12], dokter[50], klinik[50], prosedur[100], log[300];
    char pilihan;

    // Tawarkan opsi input tanggal
    printf("\nGunakan tanggal hari ini? (y/n): ");
    scanf(" %c", &pilihan);
    while (getchar() != '\n'); // buang seluruh karakter hingga newline

    if (pilihan == 'y' || pilihan == 'Y') {
        formatTanggal(tanggal, tanggalSekarang); // dari tanggalSekarang
    } else {
        printf("Masukkan tanggal kontrol (dd/mm/yyyy): ");
        fgets(tanggal, sizeof(tanggal), stdin);
        tanggal[strcspn(tanggal, "\n")] = '\0';
    }

    printf("Nama Dokter Gigi: ");
    fgets(dokter, sizeof(dokter), stdin);
    dokter[strcspn(dokter, "\n")] = '\0';

    printf("Nama Klinik: ");
    fgets(klinik, sizeof(klinik), stdin);
    klinik[strcspn(klinik, "\n")] = '\0';

    printf("Prosedur (ngapain): ");
    fgets(prosedur, sizeof(prosedur), stdin);
    prosedur[strcspn(prosedur, "\n")] = '\0';

    sprintf(log, "[KONTROL] %s - %s/%s - %s", tanggal, dokter, klinik, prosedur);
    tulisLog(log);
    tampilkanLogBaru("Rekap Hari Ini - Hasil Kontrol", log);

    // Update tanggal kontrol terakhir di profil
    if (bacaProfil(user)) {
        strcpy(user->tanggal_kontrol, tanggal);
        simpanProfil(*user);
        printf("Tanggal kontrol terakhir pada profil berhasil diperbarui.\n");
    } else {
        printf("Gagal membuka file profil.\n");
    }
}

void cekReminderKontrol(struct User user) {
    struct tm t_kontrol;
    konversiKeTanggal(user.tanggal_kontrol, &t_kontrol);

    // Tambah frekuensi hari ke tanggal kontrol terakhir
    time_t kontrol_berikutnya = mktime(&t_kontrol) + user.frekuensi_kontrol * 86400;
    time_t sekarang = mktime(&tanggalSekarang);

    double selisih_hari = difftime(kontrol_berikutnya, sekarang) / 86400;

    if (selisih_hari <= 3 && selisih_hari >= 0) {
        if ((int)selisih_hari == 0) {
            printf("\n========================== REMINDER ==========================\n");
            printf("Hari ini jadwal kontrol kamu! Jangan lupa datang ke klinik ya.\n");
            printf("==============================================================\n");
        } else {
            printf("\n===================================== REMINDER =====================================\n");
            printf("Jadwal kontrol berikutnya tinggal %.0f hari lagi! Siapkan diri dan buat janji dulu yuk.\n", selisih_hari);
            printf("====================================================================================\n");
        }
    }
}