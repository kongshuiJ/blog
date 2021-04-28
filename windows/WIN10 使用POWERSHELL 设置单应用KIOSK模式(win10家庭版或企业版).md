<h1 class="story_title">win10 使用PowerShell 设置单应用kiosk模式</h1>
<div class="story_tags"><span class="tag blue label">win10 家版或企业版<span class="tag blue label">PowerShell<span class="tag blue label">shell 启动器 v1<span class="tag blue label">Autologon.exe</span></span></span></span></div>
<h1 id="e6b3a8e6848fe4ba8be9a1b9_1" class="xsj_heading_hash xsj_heading xsj_heading_h1" data-source-line="5" data-source-line-display="true"><span class="xsj_heading_content">注意事项</span></h1>
<ul class="markdown_ul" data-source-line="6">
<li data-source-line="6"><span class="xsj_placeholder_span">win10 家庭版或企业版。</span></li>
<li data-source-line="7"><span class="xsj_placeholder_span">下载安装Autologon.exe。</span></li>
<li data-source-line="8"><span class="xsj_placeholder_span">Shell 启动器 v1调用的应用程序不可有黑窗(类似cmd)。</span></li>
<li data-source-line="9"><span class="xsj_placeholder_span">以下示例采用账号：<br />- 账户：'KIOSK'<br />- 密码：'KIOSK'</span></li>

</ul>
<h1 id="e8aebee7bdaee6ada5e9aaa4_2" class="xsj_heading_hash xsj_heading xsj_heading_h1" data-source-line="14" data-source-line-display="true"><span class="xsj_heading_content">设置步骤</span></h1>
<h2 id="e696b0e5bbbae794a8e688b7_3" class="xsj_heading_hash xsj_heading xsj_heading_h2" data-source-line="15" data-source-line-display="true"><span class="xsj_heading_content">新建用户</span></h2>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="16" data-source-line-display="true">1.进入windows设置-&gt;账户-&gt;其他用户，点击'将其他人添加到这台电脑'；<br /><span class="story_inline_image"><img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200743436-1174256044.png" alt="" /><br />2.右键用户，点击新用户,如图下操作：<br /><img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200801180-1224999986.png" alt="" /><br /></span></p>
<h2 id="e4b88be8bdbde5b9b6e689a7e8a18cautologonexeefbc9ae887aae58aa8e8be93e585a520windows20e799bbe5bd95e794a8e688b7e5af86e7a081_4" class="xsj_heading_hash xsj_heading xsj_heading_h2" data-source-line="20" data-source-line-display="true"><span class="xsj_heading_content">下载并执行Autologon.exe：自动输入 Windows 登录用户密码</span></h2>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="21" data-source-line-display="true">&nbsp;<img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200829699-1260285573.png" alt="" />&nbsp;</p>
<ol class="markdown_ol" data-source-line="22">
<li data-source-line="22"><span class="xsj_placeholder_span">开启功能：输入正确账号和密码后，点击图片'Enable'。</span></li>
<li data-source-line="23"><span class="xsj_placeholder_span">关闭功能：输入正确账号后，点击图片&lsquo;Disable&rsquo;。</span></li>

</ol>
<h1 id="e4bdbfe794a820powershell20e9858de7bdaee887aae5ae9ae4b98920shell_5" class="xsj_heading_hash xsj_heading xsj_heading_h1" data-source-line="24" data-source-line-display="true"><span class="xsj_heading_content">使用 PowerShell 配置自定义 shell</span></h1>
<h2 id="e696b0e5bbbae69687e4bbb6kioskps1e69687e4bbb6e5908de99a8fe6848f_6" class="xsj_heading_hash xsj_heading xsj_heading_h2" data-source-line="25" data-source-line-display="true"><span class="xsj_heading_content">新建文件'kiosk.ps1'(文件名随意)</span></h2>
<h2 id="kioskps1e69687e4bbb6e58685e5aeb9_7" class="xsj_heading_hash xsj_heading xsj_heading_h2" data-source-line="26" data-source-line-display="true"><span class="xsj_heading_content">'kiosk.ps1'文件内容</span></h2>
<div class="xiaoshujiang_code_container">
<pre data-source-line="27" data-source-line-display="true"><code class="nohighlight hljs">1. 文件内部关于'KIOSK'的地方都要修改成你新建用户的名称。
2. 文件内部'$ShellLauncherClass.SetCustomShell'第二个参数为调用程序的路径。
3. 文件最后有3段代表'开启'，'删除'，'禁用'，需要使用其中一个功能的时候，一定要注释其他两段，如下。</code></pre>
</div>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="30" data-source-line-display="true">&nbsp;<img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200916403-1088340450.png" alt="" /></p>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="30" data-source-line-display="true"><img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326201736786-2078957278.png" alt="" /></p>
<div class="story_image_container story_block_image">
<div class="story_image"><img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326200932289-979459588.png" alt="" /></div>
</div>
<p>&nbsp;</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;">  1</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Check if shell launcher license is enabled</span>
<span style="color: #008080;">  2</span> <span style="color: #0000ff;">function</span> Check-<span style="color: #000000;">ShellLauncherLicenseEnabled
</span><span style="color: #008080;">  3</span> <span style="color: #000000;">{
</span><span style="color: #008080;">  4</span>     [string]<span style="color: #800080;">$source</span> = @<span style="color: #800000;">"</span>
<span style="color: #008080;">  5</span> <span style="color: #800000;">using System;
</span><span style="color: #008080;">  6</span> <span style="color: #800000;">using System.Runtime.InteropServices;
</span><span style="color: #008080;">  7</span> 
<span style="color: #008080;">  8</span> <span style="color: #800000;">static class CheckShellLauncherLicense
</span><span style="color: #008080;">  9</span> <span style="color: #800000;">{
</span><span style="color: #008080;"> 10</span> <span style="color: #800000;">    const int S_OK = 0;
</span><span style="color: #008080;"> 11</span> 
<span style="color: #008080;"> 12</span> <span style="color: #800000;">    public static bool IsShellLauncherLicenseEnabled()
</span><span style="color: #008080;"> 13</span> <span style="color: #800000;">    {
</span><span style="color: #008080;"> 14</span> <span style="color: #800000;">        int enabled = 0;
</span><span style="color: #008080;"> 15</span> 
<span style="color: #008080;"> 16</span> <span style="color: #800000;">        if (NativeMethods.SLGetWindowsInformationDWORD(</span><span style="color: #800000;">"</span>EmbeddedFeature-ShellLauncher-Enabled<span style="color: #800000;">"</span><span style="color: #800000;">, out enabled) != S_OK) {
</span><span style="color: #008080;"> 17</span> <span style="color: #800000;">            enabled = 0;
</span><span style="color: #008080;"> 18</span> <span style="color: #800000;">        }
</span><span style="color: #008080;"> 19</span>         
<span style="color: #008080;"> 20</span> <span style="color: #800000;">        return (enabled != 0);
</span><span style="color: #008080;"> 21</span> <span style="color: #800000;">    }
</span><span style="color: #008080;"> 22</span> 
<span style="color: #008080;"> 23</span> <span style="color: #800000;">    static class NativeMethods
</span><span style="color: #008080;"> 24</span> <span style="color: #800000;">    {
</span><span style="color: #008080;"> 25</span> <span style="color: #800000;">        [DllImport(</span><span style="color: #800000;">"</span>Slc.dll<span style="color: #800000;">"</span><span style="color: #800000;">)]
</span><span style="color: #008080;"> 26</span> <span style="color: #800000;">        internal static extern int SLGetWindowsInformationDWORD([MarshalAs(UnmanagedType.LPWStr)]string valueName, out int value);
</span><span style="color: #008080;"> 27</span> <span style="color: #800000;">    }
</span><span style="color: #008080;"> 28</span> 
<span style="color: #008080;"> 29</span> <span style="color: #800000;">}
</span><span style="color: #008080;"> 30</span> <span style="color: #800000;">"</span>@
<span style="color: #008080;"> 31</span> 
<span style="color: #008080;"> 32</span>     <span style="color: #800080;">$type</span> = Add-Type -TypeDefinition <span style="color: #800080;">$source</span> -<span style="color: #000000;">PassThru
</span><span style="color: #008080;"> 33</span> 
<span style="color: #008080;"> 34</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">$type</span>[0]::<span style="color: #000000;">IsShellLauncherLicenseEnabled()
</span><span style="color: #008080;"> 35</span> <span style="color: #000000;">}
</span><span style="color: #008080;"> 36</span> 
<span style="color: #008080;"> 37</span> [bool]<span style="color: #800080;">$result</span> = <span style="color: #0000ff;">$false</span>
<span style="color: #008080;"> 38</span> 
<span style="color: #008080;"> 39</span> <span style="color: #800080;">$result</span> = Check-<span style="color: #000000;">ShellLauncherLicenseEnabled
</span><span style="color: #008080;"> 40</span> <span style="color: #800000;">"</span><span style="color: #800000;">`nShell Launcher license enabled is set to </span><span style="color: #800000;">"</span> + <span style="color: #800080;">$result</span>
<span style="color: #008080;"> 41</span> <span style="color: #0000ff;">if</span> (<span style="color: #008080;">-not</span>(<span style="color: #800080;">$result</span><span style="color: #000000;">))
</span><span style="color: #008080;"> 42</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 43</span>     <span style="color: #800000;">"</span><span style="color: #800000;">`nThis device doesn't have required license to use Shell Launcher</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 44</span> <span style="color: #000000;">    exit
</span><span style="color: #008080;"> 45</span> <span style="color: #000000;">}
</span><span style="color: #008080;"> 46</span> 
<span style="color: #008080;"> 47</span> <span style="color: #800080;">$COMPUTER</span> = <span style="color: #800000;">"</span><span style="color: #800000;">localhost</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 48</span> <span style="color: #800080;">$NAMESPACE</span> = <span style="color: #800000;">"</span><span style="color: #800000;">root\standardcimv2\embedded</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 49</span> 
<span style="color: #008080;"> 50</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Create a handle to the class instance so we can call the static methods.</span>
<span style="color: #008080;"> 51</span> <span style="color: #000000;">try {
</span><span style="color: #008080;"> 52</span>     <span style="color: #800080;">$ShellLauncherClass</span> = [wmiclass]<span style="color: #800000;">"</span><span style="color: #800000;">\\$COMPUTER\${NAMESPACE}:WESL_UserSetting</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 53</span> <span style="color: #000000;">    } catch [Exception] {
</span><span style="color: #008080;"> 54</span>     write-host <span style="color: #800080;">$_</span><span style="color: #000000;">.Exception.Message; 
</span><span style="color: #008080;"> 55</span>     write-host <span style="color: #800000;">"</span><span style="color: #800000;">Make sure Shell Launcher feature is enabled</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 56</span> <span style="color: #000000;">    exit
</span><span style="color: #008080;"> 57</span> <span style="color: #000000;">    }
</span><span style="color: #008080;"> 58</span> 
<span style="color: #008080;"> 59</span> 
<span style="color: #008080;"> 60</span> <span style="color: #008000;">#</span><span style="color: #008000;"> This well-known security identifier (SID) corresponds to the BUILTIN\Administrators group.</span>
<span style="color: #008080;"> 61</span> 
<span style="color: #008080;"> 62</span> <span style="color: #800080;">$Admins_SID</span> = <span style="color: #800000;">"</span><span style="color: #800000;">S-1-5-32-544</span><span style="color: #800000;">"</span>
<span style="color: #008080;"> 63</span> 
<span style="color: #008080;"> 64</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Create a function to retrieve the SID for a user account on a machine.</span>
<span style="color: #008080;"> 65</span> 
<span style="color: #008080;"> 66</span> <span style="color: #0000ff;">function</span> Get-UsernameSID(<span style="color: #800080;">$AccountName</span><span style="color: #000000;">) {
</span><span style="color: #008080;"> 67</span> 
<span style="color: #008080;"> 68</span>     <span style="color: #800080;">$NTUserObject</span> = New-Object System.Security.Principal.NTAccount(<span style="color: #800080;">$AccountName</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 69</span>     <span style="color: #800080;">$NTUserSID</span> = <span style="color: #800080;">$NTUserObject</span><span style="color: #000000;">.Translate([System.Security.Principal.SecurityIdentifier])
</span><span style="color: #008080;"> 70</span> 
<span style="color: #008080;"> 71</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">$NTUserSID</span><span style="color: #000000;">.Value
</span><span style="color: #008080;"> 72</span>     
<span style="color: #008080;"> 73</span> <span style="color: #000000;">}
</span><span style="color: #008080;"> 74</span> 
<span style="color: #008080;"> 75</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Get the SID for a user account named "KIOSK". Rename "KIOSK" to an existing account on your system to test this script.</span>
<span style="color: #008080;"> 76</span> 
<span style="color: #008080;"> 77</span> <span style="color: #800080;">$KIOSK_SID</span> = Get-UsernameSID(<span style="color: #800000;">"</span><span style="color: #800000;">KIOSK</span><span style="color: #800000;">"</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 78</span> 
<span style="color: #008080;"> 79</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Define actions to take when the shell program exits.</span>
<span style="color: #008080;"> 80</span> 
<span style="color: #008080;"> 81</span> <span style="color: #800080;">$restart_shell</span> = 0
<span style="color: #008080;"> 82</span> <span style="color: #800080;">$restart_device</span> = 1
<span style="color: #008080;"> 83</span> <span style="color: #800080;">$shutdown_device</span> = 2
<span style="color: #008080;"> 84</span> 
<span style="color: #008080;"> 85</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Examples. You can change these examples to use the program that you want to use as the shell.</span>
<span style="color: #008080;"> 86</span> 
<span style="color: #008080;"> 87</span> <span style="color: #008000;">#</span><span style="color: #008000;"> This example sets the command prompt as the default shell, and restarts the device if the command prompt is closed. </span>
<span style="color: #008080;"> 88</span> 
<span style="color: #008080;"> 89</span> <span style="color: #800080;">$ShellLauncherClass</span>.SetDefaultShell(<span style="color: #800000;">"</span><span style="color: #800000;">cmd.exe</span><span style="color: #800000;">"</span>, <span style="color: #800080;">$restart_device</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 90</span> 
<span style="color: #008080;"> 91</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Display the default shell to verify that it was added correctly.</span>
<span style="color: #008080;"> 92</span> 
<span style="color: #008080;"> 93</span> <span style="color: #800080;">$DefaultShellObject</span> = <span style="color: #800080;">$ShellLauncherClass</span><span style="color: #000000;">.GetDefaultShell()
</span><span style="color: #008080;"> 94</span> 
<span style="color: #008080;"> 95</span> <span style="color: #800000;">"</span><span style="color: #800000;">`nDefault Shell is set to </span><span style="color: #800000;">"</span> + <span style="color: #800080;">$DefaultShellObject</span>.Shell + <span style="color: #800000;">"</span><span style="color: #800000;"> and the default action is set to </span><span style="color: #800000;">"</span> + <span style="color: #800080;">$DefaultShellObject</span><span style="color: #000000;">.defaultaction
</span><span style="color: #008080;"> 96</span> 
<span style="color: #008080;"> 97</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Set Internet Explorer as the shell for "KIOSK", and restart the machine if Internet Explorer is closed.</span>
<span style="color: #008080;"> 98</span> 
<span style="color: #008080;"> 99</span> <span style="color: #800080;">$ShellLauncherClass</span>.SetCustomShell(<span style="color: #800080;">$KIOSK_SID</span>, <span style="color: #800000;">"</span><span style="color: #800000;">c:\program files\internet explorer\iexplore.exe www.microsoft.com</span><span style="color: #800000;">"</span>, (<span style="color: #800080;">$null</span>), (<span style="color: #800080;">$null</span>), <span style="color: #800080;">$restart_shell</span><span style="color: #000000;">)
</span><span style="color: #008080;">100</span> 
<span style="color: #008080;">101</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Set Explorer as the shell for administrators.</span>
<span style="color: #008080;">102</span> 
<span style="color: #008080;">103</span> <span style="color: #800080;">$ShellLauncherClass</span>.SetCustomShell(<span style="color: #800080;">$Admins_SID</span>, <span style="color: #800000;">"</span><span style="color: #800000;">explorer.exe</span><span style="color: #800000;">"</span><span style="color: #000000;">)
</span><span style="color: #008080;">104</span> 
<span style="color: #008080;">105</span> <span style="color: #008000;">#</span><span style="color: #008000;"> View all the custom shells defined.</span>
<span style="color: #008080;">106</span> 
<span style="color: #008080;">107</span> <span style="color: #800000;">"</span><span style="color: #800000;">`nCurrent settings for custom shells:</span><span style="color: #800000;">"</span>
<span style="color: #008080;">108</span> Get-WmiObject -namespace <span style="color: #800080;">$NAMESPACE</span> -computer <span style="color: #800080;">$COMPUTER</span> -class WESL_UserSetting |<span style="color: #000000;"> Select Sid, Shell, DefaultAction
</span><span style="color: #008080;">109</span> 
<span style="color: #008080;">110</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Enable Shell Launcher</span>
<span style="color: #008080;">111</span> 
<span style="color: #008080;">112</span> <span style="color: #800080;">$ShellLauncherClass</span>.SetEnabled(<span style="color: #0000ff;">$TRUE</span><span style="color: #000000;">)
</span><span style="color: #008080;">113</span> 
<span style="color: #008080;">114</span> <span style="color: #800080;">$IsShellLauncherEnabled</span> = <span style="color: #800080;">$ShellLauncherClass</span><span style="color: #000000;">.IsEnabled()
</span><span style="color: #008080;">115</span> 
<span style="color: #008080;">116</span> <span style="color: #800000;">"</span><span style="color: #800000;">`nEnabled is set to </span><span style="color: #800000;">"</span> + <span style="color: #800080;">$IsShellLauncherEnabled</span><span style="color: #000000;">.Enabled
</span><span style="color: #008080;">117</span> 
<span style="color: #008080;">118</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Remove the new custom shells.</span>
<span style="color: #008080;">119</span> 
<span style="color: #008080;">120</span> <span style="color: #008000;">#</span><span style="color: #008000;">$ShellLauncherClass.RemoveCustomShell($Admins_SID)</span>
<span style="color: #008080;">121</span> 
<span style="color: #008080;">122</span> <span style="color: #008000;">#</span><span style="color: #008000;">$ShellLauncherClass.RemoveCustomShell($KIOSK_SID)</span>
<span style="color: #008080;">123</span> 
<span style="color: #008080;">124</span> <span style="color: #008000;">#</span><span style="color: #008000;"> Disable Shell Launcher</span>
<span style="color: #008080;">125</span> 
<span style="color: #008080;">126</span> <span style="color: #008000;">#</span><span style="color: #008000;">$ShellLauncherClass.SetEnabled($FALSE)</span>
<span style="color: #008080;">127</span> 
<span style="color: #008080;">128</span> <span style="color: #008000;">#</span><span style="color: #008000;">$IsShellLauncherEnabled = $ShellLauncherClass.IsEnabled()</span>
<span style="color: #008080;">129</span> 
<span style="color: #008080;">130</span> <span style="color: #008000;">#</span><span style="color: #008000;">"`nEnabled is set to " + $IsShellLauncherEnabled.Enabled</span></pre>
</div>
<p>&nbsp;</p>
<h2><span class="xsj_heading_content">管理员权限执行.ps1文件</span></h2>
<h3 id="e7bc96e7a88be5a5bdps1e69687e4bbb6efbc8ce4bdbfe794a8e7aea1e79086e59198e69d83e99990e59ca8powershelle4b88ae689a7e8a18ce8afa5e69687e4bbb6efbc8ce698bee7a4bae5a682e4b88be7bb93e69e9ce8a1a8e7a4bae68890e58a9fe38082_9" class="xsj_heading_hash xsj_heading xsj_heading_h3" data-source-line="166" data-source-line-display="true"><span class="xsj_heading_content">编程好.ps1文件，使用管理员权限在'powerShell'上执行该文件，显示如下结果表示成功。</span></h3>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="167" data-source-line-display="true">&nbsp;<img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326201020807-1090802710.png" alt="" /></p>
<h3 id="e794a8e688b7side69fa5e8afa2_10" class="xsj_heading_hash xsj_heading xsj_heading_h3" data-source-line="168" data-source-line-display="true"><span class="xsj_heading_content">用户SID查询</span></h3>
<div class="xiaoshujiang_code_container">
<pre data-source-line="169" data-source-line-display="true"><code class="nohighlight hljs">powerShell执行'wmic useraccount get name,sid'即可，如下。</code></pre>
</div>
<p class="xsj_paragraph xsj_paragraph_level_0" data-source-line="170" data-source-line-display="true">&nbsp;<img src="https://img2020.cnblogs.com/blog/1347181/202003/1347181-20200326201032999-1927302280.png" alt="" /></p>
<p>&nbsp;</p>
<h2 id="e9878de590afe5bc80e69cba_11" class="xsj_heading_hash xsj_heading xsj_heading_h2" data-source-line="171" data-source-line-display="true"><span class="xsj_heading_content">重启开机</span></h2>
<div class="xiaoshujiang_code_container">
<pre data-source-line="172" data-source-line-display="true"><code class="nohighlight hljs">重启开机后，黑屏，只显示唯一调用的程序界面。</code></pre>
</div>
<h1 id="e79bb8e585b3e8bf9ee68ea5_12" class="xsj_heading_hash xsj_heading xsj_heading_h1" data-source-line="174" data-source-line-display="true"><span class="xsj_heading_content">相关连接</span></h1>
<ul class="markdown_ul" data-source-line="175">
<li data-source-line="175"><a class="xsj_link xsj_auto_link" href="https://docs.microsoft.com/zh-cn/windows/configuration/kiosk-shelllauncher">https://docs.microsoft.com/zh-cn/windows/configuration/kiosk-shelllauncher</a></li>
<li data-source-line="176"><a class="xsj_link xsj_auto_link" href="https://stackoverflow.com/questions/33364908/how-to-run-an-application-as-shell-replacement-on-windows-10-enterprise">https://stackoverflow.com/questions/33364908/how-to-run-an-application-as-shell-replacement-on-windows-10-enterprise</a></li>
<li data-source-line="177"><a class="xsj_link xsj_auto_link" href="https://github.com/microsoft/Windows-iotcore-samples/blob/develop/Samples/ShellLauncherV2/SampleConfigXmls/README.md">https://github.com/microsoft/Windows-iotcore-samples/blob/develop/Samples/ShellLauncherV2/SampleConfigXmls/README.md</a></li>
</ul>