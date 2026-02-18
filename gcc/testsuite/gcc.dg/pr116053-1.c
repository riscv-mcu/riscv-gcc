/* { dg-do compile } */
/* { dg-options "-O1 -finstrument-functions -fno-forward-propagate -fno-delete-dead-exceptions -fnon-call-exceptions" } */
/* { dg-require-effective-target exceptions } */

/* PR rtl-optimization/116053 */

void
foo (__int128 x)
{
  x = *(__int128 *) __builtin_memset (&x, 0, 10);
}
