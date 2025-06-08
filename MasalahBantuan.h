#ifndef MASALAH_BANTUAN_H
#define MASALAH_BANTUAN_H

#include "Tanggal.h"

struct Masalah {
    char keluhan[50];
    char daerah[100];
    int tingkatSakit;
    char durasi[50];
};

void masalah_dan_bantuan();

#endif // MASALAH_BANTUAN_H