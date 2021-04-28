<p><strong><span style="font-size: 18pt;">编程之路刚刚开始，错误难免，希望大家能够指出。</span></strong></p>
<p>&nbsp;</p>
<p><strong><span style="color: #ff0000; font-size: 18px;">一、Inotify机制</span></strong></p>
<p>1.<strong>简单介绍inotify：</strong>Inotify可用于检测单个文件，也可以检测整个目录。当检测的对象是一个目录的时候，目录本身和目录里的内容都会成为检测的对象。</p>
<p>此种机制的出现的目的是当内核空间发生某种事件之后，可以立即通知到用户空间。方便用户做出具体的操作。</p>
<p>2.<strong>inotify的三个API：</strong></p>
<p>　　inotify_init(void)　　　　　　　　　　　　　　　　　　　　　　　　</p>
<p>　　用于创建一个inotify的实例，然后返回inotify事件队列的文件描述符。</p>
<p>　　inotify_add_watch(int fd, const char* pathname, uint32_t&nbsp; mask)　　</p>
<p>　　该函数用于添加&ldquo;watch list&rdquo;，也就是检测列表。 可以是一个新的watch，也可以是一个已经存在的watch。其中fd就是inotify_init的返回值，pathname是要检测目录或者文件的路径，mask就是要检测的事件类型。该函数成功返回的是一个unique的watch描述符。</p>
<p>　　inotify_rm_watch(int fd, int wd)　　　　　　　　　　　　　　　　　 &nbsp;&nbsp;</p>
<p>　　用于从watch list种移除检测的对象。</p>
<p>3.<strong>读取事件：</strong></p>
<p>　　使用read系统调用可以获取至少一个（必定为整数个，当剩余空间不足容纳下一个结构体时，该结构体只能下次read获取）的inotify_event结构体。</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;">1</span> <span style="color: #0000ff;">struct</span><span style="color: #000000;"> inotify_event {  
</span><span style="color: #008080;">2</span>     <span style="color: #0000ff;">int</span>      wd;           <span style="color: #008000;">/*</span><span style="color: #008000;">watch描述符 </span><span style="color: #008000;">*/</span>  
<span style="color: #008080;">3</span>     uint32_t mask;     <span style="color: #008000;">/*</span><span style="color: #008000;">  事件掩码 </span><span style="color: #008000;">*/</span>  
<span style="color: #008080;">4</span> <span style="color: #000000;">    uint32_t cookie;   
</span><span style="color: #008080;">5</span>     uint32_t len;      <span style="color: #008000;">/*</span><span style="color: #008000;"> name的长度 </span><span style="color: #008000;">*/</span>  
<span style="color: #008080;">6</span>     <span style="color: #0000ff;">char</span>     name[];   <span style="color: #008000;">/*</span><span style="color: #008000;"> 文件或目录名 </span><span style="color: #008000;">*/</span>  
<span style="color: #008080;">7</span> };  </pre>
</div>
<p>　　切记如果read()的读取缓冲区如果小于一个inotify_event的长度，read会返回错误，所以建议缓冲区为每个inotify_event的长度假定为&ldquo;sizeof(struct inotify_event) + NAME_MAX +1&rdquo;，&ldquo;NAME_MAX&rdquo;是系统文件名最大长度的宏定义。</p>
<p>&nbsp;</p>
<p><span style="font-size: 18px; color: #ff0000;">二、sigaction 函数</span></p>
<p>1.int sigaction(int signum, const struct sigaction *act,&nbsp;struct sigaction *oldact)　　　　　　这个系统调用的作用是改变进程接收到的指定信号的行动。</p>
<p>　　signum : 说明具体信号，它可以是除了SIGKILL和SIGSTOP之外的任何有效信号值。</p>
<p>　　act : 将要安装的signum定义信号的新行动。</p>
<p>　　oldact: 用来保存signum定义信号的过去的行动。</p>
<p>2.目前个人所了解的sigaction和signal的区别：</p>
<p>　　1.signal只能对信号进行一次自定义处理，之后恢复默认操作，sigaction可以进行反复调用；</p>
<p>　　2.signal处理过程中无法阻塞某些信号，而sigaction可以阻塞它自身和其他信号；</p>
<p>3.sigaction 结构体定义如下：</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #0000ff;">struct</span><span style="color: #000000;"> sigaction {
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span>     <span style="color: #0000ff;">void</span> (*sa_handler)(<span style="color: #0000ff;">int</span><span style="color: #000000;">);    设置为SIG_DFL表示默认行动，设置为SIG_IGN表示忽略这个信号，或者设置为处理函数的指针。
</span><span style="color: #008080;"> 4</span> 
<span style="color: #008080;"> 5</span>     <span style="color: #0000ff;">void</span> (*sa_sigaction)(<span style="color: #0000ff;">int</span>,  siginfo_t* , vid*<span style="color: #000000;">);
</span><span style="color: #008080;"> 6</span> 
<span style="color: #008080;"> 7</span> <span style="color: #000000;">    sigset_t sa_mask;    这个参数指明了在信号处理函数执行过程中应该被阻止的信号的mask值(包括它自己)。
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span>     <span style="color: #0000ff;">int</span><span style="color: #000000;"> sa_flags;   改变信号的行为；
</span><span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span>     <span style="color: #0000ff;">void</span> (*sa_restorer)(<span style="color: #0000ff;">void</span><span style="color: #000000;">);
</span><span style="color: #008080;">12</span> 
<span style="color: #008080;">13</span> };</pre>
</div>
<p>&nbsp;</p>
<p><span style="font-size: 14pt;"><strong>简单说明一下思路：</strong></span><br /><span style="font-size: 14pt;"><strong>　　1.将argv[1]指定的目录及其子目录都设置为受监控目录；</strong></span></p>
<p><span style="font-size: 14pt;"><strong>　　2.不断去read事件，并将事件指定记录在某个文件内，并存有时间发生的大概时间；</strong></span></p>
<p><span style="font-size: 14pt;"><strong>　　3.进程需要通过发送&ldquo;SIGINT&rdquo;信号来进行停止。</strong></span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;">  1</span> <span style="color: #0000ff;">#define</span> _XOPEN_SOURCE 500
<span style="color: #008080;">  2</span> 
<span style="color: #008080;">  3</span> #include &lt;stdio.h&gt;
<span style="color: #008080;">  4</span> #include &lt;assert.h&gt;
<span style="color: #008080;">  5</span> #include &lt;unistd.h&gt;
<span style="color: #008080;">  6</span> #include &lt;stdlib.h&gt;
<span style="color: #008080;">  7</span> #include &lt;signal.h&gt;
<span style="color: #008080;">  8</span> #include &lt;errno.h&gt;
<span style="color: #008080;">  9</span> #include &lt;<span style="color: #0000ff;">string</span>.h&gt;
<span style="color: #008080;"> 10</span> #include &lt;sys/types.h&gt;
<span style="color: #008080;"> 11</span> #include &lt;sys/inotify.h&gt;
<span style="color: #008080;"> 12</span> #include &lt;limits.h&gt;
<span style="color: #008080;"> 13</span> #include &lt;fcntl.h&gt;
<span style="color: #008080;"> 14</span> #include &lt;ftw.h&gt;
<span style="color: #008080;"> 15</span> #include &lt;time.h&gt;
<span style="color: #008080;"> 16</span> 
<span style="color: #008080;"> 17</span> <span style="color: #0000ff;">#define</span> BUF_SIZE (10 *(sizeof(struct inotify_event) + NAME_MAX +1))
<span style="color: #008080;"> 18</span> <span style="color: #0000ff;">#define</span> INOTIFT_EVENT (IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO)
<span style="color: #008080;"> 19</span> 
<span style="color: #008080;"> 20</span> <span style="color: #0000ff;">struct</span><span style="color: #000000;"> pathInfo
</span><span style="color: #008080;"> 21</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 22</span>     <span style="color: #0000ff;">int</span><span style="color: #000000;"> wd;
</span><span style="color: #008080;"> 23</span>     <span style="color: #0000ff;">char</span> czPath[<span style="color: #800080;">256</span><span style="color: #000000;">];
</span><span style="color: #008080;"> 24</span>     <span style="color: #0000ff;">struct</span> pathInfo *<span style="color: #000000;">pNext;
</span><span style="color: #008080;"> 25</span> <span style="color: #000000;">};
</span><span style="color: #008080;"> 26</span> 
<span style="color: #008080;"> 27</span> <span style="color: #0000ff;">struct</span><span style="color: #000000;"> eventInfo
</span><span style="color: #008080;"> 28</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 29</span>     <span style="color: #0000ff;">int</span> <span style="color: #0000ff;">event</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 30</span>     <span style="color: #0000ff;">char</span> explain[<span style="color: #800080;">30</span><span style="color: #000000;">];
</span><span style="color: #008080;"> 31</span> <span style="color: #000000;">};
</span><span style="color: #008080;"> 32</span> 
<span style="color: #008080;"> 33</span> <span style="color: #0000ff;">static</span> <span style="color: #0000ff;">struct</span> eventInfo g_stEventInfo[] =
<span style="color: #008080;"> 34</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 35</span>     {IN_CREATE,<span style="color: #800000;">"</span><span style="color: #800000;">create file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 36</span>     {IN_DELETE,<span style="color: #800000;">"</span><span style="color: #800000;">delete file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 37</span>     {IN_DELETE_SELF,<span style="color: #800000;">"</span><span style="color: #800000;">delete file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 38</span>     {IN_MODIFY,<span style="color: #800000;">"</span><span style="color: #800000;">alter file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 39</span>     {IN_MOVED_FROM,<span style="color: #800000;">"</span><span style="color: #800000;">lose file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 40</span>     {IN_MOVED_TO,<span style="color: #800000;">"</span><span style="color: #800000;">append file</span><span style="color: #800000;">"</span><span style="color: #000000;">},
</span><span style="color: #008080;"> 41</span> <span style="color: #000000;">};
</span><span style="color: #008080;"> 42</span> 
<span style="color: #008080;"> 43</span> <span style="color: #0000ff;">int</span><span style="color: #000000;"> g_inotifyFd;
</span><span style="color: #008080;"> 44</span> FILE *<span style="color: #000000;">g_fp;
</span><span style="color: #008080;"> 45</span> <span style="color: #0000ff;">struct</span> pathInfo *<span style="color: #000000;">g_list;
</span><span style="color: #008080;"> 46</span> 
<span style="color: #008080;"> 47</span> <span style="color: #008000;">/*</span>
<span style="color: #008080;"> 48</span> <span style="color: #008000;">IN_CREATE               在受监控目录下创建了文件或目录
</span><span style="color: #008080;"> 49</span> <span style="color: #008000;">IN_DELETE               在受监控目录内删除了文件或目录
</span><span style="color: #008080;"> 50</span> <span style="color: #008000;">IN_DELETE_SELF          删除了受监控目录/文件本身
</span><span style="color: #008080;"> 51</span> <span style="color: #008000;">IN_MODIFY               文件被修改
</span><span style="color: #008080;"> 52</span> <span style="color: #008000;">IN_MOVED_FROM           文件移除受监控目录
</span><span style="color: #008080;"> 53</span> <span style="color: #008000;">IN_MOVED_TO             将文件移到受监控目录
</span><span style="color: #008080;"> 54</span> <span style="color: #008000;">*/</span>
<span style="color: #008080;"> 55</span> 
<span style="color: #008080;"> 56</span> <span style="color: #0000ff;">int</span> myNfwt(<span style="color: #0000ff;">const</span> <span style="color: #0000ff;">char</span> *fpath,<span style="color: #0000ff;">const</span> <span style="color: #0000ff;">struct</span> stat *sb,<span style="color: #0000ff;">int</span> flag,<span style="color: #0000ff;">struct</span> FTW *<span style="color: #000000;">ftwbuf)
</span><span style="color: #008080;"> 57</span> <span style="color: #000000;">{
</span><span style="color: #008080;"> 58</span>     <span style="color: #0000ff;">if</span>(flag !=<span style="color: #000000;"> FTW_DP)
</span><span style="color: #008080;"> 59</span> <span style="color: #000000;">    {
</span><span style="color: #008080;"> 60</span>         <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 61</span> <span style="color: #000000;">    }
</span><span style="color: #008080;"> 62</span>     <span style="color: #0000ff;">int</span> wd =<span style="color: #000000;"> inotify_add_watch(g_inotifyFd,fpath,INOTIFT_EVENT);
</span><span style="color: #008080;"> 63</span>     <span style="color: #0000ff;">if</span>(wd == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 64</span> <span style="color: #000000;">    {
</span><span style="color: #008080;"> 65</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">inotify_add_watch</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;"> 66</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 67</span> <span style="color: #000000;">    }
</span><span style="color: #008080;"> 68</span> 
<span style="color: #008080;"> 69</span>     <span style="color: #0000ff;">struct</span> pathInfo *pTemp = (<span style="color: #0000ff;">struct</span> pathInfo *)<span style="color: #0000ff;">malloc</span>(<span style="color: #0000ff;">sizeof</span>(<span style="color: #0000ff;">struct</span><span style="color: #000000;"> pathInfo));
</span><span style="color: #008080;"> 70</span>     memset(pTemp-&gt;czPath,<span style="color: #800080;">0</span>,<span style="color: #0000ff;">sizeof</span>(pTemp-&gt;<span style="color: #000000;">czPath));
</span><span style="color: #008080;"> 71</span>     pTemp-&gt;wd =<span style="color: #000000;"> wd;
</span><span style="color: #008080;"> 72</span>     pTemp-&gt;pNext =<span style="color: #000000;"> NULL;
</span><span style="color: #008080;"> 73</span>     <span style="color: #0000ff;">if</span>(strcpy(pTemp-&gt;czPath,fpath) ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;"> 74</span> <span style="color: #000000;">    {
</span><span style="color: #008080;"> 75</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">strcpy</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;"> 76</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">2</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 77</span> <span style="color: #000000;">    }
</span><span style="color: #008080;"> 78</span> 
<span style="color: #008080;"> 79</span>     <span style="color: #0000ff;">if</span>(g_list ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;"> 80</span> <span style="color: #000000;">    {
</span><span style="color: #008080;"> 81</span>         g_list =<span style="color: #000000;"> pTemp;
</span><span style="color: #008080;"> 82</span>         <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 83</span> <span style="color: #000000;">    }
</span><span style="color: #008080;"> 84</span>     <span style="color: #0000ff;">else</span>
<span style="color: #008080;"> 85</span> <span style="color: #000000;">    {
</span><span style="color: #008080;"> 86</span>         <span style="color: #0000ff;">if</span>(g_list-&gt;pNext ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;"> 87</span> <span style="color: #000000;">        {
</span><span style="color: #008080;"> 88</span>             g_list-&gt;pNext =<span style="color: #000000;"> pTemp;
</span><span style="color: #008080;"> 89</span>             <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 90</span> <span style="color: #000000;">        }
</span><span style="color: #008080;"> 91</span>         <span style="color: #0000ff;">struct</span> pathInfo *p = g_list-&gt;<span style="color: #000000;">pNext;
</span><span style="color: #008080;"> 92</span>         <span style="color: #0000ff;">while</span>(<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;"> 93</span> <span style="color: #000000;">        {
</span><span style="color: #008080;"> 94</span>             <span style="color: #0000ff;">if</span>(p-&gt;pNext ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;"> 95</span> <span style="color: #000000;">            {
</span><span style="color: #008080;"> 96</span>                 p-&gt;pNext =<span style="color: #000000;"> pTemp;
</span><span style="color: #008080;"> 97</span>                 <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;"> 98</span> <span style="color: #000000;">            }
</span><span style="color: #008080;"> 99</span>             p = p-&gt;<span style="color: #000000;">pNext;
</span><span style="color: #008080;">100</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">101</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">102</span> <span style="color: #000000;">}
</span><span style="color: #008080;">103</span> 
<span style="color: #008080;">104</span> <span style="color: #0000ff;">int</span> watch_object(<span style="color: #0000ff;">char</span> *<span style="color: #000000;">fileName)
</span><span style="color: #008080;">105</span> <span style="color: #000000;">{
</span><span style="color: #008080;">106</span>     <span style="color: #0000ff;">int</span> flags = FTW_PHYS |<span style="color: #000000;"> FTW_DEPTH;
</span><span style="color: #008080;">107</span>     <span style="color: #0000ff;">int</span> ret = nftw(fileName,myNfwt,<span style="color: #800080;">896</span><span style="color: #000000;">,flags);
</span><span style="color: #008080;">108</span>     <span style="color: #0000ff;">if</span>(ret == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">109</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">110</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">nftw</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">111</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">112</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">113</span> 
<span style="color: #008080;">114</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">115</span> <span style="color: #000000;">}
</span><span style="color: #008080;">116</span> 
<span style="color: #008080;">117</span> <span style="color: #0000ff;">char</span> *GetPath(<span style="color: #0000ff;">int</span><span style="color: #000000;"> wd)
</span><span style="color: #008080;">118</span> <span style="color: #000000;">{
</span><span style="color: #008080;">119</span>     <span style="color: #0000ff;">if</span>(g_list ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">120</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">121</span>         <span style="color: #0000ff;">return</span><span style="color: #000000;"> NULL;
</span><span style="color: #008080;">122</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">123</span>     <span style="color: #0000ff;">if</span>(g_list-&gt;wd ==<span style="color: #000000;"> wd)
</span><span style="color: #008080;">124</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">125</span>         <span style="color: #0000ff;">return</span> g_list-&gt;<span style="color: #000000;">czPath;
</span><span style="color: #008080;">126</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">127</span>     <span style="color: #0000ff;">struct</span> pathInfo *pTemp = g_list-&gt;<span style="color: #000000;">pNext;
</span><span style="color: #008080;">128</span> 
<span style="color: #008080;">129</span>     <span style="color: #0000ff;">while</span>(<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">130</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">131</span>         <span style="color: #0000ff;">if</span>(pTemp ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">132</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">133</span>             <span style="color: #0000ff;">break</span><span style="color: #000000;">;
</span><span style="color: #008080;">134</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">135</span>         <span style="color: #0000ff;">if</span>(pTemp-&gt;wd ==<span style="color: #000000;"> wd)
</span><span style="color: #008080;">136</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">137</span>             <span style="color: #0000ff;">return</span> pTemp-&gt;<span style="color: #000000;">czPath;
</span><span style="color: #008080;">138</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">139</span>         pTemp = pTemp-&gt;<span style="color: #000000;">pNext;
</span><span style="color: #008080;">140</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">141</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> NULL;
</span><span style="color: #008080;">142</span> <span style="color: #000000;">}
</span><span style="color: #008080;">143</span> 
<span style="color: #008080;">144</span> <span style="color: #0000ff;">int</span><span style="color: #000000;"> recordEvent()
</span><span style="color: #008080;">145</span> <span style="color: #000000;">{
</span><span style="color: #008080;">146</span>     <span style="color: #0000ff;">int</span><span style="color: #000000;"> iReadNum;
</span><span style="color: #008080;">147</span>     <span style="color: #0000ff;">char</span> czBuf[BUF_SIZE+<span style="color: #800080;">1</span>] = {<span style="color: #800080;">0</span><span style="color: #000000;">};
</span><span style="color: #008080;">148</span>     <span style="color: #0000ff;">struct</span> inotify_event *<span style="color: #000000;">pEvent;
</span><span style="color: #008080;">149</span> <span style="color: #000000;">    time_t now;
</span><span style="color: #008080;">150</span>     <span style="color: #0000ff;">struct</span> tm*<span style="color: #000000;">tm_now;
</span><span style="color: #008080;">151</span> 
<span style="color: #008080;">152</span>     iReadNum =<span style="color: #000000;"> read(g_inotifyFd,czBuf,BUF_SIZE);
</span><span style="color: #008080;">153</span>     <span style="color: #0000ff;">if</span>(iReadNum == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">154</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">155</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">read failed\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">156</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">4</span><span style="color: #000000;">;
</span><span style="color: #008080;">157</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">158</span>     <span style="color: #0000ff;">else</span> <span style="color: #0000ff;">if</span>(iReadNum == <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">159</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">160</span>         <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">161</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">162</span>     time(&amp;<span style="color: #000000;">now);
</span><span style="color: #008080;">163</span>     tm_now = localtime(&amp;<span style="color: #000000;">now);
</span><span style="color: #008080;">164</span>     <span style="color: #0000ff;">char</span> *p =<span style="color: #000000;"> czBuf;
</span><span style="color: #008080;">165</span>     <span style="color: #0000ff;">while</span>(<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">166</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">167</span>         <span style="color: #0000ff;">if</span>(p &gt;= czBuf+<span style="color: #000000;">iReadNum)
</span><span style="color: #008080;">168</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">169</span>             <span style="color: #0000ff;">break</span><span style="color: #000000;">;
</span><span style="color: #008080;">170</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">171</span>         pEvent = (<span style="color: #0000ff;">struct</span> inotify_event *<span style="color: #000000;">)p;
</span><span style="color: #008080;">172</span>         <span style="color: #0000ff;">char</span> *pPath = GetPath(pEvent-&gt;<span style="color: #000000;">wd);
</span><span style="color: #008080;">173</span>         <span style="color: #0000ff;">if</span>(pPath ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">174</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">175</span>             <span style="color: #0000ff;">return</span> -<span style="color: #800080;">5</span><span style="color: #000000;">;
</span><span style="color: #008080;">176</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">177</span>         <span style="color: #0000ff;">for</span>(<span style="color: #0000ff;">int</span> index = <span style="color: #800080;">0</span>;index &lt; <span style="color: #0000ff;">sizeof</span>(g_stEventInfo)/<span style="color: #0000ff;">sizeof</span>(<span style="color: #0000ff;">struct</span> eventInfo);index++<span style="color: #000000;">)
</span><span style="color: #008080;">178</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">179</span>             <span style="color: #0000ff;">if</span>(pEvent-&gt;mask &amp; (g_stEventInfo[index].<span style="color: #0000ff;">event</span><span style="color: #000000;">))
</span><span style="color: #008080;">180</span> <span style="color: #000000;">            {
</span><span style="color: #008080;">181</span>                 fprintf(g_fp,<span style="color: #800000;">"</span><span style="color: #800000;">path : %-30s\t   event : %-30s\t   file name : %-30s\t   time : %s</span><span style="color: #800000;">"</span>,pPath,g_stEventInfo[index].explain,pEvent-&gt;<span style="color: #000000;">name,asctime(tm_now));
</span><span style="color: #008080;">182</span>                 <span style="color: #0000ff;">break</span><span style="color: #000000;">;
</span><span style="color: #008080;">183</span> <span style="color: #000000;">            }
</span><span style="color: #008080;">184</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">185</span> <span style="color: #000000;">        fflush(g_fp);
</span><span style="color: #008080;">186</span>         p += (<span style="color: #0000ff;">sizeof</span>(<span style="color: #0000ff;">struct</span> inotify_event) + pEvent-&gt;<span style="color: #000000;">len);
</span><span style="color: #008080;">187</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">188</span> 
<span style="color: #008080;">189</span>     <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">190</span> <span style="color: #000000;">}
</span><span style="color: #008080;">191</span> 
<span style="color: #008080;">192</span> <span style="color: #0000ff;">int</span><span style="color: #000000;"> GetFileLine()
</span><span style="color: #008080;">193</span> <span style="color: #000000;">{
</span><span style="color: #008080;">194</span>     <span style="color: #0000ff;">char</span> *<span style="color: #000000;">p;
</span><span style="color: #008080;">195</span>     <span style="color: #0000ff;">char</span> czBuf[<span style="color: #800080;">200</span>] = {<span style="color: #800080;">0</span><span style="color: #000000;">};
</span><span style="color: #008080;">196</span>     <span style="color: #0000ff;">int</span> line = <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">197</span>     <span style="color: #0000ff;">while</span>(<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">198</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">199</span>         p = fgets(czBuf,<span style="color: #800080;">200</span><span style="color: #000000;">,g_fp);
</span><span style="color: #008080;">200</span>         <span style="color: #0000ff;">if</span>(p ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">201</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">202</span>             <span style="color: #0000ff;">return</span><span style="color: #000000;"> line;
</span><span style="color: #008080;">203</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">204</span>         line++<span style="color: #000000;">;
</span><span style="color: #008080;">205</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">206</span>     <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">207</span> <span style="color: #000000;">}
</span><span style="color: #008080;">208</span> 
<span style="color: #008080;">209</span> <span style="color: #0000ff;">int</span> freeSpace(<span style="color: #0000ff;">struct</span> pathInfo **<span style="color: #000000;">pInfo)
</span><span style="color: #008080;">210</span> <span style="color: #000000;">{
</span><span style="color: #008080;">211</span>     <span style="color: #0000ff;">if</span>(*pInfo ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">212</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">213</span>         <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">214</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">215</span>     <span style="color: #0000ff;">else</span>
<span style="color: #008080;">216</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">217</span>         <span style="color: #0000ff;">if</span>((*pInfo)-&gt;pNext ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">218</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">219</span>             <span style="color: #0000ff;">if</span>(inotify_rm_watch(g_inotifyFd,(*pInfo)-&gt;wd) == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">220</span> <span style="color: #000000;">            {
</span><span style="color: #008080;">221</span>                 printf(<span style="color: #800000;">"</span><span style="color: #800000;">notify_rm_watch error\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">222</span> <span style="color: #000000;">            }
</span><span style="color: #008080;">223</span>             <span style="color: #0000ff;">free</span>((*<span style="color: #000000;">pInfo));
</span><span style="color: #008080;">224</span>             *pInfo =<span style="color: #000000;"> NULL;
</span><span style="color: #008080;">225</span>             <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">226</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">227</span>         <span style="color: #0000ff;">else</span>
<span style="color: #008080;">228</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">229</span>             freeSpace(&amp;((*pInfo)-&gt;<span style="color: #000000;">pNext));
</span><span style="color: #008080;">230</span>             <span style="color: #0000ff;">if</span>(inotify_rm_watch(g_inotifyFd,(*pInfo)-&gt;wd) == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">231</span> <span style="color: #000000;">            {
</span><span style="color: #008080;">232</span>                 printf(<span style="color: #800000;">"</span><span style="color: #800000;">notify_rm_watch error\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">233</span> <span style="color: #000000;">            }
</span><span style="color: #008080;">234</span>             <span style="color: #0000ff;">free</span>(*<span style="color: #000000;">pInfo);
</span><span style="color: #008080;">235</span>             *pInfo =<span style="color: #000000;"> NULL;
</span><span style="color: #008080;">236</span>             <span style="color: #0000ff;">return</span> <span style="color: #800080;">0</span><span style="color: #000000;">;
</span><span style="color: #008080;">237</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">238</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">239</span>     <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">240</span> <span style="color: #000000;">}
</span><span style="color: #008080;">241</span> 
<span style="color: #008080;">242</span> 
<span style="color: #008080;">243</span> <span style="color: #0000ff;">void</span> catch_signal(<span style="color: #0000ff;">int</span><span style="color: #000000;"> sig)
</span><span style="color: #008080;">244</span> <span style="color: #000000;">{
</span><span style="color: #008080;">245</span>     <span style="color: #0000ff;">if</span>(sig ==<span style="color: #000000;"> SIGINT)
</span><span style="color: #008080;">246</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">247</span>         <span style="color: #0000ff;">int</span> ret = freeSpace(&amp;<span style="color: #000000;">g_list);
</span><span style="color: #008080;">248</span>         <span style="color: #0000ff;">if</span>(ret &lt; <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">249</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">250</span>             printf(<span style="color: #800000;">"</span><span style="color: #800000;">free space failed\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">251</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">252</span> <span style="color: #000000;">        close(g_inotifyFd);
</span><span style="color: #008080;">253</span> <span style="color: #000000;">        fclose(g_fp);
</span><span style="color: #008080;">254</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">255</span> <span style="color: #000000;">}
</span><span style="color: #008080;">256</span> 
<span style="color: #008080;">257</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc,<span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">258</span> <span style="color: #000000;">{
</span><span style="color: #008080;">259</span>     <span style="color: #0000ff;">if</span>(argc &lt; <span style="color: #800080;">2</span><span style="color: #000000;">)
</span><span style="color: #008080;">260</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">261</span>         printf(<span style="color: #800000;">"</span><span style="color: #800000;">please input file/dir name:./a.ot File.txt\n</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">262</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">1</span><span style="color: #000000;">;
</span><span style="color: #008080;">263</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">264</span> 
<span style="color: #008080;">265</span>     g_inotifyFd =<span style="color: #000000;"> inotify_init();
</span><span style="color: #008080;">266</span>     <span style="color: #0000ff;">if</span>(g_inotifyFd == -<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">267</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">268</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">inotify_init</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">269</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">2</span><span style="color: #000000;">;
</span><span style="color: #008080;">270</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">271</span>     <span style="color: #0000ff;">int</span> ret = watch_object(argv[<span style="color: #800080;">1</span><span style="color: #000000;">]);
</span><span style="color: #008080;">272</span>     <span style="color: #0000ff;">if</span>(ret != <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">273</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">274</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">3</span><span style="color: #000000;">;
</span><span style="color: #008080;">275</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">276</span> 
<span style="color: #008080;">277</span>     g_fp = fopen(<span style="color: #800000;">"</span><span style="color: #800000;">/home/gc/Record_Jyb</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">a+</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">278</span>     <span style="color: #0000ff;">if</span>(g_fp ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">279</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">280</span>         perror(<span style="color: #800000;">"</span><span style="color: #800000;">fopen</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">281</span>         <span style="color: #0000ff;">return</span> -<span style="color: #800080;">4</span><span style="color: #000000;">;
</span><span style="color: #008080;">282</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">283</span> 
<span style="color: #008080;">284</span>     <span style="color: #0000ff;">struct</span><span style="color: #000000;"> sigaction stSign;
</span><span style="color: #008080;">285</span>     stSign.sa_handler =<span style="color: #000000;"> catch_signal;
</span><span style="color: #008080;">286</span>     sigemptyset(&amp;<span style="color: #000000;">stSign.sa_mask);
</span><span style="color: #008080;">287</span>     stSign.sa_flags =<span style="color: #000000;"> SA_RESETHAND;
</span><span style="color: #008080;">288</span>     sigaction(SIGINT,&amp;stSign,<span style="color: #800080;">0</span><span style="color: #000000;">);
</span><span style="color: #008080;">289</span> 
<span style="color: #008080;">290</span>     <span style="color: #0000ff;">while</span>(<span style="color: #800080;">1</span><span style="color: #000000;">)
</span><span style="color: #008080;">291</span> <span style="color: #000000;">    {
</span><span style="color: #008080;">292</span>         <span style="color: #0000ff;">if</span>(GetFileLine() &gt;= <span style="color: #800080;">1000</span><span style="color: #000000;">)
</span><span style="color: #008080;">293</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">294</span> <span style="color: #000000;">            fclose(g_fp);
</span><span style="color: #008080;">295</span>             g_fp = fopen(<span style="color: #800000;">"</span><span style="color: #800000;">/home/gc/Record_Jyb</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">w</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">296</span>             <span style="color: #0000ff;">if</span>(g_fp ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">297</span> <span style="color: #000000;">            {
</span><span style="color: #008080;">298</span>                 perror(<span style="color: #800000;">"</span><span style="color: #800000;">fopen</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">299</span>                 <span style="color: #0000ff;">return</span> -<span style="color: #800080;">5</span><span style="color: #000000;">;
</span><span style="color: #008080;">300</span> <span style="color: #000000;">            }
</span><span style="color: #008080;">301</span> <span style="color: #000000;">            fclose(g_fp);
</span><span style="color: #008080;">302</span>             g_fp = fopen(<span style="color: #800000;">"</span><span style="color: #800000;">/home/gc/Record_Jyb</span><span style="color: #800000;">"</span>,<span style="color: #800000;">"</span><span style="color: #800000;">a+</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">303</span>             <span style="color: #0000ff;">if</span>(g_fp ==<span style="color: #000000;"> NULL)
</span><span style="color: #008080;">304</span> <span style="color: #000000;">            {
</span><span style="color: #008080;">305</span>                 perror(<span style="color: #800000;">"</span><span style="color: #800000;">fopen</span><span style="color: #800000;">"</span><span style="color: #000000;">);
</span><span style="color: #008080;">306</span>                 <span style="color: #0000ff;">return</span> -<span style="color: #800080;">6</span><span style="color: #000000;">;
</span><span style="color: #008080;">307</span> <span style="color: #000000;">            }
</span><span style="color: #008080;">308</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">309</span>         ret =<span style="color: #000000;"> recordEvent();
</span><span style="color: #008080;">310</span>         <span style="color: #0000ff;">if</span>(ret &lt; <span style="color: #800080;">0</span><span style="color: #000000;">)
</span><span style="color: #008080;">311</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">312</span>             <span style="color: #0000ff;">return</span> -<span style="color: #800080;">5</span><span style="color: #000000;">;
</span><span style="color: #008080;">313</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">314</span>         sleep(<span style="color: #800080;">10</span><span style="color: #000000;">);
</span><span style="color: #008080;">315</span> <span style="color: #000000;">    }
</span><span style="color: #008080;">316</span> }</pre>
</div>
<p>&nbsp;</p>
<p>总的来说，虽然这只是一个很简单的功能，但还是为自己的一小步提升而高兴，在此分享给各位一起进步。</p>
<p>单单代码逻辑可修改的地方就有很多，还望大家见谅。</p>
<p>&nbsp;</p>