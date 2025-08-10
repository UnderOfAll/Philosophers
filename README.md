
# Philosophers

Project developed as part of the 42 Lisboa curriculum.

## 🧠 Objective

Solve the classical "Dining Philosophers" problem using concurrent programming (threads and mutexes), ensuring there are no deadlocks or race conditions.

## 🧩 Description

Five philosophers sit at a table. Each thinks, and eventually tries to eat. To eat, a philosopher needs two forks (mutexes), one on the left and one on the right. The challenge is to avoid issues like deadlocks and starvation while maintaining efficient behavior.

## 🔧 Features

- Creation of multiple threads (one per philosopher)
- table protection using mutexes (forks)
- Waiting logic and timing checks to avoid starvation
- Logging with timestamps and philosopher IDs
- Death detection and clean simulation termination

## 🛠️ How to Compile

```bash
make
```

## ▶️ How to Use

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Example:

```bash
./philo 5 800 200 200
```

## 📚 What I Learned

- Thread management with pthreads
- Proper use of mutexes to protect critical sections
- Logic to avoid deadlocks and starvation
- Thread synchronization and stop condition detection
- Time control with `usleep` and `gettimeofday`

## 🧑‍💻 Author

[Kayki Rocha](https://github.com/UnderOfAll) – 42 Lisboa Student
