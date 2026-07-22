fork() creates a child process that is a copy of the parent, letting the server handle multiple requests concurrently instead of one at a time. Each child runs independently and exits with exit(0) once its task is done.

When a child terminates, it becomes a zombie until the parent reads its exit status. To prevent this, a SIGCHLD handler is registered using signal(). Whenever a child dies, the kernel sends SIGCHLD to the parent, which calls waitpid() with WNOHANG inside the handler. This reaps the child immediately without blocking the parent, so zombies never accumulate.

To handle unresponsive children, the parent tracks each child's PID and waits for a timeout period. After the timeout, it checks which children are still alive using kill(pid, 0) (a null signal used only to check existence) and sends SIGTERM to any child still running, forcing it to terminate. A final waitpid() call with WNOHANG cleans up any remaining exit statuses.

Together, fork() creates concurrency, the SIGCHLD handler with waitpid() prevents zombies by reaping children asynchronously, and kill() with SIGTERM enforces a timeout policy to stop child processes that hang, keeping the server responsive.