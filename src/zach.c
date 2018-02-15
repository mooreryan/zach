#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"

int main(int argc, char *argv[])
{

  if (argc != 2) {
    fprintf(stderr, "USAGE: %s tsv_cluster_file.txt > cdhit_format_cluster_file.txt\n", argv[0]);

    return 1;
  }

  char* in_fname = argv[1];
  PANIC_UNLESS_FILE_CAN_BE_READ(stderr, in_fname);

  long cluster_idx = 0;
  long lineno = 0;

  char centroid[10240];
  char member[10240];

  char* last_centroid = NULL;

  FILE* in_fs = fopen(in_fname, "r");

  PANIC_IF(in_fs == NULL,
           errno,
           stderr,
           "Could not open '%s': %s",
           in_fname,
           strerror(errno));


  while(fscanf(in_fs, "%s\t%s", centroid, member) == 2) {
    ++lineno;
    if (lineno++ % 10000 == 0) {
      fprintf(stderr, "Reading line %ld\r", lineno);
    }

    if (last_centroid == NULL || strcmp(centroid, last_centroid) != 0) {
      /* Starting a new cluster. */
      fprintf(stdout, ">cluster %ld\n", cluster_idx++);

      free(last_centroid);
      last_centroid = strdup(centroid);
      PANIC_MEM(last_centroid, stderr);
    }

    fprintf(stdout, "%s\n", member);
  }

  fclose(in_fs);
  free(last_centroid);

  return 0;
}
