<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p><span style="font-size: 18px;">有些需求需要我们不断的输入数据很庞大，如果我们安装常规方法不断地在终端输入值很麻烦(前提是输入的数据是固定的，并不会随程序的运行而改变)，这个时候我们就可以调用freopen函数来解决这个麻烦。</span></p>
<p><span style="font-size: 18px;">freopen一般都是将stdin和stdout重定向。</span></p>
<p>&nbsp;</p>
<p><span style="font-size: 14pt;">FILE&nbsp;*&nbsp;freopen&nbsp;(&nbsp;const&nbsp;char&nbsp;*&nbsp;filename,&nbsp;const&nbsp;char&nbsp;*&nbsp;mode,&nbsp;FILE&nbsp;*&nbsp;stream&nbsp;)</span></p>
<p class="p0"><span style="font-size: 14pt;">filename:&nbsp;<span style="font-family: 宋体;">要打开的文件名。</span></span></p>
<p class="p0"><span style="font-size: 14pt;">mode:&nbsp;<span style="font-family: 宋体;">文件打开的模式，和</span><span style="font-family: 'Courier New';">fopen</span><span style="font-family: 宋体;">中的模式</span><span style="font-family: 宋体;">相同。</span></span></p>
<p class="p0"><span style="font-size: 14pt;">stream:&nbsp;<span style="font-family: 宋体;">文件指针，通常使用标准流文件</span><span style="font-family: 'Courier New';">(stdin/stdout/stderr)。</span></span></p>
<p class="p0"><span style="font-size: 14pt;">返回值：成功，则返回一个文件<span style="font-family: 宋体;">指针；失败，返回</span><span style="font-family: 'Courier New';">NULL</span><span style="font-family: 宋体;">（一般不会使用它的返回值，但是建议判断它的结果，养成良好的习惯）。&nbsp;</span></span></p>
<p>&nbsp;</p>
<p><span style="font-size: 18px;">例子：每次提供20个整数，分别计算出它们各自乘以2的积。</span></p>
<p><span style="font-size: 18px;">　　1.创建文件"input.txt"和"output.txt"对应stdin和stdout。</span></p>
<p><span style="font-size: 18px;">　　</span></p>
<p><span style="font-size: 18px;">　　2.编写代码"test.cpp"：</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> #include &lt;stdio.h&gt;
<span style="color: #008080;"> 2</span> #include &lt;iostream&gt;
<span style="color: #008080;"> 3</span> 
<span style="color: #008080;"> 4</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;"> 5</span> 
<span style="color: #008080;"> 6</span> <span style="color: #0000ff;">int</span><span style="color: #000000;"> main()
</span><span style="color: #008080;"> 7</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 8</span>     <span style="color: #0000ff;">int</span> num = <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 9</span>     <span style="color: #0000ff;">int</span> sum = <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span>     <span style="color: #0000ff;">if</span>(NULL == freopen(<span style="color: #800000;">"</span><span style="color: #800000;">input.txt</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">r</span><span style="color: #800000;">"</span><span style="color: #000000;">,stdin))
</span><span style="color: #008080;">12</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">13</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">open input.txt failed!\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">14</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">15</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">16</span>     <span style="color: #0000ff;">if</span>(NULL == freopen(<span style="color: #800000;">"</span><span style="color: #800000;">output.txt</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">w</span><span style="color: #800000;">"</span><span style="color: #000000;">,stdout))
</span><span style="color: #008080;">17</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">18</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">open output.txt failed\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">19</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">2</span><span style="color: #000000;">;
</span><span style="color: #008080;">20</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">21</span> 
<span style="color: #008080;">22</span>     <span style="color: #0000ff;">while</span>(scanf(<span style="color: #800000;">"</span><span style="color: #800000;">%d</span><span style="color: #800000;">"</span>,&amp;num) !=<span style="color: #000000;"> EOF)
</span><span style="color: #008080;">23</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">24</span>         sum = num * <span style="color: #800080;">2</span><span style="color: #000000;">;
</span><span style="color: #008080;">25</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">%d * 2 = %d\n</span><span style="color: #800000;">"</span><span style="color: #000000;">,num,sum);
</span><span style="color: #008080;">26</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">27</span> 
<span style="color: #008080;">28</span> <span style="color: #000000;">    fclose(stdin);
</span><span style="color: #008080;">29</span> <span style="color: #000000;">    fclose(stdout);
</span><span style="color: #008080;">30</span> 
<span style="color: #008080;">31</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">32</span> }</pre>
</div>
<p>　　</p>
<p><span style="font-size: 18px;">　　3.往"input.txt"文件内每行添加一个整数：</span></p>
<p><span style="font-size: 18px;"><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180329150537706-254864018.png" alt="" width="416" height="391" /></span></p>
<p><span style="font-size: 18px;">　　4.g++ test.cpp　　./a.out</span></p>
<p><span style="font-size: 18px;"><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180329150607113-1405924037.png" alt="" /></span></p>
<p>&nbsp;</p>
<p><span style="font-size: 18px;">这个例子简单，但主要是说明一下什么样需求可能会用到freopen函数。</span></p>