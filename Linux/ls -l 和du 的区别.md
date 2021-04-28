<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>简单的来说，ls -l 显示的是实际文件(目录)大小，而du显示的是文件(目录)占用磁盘空间的大小。</p>
<p>　　</p>
<p>　　linux下一切皆文件。　　</p>
<p>&nbsp;</p>
<p>　　<span style="color: #000000;">首先，硬盘的最小存储单位叫做"扇区"。每个扇区储存512字节。&nbsp;　　</span></p>
<p><span style="color: #000000;">　　系统读取硬盘的时候，一次性读取一个"块(block)"(一次性连续读取多个扇区,提高效率)。这种由多个扇区组成的"块"，是文件存取的最小单位。"块"的大小，一般是4KB，即4096byte。</span></p>
<p><span style="color: #000000;">　　<span style="background-color: #ffffff;">数据在磁盘上以块(block)存储数据的大小不一，造成了块的数量也不尽相同，增删改查都会影响数据块的排列方式，为了让系统精准的找到数据对应的那些块，便文件的各种属性信息放在一张索引列表之上，这就是inode。</span></span></p>
<p><span style="color: #000000;"><span style="background-color: #ffffff;">　　文件的inode可通过命令 "stat 文件名"来查看：</span></span></p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180327104809918-1027128092.png" alt="" /></p>
<p>&nbsp;</p>
<p>　　<strong>实际文件大小：</strong>先说目录，通过ls -l可以看出目录大小始终是4096byte的倍数，是因为当创建目录的时候，系统为新建目录创建一个大小为4096byte的block来存放目录下的文件信息(不是目录下所有文件的内容，而是目录中文件的文件名和inode)，并将block的属性放在inode上，同理文件也是会被分配 4096 byte的大小，只不过显示的时候会显示文件的实际大小。</p>
<p>　　<strong>占用磁盘空间大小：</strong>这个就应该好理解多了，其实就是文件或目录(包含所有目录下的文件)实际在磁盘空间上所占用的block大小。</p>
<p>&nbsp;</p>