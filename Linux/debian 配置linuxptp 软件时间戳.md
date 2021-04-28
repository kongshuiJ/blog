<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>ntp，ptp，ntp，ptp</p>
<p><span style="color: #ff0000; font-size: 18pt;"><strong>本文只说软件时间戳</strong></span></p>
<p>&nbsp;</p>
<p><span style="font-size: 14pt;">先上几个推荐的网址，可以更好的了解ptp：</span></p>
<p><span style="font-size: 14pt;">https://docs.fedoraproject.org/f26/system-administrators-guide/servers/Configuring_PTP_Using_ptp4l.html</span></p>
<p><span style="font-size: 14pt;">https://doc.opensuse.org/documentation/leap/tuning/html/book.sle.tuning/cha.tuning.ptp.html#tuning.ptp.using</span></p>
<div><span style="font-size: 14pt;">linuxptp项目地址&nbsp; http://linuxptp.sourceforge.net/</span></div>
<div>&nbsp;</div>
<div><strong>第一步，查看是否安装ptp</strong></div>
<div>　　直接跳，这有啥可说的，有没有都直接"aptitue remove xxx' 给它干掉。</div>
<div>&nbsp;</div>
<div><strong>第二步，安装ptp</strong></div>
<div>　　建议直接到上面提到的linuxptp项目地址下载，然后移到一个合适的目录，比如"/home/xxx/WorkSpace/"</div>
<div>　　
<div class="cnblogs_code">
<pre>tar -xvf linuxptp-<span style="color: #800080;">1.8</span><span style="color: #000000;">.tgz
cd linuxptp</span>-<span style="color: #800080;">1.8</span><span style="color: #000000;">
make 
make install</span></pre>
</div>
<p>　　安装完之后，你直接调用"ptp4l"不会成功，你需要"reboot"重启一下。</p>
<p>&nbsp;</p>
<p>简单介绍下软件时间戳模式&ldquo;ptp4l&rdquo;，只介绍我使用过的，硬件时间戳模式得我使用过再介绍：</p>
<p>　　-i ：　　指定网络接口，也就是eth0,eth1等等。</p>
<p>　　-m：　　将消息打印到标准输出。</p>
<p>　　-s：　　开启从站模式，因为不设置的话默认是主站模式</p>
<p>　　-S：　　软件时间戳模式</p>
<p>　　-H：　　硬件时间戳模式</p>
<p>&nbsp;</p>
<p><strong>在测试命令之前，安装一个软件&ldquo;ethtool&rdquo;，该命令用于获取以太网卡的配置信息，或者修改这些配置。这个命令比较复杂，功能特别多，不过我们这里只是用它来查看当前机器上的网卡是否支持软件时间戳模式和硬件时间戳模式：</strong></p>
<p>　　同安装linuxptp一样，建议不要用命令直接安装，到下面的网址去下载压缩包，因为linuxptp项目网址提到：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180323192312535-805392562.png" alt="" /></p>
<p>　　<span style="font-size: 14pt;"><span style="color: #ff0000;">ethtool下载网址</span>：https://mirrors.edge.kernel.org/pub/software/network/ethtool/</span></p>
<p>　　安装步骤无非就是</p>
<p>　　./configure</p>
<p>　　make<br />　　make install</p>
<p>　　安装好之后执行&ldquo;ethtool -T ethX&rdquo;</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180323192727619-1353551622.png" alt="" /></p>
<p>　</p>
<p><strong>第三步，开始测试，将两台时间不同的机器进行时钟同步：</strong></p>
<p><strong>　　记得测试之前把两个机器的时间修改&ldquo;date -s &ldquo;时：分：秒&rdquo; &rdquo;　　两台机器的时间别差太多。</strong></p>
<p>　　服务端：ptp4l -i eth0 -m -S</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180323193052999-1042130116.png" alt="" /></p>
<p>&nbsp;</p>
<p>　　客户端:：ptp4l -i eth0 -m -S -s</p>
<p>&nbsp;　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180323193122243-1605198037.png" alt="" /></p>
<p>　　</p>
<p>　　简单说明下命令执行打印出来的内容，记住关键的就好：</p>
<p>　　1.<span><span>该</span></span><code class="literal">master offset</code><span><span>值表示从主设备测量的偏移量（以纳秒为单位）；</span></span></p>
<p><span><span>　　2.s0，s1，s2表示时钟伺服器的不同状态，s0表示未锁定，s1表示正在同步，s2表示锁定，锁定状态表示不会再发生阶跃行同步，只是缓慢调整；</span></span></p>
<p><span><span>　　3.<span><span>端口0是用于本地PTP管理的Unix域套接字。</span><span>端口1是</span></span><code class="systemitem">eth0</code><span><span>接口；</span></span></span></span></p>
<p><span><span><span><span>　　4.<span><span>当从端口状态改变</span></span><code class="literal">UNCALIBRATED</code><span><span>&nbsp;到</span></span><code class="literal">SLAVE</code><span><span>时，计算机已经成功地与一个PTP主时钟同步。</span></span></span></span></span></span></p>
<p>&nbsp;</p>
<p>软件时间戳就介绍这些，命令&ldquo;pmc&rdquo;我不了解，所以就不记录了，等单位要真是买来硬件服务器，我再来记录硬件时间戳模式。</p>





</div>