{
  unsigned __int8 v0; // ST10_1@6
  int result; // eax@10
  unsigned __int8 v2; // ST0C_1@12
  int l; // [sp+14h] [bp-410h]@10
  signed int k; // [sp+18h] [bp-40Ch]@7
  signed int i; // [sp+1Ch] [bp-408h]@1
  int j; // [sp+1Ch] [bp-408h]@4
  int v7; // [sp+1Ch] [bp-408h]@10
  int v8[256]; // [sp+20h] [bp-404h]@3
  int v9; // [sp+420h] [bp-4h]@7

  for ( i = 0; i <= 255; ++i )
    v8[i] = 0;
  for ( j = 0; j <= last; ++j )
  {
    v0 = *((_BYTE *)ll + j);
    *((_DWORD *)zptr + j) = v8[v0]++;
  }
  v9 = 0;
  for ( k = 0; k <= 255; ++k )
  {
    v9 += v8[k];
    v8[k] = v9 - v8[k];
  }
  v7 = origPtr;
  result = last;
  for ( l = last; l >= 0; --l )
  {
    v2 = *((_BYTE *)ll + v7);
    *((_BYTE *)block + l) = v2;
    result = *((_DWORD *)zptr + v7) + v8[v2];
    v7 = *((_DWORD *)zptr + v7) + v8[v2];
  }
  return result;
}