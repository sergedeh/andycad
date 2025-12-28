#include "pch.h"
#include "../Draw.h"
#include "../line.h"
#include "../Cercle.h"
#include "../Vector.h"
#include "../Rectangle.h" 
#include "../Figure.h" // For CFigure base class

TEST(CDrawTest, TestConstruction) {
  CDraw draw;
  SUCCEED();
}

TEST(CDrawTest, AddLine) {
	CDraw draw;
	std::vector<CVector> v;
	v.push_back(CVector(0, 0));
	v.push_back(CVector(1, 1));
	draw.AddLine(v);
	ASSERT_EQ(draw.getFigures(), 1);
}

TEST(CDrawTest, AddCircle) {
	CDraw draw;
	draw.AddCircle(CVector(0, 0), 5);
	ASSERT_EQ(draw.getFigures(), 1);
}

TEST(CDrawTest, AddRectangle) {
	CDraw draw;
	draw.AddRectangle(CVector(0, 0), CVector(10, 10));
	ASSERT_EQ(draw.getFigures(), 1);
}

TEST(CDrawTest, DeleteObject) {
    CDraw draw;
    // Add a line to be deleted
    std::vector<CVector> v;
    v.push_back(CVector(0, 0));
    v.push_back(CVector(1, 1));
    draw.AddLine(v);
    ASSERT_EQ(draw.getFigures(), 1);

    // Delete the line
    draw.Delete(0); // Assuming index 0 for the first added figure
    ASSERT_EQ(draw.getFigures(), 0);
}

TEST(CDrawTest, AddArc) {
	CDraw draw;
	draw.AddArc(CVector(0, 0), CVector(5, 5), CVector(10, 0));
	ASSERT_EQ(draw.getFigures(), 1);
}

TEST(CDrawTest, AddSpline) {
	CDraw draw;
	std::vector<CVector> v;
	v.push_back(CVector(0, 0));
	v.push_back(CVector(1, 1));
	v.push_back(CVector(2, 0));
	draw.AddSpline(v); 
	ASSERT_EQ(draw.getFigures(), 1);
}

TEST(CDrawTest, OffsetObject) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    float offset_distance = 2.0f;
    draw.Offset(offset_distance); 
    ASSERT_EQ(draw.getFigures(), 1); // Ensure no new figure is added, just offset
}

TEST(CDrawTest, MoveToAbsolute) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    CFigure* fig = draw.getFigure(0);
    ASSERT_NE(fig, nullptr);

    CVector new_pos(10, 10);
    draw.MoveTo(fig, new_pos); 
    ASSERT_EQ(draw.getFigures(), 1); // Ensure no new figure is added, just moved
}

TEST(CDrawTest, FlipObject) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    bool vertical_flip = true;
    draw.flip(vertical_flip); 
    ASSERT_EQ(draw.getFigures(), 1); // Ensure no new figure is added, just flipped
}

TEST(CDrawTest, MirrorObject) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    CFigure* fig = draw.getFigure(0);
    ASSERT_NE(fig, nullptr);

    bool copy = false; // Mirror without creating a copy
    draw.mirror(fig, copy); 
    ASSERT_EQ(draw.getFigures(), 1); // Ensure no new figure is added, just mirrored
}

TEST(CDrawTest, RotateObject) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    // Assuming rotate operates on the last added figure or a selected figure
    // Without a specific selection mechanism exposed for testing, this is a weak test.
    // It asserts that the number of figures doesn't change after rotating.
    float angle = 90.0f; // 90 degrees
    short sens = 1;      // Direction
    CVector center(0, 0); // Rotation center
    draw.rotate(angle, sens, center); // Calling the overload without CFigure*
    ASSERT_EQ(draw.getFigures(), 1); 
}

TEST(CDrawTest, ScaleObject) {
    CDraw draw;
    draw.AddRectangle(CVector(0, 0), CVector(10, 10));
    ASSERT_EQ(draw.getFigures(), 1);
    
    // Assuming scale operates on the last added figure or a selected figure
    // Without a specific selection mechanism exposed for testing, this is a weak test.
    // It asserts that the number of figures doesn't change after scaling.
    float scale_factor = 2.0f; // Scale by 2
    short sens = 1;            // Direction/type of scaling
    CVector center(0, 0);      // Scaling center
    draw.scale(scale_factor, sens, center); // Calling the overload without CFigure*
    ASSERT_EQ(draw.getFigures(), 1); 
}
