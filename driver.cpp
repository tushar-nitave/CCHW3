#include<stdio.h>
#include<iostream>
#include <chrono>
#include <cstring>
#include <fstream>
#include <pthread.h>
using namespace std;
using namespace std::chrono;

void write(int files, int record);

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
}


int main(int argc, char *argv[])
{
    char *accessPattern = argv[1];
    if (strcmp(accessPattern, "W") == 0)
    {
        cout<<"Write Method Call"<<"\n";
        write(atoi(argv[2]),atoi(argv[3]));    
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
