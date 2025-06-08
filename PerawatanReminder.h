#ifndef PERAWATAN_REMINDER_H
#define PERAWATAN_REMINDER_H

#include "Profile.h"
#include "Tanggal.h"

// Prototipe fungsi
void menuPerawatan(const char *fase, struct User* user);
void cekReminderKontrol(struct User user);

#endif // PERAWATAN_REMINDER_H