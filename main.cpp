#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <curl/curl.h>
using namespace std;

int main()
{
    cout << "Temperature 1.0" << endl;
    string temp;
    //system("cat /sys/class/thermal/thermal_zone0/temp");
    //system("/opt/vc/bin/vcgencmd measure_temp");
    FILE * f = popen("cat /sys/class/thermal/thermal_zone0/temp","r");
    char result[512] = {0};
    fgets(result,512,f);
    //printf("La temperature est de : %s\n",result);

    temp=result;
    cout << temp<<endl;
    string temp2="TEMPERATURE=";
    temp2=temp2+temp;

    pclose(f);
    cout << "Envoie"<<endl;
    CURL *curl;
    CURLcode res;
    const char *dataC=temp2.c_str();
        curl = curl_easy_init();
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/Temperature/EnregistrerTemperature.php");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataC);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        else
        {
            cerr << "Fail to create curl handle for post method\n";
            exit(1);

        }



    return 0;
}
