---
title: frps+fail2ban联合使用，防止frp ssh被滥用
tags: Linux
---

在服务端（frps 所在的公网服务器）安装 Fail2ban 可以在攻击流量到达你的内网主机之前，直接在公网网关处将其拦截。

以下是完整的安装与策略配置步骤：

---

## 第一步：安装 Fail2ban

在你的服务端（Ubuntu/Debian 系统）执行：

```bash
sudo apt update
sudo apt install fail2ban -y
```

安装完成后，服务会自动启动。你可以用 `systemctl status fail2ban` 查看状态。

---

## 第二步：创建 frps 专用过滤器 (Filter)

我们需要告诉 Fail2ban 如何在日志里识别“攻击行为”。

1. 创建规则文件：  
```bash
sudo nano /etc/fail2ban/filter.d/frps.conf
```


2. 粘贴以下内容（针对你提供的日志格式优化）：
```ini
[Definition]
# 直接匹配 get a user connection 后的 IP
failregex = get a user connection \[<HOST>:.*\]
ignoreregex =

# 显式指定 FRPS 自己的时间格式（跳过系统 syslog 的时间）
datepattern = %%Y-%%m-%%d %%H:%%M:%%S

```



---

## 第三步：配置监狱策略 (Jail)

这一步定义封禁的逻辑：错几次、封多久。

1. 创建配置文件：
```bash
sudo nano /etc/fail2ban/jail.d/frps.local

```


2. 粘贴以下内容：
```ini
[frps]
enabled = true
filter = frps
# 再次尝试读取 syslog
logpath = /var/log/syslog
# 强制使用 polling 模式，这对某些系统更稳
backend = polling

action = iptables-allports[name=frps]

# 攻击频率极高，门槛再调低一点
findtime = 1800
maxretry = 10
bantime = 86400

# 建议加上你自己当前的 IP 免得把自己锁死
# ignoreip = 127.0.0.1/8 你的公网IP

```



---

## 第四步：激活并验证

1. **清理并重启：**
```bash
# 1. 停止服务
sudo systemctl stop fail2ban

# 2. 清理 Fail2ban 的临时数据库（这会让它重新开始扫描）
sudo rm /var/lib/fail2ban/fail2ban.sqlite3

# 3. 启动服务
sudo systemctl start fail2ban

# 4. 观察 syslog 确保它在读文件
sudo tail -f /var/log/fail2ban.log
```


2. **查看封禁状态：**
过几分钟后，你可以查看 `frps` 这个“监狱”里抓到了多少人：
```bash
sudo fail2ban-client status frps

```


3. **手动解封（万一误伤自己）：**
```bash
sudo fail2ban-client set frps unbanip [你的IP]

```
4. **实时追踪日志：**
```bash
sudo journalctl -u frps -f

```

5. **查看iptables封禁的ip：**
```bash
sudo iptables -L -n | grep REJECT

```