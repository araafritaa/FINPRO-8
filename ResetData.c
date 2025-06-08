#include "ResetData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi fungsi internal
void resetData();
void editProfil(struct User *user);

// Fungsi utama menu reset / pengaturan
void menuReset(struct User *user) {
    int pilih;
    do {
        printf("\nMENU RESET / PENGATURAN\n");
        printf("1. Reset Semua Data\n");
        printf("2. Edit Profil\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih menu (1-3): ");
        scanf("%d", &pilih);
        getchar();

        switch(pilih) {
            case 1:
                resetData(); // reset data dengan konfirmasi
                break;
            case 2:
                editProfil(user); // masuk ke menu edit profil
                break;
            case 3:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                break;
        }
    } while(pilih != 3);
}

// fungsi buat reset data, nanti bakal tanya konfirmasi dulu ya
void resetData() {
    char konfirmasi;
    printf("Apakah kamu yakin ingin menghapus semua data? (y/n): ");
    scanf(" %c", &konfirmasi);
    getchar();  // buang newline yang tersisa biar gak ganggu input selanjutnya

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Buka file buat dihapus isinya (mode "w" buat kosongin file)
        FILE *f1 = fopen("log_masalah.txt", "w");
        FILE *f2 = fopen("log_perawatan.txt", "w");
        FILE *f3 = fopen("log_profil.txt", "w");
        FILE *f4 = fopen("log_tanggalSekarang.txt", "w");
        if (f1 && f2 && f3 && f4) {
            // kalau file terbuka dengan baik, langsung ditutup aja
            fclose(f1);
            fclose(f2);
            fclose(f3);
            fclose(f4);
            printf("Semua data berhasil direset. Kamu bisa mulai mengisi ulang profilmu dari awal.\n");
            exit(0); // langsung keluar dari program
        } else {
            // kalo ada yang error waktu buka file
            printf("Gagal menghapus data. Pastikan file dapat diakses.\n");
        }
    } else {
        // Kalau user batal (n atau lainnya)
        printf("Reset dibatalkan. Tidak ada data yang dihapus.\n");
    }
}

// Fungsi buat menu edit profil yang looping sampe pilih "Kembali"
void editProfil(struct User *user) {
    int pilih;
    do {
        // Tampilin menu edit profil
        printf("\n===== EDIT PROFIL =====\n");
        printf("1. Ganti Nama\n");
        printf("2. Ganti Fase (1 = Behel, 2 = Retainer)\n");
        printf("3. Ganti Periode Pemakaian\n");
        printf("4. Ganti Nama Ortodontis\n");
        printf("5. Ganti Tanggal Terakhir Kontrol\n");
        printf("6. Ganti Frekuensi Kontrol Rutin (30/45/60 hari)\n");
        printf("7. Kembali\n");
        printf("Pilih (1-7): ");
        scanf("%d", &pilih);
        getchar(); // buang newline

        switch(pilih) {
            case 1:
                // Ganti nama
                printf("Masukkan nama baru: ");
                fgets(user->nama, sizeof(user->nama), stdin);
                // Buang newline yang biasanya masuk karena fgets
                user->nama[strcspn(user->nama, "\n")] = '\0';
                printf("Nama berhasil diperbarui!\n");
                break;

            case 2:
                // Ganti fase behel atau retainer
                printf("Masukkan fase saat ini (1 = Behel, 2 = Retainer): ");
                int fase;
                scanf("%d", &fase);
                getchar();
                if (fase == 1) strcpy(user->fase, "Behel");
                else if (fase == 2) strcpy(user->fase, "Retainer");
                else printf("Pilihan fase tidak valid.\n");
                printf("Fase berhasil diperbarui menjadi: %s\n", user->fase);
                break;

            case 3:
                // Ganti periode pemakaian
                printf("Masukkan periode pemakaian: ");
                fgets(user->periode, sizeof(user->periode), stdin);
                user->periode[strcspn(user->periode, "\n")] = '\0';
                printf("Periode berhasil diperbarui!\n");
                break;

            case 4:
                // Ganti nama ortodontis
                printf("Masukkan nama ortodontis: ");
                fgets(user->ortodontis, sizeof(user->ortodontis), stdin);
                user->ortodontis[strcspn(user->ortodontis, "\n")] = '\0';
                printf("Nama ortodontis berhasil diperbarui!\n");
                break;

            case 5:
                // Ganti tanggal kontrol terakhir
                printf("Masukkan tanggal terakhir kontrol (dd/mm/yyyy): ");
                fgets(user->tanggal_kontrol, sizeof(user->tanggal_kontrol), stdin);
                user->tanggal_kontrol[strcspn(user->tanggal_kontrol, "\n")] = '\0';
                printf("Tanggal kontrol berhasil diperbarui!\n");
                break;

            case 6:
                // Ganti frekuensi kontrol (30, 45, atau 60 hari)
                printf("Masukkan frekuensi kontrol (30/45/60): ");
                scanf("%d", &user->frekuensi_kontrol);
                getchar();
                if(user->frekuensi_kontrol == 30 || user->frekuensi_kontrol == 45 || user->frekuensi_kontrol == 60){
                    printf("Frekuensi kontrol berhasil diperbarui!\n");
                } else {
                    printf("Pilihan frekuensi tidak valid.\n");
                }
                break;

            case 7:
                // Kembali ke menu reset
                printf("Kembali.\n");
                break;

            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                break;
        }

        // Kalau gak pilih kembali, simpan data setelah edit
        if (pilih != 7) simpanProfil(*user);

    } while(pilih != 7);
}