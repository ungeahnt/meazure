/*
 * Copyright 2022 C Thing Software
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

#include "pch.h"
#include <boost/test/unit_test.hpp>
#include <meazure/utilities/Geometry.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;


namespace {
    void TestInitialSize() {
        FSIZE fs1;
        BOOST_CHECK_CLOSE(0.0, fs1.cx, 0.0001);
        BOOST_CHECK_CLOSE(0.0, fs1.cy, 0.0001);

        FSIZE fs2(1.0, 2.0);
        BOOST_CHECK_CLOSE(1.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(2.0, fs2.cy, 0.0001);
    }

    void TestAddFSize() {
        FSIZE fs1;
        FSIZE fs2;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        fs2.cx = 5.0;
        fs2.cy = 6.0;

        FSIZE fs3 = fs1 + fs2;
        BOOST_CHECK_CLOSE(15.0, fs3.cx, 0.0001);
        BOOST_CHECK_CLOSE(17.0, fs3.cy, 0.0001);
    }

    void TestAddValue() {
        FSIZE fs1;
        fs1.cx = 10.0;
        fs1.cy = 11.0;

        FSIZE fs2 = fs1 + 13.0;
        BOOST_CHECK_CLOSE(23.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(24.0, fs2.cy, 0.0001);
    }

    void TestMultFSize() {
        FSIZE fs1;
        FSIZE fs2;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        fs2.cx = 2.0;
        fs2.cy = 3.0;

        FSIZE fs3 = fs1 * fs2;
        BOOST_CHECK_CLOSE(20.0, fs3.cx, 0.0001);
        BOOST_CHECK_CLOSE(33.0, fs3.cy, 0.0001);
    }

    void TestMultSize() {
        FSIZE fs1;
        SIZE s;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        s.cx = 2;
        s.cy = 3;

        FSIZE fs2 = fs1 * s;
        BOOST_CHECK_CLOSE(20.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(33.0, fs2.cy, 0.0001);
    }

    void TestMultValue() {
        FSIZE fs1;
        fs1.cx = 10.0;
        fs1.cy = 11.0;

        FSIZE fs2 = fs1 * 2.0;
        BOOST_CHECK_CLOSE(20.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(22.0, fs2.cy, 0.0001);
    }

    void TestAddAssign() {
        FSIZE fs1;
        FSIZE fs2;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        fs2.cx = 5.0;
        fs2.cy = 6.0;

        fs1 += fs2;
        BOOST_CHECK_CLOSE(15.0, fs1.cx, 0.0001);
        BOOST_CHECK_CLOSE(17.0, fs1.cy, 0.0001);
    }

    void TestSubAssign() {
        FSIZE fs1;
        FSIZE fs2;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        fs2.cx = 3.0;
        fs2.cy = 6.0;

        fs1 -= fs2;
        BOOST_CHECK_CLOSE(7.0, fs1.cx, 0.0001);
        BOOST_CHECK_CLOSE(5.0, fs1.cy, 0.0001);
    }

    void TestMultAssign() {
        FSIZE fs1;
        FSIZE fs2;

        fs1.cx = 10.0;
        fs1.cy = 11.0;

        fs2.cx = 3.0;
        fs2.cy = 6.0;

        fs1 *= fs2;
        BOOST_CHECK_CLOSE(30.0, fs1.cx, 0.0001);
        BOOST_CHECK_CLOSE(66.0, fs1.cy, 0.0001);
    }

    void TestLog10() {
        FSIZE fs1;
        fs1.cx = 1000.0;
        fs1.cy = 100.0;

        FSIZE fs2 = log10(fs1);
        BOOST_CHECK_CLOSE(3.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(2.0, fs2.cy, 0.0001);
    }

    void TestFloor() {
        FSIZE fs1;
        fs1.cx = 12.98;
        fs1.cy = 4.01;

        FSIZE fs2 = floor(fs1);
        BOOST_CHECK_CLOSE(12.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(4.0, fs2.cy, 0.0001);
    }

    void TestValueSub() {
        FSIZE fs1;
        fs1.cx = 11.0;
        fs1.cy = 45.0;

        FSIZE fs2 = 200.0 - fs1;
        BOOST_CHECK_CLOSE(189.0, fs2.cx, 0.0001);
        BOOST_CHECK_CLOSE(155.0, fs2.cy, 0.0001);
    }

    void TestInitialRectangle() {
        FRECT fr1;
        BOOST_CHECK_CLOSE(0.0, fr1.top, 0.0001);
        BOOST_CHECK_CLOSE(0.0, fr1.bottom, 0.0001);
        BOOST_CHECK_CLOSE(0.0, fr1.left, 0.0001);
        BOOST_CHECK_CLOSE(0.0, fr1.right, 0.0001);

        FRECT fr2(1.0, 2.0, 3.0, 4.0);
        BOOST_CHECK_CLOSE(1.0, fr2.top, 0.0001);
        BOOST_CHECK_CLOSE(2.0, fr2.bottom, 0.0001);
        BOOST_CHECK_CLOSE(3.0, fr2.left, 0.0001);
        BOOST_CHECK_CLOSE(4.0, fr2.right, 0.0001);
    }

    void TestInitialPoint() {
        FPOINT fp1;
        BOOST_CHECK_CLOSE(0.0, fp1.x, 0.0001);
        BOOST_CHECK_CLOSE(0.0, fp1.y, 0.0001);

        FPOINT fp2(1.0, 2.0);
        BOOST_CHECK_CLOSE(1.0, fp2.x, 0.0001);
        BOOST_CHECK_CLOSE(2.0, fp2.y, 0.0001);
    }

    void TestCalcLength() {
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(0.0, 0.0), 0.0, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(1.0, 2.0), 2.2360679774997898, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(0.5, 0.7), 0.86023252670426265, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(-1.0, -2.0), 2.2360679774997898, 0.0000001);

        POINT p0 = { 0, 0 };
        POINT p1 = { 1, 2 };
        POINT p2 = { 2, 4 };
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(p0, p0), 0.0, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcLength(p1, p2), 2.2360679774997898, 0.0000001);
    }

    void TestCalcCircumference() {
        BOOST_CHECK_CLOSE(MeaGeometry::CalcCircumference(0.0), 0.0, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcCircumference(1.0), 6.2831853071795862, 0.0000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcCircumference(15.5), 97.389372261283583, 0.0000001);
    }

    void TestCalcSector() {
        // Zero vector
        POINT p0 = { 1, 2 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p0), 0);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p0));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p0));

        // 27 degrees
        POINT p1 = { p0.x + 2, p0.y + 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p1), 1);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p1));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p1));

        // 63 degrees
        POINT p2 = { p0.x + 1, p0.y + 2 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p2), 2);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p2));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p2));

        // 117 degrees
        POINT p3 = { p0.x - 1, p0.y + 2 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p3), 3);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p3));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p3));

        // 153 degrees
        POINT p4 = { p0.x - 2, p0.y + 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p4), 4);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p4));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p4));

        // 207 degrees
        POINT p5 = { p0.x - 2, p0.y - 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p5), -4);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p5));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p5));

        // 243 degrees
        POINT p6 = { p0.x - 1, p0.y - 2 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p6), -3);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p6));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p6));

        // 297 degrees
        POINT p7 = { p0.x + 1, p0.y - 2 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p7), -2);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p7));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p7));

        // 333 degrees
        POINT p8 = { p0.x + 2, p0.y - 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p8), -1);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p8));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p8));

        // 0 degrees
        POINT p9 = { p0.x + 1, p0.y };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p9), 1);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p9));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p9));

        // 45 degrees
        POINT p10 = { p0.x + 1, p0.y + 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p10), 2);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p10));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p10));

        // 90 degrees
        POINT p11 = { p0.x, p0.y + 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p11), 3);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p11));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p11));

        // 135 degrees
        POINT p12 = { p0.x - 1, p0.y + 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p12), 4);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p12));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p12));

        // 180 degrees
        POINT p13 = { p0.x - 1, p0.y };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p13), -4);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p13));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p13));

        // 225 degrees
        POINT p14 = { p0.x - 1, p0.y - 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p14), -4);
        BOOST_CHECK(MeaGeometry::IsHorizontallyOriented(p0, p14));
        BOOST_CHECK(!MeaGeometry::IsVerticallyOriented(p0, p14));

        // 270 degrees
        POINT p15 = { p0.x, p0.y - 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p15), -3);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p15));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p15));

        // 315 degrees
        POINT p16 = { p0.x + 1, p0.y - 1 };
        BOOST_CHECK_EQUAL(MeaGeometry::CalcSector(p0, p16), -2);
        BOOST_CHECK(!MeaGeometry::IsHorizontallyOriented(p0, p16));
        BOOST_CHECK(MeaGeometry::IsVerticallyOriented(p0, p16));
    }

    void TestCalcAngle1() {
        FPOINT p0(1.0, 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p0), 0.0, 0.000001);

        // 27 degrees
        FPOINT p1(p0.x + 2.0, p0.y + 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p1), 0.46364761, 0.000001);

        //// 63 degrees
        FPOINT p2(p0.x + 1.0, p0.y + 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p2), 1.10714872, 0.000001);

        // 117 degrees
        FPOINT p3(p0.x - 1.0, p0.y + 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p3), 2.03444393, 0.000001);

        // 153 degrees
        FPOINT p4(p0.x - 2.0, p0.y + 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p4), 2.67794504, 0.000001);

        // 207 degrees
        FPOINT p5(p0.x - 2.0, p0.y - 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p5), -2.67794504, 0.000001);

        // 243 degrees
        FPOINT p6(p0.x - 1.0, p0.y - 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p6), -2.03444393, 0.000001);

        // 297 degrees
        FPOINT p7(p0.x + 1.0, p0.y - 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p7), -1.10714872, 0.000001);

        // 333 degrees
        FPOINT p8(p0.x + 2.0, p0.y - 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p8), -0.46364761, 0.000001);

        // 0 degrees
        FPOINT p9(p0.x + 1.0, p0.y);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p9), 0.0, 0.000001);

        // 45 degrees
        FPOINT p10(p0.x + 1.0, p0.y + 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p10), 0.78539816, 0.000001);

        // 90 degrees
        FPOINT p11(p0.x, p0.y + 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p11), 1.57079633, 0.000001);

        // 135 degrees
        FPOINT p12(p0.x - 1.0, p0.y + 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p12), 2.35619449, 0.000001);

        // 180 degrees
        FPOINT p13(p0.x - 1.0, p0.y);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p13), 3.14159265, 0.000001);

        // 225 degrees
        FPOINT p14(p0.x - 1.0, p0.y - 1);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p14), -2.35619449, 0.000001);

        // 270 degrees
        FPOINT p15(p0.x, p0.y - 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p15), -1.57079633, 0.000001);

        // 315 degrees
        FPOINT p16(p0.x + 1.0, p0.y - 1.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p16), -0.78539816, 0.000001);
    }

    void TestCalcAngle2() {
        FPOINT p0(1.0, 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p0, p0), 0.0, 0.000001);

        FPOINT p1(5.0, 6.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p1, p1), 0.0, 0.000001);

        FPOINT p2(4.0, -1.0);
        FPOINT p3(5.0, 6.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p2, p3), 1.57079633, 0.000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p3, p2), -1.57079633, 0.000001);

        FPOINT p4(1.0, 5.0);
        FPOINT p5(5.0, 2.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p4, p5), -1.57079633, 0.000001);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p5, p4), 1.57079633, 0.000001);

        FPOINT p6(5.0, -2.0);
        FPOINT p7(-4.0, 4.0);
        BOOST_CHECK_CLOSE(MeaGeometry::CalcAngle(p0, p6, p7), -2.73670086, 0.000001);
    }
}

boost::unit_test_framework::test_suite* init_unit_test_suite(int, char* []) {
    if (!AfxWinInit(::GetModuleHandle(nullptr), nullptr, ::GetCommandLine(), 0)) {
        std::cerr << "Fatal Error: MFC initialization failed\n";
        return nullptr;
    }

    boost::unit_test_framework::test_suite* fsizeTestSuite = BOOST_TEST_SUITE("FSIZE Tests");
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestInitialSize));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestAddFSize));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestAddValue));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestMultFSize));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestMultSize));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestMultValue));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestAddAssign));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestSubAssign));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestMultAssign));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestLog10));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestFloor));
    fsizeTestSuite->add(BOOST_TEST_CASE(&TestValueSub));
    boost::unit_test_framework::framework::master_test_suite().add(fsizeTestSuite);

    boost::unit_test_framework::test_suite* frectTestSuite = BOOST_TEST_SUITE("FRECT Tests");
    frectTestSuite->add(BOOST_TEST_CASE(&TestInitialRectangle));
    boost::unit_test_framework::framework::master_test_suite().add(frectTestSuite);

    boost::unit_test_framework::test_suite* fpointTestSuite = BOOST_TEST_SUITE("FPOINT Tests");
    fpointTestSuite->add(BOOST_TEST_CASE(&TestInitialPoint));
    boost::unit_test_framework::framework::master_test_suite().add(fpointTestSuite);

    boost::unit_test_framework::test_suite* geomTestSuite = BOOST_TEST_SUITE("Geometry Tests");
    geomTestSuite->add(BOOST_TEST_CASE(&TestCalcLength));
    geomTestSuite->add(BOOST_TEST_CASE(&TestCalcCircumference));
    geomTestSuite->add(BOOST_TEST_CASE(&TestCalcSector));
    geomTestSuite->add(BOOST_TEST_CASE(&TestCalcAngle1));
    geomTestSuite->add(BOOST_TEST_CASE(&TestCalcAngle2));
    boost::unit_test_framework::framework::master_test_suite().add(geomTestSuite);

    return nullptr;
}
