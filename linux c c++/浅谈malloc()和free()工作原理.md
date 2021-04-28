<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。&nbsp;</strong></span></p>
<p>&nbsp;</p>
<p>malloc()和free()是我经常需要用到的函数，一般情况下，C程序使用malloc()在堆上分配内存，free()释放内存，两者的参数和返回值就不在这叙述了，本文主要是简单的记录下malloc()和free()的工作原理。</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201804/1347181-20180410184649523-732576745.png" alt="" /></p>
<p>&nbsp;</p>
<p>malloc()返回内存块所采用的字节对齐方式，总是适宜于高效访问任何类型的C语言数据结构。在大多数硬件架构上，这实际意味着malloc是基于8字节或16字节边界来分配内存的。若无法分配内存，或许是因为已经抵达program break所能达到的地址上限，但一般分配内存失败的可能性很小。</p>
<p>一般情况下，free()并不降低program break的位置，而是将这块内存添加到空闲内存列表中，供后续的malloc()循环使用，原因有以下几点：</p>
<p>　　1.被释放的内存块通常会位于堆的中间，而非堆的顶部，因为降低program break是不可能的；</p>
<p>　　2.它最大限度地减少了程序必须执行的sbrk()调用次数，其实就是降低系统调用的开销；</p>
<p>　　3.多数情况下，降低program break的位置不会对那些分配大量内存的程序有多少帮助，因为它们通常倾向于持有已分配内存或是反复释放和重新分配内存，而非释放所有内存后再持续运行一段时间。</p>
<p>&nbsp;</p>
<p><span style="color: #ff0000;">malloc()工作原理：</span></p>
<p>　　它首先会扫描之前由free()所释放的空闲内存块列表，以求找到尺寸大于或等于要求的一块空闲内存，如果这一内存块的尺寸正好与要求想当，就把该内存块地址直接返回给调用者，如果是一块较大的内存，那么将对其进行分割，在将一块大小相当的内存返回给调用者的同时，把较小的那块空闲内存保留在空闲列表中。如果空闲内存列表中没有足够大的空闲内存块，那么malloc()会调用sbrk()以分配更多的内存。为减少对sbrk()的调用次数，malloc()并未只是严格按所需字节数来分配内存，而是以更大幅度(以虚拟内存页大小的数倍)来增加program break，并将超出部分置于空闲内存列表。</p>
<p>　　</p>
<p>　　malloc()分配内存块的时候，会额外分配几个字节来记录内存块的大小，该数值存放在内存块的起始处，malloc()实际返回给调用者的地址其实是该数值之后的内存块长度。</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201804/1347181-20180410190152253-2123210531.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000;">free()工作原理：</span></p>
<p>　　free()将内存块置于空闲链表中是根据该内存块所记录的内存块大小来实现的。</p>
<p>　　当将内存块置于空闲内存列表(双向链表)时，free()会使用内存块本身的空间来存放链表指针，将自身添加到列表中。</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201804/1347181-20180410190344037-1038171149.png" alt="" /></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>所以，实际上的堆是空闲内存和已分配在用内存的混合，如下图：</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201804/1347181-20180410190520763-2140653929.png" alt="" /></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>了解了两者的工作原理，<strong>我们在使用的时候一定要切记free()只能释放malloc()返回的指针，并且程序中有malloc()，就一定要有free()。</strong></p>
<p>&nbsp;</p>
<p><span style="font-size: 18px;"><strong>简单记录malloc调试工具mtrace:</strong></span></p>
<p>　　代码：</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> #include &lt;stdio.h&gt;
<span style="color: #008080;"> 2</span> #include &lt;stdlib.h&gt;
<span style="color: #008080;"> 3</span> #include &lt;mcheck.h&gt;
<span style="color: #008080;"> 4</span> 
<span style="color: #008080;"> 5</span> <span style="color: #0000ff;">int</span><span style="color: #000000;"> main()
</span><span style="color: #008080;"> 6</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 7</span>     setenv(<span style="color: #800000;">"</span><span style="color: #800000;">MALLOC_TRACE</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">output.txt</span><span style="color: #800000;">"</span>,<span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;"> 8</span> <span style="color: #000000;">    mtrace();
</span><span style="color: #008080;"> 9</span> 
<span style="color: #008080;">10</span>     <span style="color: #0000ff;">int</span> *p = (<span style="color: #0000ff;">int</span> *)<span style="color: #0000ff;">malloc</span>(<span style="color: #800080;">2</span> * <span style="color: #0000ff;">sizeof</span>(<span style="color: #0000ff;">int</span><span style="color: #000000;">));
</span><span style="color: #008080;">11</span> 
<span style="color: #008080;">12</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">13</span> }</pre>
</div>
<p>　　执行命令：</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201804/1347181-20180410192823203-719036115.png" alt="" /></p>
<p>&nbsp;</p>
<p>　　mtrace和addr2line配合起来还是不错滴。</p>
<p>　　addr2line 可看http://www.cnblogs.com/jiangyibo/p/8653720.html</p>
<p>　　mtrace调试动态库推荐http://blog.sina.com.cn/s/blog_590be5290102vtdb.html</p>