#include "Cone.hpp"
#include "Cube.hpp"
#include "FigureCollection.hpp"
#include "Sphere.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <numbers>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(SphereTest, VolumeAndRadius) {
    Sphere sphere(3.0);
    EXPECT_NEAR(sphere.metric(), 36.0 * std::numbers::pi, 1e-9);
    EXPECT_DOUBLE_EQ(sphere.radius(), 3.0);
}

TEST(CubeTest, VolumeAndEdge) {
    Cube cube(4.0);
    EXPECT_DOUBLE_EQ(cube.metric(), 64.0);
    EXPECT_DOUBLE_EQ(cube.edge(), 4.0);
}

TEST(ConeTest, VolumeAndSlantHeight) {
    Cone cone(3.0, 4.0);
    EXPECT_NEAR(cone.metric(), 12.0 * std::numbers::pi, 1e-9);
    EXPECT_DOUBLE_EQ(cone.slantHeight(), 5.0);
}

TEST(FigureTest, DefaultDimensionsGiveZeroVolume) {
    EXPECT_DOUBLE_EQ(Sphere().metric(), 0.0);
    EXPECT_DOUBLE_EQ(Cube().metric(), 0.0);
    EXPECT_DOUBLE_EQ(Cone().metric(), 0.0);
}

TEST(FigureTest, InvalidDimensionsThrow) {
    EXPECT_THROW(Sphere(-1.0), std::invalid_argument);
    EXPECT_THROW(Cube(std::numeric_limits<double>::infinity()), std::invalid_argument);
    EXPECT_THROW(Cone(1.0, -1.0), std::invalid_argument);
    EXPECT_THROW(Cone(std::numeric_limits<double>::quiet_NaN(), 1.0), std::invalid_argument);
}

TEST(FigureTest, InputAndOutputUseVirtualMethods) {
    Cone cone;
    Figure& figure = cone;
    std::istringstream input("3 4");
    input >> figure;
    EXPECT_FALSE(input.fail());
    EXPECT_DOUBLE_EQ(cone.slantHeight(), 5.0);
    std::ostringstream output;
    output << figure;
    EXPECT_NE(output.str().find("Cone: r=3 h=4"), std::string::npos);
}

TEST(FigureTest, InvalidInputDoesNotChangeObject) {
    Sphere sphere(2.0);
    std::istringstream input("-5");
    input >> sphere;
    EXPECT_TRUE(input.fail());
    EXPECT_DOUBLE_EQ(sphere.radius(), 2.0);
}

TEST(FigureTest, ComparisonUsesMetricAndTolerance) {
    Cube first(2.0);
    Cube close(2.0 + 1e-8);
    Cube different(3.0);
    EXPECT_TRUE(first == close);
    EXPECT_FALSE(first == different);
    EXPECT_DOUBLE_EQ(static_cast<double>(first), 8.0);
}

TEST(FigureTest, ClonePreservesTypeAndIsIndependent) {
    Sphere original(2.0);
    std::unique_ptr<Figure> copy(original.clone());
    auto* sphereCopy = dynamic_cast<Sphere*>(copy.get());
    ASSERT_NE(sphereCopy, nullptr);
    std::istringstream input("4");
    input >> *sphereCopy;
    EXPECT_DOUBLE_EQ(original.radius(), 2.0);
    EXPECT_DOUBLE_EQ(sphereCopy->radius(), 4.0);
}

TEST(CollectionTest, AddsDifferentTypesAndSumsVolumes) {
    FigureCollection figures;
    figures.add(new Sphere(0.0));
    figures.add(new Cube(2.0));
    figures.add(new Cone(3.0, 4.0));
    EXPECT_EQ(figures.size(), 3u);
    EXPECT_FALSE(figures.empty());
    EXPECT_NE(dynamic_cast<const Cube*>(&figures[1]), nullptr);
    EXPECT_NEAR(figures.totalMetric(), 8.0 + 12.0 * std::numbers::pi, 1e-9);
}

TEST(CollectionTest, RemovesAndShiftsElements) {
    FigureCollection figures;
    figures.add(new Cube(1.0));
    figures.add(new Sphere(2.0));
    figures.add(new Cone(3.0, 4.0));
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2u);
    EXPECT_NE(dynamic_cast<Cone*>(&figures[1]), nullptr);
    EXPECT_NEAR(figures.totalMetric(), 1.0 + 12.0 * std::numbers::pi, 1e-9);
}

TEST(CollectionTest, RejectsInvalidOperations) {
    FigureCollection figures;
    EXPECT_TRUE(figures.empty());
    EXPECT_THROW(figures.add(nullptr), std::invalid_argument);
    EXPECT_THROW(figures.remove(0), std::out_of_range);
    EXPECT_THROW(figures[0], std::out_of_range);
    const FigureCollection& constFigures = figures;
    EXPECT_THROW(constFigures[0], std::out_of_range);
}

TEST(CollectionTest, CopyConstructorMakesIndependentObjects) {
    FigureCollection original;
    original.add(new Sphere(2.0));
    original.add(new Cube(3.0));
    FigureCollection copy(original);
    ASSERT_EQ(copy.size(), 2u);
    EXPECT_NE(&copy[0], &original[0]);
    EXPECT_NE(dynamic_cast<Sphere*>(&copy[0]), nullptr);
    std::istringstream input("4");
    input >> copy[0];
    EXPECT_NE(copy[0].metric(), original[0].metric());
    copy.remove(1);
    EXPECT_EQ(original.size(), 2u);
}

TEST(CollectionTest, CopyAssignmentReplacesContents) {
    FigureCollection original;
    original.add(new Cube(2.0));
    FigureCollection copy;
    copy.add(new Sphere(5.0));
    copy = original;
    ASSERT_EQ(copy.size(), 1u);
    EXPECT_DOUBLE_EQ(copy.totalMetric(), 8.0);
    EXPECT_NE(&copy[0], &original[0]);
    copy = copy;
    EXPECT_DOUBLE_EQ(copy.totalMetric(), 8.0);
}

TEST(CollectionTest, MoveTransfersOwnership) {
    FigureCollection original;
    original.add(new Cube(2.0));
    Figure* address = &original[0];
    FigureCollection moved(std::move(original));
    EXPECT_TRUE(original.empty());
    ASSERT_EQ(moved.size(), 1u);
    EXPECT_EQ(&moved[0], address);
    FigureCollection destination;
    destination.add(new Sphere(1.0));
    destination = std::move(moved);
    EXPECT_TRUE(moved.empty());
    ASSERT_EQ(destination.size(), 1u);
    EXPECT_EQ(&destination[0], address);
}
