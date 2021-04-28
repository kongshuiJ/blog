<h1><span style="font-size: 18pt;">源码：</span></h1>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">#</span><span style="color: #008000;">!/usr/bin/python</span>
<span style="color: #008080;"> 2</span>     <span style="color: #0000ff;">import</span><span style="color: #000000;"> sys
</span><span style="color: #008080;"> 3</span>     <span style="color: #0000ff;">import</span><span style="color: #000000;"> usb.core
</span><span style="color: #008080;"> 4</span>     <span style="color: #008000;">#</span><span style="color: #008000;"> find USB devices</span>
<span style="color: #008080;"> 5</span>     dev = usb.core.find(find_all=<span style="color: #000000;">True)
</span><span style="color: #008080;"> 6</span>     <span style="color: #008000;">#</span><span style="color: #008000;"> loop through devices, printing vendor and product ids in decimal and hex</span>
<span style="color: #008080;"> 7</span>     <span style="color: #0000ff;">for</span> cfg <span style="color: #0000ff;">in</span><span style="color: #000000;"> dev:
</span><span style="color: #008080;"> 8</span>         <span style="color: #0000ff;">if</span> cfg.idVendor == 0x2207<span style="color: #000000;">:
</span><span style="color: #008080;"> 9</span>             <span style="color: #0000ff;">print</span>(str(cfg.serial_number))        <span style="color: #008000;">#</span><span style="color: #008000;"> 之前就是这里报错</span>
<span style="color: #008080;">10</span>             <span style="color: #0000ff;">print</span><span style="color: #000000;">(str(cfg.port_number))
</span><span style="color: #008080;">11</span>             sys.stdout.write(<span style="color: #800000;">'</span><span style="color: #800000;">Decimal VendorID=</span><span style="color: #800000;">'</span> + str(cfg.idVendor) + <span style="color: #800000;">'</span><span style="color: #800000;">&amp; ProductID=</span><span style="color: #800000;">'</span> + str(cfg.idProduct) + <span style="color: #800000;">'</span><span style="color: #800000;">\n</span><span style="color: #800000;">'</span><span style="color: #000000;">)
</span><span style="color: #008080;">12</span>             sys.stdout.write(<span style="color: #800000;">'</span><span style="color: #800000;">Hexadecimal VendorID=</span><span style="color: #800000;">'</span> + hex(cfg.idVendor) + <span style="color: #800000;">'</span><span style="color: #800000;">&amp; ProductID=</span><span style="color: #800000;">'</span> + hex(cfg.idProduct) + <span style="color: #800000;">'</span><span style="color: #800000;">\n\n</span><span style="color: #800000;">'</span>)</pre>
</div>
<h1><span style="font-size: 18pt;">遇到的问题:</span></h1>
<p>通过pyusb打印出usb设备的所有属性,发现关于serial_number的属性发生了异常,异常如下:<br />		'Traceback (most recent call last):<br />	  File "D:\\Program Files\\JetBrains\\PyCharm 2019.3.1\\plugins\\python\\helpers\\pydev\\_pydevd_bundle\\pydevd_resolver.py", line 178, in _getPyDictionary<br />	    attr = getattr(var, n)<br />	  File "D:\\Program Files\\Python37\\lib\\site-packages\\usb\\core.py", line 830, in serial_number<br />	    self._serial_number = util.get_string(self, self.iSerialNumber)<br />	  File "D:\\Program Files\\Python37\\lib\\site-packages\\usb\\util.py", line 314, in get_string<br />	    raise ValueError("The device has no langid")<br />	ValueError: The device has no langid</p>
<p>&nbsp;</p>
<h1><span style="font-size: 18pt;">解决办法:</span></h1>
<p>通过zadig软件安装libusb-win32,libusbk</p>
<p>&nbsp;</p>
<h1><span style="font-size: 18pt;">问题分析:</span></h1>
<p>https://stackoverflow.com/questions/58131082/simple-communication-usb-with-python-pyusb-on-windows-10<br />	https://sourceforge.net/p/pyusb/mailman/pyusb-users/?viewmonth=201608</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<h1><span style="font-size: 18pt;">后续</span></h1>
<p><span style="font-size: 15px;">&nbsp;</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #0000ff;"><br /></span></pre>
</div>