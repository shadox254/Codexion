*This project has been created as part of the 42 curriculum by rruiz.*

## 📄 Description

Codexion is a concurrency project inspired by the Dining Philosophers problem, reimagined as a coding workflow where each coder must acquire two shared dongles to compile, then debug and refactor in a continuous cycle. \
Each coder runs in its own thread, dongles are protected with mutexes, and a dedicated monitor thread detects burnouts and enforces a clean simulation stop. \
The program implements two scheduling policies for resource allocation (FIFO and EDF) and ends when either a coder burns out or all coders reach the required number of compilations.

## 🛠️ Instructions

1. Build the project

	make

2. Run the simulation

	./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler


3. Scheduler values

	scheduler must be fifo or edf

4. Example

	./codexion 5 800 200 200 150 6 50 edf

5. Clean build files

	make clean
	make fclean
	make re

## Arguments
| Argument | Description |
| --- | --- |
| number_of_coders | Total number of coder threads (and dongles). |
| time_to_burnout | Maximum time in ms a coder can stay without starting a compile before burning out. |
| time_to_compile | Time in ms spent compiling while holding two dongles. |
| time_to_debug | Time in ms spent debugging. |
| time_to_refactor | Time in ms spent refactoring. |
| number_of_compiles_required | Completion quota per coder (simulation stops when all coders reach it). |
| dongle_cooldown | Time in ms during which a dongle stays unavailable after being released. |
| scheduler | Resource allocation policy, must be fifo or edf. |

## 📜 Rules
- The program must not crash unexpectedly.
- No memory leaks are allowed: all heap allocations must be freed.
- Each coder is an independent thread.
- Each dongle is protected by a mutex and cannot be used by two coders at the same time.
- A coder must hold two dongles to compile.
- The action cycle is strict: compile -> debug -> refactor -> repeat.
- A monitor thread must detect burnouts and stop the simulation.
- Logs must be synchronized to prevent interleaved output.
- The simulation ends when one coder burns out, or when all coders reach the required number of compilations.
- Supported schedulers are fifo and edf.

## 🧱 Directory Structure
```
.
├── Makefile					# Build targets: all, clean, fclean, re
├── README.md					# Project documentation
└── coders/						# [Main source code]
	├── main.c						# Program entry point
	├── codexion.c					# Core simulation bootstrap and high-level flow
	├── include/
	│   └── codexion.h					# Shared structs, constants, and function prototypes
	├── engine/						# [Runtime engine (actions, threads, synchronization, monitoring)]
	│   ├── action.c					# Coder actions (compile, debug, refactor, etc.)
	│   ├── monitoring.c				# Burnout/completion checks and global stop conditions
	│   ├── mutex.c						# Mutex initialization and lock/unlock helpers
	│   └── thread.c					# Thread creation, launch, and join routines
	├── init/						# [Data and simulation initialization]
	│   ├── data.c						# Runtime data structures setup
	│   └── initialization.c			# Full simulation initialization pipeline
	├── parsing/					# [CLI parsing and rules validation]
	│   ├── args_verification.c			# Argument count/format validation
	│   └── rules_management.c			# Constraint checks and parsed rules handling
	├── schedulers/					# [Scheduling strategies]
	│   ├── edf.c						# Earliest Deadline First scheduler logic
	│   └── fifo.c						# First In, First Out scheduler logic
	└── utils/						# [Shared helper functions]
		├── debug.c						# Debug output utilities
		├── edf_utils.c					# EDF-specific helper functions
		├── error.c						# Error handling and message helpers
		├── fifo_utils.c				# FIFO-specific helper functions
		├── heap_utils.c				# Heap and priority queue helpers
		├── time.c						# Time measurement and sleep helpers
		└── utils.c						# Generic utility helpers
```

## 🚧 Blocking Cases Handled

- Deadlock prevention: Dongle allocation is coordinated through the selected scheduler (FIFO or EDF), reducing circular wait scenarios when multiple coders request resources.
- Starvation prevention: In EDF mode, coders with the shortest remaining time before burnout are prioritized to keep the system fair and prevent indefinite waiting.
- Dongle cooldown handling: After being released, each dongle is temporarily unavailable for `dongle_cooldown` milliseconds before it can be acquired again.
- Burnout monitoring: A dedicated monitor thread checks coder deadlines continuously and stops the simulation immediately when a burnout is detected.
- Safe termination: The simulation exits cleanly when one coder burns out or when all coders reach `number_of_compiles_required`.

## 🔒 Thread Synchronization Mechanisms

- Thread model:
Each coder runs in its own pthread, plus one dedicated monitor thread.

- Resource protection:
Each dongle owns a mutex lock (`pthread_mutex_t`) to guarantee exclusive access.

- Scheduler coordination:
Condition variables (`pthread_cond_t`) are used to block and wake waiting coders when dongles become available or priority changes.

- Per-coder state safety:
Each coder has a dedicated `data_lock` mutex to protect shared fields such as `last_compile`, `last_compile_start`, and completion state.

- Global simulation state:
A global mutex protects the simulation flag (`is_simu`) so start/stop decisions are consistent across threads.

- Output consistency:
All logs are guarded by `print_lock` to prevent interleaved or corrupted output lines.

- Wake-up on termination:
When the monitor stops the simulation, it broadcasts on dongle condition variables to unblock waiting threads and allow a clean shutdown.

## 📚 Resources

- Threads: https://www.geeksforgeeks.org/c/thread-functions-in-c-c/
- Threads and Mutex: https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
- Dining Philosophers: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- A friend who helped me: https://github.com/Overtekk/A_Maze_ing
- AI Usage: AI was used to review the code structure, identify potential concurrency issues, and format this README.