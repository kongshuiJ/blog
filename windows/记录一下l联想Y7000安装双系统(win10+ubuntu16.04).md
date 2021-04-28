<p><span style="font-family: Microsoft YaHei; font-size: 16px;">单位新配的联想拯救者Y7000，感觉很不错哈，先上一张图。</span></p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719112435405-1618562163.png" alt="" /></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">说实在的，装这个有些小坑，我最开始是直接在原装win10上去装双系统的，结果死活装不上，还把原装win10给折腾没了，哈哈，好逗，以前装双系统也没玩成这。。。。</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">所以我个人建议<span style="color: #ff0000;">如果你在原装win10上装双系统不成功，就把它也干掉得了，重新安装个win10</span>。</span></p>
<hr />
<p><span style="font-size: 16px; font-family: Microsoft YaHei;">&nbsp;</span></p>
<p><span style="font-size: 16px; font-family: Microsoft YaHei;">如何删除原装win10就不介绍了。</span></p>
<p><strong>&nbsp;</strong></p>
<p><strong><span style="font-size: 18pt;">一　　修改BIOS</span></strong></p>
<p><span style="font-size: 18pt;">　<span style="font-size: 16px;">想要知道为什么这么设置的自己查一下UEFI吧，我本身也不太懂，就不在这乱介绍了。</span></span></p>
<h2>　关闭secure boot就可以了。</h2>
<p>　　</p>
<p><strong><span style="font-size: 18pt;">二　　U盘UEFI模式安装win10镜像</span></strong></p>
<p><span style="font-size: 16px;">　　<span style="color: #99cc00;">在这里给U深度点个大大的赞！！！</span></span></p>
<p><span style="font-size: 16px;">　　win10pe工具，下载UEFI版：　　　　http://ushendu.wulianos.cn/win10pe/</span></p>
<p><span style="font-size: 16px;">　　u深度win10pe uefi版制作教程：　　 &nbsp;http://ushendu.wulianos.cn/win10pe/pages/uefi.html</span></p>
<p><span style="font-size: 16px;">　　u深度win10pe安装win10系统教程： &nbsp;http://ushendu.wulianos.cn/win10pe/pages/win10.html</span></p>
<p>&nbsp;</p>
<p><span style="font-size: 16px; font-family: Microsoft YaHei;"><span style="font-size: 18pt;"><strong>三　　硬盘分区</strong></span><br /></span></p>
<p><span style="font-size: 16px; font-family: Microsoft YaHei;">　　我是自带的500G SSD，win10分了350G为C、D、E盘， ubuntu分了150G。<br /></span></p>
<p><span style="font-size: 16px; font-family: Microsoft YaHei;">　　<span class="bjh-p">win10磁盘管理器可以直接对磁盘进行管理、分区等操作。</span></span></p>
<p><span style="font-size: 16px; font-family: Microsoft YaHei;">　　<span class="bjh-p">我们可以在&ldquo;开始&rdquo;、&ldquo;运行&rdquo;中输入&ldquo;diskmgmt.msc&rdquo;之后，按键盘的&ldquo;回车&rdquo;或者&ldquo;确定&rdquo;键，进入磁盘管理工具。</span></span></p>
<p><span style="font-family: Microsoft YaHei;">&nbsp;</span></p>
<p><span style="font-size: 18pt; font-family: Microsoft YaHei;">四　　制作ubuntu16.04的isoU盘启动</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　中科大源　　<a style="color: #4285f4;" href="http://mirrors.ustc.edu.cn/ubuntu-releases/16.04/" rel="nofollow">http://mirrors.ustc.edu.cn/ubuntu-releases/16.04/</a></span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　UltraISO软碟通官方中文版　　https://cn.ultraiso.net/xiazai.html</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　借鉴链接：　　https://blog.csdn.net/zjx2014430/article/details/49303785</span></p>
<ol>
<li><span style="font-family: Microsoft YaHei; font-size: 16px;">点击工具栏中的第二个打开镜像文件工具，如图红色方框标志按钮，然后在打开的&ldquo;打开ISO文件&rdquo;对话框中找到我们下载好的Ubuntu镜像文件，之后点右下方的&ldquo;打开&rdquo;按钮。</span><br /><span style="font-size: 16px;"><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152630922-710407529.jpg" alt="" /></span><br /><span style="font-size: 16px;"><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152652463-833144728.jpg" alt="" /><br /><br /><br /></span></li>
<li><span style="font-size: 16px;">打开镜像文件之后，在上方的列表中就会出现对打开的镜像文件的预览左边显示的是具体的目录，右边显示的目录和具体文件。</span><br /><span style="font-size: 16px;"><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152642114-1194785409.jpg" alt="" /><br /><br /><br /></span></li>
<li><span style="font-size: 16px;">下面就开始制作启动盘了，点击菜单栏的&ldquo;启动&rdquo;，然后再弹出才按中选择&ldquo;写入硬盘映像...&rdquo;，打开&ldquo;写入硬盘映像&rdquo;对话框。<br /><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152746470-1086045542.jpg" alt="" /><br /><br /><br /></span></li>
<li><span style="font-size: 16px;">在写入硬盘映像对话框中，硬盘驱动器选择我们要写入的U盘，写入方式默认就好(USB-HDD+)。点击&ldquo;便捷启动&rdquo;，然后再弹出的菜单中依次选择&ldquo;写入新的驱动器引导扇区&rdquo;，再选择&ldquo;Syslinux&rdquo;，这一步的没有选择的话，那么我们最后制作的U盘映像将不能识别硬盘，不能安装系统。<br /><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152837698-1287444353.jpg" alt="" /><br /><br /><br /></span></li>
<li><span style="font-size: 16px;">现在就到了将ISO内的文件写入到U盘的时候了，点击下面的&ldquo;写入&rdquo;按钮，会弹出警告提示框，点击&ldquo;是&rdquo;就开始U盘安装盘的写入了。<br /><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152854681-611313291.jpg" alt="" /><br /><img src="https://img2018.cnblogs.com/blog/1347181/201907/1347181-20190719152904673-1970094047.jpg" alt="" /><br /></span></li>






</ol>
<p>　　　　</p>
<p><span style="font-size: 18pt; font-family: Microsoft YaHei;">五　　U<strong>盘启动安装ubuntu成功</strong></span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　插入U盘，启动电脑，按住F12进入选择界面后选U盘启动。</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　跳出ubuntu安装界面，选&ldquo;install Ubuntu&rdquo;，进入安装过程，我基本上都是默认选项。</span></p>
<p>&nbsp;</p>
<hr />
<p>&nbsp;</p>
<p><strong><span style="font-family: Microsoft YaHei; font-size: 16px;"><span style="font-size: 18pt;">安装完成遇到的问题：</span></span></strong></p>
<p>&nbsp;</p>
<p><strong><span style="font-family: Microsoft YaHei; font-size: 16px;"><span style="font-size: 18pt;">一　　wifi问题</span></span></strong></p>
<p><span style="font-size: 16px;"><span style="font-family: Microsoft YaHei;">　　如果是wifi都不显示，那么看看是不是你的内核版本低于4.14。　　</span></span></p>
<p><span style="font-size: 16px;"><span style="font-family: Microsoft YaHei;">　　<span style="font-family: Microsoft YaHei;">搜索不到附近到wifi热点，原因是ubuntu默认关闭联想Y7000的wifi硬件，即硬阻塞。<br />　　显示无线和蓝牙状态：<br />　　rfkill list all <br />　　打开文件：<br />　　sudo gedit /etc/rc.local<br />　　在exit 0之前追加一行：</span></span></span></p>
<p><span style="font-size: 16px;"><span style="font-family: Microsoft YaHei;"><span style="font-family: Microsoft YaHei;">　　echo "123" | sudo modprobe -r ideapad_laptop<br />　　保存重启</span></span></span></p>
<p><span style="font-size: 16px;"><span style="font-family: Microsoft YaHei;"><span style="font-family: Microsoft YaHei;">　　以下为<span style="font-size: 16px;"><span style="font-family: Microsoft YaHei;"><span style="font-family: Microsoft YaHei;">/etc/rc.local</span></span></span>文件：</span></span></span></p>
<p>&nbsp;</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> #!/bin/sh -<span style="color: #000000;">e
</span><span style="color: #008080;"> 2</span> <span style="color: #000000;">#
</span><span style="color: #008080;"> 3</span> <span style="color: #000000;"># rc.local
</span><span style="color: #008080;"> 4</span> <span style="color: #000000;">#
</span><span style="color: #008080;"> 5</span> # This script <span style="color: #0000ff;">is</span><span style="color: #000000;"> executed at the end of each multiuser runlevel.
</span><span style="color: #008080;"> 6</span> # Make sure that the script will <span style="color: #800000;">"</span><span style="color: #800000;">exit 0</span><span style="color: #800000;">"</span><span style="color: #000000;"> on success or any other
</span><span style="color: #008080;"> 7</span> <span style="color: #000000;"># value on error.
</span><span style="color: #008080;"> 8</span> <span style="color: #000000;">#
</span><span style="color: #008080;"> 9</span> # In order to enable or disable <span style="color: #0000ff;">this</span><span style="color: #000000;"> script just change the execution
</span><span style="color: #008080;">10</span> <span style="color: #000000;"># bits.
</span><span style="color: #008080;">11</span> <span style="color: #000000;">#
</span><span style="color: #008080;">12</span> # By <span style="color: #0000ff;">default</span> <span style="color: #0000ff;">this</span><span style="color: #000000;"> script does nothing.
</span><span style="color: #008080;">13</span> 
<span style="color: #008080;">14</span> echo <span style="color: #800000;">"</span><span style="color: #800000;">123</span><span style="color: #800000;">"</span> | sudo modprobe -<span style="color: #000000;">r ideapad_laptop
</span><span style="color: #008080;">15</span> 
<span style="color: #008080;">16</span> exit <span style="color: #800080;">0</span></pre>
</div>
<p>&nbsp;</p>
<p><strong><span style="font-family: Microsoft YaHei; font-size: 16px;"><span style="font-size: 18pt;">二　　登录之后卡死问题</span></span></strong></p>
<p><strong><span style="font-family: Microsoft YaHei; font-size: 16px;">　　临时解决：</span></strong></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　　　开机F12选择安装的ubuntu硬盘后 在grub界面选择ubuntu然后按e。</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　　　在splash后面空格再加nouveau.modeset = 0。</span></p>
<p><strong><span style="font-family: Microsoft YaHei; font-size: 16px;">　　永久解决：</span></strong></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　sudo vim /etc/default/grub</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　GRUB_CMDLINE_LINUX_DEFAULT修改为：</span></p>
<p><span style="font-family: Microsoft YaHei; font-size: 16px;">　　　　GRUB_CMDLINE_LINUX_DEFAULT="quiet nouveau.modeset=0"</span></p>
<p>&nbsp;</p>