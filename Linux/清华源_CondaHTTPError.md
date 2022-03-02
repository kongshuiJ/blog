## 问题

嫌官网源安装**jupyter notebook**太慢，所以尝试修改为清华源，但每次在**Solving environment**的时候就报错如下：
![](https://img2022.cnblogs.com/blog/1347181/202203/1347181-20220302114837110-1423515473.png)

## 解决方法，修改conda配置信息：

**vim ~/.condarc**
直接把下方内容替换掉**~/.condarc**中的内容，然后保存就可以了。
```
channels:
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/Paddle/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/fastai/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/pytorch/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/bioconda/
show_channel_urls: true
ssl_verify: false
```
