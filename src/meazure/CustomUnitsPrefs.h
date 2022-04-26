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
/// @brief Custom measurement units property page header file.

#pragma once

#include "NumberField.h"
#include "Units.h"


/// Property page for custom measurement units preferences. Using this
/// property page, the user can define their own measurement units
/// (i.e. label and conversion factor).
///
class MeaCustomUnitsPrefs : public CPropertyPage
{
    DECLARE_DYNCREATE(MeaCustomUnitsPrefs)

public:
    /// Constructs an instance of the custom measurement units page.
    ///
    MeaCustomUnitsPrefs();

    /// Destroys an instance of the custom measurement units page.
    ///
    ~MeaCustomUnitsPrefs();


    /// Obtains the units basis and scale factor for the custom units.
    ///
    /// @param scaleBasis   [out] Indicates whether the custom units are based
    ///                     on pixels, inches or centimeters.
    /// @param scaleFactor  [out] Conversion factor to/from scaleBasis to/from the
    ///                     custom units.
    ///
    void GetScaleFactor(MeaCustomUnits::ScaleBasis& scaleBasis, double& scaleFactor) const;

    /// Sets the custom units basis and scale factor.
    ///
    /// @param scaleBasis   [in] Specifies whether the custom units are based on
    ///                     pixels, inches or centimeters.
    /// @param scaleFactor  [in] Conversion factor to/from scaleBasis to/from the
    ///                     custom units.
    ///
    void SetScaleFactor(MeaCustomUnits::ScaleBasis scaleBasis, double scaleFactor);

    enum { IDD = IDD_PREF_CUSTOM };
    CString m_abbrev;
    CString m_name;
    int     m_scaleBasis;
    double  m_pxScaleFactor;
    double  m_inScaleFactor;
    double  m_cmScaleFactor;

    /// @var m_abbrev
    /// Abbreviation for the custom units.

    /// @var m_name
    /// Full name for the custom units.

    /// @var m_scaleBasis
    /// Indicates whether the custom units are based on pixels, inches or centimeters.

    /// @var m_pxScaleFactor
    /// Scale factor if the custom units are based on pixels.

    /// @var m_inScaleFactor
    /// Scale factor if the custom units are based on inches.

    /// @var m_cmScaleFactor
    /// Scale factor if the custom units are based on centimeters.


    virtual BOOL OnInitDialog() override;
    virtual BOOL OnKillActive() override;
    virtual BOOL OnSetActive() override;
    virtual BOOL OnApply() override;

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;

    /// @fn OnInitDialog()
    /// Called when the property page is created. This method
    /// subclasses a number of controls on the page, with our
    /// implementations and obtains pointers to the page controls.
    ///
    /// @return TRUE, indicating that the input focus should be
    ///         set to the first control on the page.

    /// @fn OnKillActive()
    /// Called when the page becomes inactive. The data on the page
    /// is validated.
    ///
    /// @return TRUE if the data was valid and the page can become
    ///         inactive. FALSE if the data is not valid and the page
    ///         must remain active.

    /// @fn OnSetActive()
    /// Called when the page becomes active. This method ensures that
    /// the scale factor basis labels reflect the custom units abbreviation,
    /// if any.
    ///
    /// @return TRUE, indicating that the page is active.

    /// @fn OnApply()
    /// Called when the Apply button is pressed and validates the page
    /// contents. The page contents are valid if the menu name label and
    /// abbreviation are either both empty or both non-empty and the scale
    /// factor is greater than zero.
    ///
    /// @return TRUE if the page contents are valid and can be applied. If
    ///         the page contents are not valid, FALSE is returned.

    /// @fn DoDataExchange(CDataExchange* pDX)
    /// Performs Dynamic Data Exchange (DDX) for the page.
    ///
    /// @param pDX  [in] DDX object for exchanging data between the page UI
    ///             and the member variables.

    afx_msg void OnClear();
    afx_msg void OnChange();
    afx_msg void OnPixelChange();
    afx_msg void OnInchChange();
    afx_msg void OnCentimeterChange();
    afx_msg void OnNameChange();
    afx_msg void OnAbbrevChange();
    afx_msg void OnPrecision();
    afx_msg void OnCentimeterBasis();
    afx_msg void OnInchBasis();
    afx_msg void OnPixelBasis();

    DECLARE_MESSAGE_MAP()
    
    /// @fn OnClear()
    /// Called when the Clear Units button is pressed. This method clears
    /// the text from the units label fields, which effectively deletes the
    /// custom units.

    /// @fn OnChange()
    /// Called when a value changes on the UI. This method sets the modified
    /// flag.

    /// @fn OnPixelChange()
    /// Called when the pixel-based scale factor text field value is changed.

    /// @fn OnInchChange()
    /// Called when the inch-based scale factor text field value is changed.

    /// @fn OnCentimeterChange()
    /// Called when the centimeter-based scale factor text field value is changed.

    /// @fn OnNameChange()
    /// Called when the units menu name text field value is changed.

    /// @fn OnAbbrevChange()
    /// Called when the units abbreviation text field value is changed.

    /// @fn OnPrecision()
    /// Called when the Set Display Precision button is pressed. Pressing this
    /// button makes the Precision property page active so that the precision
    /// can be set for the custom units.

    /// @fn OnCentimeterBasis()
    /// Called when the centimeter-based scale factor radio button is selected.

    /// @fn OnInchBasis()
    /// Called when the inch-based scale factor radio button is selected.

    /// @fn OnPixelBasis()
    /// Called when the pixel-based scale factor radio button is selected.

private:
    /// Ensures radio button behavior on the scale factor basis radio buttons.
    /// The specified button is set and all other basis buttons are unset.
    ///
    /// @param buttonId     [in] ID for the radio button to set.
    ///
    void    SetCheck(UINT buttonId);

    /// Validates the custom units data on the page. The page data is considered
    /// valid either if both the name and abbrev. fields are empty, or if they
    /// both contain text and the scale factor is greater than 0.
    ///
    /// @return <b>true</b> if the page data is valid, and <b>false</b> if the
    ///         data is invalid.
    ///
    bool    Validate();

    /// Enables or disables the scale factor and precision controls depending on
    /// whether the units name and abbrev. fields contain text or are empty.
    ///
    void    EnableScaleFactor();

    bool        m_lockout;              ///< Prevents cyclic modification of text fields.

    CWnd        *m_nameField;           ///< Units menu name text field.
    CWnd        *m_abbrevField;         ///< Units abbreviation text field.
    CWnd        *m_precisionButton;     ///< Units display precision button.
    CWnd        *m_basisLabel;          ///< Label for the scale factor section of the page.

    MeaNumberField  m_pxScaleField;     ///< Numeric text field for the pixel-based scale factor.
    MeaNumberField  m_inScaleField;     ///< Numeric text field for the inch-based scale factor.
    MeaNumberField  m_cmScaleField;     ///< Numeric text field for the centimeter-based scale factor.

    CButton     *m_pxButton;            ///< Pixel-based scale factor radio button.
    CButton     *m_inButton;            ///< Inch-based scale factor radio button.
    CButton     *m_cmButton;            ///< Centimeter-based scale factor radio button.

    CWnd        *m_pxLabel;             ///< Pixel-based scale factor label.
    CWnd        *m_inLabel;             ///< Inch-based scale factor label.
    CWnd        *m_cmLabel;             ///< Centimeter-based scale factor label.

    CWnd        *m_pxAbbrev;            ///< Pixel-based scale factor abbreviation label.
    CWnd        *m_inAbbrev;            ///< Inch-based scale factor abbreviation label.
    CWnd        *m_cmAbbrev;            ///< Centimeter-based scale factor abbreviation label.
};
