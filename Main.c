#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Include semua file header dari modul-modul yang sudah dibuat
#include "Tanggal.h"
#include "Profile.h"
#include "PerawatanReminder.h"
#include "MasalahBantuan.h"
#include "LaporanPerawatan.h"
#include "LogKeluhan.h"
#include "ResetData.h"
#include "NextDay.h"

int main() {
    struct User user;
    int pilihan;

    if (!bacaTanggalSaatIni(&tanggalSekarang)) {
        char tanggalAwal[12];
        printf("\nMasukkan tanggal awal (dd/mm/yyyy): ");
        fgets(tanggalAwal, sizeof(tanggalAwal), stdin);
        tanggalAwal[strcspn(tanggalAwal, "\n")] = '\0';
        konversiKeTanggal(tanggalAwal, &tanggalSekarang);
        simpanTanggalSaatIni(tanggalSekarang);
    }

    // Cek apakah sudah ada profil
    if (bacaProfil(&user)) {
        printf("Selamat datang kembali, %s!\n", user.nama);
    } else {
        printf("Selamat datang! Yuk lengkapi profil kamu terlebih dahulu.\n");
        inputAwalProfil(&user);
    }

    do {
        char tanggalBuffer[11];
        formatTanggal(tanggalBuffer, tanggalSekarang);
        
        cekReminderKontrol(user);
        
        printf("\nTanggal: %s\n", tanggalBuffer);
        printf("\n====== MENU UTAMA ======\n");
        printf("1. Profile\n");
        printf("2. Perawatan & Reminder\n");
        printf("3. Masalah & Bantuan\n");
        printf("4. Laporan Perawatan\n");
        printf("5. Log Keluhan\n");
        printf("6. Pengaturan & Reset\n");
        printf("7. Next Day\n");
        printf("8. Keluar\n");
        printf("Pilih menu (1-8): ");
        scanf("%d", &pilihan);
        getchar();  // buang newline dari input pilihan

        switch(pilihan) {
            case 1:
                printf("\n===== PROFILE =====\n");
                printf("Nama: %s\n", user.nama);
                printf("Fase: %s\n", user.fase);
                printf("Periode: %s\n", user.periode);
                printf("Ortodontis: %s\n", user.ortodontis);
                printf("Tanggal kontrol terakhir: %s\n", user.tanggal_kontrol);
                printf("Frekuensi kontrol: %d hari\n", user.frekuensi_kontrol);
                break;

            case 2:
                printf("\n======== PERAWATAN & REMINDER ========\n");
                menuPerawatan(user.fase, &user);
                break;
            
            case 3:
                printf("\n======== MASALAH & BANTUAN ========\n"); 
                masalah_dan_bantuan();
                break;

            case 4:
                printf("\n======== LAPORAN PERAWATAN ========\n");
                tampilkanRiwayatLengkap();
                break; 

            case 5:
                printf("\n======== LOG KELUHAN ========\n");
                tampilkanLogKeluhan();
                break;

            case 6:
                printf("\n======== PENGATURAN & RESET ========\n");    
                menuReset(&user);
                break;

            case 7:
                printf("\n======== NEXT DAY ========\n");
                nextDay();
                break;

            case 8:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihan != 8);
    return 0;
}