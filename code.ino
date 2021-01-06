#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LedControl.h> // include led control library
int DIN = D7; // define DIN pin to digital pin 10
int CS =  D4; // define CS pin to digital pin 11
int CLK = D5; // define CLK to digital pin 12
byte digit0[]=   {0x00,0x38,0x44,0x44,0x44,0x44,0x38,0x00}; // number 0 byte arrays custom character
byte digit1[]=   {0x00,0x10,0x30,0x50,0x10,0x10,0x7C,0x00}; // number 1 byte arrays custom character
byte digit2[]=   {0x00,0x38,0x6C,0x0C,0x18,0x30,0x7C,0x00}; // number 2 byte arrays custom character
byte digit3[]=   {0x00,0x78,0x08,0x38,0x08,0x08,0x78,0x00}; // number 3 byte arrays custom character
byte digit4[]=   {0x00,0x00,0x48,0x48,0x78,0x08,0x08,0x00}; // number 4 byte arrays custom character
byte digit5[]=   {0x00,0x3C,0x20,0x3C,0x04,0x04,0x3C,0x00}; // number 5 byte arrays custom character
byte digit6[]=   {0x00,0x7C,0x40,0x7C,0x44,0x44,0x7C,0x00}; // number 6 byte arrays custom character
byte digit7[]=   {0x00,0x3E,0x02,0x04,0x08,0x10,0x20,0x00}; // number 7 byte arrays custom character
byte digit8[]=   {0x00,0x3C,0x24,0x3C,0x24,0x24,0x3C,0x00}; // number 8 byte arrays custom character
byte digit9[]=   {0x00,0x78,0x48,0x78,0x08,0x08,0x08,0x00}; // number 9 byte arrays custom character
byte heart[] = {0x0, 0x66, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0};
byte dim[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
byte A[] = {0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42};
byte B[] = {0x78, 0x44, 0x44, 0x44, 0x78, 0x44, 0x44, 0x78};
byte C[] = {0x3c, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x3c};
byte D[] = {0xf8, 0x84, 0x82, 0x82, 0x82, 0x82, 0x84, 0xf8};
byte E[] = {0x7c, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x7c};
byte F[] = {0xf8, 0x80, 0x80, 0xe0, 0x80, 0x80, 0x80, 0x80};
byte G[] = {0x7c, 0x44, 0x40, 0x40, 0x5c, 0x44, 0x44, 0x7c};
byte H[] = {0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42};
byte I[] = {0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff};
byte J[] = {0x3e, 0x4, 0x4, 0x4, 0x4, 0x24, 0x24, 0x18};
byte K[] = {0x24, 0x28, 0x30, 0x20, 0x30, 0x28, 0x24, 0x24};
byte L[] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7c};
byte M[] = { 0xc3, 0xa5, 0x99, 0x81, 0x81, 0x81, 0x81, 0x0};
byte N[] = {0x81, 0xc1, 0xa1, 0x91, 0x89, 0x85, 0x83, 0x81};
byte O[] = {0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c};
byte P[] = {0x7c, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40};
byte Q[] = { 0x0, 0x7c, 0x44, 0x44, 0x44, 0x7c, 0x2, 0x0};
byte R[] = {0x7c, 0x42, 0x42, 0x42, 0x7c, 0x48, 0x44, 0x42};
byte S[] = {0x0, 0x3e, 0x20, 0x20, 0x3e, 0x2, 0x3e, 0x0};
byte T[] = {0x0, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0};
byte U[] = {0x0, 0x24, 0x24, 0x24, 0x24, 0x3c, 0x0, 0x0};
byte V[] = {0x0, 0x82, 0x82, 0xc6, 0x44, 0x38, 0x38, 0x0};
byte W[] = {0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xff};
byte X[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
byte Y[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, 0x18};
byte Z[] = {0xff, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0xff};
byte puppy[] = {0x81, 0x0, 0x42, 0x18, 0x18, 0x18, 0x3c, 0x0};
LedControl lc=LedControl(DIN,CLK,CS,0);
// Update with wifi ssid and password .

const char* ssid = "-------";
const char* password = "-------";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup(){
 Serial.begin(115200);
 lc.shutdown(0,false);      //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,5);      // Set the brightness, the maximum is 0,15
 lc.clearDisplay(0);        // and clear the display
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  //  connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Counter on if an 1 was received 
  switch((char) payload[0]){
    case '?': startcounter();break;
    case '<': printByte(heart);break;
    case '>': printByte(puppy);break;
    case '+': printByte(dim); break;
    case '0': printByte(digit0);break;
    case '1': printByte(digit1);break;
    case '2': printByte(digit2);break;
    case '3': printByte(digit3);break;
    case '4': printByte(digit4);break;
    case '5': printByte(digit5);break;
    case '6': printByte(digit6);break;
    case '7': printByte(digit7);break;
    case '8': printByte(digit8);break;
    case '9': printByte(digit9);break;
    case 'A': printByte(A);break;
    case 'B': printByte(B);break;
    case 'C': printByte(C);break;
    case 'D': printByte(D);break;
    case 'E': printByte(E);break;
    case 'F': printByte(F);break;
    case 'G': printByte(G);break;
    case 'H': printByte(H);break;
    case 'I': printByte(I);break;
    case 'J': printByte(J);break;
    case 'K': printByte(K);break;
    case 'L': printByte(L);break;
    case 'M': printByte(M);break;
    case 'N': printByte(N);break;
    case 'O': printByte(O);break;
    case 'P': printByte(P);break;
    case 'Q': printByte(Q);break;
    case 'R': printByte(R);break;
    case 'S': printByte(S);break;
    case 'T': printByte(T);break;
    case 'U': printByte(U);break;
    case 'V': printByte(V);break;
    case 'W': printByte(W);break;
    case 'X': printByte(X);break;
    case 'Y': printByte(Y);break;
    case 'Z': printByte(Z);break;
    }
}

void reconnect() {
  // case connection lost try to reconnect until we're reconnected
  while (!client.connected()) {
    Serial.print("MQTT connection reconecting...");
    // Attempt to connect
    if (client.connect("emmyyaged3an")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outMatrix", "It's ON!");
      // ... and resubscribe
      client.subscribe("inMatrix");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(500);
    }
  }
}


void loop(){ 
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); //maintaining connection to the server

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Counter #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}

void startcounter()
{
  printByte(digit0);
  delay(1000);
  printByte(digit1);
  delay(1000);
  printByte(digit2);
  delay(1000);
  printByte(digit3);
  delay(1000);
  printByte(digit4);
  delay(1000);
  printByte(digit5);
  delay(1000);
  printByte(digit6);
  delay(1000);
  printByte(digit7);
  delay(1000);
  printByte(digit8);
  delay(1000);
  printByte(digit9);
  delay(1000);
  printByte(heart);
  delay(1000);
}
void printByte(byte character [])
{
  lc.clearDisplay(0);
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]); // this is for blank
  }
}
