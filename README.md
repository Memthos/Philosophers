*This project has been created as part of the 42 curriculum by mperrine.*

## Description
`Philosophers` is a program that simulates the classic Dining Philosophers Problem. The program creates multiple philosopher threads that must share forks to eat while avoiding deadlock and starvation.

It addresses the following synchronization challenges:
- Each philosopher needs two forks to eat
- Philosophers alternate between eating, sleeping, and thinking
- Must prevent deadlock (all philosophers waiting indefinitely)
- Must prevent starvation (philosophers dying from not eating in time)

## Instructions
A `Makefile` is provided to compile the project.

**Build**
```bash
make
```

**Clean**
```bash
make clean
make fclean
```

**Rebuild**
```bash
make re
```

## Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers (and forks) at the table
- `time_to_die`: Time in milliseconds - philosopher dies if they don't start eating within this time since their last meal
- `time_to_eat`: Time in milliseconds - how long it takes a philosopher to eat
- `time_to_sleep`: Time in milliseconds - how long a philosopher sleeps after eating
- `[number_of_times_each_philosopher_must_eat]`: Optional argument - simulation stops when all philosophers have eaten at least this many times

**Output format:**
```
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
```
Replace *timestamp_in_ms* with the current timestamp in milliseconds
and *X* with the philosopher number.

Example:
```bash
./philo 5 800 200 200
# 5 philosophers, die after 800ms without eating, eat for 200ms, sleep for 200ms
```

```bash
./philo 5 800 200 200 7
# Same as above, but stops when each philosopher has eaten 7 times
```

## Resources

The problem is explained in the following article : [Philosophers 42 Guide— “The Dining Philosophers Problem”](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

This project was developed without the use of any AI tools.
