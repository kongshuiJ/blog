<p>为了能够快速找到发生段错误的地方，记录以下两种方法。</p>
<p><a id="homepage1_HomePageDays_DaysList_ctl00_DayList_TitleUrl_0" class="postTitle2" href="https://www.cnblogs.com/jiangyibo/p/9507555.html">objdump和backtrace的配合使用</a>&nbsp;：https://www.cnblogs.com/jiangyibo/p/9507555.html&nbsp;</p>
<p>&nbsp;</p>
<p><span style="font-size: 14pt;">代码：test.c</span></p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326203700566-499545967.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="font-size: 18pt;"><strong>一、命令addr2line: &nbsp;addr2line -e '可执行文件名' &nbsp;'dmesg打印的地址'</strong></span></p>
<p>　　编译的时候一定要加&ldquo;-g&rdquo; &nbsp;添加调试信息:gcc -g test.c</p>
<p>　　生成的可执行文件a.out一运行就会报错：Segmentation fault</p>
<p>　　调用命令dmesg ，可以查看系统启动信息，其中最新的一行信息应该是段错误的描述信息，如下，ip后的地址就是发生段错误的地址。</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326204051661-1147552321.png" alt="" /></p>
<p>　　然后调用命令"addr2line -e a.out 0x8043db"就会打印出发生错误的文件和行号：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326204224861-863170850.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="font-size: 18pt;"><strong>二、core dumpe文件：程序崩溃时会保存程序运行时的内存信息</strong></span></p>
<p>　　先使用 ulimit -a 查看目前资源限制的设定：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326204448150-1010305750.png" alt="" /></p>
<p>　　可查看到&ldquo;core file size&rdquo;的大小为0，我们设置成 200。</p>
<p>　　然后再次 gcc -g test.c ，运行可执行文件a.out：</p>
<p>&nbsp;　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326204704559-723113087.png" alt="" /></p>
<p>　　ls可以看到当前目录下生成了&ldquo;core&rdquo;文件</p>
<p>　　然后我们 gdb a.out：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180326204808142-1152504179.png" alt="" /></p>
<p>　　可以看到，一旦我们run了之后，程序就会停在发生段错误的地方。</p>
<p>　　或者执行 gdb a.out core ，gdb会自动运行并停在发生段错误的地方。</p>
<p>&nbsp;</p>
<p>　<span style="font-size: 14pt;">　一般调用ulimit -c X 设置的文件大小都是临时有效，如果要设置永久有效，可以修改/etc/security/limits.conf 文件， 找到 * soft core 0，修改为* soft core unlimited保存，这样每次启动时都会去读取这个配置文件。</span></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>　　</p>