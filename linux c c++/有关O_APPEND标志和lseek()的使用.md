<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>O_APPEND表示以每次写操作都写入文件的末尾。<br />lseek()可以调整文件读写位置。</p>
<p>&nbsp;</p>
<p>&lt;&lt;Linux/UNIX系统编程手册&gt;&gt;上有这样一个问题：当在O_APPEND打开后，然后用 lseek移动文件开头，然后再用write写，这个时候，数据会显示在文件中的哪个位置？为什么？</p>
<p>先上代码：</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> #include &lt;unistd.h&gt;
<span style="color: #008080;"> 2</span> #include &lt;<span style="color: #0000ff;">string</span>.h&gt;
<span style="color: #008080;"> 3</span> #include &lt;fcntl.h&gt;
<span style="color: #008080;"> 4</span> #include &lt;stdio.h&gt;
<span style="color: #008080;"> 5</span> 
<span style="color: #008080;"> 6</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">void</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 7</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 8</span>     <span style="color: #0000ff;">int</span> fd = open(<span style="color: #800000;">"</span><span style="color: #800000;">test_open.txt</span><span style="color: #800000;">"</span>,O_RDWR |<span style="color: #000000;"> O_APPEND);
</span><span style="color: #008080;"> 9</span>     <span style="color: #0000ff;">if</span>(fd &lt; <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">10</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">11</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">open</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">12</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">13</span> 
<span style="color: #008080;">14</span>     <span style="color: #0000ff;">int</span> pos = lseek(fd,<span style="color: #800080;">0</span><span style="color: #000000;">,SEEK_SET);
</span><span style="color: #008080;">15</span>     <span style="color: #0000ff;">if</span>(pos != <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">16</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">17</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">lseek error\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">18</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">19</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">20</span> 
<span style="color: #008080;">21</span>     <span style="color: #0000ff;">int</span> size =write(fd,<span style="color: #800000;">"</span><span style="color: #800000;">world</span><span style="color: #800000;">"</span>,strlen(<span style="color: #800000;">"</span><span style="color: #800000;">world</span><span style="color: #800000;">"</span><span style="color: #000000;">));
</span><span style="color: #008080;">22</span>     <span style="color: #0000ff;">if</span>(size != <span style="color: #800080;">5</span><span style="color: #000000;">)
</span><span style="color: #008080;">23</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">24</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">write error\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">25</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">26</span> 
<span style="color: #008080;">27</span> <span style="color: #000000;">    close(fd);
</span><span style="color: #008080;">28</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">29</span> }</pre>
</div>
<p>&nbsp;</p>
<p>test_open.txt的内容随意，编译运行程序会发现数据显示在了文件最后，这个原因在APUE的3.8章节提到了：<br />　　<strong><span style="color: #ff0000;">对于普通文件，写操作从文件的当前偏移量处开始。如果在打开该文件时，指定了O_APPEND选项，则在每次写操作之前，将文件偏移量设置在文件的当前结尾处。在一次成功写入之后，该文件偏移量增加实际写的字节数。</span></strong></p>
<p><strong>　　</strong>其实就是在说O_APPEND会将lseek()的作用抵消掉。</p>