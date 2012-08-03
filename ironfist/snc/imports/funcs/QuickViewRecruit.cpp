{
  heroWindow *v8; // [sp+14h] [bp-3Ch]@8
  int avail; // [sp+18h] [bp-38h]@1
  int goldCost; // [sp+1Ch] [bp-34h]@1
  signed int i; // [sp+20h] [bp-30h]@1
  int specialResourceAmt; // [sp+24h] [bp-2Ch]@6
  heroWindow *window; // [sp+28h] [bp-28h]@9
  int costs[7]; // [sp+2Ch] [bp-24h]@1
  int specialResource; // [sp+48h] [bp-8h]@6
  int creatureType; // [sp+4Ch] [bp-4h]@1

  creatureType = gDwellingType[castle->factionID][dwellingIdx];
  avail = castle->numCreaturesInDwelling[dwellingIdx];
  getCreatureCosts(creatureType, costs);
  goldCost = costs[6];
  for ( i = 0; i < 6 && !costs[i]; ++i )
    ;
  if ( i >= 6 )
  {
    specialResource = -1;
    specialResourceAmt = 0;
  }
  else
  {
    specialResource = i;
    specialResourceAmt = costs[i];
  }
  v8 = (heroWindow *)operator new(68);
  if ( v8 )
    window = heroWindow::heroWindow(
               v8,
               160,
               16,
               &aRecruiq0_bin[("recruiq1.bin" - "recruiq0.bin") & ((specialResource == -1) - 1)]);
  else
    window = 0;
  if ( !window )
    MemError();
  SetupRecruitWin(window, creatureType, goldCost, specialResource, specialResourceAmt, avail);
  heroWindowManager::AddWindow(gpWindowManager, window, -1, 1);
  QuickViewWait();
  heroWindowManager::RemoveWindow(gpWindowManager, window);
}