{
  hexcell *thisa; // [sp+Ch] [bp-10h]@1
  int i; // [sp+14h] [bp-8h]@2

  thisa = this;
  if ( this->numCorpses > 0 )
  {
    for ( i = 0; thisa->numCorpses - 1 > i; ++i )
    {
      if ( thisa->field_33[i] != gpCombatManager->creatures[thisa->corpseOwners[i]][thisa->corpseStackIndices[i]].facingRight )
        army::DrawToBuffer(
          &gpCombatManager->creatures[thisa->corpseOwners[i]][thisa->corpseStackIndices[i]],
          thisa->centerX,
          thisa->occupyingCreatureBottomY,
          0);
    }
  }
}