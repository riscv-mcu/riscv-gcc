// { dg-do compile }
// { dg-options "-O2 -fdump-tree-evrp-details" }

void gg(void);
int f(unsigned t)
{
  unsigned g = t*16;
  if (g==0)  return 1;
  gg();
  gg();
  gg();
  gg();
  gg();
  gg();
  if (g<=4)  return 1;
  return 0;
}

// With -O2, CCP (flag_ipa_bit_cp) exports the narrowed range and bitmask
// for g via set_bitmask, so EVRP no longer prints a new "Global Exported"
// line; check the range with the mask in the evrp dump instead.
// { dg-final { scan-tree-dump "g_\[0-9\]+.*MASK 0xfffffff0 VALUE 0x0" "evrp" } }
