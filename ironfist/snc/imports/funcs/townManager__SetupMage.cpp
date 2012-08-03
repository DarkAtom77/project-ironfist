{
  signed int v2; // eax@22
  signed int v3; // eax@23
  void *v4; // ST2C_4@27
  townManager *thisa; // [sp+Ch] [bp-60h]@1
  bool v7; // [sp+10h] [bp-5Ch]@9
  Event evt; // [sp+20h] [bp-4Ch]@1
  int j; // [sp+3Ch] [bp-30h]@5
  __int16 v10; // [sp+40h] [bp-2Ch]@1
  __int16 v11; // [sp+44h] [bp-28h]@1
  int i; // [sp+4Ch] [bp-20h]@3
  bool v13; // [sp+50h] [bp-1Ch]@12
  __int16 v14; // [sp+54h] [bp-18h]@1
  __int16 v15; // [sp+58h] [bp-14h]@1
  __int16 v16; // [sp+5Ch] [bp-10h]@1
  __int16 v17; // [sp+60h] [bp-Ch]@1
  __int16 v18; // [sp+64h] [bp-8h]@1
  __int16 v19; // [sp+68h] [bp-4h]@1

  thisa = this;
  v19 = 0;
  v14 = 1;
  v10 = 999;
  v11 = 2;
  v18 = 10;
  v15 = 40;
  v16 = 70;
  v17 = 100;
  evt.inputEvt.eventCode = INPUT_GUI_MESSAGE_CODE;
  if ( this->castle->visitingHeroIdx == -1 )
  {
    strcpy(gText, "The above spells are available here.");
    *(_QWORD *)&evt.inputEvt.xCoordOrKeycode = GUI_MESSAGE_SET_CONTENTS;
    evt.inputEvt.payload = gText;
    heroWindow::BroadcastMessage(mageGuildWindow, &evt);
  }
  for ( i = 0; i < 5; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      v7 = thisa->castle->factionID == 4 && BYTE1(thisa->castle->buildingsBuiltFlags) & 0x20;
      if ( v7 + mageGuildSpellsForLevel[i + 1] > j )
        v13 = thisa->castle->numSpellsOfLevel[i] <= j;
      else
        v13 = 999;
      if ( v13 == 999 )
        evt.inputEvt.xCoordOrKeycode = 6;
      else
        evt.inputEvt.xCoordOrKeycode = 5;
      evt.inputEvt.yCoord = j + 4 * i + 10;
      evt.inputEvt.payload = (void *)4;
      heroWindow::BroadcastMessage(mageGuildWindow, &evt);
      if ( v13 != 999 )
      {
        evt.inputEvt.xCoordOrKeycode = 4;
        evt.inputEvt.yCoord = j + 4 * i + 10;
        evt.inputEvt.payload = (void *)v13;
        heroWindow::BroadcastMessage(mageGuildWindow, &evt);
      }
      if ( v13 )
      {
        evt.inputEvt.xCoordOrKeycode = 6;
        evt.inputEvt.payload = (void *)4;
        evt.inputEvt.yCoord = j + 4 * i + 40;
        heroWindow::BroadcastMessage(mageGuildWindow, &evt);
        evt.inputEvt.yCoord = j + 4 * i + 70;
        heroWindow::BroadcastMessage(mageGuildWindow, &evt);
      }
      else
      {
        evt.inputEvt.xCoordOrKeycode = 4;
        evt.inputEvt.yCoord = j + 4 * i + 40;
        evt.inputEvt.payload = (void *)gsSpellInfo[thisa->castle->mageGuildSpells[i][j]].spriteIdx;
        heroWindow::BroadcastMessage(mageGuildWindow, &evt);
        if ( font::LineLength(smallFont, gSpellNames[thisa->castle->mageGuildSpells[i][j]], 74) == 1 )
        {
          v2 = GetManaCost(thisa->castle->mageGuildSpells[i][j], 0);
          sprintf(gText, "%s\n[%d]", gSpellNames[thisa->castle->mageGuildSpells[i][j]], v2);
        }
        else
        {
          v3 = GetManaCost(thisa->castle->mageGuildSpells[i][j], 0);
          sprintf(gText, "%s  [%d]", gSpellNames[thisa->castle->mageGuildSpells[i][j]], v3);
        }
        evt.inputEvt.xCoordOrKeycode = 3;
        evt.inputEvt.yCoord = j + 4 * i + 70;
        evt.inputEvt.payload = gText;
        heroWindow::BroadcastMessage(mageGuildWindow, &evt);
      }
    }
  }
  v4 = (void *)(thisa->castle->mageGuildLevel - 1);
  *(_QWORD *)&evt.inputEvt.xCoordOrKeycode = GUI_MESSAGE_SET_IMG_IDX;
  evt.inputEvt.payload = v4;
  heroWindow::BroadcastMessage(mageGuildWindow, &evt);
  sprintf(gText, "magegld%c.icn", cHeroTypeInitial[thisa->castle->factionID]);
  *(_QWORD *)&evt.inputEvt.xCoordOrKeycode = 429496729609i64;
  evt.inputEvt.payload = gText;
  return heroWindow::BroadcastMessage(mageGuildWindow, &evt);
}