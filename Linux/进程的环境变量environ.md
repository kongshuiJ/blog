<p><span style="font-size: 18pt;"><strong>编程之路刚刚开始，错误难免，希望大家能够指出。</strong></span></p>
<p>&nbsp;</p>
<p>每个进程都有自己的环境变量，在C语言程序中可使用外部变量(char **environ)来访问环境，而库函数可允许进程去获取或修改自己环境的值。</p>
<p>　　两种方法使用该变量。</p>
<p>　　<strong>第一种</strong>是将其直接声明为外部变量，就可以直接调用了：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180327203350600-1648880179.png" alt="" /></p>
<p>　　</p>
<p>　　<strong>第二种</strong>，该变量在unistd.h头文件里已有声明，打开头文件如下：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180327203606490-669460462.png" alt="" /></p>
<p>　　可以看到当宏定义了"__USE_GNU"后，才可以使用该变量，代码如下：</p>
<p>　　<img src="https://images2018.cnblogs.com/blog/1347181/201803/1347181-20180327203834874-674365772.png" alt="" /></p>
<p>&nbsp;</p>
<p>添加环境变量可以调用函数setenv()和putenv()，删除某个环境变量调用unsetenv()，清空环境变量，如将environ参数复制为NULL(也可调用函数clearenv())来实现。</p>
<p>&nbsp;</p>