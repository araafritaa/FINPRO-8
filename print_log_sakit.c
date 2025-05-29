#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void tampilkanLogKeluhan() {
    FILE *file = fopen("log_masalah.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file log_masalah.txt\n");
        return;
    }

    char baris[200];
    char tanggal[20], keluhan[50], daerah[100], durasi[50];
    int tingkatSakit;
    int status = 0;

    printf("\n=== LOG KELUHAN ===\n");

    while (fgets(baris, sizeof(baris), file)) {
        if (strstr(baris, "--- RINGKASAN MASALAH ---")) {
            status = 1;
            tanggal[0] = '\0'; keluhan[0] = '\0'; daerah[0] = '\0'; durasi[0] = '\0';
            tingkatSakit = 0;
        } else if (status == 1) {
            if (strstr(baris, "Tanggal")) {
                sscanf(baris, "Tanggal       : %[^\n]", tanggal);
            } else if (strstr(baris, "Keluhan")) {
                sscanf(baris, "Keluhan       : %[^\n]", keluhan);
            } else if (strstr(baris, "Daerah")) {
                sscanf(baris, "Daerah        : %[^\n]", daerah);
            } else if (strstr(baris, "Tingkat Sakit")) {
                sscanf(baris, "Tingkat Sakit : %d", &tingkatSakit);
            } else if (strstr(baris, "Durasi")) {
                sscanf(baris, "Durasi        : %[^\n]", durasi);
            }

            // Jika sudah lengkap
            if (tanggal[0] && keluhan[0] && daerah[0] && durasi[0] && tingkatSakit > 0) {
                printf("%s - %s - %s - %d/10 - %s\n", tanggal, keluhan, daerah, tingkatSakit, durasi);
                status = 0; // Reset status
            }
        }
    }

    printf("=================\n");
    fclose(file);
}