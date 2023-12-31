# Модуль ядра Linux с таймером и управлением параметрами

Это модуль ядра Linux, который записывает сообщение в файл через определенные промежутки времени, используя таймер. Также включена программа для управления параметрами модуля.

## Требования

- Linux ядро версии 5.10 и выше.
- Средство сборки ядра, например, `make`.
- [Пакеты модулей ядра и заголовочные файлы](https://habr.com/ru/companies/ruvds/articles/681880/)

## Как использовать

1. Соберите модуль ядра с помощью команды `make all`.

2. Загрузите модуль в ядро с помощью команды `make load`(параметры по умолчанию, проверьте файл /tmp/kernel_output.txt).

3. Для изменения параметров модуля используйте программу `set_params`. Запустите ее с аргументами: `<output_filename>` и `<timer_interval>`. После нужно ввести пароль суперпользователя. Например:
   
   ```bash
   ./set_params /tmp/kernel_output.txt 10
   ```

   Чтобы увидеть произошедшее в логах, выполните:
   ```bash
   sudo journalctl --since "1 hour ago" | grep kernel
   ```

   Чтобы выгрузить модуль из ядра, выполните команду `make unload`.
   
## Основные файлы

`kernel_module.c`: код модуля ядра. Он создает таймер и периодически записывает сообщение в файл.

`set_params.c`: Программа для управления параметрами модуля. Позволяет задать имя файла и интервал таймера.

Автор

Автор: [Eraj](https://github.com/ErajKarimov)
