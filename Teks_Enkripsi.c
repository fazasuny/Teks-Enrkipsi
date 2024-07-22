#include<stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

char arr[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char password[100] ="-";
char bin[5];

void menu(){
	printf("========== Teks Enkripsi ==========\n");
	printf("-- Password : %s\t\t     --\n", password);
	printf("--\t\tMenu\t\t     --\n");
	printf("--\t1. Masukan Password\t     --\n");
	printf("--\t2. Mengkripsi teks\t     --\n");
	printf("--\t3. Mendeskripsi teks\t     --\n");
	printf("--\t4. Keluar\t\t     --\n");
	printf("=======================================\n\n");
	printf("Masukkan Pilihan : ");
}

int Indeks_Karakter(char karakter){
	int i;
	for(i = 0; i<strlen(arr);i++){
		if(arr[i]==karakter){
			return i;
			break;
		}
	}
}

int BinToDec(){
    int cnt=0;
    int dec=0;
    int i;
    for(i=(strlen(bin)-1);i>=0;i--){
        dec=dec+(bin[i]-'0')*pow(2,cnt);
        cnt++;
    }
    return dec;
}

char DecToBin(int X) {
    char b[5];
	int c, k;
	for (c = 0; c <6; c++){
    	k = X >> c;
    	if(k & 1)
      		b[c] = '1';
   		else
      		b[c] = '0';
  	}
  	strcpy(bin,strrev(b));
}


void geserKiri(int k){ 
	int i, j, n = 6;
	char temp;
	for(i=0; i<k; i++){
        temp=bin[0];
        for(j=0; j<n-1; j++){
           bin[j]=bin[j+1];
		}
    	bin[n-1]=temp;
    }
}

void geserKanan(int k){
	int i, j, n = 6;
	char temp;
	for(i=0; i<k; i++){
        temp=bin[n-1];
        for(j=n-1; j>0; j--){
           bin[j]=bin[j-1];
		}
 		bin[j]=temp;
    }
}

void enkripsi(char str[]){
	char str2[10000] = {0};
	int i = 0, j = 0;
	int prev = 0, pw, pos, keyChain;
	for(i = 0;i<strlen(str);i++){
		if(j == strlen(password)){
			j = 0;
		}
		pw = Indeks_Karakter(password[j]);
		pos = pw;
		if(i == 0){
			if((pw+1)%2==1){
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKiri((pw+1));
			}else{
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKanan((pw+1));
			}
			prev = BinToDec()-1;
			if(prev>62){
				prev = prev%62;
			}
			
			str2[i] = arr[prev];
		}else if(str[i]==' '){
			str2[i]=' ';
			continue;
		}else if(str[i]==','){
			str2[i]=',';
			continue;
		}else if(str[i]=='.'){
			str2[i]='.';
			continue;
		}else if(str[i]=='-'){
			str2[i]='-';
			continue;
		}
		else{
			keyChain = pos+pw+1+prev;
			if(keyChain%2==1){
				DecToBin(Indeks_Karakter(str[i])+1); 
				geserKiri(keyChain);
			}else{
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKanan(keyChain);
			}
			prev = BinToDec()-1;
			if(prev>62){
				prev = prev%62;
			}
			
			str2[i] = arr[prev];
		}
		j++;
	}
	printf("%s\n", str2);
}

void deskripsi(char str[]){
	char str2[10000] = {0};
	int i = 0, j = 0;
	int prev = 0, pw, pos, keyChain;
	for(i = 0;i<strlen(str);i++){
		if(j == strlen(password)){
			j = 0;
		}
		pw = Indeks_Karakter(password[j]);
		pos = pw;
		if(i ==0){
			if((pw+1)%2==1){ 
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKanan((pw+1));	
			}else{
				DecToBin(Indeks_Karakter(str[i])+1);	
				geserKiri((pw+1));
			}
			
			prev = BinToDec()-1;
			
			if(prev>62){
				prev = prev%62;
			}
			
			str2[i] = arr[prev];
			prev = Indeks_Karakter(str[i]);
		}else if(str[i]==' '){
			str2[i]=' ';
			continue;
		}else if(str[i]==','){
			str2[i]=',';
			continue;
		}else if(str[i]=='.'){
			str2[i]='.';
			continue;
		}else if(str[i]=='-'){
			str2[i]='-';
			continue;
		}
		else{
			keyChain = pos+pw+1+prev;
			if(keyChain%2==1){
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKanan(keyChain);
			}else{
				DecToBin(Indeks_Karakter(str[i])+1);
				geserKiri(keyChain);
			}
			prev = BinToDec()-1;
			if(prev>62){
				prev = prev%62;
			}
			
			str2[i] = arr[prev];
			prev = Indeks_Karakter(str[i]);
		}
		j++;
	}
	printf("%s\n", str2);
}

int main(){
	char str1[10000];
	char m;
	do{
		menu();
		m = getch();
		switch(m){
			case '1':
				printf("\n========== Masukan Password ==========  : ");
				scanf("%s", &password);
				getchar();
				system("pause");
				break;
			case '2':
				printf("\n============ UBAH TEKS ============\n");
				printf("Masukkan Teks    : ");
				scanf("%[^\n]", &str1);
				getchar();
				printf("Teks yang di sudah di ubah : ");
				enkripsi(str1);
				system("pause");
				break;
			case '3':
				printf("\n============ TRANSLATE ============\n");
				printf("Masukkan Teks    : ");
				scanf("%[^\n]", &str1);
				getchar();
				printf("Teks Translate : ");
				deskripsi(str1);
				system("pause");
				break;
			case '4':
				system("cls");
				exit(0);
				break;
		}
		system("cls");
	}
	while(m>='1'||m<='4');
	return 0;
}
