{
  signed int result; // eax@3
  int v2; // [sp+Ch] [bp-2Ch]@1
  signed int i; // [sp+14h] [bp-24h]@12
  int arr[7]; // [sp+1Ch] [bp-1Ch]@12

  v2 = *(_DWORD *)(a1 + 4);
  if ( !v2 )
  {
    if ( CanBuy(*(_DWORD *)a1, *(_DWORD *)(a1 + 8)) )
      return 1;
    return 0;
  }
  if ( v2 == 1 )
  {
    if ( gpCurPlayer->resources[6] >= gHeroGoldCost && *(_BYTE *)(*(_DWORD *)a1 + 23) == -1 && !bHeroBuiltThisTurn )
      return 1;
    return 0;
  }
  if ( v2 != 2 )
    return 0;
  if ( (signed int)*(_WORD *)(*(_DWORD *)a1 + 2 * *(_DWORD *)(a1 + 8) + 30) >= *(_DWORD *)(a1 + 12) )
  {
    getCreatureCosts(gDwellingType[*(_BYTE *)(*(_DWORD *)a1 + 3)][*(_DWORD *)(a1 + 8)], arr);
    for ( i = 0; i < 7; ++i )
    {
      if ( *(_DWORD *)(a1 + 12) * arr[i] > gpCurPlayer->resources[i] )
        return 0;
    }
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}