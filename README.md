# 📡 ESP32 Advanced Wireless Auditor (Universal Evil Twin)

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif" alt="Platform">
  <img src="https://img.shields.io/badge/Framework-Arduino-pro?style=for-the-badge&logo=arduino" alt="Framework">
  <img src="https://img.shields.io/badge/Focus-Network%20Security-green?style=for-the-badge&logo=wireshark" alt="Focus">
</p>

Repository ini berisi implementasi alat audit keamanan nirkabel berbasis **ESP32 (WROOM-32U)**. Proyek ini dirancang untuk mensimulasikan serangan *Evil Twin Captive Portal* secara universal dengan fitur pemindaian jaringan *real-time* dan verifikasi kredensial otomatis yang divalidasi langsung terhadap router target.

---

## 📸 Antarmuka Sistem

| **C&C Admin Panel (Scanner)** | **Target View (Captive Portal)** |
|:---:|:---:|
| <img src="admin_scanner.jpeg" height="230"> | <img src="mikrotik_portal.jpeg" height="230"> |
| *Panel kontrol untuk memindai WiFi secara real-time.* | *Tampilan login MikroTik untuk validasi kredensial.* |

---

## 🔥 Fitur Utama

| Fitur | Deskripsi | Logika Kerja |
| :--- | :--- | :--- |
| **📶 Universal Scanner** | Memindai SSID, BSSID, dan RSSI secara *real-time*. | `WiFi.scanNetworks()` pada interval asinkron. |
| **🎯 Dynamic Evil Twin** | Meniru SSID target secara dinamis tanpa *hardcode*. | Rekonfigurasi `softAP()` berdasarkan input Admin. |
| **⚔️ Integrated Deauther** | Memutus koneksi klien asli agar berpindah ke portal audit. | Injeksi paket 802.11 via `esp_wifi_80211_tx()`. |
| **✅ Real-time Validation** | Verifikasi *password* instan terhadap router asli. | Mencoba jabat tangan via `WiFi.begin()` untuk cek validitas. |
| **↻ Smart Reset** | Menghentikan serangan dan kembali ke mode *idle*. | Handler `/reset` untuk membersihkan status perangkat. |

---

## 🛠️ Alur Kerja (Proof of Concept)

Proses audit mengikuti siklus hidup serangan *Man-in-the-Middle* yang terotomatisasi:

1.  **Scanning**: ESP32 melakukan pemindaian menyeluruh terhadap spektrum 2.4GHz di sekitar.
2.  **Selection**: Melalui Panel Admin, pengguna menentukan target SSID yang akan diaudit.
3.  **Deauthentication**: Alat mengirimkan paket *deauth* untuk memaksa klien target terputus dari router asli.
4.  **Evil Twin & Captive Portal**: ESP32 membuat akses poin palsu dengan nama yang sama. DNS Server internal mengarahkan target ke portal login MikroTik secara otomatis.
5.  **Validation**: *Password* yang dimasukkan target akan langsung diverifikasi ke router asli secara *real-time* sebelum dianggap valid oleh sistem.

---

## 🚀 Panduan Setup & Penggunaan

1.  **Persiapan Gambar**: Pastikan file `admin_scanner.jpeg` dan `mikrotik_portal.jpeg` berada di root repository agar muncul di README.
2.  **Koneksi**: Nyalakan ESP32 dan hubungkan perangkat Anda ke WiFi **`Esp32_Admin`**.
3.  **Akses Panel**: Buka browser dan akses alamat IP `192.168.4.1`.
4.  **Audit**: Pilih target dari daftar hasil pemindaian, lalu klik **TARGET/ATTACK**.
5.  **Monitoring**: Pantau log kredensial yang masuk melalui Serial Monitor pada **Baud Rate 115200**.

---

## ⚠️ Disclaimer
*Proyek ini dikembangkan hanya untuk **tujuan edukasi** dan audit keamanan yang sah. Segala bentuk penyalahgunaan di luar lingkungan pengujian yang diizinkan adalah tanggung jawab pengguna sepenuhnya. Penulis tidak bertanggung jawab atas kerugian yang ditimbulkan oleh penggunaan alat ini.*
