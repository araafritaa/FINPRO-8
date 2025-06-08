#ifndef TANGGAL_H
#define TANGGAL_H

#include <time.h>

// Deklarasi variabel global untuk tanggal saat ini
// 'extern' menandakan bahwa variabel ini didefinisikan di file .c lain
extern struct tm tanggalSekarang;

// Prototipe fungsi
void konversiKeTanggal(const char *tanggalStr, struct tm *date);
void formatTanggal(char *buffer, struct tm date);
void simpanTanggalSaatIni(struct tm date);
int bacaTanggalSaatIni(struct tm *date);

#endif // TANGGAL_H