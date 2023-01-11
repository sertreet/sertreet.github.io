---
layout: post
title: 一些常用的Linux命令
tags: Linux
---

Ubuntu/Debian 系统: `apt-get update -y && apt-get install curl -y`  
CentOS 系统: `yum update -y && yum install curl -y`  
安装V2Ray: `bash <(curl -s -L https://git.io/v2ray.sh)` 

VMware tools安装：  
> 1. `sudo apt install open-vm-tools`  
> 2. `sudo apt install open-vm-tools-desktop` 

重启ubuntu   

豆瓣源  
`-i https://pypi.douban.com/simple/`  
`pip install -i https://pypi.doubanio.com/simple/ --trusted-host pypi.doubanio.com pillow`  
pillow替换成要安装的软件

将本地代码全部提交：`git  add .`  
为本次提交添加注释：`git commit -m "xxxx"`  
将提交的代码推送到主分支：`git push`  
查看本地代码状态，是否有待提交的代码：`git status`  
查看git合入的记录：`git log`

新建窗口：`screen` 或 `screen -S name`  
分离会话：快键键`Ctrl+A+D`实现分离  
列出窗口列表：`screen -ls`  
恢复到窗口：`screen -r xxxx(id号)或者name`  
杀死会话窗口：`kill -9 xxxx(id号)`  
清除死去窗口：`screen -wipe`