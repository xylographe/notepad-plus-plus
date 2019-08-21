//this file is part of notepad++
//Copyright (C)2020 Don HO <don.h@free.fr>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#include "StaticDialog.h"

enum hashType {hash_md5, hash_sha256};

class HashDialog : public StaticDialog
{
public :
	virtual void doDialog(bool isRTL) = 0;
	void setHashType(hashType newHashType);

protected :
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	INT_PTR run_dlgProc(UINT message);

	hashType _ht = hash_md5;
	int _originEditID;
	int _resultEditID;

private :
	LRESULT run_textEditProc(WNDPROC oldEditProc, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK HashOriginStaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		const auto dlg = (HashDialog *)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return (dlg->run_textEditProc(dlg->_oldHashOriginProc, hwnd, message, wParam, lParam));
	};

	static LRESULT CALLBACK HashResultStaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		const auto dlg = (HashDialog *)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return (dlg->run_textEditProc(dlg->_oldHashResultProc, hwnd, message, wParam, lParam));
	};

	WNDPROC _oldHashOriginProc = nullptr;
	WNDPROC _oldHashResultProc = nullptr;
};

class HashFromFilesDlg : public HashDialog
{
public :
	HashFromFilesDlg();

	virtual void destroy() {};
	void doDialog(bool isRTL = false) override;

protected :
	INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) override;
};

class HashFromTextDlg : public HashDialog
{
public :
	HashFromTextDlg();

	virtual void destroy() {};
	void doDialog(bool isRTL = false) override;
	void generateHashPerLine();
	void generateHash();

protected :
	INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) override;
};
