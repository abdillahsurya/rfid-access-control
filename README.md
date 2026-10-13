# Sistem Kontrol Akses RFID

Sistem kontrol akses berbasis Arduino dan RFID. Kartu yang terdaftar mengaktifkan relay, kartu lain ditolak. Status ditampilkan di LCD I2C dan LED.

## Komponen
- Arduino (Uno/Nano)
- Modul RFID MFRC522
- LCD 16x2 dengan modul I2C (alamat 0x27)
- Modul relay
- LED hijau + resistor
- Kabel jumper dan breadboard

## Koneksi pin
| Komponen | Pin Arduino |
|---|---|
| MFRC522 RST | 9 |
| MFRC522 SDA/SS | 10 |
| MFRC522 MOSI / MISO / SCK | 11 / 12 / 13 |
| Relay | 3 |
| LED hijau | 6 |
| LCD I2C SDA / SCL | A4 / A5 |

## Library
- MFRC522
- LiquidCrystal_I2C

## Cara kerja
1. Dekatkan kartu ke modul RFID.
2. Arduino membaca UID dan membandingkannya dengan UID yang terdaftar.
3. Cocok: LCD "Akses diterima!", LED dan relay aktif selama 2 detik.
4. Tidak cocok: LCD "Akses ditolak!".

## Cara pakai
1. Buka file `.ino` di Arduino IDE.
2. Ganti `MasterTag` dengan UID kartumu.
3. Upload ke Arduino.

## Foto / video
(tambahkan foto rangkaian atau tautan video demo)
