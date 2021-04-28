<p><span style="font-size: 14pt; color: #ff0000;">倍福：</span></p>
<p>&nbsp;</p>
<p>1.倍福的每个从站模块(IO模块)一般都有转换时间而这些时间会导致从站模块输出数值存在延迟，举例：当在15:00开始调用API让主站板卡输出数据，而用示波器实际检测到模块输出数值的时间大约在15:00之后的250us，当然随着从站模块的增加延迟时间也会变长。</p>
<p>&nbsp;</p>
<p>2.倍福的每个从站模块(IO模块)的转换时间都发生在模块自身，而非耦合器。</p>
<p>&nbsp;</p>
<p>3.EtherCAT在倍福IO模块上实现的热插拔是节点式热插拔，而非模块热插拔，即一个耦合器带多个IO模块算一个节点，节点上的模块是不支持热插拔的。</p>
<p>&nbsp;</p>
<p>4.EtherCAT主站协议栈会根据设定的周期时间，自动发送数据。应用程序写了什么数据，那么主站协议栈就会发送什么数据。如果应用程序没有写数据，那么主站协议栈就发送上个周期的数据。</p>
<p>&nbsp;</p>
<p>5.TwinCAT要想使用扫描IO板卡的功能，需要倍福自己的控制器或者兼容的网卡，控制器我不了解，网卡可以在网站中查看。https://infosys.beckhoff.com/english.php?content=../content/1033/tcsystemmanager/reference/ethercat/html/ethercat_supnetworkcontroller.htm&amp;id=94213351731972248024</p>
<p>&nbsp;</p>
<p>6.360和TwinCAT冲突，切记。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><span style="font-size: 14pt; color: #ff0000;">赫优讯：</span></p>
<p>&nbsp;</p>
<p><span style="color: #000000;">1.</span>EtherCAT主站协议栈是支持Hot Connect这个功能的，但是目前版本的SYCON.net不能支持Hot Connect的配置，需要使用ENI文件（该文件也是配置文件，是由EtherCAT Configurator生成，这个软件不是赫优讯公司的，是Beckhoff公司的）。也就是 使用ENI文件替换SYCON.net生成的config.nxd文件。</p>
<p>&nbsp;</p>
<p>2.SYCON.net软件目前只有windows版本，如果主站板卡是在Linux系统，要想使用SYCON.net的部分功能(如扫描从站板卡)，可以调用cifX驱动包自己的例子cifXTCP去连接SYCON.net，前提是需要在SYCON.net配置好要连接Linux的ip地址。</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p>暂时就先记这些。</p>
<p>&nbsp;</p>