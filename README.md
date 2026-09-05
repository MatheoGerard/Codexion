*This project has been created as part of the 42 curriculum by mgerard.*

# Codexion

## Description

Codexion is a multithreaded scheduling simulation, inspired by the classic **Dining
Philosophers** problem, reworked around a team of *coders* who need to compile,
debug and refactor code before "burning out".

Each coder is represented by its own thread and cycles through three states:
**compiling**, **debugging** and **refactoring**. To compile, a coder needs to
acquire **two dongles** (shared, limited resources) — one from its left neighbor
and one from its right neighbor, arranged in a circle. A coder that fails to
compile before its `time_to_burnout` deadline elapses is considered to have
burnt out, and the simulation ends.

The goal of the project is to correctly synchronize a large number of
concurrent threads competing for a small number of shared resources, while:
- avoiding **deadlocks**,
- avoiding **starvation**,
- respecting timing constraints (burnout, cooldown) with millisecond precision,
- supporting several **scheduling policies** to decide who gets access to a
  dongle next: **FIFO**, **LIFO** and **EDF** (Earliest Deadline First).

## Instructions

### Compilation

```bash
make        # builds the codexion binary
make clean  # removes object files
make fclean # removes object files and the binary
make re     # rebuilds from scratch
```

### Usage

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> \
           <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

| Argument                     | Description                                                        |
|-------------------------------|----------------------------------------------------------------------|
| `number_of_coders`             | Number of coder threads in the simulation                          |
| `time_to_burnout`               | Deadline (ms) after which a coder burns out without compiling      |
| `time_to_compile`                | Time (ms) a coder spends compiling once it holds both dongles      |
| `time_to_debug`                   | Time (ms) a coder spends debugging                                 |
| `time_to_refactor`                 | Time (ms) a coder spends refactoring                                |
| `number_of_compiles_required`       | Number of successful compiles before a coder "graduates"          |
| `dongle_cooldown`                    | Time (ms) a dongle stays unavailable after being released         |
| `scheduler`                            | Scheduling policy used for dongle access: `fifo` or `edf` |

Example:
```bash
./codexion 5 800 200 200 200 3 100 edf
```

## Blocking cases handled

- **Deadlock prevention (Coffman's conditions):** the *circular wait* condition
  is broken by having coders pick up their two dongles in an asymmetric order.
  Coders with an even index acquire their left dongle before their right one,
  while coders with an odd index do the opposite. This prevents the classic
  scenario where every coder holds one dongle and waits forever for the next
  one.
- **Starvation prevention:** access to contested dongles is arbitrated through
  a priority queue (min-heap) rather than raw lock contention. Every waiting
  coder is assigned a key (`compute_key`) matching the active scheduler
  (arrival time for FIFO, negated arrival time for LIFO, deadline for EDF), so
  every coder is guaranteed to eventually reach the head of the queue instead
  of being repeatedly overtaken.
- **Cooldown handling:** once a coder releases a dongle, that dongle is marked
  unavailable until `dongle_cooldown` milliseconds have passed
  (`release_dongles` sets `available = now + dongle_cooldown`). A coder that
  reaches the front of the queue still has to wait for this cooldown to expire
  before actually taking the dongle.
- **Precise burnout detection:** all timing is computed from a single shared
  reference timestamp (`set_start_time`, captured once at parsing time) rather
  than from per-thread clocks, and time differences are computed in
  milliseconds via `gettimeofday`. This avoids drift between threads and keeps
  deadline comparisons consistent across the whole simulation.
- **Log serialization:** all status messages (`print_status`) are written
  through a dedicated mutex so that concurrent coder threads cannot interleave
  their output mid-line, keeping the simulation log readable and consistent.

## Thread synchronization mechanisms

Codexion relies exclusively on `pthread_mutex_t` for synchronization, combined
with short, bounded polling loops (`usleep`) rather than blocking indefinitely,
so that no thread can deadlock while waiting on a resource.

- **`mutex_heap`** protects every access to the scheduling heap (insertion,
  extraction, peeking at the head). Any read or mutation of `dongle->heap` is
  wrapped in `pthread_mutex_lock`/`unlock` (see `protected_heap_insert`,
  `protected_extract_heap`), so the heap can be safely shared between all
  coder threads racing to enqueue or check their turn.
- **`mutex_time`** protects the `available` timestamp of each dongle. Because
  one thread can release a dongle (writing `available`) while another is
  simultaneously checking it (reading it through `get_available_time`), this
  mutex prevents a torn or stale read of that shared value.
- **`mutex`** (one per dongle) provides mutual exclusion over the dongle's
  actual usage: a coder only proceeds past `wait_for_dongle_available` once it
  holds this lock, guaranteeing that a single dongle is never used by two
  coders at the same time. It stays locked while the coder compiles, and is
  only released once both dongles are handed back.

**Race conditions prevented:** two coders can never see the same dongle as
"free" at the same moment and both grab it, because the availability check and
the acquisition of `mutex` happen atomically under lock. Likewise, two coders
can never corrupt the scheduling heap by inserting/extracting at the same
time, since every heap operation is funneled through `mutex_heap`.

**Thread-safe communication between coders and the monitor:** rather than
sharing raw state directly, coders communicate intent through the heap (by
inserting their key and waiting to become the head) and through the dongle's
`available` timestamp (read/written only under `mutex_time`). This gives the
monitor thread a consistent, lock-protected view of who is waiting, who is
active, and which resources are currently on cooldown, without needing direct
access to any coder's private state.

## Resources

- [W3Schools – POSIX threads / concurrency concepts](https://www.w3schools.com/) — used to build a general understanding of thread creation, mutexes and race conditions before implementing the synchronization logic.
- `man pthread_mutex_lock`, `man pthread_create`, `man gettimeofday` — reference documentation for the POSIX APIs used throughout the project.
- Wikipedia — [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and [Coffman conditions](https://en.wikipedia.org/wiki/Coffman_conditions) — background on the classic concurrency problem this project is modeled after, and on the four conditions required for a deadlock to occur.
- Wikipedia — [Earliest deadline first scheduling](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling) — background on the EDF scheduling policy implemented here.
- **AI usage:** Claude (Anthropic) was used as a code-review during development.