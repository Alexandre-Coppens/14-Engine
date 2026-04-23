#include "WinDialogue.h"
#include <windows.h>
#include <commdlg.h>

std::string WinDialogue::OpenFileWindow()
{
	char filePath[MAX_PATH] = "";
	
	OPENFILENAMEA ofn = {};
	ofn.lStructSize		= sizeof(ofn);
	ofn.hwndOwner		= NULL;
	ofn.lpstrFile		= filePath;
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrInitialDir = ".\\maps";
	ofn.lpstrFilter     = "Map Files\0*.map\0Text Files\0*.txt\0All Files\0*.*\0\0";
	ofn.nFilterIndex	= 0;
	ofn.lpstrDefExt		= "txt";
	ofn.Flags			= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	
	if (GetOpenFileNameA(&ofn)) return std::string(filePath);
	
	return "";
}

std::string WinDialogue::SaveFileWindow()
{
	char filePath[MAX_PATH] = "";
 
	OPENFILENAMEA ofn = {};
	ofn.lStructSize     = sizeof(ofn);
	ofn.hwndOwner       = NULL;
	ofn.lpstrFile       = filePath;
	ofn.nMaxFile        = MAX_PATH;
	ofn.lpstrInitialDir = ".\\maps";
	ofn.lpstrFilter     = "Map Files\0*.map\0Text Files\0*.txt\0All Files\0*.*\0\0";
	ofn.nFilterIndex    = 1;
	ofn.lpstrDefExt     = "txt";
	ofn.Flags           = OFN_OVERWRITEPROMPT;
 
	if (GetSaveFileNameA(&ofn))
		return std::string(filePath);
 
	return "";
}