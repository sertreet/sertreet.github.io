---
title: Nginx多站点配置certbot自动申请证书
tags: Linux
---
## 1.创建站点目录  
首先，确保你已经在服务器上创建了用于存放网站文件的目录。  
`sudo mkdir -p /var/www/rram_top`  
`sudo mkdir -p /var/www/memristor_cn`  
然后，设置这些目录的权限，确保 Nginx 可以读取和写入：  
`sudo chown -R $USER:$USER /var/www/rram_top`  
`sudo chown -R $USER:$USER /var/www/memristor_cn`  
## 2.创建和编辑 Nginx 配置文件  
Nginx 的站点配置文件通常位于 /etc/nginx/sites-available/ 目录下。你可以为每个域名创建一个单独的配置文件，或者将它们都放在一个文件中。  
为 rram.top 和 www.rram.top 创建配置文件  
创建一个名为 rram_top 的配置文件：  
`sudo vim /etc/nginx/sites-available/rram_top`  
在文件中添加以下内容：  
`server {
    listen 80;
    server_name rram.top www.rram.top;
    root /var/www/rram_top;
    index index.html index.htm index.nginx-debian.html;
    location / {
        try_files $uri $uri/ =404;
    }
}`
为 memristor.cn 和 www.memristor.cn 创建配置文件  
同样地，创建一个名为 memristor_cn 的配置文件：  
`sudo nano /etc/nginx/sites-available/memristor_cn`  
在文件中添加以下内容：  
`server {
    listen 80;
    server_name memristor.cn www.memristor.cn;
    root /var/www/memristor_cn;
    index index.html index.htm index.nginx-debian.html;
    location / {
        try_files $uri $uri/ =404;
    }
}`   
## 3.启用站点配置  
将配置文件从 sites-available 目录链接到 sites-enabled 目录，以启用这些站点：  
`sudo ln -s /etc/nginx/sites-available/rram_top /etc/nginx/sites-enabled/`  
`sudo ln -s /etc/nginx/sites-available/memristor_cn /etc/nginx/sites-enabled/`  
## 4.检查 Nginx 配置  
`sudo nginx -t`  
如果没有错误，重启 Nginx：  
`sudo systemctl reload nginx`  
## 5.安装 Certbot 和 Nginx 插件  
如果尚未安装 Certbot 和 Nginx 插件，请先执行以下命令：  
`sudo apt-get update`  
`sudo apt-get install certbot python3-certbot-nginx`  
## 6.使用 Certbot 申请 SSL 证书  
使用 Certbot 为你的域名申请 SSL 证书。Certbot 会自动为每个域名生成证书，并更新 Nginx 配置文件以启用 HTTPS。  
为 rram.top 和 www.rram.top 申请证书：  
`sudo certbot --nginx -d rram.top -d www.rram.top`  
为 memristor.cn 和 www.memristor.cn 申请证书：  
`sudo certbot --nginx -d memristor.cn -d www.memristor.cn`  
Certbot 会自动修改 Nginx 配置文件，以添加 SSL 配置并重启 Nginx。  
## 7.验证配置  
确保你的站点能够通过 HTTPS 正常访问。你可以通过浏览器访问 https://rram.top 和 https://memristor.cn 进行验证。  
## 8.自动续签  
Certbot 会自动管理证书续签。你可以通过以下命令手动测试续签：  
`sudo certbot renew --dry-run`  
这样配置完成后，你的网站就可以通过 HTTPS 安全访问，并且 Certbot 会自动管理证书的续签。  