{
  int v13; // eax@1
  searchArray *thisa; // edi@1
  PathfindingInfo *v15; // eax@8
  char v16; // al@8
  int v17; // eax@14
  char *v18; // eax@14
  char v19; // cl@22
  void *v20; // ecx@24
  int v21; // edx@24

  LOBYTE(v13) = a6;
  thisa = this;
  if ( a6 >= a5 || a6 <= 0 )
  {
    if ( a2 >= 0 )
    {
      LOBYTE(v13) = MAP_WIDTH - 1;
      if ( MAP_WIDTH - 1 >= a2 )
      {
        LOBYTE(v13) = a3;
        if ( a3 >= 0 )
        {
          LOBYTE(v13) = MAP_HEIGHT - 1;
          if ( MAP_HEIGHT - 1 >= a3 )
          {
            v13 = this->field_0;
            if ( this->field_0 < 0x400u )
            {
              dword_526B94 = 0;
              dword_526B98 = v13;
              v15 = &this->field_2414[a2 + a3 * MAP_WIDTH];
              dword_526B78 = (int)v15;
              v16 = v15->field_4;
              if ( !(v16 & 1)
                || ((LOBYTE(v13) = v13 & 4, (_BYTE)v13) || !a8)
                && (*(_WORD *)(dword_526B78 + 2) > a5 || (_BYTE)v13 && (LOBYTE(v13) = a8, !a8)) )
              {
                while ( 1 )
                {
                  v17 = (dword_526B98 + dword_526B94) >> 1;
                  dword_526B90 = v17;
                  v18 = (char *)&this->mainDataStructure[v17];
                  Src = v18;
                  if ( dword_526B94 >= dword_526B98 )
                    break;
                  if ( *((_WORD *)v18 + 1) <= a5 )
                    dword_526B98 = dword_526B90;
                  else
                    dword_526B94 = dword_526B90 + 1;
                }
                if ( this->field_0 > (unsigned int)dword_526B90 )
                  memmove(
                    (void *)(this->field_0 - dword_526B90),
                    (int)Src,
                    (char *)Src + 9,
                    Src,
                    9 * (this->field_0 - dword_526B90));
                ++thisa->field_0;
                if ( a5 <= giCurTempMobility || a11 )
                {
                  *((_BYTE *)Src + 4) ^= (*((_BYTE *)Src + 4) ^ 8 * a11) & 8;
                  *((_BYTE *)Src + 7) = a12;
                  v19 = a4;
                  *((_BYTE *)Src + 8) = a13;
                }
                else
                {
                  *((_BYTE *)Src + 4) |= 8u;
                  v19 = a4;
                  *((_BYTE *)Src + 7) = a2 - normalDirTable[4 * a4];
                  *((_BYTE *)Src + 8) = a3 - byte_4F1DC1[4 * a4];
                }
                *(_BYTE *)Src = a2;
                *((_BYTE *)Src + 1) = a3;
                *((_BYTE *)Src + 4) = 16 * v19 ^ (16 * v19 ^ *((_BYTE *)Src + 4)) & 0xF;
                *((_WORD *)Src + 1) = a5;
                *((_BYTE *)Src + 4) ^= (*((_BYTE *)Src + 4) ^ 2 * a7) & 2;
                *((_BYTE *)Src + 4) ^= (*((_BYTE *)Src + 4) ^ 4 * a8) & 4;
                *((_BYTE *)Src + 5) = a9;
                *((_BYTE *)Src + 6) = a10;
                *((_BYTE *)Src + 4) |= 1u;
                v20 = Src;
                v21 = dword_526B78;
                v13 = *(_DWORD *)Src;
                *(_DWORD *)dword_526B78 = *(_DWORD *)Src;
                *(_DWORD *)(v21 + 4) = *((_DWORD *)v20 + 1);
                *(_BYTE *)(v21 + 8) = *((_BYTE *)v20 + 8);
              }
            }
          }
        }
      }
    }
  }
  return v13;
}