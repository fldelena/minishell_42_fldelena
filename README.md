# :white_check_mark: Minishell(project 2021)

## Описание
В своё время программисты согласились с тем, что общение с компьютером с использованием 1 и 0 немного раздражает.
Вполне логично, что им пришла в голову идея общаться с компьютером с помощью интерактивных строк команд на языке, несколько близком к английскому.
Таким образом, основная задача этого проекта - написать свою собственную мини-оболочку на C.

## Запуск
```
make
./minichell
```

## Функции, которые были реализованы
- История.
- Поиск и запуск нужного исполняемого файла (на основе переменной **PATH** или с помощью относительного или абсолютного пути).
- Встроенные функции:
	- `cd` with only a relative or absolute path.
	- `pwd` with no options.
	- `echo` with `-n` option.
	- `export` with no options.
	- `unset` with no options.
	- `env` with no options.
	- `exit` with no options.
- Перенаправления:
	- `<` redirect input.
	- `>` redirect output.
	- `>>`redirect output with append mode.
- Каналы(pipes) `|` выхоодыне данные каждой команды через канал направляются как входные данные другой команды.
- Переменные окружения (**$** следующие ща символом) заменяются их значениями.
- '$?` заменяется статусом завершения последней команды.
- Сигналы работают также как в bash. Когда interactive режим:
	- `Ctrl + C` незамедлительный переход на новую строку.
	- `Ctrl + D` выход из оболочки.
	- `Ctrl + \` ничего.

## Теория
### :page_facing_up: Fork
**The Fork system call** используется для создания нового процесса, называемого дочерним процессом, который выполняется одновременно с процессом, вызывающим fork () (родительский процесс). После создания нового дочернего процесса оба процесса выполнят следующую инструкцию после системного вызова fork (). Дочерний процесс использует тот же компьютер (счетчик программ), те же регистры процессора и те же открытые файлы, которые используются в родительском процессе. 

Он не принимает параметры и возвращает целочисленное значение. Различные значения, возвращаемые функцией fork (), показаны ниже. 

**Negative value:** не удалось создать дочерний процесс.
**Zero:** вернулся к вновь созданному дочернему процессу.
**A positive value** возвращается родителю. Это значение содержит идентификатор процесса вновь созданного дочернего процесса.
  
![](https://github.com/markveligod/minishell/raw/master/img/1.jpg)  
  
Предсказать результат следующей программы:
```
#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
  
int main(void)  
{  
// создайте два процесса, которые работают одинаково
// программа после этой инструкции ->
    fork();  
    printf("Hello world!\n");
    return (0);  
}  
```
Output:
```
Hello world!  
Hello world!  
```
Количество раз, когда печатается `'hello'`, равно количеству созданных процессов. Общее количество процессов = 2^n, где n - количество системных вызовов fork. Итак, в примере ниже n = 3, 2 ^ 3 = 8
Давайте дадим несколько имен для строк:  
```
fork ();   // Line 1  
fork ();   // Line 2  
fork ();   // Line 3  
  
       L1       // Там будет 1 дочерний процесс 
    /     \     // создано строкой Line 1.  
  L2      L2    // Там будет 2 дочерних процесса 
 /  \    /  \   //  создано строкой Line 2.  
L3  L3  L3  L3  // Там будет 4 дочерних процесса
                // создано строкой Line 3.
```
Таким образом, существует в общей сложности восемь процессов (новые дочерние процессы и один исходный процесс).  
Если мы хотим представить отношения между процессами в древовидной иерархии, это выглядит следующим образом:
Main process: P0  
Processes created by the 1st fork: **P1**  
Processes created by the 2nd fork: **P2, P3**  
Processes created by the 3rd fork: **P4, P5, P6, P7**
```
             P0  
         /   |   \  
       P1    P4   P2  
      /  \          \  
    P3    P6         P5  
   /  
 P7  
```
Мы прогнозируем результат следующей программы:  
```
#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
  
void forkexample()  
{  
    // дочерний процесс, поскольку возвращаемое значение равно нулю
    if (fork() == 0)  
        printf("Hello from Child!\n");  
    // родительский процесс, потому что возвращаемое значение не равно нулю.
    else  
        printf("Hello from Parent!\n");  
}  
int main()  
{  
    forkexample();  
    return (0);  
}  
```
Output:
```
1.  
Hello from Child!  
Hello from Parent!  
     (or)  
2.  
Hello from Parent!  
Hello from Child!  
```
Приведенный выше код создает дочерний процесс. fork () возвращает 0 в дочернем процессе и положительное целое число в родительском процессе.
Здесь есть два возможных выхода, потому что родительский процесс и дочерний процесс работают одновременно. Таким образом, мы не знаем, будет ли ОС сначала передавать управление родительскому процессу или дочернему процессу. 
  
**Important:** родительский процесс и дочерний процесс запускают одну и ту же программу, но это не означает, что они идентичны. Операционная система выделяет разные данные и состояния для этих двух процессов, и поток управления для этих процессов может отличаться.
Смотрите следующий пример:

```
#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
  
void forkexample()  
{  
    int x = 1;  
    if (fork() == 0)  
        printf("Child has x = %d\n", ++x);  
    else  
        printf("Parent has x = %d\n", --x);  
}  
  
int main()  
{  
    forkexample();  
    return (0);  
}  
```
Output:
```
Parent has x = 0  
Child has x = 2  
     (or)  
Child has x = 2  
Parent has x = 0  
```
Здесь изменение глобальной переменной в одном процессе не влияет на два других процесса, поскольку данные / состояние двух процессов различны. А также родительский и дочерний работают одновременно, так что есть два возможных выхода.  
  
### :page_facing_up: Execve()
**The execve() system call function** используется для выполнения двоичного исполняемого файла или скрипта.
Функция ничего не возвращает при успешном выполнении и -1 при ошибке.  
Первым параметром должен быть путь к двоичному исполняемому файлу или скрипту.
Второй должен быть массивом указателей на символ (char *myArray[]), а последний указатель должен быть установлен в значение NULL.  
Третьим параметром должно быть окружение.
  
Example:
```
#include        <stdio.h>  
#include        <stdlib.h>  
#include        <unistd.h>  
#include        <string.h>  
#include        <errno.h>  
  
int     main()  
{  
  int e;  
  char *envp[] = { NULL };  
  char *argv[] = { "/bin/ls", "-l", NULL };  
  
  e = execve("/bin/ls", argv, envp);  
  if (e == -1)  
      fprintf(stderr, "Error: %s\n", strerror(errno));  
  return (0);  
}  
```
Output:
```
drwxr-xr-x  2 badprog tutorial  4096 March  6 19:03 .  
drwxr-xr-x 39 badprog tutorial  4096 March  6 18:51 ..  
-rwxr-xr-x  1 badprog tutorial  7031 March  6 19:03 execve-me  
-rw-r--r--  1 badprog tutorial   385 March  6 19:03 main.c  
```

### :page_facing_up: pipe
Концептуально канал(pipe) - это соединение между двумя процессами, так что стандартный вывод одного процесса становится стандартным вводом другого процесса. В операционной системе UNIX каналы полезны для обмена данными между связанными процессами (межпроцессное взаимодействие).
  
* Канал является односторонним соединением, т.е. Мы можем использовать канал так, чтобы один процесс записывал в канал, а другой записывал из канала. Он открывает канал, представляющий собой область основной памяти, которая обрабатывается как "виртуальный файл".
* Канал может использоваться процессом создания, а также всеми его дочерними процессами для чтения и записи. Один процесс может записывать в этот "виртуальный файл" или канал, а другой связанный процесс может считывать из него.
* Если процесс пытается выполнить чтение до того, как что-то будет записано в канал, процесс приостанавливается до тех пор, пока что-то не будет записано.
Системный вызов канала находит первые две доступные позиции в таблице открытых файлов процесса и распределяет их по концам канала для чтения и записи.  
![](https://github.com/markveligod/minishell/raw/master/img/2.jpg)  
  
The syntax in C:
```
int pipe(int fds[2]);  
  
Parameters :  
fd[0] will be the fd(file descriptor) for the read end of pipe.  
fd[1] will be the fd for the write end of pipe.  
Returns : 0 on Success.  
-1 on error.  
```
Каналы ведут себя как FIFO ("первый вход, первый выход"), каналы ведут себя как структура данных очереди. Размер чтения и записи здесь не должен быть одинаковым. Мы можем записывать 512 байт за раз, но мы можем считывать только 1 байт за раз в канале.

```
#include <stdio.h>  
#include <unistd.h>  
#define MSGSIZE 16  
char* msg1 = "hello, world #1";  
char* msg2 = "hello, world #2";  
char* msg3 = "hello, world #3";  
  
int main()  
{  
    char inbuf[MSGSIZE];  
    int p[2], i;  
    if (pipe(p) < 0)  
        exit(1);  
    write(p[1], msg1, MSGSIZE);  
    write(p[1], msg2, MSGSIZE);  
    write(p[1], msg3, MSGSIZE);  
    for (i = 0; i < 3; i++) {  
        read(p[0], inbuf, MSGSIZE);  
        printf("% s\n", inbuf);  
    }  
    return (0);  
}
```
Output:
```
hello, world #1  
hello, world #2  
hello, world #3  
```
  
Когда мы используем fork в любом процессе, файловые дескрипторы остаются открытыми как для дочернего процесса, так и для родительского процесса. Если мы вызовем fork после создания канала, то родитель и потомок смогут взаимодействовать через канал.  
  
![](https://github.com/markveligod/minishell/raw/master/img/3.jpg)  

```
#include <stdio.h>  
#include <unistd.h>  
#define MSGSIZE 16  
  
char* msg1 = "hello, world #1";  
char* msg2 = "hello, world #2";  
char* msg3 = "hello, world #3";  
  
int main()  
{  
    char inbuf[MSGSIZE];  
    int p[2], pid, nbytes;  
    if (pipe(p) < 0)  
        exit(1);  
    if ((pid = fork()) > 0) {  
        write(p[1], msg1, MSGSIZE);  
        write(p[1], msg2, MSGSIZE);  
        write(p[1], msg3, MSGSIZE);  
        wait(NULL);  
    }  
    else {  
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0)  
            printf("% s\n", inbuf);  
        if (nbytes != 0)  
            exit(2);  
        printf("Finished reading\n");  
    }  
    return (0);  
}
```
Output:
```
hello world, #1  
hello world, #2  
hello world, #3  
(hangs)         //program does not terminate but hangs  
```
Здесь, в этом коде, после завершения чтения / записи родительский и дочерний блоки вместо завершения процесса, и поэтому программа зависает. Это происходит потому, что системный вызов read получает столько данных, сколько запрашивает, или столько данных, сколько есть в канале, в зависимости от того, что меньше.

* Если канал пуст и мы вызываем системный вызов read, то чтение по каналу вернет EOF (возвращаемое значение равно 0), если ни у одного из процессов не открыт конец записи.
* Если у какого-либо другого процесса открыт канал для записи, чтение блокируется во время ожидания новых данных, поэтому вывод этого кода зависает, потому что здесь запись завершает родительский процесс, а дочерний процесс не закрывается. 


## Полезные ссылки:
[«Шелл» на С: пишем командную оболочку для Unix](https://tproger.ru/translations/unix-shell-in-c/)  
[Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)  
[Изучаем процессы в Linux](https://habr.com/ru/post/423049/)  
[Создание процессов с помощью вызова fork().](https://www.opennet.ru/docs/RUS/linux_parallel/node7.html)  
[Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)  
[Making your own Linux Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)  
[Чтение содержимого директорий diropen, readdir, closedir](https://firststeps.ru/linux/r.php?20)  
[Несколько подробностей о функции main](https://habr.com/ru/post/128111/)  
[Коды ошибок для errno](https://gist.github.com/greggyNapalm/2413028)  
[Fork() execve and pipe](https://yanniss.github.io/k24/set005.pdf)

## Прочее

**Авторы:**  
*[Andrey Belenov](https://github.com/luchikAR)*  
*[Soslan Zagagov](https://github.com/fldelena)*  
