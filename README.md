# wim

> **W**hat **I**s **M**issing — a C library for data structures and allocators.

The C standard library is intentionally minimal. `wim` fills the gap with two cohesive modules, written in pure C, designed to work together.

---

## Modules

### `wim/ds` — Data Structures
Dynamic arrays, linked lists, hash maps, trees, queues, and more. Generic via void pointers and macros.

| Structure              | Status       | Notes |
|------------------------|--------------|-------|
| Dynamic Array          | Completed    |       |
| Single Linked List     | Completed    |       |
| Double Linked List     | Completed    |       |
| Circular Linked List   | Planned      |       |
| Queue                  | Planned      |       |

### `wim/alloc` — Allocators
Arena, pool, buddy, slab, free list, and other allocator strategies as drop-in building blocks.


| Allocator | Status   | Notes |
|-----------|----------|-------|
| Arena     | Planned  |       |
| Pool      | Planned  |       |
| Buddy     | Planned  |       |
| Slab      | Planned  |       |
| Free List | Planned  |       |

---

## Philosophy

- **One library, two concerns** — consistent API, naming, and error handling throughout.
- **Minimal dependencies** — core library depends only on libc; external dependencies may be used for testing.

---

## Status

Early design phase. Nothing is stable yet.

---

## License

[MIT](LICENSE)