#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

  int limit_age = 60;
  char process_name[15] = "Pai";
  time_t initial_time, final_time;

  time(&initial_time);
  printf("O processo %s nasceu às %s", process_name, ctime(&initial_time));

  int actual_age = 0;
  while (actual_age <= limit_age) {
    actual_age++;

    sleep(1);

    // Nasce o primeiro filho
    if (strcmp(process_name, "Pai") == 0 && actual_age == 14) {
      int status_process = fork();

      if (status_process == 0) {
        strcpy(process_name, "Filho 1");
        limit_age = 30;
        actual_age = 0;
        time(&initial_time);
        printf("O processo %s nasceu às %s", process_name, ctime(&initial_time));
      }
    }

    // Nasce o segundo filho
    if (strcmp(process_name, "Pai") == 0 && actual_age == 16) {
      int status_process = fork();

      if (status_process == 0) {
        strcpy(process_name, "Filho 2");
        limit_age = 30;
        actual_age = 0;
        time(&initial_time);
        printf("O processo %s nasceu às %s", process_name, ctime(&initial_time));
      }
    }

    // Nasce o primeiro neto
    if (strcmp(process_name, "Filho 1") == 0 && actual_age == 12) {
      int status_process = fork();

      if (status_process == 0) {
        strcpy(process_name, "Neto 1");
        limit_age = 12;
        actual_age = 0;
        time(&initial_time);
        printf("O processo %s nasceu às %s", process_name, ctime(&initial_time));
      }
    }

    // Nasce o segundo neto
    if (strcmp(process_name, "Filho 2") == 0 && actual_age == 14) {
      int status_process = fork();

      if (status_process == 0) {
        strcpy(process_name, "Neto 2");
        limit_age = 18;
        actual_age = 0;
        time(&initial_time);
        printf("O processo %s nasceu às %s", process_name, ctime(&initial_time));
      }
    }
  }

  time(&final_time);
  printf("O processo %s morreu em %s\
         Nasceu em %s\
         e viveu %d anos\n",
         process_name,
         ctime(&final_time),
         ctime(&initial_time),
         limit_age);

  return 0;
}
