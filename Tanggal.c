#include "Tanggal.h"
#include <stdio.h>
#include <string.h>

// Definisi variabel global tanggalSekarang
struct tm tanggalSekarang;

void konversiKeTanggal(const char *tanggalStr, struct tm *date) {
    sscanf(tanggalStr, "%d/%d/%d", &date->tm_mday, &date->tm_mon, &date->tm_year);
    date->tm_mon -= 1; // bulan mulai dari 0
    date->tm_year -= 1900; // tahun mulai dari 1900
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
}

void formatTanggal(char *buffer, struct tm date) {
    strftime(buffer, 11, "%d/%m/%Y", &date);
}

void simpanTanggalSaatIni(struct tm date) {
    FILE *fp = fopen("log_tanggalSekarang.txt", "w");
    if (fp) {
        char buf[11];
        formatTanggal(buf, date);
        fprintf(fp, "%s\n", buf);
        fclose(fp);
    }
}

int bacaTanggalSaatIni(struct tm *date) {
    FILE *fp = fopen("log_tanggalSekarang.txt", "r");
    if (!fp) return 0;
    char buf[11];
    if (fgets(buf, sizeof(buf), fp)) {
        buf[strcspn(buf, "\n")] = '\0';
        konversiKeTanggal(buf, date);
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}