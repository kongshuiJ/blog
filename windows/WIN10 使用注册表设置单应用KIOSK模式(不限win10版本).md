<h1 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-注意事项" class="xsj_heading_hash xsj_heading xsj_heading_h1"><span class="xsj_heading_content">注意事项</span></h1>
<ul class="markdown_ul">
<li><span class="xsj_placeholder_span">下载安装Autologon.exe。</span></li>
<li><span class="xsj_placeholder_span">以下示例采用账号：<br />- 账户：'KIOSK'<br />- 密码：'KIOSK'</span></li>

</ul>
<h1 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-设置步骤" class="xsj_heading_hash xsj_heading xsj_heading_h1"><span class="xsj_heading_content">设置步骤</span></h1>
<h2 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-新建用户" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">新建用户</span></h2>
<p class="xsj_paragraph xsj_paragraph_level_0">1.进入windows设置-&gt;账户-&gt;其他用户，点击'将其他人添加到这台电脑'；<br /><span class="story_inline_image"><span class="confluence-embedded-file-wrapper"><img class="confluence-embedded-image confluence-external-resource" src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200743436-1174256044.png" alt="" data-image-src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200743436-1174256044.png" /><br />2.右键用户，点击新用户,如图下操作：<br /><span class="confluence-embedded-file-wrapper"><img class="confluence-embedded-image confluence-external-resource" src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200801180-1224999986.png" alt="" data-image-src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200801180-1224999986.png" /><br /></span></span></span></p>
<h2 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-下载并执行AUTOLOGON.EXE：自动输入WINDOWS登录用户密码" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">下载并执行AUTOLOGON.EXE：自动输入 WINDOWS 登录用户密码</span></h2>
<p class="xsj_paragraph xsj_paragraph_level_0">&nbsp;<span class="confluence-embedded-file-wrapper"><img class="confluence-embedded-image confluence-external-resource" src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200829699-1260285573.png" alt="" data-image-src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200829699-1260285573.png" />&nbsp;</span></p>
<ol class="markdown_ol">
<li><span class="xsj_placeholder_span">开启功能：输入正确账号和密码后，点击图片'Enable'。</span></li>
<li><span class="xsj_placeholder_span">关闭功能：输入正确账号后，点击图片&lsquo;Disable&rsquo;。<span class="xsj_placeholder_span"><br /></span></span></li>

</ol>
<h2 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-用户SID查询" class="xsj_heading_hash xsj_heading xsj_heading_h3"><span class="xsj_heading_content">用户SID查询</span></h2>
<ol>
<li>
<h3 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-powerShell执行'wmicuseraccountgetname,sid'即可，如下。"><code class="nohighlight hljs">powerShell执行'wmic useraccount get name,sid'即可，如下。</code></h3>
<h3 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-"><code class="nohighlight hljs"><span class="confluence-embedded-file-wrapper"><img class="confluence-embedded-image confluence-external-resource" src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326201032999-1927302280.png" alt="" data-image-src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326201032999-1927302280.png" /><br /></span></code></h3>

</li>
<li>
<h3 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-注册表'HKEY_USERS'内查看是否存在新建账号'KIOS'的SID项，">注册表'<strong>HKEY_USERS</strong>'内查看是否存在新建账号'KIOS'的SID项，</h3>
<ol>
<li>
<p>如果存在，直接到'<strong>计算机\HKEY_USERS\新建账号的SID\Software\Microsoft\Windows NT\CurrentVersion\Winlogon</strong>'新建字符串值'<strong>shell</strong>'，数值数据修改为你需要调用的程序绝对路径；</p>

</li>
<li>
<p>如果不存在，则切换当前登录的账号到你新建账号'KIOSK'，然后查看注册表'<strong>HKEY_CURRENT_USER</strong>'内是否有新建账号'KIOS'的SID项，如果存在按照a步骤操作，如果还没有，没得办法了，自己解决，我没遇到过；</p>

</li>

</ol></li>
<li>
<h3 id="WIN10使用注册表设置单应用KIOSK模式(不限win10版本)-重启开机" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">重启开机</span></h3>
<p><code class="nohighlight hljs">重启开机后，黑屏，只显示唯一调用的程序界面。</code></p>

</li>

</ol>
<p>&nbsp;</p>