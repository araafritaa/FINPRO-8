#include <stdio.h>
#include <time.h>

// Variabel global
int hariKe = 0;
time_t startDate;

// Fungsi untuk menampilkan tanggal
void tampilkanTanggal(time_t date) {
    char buffer[100];
    struct tm *tm_info = localtime(&date);
    strftime(buffer, sizeof(buffer), "Tanggal: %d %B %Y\n", tm_info);
    printf("%s\n", buffer);
}

// Fungsi utama
void jalankanTracker() {
    startDate = time(NULL);
    tampilkanTanggal(startDate);  // Tampilkan hari pertama

    char lanjut;
    while (1) {
        printf("Tekan Enter untuk Next Day (Ctrl+C untuk keluar)...\n");
        getchar();  // Tunggu user tekan Enter
        hariKe++;
        tampilkanTanggal(startDate + hariKe * 86400);
    }
}

int main() {
    jalankanTracker();
    return 0;
}