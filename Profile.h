#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>

// struktur buat nyimpen data profil user
struct User {
    char nama[50];               // nama lengkap user
    char fase[15];               // fase (behel atau retainer)
    char periode[30];           // periode pemakaian
    char ortodontis[50];        // nama ortodontis, boleh kosong
    char tanggal_kontrol[11];   // terakhir kali kontrol
    int frekuensi_kontrol;      // kontrol rutin: 30 / 45 / 60 hari
};

// Prototipe fungsi
void simpanProfil(struct User user);
int bacaProfil(struct User *user);
void inputAwalProfil(struct User *user);

#endif // PROFILE_H