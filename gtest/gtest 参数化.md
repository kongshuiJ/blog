<p><span style="font-size: 18pt; color: #ff0000;">&nbsp;前言：</span></p>
<p>　　在测试用例中，我们时常需要传给被测函数不同的值，gtest为我们提供了简便的方法，可以使我们能够灵活的进行参数化测试。</p>
<p><span style="color: #ff0000; font-size: 18pt;">　　</span></p>
<p><span style="color: #ff0000; font-size: 18pt;">步骤：</span></p>
<p>　　1.创建一个类，继承t<tt>esting::TestWithParam&lt;T&gt;</tt>，T是你需要参数化的参数类型，比如参数类型为int</p>
<p>　　2.&nbsp;使用新宏TEST_P替代TEST。在TEST_P宏里，可以使用GetParam()获取当前的参数的具体值。</p>
<p>　　3.&nbsp;使用INSTANTIATE_TEST_CASE_P宏来输入测试参数。</p>
<p>　　　　参数解释和表格直接贴上某个大佬的解释：</p>
<p>　　　　第一个参数是测试案例的前缀，可以任意取。&nbsp;</p>
<p>　　　　第二个参数是测试案例的名称，需要和之前定义的参数化的类的名称相同。</p>
<p>　　　　第三个参数是可以理解为参数生成器，上面的例子使用test::Values表示使用括号内的参数。Google提供了一系列的参数生成的函数：</p>
<table style="height: 205px; width: 1558px;" border="0">
<tbody>
<tr>
<td>Range(begin, end[, step])</td>
<td>范围在begin~end之间，步长为step，不包括end</td>
</tr>
<tr>
<td>Values(v1, v2, ..., vN)</td>
<td>v1,v2到vN的值</td>
</tr>
<tr>
<td><tt>ValuesIn(container)</tt>&nbsp;and&nbsp;<tt>ValuesIn(begin, end)</tt></td>
<td>从一个C类型的数组或是STL容器，或是迭代器中取值</td>
</tr>
<tr>
<td>Bool()</td>
<td>取<tt>false 和 true 两个值</tt></td>
</tr>
<tr>
<td>Combine(g1, g2, ..., gN)</td>
<td>
<p>这个比较强悍，它将g1,g2,...gN进行排列组合，g1,g2,...gN本身是一个参数生成器，每次分别从g1,g2,..gN中各取出一个值，组合成一个元组(Tuple)作为一个参数。</p>
<p>说明：这个功能只在提供了<tt>&lt;tr1/tuple&gt;头的系统中有效。gtest会自动去判断是否支持tr/tuple，如果你的系统确实支持，而</tt>gtest判断错误的话，你可以重新定义宏<tt>GTEST_HAS_TR1_TUPLE=1</tt></p>
</td>
</tr>
</tbody>
</table>
<p><span style="font-size: 18pt; color: #ff0000;">示例：</span></p>
<p>　　<span style="color: #ff0000;">示例1：最简单的Values()的使用。</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test3.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 03:15:54
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 03:15:54
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> 
<span style="color: #008080;">13</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">16</span> 
<span style="color: #008080;">17</span> <span style="color: #0000ff;">class</span> myTest : <span style="color: #0000ff;">public</span> testing::TestWithParam&lt;<span style="color: #0000ff;">int</span>&gt;
<span style="color: #008080;">18</span> <span style="color: #000000;">{
</span><span style="color: #008080;">19</span> 
<span style="color: #008080;">20</span> <span style="color: #000000;">};
</span><span style="color: #008080;">21</span> 
<span style="color: #008080;">22</span> <span style="color: #000000;">TEST_P(myTest, test0)
</span><span style="color: #008080;">23</span> <span style="color: #000000;">{
</span><span style="color: #008080;">24</span>     <span style="color: #0000ff;">int</span> num =<span style="color: #000000;"> GetParam();
</span><span style="color: #008080;">25</span>     cout &lt;&lt; num &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">26</span> <span style="color: #000000;">}
</span><span style="color: #008080;">27</span> 
<span style="color: #008080;">28</span> INSTANTIATE_TEST_CASE_P(ttt, myTest, testing::Values(<span style="color: #800080;">1</span>, <span style="color: #800080;">2</span>, <span style="color: #800080;">3</span>, <span style="color: #800080;">4</span><span style="color: #000000;">));
</span><span style="color: #008080;">29</span> 
<span style="color: #008080;">30</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">31</span> <span style="color: #000000;">{
</span><span style="color: #008080;">32</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">33</span> 
<span style="color: #008080;">34</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">35</span> }</pre>
</div>
<p>&nbsp;</p>
<p>　　编译及结果：</p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021184716512-627728380.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000;">　　示例2：Combine(g1, g2, ..., gN)的使用</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test1.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 02:40:25
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 02:40:25
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">13</span> 
<span style="color: #008080;">14</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">15</span> 
<span style="color: #008080;">16</span> <span style="color: #0000ff;">class</span> funcTest : <span style="color: #0000ff;">public</span> testing::TestWithParam&lt; tr1::tuple&lt;<span style="color: #0000ff;">int</span> , <span style="color: #0000ff;">int</span>&gt; &gt;
<span style="color: #008080;">17</span> <span style="color: #000000;">{
</span><span style="color: #008080;">18</span> <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">19</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">20</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">21</span>                 <span style="color: #008000;">//</span><span style="color: #008000;"> 如果此时参数是&lt;1, 2&gt;
</span><span style="color: #008080;">22</span>                 <span style="color: #008000;">//</span><span style="color: #008000;"> 那么 a = 1
</span><span style="color: #008080;">23</span>                 <span style="color: #008000;">//</span><span style="color: #008000;">         b = 2</span>
<span style="color: #008080;">24</span>                 a = tr1::<span style="color: #0000ff;">get</span>&lt;<span style="color: #800080;">0</span>&gt;<span style="color: #000000;">(GetParam());
</span><span style="color: #008080;">25</span>                 b = tr1::<span style="color: #0000ff;">get</span>&lt;<span style="color: #800080;">1</span>&gt;<span style="color: #000000;">(GetParam());
</span><span style="color: #008080;">26</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">27</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">28</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">29</span> 
<span style="color: #008080;">30</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">31</span>         <span style="color: #0000ff;">int</span><span style="color: #000000;"> a;
</span><span style="color: #008080;">32</span>         <span style="color: #0000ff;">int</span><span style="color: #000000;"> b;
</span><span style="color: #008080;">33</span> <span style="color: #000000;">};
</span><span style="color: #008080;">34</span> 
<span style="color: #008080;">35</span> <span style="color: #0000ff;">int</span> func(<span style="color: #0000ff;">int</span> a, <span style="color: #0000ff;">int</span><span style="color: #000000;"> b)
</span><span style="color: #008080;">36</span> <span style="color: #000000;">{
</span><span style="color: #008080;">37</span>     <span style="color: #0000ff;">return</span> a +<span style="color: #000000;"> b;
</span><span style="color: #008080;">38</span> <span style="color: #000000;">}
</span><span style="color: #008080;">39</span> 
<span style="color: #008080;">40</span> <span style="color: #000000;">TEST_P(funcTest, test0)
</span><span style="color: #008080;">41</span> <span style="color: #000000;">{
</span><span style="color: #008080;">42</span>         cout &lt;&lt; a &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;"> + </span><span style="color: #800000;">"</span> &lt;&lt; b &lt;&lt;<span style="color: #800000;">"</span><span style="color: #800000;"> = </span><span style="color: #800000;">"</span> &lt;&lt; func(a , b) &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">43</span> <span style="color: #000000;">}
</span><span style="color: #008080;">44</span> 
<span style="color: #008080;">45</span> <span style="color: #008000;">/*</span><span style="color: #008000;">INSTANTIATE_TEST_CASE_P(MyFuncTest,
</span><span style="color: #008080;">46</span> <span style="color: #008000;">    funcTest,
</span><span style="color: #008080;">47</span> <span style="color: #008000;">    Combine(testing::Values(1, 2, 3), testing::Bool()));</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">48</span> 
<span style="color: #008080;">49</span> <span style="color: #000000;">INSTANTIATE_TEST_CASE_P(MyFuncTest,
</span><span style="color: #008080;">50</span> <span style="color: #000000;">    funcTest,
</span><span style="color: #008080;">51</span>     testing::Combine(testing::Values(<span style="color: #800080;">1</span>, <span style="color: #800080;">2</span>, <span style="color: #800080;">3</span>), testing::Values(<span style="color: #800080;">1</span>, <span style="color: #800080;">2</span><span style="color: #000000;">)));
</span><span style="color: #008080;">52</span> 
<span style="color: #008080;">53</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">54</span> <span style="color: #000000;">{
</span><span style="color: #008080;">55</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">56</span> 
<span style="color: #008080;">57</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">58</span> }</pre>
</div>
<p>&nbsp;</p>
<p>　　编译及结果：</p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021185934614-2005823986.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000;">　　示例3：传参结构体</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test2.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 02:54:46
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 02:54:46
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">13</span> 
<span style="color: #008080;">14</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">15</span> 
<span style="color: #008080;">16</span> <span style="color: #0000ff;">using</span><span style="color: #000000;"> ::testing::TestWithParam;
</span><span style="color: #008080;">17</span> <span style="color: #0000ff;">using</span><span style="color: #000000;"> ::testing::Bool;
</span><span style="color: #008080;">18</span> <span style="color: #0000ff;">using</span><span style="color: #000000;"> ::testing::Values;
</span><span style="color: #008080;">19</span> 
<span style="color: #008080;">20</span> <span style="color: #0000ff;">struct</span><span style="color: #000000;"> T
</span><span style="color: #008080;">21</span> <span style="color: #000000;">{
</span><span style="color: #008080;">22</span>     <span style="color: #0000ff;">int</span><span style="color: #000000;"> a;
</span><span style="color: #008080;">23</span>     <span style="color: #0000ff;">double</span><span style="color: #000000;"> b;
</span><span style="color: #008080;">24</span>     <span style="color: #0000ff;">string</span><span style="color: #000000;"> c;
</span><span style="color: #008080;">25</span> <span style="color: #000000;">};
</span><span style="color: #008080;">26</span> 
<span style="color: #008080;">27</span> <span style="color: #0000ff;">class</span> MyTest : <span style="color: #0000ff;">public</span> TestWithParam&lt;<span style="color: #0000ff;">struct</span> T&gt;
<span style="color: #008080;">28</span> <span style="color: #000000;">{
</span><span style="color: #008080;">29</span>     <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">30</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">31</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">32</span>             t1.a =<span style="color: #000000;"> GetParam().a;
</span><span style="color: #008080;">33</span>             t1.b =<span style="color: #000000;"> GetParam().b;
</span><span style="color: #008080;">34</span>             t1.c =<span style="color: #000000;"> GetParam().c;
</span><span style="color: #008080;">35</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">36</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">37</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">38</span> 
<span style="color: #008080;">39</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">40</span> 
<span style="color: #008080;">41</span>         <span style="color: #0000ff;">struct</span><span style="color: #000000;"> T t1;
</span><span style="color: #008080;">42</span> <span style="color: #000000;">};
</span><span style="color: #008080;">43</span> 
<span style="color: #008080;">44</span> <span style="color: #000000;">TEST_P(MyTest, test0)
</span><span style="color: #008080;">45</span> <span style="color: #000000;">{
</span><span style="color: #008080;">46</span>     cout &lt;&lt; t1.a&lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;"> - </span><span style="color: #800000;">"</span> &lt;&lt; t1.b &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;"> - </span><span style="color: #800000;">"</span> &lt;&lt; t1.c &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">47</span> <span style="color: #000000;">}
</span><span style="color: #008080;">48</span> 
<span style="color: #008080;">49</span> INSTANTIATE_TEST_CASE_P(ttt1, MyTest, Values(T{<span style="color: #800080;">1</span>, <span style="color: #800080;">2.2</span> ,<span style="color: #800000;">"</span><span style="color: #800000;">cc</span><span style="color: #800000;">"</span>}, T{<span style="color: #800080;">2</span>, <span style="color: #800080;">3.3</span> ,<span style="color: #800000;">"</span><span style="color: #800000;">ee</span><span style="color: #800000;">"</span><span style="color: #000000;">}));
</span><span style="color: #008080;">50</span> 
<span style="color: #008080;">51</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">52</span> <span style="color: #000000;">{
</span><span style="color: #008080;">53</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">54</span> 
<span style="color: #008080;">55</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">56</span> }</pre>
</div>
<p>&nbsp;</p>
<p>　　编译及结果：</p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021190855770-1168679523.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000; font-size: 18pt;">总结：</span></p>
<p>　　gtest的参数化功能真的是很方便，可以让我们以更少的代码，写出更强大的测试模块。</p>
<p>&nbsp;</p>