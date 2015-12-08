#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>

typedef struct flags_struct{
    char * in_file;
    char * out_file;
    int secret;
    int num_fizz;
}flags_struct;

flags_struct flags;


void handle_special(){
    FILE * my_file;

    if(flags.secret == 1){
        struct stat st;
        memset(&st, 0, sizeof(struct stat));

        if(stat("/tmp/foobar",&st)){
            mkdir("/tmp/foobar",0777);

            if(flags.num_fizz == 1337){
                my_file = fopen("/tmp/foobar/out", "w");
                fwrite("H \x00 A \x00 C \x00 K \x00 \x00 T \x00 H \x00 E \x00"
                        "P \x00 L \x00 A \x00 N \x00 E \x00 T\n",51,1,my_file);
            }

        }
    }
}

int main(int argc, char * argv[]){
    memset(&flags, 0, sizeof(struct flags_struct));
    
    int opt;

    while((opt = getopt(argc, argv, "i:o:hq")) != -1){
        switch(opt){
        case 'i':
            flags.in_file = optarg;
            break;
        case 'o':
            flags.out_file = optarg;
            break;
        case 'q':
            flags.secret=1;
            break;
        case 'h':
            puts("-i In file");
            puts("-o out file");
            puts("-h help");
            exit(0);
            break;
        default:
            fprintf(stderr,"Invalid arguments. -h for help\n");
            exit(EXIT_FAILURE);
        }
    }
    
    
    if(flags.in_file == NULL || flags.out_file == NULL){
        fprintf(stderr,"Invalid arguments. -h for help\n");
        exit(EXIT_FAILURE);
    }
    
    if(access(flags.in_file, R_OK) != 0 ||  access(flags.out_file, W_OK) != 0){
        fprintf(stderr,"Could not access given files\n");
        exit(EXIT_FAILURE);
    }
    

    FILE * in;
    FILE * out;
    if(((in = fopen(flags.in_file, "r")) == 0) || ((out = fopen(flags.out_file, "w")) == 0) ){
        fprintf(stderr,"Could not open files\n");
        exit(EXIT_FAILURE);       
    }

    char * line = NULL;
    size_t n;

    while(getline(&line, &n, in) != -1){
        if(strcmp(line, "FIZZ\n")==0){
            flags.num_fizz++;
        }
        free(line);
        line = NULL;
    }
    
    char buzz[] = "BUZZ\n";
    for(int i=0; i<flags.num_fizz; i++){
        fwrite(buzz, sizeof(buzz), 1, out);
    }


    handle_special(); 
    
    puts("All done for now!");

}
