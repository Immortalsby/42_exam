#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct  s_ptf
{
    va_list ap;
    int     i;
    int     len;
    int     width;
    int     precision;
    int     precision_width;
    int     precision_parsing;
    int     ret;
}               t_ptf;

int     ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *s, int len)
{
    write(1, s, len);
}

void    init_ptf(t_ptf *ptf)
{
    ptf->len=0;
    ptf->width=0;
    ptf->precision=0;
    ptf->precision_width=0;
    ptf->precision_parsing=0;
}

int     is_conv(char c)
{
    if(c == 's' || c == 'x' || c == 'd')
        return (1);
    else
        return (0);
}

int     is_digit(char c)
{
    if(c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

int     ft_atoi(char *s, t_ptf *ptf)
{
    int res;

    res = 0;
    while (is_digit(s[ptf->i]))
    {
        res = res * 10 + s[ptf->i] - 48;
        ptf->i++;
    }
    ptf->i--;
    return (res);
}

void    print_spaces(t_ptf *ptf, int len)
{
    int     i;

    i = 0;
    if (len < 0)
        return ;
    while (i < len)
    {
        ft_putchar(' ');
        i++;
    }
    ptf->ret = ptf->ret + len;
}

void    print_zeros(t_ptf *ptf, int len)
{
    int     i;

    i = 0;
    if (len < 0)
        return ;
    while (i < len)
    {
        ft_putchar('0');
        i++;
    }
    ptf->ret = ptf->ret + len;
}

void    convert_str(t_ptf *ptf)
{
    char *s;

    s = va_arg(ptf->ap, char *);
    if (!s)
        s = "(null)";
    ptf->len = ft_strlen(s);
    if(ptf->precision && ptf->precision_width < ptf->len)
        ptf->len = ptf->precision_width;
    print_spaces(ptf, ptf->width-ptf->len);
    ft_putstr(s, ptf->len);
    ptf->ret += ptf->len;
}

int    ft_intlen_base(intmax_t nb, char *base)
{
    int len;
    int b_len;

    len = 1;
    b_len = ft_strlen(base);
    if (nb < 0)
        nb = -nb;
    while (nb >= b_len)
    {
        nb = nb / b_len;
        len++;
    }
    return (len);
}

void    ft_putnbr_base(intmax_t nb, char *base)
{
    int base_len;

    base_len = ft_strlen(base);
    if(nb < 0)
        nb = -nb;
    if (nb >= base_len)
        ft_putnbr_base(nb / base_len, base);
    ft_putchar(base[nb % base_len]);
}

void    convert_int(t_ptf *ptf)
{
    intmax_t  nb;
    int         sp;

    sp = 0;
    nb = va_arg(ptf->ap, int);
    ptf->len = ft_intlen_base(nb, "0123456789");
    if (nb == 0)
        ptf->len = 0;
    if (ptf->precision && ptf->precision_width > ptf->len)
        sp = ptf->precision_width - ptf->len;
    if (nb < 0)
        ptf->len += 1;
    print_spaces(ptf, ptf->width - ptf->len - sp);
    if (nb < 0)
        ft_putchar('-');
    print_zeros(ptf, sp);
    if (ptf->precision && nb == 0)
        return ;
    ft_putnbr_base(nb, "0123456789");
    ptf->ret += ptf->len;
}

void    convert_hex(t_ptf *ptf)
{
    intmax_t  nb;
    int         sp;
    sp = 0;
    nb = va_arg(ptf->ap, unsigned int);
    ptf->len = ft_intlen_base(nb, "0123456789abcdef");
    if (ptf->precision && ptf->precision_width > ptf->len)
        sp = ptf->precision_width - ptf->len;
    print_spaces(ptf, ptf->width - sp - ptf->len);
    print_zeros(ptf, sp);
    if (ptf->precision && ptf->precision_width == 0 && nb == 0)
        return ;
    ft_putnbr_base(nb, "0123456789abcdef");
    ptf->ret += ptf->len;
}

void    parse(char *str, t_ptf *ptf)
{
    ptf->i++;
    init_ptf(ptf);
    while (!is_conv(str[ptf->i]))
    {
        if (is_digit(str[ptf->i]))
        {
            if (ptf->precision_parsing)
                ptf->precision_width = ft_atoi(str, ptf);
            else
                ptf->width = ft_atoi(str, ptf);
        }
        ptf->precision_parsing = 0;
        if (str[ptf->i] == '.')
        {
            ptf->precision = 1;
            ptf->precision_parsing = 1;
        }
        ptf->i++;
    }
    str[ptf->i] == 's' ? convert_str(ptf) : 0;
    str[ptf->i] == 'd' ? convert_int(ptf) : 0;
    str[ptf->i] == 'x' ? convert_hex(ptf) : 0;
}

int     ft_printf(const char *str, ...)
{
    t_ptf ptf;

    ptf.i = 0;
    ptf.ret = 0;
    va_start(ptf.ap, str);
    while (str[ptf.i])
    {
        if (str[ptf.i] == '%')
            parse((char*)str, &ptf);
        else
        {
            ft_putchar(str[ptf.i]);
            ptf.ret++;
        }
        ptf.i++;
    }
    va_end(ptf.ap);
    return(ptf.ret);
}

int main()
{
    int d = 12;
    char *s = "hello";
    int x = 1234;
    int i;
    int j;
    i = ft_printf("%12d, %.8d, %12.8d, %12s, %.12s, %12.8s, %12x, %.8x, %12.8x\n", d,d,d,s,s,s,x,x,x);
    printf("%d\n", i);
    j = printf("%12d, %.8d, %12.8d, %12s, %.12s, %12.8s, %12x, %.8x, %12.8x\n", d,d,d,s,s,s,x,x,x);
    printf("%d\n", j);
    return (0);
}
