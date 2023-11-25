// Headers
#include <Servo.h>
#include <dht11.h>

// Pinnya masbro
#define DHTPIN 4
const int LedPin    = 6;
const int BuzzerPin = 7;
const int trigPin   = 10;
const int echoPin   = 11;

// Variabel-Variabel
long durasi;
int jarak;
Servo Ganteng;
dht11 DHT11;

// Fungsi itungJarak
int itungJarak() {
  // Menghitung jarak yang diukur HC-SR04
  // Mati
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Tembakkan gelombang ultrasonik
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Mati
  digitalWrite(trigPin, LOW);
  // Hitung selisih waktu hingga gelombang ditangkap echoPin (dalam ms)
  durasi = pulseIn(echoPin, HIGH);
  // Konversi durasi ke waktu (dengan kecepatan gelombang suara 340 m/s)
  jarak = durasi * 0.034 / 2;
  return jarak;
}

// Prosedur cekTmpHmd
void cekTmpHmd() {
  Serial.println();
  Serial.print((float)DHT11.temperature);
  Serial.print(",");
  Serial.print((float)DHT11.humidity);
  Serial.print(",");
}

// Prosedur servoMuter
void servoMuter() {
  // Memutar servo searah jarum jam sebesar 180 derajat
  for (int sudut = 0; sudut <= 180; sudut++) {
    cekTmpHmd();
    Ganteng.write(sudut);
    itungJarak();
    Serial.print(jarak);
    delay(10);
  }
  // Memutar servo berlawanan arah jarum jam sebesar 180 derajat
  for (int sudut = 180; sudut >= 0; sudut--) {
    Ganteng.write(sudut);
    itungJarak();
    Serial.print(jarak);
    cekTmpHmd();
    delay(10);
  }
}

// Prosedur KelapKelip
void KelapKelip() {
  for (int i = 0; i <= 100; i++) {
    digitalWrite(LedPin, HIGH);
    delay(2);
    digitalWrite(LedPin, LOW);
    delay(2);
  }
}

// BAGIAN UTAMA PROGRAM

void setup() {
  Serial.begin(9600);
  Ganteng.attach(12);        // Defines on which pin is the servo motor attached
  int chk = DHT11.read(DHTPIN);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Mengatur trigPin sebagai Output
  pinMode(echoPin, INPUT);   // Mengatur echoPin sebagai Input
  digitalWrite(LedPin, HIGH);
}

void loop() {
  servoMuter();
}
