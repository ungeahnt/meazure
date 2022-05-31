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

#include <meazure/pch.h>
#include "Colors.h"
#include <meazure/ui/LayeredWindows.h>
#include <meazure/utilities/NumericUtils.h>


MeaColors::Colors const MeaColors::m_defColors = {
        { LineFore,         RGB(0xFF, 0, 0) },
        { CrossHairBack,    RGB(0xFF, 0, 0) },
        { CrossHairBorder,  RGB(0x50, 0x50, 0x50) },
        { CrossHairHilite,  RGB(0xFF, 0xFF, 0) },
        { CrossHairOpacity, RGB(HaveLayeredWindows() ? 0xE5 : 0xFF, 0, 0) },
        { RulerBack,        RGB(0xFF, 0xFF, 0xFF) },
        { RulerBorder,      RGB(0, 0, 0) },
        { RulerOpacity,     RGB(HaveLayeredWindows() ? 0xE5 : 0xFF, 0, 0) }
};

MeaColors::Colors MeaColors::m_colors = m_defColors;


void MeaColors::SaveProfile(MeaProfile& profile) {
    if (!profile.UserInitiated()) {
        profile.WriteInt(_T("LineFore"), m_colors[LineFore]);
        profile.WriteInt(_T("CrossHairBack"), m_colors[CrossHairBack]);
        profile.WriteInt(_T("CrossHairBorder"), m_colors[CrossHairBorder]);
        profile.WriteInt(_T("CrossHairHilite"), m_colors[CrossHairHilite]);
        profile.WriteInt(_T("CrossHairOpacity"), m_colors[CrossHairOpacity]);
        profile.WriteInt(_T("RulerBack"), m_colors[RulerBack]);
        profile.WriteInt(_T("RulerBorder"), m_colors[RulerBorder]);
        profile.WriteInt(_T("RulerOpacity"), m_colors[RulerOpacity]);
    }
}

void MeaColors::LoadProfile(MeaProfile& profile) {
    if (!profile.UserInitiated()) {
        m_colors[LineFore] = profile.ReadInt(_T("LineFore"), m_defColors.at(LineFore));
        m_colors[CrossHairBack] = profile.ReadInt(_T("CrossHairBack"), m_defColors.at(CrossHairBack));
        m_colors[CrossHairBorder] = profile.ReadInt(_T("CrossHairBorder"), m_defColors.at(CrossHairBorder));
        m_colors[CrossHairHilite] = profile.ReadInt(_T("CrossHairHilite"), m_defColors.at(CrossHairHilite));
        m_colors[CrossHairOpacity] = profile.ReadInt(_T("CrossHairOpacity"), m_defColors.at(CrossHairOpacity));
        m_colors[RulerBack] = profile.ReadInt(_T("RulerBack"), m_defColors.at(RulerBack));
        m_colors[RulerBorder] = profile.ReadInt(_T("RulerBorder"), m_defColors.at(RulerBorder));
        m_colors[RulerOpacity] = profile.ReadInt(_T("RulerOpacity"), m_defColors.at(RulerOpacity));
    }
}

void MeaColors::MasterReset() {
    m_colors = m_defColors;
}

COLORREF MeaColors::InterpolateColor(COLORREF startRGB, COLORREF endRGB, int percent) {
    if (percent == 0) {
        return startRGB;
    }
    if (percent == 100) {
        return endRGB;
    }

    auto interpolate = [](double start, double end, int percent) {
        return start + (end - start) * percent / 100.0;
    };

    HSL startHSL = RGBtoHSL(startRGB);
    HSL endHSL = RGBtoHSL(endRGB);

    HSL hsl(interpolate(startHSL.hue, endHSL.hue, percent), 
            interpolate(startHSL.saturation, endHSL.saturation, percent),
            interpolate(startHSL.lightness, endHSL.lightness, percent));

    return HSLtoRGB(hsl);
}

HSL MeaColors::RGBtoHSL(COLORREF rgb) {
    double h, s, l;
    double r = GetRValue(rgb) / 255.0;
    double g = GetGValue(rgb) / 255.0;
    double b = GetBValue(rgb) / 255.0;
    double cmax = Max(r, Max(g, b));
    double cmin = Min(r, Min(g, b));

    l = (cmax + cmin) / 2.0;
    if (MeaNumericUtils::IsFloatingEqual(cmax, cmin)) {
        s = 0.0;
        h = 0.0; // it's really undefined
    } else {
        if (l < 0.5) {
            s = (cmax - cmin) / (cmax + cmin);
        } else {
            s = (cmax - cmin) / (2.0 - cmax - cmin);
        }
        double delta = cmax - cmin;

        if (MeaNumericUtils::IsFloatingEqual(r, cmax)) {
            h = (g - b) / delta;
        } else if (MeaNumericUtils::IsFloatingEqual(g, cmax)) {
            h = 2.0 + (b - r) / delta;
        } else {
            h = 4.0 + (r - g) / delta;
        }
        h /= 6.0;

        if (h < 0.0) {
            h += 1.0;
        }
    }

    return HSL(h, s, l);
}

double MeaColors::HuetoRGB(double m1, double m2, double h) {
    if (h < 0.0) {
        h += 1.0;
    }
    if (h > 1.0) {
        h -= 1.0;
    }
    if ((6.0 * h) < 1.0) {
        return (m1 + (m2 - m1) * h * 6.0);
    }
    if ((2.0 * h) < 1.0) {
        return m2;
    }
    if ((3.0 * h) < 2.0) {
        return (m1 + (m2 - m1) * ((2.0 / 3.0) - h) * 6.0);
    }
    return m1;
}

COLORREF MeaColors::HSLtoRGB(const HSL& hsl) {
    double r, g, b;

    if (hsl.saturation == 0.0) {
        r = g = b = hsl.lightness;
    } else {
        double m2;

        if (hsl.lightness <= 0.5) {
            m2 = hsl.lightness * (1.0 + hsl.saturation);
        } else {
            m2 = hsl.lightness + hsl.saturation - hsl.lightness * hsl.saturation;
        }
        double m1 = 2.0 * hsl.lightness - m2;

        r = HuetoRGB(m1, m2, hsl.hue + 1.0 / 3.0);
        g = HuetoRGB(m1, m2, hsl.hue);
        b = HuetoRGB(m1, m2, hsl.hue - 1.0 / 3.0);
    }

    return RGB((BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
}
