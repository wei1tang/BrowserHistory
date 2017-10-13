// FileName: BrowsHistory.h  
// ------------------------------------------------------------------------------------------------------------------------  
// Remarks:  
//   BrowsHistory对象应该设置成全局，或者静态；防止还没有获取完网址，对象就析构了；  
// ------------------------------------------------------------------------------------------------------------------------  

#pragma once  
#include <iostream>  
#include <algorithm>  
#include <functional>  
#include <vector>  
#include "afxwin.h"  
struct BrowsData
{
public:
	// 网址  
	CString strURL;

	//对应访问时间，年月日小时分钟秒
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	// 对应网址访问次数  
	unsigned int nCount;

	// 重载<操作符  
	bool operator < (const BrowsData &m)const
	{
		return nCount > m.nCount;
	}
};
class BrowsHistory
{
private:

	// 保存获得的网址和访问次数  
	std::vector<BrowsData> m_BrowsHistroy;
private:
	// IE网址过滤，如只取网址com前边的  
	void urlFiltrateIE(LPWSTR lpszSourceUrlName);

	// Chrome网址过滤，如只取网址com前边的  
	void urlFiltrateChrome(CString strUrlName, __int64 SubtleSeconds);
	// Firefox网址过滤，如只去网址com前边的  
	void urlFiltrateFirefox(CString strUrlName, __int64 SubtleSeconds);
	// 查询进程是否已存在, 返回true表示存在；自动结束其进程  
	bool IsRunning(CString exe);
	// 编码转换  
	void ConvertUtf8ToGBK(CStringA &strUtf8);
	// 获取浏览器历史记录  
	void InitHistroy(void);
	// 从1960年1月1日的毫秒转换为年月日
	void TimeTransformation(__int64 SubtleSeconds);
	// 多线程函数  
	static void ThreadPro(LPVOID * ptr);
	// 对获得的网址进行排序  
	void Sort(void);
public:
	BrowsHistory();
	~BrowsHistory();
	// 获取网址的进程，是否执行完；执行完时为true；  
	bool m_bStatus;
	// 初始化  
	void Init(void);
	// 获取浏览器历史记录  
	std::vector<BrowsData> GetBrowsHistory(void) const;
};

// 定义64位整形
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64t;
#endif  // _WIN32
// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)