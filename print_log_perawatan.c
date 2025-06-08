void tampilkanRiwayatLengkap() {
    struct User user;
    if (!bacaProfil(&user)) {
        printf("Gagal membaca profil pengguna.\n");
        return;
    }

    printf("=== RIWAYAT LENGKAP ===\n");
    printf("Nama: %s\n", user.nama);
    printf("Fase: %s\n", user.fase);
    printf("Periode Pemakaian: %s\n", user.periode);
    printf("Terakhir Controlling: %s\n", user.tanggal_kontrol);
    printf("----------------------------------------------\n");

    FILE *fp = fopen("log_perawatan.txt", "r");
    if (fp == NULL) {
        printf("Belum ada log perawatan.\n");
        return;
    }

    char line[300];

    // Log Perawatan
    printf("Log Perawatan\n");
    rewind(fp); // Kembali ke awal file
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "[KONTROL]", 9) == 0) {
            // Format: [KONTROL] tanggal - dokter/klinik - prosedur
            char tanggal[20], info[200];
            sscanf(line, "[KONTROL] %[^-] - %[^\n]", tanggal, info);
            printf("%s - %s\n", tanggal, info);
        }
    }

    // Log Sikat Gigi
    printf("----------------------------------------------\n");
    printf("Log Sikat Gigi\n");
    rewind(fp);
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "[SIKAT GIGI]", 12) == 0) {
            char tanggal[20], frekuensi[20];
            sscanf(line, "[SIKAT GIGI] %[^-] - %[^\n]", tanggal, frekuensi);
            printf("%s - %s\n", tanggal, frekuensi);
        }
    }

    // Log Retainer
    if (strcmp(user.fase, "Retainer") == 0) {
        printf("----------------------------------------------\n");
        printf("Log Retainer\n");
        rewind(fp);
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "[RETAINER]", 10) == 0) {
                char tanggal[20], status[10];
                sscanf(line, "[RETAINER] %[^-] - %[^\n]", tanggal, status);
                printf("%s - %s\n", tanggal, status);
            }
        }
    }

    printf("----------------------------------------------\n");

    fclose(fp);
}