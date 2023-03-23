---
title: 一些常用的Linux命令
tags: Linux
---

# 安装V2Ray
Ubuntu/Debian 系统: `apt-get update -y && apt-get install curl -y`  
CentOS 系统: `yum update -y && yum install curl -y`  
安装V2Ray: `bash <(curl -s -L https://git.io/v2ray.sh)`  

# VMware tools安装  
> 1. `sudo apt install open-vm-tools`  
> 2. `sudo apt install open-vm-tools-desktop`  

重启ubuntu   

# 切换Python包安装源  
豆瓣源  
`-i https://pypi.douban.com/simple/`  
`pip install -i https://pypi.doubanio.com/simple/ --trusted-host pypi.doubanio.com pillow`  
pillow替换成要安装的软件  

这个方法更简单，直接一步到位：  
`pip config set global.index-url http://mirrors.aliyun.com/pypi/simple/`  
`pip config set global.trusted-host mirrors.aliyun.com`  

# Git提交代码  
将本地代码全部提交：`git  add .`  
为本次提交添加注释：`git commit -m "xxxx"`  
将提交的代码推送到主分支：`git push`  
查看本地代码状态，是否有待提交的代码：`git status`  
查看git合入的记录：`git log`  

# screen多重视窗管理器使用方法  
新建窗口：`screen` 或 `screen -S name`  
分离会话：快键键`Ctrl+A+D`实现分离  
列出窗口列表：`screen -ls`  
恢复到窗口：`screen -r xxxx(id号)或者name`  
杀死会话窗口：`kill -9 xxxx(id号)`  
清除死去窗口：`screen -wipe`  

# 在同一个内网里使用ubuntu的jupyter notebook  
要在内网中使用Ubuntu的Jupyter Notebook，需要进行以下步骤：  
+ 安装Jupyter Notebook。您可以使用Anaconda或pip安装Jupyter Notebook。  
+ 生成配置文件。在终端中输入以下命令：`jupyter notebook --generate-config`。  
+ 设置密码。在终端中输入以下命令：`jupyter notebook password`。这将提示您输入密码并确认密码。  
+ 开启端口。在终端中输入以下命令：`jupyter notebook --ip=0.0.0.0 --port=8888`。这将开启Jupyter Notebook服务器，并允许其他计算机通过IP地址和端口号访问它。   

如果想要更好的安全性，可以使用SSL证书来加密通信。有关如何使用SSL证书的详细信息，请参见Jupyter Notebook文档。  
如果计算机上有防火墙或路由器，则可能需要配置它们以允许其他计算机访问Jupyter Notebook服务器。  

# 在ubuntu里新建用户，并切换到用户  
1. 新建用户命令`sudo adduser newuser`  
2. 系统将提示您输入新用户的密码和其他信息  
3. 切换到新用户命令`su -l newuser`  

# conda: command not found解决办法  
## 问题：  
在ubuntu中安装anaconda后，在终端输入conda info --envs检验anaconda是否安装成功，发现报错：conda: command not found 。  
## 原因分析：  
因为~/.bashrc文件没有配置好。简单来说，就是找不到ananconda的位置，就和本地电脑配置环境变量是一个道理  
## 解决方案：  
配置~/.bashrc文件  
`vim ~/.bashrc`  
然后键入 i 进行更改，找到你ananconda3的位置，在最后一行加入以下命令  
`export PATH=$PATH:/home/root/anaconda3/bin`其中这里的root表示你的账户名  
然后点击 esc键退出，输入 :wq 回车保存并退出。当然 ，也可以直接找到 .bashrc这个文件，在文件里面直接修改。  
然后添加后，激活一下  
`source ~/.bashrc`