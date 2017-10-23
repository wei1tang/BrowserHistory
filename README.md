# BrowserHistory
search the history of chrome/IE/Firefox ，C++
# 题目：第3.5题 查询上网记录
# 摘要： 
  在Windows上编写一个程序，能获取本机上网记录。把访问过的网址和时间保存到一个文本文件中。
# 关键词：  MySQL   字符串处理   Windows编程
备注：
（1）老师阅卷判分依据电子版和源程序，纸质版仅做参考和存档。
（2）电子版和源程序已经发到老师指定的邮箱。
（3）邮件附件和主题注明4个要素：“学号-姓名-题号-题目不超过15字的简短文字描述”。
（4）发送邮件时不得采用QQ超大附件或云附件或网盘等方式发送，不宜长期备份！
（5）视频不通过邮件发送！！！！视频直接拷贝到讲台老师电脑上。
（6）源文件主要拷贝完整，尤其是不要遗漏工程主目录之外的的第三方库或头文件。
（7）请删除编译过程中产生的release或debug目录，ipch目录。
 
# 1.	项目概述
在Windows上编写一个程序，能获取本机上网记录。把访问过的网址和时间保存到一个文本文件中。
本文设计了分别针对Chrome、Firefox和IE浏览器，来实现获取各种浏览的历史记录。经过测试，设计程序能够实现获取Windows 10系统的三种浏览器的历史记录，同时将获取的历史记录保存在E盘目录下。
本文设计的获取历史记录功能，是基于Windows 10操作系统，Microsoft Visual Studio 2017下运行开发程序，同时在Windows 10系统下安装数据库MYSQL，分别获取Chrome、Firefox和IE浏览器历史记录来进行测试工作。

# 2.	功能需求
（1）实现获取Windows 10系统的主流浏览器历史记录，设计MFC开发界面，生成可执行文件.EXE，当打开可执行文件的时候，能够首先出现设计好的登陆界面，点击查询浏览器历史记录能够生成浏览器历史记录并存储到E盘。
（2）实现对Chrome、Firefox和IE浏览器的支持，和网站URL网址的简化。
# 3.	设计思路
（1）获取浏览器历史记录。网上搜索浏览器历史记录存储地址，可以得到Chrome的历史记录存储在win10: C:\Users\win10\AppData\Local\Google\Chrome\User Data\Default目录下，Firefox的历史记录存储在win10：C:\Users\win10\AppData\Roaming\Mozilla\Firefox\Profiles\9x1nhhkq.default目录下，IE浏览器通过调用FindFirstUrlCacheEntry(_T("visited:"), lpCacheEntry, &dwSize)函数来获取。
（2）解析浏览器历史记录。首先编码转换ConvertUtf8ToGBK(CStringA &strUtf8)，然后浏览器URL字符串化简，最后对时间进行处理（Coordinated Universal Time（UTC）世界标准时间转换为中国时间）。
（3）输出历史记录。在MFC窗口输出历史记录，并写入TXT文档。
# 4.	开发环境下载、安装和配置
4.1 开发环境介绍
本程序是在Microsoft Visual Studio 2017 Professional下运行开发程序，同时在Windows 10系统下安装MySQL 数据库、Chrome浏览器和Firefox浏览器来进行测试工作。
Microsoft Visual Studio 2017 下载地址：https://www.visualstudio.com/zh-hans/thank-you-downloading-visual-studio/?sku=Professional&rel=15
版本：vs_professional__1805440073.1505869523
MySQL Windows (x86, 64-bit), ZIP Archive	5.7.20
下载地址：https://dev.mysql.com/downloads/file/?id=473309https://dev.mysql.com/downloads/mysql/
Win10下载地址：https://www.microsoft.com/zh-cn/software-download/windows10
版本：10
sqlite3下载地址：http://www.sqlite.org/download.html
版本：3.20.1
4.2 工程文件的目录结构和文件
工程引用sqlite3来读取数据库，特别注意，sqlite3.dll要放入生成的debug目录下（否则会发生错误）。
 
# 5.	程序的难点或核心技术分析
Firefox和Chrome数据库处理，IE的.dwHighDateTime和.dwLowDateTime时间处理。URL字符串处理。Coordinated Universal Time（UTC）世界标准时间转换处理。
//查询url
				query = db.execQuery("select url from urls");
				query2 = db.execQuery("select last_visit_time from urls");
				while (!query.eof())
				{
					CStringA utf8url;
					utf8url = query.fieldValue("url");
					CStringA inttime1;
					inttime1 = query2.fieldValue("last_visit_time");
					__int64 inttime = _atoi64(inttime1);
					ConvertUtf8ToGBK(utf8url);
					urlFiltrateChrome((CString)utf8url,inttime);
					query.nextRow();
					query2.nextRow();
				}//查询时间
转换时间函数代码截图 
# 6.	运行和测试过程
6.1基于win10的浏览器历史记录查询
【运行】本地调试器运行：
1. 在common目录下找到sqlite3.dll并放到生成的debug目录下;
2. 点击本地调试器运行;
3. 查看生成历史记录和E盘生成的TXT文件。
【注意】
1.如果出现 请在common目录下找到sqlite3.dll并放到生成的debug目录下。
7.	软件使用说明
基于win10的浏览器历史记录查询
1、打开vs2017，选择本地调试器
查询浏览器历史记录按钮：
打开E盘：
打开生成的out TXT文件：
 
# 8.	视音频录制情况
无
# 9.	编程参考网址
http://blog.csdn.net/u011569253/article/details/76177404
http://blog.csdn.net/anda0109/article/details/41385241
http://blog.csdn.net/haiross/article/details/45718743
http://www.forensicswiki.org/wiki/Internet_Explorer_History_File_Format
https://www.douban.com/note/231708030/
https://bbs.pediy.com/thread-207125.htm
