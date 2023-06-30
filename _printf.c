#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int _printf(const char *format, ...)
{
int count = 0;
char *s;
char c;
int num;
unsigned int unum;
char sbuffer[1024];
int j, k;
va_list print_args;
int ret;
int rem;
int width;
int i;
char hex[3];
void *p;

va_start(print_args, format);

while (*format != '\0')
{
if (*format == '%')
{
width = 0;
while (isdigit(*++format))
{
width = width * 10 + (*format - '0');
}


switch (*++format)
{
case 'c':
c = va_arg(print_args, int);
write(1, &c, 1);
count++;
break;

case 's':
s = va_arg(print_args, char *);

if (s == NULL)
s = "(null)";

while (*s != '\0')
{
write(1, s, 1);
s++;
count++;
}

break;

case '%':
write(1, "%", 1);
count++;
break;

case 'd':
case 'i':
num = va_arg(print_args, int);
if (num == 0)
{
ret = write(1, "0", 1);
if (ret == -1)
return (-1);
count++;
}
else if (num < 0)
{
ret = write(1, "-", 1);
if (ret == -1)
return (-1);
count++;
num = -num;
}
j = 0;
while (num > 0)
{
sbuffer[j] = (num % 10) + '0';
j++;
num = num / 10;
}
while (width > 0)
{
write(1, " ", 1);
width--;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
break;

case 'u':
unum = va_arg(print_args, unsigned int);
if (unum == 0)
{
ret = write(1, "0", 1);
if (ret == -1)
return (-1);
count++;
}
else
{
j = 0;
while (unum > 0)
{
sbuffer[j] = (unum % 10) + '0';
j++;
unum = unum / 10;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
}
break;

case 'o':
unum = va_arg(print_args, int);
if (unum == 0)
{
ret = write(1, "0", 1);
if (ret == -1)
return (-1);
count++;
}
else
{
j = 0;
while (unum > 0)
{
sbuffer[j] = (unum % 8) + '0';
j++;
unum = unum / 8;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
}
break;

case 'x':
unum = va_arg(print_args, int);
if (unum == 0)
{
ret = write(1, "0", 1);
if (ret == -1)
return (-1);
count++;
}
else
{
j = 0;
while (unum > 0)
{

rem = unum % 16;
if (rem < 10)
{
sbuffer[j] = rem + '0';
}
else
{
sbuffer[j] = rem + 'a' - 10;
}
j++;
unum = unum / 16;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
}
break;

case 'X':
unum = va_arg(print_args, int);
if (unum == 0)
{
ret = write(1, "0", 1);
if (ret == -1)
return (-1);
count++;
}
else
{
j = 0;
while (unum > 0)
{

rem = unum % 16;
if (rem < 10)
{
sbuffer[j] = rem + '0';
}
else
{
sbuffer[j] = rem + 'A' - 10;
}
j++;
unum = unum / 16;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
}
break;

case 'S':
s = va_arg(print_args, char *);

if (s == NULL)
s = "(null)";

i = 0;
while (s[i] != '\0')
{

c = s[i];

if (isprint(c))
{
write(1, &c, 1);
count++;
}
else
{
write(1, "\\x", 2);
count += 2;
sprintf(hex, "%02X", c);
write(1, hex, 2);
count += 2;
}
i++;
}
break;

case 'p':
{
p = va_arg(print_args, void *);

sprintf(hex, "%p", p);
write(1, hex, strlen(hex));
count += strlen(hex);
}
break;

case '+':
{
num = va_arg(print_args, int);
if (num >= 0)
{
write(1, "+", 1);
count++;
}
else
{
write(1, "-", 1);
count++;
num = -num;
}
j = 0;
while (num > 0)
{
sbuffer[j] = (num % 10) + '0';
j++;
num = num / 10;
}
for (k = j - 1; k >= 0; k--)
{
ret = write(1, &sbuffer[k], 1);
if (ret == -1)
return (-1);
count++;
}
format++;
}
break;






default:
write(1, "%%", 2);
count += 2;
break;
}
}
else
{
write(1, format, 1);
count++;
}

format++;
}

va_end(print_args);

return (count);
}
