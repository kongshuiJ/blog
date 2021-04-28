<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>领导要求，要4台机器时钟同步，上网查了查，主要看了看ptp和ntp，感觉ntp就够用，索性就直接上手ntp了。</p>
<p>&nbsp;</p>
<p><span style="font-size: 18pt;"><strong><span style="color: #ff0000;">以下内容纯属最基础的内容，只适合第一次接触ntp并且需求简单的朋友。</span></strong></span></p>
<p>&nbsp;</p>
<p>就我当前项目来介绍下ntp：多台计算机因为某些原因对时间的同步性比较重视，所以需要不间断的去同步各个计算机的时间，<strong>而ntp就是使网络中的各个计算机时间同步的一种协议，其精度在局域网内可达0.1ms，在互联网上绝大多数的地方其精度可以达到1-50ms。</strong></p>
<p>&nbsp;</p>
<p><strong>第一步：</strong>安装ntp</p>
<div class="cnblogs_code">
<pre>aptitude install npt （此处用apt-<span style="color: #0000ff;">get</span> 也可以，但建议使用aptitude，就我目前知道的是aptitude安装后的软件卸载时能够将其的依赖包也卸载掉，而apt-get的卸载无法办到，两者建议不要混用。）</pre>
</div>
<p>&nbsp;</p>
<p><strong>第二步：</strong>查看安装是否成功</p>
<div class="cnblogs_code">
<pre>service --status-all</pre>
</div>
<p><img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180322192355152-1314892058.png" alt="" /></p>
<p>&nbsp;</p>
<p>/etc/ntp.conf是ntp的配置文件，第一次接触最好在编辑之前先备份，你懂得。</p>
<p><strong>第三步：了解</strong>/etc/ntp.conf设置</p>
<p>　<span style="color: #000000;">　简单的来说，该文件其实就两关键词<span class="hljs-keyword">restrict和server，前者是用来做限制的，后者是用来连接上层服务器(ntp一共16层，第16层无法同步)</span></span></p>
<p><strong><span class="hljs-keyword" style="color: #000000;">　　restrict [ 客户端IP ] &nbsp;mask &nbsp;[ IP掩码 ] &nbsp;[参数]</span></strong></p>
<p><span class="hljs-keyword"><strong>　　　　</strong></span>&ldquo;客户端IP&rdquo; 和 &ldquo;IP掩码&rdquo; 如果使用default关键字，表示对所有的计算机进行控制，常见的参数如下：</p>
<p>　　　　ignore：拒绝连接到NTP服务器</p>
<p>　　　　nomodiy：&nbsp;客户端不能更改服务端的时间参数，但是客户端可以通过服务端进行网络校时。</p>
<p>　　　　noquery：&nbsp;不提供客户端的时间查询</p>
<p>　　　　notrap： 不提供trap远程登录功能，trap服务是一种远程时间日志服务。</p>
<p>　　　　notrust： 客户端除非通过认证，否则该客户端来源将被视为不信任子网&nbsp;。</p>
<p>　　　　nopeer： 提供时间服务，但不作为对等体。</p>
<p>　　　　kod： 向不安全的访问者发送Kiss-Of-Death报文。</p>
<p>&nbsp;</p>
<p><strong>　　server [上层服务器的IP或域名] &nbsp;<strong><strong>&nbsp;[参数</strong>]</strong></strong></p>
<p>其中host是上层NTP服务器的IP地址或域名，随后所跟的参数解释如下所示：</p>
<p>　　　　key： 表示所有发往服务器的报文包含有秘钥加密的认证信息，n是32位的整数，表示秘钥号。</p>
<p>　　　　prefer： 如果有多个server选项，具有该参数的服务器有限使用。</p>
<p>　　　　minpoll： 指定与查询该服务器的最小时间间隔为2的n次方秒，n默认为6，范围为4-14。</p>
<p>　　　　maxpoll：&nbsp;&nbsp;指定与查询该服务器的最大时间间隔为2的n次方秒，n默认为10，范围为4-14。</p>
<p>　　　　iburst： 当初始同步请求时，采用突发方式接连发送8个报文，时间间隔为2秒。</p>
<p><strong>第四步：</strong>编辑/etc/ntp.conf</p>
<p>　　<span style="color: #ff0000;">编辑之前一定要知道ntp的每层设备都是服务器，下面说的服务端和客户端都是相对而言的。</span></p>
<p><span style="color: #ff0000;">　　<span style="color: #000000;">先上服务端</span><br /></span></p>
<p><span style="color: #ff0000;"><span style="color: #000000;">　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180322195223913-837661123.png" alt="" /></span></span></p>
<p>　　</p>
<p>　　客服端</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180323094631257-1183223440.png" alt="" /></p>
<p>&nbsp;</p>
<p><strong>第五步：</strong>运行ntp</p>
<p><strong>　　</strong>服务端和客户端的配置文件在编辑完保存后就可以重新启动ntp了：</p>
<div class="cnblogs_code">
<pre>　　/etc/init.d/ntp restart</pre>
</div>
<p>&nbsp;</p>
<p>&nbsp;　　重启时间可能会比较长，大概在5分钟左右。</p>
<p>　　可以通过ntpq -p来查看所有作为时钟源校正过本地NTP服务器时钟的上层NTP服务器</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180322200114653-1807055402.png" alt="" /></p>
<p>　　各个选项的解释：</p>
<p>　　　　remote： 远程NTP服务器的IP地址或域名，带 &ldquo;*&rdquo; 的表示本地NTP服务器与该服务器同步。</p>
<p>　　　　refid： 远程NTP服务器的上层服务器的IP地址或域名。</p>
<p>　　　　st： 远程NTP服务器所在的层数。</p>
<p>　　　　t： 本地NTP服务器与远程NTP服务器的通信方式，u: 单播； b: 广播； l: 本地。</p>
<p>　　　　when： 上一次校正时间与现在时间的差值。</p>
<p>　　　　poll： 本地NTP服务器查询远程NTP服务器的时间间隔。</p>
<p>　　　　reach： 是一种衡量前8次查询是否成功的位掩码值，377表示都成功，0表示不成功。</p>
<p>　　　　delay： 网络延时，单位是10的-6次方秒。</p>
<p>　　　　offset： 本地NTP服务器与远程NTP服务器的时间偏移。</p>
<p>　　　　jitter： 查询偏差的分布值，用于表示远程NTP服务器的网络延时是否稳定，单位为10的-6次方秒</p>
<p>&nbsp;</p>
<p>　　还可以通过ntptrace查看本地NTP服务器的在第几层。</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180322200434986-1416606568.png" alt="" /></p>
<p>　　</p>
<p><strong><span style="font-size: 18pt;">　　最后提一下ntpd和ntpdate(教程为ntpd)：</span></strong></p>
<p>　　　ntpd在实际同步时间时是一点点的校准过来时间的，最终把时间慢慢的校正对。而ntpdate不会考虑其他程序是否会阵痛，直接调整时间。简单的说就是ntpd是校准时间，ntpdate是调整时间。<br />　　　不建议大家使用ntpdate，原因摘抄其他前辈的笔记：</p>
<p>　　第一，这样做不安全。ntpdate的设置依赖于ntp服务器的安全性，攻击者可以利用一些软件设计上的缺陷，拿下ntp服务器并令与其同步的服务器执行某些消耗性的任务。由于ntpdate采用的方式是跳变，跟随它的服务器无法知道是否发生了异常（时间不一样的时候，唯一的办法是以服务器为准）。<br />　　第二，这样做不精确。一旦ntp服务器宕机，跟随它的服务器也就会无法同步时间。与此不同，ntpd不仅能够校准计算机的时间，而且能够校准计算机的时钟。<br />　　第三，这样做不够优雅。由于是跳变，而不是使时间变快或变慢，依赖时序的程序会出错（例如，如果ntpdate发现你的时间快了，则可能会经历两个相同的时刻，对某些应用而言，这是致命的）。</p>
<p>&nbsp;</p>