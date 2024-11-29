# ft_printf

## Main Functions
- ```int  ft_printf(char *str, ...);```
  - Acts like `printf()` with more format specifiers
- ```int  ft_printf_fd(char *str, int fd, ...);```
  - Acts like `dprintf()` with more format specifiers
- ```int  ft_printf_err(char *msg, int fd, ...);```
  - Acts like `perror()` with format specifiers and a mandatory fd.
  - **NOTE : `msg` can be NULL.**
  - **NOTE : `fd` is mandatory because it will often be used for logs**
  - Examples :
    - ```
      ft_printf_err(NULL, 0);
      >>> "Remote I/O error"

      ft_printf_err("err", 0);
      >>> "err: Socket type not supported"
      
      ft_printf_err("errid[%d]", 0, i);
      >>> "errid[778]: Success"
      ```

## Makefile
- It is easy to try the library with ```make test```, it just needs a `main.c`.
- Everytime ```make``` is called, it will copy `.errmsg` in `/var/tmp/` or try to for `ft_printf_err()` to work.

## Formats && Flags
|Format|Data Type|Desc|
|:-|:-|:-|
|```%c```|```char``` |Prints a single character (e.g. 'o', '\n')|
|```%d, %i```|```int```|Prints a signed integer (e.g. 777, ```INT_MAX```, -55)|
|```%s```|```char *```|Prints a string (e.g. "I am ###", "")|
|```%p```|```void *```|Prints the adress of a pointer (e.g. 0xffffffff, 0x0)|
|```%u```|```unsigned int```|Prints an unsigned integer (e.g. ```INT_MAX + 2```, 4_000_000_000)|
|```%%```|None|Prints a percent (e.g. Do you really need an example?)|
|```%x, %X```|```int```|Prints an integer in hexadecimal (e.g. BAB3 if %X, bab3 if %x)|

### Special Format
```%b, %B```

- Data Types : ```int, char *```
- Behaviour : Prints a ```unsigned long int``` or a ```char *``` in another base.
- Basic Usage :
  - ```%b<base>``` will print an ```unsigned long int``` to another base with lowercase.
  - ```%B<base>``` will print an ```unsigned long int``` to another base with uppercase.
  - **NOTE : `base` cannot be lower than 2 nor higher than 36.**
- Flag : If a specific base is entered between '[' and ']', it will print from a ```char *``` to another base.
  - **NOTE : it won't work if there is something else than a number between 2 and 36 in the dedicated space.**
- Examples :
  - ```ft_printf("%b2", 10);
    >>> "1010"
    
    ft_printf("%b02", 10);
    >>> "1010"
    
    ft_printf("%b[08]2", "12");
    >>> "1010"
    
    ft_printf("%B36", INT_MAX);
    >>> "ZIK0ZJ"
    
    ft_printf("%b[2]36", "1111111111111111111111111111111");
    >>> "zik0zj"
    ```
- Not to Do :
  - ```
    ft_printf("%b[10]2", 10); // Not a string
    
    ft_printf("%b[010]2", "10"); // Too much characters between '[' and ']'
    
    ft_printf("%B[]10", "0"); // No character between '[' and ']'
    
    ft_printf("%B[s.]0", NULL) // NULL given as parameter
    >>> 0
    
    ft_printf("%b[6]36", "6"); // "6" not in base 6
    >>> 0
    ```

```%_0, %_1```

- Data Type : ```int```
- Behaviour : Prints a Boolean.
- ```%_0``` :
  - ```ft_printf("%_0", izzokz_likes_deathstep());``` prints TRUE.
  - ```ft_printf("%_0", 3 + 1 == 5);``` prints FALSE.
- ```%_1``` :
  - ```ft_printf("%_1", 1);``` prints **${{\color{green}\Huge{\textsf{TRUE}}}}\$**
  - ```ft_printf("%_1", izzokz_is_sane());``` prints **${{\color{red}\Huge{\textsf{FALSE}}}}\$**
  - **NOTE : Wait... WHAT??**

```%f#, %f#/```

- Data Types : ```int, char *```
- Behaviour : Prints the content of a file from a file descriptor or a filename.
- Basic Usage :
  - ```%f#``` will print the content of an opened file, using its file descriptor.
    - **NOTE : if you have already read a part of the file, it won't read it nor print it.**
    - **NOTE : once printed, the file is fully read, use lseek() if you want to reuse the file descriptor.**
  - ```%f#/``` will print the content of a file by opening it.
    - **NOTE : it won't work if the file does not exist.**
- Flag : If a specific line is entered between '[' and ']', it will print only one line of the file.
  - **NOTE : lines start at 1.**
  - **NOTE : it won't work if the line number equals 0.**
  - **NOTE : it will work if the line number is negative or overflows the number of lines.**
    - **NOTE : it works as a loop such as integers : INT_MIN - 1 == INT_MAX.**
    - **NOTE : [-1] will print the last line, [-2] the previous one and so on.**
- Examples :
  - ```
    ft_printf("%f#", fd);
    >>> Hello World !
    >>> My Name Is Izzokz !
    >>> Nice To Meet You !

    ft_printf("%f#[-2]", fd);
    >>> My Name Is Izzokz !

    ft_printf("%f#[-6]", fd);
    >>> Hello World !

    ft_printf("%f#/[55]", "../100_UTILS/.errmsg");
    >>> No anode

    ft_printf("%f#/[133]", "../100_UTILS/.errmsg");
    >>> Success
    ```
- Not to Do :
  - ```
    ft_printf("%f#/[5]", fd); // expected filename, file descriptor given instead
    
    ft_printf("%f#", "test.txt"); // expected file descriptor, filename given instead

    ft_printf("%f#[0]", fd); // 0 given as line number
    ```

### Special Flag
```%*```

- Behaviour : Prints every variable in an array.
  - **NOTE : the array must be NULL terminated.**
#### Special Flag of Special Flag
```.```

- Behaviour : After ```%*```, means that it will print every variable of every array contained in the source array, recursively.
- Parameter : As the C language can't go through pointers recursively without SIGSEGV, it needs a depth parameter as its light in the dark cave of dereferencing.
  - **NOTE : `depth` can't be 0 or higher than 9.**
  - **NOTE : every array has to be NULL terminated.**
  - **NOTE : using it with pointers of arrays will result in Segfault.**

```[separator]```

- Behaviour : Will prints separator between each print. Won't work if separator is empty or if the last character of separator is '['.
  - **NOTE : It has to be the last Flag of Flag.**

- Examples :
  - ```
    ft_printf("%*s", {"Hello", "Hohoho", "Hi", NULL});
    >>> "HelloHohohoHi"
    
    ft_printf("%*i", {1, 2, 3, 4, 5, '\0'});
    >>> "12345"
    
    ft_printf("%*[ ]s", {"My", "name", "is", "Izzokz", NULL});
    >>> "My name is Izzokz"
    
    ft_printf("%*.4[:[>:]i", {{{{1, 7, 0}, {2, 6, 0}, NULL}, {{3, 5, 0}, NULL}, NULL}, NULL});
    >>> "1:[>:7:[>:2:[>:6:[>:3:[>:5"
    
    ft_printf("%*.3[, ]p", {{{{1, 7, 0}, {2, 6, 0}, NULL}, {{3, 5, 0}, NULL}, NULL}, NULL});
    >>> "0xfff, 0xaaa, 0x111"
    ```
- Not to Do :
  - ```
    ft_printf("%*.3[, ]p", {{{{1, 7}, {2, 6}}, {{3, 5}}}}); // No NULL termination
    
    ft_printf("%*.2[\n]i", &array); // Expected array, pointer given instead

    ft_printf("%*.3[]p", {{{{1, 7, 0}, {2, 6, 0}, NULL}, {{3, 5, 0}, NULL}, NULL}, NULL}); // Empty separator slot

    ft_printf("%*[normal sep until this -> []i", {1, 2, 3, 4, 5, '\0'}); // Last character of the separator is '['

    ft_printf("%*.3[ ]s", {"My", "name", "is", "Izzokz", NULL}); // Invalid depth : too high -> SIGSEGV
    ```
- **NOTE : I made it easier in that way. If your pointer looks like this ```int ***arr``` or ```unsigned int **arr```, you will use or ```%*.3i``` or ```%*.2u```. With ```%s``` or ```%p```, you will decrease the parameter of the flag of flag ```.``` by one (```%*.4s``` for ```char *****str``` or ```%*.2p``` for ```unsigned int ***arr```).**
