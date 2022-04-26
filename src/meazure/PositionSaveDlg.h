/*
 * Copyright 2001 C Thing Software
 *
 * This file is part of Meazure.
 * 
 * Meazure is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Meazure is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Meazure.  If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// @brief Header file for the Position Log file save dialog. 

#pragma once


/// The Save dialog for Position Log files. The dialog is a standard
/// CFileDialog with the addition of a text field for specifying the
/// Log file title and a text field for specifying the Log file description.
///
class MeaPositionSaveDlg : public CFileDialog
{
    DECLARE_DYNAMIC(MeaPositionSaveDlg)

public:
    /// Constructs a position log file dialog. Call the dialog's
    /// DoModal method to display the dialog.
    ///
    /// @param lpszDefExt       [in] Default file extension.
    /// @param lpszFileName     [in] Initial filename appearing in filename box.
    /// @param lpszFilter       [in] A series of string pairs that specify
    ///                         filters you can apply to the file.
    /// @param pParentWnd       [in] A pointer to the file dialog-box object�s
    ///                         parent or owner window.
    ///
    explicit MeaPositionSaveDlg(LPCTSTR lpszDefExt = nullptr,
        LPCTSTR lpszFileName = nullptr,
        LPCTSTR lpszFilter = nullptr,
        CWnd* pParentWnd = nullptr);

    /// Destroys a position log file dialog.
    ///
    virtual ~MeaPositionSaveDlg();

    enum { IDD = IDD_POSITION_SAVE };
    CString m_desc;
    CString m_title;

    /// @var m_desc
    /// Position Log file description.

    /// @var m_title
    /// Title for the dialog.

protected:
    DECLARE_MESSAGE_MAP()

    /// Performs dynamic data exchange (DDX) for the dialog.
    ///
    /// @param pDX      [in] DDX operation object.
    ///
    virtual void DoDataExchange(CDataExchange* pDX) override;
};
