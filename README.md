⚡ ESP32 Universal Evil Twin - MikroTik Hotspot Edition
Repository ini berisi kodingan Advanced Wireless Security Auditing Tool menggunakan ESP32. Alat ini mampu melakukan pemindaian jaringan secara real-time, serangan deauthentikasi, dan penyajian Captive Portal MikroTik yang sangat meyakinkan untuk pengujian penetrasi legal.

✨ Fitur Utama
Universal WiFi Scanner: Memindai semua jaringan WiFi di sekitar secara real-time melalui web interface.

MikroTik Hotspot UI: Tampilan captive portal yang identik dengan login page MikroTik asli untuk meningkatkan keberhasilan audit.

Real-time Password Verification: ESP32 secara otomatis mencoba menghubungkan diri ke router asli untuk memvalidasi password yang dimasukkan korban.

Smart Auto-Reset: Serangan deauth berhenti otomatis jika password benar ditemukan, dan admin bisa melakukan scan ulang hanya dengan satu klik ikon refresh.

Cyber Admin Console: Antarmuka admin dengan tema Dark Mode yang responsif dan mudah digunakan.

🛠️ Hardware yang Digunakan
Microcontroller: ESP32 WROOM-32U (External Antenna).

Workstation: Lenovo ThinkPad X270 (Intel i7, 16GB RAM).

🚀 Cara Penggunaan
Upload kode .ino ke board ESP32 menggunakan Arduino IDE.

Hubungkan perangkat audit ke WiFi "Esp32_Admin".

Buka browser dan akses ke 192.168.4.1.

Gunakan SCANNER WIFI untuk memilih target jaringan.

Klik TARGET untuk memulai serangan deauth dan mengaktifkan portal palsu.

Pantau password yang masuk melalui Serial Monitor (115200 baud).

⚠️ Disclaimer
Proyek ini dibuat hanya untuk tujuan pendidikan dan pengujian keamanan jaringan yang sah (Bug Bounty/Ethical Hacking). Penulis tidak bertanggung jawab atas penyalahgunaan alat ini.
