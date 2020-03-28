// #include<stdio.h>
// #include<string.h>
// #include<unistd.h>
// #include<fcntl.h>
// #include<stdlib.h>
// #include<iostream>
// #include <chrono>

// using namespace std;
// using namespace std::chrono;

// #define BLOCKSIZE 16*1024*1024

// int main (void)
// {
//     // cout<<getpagesize();

    
//     long long int record_size = 1024*1024;

//     char *buf1 = (char *)malloc(1024*1024*sizeof(char));
//     long long int i =0;
    
//     for(i =0;i<record_size;i++){

//             buf1[i] = 'a';
//     }

//     buf1[i] = '\0';

//     void *buffer;
    
//     //cout<<buf1<<endl;
    
//     // char *buffer = (char *)malloc(16*1024*1024*sizeof(char));

//     //cout<<buffer<<endl<<sizeof(buffer)<<endl;
    
//     posix_memalign(&buffer, BLOCKSIZE, BLOCKSIZE);
	
//     memcpy(buffer, buf1, 1024*1024*sizeof(char));

//     cout<<buffer<<endl<<sizeof(buffer)<<endl;

//     int a = open("f1.txt", O_CREAT|O_TRUNC|O_DIRECT|O_WRONLY, S_IRWXU);

//     auto start = high_resolution_clock::now();
//     for(int i =0;i<10000;i++){

//     int error = write(a, buffer, BLOCKSIZE);
//     //  cout<<error;
//     }

//     auto stop = high_resolution_clock::now();


//     close(a);
//     free(buffer);
//     free(buf1);

//     auto duration = duration_cast<seconds>(stop - start);
//      cout << "--Time taken by function: "
//     <<(size/1000)/duration.count() << " kB/seconds" << endl;

//     return 0;
// }

using namespace std::chrono;

#define BLOCKSIZE 1024*1024

int main (void)
{
    // cout<<getpagesize();


    long long int record_size = 1024*1024;

    void *buffer;

    //cout<<buf1<<endl;

    // char *buffer = (char *)malloc(16*1024*1024*sizeof(char));

    //cout<<buffer<<endl<<sizeof(buffer)<<endl;

    posix_memalign(&buffer, BLOCKSIZE, BLOCKSIZE);

    cout<<buffer<<endl<<sizeof(buffer)<<endl;

    int a = open("0", O_DIRECT|O_RDONLY, S_IRWXU);

    auto start = high_resolution_clock::now();
    for(int i =0;i<10240;i++){

    int error = read(a, buffer, BLOCKSIZE);
    //  cout<<error;
    }

    auto stop = high_resolution_clock::now();


    close(a);
    free(buffer);

    auto duration = duration_cast<seconds>(stop - start);
     cout << "--Time taken by function: "<<duration.count();

    return 0;
}
