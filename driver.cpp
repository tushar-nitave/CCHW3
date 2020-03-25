#include<stdio.h>
#include<iostream>
#include <chrono>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>
#include<sstream>
using namespace std;
using namespace std::chrono;

void write(int files, int record);

void read(int files, int record);

struct thread_data {
   int id;
   int  rec;
   long long fileSize;
};


void *WriteHelper(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;    
    cout << "id : " << my_data->id;
    cout << "Record : " << my_data->rec ;
    cout << "fileSize : "<< my_data->fileSize;
    char c = 'a';
    int threadid = my_data->id;
    int size = my_data->fileSize;
    int recordSize = my_data->rec;
    string s = "";
    ofstream outfile;
    outfile.open(to_string(threadid));
    for(int i = 0; i < recordSize-1 ; i++){
        s += c;
    }
    int hops=size/recordSize;
    auto start = high_resolution_clock::now();
    for(int i = 0; i < hops ;i++){
        outfile << s << endl;
    }
    auto stop = high_resolution_clock::now();
    outfile.close();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "--Time taken by function: "
         << duration.count() << " microseconds" << endl;
    pthread_exit(NULL);
}

void *ReadHelper(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cout << "id : " << my_data->id;
    cout << "Record : " << my_data->rec ;
    int threadid = my_data->id;
    int size = my_data->fileSize;
    int BUF_SIZE = my_data->rec;

    char buffer[BUF_SIZE];

    stringstream temp_str;
    temp_str<<(threadid);
    string str = temp_str.str();
    const char* cstr2 = str.c_str();
    
    int input_fd = open (cstr2, O_RDONLY);

    if (input_fd == -1) {
            perror ("open");
    }
    ssize_t ret_in;
    auto start = high_resolution_clock::now();
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
    cout<<"In While";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "--Time taken by function: "
         << duration.count() << " microseconds" << endl;
    close (input_fd);
    pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
    char *accessPattern = argv[1];
    if (strcmp(accessPattern, "W") == 0)
    {
        cout<<"Write Method Call"<<"\n";
        write(atoi(argv[2]),atoi(argv[3]));    
    }
    else if (strcmp(accessPattern, "R") == 0)
    {
        cout<<"Read Method Call"<<"\n";
        read(atoi(argv[2]),atoi(argv[3]));
    }

     return(0);
}

void write(int files, int record) 
{   
   //put this value below prior too submission : 10000000000	
   long long tenGb = 100000;   
   long long fileSize = tenGb/files;   
    
   pthread_t threads[files];
    
   struct thread_data td[files];
   int rc;
   int i;   
   for( i = 0; i < files; i++ ) {
      td[i].id = i;
      td[i].rec = record;
      td[i].fileSize = fileSize;
      rc = pthread_create(&threads[i], NULL, WriteHelper, (void *)&td[i]);      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

void read(int files, int record)
{
   //put this value below prior too submission : 10000000000    
   long long tenGb = 100000;
   long long fileSize = tenGb/files;

   pthread_t threads[files];

   struct thread_data td[files];
   int rc;
   int i;
   for( i = 0; i < files; i++ ) {
      td[i].id = i;
      td[i].rec = record;
      td[i].fileSize = fileSize;
      rc = pthread_create(&threads[i], NULL, ReadHelper, (void *)&td[i]);
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}









