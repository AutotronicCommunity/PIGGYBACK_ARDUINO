const int inputPin = 2;    // Pin yang digunakan untuk input sinyal dari ECU
const int outputPin = 9;   // Pin yang digunakan untuk output sinyal ke injector
unsigned long highTime;    // Durasi HIGH dari sinyal input
unsigned long lowTime;     // Durasi LOW dari sinyal input
unsigned long period;      // Periode dari sinyal input
unsigned long newHighTime; // Durasi HIGH yang telah diubah
unsigned long newLowTime;  // Durasi LOW yang telah diubah
float fuel = 9.5; // tambah durasi fuel 9.5%

void setup() {
  pinMode(inputPin, INPUT);    // Set pin input sebagai INPUT
  pinMode(outputPin, OUTPUT);  // Set pin output sebagai OUTPUT
}

void loop() {
  // Membaca durasi HIGH dan LOW dari sinyal input
  highTime = pulseIn(inputPin, HIGH);
  lowTime = pulseIn(inputPin, LOW);

  // Menghitung periode dari sinyal input
  period = highTime + lowTime;

  // Mengubah durasi HIGH dengan menambah fuel persen
  newHighTime = highTime + (highTime / fuel); // Ton ditambah persen fuel

  // Menghitung durasi LOW yang baru
  newLowTime = period - newHighTime;

  // Menjamin bahwa newLowTime tidak negatif
  if (newLowTime < 0) {
    newLowTime = 0;
  }

  // Mengendalikan saklar transistor untuk menghasilkan sinyal baru
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(newHighTime);
  digitalWrite(outputPin, LOW);
  delayMicroseconds(newLowTime);
}
