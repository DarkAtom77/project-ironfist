{
  heroWindowManager *thisa; // esi@1
  heroWindow *v3; // eax@3
  heroWindow *prev; // eax@6
  heroWindow *v5; // eax@10
  heroWindow *v6; // eax@14

  thisa = this;
  if ( window )
  {
    heroWindow::Close(window);
    if ( thisa->firstWindow == window )
    {
      v3 = window->nextWindow;
      thisa->firstWindow = v3;
      if ( v3 )
        v3->prevWindow = 0;
      else
        thisa->lastWindow = 0;
    }
    else
    {
      prev = window->prevWindow;
      if ( thisa->lastWindow == window )
      {
        thisa->lastWindow = prev;
        prev->nextWindow = 0;
      }
      else
      {
        if ( prev )
          prev->nextWindow = window->nextWindow;
        v5 = window->nextWindow;
        if ( v5 )
          v5->prevWindow = window->prevWindow;
      }
    }
    if ( thisa->nextTopmostWindow == window )
      thisa->nextTopmostWindow = 0;
    v6 = thisa->nextTopmostWindow;
    if ( v6 )
      thisa->topmostWindow = v6;
    else
      thisa->topmostWindow = thisa->lastWindow;
  }
}