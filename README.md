# Philosophers

A concurrent dining-philosophers simulation written in C as part of the 42 curriculum.

The project models philosophers sitting around a table. Each philosopher repeatedly thinks, takes forks, eats, and sleeps. The simulation must coordinate shared resources safely while detecting when a philosopher dies from starvation.

## Features

- POSIX threads with `pthread`
- Mutex-protected forks and shared state
- Death monitoring
- Precise timestamped status messages
- Argument validation
- Optional meal-count termination condition
- Race-condition-conscious synchronization

## Rules

Each philosopher follows this lifecycle:

1. Think
2. Take the left and right forks
3. Eat
4. Sleep
5. Repeat until the simulation ends

A philosopher dies when they do not start eating within `time_to_die` milliseconds after their last meal.

## Build

```bash
make
```

## Make commands

```bash
make        # Build the philo executable
make clean  # Remove object files
make fclean # Remove object files and the executable
make re     # Rebuild everything
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Maximum time, in milliseconds, between meals |
| `time_to_eat` | Eating duration in milliseconds |
| `time_to_sleep` | Sleeping duration in milliseconds |
| `number_of_times_each_philosopher_must_eat` | Optional meal count before ending the simulation |

Example:

```bash
./philo 5 800 200 200
```

With a meal limit:

```bash
./philo 5 800 200 200 7
```

## Output format

The program prints timestamped actions similar to:

```text
120 2 has taken a fork
121 2 is eating
321 2 is sleeping
```

## Implementation

- `main.c` — Program entry point
- `check_arguments.c` — Input validation
- `init_data.c` — Simulation and mutex initialization
- `start_sim.c` — Thread and monitor startup
- `philo_action.c` — Philosopher actions
- `cleanup.c` — Resource cleanup
- `libft.c`, `libft_utils.c` — Local utility functions
- `philo.h` — Shared data structures and declarations

## Requirements

- C compiler
- POSIX threads support
- `make`

The project is compiled with:

- `-Wall`
- `-Wextra`
- `-Werror`
- `-pthread`

## Author

**alperenocak**
