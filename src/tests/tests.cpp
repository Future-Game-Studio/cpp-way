#include <memory>
#include <string>
#include <sstream>
#include "../thirdparty/acutest.h"
#include "../oop/shapes/helpers/exceptions.h"
#include "../oop/shapes/models/abstractions/shape.h"
#include "../oop/shapes/views/shapeConsoleView.h"
#include "../oop/shapes/views/cylinderConsoleView.h"
#include "../oop/shapes/controllers/mainController.h"

void test_example(void)
{
    void *mem; 

    mem = malloc(10);
    TEST_CHECK(mem != NULL);

    mem = realloc(mem, 20);
    TEST_CHECK(mem != NULL);

    free(mem);
}

void test_cylinder_view(void)
{
    // Prepare
    std::stringstream renderer;
    auto cylinder = Cylinder(1, 1);
    auto view = CylinderConsoleView(&cylinder, &renderer);

    // Act
    view.Render();
    TEST_CHECK(renderer.str().length() > 20);
}

void test_cylinder_view_null_logger(void)
{
    // Prepare
    auto cylinder = Cylinder(1, 1);
    auto view = CylinderConsoleView(&cylinder, nullptr);

    // Act
    view.Render();
}

void test_cylinder_view_onrender_throws_nullptr(void)
{
    // Prepare
    std::stringstream renderer;
    auto view = CylinderConsoleView(nullptr, &renderer);

    // Act
    TEST_EXCEPTION(view.Render(), NullObjectException);
}

void test_cylinder_view_onsetmodel_throws_nullptr(void)
{
    // Prepare
    std::stringstream renderer;
    auto view = CylinderConsoleView(nullptr, &renderer);

    // Act
    TEST_EXCEPTION(view.SetShape(nullptr), NullObjectException);
}

TEST_LIST = {
    {"test_example", test_example},
    {"test_cylinder_view", test_cylinder_view},
    {"test_cylinder_view_null_logger", test_cylinder_view_null_logger},
    {"test_cylinder_view_onrender_throws_nullptr", test_cylinder_view_onrender_throws_nullptr},
    {"test_cylinder_view_onsetmodel_throws_nullptr", test_cylinder_view_onsetmodel_throws_nullptr},
    {0}};