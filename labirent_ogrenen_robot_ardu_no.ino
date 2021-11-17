//Sağa dönüş#define fthold 12 // Duz gidis icin esik degeri
#define rthold 20 // Saga donus icin esik degeri
#define lthold 20 // Sola donus icin esik degeri
//Dönme zamanları
const int t = 1050; 
int tfr =2750; 
int timefr; 
int tlbef=440; 
int tlaf = 1150; 
int nf =0; // Doğrudan saga secme sayısı.
int nlr=0; // Sola donuş sayısı.
bool found=false; // True ise ,bitti.
 
int dir[100]; // Degerlerin tutulacagı dizi
int i=-1; // İndisler
int j=0; // Kavsak sayısı
// On sensor .
const int trigPinf = 2;
const int echoPinf = 6;
// Sag sensor
const int trigPinr = 8;
const int echoPinr = 5;
// Sol sensor
const int trigPinl = 3;
const int echoPinl = 9;
//Booleans duvarları tanımak için.
bool fsensor; // On sensor
bool rsensor; // Sag sensor
bool lsensor; // Sol sensor
// 5 elamanlı dizi
float middleval(float arr[])
{
 for(int p=0;p<4;p++)
 {
 for(int q=0;q<4;q++)
 {
//En kısa yol
 if(arr[q]>arr[q+1])
 {
 int temp = arr[q];
 arr[q] = arr[q+1];
 arr[q+1] = temp;
 } } }
 return arr[2]; // Ortanca değer.
}
// İleri gitme
void gofront()
{
 float ldist1 = leftdist();
 float lconst = ldist1;
 while(ldist1<=5) // Sağa yönelme
 {
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 delay(t/65);
ldist1 = leftdist();
 if(abs(lconst - ldist1)>=0.8||(ldist1>=3.6)){break;}
 }
 float rdist1 = rightdist();
 float rconst = rdist1;
 while(rdist1<=5.4) // Sola yönelme
 {
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);
 delay(t/65);
 rdist1 = rightdist();
 if(abs(rconst - rdist1)>=0.9){break;}
 }
if(leftdist()>=7.2) // sol duvarda hareket
 {
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW); 
 delay(t/30);
 }
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);
 }
 
 
 
// Ön duvardan mesafesi 
float frontdist()
{
float gapf;float ticktockf;
digitalWrite(trigPinf,LOW);
delayMicroseconds(2);
digitalWrite(trigPinf,HIGH);
delayMicroseconds(10);
digitalWrite(trigPinf,LOW);
ticktockf = pulseIn(echoPinf,HIGH); // 1 sn 29 ms
gapf = ticktockf*0.0344/2;
return gapf;
}
// Sağ duvar mesafesi
float rightdist()
{
 float gapr;float ticktockr;
 digitalWrite(trigPinr,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPinr,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinr,LOW);
 ticktockr = pulseIn(echoPinr,HIGH);
 gapr = ticktockr*0.0344/2;
 return gapr;
}
// Sol duvar mesafesi
float leftdist()
{
 float gapl;float ticktockl;
 
 digitalWrite(trigPinl,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPinl,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinl,LOW);
 ticktockl = pulseIn(echoPinl,HIGH);
 gapl = ticktockl*0.0334/2;
 return gapl;
}
// Geri dönüş dizisi.
void reduce(int dir[], int &pt)
{
int i=pt;
if(i>=2)
 {
 //Sag U Sol 
 if((dir[i-1]==3)&&(dir[i-2]==2)&&(dir[i]==1))
 {
 dir[i-2]=3;
 pt = pt -2;
 }
 //Sol U SOL
 else if((dir[i-1]==3)&&(dir[i-2]==1)&&(dir[i]==1))
 {
 dir[i-2]=0;
 pt = pt -2;
 }
 //Sol U Sağ
 else if((dir[i-1]==3)&&(dir[i-2]==1)&&(dir[i]==2)) {
 dir[i-2]=3;
 pt = pt -2;
 }
//Düz U Düz 
else if((dir[i-1]==3)&&(dir[i-2]==0)&&(dir[i]==0))
 {
 dir[i-2]=3;
 pt = pt -2;
 }
//Düz U Sol
else if((dir[i-1]==3)&&(dir[i-2]==0)&&(dir[i]==1))
 {
 dir[i-2]=2;
 pt = pt -2;
 }
//Sol U Düz
else if((dir[i-1]==3)&&(dir[i-2]==1)&&(dir[i]==0))
 {
 dir[i-2]=2;
 pt = pt -2;
 }
return;
 } }
// Robotu durdur
void stopit()
{
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW); }
// Kısa yol solda olduğunda
void frontturn()
{
 for(int n=1;n<=8;n++)
 {gofront();delay((timefr)/8);}
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 delay(1000);
}
// Kısa yol sağda olduğunda
void rightturn()
{ stopit();delay(1000);
 float prevfdist = frontdist();
 for(int n=1;n<=5;n++)
 {gofront();delay(260);}
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,HIGH);
 delay(t);
 float prevfrdist = frontdist();
 while( abs(frontdist()-prevfrdist)<=18)
{gofront();delay(300);}
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 delay(1000); }

void setup() {
  // put your setup code here, to run once:
//Pinler
 pinMode (trigPinf,OUTPUT);
 pinMode (echoPinf,INPUT);
 pinMode (trigPinr,OUTPUT);
 pinMode (echoPinr,INPUT);
 pinMode (trigPinl,OUTPUT);
 pinMode (echoPinl,INPUT);
 // Motor pinleri
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(12,OUTPUT);
 pinMode(13,OUTPUT);
 Serial.begin(9600); 
}
}

void loop() {
  // put your main code here, to run repeatedly:
 if(nlr==7)
 {
 found=true; // Sona ulaşıldığında
 for(int i=0;i<=2;i++){Serial.print(dir[i]);}
i=-1;j=0; nlr=0; // Tekrar başla
 // Robotu 30 sn durdurma
 digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(13,LOW);
delay(30000);
 }
 float fdist; float rdist; float ldist; // Ön ,Sağ ,Sol mesafeler
 float fduration;float rduration;float lduration; // Echopin süreleri
 float fdur[5]; float rdur[5]; float ldur[5]; //Süre tutma dizileri
 float ldista[5];
// Ön sensör döngüsü
 for(int i=0;i<=4;i++)
 {
 digitalWrite(trigPinf,LOW); 
 delayMicroseconds(5);
 digitalWrite(trigPinf,HIGH); 
 delayMicroseconds(10);
 digitalWrite(trigPinf,LOW);
 fdur[i] = pulseIn(echoPinf,HIGH); 
 }
 fduration = middleval(fdur);
 fdist = fduration*0.0344/2; // Ön duvar mesafesi
// Sağ sensör döngüsü
 for(int i=0;i<=4;i++)
 {
 digitalWrite(trigPinr,LOW);
 delayMicroseconds(5);
 digitalWrite(trigPinr,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinr,LOW);
 rdur[i] = pulseIn(echoPinr,HIGH);
 }
 rduration = middleval(rdur);
 rdist = rduration*0.0344/2; 
 
 
// Sol sensor döngüsü
 for(int i=0;i<=4;i++)
 {
 digitalWrite(trigPinl,LOW);
 delayMicroseconds(5);
 digitalWrite(trigPinl,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinl,LOW);
 ldur[i] = pulseIn(echoPinl,HIGH);
 }
 lduration = middleval(ldur);
 ldist = lduration*0.0344/2; 
 
if((fdist>=125)||(rdist>=150)||(ldist>=400)) {return;} 
 fsensor = false;rsensor = false;lsensor = false; // Booelan ayarlamaları
 if(rdist<=rthold) rsensor = true;
 if(ldist<=lthold) lsensor = true;
 if(fdist<=fthold) fsensor = true;
 
//Duvar takip algoritması
 //Sol kapalıysa
if((lsensor==true))
 {     // U dönüşü
 if((rsensor==true)&&(fsensor==true))
 { j=j+1;
 i=i+1;
 dir[i] = 3;
 reduce(dir,i);
digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,HIGH);
 delay(2*t);
 }
// Ön açıksa .
else if(fsensor==false)
 {
 if((rsensor==false)&&(frontdist()>=40)) // Ön ve Sağ açıksa
 {
 i = i+1;
 j=j+1;
 if((found==true)&(dir[i]!=0)) //Uca ulaştıktan sonra
 {
 rightturn();return;
 }
 else
 {
 if(found==false){
 dir[i] = 0; // Sağa ilerleme
reduce(dir,i);
 } timefr = tfr + 65*nf;
 nf=nf+1;
  stopit();delay(1000);
for(int g=1;g<=10;g++){gofront();delay(timefr/10);}
 stopit();delay(1000);
 } }
else {gofront();delay(300);} // Sadece ön açıksa
}
else
 {
 i = i+1;
 j=j+1;
 dir[i] = 2;
 reduce(dir,i);
float prevfdist = frontdist();
 while( abs(frontdist()-prevfdist)<=(prevfdist/2)-2)
{gofront();delay(300);if(frontdist()<=4.5){break;}}
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,HIGH);
 delay(t);
 float prevfrdist = frontdist();
 while( abs(frontdist()-prevfrdist)<=15.2){gofront();delay(300);
if(frontdist()<=4.5)
{break;}}
 }}
else 
{
 //Sola dönüş için
 i=i+1;
 j=j+1;
 if((found==true)&&(dir[i]!=1)){
if((dir[i]==2)&&(rightdist>=10)){rightturn();return;}
 else if((dir[i]== 0)&&(fsensor==false))
{frontturn();return;}
 }
 else{
 dir[i]=1; // Sola dönüş
 nlr=nlr+1;
 reduce(dir,i); //Yolu kısaltmak için
 {gofront(); delay(tlbef);}
 
 digitalWrite(10,LOW); // Sola dönüş
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);
 delay(2*t);
 for(int n=1;n<=8;n++) { gofront();delay(tlaf/8);}
 stopit(); delay(1000);
 }  }
 delay(320);}
