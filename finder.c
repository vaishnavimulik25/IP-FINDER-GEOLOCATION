#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include"headers.h"


// Callback function to handle the HTTP response
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
	//response from curl which was stored in userp is stored in mem
    CurlResponse *mem = (CurlResponse *)userp;
	
	//why realloc ie mem->size should be zero on every iteration
    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("Error: Failed to allocate memory\n");
        return 0;
    }
	//mem is made conducive to add string data in it and contents of response 
	//are stored in mem->data ie we have found a way to store contents got from
	//url
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = '\0';

    return realsize;
}


// Function to fetch geolocation data for an IP address using the ipapi API
void fetch_geolocation(char* ipAddress) {
    //pointer to the response
	CURL *curl;
	//CURLcode is response value
    CURLcode res;
	//initialized response
    CurlResponse response = {NULL, 0};
	//to start the process of curl required for creating curl object which 
	//does settings for network requests
    curl = curl_easy_init();

    if (curl) {
		//character array for storing url which will be send to internet
        char url[100];

        //snprintf(url, sizeof(url), "https://freegeoip.app/xml/%s/", ipAddress);
        //snprintf(url, sizeof(url), "https://api.ip2location.io/%s", ipAddress);
        snprintf(url, sizeof(url), "https://ipinfo.io/%s/", ipAddress);
        //snprintf(url, sizeof(url), "https://ipapi.co/%s/json", ipAddress);
		//curl_easy_setopt is used for setting make userdefined changes to curl
		//CURLOPT_URL for setting target url
        curl_easy_setopt(curl, CURLOPT_URL, url);
		//CURLOPT_WRITEFUNCTION handles response data received from request
		//ie by transfering that data to write_callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		//sets a pointer to response structure which will receive response data
		//ie structure response will receive data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		
		//curl_easy_perform initiates request and retrieves response data
        //result is stored in res
		res = curl_easy_perform(curl);
		
       if (res != CURLE_OK) 
           fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
         
		else {
                     printf("%s\n", response.data);  // Print the raw JSON response

       }

        curl_easy_cleanup(curl);
        free(response.data);
    }
}


//int main(){
//https://ipapi.co/198.112.1.1/json/
//	fetch_geolocation("197.112.1.1");
//	return 0;

//}


