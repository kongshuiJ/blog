<p><span style="font-size: 14px;">在程序调试过程中程序崩溃的情况时有发生，把出问题时的调用栈信息打印出来是一种不错的解决办法。</span></p>
<p><span style="font-size: 14px;">当然还有一些其他方法：https://www.cnblogs.com/jiangyibo/p/8653720.html</span></p>
<p><span style="font-size: 14px;">&nbsp;</span></p>
<p><span style="font-size: 14px;">首先，介绍三个函数：</span></p>
<p><span style="font-size: 14px;">　　<strong>1.int backtrace(void **buffer,int size)；</strong></span></p>
<p><span style="font-size: 14px;">　　　　该函数用于获取当前线程的调用堆栈信息,信息被存放在buffer中,它是一个指针数组。</span></p>
<p><span style="font-size: 14px;">　　　　参数size表示buffer中可以存放void*元素的个数，函数返回值是实际获取到的void*元素的个数。</span></p>
<p><span style="font-size: 14px;">&nbsp;</span></p>
<p><span style="font-size: 14px;">　　<strong>2.char **backtrace_symbols(void *const *buffer, int size)；</strong></span></p>
<p><span style="font-size: 14px;">　　　　backtrace_symbols将backtrace函数获取的信息转化为一个字符串数组，参数buffer是从backtrace函数获取的指针数组,size是该数组中的元素个数(backtrace函数的返回值)。</span></p>
<p><span style="font-size: 14px;">　　　　函数返回值是一个指向字符串数组的指针,它的大小同buffer相同。</span></p>
<p><span style="font-size: 14px;">　　　　需要注意的是该函数返回的地址是通过malloc函数申请的空间,为了防止内存泄露，我们要手动调用free来释放这块内存。"free(函数返回的指针)"</span></p>
<p><span style="font-size: 14px;">　　</span></p>
<p><strong><span style="font-size: 14px;">　　<span style="color: #888888;">3.void backtrace_symbols_fd (void *const *buffer, int size, int fd)；</span></span></strong></p>
<p><span style="font-size: 14px;">　　　　该函数与backtrace_symbols 函数功能类似，不同的是，这个函数直接把结果输出到文件描述符为fd的文件中，且没有调用malloc，不需要手动释放空间。</span></p>
<p><span style="font-size: 14px;">&nbsp;</span></p>
<p><span style="font-size: 14px;">测试用例：</span></p>
<p><span style="font-size: 14px;">　　main.c</span></p>
<div class="cnblogs_code">
<pre><span style="font-size: 14px;"><span style="color: #008080;"> 1</span> #include &lt;stdio.h&gt;
<span style="color: #008080;"> 2</span> #include &lt;stdlib.h&gt;
<span style="color: #008080;"> 3</span> #include &lt;unistd.h&gt;
<span style="color: #008080;"> 4</span> #include &lt;signal.h&gt;
<span style="color: #008080;"> 5</span> #include &lt;execinfo.h&gt;
<span style="color: #008080;"> 6</span> 
<span style="color: #008080;"> 7</span> <span style="color: #0000ff;">#define</span> Size 128
<span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #0000ff;">void</span> fun(<span style="color: #0000ff;">void</span><span style="color: #000000;">)
</span><span style="color: #008080;">10</span> <span style="color: #000000;">{
</span><span style="color: #008080;">11</span>     <span style="color: #0000ff;">int</span> *piTest =<span style="color: #000000;"> NULL;
</span><span style="color: #008080;">12</span>     *piTest = <span style="color: #800080;">2</span><span style="color: #000000;">;
</span><span style="color: #008080;">13</span> <span style="color: #000000;">}
</span><span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">void</span> signalHandler(<span style="color: #0000ff;">int</span><span style="color: #000000;"> signalId)
</span><span style="color: #008080;">16</span> <span style="color: #000000;">{
</span><span style="color: #008080;">17</span>     <span style="color: #0000ff;">int</span> i = <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">18</span>     <span style="color: #0000ff;">int</span> iNum = <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">19</span>     <span style="color: #0000ff;">void</span> *pBuffer[Size] = {<span style="color: #800080;">0</span><span style="color: #000000;">};
</span><span style="color: #008080;">20</span>     <span style="color: #0000ff;">char</span> **pszDebugInfo =<span style="color: #000000;"> NULL;
</span><span style="color: #008080;">21</span> 
<span style="color: #008080;">22</span>     iNum =<span style="color: #000000;"> backtrace(pBuffer, Size);
</span><span style="color: #008080;">23</span>     pszDebugInfo =<span style="color: #000000;"> backtrace_symbols(pBuffer, iNum);
</span><span style="color: #008080;">24</span> 
<span style="color: #008080;">25</span>     <span style="color: #0000ff;">if</span> (pszDebugInfo ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">26</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">27</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">backtrace_symbols</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">28</span>         exit(EXIT_FAILURE);         <span style="color: #008000;">//</span><span style="color: #008000;"> 表示没有成功执行程序</span>
<span style="color: #008080;">29</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">30</span> 
<span style="color: #008080;">31</span>     <span style="color: #0000ff;">for</span> (i = <span style="color: #800080;">0</span>; i &lt; iNum; i++<span style="color: #000000;">)
</span><span style="color: #008080;">32</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">33</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;"> [%02d] %s\n</span><span style="color: #800000;">"</span><span style="color: #000000;">, i, pszDebugInfo[i]);
</span><span style="color: #008080;">34</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">35</span> 
<span style="color: #008080;">36</span>     <span style="color: #0000ff;">free</span><span style="color: #000000;">(pszDebugInfo);
</span><span style="color: #008080;">37</span> 
<span style="color: #008080;">38</span> <span style="color: #000000;">    signal(signalId, SIG_DFL);
</span><span style="color: #008080;">39</span> 
<span style="color: #008080;">40</span> <span style="color: #000000;">    raise(signalId);
</span><span style="color: #008080;">41</span> <span style="color: #000000;">}
</span><span style="color: #008080;">42</span> 
<span style="color: #008080;">43</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">44</span> <span style="color: #000000;">{
</span><span style="color: #008080;">45</span>     <span style="color: #008000;">//</span><span style="color: #008000;"> SIGSEGV是当一个进程执行了一个无效的内存引用,
</span><span style="color: #008080;">46</span>     <span style="color: #008000;">//</span><span style="color: #008000;"> 或发生段错误时发送给它的信号</span>
<span style="color: #008080;">47</span> <span style="color: #000000;">    signal(SIGSEGV, signalHandler);
</span><span style="color: #008080;">48</span> 
<span style="color: #008080;">49</span> <span style="color: #000000;">    fun();
</span><span style="color: #008080;">50</span> 
<span style="color: #008080;">51</span>     printf(<span style="color: #800000;">"</span><span style="color: #800000;">----\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">52</span> 
<span style="color: #008080;">53</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">54</span> }</span></pre>
</div>
<p><span style="font-size: 14px;">&nbsp;</span></p>
<p><span style="font-size: 14px;">&nbsp;</span></p>
<p><span style="font-size: 14px;"><strong>gcc -g -rdynamic main.c -o main</strong></span></p>
<p><span style="font-size: 14px;">　　-g　　　　　　"objdump"的参数"-l"，"-S"要求编译时使用了-g之类的调试编译选项。&nbsp;</span></p>
<p><span style="font-size: 14px;">　　-rdynamic　　该参数是链接选项，不是编译选项。这主要是对可执行程序(elf)而言的，而编译动态库时，即使没有rdynamic选项，默认也会将非静态函数放入动态符号表中（刻意隐藏的函数除外）。默认情况下，可执行程序（非动态库）文件内我们定义的非静态函数，是不放到动态符号表中的，链接时只有加上"-rdynamic"才能将所有非静态函数加到动态符号表中。</span></p>
<p><span style="font-size: 14px;"><strong>./main</strong></span></p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201808/1347181-20180820190745816-433134254.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="font-size: 14px;">objdump -S -l ./main &gt; info.txt</span></p>
<p><span style="font-size: 14px;">　　<strong>objdump命令</strong>是用查看目标文件或者可执行的目标文件的构成的gcc<span class="wp_keywordlink">工具。</span></span></p>
<pre><span style="font-size: 14px;"><strong>　　-l    --line-numbers </strong>
　　用文件名和行号标注相应的目标代码，仅仅和-d、-D或者-r一起使用使用-<span class="wp_keywordlink"><a title="ld命令" href="http://man.linuxde.net/ld" target="_blank">ld</a>和使用-d的区别不是很大，在源码级调试的时候有用，要求编译时使用了-g之类的调试编译选项。<br /><br /></span></span></pre>
<pre><span style="font-size: 14px;"><strong>　　-S    --source</strong> 
　　尽可能反汇编出源代码，尤其当编译的时候指定了-g这种调试参数时，效果比较明显。隐含了-d参数。 <br /><br />上图可以看到发生了段错误，从下往上可以看到错误大概是发生在"fun"函数，然后打开info.txt，查找有关地址"0a16"的行号:<br />　　<strong>vim info.txt</strong><br /><strong>　　命令模式：/0a16</strong><br /><img src="https://images2018.cnblogs.com/blog/1347181/201808/1347181-20180820192407790-1763391873.png" alt="" /></span></pre>
<p>　　可以看到"0a16"所在"main.c"的12行，而12号正好是"*piTemp = 2;"。</p>
<p>　　这里只举例了可执行文件，同理的动态库(记得加-g)也可以按照这个办法来查找错误，这里就不细说了。</p>