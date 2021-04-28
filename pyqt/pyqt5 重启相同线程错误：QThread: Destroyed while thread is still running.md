<h2>背景：</h2>
<p>&nbsp; &nbsp; &nbsp; &nbsp; 把一个基于QObject的类的槽运行在另一个线程，我们可以用moveToThread的方法。</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;">1</span> 新建一个子线程类，编写槽函数和信号，MyClass *m_MyClass=<span style="color: #000000;">new MyClass()；
</span><span style="color: #008080;">2</span> 新建一个线程对象QThread *runThread=<span style="color: #000000;">new QThread();
</span><span style="color: #008080;">3</span> <span style="color: #000000;">使用connect连接当前类与子线程的信号槽，以便触发线程及接收线程执行结果；
</span><span style="color: #008080;">4</span> <span style="color: #000000;">使用m_MyClass.moveToThread(runThread)，将子线程类移到线程中执行；
</span><span style="color: #008080;">5</span> runThread-&gt;start()，开启线程。</pre>
</div>
<p>　　以下子线程名称统称为B线程，主线程统称为A线程；</p>
<p>&nbsp; &nbsp; &nbsp; &nbsp;B线程是在后台不断的检测PC连接的设备，当检测到合适的设备连接成功后，A线程进行逻辑处理，此时B线程函数内部会直接return，等到A线程处理完连接设备的数据后，会再次新起一个B线程。(这里是因为A线程处理一次数据时间比较长，B线程没必要一直运行。）</p>
<p>&nbsp; &nbsp; <span style="color: #ff6600;">&nbsp; 注：&nbsp; 此处之所以不用互斥量来加锁，直接让B线程阻塞是因为担心死锁，而且本身程序比较小，耗用内存和CPU什么的都非常小，重启一个B线程也不会有影响。</span></p>
<p>&nbsp;</p>
<h2>问题：</h2>
<p>&nbsp; &nbsp; &nbsp; 但是B线程函数内部会直接<span style="color: #ff0000;">return</span>并不代表线程结束(归根结底还是自己不了解如何调用)，所以直接再次调用runThread.start()会报错&nbsp; &nbsp;<span style="color: #ff0000;">QThread: Destroyed while thread is still running</span>。</p>
<p>&nbsp;</p>
<h2>解决方法：</h2>
<p>　　再次调用runThread.start()之前添加两行：</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;">1</span> <span style="color: #000000;">runThread.quit()
</span><span style="color: #008080;">2</span> runThread.wait()</pre>
</div>
<p>&nbsp;</p>