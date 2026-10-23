# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most.

## Week 10 (Lab 5)

### Part A: basics with `buggy_rooms.cpp`

Build and run:

```
cmake -S . -B build
cmake --build build --target buggy_rooms
./build/buggy_rooms
```

Record:

- The backtrace (`bt`) after the crash:
- The function and line number where your own code crashed (use `frame N` to move to it):
- The value of the pointer that caused the crash (`print`):
- How you stepped through the program (`break main`, `run`, `next`, `step`): list the commands and what each showed:
- The fix, and how you checked it:

### Part B: memory with `deck_bugs.cpp`

Build with AddressSanitizer and run each bug on its own (`./deck_bugs 1`, `2`, `3`).

For each bug, write one or two sentences: what kind of error AddressSanitizer reported, where the memory was allocated, and where it was freed.

| Bug | Report kind | Allocated at | Freed at | Cause in one sentence |
| --- | --- | --- | --- | --- |
| 1 | |Memory leak| Card *hand = new Card[52]; in deal_a_hand()| Not freed| The dynamically allocated array was never deleted before the function returned.|
| 2 |Double free caused by a shallow copy| cards_{new Card[52]} in RawDeck::RawDeck()| delete[] cards_ in RawDeck::~RawDeck()| The compiler-generated copy constructor copied the pointer, so two RawDeck objects tried to delete the same array.|
| 3 |Double free| Card *table = new Card[5]; in clear_a_table()| delete[] table; in clear_a_table()| The same pointer was deleted twice.|

Confirm one bug in GDB. Use at least two of `watch`, `finish`, and `x`. Paste the session and explain what each command showed:

Fixes for all three bugs (describe each change): 

Bug 1 (Memory Leak): I added delete[] hand; at the end of deal_a_hand(). This releases the dynamically allocated array and prevents the memory leak.

Bug 2 (Shallow Copy): I added a deep-copy constructor to RawDeck. Instead of copying the cards_ pointer, the copy constructor allocates a new array and copies each Card, so each RawDeck owns its own memory.

Bug 3 (Double Delete): I removed the second delete[] table; statement from clear_a_table(). This prevents the same pointer from being freed twice.
