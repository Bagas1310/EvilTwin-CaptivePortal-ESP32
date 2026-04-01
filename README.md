# 📡 ESP32 Advanced Wireless Auditor (Universal Evil Twin)

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif" alt="Platform">
  <img src="https://img.shields.io/badge/Workstation-ThinkPad%20X270-red?style=for-the-badge&logo=lenovo" alt="Workstation">
  <img src="https://img.shields.io/badge/Focus-Network%20Security-green?style=for-the-badge&logo=wireshark" alt="Focus">
</p>

Repository ini berisi implementasi alat audit keamanan nirkabel berbasis ESP32 (WROOM-32U). Alat ini dirancang untuk mensimulasikan serangan *Evil Twin Captive Portal* secara universal. Fitur utamanya adalah kemampuan untuk memindai jaringan sekitar secara real-time, menyamar sebagai target mana pun, dan memverifikasi kredenisial korban secara langsung ke router asli (Real-time Handshake Validation).

---

## 📸 Antarmuka Sistem

| **C&C Admin Panel (Scanner)** | **Target View (Captive Portal)** |
|:---:|:---:|
| <img src="images/admin_scanner.png" width="400" alt="Admin Panel"> | <img src="images/mikrotik_portal.png" width="400" alt="MikroTik Portal"> |
| *Tampilan Dark Mode ala Cyber Auditor untuk memindai dan memilih target.* | *Tampilan palsu MikroTik Hotspot Gateway yang identik untuk memancing korban.* |

---

## 🔥 Fitur Unggulan

| Fitur | Deskripsi | Logika Kerja |
| :--- | :--- | :--- |
| **📶 Universal Scanner** | Memindai SSID, BSSID, dan kekuatan sinyal (RSSI) di sekitar secara real-time. | Menggunakan `WiFi.scanNetworks()` pada interval Reset. |
| **🎯 Dynamic Evil Twin** | Otomatis meniru SSID, Channel, dan MAC Address target yang dipilih dari panel admin. | Logika `handleSelect()` mengubah konfigurasi `softAP()` secara dinamis. |
| **⚔️ Integrated Deauther** | Memutuskan koneksi pengguna asli dari router target agar mereka terhubung ke portal palsu. | Menggunakan `esp_wifi_80211_tx()` untuk mengirim paket raw deauth. |
| **✅ Real-time Validation** | Memverifikasi password yang dimasukkan korban langsung ke router asli sebelum mencatatnya sebagai valid. | Menggunakan `WiFi.begin(targetSSID, attemptPass)` untuk mengecek koneksi. |
| **↻ Smart Reset** | Satu klik untuk menghentikan serangan, membersihkan variabel, dan kembali ke mode scan. | Handler khusus `/reset` mengembalikan ESP32 ke status idle. |

---

## 🛠️ Persyaratan Perangkat

### 1. Hardware
* **Board**: ESP32 WROOM-32U (disarankan memakai antena eksternal untuk jangkauan deauth lebih baik).
* **Laptop**: Lenovo ThinkPad X270 (Kerja Bagas).

### 2. Software (IDE)
* Arduino IDE (dengan Board Manager ESP32 terinstall).
* Library: `WiFi`, `DNSServer`, `WebServer`, `esp_wifi`.

---

## 🚀 Panduan Penggunaan

1.  **Koneksi Awal**: Nyalakan ESP32, hubungkan laptop/HP audit ke WiFi **`Esp32_Admin`**.
2.  **Akses Panel**: Buka browser ke alamat `192.168.4.1`.
3.  **Audit Jaringan**: Pada halaman **Scanner WiFi**, klik tombol **TARGET** di sebelah jaringan yang ingin diaudit.
4.  **Monitoring**: ESP32 akan mulai menyamar. Pantau Serial Monitor (Baud: 115200) untuk melihat password valid yang berhasil tertangkap.

---

## 🤝 Kontribusi

Proyek ini terbuka untuk kontribusi. Jika Anda menemukan bug atau memiliki ide fitur baru (misalnya: UI vendor lain), silakan buat *Issue* atau kirim *Pull Request*.

### 📜 Lisensi
Lisensi MIT. Lihat file `LICENSE` untuk detailnya.

### ⚠️ Disclaimer
*Alat ini dibuat murni untuk tujuan pendidikan dan pengujian keamanan yang sah (Ethical Hacking). Penulis tidak bertanggung jawab atas segala kerusakan atau penyalahgunaan yang dilakukan dengan alat ini. Gunakan hanya pada jaringan yang Anda miliki izin tertulis untuk mengujinya.*
