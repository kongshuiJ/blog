<p style="text-align: left;"><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p style="text-align: center;">&nbsp;</p>
<p style="text-align: center;"><span style="font-size: 18pt;">cifX驱动安装及SYCON.net的使用</span></p>
<p>说明：</p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 简单描述运行cifX的示例之前需要进行的准备，具体的主从站设置请自行查看DVD中的文档。</p>
<p>&nbsp;</p>
<p>关于cifX产品的DVD下载：</p>
<p align="left"><a title="Initiates file download" href="https://www.hilscher.com/fileadmin/big_data/en-US/Resources/zip/Communication_Solutions_DVD_2017-08-1_V1_400_170125_19044.zip" target="_blank">Communication Solutions DVD - cifX, comX and netJACK 2017-08-1/V1.400.170125.19044</a></p>
<p align="left"><a href="https://www.hilscher.com/support/downloads/" target="_blank">https://www.hilscher.com/support/downloads/</a></p>
<p align="left">或者百度云下载：</p>
<p align="left"><a href="https://pan.baidu.com/s/1qYjwSTQ" target="_blank">https://pan.baidu.com/s/1qYjwSTQ</a></p>
<p>&nbsp;</p>
<p>一、 安装SYCON.net软件</p>
<p>1.下载好cifX产品的DVD，打开如下图所示，点击&ldquo;Install SYCON.net Configuration Software&rdquo;下载SYCON.net。</p>
<p align="center">&nbsp;<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192726826-140413547.png" alt="" /></p>
<p align="center">图1 &nbsp;DVD界面</p>
<p>2.安装步骤全都默认选项。</p>
<p>3.安装好后打开SYCON.net界面如下图所示：</p>
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192739662-1195592934.png" alt="" /></p>
<p align="center">图2 &nbsp;SYCON.net界面</p>
<p align="center">&nbsp;</p>
<p align="left">二、安装cifX驱动</p>
<p align="left">1.linux自行建立一个存放驱动的文件夹(如:/root/WorkSpace/EtherCAT_cifX)，后文一律将该文件称为MyPorject。</p>
<p align="left">2.将驱动安装包存放并解压在MyPorject文件夹内。</p>
<p align="left">3.安装驱动的方式有两种，一种是自动构建所有的组件，另一种是分别安装所有组件，此处推荐后一种，第一种是直接到解压文件后的&ldquo;driver&rdquo;目录执行脚本./build_install_driver；第二种是按照&ldquo;driver&rdquo;目录中&ldquo;readme&rdquo;文件所描述的步骤依次执行。</p>
<p align="left">4.安装完驱动后，需要加载uio_netx模块，建议在&ldquo;/etc/modules&rdquo;添加&ldquo;uio_netx&rdquo;使得系统能够在开启的时候自动加载&ldquo;uio_netx&rdquo;模块。</p>
<p align="left">5.调用&ldquo;script&rdquo;目录下的&ldquo;install_firmware&rdquo;脚本来创建存放配置文件的目录结构，并将EtherCAT协议栈文件&ldquo;cifxecm.nxf&rdquo;按图3存放。</p>
<p align="left">&nbsp;&nbsp; ./install_firmware add_device [device no] [serial no]</p>
<p align="left">(如：./install_firmware add_device 1280100 21246)</p>
<p align="left">创建出的目录结构如下图所示：</p>
<p align="left"><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192804387-1106500527.png" alt="" /></p>
<p align="center">图3 cifX设备信息目录结构</p>
<p align="center">&nbsp;</p>
<p>三、SYCON.net添加设备描述文件</p>
<p>1.SYCON.net软件自动扫描从站板卡功能的前提条件是已添加上将要扫描的从站设备描述文件，点击菜单栏&ldquo;Network&rdquo;后选择&ldquo;Import Device Description&rdquo;，根据从站所属的协议类型修改选项框&ldquo;文件类型&rdquo;，如图4所示。</p>
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180314093806954-31243867.png" alt="" /></p>
<p align="center">图4 添加设备描述文件</p>
<p>2.选择好设备描述文件后点击&ldquo;打开&rdquo;会提示是否重新加载设备描述文件目录，点击&ldquo;是&rdquo;，加载完成之后即可在&ldquo;netDevice&rdquo;窗体右侧查看添加的设备描述文件。</p>
<p>&nbsp;</p>
<p align="left">四、生成nxd网络配置文件</p>
<p align="left">1.进入目录&ldquo;example/cifXTCPServer&rdquo;目录，运行&ldquo;./configure&rdquo;，再运行&ldquo;make&rdquo;和&ldquo;make install&rdquo;生成可执行文件&ldquo;cifXTCPServer&rdquo;。</p>
<p align="left">2.Windows上打开SYCON.net软件，从&ldquo;Fieldbus&rdquo;窗口拖出EtherCAT主站&ldquo;CIFX RE/ECM&rdquo;放在&ldquo;netDevice&rdquo;窗体内。</p>
<p align="left"><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192817046-2141791308.png" alt="" /></p>
<p align="center">图5 EtherCAT主站</p>
<p align="left">3.Linux运行步骤1生成的可执行文件，然后在windows上双击主站，在弹出的窗体中选择&ldquo;Settings-&gt;Driver&rdquo;，勾选&ldquo;netX Driver&rdquo;。</p>
<p align="left"><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192840482-1747027951.png" alt="" /></p>
<p align="center">图6 选择扫描设备类型</p>
<p>4.&ldquo;TCP Connection&rdquo;中点击图形&ldquo;+&rdquo;添加一个&ldquo;Select IP Range&rdquo;，然后在&ldquo;IP Address&rdquo;中输入linux的IP地址，确定无误点击&ldquo;Save All&rdquo;进行保存。</p>
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192850392-224114935.png" alt="" /></p>
<p align="center">图7 连接linux服务端</p>
<p>5.点击&ldquo;Device Assignment-&gt;Scan&rdquo;扫描到EtherCAT主站板卡，勾选板卡后点击&ldquo;Apply&rdquo;保存并退出。</p>
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192945176-738816694.png" alt="" /></p>
<p align="center">图8 扫描EtherCAT主站</p>
<p align="left">6.右键点击窗口&ldquo;netDevice&rdquo;中的主站，选择&ldquo;Network scan&rdquo;来扫描所有从站板卡，勾选之后点击&ldquo;Create Devices&rdquo;来自行构建EtherCAT网络结构。</p>
<p align="left">7.构建EtherCAT网络结构后，保存当前工程设置，然后再次右键点击窗口&ldquo;netDevice&rdquo;中的主站，选择&ldquo;Download&rdquo;将网络配置文件&ldquo;config.nxd&rdquo;自行下载到如图3所示的目录中。</p>
<p align="left"><img style="display: block; margin-left: auto; margin-right: auto;" src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180309192930051-1772459289.png" alt="" /></p>
<p align="center">图9 下载网络配置文件</p>