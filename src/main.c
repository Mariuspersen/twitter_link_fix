#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SB_IMPLEMENTATION
#include "../sb/sb.h"

int main(void)
{
    FILE* f = popen("wl-paste","r");
    if(!f) {
        perror("Unable to open execute and create pipe to wl-paste");
        return EXIT_FAILURE;
    }
    
    char buffer[1024] = { 0 };
    
    String_Builder *builder = sb_create(1024);

    if (builder == NULL)
    {
        perror("Unable to create string builder");        
        return EXIT_FAILURE;
    }

    while (fgets(buffer,sizeof(buffer),f) != NULL)
    {
        sb_append(builder,buffer);
    }

    if(pclose(f) < 0) {
        if (builder) sb_destroy(builder);
        perror("Some error occured during reading input from wl-paste");
        return EXIT_FAILURE;
    };
    


    if (strstr(builder->data, "https://x.com/") == NULL)
    {
        if (builder) sb_destroy(builder);
        fprintf(stderr,"Clipboard does not contain a twitter link\n");
        return EXIT_FAILURE;
    }

    sb_insert(builder, 8, "v");
    sb_insert(builder, 10, "twitter");

    f = popen("wl-copy","w");
    if(!f) {
        if (builder) sb_destroy(builder);
        perror("Unable to execute command 'wl-copy'");
        return EXIT_FAILURE;
    }

    fprintf(f,SB_Fmt,SB_Arg(builder));

    if(pclose(f) < 0) {
        if (builder) sb_destroy(builder);
        perror("Some error occured during writing output to wl-copy");
        return EXIT_FAILURE;
    };
    
    sb_destroy(builder);
    return EXIT_SUCCESS;
}