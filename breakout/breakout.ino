#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);


#define Direction 14 
#define Direction_RMB 15 
#define Data_of_left 300 
#define Data_of_right 650 
#define Data_of_up 100 
#define Data_of_down 950 
int muban = 1;
int Atmp; 
int Btmp;
byte DF = 1; 
int WX; 
byte WL; 
float BX, BY; 
boolean MAP[16][8]; 
float AX, AY; 
boolean WIN; 
int Data_of_sensor = 0; 
int Data_of_sensor_RMB = 0; 

void setup() {

Serial.begin(9600); 
pinMode(Direction,INPUT); 
pinMode(Direction_RMB,INPUT); 
start(); 
}

void loop() {
muban = 1;
Data_of_sensor = analogRead(Direction); 
Data_of_sensor_RMB = analogRead(Direction_RMB); 
if( Data_of_sensor <= Data_of_left) { WX -= 5; } 
if( Data_of_sensor >= Data_of_right) { WX += 5; } 
if( Data_of_sensor_RMB <= Data_of_up) { win(); } 
if( Data_of_sensor_RMB >= Data_of_down) { Reset(); } 
else { delay(1); } 


if (WIN == true) win();
if (WX < -(WL / 2)) WX = -(WL / 2); 
if (WX > 128 - (WL / 2)) WX = 128 - (WL / 2); 

BX += AX;
BY += AY;


if (BX > 125) {
BX = 125;
AX = -AX;
}
if (BX < 0) {
BX = 0;
AX = -AX;
}
if (BY >= 61) { 
BY = 61;
muban = 0;
draw();
AY = -AY;
}
if (BY < 0) {
BY = 0;
AY = -AY;
}


if (BX >= WX && BX <= WX + WL) {
if (BY >= 56 - 3 && BY <= 57 - 3) {

AX = -(((WX + (WL / 2)) - BX) / (WL / 2));
AX *= 1.8;
AY = -AY;
}
}


if (int(BX / 8) + 1 <= 16 && int(BY / 4) + 1 <= 8) {
Atmp = BX / 8;
Btmp = BY / 4;
if (MAP[Atmp][Btmp] == 1) {

MAP[Atmp][Btmp] = 0;

if (BY - 2 <= Btmp * 4 || BY >= Btmp * 4 + 4) {

AY = -AY;
} else
{
AX = -AX;
}
}
}


u8g.firstPage();
do {
draw();
} while ( u8g.nextPage() );
}


void start() {
WL = 32;
for (byte i = 1; i < DF; i++) {
WL = WL / 2; 
}
WX = 64 - (WL / 2); 
for (byte x = 0; x < 16; x++) {
for (byte y = 0; y < 8; y++) {
MAP[x][y] = 1; 
} 
}
BX = 64;
BY = 52; 
AX = 2;
AY = -2;
loop();
}


void draw() {
if(muban == 0)
{
fail(); 
}

if (muban == 1)
{
no_fail();
}
}


void fail()
{
for(int i=0;i<3;i++) 
{ 
u8g.firstPage(); 
do {
no_fail();
u8g.setFont(u8g_font_courB12);
u8g.setColorIndex(0); 
u8g.drawBox(20, 12, 88, 40); 

u8g.setColorIndex(1); 
u8g.setPrintPos(20, 30); 
u8g.print("Game Over");
} while ( u8g.nextPage() ); 
delay(500);

u8g.firstPage();
do {
no_fail();
u8g.setFont(u8g_font_courB12); 
u8g.setColorIndex(0); 
u8g.drawBox(20, 12, 88, 40); 

u8g.setColorIndex(1); 
u8g.setPrintPos(20, 30); 
u8g.print(""); 
} while ( u8g.nextPage() );
delay(500);

}
start();
}

void no_fail()
{
WIN = true;
u8g.drawBox(WX, 56, WL, 3); 
u8g.drawBox(int(BX), int(BY), 3, 3);
for (byte x = 0; x < 16; x++) {
for (byte y = 0; y < 8; y++) {
if (MAP[x][y] == 1) {
WIN = false;

u8g.drawBox(x * 8, y * 4, 7, 3);
}
}
}
}


void win() {
u8g.firstPage();
do {
draw();
u8g.setFont(u8g_font_courB12); 
u8g.setColorIndex(0); 
u8g.drawBox(20, 12, 88, 40);

u8g.setColorIndex(1); 
u8g.setPrintPos(30, 30);
u8g.print("You Win");
} while ( u8g.nextPage() );
delay (2000);
if (DF < 3) {
DF++; 
} else { 
DF = 1; 
}
start(); 
}


void Reset() {
u8g.firstPage();
do {
u8g.setFont(u8g_font_courB12); 
u8g.setColorIndex(1); 
u8g.setPrintPos(40, 30); 
u8g.print("Reset"); 
} while ( u8g.nextPage() );
delay (1500);
start();
}
