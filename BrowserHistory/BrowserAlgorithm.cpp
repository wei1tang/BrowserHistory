// // FileName: BrowsHistory.cpp
#include "stdafx.h"                    // 如果编译出错请删除此行
#include "BrowserAlgorithm.h"
#include <wininet.h>
#include "Common\\CppSQLite3.h"
#include <shlobj.h> 
#include "Shlwapi.h"
#include "tlhelp32.h"
#include <atlconv.h>

#pragma  comment(lib,"Shlwapi.lib")
#pragma comment(lib,"Common\\sqlite3.lib")

#include <io.h> 
__int64 IEtime;
int tempYear;
int tempMonth;
int tempDay;
int tempHour;
int tempMinute;
int tempSecond;


BrowsHistory::BrowsHistory()
{
	m_bStatus = false;
}
BrowsHistory::~BrowsHistory()
{
}
void BrowsHistory::urlFiltrateIE(LPWSTR lpszSourceUrlName)
{
	BrowsData browsDate;
	browsDate.nCount = 0;
	CString strTemp(lpszSourceUrlName);

	std::vector<BrowsData>::iterator iter;
	// 排除非必要的网址
	if (strTemp.Find(_T("@http://")) != -1)
	{
		strTemp.Delete(0, strTemp.Find(_T("@http://")) + 8);
		// 排除非必要网址
		if (strTemp.Find(_T(":")) != -1)
		{
			return;
		}
		int nIndex = strTemp.Find(_T("/"));
		if (nIndex != -1)
		{
			for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
			{
				if (iter->strURL == strTemp.Left(nIndex))
				{
					iter->nCount += 1;
					return;
				}
			}
			browsDate.strURL = strTemp.Left(nIndex);
			browsDate.nCount = 1;

			TimeTransformation(IEtime);
			browsDate.year = tempYear;
			browsDate.month = tempMonth;
			browsDate.day = tempDay;
			browsDate.hour = tempHour;
			browsDate.minute = tempMinute;
			browsDate.second = tempSecond;

			m_BrowsHistroy.push_back(browsDate);
		}
		else
		{
			for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
			{
				if (iter->strURL == strTemp)
				{
					iter->nCount += 1;
					return;
				}
			}
			browsDate.strURL = strTemp;
			browsDate.nCount = 1;

			TimeTransformation(IEtime);
			browsDate.year = tempYear;
			browsDate.month = tempMonth;
			browsDate.day = tempDay;
			browsDate.hour = tempHour;
			browsDate.minute = tempMinute;
			browsDate.second = tempSecond;

			m_BrowsHistroy.push_back(browsDate);
		}
	}
}
void BrowsHistory::urlFiltrateChrome(CString strUrlName, __int64 SubtleSeconds)
{
	// 删除开始的"https://"

	if (strUrlName.Find(_T("https://")) != -1)
	{
		strUrlName.Delete(0, 8);
	}
	else if (strUrlName.Find(_T("http://")) != -1)
	{
		strUrlName.Delete(0, 7);
	}
	int nIndex = strUrlName.Find(_T("/"));
	BrowsData browsDate;
	browsDate.nCount = 0;
	std::vector<BrowsData>::iterator iter;
	if (nIndex != -1)
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
		{
			if (iter->strURL == strUrlName.Left(nIndex))
			{
				iter->nCount += 1;
				//TimeTransformation(SubtleSeconds);//更新浏览时间
				//iter->year = tempYear;
				//iter->month = tempMonth;
				//iter->day = tempDay;
				//iter->hour = tempHour;
				//iter->minute = tempMinute;
				//iter->second = tempSecond;
				return;
			}
		}
		browsDate.strURL = strUrlName.Left(nIndex);
		browsDate.nCount = 1;

		TimeTransformation(SubtleSeconds);
		browsDate.year = tempYear;
		browsDate.month = tempMonth;
		browsDate.day = tempDay;
		browsDate.hour = tempHour;
		browsDate.minute = tempMinute;
		browsDate.second = tempSecond;

		m_BrowsHistroy.push_back(browsDate);
	}
	else
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
		{
			if (iter->strURL == strUrlName)
			{
				iter->nCount += 1;
				return;
			}
		}
		browsDate.strURL = strUrlName;
		browsDate.nCount = 1;

		TimeTransformation(SubtleSeconds);
		browsDate.year = tempYear;
		browsDate.month = tempMonth;
		browsDate.day = tempDay;
		browsDate.hour = tempHour;
		browsDate.minute = tempMinute;
		browsDate.second = tempSecond;

		m_BrowsHistroy.push_back(browsDate);
	}
}
void BrowsHistory::urlFiltrateFirefox(CString strUrlName, __int64 SubtleSeconds)
{
	// 删除开始的"https://"

	if (strUrlName.Find(_T("https://")) != -1)
	{
		strUrlName.Delete(0, 8);
	}
	else if (strUrlName.Find(_T("http://")) != -1)
	{
		strUrlName.Delete(0, 7);
	}
	int nIndex = strUrlName.Find(_T("/"));
	BrowsData browsDate;
	browsDate.nCount = 0;
	std::vector<BrowsData>::iterator iter;

	if (nIndex != -1)
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
		{
			CString tsetString = strUrlName.Left(nIndex);
			if (iter->strURL == strUrlName.Left(nIndex))
			{
				iter->nCount += 1;
				return;
			}
		}
		browsDate.strURL = strUrlName.Left(nIndex);
		browsDate.nCount = 1;

		TimeTransformation(SubtleSeconds);
		browsDate.year = tempYear;
		browsDate.month = tempMonth;
		browsDate.day = tempDay;
		browsDate.hour = tempHour;
		browsDate.minute = tempMinute;
		browsDate.second = tempSecond;

		m_BrowsHistroy.push_back(browsDate);
	}
	else
	{
		for (iter = m_BrowsHistroy.begin(); iter != m_BrowsHistroy.end(); iter++)
		{
			if (iter->strURL == strUrlName)
			{
				iter->nCount += 1;
				return;
			}
		}
		browsDate.strURL = strUrlName;
		browsDate.nCount = 1;

		TimeTransformation(SubtleSeconds);
		browsDate.year = tempYear;
		browsDate.month = tempMonth;
		browsDate.day = tempDay;
		browsDate.hour = tempHour;
		browsDate.minute = tempMinute;
		browsDate.second = tempSecond;

		m_BrowsHistroy.push_back(browsDate);
	}
	
	
	
}
bool BrowsHistory::IsRunning(CString exe)
{
	PROCESSENTRY32 pe32;
	HANDLE hprocess;
	hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hprocess, &pe32))
	{
		do
		{
			HANDLE h_id;
			h_id = OpenProcess(PROCESS_TERMINATE, false, pe32.th32ProcessID);
			CString exefile;
			exefile = pe32.szExeFile;
			exefile.MakeLower();
			exe.MakeLower();
			if (exefile == exe)
			{
				if (TerminateProcess(h_id, 0) != 0)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		} while (Process32Next(hprocess, &pe32));
	}
	return FALSE;
}
void BrowsHistory::ConvertUtf8ToGBK(CStringA &strUtf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	strUtf8 = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}
bool IsRound(int year) {
	if ((year % 100) && (year % 4 == 0)) return 1;
	if ((year % 100 == 0) && (year % 400 == 0)) return 1;
	return 0;
}
void BrowsHistory::TimeTransformation(__int64 SubtleSeconds)
{
	int year_s[2] = { 365 * 24 * 60 * 60, 366 * 24 * 60 * 60 };
	int month_s[2][12] = { { 31,28,31,30,31,30,31,31,30,31,30,31 },
	{ 31,29,31,30,31,30,31,31,30,31,30,31 } };
	int day_s = 24 * 60 * 60;
	int hour_s = 60 * 60;
	int minute_s = 60;

	__int64 temp = (SubtleSeconds - EPOCHFILETIME / 10) / 1000000;//从1970年1月1日到现在秒数
	temp = temp + 8 * 60 * 60;//转换中国时间
	int year = 1970;
	int month = 1;
	int day = 1;
	int hour = 0;
	int minute = 0;
	int second = 0;

	while (temp >= 60) {

		int flag = IsRound(year);
		if (temp >= year_s[flag]) { year++; temp -= year_s[flag]; }
		else if (temp >= day_s) {
			int days = temp / day_s;
			temp = temp%day_s;
			int i = 0;
			int flag = IsRound(year);
			int hh = 31;
			while (days >= hh) {
				days -= month_s[flag][i++];
				hh = month_s[flag][i];
			}
			month += i;
			day += days;

		}
		else if (temp >= hour_s) {
			hour = temp / hour_s;
			temp %= hour_s;
		}
		else if (temp >= minute_s) {
			minute = temp / minute_s;
			temp %= minute_s;
		}
	}
	second = temp;

	tempYear = year;
	tempMonth = month;
	tempDay = day;
	tempHour = hour;
	tempMinute = minute;
	tempSecond = second;

}
void BrowsHistory::Init(void)
{
	// 创建一个线程
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPro, this, 0, NULL);
}
void BrowsHistory::InitHistroy(void)
{
	
	__int64 IEtime_l;
	__int64 IEtime_h;
	// 用来支持多次调用
	m_bStatus = false;
	m_BrowsHistroy.clear();
	// 获取IE的历史记录
	HANDLE hCacheEnumHandle = NULL;
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;
	DWORD dwSize = 4096;
	BrowsData browsDate;
	browsDate.nCount = 0;
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwSize];
	lpCacheEntry->dwStructSize = dwSize;
	hCacheEnumHandle = FindFirstUrlCacheEntry(_T("visited:"), lpCacheEntry, &dwSize);
	if (hCacheEnumHandle != NULL)
	{
		IEtime_h = lpCacheEntry->LastAccessTime.dwHighDateTime;
		IEtime_l = lpCacheEntry->LastAccessTime.dwLowDateTime;
		IEtime = (IEtime_h << 32) + IEtime_l;
		urlFiltrateIE(lpCacheEntry->lpszSourceUrlName);
		
	}
	else
	{
		switch (GetLastError())
		{
		case ERROR_INSUFFICIENT_BUFFER:
			lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwSize];
			lpCacheEntry->dwStructSize = dwSize;
			hCacheEnumHandle = FindFirstUrlCacheEntry(_T("visited:"), lpCacheEntry,
				&dwSize);
			if (hCacheEnumHandle != NULL)
			{
				IEtime_h = lpCacheEntry->LastAccessTime.dwHighDateTime;
				IEtime_l = lpCacheEntry->LastAccessTime.dwLowDateTime;
				IEtime = ((IEtime_h << 32) + IEtime_l)/10;
				urlFiltrateIE(lpCacheEntry->lpszSourceUrlName);
				break;
			}
			else
			{
				// 查找失败
				return;
			}
		default:
		{
			FindCloseUrlCache(hCacheEnumHandle);
		}
		}
	}
	bool bSign = true;
	do
	{
		if (FindNextUrlCacheEntry(hCacheEnumHandle, lpCacheEntry, &dwSize))
		{
			IEtime_h = lpCacheEntry->LastAccessTime.dwHighDateTime;
			IEtime_l = lpCacheEntry->LastAccessTime.dwLowDateTime;
			IEtime = ((IEtime_h << 32) + IEtime_l) / 10;
			urlFiltrateIE(lpCacheEntry->lpszSourceUrlName);
		}
		else
		{
			switch (GetLastError())
			{
			case ERROR_INSUFFICIENT_BUFFER:
				lpCacheEntry =
					(LPINTERNET_CACHE_ENTRY_INFO) new char[dwSize];
				memset(lpCacheEntry, 0, dwSize);
				lpCacheEntry->dwStructSize = dwSize;

				if (FindNextUrlCacheEntry(hCacheEnumHandle, lpCacheEntry,
					&dwSize))
				{
					IEtime_h = lpCacheEntry->LastAccessTime.dwHighDateTime;
					IEtime_l = lpCacheEntry->LastAccessTime.dwLowDateTime;
					IEtime = ((IEtime_h << 32) + IEtime_l) / 10;
					urlFiltrateIE(lpCacheEntry->lpszSourceUrlName);
					break;
				}
				else
				{
					FindCloseUrlCache(hCacheEnumHandle);
					bSign = false;
					break;
				}
				break;
			case ERROR_NO_MORE_ITEMS:
				FindCloseUrlCache(hCacheEnumHandle);
				bSign = false;
				break;
			default:
				FindCloseUrlCache(hCacheEnumHandle);
				bSign = false;
				break;
			}
		}
	} while (bSign);
	// 获取谷歌浏览器的历史记录
	char path[MAX_PATH];
	::SHGetSpecialFolderPathA(NULL, path, CSIDL_LOCAL_APPDATA, FALSE);
	strcat_s(path, "\\google\\chrome\\User Data\\default\\History");
	if (PathFileExistsA(path))
	{
		// 谷歌浏览器正在运行，强制关闭；关闭后才能得到谷歌浏览器的历史记录
		if (!IsRunning(_T("chrome.exe")))
		{
			try
			{
				CppSQLite3DB db;
				CppSQLite3Query query;
				CppSQLite3Query query2;
				db.open(path);
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
				}
				//查询时间
				
				db.close();
			}
			catch (CppSQLite3Exception& e)
			{
				//return;
			}
		}
	}
	// 获取火狐浏览器的历史记录
	char pathFirefox[MAX_PATH] = { 0 };
	::SHGetSpecialFolderPathA(NULL, pathFirefox, CSIDL_LOCAL_APPDATA, FALSE);
	int pathFirefoxLength=strlen(pathFirefox);
	for (int k = 0; k < 5; k++) {
		pathFirefox[pathFirefoxLength - 1 - k] = 0;
	}
	strcat_s(pathFirefox, "Roaming\\Mozilla\\Firefox\\Profiles\\9x1nhhkq.default\\places.sqlite");
	
	if (PathFileExistsA(pathFirefox))
	{
		// 火狐浏览器正在运行，强制关闭；关闭后才能得到火狐浏览器的历史记录
		if (!IsRunning(_T("firefox.exe")))
		{
			try
			{
				CppSQLite3DB dbFirefox;
				CppSQLite3Query queryFirefox;
				CppSQLite3Query query2Firefox;
				dbFirefox.open(pathFirefox);
				//查询url
				queryFirefox = dbFirefox.execQuery("select url from moz_places");
				query2Firefox = dbFirefox.execQuery("select visit_date from moz_historyvisits");
				while (!queryFirefox.eof())
				{
					CStringA utf8url;
					utf8url = queryFirefox.fieldValue("url");

					CStringA inttime1;
					inttime1 = query2Firefox.fieldValue("visit_date");

					__int64 inttime = _atoi64(inttime1)+ EPOCHFILETIME/10;//16位数微秒

					ConvertUtf8ToGBK(utf8url);
					urlFiltrateFirefox((CString)utf8url, inttime);
					queryFirefox.nextRow();

					query2Firefox.nextRow();
				}
				//查询时间

				dbFirefox.close();
			}
			catch (CppSQLite3Exception& e)
			{
				//return;
			}
		}
	}


	
	Sort();
}
void BrowsHistory::ThreadPro(LPVOID * ptr)
{
	BrowsHistory * pBrowsHistroy = (BrowsHistory*)ptr;
	pBrowsHistroy->InitHistroy();

	// 获取网址的函数执行完了
	pBrowsHistroy->m_bStatus = true;
}
std::vector<BrowsData> BrowsHistory::GetBrowsHistory(void) const
{
	return m_BrowsHistroy;
}
void BrowsHistory::Sort(void)
{
	stable_sort(m_BrowsHistroy.begin(), m_BrowsHistroy.end(), std::less<BrowsData>());
}