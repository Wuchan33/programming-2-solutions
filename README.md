# Programming 2 — solutions

Solutions to assignments from the Programming 2 course. Each assignment is a separate file
or directory. Unlike the first course, these are not standalone programs — most contain no
`main()` and are submitted to an automated judge that supplies its own test harness. The
focus moves from procedural basics to classes, operator overloading, inheritance and manual
memory management.

## Assignments

- **[napisy.cpp](napisy.cpp)** — text processing on `std::string`: extracting words,
  normalizing whitespace and punctuation, and a small template engine driven by tags such as
  `{p:n:c}` and `{W:n:m}`.

- **[operacje-zbiorowe.cpp](operacje-zbiorowe.cpp)** — a set over the universe 0–31 packed
  into a single `int`, one bit per element and read from 5-bit binary strings. The whole set
  algebra and ordering is built from bit operations, with recursion in place of loops.

- **[rozwijana-tablica.cpp](rozwijana-tablica.cpp)** — an unrolled linked list, where each
  node holds an array of elements instead of a single value. Supports insertion, removal,
  cursor navigation over (node, index) pairs, compaction and reversal.

- **[wielomiany.cpp](wielomiany.cpp)** — a polynomial class over integer coefficients built
  almost entirely from overloaded operators: arithmetic, shifts, comparisons and stream I/O.
  Every result is normalized by dropping trailing zeros and dividing by the GCD.

- **[igrzyska.cpp](igrzyska.cpp)** — a gladiator combat simulation resting on an abstract
  base class: a human, a beast, a berserker inheriting from both through virtual (diamond)
  inheritance, and a squad that spreads incoming damage across its members.

- **[podprogramy/](podprogramy/)** — arbitrary-precision signed arithmetic on decimal
  strings, computed recursively. Addition, multiplication and a dispatcher taking either as
  a function pointer, each exposed through overloads returning by value, pointer or
  reference.

- **[owocowy-ogrod/](owocowy-ogrod/)** — a multi-module project modelling a four-level
  hierarchy (garden → tree → branch → fruit). Trees and branches grow, fade and can be
  cloned or pruned, with aggregate counters propagating up the hierarchy on every change.
