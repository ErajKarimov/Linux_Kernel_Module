// Copyright 2023 Eraj eradzh2017@mail.ru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Использование: %s <output_filename> <timer_interval>\n", argv[0]);
    return 1;
  }

  // Составление команды для запуска модуля с передачей параметров
  char command[256];
  snprintf(command, sizeof(command),
           "sudo insmod kernel_module.ko output_filename=\"%s\" timer_period=%s",
           argv[1], argv[2]);

  // Выполнение команды с помощью системного вызова system
  if (system(command) == -1) {
    perror("system");
    return 1;
  }

  return 0;
}
