// Copyright 2023 Eraj eradzh2017@mail.ru

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/uaccess.h>
#include <linux/version.h>

// Объявление лицензии, автора и описания модуля
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eraj Karimov");
MODULE_DESCRIPTION("Kernel Module with Timer");

#define FILENAME_SIZE 100
static char output_filename[FILENAME_SIZE] = "/tmp/kernel_output.txt";
module_param_string(output_filename, output_filename, FILENAME_SIZE, 0644);

static int timer_period = 5;  
module_param(timer_period, int, 0644);

static struct timer_list custom_timer;
static struct file *output_file;      

// Функция обратного вызова для таймера
static void timer_callback(struct timer_list *t) {
  char message[] = "Hello from kernel module\n";
  kernel_write(output_file, message, sizeof(message) - 1, &output_file->f_pos);
  mod_timer(&custom_timer, jiffies + msecs_to_jiffies(timer_period * 1000));
}

// Функция инициализации модуля
static int __init hello_module_init(void) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)
  // Открываем файл для записи с возможностью добавления в конец
  output_file = filp_open(output_filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
  if (IS_ERR(output_file)) {
    printk(KERN_ALERT "Не удалось открыть файл\n");
    return PTR_ERR(output_file);
  }

  // Настройка таймера и его активация
  timer_setup(&custom_timer, timer_callback, 0);
  mod_timer(&custom_timer, jiffies + msecs_to_jiffies(timer_period * 1000));
  printk(KERN_INFO "Hello Module: Таймер запущен\n");
  return 0;
#else
  printk(KERN_ALERT "Данный модуль требует ядро Linux версии 5.10 или выше.\n");
  return -ENODEV;
#endif
}

// Функция выхода из модуля
static void __exit hello_module_exit(void) {
  del_timer(&custom_timer);       // Удаление таймера
  filp_close(output_file, NULL);  // Закрытие файла
  printk(KERN_INFO "Hello Module: Таймер остановлен\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);
