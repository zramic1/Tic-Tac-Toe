
#include "mbed.h"
#include "N5110.h"
#include "string"
#define dp23 P0_0

DigitalOut enable(dp14);
InterruptIn taster(dp1);

N5110 lcd(dp4,dp24,dp23,dp25,dp2,dp6,dp18);

AnalogIn X(dp11), Y(dp10);
InterruptIn SW(dp9);

Timer tajmer;
Timer tajmerK;
//Timer upisiZ;

int red1X(0), red2X(0), red3X(0), kolona1X(0), kolona2X(0), kolona3X(0), dijagonala1X(0), dijagonala2X(0);
int red1O(0), red2O(0), red3O(0), kolona1O(0), kolona2O(0), kolona3O(0), dijagonala1O(0), dijagonala2O(0);
int nerijeseno(0);

int globalnoX = 30, globalnoY = 16;

bool CPU=false;

bool zadnji=false;

bool stanje1=true;
bool stanje2=false;
//Definisanje tačaka za prikaz

//prvi red
int x1 = 10, y1 = 0;
int x2 = 30, y2 = 0;
int x3 = 50, y3 = 0;

//drugi red
int x4 = 10, y4 = 16;
int x5 = 30, y5 = 16;
int x6 = 50, y6 = 16;

//treći red

int x7 = 10, y7 = 32;
int x8 = 30, y8 = 32;
int x9 = 50, y9 = 32;


bool upisano[3][3]={
    {0,0,0},{0,0,0},{0,0,0}
};


bool aktivirano[3][3]={
    {0,0,0},{0,0,0},{0,0,0}
};

void postaviKursor(int x, int y){
    lcd.drawLine(x+8,y+8,x+13,y+8,1);
    lcd.refresh();
    globalnoX=x;
    globalnoY=y;
    
}

int xilio = 1;
void crtajO(int x, int y){
    if(y==0){ 
    
     if(x==10)
        lcd.drawCircle((x+30)/2,(y+16)/2,4,0);
     else if(x==30) 
        lcd.drawCircle((x+50)/2,(y+16)/2,4,0);
     else if(x==50)
        lcd.drawCircle((x+70)/2,(y+16)/2,4,0);
        
     }
    else if(y==16){
          
     if(x==10)
        lcd.drawCircle((x+30)/2,(y+32)/2,4,0);
     else if(x==30) 
        lcd.drawCircle((x+50)/2,(y+32)/2,4,0);
     else if(x==50)
        lcd.drawCircle((x+70)/2,(y+32)/2,4,0);
        
    }
    else if(y==32){ 
    
     if(x==10)
        lcd.drawCircle((x+30)/2,(y+48)/2,4,0);
     else if(x==30) 
        lcd.drawCircle((x+50)/2,(y+48)/2,4,0);
     else if(x==50)
        lcd.drawCircle((x+70)/2,(y+48)/2,4,0);
        
    }
     lcd.refresh();  
}

void crtajMrezu(){
    for (int i = 10; i < 70; i++) {
            lcd.setPixel(i,16);
        }
        lcd.refresh();
        
      for (int i = 10; i < 70; i++) {
            lcd.setPixel(i,32);
        }  
        lcd.refresh();
      for (int i = 0; i < 49; i++) {
            lcd.setPixel(30,i);
        }
        
        lcd.refresh();
        
      for (int i = 0; i < 49; i++) {
            lcd.setPixel(50,i);
        }  
        lcd.refresh();  
        
}
void crtajX(int x, int y){      
    lcd.drawLine(x+5,y+5,x+15,y+11,1);
    lcd.drawLine(x+15,y+5,x+5,y+11,1);
    lcd.refresh();  
}

int pozicijaUMeniju=3;

void ispisiMeni(){
    lcd.printString("IKS-OKS", 10, 0);
    lcd.printString("P vs P", 10, 3);
    lcd.printString("P vs CPU", 10, 4);
    lcd.printString("Izlaz",10,5);
    
}

void back(){
    lcd.clear();
    for(int i=0; i<84; i++){
        for(int j=0; j<48; j++){
            lcd.clearPixel(i, j);
        }
    }
    //lcd.refresh();
}

void igrajCpu(){
    int k, s;
    nerijeseno++;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(upisano[i][j]==false){
                k=i;s=j;
                break;
            }
            }
        }
    
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(upisano[i][j]==false){
                    
                    if(i==0){
                        if(red1O==2) {k=i;s=j; break;} 
                        if(j==0){
                            if(dijagonala1O==2){ k=i; s=j; break;}
                        }
                        else if(j==2){
                            if(dijagonala2O==2){ k=i; s=j; break;}
                        }
                        
                        if(red1X==2) {k=i;s=j; break;} 
                        if(j==0){
                            if(dijagonala1X==2){ k=i; s=j; break;}
                        }
                        else if(j==2){
                            if(dijagonala2X==2){ k=i; s=j; break;}
                        }
                    }
                    else if(i==1) {
                     if(red2O==2) {k=i;s=j; break;} 
                     if(j==1){
                            if(dijagonala1O==2){ k=i; s=j; break;}
                            else if(dijagonala2O==2){ k=i; s=j; break;}
                        }
                        
                     if(red2X==2) {k=i;s=j; break;} 
                     if(j==1){
                            if(dijagonala1X==2){ k=i; s=j; break;}
                            else if(dijagonala2X==2){ k=i; s=j; break;}
                        }
                    }
                    else if(i==2){
                     if(red3O==2) {k=i;s=j; break;} 
                        if(j==0){
                            if(dijagonala2O==2){ k=i; s=j; break;}
                        }
                        else if(j==2){
                            if(dijagonala1O==2){ k=i; s=j; break;}
                        }
                        
                     if(red3X==2) {k=i;s=j; break;} 
                        if(j==0){
                            if(dijagonala2X==2){ k=i; s=j; break;}
                        }
                        else if(j==2){
                            if(dijagonala1X==2){ k=i; s=j; break;}
                        }
                    }
                    
                    if(j==0){
                        if(kolona1O==2){ k=i;s=j; break;}
                        if(kolona1X==2){ k=i;s=j; break;}
                    }
                    else if(j==1) {
                        if(kolona2O==2){ k=i;s=j; break;}
                        if(kolona2X==2){ k=i;s=j; break;}
                    }
                    else if(j==2){
                        if(kolona3O==2){ k=i;s=j; break;}
                        if(kolona3X==2){ k=i;s=j; break;}
                    }
                
            }
        }
    }
    upisano[k][s]=true;
    aktivirano[k][s]=true;   
   
    
    
        if(aktivirano[0][0]==true){
            crtajO(x1,y1);
            kolona1O++;
            red1O++;
            dijagonala1O++;
            postaviKursor(x1, y1);
            
        }
        else if(aktivirano[0][1]==true){
            crtajO(x2,y2);
            kolona2O++;
            red1O++;
            postaviKursor(x2, y2);
        }
        else if(aktivirano[0][2]==true){
            crtajO(x3,y3);
            kolona3O++;
            red1O++;
            dijagonala2O++;
            postaviKursor(x3, y3);
        }
        else if(aktivirano[1][0]==true){
            crtajO(x4,y4);
            kolona1O++;
            red1O++;
            postaviKursor(x4, y4);
        }
        else if(aktivirano[1][1]==true){
            crtajO(x5,y5);
            kolona2O++;
            red2O++;
            dijagonala1O++;
            dijagonala2O++;
            postaviKursor(x5, y5);
        }
        else if(aktivirano[1][2]==true){
            crtajO(x6,y6);
            kolona3O++;
            red2O++;
            postaviKursor(x6, y6);
        }
        else if(aktivirano[2][0]==true){
            crtajO(x7,y7);
            kolona1O++;
            red3O++;
            dijagonala2O++;
            postaviKursor(x7, y7);
        }
        else if(aktivirano[2][1]==true){
            crtajO(x8,y8);
            kolona2O++;
            red3O++;
            postaviKursor(x8, y8);
            
        }
        else if(aktivirano[2][2]==true){
            crtajO(x9,y9);
            kolona3O++;
            red3O++;
            dijagonala1O++;
            postaviKursor(x9, y9);
        } 
        
             
    }
    


int pobijedioX(0), pobijedioO(0);

void pobjeda(){
     
    if(red1X == 3 || red2X == 3 || red3X == 3 || kolona1X == 3 || kolona2X == 3 || kolona3X == 3 || dijagonala1X == 3 || dijagonala2X == 3){
        pobijedioX++;
        wait(0.2);
        back();
        lcd.printString("Pobjednik P1",0,1);
        
        wait(2);
        char ispis[20];
        if(CPU) sprintf(ispis, "P1 %d:%d CPU", pobijedioX, pobijedioO);
        else{ sprintf(ispis, "P1 %d:%d P2", pobijedioX, pobijedioO);}
        lcd.printString(ispis, 0,3);
        wait(2);
        
        back();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                aktivirano[i][j]=false;
                upisano[i][j]=false;
                }
        }
      
        
        
        
        red1X=0; red2X=0; red3X=0; kolona1X=0; kolona2X=0; kolona3X=0; dijagonala1X=0; dijagonala2X=0;
        red1O=0; red2O=0; red3O=0; kolona1O=0; kolona2O=0; kolona3O=0; dijagonala1O=0; dijagonala2O=0;
        nerijeseno=0;
        xilio=1;
        globalnoX = 30; globalnoY = 16;
        zadnji=true;
        
        aktivirano[1][1] = true;
        crtajMrezu();
        postaviKursor(x5,y5);
        
    }
    else if(red1O == 3 || red2O == 3 || red3O == 3 || kolona1O == 3 || kolona2O == 3 || kolona3O == 3 || dijagonala1O == 3 || dijagonala2O == 3){
        pobijedioO++;
        wait(0.2);
        back();
        if(CPU) lcd.printString("Pobjednik CPU",0,1);
        else lcd.printString("Pobjednik P2",0,1);
        
        wait(2);
        char ispis[20];
        if(CPU) sprintf(ispis, "P1 %d:%d CPU", pobijedioX, pobijedioO);
        else{ sprintf(ispis, "P1 %d:%d P2", pobijedioX, pobijedioO);}
        lcd.printString(ispis, 0,3);
        
        wait(2);
        
        back();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                aktivirano[i][j]=false;
                upisano[i][j]=false;
                }
        }
        
        
        
        red1X=0; red2X=0; red3X=0; kolona1X=0; kolona2X=0; kolona3X=0; dijagonala1X=0; dijagonala2X=0;
        red1O=0; red2O=0; red3O=0; kolona1O=0; kolona2O=0; kolona3O=0; dijagonala1O=0; dijagonala2O=0;
        nerijeseno=0;
        xilio=1;
        zadnji=true;
        globalnoX = 30; globalnoY = 16;
        aktivirano[1][1] = true;
        crtajMrezu();
        postaviKursor(x5,y5);
        
    }
    else if(nerijeseno==9){
        wait(0.2);
        back();
        lcd.printString("Nerijeseno",0,1);
        
        wait(2);
        char ispis[20];
        if(CPU) sprintf(ispis, "P1 %d:%d CPU", pobijedioX, pobijedioO);
        else{ sprintf(ispis, "P1 %d:%d P2", pobijedioX, pobijedioO);}
        lcd.printString(ispis, 0,3);
        
        wait(3);
        back();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                aktivirano[i][j]=false;
                upisano[i][j]=false;
                }
        }
        
        
        
        red1X=0; red2X=0; red3X=0; kolona1X=0; kolona2X=0; kolona3X=0; dijagonala1X=0; dijagonala2X=0;
        red1O=0; red2O=0; red3O=0; kolona1O=0; kolona2O=0; kolona3O=0; dijagonala1O=0; dijagonala2O=0;
        nerijeseno=0;
        xilio=1;
        zadnji=true;
        globalnoX = 30; globalnoY = 16;
        
        aktivirano[1][1] = true;
        crtajMrezu();
        postaviKursor(x5,y5);
        
    }
}

void ocistiKursor(int x,int y){
    for(int i=x+8;i<=x+13;i++){
        lcd.clearPixel(i,y+8);}
}





void upisiZnak(){
    int p1=0;
    int p2=0;
    bool slobodno=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
             if(aktivirano[i][j]==true){
                 if(upisano[i][j]==false){ 
                    slobodno = true;
                    upisano[i][j]=true;
                    p1=i;
                    p2=j;
                 }
                 
                }
            }
           
        } 
           
        if(slobodno){
                nerijeseno++;
                if(CPU==false){
                if(xilio==1){ 
                    crtajX(globalnoX,globalnoY);
                    if(p1==0){
                     red1X++; 
                     if(p2==0) dijagonala1X++;
                     else if(p2==2) dijagonala2X++;  
                    }
                    else if(p1==1) {
                     red2X++;
                     if(p2==1){ dijagonala1X++; dijagonala2X++;}
                    }
                    else if(p1==2){
                     red3X++;
                     if(p2==0) dijagonala2X++;
                     else if(p2==2) dijagonala1X++; 
                    }
                    
                    
                    if(p2==0){
                     kolona1X++;   
                    }
                    else if(p2==1) {
                     kolona2X++;
                    }
                    else if(p2==2){
                     kolona3X++;
                    }
                    xilio=1-xilio;
                    pobjeda();
                    }
                else{
                    crtajO(globalnoX,globalnoY);
                    
                    if(p1==0){
                     red1O++; 
                     if(p2==0) dijagonala1O++;
                     else if(p2==2) dijagonala2O++;  
                    }
                    else if(p1==1) {
                     red2O++;
                     if(p2==1){ dijagonala1O++; dijagonala2O++;}
                    }
                    else if(p1==2){
                     red3O++;
                     if(p2==0) dijagonala2O++;
                     else if(p2==2) dijagonala1O++; 
                    }
                    
                    
                    if(p2==0){
                     kolona1O++;   
                    }
                    else if(p2==1) {
                     kolona2O++;
                    }
                    else if(p2==2){
                     kolona3O++;
                    }
                    xilio=1-xilio;
                    pobjeda();
                    }
                //xilio=1-xilio;
            }
            else{
                    crtajX(globalnoX,globalnoY);
                    zadnji = false;
                    if(p1==0){
                     red1X++; 
                     if(p2==0) dijagonala1X++;
                     else if(p2==2) dijagonala2X++;  
                    }
                    else if(p1==1) {
                     red2X++;
                     if(p2==1){ dijagonala1X++; dijagonala2X++;}
                    }
                    else if(p1==2){
                     red3X++;
                     if(p2==0) dijagonala2X++;
                     else if(p2==2) dijagonala1X++; 
                    }
                    
                    
                    if(p2==0){
                     kolona1X++;   
                    }
                    else if(p2==1) {
                     kolona2X++;
                    }
                    else if(p2==2){
                     kolona3X++;
                    }
                    aktivirano[p1][p2]=false;
                    ocistiKursor(globalnoX,globalnoY);
                    //wait(0.5);
                    pobjeda();
                    if(zadnji == false){
                        igrajCpu();
                        pobjeda();
                    }
                }
            }
}
         



void igra(){
    
    if(X>2.0/3.0){
        if(aktivirano[0][0]==true){
            ocistiKursor(x1,y1);
            
            
            aktivirano[0][0]=false;
            aktivirano[0][2]=true;
            postaviKursor(x3,y3);
        }
        else if(aktivirano[0][1]==true){
            ocistiKursor(x2,y2);
            
            aktivirano[0][1]=false;
            aktivirano[0][0]=true;
            postaviKursor(x1,y1);
        }
        else if(aktivirano[0][2]==true){
            ocistiKursor(x3,y3);
            
            
            aktivirano[0][2]=false;
            aktivirano[0][1]=true;
            postaviKursor(x2,y2);
        }
        else if(aktivirano[1][0]==true){
            ocistiKursor(x4,y4);
            
            
            aktivirano[1][0]=false;
            aktivirano[1][2]=true;
            postaviKursor(x6,y6);
        }
        else if(aktivirano[1][1]==true){
            ocistiKursor(x5,y5);
            
            
            aktivirano[1][1]=false;
            aktivirano[1][0]=true;
            postaviKursor(x4,y4);
        }
        else if(aktivirano[1][2]==true){
            ocistiKursor(x6,y6);
            
            
            aktivirano[1][2]=false;
            aktivirano[1][1]=true;
            postaviKursor(x5,y5);
        }
        else if(aktivirano[2][0]==true){
            ocistiKursor(x7,y7);
            
            
            aktivirano[2][0]=false;
            aktivirano[2][2]=true;
            postaviKursor(x9,y9);
        }
        else if(aktivirano[2][1]==true){
            ocistiKursor(x8,y8);
            
            
            aktivirano[2][1]=false;
            aktivirano[2][0]=true;
            postaviKursor(x7,y7);
        }
        else if(aktivirano[2][2]==true){
            ocistiKursor(x9,y9);
            
            
            aktivirano[2][2]=false;
            aktivirano[2][1]=true;
            postaviKursor(x8,y8);
        } 
    }
    else if(X<1.0/3.0){
      
      if(aktivirano[0][0]==true){
            ocistiKursor(x1,y1);
            
            
            aktivirano[0][0]=false;
            aktivirano[0][1]=true;
            postaviKursor(x2,y2);
        }
        else if(aktivirano[0][1]==true){
            ocistiKursor(x2,y2);
            
            
            aktivirano[0][1]=false;
            aktivirano[0][2]=true;
            postaviKursor(x3,y3);
        }
        else if(aktivirano[0][2]==true){
            ocistiKursor(x3,y3);
            
            
            aktivirano[0][2]=false;
            aktivirano[0][0]=true;
            postaviKursor(x1,y1);
        }
        else if(aktivirano[1][0]==true){
            ocistiKursor(x4,y4);
            
            
            aktivirano[1][0]=false;
            aktivirano[1][1]=true;
            postaviKursor(x5,y5);
        }
        else if(aktivirano[1][1]==true){
            ocistiKursor(x5,y5);
            
            
            aktivirano[1][1]=false;
            aktivirano[1][2]=true;
            postaviKursor(x6,y6);
        }
        else if(aktivirano[1][2]==true){
            ocistiKursor(x6,y6);
            
            
            aktivirano[1][2]=false;
            aktivirano[1][0]=true;
            postaviKursor(x4,y4);
        }
        else if(aktivirano[2][0]==true){
            ocistiKursor(x7,y7);
            
            
            aktivirano[2][0]=false;
            aktivirano[2][1]=true;
            postaviKursor(x8,y8);
        }
        else if(aktivirano[2][1]==true){
            ocistiKursor(x8,y8);
            
            
            aktivirano[2][1]=false;
            aktivirano[2][2]=true;
            postaviKursor(x9,y9);
        }
        else if(aktivirano[2][2]==true){
            ocistiKursor(x9,y9);
            
            
            aktivirano[2][2]=false;
            aktivirano[2][0]=true;
            postaviKursor(x7,y7);
        }     
    }
    
    if(Y<1.0/3.0){
        if(aktivirano[0][0]==true){
            ocistiKursor(x1,y1);
            
            aktivirano[0][0]=false;
            aktivirano[1][0]=true;
            postaviKursor(x4,y4);
            
        }
        else if(aktivirano[0][1]==true){
            ocistiKursor(x2,y2);
            
            
            aktivirano[0][1]=false;
            aktivirano[1][1]=true;
            postaviKursor(x5,y5);
        }
        else if(aktivirano[0][2]==true){
            ocistiKursor(x3,y3);
            
            
            aktivirano[0][2]=false;
            aktivirano[1][2]=true;
            postaviKursor(x6,y6);
        }
        else if(aktivirano[1][0]==true){
            ocistiKursor(x4,y4);
            
            
            aktivirano[1][0]=false;
            aktivirano[2][0]=true;
            postaviKursor(x7,y7);
        }
        else if(aktivirano[1][1]==true){
            ocistiKursor(x5,y5);
            
            
            aktivirano[1][1]=false;
            aktivirano[2][1]=true;
            postaviKursor(x8,y8);
        }
        else if(aktivirano[1][2]==true){
            ocistiKursor(x6,y6);
            
            
            aktivirano[1][2]=false;
            aktivirano[2][2]=true;
            postaviKursor(x9,y9);
        }
        else if(aktivirano[2][0]==true){
            ocistiKursor(x7,y7);
            
            
            aktivirano[2][0]=false;
            aktivirano[0][0]=true;
            postaviKursor(x1,y1);
        }
        else if(aktivirano[2][1]==true){
            ocistiKursor(x8,y8);
            
            
            aktivirano[2][1]=false;
            aktivirano[0][1]=true;
            postaviKursor(x2,y2);
        }
        else if(aktivirano[2][2]==true){
            ocistiKursor(x9,y9);
            
            
            aktivirano[2][2]=false;
            aktivirano[0][2]=true;
            postaviKursor(x3,y3);
        } 
    }
    else if(Y>2.0/3.0){
        if(aktivirano[0][0]==true){
            ocistiKursor(x1,y1);
            
            
            aktivirano[0][0]=false;
            aktivirano[2][0]=true;
            postaviKursor(x7,y7);
        }
        else if(aktivirano[0][1]==true){
            ocistiKursor(x2,y2);
            
            
            aktivirano[0][1]=false;
            aktivirano[2][1]=true;
            postaviKursor(x8,y8);
        }
        else if(aktivirano[0][2]==true){
            ocistiKursor(x3,y3);
            
            
            aktivirano[0][2]=false;
            aktivirano[2][2]=true;
            postaviKursor(x9,y9);
        }
        else if(aktivirano[1][0]==true){
            ocistiKursor(x4,y4);
            
            
            aktivirano[1][0]=false;
            aktivirano[0][0]=true;
            postaviKursor(x1,y1);
        }
        else if(aktivirano[1][1]==true){
            ocistiKursor(x5,y5);
            
            
            aktivirano[1][1]=false;
            aktivirano[0][1]=true;
            postaviKursor(x2,y2);
        }
        else if(aktivirano[1][2]==true){
            ocistiKursor(x6,y6);
            
            
            aktivirano[1][2]=false;
            aktivirano[0][2]=true;
            postaviKursor(x3,y3);
        }
        else if(aktivirano[2][0]==true){
            ocistiKursor(x7,y7);
            
            
            aktivirano[2][0]=false;
            aktivirano[1][0]=true;
            postaviKursor(x4,y4);
        }
        else if(aktivirano[2][1]==true){
            ocistiKursor(x8,y8);
            
            
            aktivirano[2][1]=false;
            aktivirano[1][1]=true;
            postaviKursor(x5,y5);
        }
        else if(aktivirano[2][2]==true){
            ocistiKursor(x9,y9);
            
            
            aktivirano[2][2]=false;
            aktivirano[1][2]=true;
            postaviKursor(x6,y6);
        } 
    
    }
    
    
}

void ocistiKursorZaMeni(int red){
    for(int i=3;i<=8;i++){
        for(int j=(red)*8;j<(1+red)*8;j++){
            lcd.clearPixel(i,j);
        }
    }
    lcd.refresh();
}


void kursorZaMeni(int red){
    lcd.printString(">", 3, red);
    lcd.refresh();
}
    
  
void meni(){
    //Kretanje dolje
    if(Y<1.0/3.0){
        ocistiKursorZaMeni(pozicijaUMeniju);
        if(pozicijaUMeniju==5) pozicijaUMeniju=2;
        pozicijaUMeniju++;
        kursorZaMeni(pozicijaUMeniju);
        lcd.refresh();
    }//Gore
    else if(Y>2.0/3.0){
        ocistiKursorZaMeni(pozicijaUMeniju);
        if(pozicijaUMeniju==3) pozicijaUMeniju=6;
        pozicijaUMeniju--;
        kursorZaMeni(pozicijaUMeniju);
        lcd.refresh();
    }
    wait(0.3);
}

void resetujIgricu(){
        stanje1=true;
        stanje2=false;
        back();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                aktivirano[i][j]=false;
                upisano[i][j]=false;
                }
        }
        aktivirano[1][1] = true;
        
        red1X=0; red2X=0; red3X=0; kolona1X=0; kolona2X=0; kolona3X=0; dijagonala1X=0; dijagonala2X=0;
        red1O=0; red2O=0; red3O=0; kolona1O=0; kolona2O=0; kolona3O=0; dijagonala1O=0; dijagonala2O=0;
        nerijeseno=0;
        xilio=1;
        zadnji=false;
        globalnoX = 30; globalnoY = 16;
        
        pobijedioX=0; pobijedioO=0;
        pozicijaUMeniju=3;
        
        ispisiMeni();
        kursorZaMeni(3);
}


void izaberiOpciju(){
    if(stanje1){
        if(tajmer.read()>0.33){
            back();
            stanje1=false;
            stanje2=true;
            if(pozicijaUMeniju==3){
                CPU=false;
                crtajMrezu();
                aktivirano[1][1]=true;
                postaviKursor(x5,y5);    
            }
            else if(pozicijaUMeniju==4){
                crtajMrezu();
                aktivirano[1][1]=true;
                postaviKursor(x5,y5);
                CPU=true;
            }
            else if(pozicijaUMeniju==5){
            lcd.turnOff();
            }
        }
        tajmer.reset();
    }
    else{
       if(tajmer.read()>0.33){
            upisiZnak(); 
       }
       tajmer.reset();
    }


}



int main() {
    
    SW.mode(PullUp);   
    tajmer.start();
    tajmerK.start();
    enable=1;
    lcd.init();
    
    ispisiMeni();
    kursorZaMeni(3);
    
    
    SW.rise(&izaberiOpciju);
    taster.rise(&resetujIgricu);

    while(1){
        
        if(stanje1){
            meni();
        }
        else if(stanje2){ 
            if(tajmerK.read()>0.2){
                igra();
            }
            tajmerK.reset();
        }
        
        lcd.refresh();
        wait(0.25);
        
    }
}
