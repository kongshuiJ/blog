<h1><span style="font-family: 'Microsoft YaHei'; color: #ff0000;">问题出现：</span></h1>
<p><span style="font-family: 'Microsoft YaHei';">Jenkins一直都构建成功，今天突然报错：Jenkins Build step 'Execute shell' marked build as failure</span></p>
<p>&nbsp;</p>
<h1><span style="font-family: 'Microsoft YaHei'; color: #ff0000;">问题原因：</span></h1>
<p><span style="font-family: 'Microsoft YaHei';">By default Jenkins take /bin/sh -xe and this means -x will print each and every command.And the other option -e, which causes shell to stop running a script immediately when any command exits with non-zero (when any command fails) exit code.</span></p>
<p>&nbsp;</p>
<h1><span style="font-family: 'Microsoft YaHei'; color: #99cc00;">解决办法：</span></h1>
<p><span style="font-family: 'Microsoft YaHei';">通过问题原因基本确定是因为-e或者-x导致构建失败(我这边是因为-x导致磁盘空间不足)，所以我们在"Execute shell"的开头加上"#!/bin/sh" 或"#!/bin/bash"就可以了。</span></p>