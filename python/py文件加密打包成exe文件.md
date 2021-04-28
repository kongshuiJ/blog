<h2 id="py文件加密打包成exe文件-python的py、pyc、pyo、pyd文件区别" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">python的py、pyc、pyo、pyd文件区别</span></h2>
<ol class="markdown_ol">
<li>py是源文件；</li>
<li>pyc是源文件编译后的文件；</li>
<li>pyo是源文件优化编译后的文件；</li>
<li>pyd是其他语言写的python库；</li>
</ol>
<h2 id="py文件加密打包成exe文件-为什么选用Cpython" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">为什么选用Cpython</span></h2>
<ul class="markdown_ul">
<li>.pyd 文件是由 .c 文件生成的，.c 由源 .py 或 .pyx 文件生成，也就是说，无法反编译成 .py 或 .pyx 源文件，只能反编译成 .c 文件，这样就提高了一定代码安全性。</li>
</ul>
<h2 id="py文件加密打包成exe文件-安装依赖项：" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">安装依赖项：</span></h2>
<ol class="markdown_ol">
<li>Cython(pip install Cython)</li>
<li>pyinstaller</li>
<li>python3</li>
</ol>
<h2 id="py文件加密打包成exe文件-示例(以下文件在同一层目录)" class="xsj_heading_hash xsj_heading xsj_heading_h2"><span class="xsj_heading_content">示例(以下文件在同一层目录)</span></h2>
<h3 id="py文件加密打包成exe文件-目录结构" class="xsj_heading_hash xsj_heading xsj_heading_h3"><span class="xsj_heading_content">目录结构</span></h3>
<p class="xsj_paragraph xsj_paragraph_level_0">├───conf_file<br />│ ├───t1.conf<br />├───log_file<br />├───src<br />│&nbsp;<a class="external-link" href="http://xn--main-4e2baa5t.py/" rel="nofollow">├───main.py</a><br />│&nbsp;<a class="external-link" href="http://xn--setup-309baa3w.sh/" rel="nofollow">├───setup.sh</a><br />│&nbsp;<a class="external-link" href="http://xn--t1-64waa9n.py/" rel="nofollow">├───t1.py</a><br />│&nbsp;<a class="external-link" href="http://xn--t2-64waa9n.py/" rel="nofollow">├───t2.py</a><br />├───tool<br />│ ├───t1.exe</p>
<h3 id="py文件加密打包成exe文件-文件内容" class="xsj_heading_hash xsj_heading xsj_heading_h3"><span class="xsj_heading_content">文件内容</span></h3>
<p><span class="xsj_heading_content">1.创建'<a class="external-link" href="http://t1.py/" rel="nofollow">t1.py</a>'，'<a class="external-link" href="http://t2.py/" rel="nofollow">t2.py</a>'，'<a class="external-link" href="http://main.py/" rel="nofollow">main.py</a>'文件</span></p>
<p>&nbsp;</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">#</span><span style="color: #008000;"> file: t1.py</span>
<span style="color: #008080;"> 2</span> <span style="color: #0000ff;">def</span><span style="color: #000000;"> printT1():
</span><span style="color: #008080;"> 3</span>     <span style="color: #0000ff;">print</span>(<span style="color: #800000;">"</span><span style="color: #800000;">Hello t1</span><span style="color: #800000;">"</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 4</span>     
<span style="color: #008080;"> 5</span>     
<span style="color: #008080;"> 6</span> <span style="color: #008000;">#</span><span style="color: #008000;"> file: t2.py</span>
<span style="color: #008080;"> 7</span> <span style="color: #0000ff;">def</span><span style="color: #000000;"> printT2():
</span><span style="color: #008080;"> 8</span>     <span style="color: #0000ff;">print</span>(<span style="color: #800000;">"</span><span style="color: #800000;">Hello t2</span><span style="color: #800000;">"</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 9</span>     
<span style="color: #008080;">10</span>     
<span style="color: #008080;">11</span> <span style="color: #008000;">#</span><span style="color: #008000;"> file: main.py</span>
<span style="color: #008080;">12</span> <span style="color: #0000ff;">import</span><span style="color: #000000;"> t1
</span><span style="color: #008080;">13</span> <span style="color: #0000ff;">import</span><span style="color: #000000;"> t2
</span><span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">if</span> <span style="color: #800080;">__name__</span> == <span style="color: #800000;">"</span><span style="color: #800000;">__main__</span><span style="color: #800000;">"</span><span style="color: #000000;">:
</span><span style="color: #008080;">16</span> 
<span style="color: #008080;">17</span> <span style="color: #000000;">    t1.printT1()
</span><span style="color: #008080;">18</span>     t2.printT2()</pre>
</div>
<p>&nbsp;</p>
<p>2.创建'<a class="external-link" href="http://setup.py/" rel="nofollow">setup.py</a>'文件</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">#</span><span style="color: #008000;"> file: setup.py</span>
<span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #0000ff;">from</span> distutils.core <span style="color: #0000ff;">import</span><span style="color: #000000;"> setup
</span><span style="color: #008080;"> 4</span> <span style="color: #0000ff;">from</span> distutils.extension <span style="color: #0000ff;">import</span><span style="color: #000000;"> Extension
</span><span style="color: #008080;"> 5</span> <span style="color: #0000ff;">from</span> Cython.Distutils <span style="color: #0000ff;">import</span><span style="color: #000000;"> build_ext
</span><span style="color: #008080;"> 6</span> 
<span style="color: #008080;"> 7</span> ext_modules1 = [Extension(<span style="color: #800000;">"</span><span style="color: #800000;">t1</span><span style="color: #800000;">"</span>, [<span style="color: #800000;">"</span><span style="color: #800000;">t1.py</span><span style="color: #800000;">"</span><span style="color: #000000;">])]
</span><span style="color: #008080;"> 8</span> <span style="color: #000000;">setup(
</span><span style="color: #008080;"> 9</span>     name = <span style="color: #800000;">'</span><span style="color: #800000;">t1</span><span style="color: #800000;">'</span><span style="color: #000000;">,
</span><span style="color: #008080;">10</span>     cmdclass = {<span style="color: #800000;">'</span><span style="color: #800000;">build_ext</span><span style="color: #800000;">'</span><span style="color: #000000;">: build_ext},
</span><span style="color: #008080;">11</span>     ext_modules =<span style="color: #000000;"> ext_modules1
</span><span style="color: #008080;">12</span> <span style="color: #000000;">)
</span><span style="color: #008080;">13</span> 
<span style="color: #008080;">14</span> ext_modules1 = [Extension(<span style="color: #800000;">"</span><span style="color: #800000;">t2</span><span style="color: #800000;">"</span>, [<span style="color: #800000;">"</span><span style="color: #800000;">t2.py</span><span style="color: #800000;">"</span><span style="color: #000000;">])]
</span><span style="color: #008080;">15</span> <span style="color: #000000;">setup(
</span><span style="color: #008080;">16</span>     name = <span style="color: #800000;">'</span><span style="color: #800000;">t2</span><span style="color: #800000;">'</span><span style="color: #000000;">,
</span><span style="color: #008080;">17</span>     cmdclass = {<span style="color: #800000;">'</span><span style="color: #800000;">build_ext</span><span style="color: #800000;">'</span><span style="color: #000000;">: build_ext},
</span><span style="color: #008080;">18</span>     ext_modules =<span style="color: #000000;"> ext_modules1
</span><span style="color: #008080;">19</span> )</pre>
</div>
<p>&nbsp;</p>
<p>3.创建&lsquo;<a class="external-link" href="http://pack.sh/" rel="nofollow">pack.sh</a>&rsquo;文件</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #000000;"># 如果使用的python3 ，以下指令请全部使用python3
</span><span style="color: #008080;"> 2</span> <span style="color: #000000;"># 仅适用win10
</span><span style="color: #008080;"> 3</span> <span style="color: #000000;"> # 生成pyd文件
</span><span style="color: #008080;"> 4</span> python setup.py build_ext --<span style="color: #000000;">inplace
</span><span style="color: #008080;"> 5</span> <span style="color: #000000;"> # pyinstall打包
</span><span style="color: #008080;"> 6</span> pyinstaller.exe -<span style="color: #000000;">D main.py
</span><span style="color: #008080;"> 7</span> <span style="color: #000000;"> # 拷贝文件夹到 dist
</span><span style="color: #008080;"> 8</span> <span style="color: #0000ff;">cp</span> -rf ../conf_file dist/<span style="color: #000000;">main
</span><span style="color: #008080;"> 9</span> <span style="color: #0000ff;">cp</span> -rf ../log_file dist/<span style="color: #000000;">main
</span><span style="color: #008080;">10</span> <span style="color: #0000ff;">cp</span> -rf ../tool dist/<span style="color: #000000;">main
</span><span style="color: #008080;">11</span> <span style="color: #000000;"> # 拷贝pyd文件到dist
</span><span style="color: #008080;">12</span> <span style="color: #0000ff;">cp</span> -rf *.pyd dist/main</pre>
</div>
<p>&nbsp;</p>