<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>今天编了个动态库，然后自己测试了一下。</p>
<p>忘记设置程序运行时系统搜索库的路径发生错误：</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180320195911339-861498855.png" alt="" /></p>
<p>忘记设置程序编译的时候 -L 指定路径报的错误：</p>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180320200140704-704552889.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000;">-L ： 告诉程序在编译的时候动态库的信息在那个路径可以找到。</span></p>
<p><span style="color: #ff0000;">/etc/ld.so.conf &nbsp;：告诉系统程序运行时加载动态库的信息在那个路径可以找到。但需要注意的是/etc/ld.so.conf最重要的作用是作为将文件内的路径缓存到/etc/ld.so.cache以供系统快速查找库，具体看下面。</span></p>
<p>&nbsp;</p>
<p><span style="color: #000000;">在这里顺便记录一下设置动态库路径的三种方法：</span></p>
<p><span style="color: #000000;">　　<span style="font-size: 18pt;">1.gcc参数设置</span><br />　</span></p>
<div class="cnblogs_code">
<pre>-Wl,-rpath=库路径(相对，绝对都可以)</pre>
</div>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180320201756773-312616169.png" alt="" /></p>
<p><span style="font-size: 18pt;">　　2.环境变量设置</span></p>
<div class="cnblogs_code">
<pre>export LD_LIBRARY_PATH=库路径（同上）</pre>
</div>
<p>　　这里只是临时设置，永久设置自行百度。</p>
<p><span style="font-size: 18pt;">　　3./etc/ld.so.conf设置</span></p>
<div class="cnblogs_code">
<pre>vim /etc/<span style="color: #000000;">ld.so.conf
另起一行添加库的绝对路径！！！</span></pre>
</div>
<p>　　保存好文件后一定要执行 ldconfig。</p>
<p>　　/sbin/ldconfig，作用是将文件/etc/ld.so.conf列出的路径下的库文件缓存到/etc/ld.so.cache以供系统使用，因此当安装完一些库文件，或者修改/etc/ld.so.conf增加了库的新的搜索路径，需要执行一下ldconfig，使所有的库文件都被缓存到文件/etc/ld.so.cache中，如果没做，可能会找不到刚安装的库。</p>
<p>&nbsp;</p>
<p><span style="color: #000000;">&nbsp;一定要记住 -L服务于程序，/etc/ld.so.conf服务于系统。</span></p>
<p>&nbsp;</p>