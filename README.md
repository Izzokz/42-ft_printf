# ft_printf

## Main Functions
- ```int  ft_printf(char *str, ...);```
- ```int  ft_printf_fd(char *str, int fd, ...);```

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
  - ```%b<base>``` will print an ```unsigned long int``` to another base with lowercase
  - ```%B<base>``` will print an ```unsigned long int``` to another base with uppercase
  - **NOTE : base cannot be lower than 2 nor higher than 36**
- Flag : If a specific base is entered between '[' and ']', it will print from a ```char *``` to another base
  - **NOTE : it won't work if there is something else than a number between 2 and 36 in the dedicated space**
- Examples :
  - ```ft_printf("%b2", 10) >>> "1010"```
  - ```ft_printf("%b02", 10) >>> "1010"```
  - ```ft_printf("%b[08]2", "12") >>> "1010"```
  - ```ft_printf("%B36", INT_MAX) >>> "ZIK0ZJ"```
  - ```ft_printf("%b[2]36", "1111111111111111111111111111111") >>> "zik0zj"```
- Not to Do :
  - ```ft_printf("%b[10]2", 10)```
  - ```ft_printf("%b[010]2", "10")```
  - ```ft_printf("%B[]10", "0")```
  - ```ft_printf("%b[6]36", "6")```

```%_0, %_1```

- Data Type : ```int```
- Behaviour : Prints a Boolean
- ```%_0``` :
  - ```ft_printf("%_0", izzokz_likes_deathstep())``` prints TRUE
  - ```ft_printf("%_0", 3 + 1 == 5)``` prints FALSE
- ```%_1``` :
  - ```ft_printf("%_1", 1)``` prints **${{\color{green}\Huge{\textsf{TRUE}}}}\$**
  - ```ft_printf("%_1", izzokz_is_sane())``` prints **${{\color{red}\Huge{\textsf{FALSE}}}}\$**
  - **NOTE : Wait... WHAT??**

### Special Flag
```%*```

- Behaviour : Prints every variable in an array.
- **NOTE : the array must be NULL terminated.**
#### Special Flag of Special Flag
```.```

- Behaviour : After ```%*```, means that it will print every variable of every array contained in the source array, recursively.
- Parameter : As the C language can't go through pointers recursively without SIGSEGV, it needs a depth parameter as its light in the dark cave of dereferencing.
 - **NOTE : depth can't be 0 or higher than 9**
 - **NOTE : every array has to be NULL terminated**
 - **NOTE : using it with pointers of arrays will result in Conditional Jump**

```[separator]```

- Behaviour : Will prints separator between each print. Won't work if separator is empty or if the last character of separator is '['.
  - **NOTE : It has to be the last Flag of Flag**

- Examples :
  - ```ft_printf("%*s", {"Hello", "Hohoho", "Hi", NULL}) >>> "HelloHohohoHi"```
  - ```ft_printf("%*i", {1, 2, 3, 4, 5, '\0'}) >>> "12345"```
  - ```ft_printf("%*[ ]s", {"My", "name", "is", "Izzokz", NULL}) >>> "My name is Izzokz"```
  - ```ft_printf("%*.4[::]i", {{{{1, 7, 0}, {2, 6, 0}, NULL}, {{3, 5, 0}, NULL}, NULL}, NULL}) >>> "1::7::2::6::3::5"```
  - ```ft_printf("%*.3[, ]p", {{{{1, 7, 0}, {2, 6, 0}, NULL}, {{3, 5, 0}, NULL}, NULL}, NULL}) >>> "0xfff, 0xaaa, 0x111"```
- Not to Do :
  - ```ft_printf("%*.3[, ]p", {{{{1, 7}, {2, 6}}, {{3, 5}}}})```
  - ```ft_printf("%*.2[\n]i", &array)```
- **NOTE : I made it easier in that way. If your pointer looks like this ```int ***arr``` or ```unsigned int **arr```, you will use or ```%*.3i``` or ```%*.2u```. With ```%s``` or ```%p```, you will decrease the parameter of the flag of flag ```.``` by one (```%*.4s``` for ```char *****str``` or ```%*.2p``` for ```unsigned int ***arr```).**
