/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-flto" } { "" } } */
/* { dg-options "-march=rv64gc_xxlczbri -mabi=lp64 -mtune=rocket -mautogen-xxlcz" } */
/* { dg-final { check-function-bodies "**" "" } } */

int foo_n1(int a, int b, int c)
{
    /*
**foo_n1:
**  ...
**  xl.b(eq|ne)i	[ats][0-9]+,-1,.L[0-9]+
**  ...
*/
    if (a == -1)
	return b - c;
    return c - b;
}

int foo_zero(int a, int b, int c)
{
    /*
**foo_zero:
**  ...
**  b(eq|ne)	[ats][0-9]+,zero,.L[0-9]+
**  ...
*/
    if (a == 0)
	return b - c;
    return c - b;
}

int foo_1(int a, int b, int c)
{
    /*
**foo_1:
**  ...
**  xl.b(eq|ne)i	[ats][0-9]+,1,.L[0-9]+
**  ...
*/
    if (a == 1)
	return b - c;
    return c - b;
}

int foo_15(int a, int b, int c)
{
    /*
**foo_15:
**  ...
**  xl.b(eq|ne)i	[ats][0-9]+,-15,.L[0-9]+
**  ...
*/
    if (a == -15)
	return b - c;
    return c - b;
}

int foo_16(int a, int b, int c)
{
    /*
**foo_16:
**  ...
**  b(eq|ne)	[ats][0-9]+,[ats][0-9]+,.L[0-9]+
**  ...
*/
    if (a == 16)
	return b - c;
    return c - b;
}
