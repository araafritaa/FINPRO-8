#ifndef TANGGAL_H
#define TANGGAL_H

#include <time.h>

// Variabel global untuk tanggal saat ini
// 'extern' karena variabel ini didefinisikan di file .c lain
extern struct tm tanggalSekarang;

void konversiKeTanggal(const char *tanggalStr, struct tm *date);
void formatTanggal(char *buffer, struct tm date);
void simpanTanggalSaatIni(struct tm date);
int bacaTanggalSaatIni(struct tm *date);

#endif // TANGGAL_H