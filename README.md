# EvilTwin-CaptivePortal-ESP32
Proyek riset simpel buat simulasi Evil Twin dan Captive Portal pakai ESP32. Fokusnya ke pengujian keamanan protokol 802.11 dan cara kerja autentikasi Wi-Fi.

## 🚀 Fitur Utama
* **WiFi Scanning:** Scan SSID dan BSSID target di sekitar secara real-time.
* **DNS Redirection:** Pakai DNS Server lokal buat nge-direct semua traffic ke IP 192.168.4.1.
* **Captive Portal:** UI login MikroTik (HTML/CSS) buat nangkep dan validasi password.
* **Deauth Frame:** Kirim paket deauthentication buat mutus koneksi client dari AP asli (buat keperluan testing).

## 🛠️ Cara Kerja
1. ESP32 nyari target AP dan channel-nya.
2. ESP32 bikin Access Point baru dengan SSID yang sama.
3. Client yang connect bakal kena force redirect ke halaman login (Captive Portal).
4. Password yang di-input bakal di-check langsung (ESP32 nyoba connect ke AP asli pakai password itu).
5. Kalau valid, password bakal muncul di Serial Monitor.

## 📦 Requirements
* Board ESP32 (WROOM-32U/sejenisnya).
* Library: `WiFi.h`, `DNSServer.h`, `WebServer.h`, `esp_wifi.h`.

## ⚠️ Disclaimer
Proyek ini cuma buat **tujuan edukasi dan riset keamanan**. Jangan disalahgunakan buat hal ilegal atau ngerugiin orang lain tanpa izin. Gue gak tanggung jawab atas segala bentuk penyalahgunaan tool ini.

## 📄 License
MIT License.
