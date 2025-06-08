#include "NextDay.h"
#include "Tanggal.h"
#include <stdio.h>
#include <time.h>

void nextDay() {
    time_t raw = mktime(&tanggalSekarang);
    raw += 86400; // tambah 1 hari
    tanggalSekarang = *localtime(&raw);
    simpanTanggalSaatIni(tanggalSekarang);
    printf("Tanggal sekarang telah diperbarui ke hari berikutnya.\n");
}