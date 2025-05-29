#include <stdio.h>
#include <string.h>

// Membaca profil dari log_profil.txt
int bacaProfil(struct User *user) {
    FILE *fp = fopen("log_profil.txt", "r");
    if (fp == NULL) return 0;

    fgets(user->nama, sizeof(user->nama), fp);
    user->nama[strcspn(user->nama, "\n")] = '\0';

    fgets(user->fase, sizeof(user->fase), fp);
    user->fase[strcspn(user->fase, "\n")] = '\0';

    fgets(user->periode, sizeof(user->periode), fp);
    user->periode[strcspn(user->periode, "\n")] = '\0';

    fgets(user->ortodontis, sizeof(user->ortodontis), fp);
    user->ortodontis[strcspn(user->ortodontis, "\n")] = '\0';

    fgets(user->tanggal_kontrol, sizeof(user->tanggal_kontrol), fp);
    user->tanggal_kontrol[strcspn(user->tanggal_kontrol, "\n")] = '\0';

    fscanf(fp, "%d", &user->frekuensi_kontrol);

    fclose(fp);
    return 1;
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
    printf("----------------------------------------------\n");
    printf("%s\n", judul);
    printf("%s\n", logBaru);
    printf("----------------------------------------------\n");
}

// Menu 1: Daily Checklist
void dailyChecklist(const char *fase) {
    char tanggal[20];
    int frekuensi;
    char log[300];

    printf("Tanggal hari ini (DD/MM/YYYY): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\n")] = '\0';

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
        printf("\nSudah menggunakan retainer hari ini? (YES/NO): ");
        fgets(pakaiRetainer, sizeof(pakaiRetainer), stdin);
        pakaiRetainer[strcspn(pakaiRetainer, "\n")] = '\0';

        sprintf(log, "[RETAINER] %s - %s", tanggal, pakaiRetainer);
        tulisLog(log);
        tampilkanLogBaru("Rekap Hari Ini - Retainer", log);

        if (strcmp(pakaiRetainer, "YES") == 0 || strcmp(pakaiRetainer, "Yes") == 0) {
            printf("Great Job!\n");
        } else {
            printf("Jangan lupa menggunakan retainer sebelum tidur!\n");
        }
    }

}

// Menu 2: Update hasil controlling
void updateHasilKontrol() {
    char tanggal[20], dokter[50], klinik[50], prosedur[100], log[300];
    struct User user;

    printf("Tanggal (DD/MM/YYYY): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\n")] = '\0';

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
    if (bacaProfil(&user)) {
        strcpy(user.tanggal_kontrol, tanggal);
        simpanProfil(user);  // Gunakan fungsi yang sudah ada
        printf("Tanggal kontrol terakhir pada profil berhasil diperbarui.\n");
    } else {
        printf("Gagal membuka file profil.\n");
    }
}