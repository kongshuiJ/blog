<p>&nbsp;</p>
<p><span style="font-size: 18pt; color: #ff0000;">前言：</span></p>
<p><span style="color: #888888;">　　1.首先说明gtest中事件的结构层次：</span></p>
<p>　　<img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021164809916-1521429505.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #888888;">　　测试程序：一个测试程序只有一个main函数，也可以说是一个可执行程序是一个测试程序。该级别的事件机制会在程序的开始和结束执行。</span></p>
<p><span style="color: #888888;">　　测试套件：代表一个测试用例的集合体，该级别的事件机制会在整体的测试案例开始可结束执行。</span></p>
<p><span style="color: #888888;">　　测试用例：该级别的事件机制会在每个测试用例开始和结束都执行。</span></p>
<p>&nbsp;</p>
<p>　　<span style="color: #ff0000;">gtest中的事件机制是指在测试前和测试后提供给用户自行添加操作的机制，而且次机制也可用让同一测试套件下的测试用例共享数据。</span></p>
<p>　　</p>
<p><span style="font-size: 18pt; color: #ff0000;">一、全局的事件机制(针对整个测试程序)</span></p>
<p><span style="color: #888888;">　　实现全局的事件机制，需要创建一个自己的类，然后继承testing::Environment类，然后分别实现成员函数SetUp()和TearDown()，同时在main函数内进行调用，即"testing::AddGlobalTestEnvironment(new MyEnvironment);"，通过调用函数我们可以添加多个全局的事件机制。<br /></span></p>
<p><span style="color: #888888;">　　SetUp()函数是在所有测试开始前执行。</span></p>
<p><span style="color: #888888;">　　TearDown()函数是在所有测试结束后执行。</span></p>
<p><span style="color: #888888;">　　示例：　　</span></p>
<p>&nbsp;</p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 00:42:34
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 00:42:34
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> 
<span style="color: #008080;">13</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">16</span> 
<span style="color: #008080;">17</span> <span style="color: #0000ff;">class</span> MyEnvironment0 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Environment
</span><span style="color: #008080;">18</span> <span style="color: #000000;">{
</span><span style="color: #008080;">19</span>     <span style="color: #0000ff;">public</span><span style="color: #000000;">:
</span><span style="color: #008080;">20</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">21</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">22</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">Global event0 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">23</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">24</span> 
<span style="color: #008080;">25</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">26</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">27</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">Global event0 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">28</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">29</span> <span style="color: #000000;">};
</span><span style="color: #008080;">30</span> 
<span style="color: #008080;">31</span> <span style="color: #0000ff;">class</span> MyEnvironment1 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Environment
</span><span style="color: #008080;">32</span> <span style="color: #000000;">{
</span><span style="color: #008080;">33</span>     <span style="color: #0000ff;">public</span><span style="color: #000000;">:
</span><span style="color: #008080;">34</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">35</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">36</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">Global event1 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">37</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">38</span> 
<span style="color: #008080;">39</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">40</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">41</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">Global event1 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">42</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">43</span> <span style="color: #000000;">};
</span><span style="color: #008080;">44</span> 
<span style="color: #008080;">45</span> <span style="color: #000000;">TEST(GlobalTest0, test0)
</span><span style="color: #008080;">46</span> <span style="color: #000000;">{
</span><span style="color: #008080;">47</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">48</span> <span style="color: #000000;">};
</span><span style="color: #008080;">49</span> 
<span style="color: #008080;">50</span> 
<span style="color: #008080;">51</span> <span style="color: #000000;">TEST(GlobalTest0, test1)
</span><span style="color: #008080;">52</span> <span style="color: #000000;">{
</span><span style="color: #008080;">53</span>     EXPECT_EQ(<span style="color: #800080;">2</span>, <span style="color: #800080;">2</span><span style="color: #000000;">);
</span><span style="color: #008080;">54</span> <span style="color: #000000;">};
</span><span style="color: #008080;">55</span> 
<span style="color: #008080;">56</span> <span style="color: #000000;">TEST(GlobalTest1, test0)
</span><span style="color: #008080;">57</span> <span style="color: #000000;">{
</span><span style="color: #008080;">58</span>     EXPECT_EQ(<span style="color: #800080;">3</span>, <span style="color: #800080;">3</span><span style="color: #000000;">);
</span><span style="color: #008080;">59</span> <span style="color: #000000;">};
</span><span style="color: #008080;">60</span> 
<span style="color: #008080;">61</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">62</span> <span style="color: #000000;">{
</span><span style="color: #008080;">63</span>     testing::AddGlobalTestEnvironment(<span style="color: #0000ff;">new</span><span style="color: #000000;"> MyEnvironment0);
</span><span style="color: #008080;">64</span>     testing::AddGlobalTestEnvironment(<span style="color: #0000ff;">new</span><span style="color: #000000;"> MyEnvironment1);
</span><span style="color: #008080;">65</span> 
<span style="color: #008080;">66</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">67</span> 
<span style="color: #008080;">68</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">69</span> }</pre>
</div>
<p>&nbsp;</p>
<p><span style="color: #888888;">　　编译命令及结果：</span></p>
<p><span style="color: #000000;"><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021155511597-579740797.png" alt="" /></span></p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><span style="font-size: 18pt; color: #ff0000;">二、局部的事件机制(针对一个个测试套件)</span></p>
<p><span style="color: #888888;">　　测试套件的事件机制我们同样需要去创建一个类，继承testing::Test，实现两个静态函数SetUpTestCase()和TearDownTestCase()，测试套件的事件机制不需要像全局事件机制一样在main注册，而是需要将我们平时使用的TEST宏改为TEST_F宏。</span></p>
<p><span style="color: #888888;">　　SetUpTestCase()函数是在测试套件第一个测试用例开始前执行。</span></p>
<p><span style="color: #888888;">　　TearDownTestCase()函数是在测试套件最后一个测试用例结束后执行。</span></p>
<p><span style="color: #888888;">&nbsp;　　需要注意TEST_F的第一个参数使我们创建的类名，也就是当前测试套件的名称。</span></p>
<p><span style="color: #888888;">　　示例：</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 01:05:17
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 01:05:17
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> 
<span style="color: #008080;">13</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">16</span> 
<span style="color: #008080;">17</span> <span style="color: #0000ff;">class</span> MyTestSuite0 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Test
</span><span style="color: #008080;">18</span> <span style="color: #000000;">{
</span><span style="color: #008080;">19</span>     <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">20</span>         <span style="color: #0000ff;">static</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUpTestSuite()
</span><span style="color: #008080;">21</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">22</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestSuite event0 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">23</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">24</span> 
<span style="color: #008080;">25</span>         <span style="color: #0000ff;">static</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDownTestSuite()
</span><span style="color: #008080;">26</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">27</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestSuite event0 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">28</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">29</span> <span style="color: #000000;">};
</span><span style="color: #008080;">30</span> 
<span style="color: #008080;">31</span> <span style="color: #0000ff;">class</span> MyTestSuite1 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Test
</span><span style="color: #008080;">32</span> <span style="color: #000000;">{
</span><span style="color: #008080;">33</span>     <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">34</span>         <span style="color: #0000ff;">static</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUpTestSuite()
</span><span style="color: #008080;">35</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">36</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestSuite event1 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">37</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">38</span> 
<span style="color: #008080;">39</span>         <span style="color: #0000ff;">static</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDownTestSuite()
</span><span style="color: #008080;">40</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">41</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestSuite event1 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">42</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">43</span> <span style="color: #000000;">};
</span><span style="color: #008080;">44</span> 
<span style="color: #008080;">45</span> <span style="color: #000000;">TEST_F(MyTestSuite0, test0)
</span><span style="color: #008080;">46</span> <span style="color: #000000;">{
</span><span style="color: #008080;">47</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">48</span> <span style="color: #000000;">}
</span><span style="color: #008080;">49</span> 
<span style="color: #008080;">50</span> <span style="color: #000000;">TEST_F(MyTestSuite1, test0)
</span><span style="color: #008080;">51</span> <span style="color: #000000;">{
</span><span style="color: #008080;">52</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">53</span> <span style="color: #000000;">}
</span><span style="color: #008080;">54</span> 
<span style="color: #008080;">55</span> <span style="color: #000000;">TEST_F(MyTestSuite0, test1)
</span><span style="color: #008080;">56</span> <span style="color: #000000;">{
</span><span style="color: #008080;">57</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">58</span> <span style="color: #000000;">}
</span><span style="color: #008080;">59</span> 
<span style="color: #008080;">60</span> <span style="color: #000000;">TEST_F(MyTestSuite1, test1)
</span><span style="color: #008080;">61</span> <span style="color: #000000;">{
</span><span style="color: #008080;">62</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">63</span> <span style="color: #000000;">}
</span><span style="color: #008080;">64</span> 
<span style="color: #008080;">65</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">66</span> <span style="color: #000000;">{
</span><span style="color: #008080;">67</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">68</span> 
<span style="color: #008080;">69</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">70</span> }</pre>
</div>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><span style="color: #888888;">　　编译命令及结果：</span></p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021163015720-259930097.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="font-size: 18pt; color: #ff0000;">三、个体的事件机制(针对一个个测试用例)</span></p>
<p><span style="color: #888888;">　　测试用例的事件机制的创建和测试套件的基本一样，不同地方在于测试用例实现的两个函数分别是SetUp()和TearDown(),这两个函数不是静态函数了。</span></p>
<p><span style="color: #888888;">　　SetUp()函数是在一个测试用例的开始前执行。</span></p>
<p><span style="color: #888888;">　　TearDown()函数是在一个测试用例的结束后执行。</span></p>
<p><span style="color: #888888;">&nbsp;　　示例：</span></p>
<div class="cnblogs_code">
<pre><span style="color: #008080;"> 1</span> <span style="color: #008000;">/*</span><span style="color: #008000;">**********************************************
</span><span style="color: #008080;"> 2</span> 
<span style="color: #008080;"> 3</span> <span style="color: #008000;">    Filename       : test.cpp
</span><span style="color: #008080;"> 4</span> <span style="color: #008000;">    Author         :
</span><span style="color: #008080;"> 5</span> <span style="color: #008000;">    Description    :
</span><span style="color: #008080;"> 6</span> <span style="color: #008000;">    Create Data    : 2018-10-21 01:23:12
</span><span style="color: #008080;"> 7</span> <span style="color: #008000;">    Modfiy History : 2018-10-21 01:23:12
</span><span style="color: #008080;"> 8</span> 
<span style="color: #008080;"> 9</span> <span style="color: #008000;">**********************************************</span><span style="color: #008000;">*/</span>
<span style="color: #008080;">10</span> 
<span style="color: #008080;">11</span> #include &lt;iostream&gt;
<span style="color: #008080;">12</span> 
<span style="color: #008080;">13</span> #include &lt;gtest/gtest.h&gt;
<span style="color: #008080;">14</span> 
<span style="color: #008080;">15</span> <span style="color: #0000ff;">using</span> <span style="color: #0000ff;">namespace</span><span style="color: #000000;"> std;
</span><span style="color: #008080;">16</span> 
<span style="color: #008080;">17</span> <span style="color: #0000ff;">class</span> MyTestCase0 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Test
</span><span style="color: #008080;">18</span> <span style="color: #000000;">{
</span><span style="color: #008080;">19</span>     <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">20</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">21</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">22</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestCase event0 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">23</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">24</span> 
<span style="color: #008080;">25</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">26</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">27</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestCase event0 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">28</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">29</span> <span style="color: #000000;">};
</span><span style="color: #008080;">30</span> 
<span style="color: #008080;">31</span> <span style="color: #0000ff;">class</span> MyTestCase1 : <span style="color: #0000ff;">public</span><span style="color: #000000;"> testing::Test
</span><span style="color: #008080;">32</span> <span style="color: #000000;">{
</span><span style="color: #008080;">33</span>     <span style="color: #0000ff;">protected</span><span style="color: #000000;">:
</span><span style="color: #008080;">34</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> SetUp()
</span><span style="color: #008080;">35</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">36</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestCase event1 : start</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">37</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">38</span>         <span style="color: #0000ff;">virtual</span> <span style="color: #0000ff;">void</span><span style="color: #000000;"> TearDown()
</span><span style="color: #008080;">39</span> <span style="color: #000000;">        {
</span><span style="color: #008080;">40</span>             cout &lt;&lt; <span style="color: #800000;">"</span><span style="color: #800000;">TestCase event1 : end</span><span style="color: #800000;">"</span> &lt;&lt;<span style="color: #000000;"> endl;
</span><span style="color: #008080;">41</span> <span style="color: #000000;">        }
</span><span style="color: #008080;">42</span> <span style="color: #000000;">};
</span><span style="color: #008080;">43</span> 
<span style="color: #008080;">44</span> <span style="color: #000000;">TEST_F(MyTestCase0, test0)
</span><span style="color: #008080;">45</span> <span style="color: #000000;">{
</span><span style="color: #008080;">46</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">47</span> <span style="color: #000000;">}
</span><span style="color: #008080;">48</span> 
<span style="color: #008080;">49</span> <span style="color: #000000;">TEST_F(MyTestCase0, test1)
</span><span style="color: #008080;">50</span> <span style="color: #000000;">{
</span><span style="color: #008080;">51</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">52</span> <span style="color: #000000;">}
</span><span style="color: #008080;">53</span> 
<span style="color: #008080;">54</span> <span style="color: #000000;">TEST_F(MyTestCase1, test0)
</span><span style="color: #008080;">55</span> <span style="color: #000000;">{
</span><span style="color: #008080;">56</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">57</span> <span style="color: #000000;">}
</span><span style="color: #008080;">58</span> 
<span style="color: #008080;">59</span> <span style="color: #000000;">TEST_F(MyTestCase1, test1)
</span><span style="color: #008080;">60</span> <span style="color: #000000;">{
</span><span style="color: #008080;">61</span>     EXPECT_EQ(<span style="color: #800080;">1</span>, <span style="color: #800080;">1</span><span style="color: #000000;">);
</span><span style="color: #008080;">62</span> <span style="color: #000000;">}
</span><span style="color: #008080;">63</span> 
<span style="color: #008080;">64</span> <span style="color: #0000ff;">int</span> main(<span style="color: #0000ff;">int</span> argc, <span style="color: #0000ff;">char</span> *<span style="color: #000000;">argv[])
</span><span style="color: #008080;">65</span> <span style="color: #000000;">{
</span><span style="color: #008080;">66</span>     testing::InitGoogleTest(&amp;<span style="color: #000000;">argc, argv);
</span><span style="color: #008080;">67</span> 
<span style="color: #008080;">68</span>     <span style="color: #0000ff;">return</span><span style="color: #000000;"> RUN_ALL_TESTS();
</span><span style="color: #008080;">69</span> }</pre>
</div>
<p>&nbsp;</p>
<p><span style="color: #888888;">　　编译命令及结果：</span></p>
<p><img src="https://img2018.cnblogs.com/blog/1347181/201810/1347181-20181021163834098-1005714920.png" alt="" /></p>
<p>&nbsp;</p>
<p><span style="color: #ff0000; font-size: 18pt;">总结：</span></p>
<p><span style="color: #888888;">　　gtest的三种事件机制总的来说还是简单的，而且也比较灵活，通过上面的例子也能看出我们可以在事件机制中实现一些资源共享，使我们的测试更加灵活。</span></p>
<p>&nbsp;</p>
<p></p>
<p><audio controls="controls" style="display: none;"></audio></p>