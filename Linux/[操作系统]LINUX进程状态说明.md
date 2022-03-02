## R(task_running) : 可执行状态

       只有在该状态的进程才可能在CPU上运行。而同一时刻可能有多个进程 处于可执行状态，这些进程的task_struct结构（进程控制块）被放入对应CPU的 可执行队列中（一个进程最多只能出现在一个CPU的可执行队列中）。进程调度器的任务就是从各个CPU的可执行队列中分别选择一个进程在该CPU上运行。

       很多操作系统教科书将正在CPU上执行的进程定义为RUNNING状态、而将可执行但是尚未被调度执行的进程定义为READY状态，这两种状态在linux下统一为 TASK_RUNNING状态。

## S(task_interruptible): 可中断的睡眠状态

       处于这个状态的进程因为等待某某事件的发生（比如等待socket连 接、等待信号量），而被挂起。这些进程的task_struct结构被放入对应事件的等待队列中。当这些事件发生时（由外部中断触发、或由其他进程触发），对应的等 待队列中的一个或多个进程将被唤醒。

       通过ps命令我们会看到，一般情况下，进程列表中的绝大多数进程都处于task_interruptible状态（除非机器的负载很高）。毕竟CPU就这么一两个，进程动辄几十上百个，如果不是绝大多数进程都在睡眠，CPU又怎么响应得过来。

## D(task_uninterruptible): 不可中断的睡眠状态

       与task_interruptible状态类似，进程处于睡眠状态，但是此刻进程是不可中断的。不可中断，指的并不是CPU不响应外部硬件的中断，而是指进程不响应异步信号。
       绝大多数情况下，进程处在睡眠状态时，总是应该能够响应异步信号的。但是uninterruptible sleep 状态的进程不接受外来的任何信号，因此无法用kill杀掉这些处于D状态的进程，无论是”kill”, “kill -9″还是”kill -15″，这种情况下，一个可选的方法就是reboot。

       处于uninterruptible sleep状态的进程通常是在等待IO，比如磁盘IO，网络IO，其他外设IO，如果进程正在等待的IO在较长的时间内都没有响应，那么就被ps看到了，同时也就意味着很有可能有IO出了问题，可能是外设本身出了故障，也可能是比如挂载的远程文件系统已经不可访问了.

       而task_uninterruptible状态存在的意义就在于，内核的某些处理流程是不能被打断的。如果响应异步信号，程序的执行流程中就会被插入一段用于处理异步信号的流程（这个插入的流程可能只存在于内核态，也可能延伸到用户态），于是原有的流程就被中断了。

       在进程对某些硬件进行操作时（比如进程调用read系统调用对某个设 备文件进行读操作，而read系统调用最终执行到对应设备驱动的代码，并与对应的物理设备进行交互），可能需要使用task_uninterruptible状态对进程进行保护，以避免进程与设备交互的过程被打断，造成设备陷入不可控的状态。这种情况下的task_uninterruptible状态总是非常短暂的，通过ps命 令基本上不可能捕捉到。

       我们通过vmstat 命令中procs下的b 可以来查看是否有处于uninterruptible 状态的进程。该命令只能显示数量。

       In computeroperating systems terminology, a sleeping process can either be interruptible(woken via signals) or uninterruptible (woken explicitly). An uninterruptible sleep state is a sleep state that cannothandle a signal (such as waiting for disk or network IO (input/output)).

       When the process is sleeping uninterruptibly, the signal willbe noticed when the process returns from the system call or trap.

       -- 这句是关键。 当处于uninterruptiblysleep 状态时，只有当进程从system 调用返回时，才通知signal。

       A process whichends up in “D” state for anymeasurable length of time is trapped in the midst of a system call (usually anI/O operation on a device — thus the initial in the psoutput).

       Such a process cannot be killed — it would risk leaving the kernel in an inconsistent state, leadingto a panic. In general you can consider this to be abug in the device driver that the process is accessing.

## T(task_stoppedor task_traced)：暂停状态或跟踪状态

       向进程发送一个sigstop信号，它就会因响应该信号而进入task_stopped状态（除非该进程本身处于task_uninterruptible状态而不响应信号）。（sigstop与sigkill信号一样，是非常强制的。不允许用户进程通过signal系列的系统调用重新设置对应的信号处理函数。）
       向进程发送一个sigcont信号，可以让其从task_stopped状态恢复到task_running状态。

       当进程正在被跟踪时，它处于task_traced这个特殊的状态。“正 在被跟踪”指的是进程暂停下来，等待跟踪它的进程对它进行操作。比如在gdb中对被跟踪的进程下一个断点，进程在断点处停下来的时候就处于task_traced状态。而在其他时候，被跟踪的进程还是处于前面提到的那些状态。     

       对于进程本身来说，task_stopped和task_traced状态很类似，都是表示进程暂停下来。
       而task_traced状态相当于在task_stopped之上多了一层保护，处于task_traced状态的进程不能响应sigcont信号而被唤醒。只能等到调试进程通过ptrace系统调用执行ptrace_cont、ptrace_detach等操作（通过ptrace系统调用的参数指定操作），或调试进程退出，被调试的进程才能恢复task_running状态。

## Z (task_dead -exit_zombie)：退出状态，进程成为僵尸进程

       在Linux进程的状态中，僵尸进程是非常特殊的一种，它是已经结束了的进程，但是没有从进程表中删除。太多了会导致进程表里面条目满了，进而导致系统崩溃，倒是不占用其他系统资源。     

       它已经放弃了几乎所有内存空间，没有任何可执行代码，也不能被调度，仅仅在 进程列表中保留一个位置，记载该进程的退出状态等信息供其他进程收集，除此之外，僵尸进程不再占有任何内存空间。    

       进 程在退出的过程中，处于TASK_DEAD状态。在这个退出过程中，进程占有的所有资源将被回收，除了task_struct结构（以及少数资源）以外。于是进程就只剩 下task_struct这么个空壳，故称为僵尸。

       之所以保留task_struct，是因为task_struct里面保存了进程的退出码、以及一些统计信息。而其父进程很可能会关心这些信息。比如在shell中，$?变量就保存了最后一个退出的前台进程的退出码，而这个退出码往往被作为if语句的判断条件。
       当然，内核也可以将这些信息保存在别的地方，而将task_struct结构释放掉，以节省一些空间。但是使用task_struct结构更为方便，因为在内核中已经建立了从pid到task_struct查找关系，还有进程间的父子关系。释放掉task_struct，则需要建立一些新的数据结构，以便让父进程找到它的子进程的退出信息。

       子进程在退出的过程中，内核会给其父进程发送一个信号，通知父进程来“收 尸”。父进程可以通过wait系列的系统调用（如wait4、waitid）来等待某个或某些子进程的退出，并获取它的退出信息。然后wait系列的系统调用会顺便将子进程的尸体（task_struct）也释放掉。

       这 个信号默认是SIGCHLD，但是在通过clone系统调用创建 子进程时，可以设置这个信号。

       如果他的父进程没安装SIGCHLD信号处理函数调用wait或waitpid()等待子进程结束，又没有显式忽略该信号，那么它就一直保持僵尸状态，子进程的尸体（task_struct）也就无法释放掉。

       如果这时父进程结束了，那么init进程自动会接手这个子进程，为它收尸，它还是能被清除的。但是如果如果父进程是一个循环，不会结束， 那么子进程就会一直保持僵尸状态，这就是为什么系统中有时会有很多的僵尸进程。

       当进程退出的时候，会将它的所有子进程都托管给别的进程（使之成为别的进程的子进程）。托管的进程可能是退出进程所在进程组的下一个进程（如果存在的话），或者是1号进程。所以每个进程、每时每刻都有父进程 存在。除非它是1号进程。1号进程，pid为1的进程，又称init进程。


linux系统启动后，第一个被创建的用户态进程就是init进程。它有两项使命：

       1. 执行系统初始化脚本，创建一系列的进程（它们都是init进程的子孙）；
       2. 在一个死循环中等待其子进程的退出事件，并调用waitid系统调用来完成“收尸”工作；

       init进程不会被暂停、也不会被杀死（这是由内核来保证的）。它在等待子进程退出的过程中处于task_interruptible状态，“收尸”过程中则处于task_running状态。

Unix/Linux 处理僵尸进程的方法：

       找出父进程号，然后kill 父进程，之后子进程（僵尸进程）会被托管到其他进程，如init进程，然后由init进程将子进程的尸体（task_struct）释放掉。

除了通过ps 的状态来查看Zombi进程，还可以用如下命令查看：

[oracle@rac1 ~]$ ps -ef|grep defun

oracle   13526 12825  0 16:48 pts/1    00:00:00 grepdefun

oracle   2833028275  0 May18?        00:00:00 [Xsession]<defunct>

僵尸进程解决办 法：

1. 改写父进程，在子进程死后要为它收尸。

       具体做法是接管SIGCHLD信号。子进程死后，会发送SIGCHLD信号给父进程，父进程收到此信号后，执行 waitpid()函数为子进程收尸。这是基于这样的原理：就算父进程没有调用wait，内核也会向它发送SIGCHLD消息，尽管对的默认处理是忽略，如果想响应这个消息，可以设置一个处理函数。

2. 把父进程杀掉。

       父进程死后，僵尸进程成为"孤儿进程"，过继给1号进程init，init始终会负责清理僵尸进程．它产生的所有僵尸进程也跟着消失。如：

       kill -9 `ps -ef |grep "Process Name" | awk '{ print $3 }'`
       其中，“ProcessName”为处于zombie状态的进程名。

3. 杀父进程不行的话，就尝试用skill -t TTY关闭相应终端，TTY是进程相应的tty号(终 端号)。但是，ps可能会查不到特定进程的tty号，这时就需要自己判断了。
4. 重启系统，这也是最常用到方法之一。

## X (task_dead -exit_dead)：退出状态，进程即将被销毁

       进程在退出过程中也可能不会保留它的task_struct。比如这个进程是多线程程序中被detach过的进 程。或者父进程通过设置sigchld信号的handler为sig_ign，显式的忽略了sigchld信号。（这是posix的规定，尽管子进程的退出信号可以被设置为sigchld以外的其他信号。）
       此时，进程将被置于exit_dead退出状态，这意味着接下来的代码立即就会将该进程彻底释放。所以exit_dead状态是非常短暂的，几乎不可能通过ps命 令捕捉到。
