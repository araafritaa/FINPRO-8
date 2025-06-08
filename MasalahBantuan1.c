#include "MasalahBantuan.h"
#include <stdio.h>
#include <string.h>

void masalah_dan_bantuan() {
    struct Masalah log;
    int pilihan;
    FILE *file = fopen("log_masalah.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file log_masalah.txt\n");
        return; // Keluar dari fungsi tanpa mengembalikan nilai
    }

    // Gunakan tanggal global
    char tanggal[12];
    formatTanggal(tanggal, tanggalSekarang);
    
    // Menu keluhan
    printf("Pilih keluhan yang kamu alami:\n");
    printf("1. Sariawan\n");
    printf("2. Kawat menusuk\n");
    printf("3. Gusi bengkak\n");
    printf("4. Nyeri rahang\n");
    printf("5. Lainnya\n");
    printf("Pilih nomor keluhan (1-5): ");
    scanf("%d", &pilihan);
    getchar(); // bersihkan newline

    // Simpan nama keluhan berdasarkan pilihan
    switch(pilihan) {
        case 1: strcpy(log.keluhan, "Sariawan"); break;
        case 2: strcpy(log.keluhan, "Kawat menusuk"); break;
        case 3: strcpy(log.keluhan, "Gusi bengkak"); break;
        case 4: strcpy(log.keluhan, "Nyeri rahang"); break;
        case 5:
            printf("Tulis keluhan lainnya: ");
            fgets(log.keluhan, sizeof(log.keluhan), stdin);
            strtok(log.keluhan, "\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            fclose(file); // Tutup file sebelum keluar
            return;
    }

    // Input tambahan
    printf("\nDaerah yang sakit? ");
    fgets(log.daerah, sizeof(log.daerah), stdin);
    strtok(log.daerah, "\n");

    printf("Tingkat sakit (1-10)? ");
    scanf("%d", &log.tingkatSakit);
    getchar();

    printf("Durasi (udah berapa lama)? ");
    fgets(log.durasi, sizeof(log.durasi), stdin);
    strtok(log.durasi, "\n");

    int parah = log.tingkatSakit >= 5;

    // Tampilkan ringkasan
    printf("===============================================\n");
    printf("Ringkasan keluhan kamu:\n");
    printf("Tanggal       : %s\n", tanggal);
    printf("Keluhan       : %s\n", log.keluhan);
    printf("Daerah        : %s\n", log.daerah);
    printf("Tingkat Sakit : %d\n", log.tingkatSakit);
    printf("Durasi        : %s\n", log.durasi);
    printf("===============================================\n");

    // Simpan ke file
    fprintf(file, "\n===== RINGKASAN MASALAH =====\n");
    fprintf(file, "Tanggal       : %s\n", tanggal);
    fprintf(file, "Keluhan       : %s\n", log.keluhan);
    fprintf(file, "Daerah        : %s\n", log.daerah);
    fprintf(file, "Tingkat Sakit : %d\n", log.tingkatSakit);
    fprintf(file, "Durasi        : %s\n", log.durasi);

    // Tips penanganan
    if (parah) {
        printf("Tingkat sakit tinggi! Disarankan segera ke ortodontis.\n");
        printf("\nKamu bisa mengirimkan ini ke ortho:\n");
        printf("\"Halo, saya punya keluhan %s di daerah bagian %s dengan tingkat sakit %d dan udah berlangsung selama %s\"\n",
               log.keluhan, log.daerah, log.tingkatSakit, log.durasi);
    } else {
        printf("Tips penanganan awal:\n");
        switch (pilihan) {
            case 1:
                printf("- Berkumur dengan air garam hangat: Campurkan 1 sendok teh garam ke dalam segelas air hangat dan berkumur selama 30 detik, 2-3 kali sehari\n");
                printf("- Gunakan orthodontic wax: Oleskan wax pada bagian behel yang tajam untuk mengurangi gesekan dengan jaringan mulut.\n");
                printf("- Konsumsi makanan lunak: Hindari makanan keras, pedas, atau asam yang dapat memperparah sariawan\n");
                printf("- Jaga kebersihan mulut: Sikat gigi secara teratur dan gunakan benang gigi untuk mencegah infeksi\n");
                printf("- Perbanyak minum air putih: Menjaga kelembapan mulut dapat membantu proses penyembuhan.\n");
                break;
            case 2:
                printf("- Gunakan orthodontic wax: Tutup ujung kawat yang menusuk dengan wax untuk mengurangi iritasi.\n");
                printf("- Potong kawat yang berlebih: Jika memungkinkan, potong ujung kawat yang menusuk dengan gunting kuku yang bersih.\n");
                printf("- Kompres dengan es batu: Tempelkan es batu yang dibungkus kain pada area yang sakit untuk mengurangi pembengkakan.\n");
                printf("- Konsultasikan dengan ortodontis: Segera hubungi dokter gigi untuk penanganan lebih lanjut.\n");
                break;
            case 3:
                printf("- Kompres dingin: Tempelkan es batu yang dibungkus kain pada area yang bengkak untuk mengurangi pembengkakan\n");
                printf("- Berkumur dengan air garam: Campurkan 1 sendok teh garam ke dalam segelas air hangat dan berkumur selama 30 detik.\n");
                printf("- Gunakan obat kumur antiseptik.Gunakan obat kumur antiseptik: Pilih obat kumur yang mengandung bahan antiseptik untuk membantu mengurangi peradangan.\n");
                printf("- Hindari makanan keras: Konsumsi makanan lunak untuk mengurangi tekanan pada gusi.\n");
                printf("- Jaga kebersihan mulut: Sikat gigi dengan sikat gigi khusus behel dan gunakan benang gigi secara teratur\n");
                break;
            case 4:
                printf("- Kompres hangat atau dingin: Gunakan kompres hangat atau dingin pada area rahang yang nyeri untuk meredakan ketegangan otot.\n");
                printf("- Konsumsi makanan lunak: Hindari makanan keras atau kenyal yang dapat memperparah nyeri.\n");
                printf("- Lakukan peregangan rahang: Buka dan tutup mulut perlahan untuk membantu meredakan ketegangan.\n");
                printf("- Minum obat pereda nyeri: Jika diperlukan, konsumsi obat pereda nyeri sesuai anjuran dokter.\n");
                printf("- Konsultasikan dengan ortodontis: Jika nyeri berlanjut, segera hubungi dokter gigi untuk evaluasi lebih lanjut.\n");
                break;
            case 5:
                printf("- Jaga kebersihan mulut.\n");
                printf("- Hindari makanan keras dan lengket.\n");
                printf("- Minum cukup air putih.\n");
                break;
        }
        fprintf(file, "Penanganan Awal : Lihat tips sesuai keluhan.\n");
    }

    fclose(file);
}