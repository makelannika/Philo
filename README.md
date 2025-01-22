## Philosophers
Classic concurrency problem used to demonstrate challenges like resource allocation and deadlock prevention in multi-threaded programming.

This project simulates philosophers sitting at a round table, alternating between eating, sleeping and thinking while sharing forks to eat spaghetti.
There are as many forks as there are philosophers. To be able to eat, a philosopher needs to grab two forks, one on their left and one on their right.
When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.

The philosophers don't communicate with each other or know if another philosopher is about to die. The philosophers should avoid dying.

The simulation ends when a philosopher dies of starvation, or optionally, when all philosophers have eaten a specified number of times.


This program takes the following arguments:
  1. **`number_of_philosophers`**: Number of philosophers (and forks) at the table.
  2. **`time_to_die`** (in ms): Time a philosopher can go without eating before dying.
  3. **`time_to_eat`** (in ms): Time it takes a philosopher to eat (holding two forks).
  4. **`time_to_sleep`** (in ms): Time a philosopher spends sleeping.
  5. **`number_of_times_each_philosopher_must_eat`** (optional): If provided, the simulation ends when all philosophers have eaten this many times.

Example:
```bash
./philo 5 800 200 200 7

