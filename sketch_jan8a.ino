#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Pastikan alamat I2C sudah sesuai

int led1 = 6;  // LED hijau
int relayPin = 3; // Pin untuk relay

#define RST_PIN 9
#define SS_PIN 10

String MasterTag = "xxxxxxx";  // Ganti dengan Tag ID Anda
String tagID = "";

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Aktifkan backlight LCD
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // Inisialisasi RFID module
  
  pinMode(led1, OUTPUT);     // Konfigurasi LED hijau sebagai output
  pinMode(relayPin, OUTPUT); // Konfigurasi relay sebagai output
  
  digitalWrite(relayPin, LOW); // Pastikan relay dalam kondisi mati saat awal

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Kontrol Akses ");
  lcd.setCursor(0, 1);
  lcd.print("Scan kartu>>");
}

void loop() {
  Serial.begin(9600);
  
  // Tunggu hingga kartu tersedia
  if (getID()) {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (tagID == MasterTag) {
      lcd.print(" Akses diterima!");
      digitalWrite(led1, HIGH);       // Aktifkan LED hijau
      digitalWrite(relayPin, HIGH);  // Aktifkan relay (ON)
      
      // Tunda beberapa detik untuk memberikan waktu akses
      delay(2000); // Relay aktif selama 5 detik
      
      digitalWrite(relayPin, LOW);   // Matikan relay (OFF)
    } else {
      digitalWrite(led1, LOW); // Nonaktifkan LED hijau
      digitalWrite(relayPin, LOW); // Pastikan relay tetap mati
      lcd.print(" Akses ditolak!");
    }

    // Tampilkan UID pada LCD
    lcd.setCursor(0, 1);
    lcd.print(" ID : ");
    lcd.print(tagID);

    delay(2000); // Tunda 2 detik
    digitalWrite(led1, LOW); // Nonaktifkan LED hijau
    lcd.clear();
    lcd.print(" Akses kontrol ");
    lcd.setCursor(0, 1);
    lcd.print("Scan kartu>>");
  }
}

// Fungsi untuk membaca UID dari kartu RFID
boolean getID() {
  // Cek apakah kartu baru tersedia
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  
  // Membaca UID kartu
  tagID = "";
  for (uint8_t i = 0; i < mfrc522.uid.size; i++) { // mfrc522.uid.size adalah ukuran UID
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Tambahkan byte UID ke string
  }
  tagID.toUpperCase(); // Ubah ke huruf besar
  mfrc522.PICC_HaltA(); // Hentikan pembacaan kartu
  return true;
}
