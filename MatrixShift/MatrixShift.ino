const int out[7]={1,2,4,8,16,32,64};

void setup() {
 
  DDRF=255;
  PORTF=1;  
  DDRK=255;
  PORTK=1;
  Serial.begin(9600);
}

void loop() {
  int i,j;
  for(i=0; i<7;i++){
          PORTF=out[i];
    for(j=0;j<5;j++){
      PORTK=~out[j]; 
    delay(100);
    }

    delay(100);
  }
}
