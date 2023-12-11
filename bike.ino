#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>


char ssid[] ="Itreek";// "Shriya";//JioFiber-QhM58";
char pass[] ="7893031134"; //"akarsh12";//"9550286930";
const char serverAddress[] = "script.google.com";  // server address
String sheet_id ="AKfycbwFqbFzFRKrvuPZ16Z8ON3mqmQrKZ-6K0d3I-Be2I0qG1Mm_-210CRZKr2yGZTL_I6s";
int port = 443;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid); 
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {

  while(IMU.accelerationAvailable() && IMU.gyroscopeAvailable()){
  float ax, ay, az,gx,gy,gz;
  IMU.readAcceleration(ax, ay, az);
  IMU.readGyroscope(gx, gy, gz);

  String aax=String(ax,6);
  String aay=String(ay,6);
  String aaz=String(az,6);
  
  String ggx=String(gx,6);
  String ggy=String(gy,6);
  String ggz=String(gz,6);
  
  unsigned long currentMillis = millis();
  unsigned long seconds = currentMillis / 1000;
  
  int secondsInMinute = seconds % 60;
  int minutesInHour = (seconds / 60) % 60;
  int hoursInDay = (seconds / 3600) % 24;

  Serial.print(hoursInDay);
  Serial.print(':');
  Serial.print(minutesInHour);
  Serial.print(':');
  Serial.println(secondsInMinute);

  Serial.print(ax);
  Serial.print('\t');
  Serial.print(ay);
  Serial.print('\t');
  Serial.print(az);
  Serial.print('\t');

  Serial.print(gx);
  Serial.print('\t');
  Serial.print(gy);
  Serial.print('\t');
  Serial.println(gz);

  String path = ("/macros/s/" + sheet_id + "/exec?ax=" + aax + "&ay=" + aay + "&az=" + aaz + "&gx="+ggx+ "&gy=" + ggy + "&gz="+ ggz);

  Serial.println("making GET request");
  client.get(path);
  client.stop();  
  }
  delay (10);
}
